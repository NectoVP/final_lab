#include "EBO.h"
#include <vector>

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	std::vector<GLuint> vec;
	for (int i = 0; i < 72; ++i)
		vec.push_back(indices[i]);
	GLuint* ind = vec.data();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vec.data(), GL_STATIC_DRAW);
	
}

EBO::~EBO()
{
	glDeleteBuffers(1, &ID);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
