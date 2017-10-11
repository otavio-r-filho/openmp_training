CC = gcc
CVER = -std=c99
CFLAGS = -O3
DFLAG = -Wall -g3
OMPFLAGS = -fopenmp -mavx -ftree-vectorize
LIBS=m

all: serial parallel debug_serial debug_parallel

serial:
	$(CC) $(CVER) $(CFLAGS) ser_prime.c -o ser_prime -l$(LIBS)

parallel:
	$(CC) $(CFLAGS) $(OMPFLAGS) par_prime.c -o par_prime -l$(LIBS)

debug_serial: 
	$(CC) $(CVER) $(CFLAGS) $(DFLAG) ser_prime.c -o d-ser_prime -l$(LIBS)

debug_parallel:
	$(CC) $(CFLAGS) $(OMPFLAGS) $(DFLAG) par_prime.c -o d-par_prime -l$(LIBS)

clean:
	rm *_prime