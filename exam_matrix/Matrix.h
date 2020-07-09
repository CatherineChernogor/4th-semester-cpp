#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>


class Matrix {

protected:
	int col;
	int row;
	double** mat;
	int det_sign;

	Matrix getMinor(int a, int  b);

public:
	Matrix(int r) : Matrix(r, r) {}
	Matrix(int r, int c) : Matrix(r, c, NULL) {}
	Matrix(int r, int c, double** d) { *this = createMatrix(r, c, d); }

	Matrix(const Matrix& m);

	~Matrix();

	Matrix& operator=(const Matrix& m);
	Matrix operator*(const Matrix& m) const;

	double getDet();            //determinant
	Matrix getInv();            //inverse matrix
	Matrix getTransp();         //transposed matrix
	bool isDegen();             // is degenerate matrix

	void fout(std::string filename);
	void fin(std::string filename);
	friend std::ostream& operator<<(std::ostream& out, Matrix& m);

	int getRow() { return this->row; }
	int getCol() { return this->col; }

	bool isSquare() { return this->row == this->col ? true : false; }

	Matrix createMatrix(int r, int c, double** d);

	void switchRows(int from, int to);
	void reshapeToTriangle();
};


Matrix::Matrix(const Matrix& m) { //copy constructor
	this->row = m.row;
	this->col = m.col;
	this->det_sign = m.det_sign;


	this->mat = new double* [this->row];
	for (int i = 0; i < this->row; i++) {
		this->mat[i] = new double[this->col];
	}

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			this->mat[i][j] = m.mat[i][j];
		}
	}
}

Matrix::~Matrix() { //destructor
	for (int i = 0; i < this->row; i++) {
		delete[] this->mat[i];
	}
	delete[] this->mat;
}

Matrix& Matrix::operator=(const Matrix& m) {
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
Matrix Matrix::operator*(const Matrix& m) const {
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

double Matrix::getDet() {

	if (this->isSquare()) {

		if (this->row == 1) return this->mat[0][0];

		else if (this->row == 2)
			return (this->mat[0][0] * this->mat[1][1]) - (this->mat[0][1] * this->mat[1][0]);

		if (this->row > 2) {

			Matrix res(*this);
			double det = 1;

			res.reshapeToTriangle();
			//std::cout <<"reshape to triangle\n"<< res<<"\n\n\n";

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
Matrix Matrix::getInv() {
	try {
		if (!this->isDegen()) {
			Matrix res(this->row, this->col);

			for (int i = 0; i < this->row; i++) {		//create union matrix
				for (int j = 0; j < this->col; j++) {
					Matrix minor = this->getMinor(i, j);
					double d_minor = minor.getDet();
					int sign = ((i + j) % 2 == 0 ? 1 : -1);

					//std::cout << "minor " << i + 1 << ' ' << j + 1 << "\n" << minor << "det: " << d_minor << '\n' << "sign: " << sign << "\n\n";

					res.mat[i][j] = sign * d_minor;
				}
			}
			//std::cout << "\n\n";

			double det = this->getDet();

			//std::cout << "union\n" << res << "\n\n\ntransponsed\n";

			res = res.getTransp();						//union and transposed

			//std::cout << res << "\n\n\ndet\n" << det << "\n\n\n";

			for (int i = 0; i < this->row; i++) {
				for (int j = 0; j < this->col; j++) {
					res.mat[i][j] /= det;
				}
			}

			//std::cout <<"inversed\n"<< res << "\n\n\n";

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
Matrix Matrix::getTransp() {

	Matrix res(*this);

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			res.mat[j][i] = this->mat[i][j];
		}
	}
	return res;
}
bool Matrix::isDegen() {
	return this->getDet() == 0 ? true : false;
}

void Matrix::fout(std::string filename) {

	std::ofstream out(filename);
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			out << this->mat[i][j] << ' ';
		}
		out << '\n';
	}
	out.close();
}
void Matrix::fin(std::string filename) {

	std::ifstream in(filename);
	double n;
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			in >> n;
			this->mat[i][j] = n;
		}
	}
	in.close();
}
std::ostream& operator<<(std::ostream& out, Matrix& m) {

	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.col; j++) {
			std::cout.precision(4);
			out << std::setw(6) << m.mat[i][j] << " ";
		}
		out << '\n';
	}
	return out;
}

Matrix Matrix::getMinor(int a, int  b) {

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

Matrix Matrix::createMatrix(int r, int c, double** d) {
	row = r;
	col = c;
	det_sign = 1;

	mat = new double* [row];
	for (int i = 0; i < row; i++) {
		mat[i] = new double[col];
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

void Matrix::switchRows(int from, int to) {

	double* rowFrom = new double[this->row];
	double* rowTo = new double[this->row];

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
void Matrix::reshapeToTriangle() {

	//Matrix res(*this);
	//std::cout << "normal\n" << *this << "\n\n\n";
	int s = 0;
	for (; s < this->row; s++) {
		if (this->mat[s][0] != 0) break;
	}

	//Если поменять местами две строки матрицы, то определитель матрицы поменяет знак.
	if (s != 0) {
		//std::cout << res.getCol() << res.getRow() << '\n';
		this->switchRows(0, s);
		this->det_sign *= -1;
	}
	//std::cout << "switched\n" << *this << "\n\n\n";

	for (int i = 1; i < this->col; i++)
		for (int j = i; j < this->col; j++) {


			for (int k = this->col - 1; k >= 0; k--){
				float koef = this->mat[j][i - 1] / this->mat[i - 1][i - 1];

				this->mat[j][k] -= koef * this->mat[i - 1][k];
				}
		}

	//*this = res;
}