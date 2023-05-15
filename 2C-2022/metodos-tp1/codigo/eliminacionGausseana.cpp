#include <chrono>
#include <iostream>
#include <list>
#include "eliminacionGausseana.h"
#include "matrizlil.h"

using namespace std;
using namespace chrono;

string imprimir(vector<list<pair<int, double>>> m, int N) {
    string s;
    for (auto i : m) {
        int prev = 0;
        auto j = i.begin();
        for (; j != i.end(); j++){
            for (; prev < j->first; prev++) {
                s += " " + to_string(0) + ".000000 ";
            }
            s += (j->second >= 0.0 ? " " : "") + to_string(j->second) + " ";
            prev++;
        }
        for (; prev < N; prev++) s += " " + to_string(0) + ".000000 ";
        s += "\n";
    }
    return s;
}

vector<double> eliminacionGausseana(Matriz &coefs, vector<double> &b, int N) {
    pair<Matriz, vector<double>> triangularExtendida = convertirEnTriangular(coefs, b, N);
    Matriz triangular = triangularExtendida.first;
    vector<double> nuevaB = triangularExtendida.second;
    return backwardSubstitution(triangular, nuevaB, N);
}

pair<Matriz, vector<double>> convertirEnTriangular(Matriz &coefs, vector<double> &b, int N) {
    vector<list<pair<int, double>>> triangular(N, list<pair<int, double>>());
    for (int i = 0; i < N; i++) {
        for(int j = coefs.IA[i]; j < coefs.IA[i+1]; j++) {
            triangular[i].push_back({coefs.JA[j], coefs.A[j]});
        }
    }
    vector<double> bPrima = b;
    auto s = std::chrono::high_resolution_clock::now();
    for (int p = 0; p < N - 1; p++) {
        auto filaP = triangular[p];
        for (int f = p + 1; f < N; f++) {
            auto pFilaF = &triangular[f];
            auto itFilaF = pFilaF->begin();
            auto itFilaP = filaP.begin();
            if (itFilaF->first == p) {
                double factor = itFilaF->second / itFilaP->second;
                for (; itFilaP != filaP.end(); itFilaP++) {
                    while (itFilaF != pFilaF->end() && itFilaF->first < itFilaP->first) itFilaF++;
                    int columnaModificada = itFilaP->first;
                    double valorPrevio = 0;
                    if (itFilaF != pFilaF->end() && itFilaF->first == itFilaP->first) {
                        valorPrevio = itFilaF->second;
                        itFilaF = pFilaF->erase(itFilaF);
                    }
                    double valor = valorPrevio - factor * itFilaP->second;
                    if(!esCero(valor))
                        pFilaF->insert(itFilaF, { columnaModificada, valor });
                }

                bPrima[f] -= factor * bPrima.at(p);
            }
        }
        /* cout << p << endl;
        cout << imprimir(triangular, N) << endl; */
    }
    cout << "tot " << to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()-s).count()) << endl;

    return {MatrizLil(triangular, N).aCsr(), bPrima};
}

vector<double> backwardSubstitution(Matriz &m, vector<double> &b, int N) {
    vector<double> coef_x(N, 0);
    for (int i = N - 1; i >= 0; i--) {
        double b_i = b.at(i);
        double sum = 0;
        for (int j = i + 1; j <= N - 1; j++) {
            sum += m.at(i, j) * coef_x[j];
        }
        double x_i = (b_i - sum) / m.at(i, i);
        coef_x[i] = x_i;
    }
    return coef_x;
}