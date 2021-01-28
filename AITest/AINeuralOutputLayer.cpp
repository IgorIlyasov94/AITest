#include "AINeuralOutputLayer.h"

AINeuralOutputLayer::AINeuralOutputLayer()
	: lastLayer(nullptr)
{

}

AINeuralOutputLayer::~AINeuralOutputLayer()
{

}

void AINeuralOutputLayer::Connect(const AINeuralLayer* const _lastLayer)
{
	lastLayer = _lastLayer;
}
