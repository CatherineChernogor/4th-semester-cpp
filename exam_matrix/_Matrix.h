#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>


template <class T> class Matrix {

protected:
	int col;
	int row;
	T** mat;
	int det_sign;

	Matrix<T> getMinor(int a, int  b);

public:
	Matrix<T>(int r) : Matrix<T>(r, r) {}
	Matrix<T>(int r, int c) : Matrix<T>(r, c, NULL) {}
	Matrix<T>(int r, int c, T** d) { *this = createMatrix(r, c, d); }

	Matrix<T>(const Matrix& m);

	~Matrix<T>();

	Matrix<T>& operator=(const Matrix<T>& m);
	Matrix<T> operator*(const Matrix<T>& m) const;
	Matrix<T> operator*(const std::vector<T>& v) const;

	double getDet();            //determinant
	Matrix<T> getInv();            //inverse matrix
	Matrix<T> getTransp();         //transposed matrix
	bool isDegen();             // is degenerate matrix

	void fout(std::string filename);
	void fin(std::string filename);
	template <class T> friend std::ostream& operator<<(std::ostream& out, Matrix<T>& m);

	int getRow() { return this->row; }
	int getCol() { return this->col; }

	bool isSquare() { return this->row == this->col ? true : false; }

	Matrix<T> createMatrix(int r, int c, T** d);

	void switchRows(int from, int to);
	void reshapeToTriangle();
};


template <class T> Matrix<T>::Matrix(const Matrix<T>& m) {
	this->row = m.row;
	this->col = m.col;
	this->det_sign = m.det_sign;


	this->mat = new T * [this->row];
	for (int i = 0; i < this->row; i++) {
		this->mat[i] = new T[this->col];
	}

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			this->mat[i][j] = m.mat[i][j];
		}
	}
}

template <class T> Matrix<T>::~Matrix() {
	for (int i = 0; i < this->row; i++) {
		delete[] this->mat[i];
	}
	delete[] this->mat;
}

template <class T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
	try {
		if (m.row == this->row && m.col == this->col) {
			for (int i = 0; i < this->row; i++) {
				for (int j = 0; j < this->col; j++) {
					this->mat[i][j] = m.mat[i][j];
				}
			}
		}
		else
			throw - 1;
	}
	catch (int i) {
		std::cout << "Error " << i << " invalid res.mat dimention";
		exit(i);
	}
}
template <class T> Matrix<T> Matrix<T>::operator*(const Matrix<T>& m) const {
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
		else
			throw 1;
	}
	catch (int i) {
		std::cout << "Error " << i << " invalid res.mat dimention";
		exit(i);
	}
}
template <class T> Matrix<T> Matrix<T>::operator*(const std::vector<T>& v) const {
	try {
		if (this->col == v.size()) {

			Matrix res(this->row, 1);

			for (int i = 0; i < this->row; i++) {

				for (int k = 0; k < this->col; k++)
					res.mat[i][0] += this->mat[i][k] * v[k];

			}
			return res;
		}
		else
			throw 1;
	}
	catch (int i) {
		std::cout << "Error " << i << " invalid res.mat dimention";
		exit(i);
	}
}

