#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

// Funcion original: f(t) = cos(t)
double f(double t){
    return cos(t);
}

// Segunda derivada exacta: f''(t) = -cos(t)
double exacta(double t){
    return -cos(t);
}

// Segunda derivada numerica central
double segunda_derivada(double t, double h){
    return (f(t+h) - 2.0*f(t) + f(t-h))/(h*h);
}

// Error absoluto
double error_absoluto(double valor_exacto, double valor_aproximado){
    return abs(valor_exacto - valor_aproximado);
}

int main(){

    vector<double> h_valores = {1.0, 0.5, 0.1, 0.05, 0.01, 0.005, 0.001, 0.0005, 0.0001, 0.00001};

    vector<double> t_valores;

    double t_inicial = 0.0;
    double t_final = 10.0;
    double paso_t = 0.01;

    for(double t = t_inicial; t <= t_final; t = t + paso_t){
        t_valores.push_back(t);
    }

    ofstream archivo("datos_segunda_derivada.csv");

    archivo << "h,t,exacta,segunda_derivada,error" << endl;

    ofstream archivo_error("errores_vs_h_segunda.csv");

    archivo_error << "h,error_promedio" << endl;

    for(int j = 0; j < h_valores.size(); j++){

        double h = h_valores[j];
        double suma_error = 0.0;

        for(int i = 0; i < t_valores.size(); i++){

            double t = t_valores[i];

            double d_exacta = exacta(t);
            double d_numerica = segunda_derivada(t,h);

            double error = error_absoluto(d_exacta,d_numerica);

            suma_error += error;

            archivo << h << ","
                    << t << ","
                    << d_exacta << ","
                    << d_numerica << ","
                    << error
                    << endl;
        }

        double error_promedio = suma_error / t_valores.size();

        archivo_error << h << ","
                      << error_promedio
                      << endl;
    }

    archivo.close();
    archivo_error.close();

    cout << "Datos guardados correctamente." << endl;
    cout << "Archivo 1: datos_segunda_derivada.csv" << endl;
    cout << "Archivo 2: errores_vs_h_segunda.csv" << endl;

    return 0;
}