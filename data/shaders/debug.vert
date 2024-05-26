#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 vp;

out vec3 VertColor;

void main() 
{
	gl_Position = vp * vec4(aPos, 1.0);
    VertColor = aColor;
}