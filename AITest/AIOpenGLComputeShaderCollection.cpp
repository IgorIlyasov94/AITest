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

AIOpenGLComputeShaderCollection::AIOpenGLComputeShaderCollection()
	: convertTextureToBuffer("Shaders//ConvertTextureToBufferCS.glsl"),
	convertBufferToTexture("Shaders//ConvertBufferToTextureCS.glsl")
{

}

AIOpenGLComputeShaderCollection::~AIOpenGLComputeShaderCollection()
{

}
