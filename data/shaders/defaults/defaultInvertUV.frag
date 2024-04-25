#version 450 core

#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : require

in vec2 TexCoords;
in vec2 LMTexCoords;
flat in uint TexId;
in vec3 WorldPos;
in vec3 Normal;


uniform vec4 color;


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
	// Now using invertedUVs again
	vec2 invertedUVs = vec2(TexCoords.x, -TexCoords.y);
	vec3 calc_color = texture(tex[TexId], invertedUVs).rgb * texture(lmt, LMTexCoords).rgb * color.rgb;
	float alpha = texture(tex[TexId], invertedUVs).a == 1 ? color.w : texture(tex[TexId], invertedUVs).a * color.w;
	FragColor = vec4(calc_color, alpha);
}
