#include "main.h"

#include <eigen3/Eigen/Dense>
#include <fstream>
#include <iostream>

using namespace std;
#define MAXBUFSIZE ((int)1e6)

// Instalacion de eigen: sudo apt-get install libeigen3-dev
// Atencion: compilar con flag '-O3' para optimizar tiempos de ejecucion

// TODO: analizar conveniencia de uso de punteros/referencias

tuple<double, Eigen::VectorXd> potencia(const Eigen::MatrixXd &a, long iteraciones, double epsilon)
{
    // cout << "a =\n" << a << "\n" << endl;

    // Vector inicial aleatorio. TODO: revisar por que devuelve siempre el mismo
    Eigen::VectorXd v = Eigen::VectorXd::Random(a.rows());
    v.setRandom();

    for(int i = 0; i < v.size(); i++) {
        if(v(i) < 0) {
            v(i) = (-1)*v(i);
        }
    }

    Eigen::VectorXd prev_v = v;

    for (int it = 0; it < iteraciones; it++) {
        v = (a * prev_v);
        v = v / v.norm();

        if ((v - prev_v).norm() < epsilon) {  // Norma 2 entre el v actual y el previo
            //cout << "Corto en la iteracion " << it << endl;
            break;
        }

        prev_v = v;
    }

    // Calculo el autovalor asociado al autovector hallado
    double autovalor_num = v.transpose() * a * v;
    double autovalor_denom = v.transpose() * v;
    double autovalor = autovalor_num / autovalor_denom;

    // cout << "autovalor = " << autovalor << "\n" << endl;
    // cout << "autovector =\n" << v << "\n" << endl;

    return make_tuple(autovalor, v);
}

Eigen::MatrixXd deflacion(const Eigen::MatrixXd &a, const Eigen::VectorXd &autovector, double autovalor)
{
    Eigen::MatrixXd result(a.rows(), a.cols());
    result = a - autovalor * autovector * autovector.transpose();

    return result;
}

tuple<Eigen::VectorXd, Eigen::MatrixXd> eigen(Eigen::MatrixXd a, long iteraciones, double epsilon)
{
    Eigen::MatrixXd result_autovectores(a.rows(), a.cols());
    Eigen::VectorXd result_autovalores(a.rows());

    double autovalor_actual;
    Eigen::VectorXd autovector_actual;

    // Itero cantidad de filas veces
    for (int i = 0; i < a.rows(); ++i) {
        // A partir de la segunda iteracion, aplico deflacion
        if (i > 0)
            a = deflacion(a, autovector_actual, autovalor_actual);

        // Busco i-esimo autovector y autovalor
        tie(autovalor_actual, autovector_actual) = potencia(a, iteraciones, epsilon);

        // Los appendeo al resultado
        result_autovalores(i) = autovalor_actual;
        result_autovectores.col(i) = autovector_actual;
    }

    return make_tuple(result_autovalores, result_autovectores);
}

void imprimirResultado(const string &directorio, Eigen::VectorXd &autovalores, Eigen::MatrixXd &autovectores)
{
    ofstream output_eigenvalue;
    output_eigenvalue.open(directorio + "-autovalores.out");
    for (double i : autovalores) {
        output_eigenvalue << i << " ";
    }
    output_eigenvalue << endl;
    output_eigenvalue.close();

    ofstream output_eigenvector;
    output_eigenvector.open(directorio + "-autovectores.out");
    // Eigen::IOFormat HeavyFmt(5, 0, ", ", ";\n", "[", "]", "[", "]");
    // cout << autovectores.format(HeavyFmt) << endl;
    for (int i = 0; i < autovectores.rows(); i++) {
        for (int j = 0; j < autovectores.rows(); j++) {
            output_eigenvector << autovectores(i, j) << " ";
        }
        output_eigenvector << endl;
    }
    output_eigenvector << endl;

    output_eigenvector.close();
}

Eigen::MatrixXd leerArchivo(const char *filename)
{
    int cols = 0, rows = 0;
    double buff[MAXBUFSIZE];

    ifstream file;
    file.open(filename);
    while (!file.eof()) {
        string line;
        getline(file, line);

        int temp_cols = 0;
        stringstream stream(line);
        while (!stream.eof()) {
            stream >> buff[cols * rows + temp_cols++];
            stream >> std::ws;
        }

        if (temp_cols == 0)
            continue;

        if (cols == 0)
            cols = temp_cols;

        rows++;
    }

    file.close();
    rows--;

    Eigen::MatrixXd result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result(i, j) = buff[cols * i + j];

    return result;
};

int main(int argc, char const *argv[])
{
    Eigen::MatrixXd A = leerArchivo(argv[1]);

    long iteraciones = long(atoi(argv[2]));
    double epsilon = strtod(argv[3], NULL);

    // Busco autovectores y autovalores
    Eigen::MatrixXd autovectores;
    Eigen::VectorXd autovalores;

    tie(autovalores, autovectores) = eigen(A, iteraciones, epsilon);

    imprimirResultado(argv[1], autovalores, autovectores);

    return 0;
}
