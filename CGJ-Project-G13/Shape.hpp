#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <GL/glew.h>
#include "../mgl/mgl.hpp"

#include <vector>
#include <glm/ext.hpp>
#include <mglShader.hpp>

typedef struct {
	GLfloat XYZW[4];
} Vertex;

class Shape {
	protected:
		std::vector<Vertex> Vertices;
		std::vector<GLubyte> Indices;
		GLuint VAO, VBO[2];
		const GLuint POSITION = 0;
		GLint MatrixId;
		GLint ColorId;
	public:
		Shape(GLint MatrixId, GLint ColorId, std::vector<Vertex> Vertices, std::vector<GLubyte> Indices);
		void createBufferObjects();
		void destroyBufferObjects();
		void draw(glm::mat4 transform, glm::vec4 color);
};

#endif /* SHAPE_HPP */