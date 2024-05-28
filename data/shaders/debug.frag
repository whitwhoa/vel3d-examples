#version 450 core









// TOP 10 lines are reserved in script compiler for version and extensions


in vec3 VertColor;
out vec4 FragColor;


void main() 
{
	FragColor = vec4(VertColor, 1.0);
}