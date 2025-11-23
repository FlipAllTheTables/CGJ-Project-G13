#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "./Shape.hpp"

class Triangle : public Shape {
public:
	Triangle(GLuint VAO, glm::vec3 color, GLint MatrixId, GLint ColorId, glm::mat4 transform = glm::mat4(1.0f));
	void draw() override;
};

#endif /* TRIANGLE_HPP */