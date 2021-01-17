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

# What am I looking for?
I use C/C++ for work. While I really love these languages, they leave a lot to
be desired, and I would not like to use them for a fun, casual, personal 
project.

## My ideal language
- has a strong package management and build system
  - Rust's cargo, Haskell's stack are good examples
  - Python and C++ are anti-examples.
    - Python makes it super difficult to create your own packages and make
      other programs aware of them
    - C++ has deeply coupled language package management and OS package
      management. Also, make/cmake basically require you to learn a second
      language just to build your C/C++ code.
- has few(er) runtime errors
  - compiled languages with static analysis are greatly preferred
  - I want to avoid how with python/javascript your code will work the first
    time, but then down the line you have to scratch your head for hours while
    you track down a runtime error
- is appropriate for large projects
  - maintainabiliy is huge: how easily can I parse an existing codebase to
    debug or add features?
  - robustness is important: rust's nanny of a compiler shines here
  - strong object-oriented principles are a plus, but not necessary
- it should be somewhat easy to pick up
  - This is a language I'll be using for fun. I don't want to have to spend
    huge amounts of time just getting things up and running
  - Haskell, rust are anti-examples
    - Haskell is obtuse, pedantic, and deeply integrated in theory
    - Rust has its own set of rules that are not intuitive, even to someone who
      is well-versed in computer architecture.
- it should be enjoyable
  - I'm just here to have fun
