#include <windows.h>
#include <common/win32-application.h>

#include "gl-coordination-sample.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow)
{
    GlCoordinationSample sample(L"GlConstantSample", 512, 512);
    Win32Application(instance).run(&sample, cmdShow);
    return 0;
}