template <class T> double Matrix<T>::getDet() {

	if (this->isSquare()) {

		if (this->row == 1) return this->mat[0][0];

		else if (this->row == 2)
			return (this->mat[0][0] * this->mat[1][1]) - (this->mat[0][1] * this->mat[1][0]);

		if (this->row > 2) {

			Matrix res(*this);
			double det = 1;

			res.reshapeToTriangle();

			for (int i = 0; i < res.row; i++) {
				for (int j = 0; j < res.col; j++) {
					if (i == j)
						det *= res.mat[i][j];
				}
			}

			return det * res.det_sign;
		}
	}
	else {
		std::cout << "Error: not square res.mat";
		return 0;
	}
}
template <class T> Matrix<T> Matrix<T>::getInv() {

	try {
		if (!this->isDegen()) {
			Matrix res(this->row, this->col);

			for (int i = 0; i < this->row; i++) {		//create union matrix
				for (int j = 0; j < this->col; j++) {

					Matrix minor = this->getMinor(i, j);
					double d_minor = minor.getDet();
					int sign = ((i + j) % 2 == 0 ? 1 : -1);


					res.mat[i][j] = sign * d_minor;


				}
			}

			double det = this->getDet();

			res = res.getTransp();						//union and transposed

			for (int i = 0; i < this->row; i++) {
				for (int j = 0; j < this->col; j++) {

					res.mat[i][j] /= det;
				}
			}

			return res;
		}
		else
			throw 1;
	}
	catch (int i) {

		std::cout << "Error " << i << " matrix is degenerated";
		exit(i);
	}
}
template <class T> Matrix<T> Matrix<T>::getTransp() {

	Matrix res(*this);

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			res.mat[j][i] = this->mat[i][j];
		}
	}
	return res;
}
template <class T> bool Matrix<T>::isDegen() {

	return this->getDet() == 0 ? true : false;
}

template <class T> void Matrix<T>::fout(std::string filename) {

	std::ofstream out(filename);
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			out << this->mat[i][j] << ' ';
		}
		out << '\n';
	}
	out.close();
}
template <class T> void Matrix<T>::fin(std::string filename) {

	std::ifstream in(filename);
	T n;
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			in >> n;
			this->mat[i][j] = n;
		}
	}
	in.close();
}
template <class T> std::ostream& operator<<(std::ostream& out, Matrix<T>& m) {

	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.col; j++) {
			std::cout.precision(4);

			/*if (
				(m.mat[i][j] < 1E-6 && m.mat[i][j]>0)
				|| m.mat[i][j] > -1E-6
				)

				out << std::setw(6) << int(m.mat[i][j]) << " ";
			else*/
			out << std::setw(6) << m.mat[i][j] << " ";
		}
		out << '\n';
	}
	return out;
}

template <class T> Matrix<T> Matrix<T>::getMinor(int a, int  b) {

	Matrix res(this->row - 1);

	int koef_i = 0;
	for (int i = 0; i < res.row; i++) {

		int koef_j = 0;
		for (int j = 0; j < res.col; j++) {
			if (i == a) koef_i = 1;
			if (j == b) koef_j = 1;
			res.mat[i][j] = this->mat[i + koef_i][j + koef_j];
		}
	}
	return res;
}

template <class T> Matrix<T> Matrix<T>::createMatrix(int r, int c, T** d) {
	row = r;
	col = c;
	det_sign = 1;

	mat = new T * [row];
	for (int i = 0; i < row; i++) {
		mat[i] = new T[col];
	}

	if (d != NULL) {
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				mat[i][j] = d[i][j];
	}
	else {
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				mat[i][j] = 0;
	}
	return *this;
}

template <class T> void Matrix<T>::switchRows(int from, int to) {

	T* rowFrom = new T[this->row];
	T* rowTo = new T[this->row];

	for (int i = 0; i < this->row; i++) {
		rowFrom[i] = this->mat[from][i];
		rowTo[i] = this->mat[to][i];
	}

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->row; j++) {

			if (i == from) { this->mat[i][j] = rowTo[j]; }
			if (i == to) { this->mat[i][j] = rowFrom[j]; }
		}
	}
}
template <class T> void Matrix<T>::reshapeToTriangle() {

	int s = 0;
	for (; s < this->row; s++) {
		if (this->mat[s][0] != 0) break;
	}

	//If we swap two rows of the matrix, the matrix determinant changes the sign.
	if (s != 0) {

		this->switchRows(0, s);
		this->det_sign *= -1;
	}

	for (int i = 1; i < this->col; i++) {
		for (int j = i; j < this->col; j++) {

			float koef = this->mat[j][i - 1] / this->mat[i - 1][i - 1];
			for (int k = this->col - 1; k >= 0; k--) {

				this->mat[j][k] -= koef * this->mat[i - 1][k];
			}
		}
	}
}