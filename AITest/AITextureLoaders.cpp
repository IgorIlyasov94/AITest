#include "AITextureLoaders.h"

void LoadTextureBMP(const std::string& filePath, std::vector<uint8_t>& dataBuffer, int& width, int& height)
{
	std::ifstream textureFile{ filePath, std::ios::binary | std::ios::in };

	if (!textureFile.is_open())
		throw std::exception("LoadTextureBMP: File loading has failed!");

	const auto bmpHeaderSize = 54u;

	std::vector<uint8_t> bmpRawData{ std::istream_iterator<uint8_t>(textureFile), std::istream_iterator<uint8_t>() };

	if (bmpRawData.size() < bmpHeaderSize)
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	if (bmpRawData[0] != 'B' || bmpRawData[1] != 'M')
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	const auto bmpHeaderDataPosition = 0x0Au;
	
	auto textureDataPosition = bmpRawData[bmpHeaderDataPosition];

	if (bmpRawData.size() < textureDataPosition)
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	const auto bmpHeaderWidth = 0x12u;
	const auto bmpHeaderHeight = 0x16u;

	width = bmpRawData[bmpHeaderWidth];
	height = bmpRawData[bmpHeaderHeight];

	auto iteratorBegin = bmpRawData.begin();
	std::advance(iteratorBegin, bmpHeaderDataPosition);
	auto iteratorEnd = bmpRawData.end();

	std::copy(iteratorBegin, iteratorEnd, dataBuffer);
}
