#pragma once

#include "AINeuralLayer.h"
#include "AINeuralOutputLayer.h"

class AINeuralNet
{
public:
	AINeuralNet();
	~AINeuralNet();

	int AddNeuralLayer(AINeuralLayer*&& newNeuralLayer);
	void SetNeuralOutputLayer(AINeuralOutputLayer*&& neuralOutputLayer);

	void Compute();

private:
	std::vector<std::shared_ptr<AINeuralLayer>> neuralLayers;
	std::shared_ptr<AINeuralOutputLayer> outputLayer;
};
