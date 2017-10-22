module load intel/2017_u1
export SINK_LD_LIBRARY_PATH=${SINK_LD_LIBRARY_PATH}:/home_nfs/murilo1/openmp_training/mm
/opt/intel/mic/bin/micnativeloadex $1 -a "$2" -e "$3"