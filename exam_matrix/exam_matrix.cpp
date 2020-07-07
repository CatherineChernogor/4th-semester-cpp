#include <iostream>
#include "Matrix.h"
int main()
{
    std::cout << "Hello World!\n";
    Matrix<double> m1(3, 3);
    m1.fin("in_matr.txt");

    cout << m1;
    m1.fout("out.txt");

}
