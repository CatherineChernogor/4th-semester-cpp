#include <iostream>
#include "Matrix.h"

void Solve();

int main()
{
	Matrix<double> m1(3, 3);
	m1.fin("data/var2/A.txt");
	std::cout << m1 << '\n';

	double det = m1.getDet();
	std::cout << det << '\n';

	//Solve();
	return 0;
}

void Solve() {

	Matrix<double> A(3, 3);
	A.fin("data/var2/A.txt");

	Matrix<double> B(3, 1);
	B.fin("data/var2/B.txt");

	if (!A.isDegen()) {
		Matrix<double> X = A.getInv() * B;
		X.fout("data/var2/X.txt");
		std::cout << "Saved to the file";
	}
	else {
		std::cout << "Can't solve, matrix is degenerated";
	}
}
