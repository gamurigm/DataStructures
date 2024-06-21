#include <iostream>
#include <stdexcept>
#include "Cola.h"    

int main() {
    Cola<int> cola_enteros;

    bool ok = false;
    bool resp;
    size_t N;
    int X;

    cola_enteros.Crear_cola(ok);
    std::cout << "" << (resp ? "Sí" : "No") << std::endl;

    cola_enteros.Queue(10, ok);
    cola_enteros.Queue(20, ok);
    cola_enteros.Queue(30, ok);

    cola_enteros.Tamanio(N);
    std::cout << "Cardinalidad: " << N << std::endl;

    try {
        cola_enteros.Dequeue(X, ok);
        std::cout << "Elemento desencolado: " << X << ". Nuevo frente: " << cola_enteros.frente() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    cola_enteros.Borrar_cola(ok);
    std::cout << (cola_enteros.estaVacia() ? "Cola Limpia" : "Llena con almenos un elemento") << std::endl;

    return 0;
}
