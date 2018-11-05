#include <thread>
#include <windows.h>
#include <common/win32-application.h>

#include "gl-camera-sample.h"
#include "vk-camera-sample.h"

void glMain(HINSTANCE instance, int cmdShow)
{
    GlCameraSample glSample(L"GlCameraSample", 512, 512);
    Win32Application(instance).run(&glSample, cmdShow);
}

void vkMain(HINSTANCE instance, int cmdShow)
{
    VkCameraSample vkSample(L"VkCameraSample", 512, 512);
    Win32Application(instance).run(&vkSample, cmdShow);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow)
{
    std::thread glThread(glMain, instance, cmdShow);
    std::thread vkThread(vkMain, instance, cmdShow);

    glThread.join();
    vkThread.join();

    return 0;
}