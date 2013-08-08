#include "Ship.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\vector_angle.hpp>
#include <iostream>
#include "Camera.h"

#define MAX_PITCH 25.0f

Ship::Ship(ShipInfo info)
{
	maxSpeed = info.maxSpeed;
	maxAcceleration = info.maxAcceleration;
	maxTurnRate = info.maxTurnRate;
	maxTurnAcceleration = info.maxTurnAcceleration;

	velocity = 0;
	heading = 0;
	turnRate = 0;
	rollRate = 0;
}

Ship::~Ship()
{

}

void Ship::SetDestination(vec2 dest)
{
	destination = dest;
}

glm::vec2 Ship::GetDestination()
{
	return destination;
}

float Ship::GetVelocity()
{
	return velocity;
}

void Ship::Stop()
{
	destination = vec2(position.x, position.z);
}

void Ship::Update(float seconds)
{
	SpaceObject::Update(seconds);

	using namespace glm;

	vec3 target = vec3(destination.x, 0.0f, destination.y) - position;
	float distToTarget = length(target);

	if (distToTarget >= 0.01f)
	{
		float tHeading = angle(vec2(0.0f, 1.0f), normalize(vec2(target.x, target.z))); //The angle of yaw from 0 (NOT DIRECTION) required to point at target
		if (cross(vec3(0.0f, 1.0f, 0.0f), normalize(vec3(target.x, target.z, 0.0f))).z > 0.0f) //Make the correct sign
			tHeading = -tHeading;

		float dHeading = tHeading - heading; //The difference between the current heading and the required heading
		//Tie to within [-pi, pi]
		if (dHeading < -180.0f)
			dHeading += 360.0f;
		else if (dHeading > 180.0f)
			dHeading -= 360.0f;

		cout << "dHeading:\t" << dHeading << endl;

		if (abs(dHeading) > 0.01f)
		{
			if (abs(dHeading) < (maxTurnRate * seconds))
				heading += dHeading;
			else
			{
				if(dHeading >= 0.0f)
					heading += maxTurnRate * seconds; 
				else
					heading -= maxTurnRate * seconds;
			}
		}

		mat4 direction = rotate(mat4(1.0), heading, vec3(0.0f, 1.0f, 0.0f));
		vec4 toMove = direction * vec4(0, 0, 1, 1);

		//TODO: NEEDS ADJUSTMENT FOR SIZE OF SHIP, ECT.
		float angleTolerance = glm::min(70.0f, distToTarget * 3.0f); //Angle it needs to turn before it stops moving while turning
		if (abs(dHeading) > angleTolerance) //If the ship needs to turn a lot, let it turn before accelerating
		{
			velocity -= maxAcceleration * seconds;
			if (velocity < (maxSpeed/8.0f))
				velocity = (maxSpeed/8.0f);
		}
		else
		{
			if (velocity < maxSpeed)
			{
				if ((velocity + maxAcceleration * seconds) > maxSpeed)
					velocity = maxSpeed;
				else
					velocity += maxAcceleration * seconds;
			}
		}

		if (velocity < 0.0f) //No moving backwards
			velocity = 0.0f;

		position += vec3(toMove) * velocity * seconds;
	}

	position.y = 0;
}

void Ship::Render(ShaderProgram* shader)
{
	SpaceObject::Render(shader);

#ifdef _DEBUG
	mat4 proj = Camera::GetActiveCamera()->GetProjectionMatrix();
	mat4 view = Camera::GetActiveCamera()->GetViewMatrix();
	mat4 MVP = proj * view * translate(mat4(1.0f), vec3(0, 0, 0));

	shader->UniformMat4("MVP", 1, GL_FALSE, MVP);
	glBindTexture(GL_TEXTURE_2D, 0);

	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(position.x, 0.0f, position.z);
	glVertex3f(destination.x, 0.0f, destination.y);
	glEnd(); 
	glLineWidth(1);
#endif
}

