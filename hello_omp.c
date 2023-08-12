#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int num_threads = 10; // Valor default

    if (argc > 1) {
        num_threads = atoi(argv[1]);
    }

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        printf("Hello from thread %d of %d!\n", thread_num, num_threads);
    }

    return 0;
}
