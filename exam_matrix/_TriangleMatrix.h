#pragma once
#include <iostream>
#include "_Matrix.h"


 template <class T> class TriangleMatrix : public Matrix<T>{

public:

    TriangleMatrix<T>(int r) : TriangleMatrix<T>(r, r) { }
    TriangleMatrix<T>(int r, int c) : TriangleMatrix<T>(r,c, NULL) { }
    TriangleMatrix<T>(int r, int c, double ** d) : Matrix<T>(r,c,d) {
        if (d != NULL) {
            this->reshapeToTriangle();
        }
    }
                  
    TriangleMatrix<T>(const Matrix<T>& m) :Matrix<T>(m) {}

    void fin(std::string filename) { 
        Matrix<T>::fin(filename);
        this->reshapeToTriangle();
    }

    TriangleMatrix<T>& operator=(const TriangleMatrix<T>& m) {
        try {
            if (m.row == this->row && m.col == this->col) {
                for (int i = 0; i < this->row; i++) {
                    for (int j = 0; j < this->col; j++) {
                        this->mat[i][j] = m.mat[i][j];
                    }
                }
                this->reshapeToTriangle();
            }
            else
                throw - 1;
        }
        catch (int i) {
            std::cout << "Error " << i << " invalid res.mat dimention";
            exit(i);
        }
    }
};