#version 450 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : require

in vec2 TexCoords;
in vec2 LMTexCoords;
flat in uint TexId;
in vec3 WorldPos;
in vec3 Normal;


uniform vec4 color;

#ifdef USE_AMBIENT_CUBE
	uniform vec3 ambientCube[6];
#endif

// one renderable can use up to 250 textures...which is overkill, but better to set it high
// right now and scale back later if required. Each vertex of a mesh of a renderable will be
// assigned an id which is the id of the texture which it should use, meaning that one draw
// call can draw a renderable that has up to 250 different textures with a single call. in core
// engine, materials are used to track which ids use which textures
layout (std140, binding = 0) uniform TexturesUBO
{
    sampler2D tex[250];
};

layout (std140, binding = 2) uniform LightMapTextureUBO
{
    sampler2D lmt;
};



out vec4 FragColor;



#ifdef USE_AMBIENT_CUBE
	vec3 ambientCubeLight(vec3 worldNormal)
	{
		vec3 nSquared = worldNormal * worldNormal;
		ivec3 isNegative = ivec3(lessThan(worldNormal, vec3(0.0)));
		vec3 returnColor = nSquared.x * ambientCube[isNegative.x] +
						   nSquared.y * ambientCube[isNegative.y + 2] +
						   nSquared.z * ambientCube[isNegative.z + 4];
		return returnColor;
	}
#endif

void main()
{	
	#ifdef IS_TEXT
		vec4 t = texture(tex[TexId], TexCoords);
		vec4 alpha = vec4(color.w, color.w, color.w, color.w);
		vec4 textureColor = vec4(t.r, t.r, t.r, t.r);
		vec4 colorized = vec4(color.xyz * textureColor.xyz, t.r);
		
		FragColor = colorized * alpha;
	#else
		#ifdef USE_AMBIENT_CUBE
			vec3 ac_color = ambientCubeLight(Normal);
			#ifdef USE_LIGHTMAP
				vec3 calc_color = texture(tex[TexId], TexCoords).rgb * texture(lmt, LMTexCoords).rgb * ac_color * color.xyz;
			#else
				vec3 calc_color = texture(tex[TexId], TexCoords).rgb * ac_color * color.xyz;
			#endif
		#else
			#ifdef USE_LIGHTMAP
				vec3 calc_color = texture(tex[TexId], TexCoords).rgb * texture(lmt, LMTexCoords).rgb * color.xyz;
			#else
				vec3 calc_color = texture(tex[TexId], TexCoords).rgb * color.xyz;
			#endif
		#endif
		
		float alpha = texture(tex[TexId], TexCoords).a == 1 ? color.w : texture(tex[TexId], TexCoords).a * color.w;
		FragColor = vec4(calc_color, alpha);
	#endif

	
}
