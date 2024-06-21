#include "Valor.h"
#include <iostream>
#include <string>
#include <cmath>  

using namespace std;

int main(){
    string palabra;

    cout << "Ingrese una palabra, una frase o comentarios: \n";
    cin >> palabra;
    Valor<string> nombre(palabra);
    cout << "Contenido: " << nombre.getValue() << endl;

    Valor<double> PI(M_PI);
    cout << "\nEl valor de PI es: " << PI.getValue() << endl;

    return 0;
}
