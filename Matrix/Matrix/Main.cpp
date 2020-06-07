#include <iostream>
#include "Matrix.h";

using namespace std;

int main()
{

	int r = 3, c = 3;
	float** m = new float* [r];
	for (int i = 0; i < r; i++) {
		m[i] = new float[c];
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			m[i][j] =float(2* i + j);
		}
	}
	m[0][0] = 10;
	Matrix m1(r, c, m);

	r = 2, c = 2;
	float** d = new float* [r];
	for (int i = 0; i < r; i++){
		d[i] = new float[c];
}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			d[i][j] =float( i + j);
		}
	}
	Matrix m2(r, c, d);


	cout << m1 << m1.getRow() << ' ' << m1.getCol() << '\n' << endl;
	cout << m2 << m2.getRow() << ' ' << m2.getCol() << '\n' << endl;
	//cout << m2 + m1 << '\n';
	//cout << m2 - m1 << '\n';
	//cout << m2 * m1 << '\n';

	cout << m1.getDet();
}
