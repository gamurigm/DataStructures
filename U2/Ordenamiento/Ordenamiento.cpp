#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <iostream>
#include <chrono>

template <typename T>
class Ordenamiento {
public:
    virtual void ordenar(T arr[], long long int n) = 0;
    
    void medirTiempoOrdenamiento(T arr[], long long int n) {
        auto inicio = std::chrono::high_resolution_clock::now();
        ordenar(arr, n);
        auto fin = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duracion = fin - inicio;
        std::cout << "Tiempo de ordenamiento: " << duracion.count() << " milisegundos" << std::endl;
    }

    void imprimirArray(T arr[], long long int n) {
        for (long long int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

protected:
    void intercambiar(T* a, T* b) {
        T temp = *a;
        *a = *b;
        *b = temp;
    }

    long long int obtenerTamanio(T arr[]) {
        return sizeof(arr) / sizeof(arr[0]);
    }
};

template <typename T>
class ShellSort : public Ordenamiento<T> {
public:
    void ordenar(T arr[], long long int n) override {
        for (long long int salto = n / 2; salto > 0; salto /= 2) {
            for (long long int i = salto; i < n; i++) {
                T temp = arr[i];
                long long int j;
                for (j = i; j >= salto && arr[j - salto] > temp; j -= salto) {
                    arr[j] = arr[j - salto];
                }
                arr[j] = temp;
            }
        }
    }
};

template <typename T>
class QuickSort : public Ordenamiento<T> {
public:
    void ordenar(T arr[], long long int n) override {
        quickSort(arr, 0, n - 1);
    }

private:
    void quickSort(T arr[], long long int bajo, long long int alto) {
        if (bajo < alto) {
            long long int pi = particionar(arr, bajo, alto);
            quickSort(arr, bajo, pi - 1);
            quickSort(arr, pi + 1, alto);
        }
    }

    long long int particionar(T arr[], long long int bajo, long long int alto) {
        T pivote = arr[alto];
        long long int i = (bajo - 1);

        for (long long int j = bajo; j <= alto - 1; j++) {
            if (arr[j] <= pivote) {
                i++;
                this->intercambiar(&arr[i], &arr[j]);
            }
        }
        this->intercambiar(&arr[i + 1], &arr[alto]); 
        return (i + 1);
    }
};

template <typename T>
class IntercambioSimple : public Ordenamiento<T> {
public:
    void ordenar(T arr[], long long int n) override {
        for (long long int i = 0; i < n - 1; i++) {
            for (long long int j = i + 1; j < n; j++) {
                if (arr[j] < arr[i]) {
                    this->intercambiar(&arr[i], &arr[j]); 
                }
            }
        }
    }
};

template <typename T>
class Seleccion : public Ordenamiento<T> {
public:
    void ordenar(T arr[], long long int n) override {
        for (long long int i = 0; i < n - 1; i++) {
            long long int min_idx = i;
            for (long long int j = i + 1; j < n; j++) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                this->intercambiar(&arr[i], &arr[min_idx]); 
            }
        }
    }
};

template <typename T>
class Burbuja : public Ordenamiento<T> {
public:
    void ordenar(T arr[], long long int n) override {
        for (long long int i = 0; i < n - 1; i++) {
            for (long long int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    this->intercambiar(&arr[j], &arr[j + 1]); 
                }
            }
        }
    }
};


template <typename T>
class BucketSort : public Ordenamiento<T> {
public:
    void ordenar(T arr[], long long int n) override {
        if (n <= 1) return; 
        
        T max_val = arr[0];
        T min_val = arr[0];
        for (int i = 1; i < n; ++i) {
            if (arr[i] > max_val) max_val = arr[i];
            if (arr[i] < min_val) min_val = arr[i];
        }

        // Crear "buckets" de tamaño n
        const int num_buckets = n;
        T buckets[num_buckets];

        // Inicializar todos los "buckets" a 0
        for (int i = 0; i < num_buckets; ++i) {
            buckets[i] = 0;
        }

        // Colocar los elementos en los "buckets"
        for (int i = 0; i < n; ++i) {
            int bucket_index = static_cast<int>((arr[i] - min_val) / (max_val - min_val) * (num_buckets - 1));
            buckets[bucket_index] = arr[i];
        }

        // Ordenar cada "bucket" (en este caso, simplemente imprimirlos en orden)
        for (int i = 0; i < num_buckets; ++i) {
            if (buckets[i] != 0) {
                std::cout << buckets[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};


template <typename T>
void ingresarDatos(T arr[], int n) {
    std::cout << "Ingrese " << n << " números:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "Ingrese el número " << (i + 1) << ": ";
        std::cin >> arr[i];
    }
}


template <typename T>
void generarAleatorios(T arr[], int n) {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < n; ++i) {
        if (std::is_integral<T>::value) {
            arr[i] = rand() % 1000;  
        } else {
            arr[i] = (rand() % 1000) + static_cast<double>(rand()) / RAND_MAX;  
        }
    }
}

#endif // ORDENAMIENTO_H