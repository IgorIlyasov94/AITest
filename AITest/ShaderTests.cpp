#include "ShaderTests.h"

void TESTTextureAndBufferConversions(std::string inputImagePath, std::string outputImagePath)
{
	auto& openGLCore = AIOpenGLCore::GetInstance();
	auto& texturePool = AIOpenGLTexturePool::GetInstance();
	auto& bufferPool = AIOpenGLBufferPool::GetInstance();
	auto& shaderPool = AIOpenGLComputeShaderCollection::GetInstance();

	auto testTextureId = texturePool.LoadTexture(inputImagePath);
	auto testTexture = texturePool.GetTexture(testTextureId);

	auto testBufferSize = testTexture->GetWidth() * testTexture->GetHeight() * testTexture->GetStride();
	std::vector<uint8_t> bufferPaddingData(testBufferSize);

	std::fill(bufferPaddingData.begin(), bufferPaddingData.end(), 0);

	auto testBufferId = bufferPool.CreateBuffer(&bufferPaddingData[0], bufferPaddingData.size());
	auto testBuffer = bufferPool.GetBuffer(testBufferId);

	auto outputTextureId = texturePool.CreateTexture(testTexture->GetWidth(), testTexture->GetHeight(), &bufferPaddingData[0], GL_RGBA, GL_RGBA);
	auto outputTexture = texturePool.GetTexture(outputTextureId);

	auto& convertTextureToBufferCS = shaderPool.GetConvertTextureToBuffer();
	auto& convertBufferToTextureCS = shaderPool.GetConvertBufferToTexture();

	auto widthShaderLocation0 = openGLCore.glGetUniformLocation(convertTextureToBufferCS.GetShaderProgram(), "imageWidth");
	auto heightShaderLocation0 = openGLCore.glGetUniformLocation(convertTextureToBufferCS.GetShaderProgram(), "imageHeight");

	auto widthShaderLocation1 = openGLCore.glGetUniformLocation(convertBufferToTextureCS.GetShaderProgram(), "imageWidth");
	auto heightShaderLocation1 = openGLCore.glGetUniformLocation(convertBufferToTextureCS.GetShaderProgram(), "imageHeight");


	{
		openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

		openGLCore.glUseProgram(convertTextureToBufferCS.GetShaderProgram());

		openGLCore.glUniform1i(widthShaderLocation0, testTexture->GetWidth());
		openGLCore.glUniform1i(heightShaderLocation0, testTexture->GetHeight());

		openGLCore.glBindImageTexture(0, testTexture->GetID(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
		openGLCore.glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, testBuffer->GetID());

		openGLCore.glDispatchCompute(testTexture->GetWidth() / 16, testTexture->GetHeight() / 16, 1);

		openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

		openGLCore.glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA);
		openGLCore.glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	{
		openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

		openGLCore.glUseProgram(convertBufferToTextureCS.GetShaderProgram());

		openGLCore.glUniform1i(widthShaderLocation1, outputTexture->GetWidth());
		openGLCore.glUniform1i(heightShaderLocation1, outputTexture->GetHeight());

		openGLCore.glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, testBuffer->GetID());
		openGLCore.glBindImageTexture(1, outputTexture->GetID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);

		openGLCore.glDispatchCompute(testBuffer->GetSize() / 64, 1, 1);

		openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

		openGLCore.glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA);
		openGLCore.glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}


	const auto textureDataSize = outputTexture->GetWidth() * outputTexture->GetHeight() * outputTexture->GetStride();

	std::vector<uint8_t> textureData(textureDataSize);

	openGLCore.glGetTextureImage(outputTexture->GetID(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureDataSize, &textureData[0]);

	AITextureBMP::Save(outputImagePath, textureData, outputTexture->GetWidth(), outputTexture->GetHeight());
}

