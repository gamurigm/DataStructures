#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
#include <iomanip>

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
    os << std::left << std::setw(20) << cliente.nombre
       << std::left << std::setw(20) << cliente.numeroCuenta
       << std::left << std::setw(10) << (cliente.esDeposito ? "Deposito" : "Retiro")
       << std::right << std::setw(10) << std::fixed << std::setprecision(2);
    
    if (!cliente.esDeposito) {
        os << "(" << cliente.monto << ")";
    } else {
        os << cliente.monto;
    }
    
    os << std::endl;
    
    return os;
}

#endif // CLIENTE_H
