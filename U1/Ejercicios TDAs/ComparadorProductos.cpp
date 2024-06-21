#include <iostream>
#include <string>

using namespace std;

struct Producto {
    int id;
    string descripcion;
    float precio;
};

void ingresarProducto(Producto &product) {
    cout << "Ingrese el id: ";
    cin >> product.id;
    cin.ignore(); 

    cout << "Ingrese una descripcion: ";
    getline(cin, product.descripcion);

    cout << "Ingrese el precio del producto: ";
    cin >> product.precio;
    cout << "\n";
}

void mostrar(const Producto &product) {
    cout << "\nID: " << product.id << endl;
    cout << "Descripcion: " << product.descripcion << endl;
    cout << "Precio:" << product.precio << endl;
    
}

int main() {
    Producto p1, p2;
    
    ingresarProducto(p1);
    ingresarProducto(p2);

    cout << "\nComparando precios...\n" << endl;
    if (p1.precio > p2.precio) {
        cout << "Producto con mayor precio:" << endl;
        mostrar(p1);
    } else if (p1.precio < p2.precio) {
        cout << "Producto con mayor" << endl;
        mostrar(p2);
    } else {
        cout << "Ambos productos tienen el mismo precio." << endl;
        mostrar(p1);
        mostrar(p2);	
    }

    return 0;
}
