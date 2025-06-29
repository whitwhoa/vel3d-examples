#version 450 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : require







// TOP 10 lines are reserved in script compiler for version and extensions

in vec2 TexCoords;
in vec2 LMTexCoords;
flat in uint TexId;

uniform vec4 tint;
uniform vec3 resolution;
uniform bool enableFXAA;

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



vec3 applyFXAA(sampler2D tex, vec2 uv, vec2 res)
{
    vec2 inverseResolution = 1.0 / res;

    // Sample positions
    vec3 rgbNW = texture(tex, uv + (vec2(-1.0, -1.0) * inverseResolution)).rgb;
    vec3 rgbNE = texture(tex, uv + (vec2( 1.0, -1.0) * inverseResolution)).rgb;
    vec3 rgbSW = texture(tex, uv + (vec2(-1.0,  1.0) * inverseResolution)).rgb;
    vec3 rgbSE = texture(tex, uv + (vec2( 1.0,  1.0) * inverseResolution)).rgb;
    vec3 rgbM  = texture(tex, uv).rgb;

    // Luma (brightness)
    float lumaNW = dot(rgbNW, vec3(0.299, 0.587, 0.114));
    float lumaNE = dot(rgbNE, vec3(0.299, 0.587, 0.114));
    float lumaSW = dot(rgbSW, vec3(0.299, 0.587, 0.114));
    float lumaSE = dot(rgbSE, vec3(0.299, 0.587, 0.114));
    float lumaM  = dot(rgbM,  vec3(0.299, 0.587, 0.114));

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    // Early exit: if contrast is too low, skip FXAA
    if (lumaMax - lumaMin < max(0.0312, lumaMax * 0.125))
        return rgbM;
    
    // Edge detection
    vec2 dir;
    dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));

    float dirReduce = max(
        (lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * 0.5),
        1.0 / 32.0
    );
    float rcpDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);
    dir = clamp(dir * rcpDirMin, vec2(-8.0), vec2(8.0)) * inverseResolution;

    // Sample along the edge direction
    vec3 rgbA = 0.5 * (
        texture(tex, uv + dir * (1.0/3.0 - 0.5)).rgb +
        texture(tex, uv + dir * (2.0/3.0 - 0.5)).rgb
    );
    vec3 rgbB = rgbA * 0.5 + 0.25 * (
        texture(tex, uv + dir * -0.5).rgb +
        texture(tex, uv + dir * 0.5).rgb
    );

    // Choose based on brightness range
    float lumaB = dot(rgbB, vec3(0.299, 0.587, 0.114));
    if ((lumaB < lumaMin) || (lumaB > lumaMax))
        return rgbA;
    else
        return rgbB;
}



void main()
{	
	if (enableFXAA)
	{
		vec3 fxaaResult = applyFXAA(tex[TexId], TexCoords, vec2(resolution.x, resolution.y));
		FragColor = mix(vec4(fxaaResult, 1.0), vec4(tint.rgb, 1.0), tint.a);
	}
	else
	{
		vec4 texColor = texture(tex[TexId], TexCoords);
		FragColor = mix(texColor, vec4(tint.rgb, 1.0), tint.a);
	}
	
}
