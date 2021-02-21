#include "AIOpenGLComputeShaderCollection.h"

AIOpenGLComputeShaderCollection& AIOpenGLComputeShaderCollection::GetInstance()
{
	static AIOpenGLComputeShaderCollection thisInstance;

	return thisInstance;
}

const AIOpenGLComputeShader& AIOpenGLComputeShaderCollection::GetConvertTextureToBuffer()
{
	return convertTextureToBuffer;
}

const AIOpenGLComputeShader& AIOpenGLComputeShaderCollection::GetConvertBufferToTexture()
{
	return convertBufferToTexture;
}

const AIOpenGLComputeShader& AIOpenGLComputeShaderCollection::GetPrimaryConvolution3x3()
{
	return primaryConvolution3x3;
}

const AIOpenGLComputeShader& AIOpenGLComputeShaderCollection::GetConvolution3x3()
{
	return convolution3x3;
}

const AIOpenGLComputeShader& AIOpenGLComputeShaderCollection::GetConvolution4x4()
{
	return convolution4x4;
}

const AIOpenGLComputeShader& AIOpenGLComputeShaderCollection::GetMinPool2x2()
{
	return minPool2x2;
}

const AIOpenGLComputeShader& AIOpenGLComputeShaderCollection::GetMaxPool2x2()
{
	return maxPool2x2;
}

const AIOpenGLComputeShader& AIOpenGLComputeShaderCollection::GetAvgPool2x2()
{
	return avgPool2x2;
}

AIOpenGLComputeShaderCollection::AIOpenGLComputeShaderCollection()
	: convertTextureToBuffer("Shaders//ConvertTextureToBufferCS.glsl"),
	convertBufferToTexture("Shaders//ConvertBufferToTextureCS.glsl"),
	primaryConvolution3x3("Shaders//PrimaryConvolution3x3CS.glsl"),
	convolution3x3("Shaders//Convolution3x3CS.glsl"),
	convolution4x4("Shaders//Convolution4x4CS.glsl"),
	minPool2x2("Shaders//MinPool2x2CS.glsl"),
	maxPool2x2("Shaders//MaxPool2x2CS.glsl"),
	avgPool2x2("Shaders//AvgPool2x2CS.glsl")
{

}

AIOpenGLComputeShaderCollection::~AIOpenGLComputeShaderCollection()
{

}
