#include "./Parallelogram.hpp"

std::vector<Vertex> PVertices = { {-1.0f, -0.5f, 0.0f, 1.0f}, {0.0f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {1.0f, 0.5f, 0.0f, 1.0f} };
std::vector<GLubyte> PIndices = { 0, 1, 2, 1, 3, 2 };

Parallelogram::Parallelogram(GLint MatrixId, GLint ColorId) :
	Shape(MatrixId, ColorId, PVertices, PIndices) {}

