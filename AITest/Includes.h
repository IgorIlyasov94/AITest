#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>

#include <vector>
#include <array>
#include <exception>
#include <utility>
#include <algorithm>
#include <memory>
#include <iterator>

#include <iostream>
#include <fstream>
#include <iomanip>

#include <chrono>

inline void ThrowIfFailed(bool successCondition, const char* errorMessage)
{
	if (!successCondition)
		throw std::exception(errorMessage);
}

inline int AlignToNextPowerOf2(int value) noexcept
{
	return static_cast<int>(std::pow(2, static_cast<int>(std::ceil(std::log(static_cast<float>(value)) / std::log(2.0f)))));
}