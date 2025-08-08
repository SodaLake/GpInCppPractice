// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// Inputs from vertex shader
// Tex coord
in vec2 fragTexCoord;
// Normal (in world space)
in vec3 fragNormal;
// Position (in world space)
in vec3 fragWorldPos;

// This corresponds to the output color to the color buffer
out vec4 outColor;

// This is used for the texture sampling
uniform sampler2D uTexture;

// Create a struct for directional light
struct DirectionalLight
{
	// Direction of light
	vec3 mDirection;
	// Diffuse color
	vec3 mDiffuseColor;
	// Specular color
	vec3 mSpecColor;
};

struct PointLight
{
	//광원의 위치
	vec3 mPosition;
	//난반사 색상
	vec3 mDiffuseColor;
	//정반사 색상
	vec3 mSpecColor;
	//반경 범위
	float mRadius;
};

// Uniforms for lighting
// Camera position (in world space)
uniform vec3 uCameraPos;
// Specular power for this surface
uniform float uSpecPower;
// Ambient light level
uniform vec3 uAmbientLight;

// Directional Light
uniform DirectionalLight uDirLight;

//Point Light[4]
uniform PointLight uPointLight;

void main()
{
	// Surface normal
	vec3 N = normalize(fragNormal);
	// Vector from surface to light
	vec3 L = normalize(-uDirLight.mDirection);
	// Vector from surface to camera
	vec3 V = normalize(uCameraPos - fragWorldPos);
	// Reflection of -L about N
	vec3 R = normalize(reflect(-L, N));

	
	float lng = length(uPointLight.mPosition - fragWorldPos);

	vec3 L2 = normalize(uPointLight.mPosition - fragWorldPos);
	vec3 R2 = normalize(reflect(-L2, N));


	// Compute phong reflection
	vec3 Phong = uAmbientLight;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;
		vec3 Specular = uDirLight.mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);
		Phong += Diffuse + Specular;
	}
	
	float NdotL2 = dot(N, L2);
	if (NdotL2 > 0 && lng < uPointLight.mRadius)
	{
		vec3 Diffuse = uPointLight.mDiffuseColor * NdotL2;
		vec3 Specular = uPointLight.mSpecColor * pow(max(0.0, dot(R2, V)), uSpecPower);
		Phong += Diffuse + Specular;
	}


	// Final color is texture color times phong light (alpha = 1)
    outColor = texture(uTexture, fragTexCoord) * vec4(Phong, 1.0f);
}
