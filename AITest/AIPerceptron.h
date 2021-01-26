#pragma once

#include "AIMatrix.h"

using ActivationFunction = float (*)(float weightSumm);

float StandardActivationFunction(float weightSumm);

class AIPerceptron
{
public:
	AIPerceptron();
	AIPerceptron(const Matrix& _weights, const ActivationFunction _activationFunction = StandardActivationFunction);

	~AIPerceptron();

	const float Output(const Matrix& inputData) const;

	void Educate(const Matrix& inputData, const float referenceValue);

	Matrix& Weights();

private:
	Matrix weights;

	ActivationFunction activationFunction;
};
