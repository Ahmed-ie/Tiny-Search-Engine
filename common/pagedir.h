#ifndef PAGEDIR_H
#define PAGEDIR_H

#include <stdbool.h>
#include "webpage.h"

/*
 * Initializes a directory for the crawler, creating a special file to mark it as such.
 * Returns true if the directory exists and the marker file was successfully created, false otherwise.
 */
bool pagedir_init(const char* pageDirectory);

/*
 * Validates if a directory was used by the crawler by checking for a .crawler file.
 * Returns true if the .crawler file is found, false otherwise.
 */
bool pagedir_validate(const char* pageDirectory);

/*
 * Saves a webpage's content to a file within the specified directory, using the document ID to name the file.
 * The webpage's URL, depth, and HTML content are written to the file.
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, int docID);

/*
 * Loads a webpage from a file within the specified page directory.
 * The file to be read is identified by the document ID.
 * Returns a pointer to a newly allocated webpage_t if successful, NULL otherwise.
 */
webpage_t* pagedir_load(const char* pageDirectory, int docID);

#endif // PAGEDIR_H
