#ifndef _MODEL_H_
#define _MODEL_H_

#include "ModelMesh.h"
#include "GameObject.h"

class Model
{
private:
	ModelMesh* modelMesh;
	ModelMesh* parent;
	bool oMesh; //If the modelmesh is unique to this object, and should be deleted when this is destroyed

	GLuint textureID;
	glm::vec3 position;
	float pitch;
	float yaw;
	float roll;

public:
	Model(const char* objpath);
	Model(ModelMesh* mesh);
	virtual ~Model();

	void Render(ShaderProgram* shader);
	void UseTexture(GLuint id);

	void SetPosition(glm::vec3 pos);
	void SetPosition(float x, float y, float z);
	glm::vec3 GetPosition();
	void SetPitch(float newPitch);
	float GetPitch();
	void SetYaw(float newYaw);
	float GetYaw();
	void SetRoll(float newRoll);
	float GetRoll();
};

#endif