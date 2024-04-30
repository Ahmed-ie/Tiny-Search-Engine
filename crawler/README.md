# CS50 Dartmouth Spring 2024 - Web Crawler Module

## Description
The web crawler is a program that systematically browses and downloads web content starting from a seed URL. It is designed to crawl web pages by fetching each page, extracting the links it contains, and following those links to discover new pages, while avoiding revisiting the same pages.

## Usage
The crawler module, defined in `crawler.c` and associated header files, handles the fetching, parsing, and saving of webpages as follows:

- **Initialization**: Starts with a seed URL and a maximum crawl depth.
- **Fetching**: Downloads webpages starting from the seed URL.
- **Parsing**: Extracts links from the downloaded content.
- **Saving**: Saves the fetched webpages to a specified directory.

### Functions
- `crawler.c` contains the main logic to initialize, execute, and manage the crawling process.

Arguments:
seedURL: The initial URL to start crawling
pageDirectory: The directory where the pages are saved
maxDepth: The maximum depth to crawl

Implementation
The crawler is implemented with these data structures:

Hashtable: Used to track seen URLs to avoid revisiting the same page.
Bag: Stores the webpages yet to be crawled.
Webpage Module: Manages the fetching and parsing of individual webpages.

### Entry Point
```c
int main(int argc, char* argv[]);
```

Compilation
Compile with the command:

```bash
make crawler
```
Running the Crawler
To run the crawler, use:

```bash
./crawler <seedURL> <pageDirectory> <maxDepth>
```


