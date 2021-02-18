#pragma once

#include "AIOpenGLComputeShader.h"

class AIOpenGLComputeShaderCollection
{
public:
	static AIOpenGLComputeShaderCollection& GetInstance();

	const AIOpenGLComputeShader& GetConvertTextureToBuffer();
	const AIOpenGLComputeShader& GetConvertBufferToTexture();
	const AIOpenGLComputeShader& GetPrimaryConvolution3x3();
	const AIOpenGLComputeShader& GetMinPool2x2();
	const AIOpenGLComputeShader& GetMaxPool2x2();
	const AIOpenGLComputeShader& GetAvgPool2x2();

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
	AIOpenGLComputeShader minPool2x2;
	AIOpenGLComputeShader maxPool2x2;
	AIOpenGLComputeShader avgPool2x2;
};

