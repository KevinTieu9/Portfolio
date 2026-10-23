# Lockbox

**Course:** Personal Project for CS 375 — Fall 2026  
**Author:** Kevin Tieu

## Overview

A multi-feature command-line utility. It dispatches commands, copies files, handles environment variables, maintains a binary index, logs activity, controls processes, offers a screen-based menu, and supports shared-memory statistics, named pipes, and a multi-threaded server.

Requires a Linux operating system or WSL to run and will not run natively on Windows.

## What the Program Does

The main program reads command-line options and routes work to modules for copy, environment, index, log, process, terminal, menu, FIFO, shared-memory statistics, and vault operations. A companion client program talks to the server. Data is stored in fixed binary records, plain-text logs, and a memory-mapped statistics file.

## Files

Source files in the finished program:

| File | Description |
|------|-------------|
| `main.c`, `lockbox.h` | Entry point and shared definitions |
| `commands.c/.h` | Command dispatch |
| `copy.c/.h` | File copy |
| `env.c/.h` | Environment handling |
| `index.c/.h` | Binary index |
| `log.c/.h` | Activity log |
| `process.c/.h` | Process control |
| `term.c/.h` | Terminal attributes |
| `menu.c/.h` | Menu interface |
| `vault.c/.h` | Vault storage |
| `ipc.c/.h` | Shared-memory counters with process-shared semaphore |
| `fifo.c/.h` | Named-pipe support |
| `serve.c/.h` | Multi-threaded server |
| `client.c` | Client for the server |

## Techniques

- File I/O and binary records
- `getopt` for options
- Process control
- Terminal attributes (termios)
- Memory-mapped shared statistics protected by a process-shared semaphore
- Named pipes (FIFOs)
- POSIX threads (one thread per client)
- Sockets

## Build and Run

```bash
make
./Tieu_K_lockbox
```
