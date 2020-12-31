# Language Quickstart
The challenge: for each language, implement the following:
- Dijkstra's algorithm on a graph defined by an adjacency matrix
- parallel mergesort
- get an optional binary command line flag (there or not) and an optional
  command line flag with an argument
- get every link on the front page of [hacker
  news](https://news.ycombinator.com/news) (and optionally, get every image on
  the pages linked to))

External packages are allowed: one of the goals of this project is to help the
new programmer discover what the package ecosystem is like.

# Why these problems?
## Dijkstra's:
- requires understanding of basic collections to create adjacency matrix
- it's simple enough to be quickly implemented but complex enough to require 
  good control flow

## Parallel mergesort:
- requires parallelism

## Command line flags
- very, very common
- can be a headache with built-in features in some languages (c getopts, for
  instance)

## Web scraping
- This is a common usecase for me
- Incorporates web requests, I/O
- will likely require an external package, providing an opportunity to learn
  about the package ecosystem

# Other fun problems
These could be added in the future
- Sieve of Eratosthenes
- More sorting algorithms
- Binary Search Tree
