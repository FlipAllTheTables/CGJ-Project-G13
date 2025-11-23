#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "./Shape.hpp"

class Square : public Shape {
public:
	Square(GLuint VAO, glm::vec3 color, GLint MatrixId, GLint ColorId, glm::mat4 transform = glm::mat4(1.0f));
	void draw() override;
};

#endif /* SQUARE_HPP */