#version 450 core









// TOP 10 lines are reserved in script compiler for version and extensions

layout (location = 0) in vec3 position;

void main()
{
	gl_Position = vec4(position, 1.0f);
}