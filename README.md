
# Tiny Search Engine (TSE)

The Tiny Search Engine (TSE) is a simple search engine. It consists of three main components:

1. **Crawler**
2. **Indexer**
3. **Querier**

This project is structured to mimic the basic components of a search engine by crawling web pages, indexing the content, and then allowing for a query engine to search through the indexed content.

This project is structured to mimic the basic components of a search engine by crawling web pages, indexing the content, and then allowing for a query engine to search through the indexed content.

## Components

### 1. Crawler

The Crawler is responsible for collecting web data by crawling web pages starting from a seed URL. It saves each page to a directory with a unique document ID and records its depth in the website's link hierarchy.

**Directory:** `crawler/`
**Usage:**
```bash
./crawler seedURL pageDirectory maxDepth
```

### 2. Indexer
The Indexer reads the documents stored by the Crawler, builds an index mapping words to document IDs and word counts, and then writes this index to a file.

Directory: `indexer/`
Usage:

```bash
./indexer pageDirectory indexFilename
```
### 3. Querier
The Querier reads the index file produced by the Indexer and answers search queries according to the specified operators (and, or).

Directory: `querier/`
Usage:

```bash
./querier pageDirectory indexFilename
```

## Building the Project

```bash
make
```

## Usage

To clean up all compiled binaries and other files, you can use:

```bash
make clean

```
## Testing

``` bash
make test
```
