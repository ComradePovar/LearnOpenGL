#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

void main()
{
    //color = mix(texture(ourTexture0, texCoord), texture(ourTexture1, texCoord), 0.2) * vec4(ourColor, 1.0);
	float ambientStrength = 0.1f;
	vec3 ambientColor = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(lightDir, norm), 0.0f);
	vec3 diffuseColor = lightColor * diff;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float specularStrength = 0.5f;
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), 32);
	vec3 specularColor = lightColor * specularStrength * spec;

	vec3 result = (ambientColor + diffuseColor + specularColor) * objectColor;
	color = vec4(result, 1.0);
}