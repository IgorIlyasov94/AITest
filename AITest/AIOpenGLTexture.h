#pragma once

#include "AIOpenGLCore.h"
#include "AITextureBMP.h"

using TextureID = GLuint;
using OpenGLTextureID = GLuint;

class AIOpenGLTexture
{
public:
	~AIOpenGLTexture();

	explicit AIOpenGLTexture(std::string filePath);
	AIOpenGLTexture(GLsizei width, GLsizei height, const void* data, GLint internalFormat = GL_RGB,
		GLenum format = GL_RGB, GLenum type = GL_UNSIGNED_BYTE);

	OpenGLTextureID GetID() const noexcept;
	GLsizei GetWidth() const noexcept;
	GLsizei GetHeight() const noexcept;
	GLuint GetStride() const noexcept;

private:
	AIOpenGLTexture() = delete;

	AIOpenGLCore& openGLCore = AIOpenGLCore::GetInstance();

	GLsizei width;
	GLsizei height;
	GLuint stride;

	OpenGLTextureID textureId;
};
