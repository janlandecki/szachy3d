#version 410 core

uniform UniformData
{
	float movement;
};


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;


layout(location = 0) out vec3 vertOutColor;

void main()
{
	gl_Position.xyz = position + movement;

	gl_Position.w = 2;

	vertOutColor = color;
}