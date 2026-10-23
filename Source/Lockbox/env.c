/*
 * env.c
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * getenv, umask, and the -d folder override.
 */

#include "env.h"
#include "lockbox.h"

#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

static const char *override_directory = NULL;

/*
 * vault_directory
 * Use the -d folder if it was set. Otherwise use LOCKBOX_DIR.
 * If neither is set, use the default vault folder.
 *
 * return pointer to that folder name
 */
const char *vault_directory(void)
{
    const char *from_environment;

    if (override_directory != NULL && override_directory[0] != '\0') {
        return override_directory;
    }
    from_environment = getenv("LOCKBOX_DIR");
    if (from_environment != NULL && from_environment[0] != '\0') {
        return from_environment;
    }
    return DEFAULT_VAULT_DIR;
}

/*
 * apply_start_settings
 * Set umask so new files are not group or world writable
 * unless we pass a mode to open or mkdir.
 */
/*
 * apply_start_settings
 * Set the process umask so new files are not group or world writable
 * unless a mode is passed to open or mkdir.
 *
 * return nothing
 */
void apply_start_settings(void)
{
    umask(077);
}

/*
 * set_vault_directory
 * Remember a folder from the -d switch for this run.
 *
 * folder - path typed after -d
 * return nothing
 */
void set_vault_directory(const char *folder)
{
    override_directory = folder;
}

/*
 * command_env
 * Print USER, HOME, LOCKBOX_DIR, and the vault folder in use.
 *
 * return 0
 */
int command_env(void)
{
    const char *home;
    const char *user;
    const char *from_environment;

    home = getenv("HOME");
    user = getenv("USER");
    from_environment = getenv("LOCKBOX_DIR");
    printf("USER=%s\n", user != NULL ? user : "(not set)");
    printf("HOME=%s\n", home != NULL ? home : "(not set)");
    printf("LOCKBOX_DIR=%s\n",
           from_environment != NULL ? from_environment : "(not set)");
    printf("vault in use=%s\n", vault_directory());
    return 0;
}
