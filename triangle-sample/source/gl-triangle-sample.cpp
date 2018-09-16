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

#include "gl-triangle-sample.h"

#include "triangle-resources.h"

constexpr char *kVertShader = {
    "#version 310 es                             \n"
    "                                            \n"
    "layout (location = 0) in vec4 iPosition;    \n"
    "layout (location = 1) in vec4 iColor;       \n"
    "                                            \n"
    "layout (location = 0) out vec4 oColor;      \n"
    "                                            \n"
    "void main()                                 \n"
    "{                                           \n"
    "    gl_Position = iPosition;                \n"
    "    oColor = iColor;                        \n"
    "}                                           \n"
};

constexpr char *kFragShader = {
    "#version 310 es                           \n"
    "                                          \n"
    "precision highp float;                    \n"
    "                                          \n"
    "layout (location = 0) in vec4 iColor;     \n"
    "                                          \n"
    "layout (location = 0) out vec4 oColor;    \n"
    "                                          \n"
    "void main ()                              \n"
    "{                                         \n"
    "    oColor = iColor;                      \n"
    "}                                         \n"
};

GlTriangleSample::GlTriangleSample (std::wstring const& title, uint32_t width, uint32_t height)
    :
    GlSample(title, width, height)
{
}

GlTriangleSample::~GlTriangleSample ()
{
}

void GlTriangleSample::onInit (HINSTANCE instance, HWND window, HDC deviceContext)
{
    GlSample::onInit(instance, window, deviceContext);

    glGenBuffers(1, &mPosVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mPosVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * kVerticies.size(), kVerticies.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);
    glBindBuffer(GL_ARRAY_BUFFER, mPosVbo);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(glm::vec4)));
    glEnableVertexAttribArray(1);

    mVertShader = createShader(GL_VERTEX_SHADER, kVertShader);
    mFragShader = createShader(GL_FRAGMENT_SHADER, kFragShader);
    mProgram    = createProgram(mVertShader, mFragShader);
}

void GlTriangleSample::onExit ()
{
    glDeleteProgram(mProgram);
    glDeleteShader(mFragShader);
    glDeleteShader(mVertShader);

    GlSample::onExit();
}

void GlTriangleSample::onUpdate ()
{
    glViewport(0, 0, mWidth, mHeight);
    glClearColor(kClearColor.r, kClearColor.g, kClearColor.b, kClearColor.a);
}

void GlTriangleSample::onRender (HDC deviceContext)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(mVao);
    glUseProgram(mProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    wglSwapLayerBuffers(deviceContext, WGL_SWAP_MAIN_PLANE);
}