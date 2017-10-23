GCC=gcc
GCFLAGS=-O3 -std=c99 -D VERBOSE
GOMPFLAGS=-fopenmp -ftree-vectorize -mavx

ICC=icc
ICFLAGS=-O3 -std=c99 -mmic -D VERBOSE
IOMPFLAGS=-qopenmp -vec

all:
	$(ICC) $(ICFLAGS) $(IOMPFLAGS) simple_print.c -o simple_print.out

gall:
	$(GCC) $(GCFLAGS) $(GOMPFLAGS) simple_print.c -o simple_print.out

clean:
	rm *.out