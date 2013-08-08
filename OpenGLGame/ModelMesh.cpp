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

void ModelMesh::TrasformSphere(BoundingSphere* sphere, const ModelMesh* mesh)
{
	float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

	std::vector<glm::vec3> verts = mesh->vertexData;

	for (std::vector<glm::vec3>::iterator it = verts.begin(); it != verts.end(); ++it)
	{
		if (it->x > maxX)
			maxX = it->x;
		else if (it->x < minX)
			minX = it->x;
		if (it->y > maxY)
			maxY = it->y;
		else if (it->y < minY)
			minY = it->y;
		if (it->z > maxZ)
			maxZ = it->z;
		else if (it->z < minZ)
			minZ = it->z;
	}

	minX = abs(minX);
	minY = abs(minY);
	minZ = abs(minZ);

	float most = 0;
	most = glm::max(most, minX);
	most = glm::max(most, minY);
	most = glm::max(most, minZ);
	most = glm::max(most, maxX);
	most = glm::max(most, maxY);
	most = glm::max(most, maxZ);

	sphere->radius = most;
}

ModelMesh::ModelMesh(const char* objpath)
{
	canDraw = OBJLoader::LoadModel(objpath, indexData, vertexData, uvData, normalData, &numFaces);

	if (!canDraw)
		fprintf(stderr, "Could not load .obj %s into ModelMesh. This object will not render.", objpath);

	if (canDraw)
	{
		fprintf(stdout, "Sucessfully loaded %s into memory.\n", objpath);
		glGenVertexArrays(1, &vaoID); //Create VAO for this mesh
		glBindVertexArray(vaoID);

		glGenBuffers(3, &vboID[0]); //Create 3 VBOs, for verticies, uvs, and normals
		glGenBuffers(1, &iboID); //Create an index buffer

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

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned short), &indexData[0], GL_STATIC_DRAW);

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

	glEnable(GL_DEPTH_TEST);
	glBindVertexArray(vaoID);

	glDrawArrays(GL_TRIANGLES, 0, vertexData.size());
	glDrawElements(GL_TRIANGLES, indexData.size() * sizeof(unsigned short), GL_UNSIGNED_SHORT, (void*)0); 

	glBindVertexArray(0);
}

unsigned int ModelMesh::GetNumFaces()
{
	return numFaces;
}