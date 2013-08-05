#ifndef _MODEL_H_
#define _MODEL_H_

#include "ModelMesh.h"
#include "GameObject.h"

class Model
{
private:
	ModelMesh* modelMesh;
	bool oMesh; //If the modelmesh is unique to this object, and should be deleted when this is destroyed

	GLuint textureID;

public:
	Model(const char* objpath);
	Model(ModelMesh* mesh);
	virtual ~Model();

	void Render(ShaderProgram* shader, glm::vec3 position, float pitch, float yaw, float roll, float scale);
	void UseTexture(GLuint id);
};

#endif