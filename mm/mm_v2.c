/******************************************************************************
* FILE: ser_mm.c
* DESCRIPTION:  
*   Serial Matrix Multiply - C Version
* AUTHOR: Blaise Barney
* LAST REVISED: 04/12/05
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "help_funcs.h"

int main(int argc, char *argv[])
{
    int i, j, k;        /* misc */
    int NRA,            /* number of rows in matrix A */                
        NCA,            /* number of columns in matrix A */                
        NCB;            /* number of columns in matrix B */
    double comp_start,  /* computation start timer */
           comp_finish; /* computation finish timer */

    const char *verb = getenv("VERBOSE");

    NRA = get_matrix_dims((const int) argc, (const char**) argv)[0];   /* set matrix A number of rows */
    NCA = get_matrix_dims((const int) argc, (const char**) argv)[1];   /* set matrix A number of cols */
    NCB = get_matrix_dims((const int) argc, (const char**) argv)[2];   /* set matrix B number of cols */

    /* Alocating matrices */
    double *a_ = (double*) malloc(NRA * NCA * sizeof(double));
    double *b_ = (double*) malloc(NCA * NCB * sizeof(double));
    double *c_ = (double*) malloc(NRA * NCB * sizeof(double));

    /* Transforming matrices to improve readability */
    double (*a)[NCA] = (double (*)[NCA]) a_;
    double (*b)[NCB] = (double (*)[NCB]) b_;
    double (*c)[NCB] = (double (*)[NCB]) c_;

    printf("Starting serial matrix multiple example...\n");
    printf("Using matrix sizes a[%d][%d], b[%d][%d], c[%d][%d]\n",
        NRA,NCA,NCA,NCB,NRA,NCB);

    /* Initialize A, B, and C matrices */
    printf("Initializing matrices...\n");
    initialize_matrices_arr(a_, b_, c_, (const int) NRA, (const int) NCA, (const int) NCB);

    /* Perform matrix multiply */
    printf("Performing matrix multiply...\n");
    comp_start = (double) clock();
    for(i=0;i<NRA;i++){
        for(j=0;j<NCB;j++){
            for(k=0;k<NCA;k++){
                c[i][j]+= a[i][k] * b[k][j];
            }
        }
    }
    comp_finish = (double) clock();

    printf("Total computation time %lfs\n", (comp_finish - comp_start) / CLOCKS_PER_SEC);

    if(verb[0] == '1'){
        print_matrix_arr(c_, NRA, NCB);
    }

    printf ("Done.\n");

    return 0;
}
