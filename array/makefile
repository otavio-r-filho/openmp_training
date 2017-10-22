GCC=gcc
GCFLAGS=-O3 -std=c99
GOMPFLAGS=-fopenmp -ftree-vectorize -mavx

ICC=icc
ICFLAGS=-O3 -std=c99  -mmic
IOMPFLAGS=-qopenmp -vec

all: ser par

ser:
	$(ICC) $(ICFLAGS) ser_array.c -o ser_array.out

par:
	$(ICC) $(ICFLAGS) $(IOMPFLAGS) par_array.c -o par_array.out

gall: gser gpar

gser:
	$(GCC) $(GCFLAGS) ser_array.c -o ser_array.out

gpar:
	$(GCC) $(GCFLAGS) $(GOMPFLAGS) par_array.c -o par_array.out

clean:
	rm *.out
