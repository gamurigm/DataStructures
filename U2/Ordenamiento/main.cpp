#include <iostream>
#include "Ordenamiento.h"
#include "Lista.h"
#include <cstdlib>
#include <ctime>


using namespace std;

int main() {
    const long long int TAM = 10000; 
    long long int arr1[TAM];
    long long int arr2[TAM];


    std::srand(std::time(0));
    for (long long int i = 0; i < TAM; ++i) {
        long long int val = std::rand() % 10000;
        arr1[i] = val;
        arr2[i] = val;
    }

    ShellSort<long long int> shellSort;
    QuickSort<long long int> quickSort;
    IntercambioSimple<long long int> intercambioSimple;
    Seleccion<long long int> seleccion;
    Burbuja<long long int> burbuja;    
	BucketSort<long long int> bs;

    cout << "tiempo de ShellSort: ";
    shellSort.medirTiempoOrdenamiento(arr1, TAM);
    cout << "ordenado con ShellSort." << endl;

    cout << "Medici�n del tiempo de QuickSort: ";
    quickSort.medirTiempoOrdenamiento(arr2, TAM);
    cout << "ordenado con QuickSort." << endl;

    cout << "Array ordenado con Intercambio Simple: ";
    intercambioSimple.medirTiempoOrdenamiento(arr1, TAM);
    cout << "ordenado con Intercambio Simple." << endl;

    cout << "Selecci�n: ";
    seleccion.medirTiempoOrdenamiento(arr2, TAM);
    cout << "ordenado con Selecci�n." << endl;

    cout << "Burbuja: ";
    burbuja.medirTiempoOrdenamiento(arr1, TAM);
    cout << "ordenado con Burbuja." << endl;
    

	bs.medirTiempoOrdenamiento(arr2, TAM);
	

    return 0;
}
