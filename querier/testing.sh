#!/bin/bash
# Ahmed Elmi
# Dartmouth College, CS50
# Script to test the querier module of the Tiny Search Engine

# Define directories
CRAWLER_DIR=~/cs50-dev/shared/tse/output
INDEXER_DIR=~/cs50-dev/shared/tse/output

# Function to test with inputs from a file
function test_with_inputs() {
    local crawlerPath=$CRAWLER_DIR/$1
    local indexPath=$INDEXER_DIR/$1.index
    local queryFile=$2

    if [ ! -d "$crawlerPath" ] || [ ! -f "$indexPath" ]; then
        echo "Directory or index file for $1 does not exist."
        return 1
    fi

    echo "Testing with input from $queryFile..."
    while IFS= read -r line; do
        echo "Query: $line"
        echo "$line" | ./querier $crawlerPath $indexPath
    done < "$queryFile"
}

echo "====================================================="
echo "Testing valid queries from queries.txt on wikipedia-2..."
echo "====================================================="
test_with_inputs "wikipedia-2" "queries.txt"

echo "====================================================="
echo "Running Valgrind tests on wikipedia-2..."
echo "====================================================="
valgrind --leak-check=full --show-leak-kinds=all ./querier $CRAWLER_DIR/wikipedia-2 $INDEXER_DIR/wikipedia-2.index < queries.txt

echo "Testing completed."
echo "====================================================="
