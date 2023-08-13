// Planteamiento: 
// Se hace uso del arreglo en lugar del ejercicio anterior.

// Marco Jurado 20308

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

// Funciones solicitadas en ejercicio
double fun_cuadrada(double x) {
    return x * x;
}

double fun_cubo(double x) {
    return 2 * pow(x, 3);
}

double fun_seno(double x) {
    return sin(x);
}

double *partial_results; // Arreglo global para almacenar los resultados parciales de cada hilo

void trapezoide(int tipo, double a, double b, int n, int threads) {
    double (*f)(double); // Declaración de un puntero a función
    switch (tipo) {
        case 1:
            f = fun_cuadrada;
            break;
        case 2:
            f = fun_cubo;
            break;
        case 3:
            f = fun_seno;
            break;
        default:
            printf("Tipo de función inválido.\n");
            return;
    }
    double h = (b - a) / n;

    partial_results = (double *)malloc(threads * sizeof(double)); // Reservar espacio para el arreglo global

    // Paralelizar
    #pragma omp parallel num_threads(threads)
    {
        int thread_num = omp_get_thread_num();
        double A_threaded = a + thread_num * (n / threads) * h;
        double B_threaded = A_threaded + (n / threads) * h;
        double pool_threads = (f(A_threaded) + f(B_threaded)) / 2.0;

        for (int i = 1; i < (n / threads); i++) {
            double x = A_threaded + i * h;
            pool_threads += f(x);
        }

        pool_threads *= h;

        partial_results[thread_num] = pool_threads; // Almacenar el resultado parcial en el arreglo global
    }

    double resultado = 0.0;
    for (int i = 0; i < threads; i++) {
        resultado += partial_results[i]; // Sumar los resultados parciales para obtener el resultado final
    }

    printf("Resultado de la integral \n     con n = %d trapezoides, nuestra aproximacion de la integral de (%f, %f) es %f\n", n, a, b, resultado);

    free(partial_results); // Liberar la memoria del arreglo global
}

int main(int argc, char* argv[]) {
        if (argc <= 3) {
        printf(" >> ERROR: input de parametros no estan correctos");
        return 1;
    }

    // parametros a operar
    double a = atof(argv[1]);
    double b = atof(argv[2]);

    // numero de intervalos
    int n = 1000000; 
    
    // parametros nuevos
    int threads = atoi(argv[3]); // se agrego cantidad de threads del ejercicio anterior.
    
    // verificacion que se pueda computar en el algoritmo la cantidad de threads
    if (n % threads) {
        printf(" >> ERROR: la cantidad de trapezoides (10e6) tiene que ser multiplo de threads que ingreses.");
        return 1;
    }

    trapezoide(1, a, b, n, threads);
    trapezoide(2, a, b, n, threads);
    trapezoide(3, a, b, n, threads);

    return 0;
}
