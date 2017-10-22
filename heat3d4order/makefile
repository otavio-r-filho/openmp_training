GCC=gcc
GCFLAGS=-O3 -std=c99 -D VERBOSE
GOMPFLAGS=-fopenmp -ftree-vectorize -mavx

ICC=icc
ICFLAGS=-O3 -std=c99 -mmic -D VERBOSE
IOMPFLAGS=-qopenmp -vec

all: ser par

ser:
	$(ICC) $(ICFLAGS) ser_heat3d4order.c -o ser_h3d4o.out

par:
	$(ICC) $(ICFLAGS) $(IOMPFLAGS) par_heat3d4order.c -o par_h3d4o.out

gall: gser gpar

gser:
	$(GCC) $(GCFLAGS) ser_heat3d4order.c -o ser_h3d4o.out

gpar:
	$(GCC) $(GCFLAGS) $(GOMPFLAGS) par_heat3d4order.c -o par_h3d4o.out

clean:
	rm *.out
