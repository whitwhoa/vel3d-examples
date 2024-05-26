#version 450 core
#extension GL_ARB_gpu_shader_int64 : require

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec2 aLightMapCoords;
layout (location = 4) in uint aTexId;

#ifdef IS_SKINNED
	// no more than 4 bones can influence a single vertex
	layout (location = 5) in ivec4	aBoneIds[2];
	layout (location = 7) in vec4	aWeights[2];
	
	// uniform buffers can be no larger than 16k!!!
	// ...well...kinda...it's confusing, but 200 should be WAAAAYYYY more than is ever needed or should ever be used
	// and having them in their own self contained block doesn't take away from default uniform components...and on MOST
	// (from what I can tell) desktop implementations the limit for uniform blocks is much much much higher anyway...so this should be fine
	layout (std140, binding = 1) uniform BoneSlots
	{
		mat4 bones[200];
	};
#endif

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
	
	#ifdef IS_SKINNED
		mat4 boneTransform	=	bones[aBoneIds[0][0]] * aWeights[0][0];
		boneTransform		+=	bones[aBoneIds[0][1]] * aWeights[0][1];
		boneTransform		+=	bones[aBoneIds[0][2]] * aWeights[0][2];
		boneTransform		+=	bones[aBoneIds[0][3]] * aWeights[0][3];
		
		boneTransform		+=	bones[aBoneIds[1][0]] * aWeights[1][0];
		boneTransform		+=	bones[aBoneIds[1][1]] * aWeights[1][1];
		boneTransform		+=	bones[aBoneIds[1][2]] * aWeights[1][2];
		boneTransform		+=	bones[aBoneIds[1][3]] * aWeights[1][3];
		
		gl_Position = projection * view * model * boneTransform * vec4(aPos, 1.0);
	#else
		gl_Position = projection * view * model * vec4(aPos, 1.0);
	#endif
	
	
}