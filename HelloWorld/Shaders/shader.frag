#version 330 core

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

in vec3 ourColor;
in vec2 texCoord;

out vec4 color;

void main()
{
    //color = mix(texture(ourTexture0, texCoord), texture(ourTexture1, texCoord), 0.2) * vec4(ourColor, 1.0);
	color = texture(ourTexture2, texCoord);
}