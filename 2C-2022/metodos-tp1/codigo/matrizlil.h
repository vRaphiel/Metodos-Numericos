#ifndef CODIGO_MATRIZLIL_H
#define CODIGO_MATRIZLIL_H

#include "matriz.h"
#include <map>
#include <vector>
#include <list>

using namespace std;

struct MatrizLil {

    MatrizLil(vector<list<pair<int, double>>> lil, int dim);

    int dimension;

    Matriz aCsr();

private:
    vector<list<pair<int, double>>> _rep;

    string imprimir();
};

#endif
