#include "GameUpdate.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../../gametext.h"
#include "../../vecmath.h"
#include "game_state.h"

extern float g_482678;
extern float g_48267c;
extern float g_482680;

void FUN_442cf0(int a, char *text, Car *car, int b, int c);
void FUN_401d70(float *v, float scale);
void FUN_405c80();
void FUN_406190();
void FUN_406270();
void FUN_408000();
void FUN_4081d0();
void FUN_408d80();
void FUN_40d790();
void FUN_40fc90();
void FUN_410b30();
void FUN_410df0();
void FUN_410f80();
void FUN_411150();
void FUN_411290();
void FUN_411420();
void FUN_412670();
void FUN_413330();
void FUN_4137b0();
void FUN_413da0();
void FUN_414370();
void FUN_414460();
void FUN_414710();
void FUN_414b30();
void FUN_414c60();
void FUN_414f90();
void FUN_4152d0();
void FUN_415640();
void FUN_415770();
void FUN_415880();
void FUN_416800();
void FUN_416a80();
void FUN_416f30();
void FUN_4173e0();
void FUN_417800();
void FUN_417ca0();
void FUN_417f10();
void FUN_418320();
void FUN_418580();
void FUN_418660(Car *car);
void FUN_4186c0();
int FUN_418760(Car *car);
void FUN_4187a0();
void FUN_4187c0();
void FUN_418830();
void FUN_419310();
void FUN_419910();
void FUN_419960();
void FUN_419970();
void FUN_41ac30(Car *car);
void FUN_41bea0();
void FUN_41bf20();
void FUN_41d140();
void FUN_41e210();
void FUN_443700(Car *car);
void FUN_401220(int type, int mode, unsigned int points);
void FUN_414d80(Car *car);
void FUN_414c50(Car *car);
void FUN_414ef0(Car *car);
void FUN_4152c0(Car *car);

CameraPath *FUN_428800(int id);

extern int g_60d688[37];
extern DWORD g_61297c;
extern int g_60f02c[0x96];
extern CameraPath *g_571328;
extern float g_60e1f0[0x80];
extern float g_60e3f0[0x80];

// GLOBAL: STUNTGP_D3D 0x5712f0
DWORD g_5712f0;

// GLOBAL: STUNTGP_D3D 0x5712f4
DWORD g_5712f4;

// GLOBAL: STUNTGP_D3D 0x5712f8
int g_5712f8;

// STUB: STUNTGP_D3D 0x401220
void FUN_401220(int type, int mode, unsigned int points)
{
}

// Adds the scaled gravity vector unless the velocity is already above the cap.
// STUB: STUNTGP_D3D 0x405c80
void FUN_405c80()
{
}

// STUB: STUNTGP_D3D 0x406190
void FUN_406190()
{
}

// FUNCTION: STUNTGP_D3D 0x406270
void FUN_406270()
{
    Car *car = g_4d5bb8;
    if (car->unk1fd8)
    {
        float speed = car->unk1cf0;
        for (int i = 0; i < 4; i++)
        {
            car->wheels[i].unk04 += (speed - car->wheels[i].unk04) * 0.5f;
        }
    }
}

// STUB: STUNTGP_D3D 0x408000
void FUN_408000()
{
}

// STUB: STUNTGP_D3D 0x4081d0
void FUN_4081d0()
{
}

// FUNCTION: STUNTGP_D3D 0x408d80
void FUN_408d80()
{
    Car *car = g_4d5bb8;
    if (car->unk257c != 0.0f)
    {
        car->unk2580--;
        car->unk257c = 0.0f;
    }
}

// STUB: STUNTGP_D3D 0x40d790
void FUN_40d790()
{
}

// STUB: STUNTGP_D3D 0x40fc90
void FUN_40fc90()
{
}

// STUB: STUNTGP_D3D 0x410b30
void FUN_410b30()
{
}

// STUB: STUNTGP_D3D 0x410df0
void FUN_410df0()
{
}

// STUB: STUNTGP_D3D 0x410f80
void FUN_410f80()
{
}

// STUB: STUNTGP_D3D 0x411150
void FUN_411150()
{
}

