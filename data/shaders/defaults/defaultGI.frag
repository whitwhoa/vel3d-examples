#version 450 core

#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : require

in vec2 TexCoords;
in vec2 LMTexCoords;
flat in uint TexId;
in vec3 WorldPos;
in vec3 Normal;


uniform vec4 color;
uniform vec3 giColors[6];


const int MAX_TEXTURE_SLOTS = 250;
layout (std140, binding = 0) uniform TexturesUBO
{
    sampler2D tex[MAX_TEXTURE_SLOTS];
};

// if you're using this shader, there should be no lightmap for this fragment as 
// GI should only be applied to dynamic objects which will not have a lightmap,
// might be able to remove down the road, but leaving this here now until we confirm
// what we're doing will work, just FYI
layout (std140, binding = 2) uniform LightMapTextureUBO
{
    sampler2D lmt;
};


out vec4 FragColor;








vec3 giLight(vec3 worldNormal)
{
    vec3 nSquared = worldNormal * worldNormal;
    ivec3 isNegative = ivec3(lessThan(worldNormal, vec3(0.0)));
    vec3 returnColor = nSquared.x * giColors[isNegative.x] +
                       nSquared.y * giColors[isNegative.y + 2] +
                       nSquared.z * giColors[isNegative.z + 4];
    return returnColor;
}


void main()
{	

	vec3 gi_color = giLight(Normal);
	
	vec3 calc_color = texture(tex[TexId], TexCoords).rgb * texture(lmt, LMTexCoords).rgb * gi_color * color.xyz;
	//vec3 calc_color = texture(tex[TexId], TexCoords).rgb * texture(lmt, LMTexCoords).rgb * color.xyz;
	float alpha = texture(tex[TexId], TexCoords).a == 1 ? color.w : texture(tex[TexId], TexCoords).a * color.w;
	FragColor = vec4(calc_color, alpha);



}
