#include "Model.h"
#include "Controls.h"
#include <glm\gtc\matrix_transform.hpp>

Model::Model(const char* objpath)
{
	modelMesh = new ModelMesh(objpath);
	textureID = 0;
	oMesh = true;
	position = vec3(0, 0, 0);
	pitch = 0;
	yaw = 0;
	roll = 0;
}

Model::Model(ModelMesh* mesh)
{
	modelMesh = mesh;
	textureID = 0;
	oMesh = false;
	position = vec3(0, 0, 0);
	pitch = 0;
	yaw = 0;
	roll = 0;
}

Model::~Model()
{
	if(oMesh)
		delete modelMesh;
}

void Model::Render(ShaderProgram* shader)
{
	ShaderProgram::SetActive(shader);

	mat4 projection = getProjectionMatrix();
	mat4 view = getViewMatrix();
	mat4 model = translate(mat4(1.0), position) * rotate(mat4(1.0), pitch, vec3(1, 0, 0)) * rotate(mat4(1.0), yaw, vec3(0, 1, 0)) * rotate(mat4(1.0), roll, vec3(0, 0, 1));
	mat4 MVP = projection * view * model;

	shader->UniformMat4("MVP", 1, GL_FALSE, MVP);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	shader->Uniform1i("myTextureSampler", 0);

	modelMesh->Render();
}

void Model::UseTexture(GLuint id)
{
	textureID = id;
}

void Model::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void Model::SetPosition(float x, float y, float z)
{
	position = vec3(x, y, z);
}

glm::vec3 Model::GetPosition()
{
	return position;
}

void Model::SetPitch(float newPitch)
{
	pitch = newPitch;
}

float Model::GetPitch()
{
	return pitch;
}

void Model::SetYaw(float newYaw)
{
	yaw = newYaw;
}

float Model::GetYaw()
{
	return yaw;
}

void Model::SetRoll(float newRoll)
{
	roll = newRoll;
}

float Model::GetRoll()
{
	return roll;
}