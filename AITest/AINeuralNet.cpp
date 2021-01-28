#include "AINeuralNet.h"

AINeuralNet::AINeuralNet()
{

}

AINeuralNet::~AINeuralNet()
{

}

int AINeuralNet::AddNeuralLayer(AINeuralLayer*&& newNeuralLayer)
{
	ThrowIfFailed(newNeuralLayer != nullptr, "AINeuralNet::AddNeuralLayer: Added layer can not be null");

	neuralLayers.push_back(std::shared_ptr<AINeuralLayer>(std::forward<AINeuralLayer*>(newNeuralLayer)));

	return neuralLayers.size() - 1;
}

void AINeuralNet::SetNeuralOutputLayer(AINeuralOutputLayer*&& neuralOutputLayer)
{
	ThrowIfFailed(neuralOutputLayer != nullptr, "AINeuralNet::SetNeuralOutputLayer: Output layer can not be null");

	outputLayer = std::shared_ptr<AINeuralOutputLayer>(std::forward<AINeuralOutputLayer*>(neuralOutputLayer));
}

void AINeuralNet::Compute()
{
	ThrowIfFailed(neuralLayers.size() > 0, "AINeuralNet::Compute: Neural net has no layers");
	ThrowIfFailed(outputLayer != nullptr, "AINeuralNet::Compute: Neural net has no output layer");

	for (auto& neuralLayer : neuralLayers)
	{
		neuralLayer->Compute();
	}

	//outputLayer
}
