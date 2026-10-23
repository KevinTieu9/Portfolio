/*
 * screen.h
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Terminal file list. Arrow keys move. q quits.
 */

#ifndef SCREEN_H
#define SCREEN_H

/*
 * command_screen
 * Open a full-terminal file list of the vault.
 *
 * return 0 when the user quits, 1 if setup failed
 */
int command_screen(void);

#endif
