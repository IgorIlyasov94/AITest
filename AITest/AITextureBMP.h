#pragma once

#include "Includes.h"
#include "AITextureHelper.h"

class AITextureBMP
{
public:
	static void Load(const std::string& filePath, std::vector<uint8_t>& rgbaDataBuffer, int& width, int& height);
	static void Save(const std::string& filePath, std::vector<uint8_t>& rgbaDataBuffer, int width, int height);
	static void SaveSingleChannel(const std::string& filePath, std::vector<uint8_t>& rDataBuffer, int width, int height);

private:
	AITextureBMP();
	~AITextureBMP();

	AITextureBMP(const AITextureBMP&) = delete;
	AITextureBMP(AITextureBMP&&) = delete;
	AITextureBMP& operator=(const AITextureBMP&) = delete;
	AITextureBMP& operator=(AITextureBMP&&) = delete;

#pragma pack(2)

	using BMPHeader = struct
	{
		char bmpSignature[2];
		uint32_t bmpFileSize;
		uint32_t reserved;
		uint32_t dataOffset;
	};

#pragma pack()

	using BMPInfoHeader = struct
	{
		uint32_t bmpInfoHeaderSize;
		int32_t width;
		int32_t height;
		uint16_t colorPlanesNumber;
		uint16_t colorDepth;
		uint32_t compressionMethod;
		uint32_t bmpRawDataSize;
		int32_t horizontalResolution;
		int32_t verticalResolution;
		uint32_t colorTableEntries;
		uint32_t importantColors;
	};

	static const uint32_t BMP_HEADER_SIZE = sizeof(BMPHeader) + sizeof(BMPInfoHeader);
};
