#include <iostream>
#include "Ordenamiento.h"

template <typename T>
void Ordenamiento<T>::shellSort(T arr[], int n) {
    for (int salto = n/2; salto > 0; salto /= 2) {
        for (int i = salto; i < n; i++) {
            T temp = arr[i];
            int j;
            for (j = i; j >= salto && arr[j - salto] > temp; j -= salto) {
                arr[j] = arr[j - salto];
            }
            arr[j] = temp;
        }
    }
}

template <typename T>
void Ordenamiento<T>::quickSort(T arr[], int bajo, int alto) {
    if (bajo < alto) {
        int pi = particionar(arr, bajo, alto);
        quickSort(arr, bajo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

template <typename T>
void Ordenamiento<T>::imprimirArray(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
int Ordenamiento<T>::particionar(T arr[], int bajo, int alto) {
    T pivote = arr[alto];
    int i = (bajo - 1);

    for (int j = bajo; j <= alto - 1; j++) {
        if (arr[j] <= pivote) {
            i++;
            intercambiar(&arr[i], &arr[j]);
        }
    }
    intercambiar(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

template <typename T>
void Ordenamiento<T>::intercambiar(T* a, T* b) {
    T t = *a;
    *a = *b;
    *b = t;
}
