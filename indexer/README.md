# CS50 TSE Indexer by Ahmed Elmi

## Overview

The `indexer` program, developed by Ahmed Elmi, is part of the Tiny Search Engine (TSE) project. This program reads crawled web pages from a specified directory, processes their content to build an index mapping words to the documents where they appear, and saves the index to an output file. This index enables the `querier` program to efficiently respond to search queries.

## Assumptions

- **Page Directory**: Assumes that the page directory passed to the program contains a `.crawler` file, indicating that it is a valid crawler-produced directory.
- **Well-Formed Pages**: Assumes that the pages stored in the directory are well-formed, meaning they contain the URL on the first line, the depth on the second line, and HTML content starting from the third line.
- **Word Length**: Words shorter than 3 characters are ignored during indexing to exclude common and irrelevant words.

## Implementation Deviations

- **Hash Table Size**: I set the hash table size to 500 slots by default, which may differ from the recommended size.
- **Word Normalization**: The program normalizes words to lowercase and excludes additional preprocessing like stemming.
- **Load and Save Functions**: The `index_load` and `index_save` functions assume the index files follow a specific format.

## Known Issues

- **Corrupted Pages**: If a page file is corrupted (e.g., missing depth or content), the indexer may skip it without additional error handling.
- **Incomplete Index File**: If the index file is not completely written due to an error, it will leave a partial file without retrying the write operation.
- **Index Size**: In some cases, the index size may become too large for directories with many documents.

## Compilation

To compile the `indexer` program, use the `make` command:

```bash
make indexer
