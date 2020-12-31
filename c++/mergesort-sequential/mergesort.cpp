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
  float * array = create_array(array_size, 1);
  delete[] array;

  return 0;
}
