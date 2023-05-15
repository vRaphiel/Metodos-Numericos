#ifndef CODIGO_MATRIZ_H
#define CODIGO_MATRIZ_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <Eigen/Sparse>
#include <iostream>

using namespace std;
using namespace Eigen;
using Eigen::VectorXd;
using Eigen::DecompositionOptions;

typedef SparseMatrix<double> Matriz;
typedef Triplet<double> T;
typedef pair<int, int> link;

//VectorXd eliminacionGausseana(Matriz &coefs, VectorXd &b, int N);
//VectorXd backwardSubstitution(Matriz &m, VectorXd &b, int N);

pair<VectorXd, VectorXd> metodo_Gauss_Seidel(Matriz A, VectorXd b, int rango, VectorXd x_inicial, VectorXd x_directo, double eps);
pair<VectorXd, VectorXd> metodo_Jacobi(Matriz A, VectorXd b, int rango, VectorXd x_inicial, VectorXd x_directo, double eps);
//pair<Matriz, VectorXd> triangularMatriz(Matriz &matriz, VectorXd &b, int N);

Matriz extractDiag(const Matriz &A);
Matriz construirMatrizCoeficientes(Matriz W, int N, int M, double p);
Matriz construirD(Matriz & W, int N);

VectorXd generarVectorUnos(int n);
VectorXd generarVectorAleatorio(int n);
VectorXd normalizar(VectorXd &x, int N);

int distintosCeroRow(Matriz &A, int fila);
bool esCero(double valor);
#endif //CODIGO_MATRIZ_H
