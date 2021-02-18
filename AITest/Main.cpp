#include "Main.h"

#include "ShaderTests.h"

int main()
{
	try
	{
		//TESTTextureAndBufferConversions("TestImage.bmp", "TestImageOutput.bmp");
		//TESTPrimaryConvolution3x3("TestImage.bmp", "TestImageOutput.bmp");

		//TESTAvgPool2x2("TestImage.bmp", "TestImageOutput.bmp");
		//TESTAvgPool2x2("TestImageOutput.bmp", "TestImageOutput2.bmp");
		//TESTAvgPool2x2("TestImageOutput2.bmp", "TestImageOutput3.bmp");

		TESTMaxPool2x2("TestImage.bmp", "TestImageOutput.bmp");
		TESTConvolution3x3("TestImageOutput.bmp", "TestImageOutput2.bmp");
		TESTMaxPool2x2("TestImageOutput2.bmp", "TestImageOutput3.bmp");
		TESTConvolution3x3("TestImageOutput3.bmp", "TestImageOutput4.bmp");
		TESTMaxPool2x2("TestImageOutput4.bmp", "TestImageOutput5.bmp");
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR | MB_DEFAULT_DESKTOP_ONLY);
	}

	return 0;
}
