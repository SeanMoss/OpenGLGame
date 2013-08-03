/*
 * This is a class for generic ships. Any size, class, race, faction, type... all go here
 * Templates will probably be loaded from a .xml file, similar to Artemis
*/
#ifndef _SHIP_H_
#define _SHIP_H_

#include "SpaceObject.h"
#include <math.h>

typedef struct
{
	float maxSpeed;
	float maxAcceleration;
	float maxTurnRate;
	float maxTurnAcceleration;
	//float maxHitPoints;
	//float maxArmor;
	//float maxShields;
	//int maxEnergy;
	//bool friendly;
	//float beamDamage;
	//float missileDamage;
} ShipInfo;

class Ship : public SpaceObject
{
private:
	//Constants
	float maxSpeed;
	float maxAcceleration;
	float maxTurnRate;
	float maxTurnAcceleration;
	//int maxHitPoints;
	//int maxArmor;
	//int maxShields;
	//int maxEnergy;
	//bool friendly;
	//Variables
	float velocity;
	float pitchRate;
	float yawRate;
	float rollRate;
	glm::vec3 destination;

public:
	Ship(ShipInfo info);
	~Ship();

	void SetDestination(vec3 dest);
	vec3 GetDestination();
	float GetVelocity();

	virtual void Update();
	virtual void Render(ShaderProgram *shader);
};

#endif