/*
 * vault.h
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Vault folder, safe names, and full paths.
 */

#ifndef VAULT_H
#define VAULT_H

#include <stddef.h>

/*
 * ensure_vault
 * Create the vault folder if it is not there yet.
 * EEXIST means the folder already exists. That is not an error.
 *
 * return 0 if it worked, 1 if mkdir failed
 */
int ensure_vault(void);

/*
 * name_is_safe
 * A stored name must stay inside the vault folder.
 * Reject empty names, slashes, "." and "..".
 *
 * stored_name - name the caller wants to use inside vault/
 * return 1 if the name is usable, 0 if it is not
 */
int name_is_safe(const char *stored_name);
/*
 * base_name
 * Return the part after the last slash.
 * put /tmp/notes.txt should store notes.txt, not the whole path.
 *
 * path - path the user typed
 */
const char *base_name(const char *path);
/*
 * make_vault_path
 * Build the full path of one stored file.
 *
 * path_buffer - caller array
 * path_size   - size of that array
 * stored_name - plain file name, no slashes
 * return 0 if it worked, 1 if the name is bad or the path is too long
 */
int make_vault_path(char *path_buffer, size_t path_size,
                    const char *stored_name);
/*
 * make_log_path
 * Build the path of vault/lockbox.log.
 *
 * return 0 if it worked, 1 if the path is too long
 */
int make_log_path(char *path_buffer, size_t path_size);

/*
 * is_bookkeeping_name
 * The log, index, fifo, and stats files live in the vault folder
 * but they are not files the user stored with put.
 *
 * entry_name - a name from readdir
 * return 1 if this name should be skipped in the file list
 */
int is_bookkeeping_name(const char *entry_name);

int make_index_path(char *path_buffer, size_t path_size);
int make_index_bin_path(char *path_buffer, size_t path_size);

#endif
