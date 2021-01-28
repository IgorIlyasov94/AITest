#include "AIOpenGLConvolutionLayer.h"

AIOpenGLConvolutionLayer::AIOpenGLConvolutionLayer()
	: previousLayer(nullptr), nextLayer(nullptr)
{

}

AIOpenGLConvolutionLayer::~AIOpenGLConvolutionLayer()
{

}

void AIOpenGLConvolutionLayer::Connect(const AINeuralLayer* const previousNeuralLayer, const AINeuralLayer* const nextNeuralLayer) noexcept
{
	previousLayer = previousNeuralLayer;
	nextLayer = nextNeuralLayer;
}

void AIOpenGLConvolutionLayer::Compute()
{

}
