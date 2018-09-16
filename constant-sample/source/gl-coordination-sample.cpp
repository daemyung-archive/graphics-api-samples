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

#include "gl-coordination-sample.h"

#include <stb/stb_image.h>
#include <glm/gtc/type_ptr.hpp>

#include "coordination-resources.h"

constexpr char *kVertShader = {
    "#version 310 es                             \n"
    "                                            \n"
    "layout (location = 0) in vec4 iPosition;    \n"
    "layout (location = 1) in vec4 iTexCoord;    \n"
    "                                            \n"
    "layout (location = 0) out vec4 oTexCoord;   \n"
    "                                            \n"
    "uniform mat4 uMvp;                          \n"
    "                                            \n"
    "void main()                                 \n"
    "{                                           \n"
    "    gl_Position = uMvp * iPosition;         \n"
    "    oTexCoord = iTexCoord;                  \n"
    "}                                           \n"
};

constexpr char *kFragShader = {
    "#version 310 es                            \n"
    "                                           \n"
    "precision highp float;                     \n"
    "                                           \n"
    "layout (location = 0) in vec2 iTexCoord;   \n"
    "                                           \n"
    "layout (location = 0) out vec4 oColor;     \n"
    "                                           \n"
    "uniform sampler2D sTexture;                \n"
    "                                           \n"
    "void main ()                               \n"
    "{                                          \n"
    "    oColor = texture(sTexture, iTexCoord); \n"
    "}                                          \n"
};

GlCoordinationSample::GlCoordinationSample (std::wstring const& title, uint32_t width, uint32_t height)
    :
    GlSample(title, width, height),
    mRandomGenerator()
{
}

GlCoordinationSample::~GlCoordinationSample ()
{
}

void GlCoordinationSample::onInit (HINSTANCE instance, HWND window, HDC deviceContext)
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
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(glm::vec4)));
    glEnableVertexAttribArray(1);

    int width, height, components;
    auto imgPixels = stbi_load(RESOURCE_DIR"/box.jpg", &width, &height, &components, STBI_rgb_alpha);

    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glActiveTexture(GL_TEXTURE0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgPixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(imgPixels);
    
    mVertShader = createShader(GL_VERTEX_SHADER, kVertShader);
    mFragShader = createShader(GL_FRAGMENT_SHADER, kFragShader);
    mProgram    = createProgram(mVertShader, mFragShader);

    glEnable(GL_DEPTH_TEST);
}

void GlCoordinationSample::onExit ()
{
    glDeleteProgram(mProgram);
    glDeleteShader(mFragShader);
    glDeleteShader(mVertShader);

    GlSample::onExit();
}

void GlCoordinationSample::onUpdate ()
{
    glViewport(0, 0, mWidth, mHeight);
    glClearColor(kClearColor.r, kClearColor.g, kClearColor.b, kClearColor.a);
    glClearDepthf(1.0f);

    const auto ratio = static_cast<float>(mWidth) / static_cast<float>(mHeight);
    mProjMatix  = glm::perspective(glm::radians(45.0f), ratio, 1.0f, 100.0f);
    mViewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void GlCoordinationSample::onRender (HDC deviceContext)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(mVao);

    glBindTexture(GL_TEXTURE_2D, mTexture);
    glActiveTexture(GL_TEXTURE0);

    glUseProgram(mProgram);

    auto texLoc = glGetUniformLocation(mProgram, "sTexture");
    glUniform1i(texLoc, 0);

    auto mvpLoc = glGetUniformLocation(mProgram, "uMvp");

    glm::mat4 modelMatrix;
    for (auto &pos : kPositions)
    {
        modelMatrix = glm::translate(glm::mat4(1.0f), pos);

        auto mvpMatrix = mProjMatix * mViewMatrix * modelMatrix;
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);

    wglSwapLayerBuffers(deviceContext, WGL_SWAP_MAIN_PLANE);
}