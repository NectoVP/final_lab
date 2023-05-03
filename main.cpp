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

//void rotate_by_angle(float angle, Shader& shader, glm::vec3& axes) {
//	glm::mat4 model = glm::mat4(1.0f);
//	glm::mat4 view = glm::mat4(1.0f);
//	glm::mat4 proj = glm::mat4(1.0f);
//
//	model = glm::rotate(model, glm::radians(angle), axes);
//	view = glm::translate(view, glm::vec3(0.0f, -1.5f, -3.5f));
//	proj = glm::perspective(glm::radians(90.0f), (float)(width / height), 0.1f, 100.0f);
//
//	int modelLoc = glGetUniformLocation(shader.ID, "model");
//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//	int viewLoc = glGetUniformLocation(shader.ID, "view");
//	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//	int projLoc = glGetUniformLocation(shader.ID, "proj");
//	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
//}

void draw(std::list<std::tuple<uint64_t, uint64_t, float, glm::vec3>>& turns, std::vector<GLuint>& VAOs,
	std::vector<GLuint>& color_VAOs , Shader& shader) {

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::translate(view, glm::vec3(0.0f, -1.5f, -3.5f));
	proj = glm::perspective(glm::radians(90.0f), (float)(width / height), 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(shader.ID, "model");
	
	int viewLoc = glGetUniformLocation(shader.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projLoc = glGetUniformLocation(shader.ID, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


	uint64_t aa = 1;

	for (int i = 0; i < VAOs.size(); ++i) {
		model = glm::mat4(1.0f);
		int temp = 64 - i - 1;
		for (auto it = turns.begin(); it != turns.end(); ++it) {
			uint64_t c = (((std::get<0>(*it)) & (aa << temp)) >> temp);
			if(c == 1)
				model = glm::rotate(model, glm::radians(std::get<2>(*it)), std::get<3>(*it));
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAOs[i]);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

	}

	for (int i = 0; i < color_VAOs.size(); ++i) {
		model = glm::mat4(1.0f);
		int temp = 64 - i - 1;
		for (auto it = turns.begin(); it != turns.end(); ++it) {
			uint64_t c = (((std::get<1>(*it)) & (aa << temp)) >> temp);
			if (c == 1) {
				//std::cout << i << std::endl;
				model = glm::rotate(model, glm::radians(std::get<2>(*it)), std::get<3>(*it));
			}
		}
		//std::cout << std::endl;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(color_VAOs[i]);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
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

	int choice;

	int cube_start = 0, cube_finish = 0;
	int color_start = 0, color_finish = 0;

	std::list<std::tuple<uint64_t, uint64_t, float, glm::vec3>> turns;

	turns.push_back(std::make_tuple(CUBE_ROTATION, CUBE_ROTATION, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	turns.push_back(std::make_tuple(CUBE_DOWN_TURN, COLOR_DOWN_TURN, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	turns.push_back(std::make_tuple(CUBE_DOWN_TURN, COLOR_DOWN_TURN, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

	while (!glfwWindowShouldClose(window)) {
		
		init_frame(shader);

		get_rotation(prev_time, rotation);
		
		//std::cin >> choice;

		//if (choice == 1) {
		//	cube_start = 0;
		//	cube_finish = 9;
		//	color_start = 0;
		//	color_finish = 21;
		//	axes = glm::vec3(0.0f, 1.0f, 0.0f);
		//	rotation = 90.0f;
		//}

		//if (choice == 2) {
		//	cube_start = 9;
		//	cube_finish = 18;
		//	color_start = 21;
		//	color_finish = 42;
		//	axes = glm::vec3(0.0f, 0.0f, 1.0f);
		//	rotation = 90.0f;
		//}

		draw(turns, VAOs, color_VAOs, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		int a;
		std::cin >> a;
	}

	free_all_memory(&window, all_verts);
	
	return 0;
}