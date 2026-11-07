#include "Game.h"
#include "../../d3drender.h"
#include "../../sprite.h"
#include "game_state.h"

// GLOBAL: STUNTGP_D3D 0x612984
int g_frameCount = 0;

// GLOBAL: STUNTGP_D3D 0x61b630
int g_61b630 = 0;

#include "../../input.h"
#include "../../mem.h"
#include "../../objects.h"
#include "../../sound.h"
#include "../../surface.h"
#include "../../windowInit.h"
#include "io_wad.h"

// GLOBAL: STUNTGP_D3D 0x60d61c
int g_60d61c;

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

extern int g_61297c;

extern int g_60df9c;

// GLOBAL: STUNTGP_D3D 0x4d5b20
int g_4d5b20;

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

// GLOBAL: STUNTGP_D3D 0x4722d0
GameSlot *g_4722d0 = g_498248;

// GLOBAL: STUNTGP_D3D 0x498248
GameSlot g_498248[4];

// GLOBAL: STUNTGP_D3D 0x612bf0
int g_612bf0;

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
void FUN_441e20();
void FUN_441ec0();
void FUN_445530();
void FUN_441f70();
void FUN_4420e0();
int FUN_4423d0();
void FUN_442490();
void FUN_442ad0(int type, int duration, int delay, int end, int from, int to, float scale);
void FUN_442a40(int type, int duration, int delay, int end, int from, int to, float scale);
void FUN_442b60();
void FUN_442be0();

