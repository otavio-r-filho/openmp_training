module load intel/2017_u1
export SINK_LD_LIBRARY_PATH=${SINK_LD_LIBRARY_PATH}:/home_nfs/murilo1/openmp_training/pi_calc
/opt/intel/mic/bin/micnativeloadex $1 -e "$2"