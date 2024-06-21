#include <iostream>

class Estudiante{
	
	public:
		Estudiante(){};
		Estudiante(std::string nombre, int n, double n1, double n2, double n3 ) : 
		nombre(nombre), nivel(n), nota1(n1), nota2(n2), nota3(n3) {} ;
	public:
	    std::string nombre;
	    int nivel;
	    double nota1;
	    double nota2;
	    double nota3;	
};