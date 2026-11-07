#include "Game.h"

#include "../../input.h"
#include "../../mem.h"
#include "../../sound.h"
#include "../../surface.h"
#include "../../windowInit.h"
#include "io_wad.h"

// GLOBAL: STUNTGP_D3D 0x60d61c
int g_60d61c;

// TODO: update this based on currrent date and a compile-time define?

#if !defined(REGP_FIXES)
// GLOBAL: STUNTGP_D3D 0x4826a4
const char g_VERSION_DATE[] = "Nov 21 2000";

// GLOBAL: STUNTGP_D3D 0x482698
const char g_VERSION_TIME[] = "16:26:50";
#else
const char g_VERSION_DATE[] = __DATE__;

const char g_VERSION_TIME[] = __TIME__;
#endif

// GLOBAL: STUNTGP_D3D 0x4826b0
const char g_VERSION_FORMAT[] = "Version: %s - %s";

// GLOBAL: STUNTGP_D3D 0x612bf8
static char g_VERSION_STRING[255];

// FUNCTION: STUNTGP_D3D 0x442010
void GetGameBuildVersion()
{
    sprintf(g_VERSION_STRING, g_VERSION_FORMAT, g_VERSION_DATE, g_VERSION_TIME);
#if defined(SGP_DEBUG)
    OutputDebugString(g_VERSION_STRING);
#endif
    return;
}

// STUB: STUNTGP_D3D 0x441d70
void FUN_441d70()
{
}

// STUB: STUNTGP_D3D 0x441f00
void FUN_441f00()
{
}

// STUB: STUNTGP_D3D 0x442120
void FUN_442120()
{
}

// STUB: STUNTGP_D3D 0x43d180
void FUN_43d180()
{
}

// FUNCTION: STUNTGP_D3D 0x442180
void FUN_442180()
{
    if (g_60d61c == 1)
    {
        FUN_43d180();
    }
    FUN_431800();
    WAD_FlushWadCache();
    FUN_422a60();
    Input_Shutdown();
    Sound_Shutdown();
    Mem_Shutdown();
}

// STUB: STUNTGP_D3D 0x4427b0
void FUN_4427b0()
{
}

// STUB: STUNTGP_D3D 0x442810
void FUN_442810()
{
}
