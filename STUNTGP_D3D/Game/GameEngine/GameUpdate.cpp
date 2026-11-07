#include "GameUpdate.h"
#include "Game.h"

// 128-byte PCX file header.
struct PcxHeader
{
    BYTE manufacturer;  // 0x00
    BYTE version;       // 0x01
    BYTE encoding;      // 0x02
    BYTE bitsPerPixel;  // 0x03
    short xMin;         // 0x04
    short yMin;         // 0x06
    short xMax;         // 0x08
    short yMax;         // 0x0a
    short hDpi;         // 0x0c
    short vDpi;         // 0x0e
    BYTE palette[48];   // 0x10
    BYTE reserved;      // 0x40
    BYTE planes;        // 0x41
    short bytesPerLine; // 0x42
    short paletteInfo;  // 0x44
    BYTE filler[58];    // 0x46
};

extern int g_48971c;
extern int g_489720;

#include <cstring>
#include <stdio.h>
#include <float.h>
#include <math.h>

#include "../../d3drender.h"
#include "../../gametext.h"
#include "../../globals.h"
#include "../../sintable.h"
#include "../../sound.h"
#include "io_wad.h"
#include "../../random.h"
#include "../../surface.h"
#include "../../timer.h"
#include "../../vecmath.h"

// GLOBAL: STUNTGP_D3D 0x60d618
int g_60d618;

// GLOBAL: STUNTGP_D3D 0x60d620
int g_60d620;

// GLOBAL: STUNTGP_D3D 0x60df9c
int g_60df9c;

// GLOBAL: STUNTGP_D3D 0x60f2c0
int g_60f2c0;

// GLOBAL: STUNTGP_D3D 0x60f2c4
DWORD g_60f2c4;

// GLOBAL: STUNTGP_D3D 0x61294c
int g_61294c;

// GLOBAL: STUNTGP_D3D 0x612954
DWORD g_612954;

// Entry 0 is the fallback zone; the list ends at id -1.
// GLOBAL: STUNTGP_D3D 0x483f98
SoundZone g_483f98[32] = {
    {0, 0, {1000.0f, 1000.0f, 1000.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f}},
    {-1},
};

// GLOBAL: STUNTGP_D3D 0x484898
SoundZone *g_484898 = g_483f98;

// GLOBAL: STUNTGP_D3D 0x61b740
SlotFx *g_61b740;

int FUN_4278a0(float *bounds, float *point);

// GLOBAL: STUNTGP_D3D 0x473a24
int g_473a24 = 720;

// GLOBAL: STUNTGP_D3D 0x473a28
float g_473a28 = -5.0f;

// GLOBAL: STUNTGP_D3D 0x4d5b18
float g_4d5b18;

// GLOBAL: STUNTGP_D3D 0x4d5b1c
int g_4d5b1c;

// GLOBAL: STUNTGP_D3D 0x612990
DWORD g_612990;

// GLOBAL: STUNTGP_D3D 0x61299c
int g_61299c;

void FUN_441e20();

// Animation setup of a scene object, as loaded with the level.
struct AnimDef
{
    Vec4 rot;   // 0x00
    Vec4 spin;  // 0x10
    Vec4 unk20; // 0x20
    int type;   // 0x30
    int unk34;  // 0x34
    int unk38;  // 0x38
    int unk3c;  // 0x3c
};

struct AnimObject
{
    int type;    // 0x00
    Vec4 rot;    // 0x04
    Vec4 spin;   // 0x14
    Vec4 unk24;  // 0x24
    int unk34;   // 0x34
    int angleA;  // 0x38
    int angleB;  // 0x3c
    int unk40;   // 0x40
    int unk44;   // 0x44
};

// GLOBAL: STUNTGP_D3D 0x576cd0
AnimObject g_576cd0[32];

// GLOBAL: STUNTGP_D3D 0x624484
AnimDef *g_624484;

// 6 entries at 0x49a1f8, 0x7724 bytes each
// GLOBAL: STUNTGP_D3D 0x49a1f8
Car g_49a1f8[6];

// GLOBAL: STUNTGP_D3D 0x4d5bb8
Car *g_4d5bb8;

// GLOBAL: STUNTGP_D3D 0x60f2b0
DWORD g_60f2b0;

// GLOBAL: STUNTGP_D3D 0x612d10
unsigned int g_612d10;

// GLOBAL: STUNTGP_D3D 0x612d14
Car *g_612d14[6];

// GLOBAL: STUNTGP_D3D 0x474630
Car *g_474630 = g_49a1f8;

void FUN_41af50();
void FUN_404450();
void FUN_418830();
void FUN_41e2d0();

// --- per-tick game logic ---

// STUB: STUNTGP_D3D 0x401770
void FUN_401770()
{
}

// FUNCTION: STUNTGP_D3D 0x4023f0
void FUN_4023f0()
{
    GameSlot *slot = g_4722d0;
    slot->accelX = 0;
    slot->accelY = 0;
    slot->accelZ = 0;
    slot->angAccelX = 0;
    slot->angAccelY = 0;
    slot->angAccelZ = 0;
}

// GLOBAL: STUNTGP_D3D 0x4864e8
Camera g_4864e8 = {
    {0.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, 0, NULL, NULL, 2,
};

// FUNCTION: STUNTGP_D3D 0x4023d0
void FUN_4023d0()
{
    GameSlot *slot = g_4722d0;
    slot->velX = 0;
    slot->velY = 0;
    slot->velZ = 0;
    slot->speed = 0;
}

void FUN_4128f0(Car *car);

// FUNCTION: STUNTGP_D3D 0x412910
void FUN_412910()
{
    Car *car = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        if (car->active == 1)
        {
            FUN_4128f0(car);
        }
        car++;
    }
}

// FUNCTION: STUNTGP_D3D 0x4028d0
void FUN_4028d0(int mode)
{
    GameSlot *slot = g_4722d0;
    slot->camMode = mode;
    slot->roll = 0;
    slot->unk1a4 = 300;
    FUN_412910();
}

