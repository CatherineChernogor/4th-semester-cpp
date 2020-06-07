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

//int Matrix::getDet() {
//	if (this->isSquare()) {
//		for (int i = 0; i < this->row; i++) {
//			count_zero(this->mat[i]);
//			cout << '\n';
//		}
//
//		return 10;
//	}
//	else {
//		cout << "Error: not square matrix";
//		return 0;
//	}
//}

void Matrix::getMinor(Matrix m, int row, int col, Matrix new_m) {
	int _row = 0, _col = 0;//смещение

	for (int i = 0; i < m.row - 1; i++) {

		if (i == row) {
			_row = 1; // встретили нужную строку, пропускаем со смещением
		}

		_col = 0;
		for (int j = 0; j < m.col - 1; j++) {
			if (j == col) {
				_col = 1; // встретили нужный столбец, пропускаем его смещением
			}
			new_m.mat[i][j] = m.mat[_row + i][_col + j];
		}
	}
}
int Matrix::getDet() {
	int det = 0;
	int degree = 1; // степень в которую возводиться -1 

	if (this->isSquare()) {
		if (this->row == 1) {
			return this->mat[0][0];
		}
		else if (this->row == 2) {
			return this->mat[0][0] * this->mat[1][1] - this->mat[0][1] * this->mat[1][0];
		}
		else {
			
			Matrix new_mat(this->row-1, this->col-1);//алгебраическое дополнение

			for (int j = 0; j < this->col; j++) {//раскладываем по 0 строке

				getMinor(*this, 0, j, new_mat);//удалить из матрицы i строку и j столбец

				det = det + (degree * this->mat[0][j] * new_mat.getDet());
				degree = -degree;
			}
			new_mat.~Matrix();
		}

		return det;
	}
	else {
		cout << "Error: not square matrix";
		return 0;
	}
}
