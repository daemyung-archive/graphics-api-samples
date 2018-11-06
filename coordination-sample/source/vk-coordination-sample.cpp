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

#include "vk-coordination-sample.h"

#include <cassert>
#include <fstream>
#include <iterator>
#include <array>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#undef STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "coordination-resources.h"

// #version 310 es
// 
// layout (location = 0) in vec4 iPosition;
// layout (location = 1) in vec4 iTexCoord;
// 
// layout (location = 0) out vec4 oTexCoord;
// 
// layout (set = 0, binding = 0) uniform Global
// {
//     mat4 uMvp;
// };
// 
// void main()
// {
//     gl_Position = uMvp * iPosition;
//     oTexCoord = iTexCoord;
// }
constexpr char* kVertShaderPath = RESOURCE_DIR"/coordination.vert.spv";

// #version 310 es
// 
// precision highp float;
// 
// layout (location = 0) in vec2 iTexCoord;
// 
// layout (location = 0) out vec4 oColor;
// 
// layout (set = 0, binding = 1) uniform sampler2D sTexture;
// 
// void main ()
// {
//     oColor = texture(sTexture, iTexCoord);
// }
constexpr char* kFragShaderPath = RESOURCE_DIR"/coordination.frag.spv";

VkCoordinationSample::VkCoordinationSample (std::wstring const& title, uint32_t width, uint32_t height)
    :
    VkSample(title, width, height)
{
}

