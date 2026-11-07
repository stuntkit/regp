#include "GameUpdate.h"
#include "MenuUpdate.h"

#include <string.h>
#include "../../sound.h"
#include "../../d3drender.h"
#include "../../objects.h"
#include "../../sprite.h"

// Menu button state per player, indexed 1..4.
struct MenuInput
{
    BYTE held[8]; // 0x00, [1..7] used
    BYTE prev[8]; // 0x08
    int unk10;    // 0x10
    int unk14;    // 0x14
};

// GLOBAL: STUNTGP_D3D 0x5da2e8
MenuInput g_menuInput[5];

// GLOBAL: STUNTGP_D3D 0x5df528
int g_5df528[13];

// GLOBAL: STUNTGP_D3D 0x5df560
MenuState g_menuState;

// GLOBAL: STUNTGP_D3D 0x5ff4b8
DWORD g_5ff4b8;

// GLOBAL: STUNTGP_D3D 0x5ff8c0
int g_5ff8c0;

// GLOBAL: STUNTGP_D3D 0x5ff3e8
int g_5ff3e8;

// Screen fade in 16.16 fixed point.
// GLOBAL: STUNTGP_D3D 0x5ff3ec
int g_5ff3ec;

// GLOBAL: STUNTGP_D3D 0x5ff444
int g_5ff444;

// GLOBAL: STUNTGP_D3D 0x5ff44c
float g_5ff44c;

// GLOBAL: STUNTGP_D3D 0x5ff450
float g_5ff450;

// GLOBAL: STUNTGP_D3D 0x5ff454
float g_5ff454;

// GLOBAL: STUNTGP_D3D 0x5ff458
float g_5ff458;

// GLOBAL: STUNTGP_D3D 0x5ff45c
int g_5ff45c;

// GLOBAL: STUNTGP_D3D 0x5ff460
int g_5ff460;

// GLOBAL: STUNTGP_D3D 0x5ff464
int g_5ff464;

// GLOBAL: STUNTGP_D3D 0x5ff468
float g_5ff468;

// GLOBAL: STUNTGP_D3D 0x5ff470
float g_5ff470[6];

// GLOBAL: STUNTGP_D3D 0x5ff488
float g_5ff488[6];

// GLOBAL: STUNTGP_D3D 0x5ff4a4
int g_5ff4a4;

// GLOBAL: STUNTGP_D3D 0x5ff4ac
int g_5ff4ac;

// GLOBAL: STUNTGP_D3D 0x5ff4b4
int g_5ff4b4;

// GLOBAL: STUNTGP_D3D 0x61297c
DWORD g_61297c;

void FUN_437eb0();
void FUN_442ad0(int type, int duration, int delay, int end, int from, int to, float scale);
int FUN_43efc0();
void FUN_441210();
int FUN_452d70(int id);
void FUN_462270(int a);

// FUNCTION: STUNTGP_D3D 0x424bd0
void FUN_424bd0(float x, float y)
{
    g_576be4 = x;
    g_576be8 = y;
    x = g_576b9c + x;
    y = g_576ba0 + y;
    g_576b8c = (int)x;
    g_576b90 = (int)y;
    g_576b94 = x;
    g_576b98 = y;
}

// STUB: STUNTGP_D3D 0x434b50
void FUN_434b50()
{
}

// FUNCTION: STUNTGP_D3D 0x436eb0
void FUN_436eb0()
{
    memset(g_menuInput, 0, sizeof(g_menuInput));
}

// FUNCTION: STUNTGP_D3D 0x436ed0
void FUN_436ed0()
{
    for (int i = 1; i < 5; i++)
    {
        memcpy(g_menuInput[i].prev, g_menuInput[i].held, 8);
    }
    for (int j = 1; j < 5; j++)
    {
        FUN_436f00(j);
    }
}

// FUNCTION: STUNTGP_D3D 0x436f00
void FUN_436f00(int player)
{
    MenuInput *in = &g_menuInput[player];
    if (FUN_437090(player))
    {
        for (int i = 1; i < 8; i++)
        {
            in->held[i] = FUN_436f60(g_62d580[player - 1].keys, i);
        }
    }
    else
    {
        memset(&in->held[1], 0, 7);
    }
}

