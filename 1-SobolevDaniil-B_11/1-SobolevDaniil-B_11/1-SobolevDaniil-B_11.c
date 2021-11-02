#define _CRT_SECURE_NO_WARNINGS

#include "memallocator.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>

#define MAX_SIZE 200
#define ITERATIONS 1000

int main() {
	FILE* file = fopen("memalloc_memfree.txt", "wb");
	void* mem = malloc((MAX_SIZE + 16) * ITERATIONS);
	meminit(mem, (MAX_SIZE + 16) * ITERATIONS);
	double* results = (double*)malloc(ITERATIONS * sizeof(double));
	int** pointers = (int**)malloc(ITERATIONS * sizeof(int*));
	long int start;

	LARGE_INTEGER freq;
	LARGE_INTEGER time1, time2;
	double elapsedTime;
	QueryPerformanceFrequency(&freq);

	for (int test = 0; test < ITERATIONS; test++) {
		QueryPerformanceCounter(&time1);

		for (int iter = 0; iter < test; iter++) {
			pointers[iter] = (int*)memalloc((int)rand() % MAX_SIZE);
		}

		for (int iter = 0; iter < test; iter++) {
			memfree(pointers[iter]);
		}


		QueryPerformanceCounter(&time2);
		elapsedTime = (float)(time2.QuadPart - time1.QuadPart) / freq.QuadPart;
		results[test] = elapsedTime;
	}

	for (int i = 0; i < ITERATIONS; i++) {
		fprintf(file, "%lf;", results[i]);
	}


	fclose(file);

	file = fopen("malloc_free.txt", "wb");

	for (int test = 0; test < ITERATIONS; test++) {
		QueryPerformanceCounter(&time1);

		for (int iter = 0; iter < test; iter++)
			pointers[iter] = (int*)malloc((int)rand() % MAX_SIZE);

		for (int iter = 0; iter < test; iter++)
			free(pointers[iter]);

		QueryPerformanceCounter(&time2);
		elapsedTime = (float)(time2.QuadPart - time1.QuadPart) / freq.QuadPart;
		results[test] = elapsedTime;
	}

	for (int i = 0; i < ITERATIONS; i++)
		fprintf(file, "%lf;", results[i]);

	fclose(file);

	free(results);
	free(pointers);
	free(mem);

	return 0;
}
