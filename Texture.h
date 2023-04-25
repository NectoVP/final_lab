#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include "Shader.h"

class Texture
{
	GLuint ID;
public:
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	~Texture();

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void UnBind();
};