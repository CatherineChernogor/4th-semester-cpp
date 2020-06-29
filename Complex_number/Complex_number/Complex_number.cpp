#include <iostream>
#include "complex.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    Complex<double> n1(1, -2);
    Complex<double> n2(4, 8);
    cout << n1 << '\n' << n2 << '\n';

    Complex<double> res = n1 / n2;
    cout << res << '\n';

    cout << n1.phase();
}
