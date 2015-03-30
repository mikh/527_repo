git pull gg master
gcc -O1 -fopenmp -o test_omp test_omp.c -lrt -lm
export NUM_OMP_THREADS=4
./test_SOR_multithreaded