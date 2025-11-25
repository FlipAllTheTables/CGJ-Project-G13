#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "./Shape.hpp"

class Triangle : public Shape {
	public:
		Triangle(GLint MatrixId, GLint ColorId);
};

#endif /* TRIANGLE_HPP */