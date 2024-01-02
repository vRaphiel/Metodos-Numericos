#include "main.h"

using namespace std;
using namespace std::chrono;

int iter;
double eps;
double alpha;

// IN: Matriz A, Vector B, Solucion X, iter, eps, alpha
int main(int argc, char *argv[]){

    MatrizMP A = leerArchivo(argv[1]);
    VectorMP x = leerVector(argv[2]);
    VectorMP b = leerVector(argv[3]);

    iter = int(atoi(argv[5]));
    eps = strtod(argv[6], NULL);
    alpha = strtod(argv[7], NULL);

    string inicial = argv[8];

    Errores time;
    auto start = high_resolution_clock::now();
    VectorMP LU = SolveLU(A,b);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;    
    time.push_back(duration.count());

    string s = "-lu";
    imprimirResultado(LU, argv[4] + s);
    s = "-lu-err";
    ofstream output;
    output.open(argv[4] + s + ".out");
    output << (LU - x).norm();
    output.close();

    start = high_resolution_clock::now();
    tuple<VectorMP, Errores> JS = JacobiSumatoria(A, b, x, inicial);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;
    time.push_back(duration.count());


    s = "-js";
    imprimirResultado(get<0>(JS), argv[4] + s);
    s = "-js-err";
    imprimirErrores(get<1>(JS), argv[4] + s);

    start = high_resolution_clock::now();
    tuple<VectorMP, Errores> JM = JacobiMatricial(A, b, x, inicial);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;
    time.push_back(duration.count());
  
    s = "-jm";
    imprimirResultado(get<0>(JM), argv[4] + s);
    s = "-jm-err";
    imprimirErrores(get<1>(JM), argv[4] + s);

    start = high_resolution_clock::now();
    tuple<VectorMP, Errores> GSS = GSSumatoria(A, b, x, inicial);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);    
    cout << duration.count() << endl;
    time.push_back(duration.count());

    s = "-gss";
    imprimirResultado(get<0>(GSS), argv[4] + s);
    s = "-gss-err";
    imprimirErrores(get<1>(GSS), argv[4] + s);

    start = high_resolution_clock::now();
    tuple<VectorMP, Errores> GSM = GSMatricial(A, b, x, inicial);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;
    time.push_back(duration.count());

    s = "-gsm";
    imprimirResultado(get<0>(GSM), argv[4] + s);   
    s = "-gsm-err";
    imprimirErrores(get<1>(GSM), argv[4] + s);

    s = "-tiempo";
    imprimirErrores(time, argv[4] + s);

    return 0;
}

tuple<VectorMP, Errores> JacobiSumatoria(MatrizMP &A, VectorMP &b, VectorMP &x, string v0){

    VectorMP vec = VectorMP(A.rows());
    if(v0 == "CN"){
        vec(0) = 1;
        for(int i = 1; i < vec.size(); i++){ 
            vec(i) = 0;
        } 
    } else if (v0 == "RN"){
        srand(12345);
        for(int i = 0; i < vec.size(); i++){ 
            int random = rand() % 100;
            vec(i) = random;
        } 
    } else {
        for(int i = 0; i < vec.size(); i++){ 
        vec(i) = 1;
        } 
    }
    Errores error;

    VectorMP oldVector;
    for(int k = 0; k < iter; k++){
        oldVector = vec;
        for(int i = 0; i < vec.size(); i++){
            double suma = 0;
            for(int j = 0; j < vec.size(); j++){
                if(j != i){
                    suma += A(i,j)*oldVector(j);
                }
            }
            vec(i) = (b(i) - suma)/A(i,i);
        }
        
        double diferencia = (oldVector - vec).norm();
         if(diferencia < eps) {
             break;
         }
        // if(diferencia > alpha) {
        //     break;
        // }
        error.push_back((vec - x).norm());
    }
    return make_tuple(vec, error);
}

tuple<VectorMP, Errores> JacobiMatricial(MatrizMP &A, VectorMP &b, VectorMP &x, string v0){

    int n = A.rows();
    MatrizMP D(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            D(i, j) = 0;
        }
    }

    MatrizMP L(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            L(i, j) = 0;
        }
    }

    MatrizMP U(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            U(i, j) = 0;
        }
    }

    for(int i = 0; i < A.rows(); i++){ //Armo matrices D, L, U
        for(int j = 0; j < A.rows(); j++){
            if(i == j){
                D(i,i) = A(i,i);
            } else if(i < j){
                U(i,j) = -A(i,j);
            } else {
                L(i,j) = -A(i,j);
            }
        }
    }
    VectorMP vec = VectorMP(n);
    if(v0 == "CN"){
        vec(0) = 1;
        for(int i = 1; i < vec.size(); i++){ 
            vec(i) = 0;
        } 
    } else if (v0 == "RN"){
        srand(12345);
        for(int i = 0; i < vec.size(); i++){ 
            vec(i) = rand() % 100;
        } 
    } else {
        for(int i = 0; i < vec.size(); i++){ 
        vec(i) = 1;
        } 
    }

    Errores error;


    MatrizMP Dinv = D.inverse();
    MatrizMP DinvLU = Dinv*(L + U);

    for(int k = 0; k < iter; k++){
        VectorMP oldVector = vec;
        VectorMP c = Dinv*b;
        VectorMP t = DinvLU*vec;
        vec = t + c;
        double diferencia = (oldVector - vec).norm();
         if(diferencia < eps) {
             break;
         }
        // if(diferencia > alpha) {
        //     break;
        // }
        error.push_back((vec - x).norm());
    }

    return make_tuple(vec, error);
}

