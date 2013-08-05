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
	glm::vec3 position;
	float heading;
	float roll;
	float scale;

public:
	SpaceObject();
	SpaceObject(Model* model);
	virtual ~SpaceObject();

	void UseModel(Model* model);
	void UseTexture(GLuint texId);

	void SetPosition(glm::vec2 pos);
	void SetPosition(float x, float z);
	glm::vec2 GetPosition();
	void SetHeading(float newYaw);
	float GetHeading();
	void SetRoll(float newRoll);
	float GetRoll();
	void SetScale(float newScale);
	float GetScale();

	virtual void Update(float seconds);

	virtual void Render(ShaderProgram* shader);
};

#endif