# Indexer Implementation Functions

## Main Functions

1. **`main` (Indexer)**:
   - **Purpose**: Initializes the indexer program, validates input arguments, and orchestrates the indexing process.
   - **Key Calls**:
     - `pagedir_validate`: Ensures the page directory is valid.
     - `pagedir_load`: Loads pages from the directory.
     - `index_new`: Creates a new index data structure.
     - `index_insert`: Adds words to the index.

2. **`main` (Indextest)**:
   - **Purpose**: Loads an existing index from a file and writes it to another file to verify the loading and saving process.
   - **Key Calls**:
     - `index_load`: Loads an index from a file.
     - `index_save`: Writes the index to a new file.

## Indexer Helper Functions

1. **`index_new`**:
   - **Purpose**: Creates and initializes a new index structure.
   - **Parameters**:
     - `num_slots`: Number of slots for the hashtable.
   - **Returns**: Pointer to a new `index_t` structure.

2. **`index_insert`**:
   - **Purpose**: Inserts a word and document ID into the index.
   - **Parameters**:
     - `index`: Pointer to the `index_t` structure.
     - `word`: The word to insert.
     - `docID`: The document ID where the word was found.
   - **Returns**: `true` on success, `false` otherwise.

3. **`index_get`**:
   - **Purpose**: Retrieves the counters structure for a given word.
   - **Parameters**:
     - `index`: Pointer to the `index_t` structure.
     - `word`: The word to look up.
   - **Returns**: Pointer to a counters structure.

4. **`index_save`**:
   - **Purpose**: Writes the index data to a file.
   - **Parameters**:
     - `fp`: File pointer to the output file.
     - `index`: Pointer to the `index_t` structure.

5. **`index_load`**:
   - **Purpose**: Loads index data from a file.
   - **Parameters**:
     - `fp`: File pointer to the input file.
     - `num_slots`: Number of slots in the hashtable.
   - **Returns**: Pointer to a new `index_t` structure.

6. **`index_delete`**:
   - **Purpose**: Frees all memory used by the index.
   - **Parameters**:
     - `index`: Pointer to the `index_t` structure.

## Pagedir Functions

1. **`pagedir_init`**:
   - **Purpose**: Prepares a directory to store webpages.
   - **Parameters**:
     - `pageDirectory`: The directory path to initialize.
   - **Returns**: `true` if successful, `false` otherwise.

2. **`pagedir_save`**:
   - **Purpose**: Saves a webpage to a specified directory.
   - **Parameters**:
     - `page`: Pointer to the `webpage_t` structure.
     - `pageDirectory`: The directory path where the page will be saved.
     - `docID`: The document ID.

3. **`pagedir_validate`**:
   - **Purpose**: Verifies whether a directory was used by the crawler.
   - **Parameters**:
     - `pageDirectory`: The directory path to validate.
   - **Returns**: `true` if the directory is valid, `false` otherwise.

4. **`pagedir_load`**:
   - **Purpose**: Loads a webpage from the specified directory.
   - **Parameters**:
     - `pageDirectory`: The directory path where the pages are stored.
     - `docID`: The document ID to load.
   - **Returns**: Pointer to a `webpage_t` structure.

## Word Processing Functions

1. **`normalizeWord`**:
   - **Purpose**: Normalizes a word by converting it to lowercase.
   - **Parameters**:
     - `word`: The word to normalize.
