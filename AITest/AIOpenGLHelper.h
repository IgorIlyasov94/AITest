#pragma once

#include "AIOpenGLCore.h"

inline constexpr auto AlignTextureSizeForDispatch(GLsizei textureSize, GLint groupNumber, GLint paddingSize)
{
	if (paddingSize > 0)
		return (textureSize + paddingSize) / groupNumber + 1;

	return textureSize / groupNumber;
}
