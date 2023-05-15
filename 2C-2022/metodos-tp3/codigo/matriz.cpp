#include <chrono>
#include <iostream>
#include "matriz.h"

using namespace std;
using namespace chrono;

//VectorXd eliminacionGausseana(Matriz &matriz, VectorXd &b, int N) {
//    pair<Matriz, VectorXd> tuplaTriangular = triangularMatriz(matriz, b, N);
//    Matriz matrizTriangulada = tuplaTriangular.first;
//    VectorXd nuevaB = tuplaTriangular.second;
//    return backwardSubstitution(matrizTriangulada, nuevaB, N);
//}

//pair<Matriz, VectorXd> triangularMatriz(Matriz &coefs, VectorXd &b, int N) {
//    Matriz triangulada = coefs;
//    VectorXd bPrima = b;
//    auto s = std::chrono::high_resolution_clock::now();
//    for(int p = 0; p < N - 1; p++) {
//        Matriz::InnerIterator itP(triangulada, p);
//        for (int f = p + 1; f < N; f++){
//            Matriz::InnerIterator itF(triangulada, f);
//            cout << itF.col() << endl;
//            if(itF.col() == p){
//                double factor = itF.value() / itP.value();
//                for(; itP; ++itP){
//                    while (itF.col() < N && itF.col() < itP.col()) ++itF;
//                    int columnaModificada = itP.col();
//                    double valorPrevio = 0; 
//                    if(itF.col() == itP.col()){
//                        valorPrevio = itF.value();
//                        triangulada.prune(itF.row(), itF.col());
//                        //triangulada.coeffRef(itF.row(), itF.col()) = 0.0;
//                    }
//                    double valor = valorPrevio - factor * itP.value();
//                    if (!esCero(valor)) {
//                        triangulada.coeffRef(itF.row(), itF.col()) = valor;
//                    }
//                }
//                bPrima[f] -= factor * bPrima[p];
//            }
//        }
//    }
//    cout << "tot " << to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - s).count()) << endl;
//    return {triangulada, bPrima};
//}

//VectorXd backwardSubstitution(Matriz &m, VectorXd &b, int N) {
//    VectorXd coef_x(N, 0);
//    for (int i = N - 1; i >= 0; i--) {
//        double b_i = b[i];
//        double sum = 0;
//        for (int j = i + 1; j <= N - 1; j++) {
//            sum += m.coeff(i, j) * coef_x[j];
//        }
//        double x_i = (b_i - sum) / m.coeff(i, i);
//        coef_x[i] = x_i;
//    }
//    return b;
//}

bool esCero(double valor) {
    return -1e-5 < valor && valor < 1e-5;
}

/**
 * Matriz A : Matriz A
 * Vector b : Vector B
 * int reps : Rango
 * Vector x_inicial : Vector inicial
 * Vector x_directo : Vector directo
 * double eps : Error posible a cometer
 *
 * Return: Vector X_I solución y Vector Error de errores cometidos
 */
pair<VectorXd, VectorXd> metodo_Gauss_Seidel(Matriz A, VectorXd b, int rango, VectorXd x_inicial, VectorXd x_directo, double eps) {
    int N = A.cols();
    // Busco las triangulares superiores e inferiores
    Matriz TS = A.triangularView<UpLoType::Upper>();
    Matriz TI = A.triangularView<UpLoType::Lower>();

    // Busco D, L, U
    Matriz D = TS.triangularView<UpLoType::Lower>();
    Matriz L = (-1) * TI + D;
    Matriz U = (-1) * TS + D;

    // Matriz identidad
    Matriz I(N, N);
    I.setIdentity();

    Matriz DL = D - L;
    // Buscamos la inversa
    SimplicialLLT<Matriz> solver;
    DL.makeCompressed();
    solver.compute(DL);
    Matriz DL_inversa = solver.solve(DL);

    // Calculo el T y el C
    Matriz T = DL_inversa * U;
    VectorXd c = DL_inversa * b;

    // Defino el vector x_i
    VectorXd x_i = x_inicial;

    // Defino el vector donde guardaré los errores
    VectorXd x_error(rango);
    double error = 1;

    VectorXd anterior = x_inicial;
    for (int i = 0; i < rango; i++) {
        x_i = (T * x_i) + c;
        VectorXd actual = x_i;
        double diferencia = (anterior - actual).norm();
        anterior = actual;
        if(isinf(diferencia)){
            x_error[i] = 0;
        } else {
            x_error[i] = (x_i - x_directo).norm();
        }
        if (diferencia < eps) {
            break;
        }
    }

    return make_pair(x_i, x_error);
}

