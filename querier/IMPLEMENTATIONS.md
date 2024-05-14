
### `IMPLEMENTATIONS.md`
This document should provide a detailed explanation of how you implemented the Querier, including descriptions of the algorithms, data structures, and major functions used.

```markdown
# Implementation Details for TSE Querier

## Data Structures
- **Counters**: Used to keep track of the word counts per document.
- **Hashtable**: Stores the mapping from words to `Counters` that track document IDs where the word appears.

## Major Functions
### Query Parsing
- **parse_query**: Parses and tokenizes the input query, validating syntax and handling errors.
- **normalize_query**: Converts the query into a consistent format, making it case-insensitive and trimming excess whitespace.

### Query Processing
- **process_query**: Takes a parsed query and executes it against the provided index, using logical `and` and `or` operations.
- **and_sequence**: Handles sequences of terms connected by `and`.
- **or_sequence**: Handles sequences of terms connected by `or`.

### Combining Results
- **intersect_counters**: Intersects two `Counters`, finding documents that appear in both and taking the minimum count.
- **union_counters**: Unions two `Counters`, adding counts together for documents that appear in both.

### Result Sorting and Output
- **sort_results**: Sorts documents by their score in descending order before output.
- **print_results**: Formats and prints the results of a query to stdout.

## Algorithmic Design
1. **Input Processing**: The querier reads from stdin, breaks input into words, and checks for operators.
2. **Query Execution**: Based on the operators and words, the querier builds a query plan which decides the order of operations (`and` before `or`).
3. **Result Processing**: Accumulates results in a `Counters` structure, which is then sorted and printed.

## Memory Management
- Each function is responsible for the memory it allocates. Temporary structures are freed as soon as they are no longer needed.
- Valgrind is used to ensure there are no memory leaks or errors.

## Testing
- Detailed tests are provided in `testing.sh`, including tests for input edge cases, memory leaks, and typical usage scenarios.

## Enhancements and Optimizations
- Future enhancements could include more complex query optimizations, and the implementation of a caching mechanism for frequent queries to improve performance.

## Conclusion
This document describes the detailed implementation of the Querier module of the Tiny Search Engine, outlining the approach taken in handling queries, combining results, and ensuring efficiency and correctness throughout the process.

