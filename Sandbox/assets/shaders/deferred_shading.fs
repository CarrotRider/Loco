#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

// Lights
#define LIGHT_DIR_NUM 1
#define LIGHT_POINT_NUM 10
#define LIGHT_SPOT_NUM 10

struct DirLight
{
	vec3 Direction;
	vec3 Color;
};

struct PointLight
{
	vec3 Position;
	vec3 Color;
	float Radius;
	float Kc;		// 衰减：常系数
	float Kl;		// 衰减：线性系数
	float Kq;		// 衰减：平方项系数
};

uniform DirLight dirLights[LIGHT_DIR_NUM];
uniform PointLight pointLights[LIGHT_POINT_NUM];

// Other Uniforms
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 fragPos, vec3 normal, vec3 viewDir, vec3 albedo, float specular);
vec3 CalcPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir, vec3 albedo, float specular);

void main()
{
	vec3 FragPos = texture(gPosition, TexCoords).rgb;
	vec3 Normal = texture(gNormal, TexCoords).rgb;
	vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
	float Specular = texture(gAlbedoSpec, TexCoords).a;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result;

	// 方向光
	for(int i=0; i<LIGHT_DIR_NUM; i++)
	{
		result += CalcDirLight(dirLights[i], FragPos, Normal, viewDir, Albedo, Specular);
	}
	// 点光
	for(int i=0; i<LIGHT_POINT_NUM; i++)
	{
		result += CalcPointLight(pointLights[i], FragPos, Normal, viewDir, Albedo, Specular);
	}

	FragColor = vec4(result, 1.0f);
}

// 方向光
vec3 CalcDirLight(DirLight light, vec3 fragPos, vec3 normal, vec3 viewDir, vec3 albedo, float specular)
{
	vec3 lightDir = normalize(-light.Direction);
	// ambient
	vec3 ambient = light.Color * albedo * 0.5;
	// diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.Color * diff * albedo * 2;
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
	vec3 _specular = light.Color * spec * specular;

	return ambient + diffuse + _specular;
}

// 点光源
vec3 CalcPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir, vec3 albedo, float specular)
{
	vec3 lightDir = normalize(light.Position - fragPos);
	// ambient
	vec3 ambient = light.Color * albedo * 0.5;
	// diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.Color * diff * albedo * 2;
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
	vec3 _specular = light.Color * spec * specular;

	// attenuation
	float distance = length(light.Position - fragPos);
	float attenuation = 1.0 / (light.Kc + light.Kl * distance + light.Kq * distance * distance);

	ambient = max(attenuation * ambient, 0.0f);
	diffuse = max(attenuation * diffuse, 0.0f);
	_specular = max(attenuation * _specular, 0.0f);

	return ambient + diffuse + _specular;
}
