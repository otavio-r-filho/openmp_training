GCC=gcc
GCFLAGS=-O3 -std=c99
GOMPFLAGS=-fopenmp -ftree-vectorize -mavx

ICC=icc
ICFLAGS=-O3 -std=c99  -mmic
IOMPFLAGS=-qopenmp -vec

all: ser par

ser:
	$(ICC) $(ICFLAGS) mm_v1.c -o mm_v1.out

par:
	$(ICC) $(ICFLAGS) $(IOMPFLAGS) mm_v4.c -o mm_v4.out

gall: gser gpar

gser:
	$(GCC) $(GCFLAGS) mm_v1.c -o mm_v1.out

gpar:
	$(GCC) $(GCFLAGS) $(GOMPFLAGS) mm_v4.c -o mm_v4.out

clean:
	rm *.out