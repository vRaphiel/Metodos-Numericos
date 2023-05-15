#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

pair<VectorXd, VectorXd> Gauss_Seidel(Matriz A, VectorXd b, int rango, VectorXd x_inicial, VectorXd x_directo, double eps);
Matriz extractDiag(const Matriz &A);