#pragma once

#include "AIOpenGLCore.h"

using BufferID = GLuint;

class AIOpenGLBuffer
{
public:
	~AIOpenGLBuffer();

	AIOpenGLBuffer(const void* data, size_t dataSize);

	BufferID GetID() const noexcept;

private:
	AIOpenGLBuffer() = delete;

	AIOpenGLCore& openGLCore = AIOpenGLCore::GetInstance();

	BufferID bufferId;
};

