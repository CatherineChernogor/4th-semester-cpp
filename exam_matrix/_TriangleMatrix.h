#pragma once
#include <iostream>
#include "_Matrix.h"


 class TriangleMatrix : public Matrix{

public:

    TriangleMatrix(int r) : TriangleMatrix(r, r) { }
    TriangleMatrix(int r, int c) : TriangleMatrix(r,c, NULL) { }
    TriangleMatrix(int r, int c, double ** d) : Matrix(r,c,d) {
        if (d != NULL) {
            this->reshapeToTriangle();
        }
    }

    TriangleMatrix(const Matrix& m) :Matrix(m) {}

    void fin(std::string filename) { 
        Matrix::fin(filename);
        this->reshapeToTriangle();

    }

    TriangleMatrix& operator=(const TriangleMatrix& m) {
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