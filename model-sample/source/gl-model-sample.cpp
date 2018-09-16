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

#include "gl-model-sample.h"

#include <stb/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <common/model.h>

#include "model-resources.h"

constexpr char *kVertShader = {
    "#version 310 es                                   \n"
    "                                                  \n"
    "layout (location = 0) in vec3 iPosition;          \n"
    "layout (location = 1) in vec3 iNormal;            \n"
    "layout (location = 2) in vec2 iTexCoord;          \n"
    "                                                  \n"
    "layout (location = 0) out vec2 oTexCoord;         \n"
    "                                                  \n"
    "uniform mat4 uMvp;                                \n"    
    "                                                  \n"
    "void main()                                       \n"
    "{                                                 \n"
    "    gl_Position = uMvp * vec4(iPosition, 1.0);    \n"
    "    oTexCoord = iTexCoord;                        \n"
    "}                                                 \n"
};

constexpr char *kFragShader = {
    "#version 310 es                                   \n"
    "                                                  \n"
    "precision highp float;                            \n"
    "                                                  \n"
    "layout (location = 0) in vec2 iTexCoord;          \n"
    "                                                  \n"
    "layout (location = 0) out vec4 oColor;            \n"
    "                                                  \n"
    "uniform sampler2D sDiffuse;                       \n"
    "                                                  \n"
    "void main ()                                      \n"
    "{                                                 \n"
    "    oColor = texture(sDiffuse, iTexCoord);        \n"
    "}                                                 \n"
};

GlModelSample::GlModelSample (std::wstring const& title, uint32_t width, uint32_t height)
    :
    GlSample(title, width, height),
    mModel(kModelPath)
{
}

GlModelSample::~GlModelSample ()
{
}

void GlModelSample::onInit (HINSTANCE instance, HWND window, HDC deviceContext)
{
    GlSample::onInit(instance, window, deviceContext);

    const auto kMeshCount = mModel.getMeshes().size();

    mVertexBuffers.resize(kMeshCount);
    glGenBuffers(static_cast<GLsizei>(kMeshCount), mVertexBuffers.data());

    for (auto i = 0; i != kMeshCount; ++i)
    {
        auto &vertices = mModel.getMeshes()[i].vertices;

        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffers[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    mIndexBuffers.resize(kMeshCount);
    glGenBuffers(static_cast<GLsizei>(kMeshCount), mIndexBuffers.data());

    for (auto i = 0; i != kMeshCount; ++i)
    {
        auto &indices = mModel.getMeshes()[i].indicies;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    mVertexArrayObjects.resize(kMeshCount);
    glGenVertexArrays(static_cast<GLsizei>(kMeshCount), mVertexArrayObjects.data());

    for (auto i = 0; i != kMeshCount; ++i)
    {
        glBindVertexArray(mVertexArrayObjects[i]);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffers[i]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoords)));
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[i]);
        glBindVertexArray(mVertexArrayObjects[0]);
    }

    mDiffuseTexs.resize(kMeshCount);
    glGenTextures(static_cast<GLsizei>(kMeshCount), mDiffuseTexs.data());

    for (auto i = 0; i != kMeshCount; ++i)
    {
        std::string diffusePath = RESOURCE_DIR"/" + mModel.getMeshes()[i].diffuse;

        int width, height, components;
        auto imgPixels = stbi_load(diffusePath.c_str(), &width, &height, &components, STBI_rgb_alpha);

        glBindTexture(GL_TEXTURE_2D, mDiffuseTexs[i]);
        glActiveTexture(GL_TEXTURE0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgPixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(imgPixels);
    }

    mVertShader = createShader(GL_VERTEX_SHADER, kVertShader);
    mFragShader = createShader(GL_FRAGMENT_SHADER, kFragShader);
    mProgram    = createProgram(mVertShader, mFragShader);

    glEnable(GL_DEPTH_TEST);
}

void GlModelSample::onExit ()
{
    glDeleteProgram(mProgram);
    glDeleteShader(mFragShader);
    glDeleteShader(mVertShader);

    GlSample::onExit();
}

void GlModelSample::onUpdate ()
{
    glViewport(0, 0, mWidth, mHeight);
    glClearColor(kClearColor.r, kClearColor.g, kClearColor.b, kClearColor.a);
    glClearDepthf(1.0f);
    glCullFace(GL_BACK);

    const auto ratio = static_cast<float>(mWidth) / static_cast<float>(mHeight);
    glm::mat4 projMatrix = glm::perspective(mCamera.getFov(), ratio, 1.0f, 100.0f);
    glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -3.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

    mMvpMatrix = projMatrix * mCamera.getViewMatrix() * modelMatrix;
}

void GlModelSample::onRender (HDC deviceContext)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(mProgram);

    for (auto i = 0; i != mVertexArrayObjects.size(); ++i)
    {
        auto mvpLoc = glGetUniformLocation(mProgram, "uMvp");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mMvpMatrix));

        auto difLoc = glGetUniformLocation(mProgram, "sDiffuse");
        glUniform1i(difLoc, 0);

        glBindTexture(GL_TEXTURE_2D, mDiffuseTexs[i]);
        glActiveTexture(GL_TEXTURE0);

        glBindVertexArray(mVertexArrayObjects[i]);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mModel.getMeshes()[i].indicies.size()), GL_UNSIGNED_SHORT, NULL);
    }

    wglSwapLayerBuffers(deviceContext, WGL_SWAP_MAIN_PLANE);
}