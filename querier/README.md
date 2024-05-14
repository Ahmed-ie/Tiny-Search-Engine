# Querier for Tiny Search Engine (TSE)

## Overview
The Querier is a standalone program in the TSE architecture, built on top of the TSE Crawler and the TSE Indexer. It reads the document set produced by the Crawler and the index produced by the Indexer, and answers search queries submitted via stdin.

## Compilation
To compile:
``` bash
make
```
## Usage
``` bash
./querier pageDirectory indexFilename
```
`pageDirectory` is the pathname for the directory produced by the Crawler.
`indexFilename` is the pathname of the file produced by the Indexer.

## Assumptions

`pageDirectory` has files named 1, 2, 3, ..., without gaps.
The index file is formatted as expected by the Indexer spec.
