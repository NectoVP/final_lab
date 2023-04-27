#pragma once

#include <vector>

GLfloat vertices[] = {
	-0.9f, -0.9f, -0.9f,
	-0.9f, -0.9f, -0.3f,
	-0.3f, -0.9f, -0.3f,
	-0.3f, -0.9f, -0.9f,

	-0.9f, -0.3f, -0.9f,
	-0.9f, -0.3f, -0.3f,
	-0.3f, -0.3f, -0.3f,
	-0.3f, -0.3f, -0.9f,
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

//void generate_first_row(std::vector<std::vector<GLfloat>>& all_verts) {
//	all_verts.resize(3);
//	for (int i = 0; i < 3; ++i) {
//		all_verts[i].resize(24);
//		for (int j = 0; j < 24; j+=3) {
//			all_verts[i][j] = origin_vertex[j];
//			if (j % 3 == 0) 
//				all_verts[i][j] += 0.6f;
//		}
//	}
//}

//void draw_base(std::vector<std::vector<GLfloat>>& all_verts) {
//
//	GLuint *VAO, *VBO, *EBO;
//
//	glGenVertexArrays(all_verts.size(), VAO);
//	glGenBuffers(all_verts.size(), VBO);
//	glGenBuffers(1, EBO);
//
//	glBindVertexArray(*VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//
//	for (auto it = all_verts.begin(); it != all_verts.end(); ++it) {
//
//	}
//}