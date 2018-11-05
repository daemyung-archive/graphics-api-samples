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

#include "common/vk-sample.h"

#include <algorithm>
#include <fstream>
#include <cassert>

#define GET_VK_INSTANCE_API_PROC_ADDR_MACRO(function)                                        \
    function = reinterpret_cast<PFN_##function>(vkGetInstanceProcAddr(mInstance, #function));

#define GET_VK_DEVICE_API_PROC_ADDR_MACRO(function)                                      \
    function = reinterpret_cast<PFN_##function>(vkGetDeviceProcAddr(mDevice, #function));

VkSample::VkSample (std::wstring const& title, uint32_t width, uint32_t height)
    :
    Sample(title, width, height),
    mFrameNumber(0)
{
    {
        const std::vector<const char *> kLayerNames = {
            "VK_LAYER_LUNARG_standard_validation"
        };

        const std::vector<const char *> kExtensionNames = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME
        };

        VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
        createInfo.enabledLayerCount = static_cast<uint32_t>(kLayerNames.size());
        createInfo.ppEnabledLayerNames = kLayerNames.data();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(kExtensionNames.size());
        createInfo.ppEnabledExtensionNames = kExtensionNames.data();

        auto result = vkCreateInstance(&createInfo, nullptr, &mInstance);
        switch (result)
        {
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                assert(false);
                break;
            case VK_ERROR_INITIALIZATION_FAILED:
                assert(false);
                break;
            case VK_ERROR_LAYER_NOT_PRESENT:
                assert(false);
                break;
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                assert(false);
                break;
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                assert(false);
                break;
            default:
                break;
        }

        APPLY_MACRO_TO_VK_INSTANCE_API(GET_VK_INSTANCE_API_PROC_ADDR_MACRO);
    }

    {
        uint32_t count;
        vkEnumeratePhysicalDevices(mInstance, &count, nullptr);

        std::vector<VkPhysicalDevice> physicalDevices(count);
        vkEnumeratePhysicalDevices(mInstance, &count, physicalDevices.data());

        assert(physicalDevices.size() != 0);

        mPhysicalDevice = physicalDevices[0];
    }

    {
        vkGetPhysicalDeviceProperties(mPhysicalDevice, &mPhysicalDeviceProperties);
    }

    {
        vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &mMemoryProperties);
    }

    {
        uint32_t count;
        vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &count, nullptr);
        
        std::vector<VkQueueFamilyProperties> properties(count);
        vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &count, properties.data());

        constexpr auto kQueueFlags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT;
        for (auto i = 0; i != properties.size(); ++i)
        {
            if ((properties[i].queueFlags & kQueueFlags) == kQueueFlags)
            {
                mQueueFamilyIndex = i;
                break;
            }
        }
    }

    {
        constexpr auto kQueuePriority = 1.0f;

        VkDeviceQueueCreateInfo queueCreateInfo = { VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
        queueCreateInfo.queueFamilyIndex = mQueueFamilyIndex;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &kQueuePriority;
        
        VkPhysicalDeviceFeatures physicalDeviceFeatures;
        vkGetPhysicalDeviceFeatures(mPhysicalDevice, &physicalDeviceFeatures);

        const std::vector<const char *> kExtensionNames = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            VK_KHR_MAINTENANCE1_EXTENSION_NAME
        };

        VkDeviceCreateInfo createInfo = { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
        createInfo.queueCreateInfoCount = 1;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(kExtensionNames.size());
        createInfo.ppEnabledExtensionNames = kExtensionNames.data();
        createInfo.pEnabledFeatures = &physicalDeviceFeatures;

        auto result = vkCreateDevice(mPhysicalDevice, &createInfo, nullptr, &mDevice);

        switch (result)
        {
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                assert(false);
                break;
                
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                assert(false);
                break;
            
            case VK_ERROR_INITIALIZATION_FAILED:
                assert(false);
                break;

            case VK_ERROR_EXTENSION_NOT_PRESENT:
                assert(false);
                break;

            case VK_ERROR_FEATURE_NOT_PRESENT:
                assert(false);
                break;

            case VK_ERROR_TOO_MANY_OBJECTS:
                assert(false);
                break;

            case VK_ERROR_DEVICE_LOST:
                assert(false);
                break;

            default:
                break;
        }

        APPLY_MACRO_TO_VK_DEVICE_API(GET_VK_DEVICE_API_PROC_ADDR_MACRO)
    }

    {
        vkGetDeviceQueue(mDevice, mQueueFamilyIndex, 0, &mQueue);
    }

    {
        VkCommandPoolCreateInfo createInfo = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
        createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        createInfo.queueFamilyIndex = mQueueFamilyIndex;

        vkCreateCommandPool(mDevice, &createInfo, nullptr, &mCommandPool);
    }
}

