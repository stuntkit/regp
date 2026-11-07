#include "Game.h"

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

// GLOBAL: STUNTGP_D3D 0x482668
float g_482668 = 1.0f;

// GLOBAL: STUNTGP_D3D 0x48266c
float g_48266c = 1.0f;

// GLOBAL: STUNTGP_D3D 0x482670
float g_482670 = 0.2725f;

// GLOBAL: STUNTGP_D3D 0x482674
float g_482674 = 1.0f / 0.2725f;

// GLOBAL: STUNTGP_D3D 0x482678
float g_482678 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x48267c
float g_48267c = -0.2725f;

// GLOBAL: STUNTGP_D3D 0x482680
float g_482680 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x482688
float g_482688 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x48268c
float g_48268c = -1.0f;

// GLOBAL: STUNTGP_D3D 0x482690
float g_482690 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x612cf8
int g_612cf8;

// GLOBAL: STUNTGP_D3D 0x61297c
int g_61297c;

// GLOBAL: STUNTGP_D3D 0x60df9c
int g_60df9c;

// GLOBAL: STUNTGP_D3D 0x4d5b20
int g_4d5b20;

// GLOBAL: STUNTGP_D3D 0x60d61c
int g_60d61c;

// FUNCTION: STUNTGP_D3D 0x441f90
void FUN_441f90()
{
    g_48266c = 1.0f / g_482668;
    g_482688 = 0.0f;
    g_48268c = -1.0f;
    g_482690 = 0.0f;
    g_482670 = g_482668 * 0.2725f;
    g_482674 = 1.0f / g_482670;
    g_482678 = 0.0f;
    g_48267c = g_482670 * -1.0f;
    g_482680 = 0.0f;
}

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

// FUNCTION: STUNTGP_D3D 0x442030
void FUN_442030()
{
    g_4d5b20 = 0;
    FUN_45f9d0();
    FUN_460dd0();
    FUN_460c90();
    FUN_445fa0();
    Mem_Reset();
    FUN_42e6e0();
    FUN_443d70();
    FUN_4457e0();
    if (g_612be8 == 1)
    {
        FUN_445f80();
        FUN_4469f0();
        FUN_40e050();
        FUN_40a2f0();
        FUN_401de0();
        FUN_413670();
        FUN_422420();
        FUN_4199a0();
        FUN_40d500();
    }
    if (g_612be8 == 2)
    {
        FUN_424c30(1);
        if (g_60d61c == 0)
        {
            g_60d61c = 1;
            FUN_43d0b0();
        }
        else
        {
            FUN_43d1d0();
        }
    }
    if (g_612be8 == 1)
    {
        FUN_43d1b0();
    }
    Timer_Reset();
}

// FUNCTION: STUNTGP_D3D 0x442100
void Timer_Reset()
{
    g_612d00 = Timer_GetCounter();
    g_612d04 = Timer_GetCounter();
}

// FUNCTION: STUNTGP_D3D 0x442120
void FUN_442120()
{
    g_612cf8 = 0;
    g_61297c = 100;
    FUN_429510();
    Random_SeedFromTime();
    Timer_Init();
    Mem_Init();
    FUN_4624b0();
    Script_ParseGameConfig();
    FUN_462090();
    FUN_45ec30();
    FUN_445f80();
    FUN_4249b0();
    g_60df9c = 0;
    FUN_442030();
}

// STUB: STUNTGP_D3D 0x442180
void FUN_442180()
{
}

// STUB: STUNTGP_D3D 0x4427b0
void FUN_4427b0()
{
}

// STUB: STUNTGP_D3D 0x442810
void FUN_442810()
{
}
