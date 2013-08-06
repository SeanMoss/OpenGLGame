#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include <soil\SOIL.h>

class Skybox
{
private:
	GLuint texture;
	GLuint vaoID;
	GLuint vboID;
	GLuint iboID;
	float scale;

public:
	Skybox(const char* xp, const char* xn, const char* yp, const char* yn, const char* zp, const char* zn);
	~Skybox();

	void SetScale(float scale);
	float GetScale();
	void Render();
};

#endif