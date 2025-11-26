#include "./Triangle.hpp"
#include <iostream>

std::vector<Vertex> TVertices = { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f} };
std::vector<GLubyte> TIndices = { 0, 1, 2 };

Triangle::Triangle(GLint MatrixId, GLint ColorId) :
    Shape(MatrixId, ColorId, TVertices, TIndices) {}
