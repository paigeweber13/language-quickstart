import os
import parseopt
import parseutils
import random
import strformat
import times

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


# -------- cli -------- #
type
  ThingToDo = enum
    singleExecution, speedtestMultiple


# -------- main -------- #
proc main() =
  var goal: ThingToDo = singleExecution
  var n: Natural
  var missingN = true

  var usage = "Usage: " & getAppFilename() & " [-s] n\n" &
    "  -s,speedtest: if included, will speedtest all arrays between size \n" &
    "                1 and n. If omitted, will only run run mergesort for \n" &
    "                size n, with more verbose output.\n"
  var p = initOptParser(commandLineParams())    

  # 'case' must cover all cases, so we may as well do 'while true:'
  while true:
    p.next()
    case p.kind
    of cmdEnd: break
    of cmdShortOption, cmdLongOption:
      if p.key == "s" or p.key == "speedtest":
        goal = speedtestMultiple
    of cmdArgument:
      discard parseSaturatedNatural(p.key, n)
      missingN = false

  if missingN:
    echo "Error! must supply 'n'"
    echo usage
    return

  case goal

  of singleExecution:      
    const ARRAY_PRINT_THRESHOLD = 21

    echo fmt"Allocating and randomizing array of length {n}..."
    var arr = newRandomArray(n)
    echo "Done!"

    if len(arr) < ARRAY_PRINT_THRESHOLD:
      echo "Array is: ", arr
      
    echo "Sorting array..."
    arr = mergeSort(arr)
    echo "Done!"

    if len(arr) < ARRAY_PRINT_THRESHOLD:
      echo "Array is: ", arr

    if isSorted(arr):
      echo "SUCCESS: array is sorted"
    else:
      echo "FAILURE: array is *not* sorted"

  of speedtestMultiple:
    var i = 1
    var arr: seq[float]
    var resultString: string

    echo fmt"""{"result":>7},{"n":>9},{"items_per_second":>17},""" &
      fmt"""{"alloc_duration":>15},{"sort_duration":>14}"""
    while i < n+1:
      let startAllocAndRandomize = cpuTime()
      arr = newRandomArray(i)
      let durationAllocAndRandomize = cpuTime() - startAllocAndRandomize

      let startMergeSort = cpuTime()
      arr = mergeSort(arr)
      let durationMergeSort = cpuTime() - startMergeSort

      let totalTime = durationAllocAndRandomize + durationMergeSort

      if isSorted(arr):
        resultString = "success"
      else:
        resultString = "failure"

      echo fmt"{resultString},{float(i):9.2e},{float(i)/totalTime:17.2e}," &
        fmt"{durationAllocAndRandomize:15.4f},{durationMergeSort:14.4f}"

      i *= 10


main()

