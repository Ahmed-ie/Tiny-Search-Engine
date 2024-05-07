# Indexer Design Specification

This document describes the design of the `indexer` component of the Tiny Search Engine (TSE). The `indexer` reads previously crawled web pages, processes their content to build an index, and stores this index in a file.

## User Interface

The `indexer` is run from the command line with the following syntax:

```bash
./indexer <pageDirectory> <indexFilename>
```
`<pageDirectory>`: The directory where the crawled web pages are stored.
`<indexFilename>`: The output file where the generated index is saved.
### Inputs and Outputs

Inputs:

Web Pages: Web pages retrieved by the crawler and stored in `<pageDirectory>`.

Outputs:

Index File: An index file saved at `<indexFilename>`, containing the list of all unique words and the documents in which they appear, along with their frequency.

### Functional Decomposition
The indexer is divided into three key functions:

Main: Parses command-line arguments, initializes indexing structures, and orchestrates the indexing process.
Build Index: Processes each webpage in the given directory and builds the index using a data structure.
Save Index: Writes the constructed index to the specified output file.
Data Structures
Hashtable: Stores the mapping of words to document IDs and their frequencies.

### Pseudocode

#### Main

Parse command-line arguments
Initialize index data structure
For each file in the page directory:
  Load the webpage data
  Parse the words and build the index
Save the index to the specified file

#### Buidling Index

Load webpage data
For each word in the webpage:
  Normalize the word
  If the word is not in the index, add it
  Update the word count for the specific document

#### Saving Index

Open the output file
For each word in the index:
  Write the word, document ID(s), and frequency
Close the file

### Major Data Structures

Hashtable: Maps each word to a list of document IDs and their frequencies.
Word Normalization: Converts words to lowercase and filters out short words.

