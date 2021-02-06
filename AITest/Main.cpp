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

		auto testTextureId = texturePool.LoadTexture("TestImage.bmp");
		auto testTexture = texturePool.GetTexture(testTextureId);
		
		auto testBufferSize = testTexture->GetWidth() * testTexture->GetHeight() * testTexture->GetStride();
		std::vector<uint8_t> bufferPaddingData(testBufferSize);

		std::fill(bufferPaddingData.begin(), bufferPaddingData.end(), 0);

		auto testBufferId = bufferPool.CreateBuffer(&bufferPaddingData[0], bufferPaddingData.size());
		auto testBuffer = bufferPool.GetBuffer(testBufferId);

		auto& convertTextureToBufferCS = shaderPool.GetConvertTextureToBuffer();
		auto& convertBufferToTextureCS = shaderPool.GetConvertBufferToTexture();

		auto widthShaderLocation0 = openGLCore.glGetUniformLocation(convertTextureToBufferCS.GetShaderProgram(), "imageWidth");
		auto heightShaderLocation0 = openGLCore.glGetUniformLocation(convertTextureToBufferCS.GetShaderProgram(), "imageHeight");

		auto widthShaderLocation1 = openGLCore.glGetUniformLocation(convertBufferToTextureCS.GetShaderProgram(), "imageWidth");
		auto heightShaderLocation1 = openGLCore.glGetUniformLocation(convertBufferToTextureCS.GetShaderProgram(), "imageHeight");

		openGLCore.glUniform1i(widthShaderLocation0, testTexture->GetWidth());
		openGLCore.glUniform1i(heightShaderLocation0, testTexture->GetHeight());

		openGLCore.glBindImageTexture(0, testTexture->GetID(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGB);
		openGLCore.glBindBuffer(GL_SHADER_STORAGE_BUFFER, testBuffer->GetID());
		openGLCore.glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, testBuffer->GetID());

		convertTextureToBufferCS.Dispatch(testTexture->GetWidth(), testTexture->GetHeight(), 1);

		openGLCore.glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		openGLCore.glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGB);
		openGLCore.glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);



		openGLCore.glUniform1i(widthShaderLocation1, testTexture->GetWidth());
		openGLCore.glUniform1i(heightShaderLocation1, testTexture->GetHeight());

		openGLCore.glBindBuffer(GL_SHADER_STORAGE_BUFFER, testBuffer->GetID());
		openGLCore.glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, testBuffer->GetID());
		openGLCore.glBindImageTexture(1, testTexture->GetID(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGB);

		convertTextureToBufferCS.Dispatch(testTexture->GetWidth(), testTexture->GetHeight(), 1);

		openGLCore.glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		openGLCore.glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGB);
		openGLCore.glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		openGLCore.Compute();



		const auto textureDataSize = testTexture->GetWidth() * testTexture->GetHeight() * testTexture->GetStride();

		std::vector<uint8_t> textureData(textureDataSize);

		openGLCore.glGetTextureImage(testTexture->GetID(), 0, GL_RGB, GL_UNSIGNED_BYTE, textureDataSize, &textureData[0]);

		AITextureBMP::Save("TestImageOutput.bmp", textureData, testTexture->GetWidth(), testTexture->GetHeight());
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR | MB_DEFAULT_DESKTOP_ONLY);
	}

	return 0;
}