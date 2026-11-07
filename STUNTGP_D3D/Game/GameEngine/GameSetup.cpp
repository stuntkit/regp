#include "GameSetup.h"

#include <string.h>

struct Unk62d580
{
    int unk00;
    int unk04;
    int unk08;
    int unk0c;
    int unk10;
    int unk14;
    int unk18;
    int unk1c;
    int unk20;
    int unk24;
    int unk28;
    BYTE unk2c[0x1dc - 0x2c];
};

// GLOBAL: STUNTGP_D3D 0x62d580
Unk62d580 g_62d580[4];

// GLOBAL: STUNTGP_D3D 0x4835e0
int g_4835e0 = 1;

// GLOBAL: STUNTGP_D3D 0x612944
int g_612944;

// STUB: STUNTGP_D3D 0x401de0
void FUN_401de0()
{
}

// STUB: STUNTGP_D3D 0x40a2f0
void FUN_40a2f0()
{
}

// STUB: STUNTGP_D3D 0x40d500
void FUN_40d500()
{
}

// FUNCTION: STUNTGP_D3D 0x40e050
void FUN_40e050()
{
}

// STUB: STUNTGP_D3D 0x413670
void FUN_413670()
{
}

// STUB: STUNTGP_D3D 0x4199a0
void FUN_4199a0()
{
}

// STUB: STUNTGP_D3D 0x422420
void FUN_422420()
{
}

// STUB: STUNTGP_D3D 0x4249b0
void FUN_4249b0()
{
}

// STUB: STUNTGP_D3D 0x424c30
void FUN_424c30(int param)
{
}

// STUB: STUNTGP_D3D 0x429510
void FUN_429510()
{
}

// STUB: STUNTGP_D3D 0x42e6e0
void FUN_42e6e0()
{
}

// STUB: STUNTGP_D3D 0x43d0b0
void FUN_43d0b0()
{
}

// STUB: STUNTGP_D3D 0x43d1b0
void FUN_43d1b0()
{
}

// STUB: STUNTGP_D3D 0x43d1d0
void FUN_43d1d0()
{
}

// STUB: STUNTGP_D3D 0x443d70
void FUN_443d70()
{
}

// STUB: STUNTGP_D3D 0x4457e0
void FUN_4457e0()
{
}

// STUB: STUNTGP_D3D 0x445d70
void FUN_445d70(int param)
{
}

// FUNCTION: STUNTGP_D3D 0x445f80
void FUN_445f80()
{
    if (g_4835e0 != g_612944)
    {
        FUN_445d70(g_4835e0);
    }
}

// STUB: STUNTGP_D3D 0x445fa0
void FUN_445fa0()
{
}

// STUB: STUNTGP_D3D 0x4469f0
void FUN_4469f0()
{
}

// FUNCTION: STUNTGP_D3D 0x45ec30
void FUN_45ec30()
{
    memset(g_62d580, 0, sizeof(g_62d580));
    for (int i = 0; i < 4; i++)
    {
        g_62d580[i].unk00 = 0;
        g_62d580[i].unk08 = 0;
        g_62d580[i].unk0c = 0;
        g_62d580[i].unk14 = 0;
        g_62d580[i].unk18 = 0xffff;
        g_62d580[i].unk1c = 0;
        g_62d580[i].unk20 = 0;
        g_62d580[i].unk24 = 0;
        g_62d580[i].unk28 = 0;
    }
}

// STUB: STUNTGP_D3D 0x45f9d0
void FUN_45f9d0()
{
}

// STUB: STUNTGP_D3D 0x460c90
void FUN_460c90()
{
}

// STUB: STUNTGP_D3D 0x460dd0
void FUN_460dd0()
{
}

// STUB: STUNTGP_D3D 0x462090
void FUN_462090()
{
}

// FUNCTION: STUNTGP_D3D 0x4624b0
void FUN_4624b0()
{
}
