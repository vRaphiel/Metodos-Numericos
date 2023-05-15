#ifndef CODIGO_MATRIZDOK_H
#define CODIGO_MATRIZDOK_H

#include "matriz.h"
#include <map>
#include <vector>

using namespace std;

struct MatrizDok {

    MatrizDok(int tam);
    
    MatrizDok(Matriz m);

    int dimension;

    Matriz aCsr();

    double at(int fila, int columna) const;

    void asignar(int fila, int columna, double valor);

    MatrizDok operator*(MatrizDok m);   // Producto matricial
    MatrizDok operator*(double v);      // Producto Escalar
    MatrizDok operator+(MatrizDok m);   // Suma de Matrices
    MatrizDok operator-(MatrizDok m);   // Resta de Matrices

    static MatrizDok identidad(int N) {
        MatrizDok I(N);
        for (int i = 0; i < N; i++) {
            I.asignar(i, i, 1.0);
        }
        return I;
    }

private:
    map<pair<int, int>, double> _rep = map<pair<int, int>, double>();

    string imprimir();
};

#endif
