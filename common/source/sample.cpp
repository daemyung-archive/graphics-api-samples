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

#include "common/sample.h"

#include <cassert>
#include <windows.h>

Sample::Sample (std::wstring const& title, uint32_t width, uint32_t height)
    :
    mTitle(title),
    mWidth(width),
    mHeight(height),
    mIsMouseDown(false),
    mIsFirstMouseMove(true),
    mCamera()
{
}

void Sample::onKeyDown (WPARAM key)
{
    glm::vec3 direction;

    switch (key)
    {
        case 'A':
        {
            const glm::vec3 kLeftDir = { 1.0f, 0.0f, 0.0f };
            direction = kLeftDir;
            break;
        }
        case 'D':
        {
            const glm::vec3 kRightDir = { -1.0f, 0.0f, 0.0f };
            direction = kRightDir;
            break;
        }
        case 'W':
        {
            const glm::vec3 kUpDir = { 0.0f, 1.0f, 0.0f };
            direction = kUpDir;
            break;
        }
        case 'S':
        {
            const glm::vec3 kDownDir = { 0.0f, -1.0f, 0.0f };
            direction = kDownDir;
            break;
        }
        case 'Q':
        {
            const glm::vec3 kForwardDir = { 0.0f, 0.0f, 1.0f };
            direction = kForwardDir;
            break;
        }
        case 'E':
        {
            const glm::vec3 kBackwardDir = { 0.0f, 0.0f, -1.0f };
            direction = kBackwardDir;
            break;
        }
        default:
        {
            return;
        }
    }

    mCamera.translate(direction);
}

void Sample::onMouseDown ()
{
    mIsMouseDown = true;
    mIsFirstMouseMove = true;
}

void Sample::onMouseUp ()
{
    mIsMouseDown = false;
}

void Sample::onMouseMove (int xPos, int yPos)
{
    if (!mIsMouseDown)
    {
        return;
    }

    static int lastXPos = 0, lastYPos = yPos;

    if (mIsFirstMouseMove)
    {
        lastXPos = xPos; lastYPos = yPos;
        mIsFirstMouseMove = false;
        return;
    }

    mCamera.turn(lastXPos - xPos, yPos - lastYPos);
    lastXPos = xPos; lastYPos = yPos;
}

void Sample::onMouseWheel (int wheelDelta)
{
    mCamera.aperture(wheelDelta);
}