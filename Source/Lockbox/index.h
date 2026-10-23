/*
 * index.h
 * CS 375 — lockbox
 *
 * Author: Kevin Tieu
 *
 * On-disk records of stored files.
 */

#ifndef INDEX_H
#define INDEX_H

/*
 * index_record_put
 * Remember that stored_name was put, and how big it is.
 *
 * stored_name - name inside the vault
 * file_size   - byte count
 * return 0 if it worked, 1 if the index could not be written
 */
int index_record_put(const char *stored_name, long file_size);

/*
 * command_index
 * Print every binary record.
 *
 * return 0
 */
int command_index(void);

#endif
