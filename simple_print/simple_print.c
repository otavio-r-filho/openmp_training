#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv){

    printf("\nHello before parallel region from thread %d of %d thread(s)\n", omp_get_thread_num(), omp_get_num_threads());
    printf("\n=-=-=-=-=-= START OF PARALLEL REGION =-=-=-=-=-=\n\n");
    #pragma omp parallel /* START OF PARALLEL REGION 0 */
    {
        printf("Hello inside parallel region from thread %d of %d thread(s)\n", omp_get_thread_num(), omp_get_num_threads());
    } /* END OF PARALLEL REGION 0 */
    printf("\n=-=-=-=-=-=- END OF PARALLEL REGION -=-=-=-=-=-=\n");

    printf("\nHello after parallel region from thread %d of %d thread(s)\n\n", omp_get_thread_num(), omp_get_num_threads());

    return 0;
}