// FUNCTION: STUNTGP_D3D 0x411280
void FUN_411280(Car *car)
{
    car->unk71e0 = 0;
}

// FUNCTION: STUNTGP_D3D 0x411290
void FUN_411290()
{
    if (g_4d5bb8->unk1fd0 >= 0.99f)
    {
        if (g_4d5bb8->unk71e0 > 540)
        {
            FUN_401220(5, 1, g_60d688[23]);
            FUN_442cf0(180, g_6127a0[89], g_4d5bb8, 2, 0);
        }
        else if (g_4d5bb8->unk71e0 > 300)
        {
            FUN_401220(5, 1, g_60d688[24]);
            FUN_442cf0(180, g_6127a0[88], g_4d5bb8, 2, 0);
        }
        FUN_411280(g_4d5bb8);
    }
    else
    {
        g_4d5bb8->unk71e0++;
    }
}

// FUNCTION: STUNTGP_D3D 0x411410
void FUN_411410(Car *car)
{
    car->unk71e4 = 0;
}

// FUNCTION: STUNTGP_D3D 0x411420
void FUN_411420()
{
    if (g_4d5bb8->unk236c && g_4d5bb8->unk1cf0 > 500.0f / 60.0f)
    {
        g_4d5bb8->unk71e4++;
        return;
    }
    if (g_4d5bb8->unk71e4 > 120)
    {
        FUN_401220(5, 1, g_60d688[27]);
        FUN_442cf0(180, g_6127a0[76], g_4d5bb8, 2, 0);
    }
    FUN_411410(g_4d5bb8);
}

// STUB: STUNTGP_D3D 0x412670
void FUN_412670()
{
}

// Damped spring, stepped four times per tick.
// FUNCTION: STUNTGP_D3D 0x413330
void FUN_413330()
{
    for (int i = 0; i < 4; i++)
    {
        float v[4];
        memcpy(v, g_4d5bb8->unk2308, sizeof(v));
        v[0] *= 0.033333335f;
        v[1] *= 0.033333335f;
        v[2] *= 0.033333335f;
        g_4d5bb8->unk2328 -= v[0];
        g_4d5bb8->unk232c -= v[1];
        g_4d5bb8->unk2330 -= v[2];
        g_4d5bb8->unk2308[0] = g_4d5bb8->unk2328 + g_4d5bb8->unk2308[0];
        g_4d5bb8->unk2308[1] = g_4d5bb8->unk232c + g_4d5bb8->unk2308[1];
        g_4d5bb8->unk2308[2] = g_4d5bb8->unk2330 + g_4d5bb8->unk2308[2];
        g_4d5bb8->unk2328 *= 0.9f;
        g_4d5bb8->unk232c *= 0.9f;
        g_4d5bb8->unk2330 *= 0.9f;
    }
}

// STUB: STUNTGP_D3D 0x4137b0
void FUN_4137b0()
{
}

// STUB: STUNTGP_D3D 0x4166f0
void FUN_4166f0()
{
}

// FUNCTION: STUNTGP_D3D 0x413da0
void FUN_413da0()
{
    g_4d5bb8->unk3134 = 1;
    ModelPart *part = g_4d5bb8->unk26b0->parts[g_4d5bb8->unk26b0->current];
    part->meshes[11].visible = 1;
    part->meshes[12].visible = 1;
    part->meshes[13].visible = 1;
    part->meshes[14].visible = 1;
    part->meshes[15].visible = 1;
    part->meshes[16].visible = 1;
    g_4d5bb8->unk3928 = g_4d5bb8->unk3924;
    FUN_4166f0();
    g_4d5bb8->unk328c.unk13c = 1;
    g_4d5bb8->unk33cc.unk13c = 1;
}

// Spins each wheel by the distance it rolled this tick.
// FUNCTION: STUNTGP_D3D 0x414370
void FUN_414370()
{
    for (int i = 0; i < 4; i++)
    {
        float angle = -(g_4d5bb8->wheels[i].unk04 * 180.0f / (g_4d5bb8->unkcb8[i].x * 3.1415927f)) +
                      g_4d5bb8->wheels[i].unk94;
        g_4d5bb8->wheels[i].unk90 = g_4d5bb8->wheels[i].unk94;
        g_4d5bb8->wheels[i].unk94 = angle;
        Matrix_RotationX(g_4d5bb8->wheelMatrix[i], angle);
    }
}

