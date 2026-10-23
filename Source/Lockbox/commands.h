/*
 * commands.h
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * put, get, list, and the usage text.
 */

#ifndef COMMANDS_H
#define COMMANDS_H

/*
 * print_usage
 * How to run this program. Writes to stderr.
 *
 * program_name - argument_list[0]
 */
void print_usage(const char *program_name);

/*
 * command_put
 * Copy source_path into the vault under its base name.
 *
 * source_path - file the user wants to store
 * return 0 if it worked, 1 if it failed
 */
int command_put(const char *source_path);

/*
 * command_get
 * Copy a stored file out to output_path.
 *
 * stored_name - name inside the vault
 * output_path - file to write on the outside
 * return 0 if it worked, 1 if it failed
 */
int command_get(const char *stored_name, const char *output_path);

/*
 * command_list
 * Walk the vault folder and print stored names.
 *
 * return 0 if it worked, 1 if the folder would not open
 */
int command_list(void);

#endif
