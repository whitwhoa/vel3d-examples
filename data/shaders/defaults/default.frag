#version 450 core

#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : require

in vec2 TexCoords;
in vec2 LMTexCoords;
flat in uint TexId;
in vec3 WorldPos;
in vec3 Normal;


uniform vec4 color;

// one renderable can use up to 250 textures...which is overkill, but better to set it high
// right now and scale back later if required. Each vertex of a mesh of a renderable will be
// assigned an id which is the id of the texture which it should use, meaning that one draw
// call can draw a renderable that has up to 250 different textures with a single call. in core
// engine, materials are used to track which ids use which textures
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
	vec3 calc_color = texture(tex[TexId], TexCoords).rgb * texture(lmt, LMTexCoords).rgb * color.xyz;
	float alpha = texture(tex[TexId], TexCoords).a == 1 ? color.w : texture(tex[TexId], TexCoords).a * color.w;
	FragColor = vec4(calc_color, alpha);
}
