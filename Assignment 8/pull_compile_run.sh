git pull gg master
nvcc -o SOR_cuda_p3 SOR_cuda_p3.cu cuPrintf.cu -lrt
./SOR_cuda_p3