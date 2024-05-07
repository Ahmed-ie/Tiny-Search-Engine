#include "index.h"
#include <stdio.h>
#include "pagedir.h"
#include "word.h"
#include "webpage.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s pageDirectory indexFilename\n", argv[0]);
        return 1;
    }

    char* pageDirectory = argv[1];
    char* indexFilename = argv[2];

    // Validate page directory
    if (!pagedir_validate(pageDirectory)) {
        fprintf(stderr, "The specified page directory is not valid.\n");
        return 1;
    }

    // Initialize index
    index_t* index = index_new(500);
    if (index == NULL) {
        fprintf(stderr, "Failed to create index.\n");
        return 1;
    }

   // Build index from pages
int docID = 1;
webpage_t* page;

while ((page = pagedir_load(pageDirectory, docID)) != NULL) {
    int pos = 0;
    char* word;

    while ((word = webpage_getNextWord(page, &pos)) != NULL) {
        normalizeWord(word);
        if (strlen(word) > 2) {
            index_insert(index, word, docID);
        }
        free(word);
    }

    webpage_delete(page);
    docID++;
}

// Print a more specific message once the loop is complete
if (page == NULL) {
    printf("Reached the end. No more files beyond document ID %d.\n", docID - 1);
}

    // Save index to file
    FILE* fp = fopen(indexFilename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file '%s' for writing.\n", indexFilename);
        index_delete(index);
        return 1;
    }
    index_save(fp, index);
    fclose(fp);
    index_delete(index);

    return 0;
}

