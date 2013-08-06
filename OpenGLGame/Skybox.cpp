#include <GL\glew.h>
#include "ShaderProgram.h"
#include "Skybox.h"
#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>

static ShaderProgram* cubeMapShader = nullptr;

Skybox::Skybox(const char* xp, const char* xn, const char* yp, const char* yn, const char* zp, const char* zn)
{
	if (cubeMapShader == nullptr)
		cubeMapShader = new ShaderProgram("cubemap.vert", "cubemap.frag");

	texture = SOIL_load_OGL_cubemap(xp, xn, yp, yn, zp, zn, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//TODO make cube
}

Skybox::~Skybox()
{

}

void Skybox::Render()
{
	
}