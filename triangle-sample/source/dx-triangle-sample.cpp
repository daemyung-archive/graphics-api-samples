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

#include "dx-triangle-sample.h"

#include <glm/gtc/type_ptr.hpp>

#include "triangle-resources.h"

constexpr char* kVertShaderPath = RESOURCE_DIR"/triangle.hlsl";

constexpr char* kPixelShaderPath = RESOURCE_DIR"/triangle.hlsl";

DxTriangleSample::DxTriangleSample (std::wstring const& title, uint32_t width, uint32_t height)
    :
    DxSample(title, width, height),
    mRtvDescriptorSize(0),
    mViewport(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height)),
    mScissor(0, 0, width, height)
{
}

void DxTriangleSample::onInit (HINSTANCE instance, HWND window, HDC deviceContext)
{
    DxSample::onInit(instance, window, deviceContext);

    HRESULT result = S_OK;

    {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};

        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        desc.NumDescriptors = kBackBufferCount;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

        result = mDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&mRtvHeap));
    }

    if (S_OK == result)
    {
        mRtvDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        CD3DX12_CPU_DESCRIPTOR_HANDLE handle(mRtvHeap->GetCPUDescriptorHandleForHeapStart());

        for (auto n = 0; n != kBackBufferCount; ++n)
        {
            mDevice->CreateRenderTargetView(mBackBuffers[n].Get(), nullptr, handle);
            handle.Offset(mRtvDescriptorSize);
        }
    }

    const uint32_t kVertexBufferSize = sizeof(Vertex) * static_cast<uint32_t>(kVerticies.size());

    ComPtr<ID3D12Resource> stagingBuffer;

    if (S_OK == result)
    {
        result = mDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                                                  D3D12_HEAP_FLAG_NONE,
                                                  &CD3DX12_RESOURCE_DESC::Buffer(kVertexBufferSize),
                                                  D3D12_RESOURCE_STATE_GENERIC_READ,
                                                  nullptr, IID_PPV_ARGS(&stagingBuffer));
    }

    if (S_OK == result)
    {
        result = mDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
                                                  D3D12_HEAP_FLAG_NONE,
                                                  &CD3DX12_RESOURCE_DESC::Buffer(kVertexBufferSize),
                                                  D3D12_RESOURCE_STATE_COPY_DEST,
                                                  nullptr, IID_PPV_ARGS(&mVertexBuffer));
    }

    if (S_OK == result)
    {
        mVertexBufferView.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
        mVertexBufferView.SizeInBytes = kVertexBufferSize;
        mVertexBufferView.StrideInBytes = sizeof(Vertex);
    }

    ComPtr<ID3DBlob> signature;

    if (S_OK == result)
    {
        CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC desc = {};

        desc.Init_1_1(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

        result = D3DX12SerializeVersionedRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1_0, &signature, nullptr);
    }

    if (S_OK == result)
    {
        result = mDevice->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&mRootSignature));
    }

    constexpr auto kCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

    ComPtr<ID3DBlob> error;
    ComPtr<ID3DBlob> vertexShader;

    if (S_OK == result)
    {
        result = D3DCompileFromFile(GetUnicodePath(kVertShaderPath).data(), nullptr, nullptr, "VSMain", "vs_5_0", kCompileFlags, 0, &vertexShader, &error);
    }

    if (S_OK != result)
    {
        OutputDebugStringA(reinterpret_cast<char*>(error->GetBufferPointer()));
    }

    ComPtr<ID3DBlob> pixelShader;

    if (S_OK == result)
    {
        result = D3DCompileFromFile(GetUnicodePath(kPixelShaderPath).data(), nullptr, nullptr, "PSMain", "ps_5_0", kCompileFlags, 0, &pixelShader, &error);
    }

    if (S_OK != result)
    {
        OutputDebugStringA(reinterpret_cast<char*>(error->GetBufferPointer()));
    }

    if (S_OK == result)
    {
        std::vector<D3D12_INPUT_ELEMENT_DESC> inputElementsDesc =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,                 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
            { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(glm::vec4), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
        };

        D3D12_RASTERIZER_DESC rasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
        rasterizerState.CullMode = D3D12_CULL_MODE_NONE;

        DXGI_SAMPLE_DESC sampleDesc = {};
        sampleDesc.Count = 1;

        D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};

        desc.pRootSignature = mRootSignature.Get();
        desc.VS = CD3DX12_SHADER_BYTECODE(vertexShader.Get());
        desc.PS = CD3DX12_SHADER_BYTECODE(pixelShader.Get());
        desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        desc.SampleMask = UINT32_MAX;
        desc.RasterizerState = rasterizerState;
        desc.DepthStencilState.DepthEnable = false;
        desc.DepthStencilState.StencilEnable = false;
        desc.InputLayout.NumElements = static_cast<uint32_t>(inputElementsDesc.size());
        desc.InputLayout.pInputElementDescs = inputElementsDesc.data();
        desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        desc.NumRenderTargets = 1;
        desc.RTVFormats[0] = kBackBufferFormat;
        desc.SampleDesc = sampleDesc;

        result = mDevice->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&mPipelineState));
    }

    if (S_OK == result)
    {
        result = mDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, mCommandAllocators[0].Get(), mPipelineState.Get(), IID_PPV_ARGS(&mCommandList));
    }

    if (S_OK == result)
    {
        D3D12_SUBRESOURCE_DATA subResData = {};
        subResData.pData = kVerticies.data();
        subResData.RowPitch = kVertexBufferSize;
        subResData.SlicePitch = subResData.RowPitch;

        UpdateSubresources(mCommandList.Get(), mVertexBuffer.Get(), stagingBuffer.Get(), 0, 0, 1, &subResData);

        mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mVertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

        result = mCommandList->Close();
    }

    if (S_OK == result)
    {
        std::vector<ID3D12CommandList*> pCommandLists = { mCommandList.Get() };
        mCommandQueue->ExecuteCommandLists(static_cast<uint32_t>(pCommandLists.size()), pCommandLists.data());

        DeviceWaitIdle();
    }
}

