#pragma once

#include "AIOpenGLCore.h"

using BufferID = GLuint;
using OpenGLBufferID = GLuint;

class AIOpenGLBuffer
{
public:
	~AIOpenGLBuffer();

	AIOpenGLBuffer(const void* data, size_t dataSize);

	OpenGLBufferID GetID() const noexcept;
	size_t GetSize() const noexcept;

private:
	AIOpenGLBuffer() = delete;

	AIOpenGLCore& openGLCore = AIOpenGLCore::GetInstance();

	size_t bufferSize;

	OpenGLBufferID bufferId;
};

