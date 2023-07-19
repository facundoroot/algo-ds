
template <class T>
Conjunto<T>::Conjunto(): _raiz(nullptr) {}

template <class T>
Conjunto<T>::~Conjunto() {
    while(this->cardinal() > 0){
        T aRemover = this->minimo();
        this->remover(aRemover);
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = this->_raiz;
    while(actual != nullptr){
        if (actual->valor == clave) {
            return true;
        } else {
            if (clave < actual->valor) {
                actual = actual->izq;
            } else {
                actual = actual->der;
            }
        }
    }
    return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    Nodo* actual = this->_raiz;
    Nodo* padre = nullptr;
    Nodo* nuevoNodo = new Nodo(clave);
    if (actual == nullptr){
        this->_raiz = nuevoNodo;
        return;
    }
    while (actual != nullptr) {
        if (actual->valor < clave){
            padre = actual;
            actual = actual->der;
        } else if (actual->valor > clave){
            padre = actual;
            actual = actual->izq;
        } else {
            delete nuevoNodo;
            return;
        }
    }
    if (clave > padre->valor ){
        padre->der = nuevoNodo;
    } else {
        padre->izq = nuevoNodo;
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    Nodo* actual = this->_raiz;
    Nodo* padre = nullptr;
    while(actual->valor != clave){
        if (clave > actual->valor) {
            padre = actual;
            actual = actual->der;
        } else {
            padre = actual;
            actual = actual->izq;
        }
    }

    Nodo* subIzq = actual->izq;
    Nodo* subDer = actual->der;
    //Caso 1: El nodo a remover es una hoja (o raiz)
    if (subDer == nullptr && subIzq == nullptr){
        if (padre == nullptr){
            delete actual;
            this->_raiz = nullptr;
            return;
        } else {
            if (actual->valor < padre->valor) {
                padre->izq = nullptr;
            } else {
                padre->der = nullptr;
            }
            delete actual;
            return;
        }
    }

    int hijos = 0;
    Nodo* hijo = nullptr;
    if(subIzq != nullptr){
        hijos++;
        hijo = subIzq;
    }
    if(subDer != nullptr){
        hijos++;
        hijo = subDer;
    }

    //Caso 2: El nodo a borrar tiene un solo hijo
    if (hijos == 1){
        if (padre == nullptr) {
            this->_raiz = hijo;
            delete actual;
        } else {
            if (actual->valor < padre->valor) {
                padre->izq = hijo;
                delete actual;
                return;
            } else {
                padre->der = hijo;
                delete actual;
                return;
            }
        }
    } else {
        //Caso 3: El nodo a borrar tiene dos hijos
        T minimoSucesor = actual->der->minimoDeNodos();
        actual->valor = minimoSucesor;
        // Si el nodo de la derecha es el unico que hay, lo borramos
        if (actual->der->izq == nullptr && actual->der->der == nullptr){
            delete actual->der;
            actual->der = nullptr;
            return;
        }
        Nodo* aRemover = actual->der;
        Nodo* padreARemover = actual;
        T valorARemover = actual->valor;
        while(aRemover->valor != valorARemover){
            if (clave > aRemover->valor) {
                padreARemover = aRemover;
                aRemover = aRemover->der;
            } else {
                padreARemover = aRemover;
                aRemover = aRemover->izq;
            }
        }

        subIzq = aRemover->izq;
        subDer = aRemover->der;
        //Caso 1: El nodo a remover es una hoja (o raiz)
        if (subDer == nullptr && subIzq == nullptr){
            if (aRemover->valor < padreARemover->valor) {
                delete padreARemover->izq;
                padreARemover->izq = nullptr;
                return;
            } else {
                delete padreARemover->der;
                padreARemover->der = nullptr;
                return;
            }
        }

        hijos = 0;
        if(subIzq != nullptr){
            hijos++;
            hijo = subIzq;
        }
        if(subDer != nullptr){
            hijos++;
            hijo = subDer;
        }

        //Caso 2: El nodo a borrar tiene un solo hijo
        if (hijos == 1){
            if(aRemover->valor < padreARemover->valor){
                delete padreARemover->izq;
                padreARemover->izq = hijo;
                return;
            } else {
                delete padreARemover->der;
                padreARemover->der = hijo;
                return;
            }
        }
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* actual = this->_raiz;
    Nodo* padre = nullptr;
    while(actual != nullptr){
        if (actual->valor == clave){
            break;
        }
        if (clave > actual->valor){
            padre = actual;
            actual = actual->der;
        } else {
            padre = actual;
            actual = actual->izq;
        }
    }

    if (actual->izq == nullptr && actual->der == nullptr){
        actual = padre;
    }

    T mayorDeIzq = actual->izq->maximoDeNodos();
    T menorDeDer = actual->der->minimoDeNodos();

    T distIzq = actual->valor - mayorDeIzq;
    T distDer = actual->valor - menorDeDer;
    T padreValor = actual->valor - padre->valor;

    if (distDer < 0){
        distDer = distDer * -1;
    }
    if (distIzq < 0){
        distIzq = distIzq * -1;
    }
    if (padreValor < 0){
        padreValor = padreValor * -1;
    }

    if (distIzq < distDer){
        if (distIzq < padreValor){
            return actual->izq->maximoDeNodos();
        } else {
            return padre->valor;
        }
    } else {
        if (distDer < padreValor){
            return actual->der->minimoDeNodos();
        } else {
            return padre->valor;
        }
    }

}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual = this->_raiz;
    while (actual->izq != nullptr){
        actual = actual->izq;
    }
    return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual = this->_raiz;
    while (actual->der != nullptr){
        actual = actual->der;
    }
    return actual->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    Nodo* raiz = this->_raiz;
    return raiz->longitudDeNodos();
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template <class T>
int Conjunto<T>::Nodo::longitudDeNodos() {
    if (this == nullptr){
        return 0;
    }
    if (this->der == nullptr && this->izq == nullptr){
        return 1;
    } else {
        return 1 + this->izq->longitudDeNodos() + this->der->longitudDeNodos();
    }
}

template <class T>
T& Conjunto<T>::Nodo::minimoDeNodos() {
    Nodo* actual = this;
    while (actual->izq != nullptr){
        actual = actual->izq;
    }
    return actual->valor;
}

template <class T>
T& Conjunto<T>::Nodo::maximoDeNodos() {
    Nodo* actual = this;
    while (actual->der != nullptr){
        actual = actual->der;
    }
    return actual->valor;
}

