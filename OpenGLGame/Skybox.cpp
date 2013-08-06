#include <GL\glew.h>
#include "ShaderProgram.h"
#include "Skybox.h"
#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>

#define C_TFR -1.0f,1.0f,1.0f
#define C_TFL 1.0f,1.0f,1.0f
#define C_TBR -1.0f,1.0f,-1.0f
#define C_TBL 1.0f,1.0f,-1.0f
#define C_BFR -1.0f,-1.0f,1.0f
#define C_BFL 1.0f,-1.0f,1.0f
#define C_BBR -1.0f,-1.0f,-1.0f
#define C_BBL 1.0f,-1.0f,-1.0f

static ShaderProgram* cubeMapShader = nullptr;

static const GLfloat vertices[] = 
{
	C_TFR, C_TFL, C_TBR, C_TBL,
	C_BFR, C_BFL, C_BBR, C_BBL
};
static const unsigned short indices[] = 
{
	0, 2, 1, 2, 3, 1, //Top: y+
	2, 0, 6, 0, 4, 6, //Right: x-
	3, 2, 7, 2, 6, 7, //Back: z-
	1, 3, 5, 3, 7, 5, //Left: x+
	0, 1, 4, 1, 5, 4, //Front: z+
	6, 7, 4, 7, 5, 4  //Bottom: y-
};

Skybox::Skybox(const char* xp, const char* xn, const char* yp, const char* yn, const char* zp, const char* zn)
{
	if (cubeMapShader == nullptr)
		cubeMapShader = new ShaderProgram("cubemap.vert", "cubemap.frag");

	texture = SOIL_load_OGL_cubemap(xp, xn, yp, yn, zp, zn, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glGenBuffers(1, &vboID);
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	scale = 1.0f;
}

Skybox::~Skybox()
{

}

void Skybox::Render()
{
	ShaderProgram::SetActive(cubeMapShader);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	cubeMapShader->Uniform1i("SkyTexture", 0);
	cubeMapShader->UniformVec3("CameraPosition", Camera::ActiveCameraPosition());
	cubeMapShader->UniformMat4("MVP", 1, GL_FALSE, Camera::GetActiveCamera()->GetProjectionMatrix() * Camera::GetActiveCamera()->GetViewMatrix() * glm::mat4(1.0));
	glBindVertexArray(vaoID);
	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_SHORT, (void*)0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void Skybox::SetScale(float s)
{
	scale = s;
}

float Skybox::GetScale()
{
	return scale;
}