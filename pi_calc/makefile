CC = gcc
CVER = -std=c99
CFLAGS = -O3
DFLAG = -Wall -g3
OMPFLAGS = -fopenmp -mavx -ftree-vectorize

all: serial parallel debug_serial debug_parallel

serial:
	$(CC) $(CVER) $(CFLAGS) ser_pi_calc.c -o ser_pi

parallel:
	$(CC) $(CFLAGS) $(OMPFLAGS) par_pi_calc.c -o par_pi

debug_serial: 
	$(CC) $(CVER) $(CFLAGS) $(DFLAG) ser_pi_calc.c -o d-ser_pi

debug_parallel:
	$(CC) $(CFLAGS) $(OMPFLAGS) $(DFLAG) par_pi_calc.c -o d-par_pi

clean:
	rm *pi