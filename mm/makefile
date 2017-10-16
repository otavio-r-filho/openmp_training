CC=gcc
CVER=-std=c99
CFLAGS=-O3
DFLAG=-g3
OMPFLAG=-fopenmp -ftree-vectorize -mavx

all: v1 v2 v3 v4

v1:
	$(CC) $(CVER) $(CFLAGS) mm_v1.c -o mm_v1.out

v2:
	$(CC) $(CVER) $(CFLAGS) mm_v2.c -o mm_v2.out

v3:
	$(CC) $(CVER) $(OMPFLAG) $(CFLAGS) mm_v3.c -o mm_v3.out

v4:
	$(CC) $(CVER) $(OMPFLAG) $(CFLAGS) mm_v4.c -o mm_v4.out

clean:
	rm *.out
