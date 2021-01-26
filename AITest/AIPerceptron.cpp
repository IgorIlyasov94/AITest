#include "AIPerceptron.h"

AIPerceptron::AIPerceptron()
	: weights(1, 1), activationFunction(StandardActivationFunction)
{
}

AIPerceptron::AIPerceptron(const Matrix& _weights, const ActivationFunction _activationFunction)
	: weights(_weights), activationFunction(_activationFunction)
{
	if (weights.GetRowNumber() != 1 && weights.GetColumnNumber() != 1)
		throw std::exception("Weights matrix should have dimensions 1xN or Nx1");

	if (weights.GetRowNumber() == 1)
		weights = weights.Transpose();
}

AIPerceptron::~AIPerceptron()
{
}

const float AIPerceptron::Output(const Matrix& inputData) const
{
	float summW = (inputData * weights).Cell(0, 0);

	return activationFunction(summW);
}

void AIPerceptron::Educate(const Matrix& inputData, const float referenceValue)
{
	float summW = (inputData * weights).Cell(0, 0);

	float result = activationFunction(summW);

	if (result != referenceValue)
	{
		for (size_t weightId = 0; weightId < weights.GetRowNumber(); weightId++)
		{
			float dW = (referenceValue - result) * inputData.Cell(0, weightId);
			
			weights.Cell(weightId, 0) += dW;
		}
	}
}

Matrix& AIPerceptron::Weights()
{
	return weights;
}

float StandardActivationFunction(float weightSumm)
{
	return (weightSumm > 0.0f) ? 1.0f : 0.0f;
}
