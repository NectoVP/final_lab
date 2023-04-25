#pragma once

#include "glad/glad.h"

class EBO {
	GLuint ID;
public:
	EBO(GLuint* indices, GLsizeiptr size);
	~EBO();

	void Bind();
	void UnBind();
};