#include "GameSetup.h"
#include "Game.h"
#include "GameUpdate.h"

#include <stdio.h>
#include <string.h>

#include "../../globals.h"
#include "../../mem.h"
#include "../../timer.h"
#include "../../vecmath.h"
#include "io_wad.h"

void FUN_4411c0();

extern char g_LevelScript[32];
extern float g_482668;

void FUN_441f90();
void FUN_45e0e0();
void Timer_Reset();

// GLOBAL: STUNTGP_D3D 0x5fd248
int g_5fd248;

// GLOBAL: STUNTGP_D3D 0x5fd24c
int g_5fd24c;

struct Unk4d5cc0
{
    short unk00;
    BYTE unk02[0x19d00 - 2];
};

// GLOBAL: STUNTGP_D3D 0x4d5cc0
Unk4d5cc0 g_4d5cc0[6];

// Sub-object at Car+0x280, handed to FUN_40e360/FUN_40e380.
// GLOBAL: STUNTGP_D3D 0x49a164
int g_49a164;

// GLOBAL: STUNTGP_D3D 0x60df90
Unk4d5cc0 *g_60df90;

// GLOBAL: STUNTGP_D3D 0x474670
int g_474670 = -1;

// GLOBAL: STUNTGP_D3D 0x4d5c9c
int g_4d5c9c;

// GLOBAL: STUNTGP_D3D 0x4d5ca0
int g_4d5ca0;

struct Unk496990
{
    int unk00;
    BYTE unk04[0x40 - 4];
    int unk40;
    BYTE unk44[0x138 - 0x44];
};

// GLOBAL: STUNTGP_D3D 0x496990
Unk496990 g_496990[16];

struct Unk62a078
{
    int unk00;
    BYTE unk04[0xd0 - 4];
};

// GLOBAL: STUNTGP_D3D 0x62a078
Unk62a078 g_62a078[0x40];

// GLOBAL: STUNTGP_D3D 0x62d478
int g_62d478;

// GLOBAL: STUNTGP_D3D 0x60f02c
int g_60f02c[0x96];

// GLOBAL: STUNTGP_D3D 0x61b634
int g_61b634;

extern int g_61294c;

extern int g_612958;

extern int g_612968;

// GLOBAL: STUNTGP_D3D 0x612974
int g_612974;

// GLOBAL: STUNTGP_D3D 0x612978
int g_612978;

// GLOBAL: STUNTGP_D3D 0x612980
int g_612980;

// GLOBAL: STUNTGP_D3D 0x612988
int g_612988;

// GLOBAL: STUNTGP_D3D 0x61298c
int g_61298c;

extern int g_612990;

// GLOBAL: STUNTGP_D3D 0x612998
int g_612998;

extern int g_61299c;

// GLOBAL: STUNTGP_D3D 0x6129a0
int g_6129a0;

// GLOBAL: STUNTGP_D3D 0x612be4
int g_612be4;

extern int g_612bf0;

// GLOBAL: STUNTGP_D3D 0x571328
int g_571328;

// GLOBAL: STUNTGP_D3D 0x612d54
int g_612d54[6];

// GLOBAL: STUNTGP_D3D 0x612d94
int g_612d94;

// GLOBAL: STUNTGP_D3D 0x612d98
int g_612d98;

// GLOBAL: STUNTGP_D3D 0x612d9c
int g_612d9c;

// GLOBAL: STUNTGP_D3D 0x612da0
int g_612da0;

// GLOBAL: STUNTGP_D3D 0x612da4
int g_612da4[0x2200];

// GLOBAL: STUNTGP_D3D 0x61b5a4
int g_61b5a4[0x20];

// GLOBAL: STUNTGP_D3D 0x61b624
int g_61b624;

// GLOBAL: STUNTGP_D3D 0x61b628
int g_61b628;

// GLOBAL: STUNTGP_D3D 0x61b62c
int g_61b62c;

// FUNCTION: STUNTGP_D3D 0x401000
void FUN_401000()
{
    memset(g_496990, 0, sizeof(g_496990));
    for (int i = 0; i < 16; i++)
    {
        g_496990[i].unk00 = 0;
        g_496990[i].unk40 = 0;
    }
}

struct Unk497f20
{
    float unk00;
    float unk04;
    float unk08;
    BYTE unk0c[0x50 - 0x0c];
    float unk50;
    float unk54;
    float unk58;
    float unk5c;
    float unk60;
    float unk64;
};

// GLOBAL: STUNTGP_D3D 0x497f20
Unk497f20 g_497f20;

