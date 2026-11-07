#include "Game.h"
#include "../../d3drender.h"
#include "../../sprite.h"
#include "../../font.h"
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
#include "GameSetup.h"

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

extern DWORD g_61297c;

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

void FUN_45e4f0();

// STUB: STUNTGP_D3D 0x416050
void FUN_416050()
{
}

// FUNCTION: STUNTGP_D3D 0x449d60
void FUN_449d60()
{
}

// FUNCTION: STUNTGP_D3D 0x42e870
void FUN_42e870()
{
    if (g_62498c != g_624988)
    {
        FUN_424c30(g_62498c);
    }
    FUN_42e820();
    FUN_44fd60();
    FUN_425ad0();
    FUN_402e90();
    FUN_42dcf0();
    FUN_42e800();
    FUN_42b040();
    FUN_4277d0();
    FUN_429a40();
    g_61c508 = (g_61c508 + 1) & 0xffff;
}

// STUB: STUNTGP_D3D 0x44ae40
void FUN_44ae40()
{
}

// STUB: STUNTGP_D3D 0x401b00
void FUN_401b00()
{
}

void FUN_431830(D3DCOLOR color);

void FUN_447100();

void FUN_447280(float x, float y, float width, float height);

void FUN_446c20(float x, float y);
void FUN_446d90(unsigned int value, float x, float y, float width, float height);

// GLOBAL: STUNTGP_D3D 0x6244fc
int g_6244fc;

// GLOBAL: STUNTGP_D3D 0x624500
int g_624500;

// GLOBAL: STUNTGP_D3D 0x61b74c
int g_61b74c;

// GLOBAL: STUNTGP_D3D 0x61b754
int g_61b754;

void FUN_442c30();

void FUN_447a60();
void FUN_449e80();

// FUNCTION: STUNTGP_D3D 0x448110
void FUN_448110()
{
    g_61b740 = &g_498248[0].fx;
    g_6244fc = 0;
    g_624500 = 0;
    FUN_442c30();
    FUN_447a60();
    FUN_449e80();
}

// FUNCTION: STUNTGP_D3D 0x4473f0
void FUN_4473f0()
{
    float width;
    float x;

    if (g_612bf4 == 1 || g_612958 == 1)
    {
        return;
    }
    if (g_61294c != 1)
    {
        g_61b754 = 0;
        g_61b74c = 0;
        return;
    }
    if (!g_61b754)
    {
        FUN_430d40(15, 0x1a);
        g_61b754 = 1;
    }
    FUN_447100();
    switch (g_4835e0)
    {
    case 4:
    case 6:
        width = 323.2f;
        break;
    default:
        width = 256.0f;
        break;
    }
    x = (640.0f - width) * 0.5f;
    g_spriteDesc.flags = 2;
    g_spriteDesc.x = x;
    g_spriteDesc.y = 120.0f;
    g_spriteDesc.z = 0.96f;
    if (!g_61b754)
    {
        g_spriteDesc.u0 = 952.0f;
        g_spriteDesc.v0 = 800.0f;
        g_spriteDesc.u1 = 1016.0f;
        g_spriteDesc.v1 = 864.0f;
        g_spriteDesc.texture = 11;
        FUN_447280(x, 120.0f, width, 240.0f);
    }
    else
    {
        g_spriteDesc.u0 = 0.0f;
        g_spriteDesc.v0 = 0.0f;
        g_spriteDesc.u1 = 1024.0f;
        g_spriteDesc.v1 = 1024.0f;
        g_spriteDesc.texture = 15;
    }
    g_spriteDesc.width = width;
    g_spriteDesc.height = 240.0f;
    g_spriteDesc.blendMode = 0x20;
    FUN_432e00(&g_spriteDesc);
    if (!g_61b754)
    {
        g_spriteDesc.flags = 2;
        g_spriteDesc.x = (width - 65.0f) * 0.5f + x;
        g_spriteDesc.y = 136.0f;
        g_spriteDesc.z = 0.99f;
        g_spriteDesc.u0 = 320.0f;
        g_spriteDesc.v0 = 644.0f;
        g_spriteDesc.u1 = 580.0f;
        g_spriteDesc.v1 = 732.0f;
        g_spriteDesc.width = 65.0f;
        g_spriteDesc.height = 22.0f;
        g_spriteDesc.texture = 14;
        g_spriteDesc.blendMode = 0x20;
        FUN_432e00(&g_spriteDesc);
    }
    FUN_446c20(x, 120.0f);
    x = width - 64.0f - 12.0f - 12.8f + x + 12.8f;
    FUN_446d90(g_sfxSetting, x, 255.2f, 64.0f, 12.0f);
    FUN_446d90(g_musicSetting, x, 275.2f, 64.0f, 12.0f);
    if (g_485120[5].active == 1)
    {
        FUN_446d90(g_61297c, x, 295.2f, 64.0f, 12.0f);
    }
    if (g_61b744)
    {
        FUN_4291f0(g_6127a0[98 + g_61b744->unk01c], 1, 320.0f, 80.0f, 0.98f, 0xffff00, 2.0f, 6);
    }
}

