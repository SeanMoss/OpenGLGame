#include "Camera.h"
#include "SpaceObject.h"

SpaceObject::SpaceObject()
{
	model = NULL;
	position = vec3(0);
	heading = 0;
	roll = 0;
	scale = 1.0f;

	boundingSphere = new BoundingSphere(glm::vec3(0), 0.0f);
}

SpaceObject::SpaceObject(Model* model)
{
	this->model = model;
	position = vec3(0);
	heading = 0;
	roll = 0;
	scale = 1.0f;

	boundingSphere->position = position;
	ModelMesh::TrasformSphere(boundingSphere, model->GetMesh());
}

SpaceObject::~SpaceObject()
{

}

void SpaceObject::UseModel(Model* model)
{
	this->model = model;
}

void SpaceObject::UseTexture(GLuint texId)
{
	if(model != NULL)
		model->UseTexture(texId);
}

void SpaceObject::SetPosition(glm::vec2 pos)
{
	position = vec3(pos.x, 0.0f, pos.y);
}

void SpaceObject::SetPosition(float x, float z)
{
	position = glm::vec3(x, 0.0f, z);
}

glm::vec2 SpaceObject::GetPosition()
{
	return vec2(position.x, position.z);
}

void SpaceObject::SetHeading(float newHeading)
{
	heading = newHeading;
}

float SpaceObject::GetHeading()
{
	return heading;
}

void SpaceObject::SetRoll(float newRoll)
{
	roll = newRoll;
}

float SpaceObject::GetRoll()
{
	return roll;
}

void SpaceObject::SetScale(float newScale)
{
	scale = newScale;
}

float SpaceObject::GetScale()
{
	return scale;
}

const BoundingSphere* SpaceObject::GetBoundingSphere()
{
	return boundingSphere;
}

void SpaceObject::Update(float seconds)
{
	boundingSphere->position = this->position;
}

void SpaceObject::Render(ShaderProgram* shader)
{
	if (model == NULL)
		return;

	model->Render(shader, position, 0.0f, heading, roll, scale);

#ifdef _DEBUG

#endif
}