#include <thread>
#include <windows.h>
#include <common/win32-application.h>

#include "gl-texture-sample.h"
#include "vk-texture-sample.h"

void glMain(HINSTANCE instance, int cmdShow)
{
    GlTextureSample sample(L"GlTextureSample", 512, 512);
    Win32Application(instance).run(&sample, cmdShow);
}

void vkMain(HINSTANCE instance, int cmdShow)
{
    VkTextureSample sample(L"VkTextureSample", 512, 512);
    Win32Application(instance).run(&sample, cmdShow);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow)
{
    std::thread glThread(glMain, instance, cmdShow);
    std::thread vkThread(vkMain, instance, cmdShow);

    glThread.join();
    vkThread.join();
    
    return 0;
}