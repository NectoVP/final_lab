#include <iostream>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Data.h"
#include "Base.h"
#include "Shader.h"
#include "Utility.h"

void draw(std::vector<GLuint>& VAOs, std::vector<GLuint>& color_VAOs, Shader& shader,
	std::vector<int>& idx, std::vector<std::vector<int>>& color_idx, 
	std::vector<int>& edge, std::vector<int>& corner, bool is_reversed) {
	
	do_math_stuff(shader);

	int color_loc = glGetUniformLocation(shader.ID, "aColor");
	glUniform3f(color_loc, side_colors[0].x, side_colors[0].y, side_colors[0].z);

	for (int i = 0; i < VAOs.size(); ++i) {
		glBindVertexArray(VAOs[i]);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
	}

	if (is_reversed) {
		std::reverse(edge.begin(), edge.end());
		std::reverse(corner.begin(), corner.end());
		std::reverse(idx.begin(), idx.end());
	}

	std::vector <std::vector<int>> new_color_idx(color_idx);

	for (int i = 0, j = 1; j < edge.size(); i++, j++)
		new_color_idx[edge[j]][0] = color_idx[edge[i]][0];	
	
	for (int i = 0, j = 1; j < corner.size(); i++, j++)
		new_color_idx[corner[j]][0] = color_idx[corner[i]][0];

	for (int i = 0, j = 3; j < idx.size(); i+=3, j+=3) {
		new_color_idx[idx[j]][0] = color_idx[idx[i]][0];
		new_color_idx[idx[j+1]][0] = color_idx[idx[i+1]][0];
		new_color_idx[idx[j+2]][0] = color_idx[idx[i+2]][0];
	}

	color_idx = new_color_idx;

	if (is_reversed) {
		std::reverse(edge.begin(), edge.end());
		std::reverse(corner.begin(), corner.end());
		std::reverse(idx.begin(), idx.end());
	}

	for (int i = 0; i < 54; ++i) {
		glBindVertexArray(color_VAOs[i]);
		glm::vec3 cur_color = side_colors[color_idx[i][0]];
		glUniform3f(color_loc, cur_color.x, cur_color.y, cur_color.z);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
	}
}

void make_turn(std::vector<GLuint>& VAOs, std::vector<GLuint>& color_VAOs, Shader& shader,
	std::vector<std::vector<int>>& color_idx, char choice, GLFWwindow** window) {

	if (choice == 'd')
		draw(VAOs, color_VAOs, shader, down, color_idx, down_edge, down_corner, false);

	if (choice == 'r')
		draw(VAOs, color_VAOs, shader, right, color_idx, right_edge, right_corner, false);

	if (choice == 'f')
		draw(VAOs, color_VAOs, shader, front, color_idx, front_edge, front_corner, false);

	if (choice == 'l')
		draw(VAOs, color_VAOs, shader, left, color_idx, left_edge, left_corner, false);

	if (choice == 'u')
		draw(VAOs, color_VAOs, shader, up, color_idx, up_edge, up_corner, false);

	if (choice == 'b')
		draw(VAOs, color_VAOs, shader, back, color_idx, back_edge, back_corner, false);

	if (choice == 'm')
		draw(VAOs, color_VAOs, shader, middle, color_idx, void_v, void_v, false);

	if (choice == 'e')
		draw(VAOs, color_VAOs, shader, equator, color_idx, void_v, void_v, false);

	if (choice == 's')
		draw(VAOs, color_VAOs, shader, side, color_idx, void_v, void_v, false);

	/////////////////////////////////////////////////////////////////////////////////

	if (choice == 'D')
		draw(VAOs, color_VAOs, shader, down, color_idx, down_edge, down_corner, true);

	if (choice == 'R')
		draw(VAOs, color_VAOs, shader, right, color_idx, right_edge, right_corner, true);

	if (choice == 'F')
		draw(VAOs, color_VAOs, shader, front, color_idx, front_edge, front_corner, true);

	if (choice == 'L')
		draw(VAOs, color_VAOs, shader, left, color_idx, left_edge, left_corner, true);

	if (choice == 'U')
		draw(VAOs, color_VAOs, shader, up, color_idx, up_edge, up_corner, true);

	if (choice == 'B')
		draw(VAOs, color_VAOs, shader, back, color_idx, back_edge, back_corner, true);

	if (choice == 'M')
		draw(VAOs, color_VAOs, shader, middle, color_idx, void_v, void_v, true);

	if (choice == 'E')
		draw(VAOs, color_VAOs, shader, equator, color_idx, void_v, void_v, true);

	if (choice == 'S')
		draw(VAOs, color_VAOs, shader, side, color_idx, void_v, void_v, true);

	/////////////////////////////////////////////////////////////////////////////////

	if (choice == 'x') {
		draw(VAOs, color_VAOs, shader, right, color_idx, right_edge, right_corner, false);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, middle, color_idx, void_v, void_v, true);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, left, color_idx, left_edge, left_corner, true);
	}

	if (choice == 'y') {
		draw(VAOs, color_VAOs, shader, equator, color_idx, void_v, void_v, true);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, up, color_idx, up_edge, up_corner, false);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, down, color_idx, down_edge, down_corner, true);
	}

	if (choice == 'z') {
		draw(VAOs, color_VAOs, shader, side, color_idx, void_v, void_v, false);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, front, color_idx, front_edge, front_corner, false);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, back, color_idx, back_edge, back_corner, true);
	}

	if (choice == 'X') {
		draw(VAOs, color_VAOs, shader, right, color_idx, right_edge, right_corner, true);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, middle, color_idx, void_v, void_v, false);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, left, color_idx, left_edge, left_corner, false);
	}

	if (choice == 'Y') {
		draw(VAOs, color_VAOs, shader, equator, color_idx, void_v, void_v, false);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, up, color_idx, up_edge, up_corner, true);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, down, color_idx, down_edge, down_corner, false);
	}

	if (choice == 'Z') {
		draw(VAOs, color_VAOs, shader, side, color_idx, void_v, void_v, true);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, front, color_idx, front_edge, front_corner, true);
		glfwSwapBuffers(*window);
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, back, color_idx, back_edge, back_corner, false);
	}
}

