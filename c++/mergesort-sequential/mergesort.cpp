#include <iostream>
#include <limits>
#include <random>

typedef unsigned long long ull;

const int CODE_WRONG_NUM_ARGUMENTS_ERROR = 1;
const int CODE_UNABLE_TO_PARSE_ERROR = 2;
const int CODE_INPUT_EXCEEDS_MAX_ERROR = 3;

/* any program that calls create_array is responsible for deleting the data 
 * pointed to
 */
float * create_array(ull n, unsigned seed) {
  float* array = new float[n];
  std::default_random_engine rand_generator (seed);

  if(n < rand_generator.max()) {
    for (ull i = 0; i < n; i++) {
      array[i] = rand_generator() % n;
    }
  }
  else {
    for (ull i = 0; i < n; i++) {
      array[i] = rand_generator();
    }
  }

  return array;
}

void print_array(float * array, ull n) {
  std::cout << "{";
  for(ull i = 0; i < n; i++){
    std::cout << array[i];

    if (i != n-1) {
      std::cout << ", ";
    }
  }
  std::cout << "}" << std::endl;
}

/*
 * for the purposes of this toy program, we only care about ascending order
 */
bool array_is_ordered(float * array, ull n) {
  for(ull i = 0; i < n-1; i++) {
    if(array[i] > array[i+1]) {
      return false;
    }
  }

  return true;
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


  // TODO: make seed random once results are consistent
  unsigned seed = 1;
  float * array = create_array(array_size, seed);

  while(array_is_ordered(array, array_size)) {
    std::cout << "Wow! You must be the luckiest person alive, because we just "
      << "generated an ordered array" << std::endl
      << " of length " << array_size << ". Re-generating array..." 
      << std::endl;
    print_array(array, array_size);
    
    std::cout << "old seed: " << seed << std::endl;
    seed += 11;
    std::cout << "new seed: " << seed << std::endl;

    delete[] array;
    array = create_array(array_size, seed);
  }

  print_array(array, array_size);

  delete[] array;

  return 0;
}
