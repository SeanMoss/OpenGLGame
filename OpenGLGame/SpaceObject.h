/*
 * This class will encompass everything that is a physical object in space
 * i.e. Ships, Stations, Planets, Nebulas, Asteroids, Missiles, Lasers, Bombs
*/
#ifndef _SPACE_OBJECT_H_
#define _SPACE_OBJECT_H_

#define MAX_PITCH 60.0f
#define MAX_ROLL 25.0f

#include "GameObject.h"
#include <glm\glm.hpp>
#include "ShaderProgram.h"
#include "Model.h"

class SpaceObject : public GameObject
{
private:
	Model* model;

protected:
	float signedAngle(vec2 a, vec2 b);
	glm::vec3 position;
	float pitch;
	float yaw;
	float roll;

public:
	SpaceObject();
	SpaceObject(Model* model);
	virtual ~SpaceObject();

	void UseModel(Model* model);
	void UseTexture(GLuint texId);

	void SetPosition(glm::vec3 pos);
	void SetPosition(float x, float y, float z);
	glm::vec3 GetPosition();
	void SetPitch(float newPitch);
	float GetPitch();
	void SetYaw(float newYaw);
	float GetYaw();
	void SetRoll(float newRoll);
	float GetRoll();

	virtual void Update();

	virtual void Render(ShaderProgram* shader);
};

#endif