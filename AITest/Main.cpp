#include "Main.h"

#include "ShaderTests.h"

int main()
{
	try
	{
		//TESTTextureAndBufferConversions("TestImage.bmp", "TestImageOutput.bmp");

		TESTPrimaryConvolution3x3("TestImage.bmp", "TestImageOutput.bmp");
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR | MB_DEFAULT_DESKTOP_ONLY);
	}

	return 0;
}
