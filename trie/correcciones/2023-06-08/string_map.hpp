#include <string>
#include <iostream>
using namespace std;

template <typename T>
string_map<T>::string_map(): raiz(new Nodo()), _size(0){}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
 //TODO: Para evitar leaks seguramente convenga borrar nodo por nodo
    *this->raiz = *d.raiz;
}

template <typename T>
typename string_map<T>::Nodo& string_map<T>::Nodo::operator=(const Nodo& aCopiar) {
    if (aCopiar.definicion != nullptr){
        T* def = new T;
        T valor = *aCopiar.definicion;
        *def = valor;
        this->definicion = def;
    }
    for (int i = 0; i < aCopiar.siguientes.size(); ++i) {
        if (aCopiar.siguientes[i] != nullptr){
            Nodo* nodoACopiar = aCopiar.siguientes[i];
            if (this->siguientes[i] == nullptr){
                Nodo* nuevoNodo = new Nodo();
                this->siguientes[i] = nuevoNodo;
            }
            Nodo* nodoAEscribir = this->siguientes[i];
            *nodoAEscribir = *nodoACopiar;
        }
    }
}

template <typename T>
string_map<T>::~string_map(){
    this->raiz->borrarTodo();
    delete this->raiz;
}

template<typename T>
void string_map<T>::Nodo::borrarTodo(){
    vector<Nodo*> hijos = this->siguientes;
    for (int i = 0; i < hijos.size(); ++i) {
        if (hijos[i] != nullptr){
            if (hijos[i]->definicion != nullptr) {
                delete hijos[i]->definicion;
                hijos[i]->definicion = nullptr;
            }
            hijos[i]->borrarTodo();
            delete hijos[i];
        }
    }
}


template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    Nodo* actual = this->raiz;
    string palabra = clave;
    for (int i = 0; i < palabra.length(); ++i) {
        unsigned char letra = palabra[i];
        Nodo* siguiente = actual->siguientes[int(letra)];
        if (siguiente == nullptr || (siguiente->definicion == nullptr && i == palabra.length()-1)){
            return 0;
        } else {
            actual = actual->siguientes[int(letra)];
        }
    }
    return 1;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual = this->raiz;
    string palabra = clave;

    for (unsigned char letra : palabra) {
        actual = actual->siguientes[int(letra)];
    }
    const T res = actual->definicion;
    return res;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual = this->raiz;
    string palabra = clave;

    for (unsigned char letra : palabra) {
        actual = actual->siguientes[int(letra)];
    }
    T* res = actual->definicion;
    return *res;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* actual = this->raiz;
    actual->borrarNodo(clave);
}

template<typename T>
void string_map<T>::Nodo::borrarNodo(string clave){
    Nodo* actual = this;
    Nodo* padre = nullptr;
    int direccion = 0;

    for (int i = 0; i < clave.size(); ++i) {
        padre = actual;
        unsigned char l = clave[i];
        direccion = int(l);
        actual = actual->siguientes[int(l)];
    }

    bool tieneHijos = false;
    for (int i = 0; i < actual->siguientes.size(); ++i) {
        if (actual->siguientes[i] != nullptr){
            tieneHijos = true;
        }
    }

    if (clave.empty()) {
        return;
    }

    if (!tieneHijos){
        delete actual->definicion;
        delete actual;
        padre->siguientes[direccion] = nullptr; //Si no tiene hijos, borramos el nodo directamente
        string substring = clave.substr(0, clave.size() - 1);
        this->borrarNodo(substring);
    } else {
        delete actual->definicion;
        actual->definicion = nullptr; //Borramos la definicion al llegar
        string substring = clave.substr(0, clave.size() - 1);
        this->borrarNodo(substring);
    }

}

template <typename T>
int string_map<T>::size() const{
    return this->_size;
}

template <typename T>
bool string_map<T>::empty() const{
    int i = 0;
    while(i < 256){
        if (this->raiz->siguientes[i] != nullptr){
            return false;
        }
        ++i;
    }
    return true;
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& dicc){
    Nodo* actual = this->raiz;
    string palabra = dicc.first;
    T definicion = dicc.second;

    for (unsigned char letra : palabra) {
        Nodo* siguiente = actual->siguientes[int(letra)];
        if (siguiente == nullptr){
            Nodo* nuevoNodo = new Nodo();
            actual->siguientes[int(letra)] = nuevoNodo;
            actual = nuevoNodo;
        } else {
            actual = actual->siguientes[int(letra)];
        }
    }
    if (actual->definicion != nullptr) {
        delete actual->definicion;
    }
    T* def = new T;
    *def = definicion;
    actual->definicion = def;
    this->_size++;
}