#version 330 core

//Imorted data from the vertex shader
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

//Output data
out vec3 color;

//Uniforms
uniform sampler2D myTextureSampler;
uniform vec3 LightPosition_worldspace;

void main()
{
	//Light emission properties (possible uniforms)
	vec3 LightColor = vec3(1, 1, 1);
	float LightPower = 50.0f;

	//Material properties
	vec3 MatDiffuseColor = texture(myTextureSampler, UV).rgb;
	vec3 MatAmbientColor = vec3(0.3, 0.3, 0.3) * MatDiffuseColor;
	vec3 MatSpecularColor = vec3(0.3, 0.3, 0.3);

	//Distance from vertex to light
	float lightDistance = length(LightPosition_worldspace - Position_worldspace);

	//Normal of fragment in cameraspace
	vec3 norm = normalize(Normal_cameraspace);
	//Normal of direction of light to fragment
	vec3 lightDir = normalize(LightDirection_cameraspace);

	//Cosine of angle between light direction and normal
	//Perpendicular = 1, parallel or behind = 0
	float cosTheta = clamp(dot(norm, lightDir) + .3f, 0.0, 1.0);

	//Normal of eye direction towards vertex
	vec3 eyeDir = normalize(EyeDirection_cameraspace);
	//Direction of the reflected light from the triangle the fragment is on
	vec3 reflectDir = reflect(-lightDir, norm);

	//Cosine between the eye direction and reflection
	float cosAlpha = clamp(dot(eyeDir, reflectDir), 0.0, 1.0);

	//Final color
	color = 
		//Ambient: simulates indirect lighting
		MatAmbientColor + 
		//Diffuse: "color" of the object -> material diffuse color * light color * light power * (angle between normal and light / (distance from light ^ 2))
		(MatDiffuseColor * LightColor * LightPower * (cosTheta / (lightDistance * lightDistance))) + 
		//Specular: reflective highlight -> materla specular color * light color * light power * ((angle between reflection and eye ^ 5) / (distance from light ^ 2))
		(MatSpecularColor * LightColor * LightPower * (pow(cosAlpha, 30) / (lightDistance * lightDistance))); //Change number in pow funtion to chage size of highlight (bigger # = smaller highlight)
}