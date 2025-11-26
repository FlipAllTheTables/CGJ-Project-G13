#include "./Square.hpp"

std::vector<Vertex> SVertices = { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f} };
std::vector<GLubyte> SIndices = { 0, 1, 2, 0, 2, 3 };

Square::Square(GLint MatrixId, GLint ColorId) :
    Shape(MatrixId, ColorId, SVertices, SIndices) {
}
