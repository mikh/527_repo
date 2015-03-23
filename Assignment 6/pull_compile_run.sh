git pull gg master
gcc -pthread -o test_SOR_multithreaded test_SOR_multithreaded.c -lm -lrt
./test_SOR_multithreaded