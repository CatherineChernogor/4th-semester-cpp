#include <iostream>
#include "Matrix.h";

using namespace std;




int main()
{

	int row = 3, col = 3;

	float** mat = new float* [row];
	for (int i = 0; i < row; i++) {
		mat[i] = new float[col];
	}
	mat[0][0] = 5;
	mat[0][1] = 7;
	mat[0][2] = 6;
	mat[1][0] = 3;
	mat[1][1] = 16;
	mat[1][2] = 19;
	mat[2][0] = 13;
	mat[2][1] = 10;
	mat[2][2] = 7;

	int m[3][3] = {
		{5, 7, 6},
		{3, 16, 19},
		{13, 10, 7}
	};
	Matrix m1(row, col, mat);



	cout << m1 << m1.getRow() << ' ' << m1.getCol() << '\n' << endl;
	//cout << m2 << m2.getRow() << ' ' << m2.getCol() << '\n' << endl;
	//cout << m2 + m1 << '\n';
	//cout << m2 - m1 << '\n';
	//cout << m2 * m1 << '\n';

	//cout << m1.reshapeToTriangle()<<endl;
	cout << m1.getDet();
}
