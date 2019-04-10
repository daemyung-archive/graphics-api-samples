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

#include "common/dx-sample.h"

#include <cassert>

DxSample::DxSample (std::wstring const& title, uint32_t width, uint32_t height)
    :
    Sample(title, width, height),
    mFrameNumber(0),
    mFenceValues { 1, 2 }
{
    HRESULT result = S_OK;

    ComPtr<ID3D12Debug> debugController;

    {
        result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
    }

    uint32_t factoryCreateFlags = 0;

    if (S_OK != result)
    {
        debugController->EnableDebugLayer();

        factoryCreateFlags |= DXGI_CREATE_FACTORY_DEBUG;
    }

    if (S_OK == result)
    {
        result = CreateDXGIFactory2(factoryCreateFlags, IID_PPV_ARGS(&mFactory));
    }

    if (S_OK == result)
    {
        uint32_t n = 0;

        while (DXGI_ERROR_NOT_FOUND != mFactory->EnumAdapters1(n, &mAdapter))
        {
            DXGI_ADAPTER_DESC1 desc = {};
            mAdapter->GetDesc1(&desc);

            if (DXGI_ADAPTER_FLAG_SOFTWARE != desc.Flags)
            {
                break;
            }

            ++n;
        }
    }

    if (S_OK == result)
    {
        result = D3D12CreateDevice(mAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&mDevice));
    }

    if (S_OK == result)
    {
        D3D12_COMMAND_QUEUE_DESC desc = {};

        desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

        result = mDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&mCommandQueue));
    }

    if (S_OK == result)
    {
        for (auto& commandAllocator : mCommandAllocators)
        {
            result = mDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
            assert(S_OK == result);
        }
    }

    if (S_OK == result)
    {
        result = mDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));
    }

    if (S_OK == result)
    {
        mEvent = CreateEvent(nullptr, false, false, nullptr);

        if (nullptr == mEvent)
        {
            result = E_FAIL;
        }
    }

    assert(S_OK == result);
}

DxSample::~DxSample ()
{
}

void DxSample::onInit (HINSTANCE instance, HWND window, HDC deviceContext)
{
    HRESULT result = S_OK;

    ComPtr<IDXGISwapChain1> swapChain;

    {
        DXGI_SAMPLE_DESC sampleDesc = {};
        sampleDesc.Count = 1;

        DXGI_SWAP_CHAIN_DESC1 desc = {};
        desc.Width = mWidth;
        desc.Height = mHeight;
        desc.Format = kBackBufferFormat;
        desc.SampleDesc = sampleDesc;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = kBackBufferCount;
        desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

        result = mFactory->CreateSwapChainForHwnd(mCommandQueue.Get(), window, &desc, nullptr, nullptr, &swapChain);
    }

    if (S_OK == result)
    {
        result = swapChain.As(&mSwapChain);
    }

    if (S_OK == result)
    {
        for (auto n = 0; n != kBackBufferCount; ++n)
        {
            result = mSwapChain->GetBuffer(n, IID_PPV_ARGS(&mBackBuffers[n]));
            assert(S_OK == result);
        }
    }
}

void DxSample::onExit ()
{
    DeviceWaitIdle();
    CloseHandle(mEvent);
}

void DxSample::DeviceWaitIdle()
{
    HRESULT result = S_OK;

    auto& fenceValue = mFenceValues[mSwapChain->GetCurrentBackBufferIndex()];

    {
        result = mCommandQueue->Signal(mFence.Get(), fenceValue);
    }

    if (S_OK == result)
    {
        result = mFence->SetEventOnCompletion(fenceValue, mEvent);
    }

    if (S_OK == result)
    {
        WaitForSingleObject(mEvent, INFINITE);
        ++fenceValue;
    }
}

std::wstring DxSample::GetUnicodePath(const char* pPath)
{
    auto kPathLen = strlen(pPath) + 1;
    std::wstring unicodePath(kPathLen, L'#');
    size_t outSize;

    mbstowcs_s(&outSize, unicodePath.data(), kPathLen, pPath, kPathLen - 1);

    return unicodePath;
}