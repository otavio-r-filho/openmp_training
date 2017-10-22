CC=gcc -std=c99
CFLAGS=-O3 -std=c99
OMPFLAGS=-fopenmp -ftree-vectorize -mavx

all: ser par

ser:
	$(CC) $(CFLAGS) ser-game_of_life.c -o ser-game_of_life.out

par:
	$(CC) $(CFLAGS) $(OMPFLAGS) par-game_of_life.c -o par-game_of_life.out

clean: 
	rm *.out