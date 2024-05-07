#ifndef __INDEX_H
#define __INDEX_H

#include "counters.h"

// Define the index_t type as a struct, which details are hidden from the users of the index.
typedef struct index index_t;

// Function to create a new index structure, specifying the number of slots for the hashtable.
index_t *index_new(const int num_slots);

// Function to add a word and document ID to the index.
bool index_insert(index_t *index, const char *word, const int docID);

// Function to get the counters set associated with a word.
counters_t *index_get(index_t *index, const char *word);

// Function to save the index to a file.
void index_save(FILE *fp, index_t *index);

// Helper function for index_save to handle the saving of individual words and their counters.
void index_save_helper(void *arg, const char *key, void *item);

// Helper function to save individual counters (part of the counters set for a word).
void counters_save_helper(void *arg, const int key, const int count);

// Function to load an index from a file.
index_t *index_load(FILE *fp, const int num_slots);

// Function to delete and free all memory associated with the index.
void index_delete(index_t *index);

#endif // __INDEX_H