// FUNCTION: STUNTGP_D3D 0x436f60
BYTE FUN_436f60(BYTE *keys, int button)
{
    switch (button)
    {
    case 1:
        return keys[2];
    case 2:
        return keys[3];
    case 3:
        return keys[0];
    case 4:
        return keys[1];
    case 5:
        return keys[6];
    case 6:
        return keys[4];
    case 7:
        return keys[5];
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437090
int FUN_437090(int player)
{
    if (g_62d580[player - 1].active)
    {
        switch (g_62d580[player - 1].mode)
        {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            return 5;
        }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437360
int FUN_437360(int track)
{
    switch (track)
    {
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 4;
    case 4:
        return 1;
    case 5:
        return 1;
    case 6:
        return 1;
    case 7:
        return 1;
    case 8:
        return 2;
    case 9:
        return 4;
    case 10:
        return 1;
    case 11:
        return 1;
    case 12:
        return 3;
    case 13:
        return 4;
    case 14:
        return 1;
    case 15:
        return 1;
    case 16:
        return 2;
    case 17:
        return 1;
    case 18:
        return 3;
    case 19:
        return 2;
    case 20:
        return 3;
    case 21:
        return 1;
    case 22:
        return 1;
    case 23:
        return 3;
    case 24:
        return 3;
    case 25:
        return 5;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437da0
int FUN_437da0(int track)
{
    switch (track)
    {
    case 1:
    case 2:
    case 3:
    case 8:
    case 9:
    case 13:
    case 16:
    case 19:
        return 30000;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437eb0
void FUN_437eb0()
{
    FUN_441210();
}

// FUNCTION: STUNTGP_D3D 0x439e30
void FUN_439e30()
{
    memset(g_5df528, 0, sizeof(g_5df528));
}

// FUNCTION: STUNTGP_D3D 0x43c000
void FUN_43c000()
{
    FUN_424bd0((float)g_menuState.offsetX, (float)g_menuState.offsetY);
    g_sfxSetting = g_menuState.sfx;
    g_musicSetting = g_menuState.music;
    if (!g_menuState.music)
    {
        g_musicSetting = 1;
    }
    g_61297c = g_menuState.unk0084;
    FUN_462270(g_menuState.unk4240);
    Sound_ApplyVolumes();
}

// STUB: STUNTGP_D3D 0x43c060
void FUN_43c060()
{
}

// STUB: STUNTGP_D3D 0x43c130
void FUN_43c130()
{
}

// STUB: STUNTGP_D3D 0x43c370
void FUN_43c370()
{
}

// FUNCTION: STUNTGP_D3D 0x43d200
void FUN_43d200()
{
    FUN_436ed0();
    FUN_43eff0();
    FUN_437eb0();
    FUN_43c000();
    if (g_menuState.unk0090 && g_menuState.unk0090 != g_menuState.unk4258 && FUN_43efc0() && !FUN_452d70(g_menuState.unk0090))
    {
        g_menuState.unk0090 = g_menuState.unk4258;
    }
}

// FUNCTION: STUNTGP_D3D 0x43d790
int FUN_43d790(int value, int min, int max)
{
    if (value < min)
    {
        return min;
    }
    if (value > max)
    {
        return max;
    }
    return value;
}

// STUB: STUNTGP_D3D 0x43d810
float FUN_43d810(float current, float target, float rate)
{
    return current;
}

// STUB: STUNTGP_D3D 0x43d280
void FUN_43d280()
{
}

// FUNCTION: STUNTGP_D3D 0x43dd10
void FUN_43dd10(DWORD color)
{
    DWORD r = color & 0xff;
    DWORD g = color & 0xff00;
    BYTE b = ((BYTE *)&color)[2];
    g_5ff4b8 = b | (r << 16) | g;
}

// FUNCTION: STUNTGP_D3D 0x43dd70
int FUN_43dd70()
{
    g_5ff460 = 0;
    return g_5ff464 != 0;
}

// STUB: STUNTGP_D3D 0x43dda0
void FUN_43dda0()
{
}

// FUNCTION: STUNTGP_D3D 0x43de40
void FUN_43de40()
{
    g_5ff4ac = 0;
}

// STUB: STUNTGP_D3D 0x43dee0
void FUN_43dee0()
{
}

// FUNCTION: STUNTGP_D3D 0x43efc0
int FUN_43efc0()
{
    return g_5ff3ec * 100 / 0x10000 > 95;
}

// FUNCTION: STUNTGP_D3D 0x43eff0
void FUN_43eff0()
{
    int fade = g_5ff3ec * 100 / 0x10000;
    if (g_5ff4b4)
    {
        FUN_43dd70();
        FUN_440880(2);
        FUN_4411c0();
        FUN_43de40();
        FUN_43ef10(1, 1);
        g_5ff4b4 = 0;
        return;
    }
    g_5ff4a4 = 0;
    g_5ff444 = 1;
    g_5ff454 += g_5ff44c * (1.0f / 60.0f);
    g_5ff458 += g_5ff450 * (1.0f / 60.0f);
    FUN_43f610();
    g_5ff444 = 0;
    if (fade < g_5ff464)
    {
        fade = g_5ff464;
    }
    FUN_442ad0(2, 1, 0, 0, fade, fade, 1.0f);
    g_5ff444 = 1;
    if (g_5ff3f8)
    {
        FUN_43f310(g_5ff3f8);
    }
    else if (g_5ff3f0)
    {
        FUN_43f310(g_5ff3f0);
    }
    g_5ff444 = 0;
    switch (g_5ff3e8)
    {
    case 3:
        if (g_5ff3ec > 0)
        {
            g_5ff3ec = FUN_43d790(g_5ff3ec - 0x2492, 0, 0x10000);
        }
        else
        {
            g_5ff3e8 = 1;
        }
        break;
    case 2:
        if (g_5ff3ec < 0x10000)
        {
            g_5ff3ec = FUN_43d790(g_5ff3ec + 0x2492, 0, 0x10000);
        }
        else
        {
            if (g_5ff3f0 && !g_5ff3f4)
            {
                g_5ff3f0->destroy(g_5ff3f0);
                Pool_Free(g_5ff3f0);
            }
            g_5ff3f0 = g_5ff3f8;
            g_5ff3f4 = g_5ff3fc;
            g_5ff3f8 = NULL;
            g_5ff3fc = FALSE;
            FUN_43dee0();
            g_5ff3f0->message(g_5ff3f0, 0x13, 0);
            g_5ff3e8 = 3;
            g_5ff468 = 0.0f;
        }
        break;
    }
    g_5ff468 = FUN_43d810(g_5ff468, 1.0f, 0.005f);
    if (!g_5ff4a4)
    {
        if (g_5ff3f0)
        {
            g_5ff3f0->message(g_5ff3f0, 2, 0);
        }
        if (g_5ff3f8)
        {
            g_5ff3f8->message(g_5ff3f8, 2, 0);
        }
        g_5ff444 = 1;
        if (g_5ff3f0)
        {
            if (g_5ff3f8)
            {
                g_5ff3f8->message(g_5ff3f8, 1, 0);
            }
            else
            {
                g_5ff3f0->message(g_5ff3f0, 1, 0);
            }
        }
        g_5ff444 = 0;
    }
    g_5ff470[0] = FUN_43d810(g_5ff470[0], g_5ff488[0], 0.001f);
    g_5ff470[1] = FUN_43d810(g_5ff470[1], g_5ff488[1], 0.001f);
    g_5ff470[2] = FUN_43d810(g_5ff470[2], g_5ff488[2], 0.001f);
    g_5ff470[3] = FUN_43d810(g_5ff470[3], g_5ff488[3], 0.001f);
    g_5ff470[4] = FUN_43d810(g_5ff470[4], g_5ff488[4], 0.001f);
    g_5ff470[5] = FUN_43d810(g_5ff470[5], g_5ff488[5], 0.001f);
    g_5ff45c++;
    g_5ff460++;
}

// STUB: STUNTGP_D3D 0x43f310
void FUN_43f310(PoolObject *screen)
{
}

// STUB: STUNTGP_D3D 0x43f610
void FUN_43f610()
{
}

// STUB: STUNTGP_D3D 0x440c40
int FUN_440c40(int id)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x4408e0
void FUN_4408e0()
{
    g_5ff8c0 = 1;
}

// STUB: STUNTGP_D3D 0x440770
void FUN_440770(int a, int b)
{
}

// FUNCTION: STUNTGP_D3D 0x440880
void FUN_440880(int a)
{
    FUN_440770(a, 0);
}

// STUB: STUNTGP_D3D 0x440ae0
void FUN_440ae0()
{
}

// FUNCTION: STUNTGP_D3D 0x441210
void FUN_441210()
{
}

// FUNCTION: STUNTGP_D3D 0x452d70
int FUN_452d70(int id)
{
    if (FUN_440c40(id) >= 0)
    {
        g_menuState.unk0090 = id;
    }
    return 1;
}
