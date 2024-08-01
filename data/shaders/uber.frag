#version 450 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : require







// TOP 10 lines are reserved in script compiler for version and extensions.
// If you put anything above this line, you're going to have a bad time.

in vec2 TexCoords;
in vec2 LMTexCoords;
flat in uint TexId;
in vec3 WorldPos;
in vec3 Normal;

uniform vec4 color;

#ifdef USE_AMBIENT_CUBE
	uniform vec3 ambientCube[6];
#endif

#ifdef IS_CAUSTIC
	uniform vec4 surfaceColor;
	uniform float causticStrength;
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


#ifdef HAS_ALPHA

	layout (location = 0) out vec4 accum;
	layout (location = 1) out float reveal;
	
#else
	
	layout (location = 0) out vec4 FragColor;

#endif


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
	
		#ifdef HAS_ALPHA
		
			vec4 t = texture(tex[TexId], TexCoords);
			vec4 alpha = vec4(color.a, color.a, color.a, color.a);
			vec4 textureColor = vec4(t.r, t.r, t.r, t.r);
			vec4 colorized = vec4(color.rgb * textureColor.rgb, t.r) * alpha;
			
			float weight = clamp(pow(min(1.0, color.a * 10.0) + 0.01, 3.0) * 1e8 * pow(1.0 - gl_FragCoord.z * 0.9, 3.0), 1e-2, 3e3);
			
			accum = vec4(color.rgb * color.a, color.a) * weight;
			reveal = color.a;
			
		#else
			
			vec4 t = texture(tex[TexId], TexCoords);
			vec4 textureColor = vec4(t.r, t.r, t.r, t.r);
			FragColor = vec4(color.rgb * textureColor.rgb, t.r);
			
		#endif
		
	#else
		
		#ifdef USE_AMBIENT_CUBE
	
			vec3 ac_color = ambientCubeLight(Normal);
			
			#ifdef RGBA_ONLY
			
				vec3 calc_color = ac_color * color.xyz;
				
			#else
				
				vec3 calc_color = texture(tex[TexId], TexCoords).rgb * ac_color * color.xyz;
				
			#endif
			
		#else
			
			#ifdef USE_LIGHTMAP
			
				#ifdef RGBA_ONLY
				
					vec3 calc_color = texture(lmt, LMTexCoords).rgb * color.xyz;
					
				#else
					
					#ifdef IS_CAUSTIC
					
						vec3 causticIntensity = texture(tex[TexId], TexCoords).rgb;
						vec3 causticEffect = causticIntensity * causticStrength;
						vec3 calc_color = (surfaceColor.xyz + causticEffect) * texture(lmt, LMTexCoords).rgb * color.xyz;
						
					#else
						
						vec3 calc_color = texture(tex[TexId], TexCoords).rgb * texture(lmt, LMTexCoords).rgb * color.xyz;
						
					#endif
					
				#endif
				
			#else
				
				#ifdef RGBA_ONLY
				
					vec3 calc_color = color.xyz;
					
				#else
					
					#ifdef IS_CAUSTIC
					
						vec3 causticIntensity = texture(tex[TexId], TexCoords).rgb;
						vec3 causticEffect = causticIntensity * causticStrength;
						vec3 calc_color = (surfaceColor.xyz + causticEffect) * color.xyz;
						
					#else
						
						vec3 calc_color = texture(tex[TexId], TexCoords).rgb * color.xyz;
						
					#endif	
					
				#endif
				
			#endif
			
		#endif
		
		
		#ifdef RGBA_ONLY
		
			float alpha = color.w;
			
		#else
			
			#ifdef IS_CAUSTIC
			
				float alpha = color.w;
				
			#else
				
				float alpha = texture(tex[TexId], TexCoords).a * color.w;
				
			#endif
			
		#endif
		
		
		#ifdef HAS_ALPHA

			float weight = clamp(pow(min(1.0, alpha * 10.0) + 0.01, 3.0) * 1e8 * pow(1.0 - gl_FragCoord.z * 0.9, 3.0), 1e-2, 3e3);
			
			accum = vec4(calc_color.rgb * alpha, alpha) * weight;
			reveal = alpha;

		#else
			
			FragColor = vec4(calc_color, 1.0);
			
		#endif
		
		
		
	#endif

	
}