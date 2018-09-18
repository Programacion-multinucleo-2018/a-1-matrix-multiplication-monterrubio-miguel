//compile with  g++ matrixMult_threads.cpp  -std=c++11 -fopenmp -Wall -Ofast
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <omp.h>


void multiplyMatrix(int *matrix1, int *matrix2, int *matrix3, int size) 
{
	int i = 0;
	#pragma omp parallel for private(i) shared(matrix1, matrix2, matrix3)
    for(i = 0; i < size; i++) 
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
	int size = 1000;

	int *matrix1 = (int *) malloc(size * size * sizeof(int));
	int *matrix2 = (int *) malloc(size * size * sizeof(int));

	for (int i = 1; i <= size*size; ++i)
	{
		matrix1[i - 1] = i;
		matrix2[i - 1] = i;
	}

	int *matrix3 = (int *) malloc(size * size * sizeof(int*));

	auto stopwatchStart = std::chrono::high_resolution_clock::now();
	multiplyMatrix(matrix1, matrix2, matrix3, size);
	auto stopwatchStop = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float, std::milli> duration_ms = stopwatchStop - stopwatchStart;

	std::cout << std::endl << "Duration of matrix multiplication: " << duration_ms.count() << " milliseconds" << std::endl;

	free(matrix1);
	free(matrix2);
	free(matrix3);

	return 0;
}