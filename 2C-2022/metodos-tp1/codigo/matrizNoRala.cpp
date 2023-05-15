#include "matrizNoRala.h"

Matriz Matriz::operator*(Matriz m) {
    vector<Fila> filas;
    for (Matriz::Fila filaIzq: _filas) {
        vector<double> nuevaFila;
        for (Matriz::Columna columnaDer: m.columnas()) {
            double suma = 0;
            for (int i = 0; i < filaIzq.size(); i++) {
                suma += filaIzq[i] * columnaDer[i];
            }
            nuevaFila.emplace_back(suma);
        }
        filas.emplace_back(nuevaFila);
    }

    return {filas};
}

Matriz Matriz::operator*(double v) {
    vector<Fila> filas;
    for (Matriz::Fila fila: _filas) {
        vector<double> nuevaFila;
        for (double d: fila) {
            nuevaFila.emplace_back(d * v);
        }
        filas.emplace_back(Fila(nuevaFila));
    }
    return {filas};
}

Matriz Matriz::operator+(Matriz m) {
    vector<Fila> filas;
    for (int f = 0; f < _filas.size(); f++) {
        vector<double> nuevaFila;
        for (int c = 0; c < columnas().size(); c++) {
            double suma = (*this)[f][c] + m[f][c];
            nuevaFila.emplace_back(suma);
        }
        filas.emplace_back(nuevaFila);
    }

    return {filas};
}

int Matriz::distintosDeCero(int columna) {
    Columna col = columnas()[columna];
    int total = 0;
    for (double d: col) {
        if (-1e-5 > d || 1e-5 < d) total++;
    }

    return total;
}

vector<Matriz::Columna> Matriz::columnas() {
    vector<Columna> columnas;
    for (int i = 0; i < _filas[0].size(); i++) {
        vector<double> col;
        for (Fila f: _filas) {
            col.emplace_back(f[i]);
        }
        columnas.emplace_back(Columna(col));
    }

    return columnas;
}

Matriz Matriz::operator-(Matriz m) {
    return (*this) + m * (-1);
}

Matriz::Matriz(vector<Fila> filas) {
    _filas = filas;
}

Matriz::Matriz(int tam) {
    for (int i = 0; i < tam; i++) {
        _filas.emplace_back(Fila(vector<double>(tam, 0)));
    }
}

Matriz::Fila::Fila(vector<double> elementos) {
    _elementos = elementos;
}

Matriz::Columna::Columna(vector<double> elementos) {
    _elementos = elementos;
}

double &Matriz::Columna::operator[](int fila) {
    return _elementos[fila];
}

Matriz::Fila &Matriz::operator[](int fila) {
    return _filas[fila];
}

double &Matriz::Fila::operator[](int columna) {
    return _elementos[columna];
}

int Matriz::Fila::size() {
    return _elementos.size();
}

vector<double>::iterator Matriz::Fila::begin() {
    return _elementos.begin();
}

vector<double>::iterator Matriz::Fila::end() {
    return _elementos.end();
}

vector<double>::iterator Matriz::Columna::begin() {
    return _elementos.begin();
}

vector<double>::iterator Matriz::Columna::end() {
    return _elementos.end();
}
