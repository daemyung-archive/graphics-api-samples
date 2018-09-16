#include <windows.h>
#include <common/win32-application.h>

#include "gl-model-sample.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow)
{
    GlModelSample sample(L"GlModelSample", 512, 512);
    Win32Application(instance).run(&sample, cmdShow);
    return 0;
}