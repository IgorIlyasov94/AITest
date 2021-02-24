#pragma once

#include "Includes.h"

class AINeuralLayer
{
public:
	AINeuralLayer();
	virtual ~AINeuralLayer();

	virtual void Connect(const AINeuralLayer* const previousLayer) = 0;
	virtual void Compute() = 0;

	virtual const std::any& GetOutputObject() const = 0;
};
