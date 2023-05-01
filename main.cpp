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

	std::vector<GLfloat*> all_verts;
	all_verts.push_back(origin_vert);
	all_verts.push_back(vertices2);
	std::vector<GLuint> VAOs(all_verts.size());
	std::vector<GLuint> VBOs(all_verts.size());
	std::vector<GLuint> EBOs(all_verts.size());

	GLuint color_u = glGetUniformLocation(shader.ID, "aColor");
	glUniform4f(color_u, 0.09f, 0.05f, 0.02f, 1.0f);
	
	for (int i = 0; i < all_verts.size(); ++i) {
		glGenVertexArrays(1, &VAOs[i]);
		glGenBuffers(1, &VBOs[i]);
		glGenBuffers(1, &EBOs[i]);
	
		glBindVertexArray(VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(origin_vert), all_verts[i], GL_DYNAMIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Activate();

		double crnt_time = glfwGetTime();
		if (crnt_time - prevTime >= 1) {
			rotation += 90.0f;
			prevTime = crnt_time;
			if (rotation >= 360.0f)
				rotation = 0.0f;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(-1.0f, -0.5f, -3.5f));
		proj = glm::perspective(glm::radians(90.0f), (float)(width / height), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shader.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		for (int i = 0; i < all_verts.size(); ++i) {
			glBindVertexArray(VAOs[i]);
			glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}