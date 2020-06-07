#pragma once
#include <iostream>
using namespace std;
class MatrixExeption {

};
class Matrix {
	int col;
	int row;
	int** mat;

public:

	Matrix();//+
	Matrix(int r, int c);//+
	Matrix(int r, int c, int** d);//+
	Matrix(const Matrix&m);//+

	~Matrix();//+

	Matrix& operator +=(const Matrix& m);//+
	Matrix operator +(const Matrix& m) const;//+
	Matrix& operator -=(const Matrix& m);//+
	Matrix operator -(const Matrix& m) const;//+
	Matrix operator *(const Matrix& m) const;//+

	int getDet();
	Matrix getInv();
	void out();//+
	int getRow();//+
	int getCol();//+

	friend ostream& operator <<(ostream& out, const Matrix& m);//+

};