void scramble(std::vector<GLuint>& VAOs, std::vector<GLuint>& color_VAOs, Shader& shader,
	std::vector<std::vector<int>>& color_idx, char choice, GLFWwindow** window, 
	std::list<char>& user_input) {
	
	std::string possible_turns = "lLrRfFuUbBdDxXyYzZ";

	for (int i = 0; i < 40; ++i) {
		char choice = possible_turns[rand() % possible_turns.length()];
		user_input.push_back(choice);
		make_turn(VAOs, color_VAOs, shader, color_idx, choice, &(*window));
		glfwSwapBuffers(*window);
		if (i != 39)
			init_frame(shader);
	}
}

void solve(std::vector<GLuint>& VAOs, std::vector<GLuint>& color_VAOs, Shader& shader,
	std::vector<std::vector<int>>& color_idx, GLFWwindow** window,
	std::list<char>& user_input) {
	int i = 0;
	for (auto it = user_input.rbegin(); it != user_input.rend(); ++i, ++it) {
		char choice = *it;
		if (choice <= 'Z')
			choice += 32;
		else
			choice -= 32;
		make_turn(VAOs, color_VAOs, shader, color_idx, choice, &(*window));
		glfwSwapBuffers(*window);
		if (i != user_input.size() - 1)
			init_frame(shader);
	}
	user_input.clear();
}

int main() {

	srand(time(NULL));

	GLFWwindow* window;
	create_window(&window);

	Shader shader("default.vert", "default.frag");

	std::vector<GLfloat*> all_verts;
	std::vector<GLuint> VAOs;
	create_cubes(all_verts, VAOs);

	std::vector<GLfloat*> all_color_verts;
	std::vector<GLuint> color_VAOs;
	create_colors(all_color_verts, color_VAOs);

	glEnable(GL_DEPTH_TEST);
	
	char choice = '\0';

	std::vector<std::vector<int>> color_idx(all.size(), std::vector<int>(1));
	for (int i = 0; i < all.size(); ++i) {
		color_idx[all[i]][0] = all[i] / 9 + 1;
	}

	std::list<char> user_input;

	while (!glfwWindowShouldClose(window)) {
		init_frame(shader);
		draw(VAOs, color_VAOs, shader, void_v, color_idx, void_v, void_v, false);
		glfwSwapBuffers(window);

		std::cin >> choice;

		if (choice == '{') {
			scramble(VAOs, color_VAOs, shader, color_idx, choice, &window, user_input);
		}
		else if (choice == '}') {
			solve(VAOs, color_VAOs, shader, color_idx, &window, user_input);
		}
		else {
			user_input.push_back(choice);
			make_turn(VAOs, color_VAOs, shader, color_idx, choice, &window);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	free_all_memory(&window, all_verts, all_color_verts);
	return 0;
}