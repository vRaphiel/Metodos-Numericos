#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include "matriz.h"

using namespace std;

vector<T> leerArchivo(const string &directorio);
void imprimirResultado(VectorXd &x, const string &directorio, const string &exp);