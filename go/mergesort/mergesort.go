package main

import (
	"fmt"
	"math/rand"
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

func main() {
	n := 10

	array := make([]float32, n)
	array = randomizeArray(array)

	fmt.Println("Array before sorting:", array)
	array = mergesort(array)
	fmt.Println("Array after sorting:", array)

	if isArrayInAscendingOrder(array) {
		fmt.Println("SUCCESS: Array is sorted!")
	} else {
		fmt.Println("FAILURE: Array is NOT sorted!")
	}
}
