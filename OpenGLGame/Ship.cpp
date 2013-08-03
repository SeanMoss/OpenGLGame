#include "Ship.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\vector_angle.hpp>
#include <iostream>

#define MAX_PITCH 25.0f

Ship::Ship(ShipInfo info)
{
	maxSpeed = info.maxSpeed;
	maxAcceleration = info.maxAcceleration;
	maxTurnRate = info.maxTurnRate;
	maxTurnAcceleration = info.maxTurnAcceleration;

	destination = position;

	velocity = 0.0f;
	pitchRate = 0.0f;
	yawRate = 0.0f;
}

Ship::~Ship()
{

}

void Ship::SetDestination(vec3 dest)
{
	destination = dest;
}

glm::vec3 Ship::GetDestination()
{
	return destination;
}

float Ship::GetVelocity()
{
	return velocity;
}

void Ship::Update()
{
	using namespace glm;

	vec3 target = destination - position;
	float distToTarget = length(target);

	if (distToTarget >= 0.01f)
	{
		//=========================================================TURNING==============================================================
		//=============================CALCULATE PITCH AND YAW OF TARGET FROM POSITION FROM 0 DEGREES===================================
		float rdxzLength = sqrt(pow(target.x, 2) + pow(target.z, 2)); //Length of x component on pitch plane, quadratic formula of x and z componenets on y=0 plane
		float tPitch = angle(normalize(vec2(rdxzLength, 0)), normalize(vec2(rdxzLength, target.y))); //The angle of pitch from 0 (NOT DIRECTION) required to point at target
		float tYaw = angle(vec2(0.0f, 1.0f), normalize(vec2(target.x, target.z))); //The angle of yaw from 0 (NOT DIRECTION) required to point at target

		//Correct for signs
		if (target.y < 0.0f)
			tPitch = -tPitch;
		if (cross(vec3(0.0f, 1.0f, 0.0f), normalize(vec3(target.x, target.z, 0.0f))).z > 0.0f)
			tYaw = -tYaw;

		//==============================================================================================================================

		float dPitch = tPitch - pitch; //The difference between the current pitch and the required pitch
		float dYaw = tYaw - yaw; //The difference between the current yaw and the required yaw

		//Tie to within [-pi, pi]
		if (dYaw < -180.0f)
			dYaw += 360.0f;
		else if (dYaw > 180.0f)
			dYaw -= 360.0f;
		if (dPitch < -180.0f)
			dPitch += 360.0f;
		else if (dPitch > 180.0f)
			dPitch -= 360.0f;

		cout << "dPitch:\t" << dPitch << endl;
		cout << "dYaw:\t" << dYaw << endl;

		if (abs(dPitch) < maxTurnRate)
			pitch += dPitch;
		else
			pitch += maxTurnRate;

		if (pitch > MAX_PITCH)
			pitch = MAX_PITCH;
		else if (pitch < -MAX_PITCH)
			pitch = -MAX_PITCH;

		if (abs(dYaw) < maxTurnRate)
			yaw += dYaw;
		else
			yaw += maxTurnRate;
		//==============================================================================================================================

		mat4 direction = rotate(mat4(1.0), pitch, vec3(1, 0, 0));
		direction = rotate(direction, yaw, vec3(0, 1, 0));

		vec4 toMove = direction * vec4(0, 0, 1, 1);

		//TODO: NEEDS ADJUSTMENT FOR SIZE OF SHIP, ECT.
		float angleTolerance = glm::min(70.0f, distToTarget * 5.0f); //Angle it needs to turn before it stops moving while turning
		if (abs(dYaw) > angleTolerance) //If the ship needs to turn a lot, let it turn before accelerating
		{
			velocity -= maxAcceleration;
		}
		else
		{
			if (velocity < maxSpeed)
			{
				if ((velocity + maxAcceleration) > maxSpeed)
					velocity = maxSpeed;
				else
					velocity += maxAcceleration;
			}
		}

		if (velocity < 0.0f) //No moving backwards
			velocity = 0.0f;

		position += vec3(toMove) * velocity;
	}
}

void Ship::Render(ShaderProgram* shader)
{
	SpaceObject::Render(shader);

	if (1 == _USE_DEBUG_)
	{
		vec4 target(destination - position, 1.0f);
		mat4 invrot = rotate(mat4(1.0), yaw, vec3(0, 1, 0));
		invrot = rotate(mat4(1.0), pitch, vec3(1, 0, 0));
		target = inverse(invrot) * target;
		glLineWidth(3);
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(target.x, target.y, target.z);
		glEnd(); 
		glLineWidth(1);
	}
}