// FUNCTION: STUNTGP_D3D 0x40de80
void FUN_40de80()
{
    if (g_473a24 > 300)
    {
        return;
    }
    if (!g_4d5b1c)
    {
        g_4d5b1c = 1;
        FUN_430d40(11, 0x1c);
        FUN_430d40(14, 0x1d);
        FUN_448110();
        return;
    }
    g_spriteDesc.flags = 2;
    g_spriteDesc.x = g_61b740->faders[1].x - 48.0f;
    g_spriteDesc.y = g_61b740->faders[1].y - 80.0f - g_4d5b18;
    g_spriteDesc.z = 0.97f;
    g_spriteDesc.u0 = 0.0f;
    g_spriteDesc.v0 = 0.0f;
    g_spriteDesc.u1 = 1024.0f;
    g_spriteDesc.v1 = 1024.0f;
    g_spriteDesc.width = 200.0f;
    g_spriteDesc.height = 200.0f;
    g_spriteDesc.texture = 14;
    g_spriteDesc.blendMode = 0x70;
    g_spriteDesc.alpha = 0xff;
    FUN_432e00(&g_spriteDesc);
    g_spriteDesc.texture = 11;
    g_spriteDesc.blendMode = 0x58;
    FUN_432e00(&g_spriteDesc);
}

// FUNCTION: STUNTGP_D3D 0x40df90
void FUN_40df90()
{
    DWORD color;

    Font_Select(1);
    color = g_612990 % 60 < 20 ? 0xff404000 : 0xffffff00;
    FUN_4291f0(g_6127a0[95], 1, g_6244fc + 320.0f, 448.0f - g_624500, 0.99f, color, 2.0f, 6);
    FUN_4291f0(g_6127a0[104], 1, g_6244fc + 320.0f, g_624500, 0.99f, color, 2.0f, 6);
}

void FUN_447fa0();

void FUN_4487d0(unsigned int index, float x, float y, float z);
void FUN_4476c0(DWORD flags, float x, float y, float z, float width, float height);

extern int g_60f2b4;

// FUNCTION: STUNTGP_D3D 0x443770
int FUN_443770()
{
    return g_60f2b4;
}

// GLOBAL: STUNTGP_D3D 0x4856c0
char *g_4856c0[6] = {"PLAYER 10", "PLAYER 20", "PLAYER 30", "PLAYER 40", "PLAYER 50", "PLAYER 60"};

// GLOBAL: STUNTGP_D3D 0x4856d8
char *g_4856d8[6] = {"4:07:13", "4:10:56", "4:11:31", "4:14:79", "4:17:01", "4:21:36"};

// GLOBAL: STUNTGP_D3D 0x4856f0
char *g_4856f0[6] = {"1:07:13", "1:10:56", "1:11:31", "1:14:79", "1:17:01", "1:21:36"};

// GLOBAL: STUNTGP_D3D 0x485708
char *g_485708[6] = {"6234567", "5234567", "4234567", "3234567", "2234567", "1234567"};

extern Car *g_612d14[6];

// GLOBAL: STUNTGP_D3D 0x60d728
DWORD g_60d728;

