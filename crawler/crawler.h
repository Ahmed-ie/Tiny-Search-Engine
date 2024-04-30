#ifndef CRAWLER_H
#define CRAWLER_H

#include "webpage.h"
#include "bag.h"
#include "hashtable.h"

/**
 * Parses the command-line arguments to extract the seed URL, page directory,
 * and the maximum depth for crawling. Exits the program if any arguments are
 * invalid.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @param seedURL Pointer to the seed URL string.
 * @param pageDirectory Pointer to the page directory string.
 * @param maxDepth Pointer to the maximum depth integer.
 */
void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);

/**
 * Begins the crawling process from the seed URL up to the specified maximum depth.
 * Pages are saved in the specified directory.
 * @param seedURL The seed URL from which to start crawling.
 * @param pageDirectory The directory where the pages should be saved.
 * @param maxDepth The maximum depth to crawl.
 */
void crawl(char* seedURL, char* pageDirectory, const int maxDepth);

/**
 * Scans the given webpage for URLs and processes each URL by checking if it's internal
 * and not already visited. If both conditions are met, the URL is added to the list
 * of pages to crawl.
 * @param page The webpage to scan.
 * @param pagesToCrawl The bag of pages yet to be crawled.
 * @param pagesSeen The hashtable of pages that have been seen.
 */
void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

#endif // CRAWLER_H

