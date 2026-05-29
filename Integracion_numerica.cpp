#include <iostream>
#include <cmath>
#include <fstream>
#include <vector> // Necesario para usar arreglos dinámicos
using namespace std ;

double f_x(double x) {
    return exp(-pow(x, 2)); // Función a integrar (Gaussiana)
}

// Función que integra por el método de cajas
double cajas(double x, double h) {

    // Declaramos un vector que tendrá los valores de la función
    vector<double> f_n;
    int n = f_n.size() - 1; //número de intérvalos 

    // vamos agregando cada valor de la función que vamos a usar (limites de los intervalos de las cajas)
    for (double i = 0 ; i < x; i += h) {
        f_n.push_back(f_x(i));
        n += 1;
    }

    double integral = 0; // Valor de la integral, las áreas de las cajas se iran sumando poco a poco

    for (int k = 0; k <= n; k++) {
        integral += f_n[k] * h;
    }

    return integral;
}

// Función que integra por método de trapezoides
double trapezoid(double x, double h) {
        // Declaramos un vector que tendrá los valores de la función
    vector<double> f_n;
    
    // vamos agregando cada valor de la función que vamos a usar (limites de los intervalos)
    for (double i = 0 ; i <= x; i += h) {
        f_n.push_back(f_x(i));
    }

    int n = f_n.size() - 1; //número de intérvalos 

    double sumatoria = 0; // Sumamos los terminos con sus respectivos coeficientes
    
    for (int k = 0; k <= n; k++) {
        
        if (k == 0) {
            sumatoria += f_n[k];
        }
        else if (k == n) {
            sumatoria += f_n[k];
        }
        else {
            sumatoria += 2 * f_n[k];
        }
            
        }
    
    double integral = (h/2) * sumatoria; //definimos la integral

    return integral;
}

//Función que integra por método Simpson
double simpson(double x, double h) {

    // Declaramos un vector que tendrá los valores de la función
    vector<double> f_n;

    // vamos agregando cada valor de la función que vamos a usar (limites de los intervalos)
    for (double i = 0 ; i < x; i += h) {
        f_n.push_back(f_x(i));
    }

    int n = f_n.size() - 1; //número de intérvalos 

    double sumatoria = 0; // Sumamos los terminos con sus respectivos coeficientes
    

    for (int k = 0; k <= n; k++) {
        
        if (k == 0){
            sumatoria += f_n[k];
        }
        else if (k == n){
            sumatoria += f_n[k];
        }
        else if ((k % 2) == 0){
            sumatoria += 2 * f_n[k];
        }
        else {
            sumatoria += 4 * f_n[k];
        }
    }
    
    double integral = (h/3) * sumatoria; //definimos la integral

    return integral;
}

//Valor teórico de la integral con limite inferior igual a cero
double teorico(double x) {
    double pi = acos(-1.0);
    return (sqrt(pi) / 2.0) * (erf(x));
}

int main() {
    // definimos un único valor de h para probar los métodos

    float h = 0.0001;

    // definimos unos valores de x para integrar

    vector<double> X;

    double x = 0; // valor inicial de X

    while (x <= 3) {
        X.push_back(x);
        x += 0.002; // vamos sumando de 0.002 ( X tiene que ser multiplo de h por dos para que los intervalos sean pares)
    }

    //creamos las listas con los valores para cada método de integración y el valor teórico

    vector<double> CAJAS;
    vector<double> TRAPECIOS;
    vector<double> SIMPSON;
    vector<double> TEORICO;

    for (int k = 0; k <= (X.size() -1); k++){
        CAJAS.push_back(cajas(X[k], h));
        TRAPECIOS.push_back(trapezoid(X[k], h));
        SIMPSON.push_back(simpson(X[k], h));
        TEORICO.push_back(teorico(X[k]));
    }

    //creamos y abrimos un archivo csv para graficar las integrales en python

    ofstream integralesCSV("integrales.csv");

    //es buena práctica verificar si el archivo se abrió correctamente
    if (!integralesCSV.is_open()) {
        cerr << "Error al abrir o crear el archivo." << endl;
        return 1;
    }

    //escribimos los encabezados de las columnas (separados por comas)
    integralesCSV << "X,Teorico, Cajas, Trapecios, Simpson\n";

    //vamos agregando
    for (int k = 0; k <= (X.size() -1); k++) {
        integralesCSV << X[k] << "," << TEORICO[k] << ","<< CAJAS[k] << "," << TRAPECIOS[k] << "," << SIMPSON[k] << "\n";
    }

    //cerramos el archivo al terminar
    integralesCSV.close();

    cout << "¡Datos guardados exitosamente en 'integrales.csv'!\n";


    //creamos y abrimos un archivo csv guardando los errores para luego graficar en python

    ofstream erroresCSV("errores_integracion.csv");

    //es buena práctica verificar si el archivo se abrió correctamente
    if (!erroresCSV.is_open()) {
        cerr << "Error al abrir o crear el archivo." << endl;
        return 1;
    }

    //escribimos los encabezados de las columnas (separados por comas)
    erroresCSV << "X,Error_Cajas,Error_Trapecios,Error_Simpson\n";

    //vamos agregando error por error
    for (int k = 0; k <= (X.size() -1); k++) {
        erroresCSV << X[k] << "," << abs(TEORICO[k]-CAJAS[k]) << "," << abs(TEORICO[k]-TRAPECIOS[k]) << "," << abs(TEORICO[k]-SIMPSON[k]) << "\n";
    }

    //cerramos el archivo al terminar
    erroresCSV.close();

    cout << "¡Datos guardados exitosamente en 'errores_integracion.csv'!\n";

    //para un x = 2 y 10 valores de h graficamos error vs h

    int x_0 = 2;

    vector<float> H = {0.00001, 0.00002, 0.00005, 0.0001, 0.0002, 0.0005, 0.001, 0.002, 0.005, 0.01};

    vector<double> CAJAS_H;
    vector<double> TRAPECIOS_H;
    vector<double> SIMPSON_H;

    for (int k = 0; k <= (H.size() -1); k++){
        CAJAS_H.push_back(teorico(x_0) - cajas(x_0, H[k]));
        TRAPECIOS_H.push_back(teorico(x_0) - trapezoid(x_0, H[k]));
        SIMPSON_H.push_back(teorico(x_0) - simpson(x_0, H[k]));
    }

    ofstream errores_HCSV("errores_H_integracion.csv");

    //es buena práctica verificar si el archivo se abrió correctamente
    if (!errores_HCSV.is_open()) {
        cerr << "Error al abrir o crear el archivo." << endl;
        return 1;
    }

    //escribimos los encabezados de las columnas (separados por comas)
    errores_HCSV << "H,Error_Cajas,Error_Trapecios,Error_Simpson\n";

    //vamos agregando error por error
    for (int k = 0; k <= (H.size() -1); k++) {
        errores_HCSV << H[k] << "," << abs(CAJAS_H[k]) << "," << abs(TRAPECIOS_H[k]) << "," << abs(SIMPSON_H[k]) << "\n";
    }

    //cerramos el archivo al terminar
    errores_HCSV.close();

    cout << "¡Datos guardados exitosamente en 'errores_H_integracion.csv'!\n";


    return 0;
}