#pragma once
#include <iostream>
#include "Matrix.h"


template <class T> class TriangleMatrix : public Matrix<T>{

public:


	TriangleMatrix(int r, int c) : TriangleMatrix(r,c, NULL) { }
	TriangleMatrix(int r, int c, T ** d) {
		std::cout << "12234";
		//Matrix<T>::createMatrix(r, c, d);
	}
	TriangleMatrix(const TriangleMatrix<T>& m) : Matrix< T>(m) {}

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

};
