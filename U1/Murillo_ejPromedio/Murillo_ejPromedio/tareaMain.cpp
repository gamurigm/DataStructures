#include <iostream>
#include "Promedio.h"
#include "Estudiante.h"

using namespace std;

Estudiante* ingresarDatos(int& n);

int main() {
	
    int n;
    Estudiante* estudiantes = ingresarDatos(n);
    Promedio<Estudiante> promedio;
    promedio.mostrarPromedios(estudiantes, n);

    delete[] estudiantes;

    return 0;
}

Estudiante* ingresarDatos(int& n) {
	 
	do{
		cout << "Ingrese una cantidad de estudiantes (Entera): ";
        cin >> n;
	}while(n < 0);
    

    Estudiante* estudiantes = new Estudiante[n];

    for (int i = 0; i < n; ++i) {
        
		string nombre;
        int nivel;
        double nota1, nota2, nota3;
        cin.ignore();
        
        cout << "\nIngrese el nombre del estudiante " << i+1 << ": ";
        getline(cin, nombre);
        cout << "Ingrese el nivel del estudiante " << i+1 << ": ";
        cin >> nivel;

        do {
            cout << "Ingrese la nota 1:" << i+1 << ": ";
            cin >> nota1;
            if (nota1 < 0 || nota1 > 10) {
                cout << "La nota debe estar entre 0 y 10!" << endl;
            }
        } while (nota1 < 0 || nota1 > 10);

        do {
            cout << "Ingrese la nota 2:" << i+1 << ": ";
            cin >> nota2;
            if (nota2 < 0 || nota2 > 10) {
                cout << "La nota debe estar entre 0 y 10!" << endl;
            }
        } while (nota2 < 0 || nota2 > 10);

        do {
            cout << "Ingrese la nota 3: " << i+1 << ": ";
            cin >> nota3;
            if (nota3 < 0 || nota3 > 10) {
                cout << "La nota debe estar entre 0 y 10!" << endl;
            }
        } while (nota3 < 0 || nota3 > 10);

        estudiantes[i].nombre = nombre;
        estudiantes[i].nivel = nivel;
        estudiantes[i].nota1 = nota1;
        estudiantes[i].nota2 = nota2;
        estudiantes[i].nota3 = nota3;
    }
    
    return estudiantes;
}
