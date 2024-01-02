#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <tuple>
#include <cstdlib>

using namespace std;

typedef Eigen::MatrixXd MatrizMP;
typedef Eigen::VectorXd VectorMP;
typedef vector<float> Errores;

tuple<VectorMP, Errores> JacobiSumatoria(MatrizMP &A, VectorMP &b, VectorMP &x, string v0);
tuple<VectorMP, Errores> JacobiMatricial(MatrizMP &A, VectorMP &b, VectorMP &x, string v0);
tuple<VectorMP, Errores> GSSumatoria(MatrizMP &A, VectorMP &b, VectorMP &x, string v0);
tuple<VectorMP, Errores> GSMatricial(MatrizMP &A, VectorMP &b, VectorMP &x, string v0);
VectorMP SolveLU(MatrizMP &A, VectorMP &b);

MatrizMP leerArchivo(const string &directorio);
VectorMP leerVector(const string &directorio);
void imprimirResultado(VectorMP &x, const string &directorio);
void imprimirErrores(Errores &x, const string &directorio);