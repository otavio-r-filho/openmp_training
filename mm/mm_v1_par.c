/******************************************************************************
* FILE: ser_mm.c
* DESCRIPTION:  
*   Serial Matrix Multiply - C Version
* AUTHOR: Blaise Barney
* LAST REVISED: 04/12/05
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "help_funcs.h"

int main(int argc, char *argv[])
{
    int i, j, k;        /* misc */
    int NRA,            /* number of rows in matrix A */                
        NCA,            /* number of columns in matrix A */                
        NCB;            /* number of columns in matrix B */
    double junction;    /* variable used to avoid concurrency inconsistencies */

    const char *verb = getenv("VERBOSE");   /* conditional env to print the result */

    NRA = get_matrix_dims(argc, argv)[0];   /* set matrix A number of rows */
    NCA = get_matrix_dims(argc, argv)[1];   /* set matrix A number of cols */
    NCB = get_matrix_dims(argc, argv)[2];   /* set matrix B number of cols */

    double **a = (double**) malloc(NRA * sizeof(double*));
    double **b = (double**) malloc(NCA * sizeof(double*));
    double **c = (double**) malloc(NRA * sizeof(double*));

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
    #pragma omp parallel private(i,j,k, junction) /* START PARALLEL REGION 0 */
    {
    
    printf("Initializing matrices...\n");
    #pragma omp for collapse(2)
    for (i=0; i<NRA; i++){
        for (j=0; j<NCA; j++){
                a[i][j]= i+j;
        }
    }
    
    #pragma omp for collapse(2)
    for (i=0; i<NCA; i++){
        for (j=0; j<NCB; j++){
                b[i][j]= i*j;
        }
    }

    #pragma omp for collapse(2)
    for(i=0;i<NRA;i++){
        for(j=0;j<NCB;j++){
                c[i][j] = 0.0;
        }
    }

    /* Perform matrix multiply */
    #pragma omp single
    printf("Performing matrix multiply...\n");

    #pragma omp for collapse(2)
    for(i=0;i<NRA;i++){
        for(j=0;j<NCB;j++){
            junction = 0;
            for(k=0;k<NCA;k++){
                junction += a[i][k] * b[k][j];
            }
            c[i][j] = junction;
        }
    }
    } /* END PARALLE REGION 0 */

    if(verb[0] == '1'){
        print_matrix(c, NRA, NCB);
    }

    dealoc_matrices(a, b, c, NRA, NCA, NCB);

    printf ("Done.\n");

    return 0;
}
