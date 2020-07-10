#include <iostream>
#include "_Matrix.h"
#include "_TriangleMatrix.h"

void Solve(std::string path, int size);
void TriangleExample();

int main()
{
	Solve("data/var4", 4);

	//TriangleExample();

	return 0;
}

void Solve(std::string path, int size) {

	Matrix<double> A(size);
	A.fin(path + "/A.txt");

	Matrix<double> B(size, 1);
	B.fin(path + "/B.txt");

	if (!A.isDegen()) {

		Matrix<double> X = A.getInv() * B;
		A = A.getInv();

		X.fout(path + "/X.txt");
		std::cout << "Solved and saved to the file\n"<<X;
	}
	else {
		std::cout << "Can't solve, matrix is degenerated";
	}
}

void TriangleExample() {
	TriangleMatrix<double> A1(3);
	A1.fin("data/var1/A.txt");

	Matrix<double> A2(3);
	A2.fin("data/var2/A.txt");

	TriangleMatrix<double> M(3);
	M = A1 * A2;

	std::cout << "\n\nMatrix A1:\n" << A1 << "\n\nMatrix A2:\n" << A2 << "\n\nMatrix M:\n" << M;
}