git pull gg master
gcc -O1 -fopenmp -o test_SOR test_SOR.c -lrt -lm
export NUM_OMP_THREADS=4
./test_SOR