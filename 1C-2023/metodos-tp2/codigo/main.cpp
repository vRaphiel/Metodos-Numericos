#include "main.h"

using namespace std;
double tope = 1e-310;

int main(int argc, char *argv[]){
    MatrizMP A = leerArchivo(argv[1]);
    int iteraciones = int(atoi(argv[2]));
    double tolerancia = strtod(argv[3], NULL);
    pair<VectorMP, MatrizMP> res = Deflacion(A, iteraciones, tolerancia);
    imprimirResultado(argv[1], res);
    return 0;
}

pair<VectorMP, MatrizMP> Deflacion(MatrizMP &A, int iter, double tol){
    MatrizMP A_copy = A;
    VectorMP eigenvalues(A.rows());
    MatrizMP eigenvectors(A.rows(), A.rows());
    double last_eigenvalue = 0;
    for(int i = 0; i < A.rows(); i++){
        pair<double, VectorMP> tupla = MetodoDeLaPotencia(A_copy, iter, tol);
        cout << "Obtenido autovalor: " << i << endl;
        eigenvalues(i) = tupla.first;
        eigenvectors.row(i) = tupla.second;
        ReducirMatriz(A_copy, tupla);
    }
    return make_pair(eigenvalues, eigenvectors);
}

void ReducirMatriz(MatrizMP &A, pair<double, VectorMP> tuplaPotencia){
    for(int i = 0; i < A.rows(); i++){
        for(int j = 0; j < A.rows(); j++){
            A(i,j) = A(i,j) - (tuplaPotencia.first * tuplaPotencia.second(i) * tuplaPotencia.second(j)); 
        }
    }
}

pair<double, VectorMP> MetodoDeLaPotencia(MatrizMP &A, int iter, double tol){
    VectorMP vec = VectorMP::Random(A.rows());
    for(int i = 0; i < vec.size(); i++) {
        if(vec(i) < 0) {
            vec(i) = (-1)*vec(i);
        }
    }

    vec.normalize();
    for(int i = 0; i < iter; i++){
        VectorMP oldVector = vec;
        vec = A*vec;
        vec.normalize();
        double cos_angle = oldVector.transpose()*vec;
        double diff = double(1) - tol;
        if (diff < cos_angle && cos_angle <= 1){
            break;
        }
    }
    double eigenvalue = vec.transpose()*A*vec;
    return make_pair(eigenvalue, vec);
}

void imprimirResultado(const string &directorio, pair<VectorMP, MatrizMP> &tupla) {
    ofstream output_eigenvalue;
    output_eigenvalue.open(directorio + "-autovalores.out");
    for (double i : tupla.first) {
        output_eigenvalue << i << " ";
    }
    output_eigenvalue << endl;
    output_eigenvalue.close();

    ofstream output_eigenvector;
    output_eigenvector.open(directorio + "-autovectores.out");
    //Eigen::IOFormat HeavyFmt(5, 0, ", ", ";\n", "[", "]", "[", "]");
    //cout << tupla.second.format(HeavyFmt) << endl;
    for (int i = 0; i < tupla.second.rows(); i++) {
        for (int j = 0; j < tupla.second.rows(); j++) {
            output_eigenvector << tupla.second(i,j) << " ";
        }
        output_eigenvector << endl;
    }
    output_eigenvector << endl;
    
    output_eigenvector.close();
}

MatrizMP leerArchivo(const string &directorio) {
    ifstream fin(directorio);
    int nvalue;
    fin >> nvalue;

    MatrizMP A(nvalue, nvalue);

    for (int i = 0; i < nvalue; i++){
        for (int j = 0; j < nvalue; j++) {
            fin >> A(i, j);
        }
    }

    return A;
}