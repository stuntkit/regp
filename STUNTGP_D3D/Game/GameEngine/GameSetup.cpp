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
#include "MenuUpdate.h"
#include "../../objects.h"
#include "../../sprite.h"
#include "../../d3drender.h"
#include "../../surface.h"
#include "Engine_LevelScript.h"

struct CameraPath;

struct StuntKnot
{
    float pathPosition; // 0x00
    float width;        // 0x04
    int grade;          // 0x08
};

void FUN_4411c0();
void FUN_401d40();
void FUN_402420();
void FUN_413190();
void FUN_413220();
void FUN_426260();
void FUN_428fa0();
void FUN_42b740();
void FUN_42c510();
void FUN_42d070();
void FUN_42d700();
void FUN_42e380();
void FUN_42e3e0();
void FUN_42e430();
void FUN_42e510();
void FUN_42e6d0();
void FUN_42f090();
void FUN_431300();
void FUN_431360();
void FUN_431420();
void FUN_4312c0();
void FUN_4342c0();
int FUN_445ad0();
extern int g_5fd250;

extern char g_LevelScript[32];
extern float g_482668;

void FUN_441f90();
void FUN_45e0e0();
void Timer_Reset();

// GLOBAL: STUNTGP_D3D 0x5fd248
int g_5fd248;

// GLOBAL: STUNTGP_D3D 0x5fd24c
int g_5fd24c;

// GLOBAL: STUNTGP_D3D 0x5fd254
int g_5fd254;

// GLOBAL: STUNTGP_D3D 0x6244f8
int g_6244f8;

// GLOBAL: STUNTGP_D3D 0x624980
int g_624980;

// GLOBAL: STUNTGP_D3D 0x624984
int g_624984;

// GLOBAL: STUNTGP_D3D 0x57b41c
int g_57b41c;

// GLOBAL: STUNTGP_D3D 0x589e08
int g_589e08;

// GLOBAL: STUNTGP_D3D 0x498230
int g_498230;

// GLOBAL: STUNTGP_D3D 0x498234
int g_498234;

// GLOBAL: STUNTGP_D3D 0x498238
int g_498238;

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

extern DWORD g_612990;

// GLOBAL: STUNTGP_D3D 0x612998
int g_612998;

extern int g_61299c;

// GLOBAL: STUNTGP_D3D 0x6129a0
int g_6129a0;

// GLOBAL: STUNTGP_D3D 0x612be4
int g_612be4;

extern int g_612bf0;

// GLOBAL: STUNTGP_D3D 0x571328
CameraPath *g_571328;

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

void FUN_40bde0();
void FUN_41d300();
void FUN_413450();
void FUN_4085e0();
void FUN_408710();
void FUN_41d180();
void FUN_408640(Car *car, float *pos);
void FUN_413500();
void FUN_417e10();
void FUN_4162c0();
void FUN_414f00();
void FUN_4150d0();
void FUN_419900();
void FUN_4130d0(int mode);

