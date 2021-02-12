#pragma once

#include "AIOpenGLTexture.h"

class AIOpenGLTexturePool
{
public:
	static AIOpenGLTexturePool& GetInstance();

	TextureID CreateTexture(GLuint width, GLuint height, const void* data, GLint internalFormat = GL_RGBA,
		GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE);

	TextureID LoadTexture(std::string filePath);

	AIOpenGLTexture* GetTexture(TextureID textureId) const;
	GLuint GetTextureNumber() const noexcept;

private:
	AIOpenGLTexturePool();
	~AIOpenGLTexturePool();

	AIOpenGLTexturePool(const AIOpenGLTexturePool&) = delete;
	AIOpenGLTexturePool(AIOpenGLTexturePool&&) = delete;
	AIOpenGLTexturePool& operator=(const AIOpenGLTexturePool&) = delete;
	AIOpenGLTexturePool& operator=(AIOpenGLTexturePool&&) = delete;

	std::vector<std::shared_ptr<AIOpenGLTexture>> textures;
};
