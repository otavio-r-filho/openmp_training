CC=gcc -std=c99
CFLAGS=-O3 -std=c99
OMPFLAGS=-fopenmp -ftree-vectorize -mavx

all: clean ser par

ser:
	$(CC) $(CFLAGS) game_of_life-serial.c -o ser_gol

par:
	$(CC) $(CFLAGS) $(OMPFLAGS) game_of_life-parallel.c -o par_gol

clean: 
	rm *.out