void VkCoordinationSample::onInit (HINSTANCE instance, HWND window, HDC deviceContext)
{
    VkSample::onInit(instance, window, deviceContext);

    VkResult result = VK_SUCCESS;

    if (VK_SUCCESS == result)
    {
        VkImageCreateInfo createInfo = { VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
        createInfo.imageType = VK_IMAGE_TYPE_2D;
        createInfo.format = VK_FORMAT_D16_UNORM;
        createInfo.extent.width = mWidth;
        createInfo.extent.height = mHeight;
        createInfo.extent.depth = 1;
        createInfo.mipLevels = 1;
        createInfo.arrayLayers = 1;
        createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        createInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        result = vkCreateImage(mDevice, &createInfo, nullptr, &mDepthImage);
    }

    if (VK_SUCCESS == result)
    {
        VkMemoryRequirements memoryRequirements;
        vkGetImageMemoryRequirements(mDevice, mDepthImage, &memoryRequirements);

        constexpr VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        auto memoryTypeIndex = getMemoryTypeIndex(memoryRequirements, memoryPropertyFlags);

        VkMemoryAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
        allocateInfo.allocationSize = memoryRequirements.size;
        allocateInfo.memoryTypeIndex = memoryTypeIndex;

        result = vkAllocateMemory(mDevice, &allocateInfo, nullptr, &mDepthMemory);
    }

    if (VK_SUCCESS == result)
    {
        result = vkBindImageMemory(mDevice, mDepthImage, mDepthMemory, 0);
    }

    if (VK_SUCCESS == result)
    {
        VkImageViewCreateInfo createInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
        createInfo.image = mDepthImage;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = VK_FORMAT_D16_UNORM;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        result = vkCreateImageView(mDevice, &createInfo, nullptr, &mDepthImageView);
    }

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
        VkBufferCreateInfo createInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        createInfo.size = kPositions.size() * sizeof(glm::mat4);
        createInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;

        vkCreateBuffer(mDevice, &createInfo, nullptr, &mUniformBuffer);

        VkMemoryRequirements memoryRequirements;
        vkGetBufferMemoryRequirements(mDevice, mUniformBuffer, &memoryRequirements);

        constexpr VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
        auto memoryTypeIndex = getMemoryTypeIndex(memoryRequirements, memoryPropertyFlags);

        VkMemoryAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
        allocateInfo.allocationSize = memoryRequirements.size;
        allocateInfo.memoryTypeIndex = memoryTypeIndex;

        vkAllocateMemory(mDevice, &allocateInfo, nullptr, &mUniformMemory);

        vkBindBufferMemory(mDevice, mUniformBuffer, mUniformMemory, 0);
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
        VkDescriptorPoolSize poolSize[2];

        poolSize[0] = VkDescriptorPoolSize {};
        poolSize[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        poolSize[0].descriptorCount = 1;

        poolSize[1] = VkDescriptorPoolSize { };
        poolSize[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSize[1].descriptorCount = 1;

        VkDescriptorPoolCreateInfo createInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
        createInfo.maxSets = 2;
        createInfo.poolSizeCount = 2;
        createInfo.pPoolSizes = poolSize;

        vkCreateDescriptorPool(mDevice, &createInfo, nullptr, &mDescriptorPool);        
    }

    {
        VkDescriptorSetLayoutBinding setLayoutBinding = { };
        setLayoutBinding.binding = 0;
        setLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        setLayoutBinding.descriptorCount = 1;
        setLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
        createInfo.bindingCount = 1;
        createInfo.pBindings = &setLayoutBinding;

        vkCreateDescriptorSetLayout(mDevice, &createInfo, nullptr, &mUniformDescriptorSetLayout);
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

        vkCreateDescriptorSetLayout(mDevice, &createInfo, nullptr, &mSamplerDescriptorSetLayout);
    }

    {
        VkAttachmentDescription attachmentDescriptions[2] = {};

        attachmentDescriptions[0] = VkAttachmentDescription { };
        attachmentDescriptions[0].format = mSurfaceFormat.format;
        attachmentDescriptions[0].samples = VK_SAMPLE_COUNT_1_BIT;
        attachmentDescriptions[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachmentDescriptions[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachmentDescriptions[0].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        attachmentDescriptions[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        attachmentDescriptions[1] = VkAttachmentDescription { };
        attachmentDescriptions[1].format = VK_FORMAT_D16_UNORM;
        attachmentDescriptions[1].samples = VK_SAMPLE_COUNT_1_BIT;
        attachmentDescriptions[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachmentDescriptions[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachmentDescriptions[1].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        attachmentDescriptions[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference attachmentReferences[2] = {};

        attachmentReferences[0] = VkAttachmentReference { };
        attachmentReferences[0].attachment = 0;
        attachmentReferences[0].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        attachmentReferences[1] = VkAttachmentReference {};
        attachmentReferences[1].attachment = 1;
        attachmentReferences[1].layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpassDescription = {};
        subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpassDescription.colorAttachmentCount = 1;
        subpassDescription.pColorAttachments = &attachmentReferences[0];
        subpassDescription.pDepthStencilAttachment = &attachmentReferences[1];

        VkSubpassDependency subpassDependency = {};
        subpassDependency.srcSubpass = 0;
        subpassDependency.dstSubpass = VK_SUBPASS_EXTERNAL;
        subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        subpassDependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        subpassDependency.dstAccessMask = 0;

        VkRenderPassCreateInfo createInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
        createInfo.attachmentCount = 2;
        createInfo.pAttachments = attachmentDescriptions;
        createInfo.subpassCount = 1;
        createInfo.pSubpasses = &subpassDescription;
        createInfo.dependencyCount = 1;
        createInfo.pDependencies = &subpassDependency;

        vkCreateRenderPass(mDevice, &createInfo, nullptr, &mRenderPass);
    }

    {
        mFramebuffers.resize(mSwapchainImageCount);

        std::vector<VkImageView> attachments = { VK_NULL_HANDLE, mDepthImageView };

        VkFramebufferCreateInfo createInfo = { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
        createInfo.renderPass = mRenderPass;
        createInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        createInfo.pAttachments = attachments.data();
        createInfo.width = mWidth;
        createInfo.height = mHeight;
        createInfo.layers = 1;
        

        for (auto i = 0; i != mSwapchainImageCount; ++i)
        {
            attachments[0] = mSwapchainImageViews[i];

            vkCreateFramebuffer(mDevice, &createInfo, nullptr, &mFramebuffers[i]);
        }
    }

    {
        createShaderMoudle(kVertShaderPath, mVertShaderModule);
        createShaderMoudle(kFragShaderPath, mFragShaderModule);
    }

    {
        const std::vector<VkDescriptorSetLayout> layouts = { mUniformDescriptorSetLayout, mSamplerDescriptorSetLayout };

        VkPipelineLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
        createInfo.setLayoutCount = static_cast<uint32_t>(layouts.size());
        createInfo.pSetLayouts = layouts.data();

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
        inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

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
        depthStencilStateCreateInfo.depthTestEnable = VK_TRUE;
        depthStencilStateCreateInfo.depthWriteEnable = VK_TRUE;
        depthStencilStateCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS;

        createInfo.pDepthStencilState = &depthStencilStateCreateInfo;

        VkPipelineColorBlendAttachmentState colorBlendAttachmentState = { };
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
        allocateInfo.pSetLayouts = &mUniformDescriptorSetLayout;

        vkAllocateDescriptorSets(mDevice, &allocateInfo, &mUniformDescriptorSet);
    }

    {
        VkDescriptorSetAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
        allocateInfo.descriptorPool = mDescriptorPool;
        allocateInfo.descriptorSetCount = 1;
        allocateInfo.pSetLayouts = &mSamplerDescriptorSetLayout;

        vkAllocateDescriptorSets(mDevice, &allocateInfo, &mSamplerDescriptorSet);
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

        VkImageMemoryBarrier imageMemoryBarriers[2];

        imageMemoryBarriers[0] = VkImageMemoryBarrier { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
        imageMemoryBarriers[0].srcAccessMask = 0;
        imageMemoryBarriers[0].dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
        imageMemoryBarriers[0].oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageMemoryBarriers[0].newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        imageMemoryBarriers[0].image = mDepthImage;
        imageMemoryBarriers[0].subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        imageMemoryBarriers[0].subresourceRange.baseMipLevel = 0;
        imageMemoryBarriers[0].subresourceRange.levelCount = 1;
        imageMemoryBarriers[0].subresourceRange.baseArrayLayer = 0;
        imageMemoryBarriers[0].subresourceRange.layerCount = 1;

        imageMemoryBarriers[1] = VkImageMemoryBarrier { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
        imageMemoryBarriers[1].srcAccessMask = 0;
        imageMemoryBarriers[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        imageMemoryBarriers[1].oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageMemoryBarriers[1].newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageMemoryBarriers[1].image = mTextureImage;
        imageMemoryBarriers[1].subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageMemoryBarriers[1].subresourceRange.baseMipLevel = 0;
        imageMemoryBarriers[1].subresourceRange.levelCount = 1;
        imageMemoryBarriers[1].subresourceRange.baseArrayLayer = 0;
        imageMemoryBarriers[1].subresourceRange.layerCount = 1;

        vkCmdPipelineBarrier(
            commandBuffer,
            VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT| VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
            0,
            0,
            nullptr,
            0,
            nullptr,
            2,
            imageMemoryBarriers
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
        VkDescriptorBufferInfo bufferInfo = {};
        bufferInfo.buffer = mUniformBuffer;
        bufferInfo.offset = 0;
        bufferInfo.range = VK_WHOLE_SIZE;

        VkWriteDescriptorSet descriptorWrite = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };
        descriptorWrite.dstSet = mUniformDescriptorSet;
        descriptorWrite.dstBinding = 0;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        descriptorWrite.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(mDevice, 1, &descriptorWrite, 0, nullptr);
    }

    {
        VkDescriptorImageInfo imageInfo = { };
        imageInfo.sampler = mTextureSampler;
        imageInfo.imageView = mTextureImageView;
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        VkWriteDescriptorSet descriptorWrite = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };
        descriptorWrite.dstSet = mSamplerDescriptorSet;
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


            VkClearValue clearValues[2];
            clearValues[0].color = VkClearColorValue { kClearColor.r, kClearColor.g, kClearColor.b, kClearColor.a };
            clearValues[1].depthStencil = VkClearDepthStencilValue { 1.0f, 0 };

            VkRenderPassBeginInfo renderPassBeginInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
            renderPassBeginInfo.renderPass = mRenderPass;
            renderPassBeginInfo.framebuffer = mFramebuffers[i];
            renderPassBeginInfo.renderArea.extent.width = mWidth;
            renderPassBeginInfo.renderArea.extent.height = mHeight;
            renderPassBeginInfo.clearValueCount = 2;
            renderPassBeginInfo.pClearValues = clearValues;

            vkCmdBeginRenderPass(mCommandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdBindPipeline(mCommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, mPipeline);

            VkViewport viewport = { 0, static_cast<float>(mHeight), static_cast<float>(mWidth), -static_cast<float>(mHeight), 0.0f, 1.0f };
            vkCmdSetViewport(mCommandBuffers[i], 0, 1, &viewport);

            VkRect2D scissor = { { 0, 0 }, { mWidth, mHeight } };
            vkCmdSetScissor(mCommandBuffers[i], 0, 1, &scissor);

            constexpr VkDeviceSize kOffset = 0;
            vkCmdBindVertexBuffers(mCommandBuffers[i], 0, 1, &mVertexBuffer, &kOffset);

            std::vector<VkDescriptorSet> sets = { mUniformDescriptorSet, mSamplerDescriptorSet };

            for (auto j = 0; j != kPositions.size(); ++j)
            {
                uint32_t offset = sizeof(glm::mat4) * j;

                vkCmdBindDescriptorSets(
                    mCommandBuffers[i],
                    VK_PIPELINE_BIND_POINT_GRAPHICS,
                    mPipelineLayout,
                    0,
                    static_cast<uint32_t>(sets.size()), sets.data(),
                    1, &offset
                );

                vkCmdDraw(mCommandBuffers[i], 36, 1, 0, 0);
            }

            vkCmdEndRenderPass(mCommandBuffers[i]);
            vkEndCommandBuffer(mCommandBuffers[i]);
        }
    }
}

void VkCoordinationSample::onExit ()
{
    vkDeviceWaitIdle(mDevice);

    for (auto framebuffer : mFramebuffers)
    {
        vkDestroyFramebuffer(mDevice, framebuffer, nullptr);
    }

    vkDestroyPipeline(mDevice, mPipeline, nullptr);

    vkDestroyPipelineLayout(mDevice, mPipelineLayout, nullptr);

    vkDestroyShaderModule(mDevice, mFragShaderModule, nullptr);
    vkDestroyShaderModule(mDevice, mVertShaderModule, nullptr);

    vkDestroyRenderPass(mDevice, mRenderPass, nullptr);

    vkDestroyDescriptorSetLayout(mDevice, mSamplerDescriptorSetLayout, nullptr);
    vkDestroyDescriptorSetLayout(mDevice, mUniformDescriptorSetLayout, nullptr);

    vkDestroyDescriptorPool(mDevice, mDescriptorPool, nullptr);

    vkDestroySampler(mDevice, mTextureSampler, nullptr);

    vkDestroyImageView(mDevice, mTextureImageView, nullptr);
    vkFreeMemory(mDevice, mTextureMemory, nullptr);
    vkDestroyImage(mDevice, mTextureImage, nullptr);

    vkFreeMemory(mDevice, mUniformMemory, nullptr);
    vkDestroyBuffer(mDevice, mUniformBuffer, nullptr);

    vkFreeMemory(mDevice, mVertexMemory, nullptr);
    vkDestroyBuffer(mDevice, mVertexBuffer, nullptr);

    vkDestroyImageView(mDevice, mDepthImageView, nullptr);
    vkFreeMemory(mDevice, mDepthMemory, nullptr);
    vkDestroyImage(mDevice, mDepthImage, nullptr);

    VkSample::onExit();
}

void VkCoordinationSample::onUpdate ()
{
    const auto ratio = static_cast<float>(mWidth) / static_cast<float>(mHeight);
    mProjMatix = glm::perspective(glm::radians(45.0f), ratio, 1.0f, 100.0f);
    mViewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 modelMatrix;

    void *data;
    vkMapMemory(mDevice, mUniformMemory, 0, VK_WHOLE_SIZE, 0, &data);

    for (auto i = 0; i != kPositions.size(); ++i)
    {
        modelMatrix = glm::translate(glm::mat4(1.0f), kPositions[i]);

        auto mvpMatrix = mProjMatix * mViewMatrix * modelMatrix;
        memcpy(static_cast<uint8_t*>(data) + sizeof(mvpMatrix) * i, glm::value_ptr(mvpMatrix), sizeof(mvpMatrix));
    }

    vkUnmapMemory(mDevice, mUniformMemory);
}

void VkCoordinationSample::onRender (HDC deviceContext)
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