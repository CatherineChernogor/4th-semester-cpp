#include <iostream>
#include "Matrix.h"
#include "Triangle_matrix.h"

void Solve(std::string path);

int main()
{
	Solve("data/var1");

	return 0;
}

void Solve(std::string path) {

	Matrix A(3, 3);
	A.fin(path+"/A.txt");

	Matrix B(3, 1);
	B.fin(path+"/B.txt");

	if (!A.isDegen()) {

		Matrix X = A.getInv() * B;
		std::cout << X;
		X.fout(path+"/X.txt");
		std::cout << "Saved to the file";
	}
	else {
		std::cout << "Can't solve, matrix is degenerated";
	}
}
