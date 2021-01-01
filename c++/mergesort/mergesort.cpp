#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

typedef unsigned long long ull;

const ull ARRAY_DEBUG_THRESHOLD = 21;

const int CODE_WRONG_NUM_ARGUMENTS_ERROR = 1;
const int CODE_UNABLE_TO_PARSE_ERROR = 2;
const int CODE_INPUT_EXCEEDS_MAX_ERROR = 3;

/* 
 * randomizes the array 'array'
 */
void randomize_array(std::vector<float> &array, unsigned seed) {
  std::default_random_engine rand_generator (seed);

  unsigned n;
  if(array.size() < ARRAY_DEBUG_THRESHOLD) {
    n = 100;
  } else {
    n = rand_generator.max();
  }

  for (ull i = 0; i < array.size(); i++) {
    array[i] = rand_generator() % n;
  }
}

void print_array(const std::vector<float> &array) {
  std::cout << "{";
  for(ull i = 0; i < array.size(); i++){
    std::cout << array[i];

    if (i != array.size()-1) {
      std::cout << ", ";
    }
  }
  std::cout << "}" << std::endl;
}

/*
 * for the purposes of this toy program, we only care about ascending order
 */
bool array_is_ordered(const std::vector<float> &array) {
  for(ull i = 0; i < array.size()-1; i++) {
    if(array[i] > array[i+1]) {
      return false;
    }
  }

  return true;
}

/*
 * merges two sections of array into buffer, then copies results back into 
 * array
 */
void merge(std::vector<float> &array, std::vector<float> &buffer, 
    size_t start, size_t mid, size_t end) {

  size_t l_i = start;
  size_t r_i = mid;

  size_t buffer_i = start;

  while(l_i < mid && r_i < end) {
    if(array[l_i] > array[r_i]) {
      // then b should come first
      buffer[buffer_i] = array[r_i];
      r_i++;
    }
    else {
      // else a is <= b so we put b next
      buffer[buffer_i] = array[l_i];
      l_i++;
    }

    buffer_i++;
  }

  // if either 'a' or 'b' has items left, copy them to 'buffer'
  while (l_i < mid) {
    buffer[buffer_i] = array[l_i];
    buffer_i++;
    l_i++;
  }
  while (r_i < end) {
    buffer[buffer_i] = array[r_i];
    buffer_i++;
    r_i++;
  }

  // then move stuff from 'buffer' back into original array
  for(size_t i = start; i < end; i++) {
    array[i] = buffer[i];
  }
}

/*
 * recursively merge-sorts an array in-place.
 */
void mergesort(std::vector<float> &array, std::vector<float> &buffer, 
    size_t i_start, size_t i_end) {
  
  size_t n = i_end - i_start;

  if(n == 1)
    return;
  
  ull left_n = n/2;

  mergesort(array, buffer, i_start, i_start + left_n);
  mergesort(array, buffer, i_start + left_n, i_end);

  merge(array, buffer, i_start, i_start + left_n, i_end);
}

/* 
 * init function for mergesort
 */ 
void mergesort(std::vector<float> &array) {
  std::vector<float> buffer(array.size());

  mergesort(array, buffer, 0, array.size());
}

int main(int argc, char **argv) {
  if(argc < 2) {
    std::cerr << "ERROR: Must specify array length as first and only parameter"
      << std::endl
      << "Usage: " << argv[0] << " n" << std::endl;
    return CODE_WRONG_NUM_ARGUMENTS_ERROR;
  }


  ull array_size;

  try {
    array_size = std::stoull(argv[1]);
  } 
  
  catch (const std::invalid_argument& e) {
    std::cerr << "ERROR: could not parse argument to integer." << std::endl;
    return CODE_UNABLE_TO_PARSE_ERROR;
  } 
  
  catch (const std::out_of_range& e) {
    std::cerr << "ERROR: number specified is too large. Please specify a "
      << "number smaller than " 
      << std::numeric_limits<ull>::max() << std::endl;
    return CODE_INPUT_EXCEEDS_MAX_ERROR;
  }


  unsigned seed = std::chrono::high_resolution_clock::now()
    .time_since_epoch().count();
  std::vector<float> array(array_size);
  randomize_array(array, seed);

  while(array_is_ordered(array)) {
    std::cout << "Wow! You must be the luckiest person alive, because we just "
      << "generated an ordered array" << std::endl
      << " of length " << array_size << "." << std::endl;

    if(array_size < ARRAY_DEBUG_THRESHOLD) {
      std::cout << "Array we generated: ";
      print_array(array);
    }

    std::cout << "Re-generating array..." << std::endl;
    
    std::cout << "old seed: " << seed << std::endl;
    seed += 11;
    std::cout << "new seed: " << seed << std::endl;

    randomize_array(array, seed);

    if(array_size < ARRAY_DEBUG_THRESHOLD) {
      std::cout << "New array: ";
      print_array(array);
    }
  }

  if(array_size < ARRAY_DEBUG_THRESHOLD) {
    std::cout << "Array before starting: ";
    print_array(array);
  }


  /* do mergesort */
  mergesort(array);


  /* check for successful sort! */
  if(array_is_ordered(array)) {
    std::cout << "SUCCESS: array is sorted!" << std::endl;
  }
  else {
    std::cerr << "FAILURE: array is not sorted!" << std::endl;
  }

  if(array_size < ARRAY_DEBUG_THRESHOLD) {
    std::cout << "Array after sorting: ";
    print_array(array);
  }

  return 0;
}