//Old 3D pathfinding update
//void Ship::Update()
//{
//	using namespace glm;
//
//	vec3 target = destination - position;
//	float distToTarget = length(target);
//
//	if (distToTarget >= 0.01f)
//	{
//		//=========================================================TURNING==============================================================
//		//=============================CALCULATE PITCH AND YAW OF TARGET FROM POSITION FROM 0 DEGREES===================================
//		float rdxzLength = sqrt(pow(target.x, 2) + pow(target.z, 2)); //Length of x component on pitch plane, quadratic formula of x and z componenets on y=0 plane
//		float tPitch = angle(normalize(vec2(rdxzLength, 0)), normalize(vec2(rdxzLength, target.y))); //The angle of pitch from 0 (NOT DIRECTION) required to point at target
//		float tYaw = angle(vec2(0.0f, 1.0f), normalize(vec2(target.x, target.z))); //The angle of yaw from 0 (NOT DIRECTION) required to point at target
//
//		//Correct for signs
//		if (target.y > 0.0f)
//			tPitch = -tPitch;
//		else if (abs(target.y) < 0.001f) //Fixes occasional floating point rounding error that produces an incorrect pitch
//			tPitch = 0.0f;
//		if (cross(vec3(0.0f, 1.0f, 0.0f), normalize(vec3(target.x, target.z, 0.0f))).z > 0.0f)
//			tYaw = -tYaw;
//
//		//==============================================================================================================================
//
//		float dPitch = tPitch - pitch; //The difference between the current pitch and the required pitch
//		float dYaw = tYaw - yaw; //The difference between the current yaw and the required yaw
//
//		//Tie to within [-pi, pi]
//		if (dYaw < -180.0f)
//			dYaw += 360.0f;
//		else if (dYaw > 180.0f)
//			dYaw -= 360.0f;
//		if (dPitch < -180.0f)
//			dPitch += 360.0f;
//		else if (dPitch > 180.0f)
//			dPitch -= 360.0f;
//
//		cout << "dPitch:\t" << dPitch << endl;
//		cout << "dYaw:\t" << dYaw << endl;
//
//		if (abs(dPitch) > 0.01f)
//		{
//			if (abs(dPitch) < maxTurnRate)
//				pitch += dPitch;
//			else
//			{
//				if(dPitch >= 0.0f)
//					pitch += maxTurnRate;
//				else
//					pitch -= maxTurnRate;
//			}
//
//			if (pitch > MAX_PITCH)
//				pitch = MAX_PITCH;
//			else if (pitch < -MAX_PITCH)
//				pitch = -MAX_PITCH; 
//		}
//
//		if (abs(dYaw) > 0.01f)
//		{
//			if (abs(dYaw) < maxTurnRate)
//				yaw += dYaw;
//			else
//			{
//				if(dYaw >= 0.0f)
//					yaw += maxTurnRate; 
//				else
//					yaw -= maxTurnRate;
//			}
//		}
//		//==============================================================================================================================
//
//		mat4 direction = rotate(mat4(1.0), pitch, vec3(1, 0, 0));
//		direction = rotate(direction, yaw, vec3(0, 1, 0));
//
//		vec4 toMove = direction * vec4(0, 0, 1, 1);
//
//		//TODO: NEEDS ADJUSTMENT FOR SIZE OF SHIP, ECT.
//		float angleTolerance = glm::min(70.0f, distToTarget * 5.0f); //Angle it needs to turn before it stops moving while turning
//		if (abs(dYaw) > angleTolerance) //If the ship needs to turn a lot, let it turn before accelerating
//		{
//			velocity -= maxAcceleration;
//		}
//		else
//		{
//			if (velocity < maxSpeed)
//			{
//				if ((velocity + maxAcceleration) > maxSpeed)
//					velocity = maxSpeed;
//				else
//					velocity += maxAcceleration;
//			}
//		}
//
//		if (velocity < 0.0f) //No moving backwards
//			velocity = 0.0f;
//
//		position += vec3(toMove) * velocity;
//	}
//}