git pull gg master
gcc -O1 -fopenmp -o test_omp_for test_omp_for.c -lrt -lm
export NUM_OMP_THREADS=4
./test_omp_for