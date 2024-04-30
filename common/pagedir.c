#include "pagedir.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// Prototype for a helper function to check directory writability
#include <errno.h>

bool pagedir_init(const char *pageDirectory) {
    struct stat st;

    // Check if directory exists and is a directory
    if (stat(pageDirectory, &st) != 0) {
        perror("Error accessing directory");
        return false;
    }
    if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Provided path is not a directory\n");
        return false;
    }

    // Construct the pathname for the .crawler file in that directory
    char fileName[256]; // Increased size for longer paths
    snprintf(fileName, sizeof(fileName), "%s/.crawler", pageDirectory);

    // Open the file for writing; on error, return false.
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Failed to create .crawler file");
        return false;
    }

    // Close the file and return true.
    fclose(file);
    printf("File added to .crawler\n");
    return true;
}


void pagedir_save(const webpage_t* page, const char* pageDirectory, int docID) {
    // Validate input parameters
    if (page == NULL) {
        fprintf(stderr, "Invalid input to pagedir_save function\n");
        return;
    }

    // Calculate required buffer size and allocate memory
    int required_size = snprintf(NULL, 0, "%s/%d", pageDirectory, docID) + 1;
    char* filepath = malloc(required_size);
    if (filepath == NULL) {
        fprintf(stderr, "Failed to allocate memory for filepath\n");
        return;
    }

    // Construct the file path
    snprintf(filepath, required_size, "%s/%d", pageDirectory, docID);

    // Attempt to open the file for writing
    FILE* fp = fopen(filepath, "w");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file %s for writing\n", filepath);
        free(filepath); // Free memory on error before returning
        return;
    }
    else {
      fprintf(fp, "%s\n", webpage_getURL(page), '\n');
      fprintf(fp, "%d\n", webpage_getDepth(page), '\n');
      fprintf(fp, "%s\n", webpage_getHTML(page), '\n');
    }
  

   // Clean up resources
    fclose(fp);
    free(filepath);
}

