#version 450 core









// TOP 10 lines are reserved in script compiler for version and extensions

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec2 aLightMapCoords;
layout (location = 4) in uint aTexId;



out vec2 TexCoords;
flat out uint TexId;


void main()
{
    TexCoords = aTexCoords;
	TexId = aTexId;
	
	//gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	gl_Position = vec4(aPos, 1.0);
}