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
#include "../../sintable.h"
#include "io_wad.h"
#include "MenuUpdate.h"
#include "../../objects.h"
#include "../../sprite.h"
#include "../../d3drender.h"
#include "../../surface.h"
#include "Engine_LevelScript.h"
#include "../../common.h"
#include "RenderState.h"
#include "../../sound.h"

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

// GLOBAL: STUNTGP_D3D 0x636418
SceneSlot g_636418[16];

struct RenderMaterial
{
    DWORD unk00;      // 0x00
    DWORD unk04;      // 0x04
    float alpha;      // 0x08
    DWORD unk0c;      // 0x0c
    Vec4 pos;         // 0x10
    Vec4 local;       // 0x20, pos relative to the camera
    Vec4 colour;      // 0x30, direction for directional lights
    BYTE unk40[0x10]; // 0x40
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
    int visible;      // 0x84
    BYTE unk88[0x8];  // 0x88
};

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

// GLOBAL: STUNTGP_D3D 0x62497c
int g_62497c;

// NULL-terminated name list, cleared by FUN_42c480.
// GLOBAL: STUNTGP_D3D 0x582b28
char *g_582b28[255];

extern int g_582724;

struct AnimDef;

// GLOBAL: STUNTGP_D3D 0x6249a0
int g_6249a0;

// GLOBAL: STUNTGP_D3D 0x6249a4
int g_6249a4;

// Scenes queued this frame.
// GLOBAL: STUNTGP_D3D 0x6249ac
int g_6249ac;

// GLOBAL: STUNTGP_D3D 0x477c30
DWORD g_477c30 = 0x200000;

// GLOBAL: STUNTGP_D3D 0x4955e0
DWORD *g_4955e0;

// GLOBAL: STUNTGP_D3D 0x4955e4
DWORD *g_4955e4;

// Textures of a race.
// GLOBAL: STUNTGP_D3D 0x4955e8
TextureEntry g_4955e8[31] = {
    // STRING: STUNTGP_D3D 0x49575c
    {"Misc\\LIGHT1", 0, 0},
    // STRING: STUNTGP_D3D 0x495768
    {"Misc\\Light2", 0, 0},
    // STRING: STUNTGP_D3D 0x495774
    {"Misc\\Flare2", 0, 0},
    // STRING: STUNTGP_D3D 0x495780
    {"Misc\\Hexflare3", 0, 0},
    // STRING: STUNTGP_D3D 0x495790
    {"Misc\\Spark", 0, 0},
    // STRING: STUNTGP_D3D 0x49579c
    {"Misc\\Skidmark2", 0, 0},
    // STRING: STUNTGP_D3D 0x4957ac
    {"Misc\\Corona5", 0, 0},
    // STRING: STUNTGP_D3D 0x4957bc
    {"Misc\\Smoke1", 0, 0},
    // STRING: STUNTGP_D3D 0x4957c8
    {"Misc\\Trail1", 0, 0},
    // STRING: STUNTGP_D3D 0x4957d4
    {"Misc\\Dust1", 0, 0},
    // STRING: STUNTGP_D3D 0x4957e0
    {"Overlays\\Fade", 0, 0},
    // STRING: STUNTGP_D3D 0x4957f0
    {"Overlays\\Dial", 0, 0},
    // STRING: STUNTGP_D3D 0x495800
    {"Overlays\\Bonus1", 0, 0},
    // STRING: STUNTGP_D3D 0x495810
    {"Overlays\\Bonus2", 0, 0},
    // STRING: STUNTGP_D3D 0x495820
    {"Overlays\\Gear", 0, 0},
    // STRING: STUNTGP_D3D 0x495830
    {"empty", 2, 8},
    // STRING: STUNTGP_D3D 0x495838
    {"Overlays\\Start0", 1, 1},
    // STRING: STUNTGP_D3D 0x495848
    {"Overlays\\Start1", 1, 1},
    // STRING: STUNTGP_D3D 0x495858
    {"Overlays\\Start2", 1, 1},
    // STRING: STUNTGP_D3D 0x495868
    {"Overlays\\Start3", 1, 1},
    // STRING: STUNTGP_D3D 0x495878
    {"Overlays\\LapRecord", 1, 1},
    // STRING: STUNTGP_D3D 0x49588c
    {"Overlays\\Result1", 1, 1},
    // STRING: STUNTGP_D3D 0x4958a0
    {"Overlays\\Result2", 1, 1},
    // STRING: STUNTGP_D3D 0x4958b4
    {"Overlays\\Result3", 1, 1},
    // STRING: STUNTGP_D3D 0x4958c8
    {"Overlays\\Finish", 1, 1},
    // STRING: STUNTGP_D3D 0x4958d8
    {"Overlays\\GameOver", 1, 1},
    // STRING: STUNTGP_D3D 0x4958ec
    {"Overlays\\BoxBack", 1, 1},
    // STRING: STUNTGP_D3D 0x495900
    {"Overlays\\BoxBack2", 1, 1},
    // STRING: STUNTGP_D3D 0x495914
    {"Overlays\\logo-add", 1, 1},
    // STRING: STUNTGP_D3D 0x495928
    {"Overlays\\logo-sub", 1, 1},
    {NULL, 0, 0},
};

// Scene queued with its own camera; g_632cf8 and g_62f5d8 hold lists of these.
struct SceneCamera
{
    Scene *scene; // 0x00
    Camera cam;   // 0x04
};

// GLOBAL: STUNTGP_D3D 0x62f5d8
SceneCamera g_62f5d8[168];

// GLOBAL: STUNTGP_D3D 0x632cf8
SceneCamera g_632cf8[168];

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
// Starts a 256x256 effect centred on (x, y) in the first free slot.
// FUNCTION: STUNTGP_D3D 0x401030
void FUN_401030(float x, float y)
{
    int i = 0;
    Unk496990 *e = g_496990;
    while (e->unk00 == 1)
    {
        i++;
        if (i >= 16)
        {
            return;
        }
        e++;
    }
    e->sprite.texture = 2;
    e->sprite.width = 256.0f;
    e->sprite.height = 256.0f;
    e->unk10 = 24;
    e->unk2c = 30;
    e->unk24 = -0.5f;
    e->unk14 = FUN_42f1c0(15.0f);
    e->unk18 = FUN_42f1c0(7.5f) - 7.5f;
    e->unk70 = 0.0f;
    e->unk64 = 8.0f;
    e->unk68 = 0.0f;
    e->unk6c = 15.0f;
    e->unk50 = 0.0f;
    e->unk44 = 0.1f;
    e->unk48 = 6.0f;
    e->unk4c = 15.0f;
    e->unk54 = 255.0f;
    e->unk58 = 9.0f;
    e->unk5c = 15.0f;
    e->unk8c = -1;
    e->unk00 = 1;
    e->unk08 = 0;
    e->unk28 = 0;
    e->unk40 = 0;
    e->unk98 = 0;
    e->unk34 = 0;
    e->sprite.blendMode = 0x58;
    e->sprite.flags = e->unk10;
    e->sprite.alpha = 0;
    e->sprite.angle = 0;
    e->sprite.scaleX = 1.0f;
    e->sprite.scaleY = 1.0f;
    e->sprite.originX = e->sprite.width * 0.5f;
    e->sprite.originY = e->sprite.height * 0.5f;
    e->sprite.x = 320.0f - e->sprite.originX;
    e->sprite.y = 240.0f - e->sprite.originY;
    e->sprite.z = 1.0f;
    e->sprite.x = x - e->sprite.originX;
    e->sprite.y = y - e->sprite.originY;
}

// Frames left before the sample started by FUN_4011c0 is played again, panned the other way.
// GLOBAL: STUNTGP_D3D 0x497d10
int g_497d10;

// GLOBAL: STUNTGP_D3D 0x497d14
int g_497d14;

// GLOBAL: STUNTGP_D3D 0x497d18
DWORD g_497d18;

// FUNCTION: STUNTGP_D3D 0x4011c0
void FUN_4011c0(int channel, DWORD volume)
{
    g_497d10 = 6;
    g_497d14 = channel;
    g_497d18 = volume;
    FUN_461150(channel, 0, 0, volume, 0xff, 0, NULL);
}

// FUNCTION: STUNTGP_D3D 0x4011f0
void FUN_4011f0()
{
    if (g_497d10 && --g_497d10 == 0)
    {
        FUN_461150(g_497d14, 0, 0, g_497d18, -0xff, 0, NULL);
    }
}

extern int g_60f2b4;
extern int g_60d680;
extern HudDigit g_472030[6];
GameSlot *FUN_402590(Car *car);

