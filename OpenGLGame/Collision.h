#ifndef _COLLISION_H_
#define _COLLISION_H_

typedef struct BoundingSphere
{
public:
	glm::vec3 position;
	float radius;

	BoundingSphere(glm::vec3 position, float radius);
	BoundingSphere(float x, float y, float z, float radius);
	~BoundingSphere();

	bool Intersects(const BoundingSphere& other) const;
} BoundingSphere;

#endif