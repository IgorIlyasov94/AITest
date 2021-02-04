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

	GLsizei width = 0;
	GLsizei height = 0;
	GLint internalFormat = 0;
	GLenum format = 0;
	GLenum type = 0;
	std::vector<uint8_t> data;

	if (extension == "bmp")
	{
		LoadTextureBMP(filePath, data, width, height);

		internalFormat = GL_RGB;
		format = GL_RGB;
		type = GL_UNSIGNED_BYTE;
	}
	else
		throw std::exception("AIOpenGLTexture: Wrong file format!");

	openGLCore.glGenTextures(1, &textureId);
	openGLCore.glBindTexture(GL_TEXTURE_2D, textureId);
	openGLCore.glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, &data[0]);

	openGLCore.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	openGLCore.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

AIOpenGLTexture::AIOpenGLTexture(GLsizei width, GLsizei height, const void* data, GLint internalFormat, GLenum format, GLenum type)
{
	openGLCore.glGenTextures(1, &textureId);
	openGLCore.glBindTexture(GL_TEXTURE_2D, textureId);
	openGLCore.glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);

	openGLCore.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	openGLCore.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

TextureID AIOpenGLTexture::GetID() const noexcept
{
	return textureId;
}
