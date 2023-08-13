#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

// Marco Jurado 20308

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf(" >> ERROR: input de parametros no estan correctos");
        return 1;
    }
    // Definimos una variable para los threads que se desean correr.
    int num_threads = 10;

    if (argc > 1) {
        num_threads = atoi(argv[1]); // Si tiene input se pone como los numeros de threads que quieren correr.
    }

    // Paralelizar es una fiesta
    #pragma omp parallel num_threads(num_threads)
    {
        int thread_num = omp_get_thread_num(); // Numero de hilo actual
        
        if (thread_num % 2 == 0) { // Si el número de hilo es par
            printf("Saludos del hilo %d\n", thread_num);
        } else { // Si el número de hilo es impar
            printf("Feliz cumpleaños número %d!\n", num_threads);
        }

    }

    // Great succes
    return 0;
}