import random

# -------- utilities -------- #
proc newRandomArray(len: Natural): seq[float] = 
  # 'randomize' seeds the random number generator so there are different
  # results each time

  randomize()
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


# -------- mergesort -------- #
proc merge(left: seq[float], left_n: Natural, right: seq[float], 
    right_n: Natural): seq[float] = 

  var
    buffer = newSeq[float](left_n + right_n)
    left_i = 0
    right_i = 0
    buffer_i = 0
  
  while left_i < left_n and right_i < right_n:
    if left[left_i] < right[right_i]:
      buffer[buffer_i] = left[left_i]
      left_i += 1
    else:
      buffer[buffer_i] = right[right_i]
      right_i += 1
    
    buffer_i += 1

  while left_i < left_n:
    buffer[buffer_i] = left[left_i]
    buffer_i += 1
    left_i += 1

  while right_i < right_n:
    buffer[buffer_i] = right[right_i]
    buffer_i += 1
    right_i += 1

  return buffer


proc mergeSort(arr: seq[float], n: Natural): seq[float] =
  if n == 1:
    return arr

  let mid = n div 2

  let left = mergesort(arr[0..mid], mid)
  let right = mergesort(arr[mid..^1], n-mid)

  return merge(left, mid, right, n-mid)


proc mergeSort(arr: seq[float]): seq[float] =
  return mergeSort(arr, len(arr))


# -------- main -------- #
proc main() =
  var arr: seq[float] = @[0.0, 1.0, 2.0, 3.0]
  echo arr
  echo "is arr sorted? ", isSorted(arr)

  arr = newRandomArray(10)
  echo arr
  echo "is arr sorted? ", isSorted(arr)

  arr = mergesort(arr)
  echo arr
  echo "is arr sorted? ", isSorted(arr)


main()

