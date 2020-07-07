#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

template <class T>
class Matrix
{
	int col;
	int row;
	float** mat;

	Matrix<T> getMinor(int a, int  b);
	void setMatrixElement(int r, int c, T n) { this->mat[r][c] = n; }

public:
	Matrix();
	Matrix(int r, int c);
	Matrix(int r, int c, float** d);
	Matrix(const Matrix<T>& m);

	~Matrix();

	Matrix<T>& operator=(const Matrix<T>& m);
	Matrix<T> operator*(const Matrix<T>& m) const;

	float getDet();		   //determinant
	Matrix<T> getInv();	   //inverse matrix
	Matrix<T> getTransp(); //transposed matrix
	bool isDegen();		   // is degenerate matrix

	void fout(std::string filename);
	void fin(std::string filename);


	int getRow() { return this->row; }
	int getCol() { return this->col; }

	bool isSquare() { return this->row == this->col ? true : false; }

	template <class T> friend std::ostream& operator<<(std::ostream& out, Matrix<T>& m)
	{
		for (int i = 0; i < m.row; i++)
		{
			for (int j = 0; j < m.col; j++)
			{
				std::cout.precision(4);
				out << std::setw(6) << m.mat[i][j] << " ";
			}
			out << '\n';
		}
		return out;
	}
	Matrix<T> reshapeToTriangle()
		//template <class T> Matrix<T> Matrix<T>::reshapeToTriangle()
	{

		Matrix res(*this);

		for (int i = 1; i < res.col; i++)
		{
			for (int j = i; j < res.col; j++)
			{
				for (int k = res.col - 1; k >= 0; k--)
				{

					float koef = res.mat[j][i - 1] / res.mat[i - 1][i - 1];
					std::cout<< koef <<" = "<< res.mat[j][i - 1]<<" / "<<res.mat[i - 1][i - 1]<<'\n';
					res.mat[j][k] -= koef * res.mat[i - 1][k];
				}
			}
		}
		return res;
	}
};

template <class T> Matrix<T>::Matrix() {
	row = 2;
	col = 2;

	mat = new float* [row];
	for (int i = 0; i < row; i++) {
		mat[i] = new float[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mat[i][j] = (i == j ? 1.0 : 0.0);
		}
	}
}
template <class T> Matrix<T>::Matrix(int r, int c) {
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
template <class T> Matrix<T>::Matrix(int r, int c, float** d) {
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
template <class T> Matrix<T>::Matrix(const Matrix& m) {
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

template <class T> Matrix<T>::~Matrix() {
	for (int i = 0; i < row; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}

template <class T> Matrix<T>& Matrix<T>::operator=(const Matrix& m) {
	try {
		if (m.row == row && m.col == col) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					mat[i][j] = m.mat[i][j];
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
template <class T> Matrix<T> Matrix<T>::operator*(const Matrix& m) const {
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

template <class T> Matrix<T> Matrix<T>::getMinor(int a, int  b) {
	Matrix res(this->row - 1, this->col - 1);

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
template <class T> float Matrix<T>::getDet() {

	float det = 1;
	if (this->isSquare()) {
		Matrix res(*this);
		res = res.reshapeToTriangle();

		std::cout << res;
		for (int i = 0; i < res.row; i++) {
			for (int j = 0; j < res.col; j++) {
				if (i == j)
					det *= res.mat[i][j];
			}
		}
		return det;
	}
	else {
		std::cout << "Error: not square res.mat";
		return 0;
	}
}
template <class T> Matrix<T> Matrix<T>::getInv() {
	try {
		if (!this->isDegen()) {
			Matrix<T> res(this->row, this->col);

			for (int i = 0; i < this->row; i++) {		//create union matrix
				for (int j = 0; j < this->col; j++) {
					Matrix minor = this->getMinor(i, j);
					double d_minor = minor.getDet();
					int sign = ((i + j) % 2 == 0 ? 1 : -1);
					res.mat[i][j] = sign * d_minor;
				}
			}

			res = res.getTransp();						//union and transposed
			double det = this->getDet();

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

	Matrix<T> res(*this);

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
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			out << mat[i][j] << ' ';
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
			setMatrixElement(i, j, n);
		}
	}
	in.close();
}
