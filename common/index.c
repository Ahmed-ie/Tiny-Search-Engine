#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "index.h"
#include "counters.h"
#include "file.h" 

/**************** Local Types ****************/
typedef struct index {
    hashtable_t *ht;
} index_t; 

/**************** index_new() ****************/
index_t *index_new(const int num_slots) {
    index_t *index = malloc(sizeof(index_t));
    if(index==NULL) {
        return NULL; 

    }
    index ->ht = hashtable_new(num_slots);
    if(index ->ht == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for index\n");
        free(index); 
        return NULL;
    }
    
    return index; 
}

/**************** index_insert() ****************/
bool index_insert(index_t *index, const char *word, const int docID) {
    if(index == NULL || word == NULL) {
        return false; 
    }
    counters_t *cts; 
    
    // find the counters set for the word or create it if none exists 

    if ((cts = hashtable_find(index ->ht, word)) == NULL) {
        cts= counters_new(); 
        if (cts == NULL) {
            return false; 
        }
        hashtable_insert(index ->ht, word, cts);
    }

    //increment the count for the given docID

    counters_add(cts, docID); 
    return true;
}

/**************** index_get() ****************/
counters_t *index_get(index_t *index, const char *word) {
    if (index == NULL || word == NULL) {
        return NULL;
    }
    return hashtable_find(index->ht, word);
}

/**************** index_save() ****************/

void index_save(FILE *fp, index_t *index) {
    if (fp != NULL && index != NULL) {
        hashtable_iterate(index ->ht, fp, index_save_helper);
    }
}

/**************** index_save_helper() ****************/
void index_save_helper(void *arg, const char *key, void *item) {
    FILE *fp = (FILE *)arg; 
    counters_t *cts = (counters_t *)item; 
    fprintf(fp, "%s ", key);
    counters_iterate(cts, fp, counters_save_helper);
    fprintf(fp, "\n");
}
/**************** counters_save_helper() ****************/
void counters_save_helper(void *arg, const int key, const int count) {
    FILE *fp = (FILE *)arg;
    fprintf(fp, "%d %d ", key, count);
}

/**************** index_load() ***************
index_t *index_load(FILE *fp, const int num_slots) {
    index_t *index = index_new(num_slots);
    if (index == NULL) {
        return NULL; // Error creating index
    }

    char *word = NULL;
    int docID, count;

    while ((word = file_readWord(fp)) != NULL) {
        while (fscanf(fp, "%d %d ", &docID, &count) == 2) {
            // Insert the word 'count' times into the index
            for (int i = 0; i < count; i++) {
                if (!index_insert(index, word, docID)) {
                    fprintf(stderr, "Error inserting word '%s' into index.\n", word);
                }
            }
        }
        free(word);
    }
    return index;
}
*/

index_t *index_load(FILE *fp, const int num_slots) {
    index_t *index = index_new(num_slots);
    if (index == NULL) {
        return NULL; // Error creating index
    }

    char *word = NULL;
    int docID, count;

    while ((word = file_readWord(fp)) != NULL) {
        while (fscanf(fp, "%d %d ", &docID, &count) == 2) {
            // Insert the word 'count' times into the index
            for (int i = 0; i < count; i++) {
                if (!index_insert(index, word, docID)) {
                    fprintf(stderr, "Error inserting word '%s' into index.\n", word);
                }
            }
        }
        free(word);
    }

    return index;
}


/**************** index_delete() ****************/
void index_delete(index_t *index) {
    if (index != NULL) {
        hashtable_delete(index->ht, (void (*)(void *))counters_delete);
        free(index);
    }
}