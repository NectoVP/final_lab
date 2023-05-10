#include <iostream>
#include <set>
#include <list>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Data.h"
#include "Base.h"
#include "Shader.h"
#include "Utility.h"

void draw(std::list<std::tuple<uint64_t, float, glm::vec3>>& turns, std::vector<GLuint>& VAOs,
	std::vector<GLuint>& color_VAOs , Shader& shader) {

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	int modelLoc = glGetUniformLocation(shader.ID, "model");
	int viewLoc = glGetUniformLocation(shader.ID, "view");
	int projLoc = glGetUniformLocation(shader.ID, "proj");

	view = glm::translate(view, glm::vec3(0.0f, -1.5f, -3.5f));
	proj = glm::perspective(glm::radians(90.0f), (float)(width / height), 0.1f, 100.0f);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	
	for (int i = 0; i < VAOs.size(); ++i) {
		glBindVertexArray(VAOs[i]);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
	}


	uint64_t bb = 1;

	for (int i = 0; i < color_VAOs.size(); ++i) {
		model = glm::mat4(1.0f);
		int temp = 64 - i - 1;
		for (auto it = turns.begin(); it != turns.end(); ++it) {
			uint64_t c = (((std::get<0>(*it)) & (bb << temp)) >> temp);
			if (c == 1) {
				model = glm::rotate(model, glm::radians(std::get<1>(*it)), std::get<2>(*it));
			}
		}
		//std::cout << std::endl;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(color_VAOs[i]);
		//if (i == 0 || i == 1 || i == 2)
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
	}
}

void show_binary(uint64_t j) {
	std::cout << std::endl;
	uint64_t temp = 1;
	for (int i = 63; i >= 0; --i) {
		uint64_t c = (j & (temp << i)) >> i;
		std::cout << c;
		if (i % 4 == 0)
			std::cout << " ";
	}
}

int main() {
	GLFWwindow* window;
	create_window(&window);

	Shader shader("default.vert", "default.frag");

	std::vector<GLfloat*> all_verts;
	std::vector<GLuint> VAOs;
	create_cubes(all_verts, VAOs);

	std::vector<GLfloat*> all_color_verts;
	std::vector<GLuint> color_VAOs;
	create_colors(all_color_verts, color_VAOs);

	float rotation = 45.0f;
	double prev_time = glfwGetTime();

	glEnable(GL_DEPTH_TEST);
	
	glm::vec3 axes(0.0f, 1.0f, 0.0f);

	char choice;

	std::list<std::tuple<uint64_t, float, glm::vec3>> turns;

	turns.push_back(std::make_tuple(CUBE_ROTATION, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	
	while (!glfwWindowShouldClose(window)) {
		
		init_frame(shader);

		get_rotation(prev_time, rotation);

		draw(turns, VAOs, color_VAOs, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		std::cin >> choice;

		if (choice == 'x') {
			turns.push_back(std::make_tuple(CUBE_ROTATION, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		}

		if (choice == 'd') {
			turns.push_back(std::make_tuple(COLOR_DOWN_TURN, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		}

		if (choice == 'r') {
			turns.push_back(std::make_tuple(COLOR_RIGHT_TURN, -90.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
		}

		if (choice == 'f') {
			turns.push_back(std::make_tuple(COLOR_FRONT_TURN, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
		}

		if (choice == 'y') {
			turns.push_back(std::make_tuple(COLOR_RIGHT_TURN, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
		}
	}

	free_all_memory(&window, all_verts);
	
	return 0;
}