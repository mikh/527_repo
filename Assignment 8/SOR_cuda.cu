#include <math.h>

const int MATRIX_SIZE = 2000;

void initialize_array_2D(float **A, int len, int seed);

__global__ void kernel_SOR_internal(float **A, int omega, int N_x, int N_y){
	int xx = blockIdx.x * blockDim.x + threadIdx.x;
	int yy = blockIdy.y * blockDim.y + threadIny.y;
	float phi;

	if(xx > 0 && xx < (N_x-1) && yy > 0 && yy < (N_y-1)){
		phi = A[xx][yy] - .25((A[xx-1][yy] + A[xx+1][yy]) + (A[xx][yy-1] + A[xx][yy+1]))
		A[xx][yy] = abs(A[xx][yy] - (phi*omega));
	}
}

int main(int argc, char **argv){

	int i;
	
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
	initializeArray1D(h_A, arrLen, 2453);
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

