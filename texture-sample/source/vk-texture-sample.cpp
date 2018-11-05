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

#include "vk-texture-sample.h"

#include <cassert>
#include <fstream>
#include <iterator>
#include <array>
#undef STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "texture-resources.h"

// #version 310 es
// 
// layout (location = 0) in vec4 iPosition;
// layout (location = 1) in vec4 iTexCoord;
// 
// layout (location = 0) out vec4 oTexCoord;
// 
// void main()
// {
//     gl_Position = iPosition;
//     oTexCoord = iTexCoord;
// }
constexpr char* kVertShaderPath = RESOURCE_DIR"/texture.vert.spv";

// #version 310 es
// 
// precision highp float;
// 
// layout (location = 0) in vec2 iTexCoord;
// 
// layout (location = 0) out vec4 oColor;
// 
// layout (set = 0, binding = 0) uniform sampler2D sTexture;
// 
// void main ()
// {
//     oColor = texture(sTexture, iTexCoord);
// }
constexpr char* kFragShaderPath = RESOURCE_DIR"/texture.frag.spv";

VkTextureSample::VkTextureSample (std::wstring const& title, uint32_t width, uint32_t height)
    :
    VkSample(title, width, height)
{
}

void VkTextureSample::onInit (HINSTANCE instance, HWND window, HDC deviceContext)
{
    VkSample::onInit(instance, window, deviceContext);

    {
        VkBufferCreateInfo createInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        createInfo.size = kVerticies.size() * sizeof(Vertex);
        createInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

        vkCreateBuffer(mDevice, &createInfo, nullptr, &mVertexBuffer);

        VkMemoryRequirements memoryRequirements;
        vkGetBufferMemoryRequirements(mDevice, mVertexBuffer, &memoryRequirements);

        constexpr VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
        auto memoryTypeIndex = getMemoryTypeIndex(memoryRequirements, memoryPropertyFlags);

        VkMemoryAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
        allocateInfo.allocationSize = memoryRequirements.size;
        allocateInfo.memoryTypeIndex = memoryTypeIndex;

        vkAllocateMemory(mDevice, &allocateInfo, nullptr, &mVertexMemory);

        vkBindBufferMemory(mDevice, mVertexBuffer, mVertexMemory, 0);

        void *data;
        vkMapMemory(mDevice, mVertexMemory, 0, VK_WHOLE_SIZE, 0, &data);
        memcpy(data, kVerticies.data(), kVerticies.size() * sizeof(Vertex));
        vkUnmapMemory(mDevice, mVertexMemory);
    }

    {
        int width, height, components;
        auto imgPixels = stbi_load(kTexturePath, &width, &height, &components, STBI_rgb_alpha);

        VkImageCreateInfo createInfo = { VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
        createInfo.imageType = VK_IMAGE_TYPE_2D;
        createInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        createInfo.extent.width = width;
        createInfo.extent.height = height;
        createInfo.extent.depth = 1;
        createInfo.mipLevels = 1;
        createInfo.arrayLayers = 1;
        createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        createInfo.tiling = VK_IMAGE_TILING_LINEAR;
        createInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
        createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        vkCreateImage(mDevice, &createInfo, nullptr, &mTextureImage);

        VkMemoryRequirements memoryRequirements;
        vkGetImageMemoryRequirements(mDevice, mTextureImage, &memoryRequirements);

        constexpr VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
        auto memoryTypeIndex = getMemoryTypeIndex(memoryRequirements, memoryPropertyFlags);

        VkMemoryAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
        allocateInfo.allocationSize = memoryRequirements.size;
        allocateInfo.memoryTypeIndex = memoryTypeIndex;

        vkAllocateMemory(mDevice, &allocateInfo, nullptr, &mTextureMemory);

        vkBindImageMemory(mDevice, mTextureImage, mTextureMemory, 0);

        void *data;
        vkMapMemory(mDevice, mTextureMemory, 0, VK_WHOLE_SIZE, 0, &data);
        memcpy(data, imgPixels, width * height * STBI_rgb_alpha);
        vkUnmapMemory(mDevice, mTextureMemory);

        stbi_image_free(imgPixels);
    }

    {
        VkImageViewCreateInfo createInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
        createInfo.image = mTextureImage;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_R;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_G;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_B;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_A;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;

        vkCreateImageView(mDevice, &createInfo, nullptr, &mTextureImageView);
    }

    {
        VkSamplerCreateInfo createInfo = { VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
        createInfo.magFilter = VK_FILTER_LINEAR;
        createInfo.minFilter = VK_FILTER_LINEAR;
        createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;

        vkCreateSampler(mDevice, &createInfo, nullptr, &mTextureSampler);
    }

    {
        VkDescriptorPoolSize poolSize = { };
        poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSize.descriptorCount = 1;

        VkDescriptorPoolCreateInfo createInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
        createInfo.maxSets = 1;
        createInfo.poolSizeCount = 1;
        createInfo.pPoolSizes = &poolSize;

        vkCreateDescriptorPool(mDevice, &createInfo, nullptr, &mDescriptorPool);        
    }

    {
        VkDescriptorSetLayoutBinding setLayoutBinding = { };
        setLayoutBinding.binding = 0;
        setLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        setLayoutBinding.descriptorCount = 1;
        setLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

        VkDescriptorSetLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
        createInfo.bindingCount = 1;
        createInfo.pBindings = &setLayoutBinding;

        vkCreateDescriptorSetLayout(mDevice, &createInfo, nullptr, &mDescriptorSetLayout);
    }

    {
        VkAttachmentDescription attachmentDescription = {};
        attachmentDescription.format = mSurfaceFormat.format;
        attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
        attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachmentDescription.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference attachmentReference = {};
        attachmentReference.attachment = 0;
        attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpassDescription = {};
        subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpassDescription.colorAttachmentCount = 1;
        subpassDescription.pColorAttachments = &attachmentReference;

        VkSubpassDependency subpassDependency = {};
        subpassDependency.srcSubpass = 0;
        subpassDependency.dstSubpass = VK_SUBPASS_EXTERNAL;
        subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        subpassDependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        subpassDependency.dstAccessMask = 0;

        VkRenderPassCreateInfo createInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
        createInfo.attachmentCount = 1;
        createInfo.pAttachments = &attachmentDescription;
        createInfo.subpassCount = 1;
        createInfo.pSubpasses = &subpassDescription;
        createInfo.dependencyCount = 1;
        createInfo.pDependencies = &subpassDependency;

        vkCreateRenderPass(mDevice, &createInfo, nullptr, &mRenderPass);
    }

    {
        mFramebuffers.resize(mSwapchainImageCount);

        VkFramebufferCreateInfo createInfo = { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
        createInfo.renderPass = mRenderPass;
        createInfo.attachmentCount = 1;
        createInfo.width = mWidth;
        createInfo.height = mHeight;
        createInfo.layers = 1;

        for (auto i = 0; i != mSwapchainImageCount; ++i)
        {
            createInfo.pAttachments = &mSwapchainImageViews[i];

            vkCreateFramebuffer(mDevice, &createInfo, nullptr, &mFramebuffers[i]);
        }
    }

    {
        createShaderMoudle(kVertShaderPath, mVertShaderModule);
        createShaderMoudle(kFragShaderPath, mFragShaderModule);
    }

    {
        VkPipelineLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
        createInfo.setLayoutCount = 1;
        createInfo.pSetLayouts = &mDescriptorSetLayout;

        vkCreatePipelineLayout(mDevice, &createInfo, nullptr, &mPipelineLayout);
    }

    {
        VkGraphicsPipelineCreateInfo createInfo = { VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };

        std::array<VkPipelineShaderStageCreateInfo, 2> stageCreateInfos;

        stageCreateInfos[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stageCreateInfos[0].pNext = nullptr;
        stageCreateInfos[0].flags = 0;
        stageCreateInfos[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
        stageCreateInfos[0].module = mVertShaderModule;
        stageCreateInfos[0].pName = "main";
        stageCreateInfos[0].pSpecializationInfo = nullptr;

        stageCreateInfos[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stageCreateInfos[1].pNext = nullptr;
        stageCreateInfos[1].flags = 0;
        stageCreateInfos[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        stageCreateInfos[1].module = mFragShaderModule;
        stageCreateInfos[1].pName = "main";
        stageCreateInfos[1].pSpecializationInfo = nullptr;

        createInfo.stageCount = static_cast<uint32_t>(stageCreateInfos.size());
        createInfo.pStages = stageCreateInfos.data();

        VkVertexInputBindingDescription vertexInputBindingDescription;
        vertexInputBindingDescription.binding = 0;
        vertexInputBindingDescription.stride = sizeof(Vertex);
        vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        std::array<VkVertexInputAttributeDescription, 2> vertexInputAttributeDescriptions;

        vertexInputAttributeDescriptions[0].location = 0;
        vertexInputAttributeDescriptions[0].binding = 0;
        vertexInputAttributeDescriptions[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
        vertexInputAttributeDescriptions[0].offset = 0;

        vertexInputAttributeDescriptions[1].location = 1;
        vertexInputAttributeDescriptions[1].binding = 0;
        vertexInputAttributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
        vertexInputAttributeDescriptions[1].offset = offsetof(Vertex, texCoord);


        VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
        vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
        vertexInputStateCreateInfo.pVertexBindingDescriptions = &vertexInputBindingDescription;
        vertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributeDescriptions.size());
        vertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();

        createInfo.pVertexInputState = &vertexInputStateCreateInfo;

        VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
        inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;

        createInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;

        VkPipelineViewportStateCreateInfo viewportStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
        viewportStateCreateInfo.viewportCount = 1;
        viewportStateCreateInfo.scissorCount = 1;

        createInfo.pViewportState = &viewportStateCreateInfo;

        VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
        rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_NONE;
        rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizationStateCreateInfo.lineWidth = 1.0f;

        createInfo.pRasterizationState = &rasterizationStateCreateInfo;

        VkPipelineMultisampleStateCreateInfo multisampleCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
        multisampleCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        createInfo.pMultisampleState = &multisampleCreateInfo;

        VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };

        createInfo.pDepthStencilState = &depthStencilStateCreateInfo;

        VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {};
        colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

        VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
        colorBlendStateCreateInfo.attachmentCount = 1;
        colorBlendStateCreateInfo.pAttachments = &colorBlendAttachmentState;
        colorBlendStateCreateInfo.blendConstants[0] = 1.0f;
        colorBlendStateCreateInfo.blendConstants[1] = 1.0f;
        colorBlendStateCreateInfo.blendConstants[2] = 1.0f;
        colorBlendStateCreateInfo.blendConstants[3] = 1.0f;

        createInfo.pColorBlendState = &colorBlendStateCreateInfo;

        constexpr std::array<VkDynamicState, 2> dynamicStates = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
        };

        VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
        dynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
        dynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

        createInfo.pDynamicState = &dynamicStateCreateInfo;

        createInfo.layout = mPipelineLayout;
        createInfo.renderPass = mRenderPass;
        createInfo.subpass = 0;

        vkCreateGraphicsPipelines(mDevice, VK_NULL_HANDLE, 1, &createInfo, nullptr, &mPipeline);
    }

    {
        VkDescriptorSetAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
        allocateInfo.descriptorPool = mDescriptorPool;
        allocateInfo.descriptorSetCount = 1;
        allocateInfo.pSetLayouts = &mDescriptorSetLayout;

        vkAllocateDescriptorSets(mDevice, &allocateInfo, &mDescriptorSet);
    }

    {
        VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
        allocateInfo.commandPool = mCommandPool;
        allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocateInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(mDevice, &allocateInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        VkImageMemoryBarrier imageMemoryBarrier = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
        imageMemoryBarrier.srcAccessMask = 0;
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageMemoryBarrier.image = mTextureImage;
        imageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageMemoryBarrier.subresourceRange.baseMipLevel = 0;
        imageMemoryBarrier.subresourceRange.levelCount = 1;
        imageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
        imageMemoryBarrier.subresourceRange.layerCount = 1;

        vkCmdPipelineBarrier(
            commandBuffer,
            VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0,
            0,
            nullptr,
            0,
            nullptr,
            1,
            &imageMemoryBarrier
        );

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(mQueue, 1, &submitInfo, VK_NULL_HANDLE);

        vkQueueWaitIdle(mQueue);

        vkFreeCommandBuffers(mDevice, mCommandPool, 1, &commandBuffer);
    }

    {
        VkDescriptorImageInfo imageInfo = { };
        imageInfo.sampler = mTextureSampler;
        imageInfo.imageView = mTextureImageView;
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        VkWriteDescriptorSet descriptorWrite = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };
        descriptorWrite.dstSet = mDescriptorSet;
        descriptorWrite.dstBinding = 0;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrite.pImageInfo = &imageInfo;

        vkUpdateDescriptorSets(mDevice, 1, &descriptorWrite, 0, nullptr);
    }

    {
        for (auto i = 0; i != mSwapchainImageCount; ++i)
        {
            VkCommandBufferBeginInfo commandBufferBeginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };

            vkBeginCommandBuffer(mCommandBuffers[i], &commandBufferBeginInfo);

            VkImageMemoryBarrier imageMemoryBarrier = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
            imageMemoryBarrier.srcAccessMask = 0;
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            imageMemoryBarrier.image = mSwapchainImages[i];
            imageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageMemoryBarrier.subresourceRange.baseMipLevel = 0;
            imageMemoryBarrier.subresourceRange.levelCount = 1;
            imageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
            imageMemoryBarrier.subresourceRange.layerCount = 1;

            vkCmdPipelineBarrier(
                mCommandBuffers[i],
                VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                0,
                0,
                nullptr,
                0,
                nullptr,
                1,
                &imageMemoryBarrier
            );


            VkClearValue clearValue = { kClearColor.r, kClearColor.g, kClearColor.b, kClearColor.a };

            VkRenderPassBeginInfo renderPassBeginInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
            renderPassBeginInfo.renderPass = mRenderPass;
            renderPassBeginInfo.framebuffer = mFramebuffers[i];
            renderPassBeginInfo.renderArea.extent.width = mWidth;
            renderPassBeginInfo.renderArea.extent.height = mHeight;
            renderPassBeginInfo.clearValueCount = 1;
            renderPassBeginInfo.pClearValues = &clearValue;

            vkCmdBeginRenderPass(mCommandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdBindPipeline(mCommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, mPipeline);

            VkViewport viewport = { 0, static_cast<float>(mHeight), static_cast<float>(mWidth), -static_cast<float>(mHeight) };
            vkCmdSetViewport(mCommandBuffers[i], 0, 1, &viewport);

            VkRect2D scissor = { { 0, 0 }, { mWidth, mHeight } };
            vkCmdSetScissor(mCommandBuffers[i], 0, 1, &scissor);

            constexpr VkDeviceSize kOffset = 0;
            vkCmdBindVertexBuffers(mCommandBuffers[i], 0, 1, &mVertexBuffer, &kOffset);

            vkCmdBindDescriptorSets(mCommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, mPipelineLayout, 0, 1, &mDescriptorSet, 0, nullptr);

            vkCmdDraw(mCommandBuffers[i], 4, 1, 0, 0);

            vkCmdEndRenderPass(mCommandBuffers[i]);
            vkEndCommandBuffer(mCommandBuffers[i]);
        }
    }
}

void VkTextureSample::onExit ()
{
    vkDeviceWaitIdle(mDevice);

    for (auto framebuffer : mFramebuffers)
    {
        vkDestroyFramebuffer(mDevice, framebuffer, nullptr);
    }

    vkDestroyPipelineLayout(mDevice, mPipelineLayout, nullptr);
    vkDestroyPipeline(mDevice, mPipeline, nullptr);
    vkDestroyShaderModule(mDevice, mFragShaderModule, nullptr);
    vkDestroyShaderModule(mDevice, mVertShaderModule, nullptr);
    vkDestroyRenderPass(mDevice, mRenderPass, nullptr);
    vkDestroyDescriptorSetLayout(mDevice, mDescriptorSetLayout, nullptr);
    vkDestroyDescriptorPool(mDevice, mDescriptorPool, nullptr);
    vkDestroySampler(mDevice, mTextureSampler, nullptr);
    vkDestroyImageView(mDevice, mTextureImageView, nullptr);
    vkFreeMemory(mDevice, mTextureMemory, nullptr);
    vkDestroyImage(mDevice, mTextureImage, nullptr);
    vkFreeMemory(mDevice, mVertexMemory, nullptr);
    vkDestroyBuffer(mDevice, mVertexBuffer, nullptr);

    VkSample::onExit();
}

void VkTextureSample::onUpdate ()
{
}

void VkTextureSample::onRender (HDC deviceContext)
{
    uint32_t frameIndex = mFrameNumber % mSwapchainImageCount;

    uint32_t imageIndex;
    vkAcquireNextImageKHR(mDevice, mSwapchain, UINT64_MAX, mSwapchainAcquireSemaphores[frameIndex], VK_NULL_HANDLE, &imageIndex);

    if (VK_NOT_READY == vkGetFenceStatus(mDevice, mRenderingDoneFences[frameIndex]))
    {
        vkWaitForFences(mDevice, 1, &mRenderingDoneFences[frameIndex], VK_FALSE, UINT64_MAX);
    }

    vkResetFences(mDevice, 1, &mRenderingDoneFences[frameIndex]);

    constexpr VkPipelineStageFlags waitDstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkSubmitInfo submitInfo = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &mSwapchainAcquireSemaphores[frameIndex];
    submitInfo.pWaitDstStageMask = &waitDstStageMask;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &mCommandBuffers[imageIndex];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &mRenderingDoneSemaphores[frameIndex];

    vkQueueSubmit(mQueue, 1, &submitInfo, mRenderingDoneFences[frameIndex]);

    ++mFrameNumber;

    VkPresentInfoKHR presentInfo = { VK_STRUCTURE_TYPE_PRESENT_INFO_KHR };
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = &mRenderingDoneSemaphores[frameIndex];
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &mSwapchain;
    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(mQueue, &presentInfo);
}