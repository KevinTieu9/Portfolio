/*
 * index.c
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Text index plus binary records and a file lock.
 */

#include "index.h"
#include "lockbox.h"
#include "vault.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

struct vault_record {
    char file_name[NAME_BUFFER_SIZE];
    long file_size;
    time_t stored_time;
};

/*
 * lock_descriptor
 * Lock the index file so only one process writes at a time.
 *
 * file_descriptor - open index file
 * return 0 if the lock was taken, -1 if it failed
 */
static int lock_descriptor(int file_descriptor)
{
    struct flock lock;

    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    return fcntl(file_descriptor, F_SETLKW, &lock);
}

/*
 * unlock_descriptor
 * Release the lock on the index file.
 *
 * file_descriptor - open index file
 * return 0 if the lock was released, -1 if it failed
 */
static int unlock_descriptor(int file_descriptor)
{
    struct flock lock;

    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    return fcntl(file_descriptor, F_SETLK, &lock);
}

/*
 * index_record_put
 * Append a text line and a binary record.
 *
 * stored_name - name inside the vault
 * file_size   - byte count
 * return 0 if it worked, 1 if a write failed
 */
int index_record_put(const char *stored_name, long file_size)
{
    FILE *text_file;
    int binary_descriptor;
    char text_path[PATH_BUFFER_SIZE];
    char binary_path[PATH_BUFFER_SIZE];
    struct vault_record record;

    if (make_index_path(text_path, sizeof(text_path)) != 0) {
        return 1;
    }
    if (make_index_bin_path(binary_path, sizeof(binary_path)) != 0) {
        return 1;
    }
    text_file = fopen(text_path, "a");
    if (text_file == NULL) {
        perror(text_path);
        return 1;
    }
    fprintf(text_file, "%s %ld\n", stored_name, file_size);
    fclose(text_file);

    memset(&record, 0, sizeof(record));
    strncpy(record.file_name, stored_name, NAME_BUFFER_SIZE - 1);
    record.file_size = file_size;
    record.stored_time = time(NULL);

    binary_descriptor = open(binary_path, O_WRONLY | O_CREAT | O_APPEND, 0600);
    if (binary_descriptor < 0) {
        perror(binary_path);
        return 1;
    }
    if (lock_descriptor(binary_descriptor) == -1) {
        perror("fcntl lock");
        close(binary_descriptor);
        return 1;
    }
    if (write(binary_descriptor, &record, sizeof(record)) !=
        (ssize_t)sizeof(record)) {
        perror("write index.bin");
        close(binary_descriptor);
        return 1;
    }
    unlock_descriptor(binary_descriptor);
    close(binary_descriptor);
    return 0;
}

/*
 * command_index
 * Print every binary record.
 *
 * return 0
 */
int command_index(void)
{
    int binary_descriptor;
    char binary_path[PATH_BUFFER_SIZE];
    struct vault_record record;
    ssize_t bytes_read;

    if (make_index_bin_path(binary_path, sizeof(binary_path)) != 0) {
        return 1;
    }
    binary_descriptor = open(binary_path, O_RDONLY);
    if (binary_descriptor < 0) {
        printf("no binary index yet\n");
        return 0;
    }
    bytes_read = read(binary_descriptor, &record, sizeof(record));
    while (bytes_read == (ssize_t)sizeof(record)) {
        printf("%s %ld\n", record.file_name, record.file_size);
        bytes_read = read(binary_descriptor, &record, sizeof(record));
    }
    close(binary_descriptor);
    return 0;
}
