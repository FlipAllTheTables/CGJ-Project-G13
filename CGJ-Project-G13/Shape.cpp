#include "./Shape.hpp"

Shape::Shape(GLuint VAO, glm::vec3 color, GLint MatrixId, GLint ColorId, glm::mat4 transform) {
	this->VAO = VAO;
	this->color = color;
	this->transform = transform;
	this->MatrixId = MatrixId;
	this->ColorId = ColorId;
}

void Shape::translate(const glm::vec3& delta) {
	this->transform = glm::translate(glm::mat4(1.0f), delta) * this->transform;
}

void Shape::scale(const glm::vec3& scale) {
	this->transform = glm::scale(glm::mat4(1.0f), scale) * this->transform;
}

// TODO: Implement using quaternions?
void Shape::rotate(const glm::vec3& axis, float angle) {
	float rad = glm::radians(angle);
	glm::vec3 normAxis = glm::normalize(axis);
	this->transform = glm::rotate(glm::mat4(1.0f), rad, normAxis) * this->transform;
}
