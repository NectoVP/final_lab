#include "Shader.h"

std::string get_file_content(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string content;
		in.seekg(0, std::ios::end);
		content.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&content[0], content.size());
		in.close();
		return(content);
	}
	throw std::exception("failed reading shader");
}

Shader::Shader(const char* vertex_file, const char* fragment_file)
{
	std::string vertex_code = get_file_content(vertex_file);
	std::string fragment_code = get_file_content(fragment_file);

	const char* temp_vertex_handler = vertex_code.c_str();
	const char* temp_fragment_handler = fragment_code.c_str();

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &temp_vertex_handler, NULL);
	glCompileShader(vertex_shader);
	Compile_errors(vertex_shader, "VERTEX");

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &temp_fragment_handler, NULL);
	glCompileShader(fragment_shader);
	Compile_errors(fragment_shader, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, fragment_shader);

	glLinkProgram(ID);
	Compile_errors(ID, "PROGRAM");

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::Compile_errors(GLuint shader, const char* type) {
	GLint has_compiled;
	char info_log[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &has_compiled);
		if (has_compiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, info_log);
			std::cout << "SHADER_COMPILATION_ERROR: " << type << "\n" << info_log << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &has_compiled);
		if (has_compiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, info_log);
			std::cout << "SHADER_LINKING_ERROR: " << type << "\n" << info_log << std::endl;
		}
	}
}