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

    void encolar(const T& valor, bool& resp) {
        Node<T>* newNode = new Node<T>(valor);
        if (estaLlena()) {
            resp = false; // No se puede encolar si la cola está llena
            delete newNode;
        } else {
            if (estaVacia()) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            size++;
            resp = true;
        }
    }

    void desencolar(T& valor, bool& resp) {
        if (estaVacia()) {
            resp = false; 
        } else {
            Node<T>* temp = head;
            valor = temp->data;
            head = head->next;
            delete temp;
            size--;
            if (!head) {
                tail = nullptr;
            }
            resp = true;
        }
    }

    T frente(bool& resp) const {
        if (estaVacia()) {
            resp = false; 
            throw std::runtime_error("La cola está vacía. No hay elemento en el frente.");
        }
        resp = true;
        return head->data;
    }

    bool estaVacia() const {
        return head == nullptr;
    }

    void limpiar() {
        while (!estaVacia()) {
            bool resp;
            T valor;
            desencolar(valor, resp);
        }
    }

    bool estaLlena() const {
        return false; 
    }

    size_t devolverTamanio() const {
        return size; 
    }
    
    void mostrar() const {
	        if (estaVacia()) {
	            std::cout << "Empty." << std::endl;
	        } else {
	            std::cout << "\n\t\tementos en la cola:" << std::endl;
	            Node<T>* temp = head;
	            while (temp != nullptr) {
	                std::cout << temp->data << " ";
	                temp = temp->next;
	            }
	            std::cout << std::endl;
	        }
	    }      

private:
    Node<T>* head;
    Node<T>* tail;
    size_t size; //el tamaño actual 

    bool estaLlena(const Cola<T>& C) const {
        return false;
    }

    bool estaVacia(const Cola<T>& C) const {
        return C.head == nullptr;
    }
};


