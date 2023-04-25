#pragma once

#include "glad/glad.h"
#include "VBO.h"

class VAO {
	GLuint ID;
public:
	VAO();
	~VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void UnBind();
};