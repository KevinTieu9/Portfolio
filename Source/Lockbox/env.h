/*
 * env.h
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Vault folder from the environment and the -d switch.
 */

#ifndef ENV_H
#define ENV_H

/*
 * vault_directory
 * Pick the folder that holds stored files.
 * LOCKBOX_DIR wins if it is set, unless -d was used.
 * return pointer to that folder name
 */
const char *vault_directory(void);
/*
 * apply_start_settings
 * Set umask so new files are not group or world writable
 * unless we pass a mode to open or mkdir.
 */
void apply_start_settings(void);
/*
 * set_vault_directory
 * Remember a folder from the -d switch for this run.
 *
 * folder - path typed after -d
 */
void set_vault_directory(const char *folder);
/*
 * command_env
 * Print USER, HOME, LOCKBOX_DIR, and the vault folder in use.
 * return 0
 */
int command_env(void);

#endif
