#include "GameUpdate.h"
#include "Game.h"
#include "GameSetup.h"

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

// GLOBAL: STUNTGP_D3D 0x5da2e4
FILE *g_5da2e4;
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
#include "game_state.h"
#include "../../random.h"
#include "../../surface.h"
#include "../../timer.h"
#include "../../vecmath.h"
#include "RenderState.h"

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

// 6 entries at 0x49a1f8, 0x7724 bytes each
// GLOBAL: STUNTGP_D3D 0x49a1f8
Car g_49a1f8[6];

// GLOBAL: STUNTGP_D3D 0x4d5bb8
Car *g_4d5bb8;

// GLOBAL: STUNTGP_D3D 0x60f2b0
DWORD g_60f2b0;

// GLOBAL: STUNTGP_D3D 0x474630
Car *g_474630 = g_49a1f8;

void FUN_41af50();
void FUN_404450();
void FUN_418830();
void FUN_41e2d0();

// --- per-tick game logic ---

void FUN_4011f0();
void FUN_401030(float x, float y);
void FUN_401d70(float *v, float scale);
DWORD Color_Lerp(DWORD from, DWORD to, int t);

// Advances the effect slots: motion under gravity, fade in and out of alpha and scale, spin, colour ramp,
// a one-shot sound and the trailing sparks.
// FUNCTION: STUNTGP_D3D 0x401770
void FUN_401770()
{
    FUN_4011f0();
    Unk496990 *e = g_496990;
    for (int n = 16; n != 0; n--, e++)
    {
        if (e->unk00 == 1)
        {
            e->sprite.x += e->unk14;
            e->sprite.y += e->unk18;
            if (e->unk18 < 10000.0f / 60.0f)
            {
                FUN_401d70(&e->unk14, e->unk24);
            }
            if (e->unk10 & 0x10)
            {
                float t = (float)e->unk28;
                if (t < e->unk58)
                {
                    e->unk60 = t * e->unk54 / e->unk58;
                }
                else
                {
                    e->unk60 = t > e->unk2c - e->unk5c ? (float)(e->unk2c - e->unk28) * e->unk54 / e->unk5c : e->unk54;
                }
            }
            else
            {
                e->unk60 = e->unk54;
            }
            if (e->unk10 & 8)
            {
                float t = (float)e->unk28;
                if (t < e->unk48)
                {
                    e->unk50 = t * e->unk44 / e->unk48;
                }
                else
                {
                    e->unk50 = t > e->unk2c - e->unk4c ? (float)(e->unk2c - e->unk28) * e->unk44 / e->unk4c : e->unk44;
                }
            }
            else
            {
                e->unk50 = e->unk44;
            }
            if (e->unk10 & 1)
            {
                float t = (float)e->unk28;
                float d;
                if (t < e->unk68)
                {
                    d = (e->unk68 - t) * e->unk64 / e->unk68;
                }
                else
                {
                    float end = e->unk2c - e->unk6c;
                    if (t > end)
                    {
                        d = (t - end) * e->unk64 / e->unk6c;
                    }
                    else
                    {
                        d = 0.0f;
                        e->unk70 = 0.0f;
                    }
                }
                e->unk70 = d + e->unk70;
                if (e->unk70 >= 360.0f)
                {
                    e->unk70 -= 360.0f;
                }
                else if (e->unk70 < 0.0f)
                {
                    e->unk70 += 360.0f;
                }
            }
            if (e->unk10 & 0x20)
            {
                float t = (float)e->unk28;
                if (t < e->unk74)
                {
                    e->sprite.color = Color_Lerp(e->unk7c, e->unk80, (int)(e->unk28 * 255 / e->unk74));
                }
                else if (t > e->unk2c - e->unk78)
                {
                    e->sprite.color = Color_Lerp(e->unk80, e->unk84,
                                                 (int)(255.0f - (e->unk2c * 255 - e->unk28 * 255) / e->unk78));
                }
                else
                {
                    e->sprite.color = e->unk80;
                }
            }
            else
            {
                e->sprite.color = e->unk7c;
            }
            if (e->unk28 == e->unk8c)
            {
                FUN_461150(e->unk88, 0, e->unk94, e->unk90, 0, 1, NULL);
            }
            if (e->unk98 == 1)
            {
                float t = (float)e->unk28;
                if (t >= e->unka4 && t < e->unk2c - e->unka8)
                {
                    e->unk9c = e->unka0 + e->unk9c;
                    if (e->unk9c > 60.0f)
                    {
                        e->unk9c = 0.0f;
                        FUN_401030(e->sprite.originX + e->sprite.x, e->sprite.y);
                    }
                }
            }
            if (++e->unk28 >= e->unk2c)
            {
                e->unk00 = 0;
            }
            e->sprite.alpha = (int)e->unk60;
            if (e->unk50 == 0.0f)
            {
                e->unk50 = 0.1f;
            }
            e->sprite.scaleX = e->unk50;
            e->sprite.scaleY = e->unk50;
            e->sprite.angle = e->unk70;
        }
    }
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
void FUN_418710(Car *car);
void FUN_4187a0();
void FUN_413490(Car *car);
void FUN_418d20(Car *car);
void FUN_418d90(Car *car);
void FUN_411880(Car *car);
void FUN_411490(Car *car);
void FUN_4127e0(CameraPath *path, Car *car);
void FUN_408640(Car *car, float *pos);
GameSlot *FUN_402590(Car *car);
extern int g_60df98;
extern Vec4 g_482688;


// Puts a car back on the track at its last checkpoint, upright and facing along the path.
// FUNCTION: STUNTGP_D3D 0x412940
void FUN_412940(Car *car)
{
    FUN_418710(car);
    FUN_4187a0();
    if (car->unk24e8 == 1)
    {
        return;
    }
    FUN_413490(car);
    car->unk763c = 0;
    FUN_4128f0(car);
    FUN_418d20(car);
    FUN_418d90(car);
    FUN_411880(car);
    FUN_411490(car);
    car->unk1f10 = 1;
    FUN_4127e0(g_renderState.unk7f8c, car);
    FUN_408640(car, &car->unk24b0.x);
    Vec4 fwd = car->unk24c0;
    Vec4 down = g_482688;
    down.x = -down.x;
    down.y = -down.y;
    down.z = -down.z;
    Vec4 side;
    side.x = fwd.y * down.z - fwd.z * down.y;
    side.y = fwd.z * down.x - fwd.x * down.z;
    side.z = fwd.x * down.y - fwd.y * down.x;
    Vec3_Normalize(&side.x);
    Matrix_Identity(car->matrix);
    *(Vec4 *)&car->matrix[0] = side;
    *(Vec4 *)&car->matrix[4] = down;
    *(Vec4 *)&car->matrix[8] = fwd;
    memcpy(car->body.mat0, car->matrix, sizeof(car->matrix));
    if (g_60df98 == 2)
    {
        car->unk7640 = 300;
    }
    car->unk7680 = 0;
    car->unk7644 = 30;
    g_4722d0 = FUN_402590(car);
    if (g_4722d0)
    {
        g_4722d0->unk1a4 = 300;
    }
    FUN_402580();
}
void FUN_4289a0(CameraPath *path, Vec4 *out, float dist, DWORD *knot);
extern CameraPath *g_571328;


// Places the car dist along the race path, facing along it, and resets it there.
// FUNCTION: STUNTGP_D3D 0x412b10
void FUN_412b10(Car *car, float dist)
{
    CameraPath *path = g_571328;
    FUN_4289a0(path, &car->unk24b0, dist, (DWORD *)&car->unk24a4);
    DWORD i = car->unk24a4;
    int pct = i * 100 / path->count;
    car->unk23ac = pct;
    car->unk23a8 = pct - 1;
    DWORD j = (i + 1) % path->count;
    car->unk23b0 = pct;
    Vec4 d;
    d.x = path->points[j].x - path->points[i].x;
    d.y = path->points[j].y - path->points[i].y;
    d.z = path->points[j].z - path->points[i].z;
    Vec3_Normalize(&d.x);
    car->unk2644 = i;
    car->unk264c = i;
    car->unk2654 = i;
    car->unk24c0 = d;
    FUN_412940(car);
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

void FUN_4436e0(Car *car);

// FUNCTION: STUNTGP_D3D 0x40d410
void FUN_40d410(Car *car)
{
    if (car->active)
    {
        FUN_4436e0(car);
        car->unk2280 = 1;
    }
}

void FUN_444c40(Car *car);
void FUN_443e10(Car *car);
void FUN_40e360(Car *sub);
void FUN_40e380(Car *sub);

// FUNCTION: STUNTGP_D3D 0x40d430
void FUN_40d430()
{
    Car *car = g_49a1f8;
    for (int i = 0; i < 6; i++, car++)
    {
        car->unk7640 = 0;
        car->unk260c = 1.0f;
        car->unk2614 = 1.0f;
        car->unk2610 = 0;
        car->unk2278 = 1;
        car->unk1f10 = 1;
        car->unk2250 = 0;
        car->unk2254 = 0;
        car->unk2258 = 0;
        car->unk225c = 0;
        car->unk2260 = 0;
        car->unk2264 = 0;
        car->unk2268 = 0;
        car->race.unk74 = 0;
        car->unk226c = 0;
        car->unk1cf4 = 0;
        for (int j = 0; j < 4; j++)
        {
            car->wheels[j].unk84 = 1.0f;
        }
        FUN_444c40(car);
        FUN_443e10(car);
        FUN_40e360(car);
        FUN_40e380(car);
    }
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

extern float g_60f2d0[31];

// FUNCTION: STUNTGP_D3D 0x4057e0
void FUN_4057e0(Car *car, float *v)
{
    *v *= (1.0f - car->unk2660) * g_60f2d0[11] + 1.0f;
}

// FUNCTION: STUNTGP_D3D 0x405800
void FUN_405800(Car *car, float *v)
{
    *v *= (1.0f - car->unk2660) * g_60f2d0[10] + 1.0f;
}

// FUNCTION: STUNTGP_D3D 0x405820
void FUN_405820(Car *car, float *v)
{
    *v *= (1.0f - car->unk2660) * g_60f2d0[9] + 1.0f;
}

// FUNCTION: STUNTGP_D3D 0x405860
void FUN_405860(Car *car, float *v)
{
    *v += (1.0f - car->unk2660) * g_60f2d0[14];
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
    if (g_612948.unk004c != 1)
    {
        g_612948.unk004c = 1;
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
    if (g_612948.unk0054 == 1)
    {
        g_60f2c0 = 1;
        FUN_40ddd0();
        if (--g_612948.unk0048 == 0 || g_612948.unk0020 == 1)
        {
            g_612948.unk004c = 0;
            g_612948.unk0054 = 0;
            g_612948.unk0048 = 0;
            FUN_441e20();
        }
    }
}

extern float *g_4d5b24;
extern InputState *g_576b6c;
int FUN_45ed60(int index);
void FUN_4240e0(int slot);
int FUN_443770();
void FUN_410780(int slot);
void FUN_410800(int slot);
void FUN_4108c0(int slot);
void FUN_410950(int slot);
void FUN_4109e0(int slot);

// FUNCTION: STUNTGP_D3D 0x410a10
void FUN_410a10(int index)
{
    int type = FUN_45ed60(index);
    if (type == 0 || type == 1)
    {
        return;
    }
    g_4d5bb8 = &g_49a1f8[g_62d580[index].unk018];
    g_576b6c = &g_62d580[index].state;
    g_4d5b24 = g_62d580[index].ffb;
    FUN_4240e0(index);
    if (g_612948.unk02a0 != 2 && g_612948.unk0004 != 1 && FUN_443770() == 2)
    {
        FUN_410780(index);
        FUN_410800(index);
        FUN_4108c0(index);
        FUN_410950(index);
        return;
    }
    FUN_4109e0(index);
}

void FUN_41e6e0(Vec4 *ring, DWORD *head, DWORD *count, Vec4 *pos, TrailParams *params);
int FUN_4215b0();
void FUN_421c30(float bounce);
extern TrailParams g_474af8;

// Moves the live effect slots, bouncing them off the scenery from race state 0x50 on, and queues each for drawing.
// FUNCTION: STUNTGP_D3D 0x415df0
void FUN_415df0()
{
    if (g_612948.unk0458)
    {
        g_612948.unk0458--;
    }
    g_612948.unk8cdc = (int)g_612948.unk8c5c;
    if (g_612948.unk0450)
    {
        Unk612da4 *p = (Unk612da4 *)g_612948.unk045c;
        for (int n = 32; n != 0; n--, p++)
        {
            if (p->life > 0)
            {
                if (--p->life <= 0)
                {
                    g_612948.unk0450--;
                }
                if (g_612948.unk0034 >= 0x50)
                {
                    g_cameraSweep.unk00 = 1.0f;
                    g_cameraSweep.unk94 = 25.0f;
                    g_cameraSweep.unk98 = 625.0f;
                    g_cameraSweep.unk90 = 1.0f;
                    g_cameraSweep.unk04 = p->pos;
                    g_cameraSweep.unk28 = p->vel;
                    g_cameraSweep.unk8c = (float)sqrt(g_cameraSweep.unk28.x * g_cameraSweep.unk28.x +
                                                      g_cameraSweep.unk28.y * g_cameraSweep.unk28.y +
                                                      g_cameraSweep.unk28.z * g_cameraSweep.unk28.z);
                    unsigned int k = 0;
                    do
                    {
                        if (FUN_4215b0() != 1)
                        {
                            break;
                        }
                        FUN_421c30(1.0f);
                    } while (k++ < 8);
                    p->pos = g_cameraSweep.unk14;
                    p->vel = g_cameraSweep.unk28;
                }
                else
                {
                    p->pos.x = p->vel.x + p->pos.x;
                    p->pos.y = p->vel.y + p->pos.y;
                    p->pos.z = p->vel.z + p->pos.z;
                }
                FUN_401d70(&p->vel.x, 1.0f);
                p->vel.x = p->unk28 * p->vel.x;
                p->vel.y = p->unk28 * p->vel.y;
                p->vel.z = p->unk28 * p->vel.z;
                if (p->unk43c)
                {
                    p->vel.x = FUN_42f1c0(3.0f) * p->unk438 + p->vel.x;
                    p->vel.y = (float)fabs(FUN_42f1c0(2.0f)) * p->unk438 + p->vel.y;
                    p->vel.z = FUN_42f1c0(3.0f) * p->unk438 + p->vel.z;
                }
                FUN_41e6e0((Vec4 *)p->unk030, (DWORD *)&p->unk430, (DWORD *)&p->unk434, &p->pos,
                           &(&g_474af8)[p->unk04]);
                *(Unk612da4 **)g_612948.unk8cdc = p;
                g_612948.unk8cdc += 4;
            }
        }
    }
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
        if (g_4d5bb8->active == 1 && !(g_4d5bb8->unk7268 && g_4d5bb8->unk7268->mode == 1))
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
            if (g_4d5bb8->unk7268 && g_4d5bb8->unk7268->mode == 1)
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

extern int g_474670;

// FUNCTION: STUNTGP_D3D 0x418b10
void FUN_418b10()
{
    char **textures = g_636418[3].scene->textures;
    int i = 0;
    g_474670 = -1;
    while (*textures)
    {
        char *name = *textures;
        while (*name != '\\')
        {
            name++;
        }
        // STRING: STUNTGP_D3D 0x474674
        if (!_strcmpi(name + 1, "Trk_TubeGlass"))
        {
            g_474670 = i;
        }
        textures++;
        i++;
    }
}

// GLOBAL: STUNTGP_D3D 0x4d5ca8
int g_4d5ca8;

// GLOBAL: STUNTGP_D3D 0x4d5cac
int g_4d5cac;

GameSlot *FUN_402590(Car *car);
void FUN_4614a0(int channel, int loop, DWORD frequency, DWORD volume, Vec4 *pos, Vec4 *velocity, int keep,
                int *slotIndex);

// Crowd: a cheer when g_4d5ca8 runs out and a random murmur every 30 ticks, halfway between car and camera.
// FUNCTION: STUNTGP_D3D 0x418bd0
void FUN_418bd0()
{
    if (g_4d5bb8->unk7648 == 1)
    {
        Vec4 pos;
        g_4722d0 = FUN_402590(g_4d5bb8);
        if (g_4722d0)
        {
            pos.x = g_4d5bb8->posX - g_4722d0->cam.pos.x;
            pos.y = g_4d5bb8->posY - g_4722d0->cam.pos.y;
            pos.z = g_4d5bb8->posZ - g_4722d0->cam.pos.z;
            pos.x *= 0.5f;
            pos.y *= 0.5f;
            pos.z *= 0.5f;
            pos.x += g_4722d0->cam.pos.x;
            pos.y += g_4722d0->cam.pos.y;
            pos.z += g_4722d0->cam.pos.z;
        }
        else
        {
            pos = *(Vec4 *)&g_4d5bb8->posX;
        }
        FUN_402580();
        if (g_4d5ca8 && --g_4d5ca8 == 0)
        {
            FUN_4614a0(0x27, 0, 0, 0xff, &pos, NULL, 1, NULL);
            g_4d5ca8 = 30;
        }
        if (--g_4d5cac <= 0)
        {
            g_4d5cac = 30;
            int n = FUN_42f1f0(0x3ff) & 3;
            n += 0x28;
            FUN_4614a0(n, 0, 0, 0xaa, &pos, NULL, 1, NULL);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x418d10
void FUN_418d10()
{
    g_4d5ca8 = g_4d5cac = 0;
}

// GLOBAL: STUNTGP_D3D 0x4d5ca4
int g_4d5ca4;

extern float g_60f010;
void FUN_447aa0(Fader *fader);

// FUNCTION: STUNTGP_D3D 0x418d20
void FUN_418d20(Car *car)
{
    int t = car->unk7674;
    if (t)
    {
        car->unk24a4 = t - (int)(5000.0f / (g_60f010 / (float)g_renderState.unk7f8c[1].count));
        if (g_4d5ca4 == 1)
        {
            FUN_447aa0(&g_498248[0].fx.faders[6]);
            g_4d5ca4 = 0;
        }
    }
}

GameSlot *FUN_402590(Car *car);
void FUN_419180();

// FUNCTION: STUNTGP_D3D 0x418d90
void FUN_418d90(Car *car)
{
    Car *saved = g_4d5bb8;
    car->unk26a8 = 1;
    g_4d5bb8 = car;
    if (car->unk7648 == 1)
    {
        car->unk7674 = 0;
        car->unk7648 = 0;
        car->unk2278 = car->unk7654;
        g_4722d0 = FUN_402590(car);
        if (g_4722d0 && g_4722d0->camMode != g_4d5bb8->unk22c8)
        {
            FUN_4028d0(g_4d5bb8->unk22c8);
        }
        FUN_402580();
        FUN_419180();
        FUN_418d10();
    }
    g_4d5bb8 = saved;
}
// Walks the segment index along the path until p projects inside the segment.
// FUNCTION: STUNTGP_D3D 0x418e10
void FUN_418e10(Vec4 *p, CameraPath *path, int *index)
{
    Vec4 *pts = path->points;
    int i = *index;
    int step = 0;
    unsigned int a;
    Vec4 d;
    float t;
    for (;;)
    {
        if (i < 0)
        {
            a = path->count - (unsigned int)-i % path->count;
        }
        else
        {
            a = (unsigned int)i % path->count;
        }
        unsigned int b = (a + 1) % path->count;
        d.x = pts[b].x - pts[a].x;
        d.y = pts[b].y - pts[a].y;
        d.z = pts[b].z - pts[a].z;
        float len;
        FUN_44eda0(&d.x, &len);
        Vec4 q;
        q.x = p->x - pts[a].x;
        q.y = p->y - pts[a].y;
        q.z = p->z - pts[a].z;
        t = q.x * d.x + q.y * d.y + q.z * d.z;
        if (t < 0.0f)
        {
            if (step > 0)
            {
                break;
            }
            i--;
            step = -1;
        }
        else
        {
            if (t < len || step < 0)
            {
                break;
            }
            i++;
            step = 1;
        }
    }
    *index = i;
    d.x = t * d.x;
    d.y = t * d.y;
    d.z = t * d.z;
    g_4d5bb8->unk7664.x = d.x + pts[a].x;
    g_4d5bb8->unk7664.y = d.y + pts[a].y;
    g_4d5bb8->unk7664.z = d.z + pts[a].z;
    g_4d5bb8->unk7650 = i * 100 / path->count;
}


// GLOBAL: STUNTGP_D3D 0x570ac0
Replay *g_570ac0;

// GLOBAL: STUNTGP_D3D 0x570ac4
ReplayFrame *g_570ac4;

// GLOBAL: STUNTGP_D3D 0x4d5cb8
ReplayFrame *g_4d5cb8;

// Car basis from the replay, interpolated between the previous and current frame.
// FUNCTION: STUNTGP_D3D 0x41a000
void FUN_41a000()
{
    Vec4 py;
    py.x = g_4d5cb8->axisY[0] * (1.0f / 127.0f);
    py.y = g_4d5cb8->axisY[1] * (1.0f / 127.0f);
    py.z = g_4d5cb8->axisY[2] * (1.0f / 127.0f);
    Vec4 pz;
    pz.x = g_4d5cb8->axisZ[0] * (1.0f / 127.0f);
    pz.y = g_4d5cb8->axisZ[1] * (1.0f / 127.0f);
    pz.z = g_4d5cb8->axisZ[2] * (1.0f / 127.0f);
    Vec4 cy;
    cy.x = g_570ac4->axisY[0] * (1.0f / 127.0f);
    cy.y = g_570ac4->axisY[1] * (1.0f / 127.0f);
    cy.z = g_570ac4->axisY[2] * (1.0f / 127.0f);
    Vec4 cz;
    cz.x = g_570ac4->axisZ[0] * (1.0f / 127.0f);
    cz.y = g_570ac4->axisZ[1] * (1.0f / 127.0f);
    cz.z = g_570ac4->axisZ[2] * (1.0f / 127.0f);
    Vec4 d;
    d.x = cy.x - py.x;
    d.y = cy.y - py.y;
    d.z = cy.z - py.z;
    d.x *= g_570ac0->unk08;
    float ty = g_570ac0->unk08;
    d.y = ty * d.y;
    float tz = g_570ac0->unk08;
    d.z = tz * d.z;
    Vec4 y;
    y.x = d.x + py.x;
    y.y = d.y + py.y;
    y.z = d.z + py.z;
    d.x = cz.x - pz.x;
    d.y = cz.y - pz.y;
    d.z = cz.z - pz.z;
    d.x *= g_570ac0->unk08;
    ty = g_570ac0->unk08;
    d.y = ty * d.y;
    tz = g_570ac0->unk08;
    d.z = tz * d.z;
    Vec4 z;
    z.x = d.x + pz.x;
    z.y = d.y + pz.y;
    z.z = d.z + pz.z;
    Vec3_Normalize(&y.x);
    Vec3_Normalize(&z.x);
    Vec4 x;
    x.x = z.y * y.z - z.z * y.y;
    x.y = z.z * y.x - z.x * y.z;
    x.z = z.x * y.y - z.y * y.x;
    Vec3_Normalize(&x.x);
    g_4d5bb8->axisX = x;
    g_4d5bb8->axisY = y;
    g_4d5bb8->axisZ = z;
}

// FUNCTION: STUNTGP_D3D 0x41a230
void FUN_41a230()
{
    for (int i = 0; i < 4; i++)
    {
        int prev = g_4d5cb8->wheelAngle[i];
        float old = g_4d5bb8->wheels[i].unk94;
        g_4d5bb8->wheels[i].unk94 = (g_570ac4->wheelAngle[i] - prev) * g_570ac0->unk08 + prev;
        float d = g_4d5bb8->wheels[i].unk94 - old;
        float spin = d < 0.0f ? -fmod(-d, 360.0) : fmod(d, 360.0);
        spin = spin * g_4d5bb8->unkcb8[i].x * -0.017453294f;
        g_4d5bb8->wheels[i].unk00 = (spin - g_4d5bb8->wheels[i].unk04) * 1.5f;
        g_4d5bb8->wheels[i].unk04 = spin;
        Matrix_RotationX(g_4d5bb8->wheelMatrix[i], g_4d5bb8->wheels[i].unk94);
    }
}

// FUNCTION: STUNTGP_D3D 0x41a330
void FUN_41a330()
{
    g_4d5bb8->unk1cf4 = (g_570ac4->unk22 - g_4d5cb8->unk22) * g_570ac0->unk08 + g_4d5cb8->unk22;
}

// FUNCTION: STUNTGP_D3D 0x41a370
void FUN_41a370()
{
    g_4d5bb8->unk1cfc = (g_570ac4->unk20 - g_4d5cb8->unk20) * g_570ac0->unk08 + g_4d5cb8->unk20;
}

// FUNCTION: STUNTGP_D3D 0x41a3c0
void FUN_41a3c0()
{
    for (unsigned int i = 0; i < 4; i++)
    {
        float prev = g_4d5cb8->unk1c[i] * 0.5f;
        g_4d5bb8->unk2240[i] = (g_570ac4->unk1c[i] * 0.5f - prev) * g_570ac0->unk08 + prev;
    }
}

extern float g_482670;

// FUNCTION: STUNTGP_D3D 0x41a430
void FUN_41a430()
{
    Car *car = g_4d5bb8;
    BYTE flag = g_570ac4->flags & 0x20;
    for (int i = 0; i < 4; i++)
    {
        float prev = g_4d5cb8->unk14[i] * 0.5f;
        car->wheels[i].unk80 = car->wheels[i].unk0c = (g_570ac4->unk14[i] * 0.5f - prev) * g_570ac0->unk08 + prev;
        if (flag)
        {
            car->wheels[i].unk80 = g_482670 * g_4d5bb8->unk2618 * 3.5f;
        }
    }
}

void FUN_408640(Car *car, float *pos);

// FUNCTION: STUNTGP_D3D 0x41a4c0
void FUN_41a4c0()
{
    Car *car = g_4d5bb8;
    Vec4 pos;
    pos.x = g_570ac4->pos[0];
    pos.y = g_570ac4->pos[1];
    pos.z = g_570ac4->pos[2];
    car->unk1c9c = car->unk1c8c;
    car->unk1c8c.x = pos.x - car->posX;
    car->unk1c8c.y = pos.y - car->posY;
    car->unk1c8c.z = pos.z - car->posZ;
    car->unk1cf0 = car->axisZ.y * car->unk1c8c.y + car->axisZ.x * car->unk1c8c.x + car->axisZ.z * car->unk1c8c.z;
    FUN_408640(car, &pos.x);
}

void FUN_40c160();

// Replay playback: rebuilds the car's orientation from the packed axes of the frame.
// FUNCTION: STUNTGP_D3D 0x41a570
void FUN_41a570()
{
    Vec4 x;
    Vec4 z;
    Vec4 y;
    y.x = g_570ac4->axisY[0] * 0.007874016f;
    y.y = g_570ac4->axisY[1] * 0.007874016f;
    y.z = g_570ac4->axisY[2] * 0.007874016f;
    z.x = g_570ac4->axisZ[0] * 0.007874016f;
    z.y = g_570ac4->axisZ[1] * 0.007874016f;
    z.z = g_570ac4->axisZ[2] * 0.007874016f;
    x.x = z.y * y.z - z.z * y.y;
    x.y = z.z * y.x - z.x * y.z;
    x.z = z.x * y.y - z.y * y.x;
    Vec3_Normalize(&x.x);
    Vec3_Normalize(&y.x);
    Vec3_Normalize(&z.x);
    g_4d5bb8->axisX = x;
    g_4d5bb8->axisY = y;
    g_4d5bb8->axisZ = z;
}

// FUNCTION: STUNTGP_D3D 0x41a6a0
void FUN_41a6a0()
{
    for (int i = 0; i < 4; i++)
    {
        float angle = g_570ac4->wheelAngle[i];
        float d = angle - g_4d5bb8->wheels[i].unk94;
        float spin = d < 0.0f ? -fmod(-d, 360.0) : fmod(d, 360.0);
        spin = spin * g_4d5bb8->unkcb8[i].x * -0.017453294f;
        g_4d5bb8->wheels[i].unk00 = (spin - g_4d5bb8->wheels[i].unk04) * 1.5f;
        g_4d5bb8->wheels[i].unk04 = spin;
        g_4d5bb8->wheels[i].unk94 = angle;
        Matrix_RotationX(g_4d5bb8->wheelMatrix[i], angle);
    }
}

// FUNCTION: STUNTGP_D3D 0x41a780
void FUN_41a780()
{
    g_4d5bb8->unk1cf4 = g_570ac4->unk22;
}

// FUNCTION: STUNTGP_D3D 0x41a7b0
void FUN_41a7b0()
{
    g_4d5bb8->unk1cfc = g_570ac4->unk20;
}

// FUNCTION: STUNTGP_D3D 0x41a7e0
void FUN_41a7e0()
{
    int value = g_570ac4->unk23;
    if (value != g_4d5bb8->unk1f10)
    {
        g_4d5bb8->unk23a0 = 1;
        FUN_40c160();
    }
    g_4d5bb8->unk1f10 = value;
}

// FUNCTION: STUNTGP_D3D 0x41a820
void FUN_41a820()
{
    for (unsigned int i = 0; i < 4; i++)
    {
        g_4d5bb8->unk2240[i] = g_570ac4->unk1c[i] * 0.5f;
    }
}

extern float g_482670;

// FUNCTION: STUNTGP_D3D 0x41a860
void FUN_41a860()
{
    Car *car = g_4d5bb8;
    BYTE flag = g_570ac4->flags & 0x20;
    for (int i = 0; i < 4; i++)
    {
        car->wheels[i].unk80 = car->wheels[i].unk0c = g_570ac4->unk14[i] * 0.5f;
        if (flag)
        {
            car->wheels[i].unk80 = g_482670 * car->unk2618 * 3.5f;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x41a8d0
void FUN_41a8d0()
{
    if (g_570ac4->flags & 2)
    {
        g_4d5bb8->unk2250 = 1;
    }
    else
    {
        g_4d5bb8->unk2250 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x41a900
void FUN_41a900()
{
    g_4d5bb8->unk22b8 = g_4d5bb8->unk22c0;
    g_4d5bb8->unk22c0 = (g_570ac4->flags >> 3) & 1;
}

// FUNCTION: STUNTGP_D3D 0x41a930
void FUN_41a930()
{
    Car *car = g_4d5bb8;
    car->unk22b4 = car->unk22bc;
    int boost = (g_570ac4->flags >> 2) & 1;
    car->unk22bc = boost;
    if (boost == 1)
    {
        car->unk1cf8 += 0.15f;
        if (car->unk1cf8 > 1.0f)
        {
            car->unk1cf8 = 1.0f;
        }
    }
    else if (car->unk71ec)
    {
        car->unk1cf8 *= 0.5f;
    }
}

// FUNCTION: STUNTGP_D3D 0x41a9b0
void FUN_41a9b0()
{
    if (g_570ac4->flags & 0x10)
    {
        g_4d5bb8->controls[9] = 1;
    }
    else
    {
        g_4d5bb8->controls[9] = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x41a9e0
void FUN_41a9e0()
{
    unsigned int value = g_570ac4->unk25;
    if (value)
    {
        if (value & 0x80)
        {
            g_4d5bb8->unk2364 = value & 0x7f;
            g_4d5bb8->unk2368 = 16;
        }
        else
        {
            g_4d5bb8->unk2360 = value;
            if (g_4d5bb8->unk2360 != 0.0f)
            {
                g_4d5bb8->unk236c = 16;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x41aa60
void FUN_41aa60()
{
    int surface;
    switch (g_570ac4->flags & 0xc0)
    {
    case 0x40:
        surface = 2;
        break;
    case 0x80:
        surface = 3;
        break;
    case 0xc0:
        surface = 4;
        break;
    default:
        surface = 1;
        break;
    }
    for (int i = 0; i < 4; i++)
    {
        g_4d5bb8->wheels[i].unk74 = g_4d5bb8->wheels[i].unk78;
        g_4d5bb8->wheels[i].unk78 = surface;
    }
}

// FUNCTION: STUNTGP_D3D 0x41aac0
void FUN_41aac0(Replay *replay)
{
    if (replay->mode)
    {
        if (replay->mode == 2)
        {
            replay->count = replay->cur - replay->frames;
        }
        replay->mode = 0;
    }
}

void FUN_414d80(Car *car);
void FUN_414c50(Car *car);
void FUN_414ef0(Car *car);
void FUN_4152c0(Car *car);

// FUNCTION: STUNTGP_D3D 0x41ab00
void FUN_41ab00(Car *car, Replay *replay)
{
    replay->mode = 1;
    car->unk7268 = replay;
    replay->cur = replay->frames;
    replay->unk08 = 0;
    FUN_414d80(car);
    FUN_414c50(car);
    FUN_414ef0(car);
    FUN_4152c0(car);
}

// FUNCTION: STUNTGP_D3D 0x41ab40
void FUN_41ab40(Car *car, Replay *replay)
{
    car->unk7268 = replay;
    replay->cur = replay->frames;
    replay->mode = 2;
    replay->unk04 = 20;
    replay->unk08 = 0;
    replay->unk0c = 0.33333334f;
    replay->unk06 = 0;
    replay->count = 0;
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
        switch (g_4d5bb8->unk7268->mode)
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
            events->order = g_612948.unk03b4;
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
    memset(g_612948.unk03cc, 0, sizeof(g_612948.unk03cc));
    unsigned int count = 0;
    for (i = 0; i < 6; i++)
    {
        if (g_49a1f8[i].active == 1)
        {
            g_612948.unk03cc[count] = &g_49a1f8[i];
            count++;
        }
    }
    g_612948.unk03c8 = count;
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            if (g_612948.unk03cc[i]->unk23b0 > g_612948.unk03cc[j]->unk23b0)
            {
                Car *t = g_612948.unk03cc[j];
                g_612948.unk03cc[j] = g_612948.unk03cc[i];
                g_612948.unk03cc[i] = t;
            }
        }
    }
    for (i = 0; i < count; i++)
    {
        if (i == 0 && g_612948.unk03cc[0]->unk24ac)
        {
            int index = g_612948.unk03cc[0] - g_49a1f8;
            // STRING: STUNTGP_D3D 0x474924
            sprintf(text, "%s %s", g_60f02c[index].name, g_6127a0[24]);
            FUN_442cf0(180, text, &g_49a1f8[index], 1, 100);
        }
        g_612948.unk03cc[i]->unk24ac = i;
    }
}


// Projects a world point to the screen; fails when it is in front of the near plane.
// FUNCTION: STUNTGP_D3D 0x41e410
int FUN_41e410(Vec4 *p, float *out)
{
    Vec4 t;
    t.x = g_renderState.unkac[0] * p->x + p->z * g_renderState.unkac[8] + p->y * g_renderState.unkac[4] + g_renderState.unkac[12];
    t.y = g_renderState.unkac[1] * p->x + p->z * g_renderState.unkac[9] + p->y * g_renderState.unkac[5] + g_renderState.unkac[13];
    t.z = g_renderState.unkac[2] * p->x + p->z * g_renderState.unkac[10] + p->y * g_renderState.unkac[6] + g_renderState.unkac[14];
    if (t.z < g_4722d0->nearZ)
    {
        return 0;
    }
    Vec4 s;
    s.x = t.x * g_61c3e8[0];
    s.y = g_61c3e8[5] * t.y;
    float inv = 1.0f / (t.z + 1.0f);
    s.x = g_576b9c * inv * s.x + g_576b94;
    s.y = g_576ba0 * inv * s.y + g_576b98;
    out[0] = s.x;
    out[1] = s.y;
    out[2] = inv * 32.0f;
    return 1;
}

// Pushes a position into a trail ring; slot size mirrors the newest point.
// FUNCTION: STUNTGP_D3D 0x41e6e0
void FUN_41e6e0(Vec4 *ring, DWORD *head, DWORD *count, Vec4 *pos, TrailParams *params)
{
    if (*count < params->size)
    {
        (*count)++;
    }
    *head = (*head + 1) % params->size;
    ring[params->size] = *pos;
    ring[*head] = *pos;
    if (!params->unk10)
    {
        FUN_41e410(pos, &ring[*head].x);
    }
}

// Trail polygon handed to the dynamic mesh.
// GLOBAL: STUNTGP_D3D 0x571330
MeshPoly g_571330;

void FUN_4342e0(MeshPoly *poly);

// Two tube segments between ring points a and b: the cross-section, scaled by sa and sb and turned by the car
// matrix, joins its corners 0-1 and 2-3.
// FUNCTION: STUNTGP_D3D 0x41e760
void FUN_41e760(TrailParams *params, Vec4 *a, float sb, float sa, Vec4 *b, int idx)
{
    Vec4 outB[4];
    Vec4 outA[4];
    Car *car = g_4d5bb8;
    for (int i = 0; i < 4; i++)
    {
        Vec4 *s = &params->unk10[i];
        float x = sa * s->x;
        float y = sa * s->y;
        float z = sa * s->z;
        Vec4 t;
        t.x = x * car->matrix[0] + z * car->matrix[8] + y * car->matrix[4];
        t.y = z * car->matrix[9] + y * car->matrix[5] + x * car->matrix[1];
        t.z = x * car->matrix[2] + z * car->matrix[10] + y * car->matrix[6];
        outA[i].x = t.x + a->x;
        outA[i].y = t.y + a->y;
        outA[i].z = t.z + a->z;
        x = sb * s->x;
        y = sb * s->y;
        z = sb * s->z;
        t.x = x * car->matrix[0] + z * car->matrix[8] + y * car->matrix[4];
        t.y = z * car->matrix[9] + y * car->matrix[5] + x * car->matrix[1];
        t.z = x * car->matrix[2] + z * car->matrix[10] + y * car->matrix[6];
        outB[i].x = t.x + b->x;
        outB[i].y = t.y + b->y;
        outB[i].z = t.z + b->z;
    }
    g_571330.v[0].color = params->colors[idx];
    g_571330.v[1].color = g_571330.v[0].color;
    g_571330.v[2].color = params->colors[idx + 1];
    g_571330.v[3].color = g_571330.v[2].color;
    g_571330.v[0].pos = outA[0];
    g_571330.v[1].pos = outA[1];
    g_571330.v[2].pos = outB[1];
    g_571330.v[3].pos = outB[0];
    FUN_4342e0(&g_571330);
    g_571330.v[0].pos = outA[2];
    g_571330.v[1].pos = outA[3];
    g_571330.v[2].pos = outB[3];
    g_571330.v[3].pos = outB[2];
    FUN_4342e0(&g_571330);
}

// Four tube segments between ring points a and b, joining every pair of neighbouring cross-section corners.
// FUNCTION: STUNTGP_D3D 0x41ea20
void FUN_41ea20(TrailParams *params, Vec4 *a, float sb, float sa, Vec4 *b, int idx)
{
    Vec4 outA[4];
    Vec4 outB[4];
    Car *car = g_4d5bb8;
    for (int i = 0; i < 4; i++)
    {
        Vec4 *s = &params->unk10[i];
        float x = sa * s->x;
        float y = sa * s->y;
        float z = sa * s->z;
        Vec4 t;
        t.x = x * car->matrix[0] + z * car->matrix[8] + y * car->matrix[4];
        t.y = z * car->matrix[9] + y * car->matrix[5] + x * car->matrix[1];
        t.z = x * car->matrix[2] + z * car->matrix[10] + y * car->matrix[6];
        outA[i].x = t.x + a->x;
        outA[i].y = t.y + a->y;
        outA[i].z = t.z + a->z;
        x = sb * s->x;
        y = sb * s->y;
        z = sb * s->z;
        t.x = x * car->matrix[0] + z * car->matrix[8] + y * car->matrix[4];
        t.y = z * car->matrix[9] + y * car->matrix[5] + x * car->matrix[1];
        t.z = x * car->matrix[2] + z * car->matrix[10] + y * car->matrix[6];
        outB[i].x = t.x + b->x;
        outB[i].y = t.y + b->y;
        outB[i].z = t.z + b->z;
    }
    g_571330.v[0].color = params->colors[idx];
    g_571330.v[1].color = g_571330.v[0].color;
    g_571330.v[2].color = params->colors[idx + 1];
    g_571330.v[3].color = g_571330.v[2].color;
    g_571330.v[0].pos = outA[1];
    g_571330.v[1].pos = outA[2];
    g_571330.v[2].pos = outB[2];
    g_571330.v[3].pos = outB[1];
    FUN_4342e0(&g_571330);
    g_571330.v[0].pos = outA[0];
    g_571330.v[1].pos = outA[3];
    g_571330.v[2].pos = outB[3];
    g_571330.v[3].pos = outB[0];
    FUN_4342e0(&g_571330);
    g_571330.v[0].pos = outA[0];
    g_571330.v[1].pos = outA[1];
    g_571330.v[2].pos = outB[1];
    g_571330.v[3].pos = outB[0];
    FUN_4342e0(&g_571330);
    g_571330.v[0].pos = outA[3];
    g_571330.v[1].pos = outA[2];
    g_571330.v[2].pos = outB[2];
    g_571330.v[3].pos = outB[3];
    FUN_4342e0(&g_571330);
}

void FUN_425830(OverlayPoly *src);

// Draws the trail's head sprite as a screen-space quad scaled by depth; p is a projected point.
// FUNCTION: STUNTGP_D3D 0x41ee10
void FUN_41ee10(TrailParams *params, Vec4 *p, float scale, int unused)
{
    if (p->z >= 0.0f && p->z <= 1.0f)
    {
        OverlayPoly poly;
        float dx = scale * params->unk100 * p->z * 100.0f;
        float dy = scale * params->unk104 * p->z * 100.0f;
        poly.numVerts = 4;
        poly.flags = params->unkf0;
        poly.alpha = params->unkf8;
        poly.texture = params->unkf4;
        poly.verts[0].x = p->x - dx;
        poly.verts[0].y = p->y - dy;
        poly.verts[0].z = p->z;
        poly.verts[0].u = 0.0f;
        poly.verts[0].v = 0.0f;
        poly.verts[0].color = params->unkfc;
        poly.verts[1].x = dx + p->x;
        poly.verts[1].y = p->y - dy;
        poly.verts[1].z = p->z;
        poly.verts[1].u = 1.0f;
        poly.verts[1].v = 0.0f;
        poly.verts[1].color = params->unkfc;
        poly.verts[2].x = dx + p->x;
        poly.verts[2].y = dy + p->y;
        poly.verts[2].z = p->z;
        poly.verts[2].u = 1.0f;
        poly.verts[2].v = 1.0f;
        poly.verts[2].color = params->unkfc;
        poly.verts[3].x = p->x - dx;
        poly.verts[3].y = dy + p->y;
        poly.verts[3].z = p->z;
        poly.verts[3].u = 0.0f;
        poly.verts[3].v = 1.0f;
        poly.verts[3].color = params->unkfc;
        FUN_425830(&poly);
    }
}

// Flat trail: a screen-space ribbon of quads back along the projected ring from head, one per unk08 points.
// FUNCTION: STUNTGP_D3D 0x41ef90
void FUN_41ef90(TrailParams *params, Vec4 *ring, int head, unsigned int count, float scale, float fade)
{
    if (params->unkec == 1)
    {
        FUN_41ee10(params, &ring[head], scale, *(int *)&fade);
    }
    OverlayPoly poly;
    poly.flags = params->unk14;
    poly.texture = params->unk18;
    Vec4 cur = ring[head];
    unsigned int k = 0;
    poly.numVerts = 4;
    Vec4 prev;
    Vec4 l;
    Vec4 r;
    Vec4 dir;
    float len;
    float half;
    float w = scale * params->widths[0];
    for (unsigned int i = 0; i < params->unk0c; i++)
    {
        float next = scale * params->widths[i + 1];
        poly.alpha = (DWORD)(fade * params->alphas[i]);
        k += params->unk08;
        if (k >= count)
        {
            break;
        }
        head -= params->unk08;
        if (head < 0)
        {
            head += params->size;
        }
        prev = cur;
        cur = ring[head];
        if (i == 0)
        {
            half = cur.z * w * 100.0f;
            dir.z = 0.0f;
            dir.x = cur.x - prev.x;
            dir.y = cur.y - prev.y;
            FUN_44eda0(&dir.x, &len);
            len = dir.x;
            dir.x = dir.y;
            dir.y = -len;
            dir.x *= half;
            dir.y *= half;
            l.x = prev.x - dir.x;
            l.y = prev.y - dir.y;
            l.z = prev.z;
            r.x = dir.x + prev.x;
            r.y = dir.y + prev.y;
            r.z = prev.z;
        }
        half = cur.z * next * 100.0f;
        dir.z = 0.0f;
        dir.x = cur.x - prev.x;
        dir.y = cur.y - prev.y;
        FUN_44eda0(&dir.x, &len);
        len = dir.x;
        dir.x = dir.y;
        dir.y = -len;
        dir.x *= half;
        dir.y *= half;
        dir.z *= half;
        poly.verts[0].x = l.x;
        poly.verts[0].y = l.y;
        poly.verts[0].z = l.z;
        poly.verts[0].unk0c = l.w;
        poly.verts[0].u = params->u0;
        poly.verts[0].v = params->v0;
        poly.verts[0].color = params->colors[i];
        poly.verts[3].x = r.x;
        poly.verts[3].y = r.y;
        poly.verts[3].z = r.z;
        poly.verts[3].unk0c = r.w;
        poly.verts[3].u = params->u0;
        poly.verts[3].v = params->v1;
        poly.verts[3].color = params->colors[i];
        l.x = cur.x - dir.x;
        l.y = cur.y - dir.y;
        l.z = cur.z;
        r.x = dir.x + cur.x;
        r.y = dir.y + cur.y;
        r.z = cur.z;
        poly.verts[1].x = l.x;
        poly.verts[1].y = l.y;
        poly.verts[1].z = l.z;
        poly.verts[1].unk0c = l.w;
        poly.verts[1].u = params->u1;
        poly.verts[1].v = params->v0;
        poly.verts[1].color = params->colors[i + 1];
        poly.verts[2].x = r.x;
        poly.verts[2].y = r.y;
        poly.verts[2].z = r.z;
        poly.verts[2].unk0c = r.w;
        poly.verts[2].u = params->u1;
        poly.verts[2].v = params->v1;
        poly.verts[2].color = params->colors[i + 1];
        FUN_425830(&poly);
        w = next;
    }
}

void FUN_4343f0(MeshPoly *poly);

// Draws a trail back from ring[head]: the optional head sprite, then a flat ribbon or a tube of unk08-point
// segments, scale widening it and fade scaling its alpha.
// FUNCTION: STUNTGP_D3D 0x41f2f0
void FUN_41f2f0(TrailParams *params, Vec4 *ring, int head, unsigned int count, float scale, float fade)
{
    int first = 1;
    if (params->unkec == first && params->unk108 != 0.0f)
    {
        float *size = (float *)(g_571330.unk00 + 0x10);
        size[0] = scale * params->unk100;
        g_571330.v[0].color = params->unkfc;
        g_571330.v[1].color = params->unkfc;
        g_571330.v[2].color = params->unkfc;
        g_571330.v[3].color = params->unkfc;
        size[1] = scale * params->unk104;
        *(Vec4 *)g_571330.unk00 = ring[params->size];
        size[2] = scale * params->unk108;
        g_571330.unk28 = (DWORD)(fade * params->unkf8);
        g_571330.unk20 = params->unkf4;
        g_571330.unk24 = params->unkf0;
        FUN_4343f0(&g_571330);
    }
    if (g_576be0 == 0)
    {
        if (!params->unk10)
        {
            FUN_41ef90(params, ring, head, count, scale, fade);
            return;
        }
        g_571330.unk20 = params->unk18;
        g_571330.unk24 = params->unk14;
        g_571330.count = 4;
        float w = scale * params->widths[0];
        int h = head;
        if (count > 1)
        {
            unsigned int n;
            if (count <= params->unk08)
            {
                n = 1;
            }
            else if (count < params->size)
            {
                n = count / params->unk08 + 1;
            }
            else
            {
                n = count / params->unk08;
            }
            Vec4 *b = &ring[head];
            for (int i = 0; i < (int)n; i++)
            {
                float prevW = w;
                w = scale * params->widths[i + 1];
                g_571330.unk28 = (DWORD)(fade * params->alphas[i]);
                h -= params->unk08;
                int idx = h;
                if (count < params->size)
                {
                    if (h < 1)
                    {
                        idx = 1;
                    }
                }
                else if (h < 0)
                {
                    idx = params->size + h;
                }
                Vec4 *a = b;
                b = &ring[idx];
                switch (params->unk00)
                {
                case 0:
                    if (first == 1)
                    {
                    g_571330.v[0].v = params->v0;
                    first = 0;
                    g_571330.v[0].u = params->u0;
                    g_571330.v[1].u = params->u1;
                    g_571330.v[1].v = params->v0;
                    g_571330.v[2].u = params->u1;
                    g_571330.v[2].v = params->v1;
                    g_571330.v[3].u = params->u0;
                    g_571330.v[3].v = params->v1;
                    }
                    FUN_41e760(params, a, w, prevW, b, i);
                    break;
                case 1:
                    if (first == 1)
                    {
                    g_571330.v[0].u = params->u0;
                    first = 0;
                    g_571330.v[0].v = params->v0;
                    g_571330.v[1].u = params->u1;
                    g_571330.v[1].v = params->v0;
                    g_571330.v[2].u = params->u1;
                    g_571330.v[2].v = params->v1;
                    g_571330.v[3].u = params->u0;
                    g_571330.v[3].v = params->v1;
                    }
                    FUN_41ea20(params, a, w, prevW, b, i);
                    break;
                }
            }
        }
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

// GLOBAL: STUNTGP_D3D 0x577a90
float g_577a90[16];

void FUN_44fbd0(Scene *scene, ObjectDef *obj, float *m);

// Clips the eight corners of an object's bounding box (point indices from box[1]) against the
// view volume: 0 outside, 1 partly visible, 2 inside.
// FUNCTION: STUNTGP_D3D 0x427b40
int FUN_427b40(Scene *scene, ObjectDef *obj, WORD *box)
{
    float *m = g_577a90;
    FUN_44fbd0(scene, obj, m);
    Vec4 **corner = (Vec4 **)&scene->unk40[box[1]];
    DWORD any = 0;
    DWORD all = 0x3f;
    for (DWORD i = 0; i < 8; corner++, i++)
    {
        Vec4 *p = *corner;
        DWORD code = 0x3f;
        float w = m[2] * p->x + (p->y * m[6] + p->z * m[10]) + m[14];
        float x = (m[0] * p->x + (p->y * m[4] + p->z * m[8]) + m[12]) * g_61c3e8[0];
        float y = (m[1] * p->x + (p->y * m[5] + p->z * m[9]) + m[13]) * g_61c3e8[5];
        float z = g_61c3e8[10] * w + g_61c3e8[14];
        if (z <= g_4722d0->nearZ)
        {
            code = 0x3e;
        }
        if (z >= g_4722d0->unk19c)
        {
            code &= ~2;
        }
        float nw = -w;
        if (x <= nw)
        {
            code &= ~4;
        }
        if (x >= w)
        {
            code &= ~8;
        }
        if (y <= nw)
        {
            code &= ~0x10;
        }
        if (y >= w)
        {
            code &= ~0x20;
        }
        if (code == 0x3f && all != 0x3f)
        {
            return 2;
        }
        any |= code;
        all &= code;
    }
    if (all == 0x3f)
    {
        return 0;
    }
    return (any == 0x3f) + 1;
}

// Tests an object's bounding sphere (radius box[0], centre point index box[1]) against the
// view frustum: 1 outside, 2 partly visible, 0 inside. index -1 tests the whole scene.
// FUNCTION: STUNTGP_D3D 0x427cc0
int FUN_427cc0(Scene *scene, ObjectDef *obj, int index, WORD *box)
{
    Vec4 *c = (Vec4 *)scene->unk40[box[1]];
    Camera *cam = scene->camera;
    Vec4 d;
    if (index != -1)
    {
        float nx = -obj->unk10.x;
        float ny = -obj->unk10.y;
        float nz = -obj->unk10.z;
        Camera *oc = (Camera *)obj->matrix;
        float *r = (float *)oc->unk40;
        Vec4 t;
        t.x = nz * r[8] + nx * r[0] + ny * r[4];
        t.y = nx * r[1] + nz * r[9] + ny * r[5];
        t.z = nx * r[2] + nz * r[10] + ny * r[6];
        t.x += obj->unk10.x;
        t.y += obj->unk10.y;
        t.z += obj->unk10.z;
        t.x += oc->pos.x;
        t.y += oc->pos.y;
        t.z += oc->pos.z;
        Vec4 u;
        u.x = c->y * r[4] + c->z * r[8] + c->x * r[0];
        u.y = c->y * r[5] + c->z * r[9] + r[1] * c->x;
        u.z = c->y * r[6] + c->z * r[10] + c->x * r[2];
        d.x = t.x + u.x;
        d.y = t.y + u.y;
        d.z = t.z + u.z;
        d.x += cam->pos.x;
        d.y += cam->pos.y;
        d.z += cam->pos.z;
        d.x -= g_4722d0->cam.pos.x;
        d.y -= g_4722d0->cam.pos.y;
        d.z -= g_4722d0->cam.pos.z;
    }
    else
    {
        d.x = cam->pos.x - g_4722d0->cam.pos.x;
        d.y = cam->pos.y - g_4722d0->cam.pos.y;
        d.z = cam->pos.z - g_4722d0->cam.pos.z;
    }
    Camera *oc = (Camera *)obj->matrix;
    float rad = (float)box[0];
    float f;
    float rz = oc->scale.z * cam->scale.z * rad;
    float dz = d.z * g_4722d0->axisZ.z + d.y * g_4722d0->axisZ.y + d.x * g_4722d0->axisZ.x;
    f = dz + rz;
    if (*(int *)&f < 0)
    {
        return 1;
    }
    float dfar = dz - g_4722d0->unk19c;
    f = dfar;
    if (*(int *)&f >= 0)
    {
        return 1;
    }
    float rx = oc->scale.x * cam->scale.x * rad;
    float dl = d.z * g_4722d0->planeLeft.z + d.y * g_4722d0->planeLeft.y + d.x * g_4722d0->planeLeft.x;
    f = dl - rx;
    if (*(int *)&f >= 0)
    {
        return 1;
    }
    float dr = d.z * g_4722d0->planeRight.z + d.y * g_4722d0->planeRight.y + d.x * g_4722d0->planeRight.x;
    f = dr - rx;
    if (*(int *)&f >= 0)
    {
        return 1;
    }
    float ry = oc->scale.y * cam->scale.y * rad;
    float dt = d.z * g_4722d0->planeTop.z + d.y * g_4722d0->planeTop.y + d.x * g_4722d0->planeTop.x;
    f = dt - rx;
    if (*(int *)&f >= 0)
    {
        return 1;
    }
    float db = d.z * g_4722d0->planeBottom.z + d.y * g_4722d0->planeBottom.y + d.x * g_4722d0->planeBottom.x;
    f = db - rx;
    if (*(int *)&f >= 0)
    {
        return 1;
    }
    f = dz - rz;
    if (*(int *)&f < 0)
    {
        return 2;
    }
    f = dl + rx;
    if (*(int *)&f >= 0)
    {
        return 2;
    }
    f = dr + rx;
    if (*(int *)&f >= 0)
    {
        return 2;
    }
    f = dt + ry;
    if (*(int *)&f >= 0)
    {
        return 2;
    }
    f = db + ry;
    if (*(int *)&f >= 0)
    {
        return 2;
    }
    f = dfar;
    return *(int *)&f < 0 ? 0 : 2;
}

// Visibility of object index of the scene (-1 for the whole scene) from its bounding data: a
// sphere when box[0] is set, else a box when box[1] is set, else always partly visible.
// FUNCTION: STUNTGP_D3D 0x428040
int FUN_428040(Scene *scene, int index)
{
    ObjectDef *obj;
    WORD *box;
    if (index == -1)
    {
        box = (WORD *)(scene->unk10 + 0x10);
        obj = scene->lods[scene->lod];
    }
    else
    {
        obj = scene->lods[scene->lod] + index;
        box = &obj->unk20;
    }
    if (box[0] == 0 && box[1] == 0)
    {
        return 2;
    }
    if (box[0] == 0)
    {
        if (index == -1)
        {
            obj = NULL;
        }
        return FUN_427b40(scene, obj, box);
    }
    return FUN_427cc0(scene, obj, index, box);
}

// STUB: STUNTGP_D3D 0x425df0
void FUN_425df0(Scene *scene, ObjectDef *def, int type)
{
}

// FUNCTION: STUNTGP_D3D 0x426260
void FUN_426260()
{
    if (g_612948.unk02a0 == 2)
    {
        return;
    }
    Scene *scene = g_636418[3].scene;
    if (scene && scene->objectCount > 1)
    {
        ObjectDef *def = scene->lods[0];
        for (DWORD i = 0; i < scene->objectCount; i++)
        {
            int type = g_renderState.unk7f9c[i].type;
            if (type == 1 || type == 2 || type == 3)
            {
                FUN_425df0(scene, def, type);
            }
            AnimDef *src = &g_renderState.unk7f9c[i];
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

// Next free entry in the normal pool at g_renderState.unk7fa4.
// GLOBAL: STUNTGP_D3D 0x576cc8
Vec4 *g_576cc8;

// Builds face normals for a two-sided strip (both faces of each quad) and smoothed normals
// for its edge vertices, taking them from the normal pool.
// FUNCTION: STUNTGP_D3D 0x426370
void FUN_426370(Scene *scene, ObjectDef *def)
{
    Vec4 *normals = g_576cc8;
    DWORD n = def->vertCount;
    DWORD half = n >> 1;
    Vec4 *edge = normals + n;
    Vec4 a;
    Vec4 nrm;
    DWORD i;
    Vec4 *p = def->points;
    for (i = 0; i < half; i++)
    {
        a.x = p[i * 2 + 1].x - p[i * 2].x;
        *(WORD *)(def->verts + i * 8 + 4) = ((int)&normals[i] - (int)g_renderState.unk7fa4) >> 4;
        a.y = p[i * 2 + 1].y - p[i * 2].y;
        a.z = p[i * 2 + 1].z - p[i * 2].z;
        Vec4 b;
        b.x = p[i * 2].x - p[i * 2 + 2].x;
        b.y = p[i * 2].y - p[i * 2 + 2].y;
        b.z = p[i * 2].z - p[i * 2 + 2].z;
        nrm.x = b.y * a.z - b.z * a.y;
        nrm.y = b.z * a.x - b.x * a.z;
        nrm.z = b.x * a.y - b.y * a.x;
        Vec3_Normalize(&nrm.x);
        normals[i] = nrm;
        *(WORD *)(def->verts + (half + i) * 8 + 4) = ((int)&normals[half + i] - (int)g_renderState.unk7fa4) >> 4;
        nrm.x = -nrm.x;
        nrm.y = -nrm.y;
        nrm.z = -nrm.z;
        normals[half + i] = nrm;
    }
    MeshUv *uv = (MeshUv *)def->unk2c;
    int idx0 = ((int)edge - (int)g_renderState.unk7fa4) >> 4;
    int idx1 = idx0 + half;
    DWORD k = (def->pointCount >> 1) + 2;
    for (i = 0; i < half - 1; i++)
    {
        a.x = normals[i].x + normals[i + 1].x;
        a.y = normals[i].y + normals[i + 1].y;
        a.z = normals[i].z + normals[i + 1].z;
        Vec3_Normalize(&a.x);
        edge[i] = a;
        a.x = -a.x;
        a.y = -a.y;
        a.z = -a.z;
        edge[half + i] = a;
        uv[i * 2 + 2].unk0a = idx0;
        uv[k + i * 2].unk0a = idx1;
        uv[i * 2 + 3].unk0a = idx0;
        uv[k + i * 2 + 1].unk0a = idx1;
        idx0++;
        idx1++;
    }
    g_576cc8 += n * 3 - 2;
}

// Ripples a strip along its length with a sine wave tapered at both ends, then rebuilds its normals.
// FUNCTION: STUNTGP_D3D 0x426610
void FUN_426610(AnimObject *obj, Scene *scene, ObjectDef *def)
{
    DWORD angle = obj->angleA;
    DWORD half = def->vertCount >> 1;
    Vec4 *p = def->points;
    DWORD mid = def->pointCount >> 1;
    for (DWORD i = 0; i < half; i++)
    {
        float amp;
        if (i * 64 < 256)
        {
            amp = (float)(i * 64);
        }
        else if (i >= half - 4)
        {
            amp = (float)((half - i) * 64);
        }
        else
        {
            amp = 256.0f;
        }
        float y = amp * g_sinTable[angle];
        p->z = y;
        p[mid].z = y;
        p++;
        p->z = y;
        p[mid].z = y;
        p++;
        angle = (angle + 0x200) & 0x1fff;
    }
    FUN_426370(scene, def);
}

// FUN_426610 with a faster wave; type 2 tapers only the start and covers one more segment.
// FUNCTION: STUNTGP_D3D 0x4266e0
void FUN_4266e0(AnimObject *obj, Scene *scene, ObjectDef *def, int type)
{
    DWORD angle = obj->angleA;
    DWORD half = def->vertCount >> 1;
    Vec4 *p = def->points;
    DWORD mid = def->pointCount >> 1;
    if (type == 2)
    {
        half++;
    }
    for (DWORD i = 0; i < half; i++)
    {
        float amp;
        if (type == 2)
        {
            if (i * 32 < 256)
            {
                amp = (float)(i * 32);
            }
            else
            {
                amp = 256.0f;
            }
        }
        else if (i >= half - 8)
        {
            amp = (float)((half - i) * 32);
        }
        else
        {
            amp = 256.0f;
        }
        float y = amp * g_sinTable[angle];
        p->z = y;
        p[mid].z = y;
        p++;
        p->z = y;
        p[mid].z = y;
        p++;
        angle = (angle + 0x400) & 0x1fff;
    }
    FUN_426370(scene, def);
}

// FUNCTION: STUNTGP_D3D 0x4267d0
void FUN_4267d0(AnimObject *obj, ObjectDef *def)
{
    Vec4 up;
    Vec4 forward;
    forward.x = 0.0f;
    forward.y = 0.0f;
    forward.z = 1.0f;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    FUN_44ec00(&obj->rot.x, &forward.x);
    FUN_44ec00(&obj->rot.x, &up.x);
    FUN_44ec00(&obj->unk24.x, &forward.x);
    FUN_44ec00(&obj->unk24.x, &up.x);
    def->matrix[2] = forward;
    def->matrix[3] = up;
}

// FUNCTION: STUNTGP_D3D 0x426880
void FUN_426880(AnimObject *obj, ObjectDef *def)
{
    Vec4 *m = def->matrix;
    Vec4 dir;
    m[0].y = g_sinTable[obj->angleA] * 32.0f - 100.0f;
    dir.x = 0.0f;
    dir.y = g_sinTable[(obj->angleA * 2) & 0x1fff];
    dir.z = 128.0f;
    Vec3_Normalize(&dir.x);
    m[2] = dir;
}

// FUNCTION: STUNTGP_D3D 0x4268f0
void FUN_4268f0(AnimObject *obj, ObjectDef *def)
{
    Vec4 *m = def->matrix;
    Vec4 dir;
    m[0].y = g_sinTable[obj->angleA] * 128.0f - 100.0f + g_sinTable[obj->angleB] * 128.0f;
    dir.x = 0.0f;
    dir.y = g_sinTable[(obj->angleB * 2) & 0x1fff];
    dir.z = 128.0f;
    Vec3_Normalize(&dir.x);
    m[2] = dir;
}

extern float g_48266c;

// FUNCTION: STUNTGP_D3D 0x426970
void FUN_426970(Unk62a078 *p)
{
    p->flags = 7;
    p->unk68 = 0.01f;
    p->mode = 2;
    p->unk7c = 1;
    p->gravity = g_48266c * -0.05f;
    p->anim = NULL;
    p->size = 10.0f;
    p->sizeIn = 3.0f;
    p->sizeOut = 12.0f;
    p->alpha = 128.0f;
    p->alphaIn = 0.0f;
    p->alphaOut = 18.0f;
    p->colors[0] = 0x406090;
    p->texture = 7;
    p->unk98 = 0x60;
}

void FUN_45e110(Unk62a078 *particle);

// Every other frame (every frame above 80 fps), puffs a FUN_426970 particle out of the
// object, 2000 units behind its offset point.
// FUNCTION: STUNTGP_D3D 0x426a00
void FUN_426a00(AnimObject *obj, ObjectDef *def)
{
    if (!(def->flags & 0x10))
    {
        obj->unk40++;
        if (g_612948.unk0034 > 80 || (DWORD)obj->unk40 >= 2)
        {
            obj->unk40 = 0;
            Unk62a078 p;
            *(Camera *)&p.pos = g_4864e8;
            float m[16];
            FUN_44fb00(m, (DWORD)(obj->rot.x * (8192.0f / 360.0f)), (DWORD)(obj->rot.y * (8192.0f / 360.0f)),
                       (DWORD)(obj->rot.z * (8192.0f / 360.0f)));
            Vec4 off = def->unk10;
            off.z += 2000.0f;
            off.x = -off.x;
            off.y = -off.y;
            off.z = -off.z;
            p.pos.x = m[4] * off.y + m[0] * off.x + m[8] * off.z;
            p.pos.y = m[5] * off.y + m[1] * off.x + m[9] * off.z;
            p.pos.z = m[6] * off.y + m[2] * off.x + m[10] * off.z;
            p.pos.x += def->matrix->x;
            p.pos.y += def->matrix->y;
            p.pos.z += def->matrix->z;
            p.pos.x += def->unk10.x;
            p.pos.y += def->unk10.y;
            p.pos.z += def->unk10.z;
            p.pos.y -= 400.0f;
            FUN_426970(&p);
            p.lifetime = (DWORD)((float)fabs(FUN_42f1c0(18.0f)) + 45.0f);
            float speed = FUN_42f1c0(100.0f);
            float s = speed * 8.0f;
            if ((float)fabs(s) < 800.0f)
            {
                if (s < 0.0f)
                {
                    s = -800.0f;
                }
                else
                {
                    s = 800.0f;
                }
            }
            off.x = s * m[0];
            off.y = s * m[1];
            off.z = s * m[2];
            p.pos.x += off.x;
            p.pos.y += off.y;
            p.pos.z += off.z;
            p.vel[0] = speed * m[0];
            p.vel[1] = speed * m[1];
            p.vel[2] = speed * m[2];
            p.vel[1] = (float)fabs(FUN_42f1c0(50.0f));
            p.spin = FUN_42f1c0(22.5f);
            FUN_45e110(&p);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x426c70
void FUN_426c70(AnimObject *obj, ObjectDef *def)
{
    Vec4 *m = def->matrix;
    m[2].x = g_sinTable[obj->angleA];
    m[2].y = 0.0f;
    m[2].z = 16.0f;
    Vec3_Normalize(&m[2].x);
}

// FUNCTION: STUNTGP_D3D 0x426ca0
void FUN_426ca0(AnimObject *obj, ObjectDef *def)
{
    Vec4 *m = def->matrix;
    int angle = obj->angleA;
    m[3].x = g_sinTable[angle];
    m[3].y = 64.0f;
    m[3].z = 0.0f;
    Vec3_Normalize(&m[3].x);
    m[2].x = g_sinTable[angle];
    m[2].y = 0.0f;
    m[2].z = 128.0f;
    Vec3_Normalize(&m[2].x);
}

// FUNCTION: STUNTGP_D3D 0x426cf0
void FUN_426cf0(AnimObject *obj, ObjectDef *def, DWORD scale)
{
    BYTE *color = (BYTE *)&obj->unk44;
    DWORD r = color[2] * scale >> 8;
    DWORD g = color[1] * scale >> 8;
    DWORD b = color[0] * scale >> 8;
    BYTE *vertex = def->unk2c;
    for (DWORD i = 0; i < def->unk26; i++)
    {
        vertex[14] = r;
        vertex[13] = g;
        vertex[12] = b;
        vertex += 16;
    }
}

// FUNCTION: STUNTGP_D3D 0x426d50
void FUN_426d50(AnimObject *obj, ObjectDef *def)
{
    FUN_426cf0(obj, def, (int)(g_sinTable[obj->angleA] * 96.0f + 159.0f));
}

// FUNCTION: STUNTGP_D3D 0x426d80
void FUN_426d80(AnimObject *obj, ObjectDef *def)
{
    FUN_426cf0(obj, def, (int)(g_sinTable[obj->angleA] * 128.0f));
}

// FUNCTION: STUNTGP_D3D 0x426db0
void FUN_426db0(AnimObject *obj, ObjectDef *def)
{
    Vec4 *m = def->matrix;
    m[1].z = m[1].x = g_sinTable[obj->angleA] * 0.01f + 1.0f;
    m[1].y = g_sinTable[(obj->angleA * 2) & 0x1fff] * 0.015f + 1.0f;
}

// FUNCTION: STUNTGP_D3D 0x426df0
void FUN_426df0(AnimObject *obj, ObjectDef *def)
{
    Vec4 *m = def->matrix;
    m[1].z = m[1].x = g_sinTable[obj->angleA] * 0.005f + 1.0f;
    m[1].y = g_sinTable[(obj->angleA * 2) & 0x1fff] * 0.01f + 1.0f;
}

// FUNCTION: STUNTGP_D3D 0x426e30
void FUN_426e30(AnimObject *obj, ObjectDef *def)
{
    int angle = obj->angleA;
    Vec4 *m = def->matrix;
    int angle2 = (angle * 2) & 0x1fff;
    m[2].x = g_sinTable[angle];
    m[2].y = 0.0f;
    m[2].z = 2.0f;
    Vec3_Normalize(&m[2].x);
    m[3].x = g_sinTable[angle];
    m[3].y = 16.0f;
    m[3].z = g_sinTable[angle2];
    Vec3_Normalize(&m[3].x);
    m[1].x = g_sinTable[angle] * 0.01f + 1.0f;
    m[1].y = g_sinTable[angle2] * 0.02f + 1.0f;
    m[1].z = g_sinTable[angle2] * 0.01f + 1.0f;
}

// Runs each animated object's animation (object 0 is the track itself).
// FUNCTION: STUNTGP_D3D 0x426ed0
void FUN_426ed0(Scene *scene)
{
    g_576cc8 = (Vec4 *)g_renderState.unk7fa8;
    ObjectDef *def = scene->lods[0];
    AnimObject *obj = g_576cd0;
    for (DWORD i = 1; i < scene->objectCount; i++)
    {
        obj++;
        def++;
        switch (obj->type)
        {
        case 1:
            FUN_426610(obj, scene, def);
            break;
        case 2:
        case 3:
            FUN_4266e0(obj, scene, def, obj->type);
            break;
        case 4:
            FUN_4267d0(obj, def);
            break;
        case 5:
            FUN_426880(obj, def);
            break;
        case 16:
            FUN_4268f0(obj, def);
            FUN_4267d0(obj, def);
            FUN_426a00(obj, def);
            break;
        case 6:
        case 7:
            FUN_426c70(obj, def);
            break;
        case 8:
            FUN_426d50(obj, def);
            break;
        case 9:
            FUN_426d80(obj, def);
            break;
        case 10:
            FUN_426db0(obj, def);
            break;
        case 11:
            FUN_426df0(obj, def);
            break;
        case 12:
        case 13:
            FUN_426e30(obj, def);
            break;
        case 14:
            FUN_426ca0(obj, def);
            break;
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
        ObjectDef *def = g_636418[3].scene->lods[0];
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



// FUN_429660 that also stores clip outcodes for the four frustum sides and the near plane.
// FUNCTION: STUNTGP_D3D 0x429520
void FUN_429520(Vec4 *in, DWORD count)
{
    float d[5];
    Vec4 t;
    float *out = (float *)g_renderState.unk28;
    float nearZ = g_4722d0->nearZ;
    for (DWORD i = 0; i < count; i++)
    {
        t.x = g_61c428[8] * in->z + g_61c428[4] * in->y + g_61c428[0] * in->x + g_61c428[12];
        t.y = g_61c428[9] * in->z + g_61c428[5] * in->y + g_61c428[1] * in->x + g_61c428[13];
        t.z = g_61c428[10] * in->z + g_61c428[6] * in->y + g_61c428[2] * in->x + g_61c428[14];
        float sx = g_61c3e8[0] * t.x;
        out[0] = sx;
        float sy = g_61c3e8[5] * t.y;
        out[1] = sy;
        float sz = g_61c3e8[10] * t.z + g_61c3e8[14];
        out[2] = sz;
        d[0] = nearZ - sz;
        d[1] = -t.z - sx;
        d[2] = sx - t.z;
        d[3] = -t.z - sy;
        d[4] = sy - t.z;
        out[7] = t.z;
        *(WORD *)(out + 4) = ((*(DWORD *)&d[4] >> 26) & 0x20) | ((*(DWORD *)&d[3] >> 27) & 0x10) |
                             ((*(DWORD *)&d[2] >> 28) & 8) | ((*(DWORD *)&d[1] >> 29) & 4) | (*(DWORD *)&d[0] >> 31) | 2;
        in++;
        out += 8;
    }
}

// Transforms points by g_61c428 and projects them into the g_renderState.unk28 vertex buffer.
// FUNCTION: STUNTGP_D3D 0x429660
void FUN_429660(Vec4 *in, DWORD count)
{
    float *out = (float *)g_renderState.unk28;
    for (DWORD i = 0; i < count; i++, in++, out += 8)
    {
        Vec4 t;
        t.x = g_61c428[0] * in->x + g_61c428[8] * in->z + g_61c428[4] * in->y + g_61c428[12];
        t.y = g_61c428[1] * in->x + g_61c428[9] * in->z + g_61c428[5] * in->y + g_61c428[13];
        t.z = g_61c428[2] * in->x + g_61c428[10] * in->z + g_61c428[6] * in->y + g_61c428[14];
        out[7] = t.z;
        out[0] = g_61c3e8[0] * t.x;
        out[1] = g_61c3e8[5] * t.y;
        out[2] = g_61c3e8[10] * t.z + g_61c3e8[14];
    }
}


// Transforms the points referenced by the visible lists, once per frame each, and queues their
// vertex-buffer slots.
// FUNCTION: STUNTGP_D3D 0x429730
void FUN_429730()
{
    VisIndexList *list = g_renderState.unk34;
    if (list < g_renderState.unk40)
    {
        ObjectDef *obj = g_renderState.unk48;
        DWORD frame = g_renderState.unk20;
        float **dst = (float **)g_renderState.unk38;
        do
        {
            WORD *idx = list->indices;
            WORD v;
            while ((v = *idx) != 0xffff)
            {
                float *out = (float *)(g_renderState.unk28 + v * 32);
                if (((WORD *)out)[9] != frame)
                {
                    *dst++ = out;
                    Vec4 *in = &obj->points[*idx];
                    ((WORD *)out)[9] = frame;
                    Vec4 t;
                    t.x = g_61c428[8] * in->z + g_61c428[4] * in->y + g_61c428[0] * in->x + g_61c428[12];
                    t.y = g_61c428[9] * in->z + g_61c428[5] * in->y + g_61c428[1] * in->x + g_61c428[13];
                    t.z = g_61c428[2] * in->x + g_61c428[10] * in->z + g_61c428[6] * in->y + g_61c428[14];
                    out[0] = g_61c3e8[0] * t.x;
                    out[1] = g_61c3e8[5] * t.y;
                    out[2] = g_61c3e8[10] * t.z + g_61c3e8[14];
                    out[7] = t.z;
                }
                idx++;
            }
        } while (++list < g_renderState.unk40);
        g_renderState.unk38 = (int)dst;
    }
}


// FUN_429730 for the partly visible lists, also storing each vertex's frustum outcodes.
// FUNCTION: STUNTGP_D3D 0x429880
void FUN_429880()
{
    float d[5];
    Vec4 t;
    float nearZ = g_4722d0->nearZ;
    for (VisIndexList *list = g_renderState.unk30; list < g_renderState.unk3c; list++)
    {
        WORD *idx = list->indices;
        while (*idx != 0xffff)
        {
            float *out = (float *)(g_renderState.unk28 + *idx * 32);
            if (((WORD *)out)[9] != g_renderState.unk20)
            {
                *(float **)g_renderState.unk38 = out;
                g_renderState.unk38 += 4;
                Vec4 *in = &g_renderState.unk48->points[*idx];
                t.x = g_61c428[8] * in->z + g_61c428[4] * in->y + g_61c428[0] * in->x + g_61c428[12];
                t.y = g_61c428[9] * in->z + g_61c428[5] * in->y + g_61c428[1] * in->x + g_61c428[13];
                t.z = g_61c428[2] * in->x + g_61c428[10] * in->z + g_61c428[6] * in->y + g_61c428[14];
                float sx = g_61c3e8[0] * t.x;
                out[0] = sx;
                float sy = g_61c3e8[5] * t.y;
                out[1] = sy;
                float sz = g_61c3e8[10] * t.z + g_61c3e8[14];
                out[2] = sz;
                d[0] = nearZ - sz;
                d[1] = -t.z - sx;
                d[2] = sx - t.z;
                d[3] = -t.z - sy;
                d[4] = sy - t.z;
                ((WORD *)out)[9] = g_renderState.unk20;
                out[7] = t.z;
                *(WORD *)(out + 4) = ((*(DWORD *)&d[4] >> 26) & 0x20) | ((*(DWORD *)&d[3] >> 27) & 0x10) |
                                     ((*(DWORD *)&d[2] >> 28) & 8) | ((*(DWORD *)&d[1] >> 29) & 4) | (*(DWORD *)&d[0] >> 31) | 2;
            }
            idx++;
        }
    }
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

// GLOBAL: STUNTGP_D3D 0x60f014
DWORD g_60f014;

extern int g_60d678;
extern int g_60d67c;
extern int g_60f284;
extern int g_60d668;
extern int g_60eff0;
extern DWORD g_60eff8;
extern int g_60f2b4;
extern Unk4d5cc0 g_4d5cc0[6];
void FUN_41aac0(Replay *replay);
void FUN_41d300();
void FUN_405350();
void FUN_412b10(Car *car, float dist);
void FUN_401000();
void FUN_442c30();
void FUN_443e10(Car *car);
void FUN_460cb0(int a);
void FUN_447b70(int delay);
void FUN_442ad0(int type, int duration, int delay, int end, int from, int to, float scale);

// Time trial start: hooks the ghost replays to the ghost cars, places the player on the path
// and starts the intro fade.
// FUNCTION: STUNTGP_D3D 0x443100
void FUN_443100()
{
    g_60d678 = g_60f284;
    g_49a1f8[0].unk7268 = (Replay *)&g_4d5cc0[0];
    g_49a1f8[4].unk7268 = (Replay *)&g_4d5cc0[1];
    g_49a1f8[3].unk7268 = (Replay *)&g_4d5cc0[2];
    g_49a1f8[1].unk7268 = (Replay *)&g_4d5cc0[3];
    g_49a1f8[2].unk7268 = (Replay *)&g_4d5cc0[4];
    FUN_41aac0(g_49a1f8[0].unk7268);
    FUN_41aac0(g_49a1f8[4].unk7268);
    FUN_41aac0(g_49a1f8[3].unk7268);
    FUN_41aac0(g_49a1f8[1].unk7268);
    FUN_41aac0(g_49a1f8[2].unk7268);
    for (int i = 0; i < 6; i++)
    {
        g_49a1f8[i].active = 0;
    }
    g_49a1f8[0].active = 1;
    if (g_60f284 == 1 && !g_60d668)
    {
        g_60f284 = 0;
        g_60d628[0].unk00 = 1;
    }
    else if (g_60d668 == 1)
    {
        g_60d628[1].unk00 = 1;
    }
    g_4d5bb8 = g_49a1f8;
    FUN_41d300();
    FUN_405350();
    FUN_412b10(g_4d5bb8, g_571328->unk18 - g_60f014);
    g_4d5bb8->unk23a8 %= 100;
    g_4d5bb8->unk23ac %= 100;
    g_4d5bb8->unk767c = 1;
    g_4722d0->cam.pos = *(Vec4 *)&g_4d5bb8->posX;
    g_4d5bb8->unk1f0c = 3;
    FUN_442ad0(2, 240, 180, 0, 100, 0, 0.96f);
    g_60f2c4 = 180;
    g_4d5bb8->unk26a4 = 300;
    FUN_442c30();
    FUN_401000();
    FUN_443e10(g_4d5bb8);
    FUN_460cb0(0);
    FUN_447b70(420);
    g_60eff0 = 3;
    g_60f2cc = 1;
    g_60f2b4 = 1;
    g_60f2b0 = 4;
    g_60eff8 = 100;
    g_60d67c = 240;
}

// FUNCTION: STUNTGP_D3D 0x4434f0
void FUN_4434f0()
{
    GhostRecord *rec = g_60d628;
    for (int i = 0; i < 4; i++, rec++)
    {
        if (rec->unk00 == 1 && rec->ghost->unk00 == 0)
        {
            FUN_41ab00((Car *)rec->unk04, (Replay *)rec->ghost);
        }
        ((Car *)rec->unk04)->active = rec->unk00;
    }
}

// FUNCTION: STUNTGP_D3D 0x443530
void FUN_443530()
{
    GhostRecord *rec = g_60d628;
    for (int i = 0; i < 4; i++, rec++)
    {
        if (rec->unk00 == 1)
        {
            FUN_41ab00((Car *)rec->unk04, (Replay *)rec->ghost);
        }
        ((Car *)rec->unk04)->active = rec->unk00;
    }
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

extern int g_60f284;

// FUNCTION: STUNTGP_D3D 0x443590
void FUN_443590()
{
    if (g_60d628[0].unk00 == 1)
    {
        if (g_60f284 == 1)
        {
            g_60d628[0].unk00 = 0;
            return;
        }
        g_60d628[1].unk00 = 0;
        g_60d628[2].unk00 = 0;
        g_60d628[3].unk00 = 0;
        return;
    }
    if (g_60d628[1].unk00 == 1)
    {
        GhostRecord *best = NULL;
        DWORD bestTime = 0;
        DWORD count = 0;
        for (int i = 1; i < 4; i++)
        {
            GhostRecord *rec = &g_60d628[i];
            if (rec->time && rec->time < 7200)
            {
                rec->unk00 = 1;
                if (rec->time > bestTime)
                {
                    best = rec;
                    bestTime = best->time;
                }
                count++;
            }
        }
        if (best && count > 2)
        {
            best->unk00 = 0;
        }
    }
}

// GLOBAL: STUNTGP_D3D 0x60d67c
int g_60d67c;

// GLOBAL: STUNTGP_D3D 0x60d678
int g_60d678;

extern int g_60d674;
void FUN_443480();

// FUNCTION: STUNTGP_D3D 0x443630
void FUN_443630()
{
    Car *car = g_4722d0->data;
    if (g_60d67c && --g_60d67c == 0)
    {
        FUN_442cf0(180, g_6127a0[0x62], g_4d5bb8, 2, 0);
    }
    if (car->unk24a8 == 1)
    {
        FUN_443480();
        FUN_41ab40(car, car->unk7268);
        FUN_443590();
        FUN_443530();
        car->unk23a4 = 1;
        if (g_60d678 == 1 && car->unk23bc < 1)
        {
            FUN_442cf0(300, g_6127a0[0x12], car, 0, 100);
            g_60d674 = 1;
            FUN_443560();
            return;
        }
    }
    else
    {
        FUN_443590();
        FUN_4434f0();
    }
    FUN_443560();
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
    if (g_612948.unk0054 == 1)
    {
        *b = 1;
    }
    else
    {
        *b = others;
    }
}

// FUNCTION: STUNTGP_D3D 0x41da50
void FUN_41da50(int *count)
{
    int n = 0;
    Car *car = g_49a1f8;
    for (int i = 0; i < 6; i++, car++)
    {
        if (car->active == 1)
        {
            n++;
        }
    }
    *count = n;
}

void FUN_4482a0(DWORD frames, DWORD *digits);
extern char *g_4856c0[6];
extern char *g_4856d8[6];
extern char *g_4856f0[6];
extern char *g_485708[6];

// The original reloads car->unk23cc/unk23d4 after FUN_4482a0, which /Oa would keep in a register.
#pragma optimize("a", off)
// Formats a car's two times and score into its results text and points results row `row` at it.
// FUNCTION: STUNTGP_D3D 0x443f10
void FUN_443f10(Car *car, int row)
{
    DWORD d[16];
    char *time2;
    char *time1;
    int index = car - g_49a1f8;
    FUN_4482a0(car->unk23cc, d);
    if (car->unk23cc >= 36000)
    {
        time1 = g_60f02c[index].time1;
        // STRING: STUNTGP_D3D 0x482b44
        sprintf(time1, "%d%d:%d%d:%d%d", d[5], d[4], d[3], d[2], d[1], d[0]);
    }
    else
    {
        time1 = g_60f02c[index].time1;
        // STRING: STUNTGP_D3D 0x482b54
        sprintf(time1, "%d:%d%d:%d%d", d[4], d[3], d[2], d[1], d[0]);
    }
    FUN_4482a0(car->unk23d4, d);
    if (car->unk23d4 >= 36000)
    {
        time2 = g_60f02c[index].time2;
        // STRING: STUNTGP_D3D 0x482b64
        sprintf(time2, "%d%d:%d%d:%d%d", d[5], d[4], d[3], d[2], d[1], d[0]);
    }
    else
    {
        time2 = g_60f02c[index].time2;
        // STRING: STUNTGP_D3D 0x482b74
        sprintf(time2, "%d:%d%d:%d%d", d[4], d[3], d[2], d[1], d[0]);
    }
    // STRING: STUNTGP_D3D 0x482b84
    sprintf(g_60f02c[index].score, "%d", (int)car->unk260c);
    g_4856c0[row] = g_60f02c[index].name;
    g_485708[row] = g_60f02c[index].score;
    g_4856d8[row] = time1;
    g_4856f0[row] = time2;
}
#pragma optimize("", on)

extern DWORD g_60d720;
extern DWORD g_60d724;
void FUN_442a40(int type, int duration, int delay, int end, int from, int to, float scale);
void FUN_447ab0(Fader *fader);
void FUN_447a90(Fader *fader);
void FUN_45f8e0(int target, int step);
void FUN_443d80();

// Results sequence: shows one finisher row per second, then on the go-ahead fades the rows out
// and leaves the race.
// FUNCTION: STUNTGP_D3D 0x444070
void FUN_444070()
{
    DWORD count;
    g_61b740 = &g_498248[0].fx;
    if (++g_60d720 > 60 && g_60d724 < 6)
    {
        Car *car = g_612948.unk040c[g_60d724];
        if (car && car->active == 1)
        {
            g_498248[0].fx.faders[g_60d724 + 12].active = 1;
            FUN_443f10(car, g_60d724);
            FUN_461150(47, 0, 0, 63, 0, 0, 0);
            g_60d720 = 0;
            g_60d724++;
        }
    }
    FUN_41da50((int *)&count);
    if (g_60d724 >= count)
    {
        g_4d5bb8->race.unk20++;
    }
    if (++g_4d5bb8->race.unk24 >= 60)
    {
        g_4d5bb8->race.unk24 = 0;
    }
    FUN_447ab0(&g_61b740->faders[9]);
    FUN_447ab0(&g_61b740->faders[11]);
    FUN_447ab0(&g_61b740->faders[10]);
    Fader *fader = &g_61b740->faders[12];
    for (count = 0; count < 6; count++, fader++)
    {
        FUN_447ab0(fader);
    }
    if (FUN_443770() == 3 && !g_612948.unk001c && g_612948.unk0020 == 1 && !g_4d5bb8->race.unk2c)
    {
        FUN_443d80();
        FUN_461150(48, 0, 0, 255, 0, 0, 0);
        g_4d5bb8->race.unk28 = 0;
        g_4d5bb8->race.unk2c = 1;
        FUN_442a40(2, 120, 0, 0, 60, 0, 0.98f);
        FUN_460ca0();
        FUN_447a90(&g_61b740->faders[9]);
        FUN_447a90(&g_61b740->faders[10]);
        FUN_447a90(&g_61b740->faders[11]);
        FUN_461150(46, 0, 0, 63, 0, 0, 0);
    }
    if (g_4d5bb8->race.unk2c)
    {
        if (!(g_4d5bb8->race.unk2c & 7))
        {
            FUN_447a90(&g_61b740->faders[g_4d5bb8->race.unk28 + 12]);
            if (g_4d5bb8->race.unk28 < 6)
            {
                g_4d5bb8->race.unk28++;
            }
        }
        g_4d5bb8->race.unk2c++;
        if (g_4d5bb8->race.unk2c == 60)
        {
            FUN_442a40(2, 60, 0, 240, 60, 100, 0.98f);
        }
        if (g_4d5bb8->race.unk2c == 120)
        {
            FUN_45f8e0(0, -10);
        }
        if (g_4d5bb8->race.unk2c == 180)
        {
            g_612948.unk02a8 = 1;
            FUN_441e20();
        }
    }
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

// Catch-up: eases the leader's throttle scale down and raises the trailing cars' back towards 1.
// FUNCTION: STUNTGP_D3D 0x405960
void FUN_405960()
{
    Car *car = g_4d5bb8;
    if (car->catchUp)
    {
        if (car->unk24ac == 0)
        {
            if (g_612948.unk03cc[1])
            {
                float d = -g_612948.unk03cc[1]->leaderGap - g_60f2d0[20];
                if (d >= 0.0f)
                {
                    d = 1.0f / g_60f2d0[20] * d;
                    if (d > 1.0f)
                    {
                        d = 1.0f;
                    }
                    car->unk2660 -= d * g_60f2d0[21];
                    if (car->unk2660 < 0.0f)
                    {
                        car->unk2660 = 0.0f;
                    }
                }
            }
        }
        else if (car->unk2660 < 1.0f)
        {
            float d = -car->leaderGap - g_60f2d0[18];
            if (d >= 0.0f)
            {
                d = 1.0f / g_60f2d0[18] * d;
                if (d > 1.0f)
                {
                    d = 1.0f;
                }
                car->unk2660 += d * g_60f2d0[19];
                if (car->unk2660 > 1.0f)
                {
                    car->unk2660 = 1.0f;
                }
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x405a80
void FUN_405a80()
{
    for (int i = 0; i < 6; i++)
    {
        if (g_4d5bb8 != &g_49a1f8[i] && g_4d5bb8->active == 1)
        {
            Car *car = g_4d5bb8;
            float gap = car->leaderGap - g_49a1f8[i].leaderGap;
            if (gap > 0.0f && gap < 7500.0f)
            {
                float f = gap * 0.00013333333f;
                f *= f;
                if (f < 0.1f)
                {
                    f = 0.0f;
                }
                f = 1.0f - f + car->unk265c;
                if (f > 1.0f)
                {
                    f = 1.0f;
                }
                if (f > car->unk265c)
                {
                    car->unk265c = f;
                }
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x405b50
void FUN_405b50()
{
    Car *car = g_4d5bb8;
    unsigned int ticks = ++car->unk2664;
    if ((float)fabs(car->unk1cf0) > 8.333333f)
    {
        if (ticks >= 120)
        {
            if (car->unk1f10 == 0)
            {
                car->unk1f10 = 2;
            }
            car->unk2664 = 0;
        }
    }
    else if (car->unk1cf8 > 0.1f && ticks > 300)
    {
        car->unk1f10 = car->unk1f10 == 0 ? 2 : 0;
        car->unk2664 = 0;
    }
}

void FUN_40cc90();

// FUNCTION: STUNTGP_D3D 0x405be0
void FUN_405be0(float target)
{
    Car *car = g_4d5bb8;
    target -= car->unk1cf0;
    if (target <= 0.0f)
    {
        car->unk22bc = 0;
        if (target > -5.0f)
        {
            car->unk1cf8 *= 0.8f;
            return;
        }
        float brake = target * -32.0f;
        car->unk1cf8 = 0;
        car->controls[0] = 0;
        if (brake > 255.0f)
        {
            brake = 255.0f;
        }
        car->controls[1] = (BYTE)brake;
        FUN_40cc90();
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
    if (g_4d5bb8->race.unk68 != 1)
    {
        g_4d5bb8->race.unk68 = 1;
        g_4d5bb8->race.unk6c = 0;
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
                g_49a1f8[0].unk23d0 = (int)g_49a1f8[0].unk260c;
                g_49a1f8[0].unk23d4 = 0;
                g_49a1f8[0].unk23d8 = 0;
                FUN_401220(5, 0, g_4d5bb8->unk23d0);
                g_4d5bb8->unk260c = (float)g_49a1f8[0].unk23d0;
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
    car->race.unk68 = 0;
    car->race.unk6c = 0;
}

// FUNCTION: STUNTGP_D3D 0x443e20
void FUN_443e20()
{
    if (g_4d5bb8->race.unk68)
    {
        if (!g_4d5bb8->race.unk6c)
        {
            FUN_461150(47, 0, 0, 127, 0, 0, 0);
        }
        if (g_612948.unk8cec != 20)
        {
            FUN_430d40(15, 20);
        }
        if (++g_4d5bb8->race.unk6c > 120)
        {
            g_4d5bb8->race.unk68 = 0;
        }
    }
}

// GLOBAL: STUNTGP_D3D 0x60d720
DWORD g_60d720;

// GLOBAL: STUNTGP_D3D 0x60d724
DWORD g_60d724;

extern DWORD g_60d728;
void FUN_449e80();

// FUNCTION: STUNTGP_D3D 0x443ea0
void FUN_443ea0()
{
    if (g_498248[0].data->race.unk1c == 1)
    {
        return;
    }
    FUN_461150(47, 0, 0, 63, 0, 0, 0);
    g_60d720 = 0;
    g_60d724 = 0;
    g_60d728 = 0;
    g_61b740 = &g_498248[0].fx;
    g_498248[0].data->race.unk1c = 1;
    FUN_449e80();
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

// FUNCTION: STUNTGP_D3D 0x4443c0
void FUN_4443c0()
{
    g_4d5bb8->race.unk30 = 1;
    g_4d5bb8->race.unk34 = 0;
    g_4d5bb8->race.unk38 = -600.0f;
    g_4d5bb8->race.unk3c = 0.0f;
    g_4d5bb8->race.unk40 = -1.0f;
    FUN_461150(46, 0, 0, 63, 0, 0, 0);
}

void FUN_443d80();

// Start sequence: the countdown camera swing (unk38, a damped spring) settles, then the race
// starts after a delay or once the countdown has been skipped.
// FUNCTION: STUNTGP_D3D 0x444410
void FUN_444410()
{
    if (g_4d5bb8->race.unk30)
    {
        int id = g_4d5bb8->unk24e4 + 0x15;
        if (g_612948.unk8cec != id)
        {
            FUN_430d40(15, id);
        }
        if (g_4d5bb8->race.unk34 > 30 && !g_612948.unk001c && g_612948.unk0020 == 1)
        {
            FUN_443d80();
            FUN_461150(48, 0, 0, 255, 0, 0, 0);
            g_4d5bb8->race.unk30 = 0;
            g_4d5bb8->race.unk34 = 0;
            FUN_443ea0();
        }
        if ((float)fabs(g_4d5bb8->race.unk40) < 0.25f && (float)fabs(g_4d5bb8->race.unk3c) < 0.25f &&
            (float)fabs(g_4d5bb8->race.unk38) < 1.0f)
        {
            g_4d5bb8->race.unk40 = 0.0f;
            g_4d5bb8->race.unk3c = 0.0f;
            g_4d5bb8->race.unk38 = 0.0f;
            if (g_4d5bb8->race.unk34 >= 240)
            {
                g_4d5bb8->race.unk30 = 0;
                g_4d5bb8->race.unk34 = 0;
                FUN_443ea0();
            }
        }
        else
        {
            g_4d5bb8->race.unk40 = g_4d5bb8->race.unk38 * -0.01f;
            g_4d5bb8->race.unk3c = (g_4d5bb8->race.unk40 + g_4d5bb8->race.unk3c) * 0.95f;
            g_4d5bb8->race.unk38 = g_4d5bb8->race.unk3c + g_4d5bb8->race.unk38;
        }
        g_4d5bb8->race.unk34++;
    }
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

void FUN_447ba0(int delay);

// FUNCTION: STUNTGP_D3D 0x444590
void FUN_444590()
{
    if (!g_576be0)
    {
        g_60f2c0 = 1;
        if ((unsigned int)g_4d5bb8->unk24e4 <= 2)
        {
            FUN_45f8f0(0x15, 0);
        }
        else
        {
            FUN_45f8f0(0x16, 0);
        }
    }
    Car *car = g_4d5bb8;
    car->race.unk4c = 1;
    car->race.unk50 = 1;
    car->race.unk54 = 0;
    car->race.unk58 = 0.0f;
    car->race.unk5c = (float)fabs(car->unk1cf0);
    car->race.unk60 = 0;
    if (car->race.unk5c < 33.333332f)
    {
        car->race.unk5c = 33.333332f;
    }
    else if (car->race.unk5c > 100.0f)
    {
        car->race.unk5c = 100.0f;
    }
    FUN_447ba0(0);
    FUN_443dd0();
    if (!g_576be0 || FUN_444550() == 1)
    {
        g_60f2c0 = 1;
    }
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
            if ((car->unk24e0 == 1 && car->race.unk4c == 0 && car->race.unk30 == 0) || car->unk2640 == 1 ||
                car->unk24e8 == 1)
            {
                finished++;
            }
        }
    }
    return finished == total;
}

extern DWORD g_62f5ac;

// Finish line sequence: the crossing swing (unk58 by unk5c) with its sounds, the fade out and the
// move on to the results or the next player.
// FUNCTION: STUNTGP_D3D 0x4446d0
void FUN_4446d0()
{
    if (g_4d5bb8->race.unk1c == 1 || g_4d5bb8->race.unk30 == 1)
    {
        return;
    }
    if (g_4d5bb8->race.unk64 == 1)
    {
        if (++g_4d5bb8->race.unk24 >= 60)
        {
            g_4d5bb8->race.unk24 = 0;
        }
        return;
    }
    if (g_4d5bb8->unk24e0 == 1 && !g_4d5bb8->race.unk4c)
    {
        FUN_444590();
    }
    if (!g_4d5bb8->race.unk4c)
    {
        return;
    }
    if (g_4d5bb8->race.unk50)
    {
        if (g_60f2b0 != 3 && g_4d5bb8->race.unk50 == 60)
        {
            if (g_4d5bb8->unk24e4 == 0)
            {
                FUN_461150(0x15, 0, 0, 255, 0, 0, 0);
            }
            else if (g_4d5bb8->unk24e4 == 1)
            {
                FUN_461150(0x14, 0, 0, 255, 0, 0, 0);
            }
            else if (g_4d5bb8->unk24e4 == 2)
            {
                FUN_461150(0x13, 0, 0, 255, 0, 0, 0);
            }
        }
        int sound = 0;
        g_4d5bb8->race.unk50++;
        g_4d5bb8->race.unk58 = g_4d5bb8->race.unk5c * 0.5f + g_4d5bb8->race.unk58;
        if (g_4d5bb8->race.unk58 >= 360.0f)
        {
            sound = 0x2e;
            g_4d5bb8->race.unk58 -= 360.0f;
        }
        g_4d5bb8->race.unk5c *= 0.98f;
        if (g_4d5bb8->race.unk5c < 4.0f)
        {
            g_4d5bb8->race.unk5c = 4.0f;
        }
        if (g_4d5bb8->race.unk5c <= 4.0f && g_4d5bb8->race.unk58 <= 10.0f)
        {
            if (!g_4d5bb8->race.unk60)
            {
                g_4d5bb8->race.unk60 = 1;
                sound = 0x32;
            }
            g_4d5bb8->race.unk58 = 0.0f;
            g_4d5bb8->race.unk5c = 0.0f;
            if (g_4d5bb8->race.unk50 > 360 && !g_4d5bb8->race.unk54)
            {
                g_4d5bb8->race.unk54 = 1;
                FUN_442ad0(2, 240, 0, 0, 0, 60, 0.96f);
            }
        }
        if (sound)
        {
            FUN_461150(sound, 0, 0, 127, 0, 0, 0);
        }
        if (g_4d5bb8->race.unk50 > 30 && !g_612948.unk001c && g_612948.unk0020 == 1)
        {
            FUN_443d80();
            FUN_461150(48, 0, 0, 255, 0, 0, 0);
            if (!g_4d5bb8->race.unk54)
            {
                FUN_442ad0(2, 240, 0, 0, 0, 60, 0.96f);
            }
            g_4d5bb8->race.unk50 = 0;
            g_4d5bb8->race.unk54 = 480;
        }
        if (g_4d5bb8->race.unk54)
        {
            if ((++g_4d5bb8->race.unk54 >= 120 && !g_62f5ac) || g_4d5bb8->race.unk54 >= 480)
            {
                if (g_60df98 == 3)
                {
                    FUN_441e20();
                    return;
                }
                g_4d5bb8->race.unk4c = 0;
                g_4d5bb8->race.unk50 = 0;
                g_4d5bb8->race.unk54 = 0;
                g_4d5bb8->race.unk1c = 0;
                if (!g_576be0)
                {
                    if ((unsigned int)g_4d5bb8->unk24e4 <= 2)
                    {
                        FUN_4443c0();
                        FUN_45f8f0(23, 1);
                    }
                    else
                    {
                        FUN_443ea0();
                        FUN_45f8f0(23, 1);
                    }
                }
                else
                {
                    g_4d5bb8->race.unk64 = 1;
                }
            }
        }
    }
    if (g_576be0 && FUN_444670() == 1)
    {
        FUN_443ea0();
    }
}

void FUN_442ad0(int type, int duration, int delay, int end, int from, int to, float scale);

// FUNCTION: STUNTGP_D3D 0x4449e0
void FUN_4449e0()
{
    if (g_4d5bb8->race.unk04 != 1)
    {
        FUN_430d40(15, 25);
        g_4d5bb8->race.unk08 = 1;
        g_4d5bb8->race.unk04 = 1;
        g_4d5bb8->race.unk18 = 0;
        g_4d5bb8->race.unk0c = -256.0f;
        g_4d5bb8->race.unk10 = 0.0f;
        g_4d5bb8->race.unk14 = -1.0f;
        FUN_447ba0(0);
        FUN_442ad0(2, 60, 0, 0, 0, 60, 0.96f);
        FUN_443dd0();
        if (!g_576be0)
        {
            FUN_45f8f0(20, 0);
            FUN_460ca0();
        }
        FUN_461150(47, 0, 0x4000, 63, 0, 0, 0);
    }
}

// FUNCTION: STUNTGP_D3D 0x444a90
int FUN_444a90()
{
    if (g_612948.unk0054 == 1)
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

extern int g_60d71c;

// Finish sequence: once the car is done the camera swing (unk0c, a damped spring) settles and
// the race ends after a timeout.
// FUNCTION: STUNTGP_D3D 0x444ae0
void FUN_444ae0()
{
    CarRace *race = &g_4d5bb8->race;
    if (g_4d5bb8->unk24e8 == 1 && !race->unk04)
    {
        FUN_4449e0();
    }
    if (FUN_444a90() == 1 && !g_60d71c)
    {
        g_60d71c = 1;
        g_612948.unk02a8 = 1;
        FUN_441e20();
    }
    if (race->unk04 && g_60d71c != 1)
    {
        if ((++race->unk08 >= 0x21c && !g_62f5ac) || race->unk08 >= 900)
        {
            race->unk18 = 1;
            return;
        }
        if ((float)fabs(race->unk14) < 0.25f && (float)fabs(race->unk10) < 0.25f && (float)fabs(race->unk0c) < 1.0f)
        {
            race->unk14 = 0.0f;
            race->unk10 = 0.0f;
            race->unk0c = 0.0f;
            if (race->unk08 == 420)
            {
                FUN_442ad0(2, 120, 0, 300, 60, 100, 1.0f);
            }
        }
        else
        {
            race->unk14 = race->unk0c * -0.01f;
            race->unk10 = (race->unk14 + race->unk10) * 0.95f;
            race->unk0c = race->unk10 + race->unk0c;
        }
    }
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
            if (g_612948.unk8cec != 19)
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
            if (g_612948.unk8cec != 18)
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
            if (g_612948.unk8cec != 17)
            {
                FUN_430d40(15, 17);
            }
        }
        else if (g_4d5bb8->race.unk00 > 0)
        {
            if (g_612948.unk8cec != 16)
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

extern char *g_482b88[76];
extern DWORD g_477c30;

// Fills the drivers from the race entries and queues each car's model files.
// FUNCTION: STUNTGP_D3D 0x444db0
void FUN_444db0()
{
    RaceEntry *first;
    int firstIdx;
    unsigned int copies;
    unsigned int humans;
    int slot;
    int k;
    int i;
    RaceEntry *e;

    memset(g_49a1f8, 0, sizeof(g_49a1f8));
    copies = 0;
    first = NULL;
    slot = 4;
    e = g_60d730.entries;
    humans = 0;
    for (i = 0; i < 6; i++, e++)
    {
        if (e->type == 2)
        {
            humans++;
        }
    }
    firstIdx = 0;
    e = g_60d730.entries;
    for (i = 0; i < 6; i++, e++)
    {
        if (e->type != 2)
        {
            continue;
        }
        strcpy(g_60f02c[i].name, (char *)e->unk010);
        if (e->unk030)
        {
            g_60f02c[i].unk10 = e->unk030;
        }
        if (e->unk028)
        {
            g_60f02c[i].unk0c = e->unk028;
        }
        g_60f02c[i].unk08 = e->unk024;
        if (e->unk02c != 8)
        {
            g_60f02c[i].unk14 = e->unk02c;
        }
        if (!e->unk004)
        {
            e->unk008 = 1;
        }
        if (e->unk008)
        {
            g_60f02c[i].unk1c = e->unk008;
        }
        if (e->unk008 != 1000)
        {
            g_60f02c[i].unk20 = e->unk00c;
        }
        if (g_477c30 <= 0x400000 && humans >= 6)
        {
            if (first && e->unk004 && copies < 1)
            {
                copies++;
                g_60f02c[i] = g_60f02c[firstIdx];
                if (e->unk008)
                {
                    g_60f02c[i].unk1c = e->unk008;
                }
                if (e->unk008 != 1000)
                {
                    g_60f02c[i].unk20 = e->unk00c;
                }
                if (e->unk030)
                {
                    g_60f02c[i].unk10 = e->unk030;
                }
                strcpy(g_60f02c[i].name, (char *)e->unk010);
                k = first->unk024;
            }
            else
            {
                k = e->unk024;
            }
            strcpy((char *)g_58c234, g_482b88[k * 2 + 32]);
            g_58c540[g_58c808].id = g_58c234;
            g_58c540[g_58c808].slot = slot;
            g_58c234 += strlen((char *)g_58c234) + 1;
            g_58c808++;
            g_58c540[g_58c808].id = 0;
            strcpy((char *)g_58c234, g_482b88[47]);
            g_58c540[g_58c808].id = g_58c234;
            g_58c540[g_58c808].slot = slot + 1;
            g_58c234 += strlen((char *)g_58c234) + 1;
            g_58c808++;
            g_58c540[g_58c808].id = 0;
            if (!first && e->unk004)
            {
                first = e;
                firstIdx = i;
            }
        }
        else
        {
            strcpy((char *)g_58c234, g_482b88[e->unk024 * 2 + 32]);
            g_58c540[g_58c808].id = g_58c234;
            g_58c540[g_58c808].slot = slot;
            g_58c234 += strlen((char *)g_58c234) + 1;
            g_58c808++;
            g_58c540[g_58c808].id = 0;
            strcpy((char *)g_58c234, g_482b88[e->unk024 * 2 + 33]);
            g_58c540[g_58c808].id = g_58c234;
            g_58c540[g_58c808].slot = slot + 1;
            g_58c234 += strlen((char *)g_58c234) + 1;
            g_58c808++;
            g_58c540[g_58c808].id = 0;
        }
        slot += 2;
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

void FUN_4291f0(const char *text, int align, float x, float y, float z, D3DCOLOR color, float size, DWORD flags);

// Draws the first live message of the current slot, sliding it in and out at the bottom of the screen.
// FUNCTION: STUNTGP_D3D 0x442e30
void FUN_442e30()
{
    if (g_612948.unk0004 == 1)
    {
        return;
    }
    DWORD limit = g_renderState.unk8018 + 40;
    SlotEvent *event = g_4722d0->events;
    for (DWORD i = 0; i < 8; event++, i++)
    {
        if (event->count != 0 && event->count != event->duration)
        {
            DWORD count = event->count;
            DWORD offset;
            if (count < limit)
            {
                offset = count;
            }
            else
            {
                offset = event->duration - count;
                if (offset > limit)
                {
                    offset = limit;
                }
            }
            if (g_576be0)
            {
                offset = limit;
            }
            FUN_4291f0(event->text, 1, 320.0f, 480.0f - offset, 0.94f, count % 60 > 30 ? 0xff4040 : 0xffff00, 1.75f, 6);
            return;
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

// Dumps the sound zone boxes in level script syntax.
// FUNCTION: STUNTGP_D3D 0x446180
void FUN_446180()
{
    // STRING: STUNTGP_D3D 0x484aa4
    fprintf(g_5da2e4, "-LevelBoxList[] =\n");
    for (SoundZone *zone = g_483f98; zone->id != -1; zone++)
    {
        // STRING: STUNTGP_D3D 0x484ab8
        fprintf(g_5da2e4, "   -Type = %d\n", zone->id);
        // STRING: STUNTGP_D3D 0x484ac8
        fprintf(g_5da2e4, "   -Position = %12f %12f %12f\n", zone->bounds[0], zone->bounds[1], zone->bounds[2]);
        // STRING: STUNTGP_D3D 0x484ae8
        fprintf(g_5da2e4, "   -Scale    = %12f %12f %12f\n", zone->bounds[4], zone->bounds[5], zone->bounds[6]);
        // STRING: STUNTGP_D3D 0x484b08
        fprintf(g_5da2e4, "   -V        = %12f %12f %12f\n", zone->bounds[8], zone->bounds[9], zone->bounds[10]);
        // STRING: STUNTGP_D3D 0x484b28
        fprintf(g_5da2e4, "   -N        = %12f %12f %12f\n", zone->bounds[12], zone->bounds[13], zone->bounds[14]);
        // STRING: STUNTGP_D3D 0x484b48
        fprintf(g_5da2e4, "\n");
    }
}

// FUNCTION: STUNTGP_D3D 0x446340
void FUN_446340()
{
    // STRING: STUNTGP_D3D 0x484bbc
    fprintf(g_5da2e4, "***********************************************************************\n");
    // STRING: STUNTGP_D3D 0x484c08
    fprintf(g_5da2e4, "*                                                                     *\n");
    // STRING: STUNTGP_D3D 0x484c54
    fprintf(g_5da2e4, "*               SGP Level Config File (Text Version)                  *\n");
    // STRING: STUNTGP_D3D 0x484ca0
    fprintf(g_5da2e4, "*                    (C) Pete Opdam                                   *\n");
    // STRING: STUNTGP_D3D 0x484cec
    fprintf(g_5da2e4, "*                                                                     *\n");
    // STRING: STUNTGP_D3D 0x484d38
    fprintf(g_5da2e4, "***********************************************************************\n");
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

// Moves HUD faders 1-7 out by their offsets, scaled by their own value plus the master fader's,
// capped at 100.
// FUNCTION: STUNTGP_D3D 0x447d80
void FUN_447d80()
{
    SlotFx *fx = g_61b740;
    float v;
    v = fx->faders[1].value + fx->faders[0].value;
    if (v > 100.0f)
    {
        v = 100.0f;
    }
    fx->faders[1].x = fx->faders[1].dx * v * 0.01f + fx->faders[1].unk08;
    fx->faders[1].y = fx->faders[1].dy * v * 0.01f + fx->faders[1].unk0c;
    v = fx->faders[2].value + fx->faders[0].value;
    if (v > 100.0f)
    {
        v = 100.0f;
    }
    fx->faders[2].x = fx->faders[2].dx * v * 0.01f + fx->faders[2].unk08;
    fx->faders[2].y = fx->faders[2].dy * v * 0.01f + fx->faders[2].unk0c;
    v = fx->faders[7].value + fx->faders[0].value;
    if (v > 100.0f)
    {
        v = 100.0f;
    }
    fx->faders[7].x = fx->faders[7].dx * v * 0.01f + fx->faders[7].unk08;
    fx->faders[7].y = fx->faders[7].dy * v * 0.01f + fx->faders[7].unk0c;
    v = fx->faders[3].value + fx->faders[0].value;
    if (v > 100.0f)
    {
        v = 100.0f;
    }
    fx->faders[3].x = fx->faders[3].dx * v * 0.01f + fx->faders[3].unk08;
    fx->faders[3].y = fx->faders[3].dy * v * 0.01f + fx->faders[3].unk0c;
    v = fx->faders[4].value + fx->faders[0].value;
    if (v > 100.0f)
    {
        v = 100.0f;
    }
    fx->faders[4].x = fx->faders[4].dx * v * 0.01f + fx->faders[4].unk08;
    fx->faders[4].y = fx->faders[4].dy * v * 0.01f + fx->faders[4].unk0c;
    v = fx->faders[5].value + fx->faders[0].value;
    if (v > 100.0f)
    {
        v = 100.0f;
    }
    fx->faders[5].x = fx->faders[5].dx * v * 0.01f + fx->faders[5].unk08;
    fx->faders[5].y = fx->faders[5].dy * v * 0.01f + fx->faders[5].unk0c;
    v = fx->faders[6].value + fx->faders[0].value;
    if (v > 100.0f)
    {
        v = 100.0f;
    }
    fx->faders[6].x = fx->faders[6].dx * v * 0.01f + fx->faders[6].unk08;
    fx->faders[6].y = fx->faders[6].dy * v * 0.01f + fx->faders[6].unk0c;
}

extern Vec4 g_482678;

// FUNCTION: STUNTGP_D3D 0x401d70
void FUN_401d70(float *v, float scale)
{
    if (v[0] * v[0] + v[1] * v[1] + v[2] * v[2] <= 27777.777f)
    {
        float g[4];
        g[0] = g_482678.x * scale;
        g[1] = g_482678.y * scale;
        g[2] = g_482678.z * scale;
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

int FUN_4280a0(Vec4 *pos, Vec4 *size);
extern MeshFace *g_5da234;
extern WORD *g_5da238;
extern Vec4 *g_5da23c;
extern MeshUv *g_5da240;
extern MeshFace *g_5da24c;
extern WORD *g_5da250;
extern Vec4 *g_5da254;
extern MeshUv *g_5da258;
extern ObjectDef *g_5da25c;
extern float g_5da1e0[16];
extern MeshPolyVertex g_478910[4];

// Appends the billboard as a quad facing along dir to the dynamic mesh unless it is outside the
// view; g_5da1e0 rows 0-2 become the billboard's basis.
// FUNCTION: STUNTGP_D3D 0x434590
void FUN_434590(Billboard *billboard)
{
    if (g_5da24c < g_5da234 + 0x200)
    {
        if (FUN_4280a0(&billboard->pos, (Vec4 *)billboard->size) != 1)
        {
            ObjectDef *object = g_5da25c;
            object->vertCount++;
            object->unk26 += 4;
            object->pointCount += 4;
            g_5da24c->count = 4;
            g_5da24c->flags = (BYTE)billboard->unk00 | 0x80;
            g_5da24c->unk01 = (BYTE)billboard->texture;
            g_5da24c->unk02 = (BYTE)billboard->alpha;
            g_5da24c->index = g_5da250 - g_5da238;
            g_5da24c++;
            *(Vec4 *)&g_5da1e0[4] = billboard->dir;
            g_5da1e0[0] = g_5da1e0[10] * g_5da1e0[5] - g_5da1e0[9] * g_5da1e0[6];
            g_5da1e0[1] = g_5da1e0[8] * g_5da1e0[6] - g_5da1e0[4] * g_5da1e0[10];
            g_5da1e0[2] = g_5da1e0[4] * g_5da1e0[9] - g_5da1e0[8] * g_5da1e0[5];
            Vec4 *m = g_4722d0->cam.matrix;
            int point = g_5da254 - g_5da23c;
            for (int i = 0; i < 4; i++)
            {
                Vec4 r;
                Vec4 t;
                float x = g_478910[i].pos.x * billboard->size[0];
                float y = billboard->size[1] * g_478910[i].pos.y;
                float z = g_478910[i].pos.z * billboard->size[2];
                g_5da258->point = point;
                g_5da258->color = billboard->colors[0];
                g_5da258->u = g_478910[i].u;
                g_5da258->v = g_478910[i].v;
                r.x = g_5da1e0[0] * x + g_5da1e0[4] * y + g_5da1e0[8] * z;
                r.y = g_5da1e0[5] * y + g_5da1e0[1] * x + g_5da1e0[9] * z;
                r.z = g_5da1e0[6] * y + g_5da1e0[10] * z + g_5da1e0[2] * x;
                t.x = r.x * m[0].x + r.y * m[1].x + r.z * m[2].x;
                t.y = r.y * m[1].y + r.z * m[2].y + r.x * m[0].y;
                t.z = r.y * m[1].z + r.z * m[2].z + r.x * m[0].z;
                g_5da254->x = t.x + billboard->pos.x;
                g_5da254->y = t.y + billboard->pos.y;
                g_5da254->z = t.z + billboard->pos.z;
                *g_5da250++ = g_5da258 - g_5da240;
                g_5da258++;
                point++;
                g_5da254++;
            }
        }
    }
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
                    billboard.texture = (short)(((TextureSlot *)p->anim[0] - g_renderState.unk62ec) + p->frame / 4096);
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

// Expands a PCX's trailing 256-colour palette into four-byte entries.
// FUNCTION: STUNTGP_D3D 0x45e620
void FUN_45e620(BYTE *pcx, BYTE *out, int size)
{
    BYTE *pal = pcx + size - 0x300;
    if (pal[-1] == 12)
    {
        for (int i = 0; i < 0x300; i += 3)
        {
            out[1] = pal[i];
            out[2] = pal[i + 1];
            out[3] = pal[i + 2];
            out[0] = 0;
            out += 4;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45e670
void FUN_45e670(BYTE *pcx, BYTE *out)
{
    BYTE *src = pcx + 0x80;
    int y = g_489720;
    while (y-- > 0)
    {
        int x = 0;
        while (x < g_48971c)
        {
            if (*src > 0xc0)
            {
                int n = *src - 0xc0;
                BYTE v = src[1];
                x += n;
                while (n-- > 0)
                {
                    *out++ = v;
                }
                src += 2;
            }
            else
            {
                *out++ = *src++;
                x++;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45e720
int FUN_45e720(BYTE *src, BYTE *out, int size)
{
    BYTE *start = out;
    BYTE *end = src + size;
    int x = -1;
    while (src < end)
    {
        BYTE c = *src;
        x = (x + 1) % g_48971c;
        src++;
        if (c <= 0xc0)
        {
            int n = 1;
            while (c == *src && n < 0x3f && x < g_48971c - 1)
            {
                x++;
                src++;
                n++;
            }
            *out = n + 0xc0;
        }
        else
        {
            *out = 0xc1;
        }
        out++;
        *out++ = c;
    }
    *out = 12;
    return out - start + 1;
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

// Encodes an 8-bit image as a PCX file; returns the file size.
// FUNCTION: STUNTGP_D3D 0x45e880
int FUN_45e880(BYTE *pixels, PcxHeader *header, BYTE *palette, int width, int height)
{
    g_48971c = width;
    g_489720 = height;
    FUN_45e7b0(header);
    int size = FUN_45e720(pixels, (BYTE *)header + 0x80, width * height);
    FUN_45e850((BYTE *)header + size + 0x80, palette);
    return size + 0x380;
}

// GLOBAL: STUNTGP_D3D 0x62d47c
BYTE *g_62d47c;

void *Mem_Alloc(int size, int type);
int Mem_Free(void *ptr);
void FUN_4234d0(char *msg);
int FUN_44aff0(char *name, void *data, int size);

// FUNCTION: STUNTGP_D3D 0x45e8e0
void FUN_45e8e0(char *path, BYTE *pixels, BYTE *palette, int width, int height)
{
    g_62d47c = (BYTE *)Mem_Alloc(0x100000, 0);
    if (!g_62d47c)
    {
        // STRING: STUNTGP_D3D 0x489724
        FUN_4234d0("Could not allocate enought memory...\n");
    }
    int size = FUN_45e880(pixels, (PcxHeader *)g_62d47c, palette, width, height);
    FUN_44aff0(path, g_62d47c, size);
    Mem_Free(g_62d47c);
}

// FUNCTION: STUNTGP_D3D 0x45e950
int FUN_45e950(BYTE *pcx, BYTE *out, BYTE *palette, int size)
{
    if (!palette)
    {
        palette = out;
    }
    g_48971c = (pcx[0x43] << 8) | pcx[0x42];
    g_489720 = ((pcx[0xb] << 8) | pcx[0xa]) + 1;
    if (pcx[0] == 10 && pcx[1] == 5)
    {
        if (palette)
        {
            FUN_45e620(pcx, palette, size);
        }
        FUN_45e670(pcx, out);
    }
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x45e9b0
void FUN_45e9b0(char *path, BYTE *out, BYTE *palette)
{
    char msg[0x80];
    int size = size_of_file(path);
    if (!size)
    {
        // STRING: STUNTGP_D3D 0x48974c
        sprintf(msg, "File: %s not found...", path);
        FUN_4234d0(msg);
    }
    g_62d47c = (BYTE *)Mem_Alloc(size, 0);
    if (g_62d47c)
    {
        bload(path, (char *)g_62d47c, size);
        if (size)
        {
            FUN_45e950(g_62d47c, out, palette, size);
            g_489714 = g_48971c;
            g_489718 = g_489720;
        }
        Mem_Free(g_62d47c);
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

void FUN_460d90(int *channel);
void FUN_4614a0(int channel, int loop, DWORD frequency, DWORD volume, Vec4 *pos, Vec4 *velocity, int keep,
                int *slotIndex);
void FUN_461850(int *channel, DWORD frequency, DWORD volume, Vec4 *pos, Vec4 *velocity);

// Sound channels per car type and per surface (index 0 is no surface).
// GLOBAL: STUNTGP_D3D 0x474700
int g_474700[5] = {11, 11, 11, 11, 11};

// GLOBAL: STUNTGP_D3D 0x47472c
int g_47472c[6] = {0, 31, 27, 27, 27, 31};

// GLOBAL: STUNTGP_D3D 0x474744
int g_474744[6] = {0, 26, 27, 27, 27, 26};

// Tyre squeal: loudness from how hard the sliding wheels are loaded, pitch from the heaviest one.
// FUNCTION: STUNTGP_D3D 0x41af70
void FUN_41af70()
{
    Car *car = g_4d5bb8;
    if (car->unk1fd8 != 1 && (float)fabs(car->unk1cf0) >= 1.0f)
    {
        float sum = 0.0f;
        float pitch = 0.0f;
        int muted = 0;
        unsigned int surface = 0;
        for (int i = 0; i < 4; i++)
        {
            Wheel *w = &car->wheels[i];
            if (w->unk30 > 0.8f)
            {
                muted |= w->unk7c;
                if ((unsigned int)w->unk78 > surface)
                {
                    surface = w->unk78;
                }
                float t = w->unk30 * 8.0f + 127.0f;
                float p = w->unk30 * 32.0f;
                if (p > pitch)
                {
                    pitch = p;
                }
                sum += t;
            }
        }
        int vol = (int)(sum * 0.1254902f);
        if (pitch > 2048.0f)
        {
            pitch = 2048.0f;
        }
        pitch += 21028.0f;
        if (vol < 0)
        {
            vol = 0;
        }
        else if (vol > 255)
        {
            vol = 255;
        }
        if (vol >= 1 && !muted)
        {
            if (!car->unk237c)
            {
                FUN_4614a0(g_474744[surface], 1, (int)pitch, vol, (Vec4 *)&car->posX, NULL, 0, &car->unk237c);
                return;
            }
            FUN_461850(&car->unk237c, (int)pitch, vol, (Vec4 *)&car->posX, NULL);
            return;
        }
    }
    FUN_460d90(&car->unk237c);
}

// GLOBAL: STUNTGP_D3D 0x47475c
int g_47475c[6] = {0, 24, 29, 29, 29, 24};

// Rolling noise: loudness from the load on each grounded wheel, pitch from the car's speed.
// FUNCTION: STUNTGP_D3D 0x41b0d0
void FUN_41b0d0()
{
    float sum = 0.0f;
    int muted = 0;
    unsigned int surface = 0;
    for (int i = 0; i < 4; i++)
    {
        Wheel *w = &g_4d5bb8->wheels[i];
        if (w->unk0c > 0.0f)
        {
            float s = w->unk04 * w->unk04 * 0.125f;
            if (s < 1.0f)
            {
                float k = s * 160.0f;
                s += k;
            }
            else
            {
                s += 160.0f;
            }
            muted |= w->unk7c;
            float v = (w->unk0c / w->unk10) * s;
            if ((unsigned int)w->unk78 > surface)
            {
                surface = w->unk78;
            }
            if (v > 255.0f)
            {
                v = 255.0f;
            }
            sum += v;
        }
    }
    if (sum < 1.0f)
    {
        FUN_460d90(&g_4d5bb8->unk2384);
        return;
    }
    float vol = sum * 0.09411765f;
    float pitch = (float)fabs(g_4d5bb8->unk1cf0) * 0.0108f;
    if (pitch > 1.0f)
    {
        pitch = 1.0f;
    }
    pitch = pitch * 33792.0f + 11264.0f;
    if (muted)
    {
        FUN_460d90(&g_4d5bb8->unk2384);
    }
    if (!g_4d5bb8->unk2384)
    {
        FUN_4614a0(g_47475c[surface], 1, (int)pitch, (int)vol, (Vec4 *)&g_4d5bb8->posX, NULL, 0,
                   &g_4d5bb8->unk2384);
        return;
    }
    FUN_461850(&g_4d5bb8->unk2384, (int)pitch, (int)vol, (Vec4 *)&g_4d5bb8->posX, NULL);
}

// FUNCTION: STUNTGP_D3D 0x41b250
void FUN_41b250()
{
    Car *car = g_4d5bb8;
    if (car->unk2360 < 4.0f)
    {
        car->unk2374 = car->unk2378;
        car->unk2378 = 0;
        return;
    }
    if (car->unk2378 && !car->unk2374)
    {
        int vol = (int)(car->unk2898 * 0.1875f);
        if (vol < 0)
        {
            vol = 0;
        }
        else if (vol > 192)
        {
            vol = 192;
        }
        FUN_4614a0(0x1c, 0, 0, vol + 32, (Vec4 *)&car->posX, NULL, 0, NULL);
        g_4d5bb8->unk2374 = g_4d5bb8->unk2378;
    }
}

// GLOBAL: STUNTGP_D3D 0x474714
int g_474714[6] = {0, 25, 27, 25, 25, 25};

// GLOBAL: STUNTGP_D3D 0x474774
int g_474774[4] = {12, 13, 14, 12};

// GLOBAL: STUNTGP_D3D 0x570acc
unsigned int g_570acc;

// Scrape loop while unk236c counts down, plus a one-shot crunch for a hard enough hit.
// FUNCTION: STUNTGP_D3D 0x41b2f0
void FUN_41b2f0()
{
    if (!g_4d5bb8->unk236c)
    {
        FUN_460d90(&g_4d5bb8->unk2380);
        g_4d5bb8->unk236c = 0;
        g_4d5bb8->unk2370 = 0;
        return;
    }
    float hit = g_4d5bb8->unk2360;
    g_4d5bb8->unk2360 = 0.0f;
    g_4d5bb8->unk236c--;
    if (g_4d5bb8->unk1cf0 > 100.0f / 60.0f && g_4d5bb8->unk236c > 0)
    {
        float a = (float)fabs(hit);
        if (a > 1.0f)
        {
            a = 1.0f;
        }
        a *= 128.0f;
        float speed = (float)fabs(g_4d5bb8->unk1cf0);
        float b = speed * (1.0f / 60.0f);
        if (b > 1.0f)
        {
            b = 1.0f;
        }
        float vol = b * a;
        int channel = g_474714[g_4d5bb8->wheels[0].unk78];
        float c = speed * 0.012f;
        if (c > 1.0f)
        {
            c = 1.0f;
        }
        float freq = c * 17408.0f + 5120.0f;
        if (!g_4d5bb8->unk2380)
        {
            FUN_4614a0(channel, 1, (int)freq, (int)vol, (Vec4 *)&g_4d5bb8->posX, NULL, 0, &g_4d5bb8->unk2380);
        }
        else
        {
            FUN_461850(&g_4d5bb8->unk2380, (int)freq, (int)vol, (Vec4 *)&g_4d5bb8->posX, NULL);
        }
    }
    else if (g_4d5bb8->unk1cf0 < 100.0f / 60.0f)
    {
        FUN_460d90(&g_4d5bb8->unk2380);
    }
    if (hit >= 4.0f)
    {
        float v = hit * 8.0f + 64.0f;
        if (v > 255.0f)
        {
            v = 255.0f;
        }
        if (!g_4d5bb8->unk2370)
        {
            v *= 255.0f;
            int idx = g_570acc++ & 3;
            FUN_4614a0(g_474774[idx], 0, 0, (int)(v * (1.0f / 255.0f)), (Vec4 *)&g_4d5bb8->posX, NULL, 0,
                       &g_4d5bb8->unk2370);
        }
    }
}

// GLOBAL: STUNTGP_D3D 0x474784
int g_474784[4] = {12, 13, 14, 12};

// Collision sounds: the scrape/crunch of FUN_41b2f0, then a bump for a hard enough landing, at most every 4 ticks.
// FUNCTION: STUNTGP_D3D 0x41b510
void FUN_41b510()
{
    if (g_4d5bb8->unk2368)
    {
        g_4d5bb8->unk2368--;
    }
    FUN_41b2f0();
    float hit = g_4d5bb8->unk2364;
    g_4d5bb8->unk2364 = 0.0f;
    if (hit >= 4.0f)
    {
        float v = hit * 4.0f;
        v *= 255.0f;
        v = v * (1.0f / 255.0f) + 16.0f;
        if (v > 255.0f)
        {
            v = 255.0f;
        }
        if (!g_4d5bb8->unk2368)
        {
            int idx = g_570acc++ & 3;
            FUN_4614a0(g_474784[idx], 0, 0, (int)v, (Vec4 *)&g_4d5bb8->posX, NULL, 0, NULL);
            g_4d5bb8->unk2368 = 4;
        }
    }
}

// Engine note: pitch and volume follow the revs.
// FUNCTION: STUNTGP_D3D 0x41b5d0
void FUN_41b5d0()
{
    Car *car = g_4d5bb8;
    if (car->unk2254 == 0.0f)
    {
        FUN_460d90(&car->unk2388);
        return;
    }
    DWORD freq = (DWORD)(car->unk2254 * 5000.0f / car->unkd64 + 11025.0f);
    DWORD vol = (DWORD)(car->unk2254 * 96.0f / car->unkd64 + 48.0f);
    if (!car->unk2388)
    {
        FUN_4614a0(g_474700[car->race.unk80[3]], 1, freq, vol, (Vec4 *)&car->posX, NULL, 0, &car->unk2388);
        return;
    }
    FUN_461850(&car->unk2388, freq, vol, (Vec4 *)&car->posX, NULL);
}

// FUNCTION: STUNTGP_D3D 0x41b680
void FUN_41b680()
{
    if (g_4d5bb8->unk234c)
    {
        g_4d5bb8->unk234c--;
        g_4d5bb8->unk2354 = 0;
        return;
    }
    if (g_4d5bb8->unk2354)
    {
        g_4d5bb8->unk234c = 120;
        g_4d5bb8->unk2354 = 0;
        int vol = (int)(g_4d5bb8->unk235c * 0.75f);
        if (vol < 0)
        {
            vol = 0;
        }
        else if (vol > 192)
        {
            vol = 192;
        }
        FUN_4614a0(g_47472c[g_4d5bb8->wheels[0].unk78], 0, 0, vol + 32, (Vec4 *)&g_4d5bb8->posX, NULL, 0, NULL);
    }
}

GameSlot *FUN_402590(Car *car);

// GLOBAL: STUNTGP_D3D 0x4746c4
int g_4746c4[5] = {34, 35, 36, 37, 38};

// Peak volume of the gear change clunk per gear.
// GLOBAL: STUNTGP_D3D 0x474794
unsigned int g_474794[9] = {160, 160, 136, 112, 80, 48, 32, 24, 19};

// FUNCTION: STUNTGP_D3D 0x41b710
void FUN_41b710()
{
    if (g_4d5bb8->unk2394)
    {
        float t = g_4d5bb8->unk2398;
        float f = t * 11025.0f;
        FUN_4614a0(0x17, 0, (int)(f + 11025.0f), (int)(t * 255.0f), (Vec4 *)&g_4d5bb8->posX, NULL, 0, NULL);
        g_4d5bb8->unk2394 = 0;
    }
    if (g_4d5bb8->controls[9])
    {
        if (!g_4d5bb8->unk2338)
        {
            FUN_4614a0(g_4746c4[g_4d5bb8->race.unk80[0]], 1, 0, 0xe0, (Vec4 *)&g_4d5bb8->posX, &g_4d5bb8->unk1c8c,
                       0, &g_4d5bb8->unk2338);
        }
        else
        {
            FUN_461850(&g_4d5bb8->unk2338, 0, 0xe0, (Vec4 *)&g_4d5bb8->posX, &g_4d5bb8->unk1c8c);
        }
    }
    else if (g_4d5bb8->unk2338)
    {
        FUN_460d90(&g_4d5bb8->unk2338);
    }
    g_4722d0 = FUN_402590(g_4d5bb8);
    if (g_4722d0 && g_4d5bb8->unk23a0 == 1)
    {
        g_4d5bb8->unk23a0 = 0;
        int gear = abs((int)g_4d5bb8->unk1f10);
        Vec4 d;
        d.x = g_4722d0->cam.pos.x - g_4d5bb8->posX;
        d.y = g_4722d0->cam.pos.y - g_4d5bb8->posY;
        d.z = g_4722d0->cam.pos.z - g_4d5bb8->posZ;
        float v = (7500.0f - (float)sqrt(d.x * d.x + d.y * d.y + d.z * d.z)) * 0.00013333333f;
        if (v > 0.0f)
        {
            v += 0.1f;
            if (v > 1.0f)
            {
                v = 1.0f;
            }
            FUN_461150(0x21, 0, 0, (int)(g_474794[gear] * (v * v)), 0, 1, 0);
        }
    }
    FUN_402580();
}

// Wind volume scale: eases down while unk1cf8 is above 0.2, back up to 1 otherwise.
// GLOBAL: STUNTGP_D3D 0x4747b8
float g_4747b8 = 0.75f;

// FUNCTION: STUNTGP_D3D 0x41b8e0
void FUN_41b8e0()
{
    if (FUN_402590(g_4d5bb8))
    {
        if (g_4d5bb8->unk1cf0 < 500.0f / 60.0f)
        {
            FUN_460d90(&g_4d5bb8->unk239c);
            return;
        }
        float sum = 0.0f;
        for (int i = 0; i < 4; i++)
        {
            sum += g_4d5bb8->wheels[i].unk04;
        }
        float v = (float)fabs(sum) * 0.25f;
        v *= 0.01f;
        if (v > 1.0f)
        {
            v = 1.0f;
        }
        float freq = v * 14000.0f + 6000.0f;
        if (g_4d5bb8->unk1cf8 > 0.2f)
        {
            if (g_4747b8 > 0.75f)
            {
                g_4747b8 -= 0.05f;
            }
        }
        else if (g_4747b8 < 1.0f)
        {
            g_4747b8 += 0.025f;
        }
        float vol = v * g_4747b8 * 80.0f;
        if (!g_4d5bb8->unk239c)
        {
            FUN_4614a0(0x1e, 1, (int)freq, (int)vol, (Vec4 *)&g_4d5bb8->posX, NULL, 0, &g_4d5bb8->unk239c);
        }
        else
        {
            FUN_461850(&g_4d5bb8->unk239c, (int)freq, (int)vol, (Vec4 *)&g_4d5bb8->posX, NULL);
        }
    }
}

// GLOBAL: STUNTGP_D3D 0x4746c0
int g_4746c0 = 100;

// GLOBAL: STUNTGP_D3D 0x4746d8
int g_4746d8[5] = {1, 2, 3, 4, 5};

// GLOBAL: STUNTGP_D3D 0x4746ec
int g_4746ec[5] = {6, 7, 8, 9, 10};

// Engine: a low idle layer that fades out by 4096 revs and the main layer, both pitched by the revs.
// FUNCTION: STUNTGP_D3D 0x41ba40
void FUN_41ba40()
{
    float freq = (float)fabs(g_4d5bb8->unk1cfc) * 4.0f + 11025.0f;
    if (freq > 81900.0f)
    {
        freq = 81900.0f;
    }
    float load = (g_4d5bb8->unk1cfc / g_4d5bb8->unk045c * 0.6f + g_4d5bb8->unk1cf8 * 0.4f + 0.2f) * 255.0f;
    if (g_4746c0 == 100 && g_4d5bb8->unk1cfc < 4096.0f)
    {
        float k = g_4d5bb8->unk1cfc / 4096.0f;
        k *= 0.5f;
        load = (k + 0.5f) * load;
        float vol = ((4096.0f - g_4d5bb8->unk1cfc) / 4096.0f + 0.5f) * 100.0f;
        if (vol > 255.0f)
        {
            vol = 255.0f;
        }
        vol *= 100.0f / 255.0f;
        freq += 14000.0f;
        if (freq > 81900.0f)
        {
            freq = 81900.0f;
        }
        if (!g_4d5bb8->unk238c)
        {
            FUN_4614a0(g_4746ec[g_4d5bb8->race.unk80[2]], 1, (int)freq, (int)vol, (Vec4 *)&g_4d5bb8->posX,
                       &g_4d5bb8->unk1c8c, 0, &g_4d5bb8->unk238c);
        }
        else
        {
            FUN_461850(&g_4d5bb8->unk238c, (int)freq, (int)vol, (Vec4 *)&g_4d5bb8->posX, &g_4d5bb8->unk1c8c);
        }
    }
    else
    {
        FUN_460d90(&g_4d5bb8->unk238c);
    }
    if (load < 63.0f)
    {
        load = 63.0f;
    }
    float vol = load * 100.0f;
    vol *= 1.0f / 255.0f;
    if (vol > 100.0f)
    {
        vol = 100.0f;
    }
    if (!g_4d5bb8->unk2390)
    {
        FUN_4614a0(g_4746d8[g_4d5bb8->race.unk80[1]], 1, (int)freq, (int)vol, (Vec4 *)&g_4d5bb8->posX,
                   &g_4d5bb8->unk1c8c, 0, &g_4d5bb8->unk2390);
        return;
    }
    FUN_461850(&g_4d5bb8->unk2390, (int)freq, (int)vol, (Vec4 *)&g_4d5bb8->posX, &g_4d5bb8->unk1c8c);
}

// GLOBAL: STUNTGP_D3D 0x570ac8
float g_570ac8;

// GLOBAL: STUNTGP_D3D 0x570ad0
int g_570ad0;

// GLOBAL: STUNTGP_D3D 0x570ad4
unsigned int g_570ad4;

// Brake squeal while nearly stopped: sounds whenever unk1cf4 moves, then fades out over 8 ticks.
// FUNCTION: STUNTGP_D3D 0x41bc80
void FUN_41bc80()
{
    if (FUN_402590(g_4d5bb8))
    {
        if (g_4d5bb8->unk1cf0 <= 500.0f / 60.0f && (float)fabs(g_570ac8 - g_4d5bb8->unk1cf4) >= 0.1f)
        {
            if (!g_570ad0)
            {
                FUN_4614a0(0x20, 1, 0, 0x30, (Vec4 *)&g_4d5bb8->posX, &g_4d5bb8->unk1c8c, 0, &g_570ad0);
            }
            else if (g_570ac8 < g_4d5bb8->unk1cf4)
            {
                FUN_461850(&g_570ad0, 0x4800, 0x30, (Vec4 *)&g_4d5bb8->posX, NULL);
            }
            else
            {
                FUN_461850(&g_570ad0, 0, 0x30, (Vec4 *)&g_4d5bb8->posX, NULL);
            }
            g_570ad4 = 8;
            g_570ac8 = g_4d5bb8->unk1cf4;
            return;
        }
        if (g_570ad4 > 0)
        {
            if (g_570ad0)
            {
                FUN_461850(&g_570ad0, 0, g_570ad4 * 48 / 8, (Vec4 *)&g_4d5bb8->posX, NULL);
            }
            g_570ad4--;
            g_570ac8 = g_4d5bb8->unk1cf4;
            return;
        }
        if (g_570ad0)
        {
            FUN_460d90(&g_570ad0);
        }
        g_570ac8 = g_4d5bb8->unk1cf4;
    }
}

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

void FUN_42b7f0(Scene *scene, Camera *camera, int arg);

// Draws the car's unk26b4 scene from the car's own camera, then puts it back at unk26b0's position.
// FUNCTION: STUNTGP_D3D 0x41c420
void FUN_41c420()
{
    if (g_4d5bb8->unk3928)
    {
        Camera cam = g_4864e8;
        cam.pos = g_4d5bb8->unk3934;
        cam.target = g_4d5bb8->unk3954;
        cam.up = g_4d5bb8->unk3944;
        cam.scale.x = g_4d5bb8->unk392c;
        cam.scale.y = g_4d5bb8->unk392c;
        cam.scale.z = g_4d5bb8->unk392c;
        cam.target.x += cam.pos.x;
        cam.target.y += cam.pos.y;
        cam.target.z += cam.pos.z;
        Scene *scene = g_4d5bb8->unk26b4;
        scene->verts[3] = (scene->verts[3] & 0xf7) | 0x70;
        FUN_42b7f0(scene, &cam, 0);
        *(Vec4 *)g_4d5bb8->unk26b4->unk10 = *(Vec4 *)g_4d5bb8->unk26b0->unk10;
    }
}

// One-quad mesh scene in g_636418[1]: the face, its four UVs and transform.
// GLOBAL: STUNTGP_D3D 0x4747d8
MeshUv g_4747d8[4] = {
    {1.0f, 0.0f, 0, 0x37, 0x3737},
    {0.0f, 0.0f, 1, 0x37, 0x3737},
    {1.0f, 2.0f, 2, 0x37, 0x3737},
    {0.0f, 2.0f, 3, 0x37, 0x3737},
};

// GLOBAL: STUNTGP_D3D 0x474818
MeshFace g_474818 = {4, 5, 0x70, 0x50, 0, 0};

// GLOBAL: STUNTGP_D3D 0x474820
Camera g_474820 = {{0.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, 0, NULL, NULL, 0};

// GLOBAL: STUNTGP_D3D 0x570ad8
Vec4 g_570ad8;

// GLOBAL: STUNTGP_D3D 0x5712d8
DWORD *g_5712d8[2];

// GLOBAL: STUNTGP_D3D 0x5712e0
DWORD g_5712e0[4];

// GLOBAL: STUNTGP_D3D 0x5712fc
char *g_5712fc;

// GLOBAL: STUNTGP_D3D 0x571300
MeshFace *g_571300;

// GLOBAL: STUNTGP_D3D 0x571304
WORD *g_571304;

// GLOBAL: STUNTGP_D3D 0x571308
Vec4 *g_571308;

// GLOBAL: STUNTGP_D3D 0x57130c
MeshUv *g_57130c;

// GLOBAL: STUNTGP_D3D 0x571310
ObjectDef *g_571310;

// GLOBAL: STUNTGP_D3D 0x571314
Scene *g_571314;

// FUNCTION: STUNTGP_D3D 0x41c530
void FUN_41c530()
{
    g_571300 = (MeshFace *)Mem_Alloc(0x400, 0);
    g_571304 = (WORD *)Mem_Alloc(0x400, 0);
    g_571308 = (Vec4 *)Mem_Alloc(0x2000, 0);
    g_57130c = (MeshUv *)Mem_Alloc(0x2000, 0);
    g_571310 = (ObjectDef *)Mem_Alloc(0x40, 0);
    g_571314 = (Scene *)Mem_Alloc(0x68, 0);
    g_571300[0] = g_474818;
    memcpy(g_57130c, g_4747d8, sizeof(g_4747d8));
    g_571308[0].x = 0.0f;
    g_571308[0].y = 0.0f;
    g_571308[0].z = -50.0f;
    g_571308[1].x = 0.0f;
    g_571308[1].y = 0.0f;
    g_571308[1].z = 50.0f;
    g_571308[2].x = 100.0f;
    g_571308[2].y = 0.0f;
    g_571308[2].z = -50.0f;
    g_571308[3].x = 100.0f;
    g_571308[3].y = 0.0f;
    g_571308[3].z = 50.0f;
    memset(g_571310, 0, sizeof(ObjectDef));
    g_571310->visible = 1;
    g_571310->flags = 0;
    g_571310->unk04 = 0;
    *(WORD *)g_571310->unk06 = 0;
    g_571310->matrix = (Vec4 *)&g_474820;
    *(WORD *)(g_571310->unk0c + 0x14) = 0;
    *(WORD *)(g_571310->unk0c + 0x16) = 0;
    g_571310->vertCount = 0;
    g_571310->unk26 = 0;
    g_571310->pointCount = 0;
    g_571310->unk2c = (BYTE *)g_57130c;
    g_571310->points = g_571308;
    g_571310->verts = (BYTE *)g_571300;
    *(DWORD *)(g_571310->unk0c + 4) = 0;
    *(DWORD *)(g_571310->unk0c + 8) = 0;
    *(DWORD *)(g_571310->unk0c + 0xc) = 0;
    g_636418[1].scene = g_571314;
    g_5712d8[0] = g_5712e0;
    g_5712e0[0] = 0;
    g_5712e0[1] = 0;
    g_5712e0[2] = 0;
    g_570ad8.x = 0.0f;
    g_570ad8.y = 1.0f;
    g_570ad8.z = 0.0f;
    memset(g_571314, 0, sizeof(Scene));
    *(WORD *)g_571314->unk00 = 0;
    g_571314->flags = 1;
    g_571314->camera = NULL;
    *(DWORD *)(g_571314->unk10 + 0) = 0;
    *(DWORD *)(g_571314->unk10 + 4) = 0;
    *(DWORD *)(g_571314->unk10 + 8) = 0;
    *(WORD *)(g_571314->unk10 + 0x10) = 0;
    *(WORD *)(g_571314->unk10 + 0x12) = 0;
    g_571314->objectCount = 1;
    g_571314->unk28 = (SceneEntry *)&g_570ad8;
    g_571314->verts = (BYTE *)g_571300;
    g_571314->unk30 = (BYTE *)g_57130c;
    g_571314->points = g_571308;
    g_571314->unk38 = (BYTE *)g_571304;
    g_571314->matrices = (BYTE *)&g_474820;
    g_571314->unk40 = (DWORD *)g_5712d8;
    g_571314->view = (SceneView *)g_571310;
    g_571314->lods[0] = g_571310;
    g_571314->lods[1] = g_571310;
    g_571314->lods[2] = g_571310;
    g_571314->lods[3] = g_571310;
    g_571314->maxLod = 0;
    g_571314->lod = 0;
    g_571314->textures = &g_5712fc;
}

// FUNCTION: STUNTGP_D3D 0x41c710
void FUN_41c710()
{
    g_636418[1].scene = NULL;
}

void FUN_431ff0(D3DCOLOR color, float x, float y, float z);

// Projects p through g_636418[3]'s transform and draws a dot there when it is in front of the camera.
// FUNCTION: STUNTGP_D3D 0x41c720
void FUN_41c720(Vec4 *p, D3DCOLOR color)
{
    float m[16];
    FUN_44fbd0(g_636418[3].scene, g_636418[3].scene->lods[0], m);
    float z = m[2] * p->x + m[6] * p->y + m[10] * p->z + m[14];
    if (z > 0.0f)
    {
        float inv = 1.0f / (z + 1.0f);
        FUN_431ff0(color,
                   (m[0] * p->x + m[4] * p->y + m[8] * p->z + m[12]) * g_61c3e8[0] * g_576b9c * inv + g_576b94,
                   (m[1] * p->x + m[5] * p->y + m[9] * p->z + m[13]) * g_61c3e8[5] * g_576ba0 * inv + g_576b98,
                   1.0f);
    }
}

extern DWORD g_5712f4;

// Builds the quad for skid point i: two points either side of its centre line at each end,
// welded to the previous quad when close enough, faded out otherwise.
// FUNCTION: STUNTGP_D3D 0x41cb40
void FUN_41cb40(SkidMark *skid, int i, int unused)
{
    SkidPoint *p = &skid->points[i];
    ObjectDef *obj = g_571314->lods[0];
    Vec4 *pts = obj->points;
    Vec4 *v = &pts[p->index];
    MeshUv *uv = (MeshUv *)obj->unk2c + p->index;
    Vec4 *prev = &pts[skid->points[(i - 1) & 0x3f].index];
    Vec4 c;
    c.x = g_4d5bb8->axisY.z * p->dir.y - p->dir.z * g_4d5bb8->axisY.y;
    c.y = p->dir.z * g_4d5bb8->axisY.x - g_4d5bb8->axisY.z * p->dir.x;
    c.z = g_4d5bb8->axisY.y * p->dir.x - g_4d5bb8->axisY.x * p->dir.y;
    Vec3_Normalize(&c.x);
    c.x = c.x * 25.0f;
    c.y = c.y * 25.0f;
    c.z = c.z * 25.0f;
    v[0].x = c.x + p->a.x;
    v[0].y = c.y + p->a.y;
    v[0].z = c.z + p->a.z;
    v[1].x = p->a.x - c.x;
    v[1].y = p->a.y - c.y;
    v[1].z = p->a.z - c.z;
    v[2].x = c.x + p->b.x;
    v[2].y = c.y + p->b.y;
    v[2].z = c.z + p->b.z;
    skid->unk0c = uv;
    v[3].x = p->b.x - c.x;
    v[3].y = p->b.y - c.y;
    v[3].z = p->b.z - c.z;
    ((MeshFace *)obj->verts)[obj->vertCount].unk01 = 5;
    float dx = v[0].x - prev[2].x;
    float dy = v[0].y - prev[2].y;
    float dz = v[0].z - prev[2].z;
    if (dx * dx + dy * dy + dz * dz < 400.0f)
    {
        v[0] = prev[2];
        v[1] = prev[3];
    }
    else
    {
        ((BYTE *)&uv[0].color)[3] = 0;
        ((BYTE *)&uv[1].color)[3] = 0;
    }
    if (g_5712f4 >= 0x7f)
    {
        g_5712f4 = 0x7f;
    }
    obj->vertCount = (WORD)g_5712f4;
    obj->unk26 = (WORD)(g_5712f4 * 4);
    obj->pointCount = (WORD)(g_5712f4 * 4);
}

// FUNCTION: STUNTGP_D3D 0x41d9c0
void FUN_41d9c0(int value)
{
    if (value - g_4d5bb8->unk23ac <= 15)
    {
        if (g_4d5bb8->unk23a8 < g_4d5bb8->unk23ac)
        {
            g_4d5bb8->unk23a8 = g_4d5bb8->unk23ac;
        }
        g_4d5bb8->unk23ac = value;
    }
}
