#pragma once

#include "AIOpenGLCore.h"

using ShaderID = GLuint;
using ShaderProgramID = GLuint;

class AIOpenGLComputeShader
{
public:
	~AIOpenGLComputeShader();

	explicit AIOpenGLComputeShader(std::string&& shaderFilePath);

	void Dispatch(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ);

private:
	AIOpenGLComputeShader() = delete;

	AIOpenGLCore& openGLCore = AIOpenGLCore::GetInstance();

	void CheckCompileErrors(std::string&& shaderFilePath);

	ShaderID shaderId;
	ShaderProgramID shaderProgramId;
};
