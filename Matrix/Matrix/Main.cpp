#include <iostream>
#include "Matrix.h";

using namespace std;

int main()
{

	int r = 5, c = 3;
	int** m = new int* [r];
	for (int i = 0; i < r; i++) {
		m[i] = new int[c];
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			m[i][j] = i * j;
		}
	}
	Matrix m1(r, c, m);

	r = 5, c = 3;
	int** d = new int* [r];
	for (int i = 0; i < r; i++){
		d[i] = new int[c];
}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			d[i][j] = i + j;
		}
	}
	Matrix m2(r, c, d);


	cout << m1 << m1.getRow() << ' ' << m1.getCol() << '\n' << endl;
	cout << m2 << m2.getRow() << ' ' << m2.getCol() << '\n' << endl;
	//cout << m2 + m1 << '\n';
	//cout << m2 - m1 << '\n';

	//cout << m2 * m1 << '\n';
}
