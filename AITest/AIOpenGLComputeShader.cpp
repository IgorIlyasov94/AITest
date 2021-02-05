#include "AIOpenGLComputeShader.h"

AIOpenGLComputeShader::~AIOpenGLComputeShader()
{
	openGLCore.glDetachShader(shaderProgramId, shaderId);
	openGLCore.glDeleteShader(shaderId);
	
	openGLCore.glDeleteProgram(shaderProgramId);
}

AIOpenGLComputeShader::AIOpenGLComputeShader(std::string&& shaderFilePath)
{
	std::ifstream shaderFile{ shaderFilePath, std::ios::binary | std::ios::in };

	shaderFile >> std::noskipws;

	if (!shaderFile.is_open())
		throw std::exception("AIOpenGLComputeShader: File loading has failed!");

	std::string shaderText{ std::istream_iterator<char>(shaderFile), std::istream_iterator<char>() };

	const GLchar* const shaderTextPtr = shaderText.c_str();
	const GLint shaderTextLength = shaderText.size();

	shaderId = openGLCore.glCreateShader(GL_COMPUTE_SHADER);
	openGLCore.glShaderSource(shaderId, 1, &shaderTextPtr, &shaderTextLength);
	openGLCore.glCompileShader(shaderId);

	shaderProgramId = openGLCore.glCreateProgram();
	openGLCore.glAttachShader(shaderProgramId, shaderId);
	openGLCore.glLinkProgram(shaderProgramId);

	CheckCompileErrors(std::forward<std::string>(shaderFilePath));
}

void AIOpenGLComputeShader::Dispatch(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ)
{
	openGLCore.glUseProgram(shaderProgramId);
	openGLCore.glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
}

void AIOpenGLComputeShader::CheckCompileErrors(std::string&& shaderFilePath)
{
	GLint isLinked = 0;

	openGLCore.glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		openGLCore.glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);

		openGLCore.glGetProgramInfoLog(shaderProgramId, maxLength, &maxLength, &infoLog[0]);

		infoLog.insert(infoLog.cbegin(), '\n');
		infoLog.insert(infoLog.cbegin(), shaderFilePath.begin(), shaderFilePath.end());
		
		throw std::exception(&infoLog[0]);
	}
}
