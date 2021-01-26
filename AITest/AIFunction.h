#pragma once

#include "Includes.h"

using Function = float (*)(float);

float NullFunction(float);

class AIFunction
{
public:
	AIFunction();
	~AIFunction() {};

	AIFunction(const Function& _function);

	AIFunction(const AIFunction& aiFunction);
	AIFunction(AIFunction&& aiFunction) noexcept;
	AIFunction& operator=(const AIFunction& aiFunction);
	AIFunction& operator=(AIFunction&& aiFunction) noexcept;

	void Set(const Function& _function);

	float operator()(float argument) const;

	float Derivative(float argument) const;
	float SecondDerivative(float argument) const;

	float Primitive(float argument) const;
	float DefiniteIntegral(float lowerLimit, float upperLimit) const;

private:
	float SimpsonRule(float lowerLimit, float upperLimit) const;

	Function function;

	const float dx = 0.000100138f;
	const float d2x = 0.000200276f;
	const float dx_2 = 0.0735092f;
	const float ddx_2 = 0.0054036024846f;

	const int integrationPrecision = 10;
};