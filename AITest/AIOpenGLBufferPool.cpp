#include "AIOpenGLBufferPool.h"

AIOpenGLBufferPool& AIOpenGLBufferPool::GetInstance()
{
	static AIOpenGLBufferPool thisInstance;

	return thisInstance;
}

BufferID AIOpenGLBufferPool::CreateBuffer(const void* data, size_t dataSize)
{
	buffers.push_back(std::shared_ptr<AIOpenGLBuffer>(new AIOpenGLBuffer(data, dataSize)));

	auto newBufferId = buffers[buffers.size() - 1]->GetID();

	return newBufferId;
}

AIOpenGLBuffer* AIOpenGLBufferPool::GetBuffer(BufferID bufferId) const
{
	ThrowIfFailed(bufferId < buffers.size(), "AIOpenGLBufferPool::GetBuffer: Index out of bounds!");

	return buffers[bufferId].get();
}

AIOpenGLBufferPool::AIOpenGLBufferPool()
{

}

AIOpenGLBufferPool::~AIOpenGLBufferPool()
{

}
