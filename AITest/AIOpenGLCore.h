#pragma once

#include "AIOpenGLIncludes.h"

class AIOpenGLCore
{
public:
	static AIOpenGLCore& GetInstance();

	void Compute();

	void Disable();

	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB{};
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB{};
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT{};

	PFNGLATTACHSHADERPROC glAttachShader{};
	PFNGLBINDBUFFERPROC glBindBuffer{};
	PFNGLBINDVERTEXARRAYPROC glBindVertexArray{};
	PFNGLBUFFERDATAPROC glBufferData{};
	PFNGLCOMPILESHADERPROC glCompileShader{};
	PFNGLCREATEPROGRAMPROC glCreateProgram{};
	PFNGLCREATESHADERPROC glCreateShader{};
	PFNGLDELETEBUFFERSPROC glDeleteBuffers{};
	PFNGLDELETEPROGRAMPROC glDeleteProgram{};
	PFNGLDELETESHADERPROC glDeleteShader{};
	PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays{};
	PFNGLDETACHSHADERPROC glDetachShader{};
	PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray{};
	PFNGLGENBUFFERSPROC glGenBuffers{};
	PFNGLGENVERTEXARRAYSPROC glGenVertexArrays{};
	PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation{};
	PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog{};
	PFNGLGETPROGRAMIVPROC glGetProgramiv{};
	PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog{};
	PFNGLGETSHADERIVPROC glGetShaderiv{};
	PFNGLLINKPROGRAMPROC glLinkProgram{};
	PFNGLSHADERSOURCEPROC glShaderSource{};
	PFNGLUSEPROGRAMPROC glUseProgram{};
	PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer{};
	PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation{};
	PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation{};
	PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv{};
	PFNGLACTIVETEXTUREPROC glActiveTexture{};
	PFNGLUNIFORM1IPROC glUniform1i{};
	PFNGLGENERATEMIPMAPPROC glGenerateMipmap{};
	PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray{};
	PFNGLUNIFORM3FVPROC glUniform3fv{};
	PFNGLUNIFORM4FVPROC glUniform4fv{};
	PFNGLGENFRAMEBUFFERSPROC glGenFrameBuffers{};
	PFNGLBINDFRAMEBUFFERPROC glBindFrameBuffer{};
	PFNGLGENTEXTURESPROC glGenTextures{};
	PFNGLBINDTEXTUREPROC glBindTexture{};
	PFNGLTEXIMAGE2DPROC glTexImage2D{};
	PFNGLTEXPARAMETERIPROC glTexParameteri{};
	PFNGLBINDBUFFERBASEPROC glBindBufferBase{};
	PFNGLBINDBUFFERRANGEPROC glBindBufferRange{};
	PFNGLDELETETEXTURESPROC glDeleteTextures{};
	PFNGLDELETEBUFFERSPROC glDeleteBuffers{};
	PFNGLDISPATCHCOMPUTEPROC glDispatchCompute{};
	PFNGLMEMORYBARRIERPROC glMemoryBarrier{};

private:
	AIOpenGLCore();
	~AIOpenGLCore();

	AIOpenGLCore(const AIOpenGLCore&) = delete;
	AIOpenGLCore(AIOpenGLCore&&) = delete;
	AIOpenGLCore& operator=(const AIOpenGLCore&) = delete;
	AIOpenGLCore& operator=(AIOpenGLCore&&) = delete;

	bool LoadExtensions();

	HGLRC renderContext;
	HDC deviceContext;
	HWND windowHandler;

	const int dummyWindowSizeX = 1;
	const int dummyWindowSizeY = 1;
};