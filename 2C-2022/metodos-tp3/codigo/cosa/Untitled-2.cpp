pair<Matriz, vector<double>> triangularMatriz(Matriz &coefs, vector<double> &b, int N) {

    vector<double> bPrima = b;
    
    auto s = std::chrono::high_resolution_clock::now();

    for(int p = 0; p < N - 1; p++) {
        Matriz::InnerIterator itP(coefs, p);
        for (int f = p + 1; f < N; f++) {
            Matriz::InnerIterator itF(coefs, f);
            cout << "Valor f: " << f << " Columna: " << itF.col() << " comp to " << p << endl;
            if(itF.col() == p){
                cout << p << " at " << f << endl;
                double factor = itF.value() / itP.value();
                for(; itP.col() < N; ++itP){
                    while(itF.col() < N && itF.col() < itP.col())
                        ++itF;
                    double valorPrevio = 0;
                    int columnaModificada = itP.col();
                    if(itF.col() < N && itF.col() == itP.col()){
                        valorPrevio = itF.value();
                        coefs.coeffRef(itF.row(), itF.col()) = 0;
                    }
                    double valor = valorPrevio - factor * itP.value();
                    if (!esCero(valor)){
                        coefs.coeffRef(itF.row(), itF.col()) = valor;
                    }
                }
                bPrima[f] -= factor * bPrima.at(p);
            }
        }
        cout << p << endl;
        cout << " " << endl;
    }

    /*
    for (int p = 0; p < N - 1; p++) {
        auto filaP = triangular.row(p);
        for (int f = p + 1; f < N; f++) {
            auto pFilaF = &triangular.row(f);
            auto itFilaF = pFilaF->begin();
            auto itFilaP = filaP->begin();


            if (itFilaF->first == p) {
                double factor = itFilaF->second / itFilaP->second;
                for (; itFilaP != filaP.end(); itFilaP++) {
                    while (itFilaF != pFilaF->end() && itFilaF->first < itFilaP->first) itFilaF++;
                    double valorPrevio = 0;
                    int columnaModificada = itFilaP->first;
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
    }
        */
    cout << "tot " << to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - s).count()) << endl;

    return {coefs, bPrima};
}