// FUNCTION: STUNTGP_D3D 0x441d70
void FUN_441d70()
{
    if (g_612be8 == 2)
    {
        g_frameCount++;
        FUN_402e90();
        FUN_432a60();
        FUN_433ee0();
        FUN_4328c0(0);
        FUN_43d250();
        FUN_442a00();
        FUN_442a20();
        FUN_431a80();
        FUN_44fd60();
        FUN_433f20();
    }
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
    Scores_LoadIfNeeded();
    Gameplay_LoadIfNeeded();
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

// FUNCTION: STUNTGP_D3D 0x442200
void FUN_442200()
{
    if (g_61294c == 1 && g_612954 >= 18000)
    {
        DWORD alpha = (g_612954 - 18000) >> 1;
        if (alpha > 192)
        {
            alpha = 192;
        }
        g_spriteDesc.flags = 2;
        g_spriteDesc.x = 0.0f;
        g_spriteDesc.y = 0.0f;
        g_spriteDesc.z = 1.0f;
        g_spriteDesc.width = 640.0f;
        g_spriteDesc.height = 480.0f;
        g_spriteDesc.blendMode = 0x48;
        g_spriteDesc.alpha = alpha;
        g_spriteDesc.u0 = 128.0f;
        g_spriteDesc.v0 = 128.0f;
        g_spriteDesc.u1 = 128.0f;
        g_spriteDesc.v1 = 128.0f;
        g_spriteDesc.texture = 10;
        FUN_432e00(&g_spriteDesc);
    }
}

// FUNCTION: STUNTGP_D3D 0x4421f0
int FUN_4421f0()
{
    return 0;
}

// STUB: STUNTGP_D3D 0x418180
void FUN_418180()
{
}

// STUB: STUNTGP_D3D 0x45e4f0
void FUN_45e4f0()
{
}

// STUB: STUNTGP_D3D 0x416050
void FUN_416050()
{
}

// STUB: STUNTGP_D3D 0x449d60
void FUN_449d60()
{
}

// STUB: STUNTGP_D3D 0x428f70
void FUN_428f70(DWORD font)
{
}

// STUB: STUNTGP_D3D 0x4291f0
void FUN_4291f0(const char *text, int align, float x, float y, float z, DWORD color, float scale, int flags)
{
}

// STUB: STUNTGP_D3D 0x42e870
void FUN_42e870()
{
}

// STUB: STUNTGP_D3D 0x433f40
void FUN_433f40()
{
}

// STUB: STUNTGP_D3D 0x44ae40
void FUN_44ae40()
{
}

// STUB: STUNTGP_D3D 0x401b00
void FUN_401b00()
{
}

// STUB: STUNTGP_D3D 0x431830
void FUN_431830(int a)
{
}

// STUB: STUNTGP_D3D 0x4473f0
void FUN_4473f0()
{
}

// STUB: STUNTGP_D3D 0x449fb0
void FUN_449fb0()
{
}

// STUB: STUNTGP_D3D 0x40de80
void FUN_40de80()
{
}

// STUB: STUNTGP_D3D 0x40df90
void FUN_40df90()
{
}

// FUNCTION: STUNTGP_D3D 0x442500
void FUN_442500()
{
    FUN_418180();
    FUN_45e4f0();
    FUN_416050();
    FUN_449d60();
}

// FUNCTION: STUNTGP_D3D 0x442520
void FUN_442520()
{
    FUN_428f70(1);
    // STRING: STUNTGP_D3D 0x4826cc
    FUN_4291f0("GAMEOVER!", 1, 320.0f, 208.0f, 0.98f, 0xffffff, 2.0f, 0);
    // STRING: STUNTGP_D3D 0x4826d8
    FUN_4291f0("PLEASE WAIT FOR RACE TO FINISH...", 1, 320.0f, 272.0f, 0.98f, 0xffffff, 2.0f, 0);
    FUN_428f70(0);
}

// FUNCTION: STUNTGP_D3D 0x442590
void FUN_442590()
{
    FUN_428f70(1);
    // STRING: STUNTGP_D3D 0x4826fc
    FUN_4291f0("NO PLAYER AVAILABLE...", 1, 320.0f, 240.0f, 0.98f, 0xffffff, 2.0f, 0);
    FUN_428f70(0);
}

// FUNCTION: STUNTGP_D3D 0x4425d0
void FUN_4425d0()
{
    if (g_61299c && !g_4722d0->active)
    {
        if (g_4722d0->data->unk76a0 == 1)
        {
            FUN_442520();
        }
        else
        {
            FUN_442590();
        }
        return;
    }
    FUN_402e90();
    FUN_442500();
    FUN_42e870();
    FUN_433f40();
    FUN_42e420();
    FUN_442a00();
    FUN_44ae40();
    FUN_442a20();
    FUN_401b00();
    FUN_432f60();
    FUN_431830(0);
}

// FUNCTION: STUNTGP_D3D 0x449b50
void FUN_449b50()
{
    DWORD t;
    DWORD alpha;

    if (g_61294c == 1)
    {
        return;
    }
    t = g_498248[0].data->unk7688;
    if (t == 0 || t >= 240)
    {
        return;
    }
    if (g_61b634 != 0x10 && g_61b634 != 0x11 && g_61b634 != 0x12 && g_61b634 != 0x13)
    {
        return;
    }
    if ((t <= 30 || t >= 120) && t % 60 < 30)
    {
        alpha = t % 60 * 192 / 30;
    }
    else
    {
        alpha = 192;
    }
    g_spriteDesc.flags = 2;
    g_spriteDesc.x = 217.6f;
    g_spriteDesc.y = 73.6f;
    g_spriteDesc.z = 0.98f;
    g_spriteDesc.u0 = 0.0f;
    g_spriteDesc.v0 = 0.0f;
    g_spriteDesc.u1 = 1024.0f;
    g_spriteDesc.v1 = 1024.0f;
    g_spriteDesc.width = 204.8f;
    g_spriteDesc.height = 204.8f;
    g_spriteDesc.texture = 15;
    g_spriteDesc.color = 0;
    g_spriteDesc.blendMode = 0x48;
    g_spriteDesc.alpha = alpha;
    FUN_432e00(&g_spriteDesc);
}

// FUNCTION: STUNTGP_D3D 0x40e030
void FUN_40e030()
{
    if (g_61299c == 1)
    {
        FUN_40de80();
        FUN_40df90();
    }
}

// FUNCTION: STUNTGP_D3D 0x442640
void FUN_442640()
{
    switch (g_576be0)
    {
    case 0:
        FUN_424c30(1);
        FUN_4425d0();
        break;
    case 1:
        g_4722d0 = &g_498248[0];
        FUN_424c30(6);
        FUN_4425d0();
        g_4722d0 = &g_498248[1];
        FUN_424c30(7);
        FUN_4425d0();
        break;
    case 2:
        g_4722d0 = &g_498248[0];
        FUN_424c30(8);
        FUN_4425d0();
        g_4722d0 = &g_498248[1];
        FUN_424c30(9);
        FUN_4425d0();
        break;
    case 3:
        g_4722d0 = &g_498248[0];
        FUN_424c30(10);
        FUN_4425d0();
        g_4722d0 = &g_498248[1];
        FUN_424c30(11);
        FUN_4425d0();
        g_4722d0 = &g_498248[2];
        FUN_424c30(12);
        FUN_4425d0();
        break;
    case 4:
        g_4722d0 = &g_498248[0];
        FUN_424c30(13);
        FUN_4425d0();
        g_4722d0 = &g_498248[1];
        FUN_424c30(14);
        FUN_4425d0();
        g_4722d0 = &g_498248[2];
        FUN_424c30(15);
        FUN_4425d0();
        g_4722d0 = &g_498248[3];
        FUN_424c30(16);
        FUN_4425d0();
        break;
    }
    FUN_424c30(1);
    FUN_402580();
    g_61b740 = &g_4722d0->fx;
    FUN_4473f0();
    FUN_449fb0();
    FUN_449b50();
    FUN_40e030();
    FUN_442200();
}

// FUNCTION: STUNTGP_D3D 0x4427b0
void FUN_4427b0()
{
    if (g_612be8 == 1)
    {
        g_frameCount++;
        if (FUN_4421f0() != 1)
        {
            FUN_432a60();
            FUN_433ee0();
            if (g_576bd8 == 1 || g_576be0 != 0)
            {
                FUN_4328c0(0);
            }
            FUN_442640();
            FUN_42e420();
            FUN_432f60();
            FUN_431a80();
            FUN_433f20();
        }
    }
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

// FUNCTION: STUNTGP_D3D 0x441e20
void FUN_441e20()
{
    if (g_612bf4 != 1)
    {
        if (g_612be8 == 1)
        {
            g_612bec = 2;
            FUN_445530();
            if (g_612bf0 != 1)
            {
                if (g_61294c == 1)
                {
                    FUN_442a40(2, 60, 0, 60, 60, 100, 1.0f);
                }
                else
                {
                    FUN_442a40(2, 60, 0, 60, 0, 100, 1.0f);
                }
            }
            FUN_460ca0();
            FUN_45f8e0(0, -5);
            g_612cf8 = 0;
            g_612bf4 = 1;
        }
        else
        {
            g_612bec = 1;
            g_612bf4 = 1;
            g_612cf8 = 0;
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

// STUB: STUNTGP_D3D 0x445530
void FUN_445530()
{
}

// FUNCTION: STUNTGP_D3D 0x4420e0
void FUN_4420e0()
{
    FUN_431810();
    FUN_42eaa0();
    FUN_460af0(0);
}

// FUNCTION: STUNTGP_D3D 0x4422c0
void FUN_4422c0()
{
    if (g_60f2c0 != 1)
    {
        g_61294c = 1;
        g_612954 = 0;
        for (int i = 0; i < 4; i++)
        {
            g_4722d0 = &g_498248[i];
            if (g_498248[i].active == 1 && g_498248[i].data->unk24e0 != 1)
            {
                FUN_442ad0(2, 60, 0, 0, 0, 60, 0.96f);
            }
        }
        FUN_447c30(0);
        FUN_41bdd0();
        FUN_460dd0();
        FUN_45fa00();
    }
}

// FUNCTION: STUNTGP_D3D 0x442350
void FUN_442350()
{
    for (int i = 0; i < 4; i++)
    {
        g_4722d0 = &g_498248[i];
        if (g_498248[i].active == 1 && g_498248[i].data->unk24e0 != 1)
        {
            FUN_442ad0(2, 60, 0, 60, 60, 0, 0.96f);
        }
    }
    FUN_447bd0(0);
    FUN_460cb0(0);
    FUN_45fa30();
    g_61294c = 0;
    g_61295c = 0;
    g_612958 = 0;
    g_61b744 = NULL;
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
        DWORD now = Timer_GetCounter();
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

// FUNCTION: STUNTGP_D3D 0x442ad0
void FUN_442ad0(int type, int duration, int delay, int end, int from, int to, float scale)
{
    g_4722d0->fadeActive = 1;
    g_4722d0->fadeType = type;
    g_4722d0->fadeValue = from;
    g_4722d0->fadeFrom = from;
    g_4722d0->fadeTo = to;
    g_4722d0->fadeTime = 0;
    g_4722d0->fadeDuration = duration;
    g_4722d0->fadeDelay = delay;
    g_4722d0->fadeEnd = end;
    if (scale < 1.0f)
    {
        g_4722d0->fadeScale = scale - 0.05f;
    }
    else
    {
        g_4722d0->fadeScale = scale;
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

// FUNCTION: STUNTGP_D3D 0x4428a0
void FUN_4428a0()
{
    if (g_61294c == 1 && g_612958 == 1)
    {
        return;
    }
    GameSlot *gs = g_4722d0;
    if (gs->fadeActive == 0 || gs->fadeValue < 1)
    {
        return;
    }
    DWORD alpha = gs->fadeValue * 265 / 100;
    if (alpha > 255)
    {
        alpha = 255;
    }
    g_spriteDesc.flags = 2;
    g_spriteDesc.x = 0.0f;
    g_spriteDesc.y = 0.0f;
    g_spriteDesc.z = gs->fadeScale;
    g_spriteDesc.width = 640.0f;
    g_spriteDesc.height = 480.0f;
    g_spriteDesc.blendMode = 0x48;
    g_spriteDesc.alpha = alpha;
    switch (gs->fadeType)
    {
    case 1:
        g_spriteDesc.u0 = 384.0f;
        g_spriteDesc.v0 = 128.0f;
        g_spriteDesc.u1 = 384.0f;
        g_spriteDesc.v1 = 128.0f;
        g_spriteDesc.texture = g_61b630 == 1 ? 0 : 10;
        break;
    case 2:
        g_spriteDesc.u0 = 128.0f;
        g_spriteDesc.v0 = 128.0f;
        g_spriteDesc.u1 = 128.0f;
        g_spriteDesc.v1 = 128.0f;
        g_spriteDesc.texture = g_61b630 == 1 ? 0 : 10;
        break;
    }
    FUN_432e00(&g_spriteDesc);
}

// FUNCTION: STUNTGP_D3D 0x442a00
void FUN_442a00()
{
    if (g_4722d0->fadeActive == 1 && g_4722d0->fadeScale != 1.0f)
    {
        FUN_4428a0();
    }
}

// FUNCTION: STUNTGP_D3D 0x442a20
void FUN_442a20()
{
    if (g_4722d0->fadeActive == 1 && g_4722d0->fadeScale == 1.0f)
    {
        FUN_4428a0();
    }
}
