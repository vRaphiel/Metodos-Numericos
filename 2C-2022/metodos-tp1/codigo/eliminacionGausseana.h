#ifndef CODIGO_ELIMINACIONGAUSSEANA_H
#define CODIGO_ELIMINACIONGAUSSEANA_H

#include "matriz.h"
#include <vector>
using namespace std;

vector<double> eliminacionGausseana(Matriz& coefs, vector<double> &b, int N);
pair<Matriz, vector<double>> convertirEnTriangular(Matriz& coefs, vector<double>& b, int N);
vector<double> backwardSubstitution(Matriz& m, vector<double>& b, int N);

#endif //CODIGO_ELIMINACIONGAUSSEANA_H
