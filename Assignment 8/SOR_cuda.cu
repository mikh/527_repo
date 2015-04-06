#include <math.h>
#include <cstdio>
#include <cstdlib>

// Assertion to check for errors
#define CUDA_SAFE_CALL(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, char *file, int line, bool abort=true)
{
	if (code != cudaSuccess) 
	{
		fprintf(stderr,"CUDA_SAFE_CALL: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}

const int MATRIX_SIZE = 2000;
const int NUM_BLOCKS = 1;
const int THREADS_PER_BLOCK_X = 16;
const int THREADS_PER_BLOCK_Y = 16;
const int SOR_ITERATIONS = 2000;
const int OMEGA = 1;

void initialize_array_2D(float **A, int len, int seed);

__global__ void kernel_SOR_internal(float **A, int omega, int N_x, int N_y){
	int i, j;
	//different divisions needed for group of threads etc.
	int xx = blockIdx.x * blockDim.x + threadIdx.x;
	int yy = blockIdx.x * blockDim.y + threadIdx.y;
	float phi;
	for(i = MATRIX_SIZE/THREADS_PER_BLOCK_X*xx; i < MATRIX_SIZE/THREADS_PER_BLOCK_X*(xx+1); i++){
		for(j = MATRIX_SIZE/THREADS_PER_BLOCK_Y*yy; j < MATRIX_SIZE/THREADS_PER_BLOCK_Y*(yy+1); j++){
			if(i > 0 && i < (N_x-1) && j > 0 && j < (N_y-1)){
				phi = A[i][j] - .25*((A[i-1][j] + A[i+1][j]) + (A[i][j-1] + A[i][j+1]));
				A[i][j] = abs(A[i][j] - (phi*omega));
			}
		}
	}
}

int main(int argc, char **argv){

	int i;
	dim3 dimGrid(NUM_BLOCKS,1,1);
	dim3 dimBlock(THREADS_PER_BLOCK_X,THREADS_PER_BLOCK_Y,1);
	//Arrays on GPU global memory
	float **g_A;

	//Arrays on host memory	
	float **h_A;


	//Allocate arrays on GPU memory
	CUDA_SAFE_CALL(cudaMalloc((void **)&g_A, MATRIX_SIZE * sizeof(float*)));
	for(i = 0; i < MATRIX_SIZE; i++){
		CUDA_SAFE_CALL(cudaMalloc((void**)&(g_A[i]), MATRIX_SIZE * sizeof(float)));
	}

	//Allocate arrays on host memory
	h_A = (float**) malloc(MATRIX_SIZE * sizeof(float*));
	for(i = 0; i < MATRIX_SIZE; i++){
		h_A[i] = (float*) malloc(MATRIX_SIZE * sizeof(float));
	}

	//initialize host arrays
	initialize_array_2D(h_A, MATRIX_SIZE, 2453);



	//create cuda events

	//record event on default stream


	//transfer array to GPU memory
	CUDA_SAFE_CALL(cudaMemcpy(g_A, h_A, MATRIX_SIZE, cudaMemcpyHostToDevice));
	for(i = 0; i < MATRIX_SIZE; i++){	//NOTE: might have to use pointer stuff here
		CUDA_SAFE_CALL(cudaMemcpy(g_A[i], h_A[i], MATRIX_SIZE, cudaMemcpyHostToDevice));
	}

	//launch the kernel
	for(i = 0; i < SOR_ITERATIONS; i++){
		kernel_SOR_internal<<<dimGrid, dimBlock>>>(g_A, OMEGA, MATRIX_SIZE, MATRIX_SIZE);
	}

	//check for errors during launch
	CUDA_SAFE_CALL(cudaPeekAtLastError());

	//transfer results back to host
	CUDA_SAFE_CALL(cudaMemcpy(h_A, g_A, MATRIX_SIZE, cudaMemcpyDeviceToHost));
	for(i = 0; i < MATRIX_SIZE; i++){	//NOTE: might have to use pointer stuff here
		CUDA_SAFE_CALL(cudaMemcpy(h_A[i], g_A[i], MATRIX_SIZE, cudaMemcpyDeviceToHost));
	}

	//stop and destroy the timer

	//compute results on host

	//compare results

	//errors

	//free up memory
	for(i = 0; i < MATRIX_SIZE; i++){
		CUDA_SAFE_CALL(cudaFree(g_A[i]));
	}
	CUDA_SAFE_CALL(cudaFree(g_A));

	for(i = 0; i < MATRIX_SIZE; i++){
		free(h_A[i]);
	}
	free(h_A);

	return 0;
}

void initialize_array_2D(float **A, int len, int seed){
	int i, j;
	float randNum;
	srand(seed);

	for(i = 0; i < len; i++){
		for(j = 0; j < len; j++){
			randNum = (float) rand();
			A[i][j] = randNum;
		}
	}
}

