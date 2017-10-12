/******************************************************************************
* FILE: ser_mm.c
* DESCRIPTION:  
*   Serial Matrix Multiply - C Version
* AUTHOR: Blaise Barney
* LAST REVISED: 04/12/05
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "help_funcs.h"

int main(int argc, char *argv[])
{
    int i, j, k;      /* misc */
    int NRA,          /* number of rows in matrix A */                
        NCA,          /* number of columns in matrix A */                
        NCB;          /* number of columns in matrix B */

    const char *verb = getenv("VERBOSE");

    NRA = get_matrix_dims(argc, argv)[0];   /* set matrix A number of rows */
    NCA = get_matrix_dims(argc, argv)[1];   /* set matrix A number of cols */
    NCB = get_matrix_dims(argc, argv)[2];   /* set matrix B number of cols */

    // double a[NRA][NCA], 		/* matrix A to be multiplied */
    //        b[NCA][NCB],      	/* matrix B to be multiplied */
    //        c[NRA][NCB];		/* result matrix C */

    double *a_ = (double*) malloc(NRA * NCA * sizeof(double));
    double *b_ = (double*) malloc(NCA * NCB * sizeof(double));
    double *c_ = (double*) malloc(NRA * NCB * sizeof(double));

    double (*a)[NCA] = (double (*)[NCA]) a_;
    double (*b)[NCB] = (double (*)[NCB]) b_;
    double (*c)[NCB] = (double (*)[NCB]) c_;

    printf("Starting serial matrix multiple example...\n");
    printf("Using matrix sizes a[%d][%d], b[%d][%d], c[%d][%d]\n",
        NRA,NCA,NCA,NCB,NRA,NCB);

    /* Initialize A, B, and C matrices */
    printf("Initializing matrices...\n");
    for (i=0; i<NRA; i++)
        for (j=0; j<NCA; j++)
                a[i][j]= i+j;

    for (i=0; i<NCA; i++)
        for (j=0; j<NCB; j++)
                b[i][j]= i*j;

    for(i=0;i<NRA;i++)
        for(j=0;j<NCB;j++)
                c[i][j] = 0.0;

    /* Perform matrix multiply */
    printf("Performing matrix multiply...\n");
    for(i=0;i<NRA;i++)
        for(j=0;j<NCB;j++)
                for(k=0;k<NCA;k++)
                    c[i][j]+= a[i][k] * b[k][j];

    if(verb[0] == '1'){
        print_matrix_arr(c_, NRA, NCB);
    }

    printf ("Done.\n");

    return 0;
}
