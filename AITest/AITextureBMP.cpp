#include "AITextureBMP.h"

void AITextureBMP::Load(const std::string& filePath, std::vector<uint8_t>& rgbaDataBuffer, int& width, int& height)
{
	std::ifstream textureFile{ filePath, std::ios::binary | std::ios::in };

	if (!textureFile.is_open())
		throw std::exception("LoadTextureBMP: File loading has failed!");

	textureFile >> std::noskipws;

	BMPHeader bmpHeader{};
	BMPInfoHeader bmpInfoHeader{};

	if (!textureFile.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader)))
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	if (bmpHeader.bmpSignature[0] != 'B' || bmpHeader.bmpSignature[1] != 'M')
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	if (!textureFile.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(BMPInfoHeader)))
		throw std::exception("LoadTextureBMP: Wrong file structure!");

	auto rgbDataBufferSize = bmpHeader.bmpFileSize - bmpInfoHeader.bmpInfoHeaderSize;

	std::vector<uint8_t> rgbDataBuffer{ std::istream_iterator<uint8_t>(textureFile), std::istream_iterator<uint8_t>() };

	ConvertRGBBufferToRGBA(rgbDataBuffer.begin(), rgbDataBuffer.end(), rgbaDataBuffer);

	width = bmpInfoHeader.width;
	height = bmpInfoHeader.height;
}

void AITextureBMP::Save(const std::string& filePath, std::vector<uint8_t>& rgbaDataBuffer, int width, int height)
{
	std::ofstream textureFile{ filePath, std::ios::binary | std::ios::out };

	auto rgbDataBufferSize = rgbaDataBuffer.size() * 3 / 4;

	BMPHeader bmpHeader{};
	bmpHeader.bmpSignature[0] = 'B';
	bmpHeader.bmpSignature[1] = 'M';
	bmpHeader.bmpFileSize = BMP_HEADER_SIZE + rgbDataBufferSize;
	bmpHeader.dataOffset = BMP_HEADER_SIZE;

	textureFile.write(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));

	BMPInfoHeader bmpInfoHeader{};
	bmpInfoHeader.bmpInfoHeaderSize = sizeof(BMPInfoHeader);
	bmpInfoHeader.width = width;
	bmpInfoHeader.height = height;
	bmpInfoHeader.colorPlanesNumber = 1;
	bmpInfoHeader.colorDepth = 24;
	bmpInfoHeader.horizontalResolution = 3750;
	bmpInfoHeader.verticalResolution = 3750;

	textureFile.write(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(BMPInfoHeader));

	std::vector<uint8_t> rgbDataBuffer;

	ConvertRGBABufferToRGB(rgbaDataBuffer.begin(), rgbaDataBuffer.end(), rgbDataBuffer);

	textureFile.write(reinterpret_cast<char*>(&rgbDataBuffer[0]), rgbDataBufferSize);
}

AITextureBMP::AITextureBMP()
{

}

AITextureBMP::~AITextureBMP()
{

}
