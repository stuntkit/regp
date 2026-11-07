#include "GameSetup.h"

#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include <string.h>

#include "../../globals.h"
#include "../../mem.h"
#include "../../vecmath.h"
#include "io_wad.h"

void FUN_4411c0();

extern char g_LevelScript[32];

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

// GLOBAL: STUNTGP_D3D 0x482718
int g_482718 = 1;

// GLOBAL: STUNTGP_D3D 0x482f38
int g_482f38 = 1;

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

struct Unk4a1460
{
    int unk00;
    BYTE unk04[0x7724 - 4];
};

// GLOBAL: STUNTGP_D3D 0x4a1460
Unk4a1460 g_4a1460[6];

// GLOBAL: STUNTGP_D3D 0x489798
int g_489798 = 0xff;

// GLOBAL: STUNTGP_D3D 0x48979c
int g_48979c = 0xff;

// GLOBAL: STUNTGP_D3D 0x62e0ac
int g_62e0ac;

// GLOBAL: STUNTGP_D3D 0x62e0f8
int g_62e0f8;

// GLOBAL: STUNTGP_D3D 0x62f5ac
int g_62f5ac;

// GLOBAL: STUNTGP_D3D 0x62f5b4
int g_62f5b4;

struct SoundChannel
{
    LPDIRECTSOUNDBUFFER buffer;
    BYTE unk04[0x20 - 4];
};

// GLOBAL: STUNTGP_D3D 0x62e118
SoundChannel g_62e118[0x80];

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
        g_4a1460[i].unk00 = 0;
    }
}

// STUB: STUNTGP_D3D 0x422420
void FUN_422420()
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

// STUB: STUNTGP_D3D 0x443bd0
void FUN_443bd0()
{
}

// FUNCTION: STUNTGP_D3D 0x443d70
void FUN_443d70()
{
    if (g_482718)
    {
        FUN_443bd0();
    }
}

// FUNCTION: STUNTGP_D3D 0x445610
void FUN_445610()
{
}

// STUB: STUNTGP_D3D 0x445620
void FUN_445620()
{
}

// FUNCTION: STUNTGP_D3D 0x4457e0
void FUN_4457e0()
{
    if (g_482f38)
    {
        FUN_445620();
        FUN_445610();
    }
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

// FUNCTION: STUNTGP_D3D 0x45f9d0
void FUN_45f9d0()
{
    if (g_62f5ac && g_62e0f8)
    {
        FUN_460330();
        g_62f5ac = 0;
    }
}

// STUB: STUNTGP_D3D 0x460330
void FUN_460330()
{
}

// FUNCTION: STUNTGP_D3D 0x460c90
void FUN_460c90()
{
    g_489798 = 0xff;
    g_48979c = 0xff;
}

// FUNCTION: STUNTGP_D3D 0x460d60
void FUN_460d60(unsigned int channel)
{
    if (g_62e0ac)
    {
        LPDIRECTSOUNDBUFFER buffer = g_62e118[channel].buffer;
        if (buffer)
        {
            buffer->Stop();
        }
        g_62f5b4--;
    }
}

// FUNCTION: STUNTGP_D3D 0x460dd0
void FUN_460dd0()
{
    for (unsigned int i = 0; i < 0x80; i++)
    {
        FUN_460d60(i);
    }
}

// STUB: STUNTGP_D3D 0x462090
void FUN_462090()
{
}

// FUNCTION: STUNTGP_D3D 0x4624b0
void FUN_4624b0()
{
}
