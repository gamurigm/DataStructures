#include <iostream>
#include <ctime>
#include <iomanip>
#include "Cola.h" 

struct Cliente;
std::ostream& operator<<(std::ostream& os, const Cliente& cliente);
void simularTransacciones(Cola<Cliente>& colaTransacciones, double& balanceTotal, double& totalTransacciones);


int main() {
    
	Cola<Cliente> colaTransacciones;
	
    double balanceTotal = 100000;    //Balance
    double totalTransacciones = 0.0; 

    simularTransacciones(colaTransacciones, balanceTotal, totalTransacciones);
    
	colaTransacciones.mostrar();
    std::cout << "\nTotal Tansacciones: $" << std::fixed << std::setprecision(2) << totalTransacciones << std::endl;
    std::cout << "Balance total en el banco: $" << std::fixed << std::setprecision(2) << balanceTotal << std::endl;

    return 0;
}



struct Cliente {
    std::string nombre;
    std::string numeroCuenta;
    bool esDeposito;
    double monto;

    Cliente() : nombre(""), numeroCuenta(""), esDeposito(true), monto(0.0) {}

    Cliente(const std::string& nombre, const std::string& numeroCuenta, bool esDeposito, double monto)
        : nombre(nombre), numeroCuenta(numeroCuenta), esDeposito(esDeposito), monto(monto) {}
};

std::ostream& operator<<(std::ostream& os, const Cliente& cliente) {
    os << "        Nombre: " << cliente.nombre << ", Número de cuenta: " << cliente.numeroCuenta
       << ", Tipo: " << (cliente.esDeposito ? "Depósito" : "Retiro")
       << ", Monto: $" << std::fixed << std::setprecision(2);
    
    if (!cliente.esDeposito) {
        os << "(" << cliente.monto << ")";
    } else {
        os << cliente.monto;
    }
    
    os << std::endl;
    
    return os;
}

void simularTransacciones(Cola<Cliente>& colaTransacciones, double& balanceTotal, double& totalTransacciones) {
    
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

        colaTransacciones.encolar(cliente, resp);
        if (resp) {
            std::cout << "Transacción encolada: ";
            std::cout << "| Nombre: " << cliente.nombre <<  "    | Número de cuenta: " << cliente.numeroCuenta
                      << ", Tipo: " << (cliente.esDeposito ? "Depósito" : "Retiro")
                      << ", Monto: $" << std::fixed << std::setprecision(2) << cliente.monto << std::endl;
        } else {
            std::cout << "Cola llena. No se pudo realizar la transacción." << std::endl;
        }
    }
}