VkSample::~VkSample()
{
    vkDestroyCommandPool(mDevice, mCommandPool, nullptr);

    vkDestroyDevice(mDevice, nullptr);

    vkDestroyInstance(mInstance, nullptr);
}

void VkSample::onInit (HINSTANCE instance, HWND window, HDC deviceContext)
{
    {
        VkWin32SurfaceCreateInfoKHR createInfo = { VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR };
        createInfo.hinstance = instance;
        createInfo.hwnd = window;

        vkCreateWin32SurfaceKHR(mInstance, &createInfo, nullptr, &mSurface);

        VkBool32 supported;
        vkGetPhysicalDeviceSurfaceSupportKHR(mPhysicalDevice, mQueueFamilyIndex, mSurface, &supported);
        assert(supported);
    }

    {
        uint32_t surfaceFormatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(mPhysicalDevice, mSurface, &surfaceFormatCount, nullptr);

        std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(mPhysicalDevice, mSurface, &surfaceFormatCount, surfaceFormats.data());
        mSurfaceFormat = surfaceFormats[0];

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(mPhysicalDevice, mSurface, &presentModeCount, nullptr);

        std::vector<VkPresentModeKHR> presentModes(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(mPhysicalDevice, mSurface, &presentModeCount, presentModes.data());
        mPresentMode = presentModes[0];

        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(mPhysicalDevice, mSurface, &surfaceCapabilities);

        assert(surfaceCapabilities.currentExtent.width == mWidth);
        assert(surfaceCapabilities.currentExtent.height == mHeight);

        VkSwapchainCreateInfoKHR createInfo = { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
        createInfo.surface = mSurface;
        createInfo.minImageCount = std::max<uint32_t>(surfaceCapabilities.minImageCount, 2);
        createInfo.imageFormat = mSurfaceFormat.format;
        createInfo.imageColorSpace = mSurfaceFormat.colorSpace;
        createInfo.imageExtent = surfaceCapabilities.currentExtent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = mPresentMode;
        createInfo.clipped = VK_TRUE;

        vkCreateSwapchainKHR(mDevice, &createInfo, nullptr, &mSwapchain);
    }

    {
        vkGetSwapchainImagesKHR(mDevice, mSwapchain, &mSwapchainImageCount, nullptr);

        mSwapchainImages.resize(mSwapchainImageCount);
        vkGetSwapchainImagesKHR(mDevice, mSwapchain, &mSwapchainImageCount, mSwapchainImages.data());
    }

    {
        mSwapchainImageViews.resize(mSwapchainImageCount);

        VkImageViewCreateInfo createInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = mSurfaceFormat.format;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_R;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_G;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_B;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_A;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        for (auto i = 0; i != mSwapchainImageCount; ++i)
        {
            createInfo.image = mSwapchainImages[i];

            vkCreateImageView(mDevice, &createInfo, nullptr, &mSwapchainImageViews[i]);
        }
    }

    {
        mSwapchainAcquireSemaphores.resize(mSwapchainImageCount);
        mRenderingDoneSemaphores.resize(mSwapchainImageCount);

        VkSemaphoreCreateInfo createInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };

        for (auto i = 0; i != mSwapchainImageCount; ++i)
        {
            vkCreateSemaphore(mDevice, &createInfo, nullptr, &mSwapchainAcquireSemaphores[i]);
            vkCreateSemaphore(mDevice, &createInfo, nullptr, &mRenderingDoneSemaphores[i]);
        }
    }

    {
        mRenderingDoneFences.resize(mSwapchainImageCount);

        VkFenceCreateInfo createInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
        createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (auto i = 0; i != mSwapchainImageCount; ++i)
        {
            vkCreateFence(mDevice, &createInfo, nullptr, &mRenderingDoneFences[i]);
        }
    }

    {
        mCommandBuffers.resize(mSwapchainImageCount);

        VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
        allocateInfo.commandPool = mCommandPool;
        allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocateInfo.commandBufferCount = mSwapchainImageCount;

        vkAllocateCommandBuffers(mDevice, &allocateInfo, mCommandBuffers.data());
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

        std::vector<VkImageMemoryBarrier> imageMemoryBarriers(mSwapchainImageCount);
        for (auto i = 0; i != mSwapchainImageCount; ++i)
        {
            imageMemoryBarriers[i].sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
            imageMemoryBarriers[i].srcAccessMask = 0;
            imageMemoryBarriers[i].dstAccessMask = 0;
            imageMemoryBarriers[i].oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            imageMemoryBarriers[i].newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            imageMemoryBarriers[i].image = mSwapchainImages[i];
            imageMemoryBarriers[i].subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageMemoryBarriers[i].subresourceRange.baseMipLevel = 0;
            imageMemoryBarriers[i].subresourceRange.levelCount = 1;
            imageMemoryBarriers[i].subresourceRange.baseArrayLayer = 0;
            imageMemoryBarriers[i].subresourceRange.layerCount = 1;
        }

        vkCmdPipelineBarrier(
            commandBuffer,
            VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            0,
            0,
            nullptr,
            0,
            nullptr,
            mSwapchainImageCount,
            imageMemoryBarriers.data()
        );

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(mQueue, 1, &submitInfo, VK_NULL_HANDLE);

        vkQueueWaitIdle(mQueue);

        vkFreeCommandBuffers(mDevice, mCommandPool, 1, &commandBuffer);
    }
}

void VkSample::onExit ()
{
    vkDeviceWaitIdle(mDevice);

    for (auto fence : mRenderingDoneFences)
    {
        vkDestroyFence(mDevice, fence, nullptr);
    }

    for (auto semaphore : mRenderingDoneSemaphores)
    {
        vkDestroySemaphore(mDevice, semaphore, nullptr);
    }

    for (auto semaphore : mSwapchainAcquireSemaphores)
    {
        vkDestroySemaphore(mDevice, semaphore, nullptr);
    }

    vkFreeCommandBuffers(mDevice, mCommandPool, mSwapchainImageCount, mCommandBuffers.data());

    for (auto imageView : mSwapchainImageViews)
    {
        vkDestroyImageView(mDevice, imageView, nullptr);
    }
    
    vkDestroySwapchainKHR(mDevice, mSwapchain, nullptr);

    vkDestroySurfaceKHR(mInstance, mSurface, nullptr);
}

uint32_t VkSample::getMemoryTypeIndex (VkMemoryRequirements const &requirements, VkMemoryPropertyFlags flags)
{
    for (auto i = 0; i != mMemoryProperties.memoryTypeCount; ++i)
    {
        if (requirements.memoryTypeBits & (0x1 << i))
        {
            if ((mMemoryProperties.memoryTypes[i].propertyFlags & flags) == flags)
            {
                return i;
            }
        }
    }

    return UINT32_MAX;
}

VkResult VkSample::createShaderMoudle (std::string const &shaderPath, VkShaderModule &shaderMoudle)
{
    std::fstream fs(shaderPath, std::fstream::in | std::fstream::binary);
    assert(fs.is_open());

    std::string code= std::string(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());

    VkShaderModuleCreateInfo createInfo = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<uint32_t *>(code.data());

    return vkCreateShaderModule(mDevice, &createInfo, nullptr, &shaderMoudle);
}