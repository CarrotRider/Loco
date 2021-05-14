#version 330 core
// Pass Geometry

// IO
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;

// Materials
struct Material
{
	bool bDiffuseTex;
	vec3 DiffuseColor;
	sampler2D DiffuseTexture_0;

	bool bSpecularTex;
	vec3 SpecularColor;
	sampler2D SpecularTexture_0;

	bool bNormalTex;
	vec3 Normal;
	sampler2D NormalTexture_0;

	float Shininess;
};

uniform Material material;

// Other Uniforms
uniform vec3 viewPos;

void main()
{
	gPosition = FragPos;
	
	if(material.bDiffuseTex)
		gAlbedoSpec.rgb = texture(material.DiffuseTexture_0, TexCoord).rgb;
	else
		gAlbedoSpec.rgb = material.DiffuseColor;

	if(material.bSpecularTex)
		gAlbedoSpec.a = texture(material.SpecularTexture_0, TexCoord).r;
	else
		gAlbedoSpec.a = material.SpecularColor.r;

	if(material.bNormalTex)
		gNormal = normalize(Normal);
	else
		gNormal = material.Normal;
}