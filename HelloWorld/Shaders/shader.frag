#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 color;

void main()
{
    //color = mix(texture(ourTexture0, texCoord), texture(ourTexture1, texCoord), 0.2) * vec4(ourColor, 1.0);
	color = vec4(lightColor * objectColor, 1.0);
}