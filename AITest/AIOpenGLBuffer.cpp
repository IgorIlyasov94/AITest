#include "AIOpenGLBuffer.h"

AIOpenGLBuffer::~AIOpenGLBuffer()
{
	openGLCore.glDeleteBuffers(1, &bufferId);
}

AIOpenGLBuffer::AIOpenGLBuffer(const void* data, size_t dataSize)
	: bufferSize(dataSize)
{
	openGLCore.glGenBuffers(1, &bufferId);
	openGLCore.glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferId);
	openGLCore.glBufferData(GL_SHADER_STORAGE_BUFFER, dataSize, data, GL_STATIC_COPY);
	openGLCore.glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

OpenGLBufferID AIOpenGLBuffer::GetID() const noexcept
{
	return bufferId;
}

size_t AIOpenGLBuffer::GetSize() const noexcept
{
	return bufferSize;
}
