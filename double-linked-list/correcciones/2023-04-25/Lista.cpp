#include "Lista.h"

Lista::Lista(): primer_puntero(nullptr), ultimo_puntero(nullptr) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.

    Nodo* primer_nodo_a_copiar = l.primer_puntero;
    while(primer_nodo_a_copiar != nullptr){

        this->agregarAtras(primer_nodo_a_copiar->valor);
        primer_nodo_a_copiar = primer_nodo_a_copiar->siguiente;
    }
}

Lista::~Lista() {

    destruirNodos();
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Completar

    if(this->primer_puntero != nullptr){
        this->destruirNodos();
    }

    Nodo* primer_nodo_a_copiar = aCopiar.primer_puntero;
    while(primer_nodo_a_copiar != nullptr){

        this->agregarAtras(primer_nodo_a_copiar->valor);
        primer_nodo_a_copiar = primer_nodo_a_copiar->siguiente;
    }

    // como llamo a lista por copia Lista otra(aCopiar)? tuve que copiarla a mano
    // por que el return *this?
    // no entiendo muy bien como funciona lo del operator

    return *this;
}

void Lista::destruirNodos() {

    Nodo* eliminado = this->primer_puntero;
    while(eliminado != nullptr){
        Nodo* guardo = eliminado->siguiente;
        delete eliminado;
        eliminado = guardo;
    }
    this->primer_puntero = nullptr;
    this->ultimo_puntero = nullptr;

}


void Lista::agregarAdelante(const int& elem) {

    Nodo* puntero_nuevo_nodo = new Nodo(elem);

    // si lista vacia:
    /*if(this->longitud() == 0){

        this->primer_puntero = puntero_nuevo_nodo;
        this->ultimo_puntero = puntero_nuevo_nodo;
    }else{

        Nodo primer_nodo_actual = *this->primer_puntero;

        primer_nodo_actual.anterior = puntero_nuevo_nodo;

        Nodo nuevo_nodo = *puntero_nuevo_nodo;
        nuevo_nodo.anterior = nullptr;
        nuevo_nodo.siguiente = &primer_nodo_actual;

        this->primer_puntero = puntero_nuevo_nodo;
    }*/

    if(this->longitud() == 0){

        this->primer_puntero = puntero_nuevo_nodo;
        this->ultimo_puntero = puntero_nuevo_nodo;
    }else{

        this->primer_puntero->anterior = puntero_nuevo_nodo;
        puntero_nuevo_nodo->siguiente = this->primer_puntero;
        this->primer_puntero = puntero_nuevo_nodo;
    }
}

void Lista::agregarAtras(const int& elem) {

    Nodo* puntero_nuevo_nodo = new Nodo(elem);

    // si esta vacio
    if(this->longitud() == 0){

        this->primer_puntero = puntero_nuevo_nodo;
        this->ultimo_puntero = puntero_nuevo_nodo;
    }else{

        this->ultimo_puntero->siguiente = puntero_nuevo_nodo;
        puntero_nuevo_nodo->anterior = this->ultimo_puntero;
        this->ultimo_puntero = puntero_nuevo_nodo;
    }
}

void Lista::eliminar(Nat i) {

    if(this->longitud() == 1){

        delete this->primer_puntero;
        this->primer_puntero = nullptr;
        this->ultimo_puntero = nullptr;

    }else{

        // si esta vacia
        // elimino al principio
        if(i == 0){

            // elimino el primer nodo
            this->primer_puntero->siguiente->anterior = nullptr;

            // lo uso para poder liberar el heap sino no podria hacer el cambio del primer puntero
            Nodo* puntero_intermedio = primer_puntero;

            this->primer_puntero = this->primer_puntero->siguiente;
            delete puntero_intermedio;
        }else if(i == this->longitud() - 1){

            this->ultimo_puntero->anterior->siguiente = nullptr;

            //puntero intermedio
            Nodo* puntero_intermedio = this->ultimo_puntero;

            this->ultimo_puntero = this->ultimo_puntero->anterior;
            delete puntero_intermedio;
        }else{

            // nodo a eliminar no esta ni al principio ni al final
            Nodo* puntero_actual= this->primer_puntero;
            for(int j = 0; j < i; j++){
                puntero_actual = puntero_actual->siguiente;
            }

            puntero_actual->siguiente->anterior = puntero_actual->anterior;

            // puntero intermedio
            Nodo* puntero_intermedio = puntero_actual;

            puntero_actual->anterior->siguiente = puntero_actual->siguiente;
            delete puntero_intermedio;
        }
    }
}

int Lista::longitud() const {

    int contador = 0;
    Nodo* puntero_primer_nodo = this->primer_puntero;

    while(puntero_primer_nodo != nullptr){

        contador ++;
        puntero_primer_nodo = puntero_primer_nodo->siguiente;
    }

    return contador;
}

const int& Lista::iesimo(Nat i) const {

    /*
    Nodo* puntero_primer_nodo = this->primer_puntero;

    for(int j = 0; j < i; j++){
        puntero_primer_nodo = (*primer_puntero).siguiente;
    }

    Nodo nodo_actual = *puntero_primer_nodo;

    return nodo_actual.valor;
     */

    Nodo* res= this->primer_puntero;
    for(int j = 0; j < i; j++){
        res = res->siguiente;
    }
    return res->valor;
}

int& Lista::iesimo(Nat i) {

    /*
    Nodo* puntero_primer_nodo = this->primer_puntero;


    for(int j = 0; j < i; j++){

        puntero_primer_nodo = (*primer_puntero).siguiente;
    }

    Nodo nodo_actual = *puntero_primer_nodo;

    return nodo_actual.valor; */

    Nodo* res= this->primer_puntero;
    for(int j = 0; j < i; j++){
        res = res->siguiente;
    }
    return res->valor;
}

void Lista::mostrar(ostream& o) {
}
