#include <GL\glew.h>

#include "TextureLoader.h"

GLuint LoadSOILTexture(const char* path, int forceChannels, unsigned int reuseId, unsigned int flags, bool useLinear)
{
	GLuint textureID = SOIL_load_OGL_texture(path, forceChannels, reuseId, flags);

	glBindTexture(GL_TEXTURE_2D, textureID);

	bool hasMipmaps = (flags & SOIL_FLAG_MIPMAPS) > 0;

	if(useLinear)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, hasMipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR); 
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, hasMipmaps ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}