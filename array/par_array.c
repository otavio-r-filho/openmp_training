/******************************************************************************
* FILE: ser_array.c
* DESCRIPTION: 
*   Serial Example - Array Assignment - C Version
*   In this simple example, an array is initialized and values assigned.
* AUTHOR: Blaise Barney
* LAST REVISED:  04/15/05
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define	ARRAYSIZE	16000000

int main(int argc, char *argv[])
{
    int     i; 			/* loop variable */
    float *data; 	/* the intial array */
    data = malloc(sizeof(float)*ARRAYSIZE);
    double s_time, f_time;

    #pragma omp parallel
    {

        #pragma omp single
        {
            printf("Starting parallel array example with %d threads...\n", omp_get_num_threads());
            printf("Using array of %d floats. Requires %ld bytes\n",ARRAYSIZE,sizeof(float)*ARRAYSIZE);
        }

        /* Initialize the array */
        #pragma omp single
        printf("Initializing array...\n");

        #pragma omp for nowait
        for(i=0; i<ARRAYSIZE; i++) {
            data[i] =  i * 1.0;
        }

        /* Do a simple value assignment to each of the array elements */
        #pragma omp single
        printf("Performing computation on array elements...\n");

        #pragma omp single
        s_time = omp_get_wtime();

        #pragma omp for
        for(i=1; i < ARRAYSIZE; i++) {
            data[i] = data[i] + i * 1.0;
        }
        #pragma omp single
        f_time = omp_get_wtime();

    }

    /* Print a few sample results */
    printf("Sample results\n");
    printf("   data[1]=%e\n",  data[1]);
    printf("   data[100]=%e\n",  data[100]);
    printf("   data[1000]=%e\n",  data[1000]);
    printf("   data[10000]=%e\n",  data[10000]);
    printf("   data[100000]=%e\n",  data[100000]);
    printf("   data[1000000]=%e\n",  data[1000000]);
    printf("Total computation time: %.4lfs\n", f_time - s_time);
    printf("\nAll Done!\n");
}
