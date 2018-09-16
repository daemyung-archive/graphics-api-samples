// MIT License
//
// Copyright (c) 2018 DAEMYUNG, JANG
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "common/gl-sample.h"

#include <cassert>

#define GET_GL_API_PROC_ADDR_MACRO(function)                                  \
    function = reinterpret_cast<PFN_##function>(wglGetProcAddress(#function));

GlSample::GlSample (std::wstring const& title, uint32_t width, uint32_t height)
    :
    Sample(title, width, height),
    mRenderContext(NULL)
{
}

GlSample::~GlSample ()
{
}

void GlSample::onInit (HINSTANCE instance, HWND window, HDC deviceContext)
{
    PIXELFORMATDESCRIPTOR pixelFormatDesc = {
        sizeof (PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    int format = ChoosePixelFormat(deviceContext, &pixelFormatDesc);
    SetPixelFormat(deviceContext, format, &pixelFormatDesc);

    HGLRC renderContext = wglCreateContext(deviceContext);
    wglMakeCurrent(deviceContext, renderContext);

    auto wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(
        wglGetProcAddress("wglCreateContextAttribsARB")
    );

    if (nullptr != wglCreateContextAttribsARB)
    {
        wglMakeCurrent(deviceContext, NULL);

        int const attributeList[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_FLAGS_ARB, 0,
            0
        };

        mRenderContext = wglCreateContextAttribsARB(deviceContext, NULL, attributeList);
        wglMakeCurrent(deviceContext, mRenderContext);
    }
    else
    {
        mRenderContext = renderContext;
    }

    APPLY_MACRO_TO_GL_API(GET_GL_API_PROC_ADDR_MACRO)
}

void GlSample::onExit ()
{
    if (NULL != mRenderContext)
    {
        wglDeleteContext(mRenderContext);
    }
}

GLuint GlSample::createShader (GLenum type, const char *code)
{
    auto shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (0 == success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        OutputDebugStringA(infoLog);
        assert(false);
    }

    return shader;
}

GLuint GlSample::createProgram (GLuint vertShader, GLuint fragShader)
{
    auto program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (0 == success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        OutputDebugStringA(infoLog);
        assert(false);
    }

    return program;
}