#include <thread>
#include <windows.h>
#include <common/win32-application.h>

#include "gl-coordination-sample.h"
#include "vk-coordination-sample.h"

void glMain(HINSTANCE instance, int cmdShow)
{
    GlCoordinationSample glSample(L"GlTriangleSample", 512, 512);
    Win32Application(instance).run(&glSample, cmdShow);
}

void vkMain(HINSTANCE instance, int cmdShow)
{
    VkCoordinationSample vkSample(L"VkCoordinationSample", 512, 512);
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