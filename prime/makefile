GCC=gcc
GCFLAGS=-O3 -std=c99
GOMPFLAGS=-fopenmp -ftree-vectorize -mavx

ICC=icc
ICFLAGS=-O3 -std=c99  -mmic
IOMPFLAGS=-qopenmp -vec
LIBS=m

all: ser par

ser:
	$(ICC) $(ICFLAGS) ser_prime.c -o ser_prime.out -l$(LIBS)

par:
	$(ICC) $(ICFLAGS) $(IOMPFLAGS) par_prime.c -o par_prime.out -l$(LIBS)

gall: gser gpar

gser:
	$(GCC) $(GCFLAGS) ser_prime.c -o ser_prime.out -l$(LIBS)

gpar:
	$(GCC) $(GCFLAGS) $(GOMPFLAGS) par_prime.c -o par_prime.out -l$(LIBS)

clean:
	rm *.out