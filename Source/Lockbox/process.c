/*
 * process.c
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * status uses fork. hash uses a pipe. SIGINT stops a blocked wait.
 */

#include "process.h"
#include "lockbox.h"
#include "vault.h"
#include "env.h"
#include "log.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

/*
 * handle_interrupt
 * Empty handler for SIGINT. The call that was blocked returns
 * so the program can exit cleanly.
 *
 * signal_number - the signal that arrived (unused)
 */
static void handle_interrupt(int signal_number)
{
    (void)signal_number;
}

/*
 * install_interrupt_handler
 * Catch SIGINT so a blocked read or accept can return.
 */
void install_interrupt_handler(void)
{
    signal(SIGINT, handle_interrupt);
}
