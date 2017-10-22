GCC=gcc
GCFLAGS=-O3 -std=c99
GOMPFLAGS=-fopenmp -ftree-vectorize -mavx

ICC=icc
ICFLAGS=-O3 -std=c99 -mmic
IOMPFLAGS=-qopenmp -vec

all: ser par

ser:
	$(ICC) $(ICFLAGS) ser-game_of_life.c -o ser-game_of_life.out

par:
	$(ICC) $(ICFLAGS) $(IOMPFLAGS) par-game_of_life.c -o par-game_of_life.out

gall: gser gpar

gser:
	$(GCC) $(GCFLAGS) ser-game_of_life.c -o ser-game_of_life.out

gpar:
	$(GCC) $(GCFLAGS) $(GOMPFLAGS) par-game_of_life.c -o par-game_of_life.out

clean: 
	rm *.out