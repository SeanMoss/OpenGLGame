#include "SpaceObject.h"

SpaceObject::SpaceObject()
{
	model = NULL;
	position = vec3(0, 0, 0);
	pitch = 0;
	yaw = 0;
	roll = 0;
}

SpaceObject::SpaceObject(Model* model)
{
	this->model = model;
	position = vec3(0, 0, 0);
	pitch = 0;
	yaw = 0;
	roll = 0;
}

SpaceObject::~SpaceObject()
{

}

float SpaceObject::signedAngle(vec2 a, vec2 b)
{
	vec2 an = glm::normalize(a);
	vec2 bn = glm::normalize(b);

	float angle = glm::acos(glm::dot(an, bn));

	if (glm::cross(vec3(an, 0.0f), vec3(bn, 0.0f)).z < 0.0f)
		angle = -angle;

	return angle;
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

void SpaceObject::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void SpaceObject::SetPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

glm::vec3 SpaceObject::GetPosition()
{
	return position;
}

void SpaceObject::SetPitch(float newPitch)
{
	pitch = newPitch;
}

float SpaceObject::GetPitch()
{
	return pitch;
}

void SpaceObject::SetYaw(float newYaw)
{
	yaw = newYaw;
}

float SpaceObject::GetYaw()
{
	return yaw;
}

void SpaceObject::SetRoll(float newRoll)
{
	roll = newRoll;
}

float SpaceObject::GetRoll()
{
	return roll;
}

void SpaceObject::Update()
{

}

void SpaceObject::Render(ShaderProgram* shader)
{
	if (model == NULL)
		return;

	model->Render(shader, position, pitch, yaw, roll);
}