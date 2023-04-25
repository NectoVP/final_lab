#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string get_file_content(const char* filename);

class Shader {
public:
	GLuint ID;
	Shader(const char* vertex_file, const char* fragment_file);
	~Shader();

	void Activate();
private:
	void Compile_errors(GLuint shader, const char* type);
};