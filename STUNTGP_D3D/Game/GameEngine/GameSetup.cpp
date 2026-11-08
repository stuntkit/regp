#include "GameSetup.h"
#include "Game.h"
#include "GameUpdate.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../globals.h"
#include "../../mem.h"
#include "../../timer.h"
#include "../../random.h"
#include "../../vecmath.h"
#include "io_wad.h"
#include "MenuUpdate.h"
#include "../../objects.h"
#include "../../sprite.h"
#include "../../d3drender.h"
#include "../../surface.h"
#include "Engine_LevelScript.h"
#include "../../common.h"

struct CameraPath;

struct Unk45ab70
{
    BYTE unk00[0x34];  // 0x00
    PoolObject *unk34; // 0x34
    PoolObject *unk38; // 0x38
};

struct Unk45c670
{
    BYTE unk00[0x14];  // 0x00
    PoolObject *unk14; // 0x14
    BYTE unk18[0x18];  // 0x18
    int unk30;         // 0x30
};

void FUN_45c670(Unk45c670 *object);

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

extern char g_GraphicsDirectory[128];
extern char g_GameLocation[256];
extern int g_D3DUVFix;
extern int g_61c50c;
extern int g_6244c8;
extern int g_6244cc;
extern int g_6244d0;
extern int g_61c5ec;

// GLOBAL: STUNTGP_D3D 0x636418
SceneSlot g_636418[16];

struct RenderMaterial
{
    DWORD unk00;      // 0x00
    DWORD unk04;      // 0x04
    float alpha;      // 0x08
    BYTE unk0c[0x44]; // 0x0c
    int unk50;        // 0x50
    DWORD unk54;      // 0x54
    DWORD unk58;      // 0x58
    DWORD unk5c;      // 0x5c
    BYTE unk60[0x8];  // 0x60
    float unk68;      // 0x68
    float unk6c;      // 0x6c
    float unk70;      // 0x70
    int unk74;        // 0x74
    int unk78;        // 0x78
    int unk7c;        // 0x7c
    int unk80;        // 0x80
    BYTE unk84[0xc];  // 0x84
};

// GLOBAL: STUNTGP_D3D 0x62447c
RenderMaterial *g_62447c;

// GLOBAL: STUNTGP_D3D 0x624480
TrackOctree *g_624480;

// Loaded track file; the offsets are relative to data.
struct TrackHeader
{
    BYTE unk000[0x20];
    int unk020;               // 0x020
    int unk024;               // 0x024
    int unk028;               // 0x028
    int unk02c;               // 0x02c
    int unk030;               // 0x030
    int unk034;               // 0x034
    int unk038;               // 0x038
    int unk03c;               // 0x03c
    int unk040;               // 0x040
    int unk044;               // 0x044
    int unk048;               // 0x048
    int unk04c;               // 0x04c
    BYTE unk050[0x58 - 0x50];
    int unk058;               // 0x058
    int unk05c;               // 0x05c
    int unk060;               // 0x060
    int unk064;               // 0x064
    BYTE unk068[0x70 - 0x68];
    int unk070;               // 0x070
    int unk074;               // 0x074
    int unk078;               // 0x078
    int unk07c;               // 0x07c
    int unk080;               // 0x080
    int unk084;               // 0x084
    int unk088;               // 0x088
    int unk08c;               // 0x08c
    int unk090;               // 0x090
    int unk094;               // 0x094
    int unk098;               // 0x098
    int unk09c;               // 0x09c
    int unk0a0;               // 0x0a0
    BYTE unk0a4[0xd4 - 0xa4];
    DWORD unk0d4;             // 0x0d4
    BYTE unk0d8[0xe4 - 0xd8];
    int unk0e4;               // 0x0e4
    int unk0e8;               // 0x0e8
    BYTE unk0ec[0xfc - 0xec];
    DWORD unk0fc;             // 0x0fc
    int unk100;               // 0x100
    BYTE unk104[0x10c - 0x104];
    DWORD unk10c;             // 0x10c
    BYTE unk110[0x148 - 0x110];
    BYTE data[1];             // 0x148
};

// GLOBAL: STUNTGP_D3D 0x58c800
Scene *g_58c800;

// GLOBAL: STUNTGP_D3D 0x58d810
TrackHeader *g_58d810;

// Name of the track scene from L_TRACK.
// GLOBAL: STUNTGP_D3D 0x624460
int g_624460;

// GLOBAL: STUNTGP_D3D 0x624464
BYTE *g_624464;

// GLOBAL: STUNTGP_D3D 0x624468
BYTE *g_624468;

// GLOBAL: STUNTGP_D3D 0x62446c
BYTE *g_62446c;

// GLOBAL: STUNTGP_D3D 0x624470
BYTE *g_624470;

// GLOBAL: STUNTGP_D3D 0x624478
BYTE *g_624478;

// GLOBAL: STUNTGP_D3D 0x62448c
SceneEntry *g_62448c;

// GLOBAL: STUNTGP_D3D 0x624490
SceneEntry *g_624490;

// GLOBAL: STUNTGP_D3D 0x6244a4
int g_6244a4;

// GLOBAL: STUNTGP_D3D 0x62497c
int g_62497c;

// NULL-terminated name list, cleared by FUN_42c480.
// GLOBAL: STUNTGP_D3D 0x582b28
char *g_582b28[255];

// GLOBAL: STUNTGP_D3D 0x6244a0
int g_6244a0;

extern void *g_6243c0;
extern void *g_6243c8;
extern void *g_6243d0;
extern void *g_6243d8;
extern int g_582724;
extern int g_6243c4;
extern int g_6243cc;
extern int g_6243d4;
extern int g_6243dc;
extern void *g_61c5f4;
extern void *g_61c5f8;
extern void *g_61c5fc;
extern void *g_61c600;

struct AnimDef;
extern CameraPath *g_624474;
extern DWORD g_624498;
extern AnimDef *g_624484;

// GLOBAL: STUNTGP_D3D 0x62449c
DWORD g_62449c;

// GLOBAL: STUNTGP_D3D 0x6249a0
int g_6249a0;

// GLOBAL: STUNTGP_D3D 0x6249a4
int g_6249a4;

// GLOBAL: STUNTGP_D3D 0x477c30
DWORD g_477c30 = 0x200000;

// GLOBAL: STUNTGP_D3D 0x4955e0
DWORD *g_4955e0;

// GLOBAL: STUNTGP_D3D 0x4955e4
DWORD *g_4955e4;

// GLOBAL: STUNTGP_D3D 0x62f5d8
DWORD g_62f5d8;

// GLOBAL: STUNTGP_D3D 0x632cf8
DWORD g_632cf8;

void FUN_42e240(Scene *scene);
void FUN_4311c0(Scene *scene);
void FUN_42b7f0(Scene *scene, Camera *camera, int arg);
void FUN_42b6e0();
void FUN_434030();
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

// GLOBAL: STUNTGP_D3D 0x4d5cc0
Unk4d5cc0 g_4d5cc0[6];

// Sub-object at Car+0x280, handed to FUN_40e360/FUN_40e380.
// GLOBAL: STUNTGP_D3D 0x49a164
int g_49a164;

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
Driver g_60f02c[6];

// GLOBAL: STUNTGP_D3D 0x571328
CameraPath *g_571328;

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

// Camera preset record in the level data (g_624478), 0x60 bytes each.
struct CameraRecord
{
    int unk00;       // 0x00
    float fov;       // 0x04
    BYTE unk08[0x8]; // 0x08
    Vec4 pos;        // 0x10
    BYTE unk20[0x10]; // 0x20
    Vec4 target;     // 0x30
    Vec4 up;         // 0x40
    BYTE unk50[0x10]; // 0x50
};

extern CameraPreset g_4722d8[32];
extern int g_499f90;

// GLOBAL: STUNTGP_D3D 0x499f94
int g_499f94;

// FUNCTION: STUNTGP_D3D 0x401e50
void FUN_401e50()
{
    if (g_6244a4 != 0)
    {
        for (DWORD i = 0; i < g_6244a4; i++)
        {
            g_4722d8[i].pos = ((CameraRecord *)g_624478)[i].pos;
            g_4722d8[i].target = ((CameraRecord *)g_624478)[i].target;
            g_4722d8[i].up = ((CameraRecord *)g_624478)[i].up;
            g_4722d8[i].fov = ((CameraRecord *)g_624478)[i].fov;
            g_4722d8[i].unk34 = 0;
            g_4722d8[i].roll = 0.0f;
        }
        g_499f90 = g_6244a4;
        g_499f94 = 0;
    }
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

CameraPath *FUN_428800(int id);
void FUN_418b10();

// FUNCTION: STUNTGP_D3D 0x4192f0
void FUN_4192f0()
{
    g_4d5c9c = (int)FUN_428800(2);
    FUN_418b10();
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
        g_49a1f8[i].unk26b0 = g_60f02c[i].model;
        g_49a1f8[i].unk26b4 = g_60f02c[i].unk04;
    }
    FUN_413500();
    FUN_417e10();
    FUN_4162c0();
    FUN_414f00();
    FUN_4150d0();
    FUN_419900();
    FUN_4130d0(1);
}

// FUNCTION: STUNTGP_D3D 0x4190b0
void FUN_4190b0(Car *car, unsigned int percent)
{
    car->unk2570 += (unsigned int)(percent * car->unk2574 * 0.01f);
    if (car->unk2570 > car->unk2574)
    {
        car->unk2570 = car->unk2574;
    }
}

extern int g_4d5ca8;

void FUN_442cf0(int frames, char *text, Car *car, int mode, int clear);

// FUNCTION: STUNTGP_D3D 0x419110
void FUN_419110()
{
    char text[64];
    // STRING: STUNTGP_D3D 0x474684
    sprintf(text, "%s %s\n", g_60f02c[g_4d5bb8 - g_49a1f8].name, g_6127a0[21]);
    FUN_442cf0(180, text, g_4d5bb8, 1, 0);
    g_4d5ca8 = 1;
}

