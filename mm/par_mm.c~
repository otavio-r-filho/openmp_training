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

#define NRA 2500		/* number of rows in matrix A */
#define NCA 2500		/* number of columns in matrix A */
#define NCB 2500		/* number of columns in matrix B */

double* transpose(double *a, int r_length, int c_length);
void print_matrix_inline(double *m, int r_length, int c_length);
void print_matrix(double *m, int r_length, int c_length);

int main(int argc, char *argv[])
{
    int i, j, k;
    // double a[NRA][NCA], 		/* matrix A to be multiplied */
    //        b[NCA][NCB],      	/* matrix B to be multiplied */
    //        c[NRA][NCB];		/* result matrix C */

    /* Contiguous memory allocation makes better use of cache */
    double *a;
    double *b;
    double *c;

    a = (double*) malloc(NRA * NCA * sizeof(double));
    b = (double*) malloc(NCA * NCB * sizeof(double));
    c = (double*) malloc(NRA * NCB * sizeof(double));

    omp_set_dynamic(0);
    int num_procs = omp_get_num_procs();
    omp_set_num_threads(num_procs);
    printf("Num of threads: %d\n", num_procs);

    printf("Starting serial matrix multiple example...\n");
    printf("Using matrix sizes a[%d][%d], b[%d][%d], c[%d][%d]\n",
            NRA,NCA,NCA,NCB,NRA,NCB);

    /* Initialize A, B, and C matrices */
    printf("Initializing matrices...\n");
    #pragma omp parallel private(i, j, k)
    { /* START OF PARALLEL REGION 0 */

    #pragma omp for simd nowait collapse(2)
    for (i=0; i<NRA; i++){
        for (j=0; j<NCA; j++){
                a[(i * NCA) + j] = i+j;
        }
    }

    #pragma omp for simd nowait collapse(2)
    for (i=0; i<NCA; i++){
        for (j=0; j<NCB; j++){
            b[(i * NCB) + j] = i*j;
        }
    }

    #pragma omp for simd collapse(2)
    for(i=0;i<NRA;i++){
        for(j=0;j<NCB;j++){
            c[(i * NCB) + j] = 0.0;
        }
    }

    /* Perform matrix multiply */
    #pragma omp single
    printf("Performing matrix multiply...\n");

    #pragma omp single
    b = transpose(b, NCA, NCB);

    #pragma omp for
    for(i=0;i<NRA;i++){
        for(j=0;j<NCB;j++){
                double junction = 0;
                for(k=0;k<NCA;k++){
                    junction += a[(i * NCA) + k] * b[(j * NCA) + k];
                }
                c[(i * NCB) + j] = junction;
        }
    }

    } /* END OF PARALLEL REGION 0*/

    /*printf("Here is the result matrix:\n");
    print_matrix(c, NRA, NCB);*/
    printf ("Done.\n");

    free(a);
    free(b);
    free(c);

    return 0;
}

double* transpose(double *a, int r_length, int c_length) {
    int i, j;

    double *aT = (double*) malloc(r_length * c_length * sizeof(double));

    for(i = 0; i < r_length; i++) {
        for(j = 0; j < c_length; j++) {
            aT[(j * r_length) + i] = a[(i * c_length) + j];
        }
    }

    return aT;
}

void print_matrix_inline(double *m, int r_length, int c_length) {
    int i;

    for(i = 0; i < (r_length * c_length);  i++){
        printf("%f ", m[i]);
    }
    printf("\n");
    printf("\n");
}

void print_matrix(double *m, int r_length, int c_length) {
    int i, j;

    int line_length = (c_length > 10) ? 10 : c_length;
    for(i = 0; i < r_length; i++) {
        for(j = 0; j < c_length; j++) {
            printf("%6.2f   \t", m[(i * c_length) + j]);
            printf(((j % line_length) == (line_length - 1)) ? "\n" : "");
        }
    }
}
