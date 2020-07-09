#include <iostream>
#include "_Matrix.h"
#include "_TriangleMatrix.h"

void Solve(std::string path);
void TriangleExample();

int main()
{
	Solve("data/var2");

	TriangleExample();

	return 0;
}

void Solve(std::string path) {

	Matrix A(3, 3);
	A.fin(path + "/A.txt");

	Matrix B(3, 1);
	B.fin(path + "/B.txt");

	if (!A.isDegen()) {

		Matrix X = A.getInv() * B;
		X.fout(path + "/X.txt");
		std::cout << "Solved and saved to the file\n"<<X;
	}
	else {
		std::cout << "Can't solve, matrix is degenerated";
	}
}

void TriangleExample() {
	TriangleMatrix A1(3);
	A1.fin("data/var1/A.txt");

	Matrix A2(3);
	A2.fin("data/var2/A.txt");

	TriangleMatrix M(3);
	M = A1 * A2;

	std::cout << "\n\nMatrix A1:\n" << A1 << "\n\nMatrix A2:\n" << A2 << "\n\nMatrix M:\n" << M;
}