#pragma once

#include "AIOpenGLCore.h"
#include "AIOpenGLHelper.h"

using ShaderID = GLuint;
using ShaderProgramID = GLuint;

class AIOpenGLComputeShader
{
public:
	~AIOpenGLComputeShader();

	explicit AIOpenGLComputeShader(std::string&& shaderFilePath);

	ShaderProgramID GetShaderProgram() const noexcept;

private:
	AIOpenGLComputeShader() = delete;

	AIOpenGLCore& openGLCore = AIOpenGLCore::GetInstance();

	void CheckCompileErrors(std::string&& shaderFilePath);

	ShaderID shaderId;
	ShaderProgramID shaderProgramId;
};
