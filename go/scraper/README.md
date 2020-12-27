# Go Scraper
This was remarkably easy, and took maybe 3-4 hours of work over two days.
Following are some of my thoughts:
- Error handling felt a lot like C: `err = foo(); if(err != null){ handle(err);
  }`
  - This pattern is clunky, and go may provide a better way to do it, but I
    didn't take the time to find it.
- I was impressed with GoDoc! I wrote this program without an IDE or language
  server, and it was easy to find an object and then look up what methods were
  available to me.
- At first it was unclear what collections were preferred. Using the [go
  standard library documentation](https://golang.org/pkg/), I looked for
  "containers", which led me to the standard linked-list implementation. I was
  surprised to not find a dynamic array implementation but moved forward with a
  list. It wasn't until much later that I stumbled into slices and discovered
  that they are a dynamic wrapper on arrays.
  - Once I discovered slices, it was hard to know what utilities were available
    to me. The Go standard library documentation doesn't have a section on
    slices, so I had to google the functionality I wanted like "golang append
    to slice" and "golang length of slice". This was frustrating.
- I found colly to be elegant and easy to use
- Network IO was painless, though file IO took some trial and error because I
  didn't realize folder permissions had to be manually specified (I'm on
  Linux).
- Both installing packages and creating my own package were seamless and easy
