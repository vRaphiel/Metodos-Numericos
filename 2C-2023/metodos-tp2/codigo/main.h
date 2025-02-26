#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace std;

tuple<double, Eigen::VectorXd> potencia(const Eigen::MatrixXd& a, long iteraciones, double epsilon);
Eigen::MatrixXd deflacion(const Eigen::MatrixXd& a, const Eigen::VectorXd& autovector, double autovalor);
tuple<Eigen::VectorXd, Eigen::MatrixXd> eigen(Eigen::MatrixXd a, long iteraciones, double epsilon);
Eigen::MatrixXd leerArchivo(const char *filename);
void imprimirResultado(const string &directorio, Eigen::VectorXd &autovalores, Eigen::MatrixXd &autovectores);