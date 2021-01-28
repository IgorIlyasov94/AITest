#include "AIOpenGLTexturePool.h"

AIOpenGLTexturePool& AIOpenGLTexturePool::GetInstance()
{
	static AIOpenGLTexturePool thisInstance;

	return thisInstance;
}

TextureID AIOpenGLTexturePool::CreateTexture(GLuint width, GLuint height)
{
	TextureID newTextureId = textures.size();

	textures.push_back(std::shared_ptr<AIOpenGLTexture>(new AIOpenGLTexture(width, height, newTextureId)));

	return newTextureId;
}

TextureID AIOpenGLTexturePool::LoadTexture(std::string filePath)
{
	TextureID newTextureId = textures.size();

	textures.push_back(std::shared_ptr<AIOpenGLTexture>(new AIOpenGLTexture(filePath, newTextureId)));

	return newTextureId;
}

AIOpenGLTexture* AIOpenGLTexturePool::GetTexture(TextureID textureId) const
{
	ThrowIfFailed(textureId < textures.size(), "AIOpenGLTexturePool::GetTexture: Array out of bounds!");

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
