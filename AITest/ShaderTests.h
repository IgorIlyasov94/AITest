#pragma once

#include "AIOpenGLTexturePool.h"
#include "AIOpenGLBufferPool.h"
#include "AIOpenGLComputeShaderCollection.h"

void TESTTextureAndBufferConversions(std::string inputImagePath, std::string outputImagePath);

void TESTPrimaryConvolution3x3(std::string inputImagePath, std::string outputImagePath);
void TESTConvolution3x3(std::string inputImagePath, std::string outputImagePath);
void TESTConvolution4x4(std::string inputImagePath, std::string outputImagePath);

void TESTMaxPool2x2(std::string inputImagePath, std::string outputImagePath);
void TESTMinPool2x2(std::string inputImagePath, std::string outputImagePath);
void TESTAvgPool2x2(std::string inputImagePath, std::string outputImagePath);