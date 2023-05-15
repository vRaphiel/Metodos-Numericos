#ifndef METODOS_TP1_ENLAZADA_H
#define METODOS_TP1_ENLAZADA_H



#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Enlazada {

     struct Columna {
    public:

        Columna* anterior;
        Columna* siguiente;
        int posicion;
        double valor;
    };
    
    Enlazada(int dimension);
    void asignar(int fila, int columna, double valor);
    double at(int fila, int columna) const;
    vector<double> eliminacionGausseana(vector<double> &b);
    vector<double> backwardSubstitution(vector<double> &b);
    void insertar(int fila, Columna* col_j, Columna* col_i, double valor, int lado);
    void borrar(int fila, Columna* col_j);

private:
    vector<Columna*> _matriz;
    int _dimension;
};

bool esCero(double valor);

#endif //METODOS_TP1_ENLAZADA_H
