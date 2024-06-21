#include <iostream>
#include <stdexcept>
#include "Cola.h"    

int main() {
    Cola<int> cola_enteros;

    bool ok = false;
    bool resp;
    size_t N;
    int X;

    // Crear la cola
    cola_enteros.Crear_cola(ok);
    std::cout << "Cola creada. ¿Está vacía? " << (resp ? "Sí" : "No") << std::endl;

    // Encolar valores
    cola_enteros.Queue(10, ok);
    cola_enteros.Queue(20, ok);
    cola_enteros.Queue(30, ok);

    // Mostrar el tamaño de la cola
    cola_enteros.Tamanio(N);
    std::cout << "Tamaño de la cola: " << N << std::endl;

    // Mostrar el frente de la cola
    try {
        cola_enteros.Dequeue(X, ok);
        std::cout << "Elemento desencolado: " << X << ". Nuevo frente: " << cola_enteros.frente() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    // Limpiar la cola
    cola_enteros.Borrar_cola(ok);
    std::cout << "Cola limpiada. ¿Está vacía? " << (cola_enteros.estaVacia() ? "Sí" : "No") << std::endl;

    return 0;
}
