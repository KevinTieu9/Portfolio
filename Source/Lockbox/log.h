/*
 * log.h
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Append-only text log inside the vault.
 */

#ifndef LOG_H
#define LOG_H

/*
 * log_action
 * Append one line to vault/lockbox.log.
 * A failed log write does not undo the command.
 *
 * message - text to store
 */
void log_action(const char *message);

#endif