// Spawns a score popup for the current car and adds the points to its total: type picks the sprite,
// sound and colour, kind how the popup moves.
// FUNCTION: STUNTGP_D3D 0x401220
void FUN_401220(int type, int kind, unsigned int points)
{
    if (g_60f2b4 != 2 || g_4d5bb8->unk24e0 == 1 || g_60f2b0 == 4 || (g_60f2b0 == 3 && g_60d680))
    {
        return;
    }
    g_4d5bb8->unk260c += points;
    if (!FUN_402590(g_4d5bb8) || g_612948.unk0054 == 1)
    {
        return;
    }
    int i = 0;
    Unk496990 *e = g_496990;
    while (e->unk00 == 1)
    {
        i++;
        if (i >= 16)
        {
            return;
        }
        e++;
    }
    HudDigit *d = &g_472030[type];
    e->unk14 = 0.0f;
    e->unk18 = 0.0f;
    e->unk1c = 0;
    e->unk34 = points;
    // STRING: STUNTGP_D3D 0x47220c
    sprintf(e->unk38, "%d", points);
    int sample = 0x2f;
    if (type > 2)
    {
        sample = 0x2e;
    }
    FUN_4011c0(sample, 0xc0);
    switch (kind)
    {
    case 0:
        e->sprite.texture = d->texture;
        e->sprite.width = d->width;
        e->sprite.height = d->height;
        e->sprite.u0 = d->u0;
        e->sprite.v0 = d->v0;
        e->sprite.u1 = d->u1;
        e->sprite.v1 = d->v1;
        e->unk10 = 0x18;
        e->unk40 = 1;
        e->unk2c = 60;
        e->unk18 = -5.0f;
        e->unk24 = -0.025f;
        e->unk70 = 0.0f;
        e->unk64 = 8.0f;
        e->unk68 = 0.0f;
        e->unk6c = 15.0f;
        e->unk44 = 2.0f;
        e->unk48 = 60.0f;
        e->unk4c = 0.0f;
        e->unk54 = 255.0f;
        e->unk58 = 15.0f;
        e->unk5c = 15.0f;
        e->unk8c = 9;
        e->unk88 = 15;
        e->unk90 = 0x3f;
        e->unk94 = 0;
        e->unk98 = 0;
        break;
    case 1:
        e->sprite.texture = d->texture;
        e->sprite.width = d->width;
        e->sprite.height = d->height;
        e->sprite.u0 = d->u0;
        e->sprite.v0 = d->v0;
        e->sprite.u1 = d->u1;
        e->sprite.v1 = d->v1;
        e->unk10 = 0x19;
        e->unk40 = 1;
        e->unk24 = -0.025f;
        e->unk2c = 60;
        e->unk18 = -5.0f;
        e->unk70 = 0.0f;
        e->unk64 = -8.0f;
        e->unk68 = 0.0f;
        e->unk6c = 15.0f;
        e->unk44 = 2.0f;
        e->unk48 = 60.0f;
        e->unk4c = 0.0f;
        e->unk54 = 255.0f;
        e->unk58 = 15.0f;
        e->unk5c = 15.0f;
        e->unk8c = 9;
        e->unk88 = 15;
        e->unk90 = 0x55;
        e->unk94 = 0;
        e->unk98 = 0;
        break;
    case 2:
        e->sprite.texture = d->texture;
        e->sprite.width = d->width;
        e->sprite.height = d->height;
        e->sprite.u0 = d->u0;
        e->sprite.v0 = d->v0;
        e->sprite.u1 = d->u1;
        e->sprite.v1 = d->v1;
        e->unk10 = 0x39;
        e->unk40 = 1;
        e->unk2c = 120;
        e->unk24 = 0.025f;
        e->unk70 = 0.0f;
        e->unk64 = -11.75f;
        e->unk68 = 60.0f;
        e->unk6c = 0.0f;
        e->unk44 = 2.0f;
        e->unk48 = 30.0f;
        e->unk4c = 0.0f;
        e->unk54 = 255.0f;
        e->unk58 = 0.0f;
        e->unk5c = 15.0f;
        e->unk8c = 9;
        e->unk88 = 16;
        e->unk90 = 0x3f;
        e->unk94 = 0;
        e->unk98 = 0;
        break;
    case 3:
        e->sprite.texture = d->texture;
        e->sprite.width = d->width;
        e->sprite.height = d->height;
        e->sprite.u0 = d->u0;
        e->sprite.v0 = d->v0;
        e->sprite.u1 = d->u1;
        e->sprite.v1 = d->v1;
        e->unk10 = 0x39;
        e->unk40 = 1;
        e->unk2c = 120;
        e->unk24 = 0.025f;
        e->unk70 = 0.0f;
        e->unk64 = -11.75f;
        e->unk68 = 60.0f;
        e->unk6c = 0.0f;
        e->unk44 = 2.0f;
        e->unk48 = 30.0f;
        e->unk4c = 0.0f;
        e->unk54 = 255.0f;
        e->unk58 = 0.0f;
        e->unk5c = 15.0f;
        e->unk8c = 9;
        e->unk88 = 16;
        e->unk90 = 0x7f;
        e->unk94 = 0;
        e->unk74 = 30.0f;
        e->unk78 = 15.0f;
        e->unk7c = 0;
        e->unk80 = 0xffffff;
        e->unk84 = 0xc0c0c0;
        e->unk98 = 1;
        e->unk9c = 0;
        e->unka0 = 30.0f;
        e->unka4 = 15.0f;
        e->unka8 = 15.0f;
        break;
    default:
        return;
    }
    e->unk10 |= 0x20;
    e->unk74 = 6.0f;
    e->unk78 = 6.0f;
    DWORD colour;
    if (type == 0 || type == 3)
    {
        colour = 0xffa000;
    }
    else if (type == 1 || type == 4)
    {
        colour = 0xe0f0ff;
    }
    else if (type == 2 || type == 5)
    {
        colour = 0xffdc00;
    }
    else
    {
        goto place;
    }
    e->unk7c = colour;
    e->unk80 = colour;
    e->unk84 = colour;
place:
    e->unk00 = 1;
    e->unk04 = g_4d5bb8;
    e->unk08 = kind;
    e->unk0c = type;
    e->unk28 = 0;
    e->sprite.blendMode = 0x48;
    e->sprite.flags = e->unk10;
    e->sprite.alpha = 0;
    e->sprite.angle = 0;
    e->sprite.scaleX = 1.0f;
    e->sprite.scaleY = 1.0f;
    float hw = e->sprite.width * 0.5f;
    float hh = e->sprite.height * 0.5f;
    if (type == 0 || type == 1 || type == 2)
    {
        hw = e->sprite.width;
    }
    e->sprite.originX = hw;
    e->sprite.originY = hh;
    e->sprite.x = 320.0f - hw;
    e->sprite.y = 240.0f - hh;
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

// Camera preset record in the level data (g_renderState.unk7f90), 0x60 bytes each.
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
    if (g_renderState.unk7fbc != 0)
    {
        for (DWORD i = 0; i < g_renderState.unk7fbc; i++)
        {
            g_4722d8[i].pos = ((CameraRecord *)g_renderState.unk7f90)[i].pos;
            g_4722d8[i].target = ((CameraRecord *)g_renderState.unk7f90)[i].target;
            g_4722d8[i].up = ((CameraRecord *)g_renderState.unk7f90)[i].up;
            g_4722d8[i].fov = ((CameraRecord *)g_renderState.unk7f90)[i].fov;
            g_4722d8[i].unk34 = 0;
            g_4722d8[i].roll = 0.0f;
        }
        g_499f90 = g_renderState.unk7fbc;
        g_499f94 = 0;
    }
}
// Loads the track's camera presets from Config\Cams\<track>.cam, or takes them from the track data.
// FUNCTION: STUNTGP_D3D 0x401f00
void FUN_401f00()
{
    char path[128];
    if (g_612948.unk02a0 != 1)
    {
        memset(g_4722d8, 0, sizeof(g_4722d8));
        g_499f90 = 0;
        return;
    }
    // STRING: STUNTGP_D3D 0x472ad8
    sprintf(path, "%s\\Config\\Cams\\%s.cam", g_GameDirectory, g_renderState.unk7f78);
    int size = size_of_file(path);
    if (!size)
    {
        FUN_401e50();
        return;
    }
    char *text = (char *)Mem_Alloc(size + 0x20, 0);
    bload(path, text, size);
    // STRING: STUNTGP_D3D 0x472af0
    char *p = strstr(text, "-CAMERA[] =");
    // STRING: STUNTGP_D3D 0x472afc
    Script_GetInt(p, "TotalCameraCnt", &g_499f90);
    char *cur = text;
    for (int i = 0; i < g_499f90; i++)
    {
        // STRING: STUNTGP_D3D 0x472b0c
        p = strstr(cur, "-Position[] =");
        g_4722d8[i].pos.x = 0.0f;
        g_4722d8[i].pos.y = 0.0f;
        g_4722d8[i].pos.z = 0.0f;
        // STRING: STUNTGP_D3D 0x472b1c
        Script_GetFloat(p, "x", &g_4722d8[i].pos.x);
        // STRING: STUNTGP_D3D 0x472b20
        Script_GetFloat(p, "y", &g_4722d8[i].pos.y);
        // STRING: STUNTGP_D3D 0x472b24
        Script_GetFloat(p, "z", &g_4722d8[i].pos.z);
        // STRING: STUNTGP_D3D 0x472b28
        p = strstr(cur, "-OFP[] =");
        g_4722d8[i].target.x = 0.0f;
        g_4722d8[i].target.y = 0.0f;
        g_4722d8[i].target.z = 0.0f;
        // STRING: STUNTGP_D3D 0x472b34
        Script_GetFloat(p, "x", &g_4722d8[i].target.x);
        // STRING: STUNTGP_D3D 0x472b38
        Script_GetFloat(p, "y", &g_4722d8[i].target.y);
        // STRING: STUNTGP_D3D 0x472b3c
        Script_GetFloat(p, "z", &g_4722d8[i].target.z);
        // STRING: STUNTGP_D3D 0x472b40
        p = strstr(cur, "-UP[] =");
        g_4722d8[i].up.x = 0.0f;
        g_4722d8[i].up.y = 0.0f;
        g_4722d8[i].up.z = 0.0f;
        // STRING: STUNTGP_D3D 0x472b48
        Script_GetFloat(p, "x", &g_4722d8[i].up.x);
        // STRING: STUNTGP_D3D 0x472b4c
        Script_GetFloat(p, "y", &g_4722d8[i].up.y);
        // STRING: STUNTGP_D3D 0x472b50
        Script_GetFloat(p, "z", &g_4722d8[i].up.z);
        // STRING: STUNTGP_D3D 0x472b54
        Script_GetFloat(p, "Zoom", &g_4722d8[i].fov);
        // STRING: STUNTGP_D3D 0x472b5c
        Script_GetInt(p, "Tracking", &g_4722d8[i].unk34);
        // STRING: STUNTGP_D3D 0x472b68
        Script_GetFloat(p, "Twist", &g_4722d8[i].roll);
        // STRING: STUNTGP_D3D 0x472b70
        cur = strstr(cur, "Twist") + 5;
    }
    Mem_Free(text);
    g_499f94 = 0;
}


extern float g_482670;
void FUN_40a2c0(float (*m)[16]);
void FUN_40a160();
void FUN_40a1d0();

// Clears every car and loads the default vehicle setup into car 0.
// FUNCTION: STUNTGP_D3D 0x40a2f0
void FUN_40a2f0()
{
    memset(g_49a1f8, 0, sizeof(Car) * 8);
    g_4d5bb8 = g_49a1f8;
    g_49a1f8[0].active = 1;
    Matrix_Identity(g_49a1f8[0].matrix);
    Matrix_Identity(g_4d5bb8->unk1c0c);
    Matrix_Identity(g_4d5bb8->unk1c4c);
    Car *car = g_4d5bb8;
    car->posX = 0.0f;
    car->posY = 0.0f;
    car->posZ = 0.0f;
    car->unk1cac.x = 0.0f;
    car->unk1cac.y = 0.0f;
    car->unk1cac.z = 0.0f;
    car->unk1c8c.x = 0.0f;
    car->unk1c8c.y = 0.0f;
    car->unk1c8c.z = 0.0f;
    car->unk1c9c.x = 0.0f;
    car->unk1c9c.y = 0.0f;
    car->unk1c9c.z = 0.0f;
    car->unk22ec = 0.0f;
    car->unk22f4 = 0.0f;
    car->unk22f0 = 180.0f;
    car->unk22fc = 1000.0f;
    g_49a1f8[0].unk26b4 = g_636418[5].scene;
    g_49a1f8[0].unk26b0 = g_636418[4].scene;
    FUN_40a2c0((float(*)[16])car->unk270c);
    g_49a1f8[0].unk26b8 = g_4864e8;
    g_49a1f8[0].unk26b8.target.x = g_4864e8.pos.x + g_4864e8.target.x;
    g_49a1f8[0].unk26b8.target.y = g_49a1f8[0].unk26b8.pos.y + g_49a1f8[0].unk26b8.target.y;
    g_49a1f8[0].unk26b8.target.z = g_49a1f8[0].unk26b8.pos.z + g_49a1f8[0].unk26b8.target.z;
    car = g_4d5bb8;
    // STRING: STUNTGP_D3D 0x472c60
    strcpy((char *)car->unk0000, "VehicleConfig v0.5");
    car->unk220 = 1000.0f;
    car->unk224 = 0.5f;
    car->unk228 = 0.5f;
    car->unk22c = 30.000002f;
    car->unk230 = 244.0f;
    car->unk234 = 152.0f;
    car->unk238 = 152.0f;
    car->unk23c = 400.0f;
    car->unk240 = 152.0f;
    car->unk244 = 115.0f;
    car->unk24c = 25.0f;
    car->unk250 = 1.0f;
    int i;
    for (i = 0; i < 128; i++)
    {
        car->unk258[i] = 1.0f;
    }
    car->unkd58 = 2.5f;
    car->unkd5c = 0.4f;
    car->unk28a8 = 0xff;
    car->unk28b0 = -60.0f;
    car->unk28ac = 0;
    car->unk2cf4[0] = 0.0f;
    car->unk2cf4[1] = 0.0f;
    car->unk2cf4[2] = 0.0f;
    car->unk2cf4[3] = 0.0f;
    car->unkcac = 0.6f;
    car->unkcb0 = 0.3f;
    car->unkcb4 = 1.86f;
    car->unk1fd0 = 1.0f;
    for (i = 0; i < 4; i++)
    {
        car->unkcb8[i].x = 0.33f;
        car->unkcb8[i].y = 30.0f;
        car->wheels[i].unk0c = g_482670;
        car->unkcb8[i].z = 0.7f;
        car->unkcb8[i].w = 0.4f;
        car->suspension[i].maxTravelIn = 10.0f;
        car->suspension[i].maxDampingIn = 0.8f;
        car->suspension[i].maxStiffnessIn = 0.005f;
        car->suspension[i].maxTravelOut = 10.0f;
        car->suspension[i].maxDampingOut = 0.8f;
        car->suspension[i].maxStiffnessOut = 0.005f;
    }
    car->unkc70 = 0;
    car->unkca0 = 0.5f;
    car->unkc74 = 6;
    car->unkc78 = 0;
    car->unk1f10 = 1;
    car->unk1f14 = 1.0f;
    car->unk1f18 = 0;
    car->unkc7c[1] = -2.06f;
    car->unkc7c[2] = 0.0f;
    car->unkc7c[3] = 3.36f;
    car->unkc7c[4] = 2.06f;
    car->unkc7c[5] = 1.38f;
    car->unkc7c[6] = 1.04f;
    car->unkc7c[7] = 0.92f;
    car->unkc7c[8] = 0.8f;
    car->unkc7c[0] = 3.89f;
    car->unkca4 = 0.9f;
    car->inputMode = 2;
    car->unk2298 = 0;
    car->unk229c = 0;
    for (i = 0; i < 128; i++)
    {
        car->unk1188[0][i] = 1.0f;
        car->unk1188[1][i] = 1.0f;
        car->unk1188[2][i] = 1.0f;
        car->unk1188[3][i] = 1.0f;
        car->unk1188[4][i] = 1.0f;
    }
    car->unk045c = 9000.0f;
    car->unk464 = 7000.0f;
    car->unk460 = 150.0f;
    car->unk468 = 0.97f;
    car->unk1d04 = 300.0f;
    car->unk46c = 394.0f;
    FUN_40a160();
    FUN_40a1d0();
    car = g_4d5bb8;
    car->unk2250 = 0;
    car->unkd60 = 25.0f;
    car->unkd68 = 0.6f;
    car->unkd64 = 5000.0f;
    car->unkd6c = 0.5f;
    car->unk2258 = 1.0f;
    car->unkf70 = 0.01f;
    car->unkf74 = 0.3f;
    unsigned int n;
    for (n = 0; n < 128; n++)
    {
        car->unkd70[n] = n * 0.0078125f;
    }
    car->unkf78 = 75.0f;
    car->unk2270 = 75.0f;
    car->unkf7c = 1.0f;
    car->unkf80 = 0.005f;
    car->unk1184 = 1.0f;
    for (i = 0; i < 128; i++)
    {
        car->unkf84[i] = 1.0f;
    }
    car->unkf84[0] = 0.0f;
    car->unk1b94 = 18.0f;
    car->unk1b98 = 4.002f;
    car->unk1b9c = car->unk220 * 25.0f;
    car->unk1ba0 = 7500.0f;
    car->unk1ba4 = 7500.0f;
    car->unk1fd8 = 0;
    car->unk71ec = 0;
    car->unk71f0 = 0;
    car->unk71f8 = 0;
    car->unk71fc = 0;
    car->unk7200 = 0;
    car->unk7234 = 0;
    car->unk7238 = 20000.0f;
    car->unk2568 = 0;
    car->unk256c = 1000;
    car->unk2574 = 1000.0f;
    car->unk2570 = 1000.0f;
    car->unk2274 = car->unk1184;
    car->race.unk80[1] = 1;
    car->race.unk80[2] = 6;
    car->race.unk80[3] = 11;
    for (n = 0; n < 128; n++)
    {
        if (n < 51.2f)
        {
            car->tyreFrictionEnv[n] = 1.0f;
        }
        else
        {
            car->tyreFrictionEnv[n] = 0.4f;
        }
    }
}

