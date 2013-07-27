#ifndef _TEXTURE_LOADER_H_
#define _TEXTURE_LOADER_H_

#include <soil\SOIL.h>

GLuint LoadSOILTexture(const char* path, int forceChannels, unsigned int reuseId, unsigned int flags, bool useLinear);

#endif