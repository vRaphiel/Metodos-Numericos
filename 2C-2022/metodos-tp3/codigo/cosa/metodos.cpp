#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

/**
 * Matriz A : Matriz A
 * Vector b : Vector B
 * int reps : Rango
 * Vector x_inicial : Vector inicial
 * Vector x_directo : Vector directo
 * double eps : Error posible a cometer
*/
pair<VectorXd, VectorXd> Gauss_Seidel(Matriz A, VectorXd b, int rango, VectorXd x_inicial, VectorXd x_directo, double eps){
    Matriz D = extractDiag(A);

    VectorXd x_i = x_inicial;
    /*
    double error = 1;

    for(int i = 0; i < rango; i++){
        x_i = ;
        VectorXd actual = x_i;
        //diferencia = 0;
    }
    */
    return {x_i, x_i};
}

Matriz extractDiag(const Matriz &A){
    int n = A.cols();
    Matriz res(n, n);
    vector<T> coefficients;
    for (int i = 0; i < n; i++){
        coefficients.push_back(T(i, i, A.coeff(i, i)));
    }
    res.setFromTriplets(coefficients.begin(), coefficients.end());
    return res;
}