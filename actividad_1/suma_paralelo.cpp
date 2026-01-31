// RegionesParalelas.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include <omp.h>

#define N 1000
#define chunk 100
#define mostrar 10

void printArray(int arr[], char name) {
	std::cout << "Imprimiendo los primeros " << mostrar << " elementos del arreglo " << name << ": ";
	for (int i = 0; i < mostrar; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void generateRandomArray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 10;
	}
}

int main()
{
	srand(time(nullptr));

	int a[N], b[N], c[N];
	int i;

	std::cout << "Generando arreglos aleatorios a y b..." << std::endl;
	generateRandomArray(a, N);
	generateRandomArray(b, N);

	std::cout << "Realizando la suma en paralelo..." << std::endl;

	#pragma omp parallel
	{
		#pragma omp single
		{
			std::cout << "Threads usados: "
					<< omp_get_num_threads() << std::endl;
		}
	}

	#pragma omp parallel for \
	shared(a, b, c) private(i) \
	schedule(static, chunk)

	for (i = 0; i < N; i++) {
		int tid = omp_get_thread_num();
		c[i] = a[i] + b[i];

	// Mostrar evidencia de paralelismo
    if (i % 50 == 0) {
        #pragma omp critical
        {
            std::cout << "i=" << i
                      << " ejecutado por thread "
                      << omp_get_thread_num()
                      << std::endl;
        }}
	}

	printArray(a, 'a');
	printArray(b, 'b');
	printArray(c, 'c');
	return 0;
}



