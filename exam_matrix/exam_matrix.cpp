#include <iostream>
#include "Matrix.h"

void Solve(std::string path);

int main()
{
	/*Matrix<double> m1(3, 3);
	m1.fin("data/var2/A.txt");
	std::cout << m1 << '\n';

	double det = m1.getDet();
	std::cout << det << '\n';*/

	Solve("data/var2");
	return 0;
}

void Solve(std::string path) {

	Matrix<double> A(3, 3);
	A.fin(path+"/A.txt");

	Matrix<double> B(3, 1);
	B.fin(path+"/B.txt");

	if (!A.isDegen()) {

		Matrix<double> X = A.getInv() * B;

		Matrix<double> m1 = A.getInv();
		std::cout<<"A\n" <<A<<"\n\nInversed\n"<< m1 << "\nX\n";
		std::cout << X;


		X.fout(path+"/X.txt");
		std::cout << "Saved to the file";
	}
	else {
		std::cout << "Can't solve, matrix is degenerated";
	}
}
