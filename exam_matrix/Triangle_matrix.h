#pragma once
#include <iostream>
#include "Matrix.h"
using namespace std;


template<class T> class TriangleMatrix : public Matrix<class T>
{
public:

	TriangleMatrix() : Matrix<class T>() {}
	TriangleMatrix(int r, int c) : Matrix<class T>(r, c) {}
	TriangleMatrix(int r, int c, float** d) : Matrix<class T>(r, c, d) {}
	TriangleMatrix(const TriangleMatrix<T>& m) : Matrix<class T>(m) {}

	TriangleMatrix<T> reshapeToTriangle()
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
	void ValueSqr() // возводит value в квадрат. Без спецификатора доступа protected эта функция не могла бы изменить значение value
	{
		value *= value;
	}
};
