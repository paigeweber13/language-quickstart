package main

import (
	"flag"
	"fmt"
	"math/rand"
	"strconv"
	"time"
)

func randomizeArray(array []float32) []float32 {
	// TODO: change to random seed
	// r := rand.New(rand.NewSource(time.Now().UnixNano()))
	r := rand.New(rand.NewSource(14))

	for i := 0; i < len(array); i++ {
		array[i] = r.Float32() * 100
	}

	return array
}

func isArrayInAscendingOrder(array []float32) bool {
	for i := 0; i < len(array)-1; i++ {
		if array[i] > array[i+1] {
			return false
		}
	}

	return true
}

// expects left and right to be contiguous in memory
func merge(left []float32, right []float32) []float32 {
	// 0 length, all capacity we need
	buffer := make([]float32, 0, len(left)+len(right))

	leftI, rightI := 0, 0

	for leftI < len(left) && rightI < len(right) {
		if left[leftI] < right[rightI] {
			buffer = append(buffer, left[leftI])
			leftI++
		} else {
			buffer = append(buffer, right[rightI])
			rightI++
		}
	}

	for ; leftI < len(left); leftI++ {
		buffer = append(buffer, left[leftI])
	}
	for ; rightI < len(right); rightI++ {
		buffer = append(buffer, right[rightI])
	}

	return buffer
}

func mergesort(array []float32) []float32 {
	mid := len(array) / 2

	if len(array) == 1 {
		return array
	}

	left := array[:mid]
	right := array[mid:]

	left = mergesort(left)
	right = mergesort(right)

	return merge(left, right)
}

const (
	singleMergesort   = "single"
	multipleSpeedtest = "speedtest"
)

type cliArgs struct {
	n    uint64
	goal string
}

func parseCommandLineArgs() cliArgs {

	var defaultN uint64 = 1000
	defaultGoal := singleMergesort

	nFlag := flag.Uint64("n", defaultN, "The size of the array to randomize and "+
		"sort. Defaults to "+strconv.FormatUint(defaultN, 10))
	goalFlag := flag.String("goal", singleMergesort, "Whether you want to do "+
		"a single mergesort or run multiple and speedtest them. Options are '"+
		singleMergesort+"' and '"+multipleSpeedtest+"'. Default is '"+
		defaultGoal+"'.")

	flag.Parse()

	return cliArgs{
		n:    *nFlag,
		goal: *goalFlag,
	}
}

func main() {
	args := parseCommandLineArgs()

	if args.goal == singleMergesort {
		array := make([]float32, args.n)
		array = randomizeArray(array)

		const ARRAY_PRINT_THRESHOLD = 21
		if args.n < ARRAY_PRINT_THRESHOLD {
			fmt.Println("Array before sorting:", array)
		}

		array = mergesort(array)

		if args.n < ARRAY_PRINT_THRESHOLD {
			fmt.Println("Array after sorting:", array)
		}

		if isArrayInAscendingOrder(array) {
			fmt.Println("SUCCESS: Array is sorted!")
		} else {
			fmt.Println("FAILURE: Array is NOT sorted!")
		}
	} else if args.goal == multipleSpeedtest {
		fmt.Printf("%7v,%9v,%17v,%15v,%19v,%14v\n", "result", "n",
			"items_per_second", "alloc_duration", "randomize_duration",
			"sort_duration")

		var i uint64
		for i = 1; i < args.n+1; i *= 10 {
			startAlloc := time.Now()
			array := make([]float32, i)
			durationAlloc := time.Now().Sub(startAlloc)

			startRandomize := time.Now()
			array = randomizeArray(array)
			durationRandomize := time.Now().Sub(startRandomize)

			startSort := time.Now()
			array = mergesort(array)
			durationSort := time.Now().Sub(startSort)

			durationTotal := durationAlloc + durationRandomize + durationSort

			var resultStr string
			if isArrayInAscendingOrder(array) {
				resultStr = "success"
			} else {
				resultStr = "failure"
			}

			fmt.Printf("%7s,%9.2e,%17.2e,%15.4f,%19.4f,%14.4f\n",
				resultStr, float32(i), float64(i)/durationTotal.Seconds(),
				durationAlloc.Seconds(), durationRandomize.Seconds(),
				durationSort.Seconds())
		}
	} else {
		fmt.Println("ERROR: Unrecognized goal")
		flag.Usage()
	}
}
