#ifndef CODIGO_MATRIZ_H
#define CODIGO_MATRIZ_H

#include <unordered_map>
#include <vector>

using namespace std;

struct Matriz {

    Matriz(int tam);

    struct Fila {
        Fila(vector<double> vector1);

        const double &operator[](int columna) const;

        vector<double>::iterator begin();

        vector<double>::iterator end();

        int size();

    private:
        vector<double> _elementos;
    };

    Matriz(vector<Fila> filas);

    const Fila &operator[](int fila) const;

    Matriz operator*(Matriz m);   // Producto matricial
    Matriz operator*(double v);      // Producto Escalar
    Matriz operator+(Matriz m);   // Suma de Matrices
    Matriz operator-(Matriz m);   // Resta de Matrices
    int distintosDeCero(int columna);

    static Matriz identidad(int N) {
        Matriz I(N);
        for (int i = 0; i < N; i++) {
            I[i][i] = (double) 1;
        }
        return I;
    }

private:
    struct Columna {
        Columna(vector<double> elementos);

        double &operator[](int fila);

        vector<double> _elementos;

        vector<double>::iterator begin();

        vector<double>::iterator end();
    };

    unordered_map<int, Fila> _filas;

    vector<Columna> columnas();
};

#endif