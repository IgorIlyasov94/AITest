#include "AIOpenGLConvolution3x3.h"

AIOpenGLConvolution3x3::AIOpenGLConvolution3x3()
	: previousLayer(nullptr), paddingSize(0), inputTexture(nullptr), outputTexture(nullptr), kernel{}, bias(0.0f)
{
	std::random_device randomDevice;

	std::default_random_engine defaultRandomEngine(randomDevice());

	for (auto& kernelElement : kernel)
	{
		kernelElement = Random(defaultRandomEngine) * 2.0f - 1.0f;
	}
}

AIOpenGLConvolution3x3::~AIOpenGLConvolution3x3()
{

}

void AIOpenGLConvolution3x3::SetPaddingSize(int _paddingSize) noexcept
{
	paddingSize = _paddingSize;
}

void AIOpenGLConvolution3x3::Connect(const AINeuralLayer* const previousNeuralLayer)
{
	previousLayer = previousNeuralLayer;

	ThrowIfFailed(previousNeuralLayer != nullptr, "AIOpenGLConvolution3x3::Connect: Previous neural layer must not be null!");

	ThrowIfFailed(previousNeuralLayer->GetOutputObject().has_value(), "AIOpenGLConvolution3x3::Connect: Previous neural layer has no return result object!");

	ThrowIfFailed(previousNeuralLayer->GetOutputObject().type() == typeid(AIOpenGLTexture*), "AIOpenGLConvolution3x3::Connect: Previous neural layer has no return result object!");

	inputTexture = std::any_cast<AIOpenGLTexture*>(previousNeuralLayer->GetOutputObject());

	auto resultImageWidth = inputTexture->GetWidth() + paddingSize * 2;
	auto resultImageHeight = inputTexture->GetHeight() + paddingSize * 2;

	auto resultTextureId = texturePool.CreateTexture(resultImageWidth, resultImageHeight, nullptr, GL_R32F, GL_RED, GL_FLOAT);
	outputTexture = texturePool.GetTexture(resultTextureId);
}

void AIOpenGLConvolution3x3::Compute()
{
	auto paddingSizeShaderLocation = openGLCore.glGetUniformLocation(shader.GetShaderProgram(), "paddingSize");
	auto biasShaderLocation = openGLCore.glGetUniformLocation(shader.GetShaderProgram(), "bias");

	auto kernelShaderLocation = openGLCore.glGetUniformLocation(shader.GetShaderProgram(), "kernel");


	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glUseProgram(shader.GetShaderProgram());

	openGLCore.glUniform1i(paddingSizeShaderLocation, paddingSize);
	openGLCore.glUniform1f(biasShaderLocation, bias);

	openGLCore.glUniformMatrix3fv(kernelShaderLocation, 1, GL_FALSE, &kernel[0]);

	openGLCore.glBindImageTexture(0, inputTexture->GetID(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
	openGLCore.glBindImageTexture(1, outputTexture->GetID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	openGLCore.glDispatchCompute(AlignTextureSizeForDispatch(inputTexture->GetWidth(),16, paddingSize), AlignTextureSizeForDispatch(inputTexture->GetHeight(), 16, paddingSize), 1);

	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
	openGLCore.glBindImageTexture(1, 0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);
}

const std::any& AIOpenGLConvolution3x3::GetOutputObject() const
{
	return std::any(outputTexture);
}
