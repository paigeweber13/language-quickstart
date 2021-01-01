SRC=mergesort.c
CC=gcc
EXEC=mergesort
COMMON_FLAGS=-Wall -fopenmp -o $(EXEC)

debug:
	$(CC) -g -pg $(COMMON_FLAGS) $(SRC)

release:
	$(CC) -O3 $(COMMON_FLAGS) $(SRC)
