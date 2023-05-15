#include "matrizdok.h"
#include "matriz.h"

MatrizDok::MatrizDok(int tam) {
    dimension = tam;
}

MatrizDok::MatrizDok(Matriz m) {
    dimension = m.dimension;
    for (int fila = 0; fila < m.dimension; fila++)
        for (int i = m.IA[fila]; i < m.IA[fila + 1]; i++)
            asignar(fila, m.JA[i], m.A[i]);
}

double MatrizDok::at(int fila, int columna) const {
    double val = 0;

    pair<int, int> p = {fila, columna};
    if (_rep.count(p)) {
        val = _rep.at(p);
    }
    return val;
}

void MatrizDok::asignar(int fila, int columna, double valor) {
    pair<int, int> p = {fila, columna};
    if (esCero(valor)) {
        _rep.erase(p);
    } else {
        _rep[p] = valor;
    }
}

Matriz MatrizDok::aCsr() {
    int tot = 0, f = 0;
    vector<int> IA(dimension + 1, 0);
    vector<int> JA;
    vector<double> A;
    for (auto i : _rep) {
        while (f < i.first.first) {
            IA[f + 1] = tot;
            f++;
        }
        tot++;
        A.push_back(i.second);
        JA.push_back(i.first.second);
    }
    while (f < dimension) {
        IA[f + 1] = tot;
        f++;
    }

    return { dimension, A, JA, IA };
}

MatrizDok MatrizDok::operator+(MatrizDok m) {
    MatrizDok resultado = MatrizDok(dimension);
    for (int f = 0; f < dimension; f++) {
        for (int c = 0; c < dimension; c++) {
            resultado.asignar(f, c, at(f, c) + m.at(f, c));
        }
    }
    return resultado;
}

MatrizDok MatrizDok::operator*(MatrizDok m) {
    MatrizDok resultado = MatrizDok(dimension);
    for (int f = 0; f < dimension; f++) {
        for (int c = 0; c < dimension; c++) {
            double suma = 0;
            for (int x = 0; x < dimension; x++) {
                suma += at(f, x) * m.at(x, c);
            }
            resultado.asignar(f, c, suma);
        }
    }
    return resultado;
}

MatrizDok MatrizDok::operator*(double v) {
    MatrizDok resultado = MatrizDok(dimension);
    for (int f = 0; f < dimension; f++) {
        for (int c = 0; c < dimension; c++) {
            resultado.asignar(f, c, at(f, c) * v);
        }
    }
    return resultado;
}

MatrizDok MatrizDok::operator-(MatrizDok m) {
    return (*this) + m * (-1);
}

string MatrizDok::imprimir() {
    string s;
    for (int f = 0; f < dimension; f++)
        for (int c = 0; c < dimension; c++) {
            s += to_string(at(f, c));
            s += c == dimension - 1 ? "\n" : " ";
        }
    return s;
}
