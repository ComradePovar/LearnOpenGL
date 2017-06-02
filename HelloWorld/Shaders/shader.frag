#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct Spotlight {
	vec3 position;
	vec3 direction;
	float cutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NR_POINT_LIGHTS 1

uniform Material material;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Spotlight spotlight;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoord;

out vec4 color;

vec3 getDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = getDirectionalLight(dirLight, normal, viewDir);

	for (int i = 0; i < NR_POINT_LIGHTS; i++){
		result += getPointLight(pointLights[i], normal, FragPos, viewDir);
	}

	color = vec4(result, 1.0);
}

vec3 getDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
	vec3 ambientColor = vec3(texture(material.diffuse, texCoord)) * light.ambient;

	vec3 lightDir = normalize(-dirLight.direction);
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuseColor = light.diffuse * (diff * vec3(texture(material.diffuse, texCoord)));

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specularColor = light.specular * (spec * vec3(texture(material.specular, texCoord)));

	return (ambientColor + diffuseColor + specularColor);
}

vec3 getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 ambientColor = vec3(texture(material.diffuse, texCoord)) * light.ambient;

	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuseColor = light.diffuse * (diff * vec3(texture(material.diffuse, texCoord)));

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specularColor = light.specular * (spec * vec3(texture(material.specular, texCoord)));

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	ambientColor *= attenuation;
	diffuseColor *= attenuation;
	specularColor *= attenuation;

	return (ambientColor + diffuseColor + specularColor);
}