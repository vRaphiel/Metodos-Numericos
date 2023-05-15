#include "main.h"
#include <chrono>

using namespace std;
int N;
int M;

int main(int argc, char *argv[]) {

    auto start = std::chrono::system_clock::now();

    vector<link> links = leerArchivo(argv[1]);
    double p = atof(argv[2]);

    Matriz W = construirW(links);
    Matriz D = construirD(W);
    vector<double> e = vector<double>(N, 1);
    Matriz I = Matriz::identidad(N);
    Matriz coefs = I - W * D * p;

    vector<double> x = eliminacionGausseana(coefs, e, N);
    vector<double> xNormalizado = normalizar(x);

    imprimirResultado(p, xNormalizado, argv[1]);

    auto end = std::chrono::system_clock::now();

    cout << (end - start).count() << endl;
    return 0;
}

Matriz construirW(vector<link> &links) {
    Matriz W(N);
    for (link l: links) {
        W.asignar(l.second, l.first, 1);   // W[j][i]
    }
    return W;
}

Matriz construirD(Matriz &W) {
    Matriz D(N);
    // Fijamos [i] e iteramos sobre [j] -> W[j][*]
    for (int i = 0; i < N; i++) {
        int distintosDeCero = W.distintosDeCero(i);
        if (distintosDeCero != 0) {
            D.asignar(i, i, (1.0 / distintosDeCero));
        }
    }
    return D;
}

Matriz construirE() {
    Matriz E(N);
    for (int i = 0; i < N; i++) {
        E.asignar(i, 0, 1);
    }
    return E;
}

vector<double> normalizar(vector<double> &x) {
    vector<double> norm(N);
    double suma = 0;
    for (double i: x) suma += i;
    for (int i = 0; i < N; i++) {
        norm[i] = x[i] / suma;
    }
    return norm;
}

vector<link> leerArchivo(const string &directorio) {
    ifstream archivo(directorio);
    archivo >> N;
    archivo >> M;
    vector<link> links;
    for (int i = 0; i < M; i++) {
        int s, e;
        archivo >> s >> e;
        links.emplace_back(s - 1, e - 1);
    }
    return links;
}

void imprimirResultado(double p, vector<double> &x, const string &directorio) {
    ofstream output;
    output.open(directorio + ".out");
    output << p << endl;
    for (double i: x) {
        output << i << endl;
    }
    output.close();
}