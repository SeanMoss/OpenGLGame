#include "ModelMesh.h"
#include "Controls.h"
#include <iostream>
#include <map>

static std::map<std::string, ModelMesh*> meshCache;

ModelMesh* ModelMesh::GetMesh(const char* path)
{
	bool contains = (meshCache.find(string(path)) != meshCache.end());

	if (contains)
	{
		cout << "Mesh " << path << " already loaded. Using pre-existing mesh." << endl;
		return meshCache[string(path)];
	}
	else
	{
		cout << "Loading new mesh " << path << " into memory." << endl;
		ModelMesh* mesh = new ModelMesh(path);
		meshCache[string(path)] = mesh;
		return mesh;
	}
}

ModelMesh::ModelMesh(const char* objpath)
{
	canDraw = OBJLoader::LoadObj(objpath, vertexData, uvData, normalData, &numFaces);

	if (!canDraw)
		fprintf(stderr, "Could not load .obj %s into ModelMesh. This object will not render.", objpath);

	if (canDraw)
	{
		fprintf(stdout, "Sucessfully loaded %s into memory.\n", objpath);
		glGenVertexArrays(1, &vaoID); //Create VAO for this mesh
		glBindVertexArray(vaoID);

		glGenBuffers(3, &vboID[0]); //Create 3 VBOs, for verticies, uvs, and normals

		glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); //Bind vertex data
		glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(glm::vec3), &vertexData[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); //Bind uv data
		glBufferData(GL_ARRAY_BUFFER, uvData.size() * sizeof(glm::vec2), &uvData[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, vboID[2]); //Bind normal data
		glBufferData(GL_ARRAY_BUFFER, normalData.size() * sizeof(glm::vec3), &normalData[0], GL_STATIC_DRAW); 
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glBindVertexArray(0);

		cout << "Size of model (Mb): " << ((vertexData.size() * sizeof(glm::vec3) + uvData.size() * sizeof(glm::vec2) + normalData.size() * sizeof(glm::vec3))/1048576.0f) << endl;
	}
}

ModelMesh::~ModelMesh()
{
	glDeleteBuffers(3, &vboID[0]);
	glDeleteVertexArrays(1, &vaoID);
}

void ModelMesh::Render()
{
	if(!canDraw)
		return;

	glBindVertexArray(vaoID);

	glDrawArrays(GL_TRIANGLES, 0, vertexData.size());

	glBindVertexArray(0);
}

unsigned int ModelMesh::GetNumFaces()
{
	return numFaces;
}