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

void free_all_memory(GLFWwindow** window, std::vector<GLfloat*>& all_verts) {

	glfwDestroyWindow(*window);
	glfwTerminate();

	for (int i = 0; i < all_verts.size(); ++i)
		delete[] all_verts[i];
}

void init_frame(Shader& shader)
{
	glClearColor(1.0f, 0.97f, 0.84f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Activate();
}
