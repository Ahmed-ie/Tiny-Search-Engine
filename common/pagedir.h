#ifndef PAGEDIR_H
#define PAGEDIR_H

#include <stdbool.h>
#include "webpage.h"

// Initializes a directory for the crawler, creating a special file to mark it as such.
bool pagedir_init(const char* pageDirectory);

// Saves a webpage's content to a file within the specified directory, using the document ID to name the file.
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

// Updates a file path by appending a document ID to it, used for creating unique file names within a directory.
char* updateFilePointer(char* fp, int docID);

// Validates if a directory is suitable for storing crawler output by checking for a special file.
bool directoryValidate(char* dirPath);

// Loads a webpage from a file within the specified page directory.
webpage_t* pageload(char* current);

#endif // PAGEDIR_H
