//This shader only allows for texturing with a constant ambient light
#version 330 core

//Only need position and uv
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

//Out uv
out vec2 UV;

//Uniforms
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	UV = vertexUV;
}