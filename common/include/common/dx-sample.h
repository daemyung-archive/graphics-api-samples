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

#ifndef DX_SAMPLE_H
#define DX_SAMPLE_H

#include <windows.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <d3d12.h>
#include <wrl.h>
#include <microsoft/d3dx12.h>
#include <array>

#include "common/sample.h"

using Microsoft::WRL::ComPtr;

constexpr auto kBackBufferCount = 2;
constexpr auto kBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

class DxSample : public Sample
{
public:
    DxSample (std::wstring const& title, uint32_t width, uint32_t height);

    virtual ~DxSample ();

    void onInit (HINSTANCE instance, HWND window, HDC deviceContext) override;

    void onExit () override;

protected:
    void DeviceWaitIdle();

    std::wstring GetUnicodePath(const char* pPath);

protected:
    uint32_t mFrameNumber;
    ComPtr<IDXGIFactory4> mFactory;
    ComPtr<IDXGIAdapter1> mAdapter;
    ComPtr<ID3D12Device> mDevice;
    ComPtr<ID3D12CommandQueue> mCommandQueue;
    std::array<ComPtr<ID3D12CommandAllocator>, kBackBufferCount> mCommandAllocators;
    ComPtr<ID3D12Fence> mFence;
    std::array<uint32_t, kBackBufferCount> mFenceValues;
    HANDLE mEvent;
    ComPtr<IDXGISwapChain3> mSwapChain;
    std::array<ComPtr<ID3D12Resource>, kBackBufferCount> mBackBuffers;
};

#endif
