#include "uwu.h"

// TODO: update this based on currrent date and a compile-time define?

#ifndef REGP_FIXES
// STRING: STUNTGP_D3D 0x4826a4
const char g_VERSION_DATE[] = "Nov 21 2000";

// STRING: STUNTGP_D3D 0x482698
const char g_VERSION_TIME[] = "16:26:50";
#else
// STRING: STUNTGP_D3D 0x4826a4
const char g_VERSION_DATE[] = __DATE__;

// STRING: STUNTGP_D3D 0x482698
const char g_VERSION_TIME[] = __TIME__;
#endif
// STRING: STUNTGP_D3D 0x4826b0
const char g_VERSION_FORMAT[] = "Version: %s - %s";

// STRING: STUNTGP_D3D 0x612bf8
static char g_VERSION_STRING[255];

// FUNCTION: STUNTGP_D3D 0x442010
void GetGameBuildVersion()
{
    sprintf(g_VERSION_STRING, g_VERSION_FORMAT, g_VERSION_DATE, g_VERSION_TIME);
    return;
}

int size_of_file(char *path)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x42d660
void Script_ParseGameConfig()
{
    int size = {0};
    // char *filename;
    char path[128];
    sprintf(path, "Game.cfg");
    size = size_of_file(path);
    if (size == 0)
    {
        sprintf(path, "D:\\Game\\Game.cfg");
        size = size_of_file(path);
        if (size == 0)
        {
            sprintf(path, "C:\\Game\\Game.cfg");
            size_of_file(path);
        }
    }
    size = size_of_file(path);
    // mem alloc etc
    return;
}