// FUNCTION: STUNTGP_D3D 0x449fb0
void FUN_449fb0()
{
    CarRace *race;
    int title;
    char **column;
    float rowHeight;
    float y;
    Fader *row;
    float pad;
    int place;
    int i;
    DWORD color;
    float rowX;
    float rowY;
    float width;
    float top;
    float height;
    const char *text;

    race = &g_4722d0->data->race;
    if (!race->unk1c)
    {
        return;
    }
    if (g_60d728 < 2)
    {
        g_60d728++;
        return;
    }
    if (g_4d5bb8->race.unk2c > 120)
    {
        return;
    }
    if (g_61b634 != 0x1b)
    {
        FUN_430d40(15, 0x1b);
    }
    switch (race->unk48)
    {
    case 0:
        title = 3;
        column = g_4856d8;
        rowHeight = 70.4f;
        break;
    case 1:
        title = 2;
        column = g_4856f0;
        rowHeight = 70.4f;
        break;
    case 2:
        title = 4;
        column = g_485708;
        rowHeight = 89.6f;
        break;
    }
    FUN_447fa0();
    y = 0.0f;
    row = &g_61b740->faders[12];
    Font_Select(1);
    pad = 5.0f;
    place = g_4722d0->data->unk24e4;
    for (i = 0; i < 6; i++)
    {
        if (!g_612d14[i])
        {
            break;
        }
        if (i == place && race->unk24 > 30 && !g_61b740->faders[12 + place].active)
        {
            color = 0xff404000;
        }
        else
        {
            color = 0xffffff00;
        }
        rowY = y + row->y;
        rowX = row->x;
        width = 521.60004f - (row->x - row->unk08);
        if (race->unk44)
        {
            pad += 0.5f;
            width = (g_61b740->faders[10].x - g_61b740->faders[10].unk08) * pad + width;
        }
        FUN_4487d0(i, rowX - 76.8f, rowY - 19.2f, 0.99f);
        top = rowY - 4.0f;
        FUN_4476c0(10, width, top, 0.96f, rowHeight, 35.2f);
        height = FUN_4290d0(g_4856c0[i], 1.6f);
        FUN_4476c0(9, rowX, top, 0.96f, height, 35.2f);
        FUN_4291f0(g_4856c0[i], 0, rowX, rowY, 0.99f, color, 1.6f, 6);
        FUN_4291f0(column[i], 1, width, rowY, 0.99f, color, 1.6f, 6);
        y += 51.2f;
        row++;
    }

    text = g_6127a0[1];
    rowX = g_61b740->faders[9].x;
    rowY = g_61b740->faders[9].y;
    height = FUN_4290d0(text, 1.6f) + 16.0f;
    FUN_4476c0(0x21, rowX - 16.0f, rowY - 12.0f, 0.96f, height, 51.2f);
    FUN_4291f0(text, 0, rowX, rowY, 0.99f, 0xffffff00, 1.6f, 6);

    rowX = g_61b740->faders[10].x;
    rowY = g_61b740->faders[10].y;
    text = g_6127a0[title];
    height = FUN_4290d0(text, 1.6f);
    FUN_4476c0(0x44, rowX, rowY - 12.0f, 0.96f, height, 51.2f);
    FUN_4291f0(text, 2, rowX, rowY, 0.99f, 0xffffff00, 1.6f, 6);
    Font_Select(0);

    if (race->unk24 > 30 && !g_61b740->faders[11].active)
    {
        color = 0xff404000;
    }
    else
    {
        color = 0xffffff00;
    }
    text = FUN_443770() == 2 ? g_6127a0[6] : g_6127a0[95];
    height = FUN_4290d0(text, 1.0f);
    FUN_4476c0(0x12, g_61b740->faders[11].x, g_61b740->faders[11].y - 5.0f, 0.96f, height, 26.4f);
    FUN_4291f0(text, 1, g_61b740->faders[11].x, g_61b740->faders[11].y, 0.99f, color, 1.0f, 6);
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
    Font_Select(1);
    // STRING: STUNTGP_D3D 0x4826cc
    FUN_4291f0("GAMEOVER!", 1, 320.0f, 208.0f, 0.98f, 0xffffff, 2.0f, 0);
    // STRING: STUNTGP_D3D 0x4826d8
    FUN_4291f0("PLEASE WAIT FOR RACE TO FINISH...", 1, 320.0f, 272.0f, 0.98f, 0xffffff, 2.0f, 0);
    Font_Select(0);
}

