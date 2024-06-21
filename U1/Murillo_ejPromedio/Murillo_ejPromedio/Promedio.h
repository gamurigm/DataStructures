#ifndef PROMEDIO_H
#define PROMEDIO_H
#include <iostream>

class Estudiante;

template <typename E>
class Promedio {
public:
    
    double calcularPromedio(const E& estudiante) const {
        double promedio = (estudiante.nota1 + estudiante.nota2 + estudiante.nota3) / 3;	
        return promedio;
    }
    
    void mostrarPromedios(const E* estudiantes, int n) const {
        for (int i = 0; i < n; ++i) {
        	std::cout << "\n";
            std::cout << "Estudiante " << i+1 << ": " << estudiantes[i].nombre<< std::endl;
            std::cout << "Promedio: " << calcularPromedio(estudiantes[i]) << std::endl;
            std::cout << "Mensaje: " << ((calcularPromedio(estudiantes[i]) >=7 ) ? "Aprobado \n" : "Reprobado \n");
        }
    }

private:
    E* Estudiantes;    
};

#endif 