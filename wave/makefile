CC = gcc
CVER = -std=c99
CFLAGS = -O3
DFLAG = -Wall -g3
OMPFLAGS = -fopenmp -mavx -ftree-vectorize
LIBS=m

all: serial parallel debug_serial debug_parallel

serial:
	$(CC) $(CVER) $(CFLAGS) ser_wave.c -o ser_wave -l$(LIBS)

parallel:
	$(CC) $(CFLAGS) $(OMPFLAGS) par_wave.c -o par_wave -l$(LIBS)

debug_serial: 
	$(CC) $(CVER) $(CFLAGS) $(DFLAG) ser_wave.c -o d-ser_wave -l$(LIBS)

debug_parallel:
	$(CC) $(CFLAGS) $(OMPFLAGS) $(DFLAG) par_wave.c -o d-par_wave -l$(LIBS)

clean:
	rm *_wave