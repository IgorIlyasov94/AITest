#include "Main.h"

#include "AIOpenGLTexturePool.h"
#include "AIOpenGLBufferPool.h"
#include "AIOpenGLComputeShaderCollection.h"

int main()
{
	try
	{
		auto& openGLCore = AIOpenGLCore::GetInstance();
		auto& texturePool = AIOpenGLTexturePool::GetInstance();
		auto& bufferPool = AIOpenGLBufferPool::GetInstance();
		auto& shaderPool = AIOpenGLComputeShaderCollection::GetInstance();

		//auto tex = texturePool.LoadTexture("TestImage.bmp");

		openGLCore.Compute();
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR | MB_DEFAULT_DESKTOP_ONLY);
	}

	return 0;
}