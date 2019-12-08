#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
	FragColor = vec4(texture(texture1, TexCoord).xyz, 0.7);
}
