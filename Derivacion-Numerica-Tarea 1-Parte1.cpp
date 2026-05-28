#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

// Funcion Gaussiana:
// f(t) = e^(-t²)

double f(double t){
    return exp(-t*t);
}

// Derivada exacta:
// f'(t) = -2t e^(-t²)

double exacta(double t){
    return -2.0*t*exp(-t*t);
}

// Metodo Forward Difference

double forward(double t, double h){
    return (f(t+h)-f(t))/h;
}

// Metodo Central Difference

double central(double t, double h){
    return (f(t+h/2.0)-f(t-h/2.0))/h;
}

// Metodo Extrapolado

double extrapolada(double t, double h){

    double dcd_h =
    central(t,h);

    double dcd_h2 =
    central(t,h/2.0);

    return (4.0*dcd_h2-dcd_h)/3.0;
}

// Error absoluto

double error_absoluto(double valor_exacto,
                      double valor_aproximado){

    return abs(valor_exacto-valor_aproximado);
}

int main(){

    // Valores de h

    vector<double> h_valores = {1.0, 0.5, 0.1, 0.05, 0.01, 0.005, 0.001, 0.0005, 0.0001, 0.00001};

    // Valores de t

    vector<double> t_valores;

    double t_inicial = -5.0;
    double t_final = 5.0;

    double paso_t = 0.01;

    for(double t = t_inicial;
        t <= t_final;
        t = t + paso_t){

        t_valores.push_back(t);
    }

    // Archivo 1:
    // derivadas para todos los valores de h y t

    ofstream archivo("datos_derivadas.csv");

    archivo
    << "h,t,exacta,forward,central,"
    << "extrapolada,error_forward,"
    << "error_central,error_extrapolada"
    << endl;

    // Archivo 2:
    // error promedio para cada h

    ofstream archivo_error("errores_vs_h.csv");

    archivo_error
    << "h,error_forward_promedio,"
    << "error_central_promedio,"
    << "error_extrapolada_promedio"
    << endl;

    // Ciclo externo:
    // recorre los valores de h

    for(int j = 0;
        j < h_valores.size();
        j++){

        double h = h_valores[j];

        double suma_error_forward = 0.0;
        double suma_error_central = 0.0;
        double suma_error_extrapolada = 0.0;

        // Ciclo interno:
        // recorre los valores de t

        for(int i = 0;
            i < t_valores.size();
            i++){

            double t = t_valores[i];

            // Derivada exacta

            double d_exacta =
            exacta(t);

            // Aproximaciones numericas

            double d_forward =
            forward(t,h);

            double d_central =
            central(t,h);

            double d_extrapolada =
            extrapolada(t,h);

            // Errores absolutos

            double e_forward =
            error_absoluto(d_exacta,
                           d_forward);

            double e_central =
            error_absoluto(d_exacta,
                           d_central);

            double e_extrapolada =
            error_absoluto(d_exacta,
                           d_extrapolada);

            // Sumamos errores

            suma_error_forward += e_forward;

            suma_error_central += e_central;

            suma_error_extrapolada += e_extrapolada;

            // Guardamos datos

            archivo
            << h << ","
            << t << ","
            << d_exacta << ","
            << d_forward << ","
            << d_central << ","
            << d_extrapolada << ","
            << e_forward << ","
            << e_central << ","
            << e_extrapolada
            << endl;
        }

        // Error promedio

        double error_forward_promedio =
        suma_error_forward /
        t_valores.size();

        double error_central_promedio =
        suma_error_central /
        t_valores.size();

        double error_extrapolada_promedio =
        suma_error_extrapolada /
        t_valores.size();

        // Guardamos errores promedio

        archivo_error
        << h << ","
        << error_forward_promedio << ","
        << error_central_promedio << ","
        << error_extrapolada_promedio
        << endl;
    }

    archivo.close();
    archivo_error.close();

    cout << "Datos guardados correctamente."
         << endl;

    cout << "Archivo 1: datos_derivadas.csv"
         << endl;

    cout << "Archivo 2: errores_vs_h.csv"
         << endl;

    return 0;
}