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
    int i, j, k;        /* misc */
    int NRA,            /* number of rows in matrix A */                
        NCA,            /* number of columns in matrix A */                
        NCB;            /* number of columns in matrix B */
    double comp_start,  /* computation start timer */
           comp_finish; /* computation finish timer */
    double junction;

    char *verb = getenv("VERBOSE");
    char *par_mul = getenv("PARALLEL_MUL");

    if(verb == NULL){
        verb = (char*) malloc(sizeof(char));
        *verb = '0';
    }

    if(par_mul == NULL){
        par_mul = (char*) malloc(sizeof(char));
        *par_mul = '0';
    }


    NRA = get_matrix_dims((const int) argc, (const char**) argv)[0];   /* set matrix A number of rows */
    NCA = get_matrix_dims((const int) argc, (const char**) argv)[1];   /* set matrix A number of cols */
    NCB = get_matrix_dims((const int) argc, (const char**) argv)[2];   /* set matrix B number of cols */

    /* Alocating matrices */
    double *a_ = (double*) malloc(NRA * NCA * sizeof(double));
    double *b_ = (double*) malloc(NCA * NCB * sizeof(double));
    double *c_ = (double*) malloc(NRA * NCB * sizeof(double));

    double *bT; /* Will holde the transpose of matrix b */

    printf("Starting parallel matrix multiple example with %d threads...\n", omp_get_max_threads());
    printf("Using matrix sizes a[%d][%d], b[%d][%d], c[%d][%d]\n",
        NRA,NCA,NCA,NCB,NRA,NCB);

    /* Initialize A, B, and C matrices */
    printf("Initializing matrices...\n");
    initialize_matrices_arr(a_, b_, c_, (const int) NRA, (const int) NCA, (const int) NCB);

    printf("Transposing matrix...\n");
    bT = transpose_matrix(b_, NCA, NCB);


    /* Perform matrix multiply */
    comp_start = omp_get_wtime();
    if(*par_mul == '1'){
        #pragma omp parallel private(i,j,k,junction)
        {
        #pragma omp single
        printf("Performing matrix parallel multiply with %d threads ...\n", omp_get_num_threads());
        #pragma omp parallel for
        for(i=0;i<NRA;i++){
            for(j=0;j<NCB;j++){
                junction = 0.0;
                for(k=0;k<NCA;k++){
                    junction += a_[(i * NCA) + k] * bT[(j * NCA) + k];
                }
                c_[(i * NCB) + j] = junction;
            }
        }
        } /* END OF PARALLEL SECTION */
    } else{
        printf("Performing serial matrix multiply ...\n");
        for(i=0;i<NRA;i++){
            for(j=0;j<NCB;j++){
                junction = 0.0;
                for(k=0;k<NCA;k++){
                    c_[(i * NCB) + j] += a_[(i * NCA) + k] * bT[(j * NCA) + k];
                }
            }
        }
    }
    comp_finish = omp_get_wtime();

    printf("Total computation time: %.2lfs\n", comp_finish - comp_start);

    if(verb[0] == '1'){
        print_matrix_arr(c_, NRA, NCB);
    }

    dealoc_matrices_arr(a_, b_, c_);
    free(bT);

    printf ("Done.\n");

    return 0;
}
