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

#ifndef VK_SAMPLE_H
#define VK_SAMPLE_H

#include <vector>
#include <vulkan/vulkan.h>

#include "common/sample.h"

#define APPLY_MACRO_TO_VK_INSTANCE_CORE(macro)         \
    macro(vkGetDeviceProcAddr)                         \
    macro(vkGetPhysicalDeviceFeatures)                 \
    macro(vkGetPhysicalDeviceFormatProperties)         \
    macro(vkGetPhysicalDeviceImageFormatProperties)    \
    macro(vkGetPhysicalDeviceQueueFamilyProperties)    \
    macro(vkGetPhysicalDeviceMemoryProperties)         \
    macro(vkCreateDevice)                              \
    macro(vkDestroyDevice)                             \
    macro(vkEnumerateDeviceExtensionProperties)        \
    macro(vkEnumerateDeviceLayerProperties)

#define APPLY_MACRO_TO_VK_INSTANCE_EXT_KHR_SURFACE(macro) \
    macro(vkDestroySurfaceKHR)                            \
    macro(vkGetPhysicalDeviceSurfaceSupportKHR)           \
    macro(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)      \
    macro(vkGetPhysicalDeviceSurfaceFormatsKHR)           \
    macro(vkGetPhysicalDeviceSurfacePresentModesKHR)

#define APPLY_MACRO_TO_VK_INSTANCE_EXT_KHR_WIN32_SURFACE(macro) \
    macro(vkCreateWin32SurfaceKHR)                              \
    macro(vkGetPhysicalDeviceWin32PresentationSupportKHR)

#define APPLY_MACRO_TO_VK_DEVICE_CORE(macro)                 \
    macro(vkGetDeviceQueue)                                  \
    macro(vkQueueSubmit)                                     \
    macro(vkQueueWaitIdle)                                   \
    macro(vkDeviceWaitIdle)                                  \
    macro(vkAllocateMemory)                                  \
    macro(vkFreeMemory)                                      \
    macro(vkMapMemory)                                       \
    macro(vkUnmapMemory)                                     \
    macro(vkFlushMappedMemoryRanges)                         \
    macro(vkInvalidateMappedMemoryRanges)                    \
    macro(vkGetDeviceMemoryCommitment)                       \
    macro(vkBindBufferMemory)                                \
    macro(vkBindImageMemory)                                 \
    macro(vkGetBufferMemoryRequirements)                     \
    macro(vkGetImageMemoryRequirements)                      \
    macro(vkGetImageSparseMemoryRequirements)                \
    macro(vkGetPhysicalDeviceSparseImageFormatProperties)    \
    macro(vkQueueBindSparse)                                 \
    macro(vkCreateFence)                                     \
    macro(vkDestroyFence)                                    \
    macro(vkResetFences)                                     \
    macro(vkGetFenceStatus)                                  \
    macro(vkWaitForFences)                                   \
    macro(vkCreateSemaphore)                                 \
    macro(vkDestroySemaphore)                                \
    macro(vkCreateEvent)                                     \
    macro(vkDestroyEvent)                                    \
    macro(vkGetEventStatus)                                  \
    macro(vkSetEvent)                                        \
    macro(vkResetEvent)                                      \
    macro(vkCreateQueryPool)                                 \
    macro(vkDestroyQueryPool)                                \
    macro(vkGetQueryPoolResults)                             \
    macro(vkCreateBuffer)                                    \
    macro(vkDestroyBuffer)                                   \
    macro(vkCreateBufferView)                                \
    macro(vkDestroyBufferView)                               \
    macro(vkCreateImage)                                     \
    macro(vkDestroyImage)                                    \
    macro(vkGetImageSubresourceLayout)                       \
    macro(vkCreateImageView)                                 \
    macro(vkDestroyImageView)                                \
    macro(vkCreateShaderModule)                              \
    macro(vkDestroyShaderModule)                             \
    macro(vkCreatePipelineCache)                             \
    macro(vkDestroyPipelineCache)                            \
    macro(vkGetPipelineCacheData)                            \
    macro(vkMergePipelineCaches)                             \
    macro(vkCreateGraphicsPipelines)                         \
    macro(vkCreateComputePipelines)                          \
    macro(vkDestroyPipeline)                                 \
    macro(vkCreatePipelineLayout)                            \
    macro(vkDestroyPipelineLayout)                           \
    macro(vkCreateSampler)                                   \
    macro(vkDestroySampler)                                  \
    macro(vkCreateDescriptorSetLayout)                       \
    macro(vkDestroyDescriptorSetLayout)                      \
    macro(vkCreateDescriptorPool)                            \
    macro(vkDestroyDescriptorPool)                           \
    macro(vkResetDescriptorPool)                             \
    macro(vkAllocateDescriptorSets)                          \
    macro(vkFreeDescriptorSets)                              \
    macro(vkUpdateDescriptorSets)                            \
    macro(vkCreateFramebuffer)                               \
    macro(vkDestroyFramebuffer)                              \
    macro(vkCreateRenderPass)                                \
    macro(vkDestroyRenderPass)                               \
    macro(vkGetRenderAreaGranularity)                        \
    macro(vkCreateCommandPool)                               \
    macro(vkDestroyCommandPool)                              \
    macro(vkResetCommandPool)                                \
    macro(vkAllocateCommandBuffers)                          \
    macro(vkFreeCommandBuffers)                              \
    macro(vkBeginCommandBuffer)                              \
    macro(vkEndCommandBuffer)                                \
    macro(vkResetCommandBuffer)                              \
    macro(vkCmdBindPipeline)                                 \
    macro(vkCmdSetViewport)                                  \
    macro(vkCmdSetScissor)                                   \
    macro(vkCmdSetLineWidth)                                 \
    macro(vkCmdSetDepthBias)                                 \
    macro(vkCmdSetBlendConstants)                            \
    macro(vkCmdSetDepthBounds)                               \
    macro(vkCmdSetStencilCompareMask)                        \
    macro(vkCmdSetStencilWriteMask)                          \
    macro(vkCmdSetStencilReference)                          \
    macro(vkCmdBindDescriptorSets)                           \
    macro(vkCmdBindIndexBuffer)                              \
    macro(vkCmdBindVertexBuffers)                            \
    macro(vkCmdDraw)                                         \
    macro(vkCmdDrawIndexed)                                  \
    macro(vkCmdDrawIndirect)                                 \
    macro(vkCmdDrawIndexedIndirect)                          \
    macro(vkCmdDispatch)                                     \
    macro(vkCmdDispatchIndirect)                             \
    macro(vkCmdCopyBuffer)                                   \
    macro(vkCmdCopyImage)                                    \
    macro(vkCmdBlitImage)                                    \
    macro(vkCmdCopyBufferToImage)                            \
    macro(vkCmdCopyImageToBuffer)                            \
    macro(vkCmdUpdateBuffer)                                 \
    macro(vkCmdFillBuffer)                                   \
    macro(vkCmdClearColorImage)                              \
    macro(vkCmdClearDepthStencilImage)                       \
    macro(vkCmdClearAttachments)                             \
    macro(vkCmdResolveImage)                                 \
    macro(vkCmdSetEvent)                                     \
    macro(vkCmdResetEvent)                                   \
    macro(vkCmdWaitEvents)                                   \
    macro(vkCmdPipelineBarrier)                              \
    macro(vkCmdBeginQuery)                                   \
    macro(vkCmdEndQuery)                                     \
    macro(vkCmdResetQueryPool)                               \
    macro(vkCmdWriteTimestamp)                               \
    macro(vkCmdCopyQueryPoolResults)                         \
    macro(vkCmdPushConstants)                                \
    macro(vkCmdBeginRenderPass)                              \
    macro(vkCmdNextSubpass)                                  \
    macro(vkCmdEndRenderPass)                                \
    macro(vkCmdExecuteCommands)

