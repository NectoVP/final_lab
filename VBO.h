#pragma once

#include "glad/glad.h"

class VBO {
	GLuint ID;
public:
	VBO(GLfloat* vertices, GLsizeiptr size);
	~VBO();

	void Bind();
	void UnBind();
};