#include "matriz.h"

bool esCero(double valor) {
    return -1e-5 < valor && valor < 1e-5;
}

Matriz::Matriz(int tam) {
    dimension = tam;
    A = vector<double>();
    JA = vector<int>();
    IA = vector<int>(dimension + 1, 0);
}

Matriz::Matriz(int dim, vector<double> &a, vector<int> &ja, vector<int> &ia) {
    dimension = dim;
    A = a;
    JA = ja;
    IA = ia;
}

double Matriz::at(int fila, int columna) const {
    int l = IA[fila];
    int r = IA[fila + 1] - 1;

    if (l > r) return 0;

    while (l <= r) {
        int m = (l + r) / 2;
        if (JA[m] == columna) return A[m];
        else if (JA[m] < columna) l = m + 1;
        else r = m - 1;
    }

    return 0;
}

void Matriz::asignar(int fila, int columna, double valor) {
    int startInd = IA[fila];
    int endInd = IA[fila + 1];

    if (esCero(valor)) {
        for (int i = startInd; i < endInd && JA[i] <= columna; i++) {
            if (JA[i] == columna) {
                JA.erase(JA.cbegin() + i);
                A.erase(A.cbegin() + i);
                for (int c = fila + 1; c <= dimension; c++) IA[c] -= 1;
                return;
            }
        }
    } else {
        auto aIter = A.begin() + startInd;
        auto jaIter = JA.begin() + startInd;
        auto jaEnd = JA.begin() + endInd;
        while (jaIter != jaEnd && *jaIter < columna) {
            aIter++;
            jaIter++;
        }
        if (jaIter == jaEnd || *jaIter > columna) { // habia un 0 en esa posicion
            A.insert(aIter, valor);
            JA.insert(jaIter, columna);
            for (int f = fila + 1; f <= dimension; f++) IA[f] += 1;
        } else {
            *aIter = valor;
        }
    }
}

int Matriz::distintosDeCero(int columna) {
    int tot = 0;
    for (auto i : JA) {
        if (i == columna) tot++;
    }
    return tot;
}

Matriz Matriz::operator+(Matriz m) {
    Matriz resultado = Matriz(dimension);
    for (int f = 0; f < dimension; f++) {
        for (int c = 0; c < dimension; c++) {
            resultado.asignar(f, c, at(f, c) + m.at(f, c));
        }
    }
    return resultado;
}

Matriz Matriz::operator*(Matriz m) {
    Matriz resultado = Matriz(dimension);
    int elementos = 0;
    for (int f = 0; f < dimension; f++) {
        resultado.IA[f] = elementos;
        for (int c = 0; c < dimension; c++) {
            double suma = 0;
            for (int i = IA[f]; i < IA[f + 1]; i++) {
                suma += A[i] * m.at(JA[i], c);
            }
            if (!esCero(suma)) {
                resultado.A.push_back(suma);
                resultado.JA.push_back(c);
                elementos++;
            }
        }
    }
    resultado.IA[dimension] = elementos;
    return resultado;
}

Matriz Matriz::operator*(double v) {
    Matriz resultado = Matriz(dimension);
    resultado.A = A;
    resultado.IA = IA;
    resultado.JA = JA;
    for(int i = 0; i < A.size(); i++) resultado.A[i] *= v;
    return resultado;
}

Matriz Matriz::operator-(Matriz m) {
    Matriz resultado = Matriz(dimension);
    for (int f = 0; f < dimension; f++) {
        for (int c = 0; c < dimension; c++) {
            resultado.asignar(f, c, at(f, c) - m.at(f, c));
        }
    }
    return resultado;
}

string Matriz::imprimir() {
    string s;
    for (int f = 0; f < dimension; f++)
        for (int c = 0; c < dimension; c++) {
            s += to_string(at(f, c));
            s += c == dimension - 1 ? "\n" : " ";
        }
    return s;
}