/**
 * Matriz A : Matriz A
 * Vector b : Vector B
 * int reps : Rango
 * Vector x_inicial : Vector inicial
 * Vector x_directo : Vector directo
 * double eps : Error posible a cometer
 * 
 * Return: Vector X_I solución y Vector Error de errores cometidos
 */
pair<VectorXd, VectorXd> metodo_Jacobi(Matriz A, VectorXd b, int rango, VectorXd x_inicial, VectorXd x_directo, double eps) {
    int N = A.cols();
    // Busco las triangulares superiores e inferiores
    Matriz TS = A.triangularView<UpLoType::Upper>();
    Matriz TI = A.triangularView<UpLoType::Lower>();

    // Busco D, L, U
    Matriz D = TS.triangularView<UpLoType::Lower>();
    Matriz L = (-1)*TI + D;
    Matriz U = (-1)*TS + D;

    // Matriz identidad
    Matriz I(N, N);
    I.setIdentity();

    // Buscamos la inversa
    SimplicialLLT<Matriz> solver;
    D.makeCompressed();
    solver.compute(D);
    Matriz D_inversa = solver.solve(I);

    // Calculo el T y el C
    Matriz T = D_inversa * (L + U);
    VectorXd c = D_inversa * b;

    // Defino el vector x_i
    VectorXd x_i = x_inicial;

    // Defino el vector donde guardaré los errores
    VectorXd x_error(rango);
    double error = 1;

    VectorXd anterior = x_inicial;
    for(int i = 0; i < rango; i++){
        x_i = (T * x_i) + c;
        VectorXd actual = x_i;
        double diferencia = (anterior - actual).norm();
        anterior = actual;
        if (isinf(diferencia)) {
            x_error[i] = 0;
        } else {
            x_error[i] = (x_i - x_directo).norm();
        }
        if(diferencia < eps){
            break;
        }
    }

    return make_pair(x_i, x_error);
}

VectorXd generarVectorUnos(int n) {
    VectorXd aux(n);
    for (int i = 0; i < n; i++) {
        aux[i] = 1.0;
    }
    return aux;
}

Matriz construirD(Matriz &W, int N) {
    Matriz D(N, N);
    for (int i = 0; i < N; i++) {
        int distintosDeCero = distintosCeroRow(W, i);
        if (distintosDeCero != 0) {
            D.insert(i, i) = (1.0 / distintosDeCero);
        }
    }
    return D;
}

int distintosCeroRow(Matriz &A, int fila){
    int cant = 0;
    for(int columna = 0; columna < A.cols(); columna++){
        int valor = A.coeff(fila, columna);
        if(valor != 0){
            cant++;
        }
    }
    return cant;
}

VectorXd generarVectorAleatorio(int n){
    VectorXd aux(n);
    for (int i = 0; i < n; i++) {
        aux[i] = rand() % 20 + 1;
    }
    return aux;
}

Matriz construirMatrizCoeficientes(Matriz W, int N, int M, double p){
    Matriz I(W.cols(), W.cols());
    I.setIdentity();
    Matriz D = construirD(W, N);
    Matriz WDp = W * D * p;
    Matriz coefs = I - WDp;
    return coefs;
}

VectorXd normalizar(VectorXd &x, int N) {
    VectorXd norm(N);
    double suma = 0;
    for (double i : x)
        suma += i;

    for (int i = 0; i < N; i++){
        norm[i] = x[i] / suma;
    }
    return norm;
}
