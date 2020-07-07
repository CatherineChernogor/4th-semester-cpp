#include <iostream>
#include "Matrix.h"
int main()
{
    std::cout << "Hello World!\n";
    Matrix<double> m1(3, 3);
    m1.fin("in_matr.txt");

    cout << m1<<'\n';
    //m1.fout("out.txt");

    Matrix<double> m2 = m1.getTransp();
    cout << m2;

}
