#include "AIOpenGLCore.h"

LRESULT CALLBACK DummyWindowProc(HWND windowHandler, UINT message, WPARAM wParam, LPARAM lParam);

AIOpenGLCore::AIOpenGLCore()
{
	HINSTANCE instance = GetModuleHandle(nullptr);

	WNDCLASSEX tempWindowClass{};

	auto windowClassName = L"DummyWindow";
	auto windowTitleName = L"DummyWindow";

	tempWindowClass.cbSize = sizeof(WNDCLASSEX);
	tempWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	tempWindowClass.lpfnWndProc = DummyWindowProc;
	tempWindowClass.hInstance = instance;
	tempWindowClass.hIcon = nullptr;
	tempWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	tempWindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	tempWindowClass.lpszClassName = windowClassName;
	tempWindowClass.hIconSm = nullptr;

	RegisterClassEx(&tempWindowClass);

	windowHandler = CreateWindowEx(WS_EX_APPWINDOW, windowClassName, windowTitleName, WS_POPUP,
		0, 0, 1024, 768, nullptr, nullptr, instance, nullptr);

	ThrowIfFailed(windowHandler != nullptr, "InitializeExtensions: Temporary Window creation failed!");

	ShowWindow(windowHandler, SW_HIDE);

	PIXELFORMATDESCRIPTOR pixelFormat;
	
	deviceContext = GetDC(windowHandler);
	ThrowIfFailed(deviceContext, "InitializeExtensions: Device Context creating failed!");

	ThrowIfFailed(SetPixelFormat(deviceContext, 1, &pixelFormat), "InitializeExtensions: Setting pixel format failed!");

	renderContext = wglCreateContext(deviceContext);
	ThrowIfFailed(renderContext, "InitializeExtensions: Render Context creating failed!");

	ThrowIfFailed(wglMakeCurrent(deviceContext, renderContext), "InitializeExtensions: Setting current RenderTarget failed!");

	ThrowIfFailed(LoadExtensions(), "InitializeExtensions: Extension list creating failed!");
}

AIOpenGLCore::~AIOpenGLCore()
{
	Disable();
}

void AIOpenGLCore::Compute()
{
	SwapBuffers(deviceContext);
}

void AIOpenGLCore::Disable()
{
	if (renderContext)
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(renderContext);

		renderContext = nullptr;
	}

	if (deviceContext)
	{
		ReleaseDC(windowHandler, deviceContext);

		deviceContext = nullptr;
	}
}

bool AIOpenGLCore::LoadExtensions()
{
	wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
	if (!wglChoosePixelFormatARB)
	{
		return false;
	}

	wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
	if (!wglCreateContextAttribsARB)
	{
		return false;
	}

	wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(wglGetProcAddress("wglSwapIntervalEXT"));
	if (!wglSwapIntervalEXT)
	{
		return false;
	}

	glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(wglGetProcAddress("glAttachShader"));
	if (!glAttachShader)
	{
		return false;
	}

	glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(wglGetProcAddress("glBindBuffer"));
	if (!glBindBuffer)
	{
		return false;
	}

	glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));
	if (!glBindVertexArray)
	{
		return false;
	}

	glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(wglGetProcAddress("glBufferData"));
	if (!glBufferData)
	{
		return false;
	}

	glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(wglGetProcAddress("glCompileShader"));
	if (!glCompileShader)
	{
		return false;
	}

	glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(wglGetProcAddress("glCreateProgram"));
	if (!glCreateProgram)
	{
		return false;
	}

	glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(wglGetProcAddress("glCreateShader"));
	if (!glCreateShader)
	{
		return false;
	}

	glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(wglGetProcAddress("glDeleteBuffers"));
	if (!glDeleteBuffers)
	{
		return false;
	}

	glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(wglGetProcAddress("glDeleteProgram"));
	if (!glDeleteProgram)
	{
		return false;
	}

	glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(wglGetProcAddress("glDeleteShader"));
	if (!glDeleteShader)
	{
		return false;
	}

	glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(wglGetProcAddress("glDeleteVertexArrays"));
	if (!glDeleteVertexArrays)
	{
		return false;
	}

	glDetachShader = reinterpret_cast<PFNGLDETACHSHADERPROC>(wglGetProcAddress("glDetachShader"));
	if (!glDetachShader)
	{
		return false;
	}

	glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(wglGetProcAddress("glEnableVertexAttribArray"));
	if (!glEnableVertexAttribArray)
	{
		return false;
	}

	glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(wglGetProcAddress("glGenBuffers"));
	if (!glGenBuffers)
	{
		return false;
	}

	glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(wglGetProcAddress("glGenVertexArrays"));
	if (!glGenVertexArrays)
	{
		return false;
	}

	glGetAttribLocation = reinterpret_cast<PFNGLGETATTRIBLOCATIONPROC>(wglGetProcAddress("glGetAttribLocation"));
	if (!glGetAttribLocation)
	{
		return false;
	}

	glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(wglGetProcAddress("glGetProgramInfoLog"));
	if (!glGetProgramInfoLog)
	{
		return false;
	}

	glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(wglGetProcAddress("glGetProgramiv"));
	if (!glGetProgramiv)
	{
		return false;
	}

	glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(wglGetProcAddress("glGetShaderInfoLog"));
	if (!glGetShaderInfoLog)
	{
		return false;
	}

	glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(wglGetProcAddress("glGetShaderiv"));
	if (!glGetShaderiv)
	{
		return false;
	}

	glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(wglGetProcAddress("glLinkProgram"));
	if (!glLinkProgram)
	{
		return false;
	}

	glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(wglGetProcAddress("glShaderSource"));
	if (!glShaderSource)
	{
		return false;
	}

	glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(wglGetProcAddress("glUseProgram"));
	if (!glUseProgram)
	{
		return false;
	}

	glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(wglGetProcAddress("glVertexAttribPointer"));
	if (!glVertexAttribPointer)
	{
		return false;
	}

	glBindAttribLocation = reinterpret_cast<PFNGLBINDATTRIBLOCATIONPROC>(wglGetProcAddress("glBindAttribLocation"));
	if (!glBindAttribLocation)
	{
		return false;
	}

	glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(wglGetProcAddress("glGetUniformLocation"));
	if (!glGetUniformLocation)
	{
		return false;
	}

	glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(wglGetProcAddress("glUniformMatrix4fv"));
	if (!glUniformMatrix4fv)
	{
		return false;
	}

	glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>(wglGetProcAddress("glActiveTexture"));
	if (!glActiveTexture)
	{
		return false;
	}

	glUniform1i = reinterpret_cast<PFNGLUNIFORM1IPROC>(wglGetProcAddress("glUniform1i"));
	if (!glUniform1i)
	{
		return false;
	}

	glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(wglGetProcAddress("glGenerateMipmap"));
	if (!glGenerateMipmap)
	{
		return false;
	}

	glDisableVertexAttribArray = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(wglGetProcAddress("glDisableVertexAttribArray"));
	if (!glDisableVertexAttribArray)
	{
		return false;
	}

	glUniform3fv = reinterpret_cast<PFNGLUNIFORM3FVPROC>(wglGetProcAddress("glUniform3fv"));
	if (!glUniform3fv)
	{
		return false;
	}

	glUniform4fv = reinterpret_cast<PFNGLUNIFORM4FVPROC>(wglGetProcAddress("glUniform4fv"));
	if (!glUniform4fv)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK DummyWindowProc(HWND windowHandler, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(windowHandler, message, wParam, lParam);
}