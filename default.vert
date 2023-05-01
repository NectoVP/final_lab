#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform vec4 aaa_Color;

out vec4 color;
//out vec4 color2;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform int aCube_or_side_color;

void main()
{
	gl_Position = proj * view * model * vec4(aPos, 1.0); 
	//color = aColor;
	color = vec4(aaa_Color.x, aaa_Color.y , aaa_Color.z, 1.0f);
}