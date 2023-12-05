# Search Engine Project Overview

## Introduction
This project implements a simple search engine using a simplified version of the PageRank algorithm. The objective is to build a graph structure, calculate PageRanks, and rank pages based on these values. The search engine operates on a collection of mock web pages provided as plain text files.

## Project Structure
The project is divided into three main parts:

### Part 1: PageRank Calculation
- `pagerank.c`

### Part 2: Inverted Index
- `invertedIndex.c`

### Part 3: Simple Search Engine
- `searchPagerank.c`

## Additional Components
- `BST.c`
- `BST.h`
- `DLListStr.c`
- `DLListStr.h`
- `Graph.c`
- `Graph.h`
- `helpers.c`
- `helpers.h`
- `readData.c`
- `readData.h`
- `InvertedIdx.c`
- `InvertedIdx.h`

## Web Page Format
Each mock web page is divided into two sections:
- **Section 1**: Contains URLs representing outgoing links.
- **Section 2**: Contains the actual content of the web page.

Sections are delimited by specific markers, ensuring clear separation of content and links.

# Part 1: PageRank Calculation

## Overview
Implement `pagerank.c` to calculate the PageRank for URLs listed in `collection.txt`. The program will construct a graph from these URLs and compute their PageRank using the provided algorithm.

## Input File: `collection.txt`
Contains URLs separated by whitespace. Each URL corresponds to a text file.

Example:
```
url11 url21 url22
url23
url31 url24 url34
```


## Task
- Read `collection.txt` and construct a graph (adjacency list or matrix).
- Calculate Weighted PageRank for each page using the algorithm provided.

## PageRank Algorithm

The PageRank algorithm is used to calculate the importance of pages within a collection. The following steps are performed:

1. **Read Pages**: Read pages from the collection in the file `collection.txt` and build a graph structure using a chosen representation (adjacency list or matrix).

2. **Initialize Variables**:
   - `N`: Total number of URLs in the collection.
   - For each URL `pi` in the collection, initialize PageRank: `PR(pi, 0) = 1/N`.
   - Set `iteration` to 0.
   - Set `diff` to the threshold `diffPR`.

3. **Iterate**: While `iteration < maxIterations` and `diff >= diffPR` do:
   - Set `t` to the current iteration count.
   - For each URL `pi` in the collection, update PageRank using the following formula:
     ```
     PR(pi, t+1) = (1 - d)/N + d * Σ (PR(pj, t) / L(pj))
     ```
     where:
     - `pj ∈ M(pi)`: Set of pages with outgoing links to `pi` (excluding self-loops and parallel edges).
     - `L(pj)`: Out-degree of the page `pj`.

4. **Calculate Difference**: After each iteration, update `diff`:
    ```
    diff = Σ |PR(pi, t+1) - PR(pi, t)|
    ```
    for all `i` from 1 to `N`.

5. **Increment Iteration Count**: Increase `iteration` by 1.

In this algorithm:
- `M(pi)` is a set of pages that have outgoing links to page `pi`.
- `L(pj)` is the number of outgoing links from page `pj`.
- `t` and `t+1` refer to the iteration numbers; for example, `PR(pi, 2)` refers to the PageRank of `pi` after iteration 2.

## Command-Line Arguments
- `d`: Damping factor
- `diffPR`: Threshold for PageRank differences
- `maxIterations`: Maximum iterations
- Example: `./pagerank 0.85 0.00001 1000`

## Output: `pagerankList.txt`
- Format: `URL, outdegree, PageRank`
- PageRank values formatted to 7 decimal places (`%.7lf`)
- Sorted in descending order of PageRank
- Example:
```
url31, 3, 0.2623546
url21, 1, 0.1843112
...
```

## Note
PageRank values may slightly vary but should align with expected values to the first 6 decimal places.

# Part 2: Inverted Index

## Overview
In this part, you will implement `invertedIndex.c`, which reads data from the `collection.txt` file and generates an inverted index. This index maps every word in the collection to a sorted list of URLs where the word appears.

## Implementation
- **Binary Search Tree (BST)**: Represent the inverted index as a BST where each node contains a word.
- **File List**: Each BST node has a linked list of filenames (URLs) where the word is found.
- **Ordering**:
  - The BST is alphabetically ordered by words.
  - Each file list is alphabetically ordered by filename.

## Diagram
![Inverted Index Example](/read_me_images/inverted_index.png "Inverted Index Example")


## Normalization
Before inserting words into the index, normalize them by:
- Converting all letters to lowercase.
- Removing punctuation marks at the end of words: `. , : ; ? *`
- If a word becomes empty after normalization, it is not inserted.

## Example Normalization
| Word          | Normalised Word |
|---------------|-----------------|
| Data          | data            |
| BSTs          | bsts            |
| algorithms.   | algorithms      |
| Why?          | why             |
| graphs*.      | graphs          |
| .NET          | .net            |
| unsw.edu.au.  | unsw.edu.au     |
| Sydney?       | sydney?         |
| .,!.,:;       | .,!             |
| new.........s | new.........s   |
| *             | (empty word)    |

## Execution
Run the program with:

```bash
./invertedIndex
```

## Output: `invertedIndex.txt`
- Each line starts with a word followed by a list of filenames.
- Sort lines alphabetically by the initial word.
- Sort filenames alphabetically within each line.

## Example Output
```
design url2 url25 url31 url61
mars url101 url25 url31
vegetation url31 url61
```

- Words and URLs are separated by spaces (additional spaces are ignored by the testing program).

# Part 3: Search Engine Query Processor

## Overview
Implement `searchPagerank.c` to process search queries using two key data files: `invertedIndex.txt` and `pagerankList.txt`. The program finds the most relevant pages based on search terms and outputs the top 30 URLs sorted by relevance and PageRank.

## Data Files
- `invertedIndex.txt`: Contains words and their corresponding page URLs, as produced in Part 2.
- `pagerankList.txt`: Contains pages with their URL, outdegree, and PageRank, as produced in Part 1. The values are separated by ", " (comma followed by a space).

## Functionality
- Accepts one or more search terms as command-line arguments.
- Identifies pages that contain one or more matching search terms.
- Outputs the top 30 pages, sorted by:
  1. Descending order of the number of matching search terms.
  2. Descending order of PageRank for ties.

## Matching Criteria
- Matches are based on exact words; word variants and plurals are treated as distinct.
- A page's relevance is determined by the presence of search terms, not their frequency on the page.

## Usage
```bash
./searchPagerank [search_term1] [search_term2] [...]
```

## Example Output
When searching for "mars" and "design":

```bash
./searchPagerank mars design
url31
url25
```

# Testing
To run these tests, a bash script is provided, which will change into each directory test* and run the test. To use it, assuming the script runtests is in your current directory, do the following:
```bash
./runtests
```