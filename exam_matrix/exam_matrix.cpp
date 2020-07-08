#include <iostream>
#include "Matrix.h"
#include "Triangle_matrix.h"

void Solve(std::string path);

int main()
{

	//Matrix<double> A(3, 3);
	//A.fin("data/var2/A.txt");
	//std::cout << "A:\n" << A << "\n\n";

	//Matrix<double> m1 = A.reshapeToTriangle();
	//std::cout << "Triangle\n" << m1 << "\n\n";

	//double det = A.getDet();
	//std::cout<<"det:\n" << det << "\n\n";

	// m1 = A.getInv();
	//std::cout << "Inversed\n" << m1 << "\n\n";

	//Solve("data/var1");

	int** d = new int* [3];
	for (int i = 0; i < 3; i++) {
		d[i] = new int[3];
	}
	d[0][0] = 0;
	d[0][1] = 3;
	d[0][2] = 1;
	d[1][0] = 2;
	d[1][1] = 4;
	d[1][2] = 1;
	d[2][0] = 2;
	d[2][1] = 2;
	d[2][2] = 0;


	Matrix<int> res(3, 3, d);
	std::cout << res;



	TriangleMatrix<double> A(3, 3);
	std::cout << A;

	return 0;
}

void Solve(std::string path) {

	Matrix<double> A(3, 3);
	A.fin(path+"/A.txt");

	Matrix<double> B(3, 1);
	B.fin(path+"/B.txt");

	if (!A.isDegen()) {

		Matrix<double> X = A.getInv() * B;
		std::cout << X;
		X.fout(path+"/X.txt");
		std::cout << "Saved to the file";
	}
	else {
		std::cout << "Can't solve, matrix is degenerated";
	}
}
