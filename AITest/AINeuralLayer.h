#pragma once

#include "Includes.h"

class AINeuralLayer
{
public:
	AINeuralLayer();
	virtual ~AINeuralLayer();

	virtual void Connect(const AINeuralLayer* const previousLayer, const AINeuralLayer* const nextLayer) noexcept = 0;
	virtual void Compute() = 0;
};
