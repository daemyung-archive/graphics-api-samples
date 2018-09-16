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

#include "common/win32-application.h"

#include <cassert>
#include <string>

#include "common/sample.h"

#include <sstream>

namespace
{

std::wstring generateUniqueClassName ()
{
    auto       guid = GUID { };
    auto const result = CoCreateGuid(&guid);
    assert(result == S_OK);

    auto       guidString    = std::wstring { L"{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}~" };
    auto const writtenLength = StringFromGUID2(guid, &guidString[0], static_cast<int>(guidString.size()));
    assert(writtenLength == guidString.size());

    return guidString;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            auto const createStruct = reinterpret_cast<const LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));

            auto sample = reinterpret_cast<Sample*>(createStruct->lpCreateParams);
            sample->onInit(createStruct->hInstance, hWnd, GetDC(hWnd));

            return 0;
        }
        case WM_PAINT:
        {
            auto sample = reinterpret_cast<Sample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
            sample->onUpdate();
            sample->onRender(GetDC(hWnd));
        }
        case WM_KEYDOWN:
        {
            if (VK_ESCAPE == wParam)
            {
                auto const result = PostMessage(hWnd, WM_CLOSE, 0, 0);
                assert(result != 0);
            }
            else
            {
                auto sample = reinterpret_cast<Sample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
                sample->onKeyDown(wParam);
            }
            return 0;
        }
        case WM_LBUTTONDOWN:
        {
            SetCapture(hWnd);

            auto sample = reinterpret_cast<Sample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
            sample->onMouseDown();
            return 0;
        }
        case WM_LBUTTONUP:
        {
            auto sample = reinterpret_cast<Sample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
            sample->onMouseUp();

            ReleaseCapture();
            return 0;
        }
        case WM_MOUSEMOVE:
        {
            auto sample = reinterpret_cast<Sample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
            sample->onMouseMove(LOWORD(lParam), HIWORD(lParam));
            return 0;
        }
        case WM_MOUSEWHEEL:
        {
            auto sample = reinterpret_cast<Sample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
            sample->onMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);            
            return 0;
        }
        case WM_CLOSE:
        case WM_DESTROY:
        {
            auto sample = reinterpret_cast<Sample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
            sample->onExit();

            PostQuitMessage(0);
            return 0;
        }
        default:
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
}

}

Win32Application::Win32Application (HINSTANCE instance)
    :
    mInstance(instance),
    mAtom(NULL),
    mWindow(NULL)
{
    auto const className   = generateUniqueClassName();
    auto const windowClass = WNDCLASSEX {
        sizeof(WNDCLASSEX),                 // size
        CS_HREDRAW | CS_VREDRAW | CS_OWNDC, // style
        windowProcedure,                    // window procedure
        0,                                  // class  extra data
        0,                                  // window extra data
        mInstance,                          // instance
        LoadIcon(nullptr, IDI_APPLICATION), // icon
        LoadCursor(nullptr, IDC_ARROW),     // cursor
        nullptr,                            // background brush
        nullptr,                            // menu name
        className.c_str(),                  // class name
        nullptr,                            // small icon
    };
    assert(nullptr != windowClass.hIcon);
    assert(nullptr != windowClass.hCursor);

    mAtom = RegisterClassEx(&windowClass);
    assert(0 != mAtom);
}

void Win32Application::run (Sample *sample, int cmdShow)
{
    auto       windowRect = RECT { 0, 0, static_cast<LONG>(sample->getWidth()), static_cast<LONG>(sample->getHeight()) };
    auto const success = AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, FALSE, 0);
    assert(FALSE != success);

    mWindow = CreateWindowEx(
        0,                                     // extended style
        MAKEINTATOM(mAtom),                    // class atom or name
        sample->getTitle().c_str(),            // title
        WS_OVERLAPPEDWINDOW,                   // style
        CW_USEDEFAULT,                         // x
        CW_USEDEFAULT,                         // y
        windowRect.right - windowRect.left,    // width
        windowRect.bottom - windowRect.top,    // height
        nullptr,                               // parent window
        nullptr,                               // menu
        mInstance,                             // instance
        sample                                 // create parameter received in WM_CREATE
   );
    assert(nullptr != mWindow);

    ShowWindow(mWindow, cmdShow);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}