tuple<VectorMP, Errores> GSSumatoria(MatrizMP &A, VectorMP &b, VectorMP &x, string v0){
    VectorMP vec = VectorMP(A.rows());
    if(v0 == "CN"){
        vec(0) = 1;
        for(int i = 1; i < vec.size(); i++){ 
            vec(i) = 0;
        } 
    } else if (v0 == "RN"){
        srand(12345);
        for(int i = 0; i < vec.size(); i++){ 
            vec(i) = rand() % 100;
        } 
    } else {
        for(int i = 0; i < vec.size(); i++){ 
        vec(i) = 1;
        } 
    }

    VectorMP oldVector;
    Errores error;
    for(int k = 0; k < iter; k++){
        oldVector = vec;
        for(int i = 0; i < vec.size(); i++){
            double suma = 0;
            for(int j = 0; j < i; j++){ // desde 0 a i-1 uso los valores nuevos del x
                suma += A(i,j)*vec(j);
            }

            for(int j = i+1; j < vec.size(); j++){ // desde i+1 a n uso los valores viejos del x
                suma += A(i,j)*oldVector(j);
            }

            vec(i) = (b(i) - suma)/A(i,i);
        }
        double diferencia = (oldVector - vec).norm();
         if(diferencia < eps) {
             break;
         }
        // if(diferencia > alpha) {
        //     break;
        // }
        error.push_back((vec - x).norm());
    }
    return make_tuple(vec, error);
}


tuple<VectorMP, Errores> GSMatricial(MatrizMP &A, VectorMP &b, VectorMP &x, string v0){

    int n = A.rows();
    MatrizMP D(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            D(i, j) = 0;
        }
    }

    MatrizMP L(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            L(i, j) = 0;
        }
    }

    MatrizMP U(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            U(i, j) = 0;
        }
    }

    for(int i = 0; i < n; i++){ //Armo matrices D, L, U
        for(int j = 0; j < n; j++){
            if(i == j){
                D(i,i) = A(i,i);
            } else if(i < j){
                U(i,j) = -A(i,j);
            } else {
                L(i,j) = -A(i,j);
            }
        }
    }

    VectorMP vec = VectorMP(n);
    if(v0 == "CN"){
        vec(0) = 1;
        for(int i = 1; i < vec.size(); i++){ 
            vec(i) = 0;
        } 
    } else if (v0 == "RN"){
        srand(12345);
        for(int i = 0; i < vec.size(); i++){ 
            vec(i) = rand() % 100;
        } 
    } else {
        for(int i = 0; i < vec.size(); i++){ 
        vec(i) = 1;
        } 
    }

    Errores error;

    MatrizMP DLinv = (D - L).inverse();
    MatrizMP DLinvU = DLinv*U;

    for(int k = 0; k < iter; k++){
        VectorMP oldVector = vec;
        VectorMP c =  DLinv*b;
        VectorMP t = DLinvU*vec;
        vec = t + c;
        double diferencia = (oldVector - vec).norm();
         if(diferencia < eps) {
             break;
         }
        // if(diferencia > alpha) {
        //     break;
        // }
        error.push_back((vec - x).norm());
    }

    return make_tuple(vec, error);
}

VectorMP SolveLU(MatrizMP &A, VectorMP &b){
    return A.lu().solve(b);
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

VectorMP leerVector(const string &directorio) {
    ifstream fin(directorio);
    int nvalue;
    fin >> nvalue;
    VectorMP x(nvalue);
    for (int i = 0; i < nvalue; i++){
        fin >> x(i);
    }
    return x;
}

void imprimirResultado(VectorMP &x, const string &directorio) {
    ofstream output;
    output.open(directorio + ".out");
    for (double i = 0; i < x.size(); i++) {
        output << x(i) << endl;
    }
    output.close();
}

void imprimirErrores(Errores &x, const string &directorio) {
    ofstream output;
    output.open(directorio + ".out");
    for (double i = 0; i < x.size(); i++) {
        output << x[i] << endl;
    }
    output.close();
}