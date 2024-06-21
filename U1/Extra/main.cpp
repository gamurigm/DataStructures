#include <iostream>
#include <stdexcept>
#include "Cola.h"    

int main() {
    
    Cola<int> cola_enteros;

    cola_enteros.encolar(10);
    cola_enteros.encolar(20);
    cola_enteros.encolar(30);
    cola_enteros.encolar(3);
	cola_enteros.encolar(0);
	cola_enteros.encolar(5);
	cola_enteros.encolar(7);
	cola_enteros.encolar(80);


    std::cout << " Cardinalidad:  " << cola_enteros.devolverTamanio() << std::endl;

    int frente = cola_enteros.frente();
    std::cout << "Frente de la cola: " << frente << std::endl;
  
    cola_enteros.desencolar();
    cola_enteros.desencolar();
    cola_enteros.desencolar();
    cola_enteros.desencolar();
    cola_enteros.desencolar();
    cola_enteros.devolverTamanio();
    
    std::cout << "Elemento desencolado. Nuevo frente: " << cola_enteros.frente() << std::endl;



    return 0;
}