// FUNCTION: STUNTGP_D3D 0x419180
void FUN_419180()
{
    char text[64];
    // STRING: STUNTGP_D3D 0x47468c
    sprintf(text, "%s %s\n", g_60f02c[g_4d5bb8 - g_49a1f8].name, g_6127a0[23]);
    FUN_442cf0(180, text, g_4d5bb8, 1, 0);
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

// FUNCTION: STUNTGP_D3D 0x4199d0
BYTE FUN_4199d0(BYTE *data, unsigned int size)
{
    BYTE sum = 0;
    while (size > 0)
    {
        sum += *data++;
        size--;
    }
    return sum;
}

// FUNCTION: STUNTGP_D3D 0x4199f0
int FUN_4199f0(char *name, char *buffer)
{
    char path[128];
    // STRING: STUNTGP_D3D 0x474698
    sprintf(path, "%s\\Replays\\%s.RPL", g_GameDirectory, name);
    if (!size_of_file(path))
    {
        return 0;
    }
    return bload(path, buffer, 0x20000);
}

// FUNCTION: STUNTGP_D3D 0x419a40
int FUN_419a40(Replay *replay)
{
    return replay->size = replay->count * sizeof(ReplayFrame) + sizeof(Replay);
}

void FUN_41aac0(Replay *replay);

// Finalises a recorded replay: checksum, size and the driver it belongs to.
// FUNCTION: STUNTGP_D3D 0x419a60
void FUN_419a60(Car *car, Replay *replay)
{
    FUN_41aac0(replay);
    unsigned int bytes = replay->count * sizeof(ReplayFrame);
    int size = FUN_419a40(replay);
    replay->unk14 = 1;
    replay->checksum = FUN_4199d0((BYTE *)replay->frames, bytes);
    replay->size = size;
    int index = car - g_49a1f8;
    strcpy(replay->name, g_60f02c[index].name);
    replay->unk20 = g_60f02c[index].unk08;
    replay->unk22 = g_60f02c[index].unk0c;
    replay->unk26 = g_60f02c[index].unk10;
    replay->unk24 = g_60f02c[index].unk14;
}

int FUN_44aff0(char *name, void *data, int size);

// FUNCTION: STUNTGP_D3D 0x419b30
void FUN_419b30(char *name, Car *car, Replay *replay)
{
    char path[128];
    FUN_419a60(car, replay);
    // STRING: STUNTGP_D3D 0x4746ac
    sprintf(path, "%s\\Replays\\%s.RPL", g_GameDirectory, name);
    FUN_44aff0(path, replay, replay->size);
}

void FUN_40fb30();

// FUNCTION: STUNTGP_D3D 0x419e30
void FUN_419e30()
{
    for (int i = 0; i < 4; i++)
    {
        if (g_4d5bb8->wheels[i].unk0c > 8.515625f)
        {
            g_4d5bb8->wheels[i].unk70 = 8;
            if (g_4d5bb8->unk71ec < 8)
            {
                g_4d5bb8->unk71ec++;
            }
        }
        else if (g_4d5bb8->wheels[i].unk70)
        {
            g_4d5bb8->wheels[i].unk70--;
        }
    }
    FUN_40fb30();
}

void FUN_415630();
void FUN_414ac0(unsigned int wheel);

// FUNCTION: STUNTGP_D3D 0x419e90
void FUN_419e90()
{
    if (g_4d5bb8->unk22c0 == 1)
    {
        FUN_415630();
        for (unsigned int i = 0; i < 4; i++)
        {
            FUN_414ac0(i);
        }
    }
}

extern Replay *g_570ac0;
extern ReplayFrame *g_570ac4;
extern ReplayFrame *g_4d5cb8;

// Replay playback: interpolates the position between the two recorded frames and derives the velocity.
// FUNCTION: STUNTGP_D3D 0x419ee0
void FUN_419ee0()
{
    Vec4 a;
    a.x = g_4d5cb8->pos[0];
    a.y = g_4d5cb8->pos[1];
    a.z = g_4d5cb8->pos[2];
    Vec4 b;
    b.x = g_570ac4->pos[0];
    b.y = g_570ac4->pos[1];
    b.z = g_570ac4->pos[2];
    Vec4 d;
    d.x = b.x - a.x;
    d.y = b.y - a.y;
    d.z = b.z - a.z;
    d.x = d.x * g_570ac0->unk08;
    d.y = g_570ac0->unk08 * d.y;
    d.z = g_570ac0->unk08 * d.z;
    b.x = d.x + a.x;
    b.y = d.y + a.y;
    b.z = d.z + a.z;
    g_4d5bb8->unk1c9c = g_4d5bb8->unk1c8c;
    g_4d5bb8->unk1c8c.x = b.x - g_4d5bb8->posX;
    g_4d5bb8->unk1c8c.y = b.y - g_4d5bb8->posY;
    g_4d5bb8->unk1c8c.z = b.z - g_4d5bb8->posZ;
    g_4d5bb8->unk1cf0 = g_4d5bb8->axisZ.x * g_4d5bb8->unk1c8c.x + g_4d5bb8->axisZ.y * g_4d5bb8->unk1c8c.y +
                        g_4d5bb8->axisZ.z * g_4d5bb8->unk1c8c.z;
    g_4d5bb8->unk1bbc = b;
    *(Vec4 *)&g_4d5bb8->posX = b;
}

void FUN_429510();

// FUNCTION: STUNTGP_D3D 0x401d40
void FUN_401d40()
{
    if (g_612948.unk02a0 != 2)
    {
        SceneView *view = g_636418[3].scene->view;
        g_498238 = view->unk34;
        g_498230 = view->unk2c;
        g_498234 = view->unk30;
    }
}

// STUB: STUNTGP_D3D 0x402420
void FUN_402420()
{
}

// GLOBAL: STUNTGP_D3D 0x4d5b28
char g_4d5b28[6];

// GLOBAL: STUNTGP_D3D 0x4d5bb0
BYTE g_4d5bb0[6];

// Deals the six grid numbers 2..7 in random order; after 8 misses it walks to the next free one.
// FUNCTION: STUNTGP_D3D 0x413110
void FUN_413110()
{
    memset(g_4d5bb0, 0, sizeof(g_4d5bb0));
    unsigned int n = 0;
    unsigned int tries = 0;
    do
    {
        unsigned int r = abs(FUN_42f1f0(10000)) % 6;
        tries++;
        if (tries > 8)
        {
            while (g_4d5bb0[r])
            {
                r = (r + 1) % 6;
            }
        }
        if (!g_4d5bb0[r])
        {
            g_4d5bb0[r] = 1;
            g_4d5b28[n] = r + 2;
            n++;
            tries = 0;
        }
    } while (n < 6);
}

// FUNCTION: STUNTGP_D3D 0x413190
void FUN_413190()
{
    FUN_413110();
    // STRING: STUNTGP_D3D 0x474640
    int len = strlen("grid");
    for (int i = 0; i < 6; i++)
    {
        if (g_60f02c[i].model)
        {
            for (char **names = g_60f02c[i].model->textures; *names; names++)
            {
                // STRING: STUNTGP_D3D 0x474648
                char *p = strstr(*names, "grid");
                if (p)
                {
                    int grid = g_60f02c[i].unk14;
                    if (!grid)
                    {
                        grid = g_4d5b28[i];
                    }
                    // STRING: STUNTGP_D3D 0x474650
                    sprintf(p + len, "%d", grid);
                }
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x413220
void FUN_413220()
{
    // STRING: STUNTGP_D3D 0x474654
    int len = strlen("tyre");
    for (int i = 0; i < 6; i++)
    {
        if (g_60f02c[i].model && g_60f02c[i].unk10)
        {
            for (char **names = g_60f02c[i].model->textures; *names; names++)
            {
                // STRING: STUNTGP_D3D 0x47465c
                char *p = strstr(*names, "tyre");
                if (p)
                {
                    // STRING: STUNTGP_D3D 0x474664
                    sprintf(p + len, "%d", g_60f02c[i].unk10);
                }
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x42b740
void FUN_42b740()
{
    g_4955e4 = &g_632cf8;
    g_4955e0 = &g_62f5d8;
    g_632cf8 = 0;
    g_62f5d8 = 0;
    if (g_612948.unk02a0 != 2)
    {
        if (g_636418[3].scene)
        {
            FUN_42b7f0(g_636418[3].scene, &g_4864e8, 0);
        }
        FUN_42b6e0();
        FUN_434030();
        if (g_636418[0].scene)
        {
            FUN_42b7f0(g_636418[0].scene, &g_4864e8, 0);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x42b7b0
void FUN_42b7b0(Scene *scene, int value)
{
    scene->flags |= 8;
    ObjectDef *object = scene->lods[scene->lod];
    value = (value << 8) | 0x80;
    for (DWORD i = 0; i < scene->objectCount; i++)
    {
        if (object->visible == 1)
        {
            object->flags |= value;
        }
        object++;
    }
}

// FUNCTION: STUNTGP_D3D 0x42b7e0
void FUN_42b7e0(WORD *flags)
{
    flags[1] &= 0xfff7;
}

// STUB: STUNTGP_D3D 0x42b7f0
void FUN_42b7f0(Scene *scene, Camera *camera, int arg)
{
}

// FUNCTION: STUNTGP_D3D 0x42b8b0
int FUN_42b8b0(Scene *scene, DWORD index, int lod)
{
    ObjectDef *objects = scene->lods[lod];
    ObjectDef *target = &objects[index];
    ObjectDef *object = objects;
    for (DWORD i = 0; i < index; i++)
    {
        if (object->verts == target->verts && object->vertCount != 0)
        {
            return 1;
        }
        object++;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x42b9a0
int FUN_42b9a0(const char *name)
{
    int result = 1;
    for (int i = 0; g_582b28[i] && result; i++)
    {
        result = strcmp(g_582b28[i], name);
    }
    return result;
}

// Offsets the texture index of every vertex by g_582724, once per shared vertex list.
// FUNCTION: STUNTGP_D3D 0x42b900
void FUN_42b900(Scene *scene)
{
    ObjectDef **lods = scene->lods;
    for (DWORD lod = 0; lod < scene->maxLod + 1; lod++, lods++)
    {
        ObjectDef *def = *lods;
        for (DWORD i = 0; i < scene->objectCount; i++, def++)
        {
            BYTE *verts = def->verts;
            if (!FUN_42b8b0(scene, i, lod))
            {
                BYTE *texture = verts + 1;
                for (DWORD j = 0; j < def->vertCount; j++, texture += 8)
                {
                    *texture += g_582724;
                }
            }
        }
    }
}

// Replaces texture index `from` with `to` in the vertices of every loaded track scene.
// FUNCTION: STUNTGP_D3D 0x42ba00
void FUN_42ba00(int from, int to)
{
    for (SceneSlot *slot = &g_636418[2]; slot->scene; slot++)
    {
        Scene *scene = slot->scene;
        for (DWORD lod = 0; lod < scene->maxLod + 1; lod++)
        {
            ObjectDef *def = scene->lods[lod];
            for (DWORD i = 0; i < scene->objectCount; i++, def++)
            {
                BYTE *texture = def->verts + 1;
                for (DWORD j = 0; j < def->vertCount; j++, texture += 8)
                {
                    if (*texture == from)
                    {
                        *texture = to;
                    }
                }
            }
        }
    }
}

extern char *g_582f28[255];

// Remaps scene texture indices from load order to their slot in the texture table.
// FUNCTION: STUNTGP_D3D 0x42ba90
void FUN_42ba90()
{
    for (int i = 0; g_582b28[i]; i++)
    {
        int j = 0;
        while (strcmp(g_582b28[i], g_582f28[j]))
        {
            j++;
        }
        if (i != j)
        {
            FUN_42ba00(i, j);
        }
    }
}

// Camera height for the race scene list.
// GLOBAL: STUNTGP_D3D 0x60dfa8
float g_60dfa8;

// FUNCTION: STUNTGP_D3D 0x42b620
void FUN_42b620(Scene *scene)
{
    GameSlot *slot = g_4722d0;
    Vec4 *pos = &scene->camera->pos;
    Vec4 d;
    d.x = pos->x - slot->cam.pos.x;
    d.y = pos->y - slot->cam.pos.y;
    d.z = pos->z - slot->cam.pos.z;
    float depth = (d.x * slot->axisZ.x + d.y * slot->axisZ.y + d.z * slot->axisZ.z) * 3.2f / slot->fov;
    scene->unk64 = scene->lod;
    if (depth > 5000.0f)
    {
        if (depth > 10000.0f)
        {
            scene->lod = 3;
        }
        else
        {
            scene->lod = 2;
        }
    }
    else if (depth > 3000.0f)
    {
        scene->lod = 1;
    }
    else
    {
        scene->lod = 0;
    }
    if (g_612948.unk0034 < 25)
    {
        scene->lod += 2;
    }
    else if (g_612948.unk0034 < 50)
    {
        scene->lod++;
    }
    if (scene->lod > 3)
    {
        scene->lod = 3;
    }
}

// Level of detail for a point, from its depth in front of the camera and the frame rate.
// FUNCTION: STUNTGP_D3D 0x42b580
DWORD FUN_42b580(Vec4 *pos)
{
    GameSlot *slot = g_4722d0;
    Vec4 d;
    d.x = pos->x - slot->cam.pos.x;
    d.y = pos->y - slot->cam.pos.y;
    d.z = pos->z - slot->cam.pos.z;
    float depth = (d.x * slot->axisZ.x + d.y * slot->axisZ.y + d.z * slot->axisZ.z) * 3.2f / slot->fov;
    DWORD lod;
    if (depth > 5000.0f)
    {
        if (depth > 10000.0f)
        {
            lod = 3;
        }
        else
        {
            lod = 2;
        }
    }
    else if (depth > 3000.0f)
    {
        lod = 1;
    }
    else
    {
        lod = 0;
    }
    if (g_612948.unk0034 < 25)
    {
        lod += 2;
    }
    else if (g_612948.unk0034 < 50)
    {
        lod++;
    }
    if (lod > 3)
    {
        lod = 3;
    }
    return lod;
}

// FUNCTION: STUNTGP_D3D 0x42b6e0
void FUN_42b6e0()
{
    if (g_636418[2].scene)
    {
        Camera camera = g_4864e8;
        camera.target.x += camera.pos.x;
        camera.pos.y = g_60dfa8;
        camera.target.y += camera.pos.y;
        camera.target.z += camera.pos.z;
        FUN_42b7f0(g_636418[2].scene, &camera, 0);
    }
}

// 8-byte face record of the dynamic mesh built by FUN_4342e0.
struct MeshFace
{
    BYTE count; // 0x00
    BYTE unk01; // 0x01
    BYTE unk02; // 0x02
    BYTE flags; // 0x03
    WORD unk04; // 0x04
    WORD index; // 0x06, first entry in the index buffer
};

struct MeshUv
{
    float u;     // 0x00
    float v;     // 0x04
    WORD point;  // 0x08
    WORD unk0a;  // 0x0a
    DWORD color; // 0x0c
};

// Buffer starts of the dynamic mesh, allocated by FUN_434090.
// GLOBAL: STUNTGP_D3D 0x5da234
MeshFace *g_5da234;

// GLOBAL: STUNTGP_D3D 0x5da238
WORD *g_5da238;

// GLOBAL: STUNTGP_D3D 0x5da23c
Vec4 *g_5da23c;

// GLOBAL: STUNTGP_D3D 0x5da240
MeshUv *g_5da240;

// GLOBAL: STUNTGP_D3D 0x5da244
ObjectDef *g_5da244;

// GLOBAL: STUNTGP_D3D 0x5da248
Scene *g_5da248;

// Write positions in the buffers above.
// GLOBAL: STUNTGP_D3D 0x5da24c
MeshFace *g_5da24c;

// GLOBAL: STUNTGP_D3D 0x5da250
WORD *g_5da250;

// GLOBAL: STUNTGP_D3D 0x5da254
Vec4 *g_5da254;

// GLOBAL: STUNTGP_D3D 0x5da258
MeshUv *g_5da258;

// GLOBAL: STUNTGP_D3D 0x5da25c
ObjectDef *g_5da25c;

// GLOBAL: STUNTGP_D3D 0x5da260
Scene *g_5da260;

// GLOBAL: STUNTGP_D3D 0x6249b0
int g_6249b0;

// FUNCTION: STUNTGP_D3D 0x434030
void FUN_434030()
{
    g_5da24c = g_5da234;
    g_5da250 = g_5da238;
    g_5da254 = g_5da23c;
    g_5da258 = g_5da240;
    g_5da25c = g_5da244;
    g_5da260 = g_5da248;
    g_6249b0 = g_5da25c->vertCount;
    g_5da25c->vertCount = 0;
    g_5da25c->unk26 = 0;
    g_5da25c->pointCount = 0;
}

// STUB: STUNTGP_D3D 0x42c510
void FUN_42c510()
{
}

// STUB: STUNTGP_D3D 0x42d070
void FUN_42d070()
{
}

struct Unk624488
{
    int unk00;   // 0x00
    int unk04;   // 0x04
    int unk08;   // 0x08
    int unk0c;   // 0x0c
    float unk10; // 0x10
};

// GLOBAL: STUNTGP_D3D 0x589628
RenderMaterial g_589628;

// GLOBAL: STUNTGP_D3D 0x5898d0
Ambience g_5898d0;

// No reference lands between this and 0x589df8, so the count is the size of that gap.
// GLOBAL: STUNTGP_D3D 0x5898f8
Unk624488 g_5898f8[64];

// GLOBAL: STUNTGP_D3D 0x589e04
RenderMaterial *g_589e04;

// GLOBAL: STUNTGP_D3D 0x624488
Unk624488 *g_624488;

// GLOBAL: STUNTGP_D3D 0x624494
Ambience *g_624494;

// GLOBAL: STUNTGP_D3D 0x62452c
int g_62452c;

// FUNCTION: STUNTGP_D3D 0x42d970
void FUN_42d970()
{
    RenderMaterial *material = g_62447c;
    for (DWORD i = 0; i < g_62449c; i++)
    {
        if (material->unk50 == 3)
        {
            g_589e04 = material;
            return;
        }
        material++;
    }
    g_589e04 = g_62447c;
}

// FUNCTION: STUNTGP_D3D 0x42d700
void FUN_42d700()
{
    if (g_612948.unk02a0 == 2)
    {
        g_589e04 = 0;
        g_62447c = &g_589628;
        g_62449c = 0;
        g_62452c = 0;
        g_624494 = &g_5898d0;
        g_624488 = g_5898f8;
    }
    RenderMaterial *material = g_62447c;
    for (DWORD i = 0; i < g_62449c; i++)
    {
        if (material->unk00 == 1 && material->unk04 == 1)
        {
            float alpha = material->alpha * 4.75f;
            material->alpha = alpha * alpha;
        }
        else
        {
            float g = material->unk6c * material->alpha;
            float b = material->unk70 * material->alpha;
            float r = material->unk68 * material->alpha;
            material->unk78 = (int)r;
            material->unk7c = (int)g;
            material->unk80 = (int)b;
        }
        material++;
    }
    g_624504 = *g_624494;
    FUN_42d7e0();
    FUN_42d970();
}

// Rescales the vertex colours of every object; the scale is full brightness, so it is a no-op.
// FUNCTION: STUNTGP_D3D 0x42e240
void FUN_42e240(Scene *scene)
{
    for (DWORD lod = 0; lod < scene->maxLod + 1; lod++)
    {
        for (DWORD i = 0; i < scene->objectCount; i++)
        {
            if (!FUN_42b8b0(scene, i, lod))
            {
                ObjectDef *def = &scene->lods[lod][i];
                BYTE *v = def->unk2c;
                for (DWORD j = 0; j < def->unk26; j++, v += 16)
                {
                    v[0xf] = v[0xf] * 255 / 255;
                    v[0xe] = v[0xe] * 255 / 255;
                    v[0xd] = v[0xd] * 255 / 255;
                    v[0xc] = v[0xc] * 255 / 255;
                }
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x42e380
void FUN_42e380()
{
    SceneSlot *slot = g_6244f8 == 1 ? &g_636418[2] : g_636418;
    while (slot->scene)
    {
        FUN_42e240(slot->scene);
        slot++;
    }
    for (DWORD i = 0; i < g_62449c; i++)
    {
        g_62447c[i].alpha = g_62447c[i].alpha * 255.0f * (1.0f / 255.0f);
    }
}

// FUNCTION: STUNTGP_D3D 0x42e3e0
void FUN_42e3e0()
{
    g_6249a0 = 0;
    g_6249a4 = 256;
    if (g_477c30 >= 0x3ffff8)
    {
        // STRING: STUNTGP_D3D 0x477c34
        sprintf(g_GraphicsDirectory, "%s\\Graphics24\\", g_GameLocation);
    }
}

// GLOBAL: STUNTGP_D3D 0x61c594
float g_61c594[16];

// GLOBAL: STUNTGP_D3D 0x61c5f4
void *g_61c5f4;

// GLOBAL: STUNTGP_D3D 0x61c5f8
void *g_61c5f8;

// GLOBAL: STUNTGP_D3D 0x61c5fc
void *g_61c5fc;

// GLOBAL: STUNTGP_D3D 0x61c600
void *g_61c600;

// GLOBAL: STUNTGP_D3D 0x61c518
VisIndexList *g_61c518;

// GLOBAL: STUNTGP_D3D 0x61c51c
VisIndexList *g_61c51c;

// GLOBAL: STUNTGP_D3D 0x624530
void *g_624530;

// Allocates the per-frame render buffers.
// FUNCTION: STUNTGP_D3D 0x42e430
void FUN_42e430()
{
    g_61c50c = (int)Mem_Alloc(0x78000, 0);
    g_6244c8 = (int)Mem_Alloc(0xc000, 0);
    g_6244cc = (int)Mem_Alloc(0x2000, 0);
    g_6244d0 = (int)Mem_Alloc(0x800, 0);
    g_61c5ec = (int)Mem_Alloc(0xc000, 0);
    g_61c5f4 = Mem_Alloc(0xf000, 0);
    g_61c5f8 = Mem_Alloc(0xf000, 0);
    g_61c5fc = Mem_Alloc(0xf000, 0);
    g_61c600 = Mem_Alloc(0xf000, 0);
    g_61c5f0 = (OverlayPoly *)Mem_Alloc(0x11000, 0);
    g_61c518 = (VisIndexList *)Mem_Alloc(0x1000, 0);
    g_61c51c = (VisIndexList *)Mem_Alloc(0x1000, 0);
    g_624530 = Mem_Alloc(0x4800, 0);
}

void FUN_41c710();
void FUN_42eb00();
extern BYTE g_61c7cc[0x6000];
extern BYTE *g_6227cc;
extern int g_6227d0;
extern BYTE g_61c608[0x1c0];
extern BYTE *g_61c7c8;
extern short g_6244a8[16];
extern int g_6244d4;
extern int g_6244d8;
extern int g_6244dc;
extern int g_6244e0;
extern int g_6244e4;
extern int g_61c510;
extern int g_61c514;
extern int g_61c520;
extern int g_624460;
extern BYTE *g_624464;
extern BYTE *g_624468;
extern BYTE *g_62446c;
extern BYTE *g_624470;
extern CameraPath *g_624474;
extern BYTE *g_624478;
extern Unk624488 *g_624488;
extern SceneEntry *g_62448c;
extern SceneEntry *g_624490;
extern Ambience *g_624494;
extern DWORD g_624498;
extern DWORD g_62449c;
extern int g_6244a0;
extern int g_6244a4;

// GLOBAL: STUNTGP_D3D 0x61c524
VisIndexList *g_61c524;

// GLOBAL: STUNTGP_D3D 0x61c528
VisIndexList *g_61c528;

// GLOBAL: STUNTGP_D3D 0x61c52c
Scene *g_61c52c;

// GLOBAL: STUNTGP_D3D 0x61c530
ObjectDef *g_61c530;

// GLOBAL: STUNTGP_D3D 0x61c5e8
int g_61c5e8;

// Clears all scene, render-list and track pointers before a level loads.
// FUNCTION: STUNTGP_D3D 0x42e510
void FUN_42e510()
{
    for (int i = 0; i < 16; i++)
    {
        g_636418[i].scene = NULL;
        g_636418[i].data = NULL;
        g_636418[i].size = 0;
    }
    FUN_41c710();
    g_61c5ec = 0;
    memset(g_62dcf0, 0, sizeof(g_62dcf0));
    memset(g_62d480, 0, sizeof(g_62d480));
    g_61c5f4 = NULL;
    g_61c5f8 = NULL;
    g_61c5fc = NULL;
    g_61c600 = NULL;
    g_61c5f0 = NULL;
    g_61c518 = NULL;
    g_61c51c = NULL;
    g_624530 = NULL;
    memset(g_61c7cc, 0, sizeof(g_61c7cc));
    g_6227cc = NULL;
    g_6227d0 = 0;
    g_61c52c = NULL;
    g_61c530 = NULL;
    g_61c5e4 = -1;
    g_61c50c = 0;
    g_61c510 = 0;
    g_61c514 = 0;
    g_61c5e8 = 0;
    g_61c520 = 0;
    g_61c604 = 0;
    memset(g_61c608, 0, sizeof(g_61c608));
    g_61c7c8 = NULL;
    memset(g_6227d4, 0, 255 * sizeof(TextureSlot));
    g_6243b8 = NULL;
    // g_6243c0..g_6243dc are four contiguous {list, count} pairs.
    memset(&g_6243c0, 0, 0x20);
    memset(g_6243e0, 0, sizeof(g_6243e0));
    g_61c524 = NULL;
    g_61c528 = NULL;
    memset(g_6244a8, 0, sizeof(g_6244a8));
    g_6244c8 = 0;
    g_6244cc = 0;
    g_6244d0 = 0;
    g_6244d4 = 0;
    g_6244d8 = 0;
    g_6244dc = 0;
    g_6244e0 = 0;
    g_6244e4 = 0;
    g_624460 = 0;
    g_624464 = NULL;
    g_624468 = NULL;
    g_62446c = NULL;
    g_624470 = NULL;
    g_624474 = NULL;
    g_624478 = NULL;
    g_62447c = NULL;
    g_624480 = NULL;
    g_624484 = NULL;
    g_624488 = NULL;
    g_62448c = NULL;
    g_624490 = NULL;
    g_624494 = NULL;
    g_624498 = 0;
    g_62449c = 0;
    g_6244a0 = 0;
    g_6244a4 = 0;
    FUN_42eb00();
}

// GLOBAL: STUNTGP_D3D 0x624988
int g_624988;

// GLOBAL: STUNTGP_D3D 0x62498c
int g_62498c;

// GLOBAL: STUNTGP_D3D 0x61c508
DWORD g_61c508;

// GLOBAL: STUNTGP_D3D 0x61c510
int g_61c510;

// GLOBAL: STUNTGP_D3D 0x61c514
int g_61c514;

// GLOBAL: STUNTGP_D3D 0x61c520
int g_61c520;

// GLOBAL: STUNTGP_D3D 0x61c5ec
int g_61c5ec;

// FUNCTION: STUNTGP_D3D 0x42e800
void FUN_42e800()
{
    g_61c510 = g_61c50c;
    g_61c520 = g_61c5ec;
}

// Detail level from the menu setting; g_589e08 forces specular off.
// FUNCTION: STUNTGP_D3D 0x42e820
void FUN_42e820()
{
    g_624980 = 0;
    g_624984 = 0;
    if (g_612948.unk0034 > 80)
    {
        g_624980 = 1;
        g_624984 = 1;
    }
    else if (g_612948.unk0034 > 50)
    {
        g_624980 = 1;
        g_624984 = 0;
    }
    if (g_589e08 == 1)
    {
        g_624984 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x42eb70
void FUN_42eb70()
{
    TrackHeader *header = g_58d810;
    int *offsets = (int *)&header->data[header->unk038];
    for (int i = 0; offsets[i]; i++)
    {
        offsets[i] = (int)&header->data[offsets[i]];
    }
}

// FUNCTION: STUNTGP_D3D 0x42ebb0
void FUN_42ebb0()
{
    BYTE *base = &g_58d810->data[g_58d810->unk03c];
    DWORD *p = g_58c800->unk40;
    for (DWORD i = 0; i < g_58d810->unk0d4 / 4; i++)
    {
        p[i] = (DWORD)&base[p[i] * 16];
    }
}

// Resolves the scene header's file offsets into pointers.
// FUNCTION: STUNTGP_D3D 0x42ebf0
void FUN_42ebf0()
{
    TrackHeader *header = g_58d810;
    Scene *scene = (Scene *)&header->data[header->unk04c];
    g_58c800 = scene;
    scene->unk28 = (SceneEntry *)&header->data[header->unk020];
    scene->verts = &header->data[header->unk024];
    scene->unk30 = &header->data[header->unk028];
    scene->points = (Vec4 *)&header->data[header->unk02c];
    scene->unk38 = &header->data[header->unk030];
    scene->matrices = &header->data[header->unk044];
    scene->unk40 = (DWORD *)&header->data[header->unk040];
    scene->view = (SceneView *)&header->data[header->unk048];
    scene->textures = (char **)&header->data[header->unk038];
    for (int i = 0; i < 4; i++)
    {
        scene->lods[i] = (ObjectDef *)scene->view + (int)scene->lods[i];
    }
}

// Resolves each mesh's indices into the scene's shared arrays.
// FUNCTION: STUNTGP_D3D 0x42eca0
void FUN_42eca0()
{
    Scene *scene = g_58c800;
    DWORD lodCount = scene->maxLod + 1;
    for (DWORD lod = 0; lod < lodCount; lod++)
    {
        ObjectDef *def = scene->lods[lod];
        for (DWORD i = 0; i < scene->objectCount; i++, def++)
        {
            def->matrix = (Vec4 *)(scene->matrices + (int)def->matrix * 0x50);
            def->unk2c = scene->unk30 + (int)def->unk2c * 16;
            def->points = scene->points + (int)def->points;
            def->verts = scene->verts + (int)def->verts * 8;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x42ed30
void FUN_42ed30()
{
    g_624470 = &g_58d810->data[g_58d810->unk088];
    g_62446c = &g_58d810->data[g_58d810->unk07c];
    g_624468 = &g_58d810->data[g_58d810->unk084];
    g_624464 = &g_58d810->data[g_58d810->unk080];
}

// FUNCTION: STUNTGP_D3D 0x42ed80
void FUN_42ed80()
{
    TrackHeader *header = g_58d810;
    TrackOctree *tree = (TrackOctree *)&header->data[header->unk0a0];
    g_624480 = tree;
    tree->polyLists = (short *)&header->data[header->unk090] + (int)tree->polyLists;
    tree->indices = (WORD *)&header->data[header->unk08c] + (int)tree->indices;
    tree->vertices = (Vec4 *)&header->data[header->unk02c] + (int)tree->vertices;
    tree->planes = (Vec4 *)&header->data[header->unk020] + (int)tree->planes;
    tree->polys = (TrackPoly *)&header->data[header->unk098] + (int)tree->polys;
    tree->surfaces = (DWORD *)&header->data[header->unk094] + (int)tree->surfaces;
    for (int i = 0; i < 2; i++)
    {
        tree->roots[i].root = (OctNode *)&header->data[header->unk09c] + (int)tree->roots[i].root;
    }
}

// FUNCTION: STUNTGP_D3D 0x42ee50
void FUN_42ee50()
{
    TrackHeader *header = g_58d810;
    CameraPath *paths = (CameraPath *)&header->data[header->unk078];
    DWORD count = header->unk10c / sizeof(CameraPath);
    for (DWORD i = 0; i < count; i++)
    {
        paths[i].points = (Vec4 *)&header->data[header->unk074] + (int)paths[i].points;
    }
    g_624474 = paths;
    g_624498 = count;
}

// FUNCTION: STUNTGP_D3D 0x42eee0
void FUN_42eee0()
{
    g_62449c = g_58d810->unk0fc;
    g_6244a0 = g_58d810->unk100;
    g_62447c = (RenderMaterial *)&g_58d810->data[g_58d810->unk070];
    g_624494 = (Ambience *)&g_58d810->data[g_58d810->unk064];
}

// FUNCTION: STUNTGP_D3D 0x42ef20
void FUN_42ef20()
{
    g_6244a4 = g_58d810->unk0e8;
    g_624478 = &g_58d810->data[g_58d810->unk058];
}

// FUNCTION: STUNTGP_D3D 0x42ef50
void FUN_42ef50()
{
    g_624484 = (AnimDef *)&g_58d810->data[g_58d810->unk060];
    g_624488 = (Unk624488 *)&g_58d810->data[g_58d810->unk05c];
}

// FUNCTION: STUNTGP_D3D 0x42ef80
void FUN_42ef80()
{
    g_62448c = g_58c800->unk28;
    g_624490 = g_58c800->unk28 + g_58d810->unk0e4;
}

// STUB: STUNTGP_D3D 0x425ad0
void FUN_425ad0()
{
}

// STUB: STUNTGP_D3D 0x42dcf0
void FUN_42dcf0()
{
}

// STUB: STUNTGP_D3D 0x42b040
void FUN_42b040()
{
}

// FUNCTION: STUNTGP_D3D 0x42b100
void FUN_42b100()
{
    memset(g_6243e0, 0, sizeof(g_6243e0));
    g_6243c0 = g_61c5fc;
    g_6243c8 = g_61c600;
    g_6243d0 = g_61c5f4;
    g_6243d8 = g_61c5f8;
}

// FUNCTION: STUNTGP_D3D 0x42b140
void FUN_42b140(void **out)
{
    out[6] = g_6243d8;
    out[4] = g_6243d0;
    out[0] = g_6243c0;
    out[5] = 0;
    out[7] = 0;
    out[1] = 0;
    out[2] = g_6243c8;
    out[3] = 0;
}

// FUNCTION: STUNTGP_D3D 0x42b180
void FUN_42b180(int *out)
{
    out[5] = ((int)g_6243d0 - out[4]) / 20;
    out[7] = ((int)g_6243d8 - out[6]) / 20;
    out[1] = ((int)g_6243c0 - out[0]) / 20;
    out[3] = ((int)g_6243c8 - out[2]) / 20;
}

// FUNCTION: STUNTGP_D3D 0x42b200
void FUN_42b200()
{
    g_6243c4 = ((int)g_6243c0 - (int)g_61c5fc) / 20;
    g_6243cc = ((int)g_6243c8 - (int)g_61c600) / 20;
    g_6243d4 = ((int)g_6243d0 - (int)g_61c5f4) / 20;
    g_6243dc = ((int)g_6243d8 - (int)g_61c5f8) / 20;
}

extern int g_6244d4;
extern int g_6244e4;
extern int g_61c510;
extern int g_61c514;
extern int g_61c520;

// Perspective-divides the queued vertex lists into screen space.
// FUNCTION: STUNTGP_D3D 0x429a40
void FUN_429a40()
{
    float offY;
    float scaleY;
    float offX;
    float scaleX;
    scaleX = g_576b9c;
    scaleY = g_576ba0;
    offX = g_576b94;
    offY = g_576b98;
    int n = (g_61c520 - g_61c5ec) >> 2;
    float **list = (float **)g_61c5ec;
    while (n-- > 0)
    {
        float *v = *list++;
        float s = 1.0f / (v[7] + 1.0f);
        v[0] = s * v[0] * scaleX + offX;
        v[1] = s * v[1] * scaleY + offY;
        v[7] = s * 32.0f;
    }
    float *v = (float *)g_6244d4;
    n = (g_6244e4 - g_6244d4) >> 5;
    while (n-- > 0)
    {
        float s = 1.0f / (v[7] + 1.0f);
        v[0] = s * v[0] * scaleX + offX;
        v[1] = s * v[1] * scaleY + offY;
        v[7] = s * 32.0f;
        v += 8;
    }
    n = (g_61c510 - g_61c514) >> 5;
    v = (float *)g_61c514;
    while (n-- > 0)
    {
        float s = 1.0f / (v[7] + 1.0f);
        v[0] = s * v[0] * scaleX + offX;
        v[1] = s * v[1] * scaleY + offY;
        v[7] = s * 32.0f;
        v += 8;
    }
}

// GLOBAL: STUNTGP_D3D 0x61c4e8
Vec4 g_61c4e8;

// GLOBAL: STUNTGP_D3D 0x61c4f8
Vec4 g_61c4f8;

// FUN_429d50 for partly clipped objects: also skips polygons with every vertex outside one frustum
// side and stores the vertices' shared outcodes in unk10.
// FUNCTION: STUNTGP_D3D 0x429b70
void FUN_429b70(Scene *scene, ObjectDef *obj, PolyRef **lists)
{
    DWORD blend = 0;
    if ((scene->flags & 8) && (obj->flags & 0x80))
    {
        blend = obj->flags >> 8;
    }
    Vec4 *normals = (Vec4 *)scene->unk28;
    WORD *refs = (WORD *)scene->unk38;
    Vec4 *points = obj->points;
    BYTE *src = obj->unk2c;
    DWORD count = obj->vertCount;
    PolyRef *opaque = lists[0];
    PolyRef *blended = lists[2];
    DWORD *poly = (DWORD *)obj->verts;
    for (DWORD i = 0; i < count; i++)
    {
        DWORD any = 0;
        DWORD all = 0x3f;
        WORD *ref = &refs[((WORD *)poly)[3]];
        DWORD n = poly[0] & 0xff;
        {
            WORD *r = ref;
            BYTE *e;
            while (n-- > 0)
            {
                e = src + *r++ * 16;
                DWORD code = *(WORD *)(g_61c510 + *(WORD *)(e + 8) * 32 + 16);
                any |= code;
                all &= code;
            }
            if (any == 0x3f)
            {
                Vec4 *p = &points[*(WORD *)(e + 8)];
                Vec4 d;
                d.x = p->x - g_61c4e8.x;
                d.y = p->y - g_61c4e8.y;
                d.z = p->z - g_61c4e8.z;
                Vec4 *nrm = &normals[((WORD *)poly)[2]];
                if ((int)poly[0] < 0 || d.x * nrm->x + d.y * nrm->y + d.z * nrm->z < 0.0f)
                {
                    if (!blend && !(poly[0] & 0x40000000))
                    {
                        opaque->poly = poly;
                        opaque->ref = ref;
                        opaque->verts = g_61c510;
                        opaque->src = src;
                        opaque->unk10 = all;
                        opaque++;
                    }
                    else
                    {
                        blended->poly = poly;
                        blended->ref = ref;
                        blended->verts = g_61c510;
                        blended->src = src;
                        blended->unk10 = all;
                        blended++;
                    }
                }
            }
        }
        poly += 2;
    }
    lists[0] = opaque;
    lists[2] = blended;
}

// Queues the object's camera-facing polygons into the opaque (lists[0]) or blended (lists[2]) list.
// FUNCTION: STUNTGP_D3D 0x429d50
void FUN_429d50(Scene *scene, ObjectDef *obj, PolyRef **lists)
{
    DWORD blend = 0;
    if ((scene->flags & 8) && (obj->flags & 0x80))
    {
        blend = obj->flags >> 8;
    }
    Vec4 *normals = (Vec4 *)scene->unk28;
    WORD *refs = (WORD *)scene->unk38;
    Vec4 *points = obj->points;
    BYTE *src = obj->unk2c;
    DWORD count = obj->vertCount;
    PolyRef *opaque = lists[0];
    PolyRef *blended = lists[2];
    DWORD *poly = (DWORD *)obj->verts;
    for (DWORD i = 0; i < count; i++)
    {
        WORD *ref = &refs[((WORD *)poly)[3]];
        Vec4 *p = &points[*(WORD *)(src + *ref * 16 + 8)];
        Vec4 d;
        d.x = p->x - g_61c4e8.x;
        d.y = p->y - g_61c4e8.y;
        d.z = p->z - g_61c4e8.z;
        Vec4 *n = &normals[((WORD *)poly)[2]];
        if ((int)poly[0] < 0 || d.x * n->x + d.y * n->y + d.z * n->z < 0.0f)
        {
            if (!blend && !(poly[0] & 0x40000000))
            {
                opaque->ref = ref;
                opaque->poly = poly;
                opaque->verts = g_61c510;
                opaque->src = src;
                opaque++;
            }
            else
            {
                blended->ref = ref;
                blended->poly = poly;
                blended->verts = g_61c510;
                blended->src = src;
                blended++;
            }
        }
        poly += 2;
    }
    lists[0] = opaque;
    lists[2] = blended;
}

// Polygons queued for the track so far.
// GLOBAL: STUNTGP_D3D 0x61c550
DWORD g_61c550;

// FUN_429d50 for the track: queues the camera-facing polygons of the visible meshes of g_61c530.
// FUNCTION: STUNTGP_D3D 0x42a090
void FUN_42a090(PolyRef **lists, VisIndexList *vis, DWORD count)
{
    PolyRef *blended = lists[2];
    PolyRef *opaque = lists[0];
    Vec4 *normals = (Vec4 *)g_61c52c->unk28;
    WORD *refs = (WORD *)g_61c52c->unk38;
    Vec4 *points = g_61c530->points;
    g_61c550 += count;
    BYTE *src = g_61c530->unk2c;
    for (DWORD i = 0; i < count; i++)
    {
        WORD *idx = vis->polys;
        while (*idx != 0xffff)
        {
            DWORD *poly = (DWORD *)(g_61c530->verts + *idx * 8);
            WORD *ref = &refs[((WORD *)poly)[3]];
            Vec4 *p = &points[*(WORD *)(src + *ref * 16 + 8)];
            Vec4 d;
            d.x = p->x - g_61c4e8.x;
            d.y = p->y - g_61c4e8.y;
            d.z = p->z - g_61c4e8.z;
            Vec4 *n = &normals[((WORD *)poly)[2]];
            if ((int)poly[0] < 0 || d.x * n->x + d.y * n->y + d.z * n->z < 0.0f)
            {
                if (poly[0] & 0x40000000)
                {
                    blended->poly = poly;
                    blended->ref = ref;
                    blended->verts = g_61c510;
                    blended->src = src;
                    blended++;
                }
                else
                {
                    opaque->poly = poly;
                    opaque->ref = ref;
                    opaque->verts = g_61c510;
                    opaque->src = src;
                    opaque++;
                }
            }
            idx++;
        }
        vis++;
    }
    lists[0] = opaque;
    lists[2] = blended;
}

// FUNCTION: STUNTGP_D3D 0x42a840
void FUN_42a840(Scene *scene)
{
    if (g_576be0)
    {
        g_62497c = 1;
        return;
    }
    g_62497c = scene->lod != scene->unk64 ? 1 : 4;
}

// Clips the eight corners of bounding box `box` against the view frustum, using the
// plane distances' sign bits as outcodes: 0 outside, 1 partly visible, 2 inside.
// FUNCTION: STUNTGP_D3D 0x42aa70
int FUN_42aa70(int box)
{
    float l;
    float r;
    float t;
    float b;
    Vec4 *corner = (Vec4 *)(g_62446c + box * 16);
    DWORD all = 0x3f;
    DWORD any = 0;
    DWORD n = 8;
    while (n-- > 0)
    {
        float dx = corner->x - g_4722d0->cam.pos.x;
        float dy = corner->y - g_4722d0->cam.pos.y;
        float dz = corner->z - g_4722d0->cam.pos.z;
        l = dx * g_4722d0->planeLeft.x + (dy * g_4722d0->planeLeft.y + dz * g_4722d0->planeLeft.z);
        r = dx * g_4722d0->planeRight.x + dz * g_4722d0->planeRight.z + dy * g_4722d0->planeRight.y;
        t = dz * g_4722d0->planeTop.z + dy * g_4722d0->planeTop.y + dx * g_4722d0->planeTop.x;
        b = dx * g_4722d0->planeBottom.x + (dy * g_4722d0->planeBottom.y + dz * g_4722d0->planeBottom.z);
        DWORD code = ((((((*(DWORD *)&l | 0x60000000) >> 1) | (*(DWORD *)&r & 0xbfffffff)) >> 1) |
                       (*(DWORD *)&t & 0x9fffffff)) >> 1 |
                      (*(DWORD *)&b & 0x8fffffff)) >> 26;
        if (code == 0x3f && all != 0x3f)
        {
            return 2;
        }
        all &= code;
        any |= code;
        corner++;
    }
    if (all == 0x3f)
    {
        return 0;
    }
    return (any == 0x3f) + 1;
}

// FUNCTION: STUNTGP_D3D 0x42a870
void FUN_42a870(Scene *scene, ObjectDef *object)
{
    if (g_576be0)
    {
        g_62497c = 1;
        return;
    }
    if (scene->lod != scene->unk64)
    {
        g_62497c = 1;
        return;
    }
    if (object->unk04 >= 2 && object->unk04 <= 5)
    {
        g_62497c = 1;
    }
    else
    {
        g_62497c = 4;
    }
}

// Brings the view position into the object's local space (out) and gives its direction (dir).
// FUNCTION: STUNTGP_D3D 0x42b2a0
void FUN_42b2a0(Vec4 *out, Vec4 *dir, Scene *scene, ObjectDef *obj)
{
    Vec4 t;
    Camera *cam = scene->camera;
    float dx = g_4722d0->cam.pos.x - cam->pos.x;
    float dy = g_4722d0->cam.pos.y - cam->pos.y;
    float dz = g_4722d0->cam.pos.z - cam->pos.z;
    float *m = (float *)cam->matrix;
    t.x = dz * m[8] + dy * m[4] + dx * m[0];
    t.y = dz * m[9] + dy * m[5] + dx * m[1];
    t.z = dz * m[10] + dy * m[6] + dx * m[2];
    Camera *xf = (Camera *)obj->matrix;
    t.x -= xf->pos.x;
    t.y -= xf->pos.y;
    t.z -= xf->pos.z;
    if (scene->objectCount > 1)
    {
        Vec4 *pivot = (Vec4 *)((BYTE *)obj + 0x10);
        float *r = (float *)xf->unk44;
        t.x -= pivot->x;
        t.y -= pivot->y;
        t.z -= pivot->z;
        out->x = t.z * r[8] + t.y * r[4] + t.x * r[0] + pivot->x;
        out->y = t.z * r[9] + t.y * r[5] + t.x * r[1] + pivot->y;
        out->z = t.z * r[10] + t.y * r[6] + t.x * r[2] + pivot->z;
    }
    else
    {
        *out = t;
    }
    t = *out;
    Vec3_Normalize(&t.x);
    *dir = t;
}

void FUN_44efd0(float *out, float *a, float *b);

struct Light
{
    BYTE unk00[0x10]; // 0x00
    Vec4 pos;         // 0x10
    Vec4 local;       // 0x20, pos relative to the current object
    Vec4 colour;      // 0x30
};

// Per-object light record in g_624530, 36 bytes.
struct LightRec
{
    Vec4 colour; // 0x00, rotated into object space
    Vec4 half;   // 0x10
    Light *light; // 0x20
};

// Lights active for the current object (g_62452c of them) and the next free record in g_624530.
struct LightList
{
    Light *lights[16]; // 0x00
    LightRec *next;    // 0x40
};

// GLOBAL: STUNTGP_D3D 0x624534
LightList g_624534;

// Brings the active lights into the object's space: per light its rotated colour, its offset
// from the object and the half vector towards the view.
// FUNCTION: STUNTGP_D3D 0x42b400
void FUN_42b400(Scene *scene, ObjectDef *obj)
{
    float m[16];
    Vec4 view;
    Vec4 origin;
    Vec4 h;
    Camera *cam = scene->camera;
    view.x = g_61c4f8.x * 255.0f;
    view.y = g_61c4f8.y * 255.0f;
    view.z = g_61c4f8.z * 255.0f;
    float *rot = (float *)cam->matrix;
    if (scene->objectCount > 1)
    {
        FUN_44efd0(m, rot, (float *)((Camera *)obj->matrix)->unk44);
        rot = m;
    }
    Camera *xf = (Camera *)obj->matrix;
    origin.x = xf->pos.x + cam->pos.x;
    origin.y = xf->pos.y + cam->pos.y;
    origin.z = xf->pos.z + cam->pos.z;
    g_624534.next = (LightRec *)g_624530;
    Light **lights = g_624534.lights;
    for (DWORD i = 0; i < g_62452c; i++)
    {
        Light *light = *lights++;
        float r = light->colour.x * 255.0f;
        float g = light->colour.y * 255.0f;
        float b = light->colour.z * 255.0f;
        g_624534.next->colour.x = g * rot[4] + b * rot[8] + r * rot[0];
        g_624534.next->colour.y = g * rot[5] + b * rot[9] + r * rot[1];
        g_624534.next->colour.z = g * rot[6] + b * rot[10] + r * rot[2];
        light->local.x = light->pos.x - origin.x;
        light->local.y = light->pos.y - origin.y;
        light->local.z = light->pos.z - origin.z;
        h.x = view.x + g_624534.next->colour.x;
        h.y = view.y + g_624534.next->colour.y;
        h.z = view.z + g_624534.next->colour.z;
        h.x *= 765.0f;
        h.y *= 765.0f;
        h.z *= 765.0f;
        g_624534.next->half.x = h.x * 0.5f;
        g_624534.next->half.y = h.y * 0.5f;
        g_624534.next->half.z = h.z * 0.5f;
        g_624534.next->light = light;
        g_624534.next++;
    }
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
    if (g_636418[3].scene)
    {
        g_636418[3].scene->camera = &g_4864e8;
    }
    g_6244f8 = 0;
    FUN_431420();
    FUN_4312c0();
    g_6244f8 = 1;
    g_57b41c = 0;
}

// GLOBAL: STUNTGP_D3D 0x58c230
int g_58c230;

// GLOBAL: STUNTGP_D3D 0x58c538
BYTE *g_58c538;

// GLOBAL: STUNTGP_D3D 0x58c540
SceneLoad g_58c540[24];

// GLOBAL: STUNTGP_D3D 0x58c600
BYTE g_58c600[0x200];

// GLOBAL: STUNTGP_D3D 0x58c808
int g_58c808;

// GLOBAL: STUNTGP_D3D 0x58c80c
BYTE *g_58c80c;

// GLOBAL: STUNTGP_D3D 0x58c810
BYTE g_58c810[0x1000];

// GLOBAL: STUNTGP_D3D 0x58c234
int g_58c234;

// GLOBAL: STUNTGP_D3D 0x58c238
BYTE g_58c238[0x300];

// GLOBAL: STUNTGP_D3D 0x58d814
int g_58d814;

// FUNCTION: STUNTGP_D3D 0x42eb00
void FUN_42eb00()
{
    memset(g_58c238, 0, sizeof(g_58c238));
    memset(g_58c540, 0, sizeof(g_58c540));
    memset(g_58c810, 0, sizeof(g_58c810));
    memset(g_58c600, 0, sizeof(g_58c600));
    g_58c234 = 0;
    g_58c808 = 0;
    g_58c800 = NULL;
    g_58d810 = NULL;
    g_58c230 = 0;
    g_58c538 = NULL;
    g_58c80c = NULL;
    g_58d814 = 0;
}

// Scene slots of each car's two models.
// GLOBAL: STUNTGP_D3D 0x477c4c
int g_477c4c[6] = {4, 6, 8, 10, 12, 14};

// GLOBAL: STUNTGP_D3D 0x477c64
int g_477c64[6] = {5, 7, 9, 11, 13, 15};

// STUB: STUNTGP_D3D 0x42efb0
void FUN_42efb0(int id)
{
}

// FUNCTION: STUNTGP_D3D 0x42f090
void FUN_42f090()
{
    if (g_612948.unk02a0 == 2)
    {
        g_58c540[0].id = 0;
        g_58c808 = 0;
    }
    memset(g_58c810, 0, sizeof(g_58c810));
    g_58c80c = g_58c810;
    g_58c538 = g_58c600;
    for (SceneLoad *load = g_58c540; load->id;)
    {
        FUN_42efb0(load->id);
        int slot = load->slot;
        load++;
        g_636418[slot].scene = g_58c800;
        g_636418[slot].data = g_58d810;
        g_636418[slot].size = g_58c230;
    }
    int car = 0;
    for (int i = 0; i < 6; i++)
    {
        if (g_60d730.entries[i].type == 2)
        {
            g_60f02c[i].model = g_636418[g_477c4c[car]].scene;
            g_60f02c[i].unk04 = g_636418[g_477c64[car]].scene;
            car++;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x431300
void FUN_431300()
{
    FUN_4328c0(0);
    FUN_432a60();
    FUN_4328c0(0);
    FUN_432a60();
    FUN_4328c0(0);
    FUN_432a60();
    FUN_431790();
    FUN_430690();
}

// FUNCTION: STUNTGP_D3D 0x431330
void FUN_431330()
{
    // STRING: STUNTGP_D3D 0x478874
    exitError("There was an error Initializing D3D!\n");
    exit(1);
}

// FUNCTION: STUNTGP_D3D 0x431350
void FUN_431350()
{
}

extern int g_D3DDeviceIndex;
extern int g_D3DDriverIndex;
extern int g_6244f0;
extern int g_DD_DISPLAYRESHEIGHT;
void FUN_42f300();
void FUN_42f6a0();
int FUN_42fd80(int device);
void FUN_42ff20(int device, int driver);
void FUN_42fff0();
int FUN_430020(int device, int driver);
int FUN_42f840();
int FUN_430ff0();
BOOL FUN_42fa80();
void FUN_432070();
void FUN_42f220();

// Brings up DirectDraw and Direct3D on the configured device and driver; any failure ends in
// FUN_431330.
// FUNCTION: STUNTGP_D3D 0x431360
void FUN_431360()
{
    int device = g_D3DDeviceIndex;
    int driver = g_D3DDriverIndex;
    g_6244f0 = 1;
    g_58332c = 1;
    g_477c30 = 0x3ffff8;
    g_DD_DISPLAYRESWIDTH = g_DISPLAYRESWIDTH;
    g_DD_DISPLAYRESHEIGHT = g_DISPLAYRESHEIGHT;
    FUN_42f300();
    FUN_42f6a0();
    FUN_42fd80(device);
    FUN_42ff20(device, driver);
    FUN_42fff0();
    if (!FUN_430020(device, driver))
    {
        FUN_431330();
    }
    g_d3dDevice = ((D3DDriver *)g_5ba788.deviceDesc)->device;
    if (!FUN_42f840())
    {
        FUN_431330();
    }
    FUN_430ff0();
    if (FUN_42fa80() != 1)
    {
        FUN_431330();
    }
    FUN_432070();
    FUN_431350();
    FUN_42f220();
    FUN_431300();
}

// FUNCTION: STUNTGP_D3D 0x431420
void FUN_431420()
{
    if (g_d3dDevice)
    {
        D3DMATRIX projection;
        float m[16];
        D3DMATRIX identity;
        memcpy(m, g_61c3e8, sizeof(m));
        Matrix_Transpose(m, g_61c3e8);
        memset(&identity, 0, sizeof(identity));
        identity._11 = 1.0f;
        identity._22 = 1.0f;
        identity._33 = 1.0f;
        identity._44 = 1.0f;
        g_d3dDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &identity);
        g_d3dDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &identity);
        g_d3dDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &projection);
    }
}

// FUNCTION: STUNTGP_D3D 0x4312c0
void FUN_4312c0()
{
    if (g_D3DUVFix)
    {
        SceneSlot *slot = g_6244f8 == 1 ? &g_636418[2] : g_636418;
        while (slot->scene)
        {
            FUN_4311c0(slot->scene);
            slot++;
        }
    }
}

extern BYTE g_59207c[255];
void FUN_4310a0(float *uv);

// Nudges the texture coordinates of every face whose texture is flagged in g_59207c.
// FUNCTION: STUNTGP_D3D 0x4311c0
void FUN_4311c0(Scene *scene)
{
    for (DWORD lod = 0; lod < scene->maxLod + 1; lod++)
    {
        for (DWORD i = 0; i < scene->objectCount; i++)
        {
            if (!FUN_42b8b0(scene, i, lod))
            {
                DWORD count = scene->lods[lod][i].vertCount;
                ObjectDef *def = &scene->lods[lod][i];
                BYTE *face = def->verts;
                for (DWORD j = 0; j < count; j++, face += 8)
                {
                    if (g_59207c[face[1]])
                    {
                        WORD *index = (WORD *)scene->unk38 + *(WORD *)(face + 6);
                        for (DWORD k = 0; k < face[0]; k++)
                        {
                            FUN_4310a0((float *)(def->unk2c + index[k] * 16));
                        }
                    }
                }
            }
        }
    }
}

void FUN_434090();
void FUN_434030();

// Dynamic mesh object matrix.
// GLOBAL: STUNTGP_D3D 0x5da1e0
float g_5da1e0[16];

// FUNCTION: STUNTGP_D3D 0x4342c0
void FUN_4342c0()
{
    FUN_434090();
    FUN_434030();
    Matrix_Identity(g_5da1e0);
}

struct MeshPolyVertex
{
    Vec4 pos;    // 0x00
    float u;     // 0x10
    float v;     // 0x14
    DWORD color; // 0x18
};

struct MeshPoly
{
    BYTE unk00[0x20];      // 0x00
    int unk20;             // 0x20
    int unk24;             // 0x24
    int unk28;             // 0x28
    DWORD count;           // 0x2c
    MeshPolyVertex v[4];   // 0x30
};

// GLOBAL: STUNTGP_D3D 0x5da220
DWORD g_5da220[4];

// Empty texture list of the dynamic mesh scene.
// GLOBAL: STUNTGP_D3D 0x5da230
char *g_5da230;

// GLOBAL: STUNTGP_D3D 0x4788a8
DWORD *g_4788a8[2] = {g_5da220, NULL};

// GLOBAL: STUNTGP_D3D 0x4788b0
Vec4 g_4788b0 = {0.0f, 1.0f, 0.0f, 0.0f};

// Identity transform of the dynamic mesh.
// GLOBAL: STUNTGP_D3D 0x4788c0
Camera g_4788c0 = {{0.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, 0, NULL, NULL, 0};

// Unit billboard corners, scaled by MeshPoly's size.
// GLOBAL: STUNTGP_D3D 0x478910
MeshPolyVertex g_478910[4] = {
    {{-50.0f, 50.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0x1ffffff},
    {{50.0f, 50.0f, 0.0f, 0.0f}, 0.998f, 0.0f, 0x1ffffff},
    {{50.0f, -50.0f, 0.0f, 0.0f}, 0.998f, 0.998f, 0x1ffffff},
    {{-50.0f, -50.0f, 0.0f, 0.0f}, 0.0f, 0.998f, 0x1ffffff},
};

void FUN_434030();

// Allocates the dynamic mesh buffers and builds its one-object scene in g_636418[0].
// FUNCTION: STUNTGP_D3D 0x434090
void FUN_434090()
{
    DWORD i;
    g_5da234 = (MeshFace *)Mem_Alloc(0x1000, 0);
    g_5da238 = (WORD *)Mem_Alloc(0x1000, 0);
    g_5da23c = (Vec4 *)Mem_Alloc(0x8000, 0);
    g_5da240 = (MeshUv *)Mem_Alloc(0x8000, 0);
    g_5da244 = (ObjectDef *)Mem_Alloc(0x40, 0);
    g_5da248 = (Scene *)Mem_Alloc(0x68, 0);
    g_636418[0].scene = g_5da248;
    FUN_434030();
    g_478910[0].pos.x = -50.0f;
    g_478910[0].pos.y = 50.0f;
    g_478910[0].pos.z = 0.0f;
    g_478910[1].pos.x = 50.0f;
    g_478910[1].pos.y = 50.0f;
    g_478910[1].pos.z = 0.0f;
    g_478910[2].pos.x = 50.0f;
    g_478910[2].pos.y = -50.0f;
    g_478910[2].pos.z = 0.0f;
    g_478910[3].pos.x = -50.0f;
    g_478910[3].pos.y = -50.0f;
    g_478910[3].pos.z = 0.0f;
    for (i = 0; i < 0x800; i++)
    {
        g_5da250[i] = i;
    }
    for (i = 0; i < 0x800; i++)
    {
        g_5da23c[i].x = 0;
        g_5da23c[i].y = 0;
        g_5da258[i].unk0a = 0;
        g_5da23c[i].z = 0;
    }
    for (i = 0; i < 0x200; i++)
    {
        g_5da24c[i].unk04 = 0;
    }
    memset(g_5da25c, 0, sizeof(ObjectDef));
    g_5da25c->visible = 1;
    g_5da25c->flags = 0;
    g_5da25c->matrix = (Vec4 *)&g_4788c0;
    *(WORD *)(g_5da25c->unk0c + 0x14) = 0;
    *(WORD *)(g_5da25c->unk0c + 0x16) = 0;
    g_5da25c->vertCount = 0;
    g_5da25c->unk26 = 0;
    g_5da25c->pointCount = 0;
    g_5da25c->unk2c = (BYTE *)g_5da240;
    g_5da25c->points = g_5da23c;
    g_5da25c->verts = (BYTE *)g_5da234;
    *(DWORD *)(g_5da25c->unk0c + 4) = 0;
    *(DWORD *)(g_5da25c->unk0c + 8) = 0;
    *(DWORD *)(g_5da25c->unk0c + 0xc) = 0;
    memset(g_5da260, 0, sizeof(Scene));
    g_5da260->flags = 1;
    g_5da260->camera = NULL;
    *(DWORD *)(g_5da260->unk10 + 0) = 0;
    *(DWORD *)(g_5da260->unk10 + 4) = 0;
    *(DWORD *)(g_5da260->unk10 + 8) = 0;
    *(WORD *)(g_5da260->unk10 + 0x10) = 0;
    *(WORD *)(g_5da260->unk10 + 0x12) = 0;
    g_5da260->objectCount = 1;
    g_5da260->unk28 = (SceneEntry *)&g_4788b0;
    g_5da260->verts = (BYTE *)g_5da234;
    g_5da260->unk30 = (BYTE *)g_5da240;
    g_5da260->points = g_5da23c;
    g_5da260->unk38 = (BYTE *)g_5da238;
    g_5da260->matrices = (BYTE *)&g_4788c0;
    g_5da260->unk40 = (DWORD *)g_4788a8;
    g_5da260->view = (SceneView *)g_5da244;
    g_5da260->lods[0] = g_5da244;
    g_5da260->lods[1] = g_5da244;
    g_5da260->lods[2] = g_5da244;
    g_5da260->lods[3] = g_5da244;
    g_5da260->maxLod = 0;
    g_5da260->lod = 0;
    g_5da260->textures = &g_5da230;
}

// Appends a polygon to the dynamic mesh.
// FUNCTION: STUNTGP_D3D 0x4342e0
void FUN_4342e0(MeshPoly *poly)
{
    if (g_5da24c < g_5da234 + 0x200)
    {
        ObjectDef *object = g_5da25c;
        short n = poly->count;
        DWORD i;
        object->vertCount++;
        object->unk26 += n;
        object->pointCount += n;
        g_5da24c->count = poly->count;
        g_5da24c->flags = poly->unk24 | 0x80;
        g_5da24c->unk01 = poly->unk20;
        g_5da24c->unk02 = poly->unk28;
        g_5da24c->index = g_5da250 - g_5da238;
        g_5da24c++;
        for (i = 0; i < poly->count; i++)
        {
            g_5da258->point = g_5da254 - g_5da23c;
            g_5da258->u = poly->v[i].u;
            g_5da258->v = poly->v[i].v;
            g_5da258->color = poly->v[i].color;
            *g_5da254++ = poly->v[i].pos;
            *g_5da250++ = g_5da258 - g_5da240;
            g_5da258++;
        }
    }
}

int FUN_4280a0(Vec4 *pos, Vec4 *size);

// Appends a camera-facing quad (centre unk00, half size unk00 + 0x10) to the dynamic mesh unless
// it is outside the view.
// FUNCTION: STUNTGP_D3D 0x4343f0
void FUN_4343f0(MeshPoly *poly)
{
    if (g_5da24c < g_5da234 + 0x200)
    {
        Vec4 *pos = (Vec4 *)poly->unk00;
        Vec4 *size = (Vec4 *)(poly->unk00 + 0x10);
        if (FUN_4280a0(pos, size) != 1)
        {
            ObjectDef *object = g_5da25c;
            object->vertCount++;
            object->unk26 += 4;
            object->pointCount += 4;
            g_5da24c->count = 4;
            g_5da24c->flags = poly->unk24 | 0x80;
            g_5da24c->unk01 = poly->unk20;
            g_5da24c->unk02 = poly->unk28;
            g_5da24c->index = g_5da250 - g_5da238;
            g_5da24c++;
            Vec4 *m = g_4722d0->cam.matrix;
            int point = g_5da254 - g_5da23c;
            for (int i = 0; i < 4; i++)
            {
                Vec4 t;
                float x = g_478910[i].pos.x * size->x;
                float y = size->y * g_478910[i].pos.y;
                float z = g_478910[i].pos.z * size->z;
                g_5da258->point = point;
                g_5da258->color = poly->v[i].color;
                g_5da258->u = g_478910[i].u;
                g_5da258->v = g_478910[i].v;
                t.x = y * m[1].x + z * m[2].x + x * m[0].x;
                t.y = y * m[1].y + z * m[2].y + x * m[0].y;
                t.z = x * m[0].z + y * m[1].z + z * m[2].z;
                g_5da254->x = t.x + pos->x;
                g_5da254->y = t.y + pos->y;
                g_5da254->z = t.z + pos->z;
                *g_5da250++ = g_5da258 - g_5da240;
                g_5da258++;
                point++;
                g_5da254++;
            }
        }
    }
}

struct ObjectHolder
{
    BYTE unk00[0x14];
    PoolObject *object; // 0x14
};

// FUNCTION: STUNTGP_D3D 0x43d070
void FUN_43d070(ObjectHolder *holder)
{
    PoolObject *object = holder->object;
    object->destroy(object);
    Pool_Free(object);
    holder->object = NULL;
}

// FUNCTION: STUNTGP_D3D 0x43d0a0
int FUN_43d0a0()
{
    return 0;
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
        FUN_440c40(g_menuState.languages[0].id);
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

// FUNCTION: STUNTGP_D3D 0x43d420
int FUN_43d420()
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x43d1f0
void FUN_43d1f0()
{
    FUN_43d420();
}

// FUNCTION: STUNTGP_D3D 0x443050
void FUN_443050()
{
    g_60d730.unk860 = &g_4d5cc0[2];
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
    g_612948.unk8cec = 0;
    g_612948.unk0000 = 0;
    g_612948.unk0004 = 0;
    g_612948.unk0010 = 0;
    g_612948.unk0020 = 0;
    g_612948.unk002c = 0;
    g_612948.unk0030 = 0;
    g_612948.unk0038 = 0;
    g_612948.frameCount = 0;
    g_612948.unk0040 = 0;
    g_612948.unk0044 = 0;
    g_612948.unk004c = 0;
    g_612948.unk0048 = 0;
    g_612948.unk0050 = 0;
    g_612948.unk0054 = 0;
    g_612948.unk0058 = 0;
    g_612948.unk029c = 0;
    g_612948.unk02a8 = 0;
    g_571328 = 0;
    memset(g_612948.unk040c, 0, sizeof(g_612948.unk040c));
    g_612948.unk044c = 0;
    g_612948.unk0450 = 0;
    g_612948.unk0454 = 0;
    g_612948.unk0458 = 0;
    memset(g_612948.unk045c, 0, sizeof(g_612948.unk045c));
    memset(g_612948.unk8c5c, 0, sizeof(g_612948.unk8c5c));
    g_49a164 = 0;
    g_612948.unk8cdc = 0;
    g_612948.unk8ce0 = 0;
    g_612948.unk8ce4 = 0;
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

extern FILE *g_5da2e4;

// FUNCTION: STUNTGP_D3D 0x446290
void FUN_446290()
{
    // STRING: STUNTGP_D3D 0x484b4c
    fprintf(g_5da2e4, "-CarAI_StuntKnotList[] =\n");
    for (int i = 0; g_499fb8[i].pathPosition > 0.0f; i++)
    {
        // STRING: STUNTGP_D3D 0x484b68
        fprintf(g_5da2e4, "   -PathPosition = %12f\n", g_499fb8[i].pathPosition);
        // STRING: STUNTGP_D3D 0x484b84
        fprintf(g_5da2e4, "   -Width        = %12f\n", g_499fb8[i].width);
        // STRING: STUNTGP_D3D 0x484ba0
        fprintf(g_5da2e4, "   -Grade        = %d\n", g_499fb8[i].grade);
        // STRING: STUNTGP_D3D 0x484bb8
        fprintf(g_5da2e4, "\n");
    }
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
    g_624504.intensity = intensity * (1.0f / 255.0f);
    g_624504.red = red;
    g_624504.green = green;
    g_624504.blue = blue;
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

// FUNCTION: STUNTGP_D3D 0x459a00
int FUN_459a00(int which)
{
    if (which == 2)
    {
        return g_menuState.gold;
    }
    return which == 1 ? g_menuState.silver : 0;
}

// FUNCTION: STUNTGP_D3D 0x459a20
void FUN_459a20(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x45a350
void FUN_45a350()
{
    FUN_440880(12);
}

// FUNCTION: STUNTGP_D3D 0x45a3f0
void FUN_45a3f0(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x45a610
int FUN_45a610(MenuObject *object, int arg)
{
    object->unk14 = 0;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x45a7f0
void FUN_45a7f0(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x45ab70
void FUN_45ab70(Unk45ab70 *object)
{
    PoolObject *child = object->unk34;
    child->destroy(child);
    Pool_Free(child);
    object->unk34 = NULL;
    child = object->unk38;
    child->destroy(child);
    Pool_Free(child);
    object->unk38 = NULL;
}

// FUNCTION: STUNTGP_D3D 0x45b5b0
void FUN_45b5b0(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x45b850
void FUN_45b850(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

void FUN_438710(float x, float y, int layer, int def, float scale, DWORD flags);

struct Unk45ba30
{
    DWORD unk00[6]; // 0x00
    float unk18;    // 0x18
};

// Draws the six-panel strip, scrolled left by unk18 panels.
// FUNCTION: STUNTGP_D3D 0x45ba30
void FUN_45ba30(Unk45ba30 *object)
{
    float x = 320.0f - object->unk18 * 280.0f;
    for (int i = 1; i < 7; i++)
    {
        FUN_438710(x, 176.0f, 18, i + 0x2a, 1.0f, 0x203);
        FUN_438710(x, 176.0f, 17, i + 0x24, 1.0f, 0x103);
        x += 280.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x45bba0
int FUN_45bba0(MenuObject *object, int arg)
{
    object->unk14 = 1;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x45be00
void FUN_45be00(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

void FUN_43dc40();
void FUN_45c050(MenuObject *object);

// FUNCTION: STUNTGP_D3D 0x45c030
int FUN_45c030(MenuObject *object, int arg)
{
    FUN_43dc40();
    FUN_43c400();
    FUN_45c050(object);
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x45c050
void FUN_45c050(MenuObject *object)
{
    object->unk18 = 0;
    object->unk1c = 1.0f;
    object->unk20 = 1.0f;
    object->unk14 = 0;
    g_menuState.unk4244 = 0;
    FUN_43dd90(0);
}

// FUNCTION: STUNTGP_D3D 0x45c640
void FUN_45c640(Unk45c670 *object)
{
    PoolObject *child = object->unk14;
    child->destroy(child);
    Pool_Free(child);
    object->unk14 = NULL;
    FUN_45c670(object);
}

// FUNCTION: STUNTGP_D3D 0x45c670
void FUN_45c670(Unk45c670 *object)
{
    switch (object->unk30)
    {
    case 1:
        g_menuState.unk4478 = 5;
        break;
    case 2:
        g_menuState.unk4478 = 9;
        break;
    case 0:
        g_menuState.unk4478 = 3;
        break;
    default:
        g_menuState.unk4478 = 5;
        break;
    }
}

struct Unk45d130
{
    DWORD unk00[6]; // 0x00
    int unk18;      // 0x18
    DWORD unk1c[3]; // 0x1c
    float unk28;    // 0x28
};

// FUNCTION: STUNTGP_D3D 0x45d130
void FUN_45d130(Unk45d130 *object, float x, float y)
{
    x = x - 140.0f - (float)sin(object->unk28 * 3.1415927f) * 20.0f;
    FUN_438710(x, y, 13, object->unk18 + 0x35, 1.0f, 0x203);
    FUN_438710(x, y, 12, object->unk18 + 0x31, 1.0f, 0x103);
}

// FUNCTION: STUNTGP_D3D 0x45db10
void FUN_45db10(Unk4516c0 *object)
{
    object->unk14->message(object->unk14, 0x14, 0);
    PoolObject *child = object->unk18;
    child->message(child, 0x13, 0);
    child->message(child, 0x1c, 2);
    object->unk1c = 1;
}

// FUNCTION: STUNTGP_D3D 0x45db50
void FUN_45db50(Unk4516c0 *object)
{
    object->unk14->message(object->unk14, 0x13, 0);
    object->unk18->message(object->unk18, 0x14, 0);
    object->unk1c = 0;
}

// FUNCTION: STUNTGP_D3D 0x45dde0
void FUN_45dde0(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
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

// FUNCTION: STUNTGP_D3D 0x45e110
void FUN_45e110(Unk62a078 *particle)
{
    particle->sizeNow = 0.0f;
    particle->alphaNow = 0.0f;
    particle->frame = 0;
    Unk62a078 *slot = g_62a078;
    unsigned int i = 0;
    while (slot->unk00 == 1)
    {
        i++;
        slot++;
        if (i >= 0x40)
        {
            return;
        }
    }
    *slot = *particle;
    slot->unk00 = 1;
    slot->time = 0;
    g_62d478 = 1;
    slot->angle = 0.0f;
}

// FUNCTION: STUNTGP_D3D 0x45eb90
void FUN_45eb90(int x, int y, int z)
{
    RenderMaterial *material = g_62447c;
    x <<= 2;
    y <<= 2;
    z <<= 2;
    for (int i = 0; i < g_62449c; i++, material++)
    {
        material->unk54 = (material->unk54 + x) & 0x1ffffff;
        material->unk58 = (material->unk58 + y) & 0x1ffffff;
        material->unk5c = (material->unk5c + z) & 0x1ffffff;
    }
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
