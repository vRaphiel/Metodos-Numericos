#include "matriz.h"
#include "matrizlil.h"
#include <map>

using namespace std;

//MatrizLil::MatrizLil(Matriz m) {
//    dimension = m.dimension;
//    _rep = vector<vector<pair<int, double>>>(dimension, vector<pair<int, double>>());
//    for (int f = 0; f < dimension; f++) {
//        for (int i = m.IA[f]; i < m.IA[f + 1]; i++) {
//            _rep[i].push_back({ m.JA[i], m.A[i] });
//        }
//    }
//}

Matriz MatrizLil::aCsr() {
    int elementos = 0;
    vector<int> IA = { 0 };
    vector<int> JA;
    vector<double> A;
    for (auto f : _rep) {
        for (auto i : f) {
            JA.push_back(i.first);
            A.push_back(i.second);
            elementos++;
        }
        IA.push_back(elementos);
    }
    return { dimension, A, JA, IA };
}

MatrizLil::MatrizLil(vector<list<pair<int, double>>> lil, int dim) {
    _rep = lil;
    dimension = dim;
}
