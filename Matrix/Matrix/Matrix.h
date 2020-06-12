#pragma once
#include <iostream>
using namespace std;

class Matrix {
	int col;
	int row;
	float** mat;

	void getMinor(Matrix m, int row, int col, Matrix new_m);
public:

	Matrix();//+
	Matrix(int r, int c);//+
	Matrix(int r, int c, float** d);//+
	Matrix(const Matrix& m);//+

	~Matrix();//+
	Matrix& operator =(const Matrix& m);
	Matrix& operator +=(const Matrix& m);//+
	Matrix operator +(const Matrix& m) const;//+
	Matrix& operator -=(const Matrix& m);//+
	Matrix operator -(const Matrix& m) const;//+
	Matrix operator *(const Matrix& m) const;//+

	Matrix reshapeToTriangle();//+
	float getDet();
	Matrix getInv();
	void out();//+
	int getRow();//+
	int getCol();//+
	bool isSquare();//+

	friend ostream& operator <<(ostream& out, const Matrix& m);//+

};