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
#include <omp.h>
#include "help_funcs.h"

int main(int argc, char *argv[])
{
    int i, j, k;      /* misc */
    double **a,       /* matrix A */
           **b,       /* matrix B */
           **c;       /* matrix C */
    int NRA,          /* number of rows in matrix A */                
        NCA,          /* number of columns in matrix A */                
        NCB;          /* number of columns in matrix B */
    double comp_start, comp_finish;

    const char *verb = getenv("VERBOSE");   /* conditional env to print the result */

    NRA = get_matrix_dims((const int) argc, (const char**) argv)[0];   /* set matrix A number of rows */
    NCA = get_matrix_dims((const int) argc, (const char**) argv)[1];   /* set matrix A number of cols */
    NCB = get_matrix_dims((const int) argc, (const char**) argv)[2];   /* set matrix B number of cols */

    a = (double**) malloc(NRA * sizeof(double*));
    b = (double**) malloc(NCA * sizeof(double*));
    c = (double**) malloc(NRA * sizeof(double*));

    for(i = 0; i < NRA; i++){
        a[i] = (double*) malloc(NCA * sizeof(double));
        c[i] = (double*) malloc(NCB * sizeof(double));
    }

    for(i = 0; i < NCA; i++){
        b[i] = (double*) malloc(NCB * sizeof(double));
    }

    printf("Starting serial matrix multiple example...\n");
    printf("Using matrix sizes a[%d][%d], b[%d][%d], c[%d][%d]\n",
           NRA,NCA,NCA,NCB,NRA,NCB);

    /* Initialize A, B, and C matrices */
    printf("Initializing matrices...\n");
    initialize_matrices(a, b, c, NRA, NCA, NCB);

    /* Perform matrix multiply */
    printf("Performing matrix multiply...\n");
    comp_start = (double) clock();
    for(i=0;i<NRA;i++){
        for(j=0;j<NCB;j++){
            for(k=0;k<NCA;k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    comp_finish = (double) clock();
    printf("Total computation time %lfs\n", (comp_finish - comp_start) / CLOCKS_PER_SEC);

    if(verb[0] == '1'){
        print_matrix((const double**) c, (const int) NRA, (const int) NCB);
    }

    dealoc_matrices(a, b, c, (const int) NRA, (const int) NCA, (const int) NCB);

    printf ("Done.\n");

    return 0;
}
