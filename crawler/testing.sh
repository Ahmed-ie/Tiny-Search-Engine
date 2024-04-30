#!/bin/bash

# Test parameters
seedURL1="http://cs50tse.cs.dartmouth.edu/tse/letters/index.html"
seedURL2="http://cs50tse.cs.dartmouth.edu/tse/letters/A.html"  # Different seed page in the same site
bigSeedURL="http://cs50tse.cs.dartmouth.edu/tse/"  # Bigger playground
pageDirectory="data"
maxDepth1=2
maxDepth2=1
maxDepth3=0

# Create pageDirectory if it doesn't exist
mkdir -p $pageDirectory

# Test case 1: Incorrect command-line arguments
echo "Testing incorrect command-line arguments..."
./crawler/crawler                          # Missing required arguments
./crawler/crawler invalidURL               # Invalid seed URL
./crawler/crawler $seedURL1 $pageDirectory invalidDepth  # Invalid depth
echo "Test case 1 complete."

# Test case 2: Crawl a closed set of cross-linked web pages at different depths
echo "Crawling simple closed set of cross-linked web pages..."
./crawler/crawler $seedURL1 $pageDirectory/letters-depth-$maxDepth1 $maxDepth1
./crawler/crawler $seedURL1 $pageDirectory/letters-depth-$maxDepth2 $maxDepth2
./crawler/crawler $seedURL1 $pageDirectory/letters-depth-$maxDepth3 $maxDepth3
echo "Test case 2 complete."

# Test case 3: Crawl from a different seed page in the same site
echo "Crawling from a different seed page..."
./crawler/crawler $seedURL2 $pageDirectory/letters-different-seed $maxDepth1
echo "Test case 3 complete."

# Test case 4: Crawl from a bigger playground
echo "Crawling from a bigger playground..."
./crawler/crawler $bigSeedURL $pageDirectory/bigger-playground-depth-$maxDepth1 $maxDepth1
echo "Test case 4 complete."

echo "All tests complete."

