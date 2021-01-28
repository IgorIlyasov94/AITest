#pragma once

#include "AIOpenGLCore.h"

using TextureID = GLuint;

class AIOpenGLTexture
{
public:
	~AIOpenGLTexture();
	AIOpenGLTexture(std::string filePath, TextureID _textureId);
	AIOpenGLTexture(GLuint width, GLuint height, TextureID _textureId);

private:
	AIOpenGLTexture() = delete;

	GLuint textureId;
};