// FUNCTION: STUNTGP_D3D 0x402950
void FUN_402950()
{
    if (g_4722d0->preset)
    {
        g_4722d0->camMode = g_4722d0->presetMode;
        g_4722d0->cam = g_4864e8;
        g_4722d0->cam.pos = g_4722d0->preset->pos;
        g_4722d0->cam.target = g_4722d0->preset->target;
        g_4722d0->cam.up = g_4722d0->preset->up;
        g_4722d0->fov = g_4722d0->preset->fov;
        g_4722d0->fov2 = g_4722d0->preset->fov;
        g_4722d0->roll = g_4722d0->preset->roll;
        FUN_4023d0();
        FUN_4023f0();
        FUN_44f4c0();
        if (g_4722d0->presetMode == 4)
        {
            g_4722d0->cam.target.x = g_4722d0->data->unk22dc + g_4722d0->data->posX;
            g_4722d0->cam.target.y = g_4722d0->data->unk22e0 + g_4722d0->data->posY;
            g_4722d0->cam.target.z = g_4722d0->data->unk22e4 + g_4722d0->data->posZ;
        }
        g_4722d0->preset = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x402a80
void FUN_402a80()
{
    if (g_4722d0->fovPending)
    {
        g_4722d0->fov = g_4722d0->fovNext;
        g_4722d0->fovPending = 0;
        FUN_44f4c0();
    }
}

// FUNCTION: STUNTGP_D3D 0x402f60
void FUN_402f60()
{
    g_4722d0->angVelX += g_4722d0->angAccelX;
    g_4722d0->angVelY += g_4722d0->angAccelY;
    g_4722d0->angVelZ += g_4722d0->angAccelZ;
    g_4722d0->angX = (g_4722d0->angX - (int)(g_4722d0->angVelX * -93206.75555555556)) & 0x1ffffff;
    g_4722d0->angY = (g_4722d0->angY - (int)(g_4722d0->angVelY * -93206.75555555556)) & 0x1ffffff;
    g_4722d0->angZ = (int)(g_4722d0->angVelZ * 93206.75555555556) & 0x1ffffff;
    g_4722d0->angVelX *= 0.95f;
    g_4722d0->angVelY *= 0.95f;
    if ((float)fabs(g_4722d0->angVelX) < 0.1f)
    {
        g_4722d0->angVelX = 0;
    }
    if ((float)fabs(g_4722d0->angVelY) < 0.1f)
    {
        g_4722d0->angVelY = 0;
    }
    if ((float)fabs(g_4722d0->angVelZ) < 0.1f)
    {
        g_4722d0->angVelZ = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x403080
void FUN_403080()
{
    g_4722d0->velX += g_4722d0->accelX;
    g_4722d0->velY += g_4722d0->accelY;
    g_4722d0->velZ += g_4722d0->accelZ;
    g_4722d0->velX *= 0.95f;
    g_4722d0->velY *= 0.95f;
    g_4722d0->velZ *= 0.95f;
    g_4722d0->speed = (float)sqrt(
        g_4722d0->velX * g_4722d0->velX + g_4722d0->velY * g_4722d0->velY + g_4722d0->velZ * g_4722d0->velZ
    );
    if ((float)fabs(g_4722d0->velX) < 0.1f)
    {
        g_4722d0->velX = 0;
    }
    if ((float)fabs(g_4722d0->velY) < 0.1f)
    {
        g_4722d0->velY = 0;
    }
    if ((float)fabs(g_4722d0->velZ) < 0.1f)
    {
        g_4722d0->velZ = 0;
    }
}

// GLOBAL: STUNTGP_D3D 0x4722d8
CameraPreset g_4722d8[32] = {
    {{20946.87890625f, 2384.298095703125f, -10466.134765625f, 0.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 0.0f, 1.0f, 0.0f},
     0.0f,
     0x41700000,
     1.4e-44f,
     0},
};

// GLOBAL: STUNTGP_D3D 0x499f90
int g_499f90;

// GLOBAL: STUNTGP_D3D 0x60f020
int g_60f020;

// FUNCTION: STUNTGP_D3D 0x4028f0
void FUN_4028f0(CameraPreset *preset, int mode)
{
    g_4722d0->preset = preset;
    g_4722d0->presetMode = mode;
}

// FUNCTION: STUNTGP_D3D 0x402ab0
void FUN_402ab0(float fov)
{
    g_4722d0->fovPending = 1;
    g_4722d0->fovNext = fov;
}

// FUNCTION: STUNTGP_D3D 0x403310
void FUN_403310(float fov)
{
    g_4722d0->fov = fov;
    g_4722d0->unk0bc = 1.333f;
    g_4722d0->unk0c0 = 1.0f;
    FUN_44f4c0();
}

// FUNCTION: STUNTGP_D3D 0x403770
void FUN_403770(Car *car)
{
    Vec4 target;
    Vec4 delta;

    if (car->active)
    {
        target.x = car->unk22dc + car->posX;
        target.y = car->unk22e0 + car->posY;
        target.z = car->unk22e4 + car->posZ;
        delta.x = target.x - g_4722d0->cam.target.x;
        delta.y = target.y - g_4722d0->cam.target.y;
        delta.z = target.z - g_4722d0->cam.target.z;
        delta.x *= 0.125f;
        delta.y *= 0.125f;
        delta.z *= 0.125f;
        g_4722d0->cam.target.x += delta.x;
        g_4722d0->cam.target.y += delta.y;
        g_4722d0->cam.target.z += delta.z;
    }
}

// FUNCTION: STUNTGP_D3D 0x403800
CameraPreset *FUN_403800(Car *car)
{
    CameraPreset *cur;
    CameraPreset *next;
    float dx;
    float dy;
    float dz;
    float dist;

    if (g_499f90 == 1 || car->active != 1 || !(cur = g_4722d0->unk1cc))
    {
        return g_4722d8;
    }
    next = cur + 1;
    if (next >= &g_4722d8[g_499f90])
    {
        next = g_4722d8;
    }
    dx = cur->pos.x - car->posX;
    dy = cur->pos.y - car->posY;
    dz = cur->pos.z - car->posZ;
    dist = dx * dx + dy * dy + dz * dz;
    dx = next->pos.x - car->posX;
    dy = next->pos.y - car->posY;
    dz = next->pos.z - car->posZ;
    if (dx * dx + dy * dy + dz * dz < dist)
    {
        return next;
    }
    return cur;
}

// FUNCTION: STUNTGP_D3D 0x4038c0
void FUN_4038c0(Car *car)
{
    CameraPreset *preset;
    float dx;
    float dy;
    float dz;
    float scale;

    if (g_4722d0->unk19c < 1.0f)
    {
        return;
    }
    preset = g_4722d0->unk1cc;
    switch (preset->unk34)
    {
    case 0:
        FUN_402ab0(preset->fov);
        break;
    case 1:
        dx = preset->pos.x - car->posX;
        dy = preset->pos.y - car->posY;
        dz = preset->pos.z - car->posZ;
        scale = (float)sqrt(dx * dx + dy * dy + dz * dz) * 2.5e-05f;
        scale *= 10.0f;
        if (scale > 1.0f)
        {
            scale = 1.0f;
        }
        FUN_402ab0(scale * preset->fov);
        break;
    case 2:
        dx = preset->pos.x - car->posX;
        dy = preset->pos.y - car->posY;
        dz = preset->pos.z - car->posZ;
        scale = (float)sqrt(dx * dx + dy * dy + dz * dz) * 2.5e-05f;
        scale *= 2.75f;
        if (scale > 1.0f)
        {
            scale = 1.0f;
        }
        FUN_402ab0(scale * preset->fov);
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x40d200
void FUN_40d200(Car *car)
{
    car->unk22ec = 18.0f;
    car->unk22f0 = 0.0f;
    car->unk22f4 = 0.0f;
    car->unk22fc = 1000.0f;
    car->unk2300 = 0.125f;
    car->unk22dc = 0.0f;
    car->unk22e0 = 150.0f;
    car->unk22e4 = 0.0f;
    car->unk22c8 = 5;
    car->unk2304 = 0;
    FUN_4028d0(5);
    FUN_403310(2.09f);
    FUN_402ab0(2.09f);
    g_60f020 = 2;
}

// FUNCTION: STUNTGP_D3D 0x40d280
void FUN_40d280(Car *car)
{
    car->unk22ec = 13.0f;
    car->unk22f0 = 0.0f;
    car->unk22f4 = 0.0f;
    car->unk22fc = 600.0f;
    car->unk2300 = 0.5f;
    car->unk22dc = 0.0f;
    car->unk22e0 = 150.0f;
    car->unk22e4 = 0.0f;
    car->unk22c8 = 5;
    car->unk2304 = 0;
    FUN_4028d0(5);
    FUN_403310(2.09f);
    FUN_402ab0(2.09f);
    g_60f020 = 1;
}

// FUNCTION: STUNTGP_D3D 0x40d300
void FUN_40d300(Car *car)
{
    car->unk22ec = 20.0f;
    car->unk22f0 = 0.0f;
    car->unk22f4 = 0.0f;
    car->unk22fc = 1500.0f;
    car->unk2300 = 0.125f;
    car->unk22dc = 0.0f;
    car->unk22e0 = 150.0f;
    car->unk22e4 = 0.0f;
    car->unk22c8 = 5;
    car->unk2304 = 0;
    FUN_4028d0(5);
    FUN_403310(2.09f);
    FUN_402ab0(2.09f);
    g_60f020 = 3;
}

// FUNCTION: STUNTGP_D3D 0x40d380
void FUN_40d380(Car *car)
{
    FUN_40d280(car);
    car->unk2304 = 1;
    g_60f020 = 4;
}

// FUNCTION: STUNTGP_D3D 0x4039b0
void FUN_4039b0()
{
    Car *car = g_4722d0->data;
    CameraPreset *preset;

    switch (g_4722d0->camMode)
    {
    case 10:
        preset = FUN_403800(car);
        if (preset != g_4722d0->unk1cc)
        {
            car->unk22dc = 0.0f;
            car->unk22e0 = 0.0f;
            car->unk22e4 = 0.0f;
            FUN_4028f0(preset, 10);
            g_4722d0->unk1cc = preset;
        }
        if (g_4722d0->unk1cc->unk34 != 3)
        {
            FUN_403770(car);
        }
        FUN_4038c0(car);
        break;
    case 11:
        if (g_4722d0->unk1d4 == 1)
        {
            g_4722d0->unk1d4 = 0;
            FUN_40d200(car);
            FUN_4028d0(11);
        }
        break;
    case 12:
        if (g_4722d0->unk1d4 == 1)
        {
            g_4722d0->unk1d4 = 0;
            FUN_40d280(car);
            car->unk22ec = 6.0f;
            car->unk22f0 = 200.0f;
            car->unk22f4 = 0.0f;
            car->unk22fc = 1350.0f;
            FUN_402ab0(1.25f);
            FUN_4028d0(12);
        }
        break;
    case 13:
        if (g_4722d0->unk1d4 == 1)
        {
            g_4722d0->unk1d4 = 0;
            FUN_40d280(car);
            car->unk22ec = 20.0f;
            car->unk22f0 = 260.0f;
            car->unk22f4 = 0.0f;
            car->unk22fc = 2000.0f;
            FUN_4028d0(13);
        }
        break;
    case 14:
        if (g_4722d0->unk1d4 == 1)
        {
            g_4722d0->unk1d4 = 0;
            FUN_40d280(car);
            car->unk22ec = 30.0f;
            car->unk22f0 = 45.0f;
            car->unk22f4 = 0.0f;
            car->unk22fc = 2000.0f;
            FUN_4028d0(14);
        }
        break;
    case 15:
        if (g_4722d0->unk1d4 == 1)
        {
            g_4722d0->unk1d4 = 0;
            FUN_40d280(car);
            FUN_4028d0(15);
        }
        break;
    case 16:
        if (g_4722d0->unk1d4 == 1)
        {
            g_4722d0->unk1d4 = 0;
            FUN_4028d0(16);
        }
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x405210
void FUN_405210()
{
    for (int i = 0; i < 4; i++)
    {
        g_4722d0 = &g_498248[i];
        if (g_498248[i].active == 1)
        {
            FUN_402950();
            FUN_4039b0();
            FUN_402a80();
            FUN_404450();
            FUN_403080();
            FUN_402f60();
        }
    }
    g_4722d0 = g_498248;
}

// Picks a random active car, giving up after 16 tries.
// FUNCTION: STUNTGP_D3D 0x40dd30
void FUN_40dd30()
{
    for (unsigned int i = 0; i < 16; i++)
    {
        int index = FUN_42f1f0(1024) % 6;
        if (g_49a1f8[index].active == 1)
        {
            g_474630 = &g_49a1f8[index];
            i = 16;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x40dd80
void FUN_40dd80()
{
    if (g_612994 != 1)
    {
        g_612994 = 1;
        g_473a24 = 720;
        g_4d5b18 = 0.0f;
        g_473a28 = -5.0f;
        g_4d5b1c = 0;
        FUN_40dd30();
    }
}

// FUNCTION: STUNTGP_D3D 0x40ddd0
void FUN_40ddd0()
{
    FUN_40dd80();
    FUN_447b60();
    if (g_473a24 > 0)
    {
        g_473a24--;
        return;
    }
    g_473a28 -= 0.35f;
    g_4d5b18 += g_473a28;
    if (g_4d5b18 < 0.0f)
    {
        g_4d5b18 = 0.0f;
        g_473a28 = 5.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x40de30
void FUN_40de30()
{
    if (g_61299c == 1)
    {
        g_60f2c0 = 1;
        FUN_40ddd0();
        if (--g_612990 == 0 || g_612968 == 1)
        {
            g_612994 = 0;
            g_61299c = 0;
            g_612990 = 0;
            FUN_441e20();
        }
    }
}

// STUB: STUNTGP_D3D 0x410a10
void FUN_410a10(int index)
{
}

// STUB: STUNTGP_D3D 0x415df0
void FUN_415df0()
{
}

// FUNCTION: STUNTGP_D3D 0x40e340
void FUN_40e340()
{
    for (int i = 0; i < 6; i++)
    {
        g_49a1f8[i].unk1fd0 = 1.0f;
    }
}

void FUN_40e470();
void FUN_40ead0();
void FUN_40ee70();
void FUN_414460();
void FUN_414b30();
void FUN_414c60();
void FUN_414f90();
void FUN_415640();
void FUN_415770();
void FUN_415880();
void FUN_416800();
void FUN_416a80();
void FUN_416f30();
void FUN_4173e0();
void FUN_417800();
void FUN_417ca0();
void FUN_41bea0();
void FUN_41bf20();
void FUN_41d140();

// FUNCTION: STUNTGP_D3D 0x418970
void FUN_418970()
{
    FUN_41bea0();
    FUN_40e470();
    FUN_415640();
    FUN_415770();
    FUN_40ead0();
    FUN_40ee70();
    FUN_414460();
    FUN_414b30();
    FUN_416800();
    FUN_417ca0();
    FUN_416f30();
    FUN_417800();
    FUN_4173e0();
    FUN_416a80();
    FUN_415880();
    FUN_41d140();
    FUN_414c60();
    FUN_414f90();
    if (g_4d5bb8->unk3924 == 1)
    {
        FUN_41bf20();
    }
}

// STUB: STUNTGP_D3D 0x409b60
void FUN_409b60(int a)
{
}

// Flags cars that have fallen off or left the world.
// FUNCTION: STUNTGP_D3D 0x4189e0
void FUN_4189e0()
{
    g_4d5bb8 = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        if (g_4d5bb8->active == 1 && !(g_4d5bb8->unk7268 && *g_4d5bb8->unk7268 == 1))
        {
            if (g_4d5bb8->posY < -5000.0f || g_4d5bb8->posY > 60000.0f ||
                (g_60f2b0 == 3 && g_4d5bb8->posY < 160.0f))
            {
                g_4d5bb8->unk763c = 1;
                g_4d5bb8->unk7638 = 0;
            }
            FUN_409b60(0);
        }
        g_4d5bb8++;
    }
}

// FUNCTION: STUNTGP_D3D 0x418a90
void FUN_418a90()
{
    g_4d5bb8 = g_49a1f8;
    FUN_4189e0();
    FUN_40e340();
    g_4d5bb8 = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        if (g_4d5bb8->active == 1)
        {
            FUN_41af50();
            if (g_4d5bb8->unk7268 && *g_4d5bb8->unk7268 == 1)
            {
                FUN_418970();
            }
            else
            {
                FUN_418830();
            }
        }
        g_4d5bb8++;
    }
    FUN_41e2d0();
    g_4d5bb8 = g_49a1f8;
}

// STUB: STUNTGP_D3D 0x41ab70
void FUN_41ab70(Car *car)
{
}

// FUNCTION: STUNTGP_D3D 0x41af50
void FUN_41af50()
{
    if (g_4d5bb8->unk7268)
    {
        switch (*g_4d5bb8->unk7268)
        {
        case 1:
            FUN_41ab70(g_4d5bb8);
            break;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x442c10
void FUN_442c10(SlotEvent *events)
{
    for (int i = 0; i < 8; i++)
    {
        events[i].count = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x442c30
void FUN_442c30()
{
    GameSlot *slot = g_498248;
    for (int i = 0; i < 4; i++, slot++)
    {
        FUN_442c10(slot->events);
    }
}

// FUNCTION: STUNTGP_D3D 0x442c50
SlotEvent *FUN_442c50(Car *car)
{
    GameSlot *slot = g_498248;
    for (unsigned int i = 0; i < 4; slot++, i++)
    {
        if (slot->active == 1 && slot->data == car)
        {
            return slot->events;
        }
    }
    return NULL;
}

// A clear value of 100 drops every queued message first.
// FUNCTION: STUNTGP_D3D 0x442c80
void FUN_442c80(SlotEvent *events, int frames, char *text, Car *car, int mode, int clear)
{
    if (clear == 100)
    {
        FUN_442c10(events);
    }
    for (unsigned int i = 0; i < 8; i++, events++)
    {
        if (events->count == 0)
        {
            events->count = frames;
            events->duration = frames;
            events->order = g_612cfc;
            events->car = car;
            events->mode = mode;
            strcpy(events->text, text);
            return;
        }
    }
}

extern int g_60f2b4;

// Queues a message for every view (mode 0), every view but the car's own (1) or only the car's (2).
// FUNCTION: STUNTGP_D3D 0x442cf0
void FUN_442cf0(int frames, char *text, Car *car, int mode, int clear)
{
    if (g_60f2b4 == 3)
    {
        return;
    }
    switch (mode)
    {
    case 2:
    {
        SlotEvent *events = FUN_442c50(car);
        if (events)
        {
            FUN_442c80(events, frames, text, car, 2, clear);
        }
        break;
    }
    case 1:
    {
        GameSlot *slot = g_498248;
        for (int i = 0; i < 4; i++, slot++)
        {
            if (slot->active == 1 && slot->data != car)
            {
                FUN_442c80(slot->events, frames, text, car, 1, clear);
            }
        }
        break;
    }
    case 0:
    {
        GameSlot *slot = g_498248;
        for (int i = 0; i < 4; i++, slot++)
        {
            if (slot->active == 1)
            {
                FUN_442c80(slot->events, frames, text, car, 0, clear);
            }
        }
        break;
    }
    }
}

// Sorts the active cars into race order and announces a new leader.
// FUNCTION: STUNTGP_D3D 0x41e2d0
void FUN_41e2d0()
{
    char text[32];
    unsigned int i;
    unsigned int j;
    memset(g_612d14, 0, sizeof(g_612d14));
    unsigned int count = 0;
    for (i = 0; i < 6; i++)
    {
        if (g_49a1f8[i].active == 1)
        {
            g_612d14[count] = &g_49a1f8[i];
            count++;
        }
    }
    g_612d10 = count;
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            if (g_612d14[i]->unk23b0 > g_612d14[j]->unk23b0)
            {
                Car *t = g_612d14[j];
                g_612d14[j] = g_612d14[i];
                g_612d14[i] = t;
            }
        }
    }
    for (i = 0; i < count; i++)
    {
        if (i == 0 && g_612d14[0]->unk24ac)
        {
            int index = g_612d14[0] - g_49a1f8;
            // STRING: STUNTGP_D3D 0x474924
            sprintf(text, "%s %s", g_60f02c[index].name, g_6127a0[24]);
            FUN_442cf0(180, text, &g_49a1f8[index], 1, 100);
        }
        g_612d14[i]->unk24ac = i;
    }
}

// GLOBAL: STUNTGP_D3D 0x477658
float g_477658[6][4] = {
    {-1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, -1.0f, 0.0f},
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, -1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
};

// GLOBAL: STUNTGP_D3D 0x4776d8
float g_4776d8[8][4] = {
    {-0.5f, 0.5f, -0.5f, 0.0f},
    {0.5f, 0.5f, -0.5f, 0.0f},
    {0.5f, -0.5f, -0.5f, 0.0f},
    {-0.5f, -0.5f, -0.5f, 0.0f},
    {-0.5f, 0.5f, 0.5f, 0.0f},
    {0.5f, 0.5f, 0.5f, 0.0f},
    {0.5f, -0.5f, 0.5f, 0.0f},
    {-0.5f, -0.5f, 0.5f, 0.0f},
};

// Point-in-oriented-box test. bounds: centre (0), size (4), two axes (8, 12).
// FUNCTION: STUNTGP_D3D 0x4278a0
int FUN_4278a0(float *bounds, float *point)
{
    float m[16];
    float t[16];
    float v[4];
    float e[4];
    float d;
    v[0] = bounds[9] * bounds[14] - bounds[13] * bounds[10];
    v[1] = bounds[12] * bounds[10] - bounds[8] * bounds[14];
    v[2] = bounds[13] * bounds[8] - bounds[12] * bounds[9];
    Matrix_FromRows(v, &bounds[8], &bounds[12], m);
    Matrix_Transpose(t, m);
    float dx = point[0] - bounds[0];
    float dy = point[1] - bounds[1];
    float dz = point[2] - bounds[2];
    v[0] = t[8] * dz + t[4] * dy + t[0] * dx + t[12];
    v[1] = t[9] * dz + t[5] * dy + t[1] * dx + t[13];
    v[2] = t[10] * dz + t[6] * dy + t[2] * dx + t[14];
    v[0] += bounds[0];
    v[1] += bounds[1];
    v[2] += bounds[2];

    e[0] = g_4776d8[0][0] * bounds[4];
    e[1] = g_4776d8[0][1] * bounds[5];
    e[2] = g_4776d8[0][2] * bounds[6];
    e[0] += bounds[0];
    e[1] += bounds[1];
    e[2] += bounds[2];
    e[0] = v[0] - e[0];
    e[1] = v[1] - e[1];
    e[2] = v[2] - e[2];
    d = g_477658[0][2] * e[2] + g_477658[0][1] * e[1] + g_477658[0][0] * e[0];
    if (*(int *)&d >= 0)
    {
        return 0;
    }
    d = g_477658[1][2] * e[2] + g_477658[1][1] * e[1] + g_477658[1][0] * e[0];
    if (*(int *)&d >= 0)
    {
        return 0;
    }
    d = g_477658[2][2] * e[2] + g_477658[2][1] * e[1] + g_477658[2][0] * e[0];
    if (*(int *)&d >= 0)
    {
        return 0;
    }

    e[0] = g_4776d8[6][0] * bounds[4];
    e[1] = g_4776d8[6][1] * bounds[5];
    e[2] = g_4776d8[6][2] * bounds[6];
    e[0] += bounds[0];
    e[1] += bounds[1];
    e[2] += bounds[2];
    e[0] = v[0] - e[0];
    e[1] = v[1] - e[1];
    e[2] = v[2] - e[2];
    d = g_477658[3][2] * e[2] + g_477658[3][1] * e[1] + g_477658[3][0] * e[0];
    if (*(int *)&d >= 0)
    {
        return 0;
    }
    d = g_477658[4][2] * e[2] + g_477658[4][1] * e[1] + g_477658[4][0] * e[0];
    if (*(int *)&d >= 0)
    {
        return 0;
    }
    d = g_477658[5][2] * e[2] + g_477658[5][1] * e[1] + g_477658[5][0] * e[0];
    return *(int *)&d < 0;
}

// STUB: STUNTGP_D3D 0x425df0
void FUN_425df0(Scene *scene, ObjectDef *def, int type)
{
}

// FUNCTION: STUNTGP_D3D 0x426260
void FUN_426260()
{
    if (g_612be8 == 2)
    {
        return;
    }
    Scene *scene = g_636418[3].scene;
    if (scene && scene->objectCount > 1)
    {
        ObjectDef *def = scene->objects;
        for (DWORD i = 0; i < scene->objectCount; i++)
        {
            int type = g_624484[i].type;
            if (type == 1 || type == 2 || type == 3)
            {
                FUN_425df0(scene, def, type);
            }
            AnimDef *src = &g_624484[i];
            AnimObject *obj = &g_576cd0[i];
            obj->type = src->type;
            obj->rot = src->rot;
            obj->spin = src->spin;
            obj->unk24 = src->unk20;
            obj->unk34 = src->unk34;
            obj->unk44 = src->unk38;
            obj->angleA = 0;
            def++;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x427010
void FUN_427010(AnimObject *obj)
{
    obj->angleA = (obj->angleA + 0x80) & 0x1fff;
}

// FUNCTION: STUNTGP_D3D 0x427030
void FUN_427030(AnimObject *obj, int step)
{
    obj->angleA = (obj->angleA - step) & 0x1fff;
}

// FUNCTION: STUNTGP_D3D 0x427040
void FUN_427040(AnimObject *obj, int step)
{
    obj->angleB = (obj->angleB - step) & 0x1fff;
}

// FUNCTION: STUNTGP_D3D 0x427050
void FUN_427050(AnimObject *obj, ObjectDef *def)
{
    // four lanes to match the original frame layout; w is never used
    float delta[4];
    float x;
    float y;
    float z;
    delta[0] = obj->spin.x * (1.0f / 60.0f);
    delta[1] = obj->spin.y * (1.0f / 60.0f);
    delta[2] = obj->spin.z * (1.0f / 60.0f);
    obj->rot.x = x = obj->rot.x + delta[0];
    obj->rot.y = y = obj->rot.y + delta[1];
    obj->rot.z = z = obj->rot.z + delta[2];
    if (x < 0.0f)
    {
        obj->rot.x = x + 360.0f;
    }
    else if (x > 360.0f)
    {
        obj->rot.x = x - 360.0f;
    }
    if (y < 0.0f)
    {
        obj->rot.y = y + 360.0f;
    }
    else if (y > 360.0f)
    {
        obj->rot.y = y - 360.0f;
    }
    if (z < 0.0f)
    {
        obj->rot.z = z + 360.0f;
    }
    else if (z > 360.0f)
    {
        obj->rot.z = z - 360.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x427140
void FUN_427140()
{
    if (g_636418[3].scene && g_636418[3].scene->objectCount > 1)
    {
        ObjectDef *def = g_636418[3].scene->objects;
        AnimObject *obj = g_576cd0;
        DWORD count = g_636418[3].scene->objectCount;
        for (DWORD i = 1; i < count; i++)
        {
            obj++;
            def++;
            switch (obj->type)
            {
            case 1:
                FUN_427010(obj);
                break;
            case 3:
                FUN_427030(obj, -0x100);
                break;
            case 4:
                FUN_427050(obj, def);
                break;
            case 16:
                FUN_427050(obj, def);
                FUN_427030(obj, 0x80);
                FUN_427040(obj, 0x2a);
                break;
            case 2:
            case 8:
            case 9:
                FUN_427030(obj, 0x100);
                break;
            case 5:
            case 6:
            case 10:
                FUN_427030(obj, 0x40);
                break;
            case 11:
                FUN_427030(obj, 0x80);
                break;
            case 12:
                FUN_427030(obj, 8);
                break;
            case 13:
                FUN_427030(obj, 0x10);
                break;
            case 7:
            case 14:
                FUN_427030(obj, 0x20);
                break;
            }
        }
    }
}

// --- fpu ---

// FUNCTION: STUNTGP_D3D 0x4294f0
void FUN_4294f0()
{
    _control87(_PC_53, _MCW_PC);
    _control87(_RC_NEAR, _MCW_RC);
}

// FUNCTION: STUNTGP_D3D 0x429510
void FUN_429510()
{
    FUN_4294f0();
}

// FUNCTION: STUNTGP_D3D 0x431810
void FUN_431810()
{
    FUN_431790();
}

// --- timer ---

void FUN_443100();
void FUN_443630();
void FUN_443780();
void FUN_443890();
void FUN_443950();
void FUN_443980();
void FUN_443e20();
void FUN_444390();
void FUN_444410();
void FUN_4446d0();
void FUN_444ae0();
void FUN_444c00();
void FUN_444c50();
void FUN_40e360(Car *sub);
void FUN_4051e0();
void FUN_403310(float fov);
void FUN_430d40(int slot, int id);
void FUN_444c20();
void FUN_40e380(Car *sub);

// GLOBAL: STUNTGP_D3D 0x60df98
int g_60df98;

// GLOBAL: STUNTGP_D3D 0x60f010
float g_60f010;

// GLOBAL: STUNTGP_D3D 0x60f2c8
int g_60f2c8;

// GLOBAL: STUNTGP_D3D 0x60f2cc
int g_60f2cc;

// STUB: STUNTGP_D3D 0x443100
void FUN_443100()
{
}

// FUNCTION: STUNTGP_D3D 0x443560
void FUN_443560()
{
    GhostRecord *rec = g_60d628;
    for (int i = 0; i < 4; i++, rec++)
    {
        if (rec->unk00 == 1)
        {
            ((Car *)rec->unk04)->unk7640 = 60;
        }
    }
}

// STUB: STUNTGP_D3D 0x443630
void FUN_443630()
{
}

// GLOBAL: STUNTGP_D3D 0x60f2b4
int g_60f2b4;

// GLOBAL: STUNTGP_D3D 0x60eff4
DWORD g_60eff4;

// GLOBAL: STUNTGP_D3D 0x60d680
int g_60d680;

// GLOBAL: STUNTGP_D3D 0x60f01c
int g_60f01c;

// FUNCTION: STUNTGP_D3D 0x41d9f0
void FUN_41d9f0(int *a, int *b)
{
    int others = 0;
    int count = 0;
    for (int i = 0; i < 6; i++)
    {
        if (g_49a1f8[i].active == 1 && !g_49a1f8[i].unk24e0)
        {
            if (g_49a1f8[i].unk2640 == 1)
            {
                count++;
            }
            else
            {
                others++;
            }
        }
    }
    *a = count;
    if (g_61299c == 1)
    {
        *b = 1;
    }
    else
    {
        *b = others;
    }
}

// STUB: STUNTGP_D3D 0x444070
void FUN_444070()
{
}

void FUN_447a90(Fader *fader);
void FUN_447aa0(Fader *fader);

// FUNCTION: STUNTGP_D3D 0x444300
void FUN_444300()
{
    if (!g_4d5bb8->race.unk2c)
    {
        if (g_4d5bb8->race.unk20 == 480)
        {
            FUN_447a90(&g_61b740->faders[10]);
            g_4d5bb8->race.unk44 = 240;
        }
        if (g_4d5bb8->race.unk44 && --g_4d5bb8->race.unk44 == 120)
        {
            FUN_447aa0(&g_61b740->faders[10]);
            g_4d5bb8->race.unk48 = (g_4d5bb8->race.unk48 + 1) % 3;
            g_4d5bb8->race.unk20 = 0;
        }
    }
}

extern float g_60f2d0[31];

// FUNCTION: STUNTGP_D3D 0x405880
void FUN_405880(Car *car)
{
    if (car->unk1b8c > g_60f2d0[15])
    {
        car->unk1f0c = 3;
        return;
    }
    if (car->unk1b8c > g_60f2d0[16])
    {
        car->unk1f0c = 2;
        return;
    }
    if (car->unk1b8c > g_60f2d0[17])
    {
        car->unk1f0c = 1;
        return;
    }
    car->unk1f0c = 0;
}

// FUNCTION: STUNTGP_D3D 0x4058f0
void FUN_4058f0()
{
    for (int i = 0; i < 6; i++)
    {
        if (g_49a1f8[i].active == 1)
        {
            g_49a1f8[i].unk26a4 = 300;
            if (g_60f02c[i].unk1c != 1)
            {
                g_49a1f8[i].unk1b8c = (float)g_60f02c[i].unk1c;
                g_49a1f8[i].unk1b90 = (float)g_60f02c[i].unk20;
                g_49a1f8[i].unk2640 = 1;
                FUN_405880(&g_49a1f8[i]);
            }
            else
            {
                g_49a1f8[i].unk2640 = 0;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x41de40
void FUN_41de40()
{
    for (int i = 0; i < 6; i++)
    {
        if (g_49a1f8[i].active == 1 && g_49a1f8[i].unk23cc == -1)
        {
            g_49a1f8[i].unk23cc = 0;
        }
    }
}

// GLOBAL: STUNTGP_D3D 0x60eff0
int g_60eff0;

// GLOBAL: STUNTGP_D3D 0x60eff8
DWORD g_60eff8;

// GLOBAL: STUNTGP_D3D 0x60effc
DWORD g_60effc;

// GLOBAL: STUNTGP_D3D 0x60d66c
int g_60d66c;

extern DWORD g_60f000[4];

// Whether the best lap beats the stored record.
// FUNCTION: STUNTGP_D3D 0x442fb0
int FUN_442fb0()
{
    if (!g_60d66c)
    {
        return 0;
    }
    return g_60f000[0] < g_60d628[0].ghost->unk1c;
}

// FUNCTION: STUNTGP_D3D 0x443dd0
void FUN_443dd0()
{
    FUN_4028d0(10);
}

// FUNCTION: STUNTGP_D3D 0x443de0
void FUN_443de0()
{
    if (g_4d5bb8->race.unk4c[7] != 1)
    {
        g_4d5bb8->race.unk4c[7] = 1;
        g_4d5bb8->race.unk4c[8] = 0;
    }
}

// Only steps while the car is active, so inactive slots shift the rest onto the wrong cars.
// FUNCTION: STUNTGP_D3D 0x412780
void FUN_412780()
{
    if (g_60f2b4 == 1 && g_60eff0 != 3)
    {
        Car *car = g_49a1f8;
        for (int i = 0; i < 6; i++)
        {
            if (car->active == 1)
            {
                car->unk229c += 6;
                car->wheels[0].unk04 = 0.0f;
                car->wheels[1].unk04 = 0.0f;
                car->wheels[2].unk04 = 0.0f;
                car->wheels[3].unk04 = 0.0f;
                car++;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x4436e0
void FUN_4436e0(Car *car)
{
    if (car->active == 1 && !car->unk2278)
    {
        car->unk2278 = 1;
    }
}

void FUN_443700(Car *car);

// FUNCTION: STUNTGP_D3D 0x443730
void FUN_443730()
{
    for (int i = 0; i < 6; i++)
    {
        FUN_443700(&g_49a1f8[i]);
    }
}

// FUNCTION: STUNTGP_D3D 0x443750
void FUN_443750()
{
    for (int i = 0; i < 6; i++)
    {
        FUN_4436e0(&g_49a1f8[i]);
    }
}

// FUNCTION: STUNTGP_D3D 0x443780
void FUN_443780()
{
    int a;
    int b;
    if (g_60f2b4 == 2)
    {
        switch (g_60f2b0)
        {
        case 1:
        case 2:
            FUN_41d9f0(&a, &b);
            if (!b && !a)
            {
                g_60f2b4 = 3;
                FUN_443730();
                return;
            }
            break;
        case 3:
            if (!g_60eff4)
            {
                return;
            }
            if (g_60eff4 == 1)
            {
                // The score field is reached by offset: typing it in Car perturbs codegen elsewhere.
                g_49a1f8[0].unk23d0 = (int)*(float *)&g_49a1f8[0].unk2584[0x88];
                g_49a1f8[0].unk23d4 = 0;
                g_49a1f8[0].unk23d8 = 0;
                FUN_401220(5, 0, g_4d5bb8->unk23d0);
                *(float *)&g_4d5bb8->unk2584[0x88] = (float)g_49a1f8[0].unk23d0;
                FUN_442cf0(300, g_6127a0[45], g_4d5bb8, 0, 100);
                g_60eff4 = 0;
                g_60d680 = 180;
                FUN_443730();
                break;
            }
            g_60eff4--;
            return;
        default:
            return;
        }
        if (g_60f2b4 == 3)
        {
            FUN_443730();
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x443890
void FUN_443890()
{
    if (g_60d680 && --g_60d680 == 0)
    {
        g_49a1f8[0].unk24e0 = 1;
        g_60eff4 = 0;
        g_60f2b4 = 3;
        return;
    }
    if (g_60eff4 && g_60eff4 <= 600)
    {
        if (g_60eff4 == 600)
        {
            FUN_442cf0(180, g_6127a0[97], g_4d5bb8, 2, 0);
        }
        if (g_60eff4 % 60 == 0)
        {
            FUN_461150(22, 0, 27050 - g_60eff4 * 500 / 60, 255 - g_60eff4 * 10 / 60, 0, 1, 0);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x443950
void FUN_443950()
{
    FUN_444c00();
    g_60f2b0 = 2;
    g_60f2b4 = 1;
    if (g_60f01c == 10)
    {
        FUN_4051e0();
    }
}

// FUNCTION: STUNTGP_D3D 0x443980
void FUN_443980()
{
    FUN_444c00();
    g_60f2b0 = 3;
    g_60f2b4 = 1;
    g_60d680 = 0;
    FUN_442cf0(300, g_6127a0[44], g_4d5bb8, 0, 0);
    g_4d5bb8->race.unk80[6] = 0;
    g_4d5bb8->race.unk80[5] = 0;
    FUN_4028d0(7);
    FUN_403310(2.55f);
}

// FUNCTION: STUNTGP_D3D 0x443e10
void FUN_443e10(Car *car)
{
    car->race.unk4c[7] = 0;
    car->race.unk4c[8] = 0;
}

// FUNCTION: STUNTGP_D3D 0x443e20
void FUN_443e20()
{
    if (g_4d5bb8->race.unk4c[7])
    {
        if (!g_4d5bb8->race.unk4c[8])
        {
            FUN_461150(47, 0, 0, 127, 0, 0, 0);
        }
        if (g_61b634 != 20)
        {
            FUN_430d40(15, 20);
        }
        if (++g_4d5bb8->race.unk4c[8] > 120)
        {
            g_4d5bb8->race.unk4c[7] = 0;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x444390
void FUN_444390()
{
    if (g_498248[0].data->race.unk1c)
    {
        g_61b740 = &g_498248[0].fx;
        FUN_444070();
        FUN_444300();
    }
}

// STUB: STUNTGP_D3D 0x444410
void FUN_444410()
{
}

// FUNCTION: STUNTGP_D3D 0x444550
int FUN_444550()
{
    Car *car = g_49a1f8;
    for (unsigned int i = 0; i < 6; i++, car++)
    {
        if (car->active == 1 && car->unk2640 == 0 && car->unk24e0 != 1)
        {
            return 0;
        }
    }
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x444670
int FUN_444670()
{
    int total = 0;
    int finished = 0;
    Car *car = g_49a1f8;
    for (int i = 0; i < 6; i++, car++)
    {
        if (car->active == 1)
        {
            total++;
            if ((car->unk24e0 == 1 && car->race.unk4c[0] == 0 && car->race.unk30 == 0) || car->unk2640 == 1 ||
                car->unk24e8 == 1)
            {
                finished++;
            }
        }
    }
    return finished == total;
}

// STUB: STUNTGP_D3D 0x4446d0
void FUN_4446d0()
{
}

// FUNCTION: STUNTGP_D3D 0x444a90
int FUN_444a90()
{
    if (g_61299c == 1)
    {
        return 0;
    }
    int total = 0;
    int finished = 0;
    Car *car = g_49a1f8;
    for (int i = 0; i < 6; i++, car++)
    {
        if (car->active == 1)
        {
            total++;
            if (car->unk2640 == 1 || car->race.unk18 == 1)
            {
                finished++;
            }
        }
    }
    return finished == total;
}

// STUB: STUNTGP_D3D 0x444ae0
void FUN_444ae0()
{
}

// FUNCTION: STUNTGP_D3D 0x444c00
void FUN_444c00()
{
    for (int i = 0; i < 6; i++)
    {
        g_49a1f8[i].race.unk00 = 301;
    }
}

// FUNCTION: STUNTGP_D3D 0x444c20
void FUN_444c20()
{
    FUN_4058f0();
    g_60f2b4 = 2;
    FUN_41de40();
}

// FUNCTION: STUNTGP_D3D 0x444c40
void FUN_444c40(Car *car)
{
    car->race.unk00 = 0;
}

// Start-of-race countdown: plays a beep and shows the next digit every second.
// FUNCTION: STUNTGP_D3D 0x444c50
void FUN_444c50()
{
    g_4d5bb8 = g_4722d0->data;
    if (g_4d5bb8->race.unk00)
    {
        if (--g_4d5bb8->race.unk00 > 60)
        {
            FUN_412780();
        }
        if (g_4d5bb8->race.unk00 > 180)
        {
            if (g_4d5bb8->race.unk00 == 240)
            {
                FUN_461150(44, 0, 0, 255, 0, 0, 0);
            }
            if (g_61b634 != 19)
            {
                FUN_430d40(15, 19);
            }
        }
        else if (g_4d5bb8->race.unk00 > 120)
        {
            if (g_4d5bb8->race.unk00 == 180)
            {
                FUN_461150(44, 0, 0, 255, 0, 0, 0);
            }
            if (g_61b634 != 18)
            {
                FUN_430d40(15, 18);
            }
        }
        else if (g_4d5bb8->race.unk00 > 60)
        {
            if (g_4d5bb8->race.unk00 == 120)
            {
                FUN_461150(44, 0, 0, 255, 0, 0, 0);
            }
            if (g_61b634 != 17)
            {
                FUN_430d40(15, 17);
            }
        }
        else if (g_4d5bb8->race.unk00 > 0)
        {
            if (g_61b634 != 16)
            {
                FUN_430d40(15, 16);
            }
            if (g_4d5bb8->race.unk00 == 60)
            {
                FUN_461150(45, 0, 0, 255, 0, 0, 0);
                FUN_443750();
                FUN_444c20();
                g_4722d0->data->unk767c = 0;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x4439f0
void FUN_4439f0()
{
    g_60f2c4 = 0;
    switch (g_60df98)
    {
    case 2:
    case 5:
        FUN_443950();
        break;
    case 4:
        FUN_443100();
        break;
    case 3:
        FUN_443980();
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x443a30
void FUN_443a30()
{
    if (g_60f2cc != 480)
    {
        if (g_60f010 * g_4d5bb8->unk23b0 * 0.01f > g_60f010 - 30000.0f)
        {
            g_60f2cc = 480;
            FUN_444c00();
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x443a80
void FUN_443a80()
{
    if (g_60f2c8)
    {
        if (--g_60f2c8 <= 0)
        {
            FUN_4439f0();
            g_60f2c8 = 0;
        }
    }
    FUN_443780();
    switch (g_60f2b0)
    {
    case 2:
    case 5:
    {
        for (int i = 0; i < 4; i++)
        {
            GameSlot *slot = &g_498248[i];
            if (slot->active == 1)
            {
                g_4722d0 = slot;
                g_4d5bb8 = (Car *)slot->data;
                g_61b740 = &slot->fx;
                FUN_443e20();
                FUN_4446d0();
                FUN_444c50();
                FUN_444ae0();
                FUN_444410();
                FUN_444390();
            }
        }
        g_4722d0 = g_498248;
        break;
    }
    case 3:
        g_4d5bb8 = g_474630 = (Car *)g_4722d0->data;
        FUN_443890();
        FUN_444c50();
        FUN_444ae0();
        FUN_4446d0();
        FUN_40e360((Car *)g_4722d0->data);
        FUN_40e380((Car *)g_4722d0->data);
        break;
    case 4:
        g_4d5bb8 = g_474630 = (Car *)g_4722d0->data;
        FUN_443630();
        FUN_443e20();
        FUN_444c50();
        FUN_443a30();
        FUN_40e360((Car *)g_4722d0->data);
        FUN_40e380((Car *)g_4722d0->data);
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x442de0
void FUN_442de0()
{
    GameSlot *slot = g_498248;
    for (int i = 0; i < 4; i++, slot++)
    {
        if (slot->active == 1)
        {
            SlotEvent *oldest = NULL;
            SlotEvent *event = slot->events;
            for (int j = 0; j < 8; j++, event++)
            {
                if (event->count != 0)
                {
                    if (oldest == NULL || oldest->order > event->order)
                    {
                        oldest = event;
                    }
                }
            }
            if (oldest != NULL)
            {
                oldest->count--;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x446110
void FUN_446110()
{
    SoundZone *found = &g_483f98[0];
    int searching = 1;
    for (SoundZone *zone = &g_483f98[1]; zone->id != -1 && searching == 1; zone++)
    {
        if (FUN_4278a0(zone->bounds, &g_4722d0->cam.pos.x) == 1)
        {
            found = zone;
            searching = 0;
        }
    }
    if (found != g_484898 && found->id >= 0 && found->id <= 6)
    {
        FUN_460af0(found->id);
        g_484898 = found;
    }
}

// FUNCTION: STUNTGP_D3D 0x447ab0
void FUN_447ab0(Fader *fader)
{
    if (fader->active)
    {
        if (fader->value < fader->target)
        {
            float step = (100.0f - (fader->target - fader->value)) * 0.0625f;
            if (step < 0.1f)
            {
                step = 0.1f;
            }
            fader->value += step;
            if (fader->value > fader->target)
            {
                fader->active = 0;
                fader->value = fader->target;
            }
        }
        else
        {
            float step = (fader->value - fader->target) * 0.0625f;
            if (step < 0.1f)
            {
                step = 0.1f;
            }
            fader->value -= step;
            if (fader->value < fader->target)
            {
                fader->value = fader->target;
                fader->active = 0;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x447b50
void FUN_447b50()
{
    g_61b740->unk000 = 1;
}

// FUNCTION: STUNTGP_D3D 0x447b60
void FUN_447b60()
{
    g_61b740->unk000 = 0;
}

// FUNCTION: STUNTGP_D3D 0x447b70
void FUN_447b70(int delay)
{
    g_61b740 = &g_4722d0->fx;
    g_61b740->delay = delay;
    g_61b740->faders[0].active = 1;
    g_61b740->faders[0].value = 100.0f;
    g_61b740->faders[0].target = 0.0f;
}

// FUNCTION: STUNTGP_D3D 0x447ba0
void FUN_447ba0(int delay)
{
    g_61b740 = &g_4722d0->fx;
    g_61b740->delay = delay;
    g_61b740->faders[0].active = 1;
    g_61b740->faders[0].value = 0.0f;
    g_61b740->faders[0].target = 100.0f;
}

// FUNCTION: STUNTGP_D3D 0x447bd0
void FUN_447bd0(int delay)
{
    GameSlot *saved = g_4722d0;
    g_4722d0 = g_498248;
    for (int i = 0; i < 4; i++)
    {
        if (!g_4722d0->data->unk24e0)
        {
            FUN_447b70(delay);
        }
        g_4722d0++;
    }
    g_4722d0 = saved;
}

// FUNCTION: STUNTGP_D3D 0x447c30
void FUN_447c30(int delay)
{
    GameSlot *saved = g_4722d0;
    g_4722d0 = g_498248;
    for (int i = 0; i < 4; i++)
    {
        if (!g_4722d0->data->unk24e0)
        {
            FUN_447ba0(delay);
        }
        g_4722d0++;
    }
    g_4722d0 = saved;
}

// FUNCTION: STUNTGP_D3D 0x447c90
void FUN_447c90()
{
    for (int i = 0; i < 4; i++)
    {
        if (g_498248[i].active == 1)
        {
            g_4722d0 = &g_498248[i];
            g_61b740 = &g_4722d0->fx;
            if (g_4722d0->data->unk23c4 != -1)
            {
                FUN_447ab0(&g_61b740->faders[3]);
                FUN_447ab0(&g_61b740->faders[4]);
                FUN_447ab0(&g_61b740->faders[5]);
            }
            if (g_4722d0->data->unk7648 == 1)
            {
                FUN_447ab0(&g_61b740->faders[6]);
            }
            if (g_61b740->faders[0].active == 1)
            {
                if (g_61b740->delay)
                {
                    g_61b740->delay--;
                }
                else
                {
                    FUN_447ab0(&g_61b740->faders[0]);
                }
            }
            if (g_61b740->faders[8].active == 1)
            {
                FUN_447ab0(&g_61b740->faders[8]);
            }
        }
    }
    g_4722d0 = g_498248;
    FUN_442de0();
}

extern float g_482678;
extern float g_48267c;
extern float g_482680;

// FUNCTION: STUNTGP_D3D 0x401d70
void FUN_401d70(float *v, float scale)
{
    if (v[0] * v[0] + v[1] * v[1] + v[2] * v[2] <= 27777.777f)
    {
        float g[4];
        g[0] = g_482678 * scale;
        g[1] = g_48267c * scale;
        g[2] = g_482680 * scale;
        v[0] += g[0];
        v[1] += g[1];
        v[2] += g[2];
    }
}

// FUNCTION: STUNTGP_D3D 0x422620
DWORD Color_Lerp(DWORD from, DWORD to, int t)
{
    int fromG = (BYTE)(from >> 8);
    int fromR = (BYTE)(from >> 16);
    int toR = (BYTE)(to >> 16);
    int fromB = (BYTE)from;
    return ((fromR + ((toR - fromR) * t >> 8)) << 16) |
           ((fromG + (((BYTE)(to >> 8) - fromG) * t >> 8)) << 8) | (fromB + (((BYTE)to - fromB) * t >> 8));
}

// FUNCTION: STUNTGP_D3D 0x45e170
void FUN_45e170(Unk62a078 *p)
{
    p->unk00 = 2;
}

// FUNCTION: STUNTGP_D3D 0x45e180
void FUN_45e180(Unk62a078 *p)
{
    DWORD *anim = p->anim;
    if (anim)
    {
        int frame = p->frame;
        p->frame += 0x6aa;
        if ((DWORD)(frame / 4096) >= anim[2] - 1)
        {
            p->frame = 0;
            if (p->mode == 1)
            {
                FUN_45e170(p);
            }
        }
    }
}

// 3D billboard draw request, filled from the template g_486538.
struct Billboard
{
    DWORD unk00;      // 0x00
    short texture;    // 0x04
    short alpha;      // 0x06
    DWORD colors[4];  // 0x08
    Vec4 pos;         // 0x18
    float size[3];    // 0x28
    int unk34;        // 0x34
    Vec4 unk38;       // 0x38
    Vec4 dir;         // 0x48
    int unk58;        // 0x58
    int unk5c;        // 0x5c
    int unk60;        // 0x60
    int unk64;        // 0x64
};

// GLOBAL: STUNTGP_D3D 0x486538
Billboard g_486538 = {0x20, 1, 0x80, {0xffffff, 0xffffff, 0xffffff, 0xffffff}, {0.0f, 0.0f, 0.0f, 0.0f},
                       {1.0f, 1.0f, 1.0f}, 0, {0.0f, 0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, 1, 0, 0, 2};

// FUNCTION: STUNTGP_D3D 0x45e4b0
void FUN_45e4b0(Billboard *billboard, float angle)
{
    int i = (int)(angle * (8192.0f / 360.0f));
    billboard->dir.z = 0.0f;
    billboard->dir.x = g_cosTable[i];
    billboard->dir.y = g_sinTable[i];
}

// STUB: STUNTGP_D3D 0x434590
void FUN_434590(Billboard *billboard)
{
}

// FUNCTION: STUNTGP_D3D 0x45e4f0
void FUN_45e4f0()
{
    if (g_62d478)
    {
        Billboard billboard = g_486538;
        Unk62a078 *p = g_62a078;
        for (int i = 0x40; i; i--, p++)
        {
            if (p->unk00 == 1 && p->unk7c == 1)
            {
                if (p->anim)
                {
                    billboard.texture = (short)(((TextureSlot *)p->anim[0] - g_6227d4) + p->frame / 4096);
                }
                else
                {
                    billboard.texture = (short)p->texture;
                }
                if (p->flags & 4)
                {
                    FUN_45e4b0(&billboard, p->angle);
                }
                else
                {
                    billboard.dir = g_486538.dir;
                }
                billboard.alpha = (short)(int)p->alphaNow;
                billboard.unk00 = p->unk98;
                billboard.colors[0] = p->color;
                billboard.colors[1] = p->color;
                billboard.colors[2] = p->color;
                billboard.colors[3] = p->color;
                billboard.pos = p->pos;
                billboard.size[0] = p->sizeNow;
                billboard.size[1] = p->sizeNow;
                billboard.size[2] = p->sizeNow;
                FUN_434590(&billboard);
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45e1d0
void FUN_45e1d0()
{
    if (g_62d478)
    {
        g_62d478 = 0;
        Unk62a078 *p = g_62a078;
        for (int i = 0; i < 0x40; i++, p++)
        {
            if (p->unk00 == 1)
            {
                g_62d478 = 1;
                p->pos.x = p->vel[0] + p->pos.x;
                p->pos.y = p->vel[1] + p->pos.y;
                p->pos.z = p->vel[2] + p->pos.z;
                if (p->vel[1] < 166.66667f)
                {
                    FUN_401d70(p->vel, p->gravity);
                }
                if (p->flags & 2)
                {
                    if ((float)p->time < p->alphaIn)
                    {
                        p->alphaNow = (float)p->time * p->alpha / p->alphaIn;
                    }
                    else if ((float)p->time > (float)p->lifetime - p->alphaOut)
                    {
                        p->alphaNow = (float)(p->lifetime - p->time) * p->alpha / p->alphaOut;
                    }
                    else
                    {
                        p->alphaNow = p->alpha;
                    }
                }
                else
                {
                    p->alphaNow = p->alpha;
                }
                if (p->flags & 1)
                {
                    if ((float)p->time < p->sizeIn)
                    {
                        p->sizeNow = (float)p->time * p->size / p->sizeIn;
                    }
                    else if ((float)p->time > (float)p->lifetime - p->sizeOut)
                    {
                        p->sizeNow = (float)(p->lifetime - p->time) * p->size / p->sizeOut;
                    }
                    else
                    {
                        p->sizeNow = p->size;
                    }
                }
                else
                {
                    p->sizeNow = p->size;
                }
                if (p->flags & 4)
                {
                    float angle = p->spin + p->angle;
                    p->angle = angle;
                    if (angle >= 360.0f)
                    {
                        p->angle = angle - 360.0f;
                    }
                    else if (angle < 0.0f)
                    {
                        p->angle = angle + 360.0f;
                    }
                }
                if (p->flags & 8)
                {
                    if ((float)p->time < p->colorIn)
                    {
                        p->color = Color_Lerp(p->colors[0], p->colors[1], (int)((float)p->time * 255.0f / p->colorIn));
                    }
                    else if ((float)p->time > (float)p->lifetime - p->colorOut)
                    {
                        p->color = Color_Lerp(
                            p->colors[1], p->colors[2],
                            (int)(255.0f - (float)(p->lifetime - p->time) * 255.0f / p->colorOut)
                        );
                    }
                    else
                    {
                        p->color = p->colors[1];
                    }
                }
                else
                {
                    p->color = p->colors[0];
                }
                if (p->mode == 2)
                {
                    if (++p->time >= p->lifetime)
                    {
                        FUN_45e170(p);
                    }
                }
                FUN_45e180(p);
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45e7b0
void FUN_45e7b0(PcxHeader *header)
{
    header->manufacturer = 10;
    header->version = 5;
    header->encoding = 1;
    header->bitsPerPixel = 8;
    header->xMin = 0;
    header->yMin = 0;
    header->xMax = g_48971c - 1;
    header->yMax = g_489720 - 1;
    header->hDpi = 200;
    header->vDpi = 200;
    memset(header->palette, 0, sizeof(header->palette));
    header->reserved = 0;
    header->planes = 1;
    header->bytesPerLine = g_48971c;
    header->paletteInfo = 1;
}

// FUNCTION: STUNTGP_D3D 0x45e820
void FUN_45e820(DWORD *src, DWORD *dst, int size)
{
    for (int i = 0; i < size * size; i += 4)
    {
        *dst++ = *src++;
    }
}

// FUNCTION: STUNTGP_D3D 0x45e850
void FUN_45e850(BYTE *dst, BYTE *src)
{
    for (int i = 0; i < 0x300; i++)
    {
        *dst++ = *++src;
        *dst++ = *++src;
        *dst++ = *++src;
        src++;
    }
}

// FUNCTION: STUNTGP_D3D 0x45ea50
void FUN_45ea50(char *path)
{
    char header[0xc0];
    if (bload(path, header, 0x80))
    {
        g_489714 = g_48971c = (header[0x43] << 8) | (BYTE)header[0x42];
        g_489718 = g_489720 = ((header[0xb] << 8) | (BYTE)header[0xa]) + 1;
    }
}

// FUNCTION: STUNTGP_D3D 0x45f8f0
void FUN_45f8f0(int track, int loop)
{
    char path[256];
    if (g_soundInitialised && g_musicVolume)
    {
        int t;
        if (track == 0 && g_62f5a8 != 0)
        {
            t = g_62f5a8;
        }
        else
        {
            t = track;
        }
        g_62e10c = t;
        if (t)
        {
            // STRING: STUNTGP_D3D 0x48a500
            sprintf(path, "%s\\Music\\%s.wav", g_SoundDirectory, g_4898fc[t]);
            if (!size_of_file(path))
            {
                g_62f5ac = 0;
                return;
            }
            DWORD flags = 0x24;
            if (loop == 1)
            {
                flags = 0x25;
            }
            FUN_45fb50(g_directSound, path, flags, 0, 0, 0, 0);
            FUN_45f7d0(0, 0);
            g_62e110 = 0;
            g_62e0fc = 0;
            g_62e104 = 0;
            FUN_45f8e0(255, 255);
            g_62f5ac = 1;
        }
    }
}

// --- sound ---


// FUNCTION: STUNTGP_D3D 0x41bdd0
void FUN_41bdd0()
{
    FUN_460dd0();
    for (int i = 0; i < 6; i++)
    {
        if (g_49a1f8[i].active == 1)
        {
            for (int j = 0; j < 4; j++)
            {
                g_49a1f8[i].unk233c[j] = 0;
                g_49a1f8[i].wheels[j].unk30 = 0;
            }
            g_49a1f8[i].unk234c = 0;
            g_49a1f8[i].unk2350 = 0;
            g_49a1f8[i].unk2354 = 0;
            g_49a1f8[i].unk2358 = 0;
            g_49a1f8[i].unk235c = 0;
            g_49a1f8[i].unk2360 = 0;
            g_49a1f8[i].unk2364 = 0;
            g_49a1f8[i].unk2368 = 0;
            g_49a1f8[i].unk236c = 0;
            g_49a1f8[i].unk2370 = 0;
            g_49a1f8[i].unk2374 = 0;
            g_49a1f8[i].unk2378 = 0;
            g_49a1f8[i].unk237c = 0;
            g_49a1f8[i].unk2380 = 0;
            g_49a1f8[i].unk2384 = 0;
            g_49a1f8[i].unk2388 = 0;
            g_49a1f8[i].unk238c = 0;
            g_49a1f8[i].unk2390 = 0;
            g_49a1f8[i].unk2394 = 0;
            g_49a1f8[i].unk2398 = 0;
            g_49a1f8[i].unk239c = 0;
            g_49a1f8[i].unk23a0 = 0;
        }
    }
}
