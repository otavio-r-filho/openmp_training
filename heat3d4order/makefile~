CC=gcc -std=c99
CFLAGS=-O3 -D VERBOSE
OMPFLAG=-fopenmp -ftree-vectorize -mavx

all: ser_h3d4o par_h3d4o

ser_h3d4o:
	$(CC) $(CFLAGS) ser_heat3d4order.c -o ser_h3d4o

par_h3d4o:
	$(CC) $(OMPFLAG) $(CFLAGS) par_heat3d4order.c -o par_h3d4o

clean:
	rm ser_h3d4o par_h3d4o *txt
