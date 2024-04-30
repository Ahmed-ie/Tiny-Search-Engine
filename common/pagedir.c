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
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%d", pageDirectory, docID);
    FILE* fp = fopen(filepath, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", filepath);
        return;
    }

    // Successfully opened the file, now write the data
    if (fprintf(fp, "%s\n%d\n%s", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page)) < 0) {
        fprintf(stderr, "Error writing to file %s\n", filepath);
        fclose(fp);
        return;
    }

    fclose(fp);
    return;
}