// Sets up car 0 from defaults and clones it into the other five.
// FUNCTION: STUNTGP_D3D 0x413670
void FUN_413670()
{
    g_4d5bb8 = g_49a1f8;
    g_474630 = g_49a1f8;
    FUN_40bde0();
    g_4d5bb8->posX = 0.0f;
    g_4d5bb8->posY = 0.0f;
    g_4d5bb8->posZ = -12200.0f;
    g_4d5bb8->unkcb8[0].x = 34.5f;
    g_4d5bb8->unkcb8[1].x = 34.5f;
    g_4d5bb8->unkcb8[2].x = 24.5f;
    g_4d5bb8->unkcb8[3].x = 24.5f;
    g_4d5bb8->unk230 = 250.0f;
    g_4d5bb8->unk234 = 126.600006f;
    g_4d5bb8->unk238 = 180.0f;
    g_4d5bb8->unk220 = 1000.0f;
    g_4d5bb8->unk224 = 0.5f;
    g_4d5bb8->unk228 = 0.5f;
    g_4d5bb8->unk22c = 30.000002f;
    FUN_41d300();
    FUN_413450();
    FUN_4085e0();
    FUN_408710();
    FUN_41d180();
    for (int i = 1; i < 6; i++)
    {
        g_49a1f8[i] = g_49a1f8[0];
        g_49a1f8[i].posX += 500.0f;
        FUN_408640(&g_49a1f8[i], &g_49a1f8[i].posX);
        g_49a1f8[i].unk26b0 = g_60f050[i - 1].unk40;
        g_49a1f8[i].unk26b4 = g_60f050[i - 1].unk44;
    }
    FUN_413500();
    FUN_417e10();
    FUN_4162c0();
    FUN_414f00();
    FUN_4150d0();
    FUN_419900();
    FUN_4130d0(1);
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

// FUNCTION: STUNTGP_D3D 0x401d40
void FUN_401d40()
{
    if (g_612be8 != 2)
    {
        SceneView *view = g_636448->view;
        g_498238 = view->unk34;
        g_498230 = view->unk2c;
        g_498234 = view->unk30;
    }
}

// STUB: STUNTGP_D3D 0x402420
void FUN_402420()
{
}

// STUB: STUNTGP_D3D 0x413190
void FUN_413190()
{
}

// STUB: STUNTGP_D3D 0x413220
void FUN_413220()
{
}

// STUB: STUNTGP_D3D 0x426260
void FUN_426260()
{
}

// STUB: STUNTGP_D3D 0x428fa0
void FUN_428fa0()
{
}

// STUB: STUNTGP_D3D 0x42b740
void FUN_42b740()
{
}

// STUB: STUNTGP_D3D 0x42c510
void FUN_42c510()
{
}

// STUB: STUNTGP_D3D 0x42d070
void FUN_42d070()
{
}

// STUB: STUNTGP_D3D 0x42d700
void FUN_42d700()
{
}

// STUB: STUNTGP_D3D 0x42e380
void FUN_42e380()
{
}

// STUB: STUNTGP_D3D 0x42e3e0
void FUN_42e3e0()
{
}

// STUB: STUNTGP_D3D 0x42e430
void FUN_42e430()
{
}

// STUB: STUNTGP_D3D 0x42e510
void FUN_42e510()
{
}

// FUNCTION: STUNTGP_D3D 0x42e6d0
void FUN_42e6d0()
{
    g_589e08 = 0;
}

// FUNCTION: STUNTGP_D3D 0x42e6e0
void FUN_42e6e0()
{
    FUN_42e510();
    FUN_42d070();
    FUN_44fd60();
    FUN_4342c0();
    FUN_42f090();
    if (!g_6244f8)
    {
        FUN_42e6d0();
        FUN_431360();
        g_6244f8 = 1;
        g_624980 = 1;
        g_624984 = 1;
    }
    else
    {
        FUN_431300();
    }
    FUN_429510();
    FUN_42e3e0();
    FUN_425070();
    FUN_413190();
    FUN_413220();
    FUN_42c510();
    WAD_FlushWadCache();
    FUN_428fa0();
    g_6243bc = g_6243b8 - g_6227d4;
    FUN_42e430();
    FUN_427270();
    FUN_42e380();
    FUN_402420();
    FUN_44ee00();
    FUN_42b740();
    FUN_42d700();
    FUN_426260();
    FUN_45e0e0();
    FUN_401d40();
    FUN_44fd60();
    g_6244f4 = 0;
    FUN_4320c0(1.0f);
    if (g_636448)
    {
        g_636448->camera = &g_4864e8;
    }
    g_6244f8 = 0;
    FUN_431420();
    FUN_4312c0();
    g_6244f8 = 1;
    g_57b41c = 0;
}

// STUB: STUNTGP_D3D 0x42f090
void FUN_42f090()
{
}

// STUB: STUNTGP_D3D 0x431300
void FUN_431300()
{
}

// STUB: STUNTGP_D3D 0x431360
void FUN_431360()
{
}

// STUB: STUNTGP_D3D 0x431420
void FUN_431420()
{
}

// STUB: STUNTGP_D3D 0x4312c0
void FUN_4312c0()
{
}

// STUB: STUNTGP_D3D 0x4342c0
void FUN_4342c0()
{
}

// FUNCTION: STUNTGP_D3D 0x43d0b0
void FUN_43d0b0()
{
    g_5fd248 = 0;
    g_5fd250 = 1;
    g_5fd254++;
    // STRING: STUNTGP_D3D 0x4795ec
    FUN_437e40("fe.log");
    Pool_Init();
    memset(&g_menuState, 0, sizeof(g_menuState));
    FUN_43c060();
    FUN_439e30();
    FUN_4408e0();
    FUN_437e60();
    FUN_436eb0();
    FUN_43dda0();
    FUN_440ae0();
    FUN_43dd10(0);
    FUN_43c000();
    FUN_434b50();
    FUN_43c370();
    FUN_43c130();
    if (FUN_440c40(FUN_445ad0()) < 0)
    {
        FUN_440c40(g_menuState.unk427c);
    }
    FUN_43d280();
    FUN_43ef10(0, 5);
    for (int i = 1; i < 25; i++)
    {
        FUN_437360(i);
        FUN_437da0(i);
    }
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

// FUNCTION: STUNTGP_D3D 0x445ad0
int FUN_445ad0()
{
    return 0;
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

// GLOBAL: STUNTGP_D3D 0x497d20
float g_497d20[0x80];

// GLOBAL: STUNTGP_D3D 0x499fb8
StuntKnot g_499fb8[33];

// GLOBAL: STUNTGP_D3D 0x577688
float g_577688[0x100];

// GLOBAL: STUNTGP_D3D 0x5896b8
int g_5896b8;

// GLOBAL: STUNTGP_D3D 0x5896bc
int g_5896bc;

// GLOBAL: STUNTGP_D3D 0x5896c0
int g_5896c0;

// GLOBAL: STUNTGP_D3D 0x5896c8
float g_5896c8[0x80];

// GLOBAL: STUNTGP_D3D 0x60dff0
float g_60dff0[0x80];

// GLOBAL: STUNTGP_D3D 0x60e1f0
float g_60e1f0[0x80];

// GLOBAL: STUNTGP_D3D 0x60e3f0
float g_60e3f0[0x80];

// GLOBAL: STUNTGP_D3D 0x60e7f0
float g_60e7f0[0x100];

// GLOBAL: STUNTGP_D3D 0x60ebf0
float g_60ebf0[0x100];

// GLOBAL: STUNTGP_D3D 0x61b63c
int g_61b63c;

// FUNCTION: STUNTGP_D3D 0x4460e0
void FUN_4460e0()
{
    int count = 0;
    while (g_483f98[count].id != -1)
    {
        count++;
    }
    g_61b63c = count;
    if (count)
    {
        FUN_460af0(g_483f98[0].id);
    }
}

// FUNCTION: STUNTGP_D3D 0x446700
void FUN_446700(char *script)
{
    // STRING: STUNTGP_D3D 0x484f38
    char *p = strstr(script, "-LevelBoxList[] =");
    int count = 0;
    // STRING: STUNTGP_D3D 0x484f4c
    while ((p = strstr(p + 0x10, "-Type")) != NULL)
    {
        // STRING: STUNTGP_D3D 0x484f54
        Script_GetInt(p, "-Type", &g_483f98[count].id);
        // STRING: STUNTGP_D3D 0x484f5c
        Script_GetVector3(p, "-Position", &g_483f98[count].bounds[0]);
        // STRING: STUNTGP_D3D 0x484f68
        Script_GetVector3(p, "-Scale", &g_483f98[count].bounds[4]);
        // STRING: STUNTGP_D3D 0x484f70
        Script_GetVector3(p, "-V", &g_483f98[count].bounds[8]);
        // STRING: STUNTGP_D3D 0x484f74
        Script_GetVector3(p, "-N", &g_483f98[count].bounds[12]);
        count++;
    }
    g_483f98[count].id = -1;
    FUN_4460e0();
}

// FUNCTION: STUNTGP_D3D 0x4467b0
void FUN_4467b0(char *script)
{
    // STRING: STUNTGP_D3D 0x484f78
    char *p = strstr(script, "-CarAI_StuntKnotList[] =");
    memset(g_499fb8, 0, sizeof(g_499fb8));
    int i = 0;
    // STRING: STUNTGP_D3D 0x484f94
    while ((p = strstr(p + 0x10, "-PathPosition")) != NULL)
    {
        // STRING: STUNTGP_D3D 0x484fa4
        Script_GetFloat(p, "-PathPosition", &g_499fb8[i].pathPosition);
        // STRING: STUNTGP_D3D 0x484fb4
        Script_GetFloat(p, "-Width", &g_499fb8[i].width);
        // STRING: STUNTGP_D3D 0x484fbc
        Script_GetInt(p, "-Grade", &g_499fb8[i].grade);
        i++;
    }
}

// FUNCTION: STUNTGP_D3D 0x446840
void FUN_446840(char *script)
{
    int intensity;
    int red;
    int green;
    int blue;

    // STRING: STUNTGP_D3D 0x484fc4
    strstr(script, "-VERSION =");
    // STRING: STUNTGP_D3D 0x484fd0
    Script_GetWord(script, "-VERSION =");
    // STRING: STUNTGP_D3D 0x484fdc
    char *p = strstr(script, "-Ambience[] =");
    // STRING: STUNTGP_D3D 0x484fec
    Script_GetInt(p, "I", &intensity);
    // STRING: STUNTGP_D3D 0x484ff0
    Script_GetInt(p, "R", &red);
    // STRING: STUNTGP_D3D 0x484ff4
    Script_GetInt(p, "G", &green);
    // STRING: STUNTGP_D3D 0x484ff8
    Script_GetInt(p, "B", &blue);
    g_624504 = intensity * (1.0f / 255.0f);
    g_624508 = red;
    g_62450c = green;
    g_624510 = blue;
    FUN_42d7e0();
    // STRING: STUNTGP_D3D 0x484ffc
    p = strstr(script, "-FogColour[] =");
    // STRING: STUNTGP_D3D 0x48500c
    Script_GetInt(p, "R", &g_5896b8);
    // STRING: STUNTGP_D3D 0x485010
    Script_GetInt(p, "G", &g_5896bc);
    // STRING: STUNTGP_D3D 0x485014
    Script_GetInt(p, "B", &g_5896c0);
    // STRING: STUNTGP_D3D 0x485018
    Script_GetFloatArray(p, "-FogEnvelope[]", g_5896c8, 0x80);
    // STRING: STUNTGP_D3D 0x485028
    Script_GetFloatArray(p, "-ColRestitutionTab[]", g_497d20, 0x80);
    // STRING: STUNTGP_D3D 0x485040
    Script_GetFloatArray(p, "-FarPlaneClipDistanceTab[]", g_577688, 0x100);
    // STRING: STUNTGP_D3D 0x48505c
    Script_GetFloatArray(p, "-CarReplacementSplineMask[]", g_60dff0, 0x80);
    // STRING: STUNTGP_D3D 0x485078
    Script_GetFloatArray(p, "-CarLightsMask[]", g_60e1f0, 0x80);
    // STRING: STUNTGP_D3D 0x48508c
    Script_GetFloatArray(p, "-AmbienceEnvelope[]", g_60e3f0, 0x80);
    // STRING: STUNTGP_D3D 0x4850a0
    Script_GetFloatArray(p, "-TrackWidthEnvelope_Left[]", g_60e7f0, 0x100);
    // STRING: STUNTGP_D3D 0x4850bc
    Script_GetFloatArray(p, "-TrackWidthEnvelope_Right[]", g_60ebf0, 0x100);
    FUN_446700(script);
    FUN_4467b0(script);
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
