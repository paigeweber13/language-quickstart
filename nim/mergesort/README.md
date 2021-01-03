# Running
Make sure nim is installed, then run `nim c -r mergesort.nim`

# Thoughts
I noticed I was trying to shoe-horn c-style code into this by first using
references (`ref`) and then unsafe pointers (`addr`). But I realized that the
whole point of using a high-level language is to take advantage of safety
features, so I re-learned how to be an applications programmer :)
