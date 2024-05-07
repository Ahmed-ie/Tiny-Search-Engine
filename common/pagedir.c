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
#include "file.h"

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

/*
 * Validates if a directory was used by the crawler.
 * Parameters:
 *   - pageDirectory: The directory path to validate.
 * Returns:
 *   - true if the directory contains a .crawler file, false otherwise.
 */

bool pagedir_validate(const char *pageDirectory) {
    char path[256];
    snprintf(path, sizeof(path), "%s/.crawler", pageDirectory);
    struct stat st;
    if (stat(path, &st) == 0) {
        return true;  // The .crawler file exists
    }
    return false;  // The .crawler file does not exist
}

/*
 * Loads a webpage from a file in the specified page directory.
 * Parameters:
 *   - pageDirectory: The directory path where the pages are stored.
 *   - docID: The identifier for the document to load.
 * Returns:
 *   - webpage_t pointer to the loaded webpage, or NULL if an error occurs.
 */

webpage_t *pagedir_load(const char *pageDirectory, int docID) {
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%d", pageDirectory, docID);

    FILE *fp = fopen(filePath, "r");
    if (!fp) {
        //fprintf(stderr, "Failed to open file %s for reading\n", filePath);
        return NULL;
    }

    // Read URL line
    char *url = file_readLine(fp);
    if (url == NULL) {
        fprintf(stderr, "Warning: Corrupted or incomplete file at %s (URL missing)\n", filePath);
        fclose(fp);
        return NULL;
    }

    // Read the depth value
    int depth;
    if (fscanf(fp, "%d", &depth) != 1) {
        fprintf(stderr, "Warning: Corrupted or incomplete file at %s (Depth value missing)\n", filePath);
        free(url);
        fclose(fp);
        return NULL;
    }
    fgetc(fp);  // Consume the newline character after the depth integer

    // Read the remaining HTML content
    char *html = file_readFile(fp);
    fclose(fp);

    // Check if we successfully read the URL and HTML
    if (html == NULL) {
        fprintf(stderr, "Warning: Corrupted or incomplete file at %s (HTML content missing)\n", filePath);
        free(url);
        return NULL;
    }

    // Create the webpage with the read data
    webpage_t *page = webpage_new(url, depth, html);

    // Return the created webpage
    return page;
}