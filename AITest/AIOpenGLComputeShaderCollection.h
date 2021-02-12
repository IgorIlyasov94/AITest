#pragma once

#include "AIOpenGLComputeShader.h"

class AIOpenGLComputeShaderCollection
{
public:
	static AIOpenGLComputeShaderCollection& GetInstance();

	const AIOpenGLComputeShader& GetConvertTextureToBuffer();
	const AIOpenGLComputeShader& GetConvertBufferToTexture();
	const AIOpenGLComputeShader& GetPrimaryConvolution3x3();

private:
	AIOpenGLComputeShaderCollection();
	~AIOpenGLComputeShaderCollection();

	AIOpenGLComputeShaderCollection(const AIOpenGLComputeShaderCollection&) = delete;
	AIOpenGLComputeShaderCollection(AIOpenGLComputeShaderCollection&&) = delete;
	AIOpenGLComputeShaderCollection& operator=(const AIOpenGLComputeShaderCollection&) = delete;
	AIOpenGLComputeShaderCollection& operator=(AIOpenGLComputeShaderCollection&&) = delete;

	AIOpenGLComputeShader convertTextureToBuffer;
	AIOpenGLComputeShader convertBufferToTexture;
	AIOpenGLComputeShader primaryConvolution3x3;
};

