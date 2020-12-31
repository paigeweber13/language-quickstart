#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned long long ull;

const ull MAX_ARRAY_SIZE_FOR_PRINTS = 21;

const int CODE_WRONG_NUM_ARGUMENTS_ERROR = 1;
const int CODE_UNABLE_TO_PARSE_ERROR = 2;
const int CODE_INPUT_EXCEEDS_MAX_ERROR = 3;

/* 
 * randomizes the array 'array'
 */
void randomize_array(float * array, ull n, unsigned seed) {
  srand(seed);

  for (ull i = 0; i < n; i++) {
    array[i] = rand();
  }
}

void print_array(float * array, ull n) {
  printf("{");
  for(ull i = 0; i < n; i++){
    printf("%.1f", array[i]);

    if (i != n-1) {
      printf(", ");
    }
  }
  printf("}\n");
}

/*
 * for the purposes of this toy program, we only care about ascending order
 * 
 * return value is binary, true or false.
 */
char array_is_ordered(float * array, ull n) {
  for(ull i = 0; i < n-1; i++) {
    if(array[i] > array[i+1]) {
      return 0;
    }
  }

  return 1;
}

/*
 * assumes a and b are contiguous in memory, with 'a' first
 */
void merge(float * a, ull a_n, float * b, ull b_n) {
  ull a_i = 0; // index of array a
  ull b_i = 0; // index of array b

  // merging in place requires a lot of shifting, so is very memory-intensive in
  // worst case.

  // instead, let's just create another temporary array 'merged'

  float * merged = (float*)malloc(sizeof(float) * (a_n+b_n));
  ull merged_i = 0;

  while(a_i < a_n && b_i < b_n) {
    if(a[a_i] > b[b_i]) {
      // then b should come first
      merged[merged_i] = b[b_i];
      b_i++;
    }
    else {
      // else a is <= b so we put b next
      merged[merged_i] = a[a_i];
      a_i++;
    }

    merged_i++;
  }

  // if either 'a' or 'b' has items left, copy them to 'merged'
  if(a_i < a_n) {
    memcpy(merged + merged_i, a + a_i, sizeof(float) * (a_n - a_i));
  }
  if(b_i < b_n) {
    memcpy(merged + merged_i, b + b_i, sizeof(float) * (b_n - b_i));
  }

  // then move stuff from 'merged' back into original array
  memcpy(a, merged, sizeof(float) * (a_n+b_n));

  free(merged);
}

/*
 * recursively merge-sorts an array in-place.
 */
void mergesort(float * array, ull n) {
  if(n == 1)
    return;
  
  ull left_n = n/2;
  float * left_array = array;

  ull right_n = n - n/2;
  float * right_array = array + left_n;

  mergesort(left_array, left_n);
  mergesort(right_array, right_n);

  merge(left_array, left_n, right_array, right_n);
}

int main(int argc, char **argv) {
  if(argc < 2) {
    fprintf(stderr, "ERROR: Must specify array length as first and only "
      "parameter.\nUsage: %s n\n", argv[0]);
    return CODE_WRONG_NUM_ARGUMENTS_ERROR;
  }

  /* get command line arg */
  ull array_size;

  array_size = strtoull(argv[1], NULL, 0);
  
  /* initialize array*/
  // TODO: make seed random once results are consistent
  unsigned seed = clock();

  clock_t malloc_time_start = clock();
  float * array = (float*)malloc(sizeof(float) * array_size);
  clock_t malloc_time_end = clock();

  clock_t randomize_time_start = clock();
  randomize_array(array, array_size, seed);
  clock_t randomize_time_end = clock();


  while(array_is_ordered(array, array_size)) {
    printf("Wow! You must be the luckiest person alive, because we just "
      "generated an ordered array\n"
      " of length %llu.\n", array_size);

    if(array_size < MAX_ARRAY_SIZE_FOR_PRINTS) {
      printf("Array we generated: ");
      print_array(array, array_size);
    }

    printf("Re-generating array...\n");
    
    printf("old seed: %u\n", seed);
    seed += 11;
    printf("new seed: %u\n", seed);

    randomize_array(array, array_size, seed);

    if(array_size < MAX_ARRAY_SIZE_FOR_PRINTS) {
      printf("New array: ");
      print_array(array, array_size);
    }
  }

  if(array_size < MAX_ARRAY_SIZE_FOR_PRINTS) {
    printf("Array before starting: ");
    print_array(array, array_size);
  }


  /* ----- do mergesort ----- */
  // float * sorted = new float[array_size];
  clock_t sort_time_start = clock();
  mergesort(array, array_size);
  clock_t sort_time_end = clock();


  /* ----- results ----- */
  /* check for successful sort! */
  char result_str[8];
  if(array_is_ordered(array, array_size)) {
    strcpy(result_str, "success");
  }
  else {
    strcpy(result_str, "failure");
  }

  if(array_size < MAX_ARRAY_SIZE_FOR_PRINTS) {
    printf("Array after sorting: ");
    print_array(array, array_size);
  }

  /* calculate durations */
  clock_t malloc_duration = malloc_time_end-malloc_time_start;
  double malloc_seconds = ((double)malloc_duration)/CLOCKS_PER_SEC;
  unsigned long malloc_minutes = ((unsigned long)malloc_seconds)/60;
  malloc_seconds -= malloc_minutes * 60;

  clock_t randomize_duration = randomize_time_end-randomize_time_start;
  double randomize_seconds = ((double)randomize_duration)/CLOCKS_PER_SEC;
  unsigned long randomize_minutes = ((unsigned long)randomize_seconds)/60;
  randomize_seconds -= randomize_minutes * 60;

  clock_t sort_duration = sort_time_end-sort_time_start;
  double sort_seconds = ((double)sort_duration)/CLOCKS_PER_SEC;
  unsigned long sort_minutes = ((unsigned long)sort_seconds)/60;
  sort_seconds -= sort_minutes * 60;

  // printf("sort_time_start   is: %lu\n", sort_time_start);
  // printf("sort_time_end     is: %lu\n", sort_time_end);
  // printf("sort_duration     is: %lu\n", sort_duration);
  // printf("sort_minutes      is: %lu\n", sort_minutes);
  // printf("sort_seconds      is: %f\n", sort_seconds);


  // header for this csv is "result,n,malloc_time,randomize_time,sort_time"
  // all times are given in the format "m:s.ms"

  // it is safe to remove spaces before processing

  printf(" result,       n,     malloc_time,  randomize_time,        sort_time\n");
  printf("%s,%.2e,%6lu:%9.4f,%6lu:%9.4f,%6lu:%9.4f\n", result_str, (double)array_size, 
    malloc_minutes, malloc_seconds,
    randomize_minutes, randomize_seconds,
    sort_minutes, sort_seconds);


  /* clean up */
  free(array);

  return 0;
}
