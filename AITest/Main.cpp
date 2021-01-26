#include "Main.h"

int main()
{
	try
	{
		AIFunction func([](float argument)
			{
				return std::acos(argument);
			});

		std::cout << "f(x) = acos(x)" << std::endl;
		std::cout << "x0 = 0" << std::endl;
		std::cout << "f(x0) = " << func(0.0f) << std::endl;
		std::cout << "f'(x0) = " << func.Derivative(0.0f) << std::endl;
		std::cout << "f''(x0) = " << func.SecondDerivative(0.0f) << std::endl << std::endl;

		std::cout << "F(x0) = " << func.Primitive(0.0f) << std::endl;
		std::cout << "F(-1, 1) = " << func.DefiniteIntegral(-1.0f, 1.0f) << std::endl;
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR | MB_DEFAULT_DESKTOP_ONLY);
	}

	return 0;
}