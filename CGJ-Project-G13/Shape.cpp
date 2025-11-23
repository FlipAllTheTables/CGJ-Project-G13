#include "./Shape.hpp"

Shape::Shape(GLuint VAO, glm::vec3 color, GLint MatrixId, GLint ColorId, glm::mat4 transform) {
	this->VAO = VAO;
	this->color = color;
	this->transform = transform;
	this->MatrixId = MatrixId;
	this->ColorId = ColorId;
}

void Shape::translate(const glm::vec3& delta) {
	this->transform = glm::translate(this->transform, delta);
}

void Shape::scale(const glm::vec3& scale) {
	this->transform = glm::scale(Shape::transform, scale);
}

// TODO: Implement using quaternions?
void Shape::rotate(const glm::vec3& axis, float angle) {
	float rad = glm::radians(angle);
	this->transform = glm::rotate(this->transform, angle, axis);
}
