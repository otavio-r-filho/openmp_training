CC = gcc
CFLAGS = -O3 -std=c99
DFLAG = -Wall -g3
OMPFLAGS = -fopenmp -mavx -ftree-vectorize
LIBS=m

all: ser par

ser:
	$(CC) $(CVER) $(CFLAGS) ser_wave.c -o ser_wave.out -l$(LIBS)

par:
	$(CC) $(CFLAGS) $(OMPFLAGS) par_wave.c -o par_wave.out -l$(LIBS)

clean:
	rm *.out