#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Base.h"
#include "Shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

const int width = 800;
const int height = 800;

void create_window(GLFWwindow** window) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	*window = glfwCreateWindow(width, height, "test", NULL, NULL);
	if (*window == NULL) {
		std::cerr << "Failed window construction" << std::endl;
		glfwTerminate();
		exit(0);
	}

	glfwMakeContextCurrent(*window);
	gladLoadGL();
	glViewport(0, 0, width, height);
}

int main() {
	GLFWwindow* window;
	create_window(&window);
	
	Shader shader("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	GLuint color_u = glGetUniformLocation(shader.ID, "aColor");
	glUniform4f(color_u, 0.09f, 0.05f, 0.02f, 1.0f);
	
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();
	
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Activate();

		double crnt_time = glfwGetTime();
		if (crnt_time - prevTime >= 1 / 60) {
			rotation += 0.05f;
			prevTime = crnt_time;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0, 1.0f, 0.0f));
		
		view = glm::translate(view, glm::vec3(0.5f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(120.0f), (float)(width / height), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shader.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}