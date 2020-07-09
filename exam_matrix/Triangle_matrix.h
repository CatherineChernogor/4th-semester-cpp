#pragma once
#include <iostream>
#include "Matrix.h"


 class TriangleMatrix : public Matrix{

public:

    TriangleMatrix(int r) : TriangleMatrix(r, r) { }
    TriangleMatrix(int r, int c) : TriangleMatrix(r,c, NULL) { }
    TriangleMatrix(int r, int c, double ** d) : Matrix(r,c,d) {
        if (d != NULL) {
            this->reshapeToTriangle();
        }
    }

};