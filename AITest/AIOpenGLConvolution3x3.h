#pragma once

#include "AIOpenGLCore.h"
#include "AIOpenGLTexturePool.h"
#include "AIOpenGLComputeShaderCollection.h"
#include "AINeuralLayer.h"

class AIOpenGLConvolution3x3 : public AINeuralLayer
{
public:
	AIOpenGLConvolution3x3();
	~AIOpenGLConvolution3x3();

	void SetPaddingSize(int _paddingSize) noexcept;
	void Connect(const AINeuralLayer* const previousNeuralLayer) override final;
	void Compute() override final;

	const std::any& GetOutputObject() const override final;

private:
	const AINeuralLayer* previousLayer;

	AIOpenGLCore& openGLCore = AIOpenGLCore::GetInstance();
	AIOpenGLTexturePool& texturePool = AIOpenGLTexturePool::GetInstance();
	const AIOpenGLComputeShader& shader = AIOpenGLComputeShaderCollection::GetInstance().GetConvolution3x3();

	int paddingSize;

	const AIOpenGLTexture* inputTexture;
	AIOpenGLTexture* outputTexture;

	std::array<GLfloat, 9> kernel;

	GLfloat bias;
};
