#include "Model.h"
#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>

Model::Model(const char* objpath)
{
	modelMesh = ModelMesh::GetMesh(objpath);
	textureID = 0;
	oMesh = true;
}

Model::Model(ModelMesh* mesh)
{
	modelMesh = mesh;
	textureID = 0;
	oMesh = false;
}

Model::~Model()
{
	if(oMesh)
		delete modelMesh;
}

const ModelMesh* Model::GetMesh()
{
	return modelMesh;
}

void Model::Render(ShaderProgram* shader, glm::vec3 position, float pitch, float yaw, float roll, float scale)
{
	ShaderProgram::SetActive(shader);

	mat4 projection = Camera::GetActiveCamera()->GetProjectionMatrix();
	mat4 view = Camera::GetActiveCamera()->GetViewMatrix();
	mat4 model = translate(mat4(1.0), position) * rotate(mat4(1.0), pitch, vec3(1, 0, 0)) * rotate(mat4(1.0), yaw, vec3(0, 1, 0)) * rotate(mat4(1.0), roll, vec3(0, 0, 1)) * glm::scale(mat4(1.0), vec3(scale));
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