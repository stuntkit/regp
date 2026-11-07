#include "Game.h"

#include <cstdlib>
#include <cstring>

#include "GameUpdate.h"

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

// GLOBAL: STUNTGP_D3D 0x4722d0
GameSlot *g_4722d0 = g_498248;

// GLOBAL: STUNTGP_D3D 0x498248
GameSlot g_498248[4];

// GLOBAL: STUNTGP_D3D 0x612bf4
int g_612bf4;

// GLOBAL: STUNTGP_D3D 0x612cfc
DWORD g_612cfc;

// GLOBAL: STUNTGP_D3D 0x612d00
DWORD g_612d00;

// GLOBAL: STUNTGP_D3D 0x612d04
DWORD g_612d04;

// GLOBAL: STUNTGP_D3D 0x612d08
DWORD g_612d08;

void FUN_441dc0();
void FUN_441ec0();
void FUN_441f70();
void FUN_4420e0();
int FUN_4423d0();
void FUN_442490();
void FUN_442a40(int type, int duration, int delay, int end, int from, int to, float scale);
void FUN_442b60();
void FUN_442be0();

// STUB: STUNTGP_D3D 0x441d70
void FUN_441d70()
{
}

// FUNCTION: STUNTGP_D3D 0x441f00
void FUN_441f00()
{
    FUN_429510();
    FUN_4023f0();
    FUN_45f210();
    FUN_442490();
    while (g_612d00 < g_612d04)
    {
        FUN_40d860();
        FUN_43d200();
        FUN_442be0();
        FUN_441ec0();
        memcpy(g_62dcf0, g_62d480, sizeof(g_62dcf0));
    }
    FUN_462280();
    FUN_441dc0();
}

// STUB: STUNTGP_D3D 0x442120
void FUN_442120()
{
}

// STUB: STUNTGP_D3D 0x442180
void FUN_442180()
{
}

// STUB: STUNTGP_D3D 0x4427b0
void FUN_4427b0()
{
}

// FUNCTION: STUNTGP_D3D 0x442810
void FUN_442810()
{
    FUN_429510();
    FUN_4023f0();
    FUN_45f210();
    FUN_40dad0();
    FUN_442490();
    while (g_612d00 < g_612d04)
    {
        if (!FUN_4423d0())
        {
            FUN_405210();
            FUN_427140();
            FUN_45e1d0();
            FUN_415df0();
            FUN_443a80();
            FUN_418a90();
            FUN_401770();
        }
        FUN_442be0();
        FUN_447c90();
        FUN_40de30();
        FUN_441ec0();
        FUN_441f70();
    }
    FUN_446110();
    FUN_462280();
    FUN_441dc0();
}

// FUNCTION: STUNTGP_D3D 0x441dc0
void FUN_441dc0()
{
    if (g_612bec != g_612be8)
    {
        if (g_612be8 != 1 || g_498248[0].fadeActive != 1)
        {
            FUN_4420e0();
            g_612bf4 = 0;
            g_612be8 = g_612bec;
            FUN_442030();
            FUN_442a40(2, 60, 0, 60, 100, 0, 1.0f);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x441ec0
void FUN_441ec0()
{
    g_612cfc++;
    g_612d00 += g_612d08;
    if (g_612d00 < 0x10000000 && g_612d04 > 0x80000000)
    {
        g_612d00 = g_612d04;
    }
}

// FUNCTION: STUNTGP_D3D 0x441f70
void FUN_441f70()
{
    if (g_60d618 != 0)
    {
        if (--g_60d618 == 0)
        {
            FUN_45f8f0(0, 1);
        }
    }
}

// STUB: STUNTGP_D3D 0x442030
void FUN_442030()
{
}

// FUNCTION: STUNTGP_D3D 0x4420e0
void FUN_4420e0()
{
    FUN_431810();
    FUN_42eaa0();
    FUN_460af0(0);
}

// FUNCTION: STUNTGP_D3D 0x4423d0
int FUN_4423d0()
{
    if (g_61294c == 1)
    {
        if (g_612954 < 0x48a8)
        {
            g_612954++;
        }
        if (g_612970 == 1)
        {
            g_612954 = 0;
        }
    }
    if (g_60f2c4 > 0)
    {
        g_60f2c0 = 1;
        if (--g_60f2c4 == 0)
        {
            g_60f2c0 = 0;
        }
    }
    if (g_60d620 == 1)
    {
        return 1;
    }
    return g_61294c == 1;
}

// FUNCTION: STUNTGP_D3D 0x442490
void FUN_442490()
{
    if (g_DisableFramerateCorrection != 1 && g_60df9c != 1)
    {
        DWORD now = FUN_434820();
        g_612d04 = now;
        if ((DWORD)abs((int)(now - g_612d00)) > g_612d08 * 30)
        {
            g_612d00 = now - 1;
        }
    }
    else
    {
        g_612d00 = g_612d04;
        g_612d04 += g_612d08;
    }
}

// FUNCTION: STUNTGP_D3D 0x442a40
void FUN_442a40(int type, int duration, int delay, int end, int from, int to, float scale)
{
    for (int i = 0; i < 4; i++)
    {
        GameSlot *slot = &g_498248[i];
        g_4722d0 = slot;
        if (slot->active == 1)
        {
            slot->fadeActive = 1;
            slot->fadeType = type;
            slot->fadeValue = from;
            slot->fadeFrom = from;
            slot->fadeTo = to;
            slot->fadeTime = 0;
            slot->fadeDuration = duration;
            slot->fadeDelay = delay;
            slot->fadeEnd = end;
            if (scale < 1.0f)
            {
                scale -= 0.05f;
            }
            slot->fadeScale = scale;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x442b60
void FUN_442b60()
{
    if (g_4722d0->fadeActive)
    {
        int t = g_4722d0->fadeTime > g_4722d0->fadeDuration ? g_4722d0->fadeDuration : g_4722d0->fadeTime;
        g_4722d0->fadeValue = (g_4722d0->fadeTo - g_4722d0->fadeFrom) * t / g_4722d0->fadeDuration + g_4722d0->fadeFrom;
        if (g_4722d0->fadeDelay)
        {
            g_4722d0->fadeDelay--;
        }
        else
        {
            g_4722d0->fadeTime++;
        }
        if (g_4722d0->fadeEnd > 0 && g_4722d0->fadeTime >= g_4722d0->fadeEnd)
        {
            g_4722d0->fadeActive = 0;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x442be0
void FUN_442be0()
{
    for (int i = 0; i < 4; i++)
    {
        g_4722d0 = &g_498248[i];
        if (g_498248[i].active == 1)
        {
            FUN_442b60();
        }
    }
}
