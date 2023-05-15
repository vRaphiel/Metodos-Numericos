#ifndef CODIGO_MATRIZ_H
#define CODIGO_MATRIZ_H

#include <map>
#include <vector>

using namespace std;

struct Matriz {

    Matriz(int tam);

    int dimension;

    double at(int fila, int columna) const;

    void asignar(int fila, int columna, double valor);

    Matriz operator*(Matriz m);   // Producto matricial
    Matriz operator*(double v);      // Producto Escalar
    Matriz operator+(Matriz m);   // Suma de Matrices
    Matriz operator-(Matriz m);   // Resta de Matrices
    int distintosDeCero(int columna);
    string imprimir();

    static Matriz identidad(int N) {
        Matriz I(N);
        for (int i = 0; i < N; i++) {
            I.asignar(i, i, 1.0);
        }
        return I;
    }

private:
    vector<double> A = vector<double>();
    vector<int> JA = vector<int>();
    vector<int> IA = vector<int>();
};

bool esCero(double);

#endif