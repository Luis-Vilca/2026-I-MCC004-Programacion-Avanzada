#include <fstream>
#include "matrix1.h"

template <typename T>
    void AddX(T &n, T val1, T val2) { n += val1 + val2; }

void DemoMatrix(){

    cout << "Demo Matrix1"<<endl;
    
    ofstream file("matrix2.txt");
    file << "4 4\n" << endl;
    file << "1 0 0 0\n" << "0 1 0 0\n" << "0 0 1 0\n" << "0 0 0 1\n";
    file.close();

    cout << "Prueba lectura de matriz: " << endl;
    Matrix1<TI> matrix;
    ifstream ifs("matrix2.txt");
    ifs >> matrix;
    matrix.Print(cout);

    cout << "Prueba de aplicar la funcion a todos los elementos: " << endl;
    matrix.ApplyFunctionToAll(AddX<TI>, 1, 3);
    cout << matrix;

};

