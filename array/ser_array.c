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
#include <time.h>
#define	ARRAYSIZE	16000000

int main(int argc, char *argv[])
{
	int     i; 			/* loop variable */
	//float	data[ARRAYSIZE]; 	/* the intial array */
	float *data;
	double s_time, f_time;
	data = malloc(sizeof(float)*ARRAYSIZE);

	printf("Starting serial array example...\n");
	printf("Using array of %d floats. Requires %ld bytes\n",ARRAYSIZE,sizeof(float)*ARRAYSIZE);

	/* Initialize the array */
	printf("Initializing array...\n");
	for(i=0; i<ARRAYSIZE; i++) {
		data[i] =  i * 1.0;
	}

	/* Do a simple value assignment to each of the array elements */
	printf("Performing computation on array elements...\n");
	s_time = (double) clock();
	for(i=1; i < ARRAYSIZE; i++) {
		data[i] = data[i] + i * 1.0;
	}
	f_time = (double) clock();

	/* Print a few sample results */
	printf("Sample results\n");
	printf("   data[1]=%e\n",  data[1]);
	printf("   data[100]=%e\n",  data[100]);
	printf("   data[1000]=%e\n",  data[1000]);
	printf("   data[10000]=%e\n",  data[10000]);
	printf("   data[100000]=%e\n",  data[100000]);
	printf("   data[1000000]=%e\n",  data[1000000]);
	printf("Total comutation time: %.4lfs\n", (f_time - s_time)/CLOCKS_PER_SEC);
	printf("\nAll Done!\n");
}
