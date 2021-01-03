import random

proc newRandomArray(len: Natural): seq[float] = 
  # 'randomize' seeds the random number generator so there are different
  # results each time

  # randomize()
  const MAX_NUMBER = 100.0

  var arr = newSeq[float](len)
  for i in low(arr)..high(arr):
    arr[i] = rand(MAX_NUMBER)

  return arr

proc isSorted(arr: seq[float]): bool =
  for i in low(arr)..high(arr) - 1:
    if arr[i] > arr[i+1]:
      return false

  return true

# proc merge()

proc main() =
  var arr: seq[float] = @[0.0, 1.0, 2.0, 3.0]
  echo arr
  echo "is arr sorted? ", isSorted(arr)

  arr = newRandomArray(10)
  echo arr
  echo "is arr sorted? ", isSorted(arr)

main()
