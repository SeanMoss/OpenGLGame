#include <glm\glm.hpp>
#include "Collision.h"

using namespace glm;

BoundingSphere::BoundingSphere(vec3 position, float radius)
{
	this->position = position;
	this->radius = radius;
}

BoundingSphere::BoundingSphere(float x, float y, float z, float radius)
{
	this->position = vec3(x, y, z);
	this->radius = radius;
}

BoundingSphere::~BoundingSphere()
{

}

bool BoundingSphere::Intersects(const BoundingSphere& other) const
{
	float len = length(other.position - this->position);
	return len < (other.radius + this->radius);
}