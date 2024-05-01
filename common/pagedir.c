/*
 * Ahmed's pagedir.c
 * Author: Ahmed
 * File: pagedir.c
 * 
 * This file contains implementations for functions related to managing
 * directories and saving webpages.
 */

#include "pagedir.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
 
/*
 * Initializes a page directory for storing webpages.
 * Parameters:
 *   - pageDirectory: The directory path where the pages will be stored.
 * Returns:
 *   - true if initialization is successful, false otherwise.
 */
bool pagedir_init(const char *pageDirectory) {
    struct stat st;
 
    if (stat(pageDirectory, &st) != 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: Directory does not exist or is not a directory\n");
        return false;
    }
 
    char fileName[256];
    snprintf(fileName, sizeof(fileName), "%s/.crawler", pageDirectory);
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Failed to create .crawler file");
        return false;
    }
    fclose(file);
    return true;
}

/*
 * Saves a webpage to a file in the specified page directory.
 * Parameters:
 *   - page: The webpage to be saved.
 *   - pageDirectory: The directory path where the page will be saved.
 *   - docID: The identifier for the document.
 */
void pagedir_save(const webpage_t *page, const char *pageDirectory, int docID) {
    if (!page) {
        fprintf(stderr, "Invalid webpage\n");
        return;
    }
    
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%d", pageDirectory, docID);
    FILE *fp = fopen(filePath, "w");
    if (!fp) {
        fprintf(stderr, "Failed to open file %s for writing\n", filePath);
        return;
    }
 
    fprintf(fp, "%s\n%d\n%s", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page));
    fclose(fp);
}

