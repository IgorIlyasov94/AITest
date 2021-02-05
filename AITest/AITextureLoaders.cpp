#include "AITextureLoaders.h"

void LoadTextureBMP(const std::string& filePath, std::vector<uint8_t>& dataBuffer, int& width, int& height)
{
	std::ifstream textureFile{ filePath, std::ios::binary | std::ios::in };

	if (!textureFile.is_open())
		throw std::exception("LoadTextureBMP: File loading has failed!");

	const auto BMP_HEADER_SIZE = 54u;

	std::vector<uint8_t> bmpRawData{ std::istream_iterator<uint8_t>(textureFile), std::istream_iterator<uint8_t>() };

	if (bmpRawData.size() < BMP_HEADER_SIZE)
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	if (bmpRawData[0] != 'B' || bmpRawData[1] != 'M')
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	const auto BMP_HEADER_DATA_POSITION_ADDRESS = 0x0Au;
	
	auto textureDataPosition = *reinterpret_cast<int*>(&bmpRawData[BMP_HEADER_DATA_POSITION_ADDRESS]);

	if (bmpRawData.size() < static_cast<uint32_t>(textureDataPosition))
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	const auto BMP_HEADER_WIDTH_ADDRESS = 0x12u;
	const auto BMP_HEADER_HEIGHT_ADDRESS = 0x16u;

	width = *reinterpret_cast<int*>(&bmpRawData[BMP_HEADER_WIDTH_ADDRESS]);
	height = *reinterpret_cast<int*>(&bmpRawData[BMP_HEADER_HEIGHT_ADDRESS]);

	auto iteratorBegin = bmpRawData.begin();
	std::advance(iteratorBegin, textureDataPosition);
	auto iteratorEnd = bmpRawData.end();

	std::copy(iteratorBegin, iteratorEnd, dataBuffer.begin());
}
