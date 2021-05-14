#version 330 core

#define LIGHT_DIR_NUM 1
#define LIGHT_POINT_NUM 10
#define LIGHT_SPOT_NUM 10

// IO
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

// Materials
struct Material
{
	sampler2D DiffuseTexture_0;
	sampler2D SpecularTexture_0;
	sampler2D NormalTexture_0;
	float Shininess;
};

uniform Material material;

// Lights
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

// Functions 
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);

void main()
{
	vec3 normal = normalize(Normal);
	//vec3 normal = texture(material.NormalTexture_0, TexCoord).rgb;
	//normal = normalize(normal * 2.0 - 1.0);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result;
	
	for(int i=0; i<LIGHT_DIR_NUM; i++)
	{
		result += CalcDirLight(dirLights[i], normal, viewDir);
	}

	for(int i=0; i<LIGHT_POINT_NUM; i++)
	{
		result += CalcPointLight(pointLights[i], normal, viewDir);
	}
	FragColor = vec4(result, 1.0f);
}

// 方向光
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.Direction);
	// ambient
	vec3 ambient = light.Color * vec3(texture(material.DiffuseTexture_0, TexCoord)) * 0.3f;
	// diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.Color * diff * vec3(texture(material.DiffuseTexture_0, TexCoord)) * 2;
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.Shininess);
	vec3 specular = light.Color * spec * vec3(texture(material.SpecularTexture_0, TexCoord));

	return ambient + diffuse + specular;
}

// 点光源
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.Position - FragPos);
	// ambient
	vec3 ambient = light.Color * vec3(texture(material.DiffuseTexture_0, TexCoord)) * 0.5;
	// diffuse	
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.Color * diff * vec3(texture(material.DiffuseTexture_0, TexCoord)) * 2;
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.Shininess);
	vec3 specular = light.Color * spec * vec3(texture(material.SpecularTexture_0, TexCoord));

	// attenuation
	float distance = length(light.Position - FragPos);
	float attenuation = 1.0 / (light.Kc + light.Kl * distance + light.Kq * distance * distance);

	ambient = max(attenuation * ambient, 0.0f);
	diffuse = max(attenuation * diffuse, 0.0f);
	specular = max(attenuation * specular, 0.0f);
	return ambient + diffuse + specular;
}