void TESTPrimaryConvolution3x3(std::string inputImagePath, std::string outputImagePath)
{
	auto& openGLCore = AIOpenGLCore::GetInstance();
	auto& texturePool = AIOpenGLTexturePool::GetInstance();
	auto& shaderPool = AIOpenGLComputeShaderCollection::GetInstance();

	auto testTextureId = texturePool.LoadTexture(inputImagePath);
	auto testTexture = texturePool.GetTexture(testTextureId);

	auto outputTextureSize = testTexture->GetWidth() * testTexture->GetHeight() * 4;
	std::vector<uint8_t> texturePaddingData(outputTextureSize);

	std::fill(texturePaddingData.begin(), texturePaddingData.end(), 0);

	auto outputTextureId = texturePool.CreateTexture(testTexture->GetWidth(), testTexture->GetHeight(), &texturePaddingData[0], GL_R32F, GL_RED, GL_FLOAT);
	auto outputTexture = texturePool.GetTexture(outputTextureId);

	auto& primaryConvolution3x3 = shaderPool.GetPrimaryConvolution3x3();
	
	auto paddingSizeShaderLocation = openGLCore.glGetUniformLocation(primaryConvolution3x3.GetShaderProgram(), "paddingSize");
	auto biasShaderLocation = openGLCore.glGetUniformLocation(primaryConvolution3x3.GetShaderProgram(), "bias");

	auto kernelRShaderLocation = openGLCore.glGetUniformLocation(primaryConvolution3x3.GetShaderProgram(), "kernelR");
	auto kernelGShaderLocation = openGLCore.glGetUniformLocation(primaryConvolution3x3.GetShaderProgram(), "kernelG");
	auto kernelBShaderLocation = openGLCore.glGetUniformLocation(primaryConvolution3x3.GetShaderProgram(), "kernelB");
	

	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glUseProgram(primaryConvolution3x3.GetShaderProgram());

	openGLCore.glUniform1i(paddingSizeShaderLocation, 1);
	openGLCore.glUniform1f(biasShaderLocation, 0.0f);

	const GLfloat kernelR[] =
	{ 
		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f
	};

	const GLfloat kernelG[] =
	{
		-1.0f, 0.0f, -1.0f,
		0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, -1.0f
	};

	const GLfloat kernelB[] =
	{
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	openGLCore.glUniformMatrix3fv(kernelRShaderLocation, 1, GL_FALSE, kernelR);
	openGLCore.glUniformMatrix3fv(kernelGShaderLocation, 1, GL_FALSE, kernelG);
	openGLCore.glUniformMatrix3fv(kernelBShaderLocation, 1, GL_FALSE, kernelB);

	openGLCore.glBindImageTexture(0, testTexture->GetID(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
	openGLCore.glBindImageTexture(1, outputTexture->GetID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	openGLCore.glDispatchCompute(testTexture->GetWidth() / 16, testTexture->GetHeight() / 16, 1);

	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA);
	openGLCore.glBindImageTexture(1, 0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);
	

	const auto textureDataSize = outputTexture->GetWidth() * outputTexture->GetHeight() * 1;

	std::vector<uint8_t> textureData(textureDataSize);

	openGLCore.glGetTextureImage(outputTexture->GetID(), 0, GL_RED, GL_UNSIGNED_BYTE, textureDataSize, &textureData[0]);

	AITextureBMP::SaveSingleChannel(outputImagePath, textureData, outputTexture->GetWidth(), outputTexture->GetHeight());
}

void TESTConvolution3x3(std::string inputImagePath, std::string outputImagePath)
{
	auto& openGLCore = AIOpenGLCore::GetInstance();
	auto& texturePool = AIOpenGLTexturePool::GetInstance();
	auto& shaderPool = AIOpenGLComputeShaderCollection::GetInstance();

	auto testTextureId = texturePool.LoadTexture(inputImagePath);
	auto testTexture = texturePool.GetTexture(testTextureId);

	auto testTextureSize = testTexture->GetWidth() * testTexture->GetHeight() * 4;

	std::vector<uint8_t> testTextureData(testTextureSize);

	openGLCore.glGetTextureImage(testTexture->GetID(), 0, GL_RED, GL_FLOAT, testTextureSize, &testTextureData[0]);

	auto inputTextureId = texturePool.CreateTexture(testTexture->GetWidth(), testTexture->GetHeight(), &testTextureData[0], GL_R32F, GL_RED, GL_FLOAT);
	auto inputTexture = texturePool.GetTexture(inputTextureId);

	auto outputTextureSize = inputTexture->GetWidth() * inputTexture->GetHeight() * 4;
	std::vector<uint8_t> texturePaddingData(outputTextureSize);

	std::fill(texturePaddingData.begin(), texturePaddingData.end(), 0);

	auto outputTextureId = texturePool.CreateTexture(inputTexture->GetWidth(), inputTexture->GetHeight(), &texturePaddingData[0], GL_R32F, GL_RED, GL_FLOAT);
	auto outputTexture = texturePool.GetTexture(outputTextureId);

	auto& convolution3x3 = shaderPool.GetConvolution3x3();

	auto paddingSizeShaderLocation = openGLCore.glGetUniformLocation(convolution3x3.GetShaderProgram(), "paddingSize");
	auto biasShaderLocation = openGLCore.glGetUniformLocation(convolution3x3.GetShaderProgram(), "bias");

	auto kernelShaderLocation = openGLCore.glGetUniformLocation(convolution3x3.GetShaderProgram(), "kernel");
	

	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glUseProgram(convolution3x3.GetShaderProgram());

	openGLCore.glUniform1i(paddingSizeShaderLocation, 1);
	openGLCore.glUniform1f(biasShaderLocation, 0.0f);

	const GLfloat kernel[] =
	{
		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f
	};

	openGLCore.glUniformMatrix3fv(kernelShaderLocation, 1, GL_FALSE, kernel);

	openGLCore.glBindImageTexture(0, inputTexture->GetID(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
	openGLCore.glBindImageTexture(1, outputTexture->GetID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	openGLCore.glDispatchCompute(inputTexture->GetWidth() / 16, inputTexture->GetHeight() / 16, 1);

	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
	openGLCore.glBindImageTexture(1, 0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);


	const auto textureDataSize = outputTexture->GetWidth() * outputTexture->GetHeight() * 1;

	std::vector<uint8_t> textureData(textureDataSize);

	openGLCore.glGetTextureImage(outputTexture->GetID(), 0, GL_RED, GL_UNSIGNED_BYTE, textureDataSize, &textureData[0]);

	AITextureBMP::SaveSingleChannel(outputImagePath, textureData, outputTexture->GetWidth(), outputTexture->GetHeight());
}

void TESTMaxPool2x2(std::string inputImagePath, std::string outputImagePath)
{
	auto& openGLCore = AIOpenGLCore::GetInstance();
	auto& texturePool = AIOpenGLTexturePool::GetInstance();
	auto& shaderPool = AIOpenGLComputeShaderCollection::GetInstance();


	auto testTextureId = texturePool.LoadTexture(inputImagePath);
	auto testTexture = texturePool.GetTexture(testTextureId);
	
	auto testTextureSize = testTexture->GetWidth() * testTexture->GetHeight() * 4;

	std::vector<uint8_t> testTextureData(testTextureSize);

	openGLCore.glGetTextureImage(testTexture->GetID(), 0, GL_RED, GL_FLOAT, testTextureSize, &testTextureData[0]);

	auto inputTextureId = texturePool.CreateTexture(testTexture->GetWidth(), testTexture->GetHeight(), &testTextureData[0], GL_R32F, GL_RED, GL_FLOAT);
	auto inputTexture = texturePool.GetTexture(inputTextureId);


	auto outputTextureSize = inputTexture->GetWidth() * inputTexture->GetHeight() * inputTexture->GetStride() / 4;
	std::vector<uint8_t> texturePaddingData(outputTextureSize);

	std::fill(texturePaddingData.begin(), texturePaddingData.end(), 0);

	auto outputTextureId = texturePool.CreateTexture(inputTexture->GetWidth() / 2, inputTexture->GetHeight() / 2, &texturePaddingData[0], GL_R32F, GL_RED, GL_FLOAT);
	auto outputTexture = texturePool.GetTexture(outputTextureId);

	auto& maxPool2x2 = shaderPool.GetMaxPool2x2();


	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glUseProgram(maxPool2x2.GetShaderProgram());

	openGLCore.glBindImageTexture(0, inputTexture->GetID(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
	openGLCore.glBindImageTexture(1, outputTexture->GetID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	openGLCore.glDispatchCompute(outputTexture->GetWidth() / 16, outputTexture->GetHeight() / 16, 1);

	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
	openGLCore.glBindImageTexture(1, 0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);


	const auto textureDataSize = outputTexture->GetWidth() * outputTexture->GetHeight() * 1;

	std::vector<uint8_t> textureData(textureDataSize);

	openGLCore.glGetTextureImage(outputTexture->GetID(), 0, GL_RED, GL_UNSIGNED_BYTE, textureDataSize, &textureData[0]);

	AITextureBMP::SaveSingleChannel(outputImagePath, textureData, outputTexture->GetWidth(), outputTexture->GetHeight());
}

void TESTMinPool2x2(std::string inputImagePath, std::string outputImagePath)
{
	auto& openGLCore = AIOpenGLCore::GetInstance();
	auto& texturePool = AIOpenGLTexturePool::GetInstance();
	auto& shaderPool = AIOpenGLComputeShaderCollection::GetInstance();


	auto testTextureId = texturePool.LoadTexture(inputImagePath);
	auto testTexture = texturePool.GetTexture(testTextureId);

	auto testTextureSize = testTexture->GetWidth() * testTexture->GetHeight() * 4;

	std::vector<uint8_t> testTextureData(testTextureSize);

	openGLCore.glGetTextureImage(testTexture->GetID(), 0, GL_RED, GL_FLOAT, testTextureSize, &testTextureData[0]);

	auto inputTextureId = texturePool.CreateTexture(testTexture->GetWidth(), testTexture->GetHeight(), &testTextureData[0], GL_R32F, GL_RED, GL_FLOAT);
	auto inputTexture = texturePool.GetTexture(inputTextureId);


	auto outputTextureSize = inputTexture->GetWidth() * inputTexture->GetHeight() * inputTexture->GetStride() / 4;
	std::vector<uint8_t> texturePaddingData(outputTextureSize);

	std::fill(texturePaddingData.begin(), texturePaddingData.end(), 0);

	auto outputTextureId = texturePool.CreateTexture(inputTexture->GetWidth() / 2, inputTexture->GetHeight() / 2, &texturePaddingData[0], GL_R32F, GL_RED, GL_FLOAT);
	auto outputTexture = texturePool.GetTexture(outputTextureId);

	auto& minPool2x2 = shaderPool.GetMinPool2x2();


	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glUseProgram(minPool2x2.GetShaderProgram());

	openGLCore.glBindImageTexture(0, inputTexture->GetID(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
	openGLCore.glBindImageTexture(1, outputTexture->GetID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	openGLCore.glDispatchCompute(outputTexture->GetWidth() / 16, outputTexture->GetHeight() / 16, 1);

	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
	openGLCore.glBindImageTexture(1, 0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);


	const auto textureDataSize = outputTexture->GetWidth() * outputTexture->GetHeight() * 1;

	std::vector<uint8_t> textureData(textureDataSize);

	openGLCore.glGetTextureImage(outputTexture->GetID(), 0, GL_RED, GL_UNSIGNED_BYTE, textureDataSize, &textureData[0]);

	AITextureBMP::SaveSingleChannel(outputImagePath, textureData, outputTexture->GetWidth(), outputTexture->GetHeight());
}

void TESTAvgPool2x2(std::string inputImagePath, std::string outputImagePath)
{
	auto& openGLCore = AIOpenGLCore::GetInstance();
	auto& texturePool = AIOpenGLTexturePool::GetInstance();
	auto& shaderPool = AIOpenGLComputeShaderCollection::GetInstance();


	auto testTextureId = texturePool.LoadTexture(inputImagePath);
	auto testTexture = texturePool.GetTexture(testTextureId);

	auto testTextureSize = testTexture->GetWidth() * testTexture->GetHeight() * 4;

	std::vector<uint8_t> testTextureData(testTextureSize);

	openGLCore.glGetTextureImage(testTexture->GetID(), 0, GL_RED, GL_FLOAT, testTextureSize, &testTextureData[0]);

	auto inputTextureId = texturePool.CreateTexture(testTexture->GetWidth(), testTexture->GetHeight(), &testTextureData[0], GL_R32F, GL_RED, GL_FLOAT);
	auto inputTexture = texturePool.GetTexture(inputTextureId);


	auto outputTextureSize = inputTexture->GetWidth() * inputTexture->GetHeight() * inputTexture->GetStride() / 4;
	std::vector<uint8_t> texturePaddingData(outputTextureSize);

	std::fill(texturePaddingData.begin(), texturePaddingData.end(), 0);

	auto outputTextureId = texturePool.CreateTexture(inputTexture->GetWidth() / 2, inputTexture->GetHeight() / 2, &texturePaddingData[0], GL_R32F, GL_RED, GL_FLOAT);
	auto outputTexture = texturePool.GetTexture(outputTextureId);

	auto& avgPool2x2 = shaderPool.GetAvgPool2x2();


	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glUseProgram(avgPool2x2.GetShaderProgram());

	openGLCore.glBindImageTexture(0, inputTexture->GetID(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
	openGLCore.glBindImageTexture(1, outputTexture->GetID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	openGLCore.glDispatchCompute(outputTexture->GetWidth() / 16, outputTexture->GetHeight() / 16, 1);

	openGLCore.glMemoryBarrier(GL_ALL_BARRIER_BITS);

	openGLCore.glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
	openGLCore.glBindImageTexture(1, 0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);


	const auto textureDataSize = outputTexture->GetWidth() * outputTexture->GetHeight() * 1;

	std::vector<uint8_t> textureData(textureDataSize);

	openGLCore.glGetTextureImage(outputTexture->GetID(), 0, GL_RED, GL_UNSIGNED_BYTE, textureDataSize, &textureData[0]);

	AITextureBMP::SaveSingleChannel(outputImagePath, textureData, outputTexture->GetWidth(), outputTexture->GetHeight());
}
