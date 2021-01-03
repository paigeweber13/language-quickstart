# Running
Make sure nim is installed, then run `nim c -r -d:release mergesort.nim`

# Thoughts
I noticed I was trying to shoe-horn c-style code into this by first using
references (`ref`) and then unsafe pointers (`addr`). But I realized that the
whole point of using a high-level language is to take advantage of safety
features, so I re-learned how to be an applications programmer :)

Without `addr`, mergesort is *slow* compared to C. The first time I ran it, I
forgot to use the `-d:release` flag to produce faster code, and it ran about
30x slower than mergesort in C. However, after enabling the release flag,
performance improved to about 6.5x slower than C. For an array of size 1e8, C
processed 1.58e7 items per second and took 5.62 seconds to sort the array. Nim
processed 2.72e6 items per second and took 36.0633 seconds to sort the array.
Allocation + randomization took about .7 seconds in both languages.

This performance is about half that of high-level C++, which processed 7.25e6
items per second and took 13.35 seconds to sort an array of size 1e8

However, for a proper comparison I would need to write an implementation that
uses `addr`, which is outside the scope of this project. I'm sure Nim is
capable of running faster, but I'm concerned with the performance of code
written in the way a language was designed to be used, and use of `addr` is
discouraged unless absolutely necessary.
