#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.UnBind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}
