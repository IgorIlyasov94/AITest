#pragma once

#include "AIOpenGLCore.h"
#include "AITextureLoaders.h"

using TextureID = GLuint;

class AIOpenGLTexture
{
public:
	~AIOpenGLTexture();

	explicit AIOpenGLTexture(std::string filePath);
	AIOpenGLTexture(GLsizei width, GLsizei height, const void* data, GLint internalFormat = GL_RGB,
		GLenum format = GL_RGB, GLenum type = GL_UNSIGNED_BYTE);

	TextureID GetID() const noexcept;

private:
	AIOpenGLTexture() = delete;

	AIOpenGLCore& openGLCore = AIOpenGLCore::GetInstance();

	TextureID textureId;
};
