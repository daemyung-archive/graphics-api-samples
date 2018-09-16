#include <windows.h>
#include <common/win32-application.h>

#include "gl-camera-sample.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow)
{
    GlCameraSample sample(L"GlCameraSample", 512, 512);
    Win32Application(instance).run(&sample, cmdShow);
    return 0;
}