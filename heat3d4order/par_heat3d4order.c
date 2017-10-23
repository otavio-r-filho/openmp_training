#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define C0 0.5
#define C1 0.75
#define C2 0.55
#define C3 0.25
#define C4 0.05
#define INICIO 1
#define FIM 2

int write_output(float *, int, int);
float get_time(int);

struct timeval inicio, final;

int main(int argc, char* argv[]){

	int niter,dim,save;
	int t,i,j,k,t0,t1, rc;
	float *heat_, tf_sec;
	double s_time, f_time;

	//executei /a.out 2 16 2
	if(argc < 4){
		printf("Error! Please inform number of iterations and matrix size. i.e: ./h3d4o.out 1000 500 500\n");
		exit(1);
	}
	niter = atoi(argv[1]);
	dim = atoi(argv[2]);
	save = atoi(argv[3]);
 
	#ifdef VERBOSE
	printf("Number of iterations %d\ndimension %d saved each %d timesteps\n",niter,dim,save);
	#endif

 	heat_ = (float*) malloc(sizeof(float)*2*dim*dim*dim);

	if(heat_ == NULL){
		printf("Error! Malloc fail\n");
		exit(1);
	}

	float (*heat)[dim][dim][dim] = (float (*)[dim][dim][dim]) heat_;
	// double (*a)[NRA][NCA] = (double (*)[NRA][NCA]) a_;

	#ifdef VERBOSE
	printf("Initializing matrix!\n");
	#endif

	/* Inicializando matriz com todas as celulas iguais a 1*/
	#pragma omp parallel for simd collapse(3)
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			for(k=0;k<dim;k++){
				heat[1][i][j][k] = heat[0][i][j][k] = 1;
			}
		}
	}

	#ifdef VERBOSE
	printf("Performing parallel matrix computation with %d threads!\n", omp_get_max_threads());
	#endif

	// get_time(INICIO);
	s_time = omp_get_wtime();
	for(t=1; t<niter+1; t++){
		t0 = (t % 2);
		t1 = (t0 + 1)%(2);
		#pragma omp parallel for collapse(3) private(t0, t1)
		for(i=4;i<dim-4;i++){
			for(j=4;j<dim-4;j++){
				for(k=4;k<dim-4;k++){
					heat[t0][i][j][k] = C0 * heat[t1][i][j][k] +

										C1 * (heat[t1][i+1][j][k] + heat[t1][i-1][j][k] +
											  heat[t1][i][j+1][k] + heat[t1][i][j-1][k] +
											  heat[t1][i][j][k+1] + heat[t1][i][j][k-1])+

										C2 * (heat[t1][i+2][j][k] + heat[t1][i-2][j][k] +
											  heat[t1][i][j+2][k] + heat[t1][i][j-2][k] +
											  heat[t1][i][j][k+2] + heat[t1][i][j][k-2])+

										C3 * (heat[t1][i+3][j][k] + heat[t1][i-3][j][k] +
											  heat[t1][i][j+3][k] + heat[t1][i][j-3][k] +
											  heat[t1][i][j][k+3] + heat[t1][i][j][k-3])+

										C4 * (heat[t1][i+4][j][k] + heat[t1][i-4][j][k] +
											  heat[t1][i][j+4][k] + heat[t1][i][j-4][k] +
											  heat[t1][i][j][k+4] + heat[t1][i][j][k-4]);
				}
			}
		}
	}
	// tf_sec = get_time(FIM);
	f_time = omp_get_wtime();
	// printf("Total computation time: %.1f seg\n",tf_sec);
	printf("Total computation time: %.4lfs\n", f_time - s_time);

	rc = write_output(heat_, dim, t0);
	if(!rc){
		printf("Matrix successfully saved in file: output_par.txt.\n");  
	}
    
	free(heat_);

	return 0;
}
 
float get_time(int mode){
 
	float tf_sec = 0.0;

	if(mode == INICIO){
		gettimeofday(&inicio, NULL);
	}
	else{
		gettimeofday(&final, NULL);
		unsigned long long seg = 1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000;
		tf_sec = ((float)seg)*1e-3;
	}
	return tf_sec;
}

int write_output(float *heat_, int dim, int timestep){
 
	FILE *fff;
	int i,j,k;
	float (*heat)[dim][dim][dim] = (float (*)[dim][dim][dim]) heat_;

	fff = fopen("output_par.txt","w");
	if (fff==NULL){
		printf("Error! It was not possible to open output file.\n");
		return 1;
	}

	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			for(k=0;k<dim;k++){
				fprintf(fff,"%.1f ",heat[timestep][i][j][k]);
				if((k % dim) == (dim - 1)){
					fprintf(fff, "\n");
					fprintf(fff, ((j % dim) != (dim - 1)) ? "" : "\n\n");
				}
			}
			//fprintf(fff, "\n");
		}
		//fprintf(fff, "\n\n");
	}

	fclose(fff);
	return 0;
}
