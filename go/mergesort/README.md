# Thoughts
Go was easy to work with, and I was surprised how intuitive slicing is.

Speed was good, considering I didn't use any pointers or manual memory
management, like in C. For a comparison of C, high-level C++, and Go, see the
following table. In all cases the array is of size 1e9. All times are in
seconds. 

Language|Items/second|Alloc time|Randomize time|Sort time
--------|------------|----------|--------------|---------
Go      |5.18e6      |0.0373    |6.8587        |186.1011
C++     |6.78e6      |0.7804    |3.4409        |143.3388
C       |1.50e7      |0.0000    |6.9295        | 59.5667

Go's performance was very comparable to high-level C++, with about 75% of the
performance. Both are slower than the low-level, macro-assembly style C.
However, I'm impressed with how well Go performed compared to C++. It boasts
significantly better tooling and package management than C++, but with very
close to the same performance in this one very opinionated test.

# The "Ideal Language" Checklist
- [x] has a strong package management and build system
  - Kind of? Enough to get full marks in my book. There is no true full-fledged
    build system out of the box, though some third-party options are available,
    which I haven't tested. However, in the true "occam's razor" style that go
    embraces, you don't really *need* a build system. Imports work seamlessly,
    even when packages have to be downloaded from the internet, and `go run
    <file>` is all you need to run some code. That's all a build system does
    anyway, right?
- [ ] has few(er) runtime errors
  - Go gets half marks here. Yes, go is compiled, and yes there is type
    checking, but compile errors are long, obscure, and difficult to parse.
- [ ] is appropriate for large projects
  - Go loses here. There are no generics, so lots of copy/paste code. This
    hurts maintainability.
  - Not sure what kind of OO tools are available
- [x] it should be somewhat easy to pick up
  - Go wins here wholeheartedly. The syntax was basically C. Packages were so
    easy to get.
- [x] it should be enjoyable
  - Yes! I enjoyed Go. It almost feels too easy.

# What would keep me from using Go?
I'm hesitant to start a big project for Go. Their lack of generics, plus the
fact that I have no idea how to begin an object-oriented piece of software,
make me nervous to use this for anything more than scripts and short proof of
concepts. 
