#include <iostream>
#include <ctime>
#include <iomanip>
#include "Cola.h"      
#include "Cliente.h"   
#include "ManejoJSON.h"

void simularTransacciones(Cola<Cliente>& colaTransacciones, double& balanceTotal, double& totalTransacciones);

int main() {
    
    Cola<Cliente> colaTransacciones;
    
    double balanceTotal = 100000;    // Balance inicial
    double totalTransacciones = 0.0; 

    cargarTransacciones(colaTransacciones);    
    simularTransacciones(colaTransacciones, balanceTotal, totalTransacciones);
    
    colaTransacciones.mostrar();
    std::cout << "\nTotal Tansacciones: $" << std::fixed << std::setprecision(2) << totalTransacciones << std::endl;
    std::cout << "Balance total en el banco: $" << std::fixed << std::setprecision(2) << balanceTotal << std::endl;

    return 0;
}

void simularTransacciones(Cola<Cliente>& colaTransacciones, double& balanceTotal, double& totalTransacciones) {
    
    std::cout << "Balance Inicial: $" << balanceTotal << std::endl;
    
    srand(time(0)); 

    for (int i = 0; i < 10; ++i) {
        
        bool resp;
        bool esDeposito = rand() % 2 == 0; 

        std::string nombre = "Cliente " + std::to_string(i + 1);
        std::string numeroCuenta = "Cuenta-" + std::to_string(rand() % 1000);
        double cantidad = (rand() % 1000); 

        Cliente cliente(nombre, numeroCuenta, esDeposito, cantidad);

        if (cliente.esDeposito) {
            balanceTotal += cliente.monto;
            totalTransacciones += cliente.monto; 
        } else {
            balanceTotal -= cliente.monto;
            totalTransacciones -= cliente.monto; 
        }


        guardarTransaccion(cliente, i + 1);

        colaTransacciones.encolar(cliente, resp);
        if (resp) {
            std::cout << "Transacción encolada:";
            std::cout << "| Nombre: " << cliente.nombre <<  "    | # Cuenta: " << cliente.numeroCuenta
                      << ", Tipo: " << (cliente.esDeposito ? "Deposito" : "Retiro")
                      << ", Monto: $" << std::fixed << std::setprecision(2) << cliente.monto << std::endl;
        } else {
            std::cout << "Cola llena! No se pudo realizar la transacción." << std::endl;
        }
    }
}
