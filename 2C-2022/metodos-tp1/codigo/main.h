#include "eliminacionGausseana.h"
#include "matriz.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> link;

Matriz construirW(vector<link> &links);

Matriz construirD(Matriz &W);

vector<double> normalizar(vector<double> &x);

void imprimirResultado(double p, vector<double> &x, const string &directorio);

vector<link> leerArchivo(const string &directorio);