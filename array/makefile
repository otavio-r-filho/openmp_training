CC=gcc
CVER=-std=c99
CFLAGS=-O3
DFLAG=-g3
OMPFLAGS=-fopenmp -ftree-vectorize -mavx

all: v1 v2 v3 v4

ser:
	$(CC) $(CVER) $(CFLAGS) ser_array.c -o ser_array.out

par:
	$(CC) $(CVER) $(CFLAGS) $(OMPFLAGS) par_array.c -o par_array.out

clean:
	rm *.out