// GLOBAL: STUNTGP_D3D 0x5898c8
int g_5898c8;

extern BYTE g_62dcf0[256];
extern BYTE g_62d480[256];
extern int g_60eff0;
extern Car *g_474630;
extern DWORD g_60f2b0;
extern int g_60f2c0;
extern int g_60dfa4;
extern int g_60d618;
void FUN_40bec0();
void FUN_41f5d0();
void FUN_431a90();
void FUN_442c30();
void FUN_448110();
void FUN_443d90();
void FUN_447b50();
void FUN_4082d0();
void FUN_41d980();
void FUN_402710();
void FUN_404280(Car *car);
void FUN_404310(Car *car);
void FUN_40d410(Car *car);
void FUN_40d430();
void FUN_460b80();
void FUN_45f7c0(int value);
void FUN_4130d0(int mode);

// Race start: resets input, sound and every car, then points each active player's camera at its car.
// FUNCTION: STUNTGP_D3D 0x40d500
void FUN_40d500()
{
    FUN_40bec0();
    FUN_41f5d0();
    g_5898c8 = 1;
    memset(g_62dcf0, 0, sizeof(g_62dcf0));
    memset(g_62d480, 0, sizeof(g_62d480));
    FUN_431a90();
    FUN_442c30();
    FUN_448110();
    FUN_443d90();
    FUN_447b50();
    FUN_4130d0(g_60eff0);
    Car *saved = g_4d5bb8;
    g_4d5bb8 = g_49a1f8;
    for (int n = 6; n != 0; n--)
    {
        FUN_4082d0();
        g_4d5bb8++;
    }
    g_4d5bb8 = saved;
    FUN_4130d0(g_60eff0);
    FUN_41d980();
    FUN_402710();
    FUN_447bd0(60);
    for (GameSlot *slot = g_498248; (int)slot < (int)&g_498248[4]; slot++)
    {
        g_4722d0 = slot;
        if (slot->active == 1)
        {
            g_474630 = slot->data;
            FUN_404280(g_474630);
            FUN_404310(g_474630);
        }
    }
    for (Car *car = g_49a1f8; (int)car < (int)&g_49a1f8[6]; car++)
    {
        FUN_40d410(car);
    }
    FUN_40d430();
    g_60f2b0 = 1;
    g_60f2b4 = 2;
    g_60f2c0 = 0;
    g_49a164 = 0;
    FUN_460b80();
    if (g_612948.unk02a0 == 1)
    {
        FUN_45f7c0(g_60dfa4);
    }
    g_60d618 = 60;
    FUN_460cb0(0);
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

void FUN_415c00(Vec4 *pos, Vec4 *vel, float unused);
void FUN_415d20(Vec4 *pos, Vec4 *vel, float unused);

// Throws two random sparks off the car, forward and off to the side.
// FUNCTION: STUNTGP_D3D 0x418f70
void FUN_418f70()
{
    Vec4 v;
    float r = FUN_42f1c0(83.333336f);
    v.x = r * g_4d5bb8->axisX.x;
    v.y = r * g_4d5bb8->axisX.y;
    v.z = r * g_4d5bb8->axisX.z;
    v.x += g_4d5bb8->unk1c8c.x;
    v.y += g_4d5bb8->unk1c8c.y;
    v.z += g_4d5bb8->unk1c8c.z;
    FUN_415c00((Vec4 *)&g_4d5bb8->posX, &v, 8.0f);
    float s = FUN_42f1c0(6.6666665f);
    if (s < 0.0f)
    {
        s -= 6.6666665f;
    }
    else
    {
        s += 6.6666665f;
    }
    v.x = s * g_4d5bb8->axisX.x;
    v.y = s * g_4d5bb8->axisX.y;
    v.z = s * g_4d5bb8->axisX.z;
    float u = (float)fabs(FUN_42f1c0(6.6666665f));
    Vec4 t;
    t.x = u * g_4d5bb8->axisY.x;
    t.y = u * g_4d5bb8->axisY.y;
    t.z = u * g_4d5bb8->axisY.z;
    v.x = t.x + v.x;
    v.y = t.y + v.y;
    v.z = t.z + v.z;
    v.x += g_4d5bb8->unk1c8c.x;
    v.y += g_4d5bb8->unk1c8c.y;
    v.z += g_4d5bb8->unk1c8c.z;
    FUN_415d20(&g_4d5bb8->unk327c, &v, 8.0f);
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

extern float g_60f2d0[31];
void FUN_418bd0();
void FUN_418d10();

// While the car is between 40% and 65% of the path: crowd and messages, and every third tick a boost to
// unk2570 from unk1184, capped by g_60f2d0[6].
// FUNCTION: STUNTGP_D3D 0x4191f0
void FUN_4191f0()
{
    if ((int)g_4d5bb8->unk7650 >= 40 && (int)g_4d5bb8->unk7650 < 65)
    {
        if (!g_4d5bb8->unk7660)
        {
            FUN_419110();
        }
        FUN_418f70();
        FUN_418bd0();
        if (++g_4d5bb8->unk7660 % 3)
        {
            return;
        }
        if (g_4d5bb8->unk7658 < g_60f2d0[6] * g_4d5bb8->unk1184 && g_4d5bb8->unk2570 < g_4d5bb8->unk2574)
        {
            unsigned int add = (int)(g_4d5bb8->unk1184 * 10.0f);
            g_4d5bb8->unk7658 += add;
            g_4d5bb8->unk2570 += add;
        }
    }
    if ((int)g_4d5bb8->unk7650 >= 65)
    {
        FUN_418d10();
    }
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

CameraPath *FUN_428800(int id);
void FUN_4025d0();
extern float g_499f88;
extern float g_499f8c;

// FUNCTION: STUNTGP_D3D 0x402420
void FUN_402420()
{
    FUN_401f00();
    g_4722d0 = g_498248;
    g_4722d0->preset = NULL;
    g_4722d0->presetMode = 0;
    g_4722d0->fovPending = 0;
    g_4722d0->fovNext = 0.0f;
    g_4722d0->active = 1;
    g_4722d0->data = g_49a1f8;
    g_4722d0->path = FUN_428800(1);
    g_4722d0->fov = 3.2f;
    g_4722d0->unk0b4 = 1.0f;
    g_4722d0->unk0b8 = 128.0f;
    g_4722d0->nearZ = 100.0f;
    g_4722d0->unk19c = 400000.0f;
    g_4722d0->unk0bc = 1.333f;
    g_4722d0->unk0c0 = 1.0f;
    g_4722d0->cam.pos.x = 0.0f;
    g_4722d0->cam.pos.y = 0.0f;
    g_4722d0->cam.pos.z = 0.0f;
    g_4722d0->cam.target.x = 0.0f;
    g_4722d0->cam.target.y = 0.0f;
    g_4722d0->cam.target.z = 1000.0f;
    g_4722d0->cam.up.x = 0.0f;
    g_4722d0->cam.up.y = 1.0f;
    g_4722d0->cam.up.z = 0.0f;
    g_4722d0->cam.scale.x = 1.0f;
    g_4722d0->cam.scale.y = 1.0f;
    g_4722d0->cam.scale.z = 1.0f;
    g_4722d0->unk1ac.x = 0.0f;
    g_4722d0->unk1ac.y = 1.0f;
    g_4722d0->unk1ac.z = 0.0f;
    FUN_44f4c0();
    g_4722d0->camMode = 1;
    g_4722d0->angX = 0x1000000;
    g_4722d0->angY = 0;
    g_4722d0->angZ = 0;
    g_4722d0->roll = 0.0f;
    g_4722d0->fov2 = 1.0f;
    FUN_4023d0();
    FUN_4023f0();
    g_499f88 = 0.0f;
    g_499f8c = 0.0f;
    g_4722d0->unk1cc = g_4722d8;
    g_4722d0->unk1d0 = 10;
    g_4722d0->unk1d4 = 1;
    g_4722d0->unk1bc = 0;
    g_4722d0->unk1c0 = 0.0f;
    g_4722d0->unk1c4 = 0.0f;
    *(DWORD *)g_4722d0->unk1c8 = 0;
    FUN_4025d0();
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
    g_4955e4 = (DWORD *)g_632cf8;
    g_4955e0 = (DWORD *)g_62f5d8;
    g_632cf8[0].scene = NULL;
    g_62f5d8[0].scene = NULL;
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

void FUN_44fdb0(Camera *cam);
void FUN_450150(Scene *scene);

// Appends the scene with a copy of its camera to the render list at g_4955e4.
// FUNCTION: STUNTGP_D3D 0x42b7f0
void FUN_42b7f0(Scene *scene, Camera *camera, int arg)
{
    FUN_44fdb0(camera);
    FUN_450150(scene);
    camera->unk40 = 0;
    g_4955e4[0] = (DWORD)scene;
    *(Camera *)(g_4955e4 + 1) = *camera;
    if (arg)
    {
        FUN_42b7b0(scene, arg);
    }
    else
    {
        FUN_42b7e0((WORD *)scene);
    }
    g_4955e4 += 0x15;
    *g_4955e4 = 0;
}

// Appends the scene with a copy of its camera to the render list at g_4955e0.
// FUNCTION: STUNTGP_D3D 0x42b850
void FUN_42b850(Scene *scene, Camera *camera, int arg)
{
    FUN_44fdb0(camera);
    FUN_450150(scene);
    camera->unk40 = 0;
    g_4955e0[0] = (DWORD)scene;
    *(Camera *)(g_4955e0 + 1) = *camera;
    if (arg)
    {
        FUN_42b7b0(scene, arg);
    }
    else
    {
        FUN_42b7e0((WORD *)scene);
    }
    g_4955e0 += 0x15;
    *g_4955e0 = 0;
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

void FUN_42bdd0();
void FUN_445a40();
void FUN_42c480();
void FUN_42c440(char **names);
extern int g_DisplayBootGfx;

// Loads the textures: the boot screens when enabled, the front-end or race texture list, then
// the textures of each scene not yet loaded.
// FUNCTION: STUNTGP_D3D 0x42c510
void FUN_42c510()
{
    FUN_42bdd0();
    if (g_DisplayBootGfx == 1)
    {
        FUN_445a40();
    }
    FUN_42c480();
    FUN_42c340(g_612948.unk02a0 == 2 ? (TextureEntry *)g_47f318 : g_4955e8);
    for (SceneSlot *slot = &g_636418[2]; slot->scene; slot++)
    {
        if (slot->unk04 == 0)
        {
            FUN_42c440(slot->scene->textures);
            FUN_42b900(slot->scene);
        }
    }
    FUN_42ba90();
}

// STUB: STUNTGP_D3D 0x42d070
void FUN_42d070()
{
}

// UV scroll record; unk00 is the mode (0 still, 2 u scrolls and v follows the wave, -1 ends the list).
struct Unk624488
{
    int unk00;   // 0x00
    float unk04; // 0x04, u offset
    float unk08; // 0x08, v offset
    float unk0c; // 0x0c, u speed
    float unk10; // 0x10, v speed
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

// FUNCTION: STUNTGP_D3D 0x42d970
void FUN_42d970()
{
    RenderMaterial *material = g_renderState.unk7f94;
    for (DWORD i = 0; i < g_renderState.unk7fb4; i++)
    {
        if (material->unk50 == 3)
        {
            g_589e04 = material;
            return;
        }
        material++;
    }
    g_589e04 = g_renderState.unk7f94;
}

// FUNCTION: STUNTGP_D3D 0x42d700
void FUN_42d700()
{
    if (g_612948.unk02a0 == 2)
    {
        g_589e04 = 0;
        g_renderState.unk7f94 = &g_589628;
        g_renderState.unk7fb4 = 0;
        g_renderState.unk8044 = 0;
        g_renderState.unk7fac = &g_5898d0;
        g_renderState.unk7fa0 = g_5898f8;
    }
    RenderMaterial *material = g_renderState.unk7f94;
    for (DWORD i = 0; i < g_renderState.unk7fb4; i++)
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
    g_renderState.unk801c = *g_renderState.unk7fac;
    FUN_42d7e0();
    FUN_42d970();
}

struct Light
{
    int unk00;        // 0x00
    int type;         // 0x04, 0 directional, 1 point
    float range;      // 0x08
    int unk0c;        // 0x0c
    Vec4 pos;         // 0x10
    Vec4 local;       // 0x20, pos relative to the current object
    Vec4 colour;      // 0x30
    BYTE unk40[0x20]; // 0x40
    DWORD color;      // 0x60, flare colour
    BYTE unk64[0x14]; // 0x64
    int r;            // 0x78
    int g;            // 0x7c
    int b;            // 0x80
};

void FUN_42d870();

// Collects the enabled lights for the frame into g_renderState.unk804c: their positions relative
// to the camera and, for lights with flare type 3, whether the flare is in view. Point lights
// out of view are left out.
// FUNCTION: STUNTGP_D3D 0x42d9b0
void FUN_42d9b0()
{
    FUN_42d870();
    Light **active = g_renderState.unk804c.lights;
    g_renderState.unk8044 = 0;
    for (DWORD i = 0; i < (DWORD)g_renderState.unk7fb8; i++)
    {
        RenderMaterial *light = &g_renderState.unk7f94[i];
        GameSlot *gs = g_4722d0;
        if (!light->unk00)
        {
            continue;
        }
        Vec4 d;
        int visible;
        float r;
        switch (light->unk04)
        {
        case 0:
            d.x = light->pos.x - gs->cam.pos.x;
            d.y = light->pos.y - gs->cam.pos.y;
            d.z = light->pos.z - gs->cam.pos.z;
            light->local = d;
            if (light->unk50 == 3)
            {
                visible = 1;
                float z = d.z * gs->axisZ.z + d.y * gs->axisZ.y + d.x * gs->axisZ.x;
                if (z > gs->unk19c)
                {
                    visible = 0;
                    light->visible = visible;
                    break;
                }
                if (z < gs->nearZ ||
                    d.z * gs->planeLeft.z + d.y * gs->planeLeft.y + d.x * gs->planeLeft.x > 5000.0f ||
                    d.z * gs->planeRight.z + d.y * gs->planeRight.y + d.x * gs->planeRight.x > 5000.0f ||
                    d.z * gs->planeTop.z + d.y * gs->planeTop.y + d.x * gs->planeTop.x > 5000.0f ||
                    d.z * gs->planeBottom.z + d.y * gs->planeBottom.y + d.x * gs->planeBottom.x > 5000.0f)
                {
                    visible = 0;
                }
                light->visible = visible;
            }
            else
            {
                light->visible = 0;
            }
            break;
        case 1:
            d.x = light->pos.x - gs->cam.pos.x;
            d.y = light->pos.y - gs->cam.pos.y;
            d.z = light->pos.z - gs->cam.pos.z;
            light->local = d;
            r = (light->alpha < 1.0f ? 1.0f : light->alpha) * 500.0f;
            visible = 1;
            if (d.z * gs->axisZ.z + d.y * gs->axisZ.y + d.x * gs->axisZ.x > gs->unk19c ||
                d.z * gs->planeLeft.z + d.y * gs->planeLeft.y + d.x * gs->planeLeft.x > r ||
                d.z * gs->planeRight.z + d.y * gs->planeRight.y + d.x * gs->planeRight.x > r ||
                d.z * gs->planeTop.z + d.y * gs->planeTop.y + d.x * gs->planeTop.x > r ||
                d.z * gs->planeBottom.z + d.y * gs->planeBottom.y + d.x * gs->planeBottom.x > r)
            {
                visible = 0;
            }
            if (light->unk50 == 3)
            {
                light->visible = visible;
            }
            else
            {
                light->visible = 0;
            }
            if (visible != 1)
            {
                continue;
            }
            break;
        default:
            continue;
        }
        *active++ = (Light *)light;
        g_renderState.unk8044++;
    }
}

// GLOBAL: STUNTGP_D3D 0x589df8
DWORD g_589df8;

// GLOBAL: STUNTGP_D3D 0x589dfc
int g_589dfc;

// Glow billboard on a light, fading in with distance from the camera and pulsing with g_589df8.
// FUNCTION: STUNTGP_D3D 0x42e0a0
void FUN_42e0a0(Light *light)
{
    float size = light->range * 20.0f;
    float dx = light->pos.x - g_4722d0->cam.pos.x;
    float dy = light->pos.y - g_4722d0->cam.pos.y;
    float dz = light->pos.z - g_4722d0->cam.pos.z;
    float fade = (float)sqrt(dz * dz + dy * dy + dx * dx) * 5e-05f;
    if (fade > 1.0f)
    {
        fade = 1.0f;
    }
    Billboard billboard = g_486538;
    float scale = fade * size + g_sinTable[g_589df8] * 0.01f;
    int angle = -g_589dfc & 0x1fff;
    billboard.dir.x = g_cosTable[angle];
    billboard.dir.y = g_sinTable[angle];
    billboard.dir.z = 0.0f;
    billboard.pos = light->pos;
    billboard.texture = 6;
    billboard.unk00 = 0x60;
    billboard.alpha = (short)(int)(fade * 192.0f);
    billboard.size[0] = scale;
    billboard.size[1] = scale;
    billboard.size[2] = scale;
    billboard.colors[0] = light->color;
    billboard.colors[1] = light->color;
    billboard.colors[2] = light->color;
    billboard.colors[3] = light->color;
    FUN_434590(&billboard);
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
    SceneSlot *slot = g_renderState.unk8010 == 1 ? &g_636418[2] : g_636418;
    while (slot->scene)
    {
        FUN_42e240(slot->scene);
        slot++;
    }
    for (DWORD i = 0; i < g_renderState.unk7fb4; i++)
    {
        g_renderState.unk7f94[i].alpha = g_renderState.unk7f94[i].alpha * 255.0f * (1.0f / 255.0f);
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

// Allocates the per-frame render buffers.
// FUNCTION: STUNTGP_D3D 0x42e430
void FUN_42e430()
{
    g_renderState.unk24 = (int)Mem_Alloc(0x78000, 0);
    g_renderState.unk7fe0 = (int)Mem_Alloc(0xc000, 0);
    g_renderState.unk7fe4 = (int)Mem_Alloc(0x2000, 0);
    g_renderState.unk7fe8 = (int)Mem_Alloc(0x800, 0);
    g_renderState.unk104 = (int)Mem_Alloc(0xc000, 0);
    g_renderState.unk10c = Mem_Alloc(0xf000, 0);
    g_renderState.unk110 = Mem_Alloc(0xf000, 0);
    g_renderState.unk114 = Mem_Alloc(0xf000, 0);
    g_renderState.unk118 = Mem_Alloc(0xf000, 0);
    g_renderState.unk108 = (OverlayPoly *)Mem_Alloc(0x11000, 0);
    g_renderState.unk30 = (VisIndexList *)Mem_Alloc(0x1000, 0);
    g_renderState.unk34 = (VisIndexList *)Mem_Alloc(0x1000, 0);
    g_renderState.unk8048 = Mem_Alloc(0x4800, 0);
}

void FUN_41c710();
void FUN_42eb00();

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
    g_renderState.unk104 = 0;
    memset(g_62dcf0, 0, sizeof(g_62dcf0));
    memset(g_62d480, 0, sizeof(g_62d480));
    g_renderState.unk10c = NULL;
    g_renderState.unk110 = NULL;
    g_renderState.unk114 = NULL;
    g_renderState.unk118 = NULL;
    g_renderState.unk108 = NULL;
    g_renderState.unk30 = NULL;
    g_renderState.unk34 = NULL;
    g_renderState.unk8048 = NULL;
    memset(g_renderState.unk2e4, 0, sizeof(g_renderState.unk2e4));
    g_renderState.unk62e4 = NULL;
    g_renderState.unk62e8 = 0;
    g_renderState.unk44 = NULL;
    g_renderState.unk48 = NULL;
    g_renderState.unkfc = -1;
    g_renderState.unk24 = 0;
    g_renderState.unk28 = 0;
    g_renderState.unk2c = 0;
    g_renderState.unk100 = 0;
    g_renderState.unk38 = 0;
    g_renderState.unk11c = 0;
    memset(g_renderState.unk120, 0, sizeof(g_renderState.unk120));
    g_renderState.unk2e0 = NULL;
    memset(g_renderState.unk62ec, 0, 255 * sizeof(TextureSlot));
    g_renderState.unk7ed0 = NULL;
    memset(g_renderState.unk7ed8, 0, sizeof(g_renderState.unk7ed8));
    memset(g_renderState.unk7ef8, 0, sizeof(g_renderState.unk7ef8));
    g_renderState.unk3c = NULL;
    g_renderState.unk40 = NULL;
    memset(g_renderState.unk7fc0, 0, sizeof(g_renderState.unk7fc0));
    g_renderState.unk7fe0 = 0;
    g_renderState.unk7fe4 = 0;
    g_renderState.unk7fe8 = 0;
    g_renderState.unk7fec = 0;
    g_renderState.unk7ff0 = 0;
    g_renderState.unk7ff4 = 0;
    g_renderState.unk7ff8 = 0;
    g_renderState.unk7ffc = 0;
    g_renderState.unk7f78 = 0;
    g_renderState.unk7f7c = NULL;
    g_renderState.unk7f80 = NULL;
    g_renderState.unk7f84 = NULL;
    g_renderState.unk7f88 = NULL;
    g_renderState.unk7f8c = NULL;
    g_renderState.unk7f90 = NULL;
    g_renderState.unk7f94 = NULL;
    g_renderState.unk7f98 = NULL;
    g_renderState.unk7f9c = NULL;
    g_renderState.unk7fa0 = NULL;
    g_renderState.unk7fa4 = NULL;
    g_renderState.unk7fa8 = NULL;
    g_renderState.unk7fac = NULL;
    g_renderState.unk7fb0 = 0;
    g_renderState.unk7fb4 = 0;
    g_renderState.unk7fb8 = 0;
    g_renderState.unk7fbc = 0;
    FUN_42eb00();
}

// GLOBAL: STUNTGP_D3D 0x624988
int g_624988;

// GLOBAL: STUNTGP_D3D 0x62498c
int g_62498c;

// FUNCTION: STUNTGP_D3D 0x42e800
void FUN_42e800()
{
    g_renderState.unk28 = g_renderState.unk24;
    g_renderState.unk38 = g_renderState.unk104;
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
    g_renderState.unk7f88 = &g_58d810->data[g_58d810->unk088];
    g_renderState.unk7f84 = &g_58d810->data[g_58d810->unk07c];
    g_renderState.unk7f80 = &g_58d810->data[g_58d810->unk084];
    g_renderState.unk7f7c = &g_58d810->data[g_58d810->unk080];
}

// FUNCTION: STUNTGP_D3D 0x42ed80
void FUN_42ed80()
{
    TrackHeader *header = g_58d810;
    TrackOctree *tree = (TrackOctree *)&header->data[header->unk0a0];
    g_renderState.unk7f98 = tree;
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
    g_renderState.unk7f8c = paths;
    g_renderState.unk7fb0 = count;
}

// FUNCTION: STUNTGP_D3D 0x42eee0
void FUN_42eee0()
{
    g_renderState.unk7fb4 = g_58d810->unk0fc;
    g_renderState.unk7fb8 = g_58d810->unk100;
    g_renderState.unk7f94 = (RenderMaterial *)&g_58d810->data[g_58d810->unk070];
    g_renderState.unk7fac = (Ambience *)&g_58d810->data[g_58d810->unk064];
}

// FUNCTION: STUNTGP_D3D 0x42ef20
void FUN_42ef20()
{
    g_renderState.unk7fbc = g_58d810->unk0e8;
    g_renderState.unk7f90 = &g_58d810->data[g_58d810->unk058];
}

// FUNCTION: STUNTGP_D3D 0x42ef50
void FUN_42ef50()
{
    g_renderState.unk7f9c = (AnimDef *)&g_58d810->data[g_58d810->unk060];
    g_renderState.unk7fa0 = (Unk624488 *)&g_58d810->data[g_58d810->unk05c];
}

// FUNCTION: STUNTGP_D3D 0x42ef80
void FUN_42ef80()
{
    g_renderState.unk7fa4 = g_58c800->unk28;
    g_renderState.unk7fa8 = g_58c800->unk28 + g_58d810->unk0e4;
}

// GLOBAL: STUNTGP_D3D 0x577650
float g_577650;

// GLOBAL: STUNTGP_D3D 0x577654
unsigned int g_577654;

extern int g_577660[10];

// Advances every texture UV scroll, wrapping offsets into [-1, 1].
// FUNCTION: STUNTGP_D3D 0x4258a0
void FUN_4258a0()
{
    if (g_612948.unk0004 == 1)
    {
        return;
    }
    float u;
    float v;
    unsigned int phase;
    if (g_577654 >= 0x800 && g_577654 < 0x1800)
    {
        phase = g_577654 + 0x10;
    }
    else
    {
        phase = g_577654 + 0x20;
    }
    g_577654 = phase & 0x1fff;
    g_577650 = g_sinTable[g_577654] * 0.046875f;
    Unk624488 *r = g_renderState.unk7fa0;
    while (r->unk00 != -1)
    {
        if (r->unk00 != 0)
        {
            if (r->unk00 == 2)
            {
                u = r->unk0c + r->unk04;
                r->unk08 = g_577650;
                r->unk04 = u;
                if (u > 1.0f)
                {
                    r->unk04 = u - 1.0f;
                }
            }
            else
            {
                u = r->unk04 + r->unk0c;
                r->unk04 = u;
                v = r->unk10 + r->unk08;
                r->unk08 = v;
                if (u > 1.0f)
                {
                    r->unk04 = u - 1.0f;
                }
                if (v > 1.0f)
                {
                    r->unk08 = v - 1.0f;
                }
                if (r->unk04 < -1.0f)
                {
                    r->unk04 = r->unk04 + 1.0f;
                }
                if (r->unk08 < -1.0f)
                {
                    r->unk08 = r->unk08 + 1.0f;
                }
            }
        }
        r++;
    }
    Unk624488 *s = (Unk624488 *)g_577660;
    for (int i = 2; i != 0; i--, s++)
    {
        s->unk04 = s->unk0c + s->unk04;
        s->unk08 = s->unk08 + s->unk10;
        if (s->unk04 > 1.0f)
        {
            s->unk04 = s->unk04 - 1.0f;
        }
        if (s->unk08 > 1.0f)
        {
            s->unk08 = s->unk08 - 1.0f;
        }
        if (s->unk04 < -1.0f)
        {
            s->unk04 = s->unk04 + 1.0f;
        }
        if (s->unk08 < -1.0f)
        {
            s->unk08 = s->unk08 + 1.0f;
        }
    }
}

// STUB: STUNTGP_D3D 0x425ad0
void FUN_425ad0()
{
}

// Collects the frame's lights and turns each one's angles (unk54..unk5c) into its direction.
// FUNCTION: STUNTGP_D3D 0x42dcf0
void FUN_42dcf0()
{
    FUN_42d9b0();
    g_589df8 = (g_589df8 + 0x20) & 0x1fff;
    g_589dfc = (g_589dfc + 2) & 0x1fff;
    g_renderState.unk804c.next = (LightRec *)g_renderState.unk8048;
    Light **lights = g_renderState.unk804c.lights;
    for (DWORD i = 0; i < (DWORD)g_renderState.unk8044; i++)
    {
        RenderMaterial *light = (RenderMaterial *)*lights++;
        light->colour.x = 0.0f;
        light->colour.y = 0.0f;
        light->colour.z = 1.0f;
        FUN_44eb70(light->unk54, light->unk58, light->unk5c, &light->colour.x, &light->colour.y, &light->colour.z);
    }
}

// One element of the lens flare: its texture, position along the line from the view centre
// through the light, size, spin speed and angle, and colour.
struct FlareElement
{
    int texture; // 0x00
    float t;     // 0x04
    float size;  // 0x08
    int speed;   // 0x0c
    int angle;   // 0x10
    DWORD color; // 0x14
};

// GLOBAL: STUNTGP_D3D 0x477b88
FlareElement g_477b88[7] = {
    {1, 1.0f, 0.5f, 0x20, 0, 0x804000},
    {1, 1.0f, 0.5f, 0x15, 0x6000, 0x808000},
    {3, 0.5f, 0.2f, 0x20, 0, 0xff},
    {2, 0.0f, 0.05f, 0x20, 0, 0x4c0000},
    {3, -0.5f, 0.35f, 0x20, 0, 0x800000},
    {2, -1.0f, 0.05f, 0x20, 0, 0x4c0000},
    {3, -1.75f, 0.5f, 0x20, 0, 0x8000},
};

extern float g_477b80;

// Draws the lens flare of a light: two spinning glows on the light itself and five elements
// along the line through the view centre, and brightens the screen (g_477b80) when looking at it.
// FUNCTION: STUNTGP_D3D 0x42dd80
void FUN_42dd80(RenderMaterial *light)
{
    float focus = g_4722d0->nearZ * 1.2f;
    Vec4 c;
    c.x = focus * g_4722d0->axisZ.x;
    c.y = focus * g_4722d0->axisZ.y;
    c.z = focus * g_4722d0->axisZ.z;
    c.x += g_4722d0->cam.pos.x;
    c.y += g_4722d0->cam.pos.y;
    c.z += g_4722d0->cam.pos.z;
    Vec4 d;
    d.x = light->pos.x - g_4722d0->cam.pos.x;
    d.y = light->pos.y - g_4722d0->cam.pos.y;
    d.z = light->pos.z - g_4722d0->cam.pos.z;
    Vec3_Normalize(&d.x);
    float dz = d.z * g_4722d0->axisZ.z + d.y * g_4722d0->axisZ.y + d.x * g_4722d0->axisZ.x;
    float k = focus / dz;
    Vec4 p;
    p.x = k * d.x;
    p.y = k * d.y;
    p.z = k * d.z;
    Vec4 q;
    q.x = p.x + g_4722d0->cam.pos.x;
    q.y = p.y + g_4722d0->cam.pos.y;
    q.z = p.z + g_4722d0->cam.pos.z;
    Vec4 v;
    v.x = q.x - c.x;
    v.y = q.y - c.y;
    v.z = q.z - c.z;
    if (dz < 0.8660254f)
    {
        g_477b80 = 1.0f;
    }
    else
    {
        float t = (dz - 0.8660254f) * 7.464101f;
        t = t * t;
        g_477b80 = t * t * 5.0f + 1.0f;
    }
    Billboard b = g_486538;
    b.unk00 = 0x58;
    float s = light->alpha;
    if (light->unk04 == 0)
    {
        s *= 0.25f;
    }
    else
    {
        s *= 0.025f;
    }
    if (s > 0.25f)
    {
        s = 0.25f;
    }
    float d2 = dz * dz;
    dz = d2 * d2 * s * 2.5f;
    FlareElement *e = g_477b88;
    for (int i = 0; i < 7; i++, e++)
    {
        float size = dz * e->size;
        p.x = v.x * e->t;
        p.y = v.y * e->t;
        p.z = v.z * e->t;
        p.x += c.x;
        p.y += c.y;
        p.z += c.z;
        if (i < 2)
        {
            float lx = light->pos.x - g_4722d0->cam.pos.x;
            float ly = light->pos.y - g_4722d0->cam.pos.y;
            float lz = light->pos.z - g_4722d0->cam.pos.z;
            float dist = ((float)sqrt(lz * lz + ly * ly + lx * lx) * 1e-06f) * 2000.0f;
            if (dist < 1.0f)
            {
                dist = 1.0f;
            }
            p = light->pos;
            size = g_sinTable[e->angle] * 4.0f + dist;
            e->angle = (e->speed + e->angle) & 0x1fff;
            int a = g_589dfc;
            if (i == 1)
            {
                a = -a & 0x1fff;
            }
            b.dir.x = g_cosTable[a];
            b.dir.y = g_sinTable[a];
            b.dir.z = 0.0f;
        }
        else if (i == 2)
        {
            b.dir.x = 0.0f;
            b.dir.y = 1.0f;
            b.dir.z = 0.0f;
        }
        b.pos = p;
        b.texture = (short)e->texture;
        b.size[0] = size;
        b.size[1] = size;
        b.size[2] = size;
        b.colors[0] = e->color | 0xff000000;
        b.colors[1] = b.colors[0];
        b.colors[2] = b.colors[0];
        b.colors[3] = b.colors[0];
        FUN_434590(&b);
    }
}

void FUN_42b100();
void FUN_42b140(RenderList *out);
void FUN_42b180(int *out);
void FUN_42b200();
void FUN_42ac70(Scene *scene);
void FUN_42ad30(SceneCamera *e);
void FUN_42af30(SceneCamera *e);
void FUN_42af90(SceneCamera *e);
void FUN_42add0();
void FUN_44fbd0(Scene *scene, ObjectDef *obj, float *m);

// Builds the frame's render buckets: the track (entry 0 of g_632cf8), entry 1 on its own, the
// rest of g_632cf8 with the track's animated objects, then the g_62f5d8 list.
// FUNCTION: STUNTGP_D3D 0x42b040
void FUN_42b040()
{
    SceneCamera *list = g_632cf8;
    g_6249ac = 0;
    FUN_44fbd0(g_636418[3].scene, (ObjectDef *)g_636418[3].scene->view, g_renderState.unkac);
    FUN_42b100();
    FUN_42b140((RenderList *)&g_renderState.unk7ef8[2]);
    list[0].scene->camera = &list[0].cam;
    FUN_42ac70(list[0].scene);
    FUN_42b180((int *)&g_renderState.unk7ef8[2]);
    g_renderState.unk2c = g_renderState.unk28;
    FUN_42ad30(&list[1]);
    g_4722d0->unk19c = 500000.0f;
    FUN_42b140((RenderList *)&g_renderState.unk7ef8[4]);
    FUN_42af30(&list[2]);
    if (g_612948.unk0034 >= 25)
    {
        FUN_42add0();
    }
    FUN_42b180((int *)&g_renderState.unk7ef8[4]);
    FUN_42b140((RenderList *)&g_renderState.unk7ef8[6]);
    FUN_42af90(g_62f5d8);
    FUN_42b180((int *)&g_renderState.unk7ef8[6]);
    FUN_42b740();
    FUN_42b200();
}

// FUNCTION: STUNTGP_D3D 0x42b100
void FUN_42b100()
{
    memset(g_renderState.unk7ef8, 0, sizeof(g_renderState.unk7ef8));
    g_renderState.unk7ed8[0].list = g_renderState.unk114;
    g_renderState.unk7ed8[1].list = g_renderState.unk118;
    g_renderState.unk7ed8[2].list = g_renderState.unk10c;
    g_renderState.unk7ed8[3].list = g_renderState.unk110;
}

// FUNCTION: STUNTGP_D3D 0x42b140
void FUN_42b140(RenderList *out)
{
    out[3].list = g_renderState.unk7ed8[3].list;
    out[2].list = g_renderState.unk7ed8[2].list;
    out[0].list = g_renderState.unk7ed8[0].list;
    out[2].count = 0;
    out[3].count = 0;
    out[0].count = 0;
    out[1].list = g_renderState.unk7ed8[1].list;
    out[1].count = 0;
}

// FUNCTION: STUNTGP_D3D 0x42b180
void FUN_42b180(int *out)
{
    out[5] = ((int)g_renderState.unk7ed8[2].list - out[4]) / 20;
    out[7] = ((int)g_renderState.unk7ed8[3].list - out[6]) / 20;
    out[1] = ((int)g_renderState.unk7ed8[0].list - out[0]) / 20;
    out[3] = ((int)g_renderState.unk7ed8[1].list - out[2]) / 20;
}

// FUNCTION: STUNTGP_D3D 0x42b200
void FUN_42b200()
{
    g_renderState.unk7ed8[0].count = ((int)g_renderState.unk7ed8[0].list - (int)g_renderState.unk114) / 20;
    g_renderState.unk7ed8[1].count = ((int)g_renderState.unk7ed8[1].list - (int)g_renderState.unk118) / 20;
    g_renderState.unk7ed8[2].count = ((int)g_renderState.unk7ed8[2].list - (int)g_renderState.unk10c) / 20;
    g_renderState.unk7ed8[3].count = ((int)g_renderState.unk7ed8[3].list - (int)g_renderState.unk110) / 20;
}


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
    int n = (g_renderState.unk38 - g_renderState.unk104) >> 2;
    float **list = (float **)g_renderState.unk104;
    while (n-- > 0)
    {
        float *v = *list++;
        float s = 1.0f / (v[7] + 1.0f);
        v[0] = s * v[0] * scaleX + offX;
        v[1] = s * v[1] * scaleY + offY;
        v[7] = s * 32.0f;
    }
    float *v = (float *)g_renderState.unk7fec;
    n = (g_renderState.unk7ffc - g_renderState.unk7fec) >> 5;
    while (n-- > 0)
    {
        float s = 1.0f / (v[7] + 1.0f);
        v[0] = s * v[0] * scaleX + offX;
        v[1] = s * v[1] * scaleY + offY;
        v[7] = s * 32.0f;
        v += 8;
    }
    n = (g_renderState.unk28 - g_renderState.unk2c) >> 5;
    v = (float *)g_renderState.unk2c;
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
RenderState g_renderState;

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
                DWORD code = *(WORD *)(g_renderState.unk28 + *(WORD *)(e + 8) * 32 + 16);
                any |= code;
                all &= code;
            }
            if (any == 0x3f)
            {
                Vec4 *p = &points[*(WORD *)(e + 8)];
                Vec4 d;
                d.x = p->x - g_renderState.unk00.x;
                d.y = p->y - g_renderState.unk00.y;
                d.z = p->z - g_renderState.unk00.z;
                Vec4 *nrm = &normals[((WORD *)poly)[2]];
                if ((int)poly[0] < 0 || d.x * nrm->x + d.y * nrm->y + d.z * nrm->z < 0.0f)
                {
                    if (!blend && !(poly[0] & 0x40000000))
                    {
                        opaque->poly = poly;
                        opaque->ref = ref;
                        opaque->verts = g_renderState.unk28;
                        opaque->src = src;
                        opaque->unk10 = all;
                        opaque++;
                    }
                    else
                    {
                        blended->poly = poly;
                        blended->ref = ref;
                        blended->verts = g_renderState.unk28;
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
        d.x = p->x - g_renderState.unk00.x;
        d.y = p->y - g_renderState.unk00.y;
        d.z = p->z - g_renderState.unk00.z;
        Vec4 *n = &normals[((WORD *)poly)[2]];
        if ((int)poly[0] < 0 || d.x * n->x + d.y * n->y + d.z * n->z < 0.0f)
        {
            if (!blend && !(poly[0] & 0x40000000))
            {
                opaque->ref = ref;
                opaque->poly = poly;
                opaque->verts = g_renderState.unk28;
                opaque->src = src;
                opaque++;
            }
            else
            {
                blended->ref = ref;
                blended->poly = poly;
                blended->verts = g_renderState.unk28;
                blended->src = src;
                blended++;
            }
        }
        poly += 2;
    }
    lists[0] = opaque;
    lists[2] = blended;
}

// FUN_42a090 for partly clipped meshes: skips polygons with every vertex outside one frustum side
// and stores the vertices' shared outcodes in unk10.
// FUNCTION: STUNTGP_D3D 0x429ea0
void FUN_429ea0(PolyRef **lists, VisIndexList *vis, DWORD count)
{
    Vec4 *normals = (Vec4 *)g_renderState.unk44->unk28;
    WORD *refs = (WORD *)g_renderState.unk44->unk38;
    PolyRef *opaque = lists[0];
    Vec4 *points = g_renderState.unk48->points;
    BYTE *src = g_renderState.unk48->unk2c;
    PolyRef *blended = lists[2];
    g_renderState.unk68 += count;
    for (DWORD i = 0; i < count; i++)
    {
        WORD *idx = vis->polys;
        while (*idx != 0xffff)
        {
            DWORD any = 0;
            DWORD *poly = (DWORD *)(g_renderState.unk48->verts + *idx * 8);
            WORD *ref = &refs[((WORD *)poly)[3]];
            DWORD n = poly[0] & 0xff;
            DWORD all = 0x3f;
            if (n)
            {
                WORD *r = ref;
                BYTE *e;
                while (n-- > 0)
                {
                    e = src + *r++ * 16;
                    DWORD code = *(WORD *)(g_renderState.unk28 + *(WORD *)(e + 8) * 32 + 16);
                    any |= code;
                    all &= code;
                }
                if (any == 0x3f)
                {
                    Vec4 *p = &points[*(WORD *)(e + 8)];
                    Vec4 d;
                    d.x = p->x - g_renderState.unk00.x;
                    d.y = p->y - g_renderState.unk00.y;
                    d.z = p->z - g_renderState.unk00.z;
                    Vec4 *nrm = &normals[((WORD *)poly)[2]];
                    if ((int)poly[0] < 0 || d.x * nrm->x + d.y * nrm->y + d.z * nrm->z < 0.0f)
                    {
                        if (poly[0] & 0x40000000)
                        {
                            blended->poly = poly;
                            blended->ref = ref;
                            blended->verts = g_renderState.unk28;
                            blended->src = src;
                            blended->unk10 = all;
                            blended++;
                        }
                        else
                        {
                            opaque->poly = poly;
                            opaque->ref = ref;
                            opaque->verts = g_renderState.unk28;
                            opaque->src = src;
                            opaque->unk10 = all;
                            opaque++;
                        }
                    }
                }
            }
            idx++;
        }
        vis++;
    }
    lists[2] = blended;
    lists[0] = opaque;
}

// FUN_429d50 for the track: queues the camera-facing polygons of the visible meshes of g_renderState.unk48.
// FUNCTION: STUNTGP_D3D 0x42a090
void FUN_42a090(PolyRef **lists, VisIndexList *vis, DWORD count)
{
    PolyRef *blended = lists[2];
    PolyRef *opaque = lists[0];
    Vec4 *normals = (Vec4 *)g_renderState.unk44->unk28;
    WORD *refs = (WORD *)g_renderState.unk44->unk38;
    Vec4 *points = g_renderState.unk48->points;
    g_renderState.unk68 += count;
    BYTE *src = g_renderState.unk48->unk2c;
    for (DWORD i = 0; i < count; i++)
    {
        WORD *idx = vis->polys;
        while (*idx != 0xffff)
        {
            DWORD *poly = (DWORD *)(g_renderState.unk48->verts + *idx * 8);
            WORD *ref = &refs[((WORD *)poly)[3]];
            Vec4 *p = &points[*(WORD *)(src + *ref * 16 + 8)];
            Vec4 d;
            d.x = p->x - g_renderState.unk00.x;
            d.y = p->y - g_renderState.unk00.y;
            d.z = p->z - g_renderState.unk00.z;
            Vec4 *n = &normals[((WORD *)poly)[2]];
            if ((int)poly[0] < 0 || d.x * n->x + d.y * n->y + d.z * n->z < 0.0f)
            {
                if (poly[0] & 0x40000000)
                {
                    blended->poly = poly;
                    blended->ref = ref;
                    blended->verts = g_renderState.unk28;
                    blended->src = src;
                    blended++;
                }
                else
                {
                    opaque->poly = poly;
                    opaque->ref = ref;
                    opaque->verts = g_renderState.unk28;
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
    Vec4 *corner = (Vec4 *)(g_renderState.unk7f84 + box * 16);
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

// One octant of a visibility-octree node (eight per node, 64 bytes): child is 0xffff when
// empty and 0 for a leaf.
struct VisOctant
{
    WORD child;   // 0x0, node index into g_renderState.unk7f88
    WORD polys;   // 0x2, into g_renderState.unk7f80
    WORD indices; // 0x4, into g_renderState.unk7f7c
    WORD box;     // 0x6, for FUN_42aa70
};

// Walks the visibility octree, queueing the mesh lists of the octants FUN_42aa70 accepts:
// whole ones to g_renderState.unk40 and leaves needing clipping to g_renderState.unk3c.
// FUNCTION: STUNTGP_D3D 0x42abb0
void FUN_42abb0(VisOctant *node)
{
    for (int i = 0; i < 8; i++)
    {
        WORD child = node[i].child;
        if (child != 0xffff)
        {
            int vis = FUN_42aa70(node[i].box);
            if (vis != 1)
            {
                if (vis == 0)
                {
                    g_renderState.unk40->polys = (WORD *)(g_renderState.unk7f80 + node[i].polys * 2);
                    (g_renderState.unk40++)->indices = (WORD *)(g_renderState.unk7f7c + node[i].indices * 2);
                }
                else if (child == 0)
                {
                    g_renderState.unk3c->polys = (WORD *)(g_renderState.unk7f80 + node[i].polys * 2);
                    (g_renderState.unk3c++)->indices = (WORD *)(g_renderState.unk7f7c + node[i].indices * 2);
                }
                else
                {
                    FUN_42abb0((VisOctant *)(g_renderState.unk7f88 + child * 64));
                }
            }
        }
    }
}

void FUN_429880();
void FUN_429730();
void FUN_42a220();
void FUN_426ed0(Scene *scene);
void FUN_42b2a0(Vec4 *out, Vec4 *dir, Scene *scene, ObjectDef *obj);
void FUN_44fbd0(Scene *scene, ObjectDef *obj, float *m);

// Queues the visible parts of the track scene and runs its animated objects.
// FUNCTION: STUNTGP_D3D 0x42ac70
void FUN_42ac70(Scene *scene)
{
    g_4722d0->unk19c = 500000.0f;
    g_renderState.unk3c = g_renderState.unk30;
    g_renderState.unk40 = g_renderState.unk34;
    g_renderState.unk68 = 0;
    g_renderState.unk44 = scene;
    g_renderState.unk48 = (ObjectDef *)g_636418[3].scene->view;
    FUN_42b2a0(&g_renderState.unk00, &g_renderState.unk10, scene, g_renderState.unk48);
    FUN_44fbd0(scene, NULL, g_61c428);
    FUN_42abb0((VisOctant *)g_renderState.unk7f88);
    g_renderState.unk38 = g_renderState.unk104;
    FUN_429880();
    FUN_429730();
    FUN_42a220();
    g_renderState.unk28 += g_renderState.unk48->pointCount * 0x20;
    if (g_renderState.unk44->objectCount > 1)
    {
        FUN_426ed0(scene);
    }
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

void FUN_429520(Vec4 *in, DWORD count);
void FUN_429660(Vec4 *in, DWORD count);
void FUN_44fbd0(Scene *scene, ObjectDef *obj, float *m);
void FUN_42a320(Scene *scene, ObjectDef *obj);
void FUN_42b2a0(Vec4 *out, Vec4 *dir, Scene *scene, ObjectDef *obj);
extern float g_61c428[16];

// FUN_42a8c0 without the lighting pass.
// FUNCTION: STUNTGP_D3D 0x42a260
void FUN_42a260(PolyRef **lists, Scene *scene, int mode)
{
    ObjectDef *obj = scene->lods[scene->lod];
    for (DWORD i = 0; i < scene->objectCount; obj++, i++)
    {
        if (obj->visible == 1)
        {
            FUN_42b2a0(&g_renderState.unk00, &g_renderState.unk10, scene, obj);
            FUN_44fbd0(scene, obj, g_61c428);
            if (!mode)
            {
                FUN_429660(obj->points, obj->pointCount);
                FUN_429d50(scene, obj, lists);
            }
            else
            {
                FUN_429520(obj->points, obj->pointCount);
                FUN_429b70(scene, obj, lists);
            }
            g_renderState.unk28 += obj->pointCount * 0x20;
        }
    }
}

// Transforms and queues the visible objects of the current level of detail, lighting those with
// flag 4.
// FUNCTION: STUNTGP_D3D 0x42a8c0
void FUN_42a8c0(PolyRef **lists, Scene *scene, int mode)
{
    ObjectDef *obj = scene->lods[scene->lod];
    for (DWORD i = 0; i < scene->objectCount; obj++, i++)
    {
        if (obj->visible == 1)
        {
            FUN_42b2a0(&g_renderState.unk00, &g_renderState.unk10, scene, obj);
            FUN_44fbd0(scene, obj, g_61c428);
            if (!mode)
            {
                FUN_429660(obj->points, obj->pointCount);
                FUN_429d50(scene, obj, lists);
            }
            else
            {
                FUN_429520(obj->points, obj->pointCount);
                FUN_429b70(scene, obj, lists);
            }
            if (obj->flags & 4)
            {
                FUN_42a870(scene, obj);
                FUN_42a320(scene, obj);
            }
            g_renderState.unk28 += obj->pointCount * 0x20;
        }
    }
}

void FUN_42a570(Scene *scene, ObjectDef *obj);

// FUN_42a8c0 that lights objects with specular bits (flags & 3) through FUN_42a570.
// FUNCTION: STUNTGP_D3D 0x42a990
void FUN_42a990(PolyRef **lists, Scene *scene, int mode)
{
    ObjectDef *obj = scene->lods[scene->lod];
    for (DWORD i = 0; i < scene->objectCount; obj++, i++)
    {
        if (obj->visible == 1)
        {
            FUN_42b2a0(&g_renderState.unk00, &g_renderState.unk10, scene, obj);
            FUN_44fbd0(scene, obj, g_61c428);
            if (!mode)
            {
                FUN_429660(obj->points, obj->pointCount);
                FUN_429d50(scene, obj, lists);
            }
            else
            {
                FUN_429520(obj->points, obj->pointCount);
                FUN_429b70(scene, obj, lists);
            }
            if (obj->flags & 4)
            {
                FUN_42a870(scene, obj);
                if (obj->flags & 3)
                {
                    FUN_42a570(scene, obj);
                }
                else
                {
                    FUN_42a320(scene, obj);
                }
            }
            g_renderState.unk28 += obj->pointCount * 0x20;
        }
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

// Per-object light record in g_renderState.unk8048, 36 bytes.
struct LightRec
{
    Vec4 colour; // 0x00, rotated into object space
    Vec4 half;   // 0x10
    Light *light; // 0x20
};

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
    view.x = g_renderState.unk10.x * 255.0f;
    view.y = g_renderState.unk10.y * 255.0f;
    view.z = g_renderState.unk10.z * 255.0f;
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
    g_renderState.unk804c.next = (LightRec *)g_renderState.unk8048;
    Light **lights = g_renderState.unk804c.lights;
    for (DWORD i = 0; i < g_renderState.unk8044; i++)
    {
        Light *light = *lights++;
        float r = light->colour.x * 255.0f;
        float g = light->colour.y * 255.0f;
        float b = light->colour.z * 255.0f;
        g_renderState.unk804c.next->colour.x = g * rot[4] + b * rot[8] + r * rot[0];
        g_renderState.unk804c.next->colour.y = g * rot[5] + b * rot[9] + r * rot[1];
        g_renderState.unk804c.next->colour.z = g * rot[6] + b * rot[10] + r * rot[2];
        light->local.x = light->pos.x - origin.x;
        light->local.y = light->pos.y - origin.y;
        light->local.z = light->pos.z - origin.z;
        h.x = view.x + g_renderState.unk804c.next->colour.x;
        h.y = view.y + g_renderState.unk804c.next->colour.y;
        h.z = view.z + g_renderState.unk804c.next->colour.z;
        h.x *= 765.0f;
        h.y *= 765.0f;
        h.z *= 765.0f;
        g_renderState.unk804c.next->half.x = h.x * 0.5f;
        g_renderState.unk804c.next->half.y = h.y * 0.5f;
        g_renderState.unk804c.next->half.z = h.z * 0.5f;
        g_renderState.unk804c.next->light = light;
        g_renderState.unk804c.next++;
    }
}

extern int g_62497c;

// Lights every g_62497c-th vertex of the object (starting from the frame number, so the work is
// spread over frames) from the ambient level and the active lights, packing the colour into
// MeshUv::color.
// FUNCTION: STUNTGP_D3D 0x42a320
void FUN_42a320(Scene *scene, ObjectDef *obj)
{
    DWORD b = g_renderState.unk801c.ib;
    DWORD r = g_renderState.unk801c.ir;
    DWORD g = g_renderState.unk801c.ig;
    if ((WORD)scene->unk04 > 1)
    {
        DWORD scale = (WORD)scene->unk04;
        r = scale * r >> 8;
        g = scale * g >> 8;
        b = scale * b >> 8;
    }
    FUN_42b400(scene, obj);
    Vec4 *points = obj->points;
    Vec4 *normals = (Vec4 *)scene->unk28;
    MeshUv *uv = (MeshUv *)obj->unk2c;
    DWORD n = obj->unk26;
    for (DWORD i = (g_62497c - 1) & g_renderState.unk20; i < n; i += g_62497c)
    {
        MeshUv *e = &uv[i];
        Vec4 *p = &points[e->point];
        DWORD cr = r;
        Vec4 *nrm = &normals[e->unk0a];
        DWORD cg = g;
        DWORD cb = b;
        LightRec *rec = (LightRec *)g_renderState.unk8048;
        for (DWORD j = 0; j < (DWORD)g_renderState.unk8044; j++)
        {
            Light *light = rec->light;
            if (light->type == 0)
            {
                float dot = rec->colour.x * nrm->x + rec->colour.y * nrm->y + rec->colour.z * nrm->z;
                if (*(int *)&dot < 0)
                {
                    int k = (int)dot;
                    cr -= light->r * k;
                    cg -= light->g * k;
                    cb -= light->b * k;
                }
            }
            else if (light->type == 1)
            {
                float dot = rec->colour.x * nrm->x + rec->colour.y * nrm->y + rec->colour.z * nrm->z;
                if (*(int *)&dot < 0)
                {
                    float dx = light->local.x - p->x;
                    float dy = light->local.y - p->y;
                    float dz = light->local.z - p->z;
                    int k = (int)(light->range * 4177920.0f / (dx * dx + dy * dy + dz * dz));
                    cr += light->r * k;
                    cg += light->g * k;
                    cb += light->b * k;
                }
            }
            rec++;
        }
        if (cr > 0xff00)
        {
            cr = 0xff00;
        }
        if (cg > 0xff00)
        {
            cg = 0xff00;
        }
        if (cb > 0xff00)
        {
            cb = 0xff00;
        }
        e->color = ((cb & 0xff00 | 0x10000) << 8) | (cg & 0xff00) | (cr >> 8);
    }
}

extern int g_62457c[256];

// FUN_42a320 with a specular highlight from each directional light, looked up through
// g_62457c into the colour's alpha.
// FUNCTION: STUNTGP_D3D 0x42a570
void FUN_42a570(Scene *scene, ObjectDef *obj)
{
    FUN_42b400(scene, obj);
    DWORD b = g_renderState.unk801c.ib;
    DWORD r = g_renderState.unk801c.ir;
    DWORD g = g_renderState.unk801c.ig;
    if ((WORD)scene->unk04 > 1)
    {
        DWORD scale = (WORD)scene->unk04;
        r = scale * r >> 8;
        g = scale * g >> 8;
        b = scale * b >> 8;
    }
    int shift = (obj->flags & 3) + 8;
    Vec4 *normals = (Vec4 *)scene->unk28;
    Vec4 *points = obj->points;
    DWORD n = obj->unk26;
    DWORD i = (g_62497c - 1) & g_renderState.unk20;
    MeshUv *e = (MeshUv *)obj->unk2c + i;
    for (; i < n; i += g_62497c, e += g_62497c)
    {
        Vec4 *p = &points[e->point];
        Vec4 *nrm = &normals[e->unk0a];
        LightRec *rec = (LightRec *)g_renderState.unk8048;
        DWORD cr = r;
        DWORD cg = g;
        DWORD cb = b;
        int spec = 0;
        for (DWORD j = 0; j < (DWORD)g_renderState.unk8044; j++)
        {
            Light *light = rec->light;
            if (light->type == 0)
            {
                float dot = rec->colour.z * nrm->z + rec->colour.y * nrm->y + nrm->x * rec->colour.x;
                if (*(int *)&dot < 0)
                {
                    int k = (int)dot;
                    cr -= light->r * k;
                    cg -= light->g * k;
                    cb -= light->b * k;
                    dot = rec->half.z * nrm->z + rec->half.y * nrm->y + rec->half.x * nrm->x;
                    if (*(int *)&dot < 0)
                    {
                        spec -= (int)dot;
                    }
                }
            }
            else if (light->type == 1)
            {
                float dot = rec->colour.z * nrm->z + rec->colour.y * nrm->y + nrm->x * rec->colour.x;
                if (*(int *)&dot < 0)
                {
                    float dx = light->local.x - p->x;
                    float dy = light->local.y - p->y;
                    float dz = light->local.z - p->z;
                    int k = (int)(light->range * 4177920.0f / (dx * dx + dy * dy + dz * dz));
                    cr += light->r * k;
                    cg += light->g * k;
                    cb += light->b * k;
                }
            }
            rec++;
        }
        spec >>= shift;
        if (spec < 0)
        {
            spec = 0;
        }
        else if (spec > 0xff)
        {
            spec = 0xff;
        }
        DWORD a = g_62457c[spec];
        if (cr > 0xff00)
        {
            cr = 0xff00;
        }
        if (cg > 0xff00)
        {
            cg = 0xff00;
        }
        if (cb > 0xff00)
        {
            cb = 0xff00;
        }
        e->color = (((a & 0xffffff00) << 8 | cb & 0xff00) << 8) | (cr >> 8) | (cg & 0xff00);
    }
}

// Queues the polygons of both visible-mesh lists of the track.
// FUNCTION: STUNTGP_D3D 0x42a220
void FUN_42a220()
{
    FUN_429ea0((PolyRef **)&g_renderState.unk7ed8[0], g_renderState.unk30, g_renderState.unk3c - g_renderState.unk30);
    FUN_42a090((PolyRef **)&g_renderState.unk7ed8[2], g_renderState.unk34, g_renderState.unk40 - g_renderState.unk34);
}

// Queues the scene into the first render bucket, viewed through its own camera.
// FUNCTION: STUNTGP_D3D 0x42ad30
void FUN_42ad30(SceneCamera *e)
{
    Scene *scene = e->scene;
    g_4722d0->unk19c = 5000000.0f;
    scene->camera = &e->cam;
    FUN_42b140((RenderList *)&g_renderState.unk7ef8[0]);
    FUN_42a260((PolyRef **)g_renderState.unk7ed8, scene, 2);
    FUN_42b180((int *)&g_renderState.unk7ef8[0]);
}

int FUN_428040(Scene *scene, int index);

// Queues each visible scene of the list (up to a NULL scene) with its own camera, into the
// clipped lists when only partly visible.
// FUNCTION: STUNTGP_D3D 0x42af30
void FUN_42af30(SceneCamera *e)
{
    Scene *scene;
    while ((scene = e->scene) != NULL)
    {
        scene->camera = &e->cam;
        int vis = FUN_428040(scene, -1);
        if (vis != 1)
        {
            if (scene->maxLod)
            {
                FUN_42b620(scene);
            }
            if (vis == 0)
            {
                FUN_42a260((PolyRef **)&g_renderState.unk7ed8[2], scene, vis);
            }
            else
            {
                FUN_42a260((PolyRef **)g_renderState.unk7ed8, scene, vis);
            }
            g_6249ac++;
        }
        e++;
    }
}


// FUN_42af30 for scenes that may be lit: with lighting on (g_624980), LOD 0 gets the specular
// path and LOD 1 the plain one; coarser LODs are never lit.
// FUNCTION: STUNTGP_D3D 0x42af90
void FUN_42af90(SceneCamera *e)
{
    void (*lod1)(PolyRef **, Scene *, int) = FUN_42a8c0;
    void (*lod0)(PolyRef **, Scene *, int) = FUN_42a990;
    if (!g_624980)
    {
        lod1 = FUN_42a260;
        lod0 = FUN_42a260;
    }
    Scene *scene;
    while ((scene = e->scene) != NULL)
    {
        scene->camera = &e->cam;
        int vis = FUN_428040(scene, -1);
        if (vis != 1)
        {
            if (scene->maxLod)
            {
                FUN_42b620(scene);
            }
            void (*queue)(PolyRef **, Scene *, int);
            if (scene->lod >= 2)
            {
                queue = FUN_42a260;
            }
            else if (scene->lod >= 1)
            {
                queue = lod1;
            }
            else
            {
                queue = lod0;
            }
            if (vis == 0)
            {
                queue((PolyRef **)&g_renderState.unk7ed8[2], scene, vis);
            }
            else
            {
                queue((PolyRef **)g_renderState.unk7ed8, scene, vis);
            }
            g_6249ac++;
        }
        e++;
    }
}

extern int g_624980;
extern int g_57b41c;

// Relights the track's lit sub-objects once, with every vertex at once.
// FUNCTION: STUNTGP_D3D 0x42ad70
void FUN_42ad70()
{
    if (g_624980 != 1 && g_57b41c != 1)
    {
        g_57b41c = 1;
        g_62497c = 1;
        Scene *scene = g_renderState.unk44;
        ObjectDef *obj = scene->lods[0] + 1;
        for (DWORD i = 1; i < scene->objectCount; i++, obj++)
        {
            if (obj->flags & 4)
            {
                FUN_42a320(scene, obj);
            }
        }
    }
}

// Queues the track's animated objects one by one, culling each with FUN_428040 (culled ones are
// flagged 0x10) and relighting them when full-rate lighting is on.
// FUNCTION: STUNTGP_D3D 0x42add0
void FUN_42add0()
{
    FUN_42ad70();
    Scene *scene = g_renderState.unk44;
    ObjectDef *obj = scene->lods[0] + 1;
    void (*plain)(Scene *, ObjectDef *);
    void (*spec)(Scene *, ObjectDef *);
    if (g_624980 == 1 && g_612948.unk0034 == 100)
    {
        FUN_42a840(scene);
        plain = FUN_42a320;
        if (g_624984 == 1)
        {
            spec = FUN_42a570;
        }
        else
        {
            spec = FUN_42a320;
        }
    }
    else
    {
        g_624984 = 0;
        plain = NULL;
    }
    scene->camera = &g_4864e8;
    for (DWORD i = 1; i < scene->objectCount; obj++, i++)
    {
        if (obj->visible == 1)
        {
            int vis = FUN_428040(scene, i);
            if (vis != 1)
            {
                obj->flags &= ~0x10;
                FUN_42b2a0(&g_renderState.unk00, &g_renderState.unk10, scene, obj);
                FUN_44fbd0(scene, obj, g_61c428);
                if (vis == 0)
                {
                    FUN_429660(obj->points, obj->pointCount);
                    FUN_429d50(scene, obj, (PolyRef **)&g_renderState.unk7ed8[2]);
                }
                else
                {
                    FUN_429520(obj->points, obj->pointCount);
                    FUN_429b70(scene, obj, (PolyRef **)g_renderState.unk7ed8);
                }
                if (plain && (obj->flags & 4))
                {
                    if (obj->flags & 3)
                    {
                        spec(scene, obj);
                    }
                    else
                    {
                        plain(scene, obj);
                    }
                }
                g_renderState.unk28 += obj->pointCount * 0x20;
                g_6249ac++;
            }
            else
            {
                obj->flags |= 0x10;
            }
        }
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
    if (!g_renderState.unk8010)
    {
        FUN_42e6d0();
        FUN_431360();
        g_renderState.unk8010 = 1;
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
    g_renderState.unk7ed4 = g_renderState.unk7ed0 - g_renderState.unk62ec;
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
    g_renderState.unk800c = 0;
    FUN_4320c0(1.0f);
    if (g_636418[3].scene)
    {
        g_636418[3].scene->camera = &g_4864e8;
    }
    g_renderState.unk8010 = 0;
    FUN_431420();
    FUN_4312c0();
    g_renderState.unk8010 = 1;
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
    for (int k = 0; g_58c540[k].id; k++)
    {
        FUN_42efb0(g_58c540[k].id);
        int slot = g_58c540[k].slot;
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
    g_renderState.unk8008 = 1;
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
        SceneSlot *slot = g_renderState.unk8010 == 1 ? &g_636418[2] : g_636418;
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

void FUN_434900(float *values, DWORD count);
void FUN_446180();

// Writes the level settings script.
// FUNCTION: STUNTGP_D3D 0x4463b0
void FUN_4463b0()
{
    // STRING: STUNTGP_D3D 0x484d84
    fprintf(g_5da2e4, "-VERSION = %s\n",
            // STRING: STUNTGP_D3D 0x484a9c
            "V1.0");
    // STRING: STUNTGP_D3D 0x484d94
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x484d98
    fprintf(g_5da2e4, "-Ambience[] =\n");
    // STRING: STUNTGP_D3D 0x484da8
    fprintf(g_5da2e4, " I = %d\n", (int)(g_renderState.unk801c.intensity * 255.0f));
    // STRING: STUNTGP_D3D 0x484db4
    fprintf(g_5da2e4, " R = %d\n", (int)g_renderState.unk801c.red);
    // STRING: STUNTGP_D3D 0x484dc0
    fprintf(g_5da2e4, " G = %d\n", (int)g_renderState.unk801c.green);
    // STRING: STUNTGP_D3D 0x484dcc
    fprintf(g_5da2e4, " B = %d\n", (int)g_renderState.unk801c.blue);
    // STRING: STUNTGP_D3D 0x484dd8
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x484ddc
    fprintf(g_5da2e4, "-FogColour[] =\n");
    // STRING: STUNTGP_D3D 0x484dec
    fprintf(g_5da2e4, " R = %d\n", g_5896b8);
    // STRING: STUNTGP_D3D 0x484df8
    fprintf(g_5da2e4, " G = %d\n", g_5896bc);
    // STRING: STUNTGP_D3D 0x484e04
    fprintf(g_5da2e4, " B = %d\n", g_5896c0);
    // STRING: STUNTGP_D3D 0x484e10
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x484e14
    fprintf(g_5da2e4, "-FogEnvelope[] = \n");
    FUN_434900(g_5896c8, 0x80);
    // STRING: STUNTGP_D3D 0x484e28
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x484e2c
    fprintf(g_5da2e4, "-ColRestitutionTab[] = \n");
    FUN_434900(g_497d20, 0x80);
    // STRING: STUNTGP_D3D 0x484e48
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x484e4c
    fprintf(g_5da2e4, "-FarPlaneClipDistanceTab[] = \n");
    FUN_434900(g_577688, 0x100);
    // STRING: STUNTGP_D3D 0x484e6c
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x484e70
    fprintf(g_5da2e4, "-CarReplacementSplineMask[] = \n");
    FUN_434900(g_60dff0, 0x80);
    // STRING: STUNTGP_D3D 0x484e90
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x484e94
    fprintf(g_5da2e4, "-CarLightsMask[] = \n");
    FUN_434900(g_60e1f0, 0x80);
    // STRING: STUNTGP_D3D 0x484eac
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x484eb0
    fprintf(g_5da2e4, "-AmbienceEnvelope[] = \n");
    FUN_434900(g_60e3f0, 0x80);
    // STRING: STUNTGP_D3D 0x484ec8
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x484ecc
    fprintf(g_5da2e4, "-TrackWidthEnvelope_Left[] = \n");
    FUN_434900(g_60e7f0, 0x100);
    // STRING: STUNTGP_D3D 0x484eec
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x484ef0
    fprintf(g_5da2e4, "-TrackWidthEnvelope_Right[] = \n");
    FUN_434900(g_60ebf0, 0x100);
    // STRING: STUNTGP_D3D 0x484f10
    fprintf(g_5da2e4, "\n");
    FUN_446180();
    FUN_446290();
    // STRING: STUNTGP_D3D 0x484f14
    fprintf(g_5da2e4, "-END\n\n");
}

void FUN_446340();

// Saves the level settings to Config\Levels\<level>.cfg.
// FUNCTION: STUNTGP_D3D 0x4466a0
void FUN_4466a0()
{
    char path[128];
    // STRING: STUNTGP_D3D 0x484f1c
    sprintf(path, "%s\\Config\\Levels\\%s.cfg", g_GameDirectory, g_LevelScript);
    // STRING: STUNTGP_D3D 0x484f34
    g_5da2e4 = fopen(path, "wt");
    if (g_5da2e4)
    {
        FUN_446340();
        FUN_4463b0();
        fclose(g_5da2e4);
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
    g_renderState.unk801c.intensity = intensity * (1.0f / 255.0f);
    g_renderState.unk801c.red = red;
    g_renderState.unk801c.green = green;
    g_renderState.unk801c.blue = blue;
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

float FUN_438a60(const char *text, float size);
float FUN_438ab0(float x, float y, int layer, int style, char *text, float size, D3DCOLOR color, DWORD flags);

// Framed block of text lines centred low on the screen.
// FUNCTION: STUNTGP_D3D 0x45a500
void FUN_45a500(MenuLine *lines, int count)
{
    float height = 0.0f;
    int i;
    for (i = 0; i < count; i++)
    {
        height += FUN_438a60(lines[i].text, 1.25f);
    }
    height += (count - 1) * 4.0f;
    float h = (height + 20.0f) * 0.5f;
    float y0 = 380.0f - h;
    float y1 = h + 384.0f;
    FUN_439450(100.0f, y0, 540.0f, y1, 10, 0x6f, 0x40);
    FUN_439380(100.0f, y0, 540.0f, y1, 13, 2, 0, 0.0f);
    float y = 380.0f - height * 0.5f;
    for (i = 0; i < count; i++)
    {
        y = FUN_438ab0(320.0f, y, 12, 4, lines[i].text, 1.25f, lines[i].color, 1) + y + 4.0f;
    }
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

// Framed block of text lines centred on (x, y).
// FUNCTION: STUNTGP_D3D 0x45be20
void FUN_45be20(MenuLine *lines, int count, float x, float y, float width, float spacing)
{
    float height = 0.0f;
    int i;
    for (i = 0; i < count; i++)
    {
        height += FUN_438a60(lines[i].text, 1.25f);
    }
    height += (count - 1) * spacing;
    float w = width + 40.0f;
    float h = height + 20.0f;
    float x0 = x - w * 0.5f;
    float x1 = w * 0.5f + x;
    float y0 = y - h * 0.5f;
    float y1 = h * 0.5f + y + 4.0f;
    FUN_439450(x0, y0, x1, y1, 10, 0x6f, 0x40);
    FUN_439380(x0, y0, x1, y1, 13, 2, 0, 0.0f);
    y -= height * 0.5f;
    for (i = 0; i < count; i++)
    {
        y = FUN_438ab0(x, y, 12, 4, lines[i].text, 1.25f, lines[i].color, 1) + y + spacing;
    }
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
    RenderMaterial *material = g_renderState.unk7f94;
    x <<= 2;
    y <<= 2;
    z <<= 2;
    for (int i = 0; i < g_renderState.unk7fb4; i++, material++)
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
