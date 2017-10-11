CC=gcc -std=c99
CFLAGS=-O3 -ftree-vectorize -mavx
PFLAGS=-fopenmp

all: clean ser_gol par_gol

ser_gol:
	$(CC) $(CFLAGS) game_of_life-serial.c -o ser_gol

par_gol:
	$(CC) $(CFLAGS) $(PFLAGS) game_of_life-parallel.c -o par_gol

clean: 
	rm -f ser_gol par_gol