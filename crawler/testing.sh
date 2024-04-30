#!/bin/bash

# This script tests the crawler's functionality on a variety of inputs and configurations.

echo "Testing the crawler with invalid command-line arguments..."
# Test with no arguments
./crawler

# Test with one argument
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html

# Test with an invalid URL
./crawler http://invalidurl data/invalid 1

# Test with non-existent directory
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html non/existent/dir 1

# Test with invalid depth (negative number)
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/invalid -1

# Test with depth that is too high (non-numeric input)
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/invalid abc

echo "Testing the crawler on a simple, closed set of cross-linked web pages..."

# Set up directories for valid tests
mkdir -p data/letter-2
mkdir -p data/toscrape-1

# Test crawling letters at various depths
echo "Crawling letters at depth 0..."
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letter-2 0

echo "Crawling letters at depth 1..."
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letter-2 1

echo "Crawling letters at depth 2..."
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letter-2 2

echo "Testing with a different seed page on the same site..."
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/B.html data/letter-2 2

echo "Pointing the crawler at a bigger playground..."

echo "Crawling toscrape at depth 0..."
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html data/toscrape-1 0

echo "Crawling toscrape at depth 1..."
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html data/toscrape-1 1

echo "Crawling toscrape at depth 2..."
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html data/toscrape-1 2

# Additional test with a greater depth (careful with this one)
echo "Crawling toscrape at a greater depth 3 (be ready to kill if running amok)..."
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html data/toscrape-1 3

echo "Testing completed."

