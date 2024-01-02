#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <eigen3/Eigen/Dense>

using namespace std;

typedef Eigen::MatrixXd MatrizMP;
typedef Eigen::VectorXd VectorMP;

pair<VectorMP, MatrizMP> Deflacion(MatrizMP &A, int iter, double tol);
pair<double, VectorMP> MetodoDeLaPotencia(MatrizMP &A, int iter, double tol);
void ReducirMatriz(MatrizMP &A, pair<double, VectorMP> tuplaPotencia);
MatrizMP leerArchivo(const string &directorio);
void imprimirResultado(const string &directorio, pair<VectorMP, MatrizMP> &tupla);
