#include <iostream>
#include "Cola.h"

int main() {
    Cola<int> miCola;

    bool resp;
    int valor;

    miCola.encolar(10, resp);
    if (resp) {
        std::cout << "Elemento encolado correctamente." << std::endl;
    }

    miCola.encolar(20, resp);
    if (resp) {
        std::cout << "Elemento encolado correctamente." << std::endl;
    }

    size_t tamanio = miCola.devolverTamanio();
    std::cout << "Cantidad de elementos en la cola: " << tamanio << std::endl;

    return 0;
}
