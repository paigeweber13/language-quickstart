# Language Quickstart
The challenge: for each language, implement the following:
- Dijkstra's algorithm on a graph defined by an adjacency matrix
- get the json from https://httpbin.org/json and write it to disk
- parallel mergesort
- get an optional binary command line flag (there or not) and an optional
  command line flag with an argument

External packages are allowed: one of the goals of this project is to help the
new programmer discover what the package ecosystem is like.

# Why these problems?
## Dijkstra's:
- requires understanding of basic collections to create adjacency matrix
- it's simple enough to be quickly implemented but complex enough to require 
  good control flow

## Getting the json:
- requires the ability to make http requests, a very common practice in today's
  world. This is also notoriously difficult in languages like C.
- I/O (to and from both the internet and disk) is very important
- will likely require an external package, providing an opportunity to learn
  about the package ecosystem

## Parallel mergesort:
- requires parallelism

## Command line flags
- very, very common
- can be a headache with built-in features in some languages (c getopts, for
  instance)

