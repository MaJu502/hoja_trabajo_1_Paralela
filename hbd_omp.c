#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <edad>\n", argv[0]);
        return 1;
    }

    int edad = atoi(argv[1]);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        if (thread_id % 2 == 0) {
            printf("Saludos del hilo %d\n", thread_id);
        } else {
            printf("Feliz cumpleaños número %d!\n", num_threads);
        }
    }

    return 0;
}
