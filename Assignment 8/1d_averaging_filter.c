__global__ void Average1(float* A, float* B, int N)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x
	if (i > 0 && i < N-1)
		B[i] = (A[i-1] + A[i] + A[i+1])/3;
}


__global__ void Average2(float A[N], float B[N])
{
	int i = blockIdx.x * blockDim.x + threadIdx.x
	if (i > 0 && i < N-1)
		A[i] = (B[i-1] + B[i] + B[i+1])/3;
}


int main()
{
	// Kernel invocations -- Since these are
	// asynchronous, must force to launch all at once.
	dim3 dimGrid(16,1,1);
	dim3 dimBlock(256,1,1);
	for (int i = 0; i < 50; i++) {
		Average1<<<dimGrid, dimBlock>>>(A, B, N);
		cudaThreadSynchronize();
		Average2<<<dimGrid, dimBlock>>>(A, B, N);
		cudaThreadSynchronize();
	}
}


// cudaThreadSynchronize()  Blocks until the device has completed
// all preceding requested tasks