#include "./Square.hpp"

Square::Square(GLuint VAO, glm::vec3 color, GLint MatrixId, GLint ColorId, glm::mat4 transform) : Shape(VAO, color, MatrixId, ColorId, transform) {}

void Square::draw() {
    glBindVertexArray(this->VAO);

    glUniformMatrix4fv(this->MatrixId, 1, GL_FALSE, glm::value_ptr(this->transform));
    glUniform4fv(this->ColorId, 1, glm::value_ptr(this->color));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(0));

    glBindVertexArray(0);
    return;
}
