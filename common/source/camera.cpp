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

#include "common/camera.h"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera ()
    :
    mPosition(0.0f, 0.0f, -5.0f),
    mWorldUpDir(0.0f, 1.0f, 0.0f),
    mFrontDir(0.0f, 0.0f, 1.0f),
    mRightDir(0.0f, 0.0f, 0.0f),
    mUpDir(0.0f, 0.0f, 0.0f),
    mYaw(90.0f),
    mPitch(0.0f),
    mMoveSpeed(0.1f),
    mTurnSpeed(0.1f),
    mFov(45.0f)
{
    updateDirections();
}

void Camera::translate (glm::vec3 const &direction)
{
    mPosition += direction * mMoveSpeed;
}

void Camera::turn (int xOffset, int yOffset)
{
    mYaw   += xOffset * mTurnSpeed;
    mPitch += yOffset * mTurnSpeed;

    updateDirections();
}

void Camera::aperture (int offset)
{
    mFov += offset;
    mFov = std::min(std::max(mFov, 22.5f), 67.5f);
}

float Camera::getFov () const noexcept
{
    return glm::radians(mFov);
}

glm::mat4 Camera::getViewMatrix () const noexcept
{
    return glm::lookAt(mPosition, mPosition + mFrontDir, mUpDir);
}

void Camera::updateDirections ()
{
    glm::vec3 frontDir = {
        cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)),
        sin(glm::radians(mPitch)),
        sin(glm::radians(mYaw)) * cos(glm::radians(mPitch))
    };

    mFrontDir = glm::normalize(frontDir);
    mRightDir = glm::normalize(glm::cross(mFrontDir, mWorldUpDir));
    mUpDir    = glm::normalize(glm::cross(mRightDir, mFrontDir));
}