#include "GameUpdate.h"

struct MenuCursor
{
    int x;     // 0x00
    int y;     // 0x04
    int prevX; // 0x08
    int prevY; // 0x0c
    int unk10; // 0x10
    int unk14; // 0x14
};

// GLOBAL: STUNTGP_D3D 0x5da300
MenuCursor g_5da300[4];

// GLOBAL: STUNTGP_D3D 0x5df5dc
int g_5df5dc;

// GLOBAL: STUNTGP_D3D 0x5df5e0
int g_5df5e0;

// GLOBAL: STUNTGP_D3D 0x5df5e4
int g_5df5e4;

// GLOBAL: STUNTGP_D3D 0x5df5e8
int g_5df5e8;

// GLOBAL: STUNTGP_D3D 0x5df5ec
int g_5df5ec;

// GLOBAL: STUNTGP_D3D 0x5df5f0
int g_5df5f0;

// GLOBAL: STUNTGP_D3D 0x5e37a0
int g_5e37a0;

// GLOBAL: STUNTGP_D3D 0x5e37b8
int g_5e37b8;

// GLOBAL: STUNTGP_D3D 0x5ff3ec
int g_5ff3ec;

// GLOBAL: STUNTGP_D3D 0x61297c
int g_61297c;

void FUN_424bd0(float x, float y);
void FUN_436ed0();
void FUN_436f00(int index);
void FUN_437eb0();
void FUN_43c000();
void FUN_43eff0();
int FUN_43efc0();
int FUN_440c40(int id);
void FUN_441210();
int FUN_452d70(int id);
void FUN_460bc0();
void FUN_462270(int a);

// STUB: STUNTGP_D3D 0x424bd0
void FUN_424bd0(float x, float y)
{
}

// FUNCTION: STUNTGP_D3D 0x436ed0
void FUN_436ed0()
{
    for (int i = 0; i < 4; i++)
    {
        g_5da300[i].prevX = g_5da300[i].x;
        g_5da300[i].prevY = g_5da300[i].y;
    }
    for (int j = 1; j < 5; j++)
    {
        FUN_436f00(j);
    }
}

// STUB: STUNTGP_D3D 0x436f00
void FUN_436f00(int index)
{
}

// FUNCTION: STUNTGP_D3D 0x437eb0
void FUN_437eb0()
{
    FUN_441210();
}

// FUNCTION: STUNTGP_D3D 0x43c000
void FUN_43c000()
{
    FUN_424bd0((float)g_5df5e8, (float)g_5df5ec);
    g_62e0f0 = g_5df5e0;
    g_62e0a8 = g_5df5dc;
    if (!g_5df5dc)
    {
        g_62e0a8 = 1;
    }
    g_61297c = g_5df5e4;
    FUN_462270(g_5e37a0);
    FUN_460bc0();
}

// FUNCTION: STUNTGP_D3D 0x43d200
void FUN_43d200()
{
    FUN_436ed0();
    FUN_43eff0();
    FUN_437eb0();
    FUN_43c000();
    if (g_5df5f0 && g_5df5f0 != g_5e37b8 && FUN_43efc0() && !FUN_452d70(g_5df5f0))
    {
        g_5df5f0 = g_5e37b8;
    }
}

// FUNCTION: STUNTGP_D3D 0x43efc0
int FUN_43efc0()
{
    return g_5ff3ec * 100 / 0x10000 > 95;
}

// STUB: STUNTGP_D3D 0x43eff0
void FUN_43eff0()
{
}

// STUB: STUNTGP_D3D 0x440c40
int FUN_440c40(int id)
{
    return 0;
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
        g_5df5f0 = id;
    }
    return 1;
}
