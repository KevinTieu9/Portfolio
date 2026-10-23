/*
 * commands.c
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * put copies a file in. get copies it out. list names what is stored.
 */

#include "commands.h"
#include "lockbox.h"
#include "vault.h"
#include "env.h"
#include "log.h"
#include "copy.h"
#include "index.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

/*
 * print_usage
 * How to run this program. Writes to stderr.
 *
 * program_name - argument_list[0]
 * return nothing
 */
void print_usage(const char *program_name)
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "  %s put <file>\n", program_name);
    fprintf(stderr, "  %s get <name> <outfile>\n", program_name);
    fprintf(stderr, "  %s list\n", program_name);
    fprintf(stderr, "  %s env\n", program_name);
    fprintf(stderr, "  %s screen\n", program_name);
    fprintf(stderr, "  %s index\n", program_name);
    fprintf(stderr, "  %s -d DIR <command>\n", program_name);
}

/*
 * command_put
 * Copy source_path into the vault under its base name.
 * O_EXCL refuses to overwrite a name that is already stored.
 *
 * source_path - file the user wants to store
 * return 0 if it worked, 1 if it failed
 */
int command_put(const char *source_path)
{
    int input_descriptor;
    int output_descriptor;
    char vault_path[PATH_BUFFER_SIZE];
    const char *stored_name;
    char log_line[LOG_LINE_SIZE];
    struct stat file_info;

    stored_name = base_name(source_path);
    if (make_vault_path(vault_path, sizeof(vault_path), stored_name) != 0) {
        return 1;
    }
    input_descriptor = open(source_path, O_RDONLY);
    if (input_descriptor < 0) {
        perror(source_path);
        return 1;
    }
    output_descriptor = open(vault_path, O_WRONLY | O_CREAT | O_EXCL, 0600);
    if (output_descriptor < 0) {
        perror(vault_path);
        close(input_descriptor);
        return 1;
    }
    if (copy_descriptor(input_descriptor, output_descriptor) != 0) {
        close(input_descriptor);
        close(output_descriptor);
        return 1;
    }
    close(input_descriptor);
    close(output_descriptor);
    if (stat(vault_path, &file_info) == 0) {
        index_record_put(stored_name, (long)file_info.st_size);
    }
    snprintf(log_line, sizeof(log_line), "PUT %s -> %s",
             source_path, vault_path);
    log_action(log_line);
    printf("stored %s\n", vault_path);
    return 0;
}

/*
 * command_get
 * Copy a stored file out to output_path.
 *
 * stored_name - name inside the vault
 * output_path - file to write on the outside
 * return 0 if it worked, 1 if it failed
 */
int command_get(const char *stored_name, const char *output_path)
{
    int input_descriptor;
    int output_descriptor;
    char vault_path[PATH_BUFFER_SIZE];
    char log_line[LOG_LINE_SIZE];

    if (make_vault_path(vault_path, sizeof(vault_path), stored_name) != 0) {
        return 1;
    }
    input_descriptor = open(vault_path, O_RDONLY);
    if (input_descriptor < 0) {
        perror(vault_path);
        return 1;
    }
    output_descriptor = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_descriptor < 0) {
        perror(output_path);
        close(input_descriptor);
        return 1;
    }
    if (copy_descriptor(input_descriptor, output_descriptor) != 0) {
        close(input_descriptor);
        close(output_descriptor);
        return 1;
    }
    close(input_descriptor);
    close(output_descriptor);
    snprintf(log_line, sizeof(log_line), "GET %s -> %s",
             stored_name, output_path);
    log_action(log_line);
    printf("wrote %s\n", output_path);
    return 0;
}

/*
 * command_list
 * Walk the vault folder with opendir and readdir.
 *
 * return 0 if it worked, 1 if the folder would not open
 */
int command_list(void)
{
    DIR *vault_folder;
    struct dirent *entry;
    int file_count;

    vault_folder = opendir(vault_directory());
    if (vault_folder == NULL) {
        perror(vault_directory());
        return 1;
    }
    file_count = 0;
    entry = readdir(vault_folder);
    while (entry != NULL) {
        if (!is_bookkeeping_name(entry->d_name)) {
            printf("%s\n", entry->d_name);
            file_count = file_count + 1;
        }
        entry = readdir(vault_folder);
    }
    closedir(vault_folder);
    log_action("LIST");
    printf("(%d file%s)\n", file_count, file_count == 1 ? "" : "s");
    return 0;
}
