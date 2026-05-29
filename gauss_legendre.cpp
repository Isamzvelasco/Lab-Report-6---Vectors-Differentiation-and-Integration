#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;


// Definimos los parametros Generales

// Definimos el intervalo de integracion [a, b]
const double a = 0.0;
const double b = 3.0;

// Numero de puntos de Gauss-Legendre
const int N = 4;

// Funcion a integrar: f(x) = e^(-x^2)
double f(double x) {
    return exp(-pow(x, 2));
}

// 1. Integración por metodo de Gauss-Legendre

double gaussLegendre() {

    // Nodos de Gauss-Legendre para N = 4 (Segun la tabla)
    vector<double> ti = {
        -0.8611363115940526,
        -0.3399810435848563,
         0.3399810435848563,
         0.8611363115940526
    };

    // Pesos de Gauss-Legendre para N = 4
    vector<double> wi = {
        0.3478548451374538,
        0.6521451548625461,
        0.6521451548625461,
        0.3478548451374538
    };

    // Inicializamos la suma
    double suma = 0.0;

    for (int i = 0; i < N; i++) {

        // Transformamos el nodo ti del intervalo [-1, 1] al intervalo [a, b]
        double x = ((b - a) / 2.0) * ti[i] + (a + b) / 2.0;

        // Sumamos wi * f(xi)
        suma += wi[i] * f(x);
    }

    // Multiplicamos por el factor de cambio de intervalo
    return ((b - a) / 2.0) * suma;
}



// 2. Integracion por metodo del punto medio


double punto_medio(int n) {

    // Calculamos el ancho de cada rectangulo
    double h = (b - a) / n;

    // Inicializamos la suma
    double suma = 0.0;

    for (int i = 0; i < n; i++) {

        // Calculamos el punto medio del rectangulo i
        double x_medio = a + (i + 0.5) * h;

        // Sumamos el valor de la funcion en el punto medio
        suma += f(x_medio);
    }

    // Multiplicamos la suma por h para obtener el area aproximada
    return h * suma;
}



int main() {

    cout << fixed << setprecision(10);

    // Calculamos el valor exacto de la integral para comparar los resultados
    // Integral exacta de e^(-x^2) evaluada entre 0 y 3
    double valor_exacto = (sqrt(M_PI) / 2.0) * (erf(b) - erf(a));


    // Para el punto 1: Calculamos la integral con Gauss-Legendre
    double integral_GL = gaussLegendre();

    // Calculamos el error absoluto
    double error_GL = abs(integral_GL - valor_exacto);

    // Mostramos resultados de Gauss-Legendre
    cout << "1. Metodo de Gauss-Legendre" << endl;
    cout << "Integral Gauss-Legendre: " << integral_GL << endl;
    cout << "Valor exacto: " << valor_exacto << endl;
    cout << "Error absoluto: " << error_GL << endl;
    cout << endl;



    //Para el punto 2: Calculamos la integral con el metodo del punto medio
    // Definimos la precision minima deseada
    double precision_min = 1e-6;

    // Empezamos con 1 rectangulo
    int rectangulos = 1;

    // Variables para guardar resultados
double integral_PM = 0.0;
double error_PM = 0.0;

// Creamos archivo CSV para graficar depsues
ofstream archivo("resultados_punto_medio.csv");

archivo << "n,h,integral_punto_medio,error_punto_medio" << endl;

// Repetimos hasta que el error sea menor que la precision minima
do {

    // Calculamos la integral usando n rectangulos
    integral_PM = punto_medio(rectangulos);

    // Calculamos el error absoluto
    error_PM = abs(integral_PM - valor_exacto);

    // Calculamos el ancho de cada rectangulo
    double h = (b - a) / rectangulos;

    // Guardamos los datos para graficar h vs error
    archivo << rectangulos << ","
            << h << ","
            << integral_PM << ","
            << error_PM << endl;

    // Aumentamos el numero de rectangulos
    rectangulos++;

} while (error_PM > precision_min);

archivo.close();


    // Mostramos resultados del metodo del punto medio
    cout << "2. Metodo del Punto Medio" << endl;
    cout << "Precision minima requerida: " << precision_min << endl;
    cout << "Numero de rectangulos necesarios: " << rectangulos - 1 << endl;
    cout << "Integral punto medio: " << integral_PM << endl;
    cout << "Valor exacto: " << valor_exacto << endl;
    cout << "Error absoluto: " << error_PM << endl;
    cout << endl;



    // Archivos para los grficos
    cout << "3. Archivo para graficos" << endl;
    cout << "Archivo punto medio: resultados_punto_medio.csv" << endl;

    return 0;
}
