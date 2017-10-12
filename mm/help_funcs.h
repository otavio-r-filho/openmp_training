#ifndef _HELP_FUNCS_H_
#define _HELP_FUNCS_H_

void print_matrix_arr(double *arr, int row, int col){
    int i, j;

    printf("Here is the result matrix:");

    for (i = 0; i < row; i++) { 
    printf("\n"); 
          for (j = 0; j < col; j++){
                printf("%6.2f   ", arr[i*col + j]);
                printf(((j % 15) == 14) ? "\n" : "");
          }
    }
    printf("\n");
}

void print_matrix(double **arr, int row, int col){
    int i, j;
    
        printf("Here is the result matrix:");
    
        for (i = 0; i < row; i++) { 
        printf("\n"); 
              for (j = 0; j < col; j++){
                    printf("%6.2f   ", arr[i][j]);
                    printf(((j % 15) == 14) ? "\n" : "");
              }
        }
        printf("\n");
}

int *get_matrix_dims(int argc, char **argv){

    int *dims = (int*) malloc(3 * sizeof(int));

    switch(argc){
        case 2:
        dims[0] = dims[1] = dims[2] = atoi(argv[1]);
        break;

        case 3:
        dims[0] = dims[1] = atoi(argv[1]);
        dims[2] = atoi(argv[2]);
        break;

        case 4:
        dims[0] = atoi(argv[1]);
        dims[1] = atoi(argv[2]);
        dims[2] = atoi(argv[3]);
        break;

        default:
        dims[0] = dims[1] = dims[2] = 4;
        break;
    }

    return dims;
}

void dealoc_matrices(double **a, double **b, double **c, int NRA, int NCA, int NCB){

    int i;

    for(i = 0; i < NRA; i++){
        free(a[i]);
        free(c[i]);
    }

    for(i = 0; i < NCA; i++){
        free(b[i]);
    }

    free(a);
    free(b);
    free(c);
}

#endif