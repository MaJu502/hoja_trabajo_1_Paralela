// Planteamiento: 
// Igual al anterior pero cambio el main para poder parametrizarlo y manualmente cambiar la funcion

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
            return 0.0;
    }
    double h = (b - a) / n;

    // aqui cambia pues la integral va a estar declarada y le vamos pool_threadsando con los threads
    double resultado = 0.0;

    // Paralelizar es una fiesta
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

        // Sector critico entonces se debe de mencionar omp critical para evitar problemas en la suma de los threads
        #pragma omp critical
        resultado += pool_threads; // se suma
    }

    printf("Resultado de la integral \n     con n = %d trapezoides, nuestra aproximacion de la integral de (%f, %f) es %f\n", n, a, b, resultado);
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

    return 0;
}
