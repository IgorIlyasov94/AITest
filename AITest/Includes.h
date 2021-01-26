#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>

#include <vector>
#include <exception>
//#include <algorithm>
#include <utility>
#include <memory>

#include <iostream>
#include <iomanip>

#include <chrono>

inline void ThrowIfFailed(bool successCondition, const char* errorMessage)
{
	if (!successCondition)
		throw std::exception(errorMessage);
}