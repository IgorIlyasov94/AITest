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

AIOpenGLComputeShaderCollection::AIOpenGLComputeShaderCollection()
	: convertTextureToBuffer("Shaders//ConvertTextureToBufferCS.glsl"),
	convertBufferToTexture("Shaders//ConvertBufferToTextureCS.glsl"),
	primaryConvolution3x3("Shaders//PrimaryConvolution3x3CS.glsl")
{

}

AIOpenGLComputeShaderCollection::~AIOpenGLComputeShaderCollection()
{

}
