#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <iomanip>

using namespace std;
using Matriz = vector<vector<double>>;

double productoEscalar(vector<double> &r1, vector<double> &r2);
pair<double, vector<double>> MetodoDeLaPotencia(Matriz &m, int iter, double tol);
vector<double> productoMatrizVector(Matriz &m, vector<double> &v);
vector<double> normalizarVector(vector<double> &v, double &norma);
double normaDeUnVector(vector<double> &v);
pair<vector<double>, Matriz> Deflacion(Matriz &A, int iteraciones, double tolerancia);
void reducirMatriz(Matriz &A, pair<double, vector<double>> tuplaPotencia);
Matriz leerArchivo(const string &directorio);
void imprimirResultado(const string &directorio, pair<vector<double>, Matriz> &tupla);
