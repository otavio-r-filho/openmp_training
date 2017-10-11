CC=gcc
CVER=-std=c99
CFLAGS=-O3
DFLAG=-g3
OMPFLAG=-fopenmp -ftree-vectorize -mavx

all: serial parallel

serial:
	$(CC) $(CVER) $(CFLAGS) ser_mm.c -o ser_mm

parallel:
	$(CC) $(OMPFLAG) $(CVER) $(CFLAGS) par_mm.c -o par_mm

par-debug:
	$(CC) $(OMPFLAG) $(CVER) $(CFLAGS) $(DFLAG) par_mm.c -o par_mm

clean:
	rm ser_mm par_mm
