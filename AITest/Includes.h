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