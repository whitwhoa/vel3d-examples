#version 450 core

#extension GL_ARB_gpu_shader_int64 : require

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec2 aLightMapCoords;
layout (location = 4) in uint aTexId;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 TexCoords;
out vec2 LMTexCoords;
flat out uint TexId;
out vec3 WorldPos;
out vec3 Normal;

void main()
{
    TexCoords = aTexCoords;
	LMTexCoords = aLightMapCoords;
	TexId = aTexId;
	
	WorldPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalize(mat3(model) * aNormal);
	
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}