#define APPLY_MACRO_TO_VK_DEVICE_EXT_KHR_SWAPCHAIN(macro)    \
    macro(vkCreateSwapchainKHR)                              \
    macro(vkDestroySwapchainKHR)                             \
    macro(vkGetSwapchainImagesKHR)                           \
    macro(vkAcquireNextImageKHR)                             \
    macro(vkQueuePresentKHR)

#define APPLY_MACRO_TO_VK_INSTANCE_API(macro)              \
    APPLY_MACRO_TO_VK_INSTANCE_CORE(macro)                 \
    APPLY_MACRO_TO_VK_INSTANCE_EXT_KHR_SURFACE(macro)      \
    APPLY_MACRO_TO_VK_INSTANCE_EXT_KHR_WIN32_SURFACE(macro)

#define APPLY_MACRO_TO_VK_DEVICE_API(macro)          \
    APPLY_MACRO_TO_VK_DEVICE_CORE(macro)             \
    APPLY_MACRO_TO_VK_DEVICE_EXT_KHR_SWAPCHAIN(macro)

#define DEFINE_VK_API_FUNCTION_PTR_MACRO(function) PFN_##function function;

class VkSample : public Sample
{
public:
    VkSample (std::wstring const& title, uint32_t width, uint32_t height);

    virtual ~VkSample();

    void onInit (HINSTANCE instance, HWND window, HDC deviceContext) override;

    void onExit () override;

    APPLY_MACRO_TO_VK_INSTANCE_API(DEFINE_VK_API_FUNCTION_PTR_MACRO)
    APPLY_MACRO_TO_VK_DEVICE_API(DEFINE_VK_API_FUNCTION_PTR_MACRO)

protected:
    uint32_t getMemoryTypeIndex (VkMemoryRequirements const &requirements, VkMemoryPropertyFlags flags);

    VkResult createShaderMoudle (std::string const &shaderPath, VkShaderModule &shaderMoudle);

protected:
    uint32_t                 mFrameNumber;
    VkInstance               mInstance;
    VkPhysicalDevice         mPhysicalDevice;
    VkPhysicalDeviceProperties mPhysicalDeviceProperties;
    VkPhysicalDeviceMemoryProperties mMemoryProperties;
    uint32_t                 mQueueFamilyIndex;
    VkDevice                 mDevice;
    VkQueue                  mQueue;
    VkCommandPool            mCommandPool;
    VkSurfaceKHR             mSurface;
    VkSurfaceFormatKHR       mSurfaceFormat;
    VkPresentModeKHR         mPresentMode;
    uint32_t                 mSwapchainImageCount;
    VkSwapchainKHR           mSwapchain;
    std::vector<VkImage>     mSwapchainImages;
    std::vector<VkImageView> mSwapchainImageViews;
    std::vector<VkSemaphore> mSwapchainAcquireSemaphores;
    std::vector<VkSemaphore> mRenderingDoneSemaphores;
    std::vector<VkFence>     mRenderingDoneFences;
    std::vector<VkCommandBuffer> mCommandBuffers;
};

#endif