// GLOBAL: STUNTGP_D3D 0x472210
float g_472210[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

// GLOBAL: STUNTGP_D3D 0x472250
float g_472250[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

// GLOBAL: STUNTGP_D3D 0x472290
float g_472290[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

// FUNCTION: STUNTGP_D3D 0x401de0
void FUN_401de0()
{
    g_497f20.unk00 = 0.0f;
    g_497f20.unk04 = 125.0f;
    g_497f20.unk08 = -12500.0f;
    g_497f20.unk50 = 0.0f;
    g_497f20.unk54 = 0.0f;
    g_497f20.unk58 = 0.0f;
    g_497f20.unk60 = 1.0f;
    g_497f20.unk64 = 100.0f;
    Matrix_Identity(g_472210);
    Matrix_Identity(g_472250);
    Matrix_Identity(g_472290);
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

// FUNCTION: STUNTGP_D3D 0x40e360
void FUN_40e360(Car *sub)
{
    sub->unk2270 = sub->unkf78;
    sub->unk2570 = sub->unk2574;
}

// FUNCTION: STUNTGP_D3D 0x40e380
void FUN_40e380(Car *sub)
{
    sub->unk2568 = 0;
    sub->unk2570 = sub->unk2574;
}

// FUNCTION: STUNTGP_D3D 0x4192d0
void FUN_4192d0()
{
    g_474670 = -1;
    g_4d5c9c = 0;
    g_4d5ca0 = 0;
}

// STUB: STUNTGP_D3D 0x413670
void FUN_413670()
{
}

// FUNCTION: STUNTGP_D3D 0x4199a0
void FUN_4199a0()
{
    int i;
    for (i = 0; i < 6; i++)
    {
        g_4d5cc0[i].unk00 = 0;
    }
    for (i = 0; i < 6; i++)
    {
        g_49a1f8[i].unk7268 = 0;
    }
}

// STUB: STUNTGP_D3D 0x424c30
void FUN_424c30(int param)
{
}

void FUN_429510();

// STUB: STUNTGP_D3D 0x42e6e0
void FUN_42e6e0()
{
}

// STUB: STUNTGP_D3D 0x43d0b0
void FUN_43d0b0()
{
}

// FUNCTION: STUNTGP_D3D 0x43d1b0
void FUN_43d1b0()
{
    g_5fd248 = 1;
    g_5fd24c = FUN_43d420();
}

// FUNCTION: STUNTGP_D3D 0x43d1d0
void FUN_43d1d0()
{
    FUN_43d1f0();
    g_5fd248 = 0;
    FUN_4411c0();
}

// STUB: STUNTGP_D3D 0x43d1f0
void FUN_43d1f0()
{
}

// FUNCTION: STUNTGP_D3D 0x43d420
int FUN_43d420()
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x443050
void FUN_443050()
{
    g_60df90 = &g_4d5cc0[2];
}

// FUNCTION: STUNTGP_D3D 0x445fa0
void FUN_445fa0()
{
    FUN_443050();
    for (int i = 0; i < 6; i++)
    {
        g_49a1f8[i].active = 0;
        g_49a1f8[i].unk26b0 = 0;
        g_49a1f8[i].unk26b4 = 0;
        FUN_40e360(&g_49a1f8[i]);
        FUN_40e380(&g_49a1f8[i]);
    }
    g_482668 = 4.0f;
    memset(g_60f02c, 0, sizeof(g_60f02c));
    FUN_441f90();
    FUN_401000();
    FUN_45e0e0();
    g_61b634 = 0;
    g_612948 = 0;
    g_61294c = 0;
    g_612958 = 0;
    g_612968 = 0;
    g_612974 = 0;
    g_612978 = 0;
    g_612980 = 0;
    g_frameCount = 0;
    g_612988 = 0;
    g_61298c = 0;
    g_612994 = 0;
    g_612990 = 0;
    g_612998 = 0;
    g_61299c = 0;
    g_6129a0 = 0;
    g_612be4 = 0;
    g_612bf0 = 0;
    g_571328 = 0;
    memset(g_612d54, 0, sizeof(g_612d54));
    g_612d94 = 0;
    g_612d98 = 0;
    g_612d9c = 0;
    g_612da0 = 0;
    memset(g_612da4, 0, sizeof(g_612da4));
    memset(g_61b5a4, 0, sizeof(g_61b5a4));
    g_49a164 = 0;
    g_61b624 = 0;
    g_61b628 = 0;
    g_61b62c = 0;
    Timer_Reset();
    FUN_4192d0();
}

// STUB: STUNTGP_D3D 0x446840
void FUN_446840(char *script)
{
}

// FUNCTION: STUNTGP_D3D 0x4469f0
void FUN_4469f0()
{
    char path[128];

    // STRING: STUNTGP_D3D 0x4850d8
    sprintf(path, "%s\\Config\\Levels\\%s.cfg", g_GameDirectory, g_LevelScript);
    int size = size_of_file(path);
    if (size == 0)
    {
        // STRING: STUNTGP_D3D 0x4850f0
        sprintf(path, "%s\\Config\\Levels\\Default.cfg", g_GameDirectory);
        size = size_of_file(path);
    }
    char *script = (char *)Mem_Alloc(size + 32, 0);
    bload(path, script, size);
    FUN_446840(script);
    Mem_Free(script);
}

// FUNCTION: STUNTGP_D3D 0x45e0e0
void FUN_45e0e0()
{
    Unk62a078 *p = g_62a078;
    for (int i = 0; i < 0x40; i++, p++)
    {
        p->unk00 = 2;
    }
    g_62d478 = 0;
}

// FUNCTION: STUNTGP_D3D 0x45ec30
void FUN_45ec30()
{
    memset(g_62d580, 0, sizeof(g_62d580));
    for (int i = 0; i < 4; i++)
    {
        g_62d580[i].active = 0;
        g_62d580[i].unk008 = 0;
        g_62d580[i].type = 0;
        g_62d580[i].keyMap = 0;
        g_62d580[i].unk018 = 0xffff;
        g_62d580[i].unk01c = 0;
        g_62d580[i].unk020 = 0;
        g_62d580[i].unk024 = 0;
        g_62d580[i].unk028 = 0;
    }
}
