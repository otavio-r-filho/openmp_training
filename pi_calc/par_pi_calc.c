/***************************************************************************
 * FILE: ser_pi_calc.c
 * DESCRIPTION:  
 *   Serial pi Calculation - C Version
 *   This program calculates pi using a "dartboard" algorithm.  See
 *   Fox et al.(1988) Solving Problems on Concurrent Processors, vol.1
 *   page 207.  
 * AUTHOR: unknown
 * REVISED: 02/23/12 Blaise Barney
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void srandom (unsigned seed);  
double dboard (int darts);
long rand_r(int*);

#define DARTS 100000   	/* number of throws at dartboard */
#define ROUNDS 1000    	/* number of times "darts" is iterated */

int main(int argc, char *argv[]){
	double pi;          	/* average of pi after "darts" is thrown */
	double avepi;       	/* average pi value for all iterations */
	int i, n;
	double s_time, f_time;
	// omp_set_num_threads(4);

	printf("Starting parallel version of pi calculation using dartboard algorithm with %d threads...\n", omp_get_max_threads());
				/* seed the random number generator */
	avepi = 0;
	s_time = omp_get_wtime();
	for (i = 0; i < ROUNDS; i++) {
		/* Perform pi calculation on serial processor */
		
		pi = dboard(DARTS);

		avepi = ((avepi * i) + pi)/(i + 1); 
		printf("   After %3d throws, average value of pi = %10.8f\n", (DARTS * (i + 1)),avepi);
	}
	f_time = omp_get_wtime();
	printf("\nReal value of PI: 3.1415926535897 \n");
	printf("Total computation time: %.4lfs\n", f_time - s_time);

	return 0;
}


/*****************************************************************************
 * dboard
 *****************************************************************************/
#define sqr(x)	((x)*(x))
long random(void);

double dboard(int darts)
{
	double x_coord,       /* x coordinate, between -1 and 1  */
		   y_coord,       /* y coordinate, between -1 and 1  */
		   pi,            /* pi  */
		    r;             /* random number scaled between 0 and 1  */
	int score, n;            /* number of darts that hit circle */
	unsigned int cconst;  /* must be 4-bytes in size */
	int r_seed;
	time_t t;
/*************************************************************************
 * The cconst variable must be 4 bytes. We check this and bail if it is
 * not the right size
 ************************************************************************/
	if (sizeof(cconst) != 4) {
		printf("Wrong data size for cconst variable in dboard routine!\n");
		printf("See comments in source file. Quitting.\n");
		exit(1);
	}
	/* 2 bit shifted to MAX_RAND later used to scale random number between 0 and 1 */
	cconst = 2 << (31 - 1);
	score = 0;

/***********************************************************************
 * Throw darts at board.  Done by generating random numbers
 * between 0 and 1 and converting them to values for x and y
 * coordinates and then testing to see if they "land" in
 * the circle."  If so, score is incremented.  After throwing the
 * specified number of darts, pi is calculated.  The computed value
 * of pi is returned as the value of this function, dboard.
 ************************************************************************/
	#pragma omp parallel private(r, y_coord, x_coord, r_seed)
	{
		r_seed = 72542 + 43*omp_get_thread_num();
		// r_seed = 72542 * ((int) omp_get_wtime())*omp_get_thread_num();
		#pragma omp for reduction(+: score)
		for (n = 1; n <= darts; n++) {
			/* generate random numbers for x and y coordinates */
			//r = (double)random()/MAX_RAND;
			r = (double)rand_r(&r_seed)/RAND_MAX;
			x_coord = (2.0 * r) - 1.0;
			//r = (double)random()/MAX_RAND;
			r = (double)rand_r(&r_seed)/RAND_MAX;
			y_coord = (2.0 * r) - 1.0;

			/* if dart lands in circle, increment score */
			if ((sqr(x_coord) + sqr(y_coord)) <= 1.0){
				score++;
			}
		}
	}

	/* calculate pi */
	pi = 4.0 * (double)score/(double)darts;
	return(pi);
} 
