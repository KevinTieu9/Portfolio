/*
 * copy.c
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Copy bytes between two open file descriptors.
 */

#include "copy.h"
#include "lockbox.h"

#include <stdio.h>
#include <unistd.h>

/*
 * copy_descriptor
 * Read from input_descriptor and write to output_descriptor
 * until the input ends. write may send fewer bytes than asked,
 * so the inner loop keeps going until this chunk is done.
 *
 * input_descriptor  - open file we read
 * output_descriptor - open file we write
 * return 0 if it worked, 1 if a read or write failed
 */
int copy_descriptor(int input_descriptor, int output_descriptor)
{
    char buffer[COPY_BUFFER_SIZE];
    ssize_t bytes_read;
    ssize_t bytes_written;
    ssize_t bytes_left;
    char *write_position;

    /* Read the first chunk */
    bytes_read = read(input_descriptor, buffer, sizeof(buffer));
    while (bytes_read > 0) {
        write_position = buffer;
        bytes_left = bytes_read;
        while (bytes_left > 0) {
            bytes_written = write(output_descriptor, write_position,
                                  (size_t)bytes_left);
            if (bytes_written < 0) {
                perror("write");
                return 1;
            }
            bytes_left = bytes_left - bytes_written;
            write_position = write_position + bytes_written;
        }
        bytes_read = read(input_descriptor, buffer, sizeof(buffer));
    }
    if (bytes_read < 0) {
        perror("read");
        return 1;
    }
    return 0;
}
