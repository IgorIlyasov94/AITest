#include "AIOpenGLTexturePool.h"

AIOpenGLTexturePool& AIOpenGLTexturePool::GetInstance()
{
	static AIOpenGLTexturePool thisInstance;

	return thisInstance;
}

TextureID AIOpenGLTexturePool::CreateTexture(GLuint width, GLuint height, const void* data, GLint internalFormat,
	GLenum format, GLenum type)
{
	auto newTextureId = textures.size();

	textures.push_back(std::shared_ptr<AIOpenGLTexture>(new AIOpenGLTexture(width, height, data, internalFormat, format, type)));

	return newTextureId;
}

TextureID AIOpenGLTexturePool::LoadTexture(std::string filePath)
{
	auto newTextureId = textures.size();

	textures.push_back(std::shared_ptr<AIOpenGLTexture>(new AIOpenGLTexture(filePath)));

	return newTextureId;
}

AIOpenGLTexture* AIOpenGLTexturePool::GetTexture(TextureID textureId) const
{
	ThrowIfFailed(textureId < textures.size(), "AIOpenGLTexturePool::GetTexture: Index out of bounds!");

	return textures[textureId].get();
}

GLuint AIOpenGLTexturePool::GetTextureNumber() const noexcept
{
	return textures.size();
}

AIOpenGLTexturePool::AIOpenGLTexturePool()
{

}

AIOpenGLTexturePool::~AIOpenGLTexturePool()
{

}
