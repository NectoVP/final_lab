#include "Utility.h"

static const int width = 800;
static const int height = 800;

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

void free_all_memory(GLFWwindow** window, std::vector<GLfloat*>& all_verts,
	std::vector<GLfloat*>& all_color_verts) {

	glfwDestroyWindow(*window);
	glfwTerminate();

	for (int i = 0; i < all_verts.size(); ++i)
		delete[] all_verts[i];

	for (int i = 0; i < all_color_verts.size(); ++i)
		delete[] all_color_verts[i];
}

void init_frame(Shader& shader)
{
	glClearColor(1.0f, 0.97f, 0.84f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Activate();
}

void do_math_stuff(Shader& shader) {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	int modelLoc = glGetUniformLocation(shader.ID, "model");
	int viewLoc = glGetUniformLocation(shader.ID, "view");
	int projLoc = glGetUniformLocation(shader.ID, "proj");

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.5f));
	proj = glm::perspective(glm::radians(90.0f), (float)(width / height), 0.1f, 100.0f);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(35.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}