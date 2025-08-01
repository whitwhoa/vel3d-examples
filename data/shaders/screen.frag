#version 450 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : require







// TOP 10 lines are reserved in script compiler for version and extensions

in vec2 TexCoords;
in vec2 LMTexCoords;
flat in uint TexId;

const int MAX_TEXTURE_SLOTS = 250;
layout (std140, binding = 0) uniform TexturesUBO
{
    sampler2D tex[MAX_TEXTURE_SLOTS];
};

layout (std140, binding = 2) uniform LightMapTextureUBO
{
    sampler2D lmt;
};

out vec4 FragColor;


void main()
{	
	FragColor = texture(tex[TexId], TexCoords).rgba;
}
