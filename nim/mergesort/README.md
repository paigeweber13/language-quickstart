# Running
Make sure nim is installed, then run `nim c -r mergesort.nim`

# Thoughts
I noticed I was trying to shoe-horn c-style code into this by first using
references (`ref`) and then unsafe pointers (`addr`). But I realized that the
whole point of using a high-level language is to take advantage of safety
features, so I re-learned how to be an applications programmer :)

Without `addr`, mergesort is *slow* compared to C. On my machine, this
implementation is about 30x slower: for example, let's consider an array of 
size 1e8. In C, it took 5.6219 seconds to sort this array, and less than 0.712
seconds to allocate and randomize that array. This implementation of mergesort
in nim took nearly 5 minutes (290.55s) to sort an array of the same size! The
time needed to allocate and randomize the array was actually faster than C, at
0.0454s.

However, for a proper comparison I would need to write an implementation that
uses `addr`, which is outside the scope of this project.
