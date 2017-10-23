module load intel/2017_u1
export SINK_LD_LIBRARY_PATH=${SINK_LD_LIBRARY_PATH}:/home_nfs/murilo1/openmp_training/simple_print
/opt/intel/mic/bin/micnativeloadex simple_print.out -e "OMP_NUM_THREADS=8"