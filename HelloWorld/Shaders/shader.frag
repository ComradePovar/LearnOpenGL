#version 330 core

struct Material{
	sampler2D texture_diffuse1;
};

uniform Material material;

in vec2 texCoord;

out vec4 color;

void main()
{
	color = texture(material.texture_diffuse1, texCoord);
}