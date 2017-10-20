CC = gcc
CFLAGS = -O3 -std=c99
DFLAG = -Wall -g3
OMPFLAGS = -fopenmp -mavx -ftree-vectorize

all: ser par

ser:
	$(CC) $(CFLAGS) ser_pi_calc.c -o ser_pi.out

par:
	$(CC) $(CFLAGS) $(OMPFLAGS) par_pi_calc.c -o par_pi.out

clean:
	rm *.out