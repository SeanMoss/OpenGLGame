#version 330 compatibility

uniform samplerCube SkyTexture;

in vec3 Position;

void main()
{
	gl_FragColor = textureCube(SkyTexture, Position);
}