// STUB: STUNTGP_D3D 0x414460
void FUN_414460()
{
}

// STUB: STUNTGP_D3D 0x414710
void FUN_414710()
{
}

// STUB: STUNTGP_D3D 0x414b30
void FUN_414b30()
{
}

// STUB: STUNTGP_D3D 0x414c60
void FUN_414c60()
{
}

// STUB: STUNTGP_D3D 0x414f90
void FUN_414f90()
{
}

// STUB: STUNTGP_D3D 0x4152d0
void FUN_4152d0()
{
}

// Fades the light mesh brightness down by 32 a tick, holding at 120 while lit.
// FUNCTION: STUNTGP_D3D 0x415640
void FUN_415640()
{
    if (g_4d5bb8->unk28a8 != 0)
    {
        g_4d5bb8->unk28a8 -= 32;
        if (g_4d5bb8->unk28a8 < 0)
        {
            g_4d5bb8->unk28a8 = 0;
        }
    }
    if (g_4d5bb8->unk28a0 == 1 && g_4d5bb8->unk28a8 < 120)
    {
        g_4d5bb8->unk28a8 = 120;
    }
    int level = g_4d5bb8->unk28a8;
    ModelMesh *mesh = &g_4d5bb8->unk26b0->parts[g_4d5bb8->unk26b0->current]->meshes[5];
    mesh->visible = level != 0;
    if (level != g_4d5bb8->unk28a4)
    {
        g_4d5bb8->unk28a4 = level;
        BYTE *vert = mesh->verts;
        for (DWORD i = 0; i < mesh->vertCount; i++)
        {
            vert[2] = level;
            vert[3] = 0x60;
            vert += 8;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x4156e0
void FUN_4156e0(Car *car)
{
    if (car->unk28a0 != 1)
    {
        car->unk28a0 = 1;
        FUN_414ef0(car);
        FUN_4152c0(car);
        for (int i = 0; i < 4; i++)
        {
            ModelPart *part = g_4d5bb8->unk26b0->parts[i];
            part->meshes[10].visible = 1;
            part->meshes[5].visible = 1;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x415730
void FUN_415730(Car *car)
{
    if (car->unk28a0 != 0)
    {
        g_4d5bb8->unk28a0 = 0;
        for (int i = 0; i < 4; i++)
        {
            ModelPart *part = g_4d5bb8->unk26b0->parts[i];
            part->meshes[10].visible = 0;
            part->meshes[5].visible = 0;
        }
    }
}

// Switches the car lights from the track's light mask at the car's path position.
// FUNCTION: STUNTGP_D3D 0x415770
void FUN_415770()
{
    if (g_4d5bb8->unk26b0->meshCount > 10)
    {
        DWORD count = g_624474->count;
        int pos = g_4d5bb8->unk24a4;
        DWORD wrapped;
        if (pos < 0)
        {
            wrapped = count - (DWORD)-pos % count;
        }
        else
        {
            wrapped = (DWORD)pos % count;
        }
        DWORD index = (wrapped << 7) / count;
        if (g_60e1f0[index] != 0.0f)
        {
            FUN_4156e0(g_4d5bb8);
        }
        else
        {
            FUN_415730(g_4d5bb8);
        }
        g_4d5bb8->unk7684 = g_60e3f0[index];
    }
}

// STUB: STUNTGP_D3D 0x415880
void FUN_415880()
{
}

// STUB: STUNTGP_D3D 0x416800
void FUN_416800()
{
}

// STUB: STUNTGP_D3D 0x416a80
void FUN_416a80()
{
}

// STUB: STUNTGP_D3D 0x416f30
void FUN_416f30()
{
}

// STUB: STUNTGP_D3D 0x4173e0
void FUN_4173e0()
{
}

// STUB: STUNTGP_D3D 0x417800
void FUN_417800()
{
}

// STUB: STUNTGP_D3D 0x417ca0
void FUN_417ca0()
{
}

// STUB: STUNTGP_D3D 0x417f10
void FUN_417f10()
{
}

// STUB: STUNTGP_D3D 0x418320
void FUN_418320()
{
}

// FUNCTION: STUNTGP_D3D 0x418580
void FUN_418580()
{
    g_4d5bb8->unk261c = g_4d5bb8->unk22c;
    g_4d5bb8->unk2618 = g_4d5bb8->unk2270 * g_4d5bb8->unkf7c + g_4d5bb8->unk220;
    if (g_4d5bb8->unk762c == 1)
    {
        g_4d5bb8->unk2618 = 1000.0f;
        g_4d5bb8->unk261c = 30.000002f;
    }
    if (g_4d5bb8->unk7648 == 1 && g_4d5bb8->unk261c > 10.0f)
    {
        g_4d5bb8->unk261c = 10.0f;
    }
    float scale;
    if (!g_4d5bb8->unk1f10)
    {
        scale = 2.0f;
    }
    else
    {
        scale = g_4d5bb8->unk2634;
    }
    for (int i = 0; i < 4; i++)
    {
        g_4d5bb8->wheels[i].unk34 = scale * g_4d5bb8->unkcb8[i].z;
        g_4d5bb8->wheels[i].unk38 = scale * g_4d5bb8->unkcb8[i].w;
    }
    g_4d5bb8->unk1f08 = g_4d5bb8->unk2634 * g_4d5bb8->unk1f08;
}

// FUNCTION: STUNTGP_D3D 0x418660
void FUN_418660(Car *car)
{
    char text[64];
    // STRING: STUNTGP_D3D 0x474668
    sprintf(text, "%s %s\n", g_60f050[car - g_49a1f8].name, g_6127a0[17]);
    FUN_442cf0(180, text, car, 1, 0);
}

// FUNCTION: STUNTGP_D3D 0x4186c0
void FUN_4186c0()
{
    if (!g_4d5bb8->unk24e0 && !g_4d5bb8->unk24e8)
    {
        g_4d5bb8->unk24e8 = 1;
        g_4d5bb8->unk24e4 = 0;
        FUN_443700(g_4d5bb8);
        if (g_60f2b0 == 2)
        {
            FUN_418660(g_4d5bb8);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x418760
int FUN_418760(Car *car)
{
    if (car->unk2570 <= 0.0f && (float)fabs(car->unk1cf0) < 1.6666666f)
    {
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x4187a0
void FUN_4187a0()
{
    if (g_60f2b0 == 3 && FUN_418760(g_4d5bb8) == 1)
    {
        FUN_4186c0();
    }
}

// Counts frames spent stopped with wheels spinning; gives up after 240.
// FUNCTION: STUNTGP_D3D 0x4187c0
void FUN_4187c0()
{
    Car *car = g_4d5bb8;
    if (fabs(car->unk1cf0) <= 100.0 / 60.0 && car->unk1fd8 == 2)
    {
        for (unsigned int i = 0; i < 4; i++)
        {
            if (fabs(car->wheels[i].unk04) > 1000.0 / 60.0)
            {
                if (++car->unk7680 >= 240)
                {
                    car->unk763c = 1;
                }
                return;
            }
        }
    }
}

// Per-tick update for a car that is not replaying.
// FUNCTION: STUNTGP_D3D 0x418830
void FUN_418830()
{
    if (g_4d5bb8->unk24e0 == 1 || g_4d5bb8->unk24e8 == 1)
    {
        FUN_443700(g_4d5bb8);
    }
    FUN_408d80();
    FUN_413da0();
    FUN_418580();
    FUN_419910();
    FUN_40d790();
    FUN_419310();
    FUN_4081d0();
    FUN_412670();
    FUN_408000();
    FUN_419970();
    FUN_419960();
    FUN_41e210();
    if (g_60f2b0 != 3)
    {
        FUN_410b30();
    }
    if (g_60f2b0 != 4)
    {
        FUN_410df0();
        FUN_410f80();
        FUN_411150();
        FUN_411290();
        FUN_411420();
    }
    FUN_405c80();
    FUN_406190();
    FUN_406270();
    FUN_414710();
    FUN_414370();
    FUN_401d70(g_4d5bb8->unk1c8c, 1.0f);
    FUN_40fc90();
    FUN_4137b0();
    FUN_414460();
    FUN_41ac30(g_4d5bb8);
    FUN_41bea0();
    FUN_413330();
    FUN_415640();
    FUN_415770();
    FUN_414b30();
    FUN_416800();
    FUN_416a80();
    FUN_415880();
    FUN_417ca0();
    FUN_416f30();
    FUN_417800();
    FUN_4173e0();
    FUN_417f10();
    FUN_41d140();
    FUN_414c60();
    FUN_414f90();
    FUN_4152d0();
    FUN_41bf20();
    FUN_4187a0();
    FUN_4187c0();
    FUN_418320();
}

// STUB: STUNTGP_D3D 0x419310
void FUN_419310()
{
}

// FUNCTION: STUNTGP_D3D 0x419910
void FUN_419910()
{
}

// FUNCTION: STUNTGP_D3D 0x419960
void FUN_419960()
{
}

// FUNCTION: STUNTGP_D3D 0x419970
void FUN_419970()
{
}

// STUB: STUNTGP_D3D 0x41ac30
void FUN_41ac30(Car *car)
{
}

// STUB: STUNTGP_D3D 0x41bea0
void FUN_41bea0()
{
}

// STUB: STUNTGP_D3D 0x41bf20
void FUN_41bf20()
{
}

// STUB: STUNTGP_D3D 0x41cd30
void FUN_41cd30(int wheel)
{
}

// FUNCTION: STUNTGP_D3D 0x41d140
void FUN_41d140()
{
    if (g_61297c < 80)
    {
        return;
    }
    if (g_4d5bb8->unk7268 && *g_4d5bb8->unk7268 == 1)
    {
        return;
    }
    FUN_41cd30(0);
    FUN_41cd30(1);
}

// STUB: STUNTGP_D3D 0x41e210
void FUN_41e210()
{
}

// FUNCTION: STUNTGP_D3D 0x443700
void FUN_443700(Car *car)
{
    if (car->active == 1 && car->unk2278 == 1)
    {
        car->unk2278 = 0;
        car->unk1cf8 = 0;
    }
}

// STUB: STUNTGP_D3D 0x4085e0
void FUN_4085e0()
{
}

// STUB: STUNTGP_D3D 0x408640
void FUN_408640(Car *car, float *pos)
{
}

// STUB: STUNTGP_D3D 0x408710
void FUN_408710()
{
}

// STUB: STUNTGP_D3D 0x40bde0
void FUN_40bde0()
{
}

// STUB: STUNTGP_D3D 0x412bf0
void FUN_412bf0()
{
}

// STUB: STUNTGP_D3D 0x412e80
void FUN_412e80()
{
}

// FUNCTION: STUNTGP_D3D 0x4130d0
void FUN_4130d0(int mode)
{
    if (!g_571328)
    {
        g_571328 = FUN_428800(1);
        if (!g_571328)
        {
            return;
        }
    }
    switch (mode)
    {
    case 1:
        FUN_412bf0();
        break;
    case 2:
        FUN_412e80();
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x414d80
void FUN_414d80(Car *car)
{
    car->unk328c.count = 0;
    car->unk33cc.count = 0;
}

// FUNCTION: STUNTGP_D3D 0x414c50
void FUN_414c50(Car *car)
{
    car->unk391c = 0;
    car->unk3920 = 0;
}

// FUNCTION: STUNTGP_D3D 0x414ef0
void FUN_414ef0(Car *car)
{
    car->unk2d04.count = 0;
    car->unk2f1c.count = 0;
}

// FUNCTION: STUNTGP_D3D 0x4152c0
void FUN_4152c0(Car *car)
{
    car->unk28c0.count = 0;
    car->unk2adc.count = 0;
}

// FUNCTION: STUNTGP_D3D 0x4128f0
void FUN_4128f0(Car *car)
{
    FUN_414d80(car);
    FUN_414c50(car);
    FUN_414ef0(car);
    FUN_4152c0(car);
}

// FUNCTION: STUNTGP_D3D 0x413450
void FUN_413450()
{
    Car *car = g_4d5bb8;
    for (int i = 0; i < 4; i++)
    {
        car->wheels[i].unk00 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x413500
void FUN_413500()
{
    for (int i = 0; i < 6; i++)
    {
        if (g_60f02c[i * 25] == 0)
        {
            g_49a1f8[i].active = 0;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x414f00
void FUN_414f00()
{
    Car *car = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        if (car->active == 1 && car->unk26b0->meshCount >= 23)
        {
            car->unk2d04.pos = *car->unk26b0->parts[0]->meshes[23].matrix;
            car->unk2f1c.pos = *car->unk26b0->parts[0]->meshes[24].matrix;
        }
        car++;
    }
    g_4d5bb8 = g_49a1f8;
}

// FUNCTION: STUNTGP_D3D 0x4150d0
void FUN_4150d0()
{
    Car *car = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        car->unk2ad8 = car->unk28bc = 0;
        if (car->active == 1 && car->unk26b0->meshCount >= 21)
        {
            ModelMesh *mesh = &car->unk26b0->parts[0]->meshes[21];
            car->unk28bc = 1;
            car->unk28c0.pos = *mesh->matrix;
            if (car->unk26b0->meshCount >= 22)
            {
                mesh = &car->unk26b0->parts[0]->meshes[22];
                car->unk2ad8 = 1;
                car->unk2adc.pos = *mesh->matrix;
            }
        }
        car++;
    }
    g_4d5bb8 = g_49a1f8;
}

// FUNCTION: STUNTGP_D3D 0x4162c0
void FUN_4162c0()
{
    Car *car = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        if (car->active == 1)
        {
            car->unk328c.active = 0;
            car->unk33cc.active = 0;
            if (car->unk26b0->meshCount > 19)
            {
                ModelPart *part = car->unk26b0->parts[car->unk26b0->current];
                car->unk328c.active = 1;
                car->unk328c.unk004 = part->meshes[19].matrix[0];
                car->unk328c.unk014 = part->meshes[19].matrix[1];
                if (part->meshes[20].visible == 1 && car->unk26b0->meshCount > 20)
                {
                    car->unk33cc.active = 1;
                    car->unk33cc.unk004 = part->meshes[20].matrix[0];
                    car->unk33cc.unk014 = part->meshes[20].matrix[1];
                }
            }
        }
        car++;
    }
    g_4d5bb8 = g_49a1f8;
}

// Finds the top of mesh 11's points and caches its frame.
// FUNCTION: STUNTGP_D3D 0x417e10
void FUN_417e10()
{
    Car *car = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        if (car->active == 1)
        {
            if (car->unk26b0->meshCount <= 11)
            {
                car->unk3134 = 0;
            }
            else
            {
                ModelPart *part = car->unk26b0->parts[car->unk26b0->current];
                float top = 0.0f;
                DWORD count = part->meshes[11].pointCount;
                Vec4 *points = part->meshes[11].points;
                for (DWORD j = 0; j < count; j++)
                {
                    if (top < points[j].z)
                    {
                        top = points[j].z;
                    }
                }
                car->unk3148 = part->meshes[11].matrix[2];
                car->unk3148.x = -car->unk3148.x;
                car->unk3138 = part->meshes[11].matrix[0];
                car->unk3158 = top * 0.99f;
                car->unk3134 = 1;
            }
        }
        car++;
    }
    g_4d5bb8 = g_49a1f8;
}

// FUNCTION: STUNTGP_D3D 0x419900
void FUN_419900()
{
}

// STUB: STUNTGP_D3D 0x41c9b0
void FUN_41c9b0()
{
}

// FUNCTION: STUNTGP_D3D 0x41d170
void FUN_41d170(SkidMark *skid)
{
    skid->unk00 = 0;
    skid->unk04 = 0;
    skid->unk08 = 0;
}

// FUNCTION: STUNTGP_D3D 0x41d180
void FUN_41d180()
{
    g_5712f8 = 1;
    g_5712f0 = 0;
    g_5712f4 = 1;
    FUN_41c9b0();
    for (int i = 0; i < 4; i++)
    {
        FUN_41d170(&g_4d5bb8->skids[i]);
    }
}

// STUB: STUNTGP_D3D 0x41d300
void FUN_41d300()
{
}
