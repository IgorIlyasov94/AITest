#include "AIOpenGLTexture.h"

AIOpenGLTexture::~AIOpenGLTexture()
{

}

AIOpenGLTexture::AIOpenGLTexture(std::string filePath, TextureID _textureId)
	: textureId(_textureId)
{

}

AIOpenGLTexture::AIOpenGLTexture(GLuint width, GLuint height, TextureID _textureId)
	: textureId(_textureId)
{

}
