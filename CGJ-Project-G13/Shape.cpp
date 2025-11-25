#include "./Shape.hpp"
#include <iostream>

Shape::Shape(GLint MatrixId, GLint ColorId, std::vector<Vertex> Vertices, std::vector<GLubyte> Indices) {
    this->Vertices = Vertices;
    this->Indices = Indices;
    createBufferObjects();
	this->MatrixId = MatrixId;
	this->ColorId = ColorId;
}

void Shape::createBufferObjects() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        glGenBuffers(2, VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                reinterpret_cast<GLvoid*>(0));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * Indices.size(), Indices.data(),
                GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, VBO);
}

void Shape::destroyBufferObjects() {
    glBindVertexArray(VAO);
    glDisableVertexAttribArray(POSITION);
    glDeleteVertexArrays(1, &VAO);
    glBindVertexArray(0);
}

void Shape::draw(glm::mat4 transform, glm::vec4 color) {
    glBindVertexArray(this->VAO);

    glUniformMatrix4fv(this->MatrixId, 1, GL_FALSE, glm::value_ptr(transform));
    glUniform4fv(this->ColorId, 1, glm::value_ptr(color));
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(0));

    glBindVertexArray(0);
}