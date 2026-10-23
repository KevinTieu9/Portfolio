/*
 * main.c
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Entry point. Parse the command line and call one command.
 */

#define _POSIX_C_SOURCE 200809L

#include "lockbox.h"
#include "env.h"
#include "vault.h"
#include "commands.h"
#include "screen.h"
#include "index.h"
#include "process.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

/*
 * main
 * Start the program. Read the command line and run one command.
 *
 * argument_count - how many words are on the command line
 * argument_list  - those words. argument_list[0] is the program name
 * return 0 if it worked, 1 if it failed
 */
int main(int argument_count, char *argument_list[])
{
    int option_letter;
    int first_command_index;

    apply_start_settings();
    install_interrupt_handler();

    opterr = 0;
    option_letter = getopt(argument_count, argument_list, "d:");
    while (option_letter != -1) {
        if (option_letter == 'd') {
            set_vault_directory(optarg);
        } else {
            print_usage(argument_list[0]);
            return 1;
        }
        option_letter = getopt(argument_count, argument_list, "d:");
    }
    first_command_index = optind;
    if (first_command_index >= argument_count) {
        print_usage(argument_list[0]);
        return 1;
    }
    if (ensure_vault() != 0) {
        return 1;
    }
    if (strcmp(argument_list[first_command_index], "put") == 0) {
        if (first_command_index + 1 >= argument_count) {
            print_usage(argument_list[0]);
            return 1;
        }
        return command_put(argument_list[first_command_index + 1]);
    }
    if (strcmp(argument_list[first_command_index], "get") == 0) {
        if (first_command_index + 2 >= argument_count) {
            print_usage(argument_list[0]);
            return 1;
        }
        return command_get(argument_list[first_command_index + 1],
                           argument_list[first_command_index + 2]);
    }
    if (strcmp(argument_list[first_command_index], "list") == 0) {
        return command_list();
    }
    if (strcmp(argument_list[first_command_index], "env") == 0) {
        return command_env();
    }
    if (strcmp(argument_list[first_command_index], "screen") == 0) {
        return command_screen();
    }
    if (strcmp(argument_list[first_command_index], "index") == 0) {
        return command_index();
    }
    fprintf(stderr, "unknown command: %s\n",
            argument_list[first_command_index]);
    print_usage(argument_list[0]);
    return 1;
}
