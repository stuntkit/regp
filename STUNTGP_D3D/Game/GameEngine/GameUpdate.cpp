#include "GameUpdate.h"

#include <cstring>
#include <float.h>
#include <math.h>

#include "../../globals.h"
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

struct SoundZone
{
    int id;           // 0x00
    int unk04;        // 0x04
    float bounds[16]; // 0x08
};

// Entry 0 is the fallback zone; the list ends at id -1.
// GLOBAL: STUNTGP_D3D 0x483f98
SoundZone g_483f98[2] = {
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

struct AnimObject
{
    int type;         // 0x00
    float rotX;       // 0x04
    float rotY;       // 0x08
    float rotZ;       // 0x0c
    int unk10;        // 0x10
    float spinX;      // 0x14
    float spinY;      // 0x18
    float spinZ;      // 0x1c
    BYTE unk20[0x18]; // 0x20
    int angleA;       // 0x38
    int angleB;       // 0x3c
    BYTE unk40[0x8];  // 0x40
};

// GLOBAL: STUNTGP_D3D 0x576cd0
AnimObject g_576cd0[32];

// GLOBAL: STUNTGP_D3D 0x636448
Scene *g_636448;

// 6 entries at 0x49a1f8, 0x7724 bytes each
// GLOBAL: STUNTGP_D3D 0x49a1f8
Car g_49a1f8[6];

// GLOBAL: STUNTGP_D3D 0x4d5bb8
Car *g_4d5bb8;

void FUN_41af50();
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

// STUB: STUNTGP_D3D 0x412910
void FUN_412910()
{
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
    car->unk2304 = 0.0f;
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
    car->unk2304 = 0.0f;
    FUN_4028d0(5);
    FUN_403310(2.09f);
    FUN_402ab0(2.09f);
    g_60f020 = 1;
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

// STUB: STUNTGP_D3D 0x404450
void FUN_404450()
{
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

// STUB: STUNTGP_D3D 0x40dad0
void FUN_40dad0()
{
}

// STUB: STUNTGP_D3D 0x40dd30
void FUN_40dd30()
{
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

// STUB: STUNTGP_D3D 0x415df0
void FUN_415df0()
{
}

// STUB: STUNTGP_D3D 0x40e340
void FUN_40e340()
{
}

// STUB: STUNTGP_D3D 0x418830
void FUN_418830()
{
}

// STUB: STUNTGP_D3D 0x418970
void FUN_418970()
{
}

// STUB: STUNTGP_D3D 0x4189e0
void FUN_4189e0()
{
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

// STUB: STUNTGP_D3D 0x41af50
void FUN_41af50()
{
}

// STUB: STUNTGP_D3D 0x41e2d0
void FUN_41e2d0()
{
}

// STUB: STUNTGP_D3D 0x4278a0
int FUN_4278a0(float *bounds, float *point)
{
    return 0;
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
    delta[0] = obj->spinX * (1.0f / 60.0f);
    delta[1] = obj->spinY * (1.0f / 60.0f);
    delta[2] = obj->spinZ * (1.0f / 60.0f);
    obj->rotX = x = obj->rotX + delta[0];
    obj->rotY = y = obj->rotY + delta[1];
    obj->rotZ = z = obj->rotZ + delta[2];
    if (x < 0.0f)
    {
        obj->rotX = x + 360.0f;
    }
    else if (x > 360.0f)
    {
        obj->rotX = x - 360.0f;
    }
    if (y < 0.0f)
    {
        obj->rotY = y + 360.0f;
    }
    else if (y > 360.0f)
    {
        obj->rotY = y - 360.0f;
    }
    if (z < 0.0f)
    {
        obj->rotZ = z + 360.0f;
    }
    else if (z > 360.0f)
    {
        obj->rotZ = z - 360.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x427140
void FUN_427140()
{
    if (g_636448 && g_636448->objectCount > 1)
    {
        ObjectDef *def = g_636448->objects;
        AnimObject *obj = g_576cd0;
        DWORD count = g_636448->objectCount;
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

// STUB: STUNTGP_D3D 0x443a80
void FUN_443a80()
{
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

// STUB: STUNTGP_D3D 0x45e1d0
void FUN_45e1d0()
{
}

// STUB: STUNTGP_D3D 0x45f8f0
void FUN_45f8f0(int a, int b)
{
}

// --- sound ---


// STUB: STUNTGP_D3D 0x41bdd0
void FUN_41bdd0()
{
}
