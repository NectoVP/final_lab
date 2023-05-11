#include "Utility.h"

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

	//for (int i = 0; i < all_verts.size(); ++i)
		//delete[] all_verts[i];
}

void get_rotation(double prev_time, float& rotation)
{
	double crnt_time = glfwGetTime();
	if (crnt_time - prev_time >= 1 / 15) {
		rotation += 0.05f;
		prev_time = crnt_time;
		if (rotation >= 360.0f)
			rotation = 0.0f;
	};
}

void init_frame(Shader& shader)
{
	glClearColor(1.0f, 0.97f, 0.84f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Activate();
}
