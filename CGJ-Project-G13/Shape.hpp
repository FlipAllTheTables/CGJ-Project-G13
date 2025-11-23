#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <GL/glew.h>

#include <map>
#include <string>
#include <glm/ext.hpp>
#include <mglShader.hpp>

class Shape {
	protected:
		GLuint VAO;
		glm::vec3 color;
		glm::mat4 transform;
		GLint MatrixId;
		GLint ColorId;
	public:
		Shape(GLuint VAO, glm::vec3 color, GLint MatrixId, GLint ColorId, glm::mat4 transform = glm::mat4(1.0f));
		void translate(const glm::vec3& delta);
		void scale(const glm::vec3& scale);
		void rotate(const glm::vec3& axis, float angle);
		virtual void draw() = 0;
};

#endif /* SHAPE_HPP */