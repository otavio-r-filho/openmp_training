CC = gcc
CFLAGS = -O3 -std=c99
DFLAG = -Wall -g3
OMPFLAGS = -fopenmp -mavx -ftree-vectorize
LIBS=m

all: serial parallel debug_serial debug_parallel

ser:
	$(CC) $(CVER) $(CFLAGS) ser_prime.c -o ser_prime.out -l$(LIBS)

par:
	$(CC) $(CFLAGS) $(OMPFLAGS) par_prime.c -o par_prime.out -l$(LIBS)

clean:
	rm *.out