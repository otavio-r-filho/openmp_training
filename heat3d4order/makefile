CC=gcc -std=c99
CFLAGS=-O3 -D VERBOSE
OMPFLAG=-fopenmp -ftree-vectorize -mavx

all: ser par

ser:
	$(CC) $(CFLAGS) ser_heat3d4order.c -o ser_h3d4o.out

par:
	$(CC) $(OMPFLAG) $(CFLAGS) par_heat3d4order.c -o par_h3d4o.out

clean:
	rm *.out
