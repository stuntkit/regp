#include "GameUpdate.h"
#include "MenuUpdate.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"
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
FrontEnd g_frontEnd;

// GLOBAL: STUNTGP_D3D 0x61297c
DWORD g_61297c;

void FUN_437eb0();
void FUN_442ad0(int type, int duration, int delay, int end, int from, int to, float scale);
int FUN_43efc0();
void FUN_441210();
int FUN_452d70(int id);
void FUN_462270(int a);
int FUN_462260();
int FUN_424a80();
void FUN_424a90(int mode);
extern Unk4d5cc0 *g_60df90;
float FUN_43d9e0(float value);
int FUN_436fc0(int player, int button);
int FUN_436fd0(int player, int button);
void FUN_43f3e0(PoolObject *screen, int player);
int FUN_43f5e0(int player);
int FUN_4407a0(int id);

// FUNCTION: STUNTGP_D3D 0x424a80
int FUN_424a80()
{
    return 2;
}

// FUNCTION: STUNTGP_D3D 0x424a90
void FUN_424a90(int mode)
{
}

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

// FUNCTION: STUNTGP_D3D 0x436fc0
int FUN_436fc0(int player, int button)
{
    return (char)g_menuInput[player].held[button];
}

// FUNCTION: STUNTGP_D3D 0x436fd0
int FUN_436fd0(int player, int button)
{
    if (g_menuInput[player].held[button] && !g_menuInput[player].prev[button])
    {
        return 1;
    }
    return 0;
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

// FUNCTION: STUNTGP_D3D 0x43c060
void FUN_43c060()
{
    memset(&g_menuState, 0, offsetof(MenuState, saved));
    g_menuState.unk00d4 = 0;
    g_menuState.sfx = 100;
    g_menuState.unk0084 = 100;
    g_menuState.unk00d8 = 0;
    g_menuState.unk00dc = 0;
    g_menuState.unk00e0 = 0;
    g_menuState.unk00e4 = 0;
    g_menuState.unk00e8 = 0;
    g_menuState.unk0070 = 0;
    g_menuState.unk0074 = 0;
    g_menuState.unk0078 = 1;
    g_menuState.music = 80;
    g_menuState.offsetX = 0;
    g_menuState.offsetY = 0;
    g_menuState.unk0090 = 0;
    for (int i = 0; i < 5; i++)
    {
        g_menuState.unk0098[i].unk00 = 0;
        g_menuState.unk0098[i].unk04 = 0;
        g_menuState.unk0098[i].unk08 = 0;
    }
    g_menuState.unk13148 = g_60df90;
    g_menuState.unk4240 = FUN_462260();
    if (!g_menuState.unk4240)
    {
        g_menuState.unk4240 = 1;
    }
    FUN_462270(g_menuState.unk4240);
    g_menuState.unk0094 = FUN_424a80();
    FUN_424a90(g_menuState.unk0094);
}

// Blank initials; each reset site has its own copy.
// GLOBAL: STUNTGP_D3D 0x479420
char g_479420[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479424
char g_479424[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479428
char g_479428[4] = "...";

// GLOBAL: STUNTGP_D3D 0x47942c
char g_47942c[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479430
char g_479430[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479434
char g_479434[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479438
char g_479438[4] = "...";

// GLOBAL: STUNTGP_D3D 0x47943c
char g_47943c[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479440
char g_479440[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479444
char g_479444[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479448
char g_479448[4] = "...";

// GLOBAL: STUNTGP_D3D 0x47944c
char g_47944c[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479450
char g_479450[4] = "...";

// FUNCTION: STUNTGP_D3D 0x43c130
void FUN_43c130()
{
    int i;
    int j;

    for (i = 0; i < 19; i++)
    {
        g_menuState.unk0114[i][0].time = 7200;
        memcpy(g_menuState.unk0114[i][0].name, g_479420, 3);
        g_menuState.unk0114[i][1].time = 36000;
        memcpy(g_menuState.unk0114[i][1].name, g_479424, 3);
        g_menuState.unk0114[i][2].time = 0;
        memcpy(g_menuState.unk0114[i][2].name, g_479428, 3);
        g_menuState.unk0114[i][3].time = 0;
        memcpy(g_menuState.unk0114[i][3].name, g_47942c, 3);
    }
    for (i = 0; i < 100; i++)
    {
        g_menuState.unk0374[i].time = 0;
        memcpy(g_menuState.unk0374[i].name, g_479430, 3);
    }
    for (i = 0; i < 100; i++)
    {
        g_menuState.unk1dfc[i].time = 0;
        memcpy(g_menuState.unk1dfc[i].name, g_479434, 3);
    }
    for (i = 0; i < 25; i++)
    {
        g_menuState.unk0694[i].unk00 = 0;
        for (j = 0; j < 10; j++)
        {
            g_menuState.unk0694[i].entries[j].time = 7200;
            memcpy(g_menuState.unk0694[i].entries[j].name, g_479438, 3);
        }
    }
    for (i = 0; i < 25; i++)
    {
        memcpy(g_menuState.unk1a1c[i][0].name, g_47943c, 3);
        g_menuState.unk1a1c[i][0].time = 7200;
        memcpy(g_menuState.unk1a1c[i][1].name, g_479440, 3);
        g_menuState.unk1a1c[i][1].time = 36000;
        memcpy(g_menuState.unk1a1c[i][2].name, g_479444, 3);
        g_menuState.unk1a1c[i][2].time = 0;
        memcpy(g_menuState.unk1a1c[i][3].name, g_479448, 3);
        g_menuState.unk1a1c[i][3].time = 0;
    }
    for (i = 0; i < 10; i++)
    {
        memcpy(g_menuState.unk1d5c[i].name, g_47944c, 3);
        g_menuState.unk1d5c[i].time = 0;
    }
    for (i = 0; i < 10; i++)
    {
        memcpy(g_menuState.unk1dac[i].name, g_479450, 3);
        g_menuState.unk1dac[i].time = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x43c370
void FUN_43c370()
{
    memset(g_menuState.unlocked, 0, sizeof(g_menuState.unlocked));
    g_menuState.unlocked[1] = 1;
    g_menuState.unlocked[4] = 1;
    g_menuState.unlocked[7] = 1;
    g_menuState.unlocked[8] = 1;
    g_menuState.unlocked[9] = 1;
    g_menuState.unlocked[10] = 1;
    g_menuState.unlocked[11] = 1;
    g_menuState.unlocked[15] = 1;
    g_menuState.unlocked[21] = 1;
    for (int i = 1; i < 25; i++)
    {
        int type = FUN_437360(i);
        if (type > 0 && type <= 2)
        {
            g_menuState.unlocked[24 + i] = 0;
        }
        else
        {
            g_menuState.unlocked[24 + i] = 1;
        }
    }
    g_menuState.unlocked[30] = 1;
    g_menuState.unlocked[35] = 1;
    g_menuState.unlocked[47] = 1;
    FUN_43c400();
}

// FUNCTION: STUNTGP_D3D 0x43c400
void FUN_43c400()
{
    memcpy(g_menuState.unlockedSaved, g_menuState.unlocked, sizeof(g_menuState.unlockedSaved));
    memcpy(g_menuState.saved, g_menuState.unlocked, sizeof(g_menuState.saved));
}

// FUNCTION: STUNTGP_D3D 0x43d200
void FUN_43d200()
{
    FUN_436ed0();
    FUN_43eff0();
    FUN_437eb0();
    FUN_43c000();
    if (g_menuState.unk0090 && g_menuState.unk0090 != g_menuState.language && FUN_43efc0() && !FUN_452d70(g_menuState.unk0090))
    {
        g_menuState.unk0090 = g_menuState.language;
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

// FUNCTION: STUNTGP_D3D 0x43d810
float FUN_43d810(float current, float target, float rate)
{
    float dist = FUN_43d9e0(target - current);
    if (dist != 0.0f)
    {
        float step = dist * 0.1f + rate;
        if (dist > step)
        {
            if (target < current)
            {
                step = -step;
            }
            return step + current;
        }
        return target;
    }
    return current;
}

// FUNCTION: STUNTGP_D3D 0x43d9e0
float FUN_43d9e0(float value)
{
    return value < 0.0f ? -value : value;
}

// Reads the detail level and language overrides next to the executable.
// FUNCTION: STUNTGP_D3D 0x43d280
void FUN_43d280()
{
    char path[256];
    FILE *file;
    // STRING: STUNTGP_D3D 0x4795f4
    sprintf(path, "%s\\detail.cfg", g_GameDirectory);
    // STRING: STUNTGP_D3D 0x479604
    file = fopen(path, "r");
    if (file)
    {
        // STRING: STUNTGP_D3D 0x479608
        fscanf(file, "%d", &g_menuState.unk0084);
        int detail = FUN_43d790(g_menuState.unk0084, 0, 100);
        g_menuState.unk0084 = detail - detail % 10;
        fclose(file);
    }
    // STRING: STUNTGP_D3D 0x47960c
    sprintf(path, "%s\\language.cfg", g_GameDirectory);
    // STRING: STUNTGP_D3D 0x47961c
    file = fopen(path, "r");
    if (file)
    {
        // STRING: STUNTGP_D3D 0x479620
        fscanf(file, "%d", &g_menuState.unk0090);
        if (g_menuState.unk0090 <= 0 || g_menuState.unk0090 >= 9)
        {
            g_menuState.unk0090 = 0;
        }
        fclose(file);
    }
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
    g_frontEnd.unk78 = 0;
    return g_frontEnd.unk7c != 0;
}

// FUNCTION: STUNTGP_D3D 0x43dda0
void FUN_43dda0()
{
    memset(&g_frontEnd, 0, sizeof(g_frontEnd));
    g_frontEnd.fade = 0x10000;
    g_frontEnd.state = 1;
    g_frontEnd.screen = NULL;
    g_frontEnd.screenStatic = FALSE;
    g_frontEnd.nextScreen = NULL;
    g_frontEnd.nextScreenStatic = FALSE;
    g_frontEnd.objectCount = 0;
    g_frontEnd.unk5c = 1;
    g_frontEnd.unk60 = 0;
    g_frontEnd.unk64 = 0.0f;
    g_frontEnd.unk68 = 0.0f;
    g_frontEnd.unk6c = 0.0f;
    g_frontEnd.unk70 = 0.0f;
    g_frontEnd.unk74 = 0;
    g_frontEnd.unk78 = 0;
    g_frontEnd.unk7c = 0;
    g_frontEnd.unk80 = 0.0f;
    g_frontEnd.unk84 = 0;
    g_frontEnd.lockedPlayer = 0;
    g_frontEnd.unkbc = 0;
    g_frontEnd.unkc0 = 0;
    g_frontEnd.musicTrack = 0;
    g_frontEnd.unkcc = 0;
    FUN_43dee0();
}

// FUNCTION: STUNTGP_D3D 0x43de40
void FUN_43de40()
{
    g_frontEnd.musicTrack = 0;
}

// FUNCTION: STUNTGP_D3D 0x43dee0
void FUN_43dee0()
{
    g_frontEnd.unk88[0] = 0.0f;
    g_frontEnd.unk88[1] = 0.0f;
    g_frontEnd.unk88[2] = 0.0f;
    g_frontEnd.unk88[3] = 0.0f;
    g_frontEnd.unk88[4] = 0.0f;
    g_frontEnd.unk88[5] = 0.0f;
    g_frontEnd.unka0[0] = 0.0f;
    g_frontEnd.unka0[1] = 0.0f;
    g_frontEnd.unka0[2] = 0.0f;
    g_frontEnd.unka0[3] = 0.0f;
    g_frontEnd.unka0[4] = 0.0f;
    g_frontEnd.unka0[5] = 0.0f;
}

// FUNCTION: STUNTGP_D3D 0x43efc0
int FUN_43efc0()
{
    return g_frontEnd.fade * 100 / 0x10000 > 95;
}

// FUNCTION: STUNTGP_D3D 0x43eff0
void FUN_43eff0()
{
    int fade = g_frontEnd.fade * 100 / 0x10000;
    if (g_frontEnd.unkcc)
    {
        FUN_43dd70();
        FUN_440880(2);
        FUN_4411c0();
        FUN_43de40();
        FUN_43ef10(1, 1);
        g_frontEnd.unkcc = 0;
        return;
    }
    g_frontEnd.unkbc = 0;
    g_frontEnd.unk5c = 1;
    g_frontEnd.unk6c += g_frontEnd.unk64 * (1.0f / 60.0f);
    g_frontEnd.unk70 += g_frontEnd.unk68 * (1.0f / 60.0f);
    FUN_43f610();
    g_frontEnd.unk5c = 0;
    if (fade < g_frontEnd.unk7c)
    {
        fade = g_frontEnd.unk7c;
    }
    FUN_442ad0(2, 1, 0, 0, fade, fade, 1.0f);
    g_frontEnd.unk5c = 1;
    if (g_frontEnd.nextScreen)
    {
        FUN_43f310(g_frontEnd.nextScreen);
    }
    else if (g_frontEnd.screen)
    {
        FUN_43f310(g_frontEnd.screen);
    }
    g_frontEnd.unk5c = 0;
    switch (g_frontEnd.state)
    {
    case 3:
        if (g_frontEnd.fade > 0)
        {
            g_frontEnd.fade = FUN_43d790(g_frontEnd.fade - 0x2492, 0, 0x10000);
        }
        else
        {
            g_frontEnd.state = 1;
        }
        break;
    case 2:
        if (g_frontEnd.fade < 0x10000)
        {
            g_frontEnd.fade = FUN_43d790(g_frontEnd.fade + 0x2492, 0, 0x10000);
        }
        else
        {
            if (g_frontEnd.screen && !g_frontEnd.screenStatic)
            {
                g_frontEnd.screen->destroy(g_frontEnd.screen);
                Pool_Free(g_frontEnd.screen);
            }
            g_frontEnd.screen = g_frontEnd.nextScreen;
            g_frontEnd.screenStatic = g_frontEnd.nextScreenStatic;
            g_frontEnd.nextScreen = NULL;
            g_frontEnd.nextScreenStatic = FALSE;
            FUN_43dee0();
            g_frontEnd.screen->message(g_frontEnd.screen, 0x13, 0);
            g_frontEnd.state = 3;
            g_frontEnd.unk80 = 0.0f;
        }
        break;
    }
    g_frontEnd.unk80 = FUN_43d810(g_frontEnd.unk80, 1.0f, 0.005f);
    if (!g_frontEnd.unkbc)
    {
        if (g_frontEnd.screen)
        {
            g_frontEnd.screen->message(g_frontEnd.screen, 2, 0);
        }
        if (g_frontEnd.nextScreen)
        {
            g_frontEnd.nextScreen->message(g_frontEnd.nextScreen, 2, 0);
        }
        g_frontEnd.unk5c = 1;
        if (g_frontEnd.screen)
        {
            if (g_frontEnd.nextScreen)
            {
                g_frontEnd.nextScreen->message(g_frontEnd.nextScreen, 1, 0);
            }
            else
            {
                g_frontEnd.screen->message(g_frontEnd.screen, 1, 0);
            }
        }
        g_frontEnd.unk5c = 0;
    }
    g_frontEnd.unk88[0] = FUN_43d810(g_frontEnd.unk88[0], g_frontEnd.unka0[0], 0.001f);
    g_frontEnd.unk88[1] = FUN_43d810(g_frontEnd.unk88[1], g_frontEnd.unka0[1], 0.001f);
    g_frontEnd.unk88[2] = FUN_43d810(g_frontEnd.unk88[2], g_frontEnd.unka0[2], 0.001f);
    g_frontEnd.unk88[3] = FUN_43d810(g_frontEnd.unk88[3], g_frontEnd.unka0[3], 0.001f);
    g_frontEnd.unk88[4] = FUN_43d810(g_frontEnd.unk88[4], g_frontEnd.unka0[4], 0.001f);
    g_frontEnd.unk88[5] = FUN_43d810(g_frontEnd.unk88[5], g_frontEnd.unka0[5], 0.001f);
    g_frontEnd.unk74++;
    g_frontEnd.unk78++;
}

// Routes menu input to the screen: from the locked player, or from every active one.
// FUNCTION: STUNTGP_D3D 0x43f310
void FUN_43f310(PoolObject *screen)
{
    int i;
    int count = 0;
    if (g_frontEnd.unkc8)
    {
        if (g_frontEnd.lockedPlayer)
        {
            if (FUN_43f5e0(g_frontEnd.lockedPlayer))
            {
                return;
            }
        }
        else
        {
            for (i = 1; i < 5; i++)
            {
                if (FUN_43f5e0(i))
                {
                    return;
                }
            }
        }
        g_frontEnd.unkc8 = 0;
    }
    if (g_frontEnd.lockedPlayer)
    {
        if (FUN_437090(g_frontEnd.lockedPlayer))
        {
            FUN_43f3e0(screen, g_frontEnd.lockedPlayer);
        }
        else
        {
            g_frontEnd.unkbc = 1;
        }
    }
    else
    {
        for (i = 1; i < 5; i++)
        {
            if (FUN_437090(i))
            {
                FUN_43f3e0(screen, i);
                count++;
            }
        }
        if (!count)
        {
            g_frontEnd.unkbc = 1;
        }
    }
    if (g_frontEnd.unkbc != g_frontEnd.unkc0)
    {
        if (g_frontEnd.unkbc)
        {
            FUN_440880(7);
        }
        else
        {
            FUN_440880(8);
        }
    }
    g_frontEnd.unkc0 = g_frontEnd.unkbc;
}

// FUNCTION: STUNTGP_D3D 0x43f3e0
void FUN_43f3e0(PoolObject *screen, int player)
{
    char key = g_62ddfc;
    int action = 0;
    int pressed = 0;
    g_62ddfc = 0;
    if (FUN_436fd0(player, 7))
    {
        pressed = 0x11;
    }
    else if (FUN_436fd0(player, 6))
    {
        pressed = 0x10;
    }
    else if (FUN_436fd0(player, 5))
    {
        pressed = 0xf;
    }
    else if (FUN_436fd0(player, 1))
    {
        pressed = 0xb;
    }
    else if (FUN_436fd0(player, 2))
    {
        pressed = 0xc;
    }
    else if (FUN_436fd0(player, 3))
    {
        pressed = 0xd;
    }
    else if (FUN_436fd0(player, 4))
    {
        pressed = 0xe;
    }
    if (key)
    {
        g_frontEnd.unk78 = 0;
        if (g_frontEnd.unk7c)
        {
            return;
        }
        screen->message(screen, 0x12, key);
    }
    if (FUN_436fc0(player, 7))
    {
        action = 10;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 6))
    {
        action = 9;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 1))
    {
        action = 4;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 2))
    {
        action = 5;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 3))
    {
        action = 6;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 4))
    {
        action = 7;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 5))
    {
        action = 8;
        screen->message(screen, action, player);
    }
    if (action || pressed)
    {
        g_frontEnd.unk78 = 0;
    }
    if (!g_frontEnd.unk7c && pressed)
    {
        screen->message(screen, pressed, player);
    }
}

// FUNCTION: STUNTGP_D3D 0x43f5e0
int FUN_43f5e0(int player)
{
    for (int i = 1; i < 8; i++)
    {
        if (FUN_436fc0(player, i))
        {
            return 1;
        }
    }
    return 0;
}

// Idle timeouts: drop back to the title screen, and fade in the attract overlay.
// FUNCTION: STUNTGP_D3D 0x43f610
void FUN_43f610()
{
    if (g_frontEnd.screen)
    {
        switch (g_frontEnd.screen->unk00[1])
        {
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
        case 11:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 27:
        case 29:
            if (g_frontEnd.unk78 > 3600)
            {
                FUN_440880(2);
                FUN_43ef10(1, 1);
                FUN_43dd70();
            }
        }
    }
    if (g_frontEnd.unk78 > 18000)
    {
        g_frontEnd.unk7c++;
    }
    else
    {
        g_frontEnd.unk7c = 0;
    }
    g_frontEnd.unk7c = FUN_43d790(g_frontEnd.unk7c, 0, 70);
}

// FUNCTION: STUNTGP_D3D 0x4408e0
void FUN_4408e0()
{
    g_5ff8c0 = 1;
}

// FUNCTION: STUNTGP_D3D 0x440770
void FUN_440770(int a, int b)
{
    if (g_5ff8c0 > 0)
    {
        int sound = FUN_4407a0(a);
        if (sound)
        {
            FUN_461150(sound, 0, b, 0xff, 0, 0, 0);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x4407a0
int FUN_4407a0(int id)
{
    switch (id)
    {
    case 1:
        return 0x33;
    case 2:
        return 0x34;
    case 3:
        return 0x35;
    case 4:
        return 0x36;
    case 5:
        return 0x37;
    case 6:
        return 0x38;
    case 7:
        return 0x39;
    case 8:
        return 0x3a;
    case 9:
        return 0x3b;
    case 10:
        return 0x3c;
    case 11:
        return 0x3d;
    case 12:
        return 0x3e;
    case 13:
        return 0x3f;
    case 16:
        return 0x42;
    case 17:
        return 0x43;
    case 18:
        return 0x44;
    case 19:
        return 0x45;
    case 20:
        return 0x46;
    case 21:
        return 0x47;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x440880
void FUN_440880(int a)
{
    FUN_440770(a, 0);
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
