#ifndef _MODEL_MESH_H_
#define _MODEL_MESH_H_

#include <vector>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include "ShaderProgram.h"
#include "ObjLoader.h"

class ModelMesh
{
public:
	static ModelMesh* GetMesh(const char* path);

private:
	bool canDraw; //If the model was loaded properly at initialization
	GLuint vaoID;
	GLuint vboID[3];
	GLuint iboID;
	std::vector<glm::vec3> vertexData; //Pure vertex data
	std::vector<glm::vec2> uvData;
	std::vector<glm::vec3> normalData;
	std::vector<unsigned short> indexData;
	unsigned int numFaces;

public:
	ModelMesh(const char* objpath);
	~ModelMesh();

	void Render();
	unsigned int GetNumFaces();
};

#endif