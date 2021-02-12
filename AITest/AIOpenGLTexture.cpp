#include "AIOpenGLTexture.h"

AIOpenGLTexture::~AIOpenGLTexture()
{
	openGLCore.glDeleteTextures(1, &textureId);
}

AIOpenGLTexture::AIOpenGLTexture(std::string filePath)
{
	if (filePath.size() == 0)
		throw std::exception("AIOpenGLTexture: File path must not be empty!");

	auto extensionPosition = filePath.find('.') + 1;
	auto extension = filePath.substr(extensionPosition, filePath.size() - 1);

	GLint internalFormat = GL_RGBA;
	GLenum format = GL_RGBA;
	GLenum type = GL_UNSIGNED_BYTE;
	stride = 4;

	std::vector<uint8_t> data;

	if (extension == "bmp")
		AITextureBMP::Load(filePath, data, width, height);
	else
		throw std::exception("AIOpenGLTexture: Wrong file format!");

	openGLCore.glGenTextures(1, &textureId);
	openGLCore.glActiveTexture(GL_TEXTURE0);
	openGLCore.glBindTexture(GL_TEXTURE_2D, textureId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	openGLCore.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	openGLCore.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	openGLCore.glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, &data[0]);
	openGLCore.glBindImageTexture(0, textureId, 0, GL_FALSE, 0, GL_READ_WRITE, internalFormat);

	openGLCore.glBindTexture(GL_TEXTURE_2D, 0);
}

AIOpenGLTexture::AIOpenGLTexture(GLsizei _width, GLsizei _height, const void* data, GLint internalFormat, GLenum format, GLenum type)
	: width(_width), height(_height), stride(4)
{
	openGLCore.glGenTextures(1, &textureId);
	openGLCore.glActiveTexture(GL_TEXTURE0);
	openGLCore.glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	openGLCore.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	openGLCore.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	openGLCore.glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, format, type, data);
	openGLCore.glBindImageTexture(0, textureId, 0, GL_FALSE, 0, GL_READ_WRITE, internalFormat);

	openGLCore.glBindTexture(GL_TEXTURE_2D, 0);
}

OpenGLTextureID AIOpenGLTexture::GetID() const noexcept
{
	return textureId;
}

GLsizei AIOpenGLTexture::GetWidth() const noexcept
{
	return width;
}

GLsizei AIOpenGLTexture::GetHeight() const noexcept
{
	return height;
}

GLuint AIOpenGLTexture::GetStride() const noexcept
{
	return stride;
}
