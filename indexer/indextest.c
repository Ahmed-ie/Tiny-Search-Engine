#include "index.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s oldIndexFilename newIndexFilename\n", argv[0]);
        return 1;
    }

    char* oldIndexFilename = argv[1];
    char* newIndexFilename = argv[2];

    // Open the old index file for reading
    FILE* fp = fopen(oldIndexFilename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file '%s' for reading.\n", oldIndexFilename);
        return 1;
    }

    // Load the index from file
    // Assuming you know the number of slots or read it from somewhere
    int num_slots = 500; // You need to determine this value based on your application needs
    index_t* index = index_load(fp, num_slots);
    fclose(fp);

    if (index == NULL) {
        fprintf(stderr, "Failed to load index from '%s'.\n", oldIndexFilename);
        return 1;
    }

    // Open the new index file for writing
    fp = fopen(newIndexFilename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file '%s' for writing.\n", newIndexFilename);
        index_delete(index);
        return 1;
    }

    // Save the index to the new file
    index_save(fp, index);
    fclose(fp);
    index_delete(index);

    return 0;
}
