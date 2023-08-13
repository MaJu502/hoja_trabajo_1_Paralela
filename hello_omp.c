#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

// Marco Jurado 20308


int main(int argc, char *argv[]) {
    // Definimos una variable para los threads que se desean correr.
    int num_threads = 10;

    if (argc > 1) {
        num_threads = atoi(argv[1]); // Si tiene input se pone como los numeros de threads que quieren correr.
    }

    // Paralelizar es una fiesta
    #pragma omp parallel num_threads(num_threads)
    {
        int thread_num = omp_get_thread_num(); // numero del hilo
        int num_threads = omp_get_num_threads(); // cuantos hilos van en total
        printf("Hello from thread %d of %d!\n", thread_num, num_threads); // mensaje
    }

    return 0;
}