#pragma once

#include <vector>

GLfloat origin_vert[] = {
	-0.9f, -0.9f, -0.9f, 1.0f, 1.0f, 1.0f,
	-0.9f, -0.9f, -0.3f, 1.0f, 1.0f, 1.0f,
	-0.3f, -0.9f, -0.3f, 1.0f, 1.0f, 1.0f,
	-0.3f, -0.9f, -0.9f, 1.0f, 1.0f, 1.0f,
						 
	-0.9f, -0.3f, -0.9f, 1.0f, 1.0f, 1.0f,
	-0.9f, -0.3f, -0.3f, 1.0f, 1.0f, 1.0f,
	-0.3f, -0.3f, -0.3f, 1.0f, 1.0f, 1.0f,
	-0.3f, -0.3f, -0.9f, 1.0f, 1.0f, 1.0f,
};

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 4, 5,
	1, 2, 6,
	5, 6, 1,
	2, 3, 6,
	3, 6, 7,
	3, 0, 7,
	0, 7, 4,
	6, 7, 4,
	5, 6, 4,
};

void generate_first_row(std::vector<GLfloat*>& all_verts) {
	all_verts.resize(27);

	float offset = 0;

	for (int i = 0; i < 3; ++i, offset += 0.6f) {
		all_verts[i] = new GLfloat[48];
		for (int j = 0; j < 48; ++j) {
			all_verts[i][j] = origin_vert[j];
			if (j % 6 == 0) 
				all_verts[i][j] += offset;
		}
	}	
}

void generate_first_layer(std::vector<GLfloat*>& all_verts) {
	float offset = 0.6f;
	int k = 3;
	int m = 0;
	for (int i = 0; m < 6; ++i, ++k, ++m) {
		if (i == 3) {
			i = 0;
			offset += 0.6f;
		}
		all_verts[k] = new GLfloat[48];
		for (int j = 0; j < 48; ++j) {
			all_verts[k][j] = all_verts[i][j];
			if (j % 6 == 2)
				all_verts[k][j] += offset;
		}
	}
}

void generate_whole_cube(std::vector<GLfloat*>& all_verts) {
	float offset = 0.6f;
	int k = 9;
	int m = 0;
	for (int i = 0; m < 18; ++i, ++k, ++m) {
		if (i == 9) {
			i = 0;
			offset += 0.6f;
		}
		all_verts[k] = new GLfloat[48];
		for (int j = 0; j < 48; ++j) {
			all_verts[k][j] = all_verts[i][j];
			if (j % 6 == 1)
				all_verts[k][j] += offset;
		}
	}
}

void create_cubes(std::vector<GLfloat*>& all_verts, std::vector<GLuint>& VAOs) {

	generate_first_row(all_verts);
	generate_first_layer(all_verts);
	generate_whole_cube(all_verts);

	//all_verts.push_back(origin_vert);

	VAOs.resize(all_verts.size());
	std::vector<GLuint> VBOs(all_verts.size());
	
	GLuint Global_EBO;
	glGenBuffers(1, &Global_EBO);

	for (int i = 0; i < all_verts.size(); ++i) {
		glGenVertexArrays(1, &VAOs[i]);
		glGenBuffers(1, &VBOs[i]);

		glBindVertexArray(VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(origin_vert), all_verts[i], GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Global_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}