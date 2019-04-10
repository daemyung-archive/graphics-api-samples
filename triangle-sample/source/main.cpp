#include <thread>
#include <windows.h>
#include <common/win32-application.h>

#include "gl-triangle-sample.h"
#include "vk-triangle-sample.h"
#include "dx-triangle-sample.h"

void glMain(HINSTANCE instance, int cmdShow)
{
    GlTriangleSample glSample(L"GlTriangleSample", 512, 512);
    Win32Application(instance).run(&glSample, cmdShow);
}

void vkMain(HINSTANCE instance, int cmdShow)
{
    VkTriangleSample vkSample(L"VkTriangleSample", 512, 512);
    Win32Application(instance).run(&vkSample, cmdShow);
}

void dxMain(HINSTANCE instance, int cmdShow)
{
    DxTriangleSample dxSample(L"DxTriangleSample", 512, 512);
    Win32Application(instance).run(&dxSample, cmdShow);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow)
{
    std::thread glThread(glMain, instance, cmdShow);
    std::thread vkThread(vkMain, instance, cmdShow);
    std::thread dxThread(dxMain, instance, cmdShow);

    glThread.join();
    vkThread.join();
    dxThread.join();

    DxTriangleSample dxSample(L"DxTriangleSample", 512, 512);

    return 0;
}