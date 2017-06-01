#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
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
in vec2 texCoord;

out vec4 color;

void main()
{
	vec3 ambientColor = vec3(texture(material.diffuse, texCoord)) * light.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(lightDir, norm), 0.0f);
	vec3 diffuseColor = light.diffuse * (diff * vec3(texture(material.diffuse, texCoord)));

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specularColor = light.specular * (spec * vec3(texture(material.specular, texCoord)));

	vec3 result = (ambientColor + diffuseColor + specularColor);
	color = vec4(result, 1.0);
}