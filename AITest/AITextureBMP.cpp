#include "AITextureBMP.h"

void AITextureBMP::Load(const std::string& filePath, std::vector<uint8_t>& dataBuffer, int& width, int& height)
{
	std::ifstream textureFile{ filePath, std::ios::binary | std::ios::in };

	if (!textureFile.is_open())
		throw std::exception("LoadTextureBMP: File loading has failed!");

	textureFile >> std::noskipws;

	std::vector<uint8_t> bmpRawData{ std::istream_iterator<uint8_t>(textureFile), std::istream_iterator<uint8_t>() };

	if (bmpRawData.size() < BMP_HEADER_SIZE)
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	if (bmpRawData[0] != 'B' || bmpRawData[1] != 'M')
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	const auto BMP_HEADER_DATA_OFFSET_ADDRESS = 0x0Au;

	auto textureDataOffset = *reinterpret_cast<int*>(&bmpRawData[BMP_HEADER_DATA_OFFSET_ADDRESS]);

	if (bmpRawData.size() < static_cast<uint32_t>(textureDataOffset))
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	const auto BMP_HEADER_WIDTH_ADDRESS = 0x12u;
	const auto BMP_HEADER_HEIGHT_ADDRESS = 0x16u;

	width = *reinterpret_cast<int*>(&bmpRawData[BMP_HEADER_WIDTH_ADDRESS]);
	height = *reinterpret_cast<int*>(&bmpRawData[BMP_HEADER_HEIGHT_ADDRESS]);

	auto iteratorBegin = bmpRawData.begin();
	std::advance(iteratorBegin, textureDataOffset);
	auto iteratorEnd = bmpRawData.end();

	std::copy(iteratorBegin, iteratorEnd, std::back_inserter(dataBuffer));
}

void AITextureBMP::Save(const std::string& filePath, std::vector<uint8_t>& dataBuffer, int width, int height)
{
	std::ofstream textureFile{ filePath, std::ios::binary | std::ios::out };

	BMPHeader bmpHeader{};
	bmpHeader.bmpSignature[0] = 'B';
	bmpHeader.bmpSignature[1] = 'M';
	bmpHeader.bmpFileSize = BMP_HEADER_SIZE + dataBuffer.size();
	bmpHeader.dataOffset = BMP_HEADER_SIZE;

	textureFile.write(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));

	BMPInfoHeader bmpInfoHeader{};
	bmpInfoHeader.bmpInfoHeaderSize = sizeof(BMPInfoHeader);
	bmpInfoHeader.width = width;
	bmpInfoHeader.height = height;
	bmpInfoHeader.colorPlanesNumber = 1;
	bmpInfoHeader.colorDepth = 24;
	bmpInfoHeader.compressionMethod = 0;
	bmpInfoHeader.bmpRawDataSize = 0;
	bmpInfoHeader.horizontalResolution = 3750;
	bmpInfoHeader.verticalResolution = 3750;
	bmpInfoHeader.colorTableEntries = 0;
	bmpInfoHeader.importantColors = 0;

	textureFile.write(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(BMPInfoHeader));

	textureFile.write(reinterpret_cast<char*>(&dataBuffer[0]), dataBuffer.size());
}

AITextureBMP::AITextureBMP()
{

}

AITextureBMP::~AITextureBMP()
{

}
