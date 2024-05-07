#!/bin/bash

# Paths for testing
OUTPUT_DIR="$HOME/cs50-dev/shared/tse/output"
EXPECTED_DIR="$HOME/cs50-dev/shared/tse/expected"
TEST_DIR="$HOME/cs50-dev/test-output"

# Ensure the test directory exists
mkdir -p "$TEST_DIR"

# Option to run with memory checks
if [ ! -z "$1" ] && [ "$1" == "CHECK_MEMORY" ]; then
  VALGRIND="valgrind --leak-check=full --show-leak-kinds=all"
  echo "The following tests will check for memory leaks."
else
  VALGRIND=""
  echo "The following tests will run without checking for memory leaks."
fi

# Function to compare sorted index files using `sort` and `diff`
check_index_equal() {
  sort "$1" > "$1".sorted
  sort "$2" > expected.sorted
  diff "$1".sorted expected.sorted
  rm -f "$1".sorted expected.sorted
}

# Test invalid arguments for the indexer
$VALGRIND ./indexer
$VALGRIND ./indexer hello
$VALGRIND ./indexer too few arguments

# Test invalid crawler directory
mkdir test1  # Temporary directory
$VALGRIND ./indexer/indexer test1 index
rm -rf test1  # Cleanup

# Test empty directory with a .crawler file
mkdir test2
touch test2/.crawler
$VALGRIND ./indexer test2 "$TEST_DIR/test2.output"
rm -rf test2

# Test directories with different data (letters, toscrape, wikipedia)
# Make sure these directories are properly populated first

# Letters Test
$VALGRIND ./indexer "$OUTPUT_DIR/letters-0" "$TEST_DIR/letters-0.output"
check_index_equal "$TEST_DIR/letters-0.output" "$EXPECTED_DIR/letters-0.expected"

$VALGRIND ./indexer "$OUTPUT_DIR/letters-1" "$TEST_DIR/letters-1.output"
check_index_equal "$TEST_DIR/letters-1.output" "$EXPECTED_DIR/letters-1.expected"

# ToScrape Test
$VALGRIND ./indexer "$OUTPUT_DIR/toscrape-0" "$TEST_DIR/toscrape-0.output"
check_index_equal "$TEST_DIR/toscrape-0.output" "$EXPECTED_DIR/toscrape-0.expected"

# Wikipedia Test
$VALGRIND ./indexer "$OUTPUT_DIR/wikipedia_0" "$TEST_DIR/wikipedia_0.output"
check_index_equal "$TEST_DIR/wikipedia_0.output" "$EXPECTED_DIR/wikipedia_0.expected"

# Test indextest for argument handling and specific cases

# Invalid arguments for indextest
$VALGRIND ./indextest non-existent new
$VALGRIND ./indextest only-one-arg

# Indextest with an empty file
touch "$TEST_DIR/empty-file"
$VALGRIND ./indextest "$TEST_DIR/empty-file" "$TEST_DIR/empty-file.output"
rm -f "$TEST_DIR/empty-file"
