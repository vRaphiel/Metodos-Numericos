#include "eliminacionGausseana.h"

vector<double> eliminacionGausseana(Matriz &coefs, vector<double> &b, int N) {
    pair<Matriz, vector<double>> triangularExtendida = convertirEnTriangular(coefs, b, N);
    Matriz triangular = triangularExtendida.first;
    vector<double> nuevaB = triangularExtendida.second;
    return backwardSubstitution(triangular, nuevaB, N);
}

pair<Matriz, vector<double>> convertirEnTriangular(Matriz &coefs, vector<double> &b, int N) {
    Matriz triangular = coefs;
    vector<double> bPrima = b;
    for (int p = 0; p < N - 1; p++) {
        for (int fila = p + 1; fila < N; fila++) {
            if (!esCero(triangular.at(fila, p))) {
                double factor = triangular.at(fila, p) / triangular.at(p, p);
                for (int col = p; col < N; col++) {
                    if (!esCero(triangular.at(p, col))) {
                        double valor = triangular.at(fila, col) - factor * triangular.at(p, col);
                        triangular.asignar(fila, col, valor);
                    }
                }

                bPrima[fila] -= factor * bPrima.at(p);
            }
        }
    }

    return {triangular, bPrima};
}

/*
pair<Matriz, vector<double>> convertirEnTriangular(Matriz &coefs, vector<double> &b, int N) {
    Matriz triangular = coefs;
   for(int i = 0; i < dimension - 1; i++){ //recorro todos los m_ii
       auto fila = _filas.begin();
       while(fila.first < i && fila != _filas.end()){
           fila++;
       }
       for(auto fila = _filas.begin(); fila != _filas.end(); fila++){    //recorro las filas por debajo de la diagonal
           auto columna = fila.second.begin();
           while(columna.first < i && columna != fila.second.end()){
               columna++;
           }
           if(columna.first == i){
               double factor = columna.second / _filas.at(i,i);
               auto columnaD = _filas.at(i).begin();
               while(columna != fila.second.end()){ //Aca faltaria chequear las columnas que estan en fila Diagonal, pero no en la fila que queremos modificar.
                   while(columnaD.first < columna.first && columnaD != _filas.at(i).end()){
                       columnaD++;
                   }
                   if(columnaD.first == columna.first){
                       columna.second -= factor * columnaD.second;
                   }
                   columna++;
               }
               b[fila.first] -= factor * b[i]
           } else {
                // ya habia un 0, no hago nada
           }
       }
   }
}
*/
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
