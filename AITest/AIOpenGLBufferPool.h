#pragma once

#include "AIOpenGLBuffer.h"

class AIOpenGLBufferPool
{
public:
	static AIOpenGLBufferPool& GetInstance();

	BufferID CreateBuffer(const void* data);

	AIOpenGLBuffer* GetBuffer(BufferID bufferId) const;

private:
	AIOpenGLBufferPool();
	~AIOpenGLBufferPool();

	AIOpenGLBufferPool(const AIOpenGLBufferPool&) = delete;
	AIOpenGLBufferPool(AIOpenGLBufferPool&&) = delete;
	AIOpenGLBufferPool& operator=(const AIOpenGLBufferPool&) = delete;
	AIOpenGLBufferPool& operator=(AIOpenGLBufferPool&&) = delete;

	std::vector<std::shared_ptr<AIOpenGLBuffer>> buffers;
};
