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

#ifndef VK_TEXTURE_SAMPLE_H
#define VK_TEXTURE_SAMPLE_H

#include <common/vk-sample.h>

class VkTextureSample : public VkSample
{
public:
    VkTextureSample (std::wstring const& title, uint32_t width, uint32_t height);

    void onInit (HINSTANCE instance, HWND window, HDC deviceContext) override;

    void onExit () override;

    void onUpdate () override;

    void onRender (HDC deviceContext) override;

private:
    VkBuffer         mVertexBuffer;
    VkDeviceMemory   mVertexMemory;
    VkImage          mTextureImage;
    VkDeviceMemory   mTextureMemory;
    VkImageView      mTextureImageView;
    VkSampler        mTextureSampler;
    VkDescriptorPool mDescriptorPool;
    VkDescriptorSetLayout mDescriptorSetLayout;
    VkRenderPass     mRenderPass;
    VkShaderModule   mVertShaderModule;
    VkShaderModule   mFragShaderModule;
    VkPipelineLayout mPipelineLayout;
    VkPipeline       mPipeline;
    VkDescriptorSet  mDescriptorSet;
    std::vector<VkFramebuffer> mFramebuffers;
};

#endif