/*
 * lockbox.h
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Sizes and names shared by every .c file.
 */

#ifndef LOCKBOX_H
#define LOCKBOX_H

#define DEFAULT_VAULT_DIR "vault"  /* folder used when LOCKBOX_DIR is not set */
#define COPY_BUFFER_SIZE 4096  /* bytes copied in each read/write step */
#define PATH_BUFFER_SIZE 512  /* size of a full path string */
#define NAME_BUFFER_SIZE 256  /* size of a stored file name */
#define LINE_BUFFER_SIZE 256  /* size of one input line */
#define LOG_FILE_NAME "lockbox.log"  /* text log inside the vault */
#define LOG_LINE_SIZE 640  /* size of one log line */
#define INDEX_FILE_NAME "index.txt"  /* text index inside the vault */
#define INDEX_BIN_NAME "index.bin"  /* binary index inside the vault */
#define SCREEN_MAX_FILES 128  /* names the file list can show */

#endif
