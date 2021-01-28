#pragma once

#include "AIOpenGLTexture.h"

class AIOpenGLTexturePool
{
public:
	static AIOpenGLTexturePool& GetInstance();

	TextureID CreateTexture(GLuint width, GLuint height);
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
