This document provides a detailed explanation of how the Querier component of the Tiny Search Engine (TSE) is implemented, including descriptions of the algorithms, data structures, and major functions used.

# Implementation Details for TSE Querier

## Data Structures
- **Counters**: Used to keep track of the word counts per document. This structure is integral to managing the frequency of words across various documents.
- **Hashtable**: Stores the mapping from words to `Counters` that track document IDs where the word appears, facilitating fast retrieval and updates.

## Major Functions
### Query Parsing
- **parse_query**:
  - **Purpose**: Parses and tokenizes the input query, validating syntax and handling errors.
  - **Parameters**:
    - `query`: The string input from the user.
  - **Returns**: A normalized and tokenized list of words and operators.
- **normalize_query**:
  - **Purpose**: Converts the query into a consistent format, making it case-insensitive and trimming excess whitespace.
  - **Parameters**:
    - `query`: The string input from the user.
  - **Returns**: A string that has been normalized for processing.

### Query Processing
- **process_query**:
  - **Purpose**: Takes a parsed query and executes it against the provided index, using logical `and` and `or` operations to combine results.
  - **Key Calls**:
    - `and_sequence`: Manages the logical `and` operations.
    - `or_sequence`: Manages the logical `or` operations.
- **and_sequence**:
  - **Purpose**: Handles sequences of terms connected by `and`, ensuring that all terms must be present in the document.
- **or_sequence**:
  - **Purpose**: Handles sequences of terms connected by `or`, allowing any of the terms to be present for a match.

### Combining Results
- **intersect_counters**:
  - **Purpose**: Intersects two `Counters`, finding documents that appear in both and taking the minimum count.
- **union_counters**:
  - **Purpose**: Unions two `Counters`, adding counts together for documents that appear in both.

### Result Sorting and Output
- **sort_results**:
  - **Purpose**: Sorts documents by their score in descending order before output.
- **print_results**:
  - **Purpose**: Formats and prints the results of a query to stdout, providing a clear output to the user.

## Algorithmic Design
1. **Input Processing**: The querier reads from stdin, breaks input into words, and checks for operators, ensuring a structured input format.
2. **Query Execution**: Based on the operators and words, the querier builds a query plan which decides the order of operations (`and` before `or`), optimizing the processing of queries.
3. **Result Processing**: Accumulates results in a `Counters` structure, which is then sorted and printed, ensuring efficient data handling.

## Memory Management
- **General Strategy**: Each function is responsible for the memory it allocates. Temporary structures are freed as soon as they are no longer needed, preventing memory leaks.
- **Tools Used**: Valgrind is used to ensure there are no memory leaks or errors, maintaining the integrity of the application.

## Testing
- **Approach**: Detailed tests are provided in `testing.sh`, which includes tests for input edge cases, memory leaks, and typical usage scenarios, ensuring robustness and reliability.
- **Test Execution**: Each test is executed automatically, verifying both the functionality and performance under various conditions.

## Enhancements and Optimizations
- **Future Plans**: More complex query optimizations and the implementation of a caching mechanism for frequent queries are considered to improve performance.
- **Goals**: Enhance speed and reliability, making the querier more efficient in handling large volumes of queries.

## Conclusion
This document outlines the detailed implementation of the Querier module of the Tiny Search Engine, showcasing the comprehensive approach taken in handling queries, combining results, and ensuring efficiency and correctness throughout the process.
