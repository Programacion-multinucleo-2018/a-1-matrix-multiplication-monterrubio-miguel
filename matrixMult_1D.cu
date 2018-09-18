//incomplete
#include <iostream>
#include <cstdlib>
#include <chrono>

__global__ void multiplyMatrix_GPU(int *matrix1, int *matrix2, int *matrix3, int size) 
{
    for(int i = 0; i < size; i++) 
    {
        for(int j=0; j < size; j++) 
        {
            for(int k=0; k < size; k++) 
            {
                matrix3[i * size + j] += matrix1[i * size + k] * matrix2[j + k * size];
            }
        }
    }
}


int main()
{
    int dev = 0;
    cudaDeviceProp deviceProp;
    cudaGetDeviceProperties(&deviceProp, dev);
    printf("Using Device %d: %s\n", dev, deviceProp.name);
    cudaSetDevice(dev);


	int size = 1000;



	int *matrix3 = (int *) malloc(size * size * sizeof(int*));

	auto stopwatchStart = std::chrono::high_resolution_clock::now();
	multiplyMatrix_GPU(matrix1, matrix2, matrix3, size);
	auto stopwatchStop = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float, std::milli> duration_ms = stopwatchStop - stopwatchStart;

	std::cout << std::endl << "Duration of matrix multiplication: " << duration_ms.count() << " milliseconds" << std::endl;

	free(matrix1);
	free(matrix2);
	free(matrix3);

	return 0;
}