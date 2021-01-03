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
