#include "enlazada.h"

bool esCero(double valor) {
    return -1e-5 < valor && valor < 1e-5;
}

Enlazada::Enlazada(int dimension){
    _dimension = dimension;
    _matriz = vector<Columna*>(dimension);
    for(int i = 0; i < _matriz.size(); i++){
        _matriz[i] = nullptr;
    }
}

double Enlazada::at(int fila, int columna) const {
    double val = 0;
    if(_matriz[fila] != nullptr){
        Columna* col = _matriz[fila];
        while(col != nullptr && col->posicion != columna){
            col = col->siguiente;
        }
        if(col != nullptr){
            val = col->valor;
        }
    }
    return val;
}

void Enlazada::asignar(int fila, int columna, double valor){ //solo para asignar al convertir, despues usamos insertar y borrar para EG
            Columna* nuevo = new(Columna);
            nuevo->posicion = columna;
            nuevo->valor = valor;
            if(_matriz[fila] == nullptr){
                nuevo->anterior = nullptr;
                nuevo->siguiente = nullptr;
                _matriz[fila] = nuevo;
            } else { 
                Columna* actual = _matriz[fila];
                while(actual->siguiente != nullptr && actual->posicion < nuevo->posicion){
                    actual = actual->siguiente;
                }
                if(actual->anterior == nullptr && actual->siguiente == nullptr){
                    if(actual->posicion < nuevo->posicion){
                        nuevo->anterior = actual;
                        nuevo->siguiente = nullptr;
                        actual->siguiente = nuevo;

                    } else {
                        nuevo->anterior = nullptr;
                        nuevo->siguiente = actual;
                        actual->anterior = nuevo;
                        _matriz[fila] = nuevo;
                    }
                } else if(actual->anterior == nullptr){
                        nuevo->anterior = nullptr;
                        nuevo->siguiente = actual;
                        actual->anterior = nuevo;
                        _matriz[fila] = nuevo;
                } else if(actual->siguiente == nullptr){
                    if(actual->posicion < nuevo->posicion){
                        nuevo->anterior = actual;
                        nuevo->siguiente = nullptr;
                        actual->siguiente = nuevo;
                    } else {
                        nuevo->anterior = actual->anterior;
                        nuevo->siguiente = actual;
                        nuevo->anterior->siguiente = nuevo;
                        nuevo->siguiente->anterior = nuevo;
                    }
                } else {
                    nuevo->anterior = actual->anterior;
                    nuevo->siguiente = actual;
                    nuevo->anterior->siguiente = nuevo;
                    nuevo->siguiente->anterior = nuevo;
                }
            }
}

void Enlazada::insertar(int fila, Columna* col_j, Columna* col_i, double valor, int lado){
    Columna* nuevo = new(Columna);
    nuevo->posicion = col_i->posicion;
    nuevo->valor = valor;
    if(lado == 0){ //si lo quiero a la izquierda
        if(col_j->anterior == nullptr){
            nuevo->anterior = nullptr;
            nuevo->siguiente = col_j;
            col_j->anterior = nuevo;
            _matriz[fila] = nuevo;
        } else {
            nuevo->anterior = col_j->anterior;
            nuevo->siguiente = col_j;
            nuevo->anterior->siguiente = nuevo;
            nuevo->siguiente->anterior = nuevo;
        }
    } else { // si lo quiero a la derecha
            nuevo->anterior = col_j;
            nuevo->siguiente = nullptr;
            col_j->siguiente = nuevo;
    }
}

void Enlazada::borrar(int fila, Columna* col_j){
    if(col_j->anterior == nullptr){
        Columna* primero = col_j->siguiente;
        primero->anterior = nullptr;
        _matriz[fila] = primero;
        delete(col_j);
    } else {
        if(col_j->siguiente == nullptr){
            Columna* ultimo = col_j->anterior;
            ultimo->siguiente = nullptr;
            delete(col_j);
        } else {
            Columna* ant = col_j->anterior;
            ant->siguiente = col_j->siguiente;
            Columna* sig = col_j->siguiente;
            sig->anterior = col_j->anterior;
            delete(col_j);
        }
    }
}

vector<double> Enlazada::eliminacionGausseana(vector<double> &b){
    for(int p = 0; p < _dimension - 1; p++){
        for(int fila = p + 1; fila < _dimension; fila++){
                Columna* col_j = _matriz[fila];
                while(col_j->posicion < p && col_j->siguiente != nullptr){
                    col_j = col_j->siguiente;
                }
                if(col_j->posicion == p){ //si no hay un 0 donde quiero poner un 0
                    Columna* col_i = _matriz[p];
                    while(col_i->posicion != p)
                        col_i = col_i->siguiente;
                    double factor = (col_j->valor)/(col_i->valor);
                    Columna* col_j_anterior = col_j;
                    while(col_i != nullptr && col_j != nullptr){
                        while(col_j != nullptr && col_j->posicion < col_i->posicion){
                            col_j_anterior = col_j;
                            col_j = col_j->siguiente;
                        }
                        if(col_j == nullptr){
                            double valor = (-1) * factor * (col_i->valor);
                            insertar(fila,col_j_anterior,col_i,valor,1);
                        } else {
                            if(col_j->posicion == col_i->posicion){
                                double valor = (col_j->valor) - factor * (col_i->valor);
                                if(!esCero(valor)){
                                    col_j->valor = valor;
                                } else {
                                    borrar(fila, col_j);
                                    }
                            } else {
                                double valor = (-1) * factor * (col_i->valor);
                                insertar(fila, col_j, col_i, valor, 0);
                            }
                        }
                        col_i = col_i->siguiente;
                    }
                    while(col_i != nullptr){
                        double valor = (-1) * factor * (col_i->valor);
                        insertar(fila, col_j_anterior, col_i, valor, 1);
                        col_j_anterior = col_j_anterior->siguiente;
                        col_i = col_i->siguiente;
                    }
                    b[fila] -= factor * b[p];
                }
        }
    }
    return b;
}

vector<double> Enlazada::backwardSubstitution(vector<double> &b){
    vector<double> coef_x(_dimension, 0);
    for (int i = _dimension - 1; i >= 0; i--) {
        double b_i = b[i];
        double sum = 0;
        for (int j = i + 1; j <= _dimension - 1; j++) {
            sum += at(i, j) * coef_x[j];
        }
        double x_i = (b_i - sum) / at(i, i);
        coef_x[i] = x_i;
    }
    return coef_x;
}