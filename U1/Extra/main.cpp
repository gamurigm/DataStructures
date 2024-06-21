#include <iostream>
#include <ctime>
#include <iomanip>
#include "Cola.h"
#include "Cliente.h"
#include "ManejoJSON.h"


void simularTransacciones(Cola<Cliente>& colaTransacciones, double& balanceTotal, double& totalTransacciones);
void ingresarTransaccionManualmente(Cola<Cliente>& colaTransacciones, double& balanceTotal, double& totalTransacciones);
void mostrarTransacciones(Cola<Cliente>& colaTransacciones);
void mostrarTotales(double balanceTotal, double totalTransacciones);

int main() {
    Cola<Cliente> colaTransacciones;
    double balanceTotal = 100000;    // Balance inicial
    double totalTransacciones = 0.0;

    cargarTransacciones(colaTransacciones);
    cargarBalanceDesdeJSON(balanceTotal, totalTransacciones); // Cargar el balance desde JSON

    int opcion;

    do {
        std::cout << "\n--- MENU ---" << std::endl;
        std::cout << "1. Simular transacciones autom�ticamente" << std::endl;
        std::cout << "2. Ingresar transacci�n manualmente" << std::endl;
        std::cout << "3. Mostrar transacciones en cola y tama�o actual" << std::endl;
        std::cout << "4. Procesar transacci�n de la cola" << std::endl;
        std::cout << "5. Mostrar balance y total de transacciones" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Ingrese su opci�n: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                simularTransacciones(colaTransacciones, balanceTotal, totalTransacciones);
                break;
            case 2:
                ingresarTransaccionManualmente(colaTransacciones, balanceTotal, totalTransacciones);
                break;
            case 3:
                mostrarTransacciones(colaTransacciones);
                break;
            case 4:
                if (!colaTransacciones.estaVacia()) {
                    Cliente cliente;
                    bool resp;
                    colaTransacciones.desencolar(cliente, resp);
                    if (resp) {
                        std::cout << "Transacci�n desencolada:";
                        std::cout << "| Nombre: " << cliente.nombre << "    | # Cuenta: " << cliente.numeroCuenta
                                  << ", Tipo: " << (cliente.esDeposito ? "Dep�sito" : "Retiro")
                                  << ", Monto: $" << std::fixed << std::setprecision(2) << cliente.monto << std::endl;

                        if (cliente.esDeposito) {
                            balanceTotal += cliente.monto;
                            totalTransacciones += cliente.monto;
                        } else {
                            if (balanceTotal >= cliente.monto) {
                                balanceTotal -= cliente.monto;
                                totalTransacciones -= cliente.monto;
                            } else {
                                std::cout << "No hay suficiente saldo para el retiro de $" << cliente.monto << std::endl;
                                // Volver a encolar la transacci�n si no se puede procesar
                                colaTransacciones.encolar(cliente, resp);
                            }
                        }

                        // Guardar balance y transacciones en JSON despu�s de procesar
                        guardarBalanceEnJSON(balanceTotal, totalTransacciones);
                    } else {
                        std::cout << "Error al desencolar la transacci�n." << std::endl;
                    }
                } else {
                    std::cout << "La cola de transacciones est� vac�a." << std::endl;
                }
                break;
            case 5:
                mostrarTotales(balanceTotal, totalTransacciones);
                break;
            case 0:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opci�n invalida. Intente de nuevo." << std::endl;
                break;
        }

    } while (opcion != 0);

    std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balanceTotal << std::endl;
    std::cout << "\nTotal Transacciones: $" << std::fixed << std::setprecision(2) << totalTransacciones << std::endl;

    return 0;
}

