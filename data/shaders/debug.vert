#version 450 core









// TOP 10 lines are reserved in script compiler for version and extensions

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 vp;

out vec3 VertColor;

void main() 
{
	VertColor = aColor;
	gl_Position = vp * vec4(aPos, 1.0);
}