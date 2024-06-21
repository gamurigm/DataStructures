#ifndef MANEJOJSON_H
#define MANEJOJSON_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <dirent.h>   
#include <sys/stat.h> // Para verificar y crear directorios
#include "nlohmann/json.hpp"
#include "Cola.h"     
#include "Cliente.h"  

using namespace std;
using json = nlohmann::json;

const string CARPETA_TRANSACCIONES = "Transacciones";


bool carpetaExiste(const string& carpeta) {
    struct stat buffer;
    return (stat(carpeta.c_str(), &buffer) == 0);
}

bool crearCarpeta(const string& carpeta) {
    int status = mkdir(carpeta.c_str());
    return (status == 0);
}

bool transaccionExiste(int id) {
    string nombreArchivo = CARPETA_TRANSACCIONES + "/transaccion_" + to_string(id) + ".json";
    ifstream archivo(nombreArchivo);
    return archivo.good();
}


void guardarTransaccion(const Cliente& cliente, int id) {
    if (!carpetaExiste(CARPETA_TRANSACCIONES)) {
        if (!crearCarpeta(CARPETA_TRANSACCIONES)) {
            cerr << "Error: No se pudo crear la carpeta '" << CARPETA_TRANSACCIONES << "'" << endl;
            return;
        }
        cout << "Carpeta '" << CARPETA_TRANSACCIONES << "' creada exitosamente." << endl;
    }

    if (transaccionExiste(id)) {
        cout << "Error: La transacción con ID '" << id << "' ya existe." << endl;
        return;
    }

    string nombreArchivo = CARPETA_TRANSACCIONES + "/transaccion_" + to_string(id) + ".json";

    json j;
    j["nombre"] = cliente.nombre;
    j["numeroCuenta"] = cliente.numeroCuenta;
    j["esDeposito"] = cliente.esDeposito;
    j["monto"] = cliente.monto;

    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo << setw(4) << j << endl; // Escribir JSON con formato indentado
        archivo.close();
        cout << "Transacción guardada exitosamente: " << cliente.nombre << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escribir: " << nombreArchivo << endl;
    }
}


void cargarTransacciones(Cola<Cliente>& colaTransacciones) {
    DIR* dir;
    struct dirent* ent;

    if ((dir = opendir(CARPETA_TRANSACCIONES.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string nombreArchivo = ent->d_name;
            if (nombreArchivo.find(".json") != string::npos) {
                string rutaArchivo = CARPETA_TRANSACCIONES + "/" + nombreArchivo;
                ifstream archivo(rutaArchivo);
                if (archivo.is_open()) {
                    json j;
                    try {
                        archivo >> j;
                        archivo.close();

                        if (j.contains("nombre") && j["nombre"].is_string() &&
                            j.contains("numeroCuenta") && j["numeroCuenta"].is_string() &&
                            j.contains("esDeposito") && j["esDeposito"].is_boolean() &&
                            j.contains("monto") && j["monto"].is_number_float()) {

                            Cliente cliente(j["nombre"].get<string>(),
                                            j["numeroCuenta"].get<string>(),
                                            j["esDeposito"].get<bool>(),
                                            j["monto"].get<double>());

                            bool resp;
                            colaTransacciones.encolar(cliente, resp);
                            if (resp) {
                                cout << "Transacción cargada: " << cliente.nombre << endl;
                            } else {
                                cerr << "Cola llena. No se pudo cargar la transacción." << endl;
                            }
                        } else {
                            cerr << "El archivo " << rutaArchivo << " no contiene los campos necesarios o algunos tienen tipos incorrectos." << endl;
                        }
                    } catch (const json::parse_error& e) {
                        cerr << "Error de parseo en el archivo JSON " << rutaArchivo << ": " << e.what() << endl;
                    } catch (const json::type_error& e) {
                        cerr << "Error de tipo en el archivo JSON " << rutaArchivo << ": " << e.what() << endl;
                    } catch (const std::exception& e) {
                        cerr << "Error al procesar el archivo JSON " << rutaArchivo << ": " << e.what() << endl;
                    }
                } else {
                    cerr << "No se pudo abrir el archivo: " << rutaArchivo << endl;
                }
            }
        }
        closedir(dir);
    } else {
        cerr << "No se pudo abrir el directorio: " << CARPETA_TRANSACCIONES << endl;
    }
}


void guardarBalanceEnJSON(double balanceTotal, double totalTransacciones) {
    json data;
    data["balanceTotal"] = balanceTotal;
    data["totalTransacciones"] = totalTransacciones;

    std::ofstream archivo("balance.json");
    if (archivo.is_open()) {
        archivo << std::setw(4) << data << std::endl; // Escribir JSON con formato indentado
        archivo.close();
        std::cout << "Balance guardado en balance.json" << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo balance.json para guardar el balance." << std::endl;
    }
}


void cargarBalanceDesdeJSON(double& balanceTotal, double& totalTransacciones) {
    std::ifstream archivo("balance.json");
    if (archivo.is_open()) {
        json data;
        archivo >> data;
        balanceTotal = data["balanceTotal"];
        totalTransacciones = data["totalTransacciones"];
        archivo.close();
        std::cout << "Balance cargado desde balance.json" << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo balance.json para cargar el balance." << std::endl;
    }
}


#endif // MANEJOJSON_H
