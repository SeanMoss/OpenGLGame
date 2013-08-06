#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include <soil\SOIL.h>

class Skybox
{
private:
	GLuint texture;
	GLuint vaoID;
	GLuint vboID;
	GLint vertexLocation;

public:
	Skybox(const char* xp, const char* xn, const char* yp, const char* yn, const char* zp, const char* zn);
	~Skybox();

	void Render();
};

#endif