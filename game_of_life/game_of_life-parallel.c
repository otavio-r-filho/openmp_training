/***********************

Conway Game of Life

serial version

************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NI 2000      /* array sizes */

#define NJ 2000

#define NSTEPS 500    /* number of time steps */

int main(int argc, char *argv[]) {
  int i, j, n, im, ip, jm, jp, ni, nj, nsum, isum, seed;
  // int **old, **new; 
  float x;

  int num_procs = omp_get_num_procs();
  omp_set_num_threads(num_procs);
  omp_set_nested(1);

  /* allocate arrays */

  ni = NI + 2;  /* add 2 for left and right ghost cells */
  nj = NJ + 2;
  old = malloc(ni*sizeof(int*));
  new = malloc(ni*sizeof(int*));

  omp_set_dynamic(0);

#pragma omp parallel num_threads(num_procs)
{ /* Start of parallel region 0 */
  #pragma omp for
  for(i=0; i<ni; i++){
    old[i] = malloc(nj*sizeof(int));
    new[i] = malloc(nj*sizeof(int));
  }

/*  initialize elements of old to 0 or 1 */
  #pragma omp for private(seed) collapse(2)
  for(i=1; i<=NI; i++){
    for(j=1; j<=NJ; j++){
      seed = i*j;
      x = rand_r(&seed)/((float)RAND_MAX + 1);
      if(x<0.5){
	      old[i][j] = 0;
      } else {
	      old[i][j] = 1;
      }
    }
  }

  /*  time steps */
  #pragma omp single
  { /* Start single reagion 0*/
  #pragma omp parallel num_threads(1)
  { /* Start of parallel region 1 */
  for(n=0; n<NSTEPS; n++){
    /* corner boundary conditions */
     /* Start of parallel region 2 */
    old[0][0] = old[NI][NJ];
    old[0][NJ+1] = old[NI][1];
    old[NI+1][NJ+1] = old[1][1];
    old[NI+1][0] = old[1][NJ];

    #pragma omp parallel num_threads(8)
    {
    /* left-right boundary conditions */
    #pragma omp for
    for(i=1; i<=NI; i++){
      #pragma omp critical
      {
      old[i][0] = old[i][NJ];
      old[i][NJ+1] = old[i][1];
      }
    }

    /* top-bottom boundary conditions */
    #pragma omp for
    for(j=1; j<=NJ; j++){
      #pragma omp critical
      {
      old[0][j] = old[NI][j];
      old[NI+1][j] = old[1][j];
      }
    }

    #pragma omp for private(i, j, im, ip, jp, jm, nsum) collapse(2)
    for(i=1; i<=NI; i++){
      for(j=1; j<=NJ; j++){
        im = i-1;
        ip = i+1;
        jm = j-1;
        jp = j+1;

        nsum =  old[im][jp] + old[i][jp] + old[ip][jp]
          + old[im][j ]              + old[ip][j ] 
          + old[im][jm] + old[i][jm] + old[ip][jm];

        switch(nsum){

        case 3:
          new[i][j] = 1;
          break;

        case 2:
          new[i][j] = old[i][j];
          break;

        default:
          new[i][j] = 0;
        }
      }
    }

    /* copy new state into old state */
    #pragma omp for simd collapse(2)
    for(i=1; i<=NI; i++){
      for(j=1; j<=NJ; j++){
	      old[i][j] = new[i][j];
      }
    }
    } /* End of parallel region 2, num_threads(8)*/
  }
  } /* End of parallel region 1, num_threads(1) */
  } /* End of single region 0*/
   

  /*  Iterations are done; sum the number of live cells */
  #pragma omp single//atomic write
  isum = 0;

  #pragma omp barrier

  #pragma omp for simd collapse(2) \
          reduction(+ : isum)
  for(i=1; i<=NI; i++){
    for(j=1; j<=NJ; j++){
      //isum = isum + new[i][j];
      isum += new[i][j];
    }
  }

  #pragma omp single
  printf("\nNumber of live cells = %d\n", isum);

  #pragma omp for
  for(i = 0; i < ni; i++) {
    free(old[i]);
    free(new[i]);
  }
} /* End of parallel region 0, num_threads(8) */

  free(old);
  free(new);

  return 0;
}
