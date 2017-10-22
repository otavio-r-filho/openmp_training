module load intel/2017_u1
export SINK_LD_LIBRARY_PATH=${SINK_LD_LIBRARY_PATH}:/home_nfs/murilo1/openmp_training/heat3d4order
/opt/intel/mic/bin/micnativeloadex $1 -a "$2 $3 $4" -e "$5"