#define WIN32_LEAN_AND_MEAN

#include <cstdio>
#include <windows.h>

extern int g_DISPLAYRESWIDTH;

extern int g_DISPLAYRESHEIGHT;

extern int g_DISPLAYRESDEPTH;

void GetGameBuildVersion();
void Script_ParseGameConfig();

HWND windowCreateInternal(HINSTANCE hInstance, LPCSTR className, LPCSTR windowName);
