#pragma once

#include "AIOpenGLCore.h"
#include "AINeuralLayer.h"

class AIOpenGLConvolutionLayer : public AINeuralLayer
{
public:
	AIOpenGLConvolutionLayer();
	~AIOpenGLConvolutionLayer();

	void Connect(const AINeuralLayer* const previousNeuralLayer, const AINeuralLayer* const nextNeuralLayer) noexcept override final;
	void Compute() override final;
private:
	const AINeuralLayer* previousLayer;
	const AINeuralLayer* nextLayer;
};
