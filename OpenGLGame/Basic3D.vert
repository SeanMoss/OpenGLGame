#version 330 core

//Input vertex data
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

//Out data to the fragment shader
out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

//Uniforms
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 LightPosition_worldspace;

void main()
{
	//Output position of the vertex in clip space
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	//The position of the vertex in worldspace
	Position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;

	//Position of the vertex in cameraspace (camera at (0,0,0))
	vec3 vertexPosition_cameraspace = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
	EyeDirection_cameraspace = vec3(0, 0, 0) - vertexPosition_cameraspace; //Get the direction vector from the camera to the vertex

	//Vector that goes from the vertex to the light
	vec3 lightPosition_cameraspace = (V * vec4(LightPosition_worldspace, 1)).xyz;
	LightDirection_cameraspace = lightPosition_cameraspace + EyeDirection_cameraspace;

	//Get the normal in cameraspace
	Normal_cameraspace = (V * M * vec4(vertexNormal_modelspace, 0)).xyz;

	//Nothing special for this
	UV = vertexUV;
}