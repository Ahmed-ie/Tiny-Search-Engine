/*
 * Ahmed's Web Crawler
 * Author: Ahmed
 * File: crawler.c
 * Description: A simple web crawler program that crawls webpages starting from a seed URL and saves them to a specified directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webpage.h"
#include "hashtable.h"
#include "bag.h"
#include "pagedir.h"

#define MAX_DEPTH 10

// Function prototypes
static void parse_arguments(int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, int maxDepth);
static void page_scan(webpage_t* page, int depth, hashtable_t* urls_seen, bag_t* pages_to_crawl);
static bool is_internal_link(const char* url);

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

// Parse command line arguments
static void parse_arguments(int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth) {
    if (argc != 4) {
        // Print usage message if incorrect number of arguments provided
        fprintf(stderr, "Usage: %s <seedURL> <pageDirectory> <maxDepth>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Extract arguments
    *seedURL = argv[1];
    *pageDirectory = argv[2];
    *maxDepth = atoi(argv[3]);

    // Validate maxDepth
    if (*maxDepth < 0 || *maxDepth > MAX_DEPTH) {
        fprintf(stderr, "Error: maxDepth must be between 0 and %d\n", MAX_DEPTH);
        exit(EXIT_FAILURE);
    }

    // Initialize the page directory
    if (!pagedir_init(*pageDirectory)) {
        fprintf(stderr, "Error: pageDirectory '%s' is not writable or cannot be created\n", *pageDirectory);
        exit(EXIT_FAILURE);
    }
}

// Crawl the web starting from the seed URL
static void crawl(char* seedURL, char* pageDirectory, int maxDepth) {
    int docID = 1;
    // Create hashtable to keep track of visited URLs
    hashtable_t* urls_seen = hashtable_new(500);
    if (!urls_seen) {
        fprintf(stderr, "Error: Failed to create URL hashtable.\n");
        return;
    }

    // Create bag to store pages to crawl
    bag_t* pages_to_crawl = bag_new();
    if (!pages_to_crawl) {
        fprintf(stderr, "Error: Failed to create pages to crawl bag.\n");
        hashtable_delete(urls_seen, NULL);
        return;
    }

    // Create webpage for the seed URL
    webpage_t* seedPage = webpage_new(seedURL, 0, NULL);
    if (!seedPage || !hashtable_insert(urls_seen, seedURL, "")) {
        fprintf(stderr, "Error: Failed to insert seed URL into seen hashtable.\n");
        webpage_delete(seedPage);
        hashtable_delete(urls_seen, NULL);
        bag_delete(pages_to_crawl, NULL);
        return;
    }

    // Add seed page to the bag
    bag_insert(pages_to_crawl, seedPage);

    // Start crawling loop
    webpage_t* currPage;
    while ((currPage = bag_extract(pages_to_crawl)) != NULL) {
        // Fetch the webpage
        if (webpage_fetch(currPage)) {
            // Save the webpage
            pagedir_save(currPage, pageDirectory, docID++);
            // Explore links in the webpage if depth allows
            if (webpage_getDepth(currPage) < maxDepth) {
                page_scan(currPage, webpage_getDepth(currPage) + 1, urls_seen, pages_to_crawl);
            }
        }
        printf("%s, ",webpage_getURL(currPage));
        webpage_delete(currPage);
    }

    // Cleanup
    hashtable_delete(urls_seen, NULL);
    bag_delete(pages_to_crawl, NULL);
}

// Scan the webpage for links and add them to the bag if they haven't been seen before
static void page_scan(webpage_t* page, int depth, hashtable_t* urls_seen, bag_t* pages_to_crawl) {
    // Check if the webpage is valid
    if (page == NULL || urls_seen == NULL || pages_to_crawl == NULL) {
        fprintf(stderr, "Error: Invalid arguments to page_scan\n");
        return;
    }

    // Get the HTML content of the webpage
  //  char* html = webpage_getHTML(page);
  //  if (html == NULL) {
    //    fprintf(stderr, "Error: Failed to get HTML content of the webpage\n");
      //  return;
    //}

    // Extract links from the HTML content
    int pos = 0;
    char* url;
    while ((url = webpage_getNextURL(page, &pos)) != NULL) {
        char* normalized = normalizeURL(url);
        // Check if the link is internal and hasn't been seen before
        if (normalized != NULL) {
        if (is_internal_link(normalized) && !hashtable_insert(urls_seen,normalized, "")) {
            // Create a new webpage for the link and add it to the bag
            webpage_t* new_page = webpage_new(normalized, depth, NULL);
            if (new_page != NULL) {
                bag_insert(pages_to_crawl, new_page);
            } else {
                fprintf(stderr, "Error: Failed to create webpage for URL: %s\n", url);
            }
        }}
        free(url); // Free memory allocated by webpage_getNextURL
    }

    // Free the HTML content
  //ree(html);
}

// Check if the given URL is internal (starts with "http://" or "https://")
static bool is_internal_link(const char* url) {
    return strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0;
}

