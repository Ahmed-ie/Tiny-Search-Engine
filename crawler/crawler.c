#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "webpage.h"
#include "hashtable.h"
#include "bag.h"
#include "pagedir.h"
#include "mem.h"
#include "unistd.h"

#define MAX_DEPTH 10

// Function prototypes
static void parse_arguments(int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, int maxDepth);
static void page_scan(webpage_t* page, hashtable_t* urls_seen, bag_t* pages_to_crawl);

int main(int argc, char* argv[]) {
    char* seedURL;
    char* pageDirectory;
    int maxDepth;

    // Parse command line arguments
    parse_arguments(argc, argv, &seedURL, &pageDirectory, &maxDepth);

    // Start crawling
    crawl(seedURL, pageDirectory, maxDepth);

    return 0;
}

// Parses command line arguments
static void parse_arguments(int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <seedURL> <pageDirectory> <maxDepth>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    *seedURL = normalizeURL(argv[1]);
    if (*seedURL == NULL || !isInternalURL(*seedURL)) {
        fprintf(stderr, "Invalid or external seed URL.\n");
        exit(EXIT_FAILURE);
    }
    *pageDirectory = argv[2];
    if (!pagedir_init(*pageDirectory)) {
        fprintf(stderr, "Error: pageDirectory '%s' is not writable or cannot be created\n", *pageDirectory);
        free(*seedURL); // Clean up seedURL memory
        exit(EXIT_FAILURE);
    }
    *maxDepth = atoi(argv[3]);
    if (*maxDepth < 0 || *maxDepth > MAX_DEPTH) {
        fprintf(stderr, "Error: maxDepth must be between 0 and %d\n", MAX_DEPTH);
        free(*seedURL); // Clean up seedURL memory
        exit(EXIT_FAILURE);
    }
}

// Definitions for crawl and page_scan would also include improved error handling and memory management.
// Continue crawling the web starting from the seed URL
static void crawl(char* seedURL, char* pageDirectory, int maxDepth) {
    int docID = 1;
    hashtable_t* urls_seen = hashtable_new(200);
    if (!urls_seen) {
        fprintf(stderr, "Error: Failed to create URL hashtable.\n");
        return;
    }

    bag_t* pages_to_crawl = bag_new();
    if (!pages_to_crawl) {
        fprintf(stderr, "Error: Failed to create pages to crawl bag.\n");
        hashtable_delete(urls_seen, free);
        return;
    }

    webpage_t* seedPage = webpage_new(seedURL, 0, NULL);
    if (!seedPage || !hashtable_insert(urls_seen, seedURL, "")) {
        fprintf(stderr, "Error: Failed to insert seed URL into seen hashtable.\n");
        webpage_delete(seedPage);  // Null-safe in most implementations
        hashtable_delete(urls_seen, NULL);
        bag_delete(pages_to_crawl, NULL);
        return;
    }

    bag_insert(pages_to_crawl, seedPage);

    webpage_t* currPage;
    while ((currPage = bag_extract(pages_to_crawl)) != NULL) {
        if (webpage_fetch(currPage)) {
            printf("%d fetched: %s\n", webpage_getDepth(currPage), webpage_getURL(currPage));
            pagedir_save(currPage, pageDirectory, docID);
            if (webpage_getDepth(currPage) < maxDepth) {
                page_scan(currPage, urls_seen, pages_to_crawl);
            }
        }
        webpage_delete(currPage);
        docID++;
    }

    hashtable_delete(urls_seen, NULL);
    bag_delete(pages_to_crawl, NULL);
}

// Scan the webpage for links and add them to the bag if they haven't been seen before
static void page_scan(webpage_t* page, hashtable_t* urls_seen, bag_t* pages_to_crawl) {
    int pos = 0;
    char* result;
    while ((result = webpage_getNextURL(page, &pos)) != NULL) {
        char* normalized = normalizeURL(result);
        free(result);  // Free result from webpage_getNextURL to avoid memory leaks
        if (normalized && isInternalURL(normalized) && hashtable_insert(urls_seen, normalized, "")) {
            webpage_t* new_page = webpage_new(normalized, webpage_getDepth(page) + 1, NULL);
            if (new_page) {
                bag_insert(pages_to_crawl, new_page);
            } else {
                free(normalized);  // Important to free normalized if webpage_new fails
            }
        } else {
            free(normalized);  // Free normalized URL if not inserted
        }
    }
}

