GCC=gcc
GCFLAGS=-O3 -std=c99
GOMPFLAGS=-fopenmp -ftree-vectorize -mavx

ICC=icc
ICFLAGS=-O3 -std=c99  -mmic
IOMPFLAGS=-qopenmp -vec

all: ser par

ser:
	$(ICC) $(ICFLAGS) ser_pi_calc.c -o ser_pi.out

par:
	$(ICC) $(ICFLAGS) $(IOMPFLAGS) par_pi_calc.c -o par_pi.out

gall: gser gpar

gser:
	$(GCC) $(GCFLAGS) ser_pi_calc.c -o ser_pi.out

gpar:
	$(GCC) $(GCFLAGS) $(GOMPFLAGS) par_pi_calc.c -o par_pi.out

clean:
	rm *.out