// FUNCTION: STUNTGP_D3D 0x442590
void FUN_442590()
{
    Font_Select(1);
    // STRING: STUNTGP_D3D 0x4826fc
    FUN_4291f0("NO PLAYER AVAILABLE...", 1, 320.0f, 240.0f, 0.98f, 0xffffff, 2.0f, 0);
    Font_Select(0);
}

// FUNCTION: STUNTGP_D3D 0x4425d0
void FUN_4425d0()
{
    if (g_61299c && !g_4722d0->active)
    {
        if (g_4722d0->data->race.unk18 == 1)
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
    t = g_498248[0].data->race.unk00;
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

// GLOBAL: STUNTGP_D3D 0x60d76c
int g_60d76c[4];

// GLOBAL: STUNTGP_D3D 0x60d78c
RaceEntry g_60d78c[6];

// GLOBAL: STUNTGP_D3D 0x60df74
int g_60df74;

// GLOBAL: STUNTGP_D3D 0x60df84
int g_60df84;

// GLOBAL: STUNTGP_D3D 0x60df88
int g_60df88;

// GLOBAL: STUNTGP_D3D 0x60df8c
int g_60df8c;

// GLOBAL: STUNTGP_D3D 0x60df94
int g_60df94;

// GLOBAL: STUNTGP_D3D 0x60f000
int g_60f000[4];

extern int g_60f020;

// GLOBAL: STUNTGP_D3D 0x60f284
int g_60f284;

// GLOBAL: STUNTGP_D3D 0x60f294
int g_60f294;

// GLOBAL: STUNTGP_D3D 0x60f298
int g_60f298;

// GLOBAL: STUNTGP_D3D 0x60f29c
int g_60f29c;

extern int g_60df98;

int FUN_442fd0();

// FUNCTION: STUNTGP_D3D 0x445530
void FUN_445530()
{
    g_60df94 = g_60f020;
    if (g_60df98 == 4)
    {
        g_60df74 = g_60f284;
        if (FUN_442fd0() == 1)
        {
            g_60df84 = g_60f294;
            g_60df8c = g_60f29c;
            g_60df88 = g_60f298;
        }
    }
    g_60d76c[0] = g_60f000[0];
    g_60d76c[1] = g_60f000[1];
    g_60d76c[2] = g_60f000[2];
    g_60d76c[3] = g_60f000[3];
    for (int i = 0; i < 6; i++)
    {
        RaceResult *result = &g_60d78c[i].result;
        if (g_49a1f8[i].active == 1)
        {
            result->unk04 = g_49a1f8[i].unk24e4 + 1;
            result->unk00 = g_49a1f8[i].unk23bc;
            result->unk08 = g_49a1f8[i].unk23d4;
            result->unk0c = g_49a1f8[i].unk23cc;
            result->unk10 = g_49a1f8[i].unk23d8;
            result->unk14 = g_49a1f8[i].unk23d0;
        }
    }
}

struct GhostRecord
{
    int unk00;
    int unk04;
    Unk4d5cc0 *ghost;
    unsigned int time;
};

// GLOBAL: STUNTGP_D3D 0x60d628
GhostRecord g_60d628[4];

// FUNCTION: STUNTGP_D3D 0x443330
GhostRecord *FUN_443330()
{
    GhostRecord *best = NULL;
    unsigned int bestTime = 0xffffffff;
    GhostRecord *rec = &g_60d628[2];
    for (int i = 0; i < 2; i++, rec++)
    {
        if (rec->time < bestTime && rec->time < 7200)
        {
            bestTime = rec->time;
            best = rec;
        }
    }
    return best;
}

// FUNCTION: STUNTGP_D3D 0x442fd0
int FUN_442fd0()
{
    GhostRecord *rec = FUN_443330();
    if (rec == NULL || rec->time >= g_60d628[1].time)
    {
        return 0;
    }
    Unk4d5cc0 *ghost = rec->ghost;
    g_60f298 = rec->unk04;
    g_60f29c = (int)ghost;
    g_60f294 = ghost->unk3c;
    return 1;
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
