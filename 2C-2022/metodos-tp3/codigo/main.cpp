#include <Eigen/Sparse>
#include <vector>
#include <iostream>
#include "main.h"

using namespace std;

int N;
int M;

// Parametros: Matriz.txt, iteraciones, probabilidad
int main(int argc, char *argv[]) {

    string route = argv[1];
    vector<T> links = leerArchivo(route);
    int iteraciones = atoi(argv[2]);
    double p = 0.50;

    Matriz W(N, N);
    W.setFromTriplets(links.begin(), links.end());
    // W es la matriz inicial

    Matriz coefs = construirMatrizCoeficientes(W, N, M, p);
    VectorXd b = generarVectorUnos(coefs.cols());
    VectorXd x_inicial = generarVectorAleatorio(coefs.cols());
    VectorXd x_directo;
    VectorXd res_gauss;
    VectorXd e = generarVectorUnos(N);

    pair<VectorXd, VectorXd> res_jacobi;
    pair<VectorXd, VectorXd> res_seidel;

    // Evaluación de Gauss
    auto start = std::chrono::system_clock::now();

    // Si alcanza el tiempo pasarlo a punteros de listas usando el codigod el TP1 que está comentado en matriz.cpp
    SparseLU<Matriz, COLAMDOrdering<int>> solver;
    solver.analyzePattern(coefs);
    solver.factorize(coefs);
    x_directo = solver.solve(b);
    x_directo = normalizar(x_directo, coefs.cols());
    auto end = std::chrono::system_clock::now();
    res_gauss = x_directo;
    cout << (end - start).count() << endl;

    imprimirResultado(res_gauss, "./resultados/gauss_res", route);
    VectorXd tiempo(1);
    tiempo[0] = (end - start).count();
    imprimirResultado(tiempo, "./resultados/gauss_tiempo", route);

    // Evaluación de Jacobi
    start = std::chrono::system_clock::now();
    res_jacobi = metodo_Jacobi(W, b, iteraciones, x_inicial, x_directo, p);
    end = std::chrono::system_clock::now();
    cout << (end - start).count() << endl;

    imprimirResultado(res_jacobi.first, "./resultados/jacobi_res", route);
    imprimirResultado(res_jacobi.second, "./resultados/jacobi_error", route);
    tiempo[0] = (end - start).count();
    imprimirResultado(tiempo, "./resultados/jacobi_tiempo", route);

    // Evaluación de Gauss_Seidel
    start = std::chrono::system_clock::now();
    res_seidel = metodo_Gauss_Seidel(W, b, iteraciones, x_inicial, x_directo, p);
    end = std::chrono::system_clock::now();
    cout << (end - start).count() << endl;
    
    imprimirResultado(res_seidel.first, "./resultados/gauss_seidel_res", route);
    imprimirResultado(res_seidel.second, "./resultados/gauss_seidel_error", route);
    tiempo[0] = (end - start).count();
    imprimirResultado(tiempo, "./resultados/gauss_seidel_tiempo", route);

    return 0;
}

vector<T> leerArchivo(const string &directorio) {
    ifstream archivo(directorio);
    archivo >> N;
    archivo >> M;
    vector<T> links;
    links.reserve(3*M);
    for (int i = 0; i < M; i++) {
        int s, e;
        archivo >> s >> e;
        links.push_back(T(e-1, s-1, 1));
    }
    return links;
}

void imprimirResultado(VectorXd &x, const string &directorio, const string &exp) {
    ofstream output;
    output.open(directorio + ".out");
    for (double i : x) {
        output << i << endl;
    }
    output.close();
}