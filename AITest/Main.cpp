#include "Main.h"

int main()
{
	try
	{
		AIOpenGLCore& openGLCore = AIOpenGLCore::GetInstance();

		openGLCore.Compute();
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR | MB_DEFAULT_DESKTOP_ONLY);
	}

	return 0;
}