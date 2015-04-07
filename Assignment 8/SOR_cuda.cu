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
const int SOR_ITERATIONS = 3;
const int OMEGA = 1;

void initialize_array_2D(float **A, int len, int seed);

__global__ void kernel_SOR_internal(float *A, int omega, int N_x, int N_y){
	int i, j = 0;
	//different divisions needed for group of threads etc.
	int xx = blockIdx.x * blockDim.x + threadIdx.x;
	int yy = blockIdx.x * blockDim.y + threadIdx.y;
	float phi;
	for(i = MATRIX_SIZE/THREADS_PER_BLOCK_X*xx; i < MATRIX_SIZE/THREADS_PER_BLOCK_X*(xx+1); i++){
		for(j = MATRIX_SIZE/THREADS_PER_BLOCK_Y*yy; j < MATRIX_SIZE/THREADS_PER_BLOCK_Y*(yy+1); j++){
			if(i > 0 && i < (N_x-1) && j > 0 && j < (N_y-1)){
				phi = A[i*MATRIX_SIZE + j] - .25*((A[(i-1)*MATRIX_SIZE + j] + A[(i+1)*MATRIX_SIZE+j]) + (A[i*MATRIX_SIZE + (j-1)] + A[i*MATRIX_SIZE+(j+1)]));
				A[i*MATRIX_SIZE+j] = abs(A[i*MATRIX_SIZE+j] - (phi*omega));
			}
		}
	}
}

void SOR_internal_sequential(float **A, int omega, int xx, int yy, int N_x, int N_y){
	float phi;
	if(xx > 0 && xx < N_x-1 && yy > 0 && yy < N_y-1){
		phi = A[xx][yy] - .25*((A[xx-1][yy] + A[xx+1][yy]) + (A[xx][yy-1] + A[xx][yy+1]));
		A[xx][yy] = abs(A[xx][yy] - (phi*omega));
	}
}

void write_2d_array_to_file(float **A, int N_x, int N_y, char *filename){
	int i, j;
	FILE *f = fopen(filename, "w");
	for(i = 0; i < N_x; i++){
		for(j = 0; j < N_y-1; j++){
			fprintf(f,"%f, ",A[i][j]);
		}
		fprintf(f, "%f\n", A[i][N_y-1]);
	}
}

int main(int argc, char **argv){

	int i, j, k, errors = 0;
	dim3 dimGrid(NUM_BLOCKS,1,1);
	dim3 dimBlock(THREADS_PER_BLOCK_X,THREADS_PER_BLOCK_Y,1);
	//Arrays on GPU global memory
	float *g_A;

	//Arrays on host memory	
	float **h_A;
	float **h_A_test;


	FILE *f = fopen("mismatches.txt", "w");
	if(f == NULL){
		printf("Error opening file!\n");
		exit(1);
	}

	//Allocate arrays on GPU memory
	CUDA_SAFE_CALL(cudaMalloc((void **) &g_A, MATRIX_SIZE*MATRIX_SIZE*sizeof(float)));

	//Allocate arrays on host memory
	h_A = (float**) malloc(MATRIX_SIZE * sizeof(float*));
	h_A_test = (float**) malloc(MATRIX_SIZE * sizeof(float*));
	for(i = 0; i < MATRIX_SIZE; i++){
		h_A[i] = (float*) malloc(MATRIX_SIZE * sizeof(float));
		h_A_test[i] = (float*) malloc(MATRIX_SIZE * sizeof(float));
	}

	//initialize host arrays
	initialize_array_2D(h_A, MATRIX_SIZE, 2453);
	initialize_array_2D(h_A_test, MATRIX_SIZE, 2453);


	//create cuda events

	//record event on default stream


	//transfer array to GPU memory
	for(i = 0; i < MATRIX_SIZE; i++){
		CUDA_SAFE_CALL(cudaMemcpy(&g_A[i*MATRIX_SIZE], h_A[i], MATRIX_SIZE, cudaMemcpyHostToDevice));
	}

	//launch the kernel
	for(i = 0; i < SOR_ITERATIONS; i++){
		kernel_SOR_internal<<<dimGrid, dimBlock>>>(g_A, OMEGA, MATRIX_SIZE, MATRIX_SIZE);
	}



	//check for errors during launch
	CUDA_SAFE_CALL(cudaPeekAtLastError());

	//transfer results back to host
	for(i = 0; i < MATRIX_SIZE; i++){
		CUDA_SAFE_CALL(cudaMemcpy(h_A[i], &g_A[i*MATRIX_SIZE], MATRIX_SIZE, cudaMemcpyDeviceToHost));
	}
	//stop and destroy the timer

	//compute results on host
	for(i = 0; i < SOR_ITERATIONS; i++){
		for(j = 0; j < MATRIX_SIZE; j++){
			for(k = 0; k < MATRIX_SIZE; k++){
				SOR_internal_sequential(h_A_test, OMEGA, j, k, MATRIX_SIZE, MATRIX_SIZE);
			}
		}
	}

	//compare results
	for(i = 0; i < MATRIX_SIZE; i++){
		for(j = 0; j < MATRIX_SIZE; j++){
			if(h_A[i][j] != h_A_test[i][j]){
				errors++;
				fprintf(f, "Mismatch at [%d,%d] GPU = %f CPU = %f\n", i, j, h_A[i][j], h_A_test[i][j]);
			}
		}
	}
	write_2d_array_to_file(h_A, MATRIX_SIZE, MATRIX_SIZE, "GPU_output.txt");
	write_2d_array_to_file(h_A_test, MATRIX_SIZE, MATRIX_SIZE, "CPU_output.txt");

	//errors
	printf("Found %d errors\n", errors);
	fclose(f);

	//free up memory
	CUDA_SAFE_CALL(cudaFree(g_A));
	for(i = 0; i < MATRIX_SIZE; i++){
		free(h_A[i]);
		free(h_A_test[i]);
	}
	free(h_A);
	free(h_A_test);

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

