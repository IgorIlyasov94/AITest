#include "AIFunction.h"

AIFunction::AIFunction()
	: function(NullFunction)
{
}

AIFunction::AIFunction(const Function& _function)
	: function(_function)
{
}

AIFunction::AIFunction(const AIFunction& aiFunction)
	: function(aiFunction.function)
{
}

AIFunction::AIFunction(AIFunction&& aiFunction) noexcept
	: function(NullFunction)
{
	std::swap(function, aiFunction.function);
}

AIFunction& AIFunction::operator=(const AIFunction& aiFunction)
{
	function = aiFunction.function;

	return *this;
}

AIFunction& AIFunction::operator=(AIFunction&& aiFunction) noexcept
{
	std::swap(function, aiFunction.function);

	return *this;
}

void AIFunction::Set(const Function& _function)
{
	function = _function;
}

float AIFunction::operator()(float argument) const
{
	return function(argument);
}

float AIFunction::Derivative(float argument) const
{
	return (function(argument + dx) - function(argument - dx)) / d2x;
}

float AIFunction::SecondDerivative(float argument) const
{
	float result = function(argument + dx_2);
	result += function(argument - dx_2);
	result -= 2.0f * function(argument);
	result /= ddx_2;

	return result;
}

float AIFunction::Primitive(float argument) const
{
	if (argument == 0.0f)
		return DefiniteIntegral(-0.1f, 0.1f);

	return DefiniteIntegral(std::min(0.0f, argument), std::max(0.0f, argument));
}

float AIFunction::DefiniteIntegral(float lowerLimit, float upperLimit) const
{
	float summ = 0.0f;
	float integrationStep = (upperLimit - lowerLimit) / static_cast<float>(integrationPrecision);

	float partialLowerLimit = lowerLimit;
	float partialUpperLimit = lowerLimit + integrationStep;

	for (int integrationPartId = 0; integrationPartId < integrationPrecision; integrationPartId++)
	{
		summ += SimpsonRule(partialLowerLimit, partialUpperLimit);

		partialLowerLimit = partialUpperLimit;
		partialUpperLimit += integrationStep;
	}

	return summ;
}

float AIFunction::SimpsonRule(float lowerLimit, float upperLimit) const
{
	float step = upperLimit - lowerLimit;

	float result = function(lowerLimit);
	result += 4.0f * function((lowerLimit + upperLimit) * 0.5f);
	result += function(upperLimit);
	result *= step / 6.0f;

	return result;
}

float NullFunction(float)
{
	return 0.0f;
}
