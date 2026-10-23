/*
 * copy.h
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * Copy bytes between two open file descriptors.
 */

#ifndef COPY_H
#define COPY_H

/*
 * copy_descriptor
 * Read from input_descriptor and write to output_descriptor
 * until the input ends.
 *
 * input_descriptor  - open file we read
 * output_descriptor - open file we write
 * return 0 if it worked, 1 if a read or write failed
 */
int copy_descriptor(int input_descriptor, int output_descriptor);

#endif
