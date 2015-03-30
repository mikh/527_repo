git pull gg master
gcc -O1 -fopenmp -o test_mmm_inter_omp test_mmm_inter_omp.c -lrt
export NUM_OMP_THREADS=4
./test_mmm_inter_omp