#pragma once

#include <vector>

void generate_first_row(std::vector<GLfloat*>& all_verts) {
	all_verts.resize(27);

	float offset = 0;

	for (int i = 0; i < 3; ++i, offset += 0.6f) {
		all_verts[i] = new GLfloat[24];
		for (int j = 0; j < 24; ++j) {
			all_verts[i][j] = origin_vert[j];
			if (j % 3 == 0) 
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
		all_verts[k] = new GLfloat[24];
		for (int j = 0; j < 24; ++j) {
			all_verts[k][j] = all_verts[i][j];
			if (j % 3 == 2)
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
		all_verts[k] = new GLfloat[24];
		for (int j = 0; j < 24; ++j) {
			all_verts[k][j] = all_verts[i][j];
			if (j % 3 == 1)
				all_verts[k][j] += offset;
		}
	}
}

void create_cubes(std::vector<GLfloat*>& all_verts, std::vector<GLuint>& VAOs) {

	generate_first_row(all_verts);
	generate_first_layer(all_verts);
	generate_whole_cube(all_verts);

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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void generate_first_row_of_colors(std::vector<GLfloat*>& all_color_verts, 
	int global_offset, int start, int axes, bool direction) {

	float offset = 0;

	for (int i = start; i < start + 3; ++i) {
		all_color_verts[i] = new GLfloat[12];
		for (int j = 0; j < 12; ++j) {
			all_color_verts[i][j] = colors_origin[j + global_offset];
			if (j % 3 == axes)
				all_color_verts[i][j] += offset;
		}
		if (direction)
			offset += 0.6f;
		else
			offset -= 0.6f;
	}
}

void generate_first_side_of_colors(std::vector<GLfloat*>& all_color_verts, 
	int global_offset, int start, int axes, bool direction) {

	float offset = 0.6f;
	int k = start + 3;
	int m = 0;
	for (int i = start; m < 6; ++i, ++k, ++m) {
		if (i == start + 3) {
			i = start;
			if (direction)
				offset += 0.6f;
			else
				offset -= 0.6f;
		}
		all_color_verts[k] = new GLfloat[12];
		for (int j = 0; j < 12; ++j) {
			all_color_verts[k][j] = all_color_verts[i][j];
			if (j % 3 == axes)
				all_color_verts[k][j] += offset;
		}
	}
}

void create_colors(std::vector<GLfloat*>& all_color_verts, std::vector<GLuint>& color_VAOs) {
	
	all_color_verts.resize(54);

	generate_first_row_of_colors(all_color_verts, 12*0, 0, 2, true);
	generate_first_side_of_colors(all_color_verts, 12*0, 0, 1, true);

	generate_first_row_of_colors(all_color_verts, 12*1, 9, 0, true);
	generate_first_side_of_colors(all_color_verts, 12*1, 9, 1, true);

	generate_first_row_of_colors(all_color_verts, 12*2, 18, 2, false);
	generate_first_side_of_colors(all_color_verts, 12*2, 18, 1, true);

	generate_first_row_of_colors(all_color_verts, 12*3, 27, 0, false);
	generate_first_side_of_colors(all_color_verts, 12*3, 27, 1, true);

	generate_first_row_of_colors(all_color_verts, 12*4, 36, 0, true);
	generate_first_side_of_colors(all_color_verts, 12*4, 36, 2, true);
	
	generate_first_row_of_colors(all_color_verts, 12*5, 45, 0, true);
	generate_first_side_of_colors(all_color_verts, 12*5, 45, 2, true);
	
	color_VAOs.resize(all_color_verts.size());
	std::vector<GLuint> VBOs(all_color_verts.size());

	GLuint Global_EBO;
	glGenBuffers(1, &Global_EBO);
	
	for (int i = 0; i < all_color_verts.size(); ++i) {
		glGenVertexArrays(1, &color_VAOs[i]);
		glGenBuffers(1, &VBOs[i]);

		glBindVertexArray(color_VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors_origin), all_color_verts[i], GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Global_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(color_indices), color_indices, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}