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

#ifndef SAMPLE_H
#define SAMPLE_H

#include <string>
#include <cstdint>
#include <windows.h>

#include "common/camera.h"

class Sample
{
public:
    Sample (std::wstring const& title, uint32_t width, uint32_t height);

    virtual ~Sample () = default;

    virtual void onInit (HINSTANCE instance, HWND window, HDC deviceContext) = 0;

    virtual void onExit () = 0;

    virtual void onUpdate () = 0;

    virtual void onRender (HDC deviceContext) = 0;

    virtual void onKeyDown (WPARAM key);

    virtual void onMouseDown ();

    virtual void onMouseUp ();

    virtual void onMouseMove (int xPos, int yPos);

    virtual void onMouseWheel (int wheelDelta);

    inline auto getTitle () const noexcept
    {
        return mTitle;
    }

    inline auto getWidth () const noexcept
    {
        return mWidth;
    }

    inline auto getHeight () const noexcept
    {
        return mHeight;
    }

protected:
    std::wstring mTitle;
    uint32_t     mWidth;
    uint32_t     mHeight;
    bool         mIsMouseDown;
    bool         mIsFirstMouseMove;
    Camera       mCamera;
};

#endif