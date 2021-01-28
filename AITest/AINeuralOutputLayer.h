#pragma once

#include "AINeuralLayer.h"

class AINeuralOutputLayer
{
public:
	AINeuralOutputLayer();
	~AINeuralOutputLayer();

	void Connect(const AINeuralLayer* const _lastLayer);
private:
	const AINeuralLayer* lastLayer;
};
