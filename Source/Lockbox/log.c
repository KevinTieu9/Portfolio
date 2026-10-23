/*
 * log.c
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Open the log with fopen and append one line.
 */

#include "log.h"
#include "lockbox.h"
#include "vault.h"

#include <stdio.h>

/*
 * log_action
 * Append one line to vault/lockbox.log.
 * "a" keeps old lines. A failed log write does not undo the command.
 *
 * message - text to store
 * return nothing
 */
void log_action(const char *message)
{
    FILE *log_file;
    char log_path[PATH_BUFFER_SIZE];

    if (make_log_path(log_path, sizeof(log_path)) != 0) {
        return;
    }
    log_file = fopen(log_path, "a");
    if (log_file == NULL) {
        perror(log_path);
        return;
    }
    fprintf(log_file, "%s\n", message);
    fclose(log_file);
}
