#pragma once

#include "AIOpenGLCore.h"

using ShaderID = GLuint;
using ShaderProgramID = GLuint;

class AIOpenGLComputeShader
{
public:
	~AIOpenGLComputeShader();

	AIOpenGLComputeShader(std::string shaderFilePath);

	void Dispatch(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ);

private:
	AIOpenGLComputeShader() = delete;

	AIOpenGLCore& openGLCore = AIOpenGLCore::GetInstance();

	void CheckCompileErrors();

	ShaderID shaderId;
	ShaderProgramID shaderProgramId;
};
