#include <iostream>
#include <stdexcept> // Para std::runtime_error

template<typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(const T& newData) : data(newData), next(nullptr) {}
};

template<typename T>
class Cola {
public:
    Cola() : head(nullptr), tail(nullptr), size(0) {}

    ~Cola() {
        limpiar();
    }

    void encolar(const T& valor) {
        Node<T>* newNode = new Node<T>(valor);
        if (estaVacia()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void desencolar() {
        if (estaVacia()) {
            throw std::runtime_error("La cola está vacía. No se puede desencolar.");
        }
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        if (!head) {
            tail = nullptr;
        }
    }

    T frente() const {
        if (estaVacia()) {
            throw std::runtime_error("La cola está vacía. No hay elemento en el frente.");
        }
        return head->data;
    }

    bool estaVacia() const {
        return head == nullptr;
    }

    void limpiar() {
        while (!estaVacia()) {
            desencolar();
        }
    }

    void crear() {
        limpiar(); // Simplemente limpia la cola existente
    }

    bool borrar() {
        limpiar();
        return estaVacia(); // Retorna true si la cola quedó vacía después de borrar
    }

    bool estaLlena() const {
        return false; // En una cola basada en lista enlazada, nunca está llena
    }

    size_t devolverTamanio() const {
        return size; // Retorna el tamaño actual de la cola
    }

    // Funciones adicionales para operar sobre la cola
    void Crear_cola(bool& ok) {
        limpiar();
        ok = true;
    }

    void Borrar_cola(bool& ok) {
        limpiar();
        ok = true;
    }

    void Vacia(bool& resp) {
        resp = estaVacia();
    }

    void Llena(bool& resp) {
        resp = estaLlena(); // En este caso, siempre devuelve false
    }

    void Queue(const T& X, bool& resp) {
        encolar(X);
        resp = true;
    }

    void Dequeue(T& X, bool& resp) {
        if (estaVacia()) {
            resp = false;
        } else {
            X = frente();
            desencolar();
            resp = true;
        }
    }

    void Tamanio(size_t& N) {
        N = devolverTamanio();
    }

private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;
};
