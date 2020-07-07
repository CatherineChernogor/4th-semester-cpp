#include <iostream>
#include "Matrix.h"

void Solve();

int main()
{
	//Matrix<double> m1(3, 3);
	//m1.fin("in_matr.txt");
	//std::cout << m1 << '\n';

	//Matrix<double> m2 = m1.getInv();
	//std::cout << m2 << '\n';

	Solve();
	return 0;
}

void Solve() {

	Matrix<double> A(3, 3);
	A.fin("A.txt");

	Matrix<double> B(3, 1);
	B.fin("B.txt");

	if (!A.isDegen()) {
		Matrix<double> X = A.getInv() * B;
		X.fout("X.txt");
	}
	else {
		std::cout << "Can't solve, matrix is degenerated";
	}
}

//A:      B:      X:
//0 3 1   17      3
//2 4 1   27      4
//2 2 0   14      5
