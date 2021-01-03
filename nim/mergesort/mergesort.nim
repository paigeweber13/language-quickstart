import random

proc newRandomArray(len: Natural): seq[float] = 
  # 'randomize' seeds the random number generator so there are different
  # results each time

  # randomize()

  var arr = newSeq[float](len)
  for i in low(arr)..high(arr):
    arr[i] = rand(100.0)

  return arr

# proc merge()

proc main() =
  var arr = newSeq[float](10)
  echo arr
  arr = newRandomArray(10)
  echo arr

main()
