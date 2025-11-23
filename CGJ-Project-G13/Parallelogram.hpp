#ifndef PARALLELOGRAM_HPP
#define PARALLELOGRAM_HPP

#include "./Shape.hpp"

class Parallelogram : public Shape {
public:
	Parallelogram(GLuint VAO, glm::vec3 color, GLint MatrixId, GLint ColorId, glm::mat4 transform = glm::mat4(1.0f));
	void draw() override;
};

#endif /* PARALLELOGRAM_HPP */