#include "GameUpdate.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../../gametext.h"

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

// Adds the scaled gravity vector unless the velocity is already above the cap.
// FUNCTION: STUNTGP_D3D 0x401d70
void FUN_401d70(float *v, float scale)
{
    float t[4];
    if (v[0] * v[0] + v[1] * v[1] + v[2] * v[2] <= 27777.777f)
    {
        t[0] = g_482678 * scale;
        t[1] = g_48267c * scale;
        t[2] = g_482680 * scale;
        v[0] += t[0];
        v[1] += t[1];
        v[2] += t[2];
    }
}

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

// STUB: STUNTGP_D3D 0x411290
void FUN_411290()
{
}

// STUB: STUNTGP_D3D 0x411420
void FUN_411420()
{
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

// STUB: STUNTGP_D3D 0x413da0
void FUN_413da0()
{
}

// STUB: STUNTGP_D3D 0x414370
void FUN_414370()
{
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

// STUB: STUNTGP_D3D 0x415640
void FUN_415640()
{
}

// STUB: STUNTGP_D3D 0x415770
void FUN_415770()
{
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

// STUB: STUNTGP_D3D 0x41d140
void FUN_41d140()
{
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

// STUB: STUNTGP_D3D 0x4130d0
void FUN_4130d0(int mode)
{
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

// STUB: STUNTGP_D3D 0x413500
void FUN_413500()
{
}

// STUB: STUNTGP_D3D 0x414f00
void FUN_414f00()
{
}

// STUB: STUNTGP_D3D 0x4150d0
void FUN_4150d0()
{
}

// STUB: STUNTGP_D3D 0x4162c0
void FUN_4162c0()
{
}

// STUB: STUNTGP_D3D 0x417e10
void FUN_417e10()
{
}

// FUNCTION: STUNTGP_D3D 0x419900
void FUN_419900()
{
}

// STUB: STUNTGP_D3D 0x41d180
void FUN_41d180()
{
}

// STUB: STUNTGP_D3D 0x41d300
void FUN_41d300()
{
}
