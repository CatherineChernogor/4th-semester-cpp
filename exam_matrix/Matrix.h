#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

template<class T> class Matrix {
	int col;
	int row;
	float** mat;
	//Matrix addIdentMax();
public:

	Matrix();
	Matrix(int r, int c);
	Matrix(int r, int c, float** d);
	Matrix(const Matrix<T>& m);

	~Matrix();

	Matrix<T>& operator =(const Matrix<T>& m);
	Matrix<T> operator *(const Matrix<T>& m) const;

	float getDet();				//determinant
	Matrix<T> getInv();			//inverse matrix------------------------------------
	Matrix<T> getTransp();		//transposed matrix
	bool isDegen();				// is degenerate matrix

	int getRow();
	int getCol();
	void setMatrixElement(int r, int c, T n);
	bool isSquare();

	void fout(string filename);
	void fin(string filename);

	//Matrix<T>& operator +=(const Matrix<T>& m);
	//Matrix<T> operator +(const Matrix<T>& m) const;
	//Matrix<T>& operator -=(const Matrix<T>& m);
	//Matrix<T> operator -(const Matrix<T>& m) const;

	template <class T> friend ostream& operator <<(ostream& out, Matrix<T>& m) {
		for (int i = 0; i < m.row; i++) {
			for (int j = 0; j < m.col; j++) {
				cout.precision(2);
				out << setw(4) << m.mat[i][j] << " ";
			}
			out << '\n';
		}
		return out;
	}
	Matrix<T> reshapeToTriangle()
		//template <class T> Matrix<T> Matrix<T>::reshapeToTriangle() 
	{

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
			i == j ? mat[i][j] = 1.0 : mat[i][j] = 0.0;
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

template <class T> Matrix<T>& Matrix<T>::operator =(const Matrix& m) {
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
		cout << "Error " << i << " invalid res.mat dimention";
		exit(i);
	}
}
template <class T> Matrix<T> Matrix<T>::operator *(const Matrix& m) const {
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
		cout << "Error " << i << " invalid res.mat dimention";
		exit(i);
	}
}

template <class T> float Matrix<T>::getDet() {

	float det = 1;
	if (this->isSquare()) {
		Matrix res(*this);
		res = res.reshapeToTriangle();

		for (int i = 0; i < res.row; i++) {
			for (int j = 0; j < res.col; j++) {
				if (i == j)
					det *= res.mat[i][j];
			}
		}
		return det;
	}
	else {
		cout << "Error: not square res.mat";
		return 0;
	}
}
template <class T> Matrix<T> Matrix<T>::getInv() {}
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

template <class T> int Matrix<T>::getRow() {
	return this->row;
}
template <class T> int Matrix<T>::getCol() {
	return this->col;
}
template <class T> void Matrix<T>::setMatrixElement(int r, int c, T n) {
	this->mat[r][c] = n;
}
template <class T> bool Matrix<T>::isSquare() {
	if (this->row == this->col) {
		return true;
	}
	else return false;
}

template <class T> void Matrix<T>::fout(string filename) {
	ofstream out(filename);

	for (int i = 0; i < row; i++) {

		for (int j = 0; j < col; j++) {
			out << mat[i][j] << ' ';
		}
		out << '\n';
	}
	out.close();
}
template <class T> void Matrix<T>::fin(string filename) {
	ifstream in;
	in.open(filename);
	T n;
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			in >> n;
			setMatrixElement(i, j, n);
		}
	}
	in.close();

}


//template <class T> Matrix<T>& Matrix<T>::operator+=(const Matrix& m) {
//	try {
//		if (row == m.row && col == m.col) {
//			for (int i = 0; i < row; i++) {
//				for (int j = 0; j < col; j++) {
//					mat[i][j] += m.mat[i][j];
//				}
//			}
//			return *this;
//		}
//		else {
//			throw 1;
//		}
//	}
//	catch (int i) {
//		cout << "Error " << i << " invalid res.mat dimention";
//		exit(i);
//	}
//}
//template <class T> Matrix<T> Matrix<T>::operator+(const Matrix& m) const {
//	Matrix res(*this);
//	return res += m;
//}
//template <class T> Matrix<T>& Matrix<T>::operator-=(const Matrix& m) {
//	try {
//		if (row == m.row && col == m.col) {
//			for (int i = 0; i < row; i++) {
//				for (int j = 0; j < col; j++) {
//					mat[i][j] -= m.mat[i][j];
//				}
//			}
//			return *this;
//		}
//		else {
//			throw 1;
//		}
//	}
//	catch (int i) {
//		cout << "Error " << i << " invalid res.mat dimention";
//		exit(i);
//	}
//}
//template <class T> Matrix<T> Matrix<T>::operator-(const Matrix& m) const {
//	Matrix res(*this);
//	return res -= m;
//}




//void count_zero(int* arr) {
//	cout << sizeof(arr) << '\n';
//	for (int i = 0; i < sizeof(arr); i++) {
//		cout << arr[i];
//	}
//}

//template <class T> Matrix<T> Matrix<T>::addIdentMax() {
//	int n_col = col * 2;
//	int n_row = row;
//
//	float** n_mat = new float* [n_row];
//	for (int i = 0; i < n_row; i++) {
//		n_mat[i] = new float[n_col];
//	}
//
//	for (int i = 0; i < row; i++) {
//
//		for (int j = 0; j < col; j++) {
//			n_mat[i][j] = mat[i][j];
//		}
//		for (int j = col; j < n_col; j++) {
//
//			if (i + col == j)
//				n_mat[i][j] = 1;
//			else
//				n_mat[i][j] = 0;
//		}
//	}
//
//	Matrix n(n_row, n_col, n_mat);
//	return n;
//}

//Matrix template <class T> Matrix<T>::getInv() {
//	try {
//
//		if (this->getDet() != 0) {
//
//			Matrix res = this->addIdentMax();
//
//			for (int i = 0; i < res.row; i++) {
//				for (int j = 0; j < res.col; j++) {
//					for (int k = 0; k < res.row; k++) {
//						cout<<
//					}
//				}
//			}
//
//			return res;
//		}
//		else {
//			throw 2;
//		}
//	}
//	catch (int i) {
//		cout << "Error " << i << " determinant = 0";
//		exit(i);
//	}
//}