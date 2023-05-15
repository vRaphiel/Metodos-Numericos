#include "main.h"
#include <sstream>
#include <string>
using namespace std;

int iteraciones = 0;
double tolerancia = 0;

int main(int argc, char *argv[]) {
    Matriz A = leerArchivo(argv[1]);
    iteraciones = int(atoi(argv[2]));
    tolerancia = strtod(argv[3], NULL);
    pair<vector<double>, Matriz> tuplaResultado = Deflacion(A, iteraciones, tolerancia);
    imprimirResultado(argv[1], tuplaResultado);
    return 0;
}

pair<vector<double>, Matriz> Deflacion(Matriz &A, int iteraciones, double tolerancia){
    Matriz A_copy = A;
    vector<double> eigenvalues;
    Matriz eigenvectors;

    for(int i = 0; i < A.size(); i++){
        pair<double, vector<double>> tuplaPotencia = MetodoDeLaPotencia(A_copy, iteraciones, tolerancia);
        eigenvalues.push_back(tuplaPotencia.first);
        eigenvectors.push_back(tuplaPotencia.second);
        reducirMatriz(A_copy, tuplaPotencia);
    }
    return {eigenvalues, eigenvectors};
}

void reducirMatriz(Matriz &A, pair<double, vector<double>> tuplaPotencia){
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            A[i][j] = A[i][j] - (tuplaPotencia.first * tuplaPotencia.second[i] * tuplaPotencia.second[j]);
        }
    }
}

pair<double, vector<double>> MetodoDeLaPotencia(Matriz &A, int iteraciones, double tolerancia) {
    vector<double> eigenvector(A.size());
    for(int i = 0; i < eigenvector.size(); i++){
        eigenvector[i] = ((double) rand() / (RAND_MAX));
    }

    double norma_b = normaDeUnVector(eigenvector);
    eigenvector = normalizarVector(eigenvector, norma_b); // eigenvector <- eigenvector / ||eigenvector||

    for(int i = 0; i < iteraciones; i++){
        vector<double> old_eigenvector = eigenvector;
        eigenvector = productoMatrizVector(A, eigenvector);
        double norma = normaDeUnVector(eigenvector);
        eigenvector = normalizarVector(eigenvector, norma);
        // Hasta aca coincidimos
        double cos_angle = productoEscalar(eigenvector, old_eigenvector);
        double diff = double(1) - tolerancia;
        if (diff < cos_angle && cos_angle <= 1)
        {
            cout << "Llegue hasta aca" << endl;
            break;
        }
    }
    vector<double> Av = productoMatrizVector(A, eigenvector);
    
    double eigenvalue = productoEscalar(eigenvector, Av);

    return {eigenvalue, eigenvector};
}

/**
 * in r1: Vector<double>
 * in r2: Vector<double>
 * Devuelve el producto escalar de los vectores r1 y r2
*/
double productoEscalar(vector<double> &r1, vector<double> &r2){
    double aux = 0;
    for(int i = 0; i < r1.size(); i++){
        aux += r1[i] * r2[i];
    }
    return aux;
}

/**
 * in M: Matriz<double>
 * in v: Vector<double>
 * Devuelve un Vector<double> resultado del producto M * v
*/

vector<double> productoMatrizVector(Matriz &M, vector<double> &v){
    vector<double> res;
    for(int i = 0; i < M.size(); i++){
        double vi = 0;
        for(int j = 0; j < M.size(); j++){
            vi += M[i][j] * v[j];
        }
        res.emplace_back(vi);
    }
    return res;
}

/**
 * in v: Vector<double>
 * in norma: double
 * Devuelve el vector normalizado
*/
vector<double> normalizarVector(vector<double> &v, double &norma){
    vector<double> v_aux;
    for(int i = 0; i < v.size(); i++){
        v_aux.emplace_back(v[i] / norma);
    }
    return v_aux;
}

/**
 * in v: Vector<double>
 * Devuelve la norma 2 de un vector. Esto es la raiz cuadrada del cuadrado de los valores del vector
 */
double normaDeUnVector(vector<double> &v) {
    double norma = 0;
    for(int i = 0; i < v.size(); i++){
        norma += v[i] * v[i];
    }
    return sqrt(norma);
}

void imprimirResultado(const string &directorio, pair<vector<double>, Matriz> &tupla){
    ofstream output_eigenvalue;
    output_eigenvalue.open(directorio + "-autovalores.out");
    for (double i : tupla.first) {
        output_eigenvalue << i << endl;
    }
    output_eigenvalue.close();

    ofstream output_eigenvector;
    output_eigenvector.open(directorio + "-autovectores.out");
    for(int i = 0; i < tupla.second.size(); i++){
        for(int j = 0; j < tupla.second[i].size(); j++){
            output_eigenvector << tupla.second[j][i] << " ";
        }
        output_eigenvector << "\n";
    }
    output_eigenvector.close();
}

Matriz leerArchivo(const string &directorio) {
    ifstream archivo(directorio);
    Matriz A;
    string line;
    while(getline(archivo, line, '\n')){
        vector<double> tempVec;
        istringstream ss(line);
        double word;
        while(ss >> word){
            tempVec.push_back(word);
        }
        A.push_back(tempVec);
    }
    return A;
}