void simularTransacciones(Cola<Cliente>& colaTransacciones, double& balanceTotal, double& totalTransacciones) {
    std::cout << "Simulando transacciones autom�ticamente..." << std::endl;
    std::cout << "Balance Inicial: $" << balanceTotal << std::endl;

    srand(time(0));

    for (int i = 0; i < 10; ++i) {
        bool resp;
        bool esDeposito = rand() % 2 == 0;

        std::string nombre = "Cliente " + std::to_string(i + 1);
        std::string numeroCuenta = "Cuenta-" + std::to_string(rand() % 1000);
        double cantidad = (rand() % 1000) + 1; // Ajuste para evitar montos de 0

        Cliente cliente(nombre, numeroCuenta, esDeposito, cantidad);

        if (cliente.esDeposito) {
            balanceTotal += cliente.monto;
            totalTransacciones += cliente.monto;
        } else {
            if (balanceTotal >= cliente.monto) {
                balanceTotal -= cliente.monto;
                totalTransacciones -= cliente.monto;
            } else {
                std::cout << "No hay suficiente saldo para el retiro de $" << cliente.monto << std::endl;
                continue; // Saltar esta transacci�n
            }
        }

        guardarTransaccion(cliente, i + 1);

        colaTransacciones.encolar(cliente, resp);
        if (resp) {
            std::cout << "Transacci�n encolada:";
            std::cout << "| Nombre: " << cliente.nombre << "    | # Cuenta: " << cliente.numeroCuenta
                      << ", Tipo: " << (cliente.esDeposito ? "Dep�sito" : "Retiro")
                      << ", Monto: $" << std::fixed << std::setprecision(2) << cliente.monto << std::endl;
        } else {
            std::cout << "Cola llena! No se pudo realizar la transacci�n." << std::endl;
        }
    }

    //JSON despu�s de simular
    guardarBalanceEnJSON(balanceTotal, totalTransacciones);
}

void ingresarTransaccionManualmente(Cola<Cliente>& colaTransacciones, double& balanceTotal, double& totalTransacciones) {
    std::string nombre;
    std::string numeroCuenta;
    bool esDeposito;
    double monto;

    std::cout << "Ingrese el nombre del cliente: ";
    std::cin >> nombre;
    std::cout << "Ingrese el n�mero de cuenta: ";
    std::cin >> numeroCuenta;
    std::cout << "Es un dep�sito? (1 para si, 0 para no): ";
    std::cin >> esDeposito;
    std::cout << "Ingrese el monto: ";
    std::cin >> monto;

    Cliente cliente(nombre, numeroCuenta, esDeposito, monto);

    if (cliente.esDeposito) {
        balanceTotal += cliente.monto;
        totalTransacciones += cliente.monto;
    } else {
        if (balanceTotal >= cliente.monto) {
            balanceTotal -= cliente.monto;
            totalTransacciones -= cliente.monto;
        } else {
            std::cout << "No hay suficiente saldo para el retiro de $" << cliente.monto << std::endl;
            return; // Salir de la funci�n sin procesar la transacci�n
        }
    }

    bool resultado;
    colaTransacciones.encolar(cliente, resultado);
    if (resultado) {
        std::cout << "Transacci�n encolada:";
        std::cout << "| Nombre: " << cliente.nombre << "    | # Cuenta: " << cliente.numeroCuenta
                  << ", Tipo: " << (cliente.esDeposito ? "Dep�sito" : "Retiro")
                  << ", Monto: $" << std::fixed << std::setprecision(2) << cliente.monto << std::endl;
    } else {
        std::cout << "Cola llena! No se pudo realizar la transacci�n." << std::endl;
    }

    //JSON despu�s de ingresar manualmente
    guardarBalanceEnJSON(balanceTotal, totalTransacciones);
}

void mostrarTransacciones(Cola<Cliente>& colaTransacciones) {
    colaTransacciones.mostrar();
    std::cout << "Tama�o actual de la cola: " << colaTransacciones.devolverTamanio() << std::endl;
}

void mostrarTotales(double balanceTotal, double totalTransacciones) {
    std::cout << "\nBalance total en el banco: $" << std::fixed << std::setprecision(2) << balanceTotal << std::endl;
    std::cout << "Total de transacciones acumuladas: $" << std::fixed << std::setprecision(2) << totalTransacciones << std::endl;
}
