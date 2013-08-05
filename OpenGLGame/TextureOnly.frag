#version 330 core

//Imported data
in vec2 UV;

//Output data
out vec3 color;

//Texture sampler
uniform sampler2D myTextureSampler;

void main()
{
	color = texture(myTextureSampler, UV).rgb;
}