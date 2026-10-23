/*
 * screen.c
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Terminal file list of stored names.
 */

#include "screen.h"
#include "lockbox.h"
#include "vault.h"
#include "env.h"

#include <ncurses.h>
#include <string.h>
#include <dirent.h>

/*
 * collect_stored_names
 * Fill names with stored file names. Skip helper files.
 *
 * names     - caller array of name buffers
 * max_names - how many names fit
 * return how many names were stored
 */
static int collect_stored_names(char names[][NAME_BUFFER_SIZE], int max_names)
{
    DIR *vault_folder;
    struct dirent *entry;
    int count;

    count = 0;
    vault_folder = opendir(vault_directory());
    if (vault_folder == NULL) {
        return 0;
    }
    entry = readdir(vault_folder);
    while (entry != NULL && count < max_names) {
        if (!is_bookkeeping_name(entry->d_name)) {
            strncpy(names[count], entry->d_name, NAME_BUFFER_SIZE - 1);
            names[count][NAME_BUFFER_SIZE - 1] = '\0';
            count = count + 1;
        }
        entry = readdir(vault_folder);
    }
    closedir(vault_folder);
    return count;
}

/*
 * draw_file_list
 * Draw the title and each stored name. The highlighted row is reversed.
 *
 * names            - stored names
 * file_count       - how many names
 * highlight_index  - row the user is on
 */
static void draw_file_list(char names[][NAME_BUFFER_SIZE], int file_count,
                           int highlight_index)
{
    int row;

    clear();
    mvprintw(0, 0, "lockbox file list");
    mvprintw(1, 0, "up/down move   enter selects   q quits");
    if (file_count == 0) {
        mvprintw(3, 2, "(no stored files)");
        refresh();
        return;
    }
    row = 0;
    while (row < file_count) {
        if (row == highlight_index) {
            attron(A_REVERSE);
        }
        mvprintw(row + 3, 2, "%s", names[row]);
        if (row == highlight_index) {
            attroff(A_REVERSE);
        }
        row = row + 1;
    }
    refresh();
}

/*
 * command_screen
 * Show stored names on a terminal screen.
 *
 * return 0 when the user quits
 */
int command_screen(void)
{
    char names[SCREEN_MAX_FILES][NAME_BUFFER_SIZE];
    int file_count;
    int highlight_index;
    int key;

    file_count = collect_stored_names(names, SCREEN_MAX_FILES);
    highlight_index = 0;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    while (1) {
        draw_file_list(names, file_count, highlight_index);
        key = getch();
        if (key == 'q' || key == 'Q') {
            break;
        }
        if (key == KEY_UP && highlight_index > 0) {
            highlight_index = highlight_index - 1;
        } else if (key == KEY_DOWN && highlight_index + 1 < file_count) {
            highlight_index = highlight_index + 1;
        }
        else if (key == '\n' || key == KEY_ENTER) {
            if (file_count > 0) {
                mvprintw(file_count + 5, 2, "chosen: %s", names[highlight_index]);
                refresh();
            }
        }
    }
    endwin();
    return 0;
}
