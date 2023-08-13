// Planteamiento: 
// Para dicho programa se usara paralelismo para calulcar cada valor de 
// la integral y luego se sumaran para obtener el resultado.

// Marco Jurado 20308

#include <stdio.h>
#include <string.h>
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

// Funcion trapezoide para riemann
double trapezoide(int tipo, double a, double b, int n) {
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
    double integral = (f(a) + f(b)) / 2.0; // Los puntos extremos se dividen por 2

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        integral += f(x); // Los puntos interiores se suman completamente
    }

    integral *= h;
    return integral;
}


int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf(" >> ERROR: input de parametros no estan correctos");
        return 1;
    }

    // parametros de dos numeros a operar
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    
    // numero de intervalos
    int n = 1000000; 

    // Resultados de operaciones 
    double resultado_cuadrado = trapezoide(1, a, b, n);
    double resultado_cubo = trapezoide(2, a, b, n);
    double resultado_seno = trapezoide(3, a, b, n);

    printf(" >> Resultado de integral con cuadrado \n     con n = %d trapezoides, nuestra aproximacion de la integral de (%f, %f) es %f\n", n, a, b, resultado_cuadrado);
    printf(" >> Resultado de integral con cubo \n     con n = %d trapezoides, nuestra aproximacion de la integral de (%f, %f) es %f\n", n, a, b, resultado_cubo);
    printf(" >> Resultado de integral con seno \n     con n = %d trapezoides, nuestra aproximacion de la integral de (%f, %f) es %f\n", n, a, b, resultado_seno);

    return 0;
}