#include <iostream>
#include "Matrix.h";

Matrix::Matrix() {
	row = 2;
	col = 2;

	mat = new float* [row];
	for (int i = 0; i < row; i++) {
		mat[i] = new float[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			i == j ? mat[i][j] = 1.0 : mat[i][j] = 0.0;
		}
	}
}

Matrix::Matrix(int r, int c) {
	row = r;
	col = c;

	mat = new float* [row];
	for (int i = 0; i < row; i++) {
		mat[i] = new float[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mat[i][j] = 0.0;
		}
	}
}

Matrix::Matrix(int r, int c, float** d) {
	row = r;
	col = c;

	mat = new float* [row];
	for (int i = 0; i < row; i++) {
		mat[i] = new float[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mat[i][j] = d[i][j];
		}
	}
}

Matrix::Matrix(const Matrix& m) {
	this->row = m.row;
	this->col = m.col;

	this->mat = new float* [this->row];
	for (int i = 0; i < this->row; i++) {
		mat[i] = new float[this->col];
	}

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			this->mat[i][j] = m.mat[i][j];
		}
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < row; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}

int Matrix::getCol() {
	return this->col;
}
int Matrix::getRow() {
	return this->row;
}

void Matrix::out() {
	for (int i = 0; i < row; i++) {

		for (int j = 0; j < col; j++) {
			cout << mat[i][j] << ' ';
		}
		cout << '\n';
	}
}

ostream& operator<<(ostream& out, const Matrix& m) {
	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.col; j++) {
			out << m.mat[i][j] << " ";
		}
		out << '\n';
	}
	return out;
}


Matrix& Matrix::operator+=(const Matrix& m) {
	try {
		if (row == m.row && col == m.col) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					mat[i][j] += m.mat[i][j];
				}
			}
			return *this;
		}
		else {
			throw 1;
		}
	}
	catch (int i) {
		cout << "Error " << i << " invalid matrix dimention";
		exit(i);
	}
}

Matrix Matrix::operator+(const Matrix& m) const {
	Matrix res(*this);
	return res += m;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	try {
		if (row == m.row && col == m.col) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					mat[i][j] -= m.mat[i][j];
				}
			}
			return *this;
		}
		else {
			throw 1;
		}
	}
	catch (int i) {
		cout << "Error " << i << " invalid matrix dimention";
		exit(i);
	}
}

Matrix Matrix::operator-(const Matrix& m) const {
	Matrix res(*this);
	return res -= m;
}

Matrix Matrix::operator *(const Matrix& m) const {
	try {
		if (this->col == m.row) {

			Matrix res(this->row, m.col);
			for (int i = 0; i < this->row; i++) {
				for (int j = 0; j < m.col; j++) {
					for (int k = 0; k < this->col; k++)
						res.mat[i][j] += this->mat[i][k] * m.mat[k][j];
				}
			}
			return res;
		}
		else {
			throw 1;
		}
	}
	catch (int i) {
		cout << "Error " << i << " invalid matrix dimention";
		exit(i);
	}
}

bool Matrix::isSquare() {
	if (this->row == this->col) {
		return true;
	}
	else return false;
}

void count_zero(int* arr) {
	cout << sizeof(arr) << '\n';
	for (int i = 0; i < sizeof(arr); i++) {
		cout << arr[i];
	}
}

Matrix Matrix::reshapeToTriangle() {

	Matrix res(*this);

	for (int i = 1; i < res.col; i++) {
		for (int j = i; j < res.col; j++) {
			for (int k = res.col - 1; k >= 0; k--) {

				float koef = res.mat[j][i - 1] / res.mat[i - 1][i - 1];
				res.mat[j][k] -= koef * res.mat[i - 1][k];
			}
		}
	}
	return res;
}

Matrix& Matrix::operator =(const Matrix& m) {
	try {
		if (m.row == row && m.col == col) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					mat[i][j] = m.mat[i][j];
				}
			}
		}
		else throw - 1;
	}
	catch (int i) {
		cout << "Error " << i << " invalid matrix dimention";
		exit(i);
	}
}

float Matrix::getDet() {

	float det=1;
	if (this->isSquare()) {
		Matrix res(*this);
		res = res.reshapeToTriangle();

		for (int i = 0; i < res.row; i++) {
			for (int j = 0; j < res.col; j++) {
				if (i==j)
				det*= res.mat[i][j];
			}
		}
		return det;
	}
	else {
		cout << "Error: not square matrix";
		return 0;
	}
}
