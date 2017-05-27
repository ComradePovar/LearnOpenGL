#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

void main()
{
	vec3 ambientColor = material.ambient * light.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(lightDir, norm), 0.0f);
	vec3 diffuseColor = light.diffuse * (diff * material.diffuse);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specularColor = light.specular * (spec * material.specular);

	vec3 result = (ambientColor + diffuseColor + specularColor);
	color = vec4(result, 1.0);
}