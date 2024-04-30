#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include "webpage.h"
#include <stdbool.h>

/**
 * pagedir_init - Initialize the page directory for the crawler.
 * Ensures the directory exists and is writable. If the directory does not exist,
 * it attempts to create it with appropriate permissions. This function should
 * be called before attempting to save pages to ensure the directory is
 * prepared.
 *
 * @param pageDirectory The directory to initialize.
 * @return true if the directory is ready to be used, false if an error occurred.
 */
bool pagedir_init(const char* pageDirectory);

/**
 * pagedir_save - Save a webpage's content into a specified directory with a unique ID.
 * The function constructs a file named with the docID within the directory
 * specified by pageDirectory. It writes the webpage's URL, depth, and HTML
 * content to this file. Each piece of information is written on a new line
 * starting with the URL, then the depth, and followed by the HTML content.
 *
 * @param page The webpage structure containing the page's content to save.
 * @param pageDirectory The directory where the page should be saved.
 * @param docID The unique identifier for the file, typically the sequence number of the page.
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, int docID);

#endif // __PAGEDIR_H

