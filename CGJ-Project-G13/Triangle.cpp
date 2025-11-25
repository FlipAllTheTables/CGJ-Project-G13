#include "./Triangle.hpp"
#include <iostream>

Triangle::Triangle(GLint MatrixId, GLint ColorId) :
    Shape(MatrixId, ColorId, { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f} }, { 0, 1, 2 }) {}
