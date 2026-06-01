#include <fstream>
#include <sstream>
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


    stringstream ss1( 
        "3 3 "
        "1 2 3 "
        "4 5 6 "
        "7 8 9"
    );

    stringstream ss2(
        "3 3 "
        "9 8 7 "
        "6 5 4 "
        "3 2 1"
    );

    // Matriz m4
    stringstream ss3(
        "3 3 "
        "1 0 2 "
        "0 1 2 "
        "2 1 0"
    );

    Matrix1<TI> m1, m2, m3, m4;

    ss1 >> m2;
    ss2 >> m3;
    ss3 >> m4;

    cout << "m2:\n";
    cout << m2 << endl;

    cout << "m3:\n";
    cout << m3 << endl;

    cout << "m4:\n";
    cout << m4 << endl;

    // m1 = 5*m2 + m3*m4;
    m1 = 5 * m2 + m3 * m4;

    cout << "Resultado:\n";
    cout << m1 << endl;
};