void DxTriangleSample::onExit ()
{
    DxSample::onExit();
}

void DxTriangleSample::onUpdate ()
{
}

void DxTriangleSample::onRender (HDC deviceContext)
{
    HRESULT result = S_OK;

    const auto kFrameIndex = mSwapChain->GetCurrentBackBufferIndex();

    {
        result = mCommandQueue->Signal(mFence.Get(), mFenceValues[kFrameIndex]);
    }

    if (S_OK == result)
    {
        if (mFence->GetCompletedValue() < mFenceValues[kFrameIndex])
        {
            mFence->SetEventOnCompletion(mFenceValues[kFrameIndex], mEvent);
            WaitForSingleObject(mEvent, INFINITE);
        }

        populateCommandList(kFrameIndex);

        std::vector<ID3D12CommandList*> pCommandLists = { mCommandList.Get() };
        mCommandQueue->ExecuteCommandLists(static_cast<uint32_t>(pCommandLists.size()), pCommandLists.data());
        mCommandQueue->Signal(mFence.Get(), mFenceValues[kFrameIndex]);

        const auto kNextFenceValue = mFenceValues[kFrameIndex] + 1;

        mSwapChain->Present(1, 0);

        mFenceValues[mSwapChain->GetCurrentBackBufferIndex()] = kNextFenceValue + 1;
    }
}

void DxTriangleSample::populateCommandList(uint32_t frameIndex)
{
    HRESULT result = S_OK;

    {
        result = mCommandAllocators[frameIndex]->Reset();
    }

    if (S_OK == result)
    {
        result = mCommandList->Reset(mCommandAllocators[frameIndex].Get(), mPipelineState.Get());
    }

    if (S_OK == result)
    {
        mCommandList->SetGraphicsRootSignature(mRootSignature.Get());
        mCommandList->RSSetViewports(1, &mViewport);
        mCommandList->RSSetScissorRects(1, &mScissor);

        const auto kCurrentBackBuffer = mBackBuffers[frameIndex];
        const CD3DX12_CPU_DESCRIPTOR_HANDLE kCurrentRtvHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, mRtvDescriptorSize);

        mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(kCurrentBackBuffer.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

        mCommandList->OMSetRenderTargets(1, &kCurrentRtvHandle, false, nullptr);

        mCommandList->ClearRenderTargetView(kCurrentRtvHandle, glm::value_ptr(kClearColor), 0, nullptr);

        mCommandList->IASetVertexBuffers(0, 1, &mVertexBufferView);
        mCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        mCommandList->DrawInstanced(3, 1, 0, 0);

        mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(kCurrentBackBuffer.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

        result = mCommandList->Close();
    }
}