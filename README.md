# CS50 TSE
## Ahmed Elmi (GitHub username): Ahmed-ie

The assignment and Specs are in a [public repo](https://github.com/CS50DartmouthSPS24/labs/tse).
Do not clone that repo; view it on GitHub.
Watch there for any commits that may represent updates to the assignment or specs.

Add here any assumptions you made while writing the crawler, any ways in which your implementation differs from the three Specs, or any ways in which you know your implementation fails to work.

## Features

- Crawls a website starting from a specified URL
- Retrieves web pages and their contents
- Parses initial web pages and extracts embedded URLs
- Limits the crawling depth
- Avoids visiting the same URL more than once
- Saves crawled pages and their contents to files

## Usage

```bash
./crawler [seedURL] [pageDirectory] [maxDepth]
```

## Testing

You can use the provided `testing.sh` script This script runs various tests to ensure that the crawler behaves as expected.

./testing.sh

```bash
cd crawler
make


