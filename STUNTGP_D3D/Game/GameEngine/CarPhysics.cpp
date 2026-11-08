#include "GameUpdate.h"
#include "GameSetup.h"

#include <math.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../gametext.h"
#include "../../random.h"
#include "../../vecmath.h"
#include "game_state.h"

extern float g_482678;
extern float g_48267c;
extern float g_482680;
extern float g_482688;
extern float g_48268c;
extern float g_482690;
extern int g_60eff0;
extern DWORD g_60eff8;
extern DWORD g_60effc;
extern DWORD g_60f000[4];
extern int g_60f2b4;
extern int g_576be0;
extern float g_60f010;
extern float g_60f2d0[31];


void Matrix_Multiply3(float *a, float *b);
int FUN_442fb0();
void FUN_443de0();
void FUN_40e360(Car *sub);
void FUN_40e380(Car *sub);

void FUN_442cf0(int a, char *text, Car *car, int b, int c);
void FUN_401d70(float *v, float scale);
void FUN_405c80();
void FUN_40d090();
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
void FUN_414d80(Car *car);
void FUN_414c50(Car *car);
void FUN_414ef0(Car *car);
void FUN_4152c0(Car *car);

CameraPath *FUN_428800(int id);
DWORD FUN_42b580(Vec4 *pos);
float FUN_42f1c0(float range);
void FUN_4482a0(DWORD frames, DWORD *digits);

extern int g_60d688[37];
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

// Returns the player slot driving this car, or NULL for AI cars.
// FUNCTION: STUNTGP_D3D 0x402590
GameSlot *FUN_402590(Car *car)
{
    for (int i = 0; i < 4; i++)
    {
        if (g_498248[i].active == 1 && car == g_498248[i].data)
        {
            return &g_498248[i];
        }
    }
    return NULL;
}

void FUN_404310(Car *car);

// Clones slot 0 into the other player slots and enables those with an active car.
// FUNCTION: STUNTGP_D3D 0x4025d0
void FUN_4025d0()
{
    for (int i = 1; i < 4; i++)
    {
        Car *car = &g_49a1f8[i];
        g_4722d0 = &g_498248[i];
        g_498248[i] = g_498248[0];
        g_498248[i].active = 0;
        g_498248[i].data = car;
        FUN_404310(car);
    }
    if (g_576be0 == 2 || g_576be0 == 1)
    {
        if (g_498248[1].data->active == 1)
        {
            g_498248[1].active = 1;
        }
    }
    else if (g_576be0 == 3)
    {
        if (g_498248[1].data->active == 1)
        {
            g_498248[1].active = 1;
        }
        if (g_498248[2].data->active == 1)
        {
            g_498248[2].active = 1;
        }
    }
    else if (g_576be0 == 4)
    {
        if (g_498248[1].data->active == 1)
        {
            g_498248[1].active = 1;
        }
        if (g_498248[2].data->active == 1)
        {
            g_498248[2].active = 1;
        }
        if (g_498248[3].data->active == 1)
        {
            g_498248[3].active = 1;
        }
    }
    FUN_402580();
}

// FUNCTION: STUNTGP_D3D 0x4026e0
void FUN_4026e0(int slot, Car *car)
{
    g_498248[slot].data = car;
    g_498248[slot].active = 1;
    FUN_404310(car);
}
// Hands the race's player cars to the first g_576be0 player slots.
// FUNCTION: STUNTGP_D3D 0x402710
void FUN_402710()
{
    for (int i = 0; i < 4; i++)
    {
        g_498248[i].active = 0;
    }
    switch (g_576be0)
    {
    case 0:
        FUN_4026e0(0, &g_49a1f8[g_60d730.unk024[0]]);
        break;
    case 1:
    case 2:
        FUN_4026e0(0, &g_49a1f8[g_60d730.unk024[0]]);
        FUN_4026e0(1, &g_49a1f8[g_60d730.unk024[1]]);
        break;
    case 3:
        FUN_4026e0(0, &g_49a1f8[g_60d730.unk024[0]]);
        FUN_4026e0(1, &g_49a1f8[g_60d730.unk024[1]]);
        FUN_4026e0(2, &g_49a1f8[g_60d730.unk024[2]]);
        break;
    case 4:
        FUN_4026e0(0, &g_49a1f8[g_60d730.unk024[0]]);
        FUN_4026e0(1, &g_49a1f8[g_60d730.unk024[1]]);
        FUN_4026e0(2, &g_49a1f8[g_60d730.unk024[2]]);
        FUN_4026e0(3, &g_49a1f8[g_60d730.unk024[3]]);
        break;
    }
    FUN_402580();
}


extern int g_49a164;
extern CameraPath *g_49a158;
extern CameraPath *g_49a15c;
extern CameraPath *g_49a160;
extern float g_49a16c;
extern float g_49a170;
extern float g_49a174;
void FUN_4064b0();

// FUNCTION: STUNTGP_D3D 0x405260
void FUN_405260()
{
    if (g_49a164 != 1)
    {
        g_49a164 = 1;
        g_49a16c = 0.0f;
        g_49a170 = 0.0f;
        g_49a174 = 0.0f;
        g_49a158 = FUN_428800(3);
        g_49a15c = FUN_428800(4);
        g_49a160 = FUN_428800(5);
        if (g_49a158 == NULL)
        {
            g_49a158 = FUN_428800(1);
        }
        if (g_49a15c == NULL)
        {
            g_49a15c = FUN_428800(1);
        }
        if (g_49a160 == NULL)
        {
            g_49a160 = FUN_428800(1);
        }
        FUN_4064b0();
        Car *car = g_49a1f8;
        for (int i = 0; i < 6; i++, car++)
        {
            car->unk2644 = 0;
            car->unk2648 = 0.0f;
            car->unk264c = 0;
            car->unk2650 = 0.0f;
            car->unk2654 = 0;
            car->unk2658 = 0.0f;
            car->unk2664 = 0;
            car->unk2674 = 0;
            car->unk2678 = 0;
            car->unk268c = 0;
            car->unk2694 = 0;
            car->unk26a0 = 0;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x405350
void FUN_405350()
{
    g_4d5bb8->unk264c = 0;
    g_4d5bb8->unk2650 = 0;
    g_4d5bb8->unk2644 = 0;
    g_4d5bb8->unk2648 = 0;
}

// Adds the scaled gravity vector unless the velocity is already above the cap.
// STUB: STUNTGP_D3D 0x405c80
void FUN_405c80()
{
}

// GLOBAL: STUNTGP_D3D 0x49a158
CameraPath *g_49a158;

// GLOBAL: STUNTGP_D3D 0x49a15c
CameraPath *g_49a15c;

// GLOBAL: STUNTGP_D3D 0x49a160
CameraPath *g_49a160;

// GLOBAL: STUNTGP_D3D 0x49a16c
float g_49a16c;

// GLOBAL: STUNTGP_D3D 0x49a170
float g_49a170;

// GLOBAL: STUNTGP_D3D 0x49a174
float g_49a174;

// GLOBAL: STUNTGP_D3D 0x472b88
float g_472b88[4] = {0.0f, 0.05f, 0.1f, 0.2f};

// GLOBAL: STUNTGP_D3D 0x472b98
float g_472b98 = 0.5f;

// GLOBAL: STUNTGP_D3D 0x472c74
int g_472c74 = 1;

// Walks the knot index along the path until pos projects onto its segment, then returns the percentage covered.
// FUNCTION: STUNTGP_D3D 0x405370
void FUN_405370(float *pos, CameraPath *path, int *index, float *distance)
{
    Vec4 seg;
    Vec4 *points = path->points;
    float len = 1.0f;
    int i = *index;
    int dir = 0;
    float t;
    for (;;)
    {
        DWORD a;
        if (i < 0)
        {
            a = path->count - (DWORD)-i % path->count;
        }
        else
        {
            a = (DWORD)i % path->count;
        }
        DWORD b = (a + 1) % path->count;
        seg.x = points[b].x - points[a].x;
        seg.y = points[b].y - points[a].y;
        seg.z = points[b].z - points[a].z;
        FUN_44eda0(&seg.x, &len);
        Vec4 r;
        r.x = pos[0] - points[a].x;
        r.y = pos[1] - points[a].y;
        r.z = pos[2] - points[a].z;
        t = r.x * seg.x + r.y * seg.y + r.z * seg.z;
        if (t < 0.0f)
        {
            if (dir <= 0.0f)
            {
                i--;
                dir = -1;
                continue;
            }
        }
        else if (t >= len && dir >= 0.0f)
        {
            i++;
            dir = 1;
            continue;
        }
        break;
    }
    *index = i;
    *distance = (t / len + i) * 100.0f / path->count;
}

void FUN_4143e0(float amount);
void FUN_414420(float amount);

// Turns a target point into steering input, scaled by speed and an initial ramp-in.

// FUNCTION: STUNTGP_D3D 0x4054b0
void FUN_4054b0(float *p, float amount)
{
    if (g_60f2b4 == 1)
    {
        return;
    }
    if (g_4d5bb8->unk26a4)
    {
        float f = (300 - g_4d5bb8->unk26a4) * 0.0033333334f;
        amount = f * f * amount;
    }
    Vec4 d;
    d.x = g_4d5bb8->posX - p[0];
    d.y = g_4d5bb8->posY - p[1];
    d.z = g_4d5bb8->posZ - p[2];
    float h = g_482688 * d.x + g_48268c * d.y + g_482690 * d.z;
    Vec4 u;
    u.x = g_482688 * h;
    u.y = g_48268c * h;
    u.z = g_482690 * h;
    d.x = d.x + u.x;
    d.y = u.y + d.y;
    d.z = u.z + d.z;
    float side = ((d.x * g_4d5bb8->axisX.x + d.y * g_4d5bb8->axisX.y + d.z * g_4d5bb8->axisX.z) * 0.0005f) * 2.25f;
    float m = g_4d5bb8->unk289c * g_4d5bb8->unk2660 * 0.35f;
    if (m < 1.0f)
    {
        m = 1.0f;
    }
    side /= m;
    if (g_4d5bb8->axisY.y < 0.0f)
    {
        side = -side;
    }
    amount = side * amount;
    if (amount >= 0.0f)
    {
        FUN_4143e0(amount);
    }
    else
    {
        FUN_414420(-amount);
    }
}

void FUN_4288d0(CameraPath *path, Vec4 *out, float dist);

// Steers at a point further down the racing line, blended across the track by unk265c;
// a target behind the car is swapped for one far off to the side.
// FUNCTION: STUNTGP_D3D 0x405610
void FUN_405610(float amount)
{
    float k = g_4d5bb8->unk1cf0 * 0.013333334f;
    if (k > 1.0f)
    {
        k = 1.0f;
    }
    else if (k < 0.25f)
    {
        k = 0.25f;
    }
    k *= 2000.0f;
    Vec4 a;
    FUN_4288d0(g_49a158, &a, k + g_49a16c);
    Vec4 b;
    FUN_4288d0(g_49a15c, &b, k + g_49a170);
    Vec4 t;
    t.x = b.x - a.x;
    t.y = b.y - a.y;
    t.z = b.z - a.z;
    t.x = g_4d5bb8->unk265c * t.x;
    t.y = g_4d5bb8->unk265c * t.y;
    t.z = g_4d5bb8->unk265c * t.z;
    t.x = t.x + a.x;
    t.y = t.y + a.y;
    t.z = t.z + a.z;
    if (!g_4d5bb8->unk1fd8)
    {
        Vec4 d;
        d.x = t.x - g_4d5bb8->posX;
        d.y = t.y - g_4d5bb8->posY;
        d.z = t.z - g_4d5bb8->posZ;
        if (d.x * g_4d5bb8->axisZ.x + d.y * g_4d5bb8->axisZ.y + d.z * g_4d5bb8->axisZ.z < 0.1f)
        {
            float s;
            if (d.x * g_4d5bb8->axisX.x + d.y * g_4d5bb8->axisX.y + d.z * g_4d5bb8->axisX.z < 0.0f)
            {
                s = -5000.0f;
            }
            else
            {
                s = 5000.0f;
            }
            Vec4 o;
            o.x = s * g_4d5bb8->axisX.x;
            o.y = s * g_4d5bb8->axisX.y;
            o.z = s * g_4d5bb8->axisX.z;
            t.x = o.x + g_4d5bb8->posX;
            t.y = o.y + g_4d5bb8->posY;
            t.z = o.z + g_4d5bb8->posZ;
        }
        if (!g_4d5bb8->unk1fd8)
        {
            FUN_4054b0(&t.x, amount);
        }
    }
}



// Steers towards a point, harder at low speed.
// FUNCTION: STUNTGP_D3D 0x406020
void FUN_406020(Vec4 *target, float amount)
{
    Vec4 d;
    Vec4 p;
    d.x = g_4d5bb8->posX - target->x;
    d.y = g_4d5bb8->posY - target->y;
    d.z = g_4d5bb8->posZ - target->z;
    float dot = g_482688 * d.x + g_48268c * d.y + g_482690 * d.z;
    p.x = g_482688 * dot;
    p.y = g_48268c * dot;
    p.z = g_482690 * dot;
    d.x += p.x;
    d.y = p.y + d.y;
    d.z = p.z + d.z;
    float steer = (d.x * g_4d5bb8->axisX.x + d.y * g_4d5bb8->axisX.y + d.z * g_4d5bb8->axisX.z) * 0.0005f;
    steer *= 2.25f;
    float speed = g_4d5bb8->unk289c * 0.35f;
    if (speed < 1.0f)
    {
        speed = 1.0f;
    }
    steer /= speed;
    if (g_4d5bb8->axisY.y < 0.0f)
    {
        steer = -steer;
    }
    amount = steer * amount;
    if (amount >= 0.0f)
    {
        FUN_4143e0(amount);
    }
    else
    {
        FUN_414420(-amount);
    }
}

// FUNCTION: STUNTGP_D3D 0x406140
void FUN_406140(float amount)
{
    Vec4 p;
    FUN_4288d0(g_49a158, &p, g_49a16c + 2000.0f);
    if (!g_4d5bb8->unk1fd8)
    {
        FUN_406020(&p, amount);
    }
}

// FUNCTION: STUNTGP_D3D 0x406190
void FUN_406190()
{
    if (g_4d5bb8->unk2640 == 1)
    {
        return;
    }
    FUN_405370(&g_4d5bb8->posX, g_49a15c, &g_4d5bb8->unk264c, &g_4d5bb8->unk2650);
    FUN_405370(&g_4d5bb8->posX, g_49a158, &g_4d5bb8->unk2644, &g_4d5bb8->unk2648);
    g_49a16c = g_4d5bb8->unk2648 * g_49a158->unk18 * 0.01f;
    g_49a170 = g_4d5bb8->unk2650 * g_49a15c->unk18 * 0.01f;
    if (g_4d5bb8->unk762c == 1)
    {
        FUN_406140(g_472b98);
        return;
    }
    if (g_4d5bb8->race.unk80[6] && g_4d5bb8->unk2250 != 1 && g_4d5bb8->unk7648 != 1)
    {
        FUN_405610(g_472b88[g_4d5bb8->race.unk80[6]]);
    }
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

// FUNCTION: STUNTGP_D3D 0x4064b0
void FUN_4064b0()
{
}

// FUNCTION: STUNTGP_D3D 0x4064c0
int FUN_4064c0()
{
    if (g_4d5bb8->unk2574 * g_4d5bb8->unkf74 < g_4d5bb8->unk2570)
    {
        return 1;
    }
    return 0;
}

// GLOBAL: STUNTGP_D3D 0x499fa8
float g_499fa8;

// GLOBAL: STUNTGP_D3D 0x499fac
int g_499fac;

void FUN_40cc90();

// Pulls the steering bias towards zero when closing on the car ahead.
// FUNCTION: STUNTGP_D3D 0x4064f0
void FUN_4064f0()
{
    Car *car = g_4d5bb8;
    Car *ahead = g_612948.unk03cc[car->unk24ac + 1];
    if (ahead)
    {
        float gap = car->leaderGap - ahead->leaderGap;
        if (gap > 0.0f && gap < 7500.0f)
        {
            float t = gap * 0.00013333333f;
            t = t * t;
            if (t < 0.1f)
            {
                t = 0.0f;
            }
            float v;
            if (car->unk266c >= 0.0f)
            {
                v = car->unk266c - (1.0f - t);
                if (v < 0.0f)
                {
                    v = 0.0f;
                }
                else if (v > 1.0f)
                {
                    v = 1.0f;
                }
            }
            else
            {
                v = (1.0f - t) + car->unk266c;
                if (v > 0.0f)
                {
                    v = 0.0f;
                }
                else if (v < -1.0f)
                {
                    v = -1.0f;
                }
            }
            if ((float)fabs(v) < car->unk266c)
            {
                car->unk266c = v;
            }
        }
    }
}

// At speed, eases the body's pitch and roll back towards the velocity frame while both are small.
// FUNCTION: STUNTGP_D3D 0x4062b0
void FUN_4062b0()
{
    if (!g_4d5bb8->unk71ec && g_4d5bb8->unk71f0 != 1 && g_4d5bb8->unk1cf0 >= 8.333333f)
    {
        float a[16];
        float b[16];
        float m[16];
        Vec4 r;
        Vec4 s;
        float pitch;
        float roll;
        Vec4 v = g_4d5bb8->unk1c8c;
        Vec3_Normalize(&v.x);
        s.x = g_482690 * v.y - g_48268c * v.z;
        s.y = g_482688 * v.z - g_482690 * v.x;
        s.z = g_48268c * v.x - g_482688 * v.y;
        Vec3_Normalize(&s.x);
        r.x = s.z * v.y - s.y * v.z;
        r.y = s.x * v.z - s.z * v.x;
        r.z = s.y * v.x - s.x * v.y;
        Vec3_Normalize(&r.x);
        Matrix_Identity(a);
        Matrix_Identity(b);
        float *mat = g_4d5bb8->matrix;
        memcpy(m, mat, sizeof(m));
        pitch = -(m[8] * r.x + m[9] * r.y + m[10] * r.z);
        if (fabs(pitch) <= 0.707f)
        {
            roll = -(m[0] * g_482688 + m[1] * g_48268c + m[2] * g_482690);
            if (fabs(roll) <= 0.34202009f)
            {
                Matrix_Transpose(b, mat);
                Matrix_RotateX(b, ((float)asin(pitch) * 57.295776f) * -0.1f);
                Matrix_RotateZ(b, ((float)asin(roll) * 57.295776f) * -0.1f);
                Matrix_Multiply3(b, mat);
                Matrix_Multiply3(g_4d5bb8->matrix, b);
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x406610
void FUN_406610()
{
    Car *car = g_4d5bb8;
    float v = g_499fa8 - car->unk1cf0;
    if (car->unk289c >= 10.0f)
    {
        v -= car->unk2660 * car->unk289c * 5.0f;
    }
    if (v > 0.0f)
    {
        v *= 0.1f;
        if (v > 1.0f)
        {
            v = 1.0f;
        }
        car->unk1cf8 = v;
        car->unk22bc = 1;
        return;
    }
    if (g_499fac == 1)
    {
        car->unk22bc = 0;
        if (v > -5.0f)
        {
            car->unk1cf8 *= 0.8f;
            return;
        }
        v *= -32.0f;
        if (v > 255.0f)
        {
            v = 255.0f;
        }
        car->controls[1] = (BYTE)v;
        FUN_40cc90();
        g_4d5bb8->unk1cf8 = 0.0f;
    }
}

// Point across the track: side >= 0 blends from the centre path towards g_49a158, below 0 towards g_49a160.
// FUNCTION: STUNTGP_D3D 0x406870
void FUN_406870(float dist, float side, Vec4 *out)

{
    Vec4 left;
    Vec4 centre;
    Vec4 right;
    FUN_4288d0(g_49a158, &left, g_49a16c + dist);
    FUN_4288d0(g_49a15c, &centre, g_49a170 + dist);
    FUN_4288d0(g_49a160, &right, g_49a174 + dist);
    Vec4 d;
    if (side >= 0.0f)
    {
        d.x = left.x - centre.x;
        d.y = left.y - centre.y;
        d.z = left.z - centre.z;
        d.x *= side;
        d.y *= side;
        d.z *= side;
    }
    else
    {
        d.x = right.x - centre.x;
        d.y = right.y - centre.y;
        d.z = right.z - centre.z;
        float s = -side;
        d.x = s * d.x;
        d.y = s * d.y;
        d.z = s * d.z;
    }
    d.x = d.x + centre.x;
    d.y = d.y + centre.y;
    d.z = d.z + centre.z;
    *out = d;
}

extern int g_4d5c9c;

// GLOBAL: STUNTGP_D3D 0x499fb0
float g_499fb0;

// GLOBAL: STUNTGP_D3D 0x49a148
Vec4 g_49a148;

// Measures how much the path bends ahead and picks the AI target speed from it.
// FUNCTION: STUNTGP_D3D 0x406970
void FUN_406970()
{
    float k = g_4d5bb8->unk1cf0 * 0.01f;
    if (k > 1.0f)
    {
        k = 1.0f;
    }
    else if (k < 0.5f)
    {
        k = 0.5f;
    }
    Vec4 a;
    FUN_406870(0.0f, g_4d5bb8->unk266c, &a);

    Vec4 b;
    FUN_406870(k * 2500.0f, g_4d5bb8->unk266c, &b);

    Vec4 c;
    FUN_406870(k * 5000.0f, g_4d5bb8->unk266c, &c);

    Vec4 d;
    d.x = b.x - a.x;
    d.y = b.y - a.y;
    d.z = b.z - a.z;
    Vec4 n;
    n.x = g_482690 * d.y - g_48268c * d.z;
    n.y = g_482688 * d.z - g_482690 * d.x;
    n.z = g_48268c * d.x - g_482688 * d.y;
    Vec3_Normalize(&n.x);
    Vec4 q;
    q.x = c.x - b.x;
    q.y = c.y - b.y;
    q.z = c.z - b.z;
    float t = q.x * n.x + q.y * n.y + q.z * n.z;
    g_4d5bb8->unk2668 = t;
    float speed = (108.33334f - (float)fabs(t * 0.0004f) * 100.0f) + 16.666666f;
    int flag;
    if (g_4d5bb8->unk24e0 == 1)
    {
        flag = 1;
        speed = g_60f2d0[7];
    }
    else if (g_4d5bb8->unk767c == 1)
    {
        flag = 1;
        speed = g_60f2d0[8];
    }
    else
    {
        flag = 0;
    }
    if (g_4d5bb8->unk762c == 1)
    {
        speed = 166.66667f;
    }
    g_499fa8 = speed;
    g_499fac = flag;
}

// Same steering as FUN_4054b0, aimed at g_49a148 with the g_499fb0 blend.
// FUNCTION: STUNTGP_D3D 0x406700
void FUN_406700()
{
    if (!g_4d5bb8->unk1f10)
    {
        return;
    }
    Vec4 d;
    d.x = g_4d5bb8->posX - g_49a148.x;
    d.y = g_4d5bb8->posY - g_49a148.y;
    d.z = g_4d5bb8->posZ - g_49a148.z;
    float h = g_482688 * d.x + g_48268c * d.y + g_482690 * d.z;
    Vec4 u;
    u.x = g_482688 * h;
    u.y = g_48268c * h;
    u.z = g_482690 * h;
    d.x = d.x + u.x;
    d.y = u.y + d.y;
    d.z = u.z + d.z;
    float side = ((d.x * g_4d5bb8->axisX.x + d.y * g_4d5bb8->axisX.y + d.z * g_4d5bb8->axisX.z) * 0.0005f) * 2.25f;
    float m = g_4d5bb8->unk289c * g_4d5bb8->unk2660 * 0.35f;
    if (m < 1.0f)
    {
        m = 1.0f;
    }
    side /= m;
    if (g_4d5bb8->axisY.y < 0.0f)
    {
        side = -side;
    }
    if (g_4d5bb8->unk26a4)
    {
        float f = (300 - g_4d5bb8->unk26a4) * 0.0033333334f;
        g_499fb0 = (f * f) * g_499fb0;
    }
    float amount = g_499fb0 * side;
    if (amount >= 0.0f)
    {
        FUN_4143e0(amount);
    }
    else
    {
        FUN_414420(-amount);
    }
}

// Near the end of the lap: drops the brake, slows the AI and ramps a blend towards the finish point.
// FUNCTION: STUNTGP_D3D 0x406d30
void FUN_406d30()
{
    if (g_4d5c9c && FUN_4064c0() != 1 && g_4d5bb8->unk26a8 != 1 && g_4d5bb8->unk23a4 < g_60eff8)
    {
        int lap = g_4d5bb8->unk23ac % 100;
        g_4d5bb8->controls[8] = 0;
        float p = lap * g_60f010 * 0.01f;
        float start = g_60f010 - 32500.0f;
        float end = g_60f010 - 10000.0f;
        if (g_60f010 - 35000.0f < p && p < end)
        {
            g_499fa8 = 66.666664f;
            g_499fac = 0;
        }
        if (p >= start && p <= end)
        {
            float b = ((p - start) * 20.0f) * 0.0001f;
            if (b > 20.0f)
            {
                b = 20.0f;
            }
            g_499fb0 = b;
            g_49a148 = *(Vec4 *)(*(BYTE **)(g_4d5c9c + 4) + 0x100);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x406e80
void FUN_406e80()
{
    g_4d5bb8->controls[0] = 0;
    g_4d5bb8->controls[1] = 0;
    g_4d5bb8->controls[2] = 0;
    g_4d5bb8->controls[3] = 0;
}

// Holds the scripted control for a while, cutting the throttle once the car is fast enough.
// FUNCTION: STUNTGP_D3D 0x406ea0
void FUN_406ea0()
{
    Car *car = g_4d5bb8;
    if (car->unk2678 < 0)
    {
        car->unk2678 = 0;
        return;
    }
    car->unk2678--;
    switch (car->unk267c)
    {
    case 0:
        car->controls[0] = 0xff;
        break;
    case 1:
        car->controls[1] = 0xff;
        break;
    case 2:
        car->controls[2] = 0xff;
        break;
    case 3:
        car->controls[3] = 0xff;
        break;
    case 4:
        break;
    case 5:
        return;
    }
    switch (car->unk2680)
    {
    case 0:
        if (car->unk6da4 >= 8 || car->unk6da8 >= 8)
        {
            FUN_406e80();
            if (g_4d5bb8->unk6da4 >= 10 || g_4d5bb8->unk6da8 >= 10)
            {
                g_4d5bb8->unk7224 = 0;
                g_4d5bb8->unk7228 = 0;
                g_4d5bb8->unk722c = 0;
                g_4d5bb8->unk7214 = 0;
                g_4d5bb8->unk7218 = 0;
                g_4d5bb8->unk721c = 0;
            }
        }
        break;
    case 1:
        if (car->unk6da4 >= 15 || car->unk6da8 >= 15)
        {
            FUN_406e80();
            if (g_4d5bb8->unk6da4 >= 18 || g_4d5bb8->unk6da8 >= 18)
            {
                g_4d5bb8->unk7224 = 0;
                g_4d5bb8->unk7228 = 0;
                g_4d5bb8->unk722c = 0;
                g_4d5bb8->unk7214 = 0;
                g_4d5bb8->unk7218 = 0;
                g_4d5bb8->unk721c = 0;
            }
        }
        break;
    case 2:
        if (car->unk6da4 >= 20 || car->unk6da8 >= 20)
        {
            FUN_406e80();
            if (g_4d5bb8->unk6da4 >= 26 || g_4d5bb8->unk6da8 >= 26)
            {
                g_4d5bb8->unk7224 = 0;
                g_4d5bb8->unk7228 = 0;
                g_4d5bb8->unk722c = 0;
                g_4d5bb8->unk7214 = 0;
                g_4d5bb8->unk7218 = 0;
                g_4d5bb8->unk721c = 0;
            }
        }
        break;
    }
    FUN_40d090();
}

// FUNCTION: STUNTGP_D3D 0x406ff0
void FUN_406ff0()
{
    g_4d5bb8->unk2678 = 0;
}

// FUNCTION: STUNTGP_D3D 0x407f60
void FUN_407f60()
{
    if (g_4722d0->data->race.unk00 != 0)
    {
        Car *car = g_4d5bb8;
        if (car->active == 1 && g_60f02c[car - g_49a1f8].unk1c != 1 && car->unk26ac == 0)
        {
            int r = FUN_42f1f0(64);
            car = g_4d5bb8;
            if (r == 0)
            {
                car->unk26ac = 3;
            }
        }
        if (car->unk26ac != 0)
        {
            car->unk26ac--;
            car->unk1cf8 = 1.0f;
        }
    }
}

// STUB: STUNTGP_D3D 0x408000
void FUN_408000()
{
}

extern float g_60f2d0[31];

// Finds the race leader; car 2 if nobody qualifies.
// FUNCTION: STUNTGP_D3D 0x408180
void FUN_408180(Car **leader)
{
    *leader = &g_49a1f8[2];
    for (int i = 0; i < 6; i++)
    {
        if (g_49a1f8[i].active == 1 && g_49a1f8[i].unk24ac == 0)
        {
            *leader = &g_49a1f8[i];
            return;
        }
    }
}

// Catch-up: cars trailing the leader by more than 1000 units get a power boost.
// FUNCTION: STUNTGP_D3D 0x4081d0
void FUN_4081d0()
{
    if (g_4d5bb8->catchUp)
    {
        Car *leader;
        FUN_408180(&leader);
        g_4d5bb8->unk2634 = 1.0f;
        float gap = (g_4d5bb8->unk23b0 - leader->unk23b0) * g_624474->unk18 * 0.01f;
        g_4d5bb8->leaderGap = gap;
        g_4d5bb8->unk2634 = 1.0f;
        if (g_4d5bb8 != leader)
        {
            gap -= 1000.0f;
            if (gap < 0.0f)
            {
                float boost;
                float range;
                if (g_4d5bb8->unk2640 == 1)
                {
                    boost = g_60f2d0[22];
                    range = g_60f2d0[18];
                }
                else
                {
                    boost = g_60f2d0[24];
                    range = g_60f2d0[23];
                }
                if (gap < -range)
                {
                    gap = -range;
                }
                float t = (float)fabs(gap) / range + (float)fabs(gap) / range;
                if (t > 1.0f)
                {
                    t = 1.0f;
                }
                g_4d5bb8->unk2634 = boost * t + 1.0f;
            }
        }
    }
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

extern float g_60f2d0[31];
void FUN_405820(Car *car, float *v);

// FUNCTION: STUNTGP_D3D 0x408dc0
void FUN_408dc0(float amount)
{
    if (g_4d5bb8->unk24e0 != 1 && g_4d5bb8->unk257c <= g_60f2d0[28])
    {
        amount = (float)fabs(amount) * g_60f2d0[27];
        if (amount >= g_60f2d0[25])
        {
            if (amount > g_60f2d0[26])
            {
                amount = g_60f2d0[26];
            }
            if (g_4d5bb8->unk2640 == 1)
            {
                FUN_405820(g_4d5bb8, &amount);
            }
            g_4d5bb8->unk2570 -= amount;
            g_4d5bb8->unk257c += amount;
            g_4d5bb8->unk2580 = g_60f2d0[29];
            if (g_4d5bb8->unk2570 < 0.0f)
            {
                g_4d5bb8->unk2570 = 0;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x408f90
void FUN_408f90()
{
    if (g_4d5bb8->unk762c)
    {
        g_4722d0->camMode = g_4d5bb8->unk7630;
        g_4d5bb8->unk762c = 0;
    }
}

extern int g_60dfec;

// FUNCTION: STUNTGP_D3D 0x409180
void FUN_409180(int wheel)
{
    if (g_60dfec == 1)
    {
        if (g_4d5bb8->wheels[wheel].unk78 == 1)
        {
            g_4d5bb8->wheels[wheel].unk78 = 3;
        }
    }
    else if (g_60dfec == 6)
    {
        if (g_4d5bb8->wheels[wheel].unk78 == 1)
        {
            g_4d5bb8->wheels[wheel].unk78 = 4;
        }
    }
}

extern TrackPoly *g_498164;

// FUNCTION: STUNTGP_D3D 0x4091e0
void FUN_4091e0(int wheel)
{
    BYTE *s = (BYTE *)&g_624480->surfaces[g_498164->surface];
    g_4d5bb8->wheels[wheel].unk84 = s[1] * 0.015625f;
    g_4d5bb8->wheels[wheel].unk8c = s[2];
    g_4d5bb8->wheels[wheel].unk88 = s[3];
    g_4d5bb8->wheels[wheel].unk74 = g_4d5bb8->wheels[wheel].unk78;
    g_4d5bb8->wheels[wheel].unk78 = s[0] & 0xf;
    FUN_409180(wheel);
    if (g_4d5bb8->wheels[wheel].unk78 == 10)
    {
        g_4d5bb8->wheels[wheel].unk78 = 1;
        g_4d5bb8->wheels[wheel].unk84 = 4.0f;
    }
    if (g_4d5bb8->wheels[wheel].unk74 != g_4d5bb8->wheels[wheel].unk78)
    {
        g_4d5bb8->wheels[wheel].unk7c = 1;
    }
    else
    {
        g_4d5bb8->wheels[wheel].unk7c = 0;
    }
}

// Rotates the matrix back by the excess once an axis tilts past 45 degrees.
// FUNCTION: STUNTGP_D3D 0x4092d0
void FUN_4092d0(float *m)
{
    float v = m[9];
    if ((float)fabs(v) > 0.70710683f)
    {
        float t = v < 0.0f ? v + 0.70710683f : v - 0.70710683f;
        Matrix_RotateX(m, (float)asin(t) * 57.295776f);
    }
    v = m[8] * -1.0f;
    if ((float)fabs(v) > 0.70710683f)
    {
        float t = v < 0.0f ? v + 0.70710683f : v - 0.70710683f;
        Matrix_RotateY(m, (float)asin(t) * 57.295776f);
    }
    v = m[1] * -1.0f;
    if ((float)fabs(v) > 0.70710683f)
    {
        float t = v < 0.0f ? v + 0.70710683f : v - 0.70710683f;
        Matrix_RotateZ(m, (float)asin(t) * 57.295776f);
    }
}

// FUNCTION: STUNTGP_D3D 0x40a0d0
void FUN_40a0d0(Car *car)
{
    memset(&car->unk1f2c, 0, sizeof(PosHistory));
    for (int i = 0; i < 8; i++)
    {
        car->unk1f2c.samples[i].pos = *(Vec4 *)&car->posX;
    }
}

// FUNCTION: STUNTGP_D3D 0x40a120
void FUN_40a120()
{
    for (int i = 0; i < 6; i++)
    {
        FUN_40a0d0(&g_49a1f8[i]);
        g_49a1f8[i].unk2270 = g_49a1f8[i].unkf78;
        g_49a1f8[i].unk2274 = g_49a1f8[i].unk1184;
    }
}

// FUNCTION: STUNTGP_D3D 0x40a160
void FUN_40a160()
{
    float sum = 0.0f;
    float step = 0.02226562425494194f;
    for (unsigned int i = 0; i < 128; i++)
    {
        g_4d5bb8->unk470[0][i] = (float)sqrt(sum);
        sum += step;
        if (i > 32)
        {
            if (i < 64)
            {
                step -= 0.0009765625;
                if (step < 0.0f)
                {
                    step = -0.0025f;
                }
            }
            if (i > 76)
            {
                step -= 0.0003f;
            }
        }
    }
}

// Builds the power curve from the current torque curve and records its peak below the rev limit.
// FUNCTION: STUNTGP_D3D 0x40a1d0
void FUN_40a1d0()
{
    Car *car = g_4d5bb8;
    float maxTorque = 0.0f;
    car->unk1d04 = 0.0f;
    float *torque = car->unk470[car->unk1f0c];
    for (DWORD i = 0; i < 128; i++)
    {
        float rpm = (float)i * car->unk045c * 0.0078125f;
        float power = ((rpm * 0.10471976f) * torque[i]) * 0.0013404826f;
        car->unk1d08[i] = power;
        if (rpm <= car->unk464)
        {
            if (power > car->unk1d04)
            {
                car->unk1d04 = power;
            }
            if (torque[i] > maxTorque)
            {
                maxTorque = torque[i];
            }
        }
    }
    car->unk1d04 = car->unk46c * car->unk1d04;
}

// FUNCTION: STUNTGP_D3D 0x40a2c0
void FUN_40a2c0(float (*m)[16])
{
    Matrix_Identity(m[0]);
    for (int i = 1; i < 5; i++)
    {
        Matrix_Identity(m[i]);
    }
}

extern FILE *g_5da2e4;
void FUN_434900(float *values, DWORD count);

// FUNCTION: STUNTGP_D3D 0x40a870
void FUN_40a870()
{
    // STRING: STUNTGP_D3D 0x472c78
    fprintf(g_5da2e4, "-ENGINE[] =\n");
    // STRING: STUNTGP_D3D 0x472c88
    fprintf(g_5da2e4, " RpmIdle         = %f\n", g_4d5bb8->unk460);
    // STRING: STUNTGP_D3D 0x472ca0
    fprintf(g_5da2e4, " RpmLimit        = %f\n", g_4d5bb8->unk464);
    // STRING: STUNTGP_D3D 0x472cb8
    fprintf(g_5da2e4, " RpmMax          = %f\n", g_4d5bb8->unk045c);
    // STRING: STUNTGP_D3D 0x472cd0
    fprintf(g_5da2e4, " Cm              = %f\n", g_4d5bb8->unk468);
    // STRING: STUNTGP_D3D 0x472ce8
    fprintf(g_5da2e4, " MaxTorque       = %f\n", g_4d5bb8->unk46c);
    for (int i = 0; i < 4; i++)
    {
        // STRING: STUNTGP_D3D 0x472d00
        fprintf(g_5da2e4, " TorqueEnv[%d] =\n", i);
        FUN_434900(g_4d5bb8->unk470[i], 128);
    }
    // STRING: STUNTGP_D3D 0x472d14
    fprintf(g_5da2e4, "-ENGINE_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40a990
void FUN_40a990()
{
    // STRING: STUNTGP_D3D 0x472d24
    fprintf(g_5da2e4, "-GEARBOX[] =\n");
    // STRING: STUNTGP_D3D 0x472d34
    fprintf(g_5da2e4, " DriveMode       = %d\n", g_4d5bb8->unkc70);
    // STRING: STUNTGP_D3D 0x472d4c
    fprintf(g_5da2e4, " FinalDrive      = %f\n", g_4d5bb8->unkc7c[0]);
    // STRING: STUNTGP_D3D 0x472d64
    fprintf(g_5da2e4, " NrOfGears       = %d\n", g_4d5bb8->unkc74);
    // STRING: STUNTGP_D3D 0x472d7c
    fprintf(g_5da2e4, " ShiftTime       = %f\n", g_4d5bb8->unkca0);
    // STRING: STUNTGP_D3D 0x472d94
    fprintf(g_5da2e4, " Efficiency      = %f\n", g_4d5bb8->unkca4);
    // STRING: STUNTGP_D3D 0x472dac
    fprintf(g_5da2e4, " 4WDPowerSplit   = %f\n", g_4d5bb8->unkca8);
    // STRING: STUNTGP_D3D 0x472dc4
    fprintf(g_5da2e4, " Ratios[]        =");
    for (int i = 1; i < 9; i++)
    {
        // STRING: STUNTGP_D3D 0x472dd8
        fprintf(g_5da2e4, "%12f, ", g_4d5bb8->unkc7c[i]);
    }
    // STRING: STUNTGP_D3D 0x472de0
    fprintf(g_5da2e4, "\n");
    // STRING: STUNTGP_D3D 0x472de4
    fprintf(g_5da2e4, "-GEARBOX_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40aae0
void FUN_40aae0()
{
    // STRING: STUNTGP_D3D 0x472df4
    fprintf(g_5da2e4, "-TYRES[] =\n");
    // STRING: STUNTGP_D3D 0x472e00
    fprintf(g_5da2e4, " TyreFrictionEnv =\n");
    FUN_434900(g_4d5bb8->tyreFrictionEnv, 128);
    for (int i = 0; i < 4; i++)
    {
        // STRING: STUNTGP_D3D 0x472e14
        fprintf(g_5da2e4, "-TYRE %d\n", i);
        // STRING: STUNTGP_D3D 0x472e20
        fprintf(g_5da2e4, " Radius          = %f\n", g_4d5bb8->unkcb8[i].x);
        // STRING: STUNTGP_D3D 0x472e38
        fprintf(g_5da2e4, " Pressure        = %f\n", g_4d5bb8->unkcb8[i].y);
        // STRING: STUNTGP_D3D 0x472e50
        fprintf(g_5da2e4, " Cs              = %f\n", g_4d5bb8->unkcb8[i].z);
        // STRING: STUNTGP_D3D 0x472e68
        fprintf(g_5da2e4, " Ck              = %f\n", g_4d5bb8->unkcb8[i].w);
        // STRING: STUNTGP_D3D 0x472e80
        fprintf(g_5da2e4, " MaxTravelIn     = %f\n", g_4d5bb8->suspension[i].maxTravelIn);
        // STRING: STUNTGP_D3D 0x472e98
        fprintf(g_5da2e4, " MaxDampingIn    = %f\n", g_4d5bb8->suspension[i].maxDampingIn);
        // STRING: STUNTGP_D3D 0x472eb0
        fprintf(g_5da2e4, " MaxStiffnessIn  = %f\n", g_4d5bb8->suspension[i].maxStiffnessIn);
        // STRING: STUNTGP_D3D 0x472ec8
        fprintf(g_5da2e4, " MaxTravelOut    = %f\n", g_4d5bb8->suspension[i].maxTravelOut);
        // STRING: STUNTGP_D3D 0x472ee0
        fprintf(g_5da2e4, " MaxDampingOut   = %f\n", g_4d5bb8->suspension[i].maxDampingOut);
        // STRING: STUNTGP_D3D 0x472ef8
        fprintf(g_5da2e4, " MaxStiffnessOut = %f\n", g_4d5bb8->suspension[i].maxStiffnessOut);
    }
    // STRING: STUNTGP_D3D 0x472f10
    fprintf(g_5da2e4, "-TYRES_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40acc0
void FUN_40acc0()
{
    // STRING: STUNTGP_D3D 0x472f20
    fprintf(g_5da2e4, "-AERODYNAMICS[] =\n");
    // STRING: STUNTGP_D3D 0x472f34
    fprintf(g_5da2e4, " Cd              = %f\n", g_4d5bb8->unkcac);
    // STRING: STUNTGP_D3D 0x472f4c
    fprintf(g_5da2e4, " Cl              = %f\n", g_4d5bb8->unkcb0);
    // STRING: STUNTGP_D3D 0x472f64
    fprintf(g_5da2e4, " FA              = %f\n", g_4d5bb8->unkcb4);
    // STRING: STUNTGP_D3D 0x472f7c
    fprintf(g_5da2e4, "-AERODYNAMICS_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40ad50
void FUN_40ad50()
{
    // STRING: STUNTGP_D3D 0x472f90
    fprintf(g_5da2e4, "-DIMENSIONS[] =\n");
    // STRING: STUNTGP_D3D 0x472fa4
    fprintf(g_5da2e4, " Mass            = %f\n", g_4d5bb8->unk220);
    // STRING: STUNTGP_D3D 0x472fbc
    fprintf(g_5da2e4, " Com_a           = %f\n", g_4d5bb8->unk224);
    // STRING: STUNTGP_D3D 0x472fd4
    fprintf(g_5da2e4, " Com_b           = %f\n", g_4d5bb8->unk228);
    // STRING: STUNTGP_D3D 0x472fec
    fprintf(g_5da2e4, " Com_h           = %f\n", g_4d5bb8->unk22c);
    // STRING: STUNTGP_D3D 0x473004
    fprintf(g_5da2e4, " WheelBase       = %f\n", g_4d5bb8->unk230);
    // STRING: STUNTGP_D3D 0x47301c
    fprintf(g_5da2e4, " TrackFront      = %f\n", g_4d5bb8->unk234);
    // STRING: STUNTGP_D3D 0x473034
    fprintf(g_5da2e4, " TrackRear       = %f\n", g_4d5bb8->unk238);
    // STRING: STUNTGP_D3D 0x47304c
    fprintf(g_5da2e4, " Length          = %f\n", g_4d5bb8->unk23c);
    // STRING: STUNTGP_D3D 0x473064
    fprintf(g_5da2e4, " Width           = %f\n", g_4d5bb8->unk240);
    // STRING: STUNTGP_D3D 0x47307c
    fprintf(g_5da2e4, " Height          = %f\n", g_4d5bb8->unk244);
    // STRING: STUNTGP_D3D 0x473094
    fprintf(g_5da2e4, " RideHeight      = %f\n", g_4d5bb8->unk248);
    // STRING: STUNTGP_D3D 0x4730ac
    fprintf(g_5da2e4, "-DIMENSIONS_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40aef0
void FUN_40aef0()
{
    // STRING: STUNTGP_D3D 0x4730c0
    fprintf(g_5da2e4, "-STEERING[] =\n");
    // STRING: STUNTGP_D3D 0x4730d0
    fprintf(g_5da2e4, " MaxAngle        = %f\n", g_4d5bb8->unk24c);
    // STRING: STUNTGP_D3D 0x4730e8
    fprintf(g_5da2e4, " Sensitivity     = %f\n", g_4d5bb8->unk254);
    // STRING: STUNTGP_D3D 0x473100
    fprintf(g_5da2e4, " Acceleration    = %f\n", g_4d5bb8->unk250);
    // STRING: STUNTGP_D3D 0x473118
    fprintf(g_5da2e4, " AlignmentTorque =\n");
    FUN_434900(g_4d5bb8->unk258, 128);
    // STRING: STUNTGP_D3D 0x47312c
    fprintf(g_5da2e4, "-STEERING_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40afb0
void FUN_40afb0()
{
    // STRING: STUNTGP_D3D 0x47313c
    fprintf(g_5da2e4, "-CONTROL[] =\n");
    // STRING: STUNTGP_D3D 0x47314c
    fprintf(g_5da2e4, " DigitalSteeringInputEnv =\n");
    FUN_434900(g_4d5bb8->unk1188[0], 128);
    // STRING: STUNTGP_D3D 0x473168
    fprintf(g_5da2e4, " DigitalBrakeInputEnv =\n");
    FUN_434900(g_4d5bb8->unk1188[1], 128);
    // STRING: STUNTGP_D3D 0x473184
    fprintf(g_5da2e4, " AnalogSteeringInputEnv =\n");
    FUN_434900(g_4d5bb8->unk1188[2], 128);
    // STRING: STUNTGP_D3D 0x4731a0
    fprintf(g_5da2e4, " AnalogBrakeInputEnv =\n");
    FUN_434900(g_4d5bb8->unk1188[3], 128);
    // STRING: STUNTGP_D3D 0x4731b8
    fprintf(g_5da2e4, " AnalogVelocitySteeringInputEnv =\n");
    FUN_434900(g_4d5bb8->unk1188[4], 128);
    // STRING: STUNTGP_D3D 0x4731dc
    fprintf(g_5da2e4, "-CONTROL_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40b0b0
void FUN_40b0b0()
{
    // STRING: STUNTGP_D3D 0x4731ec
    fprintf(g_5da2e4, "-FUEL[] =\n");
    // STRING: STUNTGP_D3D 0x4731f8
    fprintf(g_5da2e4, " MaxFuel         = %f\n", g_4d5bb8->unkf78);
    // STRING: STUNTGP_D3D 0x473210
    fprintf(g_5da2e4, " UnitMass        = %f\n", g_4d5bb8->unkf7c);
    // STRING: STUNTGP_D3D 0x473228
    fprintf(g_5da2e4, " MaxConsumption  = %f\n", g_4d5bb8->unkf80);
    // STRING: STUNTGP_D3D 0x473240
    fprintf(g_5da2e4, " RefuelRate      = %f\n", g_4d5bb8->unk1184);
    // STRING: STUNTGP_D3D 0x473258
    fprintf(g_5da2e4, " ConsumptionEnv =\n");
    FUN_434900(g_4d5bb8->unkf84, 128);
    // STRING: STUNTGP_D3D 0x47326c
    fprintf(g_5da2e4, "-FUEL_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40b190
void FUN_40b190()
{
    // STRING: STUNTGP_D3D 0x473278
    fprintf(g_5da2e4, "-TURBO[] =\n");
    // STRING: STUNTGP_D3D 0x473284
    fprintf(g_5da2e4, " RpmAcc          = %f\n", g_4d5bb8->unkd60);
    // STRING: STUNTGP_D3D 0x47329c
    fprintf(g_5da2e4, " RpmMax          = %f\n", g_4d5bb8->unkd64);
    // STRING: STUNTGP_D3D 0x4732b4
    fprintf(g_5da2e4, " Cm              = %f\n", g_4d5bb8->unkd68);
    // STRING: STUNTGP_D3D 0x4732cc
    fprintf(g_5da2e4, " PowerMultiplier = %f\n", g_4d5bb8->unkd6c);
    // STRING: STUNTGP_D3D 0x4732e4
    fprintf(g_5da2e4, " MaxConsumption  = %f\n", g_4d5bb8->unkf70);
    // STRING: STUNTGP_D3D 0x4732fc
    fprintf(g_5da2e4, " FuelCutoffPoint = %f\n", g_4d5bb8->unkf74);
    // STRING: STUNTGP_D3D 0x473314
    fprintf(g_5da2e4, " PowerEnv =\n");
    FUN_434900(g_4d5bb8->unkd70, 128);
    // STRING: STUNTGP_D3D 0x473324
    fprintf(g_5da2e4, "-TURBO_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40b2b0
void FUN_40b2b0()
{
    // STRING: STUNTGP_D3D 0x473334
    fprintf(g_5da2e4, "-BRAKE[] =\n");
    // STRING: STUNTGP_D3D 0x473340
    fprintf(g_5da2e4, " Bias            = %f\n", g_4d5bb8->unkd5c);
    // STRING: STUNTGP_D3D 0x473358
    fprintf(g_5da2e4, " Acceleration    = %f\n", g_4d5bb8->unkd58);
    // STRING: STUNTGP_D3D 0x473370
    fprintf(g_5da2e4, "-BRAKE_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40b320
void FUN_40b320()
{
    // STRING: STUNTGP_D3D 0x473380
    fprintf(g_5da2e4, "-SFX[] =\n");
    // STRING: STUNTGP_D3D 0x47338c
    fprintf(g_5da2e4, " Engine_Rev         = %d\n", g_4d5bb8->race.unk80[1]);
    // STRING: STUNTGP_D3D 0x4733a8
    fprintf(g_5da2e4, " Engine_Idle        = %d\n", g_4d5bb8->race.unk80[2]);
    // STRING: STUNTGP_D3D 0x4733c4
    fprintf(g_5da2e4, " Engine_Boost       = %d\n", g_4d5bb8->race.unk80[3]);
    // STRING: STUNTGP_D3D 0x4733e0
    fprintf(g_5da2e4, " Horn               = %d\n", g_4d5bb8->race.unk80[0]);
    // STRING: STUNTGP_D3D 0x4733fc
    fprintf(g_5da2e4, "-SFX_END\n\n");
}

// FUNCTION: STUNTGP_D3D 0x40b3c0
void FUN_40b3c0()
{
    // STRING: STUNTGP_D3D 0x473408
    fprintf(g_5da2e4, "-STUNT[] =\n");
    // STRING: STUNTGP_D3D 0x473414
    fprintf(g_5da2e4, " LaunchTime         = %f\n", g_4d5bb8->unk1b94);
    // STRING: STUNTGP_D3D 0x473430
    fprintf(g_5da2e4, " LaunchTolerance    = %f\n", g_4d5bb8->unk1b98);
    // STRING: STUNTGP_D3D 0x47344c
    fprintf(g_5da2e4, " LaunchSpd          = %f\n", g_4d5bb8->unk1b9c);
    // STRING: STUNTGP_D3D 0x473468
    fprintf(g_5da2e4, " MaxRotSpd_X        = %f\n", g_4d5bb8->unk1ba0);
    // STRING: STUNTGP_D3D 0x473484
    fprintf(g_5da2e4, " MaxRotSpd_Y        = %f\n", g_4d5bb8->unk1ba4);
    // STRING: STUNTGP_D3D 0x4734a0
    fprintf(g_5da2e4, "-STUNT_END\n\n");
}

void Script_GetFloat(char *section, char *key, float *out);
void Script_GetInt(char *section, char *key, int *out);
void Script_GetFloatArray(char *section, char *key, float *out, DWORD count);

// FUNCTION: STUNTGP_D3D 0x40b490
void FUN_40b490(char *text)
{
    // STRING: STUNTGP_D3D 0x4734b0
    char *section = strstr(text, "-DIMENSIONS[] =");
    // STRING: STUNTGP_D3D 0x4734c0
    Script_GetFloat(section, "Mass", &g_4d5bb8->unk220);
    // STRING: STUNTGP_D3D 0x4734c8
    Script_GetFloat(section, "Com_a", &g_4d5bb8->unk224);
    // STRING: STUNTGP_D3D 0x4734d0
    Script_GetFloat(section, "Com_b", &g_4d5bb8->unk228);
    // STRING: STUNTGP_D3D 0x4734d8
    Script_GetFloat(section, "Com_h", &g_4d5bb8->unk22c);
    // STRING: STUNTGP_D3D 0x4734e0
    Script_GetFloat(section, "WheelBase", &g_4d5bb8->unk230);
    // STRING: STUNTGP_D3D 0x4734ec
    Script_GetFloat(section, "TrackFront", &g_4d5bb8->unk234);
    // STRING: STUNTGP_D3D 0x4734f8
    Script_GetFloat(section, "TrackRear", &g_4d5bb8->unk238);
    // STRING: STUNTGP_D3D 0x473504
    Script_GetFloat(section, "Length", &g_4d5bb8->unk23c);
    // STRING: STUNTGP_D3D 0x47350c
    Script_GetFloat(section, "Width", &g_4d5bb8->unk240);
    // STRING: STUNTGP_D3D 0x473514
    Script_GetFloat(section, "Height", &g_4d5bb8->unk244);
    // STRING: STUNTGP_D3D 0x47351c
    Script_GetFloat(section, "RideHeight", &g_4d5bb8->unk248);
}

// FUNCTION: STUNTGP_D3D 0x40b5b0
void FUN_40b5b0(char *text)
{
    char key[16];
    // STRING: STUNTGP_D3D 0x473528
    char *section = strstr(text, "-ENGINE[] =");
    // STRING: STUNTGP_D3D 0x473534
    Script_GetFloat(section, "RpmIdle", &g_4d5bb8->unk460);
    // STRING: STUNTGP_D3D 0x47353c
    Script_GetFloat(section, "RpmLimit", &g_4d5bb8->unk464);
    // STRING: STUNTGP_D3D 0x473548
    Script_GetFloat(section, "RpmMax", &g_4d5bb8->unk045c);
    // STRING: STUNTGP_D3D 0x473550
    Script_GetFloat(section, "Cm", &g_4d5bb8->unk468);
    // STRING: STUNTGP_D3D 0x473554
    Script_GetFloat(section, "Torque", &g_4d5bb8->unk46c);
    for (int i = 0; i < 4; i++)
    {
        // STRING: STUNTGP_D3D 0x47355c
        sprintf(key, "TorqueEnv[%d]", i);
        Script_GetFloatArray(section, key, g_4d5bb8->unk470[i], 128);
    }
}

// FUNCTION: STUNTGP_D3D 0x40b690
void FUN_40b690(char *text)
{
    // STRING: STUNTGP_D3D 0x47356c
    char *section = strstr(text, "-GEARBOX[] =");
    // STRING: STUNTGP_D3D 0x47357c
    Script_GetInt(section, "DriveMode", &g_4d5bb8->unkc70);
    // STRING: STUNTGP_D3D 0x473588
    Script_GetInt(section, "NrOfGears", (int *)&g_4d5bb8->unkc74);
    // STRING: STUNTGP_D3D 0x473594
    Script_GetFloat(section, "FinalDrive", &g_4d5bb8->unkc7c[0]);
    // STRING: STUNTGP_D3D 0x4735a0
    Script_GetFloat(section, "ShiftTime", &g_4d5bb8->unkca0);
    // STRING: STUNTGP_D3D 0x4735ac
    Script_GetFloat(section, "Efficiency", &g_4d5bb8->unkca4);
    // STRING: STUNTGP_D3D 0x4735b8
    Script_GetFloat(section, "4WDPowerSplit", &g_4d5bb8->unkca8);
    // STRING: STUNTGP_D3D 0x4735c8
    Script_GetFloatArray(section, "Ratios[]", &g_4d5bb8->unkc7c[1], 8);
}

// FUNCTION: STUNTGP_D3D 0x40b750
void FUN_40b750(char *text)
{
    // STRING: STUNTGP_D3D 0x4735d4
    char *section = strstr(text, "-BRAKE[] =");
    // STRING: STUNTGP_D3D 0x4735e0
    Script_GetFloat(section, "Bias", &g_4d5bb8->unkd5c);
    // STRING: STUNTGP_D3D 0x4735e8
    Script_GetFloat(section, "Acceleration", &g_4d5bb8->unkd58);
}

// FUNCTION: STUNTGP_D3D 0x40b7a0
void FUN_40b7a0(char *text)
{
    char key[32];
    // STRING: STUNTGP_D3D 0x4735f8
    char *section = strstr(text, "-TYRES[] =");
    // STRING: STUNTGP_D3D 0x473604
    Script_GetFloatArray(section, "TyreFrictionEnv", g_4d5bb8->tyreFrictionEnv, 128);
    for (int i = 0; i < 4; i++)
    {
        // STRING: STUNTGP_D3D 0x473614
        sprintf(key, "-TYRE %d", i);
        section = strstr(text, key);
        // STRING: STUNTGP_D3D 0x473620
        Script_GetFloat(section, "Radius", &g_4d5bb8->unkcb8[i].x);
        // STRING: STUNTGP_D3D 0x473628
        Script_GetFloat(section, "Pressure", &g_4d5bb8->unkcb8[i].y);
        // STRING: STUNTGP_D3D 0x473634
        Script_GetFloat(section, "Cs", &g_4d5bb8->unkcb8[i].z);
        // STRING: STUNTGP_D3D 0x473638
        Script_GetFloat(section, "Ck", &g_4d5bb8->unkcb8[i].w);
        // STRING: STUNTGP_D3D 0x47363c
        Script_GetFloat(section, "MaxTravelIn", &g_4d5bb8->suspension[i].maxTravelIn);
        // STRING: STUNTGP_D3D 0x473648
        Script_GetFloat(section, "MaxDampingIn", &g_4d5bb8->suspension[i].maxDampingIn);
        // STRING: STUNTGP_D3D 0x473658
        Script_GetFloat(section, "MaxStiffnessIn", &g_4d5bb8->suspension[i].maxStiffnessIn);
        // STRING: STUNTGP_D3D 0x473668
        Script_GetFloat(section, "MaxTravelOut", &g_4d5bb8->suspension[i].maxTravelOut);
        // STRING: STUNTGP_D3D 0x473678
        Script_GetFloat(section, "MaxDampingOut", &g_4d5bb8->suspension[i].maxDampingOut);
        // STRING: STUNTGP_D3D 0x473688
        Script_GetFloat(section, "MaxStiffnessOut", &g_4d5bb8->suspension[i].maxStiffnessOut);
    }
}

// FUNCTION: STUNTGP_D3D 0x40b930
void FUN_40b930(char *text)
{
    // STRING: STUNTGP_D3D 0x473698
    char *section = strstr(text, "-AERODYNAMICS[] =");
    // STRING: STUNTGP_D3D 0x4736ac
    Script_GetFloat(section, "Cd", &g_4d5bb8->unkcac);
    // STRING: STUNTGP_D3D 0x4736b0
    Script_GetFloat(section, "Cl", &g_4d5bb8->unkcb0);
    // STRING: STUNTGP_D3D 0x4736b4
    Script_GetFloat(section, "FA", &g_4d5bb8->unkcb4);
}

void Script_GetFloatArray(char *section, char *key, float *out, DWORD count);

// FUNCTION: STUNTGP_D3D 0x40b990
void FUN_40b990(char *text)
{
    // STRING: STUNTGP_D3D 0x4736b8
    char *section = strstr(text, "-STEERING[] =");
    // STRING: STUNTGP_D3D 0x4736c8
    Script_GetFloat(section, "MaxAngle", &g_4d5bb8->unk24c);
    // STRING: STUNTGP_D3D 0x4736d4
    Script_GetFloat(section, "Sensitivity", &g_4d5bb8->unk254);
    // STRING: STUNTGP_D3D 0x4736e0
    Script_GetFloat(section, "Acceleration", &g_4d5bb8->unk250);
    // STRING: STUNTGP_D3D 0x4736f0
    Script_GetFloatArray(section, "AlignmentTorque", g_4d5bb8->unk258, 128);
}

// FUNCTION: STUNTGP_D3D 0x40ba10
void FUN_40ba10(char *text)
{
    // STRING: STUNTGP_D3D 0x473700
    char *section = strstr(text, "-CONTROL[] =");
    // STRING: STUNTGP_D3D 0x473710
    Script_GetFloatArray(section, "DigitalSteeringInputEnv", g_4d5bb8->unk1188[0], 128);
    // STRING: STUNTGP_D3D 0x473728
    Script_GetFloatArray(section, "DigitalBrakeInputEnv", g_4d5bb8->unk1188[1], 128);
    // STRING: STUNTGP_D3D 0x473740
    Script_GetFloatArray(section, "AnalogSteeringInputEnv", g_4d5bb8->unk1188[2], 128);
    // STRING: STUNTGP_D3D 0x473758
    Script_GetFloatArray(section, "AnalogBrakeInputEnv", g_4d5bb8->unk1188[3], 128);
    // STRING: STUNTGP_D3D 0x47376c
    Script_GetFloatArray(section, "AnalogVelocitySteeringInputEnv", g_4d5bb8->unk1188[4], 128);
}

// FUNCTION: STUNTGP_D3D 0x40bac0
void FUN_40bac0(char *text)
{
    // STRING: STUNTGP_D3D 0x47378c
    char *section = strstr(text, "-FUEL[] =");
    // STRING: STUNTGP_D3D 0x473798
    Script_GetFloat(section, "MaxFuel", &g_4d5bb8->unkf78);
    // STRING: STUNTGP_D3D 0x4737a0
    Script_GetFloat(section, "UnitMass", &g_4d5bb8->unkf7c);
    // STRING: STUNTGP_D3D 0x4737ac
    Script_GetFloat(section, "MaxConsumption", &g_4d5bb8->unkf80);
    // STRING: STUNTGP_D3D 0x4737bc
    Script_GetFloat(section, "RefuelRate", &g_4d5bb8->unk1184);
    // STRING: STUNTGP_D3D 0x4737c8
    Script_GetFloatArray(section, "ConsumptionEnv", g_4d5bb8->unkf84, 128);
}

void Script_GetInt(char *section, char *key, int *out);

// FUNCTION: STUNTGP_D3D 0x40bb60
void FUN_40bb60(char *text)
{
    // STRING: STUNTGP_D3D 0x4737d8
    char *section = strstr(text, "-TURBO[] =");
    // STRING: STUNTGP_D3D 0x4737e4
    Script_GetFloat(section, "RpmAcc", &g_4d5bb8->unkd60);
    // STRING: STUNTGP_D3D 0x4737ec
    Script_GetFloat(section, "RpmMax", &g_4d5bb8->unkd64);
    // STRING: STUNTGP_D3D 0x4737f4
    Script_GetFloat(section, "Cm", &g_4d5bb8->unkd68);
    // STRING: STUNTGP_D3D 0x4737f8
    Script_GetFloat(section, "PowerMultiplier", &g_4d5bb8->unkd6c);
    // STRING: STUNTGP_D3D 0x473808
    Script_GetFloat(section, "MaxConsumption", &g_4d5bb8->unkf70);
    // STRING: STUNTGP_D3D 0x473818
    Script_GetFloat(section, "FuelCutoffPoint", &g_4d5bb8->unkf74);
    // STRING: STUNTGP_D3D 0x473828
    Script_GetFloatArray(section, "PowerEnv", g_4d5bb8->unkd70, 128);
}

// FUNCTION: STUNTGP_D3D 0x40bc30
void FUN_40bc30(char *text)
{
    // STRING: STUNTGP_D3D 0x473834
    char *section = strstr(text, "-SFX[] =");
    // STRING: STUNTGP_D3D 0x473840
    Script_GetInt(section, "Engine_Rev", (int *)&g_4d5bb8->race.unk80[1]);
    // STRING: STUNTGP_D3D 0x47384c
    Script_GetInt(section, "Engine_Idle", (int *)&g_4d5bb8->race.unk80[2]);
    // STRING: STUNTGP_D3D 0x473858
    Script_GetInt(section, "Engine_Boost", (int *)&g_4d5bb8->race.unk80[3]);
    // STRING: STUNTGP_D3D 0x473868
    Script_GetInt(section, "Horn", (int *)&g_4d5bb8->race.unk80[0]);
}

// FUNCTION: STUNTGP_D3D 0x40bcb0
void FUN_40bcb0(char *text)
{
    // STRING: STUNTGP_D3D 0x473870
    char *section = strstr(text, "-STUNT[] =");
    // STRING: STUNTGP_D3D 0x47387c
    Script_GetFloat(section, "LaunchTime", &g_4d5bb8->unk1b94);
    // STRING: STUNTGP_D3D 0x473888
    Script_GetFloat(section, "LaunchTolerance", &g_4d5bb8->unk1b98);
    // STRING: STUNTGP_D3D 0x473898
    Script_GetFloat(section, "LaunchSpd", &g_4d5bb8->unk1b9c);
    // STRING: STUNTGP_D3D 0x4738a4
    Script_GetFloat(section, "MaxRotSpd_X", &g_4d5bb8->unk1ba0);
    // STRING: STUNTGP_D3D 0x4738b0
    Script_GetFloat(section, "MaxRotSpd_Y", &g_4d5bb8->unk1ba4);
}

extern char g_GameDirectory[128];
void FUN_434890();

// FUNCTION: STUNTGP_D3D 0x40bd40
void FUN_40bd40()
{
    char path[128];
    // STRING: STUNTGP_D3D 0x4738bc
    sprintf(path, "%s\\Config\\Vehicles\\Vehicle%d.cfg", g_GameDirectory, g_472c74);
    // STRING: STUNTGP_D3D 0x4738e0
    g_5da2e4 = fopen(path, "wt");
    if (g_5da2e4)
    {
        g_4d5bb8 = g_474630;
        FUN_434890();
        FUN_40ad50();
        FUN_40a870();
        FUN_40a990();
        FUN_40b2b0();
        FUN_40aae0();
        FUN_40acc0();
        FUN_40aef0();
        FUN_40afb0();
        FUN_40b0b0();
        FUN_40b190();
        FUN_40b320();
        FUN_40b3c0();
        fclose(g_5da2e4);
    }
}

// FUNCTION: STUNTGP_D3D 0x40bf20
void FUN_40bf20()
{
    g_4d5bb8->unk7224 -= 0.8f;
    if (g_4d5bb8->unk7224 < -0.8f)
    {
        g_4d5bb8->unk7224 = -0.8f;
    }
    g_4d5bb8->unk7214 += g_4d5bb8->unk7224;
    float limit = g_4d5bb8->unk1ba0 / g_4d5bb8->unk220;
    if (limit > 12.0f)
    {
        limit = 12.0f;
    }
    if (g_4d5bb8->unk7214 < -limit)
    {
        g_4d5bb8->unk7214 = -limit;
    }
}

// FUNCTION: STUNTGP_D3D 0x40bfb0
void FUN_40bfb0()
{
    g_4d5bb8->unk7224 += 0.8f;
    if (g_4d5bb8->unk7224 > 0.8f)
    {
        g_4d5bb8->unk7224 = 0.8f;
    }
    g_4d5bb8->unk7214 += g_4d5bb8->unk7224;
    float limit = g_4d5bb8->unk1ba0 / g_4d5bb8->unk220;
    if (limit > 12.0f)
    {
        limit = 12.0f;
    }
    if (g_4d5bb8->unk7214 > limit)
    {
        g_4d5bb8->unk7214 = limit;
    }
}

// FUNCTION: STUNTGP_D3D 0x40c040
void FUN_40c040()
{
    g_4d5bb8->unk7228 += 0.8f;
    if (g_4d5bb8->unk7228 > 0.8f)
    {
        g_4d5bb8->unk7228 = 0.8f;
    }
    g_4d5bb8->unk7218 += g_4d5bb8->unk7228;
    float limit = g_4d5bb8->unk1ba4 / g_4d5bb8->unk220;
    if (limit > 12.0f)
    {
        limit = 12.0f;
    }
    if (g_4d5bb8->unk7218 > limit)
    {
        g_4d5bb8->unk7218 = limit;
    }
}

// FUNCTION: STUNTGP_D3D 0x40c0d0
void FUN_40c0d0()
{
    g_4d5bb8->unk7228 -= 0.8f;
    if (g_4d5bb8->unk7228 < -0.8f)
    {
        g_4d5bb8->unk7228 = -0.8f;
    }
    g_4d5bb8->unk7218 += g_4d5bb8->unk7228;
    float limit = g_4d5bb8->unk1ba4 / g_4d5bb8->unk220;
    if (limit > 12.0f)
    {
        limit = 12.0f;
    }
    if (g_4d5bb8->unk7218 < -limit)
    {
        g_4d5bb8->unk7218 = -limit;
    }
}

// FUNCTION: STUNTGP_D3D 0x40c160
void FUN_40c160()
{
    g_4d5bb8->unk1f14 = 0.0f;
}

// Shifts up a gear.
// FUNCTION: STUNTGP_D3D 0x40c170
void FUN_40c170()
{
    if (g_4d5bb8->unk1f10 < g_4d5bb8->unkc74)
    {
        g_4d5bb8->unk1f10++;
        g_4d5bb8->unk23a0 = 1;
        FUN_40c160();
    }
}

// Shifts down a gear.
// FUNCTION: STUNTGP_D3D 0x40c1a0
void FUN_40c1a0()
{
    if (g_4d5bb8->unk1f10 > 0)
    {
        g_4d5bb8->unk1f1c = (int)(g_4d5bb8->unkca0 * 60.0f);
        g_4d5bb8->unk1f10--;
        g_4d5bb8->unk23a0 = 1;
        FUN_40c160();
    }
}

// FUNCTION: STUNTGP_D3D 0x40c1f0
void FUN_40c1f0()
{
    if (g_4d5bb8->unk1f10 != 1)
    {
        g_4d5bb8->unk1f10 = 1;
        g_4d5bb8->unk23a0 = 1;
        FUN_40c160();
    }
}

// FUNCTION: STUNTGP_D3D 0x40c4e0
void FUN_40c4e0()
{
    g_4d5bb8->unk7224 = 0.0f;
    g_4d5bb8->unk7228 = 0.0f;
    g_4d5bb8->unk722c = 0.0f;
}

// FUNCTION: STUNTGP_D3D 0x40c220
void FUN_40c220()
{
    g_4d5bb8->unk22b4 = g_4d5bb8->unk22bc;
    g_4d5bb8->unk22bc = 0;
    g_4d5bb8->unk2250 = 0;
    if ((g_4d5bb8->unk1f10 && g_4d5bb8->controls[0]) || (!g_4d5bb8->unk1f10 && g_4d5bb8->controls[1]))
    {
        g_4d5bb8->unk22bc = 1;
        if (!g_4d5bb8->unk71ec && g_4d5bb8->unk71fc > 60.0f)
        {
            g_4d5bb8->unk1cf8 *= 0.9f;
            return;
        }
        float throttle;
        if (g_4d5bb8->unk1f10)
        {
            throttle = g_4d5bb8->controls[0];
        }
        else
        {
            throttle = g_4d5bb8->controls[1];
        }
        g_4d5bb8->unk1cf8 = throttle * (1.0f / 255.0f);
        if (g_4d5bb8->controls[0] && g_4d5bb8->controls[8])
        {
            g_4d5bb8->unk2250 = 1;
        }
    }
    else
    {
        g_4d5bb8->unk1cf8 *= 0.5f;
    }
}

// FUNCTION: STUNTGP_D3D 0x413430
void FUN_413430(int wheel)
{
    g_4d5bb8->wheels[wheel].unk00 = g_4d5bb8->wheels[wheel].unk04 = 0.0f;
}

// FUNCTION: STUNTGP_D3D 0x414ac0
void FUN_414ac0(unsigned int wheel)
{
    float v = g_4d5bb8->wheels[wheel].unk00;
    v *= v;
    v = (float)fabs(v * g_4d5bb8->wheels[wheel].unk04) * 0.1f;
    if (v > 60.0f)
    {
        v = 60.0f;
    }
    g_4d5bb8->unk2cf4[wheel] += v;
    if (g_4d5bb8->unk2cf4[wheel] >= 255.0f)
    {
        g_4d5bb8->unk2cf4[wheel] = 255.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x415630
void FUN_415630()
{
    g_4d5bb8->unk28a8 = 0xff;
}

// Analog brake; the handbrake locks the front wheels instead.
// FUNCTION: STUNTGP_D3D 0x40c320
void FUN_40c320()
{
    Car *car = g_4d5bb8;
    car->unk22b8 = car->unk22c0;
    car->unk22c0 = 0;
    if ((car->unk1f10 && car->controls[1]) || (!car->unk1f10 && car->controls[0]))
    {
        car->unk22c0 = 1;
        float input;
        if (car->unk1f10)
        {
            input = car->controls[1];
        }
        else
        {
            input = car->controls[0];
        }
        if (car->controls[6])
        {
            car->wheels[0].unk04 = 0.0f;
            car->wheels[1].unk04 = 0.0f;
            FUN_415630();
            return;
        }
        float torque = -(car->unk1188[3][-(int)(input * (1.0f / 255.0f) * -127.0f)] * car->unkd58);
        if (car->wheels[0].unk04 < 0.0f)
        {
            torque = -torque;
        }
        float front = torque * car->unkd5c;
        car->wheels[0].unk00 = front;
        car->wheels[1].unk00 = front;
        float rear = (1.0f - car->unkd5c) * torque;
        car->wheels[2].unk00 = rear;
        car->wheels[3].unk00 = rear;
        front = (float)fabs(front) + (float)fabs(front);
        rear = (float)fabs(rear) + (float)fabs(rear);
        if ((float)fabs(car->wheels[0].unk04) < front)
        {
            FUN_413430(0);
            car = g_4d5bb8;
        }
        if ((float)fabs(car->wheels[1].unk04) < front)
        {
            FUN_413430(1);
            car = g_4d5bb8;
        }
        if ((float)fabs(car->wheels[2].unk04) < rear)
        {
            FUN_413430(2);
            car = g_4d5bb8;
        }
        if ((float)fabs(car->wheels[3].unk04) < rear)
        {
            FUN_413430(3);
        }
        for (unsigned int i = 0; i < 4; i++)
        {
            FUN_414ac0(i);
        }
        FUN_415630();
    }
}

void FUN_40ce60();

// Analog steering through the steering curve, scaled down with speed on some input modes.
// FUNCTION: STUNTGP_D3D 0x40c500
void FUN_40c500()
{
    FUN_40ce60();
    float boost = g_4d5bb8->unk22c4 + 1.0f;
    float input;
    if (g_4d5bb8->controls[2])
    {
        input = g_4d5bb8->controls[2];
    }
    else
    {
        input = g_4d5bb8->controls[3];
    }
    float steer = g_4d5bb8->unk1188[2][-(int)(input * 127.0f * (-1.0f / 255.0f))] * g_4d5bb8->unk254;
    if (steer > 1.0f)
    {
        steer = 1.0f;
    }
    if (g_4d5bb8->inputMode == 3 || g_4d5bb8->inputMode == 1)
    {
        float speed = (float)fabs(g_4d5bb8->unk1cf0) * 128.0f;
        unsigned int i = (int)(speed * 0.005f);
        if (i >= 128)
        {
            i = 127;
        }
        steer = steer * g_4d5bb8->unk1188[4][i] * boost;
        if (steer > 1.0f)
        {
            steer = 1.0f;
        }
    }
    steer *= g_4d5bb8->unk24c;
    if (g_4d5bb8->controls[3])
    {
        steer = -steer;
    }
    g_4d5bb8->unk1cf4 = steer;
}

// FUNCTION: STUNTGP_D3D 0x414940
void FUN_414940()
{
    if (g_482688 * g_4d5bb8->axisY.x + g_48268c * g_4d5bb8->axisY.y + g_482690 * g_4d5bb8->axisY.z < 0.0f &&
        (float)fabs(g_4d5bb8->unk7214) >= 0.05f)
    {
        float d = g_482688 * g_4d5bb8->axisZ.x + g_48268c * g_4d5bb8->axisZ.y + g_482690 * g_4d5bb8->axisZ.z;
        g_4d5bb8->unk7214 = (g_4d5bb8->unk7214 < 0.0f ? -(float)fabs(d) : (float)fabs(d)) * 6.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x4149e0
void FUN_4149e0()
{
    if (g_4d5bb8->axisZ.x * g_4d5bb8->unk1c8c.x + g_4d5bb8->axisZ.y * g_4d5bb8->unk1c8c.y +
                g_4d5bb8->axisZ.z * g_4d5bb8->unk1c8c.z >
            0.0f &&
        (float)fabs(g_4d5bb8->unk7218) >= 0.05f)
    {
        Vec4 v = g_4d5bb8->unk1c8c;
        Vec3_Normalize(&v.x);
        float d = v.x * g_4d5bb8->axisX.x + v.y * g_4d5bb8->axisX.y + v.z * g_4d5bb8->axisX.z;
        g_4d5bb8->unk7218 = (g_4d5bb8->unk7218 < 0.0f ? -(float)fabs(d) : (float)fabs(d)) * 6.0f;
    }
}

// Analog stick version of 0x40d090.
// FUNCTION: STUNTGP_D3D 0x40c5f0
void FUN_40c5f0()
{
    if (g_4d5bb8->controls[5] && !g_4d5bb8->prevControls[5])
    {
        g_4d5bb8->unk7234 = g_612948.unk03b4;
    }
    if (!g_4d5bb8->unk71ec && g_4d5bb8->unk71f0)
    {
        int steered = 0;
        if ((float)fabs(g_4d5bb8->unk7218) < 0.2f)
        {
            if (g_4d5bb8->controls[1] > 127)
            {
                FUN_40bfb0();
                steered = 1;
            }
            else if (g_4d5bb8->controls[0] > 127)
            {
                FUN_40bf20();
                steered = 1;
            }
        }
        if ((float)fabs(g_4d5bb8->unk7214) < 0.2f)
        {
            if (g_4d5bb8->controls[2] > 127)
            {
                FUN_40c040();
                return;
            }
            if (g_4d5bb8->controls[3] > 127)
            {
                FUN_40c0d0();
                return;
            }
        }
        if (!steered)
        {
            FUN_40c4e0();
            FUN_414940();
            FUN_4149e0();
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x40c6c0
void FUN_40c6c0()
{
    if (g_4d5bb8->unkc78 && g_4d5bb8->controls[4] && !g_4d5bb8->prevControls[4])
    {
        if (g_4d5bb8->unk1cf8 >= 0.5f)
        {
            FUN_40c170();
        }
        else
        {
            FUN_40c1a0();
        }
    }
}

void FUN_40ce60();

// FUNCTION: STUNTGP_D3D 0x4143e0
void FUN_4143e0(float amount)
{
    g_4d5bb8->unk1cf4 += amount;
    if (g_4d5bb8->unk1cf4 > g_4d5bb8->unk24c)
    {
        g_4d5bb8->unk1cf4 = g_4d5bb8->unk24c;
    }
}

// FUNCTION: STUNTGP_D3D 0x414420
void FUN_414420(float amount)
{
    g_4d5bb8->unk1cf4 -= amount;
    if (g_4d5bb8->unk1cf4 < -g_4d5bb8->unk24c)
    {
        g_4d5bb8->unk1cf4 = -g_4d5bb8->unk24c;
    }
}

// Digital steering: holding a direction ramps up an index into the steering curve.
// FUNCTION: STUNTGP_D3D 0x40cf90
void FUN_40cf90()
{
    FUN_40ce60();
    float boost = g_4d5bb8->unk22c4 + 1.0f;
    if (g_4d5bb8->controls[2])
    {
        FUN_4143e0(g_4d5bb8->unk1188[0][g_4d5bb8->unk2298] * g_4d5bb8->unk250 * boost);
        g_4d5bb8->unk2298++;
    }
    else if (g_4d5bb8->controls[3])
    {
        FUN_414420(g_4d5bb8->unk1188[0][g_4d5bb8->unk2298] * g_4d5bb8->unk250 * boost);
        g_4d5bb8->unk2298++;
    }
    else
    {
        g_4d5bb8->unk2298 -= 6;
    }
    if (g_4d5bb8->unk2298 < 0)
    {
        g_4d5bb8->unk2298 = 0;
    }
    else if (g_4d5bb8->unk2298 > 127)
    {
        g_4d5bb8->unk2298 = 127;
    }
}

// FUNCTION: STUNTGP_D3D 0x40ced0
void FUN_40ced0()
{
    FUN_40ce60();
    float boost = g_4d5bb8->unk22c4 + 1.0f;
    if (g_4d5bb8->controls[3])
    {
        FUN_4143e0(g_4d5bb8->unk1188[0][g_4d5bb8->unk2298] * g_4d5bb8->unk250 * boost);
        g_4d5bb8->unk2298++;
    }
    else if (g_4d5bb8->controls[2])
    {
        FUN_414420(g_4d5bb8->unk1188[0][g_4d5bb8->unk2298] * g_4d5bb8->unk250 * boost);
        g_4d5bb8->unk2298++;
    }
    else
    {
        g_4d5bb8->unk2298 -= 6;
    }
    if (g_4d5bb8->unk2298 < 0)
    {
        g_4d5bb8->unk2298 = 0;
    }
    else if (g_4d5bb8->unk2298 > 127)
    {
        g_4d5bb8->unk2298 = 127;
    }
}

// FUNCTION: STUNTGP_D3D 0x40ce60
void FUN_40ce60()
{
    if (g_4d5bb8->controls[7])
    {
        g_4d5bb8->unk22c4 += 0.1f;
    }
    else
    {
        g_4d5bb8->unk22c4 -= 0.42857143f;
    }
    if (g_4d5bb8->unk22c4 < 0.0f)
    {
        g_4d5bb8->unk22c4 = 0.0f;
        return;
    }
    if (g_4d5bb8->unk22c4 > 3.0f)
    {
        g_4d5bb8->unk22c4 = 3.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x40c710
void FUN_40c710()
{
    FUN_40c220();
    FUN_40c320();
    FUN_40cf90();
    FUN_40c5f0();
    FUN_40c6c0();
}

// FUNCTION: STUNTGP_D3D 0x40c730
void FUN_40c730()
{
    FUN_40c220();
    FUN_40c320();
    FUN_40c500();
    FUN_40c5f0();
    FUN_40c6c0();
}

// FUNCTION: STUNTGP_D3D 0x40cb90
void FUN_40cb90()
{
    if (g_4d5bb8->unk71ec)
    {
        g_4d5bb8->unk1cf8 *= 0.9f;
    }
    g_4d5bb8->unk22b4 = g_4d5bb8->unk22bc;
    g_4d5bb8->unk22bc = 0;
    g_4d5bb8->unk2250 = 0;
    if (!g_4d5bb8->unk71ec && g_4d5bb8->unk71fc > 60.0f)
    {
        return;
    }
    if ((g_4d5bb8->unk1f10 && g_4d5bb8->controls[0]) || (!g_4d5bb8->unk1f10 && g_4d5bb8->controls[1]))
    {
        g_4d5bb8->unk1cf8 += 0.15f;
        if (g_4d5bb8->unk1cf8 > 1.0f)
        {
            g_4d5bb8->unk1cf8 = 1.0f;
        }
        if (g_4d5bb8->controls[8])
        {
            g_4d5bb8->unk2250 = 1;
        }
        g_4d5bb8->unk22bc = 1;
    }
    else if (g_4d5bb8->unk71ec)
    {
        g_4d5bb8->unk1cf8 *= 0.5f;
    }
}

// Digital brake: holding the pedal ramps up an index into the brake curve.
// FUNCTION: STUNTGP_D3D 0x40cc90
void FUN_40cc90()
{
    Car *car = g_4d5bb8;
    if (car->unk71ec)
    {
        car->unk22b8 = car->unk22c0;
        car->unk22c0 = 0;
        if ((car->unk1f10 && car->controls[1]) || (!car->unk1f10 && car->controls[0]))
        {
            car->unk22c0 = 1;
            float torque = -(car->unk1188[1][car->unk229c] * car->unkd58);
            car->unk229c += 6;
            if (car->controls[6])
            {
                car->wheels[0].unk04 = 0.0f;
                car->wheels[1].unk04 = 0.0f;
                FUN_415630();
                car = g_4d5bb8;
            }
            else
            {
                if (car->wheels[0].unk04 < 0.0f)
                {
                    torque = -torque;
                }
                float front = torque * car->unkd5c;
                car->wheels[0].unk00 = front;
                car->wheels[1].unk00 = front;
                float rear = (1.0f - car->unkd5c) * torque;
                car->wheels[2].unk00 = rear;
                car->wheels[3].unk00 = rear;
                front = (float)fabs(front) + (float)fabs(front);
                rear = (float)fabs(rear) + (float)fabs(rear);
                if ((float)fabs(car->wheels[0].unk04) < front)
                {
                    FUN_413430(0);
                    car = g_4d5bb8;
                }
                if ((float)fabs(car->wheels[1].unk04) < front)
                {
                    FUN_413430(1);
                    car = g_4d5bb8;
                }
                if ((float)fabs(car->wheels[2].unk04) < rear)
                {
                    FUN_413430(2);
                    car = g_4d5bb8;
                }
                if ((float)fabs(car->wheels[3].unk04) < rear)
                {
                    FUN_413430(3);
                }
                for (unsigned int i = 0; i < 4; i++)
                {
                    FUN_414ac0(i);
                }
                FUN_415630();
                car = g_4d5bb8;
            }
        }
        else
        {
            car->unk229c -= 40;
            if (car->unk229c < 0)
            {
                car->unk229c = 0;
            }
        }
        if (car->unk229c > 127)
        {
            car->unk229c = 127;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x40d050
void FUN_40d050()
{
    if (g_4d5bb8->unkc78 == 1 && g_4d5bb8->controls[4] && !g_4d5bb8->prevControls[4])
    {
        if (g_4d5bb8->unk1cf8 > 0.5f)
        {
            FUN_40c170();
        }
        else
        {
            FUN_40c1a0();
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x40d090
void FUN_40d090()
{
    if (g_4d5bb8->controls[5] && !g_4d5bb8->prevControls[5])
    {
        g_4d5bb8->unk7234 = g_612948.unk03b4;
    }
    if (!g_4d5bb8->unk71ec && g_4d5bb8->unk71f0)
    {
        int steered = 0;
        if ((float)fabs(g_4d5bb8->unk7218) < 0.2f)
        {
            if (g_4d5bb8->controls[1])
            {
                FUN_40bfb0();
                steered = 1;
            }
            else if (g_4d5bb8->controls[0])
            {
                FUN_40bf20();
                steered = 1;
            }
        }
        if ((float)fabs(g_4d5bb8->unk7214) < 0.2f)
        {
            if (g_4d5bb8->controls[2])
            {
                FUN_40c040();
                return;
            }
            if (g_4d5bb8->controls[3])
            {
                FUN_40c0d0();
                return;
            }
        }
        if (!steered)
        {
            FUN_40c4e0();
            FUN_414940();
            FUN_4149e0();
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x40d160
void FUN_40d160()
{
    FUN_40d050();
    FUN_40cb90();
    FUN_40cc90();
    FUN_40ced0();
    FUN_40d090();
}

// FUNCTION: STUNTGP_D3D 0x40d650
void FUN_40d650(float *v)
{
    Car *car = g_4d5bb8;
    if (car->unk7648 != 1 && car->unk2570 <= 10.0f)
    {
        float f = car->unk1cf0 * 0.013333334f;
        if (f > 1.0f)
        {
            f = 1.0f;
        }
        *v *= 1.0f - f * f;
    }
}

// FUNCTION: STUNTGP_D3D 0x40d6b0
void FUN_40d6b0()
{
    char text[64];
    if (g_4d5bb8->unk7648 != 1)
    {
        if (g_4d5bb8->unk2570 > 10.0f)
        {
            g_4d5bb8->race.unk7c = 0;
            return;
        }
        g_4d5bb8->unk2578 = (g_4d5bb8->unk2578 + 1) % 60;
        if (g_4d5bb8->race.unk7c == 0)
        {
            // STRING: STUNTGP_D3D 0x473a1c
            sprintf(text, "%s %s\n", g_60f02c[g_4d5bb8 - g_49a1f8].name, g_6127a0[22]);
            FUN_442cf0(180, text, g_4d5bb8, 0, 0);
            g_4d5bb8->race.unk7c++;
            g_4d5bb8->unk2578 = 0;
        }
    }
}

// Reads this tick's controls; they are held released while the car is locked out.
// FUNCTION: STUNTGP_D3D 0x40d790
void FUN_40d790()
{
    if (g_4d5bb8->active == 1)
    {
        if (g_4d5bb8->unk7644 != 0)
        {
            g_4d5bb8->unk7644--;
            g_4d5bb8->unk1cfc = 0;
            FUN_40cb90();
        }
        if (g_4d5bb8->unk2278 == 0 || g_4d5bb8->unk7644 != 0)
        {
            g_4d5bb8->controls[0] = 0;
            g_4d5bb8->controls[1] = 0;
            g_4d5bb8->controls[4] = 0;
            g_4d5bb8->controls[5] = 0;
            g_4d5bb8->controls[8] = 0;
            g_4d5bb8->controls[9] = 0;
            if (g_4d5bb8->unk7648 == 1)
            {
                g_4d5bb8->controls[2] = 0;
                g_4d5bb8->controls[3] = 0;
            }
        }
        else
        {
            switch (g_4d5bb8->inputMode)
            {
            case 0:
                FUN_40c730();
                break;
            case 2:
            case 4:
                FUN_40d160();
                break;
            case 1:
            case 3:
                FUN_40c710();
                break;
            }
        }
        FUN_40d6b0();
    }
}

// Splits drive torque between the axles by drive mode (0 front, 1 rear, 2 4WD).
// FUNCTION: STUNTGP_D3D 0x40e3a0
void FUN_40e3a0(float torque)
{
    if (torque > 0.0f && g_4d5bb8->unk2254 != 0.0f && g_4d5bb8->unk1fd8 == 0)
    {
        float boost = torque * g_4d5bb8->unk2258;
        torque += boost;
    }
    torque *= 4.0f;
    switch (g_4d5bb8->unkc70)
    {
    case 2:
    {
        float rear = torque * g_4d5bb8->unkca8;
        g_4d5bb8->wheels[2].unk00 += rear;
        g_4d5bb8->wheels[3].unk00 += rear;
        torque *= 1.0f - g_4d5bb8->unkca8;
    }
    case 0:
        g_4d5bb8->wheels[0].unk00 += torque;
        g_4d5bb8->wheels[1].unk00 += torque;
        break;
    case 1:
        g_4d5bb8->wheels[2].unk00 += torque;
        g_4d5bb8->wheels[3].unk00 += torque;
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x40e470
void FUN_40e470()
{
    Car *car = g_4d5bb8;
    if (car->unk1f14 < 1.0f)
    {
        car->unk1f14 += 1.0f / (car->unkca0 * 60.0f);
        if (car->unk1f14 >= 1.0f)
        {
            car->unk1f14 = 1.0f;
        }
        if (car->unk1f14 < 0.5f && car->unk1cf8 > 0.0f)
        {
            car->unk1cf8 = 0.0f;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x40e4f0
void FUN_40e4f0()
{
    Car *car = g_4d5bb8;
    unsigned int gear = car->unk1f10;
    if (gear > 2)
    {
        if (car->wheels[2].unk04 * car->unkc7c[gear] * car->unkc7c[0] * 3600.0f / (car->unkcb8[0].x * 6.2831855f) <
            car->unk464 * 0.9f - 2500.0f)
        {
            FUN_40c1a0();
        }
    }
}

// Automatic gearbox: shifts up near the rev limit, down when the revs drop or the car slows.
// FUNCTION: STUNTGP_D3D 0x40e550
void FUN_40e550()
{
    if ((g_4722d0->data->unk767c == 1 || g_4722d0->data->race.unk00 <= 60) && !g_4d5bb8->unkc78)
    {
        if (g_4d5bb8->unk1cfc < g_4d5bb8->unk460 + 200.0f && !g_4d5bb8->unk22b4 && !g_4d5bb8->unk22bc &&
            !g_4d5bb8->unk22b8 && !g_4d5bb8->unk22c0 && g_4d5bb8->unk1f10 != 1 && !g_4d5bb8->controls[4])
        {
            FUN_40c1f0();
        }
        if (g_4d5bb8->unk1f1c)
        {
            g_4d5bb8->unk1f1c--;
            g_4d5bb8->unk1cfc += 200.0f;
        }
        if (g_4d5bb8->unk1f14 == 1.0f)
        {
            if (g_4d5bb8->unk1cf8 >= 0.4f)
            {
                if (g_4d5bb8->unk1f10 == 1)
                {
                    if (g_4d5bb8->unk464 * 0.5f < g_4d5bb8->unk1cfc)
                    {
                        FUN_40c170();
                    }
                }
                else if (g_4d5bb8->unk1f10 != 0)
                {
                    FUN_40e4f0();
                    if (g_4d5bb8->unk1f10 < 7 && g_4d5bb8->unk464 * 0.9f < g_4d5bb8->unk1cfc)
                    {
                        FUN_40c170();
                    }
                }
            }
            else
            {
                if ((g_4d5bb8->unk1f10 == 1 || g_4d5bb8->unk1f10 == 2) && g_4d5bb8->unk22c0 == 1 &&
                    (float)fabs(g_4d5bb8->unk1cf0 < 8.333333f) != 0.0f)
                {
                    FUN_40c1a0();
                }
                if (g_4d5bb8->unk1f10 > 2 && g_4d5bb8->unk1cfc < g_4d5bb8->unk464 * 0.4f)
                {
                    FUN_40c1a0();
                }
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x40e710
float FUN_40e710(float v)
{
    switch (g_4d5bb8->unkc70)
    {
    case 0:
        if (g_4d5bb8->wheels[1].unk70 + g_4d5bb8->wheels[0].unk70 < 8)
        {
            return v * 0.25f;
        }
        break;
    case 1:
        if (g_4d5bb8->wheels[3].unk70 + g_4d5bb8->wheels[2].unk70 < 8)
        {
            return v * 0.25f;
        }
        break;
    case 2:
        if (g_4d5bb8->wheels[3].unk70 + g_4d5bb8->wheels[2].unk70 + g_4d5bb8->wheels[1].unk70 +
                g_4d5bb8->wheels[0].unk70 <
            16)
        {
            return v * 0.25f;
        }
        break;
    }
    return v;
}

// FUNCTION: STUNTGP_D3D 0x40ead0
void FUN_40ead0()
{
    Car *car = g_4d5bb8;
    if (car->unk2570 < car->unk2574 * car->unkf74)
    {
        car->unk2250 = 0;
    }
    if (car->unk2250 == 1)
    {
        car->unk2254 += car->unkd60;
        if (car->unk2254 >= car->unkd64)
        {
            car->unk2254 = car->unkd64 - 1.0f;
        }
    }
    else
    {
        car->unk2254 *= car->unkd68;
        if (car->unk2254 < 50.0f)
        {
            car->unk2254 = 0.0f;
            car->unk2258 = 0.0f;
            return;
        }
    }
    unsigned int i = (int)(car->unk2254 * 128.0f / car->unkd64);
    if (i >= 128)
    {
        i = 127;
    }
    car->unk2258 = car->unkd70[i] * car->unkd6c;
}

// FUNCTION: STUNTGP_D3D 0x40eba0
void FUN_40eba0()
{
    if (g_4d5bb8->unk1f10 == 0)
    {
        g_4d5bb8->unk2250 = 0;
        float limit = g_4d5bb8->unk464 * 0.5f;
        while (g_4d5bb8->unk1cfc > limit)
        {
            g_4d5bb8->unk1cfc *= 0.8f;
        }
    }
}

void FUN_4057e0(Car *car, float *v);

void FUN_405800(Car *car, float *v);

// FUNCTION: STUNTGP_D3D 0x40ec00
void FUN_40ec00(float v)
{
    unsigned int i = v * 128.0f / g_4d5bb8->unk045c;
    if (i >= 128)
    {
        i = 127;
    }
    v = g_4d5bb8->unkf84[i] * g_4d5bb8->unkf80;
    if (g_4d5bb8->unk2640 == 1)
    {
        FUN_405800(g_4d5bb8, &v);
    }
    g_4d5bb8->unk2270 -= v;
    g_4d5bb8->unk2570 -= v * g_4d5bb8->unk2574 / g_4d5bb8->unkf78;
    if (g_4d5bb8->unk2570 < 0.0f)
    {
        g_4d5bb8->unk2570 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x40eca0
void FUN_40eca0(float v)
{
    unsigned int i = v * 128.0f / g_4d5bb8->unkd64;
    if (i >= 128)
    {
        i = 127;
    }
    v = g_4d5bb8->unkf84[i] * g_4d5bb8->unkf70;
    if (g_4d5bb8->unk2640 == 1)
    {
        FUN_4057e0(g_4d5bb8, &v);
    }
    g_4d5bb8->unk2570 -= v * g_4d5bb8->unk2574 / g_4d5bb8->unkf78;
    if (g_4d5bb8->unk2570 < 0.0f)
    {
        g_4d5bb8->unk2570 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x40ed30
void FUN_40ed30()
{
    if (g_60f2b4 != 3 && g_4d5bb8->unk24e0 != 1)
    {
        FUN_40ec00(g_4d5bb8->unk1cfc);
        FUN_40eca0(g_4d5bb8->unk2254);
    }
}

// FUNCTION: STUNTGP_D3D 0x40edd0
void FUN_40edd0()
{
    if (g_4d5bb8->unk1fd8 == 0)
    {
        float v = g_4d5bb8->unk1cf0 * 0.6f;
        v *= v;
        float f = v * g_4d5bb8->unk1fd0 * g_4d5bb8->unkcb4 * g_4d5bb8->unkcb0 * -0.615f;
        g_4d5bb8->unk1f24 = f;
        f /= g_4d5bb8->unk2618 * 4.0f;
        Vec4 d;
        d.x = f * g_4d5bb8->axisY.x;
        d.y = f * g_4d5bb8->axisY.y;
        d.z = f * g_4d5bb8->axisY.z;
        g_4d5bb8->unk1c8c.x += d.x;
        g_4d5bb8->unk1c8c.y += d.y;
        g_4d5bb8->unk1c8c.z += d.z;
    }
}

// FUNCTION: STUNTGP_D3D 0x40ee70
void FUN_40ee70()
{
    Car *car = g_4d5bb8;
    g_4d5bb8->unk2894 = (((g_4d5bb8->unk2240[0] + g_4d5bb8->unk2240[2]) * 0.5f -
                          (g_4d5bb8->unk2240[1] + g_4d5bb8->unk2240[3]) * 0.5f) *
                             (1.0f / ((g_4d5bb8->unk238 + g_4d5bb8->unk234) * 0.5f)) +
                         g_4d5bb8->unk2894) *
                        0.5f;
    float roll = -1.0f / g_4d5bb8->unk230 * ((g_4d5bb8->unk2240[1] + g_4d5bb8->unk2240[0]) * 0.5f -
                                             (g_4d5bb8->unk2240[3] + g_4d5bb8->unk2240[2]) * 0.5f);
    if (g_4d5bb8->unk2250 == 1 && (float)fabs(g_4d5bb8->unk1cf0) < 50.0f && roll < 0.0f)
    {
        roll *= g_4d5bb8->unk2254 * 16.0f / g_4d5bb8->unkd64 / (g_4d5bb8->unk1cf0 * 0.1f + 1.0f);
    }
    g_4d5bb8->unk2890 = (roll * 0.125f + g_4d5bb8->unk2890) * 0.95f;
    if (g_4d5bb8->unk2890 > 0.3f)
    {
        g_4d5bb8->unk2890 = 0.3f;
    }
    else if (g_4d5bb8->unk2890 < -0.3f)
    {
        g_4d5bb8->unk2890 = -0.3f;
    }
    g_4d5bb8->unk288c = 0.0f;
    for (int i = 0; i < 4; i++)
    {
        car->unk288c += car->unk2240[i];
    }
    g_4d5bb8->unk288c *= -0.25f;
    g_4d5bb8->unk288c += g_4d5bb8->unk248;
}

extern float g_482670;

// Static wheel loads plus the pitch and roll transfer from the current acceleration.
// Integrates the four suspension springs, with random jitter on rough ground.
// FUNCTION: STUNTGP_D3D 0x40efe0
void FUN_40efe0()
{
    float sum = 0.0f;
    Wheel *w = &g_4d5bb8->wheels[0];
    for (int i = 0; i < 4; i++)
    {
        float v = g_4d5bb8->unk2240[i];
        float d = w->unk0c - w->unk10;
        sum += w->unk0c;
        if (g_4d5bb8->wheels[i].unk88 != 0.0f && (g_612948.unk03b4 & 3) == 0)
        {
            d = ((FUN_42f1c0(g_4d5bb8->wheels[i].unk88 * 2.0f) - g_4d5bb8->wheels[i].unk88) * g_4d5bb8->unk1cf0 *
                 0.0054f) *
                    3.0f +
                d;
        }
        Suspension *s = &g_4d5bb8->suspension[i];
        if (v >= 0.0f)
        {
            d *= s->maxStiffnessIn;
            v = s->maxDampingIn;
        }
        else
        {
            d *= s->maxStiffnessOut;
            v = s->maxDampingOut;
        }
        g_4d5bb8->unk2240[i] = v * g_4d5bb8->unk2240[i] + d;
        v = g_4d5bb8->unk2240[i];
        if (v > s->maxTravelIn)
        {
            g_4d5bb8->unk2240[i] = s->maxTravelIn;
        }
        else if (v < -s->maxTravelOut)
        {
            g_4d5bb8->unk2240[i] = -s->maxTravelOut;
        }
        w++;
    }
    g_4d5bb8->unk2898 = sum * 0.25f;
    FUN_40ee70();
}

// FUNCTION: STUNTGP_D3D 0x40f130
void FUN_40f130()
{
    float lat = g_4d5bb8->axisX.z * g_4d5bb8->unk1cac.z + g_4d5bb8->axisX.y * g_4d5bb8->unk1cac.y +
                g_4d5bb8->axisX.x * g_4d5bb8->unk1cac.x;
    float weight = g_482670 * g_4d5bb8->unk2618;
    float front = g_4d5bb8->unk224 * 0.5f;
    float rear = g_4d5bb8->unk228 * 0.5f;
    float pitch = (g_4d5bb8->axisZ.z * g_4d5bb8->unk1cac.z + g_4d5bb8->axisZ.y * g_4d5bb8->unk1cac.y +
                   g_4d5bb8->axisZ.x * g_4d5bb8->unk1cac.x) *
                  g_4d5bb8->unk2618 * g_4d5bb8->unk261c / g_4d5bb8->unk230;
    g_4d5bb8->wheels[1].unk0c = g_4d5bb8->wheels[0].unk0c = front * weight + pitch;
    g_4d5bb8->wheels[3].unk0c = g_4d5bb8->wheels[2].unk0c = weight * rear - pitch;
    float roll =
        lat * (g_4d5bb8->unk2618 * g_4d5bb8->unk261c) / ((g_4d5bb8->unk238 + g_4d5bb8->unk234) * 0.5f);
    g_4d5bb8->wheels[0].unk0c -= roll;
    g_4d5bb8->wheels[2].unk0c -= roll;
    g_4d5bb8->wheels[1].unk0c += roll;
    g_4d5bb8->wheels[3].unk0c += roll;
}

void Matrix_Multiply3(float *a, float *b);

// FUNCTION: STUNTGP_D3D 0x40f250
void FUN_40f250()
{
    float m[16];
    float pitch = (g_4d5bb8->axisZ.z * g_4d5bb8->unk1cac.z + g_4d5bb8->axisZ.y * g_4d5bb8->unk1cac.y +
                   g_4d5bb8->axisZ.x * g_4d5bb8->unk1cac.x) *
                  g_4d5bb8->unk261c / g_4d5bb8->unk230;
    float roll = (g_4d5bb8->axisX.z * g_4d5bb8->unk1cac.z + g_4d5bb8->axisX.y * g_4d5bb8->unk1cac.y +
                  g_4d5bb8->axisX.x * g_4d5bb8->unk1cac.x) *
                 g_4d5bb8->unk261c / ((g_4d5bb8->unk238 + g_4d5bb8->unk234) * 0.5f);
    Matrix_Transpose(m, g_4d5bb8->matrix);
    Matrix_RotateX(m, -pitch);
    Matrix_RotateZ(m, roll);
    Matrix_Multiply3(m, g_4d5bb8->matrix);
    Matrix_Multiply3(g_4d5bb8->unk1c0c, m);
}

// FUNCTION: STUNTGP_D3D 0x40f330
void FUN_40f330(float *m, float scale)
{
    Vec4 r0;
    Vec4 r1;
    Vec4 r2;
    r0.x = m[0];
    r0.y = m[1];
    r0.z = m[2];
    r1.x = m[4];
    r1.y = m[5];
    r1.z = m[6];
    r2.x = m[8];
    r2.y = m[9];
    r2.z = m[10];
    float inv;
    r0.x *= inv = 1.0f / scale;
    r1.y *= inv;
    r2.z *= inv;
    Vec3_Normalize(&r0.x);
    Vec3_Normalize(&r1.x);
    Vec3_Normalize(&r2.x);
    Matrix_FromRows(&r0.x, &r1.x, &r2.x, m);
}


// FUNCTION: STUNTGP_D3D 0x40f3c0
void FUN_40f3c0()
{
    g_4d5bb8->wheels[3].unk10 = g_4d5bb8->wheels[2].unk10 = g_4d5bb8->wheels[1].unk10 = g_4d5bb8->wheels[0].unk10 =
        g_482670 * g_4d5bb8->unk2618 * 0.25f;
}

// FUNCTION: STUNTGP_D3D 0x40f3f0
void FUN_40f3f0(Vector4 *a, Wheel *wheel, float v, float *out, int index)
{
    v = (float)fabs(v);
    float s = v * 1.3424487f;
    float f = -(((s * s * 3.5000001e-05f + 0.15f) * (1.0f / a->y) + 0.005f) * wheel->unk0c /
                (g_4d5bb8->unk2618 * 0.25f));
    f = (f * g_4d5bb8->wheels[index].unk8c * 100.0f) * 0.00027777778f;
    if ((float)fabs(f) > v)
    {
        f = -v;
    }
    if (wheel->unk04 < 0.0f)
    {
        f = -f;
    }
    wheel->unk1c = f;
    wheel->unk04 += f;
    *out += f * 0.5f;
}

void FUN_405860(Car *car, float *v);

// FUNCTION: STUNTGP_D3D 0x40f4a0
void FUN_40f4a0(float *a, float *b, int unused)
{
    float s = g_4d5bb8->unk1cf0 * 0.6f;
    float f = (s * s) * g_4d5bb8->unk1fd0 * g_4d5bb8->unkcb4 * g_4d5bb8->unkcac * 0.61283678f;
    if (g_4d5bb8->unk2640 == 1)
    {
        FUN_405860(g_4d5bb8, &f);
    }
    g_4d5bb8->unk1f20 = f;
    float d = (f / g_4d5bb8->unk2618 * 100.0f) * 0.00027777778f;
    g_4d5bb8->unk1f28 -= d;
    *a -= d;
    *b -= d;
    g_4d5bb8->wheels[0].unk04 -= d;
    g_4d5bb8->wheels[1].unk04 -= d;
    g_4d5bb8->wheels[2].unk04 -= d;
    g_4d5bb8->wheels[3].unk04 -= d;
}

// FUNCTION: STUNTGP_D3D 0x40f570
void FUN_40f570()
{
    Car *car = g_4d5bb8;
    unsigned int i = (float)fabs(car->unk1cf0);
    if (i > 127)
    {
        i = 127;
    }
    car->unk1cf4 *= car->unk258[i];
}

// Clips a tyre's slip forces to its friction circle; unk30 gets the slip ratio.
// FUNCTION: STUNTGP_D3D 0x40f5b0
void FUN_40f5b0(float *fx, float *fy, float grip, float scale, float load, int i)
{
    load /= g_4d5bb8->unk2618 * 0.25f;
    grip *= g_4d5bb8->wheels[i].unk84;
    scale *= g_4d5bb8->wheels[i].unk84;
    float x = *fx;
    float y = *fy;
    float s = (float)sqrt(x * x + y * y * 0.64000005f);
    unsigned int idx = s;
    if (idx >= 128)
    {
        idx = 127;
    }
    float mu = load * g_4d5bb8->tyreFrictionEnv[idx];
    float lim = mu * grip;
    if ((float)fabs(lim) < 0.01f)
    {
        lim = 0.01f;
    }
    g_4d5bb8->wheels[i].unk30 = (float)fabs(s / lim);
    if (s > lim)
    {
        float t = (float)fabs(x);
        if (t >= mu)
        {
            t = mu;
        }
        t *= scale;
        if (x < 0.0f)
        {
            x = t + x;
        }
        else
        {
            x = x - t;
        }
        if (y > 0.0f)
        {
            mu *= 3.0f;
        }
        load = (float)fabs(y);
        if (load >= mu)
        {
            load = mu;
        }
        load *= scale;
        if (y < 0.0f)
        {
            y = -load;
        }
        else
        {
            y = load;
        }
    }
    else
    {
        x = 0.0f;
    }
    *fx = x;
    *fy = y;
}

// FUNCTION: STUNTGP_D3D 0x40f730
void FUN_40f730()
{
    float sum = 0.0f;
    for (int i = 0; i < 4; i++)
    {
        sum += g_4d5bb8->wheels[i].unk30;
    }
    g_4d5bb8->unk289c = sum * 0.25f;
}

void FUN_44efd0(float *out, float *a, float *b);
void FUN_44f8e0(float *m);

// Rotates m about the axis from body point i to the body centre (angle in radians).
// FUNCTION: STUNTGP_D3D 0x40f760
void FUN_40f760(Body *body, int i, float angle, float *m)
{
    Vec4 dir;
    dir.x = body->pos.x - body->points[i].world.x;
    dir.y = body->pos.y - body->points[i].world.y;
    dir.z = body->pos.z - body->points[i].world.z;
    Vec3_Normalize(&dir.x);
    Vec4 up;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    Vec4 side;
    side.x = up.y * dir.z - up.z * dir.y;
    side.y = up.z * dir.x - up.x * dir.z;
    side.z = up.x * dir.y - up.y * dir.x;
    Vec3_Normalize(&side.x);
    up.x = side.y * dir.z - side.z * dir.y;
    up.y = side.z * dir.x - side.x * dir.z;
    up.z = side.x * dir.y - side.y * dir.x;
    Vec3_Normalize(&up.x);
    float basis[16];
    float local[16];
    float rot[16];
    Matrix_FromRows(&side.x, &up.x, &dir.x, basis);
    Matrix_Transpose(local, basis);
    Matrix_RotateY(local, angle * 57.295776f);
    FUN_44efd0(rot, local, basis);
    FUN_44f8e0(rot);
    Matrix_Multiply3(m, rot);
}

// FUNCTION: STUNTGP_D3D 0x40fb00
void FUN_40fb00()
{
    if (g_4d5bb8->unk1fd8 == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            g_4d5bb8->wheels[i].unk04 *= 0.995f;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x40fb30
void FUN_40fb30()
{
    Car *car = g_4d5bb8;
    int n = 0;
    for (int i = 0; i < 4; i++)
    {
        if (car->wheels[i].unk70 < 4)
        {
            n++;
        }
    }
    if (car->unk1fd8 == 0)
    {
        car->unk1fdc = 16;
    }
    else if (car->unk1fdc > 0)
    {
        car->unk1fdc--;
    }
    g_4d5bb8->unk1fd4 = g_4d5bb8->unk1fd8;
    if (n == 0)
    {
        car->unk1fd8 = 0;
    }
    else if (n == 4)
    {
        car->unk1fd8 = 1;
    }
    else
    {
        car->unk1fd8 = 2;
    }
}

// FUNCTION: STUNTGP_D3D 0x40fbb0
void FUN_40fbb0()
{
    Car *car = g_4d5bb8;
    if (car->unk1fd8 == 0)
    {
        float d = g_482678 * car->axisX.x + g_482680 * car->axisX.z + g_48267c * car->axisX.y;
        if (fabs(d) >= 0.2079116)
        {
            if (car->unk1cf0 < 1.0f)
            {
                d = 0.0f;
            }
            float k = car->unk2618 * car->unk224 * d * 0.003125f;
            Vec4 f;
            f.x = k * car->axisX.x;
            f.y = k * car->axisX.y;
            f.z = k * car->axisX.z;
            car->unk284c.x += f.x;
            car->unk284c.y += f.y;
            car->unk284c.z += f.z;
        }
    }
}

// STUB: STUNTGP_D3D 0x40fc90
void FUN_40fc90()
{
}

extern float *g_4d5b24;
void FUN_424120(int slot);
void FUN_4241a0(int slot);
void FUN_424210(int slot);
void FUN_424290(int slot);

// FUNCTION: STUNTGP_D3D 0x410780
void FUN_410780(int slot)
{
    float f = (float)fabs(g_4d5bb8->axisX.z * g_4d5bb8->unk1cac.z + g_4d5bb8->axisX.y * g_4d5bb8->unk1cac.y +
                          g_4d5bb8->axisX.x * g_4d5bb8->unk1cac.x) *
                  6000.0f +
              g_4d5bb8->wheels[2].unk0c / g_4d5bb8->wheels[2].unk10 * g_4d5bb8->wheels[2].unk84 *
                  g_4d5bb8->wheels[2].unk84 * 4000.0f;
    if (f > 10000.0f)
    {
        f = 10000.0f;
    }
    g_4d5b24[0] = f;
    FUN_4241a0(slot);
}

// FUNCTION: STUNTGP_D3D 0x410800
void FUN_410800(int slot)
{
    Car *car = g_4d5bb8;
    float *ff = g_4d5b24;
    ff[7] = 400000000.0f / car->unk464;
    if (ff[7] < 30000.0f)
    {
        ff[7] = 30000.0f;
    }
    if (ff[7] > 75000.0f)
    {
        ff[7] = 75000.0f;
    }
    if (car->unk1cfc < 4096.0f)
    {
        float f = ((4096.0f - car->unk1cfc) * 0.000244140625f) * 1000.0f / (car->unk7614 + 1);
        if (f > 10000.0f)
        {
            f = 10000.0f;
        }
        ff[6] = f;
        FUN_424210(slot);
        return;
    }
    ff[6] = 0.0f;
    FUN_424210(slot);
}

// FUNCTION: STUNTGP_D3D 0x4108c0
void FUN_4108c0(int slot)
{
    g_4d5b24[1] = g_4d5bb8->race.unk70;
    g_4d5bb8->race.unk70 = 0.0f;
    if (g_4d5b24[1] >= 0.1f)
    {
        g_4d5b24[1] = g_4d5b24[1] * 5000.0f;
        g_4d5b24[2] = 100000.0f;
        if (g_4d5b24[1] >= 500.0f)
        {
            if (g_4d5b24[1] > 10000.0f)
            {
                g_4d5b24[2] = (g_4d5b24[1] * 100000.0f) * 0.0001f;
                g_4d5b24[1] = 10000.0f;
            }
            FUN_424290(slot);
        }
        g_4d5b24[1] = 0.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x410950
void FUN_410950(int slot)
{
    float sum = 0.0f;
    Wheel *w = g_4d5bb8->wheels;
    for (int i = 0; i < 4; i++, w++)
    {
        if (w->unk78 == 2)
        {
            sum += w->unk0c * 2000.0f / w->unk10;
        }
        else if (w->unk78 == 1)
        {
            sum += w->unk0c * 500.0f / w->unk10;
        }
    }
    sum = ((sum * 0.25f) * (float)fabs(g_4d5bb8->unk1cf0)) * 0.01f;
    if (sum > 10000.0f)
    {
        sum = 10000.0f;
    }
    g_4d5b24[4] = 100000.0f;
    g_4d5b24[3] = sum;
    FUN_424120(slot);
}

// FUNCTION: STUNTGP_D3D 0x4109e0
void FUN_4109e0(int slot)
{
    g_4d5b24[6] = 0.0f;
    FUN_424210(slot);
    g_4d5b24[3] = 0.0f;
    FUN_424120(slot);
}

// FUNCTION: STUNTGP_D3D 0x410ad0
void FUN_410ad0()
{
    g_4d5bb8->unk261c = g_4d5bb8->unk22c;
    g_4d5bb8->unk262c = 0;
    g_4d5bb8->unk2628 = 0;
    g_4d5bb8->unk2624 = 0;
}

// FUNCTION: STUNTGP_D3D 0x410b00
void FUN_410b00(int value)
{
    g_4d5bb8->unk261c = g_4d5bb8->unk22c;
    g_4d5bb8->unk262c = 0;
    g_4d5bb8->unk2628 = 0;
    g_4d5bb8->unk2624 = value;
}

// Wheelie / stoppie / two-wheel balance: lifts the centre of mass while only one axle or side is grounded.
// FUNCTION: STUNTGP_D3D 0x410b30
void FUN_410b30()
{
    if (g_4d5bb8->wheels[2].unk70 <= 0 && g_4d5bb8->wheels[3].unk70 <= 0 && g_4d5bb8->wheels[0].unk70 > 2 && g_4d5bb8->wheels[1].unk70 > 2)
    {
        g_4d5bb8->unk262c = 500.0f;
        g_4d5bb8->unk2624 = 24;
    }
    if (g_4d5bb8->wheels[0].unk70 <= 0 && g_4d5bb8->wheels[2].unk70 <= 0 && g_4d5bb8->wheels[1].unk70 > 2 && g_4d5bb8->wheels[3].unk70 > 2)
    {
        g_4d5bb8->unk262c = 500.0f;
        g_4d5bb8->unk2624 = 24;
    }
    if (g_4d5bb8->wheels[1].unk70 <= 0 && g_4d5bb8->wheels[3].unk70 <= 0 && g_4d5bb8->wheels[0].unk70 > 2 && g_4d5bb8->wheels[2].unk70 > 2)
    {
        g_4d5bb8->unk262c = 500.0f;
        g_4d5bb8->unk2624 = 24;
    }
    int air = 0;
    unsigned int ground = 0;
    for (int i = 0; i < 4; i++)
    {
        if (g_4d5bb8->wheels[i].unk70 > 2)
        {
            ground++;
        }
        if (g_4d5bb8->wheels[i].unk70 <= 0)
        {
            air++;
        }
    }
    if (air == 4 || ground >= 3)
    {
        FUN_410ad0();
    }
    else if (g_4d5bb8->unk2624 > 0)
    {
        g_4d5bb8->unk2624--;
        float u = g_482688 * g_4d5bb8->axisY.x + g_48268c * g_4d5bb8->axisY.y + g_482690 * g_4d5bb8->axisY.z;
        float s;
        if (u < 0.0f)
        {
            s = -(u * u);
        }
        else
        {
            s = u * u;
        }
        float f = (s + 1.0f) * g_4d5bb8->unk262c;
        float r = f - g_4d5bb8->unk2628;
        if (r < 0.01f)
        {
            r = 0.01f;
        }
        else if (r > 1.0f)
        {
            r = 1.0f;
        }
        g_4d5bb8->unk261c = g_4d5bb8->unk22c - f * r;
        g_4d5bb8->unk2628 = f;
    }
}


// FUNCTION: STUNTGP_D3D 0x410cd0
void FUN_410cd0()
{
    if (FUN_402590(g_4d5bb8))
    {
        FUN_401220(5, 0, g_60d688[36]);
        FUN_442cf0(180, g_6127a0[48], g_4d5bb8, 2, 0);
    }
}

// FUNCTION: STUNTGP_D3D 0x410d10
void FUN_410d10()
{
    if (FUN_402590(g_4d5bb8))
    {
        FUN_401220(5, 0, g_60d688[35]);
        FUN_442cf0(180, g_6127a0[47], g_4d5bb8, 2, 0);
    }
}

// FUNCTION: STUNTGP_D3D 0x410d50
void FUN_410d50()
{
    if (FUN_402590(g_4d5bb8))
    {
        FUN_401220(5, 0, g_60d688[34]);
        FUN_442cf0(180, g_6127a0[50], g_4d5bb8, 2, 0);
    }
}

// FUNCTION: STUNTGP_D3D 0x410d90
void FUN_410d90()
{
    if (FUN_402590(g_4d5bb8))
    {
        FUN_401220(5, 0, g_60d688[33]);
        FUN_442cf0(180, g_6127a0[49], g_4d5bb8, 2, 0);
    }
}

// FUNCTION: STUNTGP_D3D 0x410dd0
void FUN_410dd0(Car *car)
{
    car->unk71c0 = 0;
    car->unk71bc = 0;
    car->unk71b4 = 0;
    car->unk71b8 = 0;
}

// Counts airborne ticks per wheel pair and awards the matching stunt on landing.
// FUNCTION: STUNTGP_D3D 0x410df0
void FUN_410df0()
{
    if (g_4d5bb8->unk1fd8 == 0)
    {
        if (g_4d5bb8->unk71c0 > 30.0f)
        {
            FUN_410cd0();
        }
        else if (g_4d5bb8->unk71bc > 30.0f)
        {
            FUN_410d10();
        }
        else if (g_4d5bb8->unk71b8 > 60)
        {
            FUN_410d50();
        }
        else if (g_4d5bb8->unk71b4 > 60)
        {
            FUN_410d90();
        }
        g_4d5bb8->unk71b4 = 0;
        g_4d5bb8->unk71b8 = 0;
        g_4d5bb8->unk71c0 = 0;
        g_4d5bb8->unk71bc = 0;
    }
    else if (g_4d5bb8->unk1cf0 >= 200.0f / 60.0f)
    {
        Wheel *w = g_4d5bb8->wheels;
        if (w[2].unk70 <= 0 && w[3].unk70 <= 0 && w[0].unk70 > 2 && w[1].unk70 > 2)
        {
            g_4d5bb8->unk71c0++;
        }
        if (w[0].unk70 <= 0 && w[1].unk70 <= 0 && w[2].unk70 > 2 && w[3].unk70 > 2)
        {
            g_4d5bb8->unk71bc++;
        }
        if (w[0].unk70 <= 0 && w[2].unk70 <= 0 && w[1].unk70 > 2 && w[3].unk70 > 2)
        {
            g_4d5bb8->unk71b8++;
        }
        if (w[1].unk70 <= 0 && w[3].unk70 <= 0 && w[0].unk70 > 2 && w[2].unk70 > 2)
        {
            g_4d5bb8->unk71b4++;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x410f50
void FUN_410f50(Car *car)
{
    car->unk71c4 = 0;
    car->unk71c8 = 0;
    g_4d5bb8->unk71cc.x = 0.0f;
    g_4d5bb8->unk71cc.y = 0.0f;
    g_4d5bb8->unk71cc.z = 0.0f;
}

// Tracks a roll: up-vector flips past 135 degrees while grounded, then lands.
// FUNCTION: STUNTGP_D3D 0x410f80
void FUN_410f80()
{
    if (g_4d5bb8->unk71c8 != 0 && --g_4d5bb8->unk71c8 == 0)
    {
        FUN_410f50(g_4d5bb8);
    }
    if (g_4d5bb8->unk1fd8 == 0 && g_4d5bb8->unk71c4 == 3 && g_4d5bb8->unk71c8 != 0)
    {
        FUN_401220(5, 0, g_60d688[26]);
        FUN_442cf0(180, g_6127a0[56], g_4d5bb8, 2, 100);
        FUN_410f50(g_4d5bb8);
    }
    if (g_4d5bb8->unk1fd4 == 0 && g_4d5bb8->unk1fd8 == 0)
    {
        if (g_4d5bb8->unk71c4 != 3)
        {
            FUN_410f50(g_4d5bb8);
        }
    }
    else if (g_4d5bb8->unk1fd4 == 0 && g_4d5bb8->unk1fd8 != 0)
    {
        g_4d5bb8->unk71cc = g_4d5bb8->axisY;
        g_4d5bb8->unk71c4 = 1;
    }
    else if (g_4d5bb8->unk1fd4 == 1 && g_4d5bb8->unk1fd8 == 1)
    {
        if (g_4d5bb8->unk71c4 == 1 &&
            g_4d5bb8->unk71cc.z * g_4d5bb8->axisY.z + g_4d5bb8->unk71cc.y * g_4d5bb8->axisY.y +
                    g_4d5bb8->unk71cc.x * g_4d5bb8->axisY.x <
                -0.707f)
        {
            g_4d5bb8->unk71c4 = 2;
        }
    }
    else if (g_4d5bb8->unk1fd4 == 1 && g_4d5bb8->unk1fd8 != 1 && g_4d5bb8->unk71c4 == 2)
    {
        g_4d5bb8->unk71c4 = 3;
        g_4d5bb8->unk71c8 = 300;
    }
    if (g_4d5bb8->unk71c4 == 2 &&
        g_4d5bb8->axisZ.z * g_4d5bb8->unk1c8c.z + g_4d5bb8->axisZ.y * g_4d5bb8->unk1c8c.y +
                g_4d5bb8->axisZ.x * g_4d5bb8->unk1c8c.x <
            0.707f)
    {
        FUN_410f50(g_4d5bb8);
    }
}

// FUNCTION: STUNTGP_D3D 0x411140
void FUN_411140(Car *car)
{
    car->unk71dc = 0;
}

// Counts ticks spent driving fast against the car's heading; rewards long reverses.
// FUNCTION: STUNTGP_D3D 0x411150
void FUN_411150()
{
    if (g_4d5bb8->unk1fd8 != 1)
    {
        Vec4 dir = g_4d5bb8->unk1c8c;
        float speed;
        FUN_44eda0(&dir.x, &speed);
        if (speed >= 1000.0f / 60.0f)
        {
            if (dir.x * g_4d5bb8->axisZ.x + dir.y * g_4d5bb8->axisZ.y + dir.z * g_4d5bb8->axisZ.z < 0.9063077)
            {
                g_4d5bb8->unk71dc++;
                return;
            }
            if (g_4d5bb8->unk71dc > 150.0)
            {
                FUN_401220(5, 1, g_60d688[22]);
                FUN_442cf0(180, g_6127a0[74], g_4d5bb8, 2, 0);
            }
            else if (g_4d5bb8->unk71dc > 90.0)
            {
                FUN_401220(4, 0, g_60d688[21]);
                FUN_442cf0(180, g_6127a0[75], g_4d5bb8, 2, 0);
            }
        }
    }
    FUN_411140(g_4d5bb8);
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

// FUNCTION: STUNTGP_D3D 0x411330
void FUN_411330(Car *car)
{
    car->race.unk78 = 0;
    car->unk71e8 = 0;
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

void FUN_410dd0(Car *car);
void FUN_410f50(Car *car);
void FUN_411140(Car *car);
void FUN_411280(Car *car);
void FUN_411410(Car *car);
void FUN_411330(Car *car);
void FUN_4118b0();
void FUN_412430(Car *car);

// FUNCTION: STUNTGP_D3D 0x411490
void FUN_411490(Car *car)
{
    FUN_410dd0(car);
    FUN_410f50(car);
    FUN_411140(car);
    FUN_411280(car);
    FUN_411410(car);
    FUN_411330(car);
    FUN_4118b0();
    FUN_412430(car);
    car->unk71f4 = 0;
}

// FUNCTION: STUNTGP_D3D 0x4114e0
void FUN_4114e0()
{
    if (g_60f2b4 != 2)
    {
        g_4d5bb8->unk2610 = 0.0f;
        return;
    }
    Car *car = g_4d5bb8;
    if (car->unk71ec == 0)
    {
        if (car->unk2610 < 6.4f)
        {
            car->unk2610 += 0.025f;
        }
    }
    else
    {
        float t = car->unk2610 * 0.25f;
        if (t > 0.08f)
        {
            car->unk2610 *= 0.9f;
        }
        else
        {
            car->unk2610 = (1.0f - t) * car->unk2610;
        }
        if (car->unk2610 < 0.01f)
        {
            car->unk2610 = 0.0f;
        }
    }
    g_4d5bb8->unk260c += car->unk2610;
    if (g_4d5bb8->unk260c > 9999999.0f)
    {
        g_4d5bb8->unk260c = 9999999.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x4115c0
void FUN_4115c0()
{
    g_4d5bb8->unk7238 = g_4d5bb8->posY;
    g_4d5bb8->unk723c = 0;
    g_4d5bb8->unk7240 = 0;
}

void FUN_41d1f0(Stat *stat, float value);
void FUN_4163e0(Car *car, float value);

// Landing from a jump: scores the airtime and kicks the car up by how cleanly it came down.
// FUNCTION: STUNTGP_D3D 0x4116f0
void FUN_4116f0()
{
    if (g_4d5bb8->unk71f8 && !g_4d5bb8->unk7250)
    {
        g_4d5bb8->unk7204.x = 0.0f;
        g_4d5bb8->unk7204.y = 0.0f;
        g_4d5bb8->unk7204.z = 0.0f;
        g_4d5bb8->unk2614 = g_4d5bb8->unk260c;
        if (g_4d5bb8->unk7234)
        {
            float d = (float)fabs((float)abs((int)(g_4d5bb8->unk7234 - g_612948.unk03b4)));
            float k = g_4d5bb8->unk1b94 * 60.0f;
            if (d < k)
            {
                d -= g_4d5bb8->unk1b98 * 60.0f;
                if (d < 0.0f)
                {
                    d = 0.0f;
                }
                k = (k - d) / k;
                FUN_41d1f0(&g_4d5bb8->unk2584, k * 100.0f);
                k = k * k;
                FUN_4163e0(g_4d5bb8, k);
                float f = k * g_4d5bb8->unk1b9c / g_4d5bb8->unk2618;
                if (f > 25.0f)
                {
                    f = 25.0f;
                }
                g_4d5bb8->unk1c8c.y = f + g_4d5bb8->unk1c8c.y;
                g_4d5bb8->unk2394 = 1;
                g_4d5bb8->unk2398 = k;
                g_4d5bb8->unk71f0 = 1;
                if (g_4d5bb8->unk7258 < 10)
                {
                    g_4d5bb8->unk7258++;
                }
                if (g_4d5bb8->unk7254 < 0)
                {
                    g_4d5bb8->unk7254 = 270;
                }
                else
                {
                    g_4d5bb8->unk7254 += 270;
                    if (g_4d5bb8->unk7254 > 600)
                    {
                        g_4d5bb8->unk7254 = 600;
                    }
                }
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x411880
void FUN_411880(Car *car)
{
    car->unk7254 = 0;
}

// FUNCTION: STUNTGP_D3D 0x411890
void FUN_411890()
{
    g_4d5bb8->unk7248 = 1;
    g_4d5bb8->unk724c = 0;
}

// FUNCTION: STUNTGP_D3D 0x4118b0
void FUN_4118b0()
{
    g_4d5bb8->unk6db4[0] = 0;
    g_4d5bb8->unk6da4 = 0;
    g_4d5bb8->unk6eb4[0] = 0;
    g_4d5bb8->unk6da8 = 0;
}

// FUNCTION: STUNTGP_D3D 0x4118d0
void FUN_4118d0()
{
    Car *car = g_4d5bb8;
    int i;
    for (i = 0; i <= car->unk6da4; i++)
    {
        car->unk6fb4[i] = car->unk6db4[i];
    }
    for (i = 0; i <= car->unk6da8; i++)
    {
        car->unk70b4[i] = car->unk6eb4[i];
    }
    car->unk6dac = car->unk6da4;
    car->unk6db0 = car->unk6da8;
    FUN_4118b0();
}

// Entry of the 0x98-byte trick table at 0x473a40; the input sequences end with -1.
struct TrickDef
{
    int unk00;         // 0x00, 0 ends the table
    BYTE unk04[0x14];  // 0x04
    char seqA[0x40];   // 0x18, matched against Car::unk6fb4
    char seqB[0x40];   // 0x58, matched against Car::unk70b4
};

// Counts how often the trick's input sequence was completed, capped at 3; 0 on a stray input.
// FUNCTION: STUNTGP_D3D 0x411c10
int FUN_411c10(TrickDef *trick)
{
    int j = 0;
    int hitsA = 0;
    int hitsB = 0;
    int result = 0;
    int i = 1;
    if (trick->seqA[0] != -1)
    {
        int n = g_4d5bb8->unk6dac;
        for (; i <= n; i++)
        {
            int k = g_4d5bb8->unk6fb4[i];
            if (k == trick->seqA[j])
            {
                j++;
                hitsA++;
                if (trick->seqA[j] == -1)
                {
                    j = 1;
                    result++;
                }
            }
            else
            {
                if (j >= 4)
                {
                    return 0;
                }
                j = 0;
                while (k != trick->seqA[j])
                {
                    if (j >= 4)
                    {
                        return 0;
                    }
                    j++;
                }
                if (j >= 4)
                {
                    return 0;
                }
                j++;
            }
        }
        if (hitsA != 0 && g_4d5bb8->unk6db0 >= hitsA)
        {
            return 0;
        }
    }
    else if (trick->seqB[0] != -1)
    {
        int n = g_4d5bb8->unk6db0;
        for (i = 1; i <= n; i++)
        {
            int k = g_4d5bb8->unk70b4[i];
            if (k == trick->seqB[j])
            {
                j++;
                hitsB++;
                if (trick->seqB[j] == -1)
                {
                    j = 1;
                    result++;
                }
            }
            else
            {
                if (j >= 4)
                {
                    return 0;
                }
                j = 0;
                while (k != trick->seqB[j])
                {
                    if (j >= 4)
                    {
                        return 0;
                    }
                    j++;
                }
                if (j >= 4)
                {
                    return 0;
                }
                j++;
            }
        }
        if (hitsB != 0 && g_4d5bb8->unk6dac >= hitsB)
        {
            return 0;
        }
    }
    if (result > 3)
    {
        result = 3;
    }
    return result;
}

// GLOBAL: STUNTGP_D3D 0x474290
int g_474290[24] = {250,   500,   750,   1000,  1250,  1500,  1750,  2000,  2500,  3500,  5000,  7500,
                    10000, 12500, 15000, 17500, 20000, 25000, 30000, 40000, 50000, 60000, 75000, 100000};

// FUNCTION: STUNTGP_D3D 0x411da0
int FUN_411da0(int value, int offset)
{
    unsigned int i = 0;
    while (g_474290[i] != value)
    {
        i++;
    }
    i += offset;
    if (i > 23)
    {
        i = 23;
    }
    return g_474290[i];
}

void FUN_41d1f0(Stat *stat, float value);
void FUN_41d230();

// FUNCTION: STUNTGP_D3D 0x411fa0
void FUN_411fa0()
{
    g_4d5bb8->unk724c = 0;
    g_4d5bb8->unk7250 = 0;
    g_4d5bb8->unk7248 = 0;
    FUN_41d230();
    FUN_41d1f0(&g_4d5bb8->unk2594[0], 0.0f);
    FUN_41d1f0(&g_4d5bb8->unk2594[1], g_4d5bb8->unk260c - g_4d5bb8->unk2614);
    g_4d5bb8->unk2594[1].mean = g_4d5bb8->unk260c / g_4d5bb8->unk2594[1].count;
    g_4d5bb8->unk7254 = 0;
    if (g_4d5bb8->unk7258 != 0)
    {
        g_4d5bb8->unk7258--;
    }
    FUN_406ff0();
}

// FUNCTION: STUNTGP_D3D 0x4121c0
void FUN_4121c0()
{
    Car *car = g_4d5bb8;
    if (car->unk71ec != 0 && car->unk7254 >= 0)
    {
        car->unk7254--;
    }
    if (car->unk7258 != 0 && car->unk7254 < 0)
    {
        if (car->unk7258 >= 1)
        {
            car->unk7260 = 1;
            car->unk7264 = 0;
        }
        car->unk7254 = 0;
        car->unk7258 = 0;
    }
    if (car->unk7260 == 1 && --car->unk7264 < 0)
    {
        if (car->unk725c == 0)
        {
            car->unk725c = 0;
            car->unk7260 = 0;
            return;
        }
        car->unk725c--;
        car->unk7264 = 30;
    }
}

// FUNCTION: STUNTGP_D3D 0x412260
void FUN_412260()
{
    g_4d5bb8->unk7244 = 0;
}

// Steers the velocity around the world up axis by the clamped yaw input.
// FUNCTION: STUNTGP_D3D 0x412270
void FUN_412270()
{
    if (!g_4d5bb8->unk71ec && g_4d5bb8->unk71f0 != 1)
    {
        float s = g_4d5bb8->unk1cf4;
        if (s > 5.0f)
        {
            s = 5.0f;
        }
        else if (s < -5.0f)
        {
            s = -5.0f;
        }
        s *= 0.2f;
        Vec4 v = g_4d5bb8->unk1c8c;
        float len;
        FUN_44eda0(&v.x, &len);
        if (len >= 1.0f)
        {
            Vec4 c;
            c.x = g_482690 * v.y - g_48268c * v.z;
            c.y = g_482688 * v.z - g_482690 * v.x;
            c.z = g_48268c * v.x - g_482688 * v.y;
            len *= 0.012f;
            if (len > 1.0f)
            {
                len = 1.0f;
            }
            float k = len * s;
            c.x = k * c.x;
            c.y = k * c.y;
            c.z = k * c.z;
            g_4d5bb8->unk1c8c.x = c.x + g_4d5bb8->unk1c8c.x;
            g_4d5bb8->unk1c8c.y = c.y + g_4d5bb8->unk1c8c.y;
            g_4d5bb8->unk1c8c.z = c.z + g_4d5bb8->unk1c8c.z;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x412430
void FUN_412430(Car *car)
{
    car->unk71f0 = 0;
    car->unk71fc = 0;
    car->unk7224 = 0;
    car->unk7228 = 0;
    car->unk722c = 0;
    car->unk7214 = 0;
    car->unk7218 = 0;
    car->unk721c = 0;
}

// FUNCTION: STUNTGP_D3D 0x412670
void FUN_412670()
{
    if (g_60eff0 == 3)
    {
        return;
    }
    if (g_4d5bb8->race.unk74)
    {
        g_4d5bb8->race.unk74--;
        g_4d5bb8->unk2634 = (float)g_4d5bb8->race.unk74 * 0.0055555556f + 1.0f;
        g_4d5bb8->unk2250 = 1;
        FUN_40e360(g_4d5bb8);
        FUN_40e380(g_4d5bb8);
        return;
    }
    if (g_4d5bb8->race.unk00 && !g_4d5bb8->unk22b4 && g_4d5bb8->unk22bc == 1 &&
        g_4d5bb8->unk045c * 0.2f < g_4d5bb8->unk1cfc && abs((int)g_4d5bb8->race.unk00 - 60) < 10)
    {
        g_4d5bb8->race.unk74 = 180;
        g_4d5bb8->unk1cfc = g_4d5bb8->unk045c;
        FUN_442cf0(180, g_6127a0[55], g_4d5bb8, 2, 90);
        g_4d5bb8->unk260c += (float)(DWORD)g_60d688[25];
    }
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

// FUNCTION: STUNTGP_D3D 0x4137b0
void FUN_4137b0()
{
    if (g_4d5bb8->unk1fd8)
    {
        return;
    }
    float speed = (float)fabs(g_4d5bb8->unk1cf0);
    if (speed > 3.0f)
    {
        g_4d5bb8->unk7614 = 300;
        return;
    }
    if (--g_4d5bb8->unk7614 < 0)
    {
        g_4d5bb8->unk7614 = 0;
    }
    if (g_4d5bb8->unk7614 >= 180)
    {
        return;
    }
    if (--g_4d5bb8->unk7618 > 0)
    {
        return;
    }
    g_4d5bb8->unk7618 = 8;
    int t = g_4d5bb8->unk7614;
    speed = 1.0f / ((float)(t / 16 + 1) + speed);
    if (!t && FUN_42f1f0(32) == 1)
    {
        speed = 2.0f;
    }
    for (int i = 0; i < 4; i++)
    {
        g_4d5bb8->unk2240[i] += speed;
    }
}

// Points the steering wheel meshes along the current steering input.
// FUNCTION: STUNTGP_D3D 0x4138a0
void FUN_4138a0()
{
    ObjectDef *meshes = g_4d5bb8->unk26b0->lods[g_4d5bb8->unk26b0->lod];
    Vec4 a;
    a.x = g_4d5bb8->unk2894;
    a.y = 1.0f;
    a.z = 0.0f;
    Vec3_Normalize(&a.x);
    Vec4 b;
    b.x = 0.0f;
    b.y = g_4d5bb8->unk2890;
    b.z = 1.0f;
    Vec3_Normalize(&b.x);
    meshes[0].matrix[3] = a;
    meshes[0].matrix[2] = b;
    meshes[0].matrix[0].y = g_4d5bb8->unk288c;
    meshes[5].matrix[3] = a;
    meshes[5].matrix[2] = b;
    meshes[5].matrix[0].y = g_4d5bb8->unk288c;
    if (g_4d5bb8->unk28a0 == 1)
    {
        meshes[10].matrix[3] = a;
        meshes[10].matrix[2] = b;
        meshes[10].matrix[0].y = g_4d5bb8->unk288c;
    }
}

// Copies the wheel spin into the wheel meshes, turning the front pair by the steering angle.
// FUNCTION: STUNTGP_D3D 0x4139f0
void FUN_4139f0()
{
    ObjectDef *meshes = g_4d5bb8->unk26b0->lods[g_4d5bb8->unk26b0->lod];
    float rot[16];
    float m[16];
    Matrix_RotationY(rot, g_4d5bb8->unk1cf4);
    meshes[1].matrix[3] = *(Vec4 *)&g_4d5bb8->wheelMatrix[0][4];
    meshes[1].matrix[2] = *(Vec4 *)&g_4d5bb8->wheelMatrix[0][8];
    meshes[2].matrix[3] = *(Vec4 *)&g_4d5bb8->wheelMatrix[1][4];
    meshes[2].matrix[2] = *(Vec4 *)&g_4d5bb8->wheelMatrix[1][8];
    Vec4 *front = meshes[3].matrix;
    FUN_44efd0(m, g_4d5bb8->wheelMatrix[2], rot);
    front[3] = *(Vec4 *)&m[4];
    front[2] = *(Vec4 *)&m[8];
    front = meshes[4].matrix;
    FUN_44efd0(m, g_4d5bb8->wheelMatrix[3], rot);
    front[3] = *(Vec4 *)&m[4];
    front[2] = *(Vec4 *)&m[8];
}

// FUNCTION: STUNTGP_D3D 0x416590
void FUN_416590(Vec4 *pos, Vec4 *vel)
{
    if ((DWORD)g_612948.unk0454 >= 32)
    {
        g_612948.unk0454 = 0;
    }
    Unk612da4 *p = &((Unk612da4 *)g_612948.unk045c)[g_612948.unk0454];
    p->pos = *pos;
    p->unk04 = 8;
    p->life = FUN_42f1f0(15) + 30;
    p->unk28 = 0.95f;
    p->unk438 = 0.25f;
    p->unk43c = p->life;
    p->unk430 = 0;
    p->unk434 = 0;
    p->unk2c = 2.5f;
    p->vel = *vel;
    g_612948.unk0454++;
    g_612948.unk0450++;
}

void FUN_416420(Car *car, Vec4 *in, float *out);

// Every other tick of the unk2268 countdown, puffs smoke from the two exhaust meshes.
// FUNCTION: STUNTGP_D3D 0x416650
void FUN_416650()
{
    ObjectDef *meshes = g_4d5bb8->unk26b0->lods[g_4d5bb8->unk26b0->lod];
    if (g_4d5bb8->unk2268 && (--g_4d5bb8->unk2268 & 1) == 0 && g_4d5bb8->unk328c.active == 1)
    {
        Vec4 p;
        FUN_416420(g_4d5bb8, meshes[19].matrix, &p.x);
        FUN_416590(&p, &g_4d5bb8->unk1c8c);
        if (g_4d5bb8->unk33cc.active == 1)
        {
            FUN_416420(g_4d5bb8, meshes[20].matrix, &p.x);
            FUN_416590(&p, &g_4d5bb8->unk1c8c);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x4166f0
void FUN_4166f0()
{
    Car *car = g_4d5bb8;
    ObjectDef *meshes = car->unk26b0->lods[car->unk26b0->lod];
    if (!car->unk226c)
    {
        if (car->unk328c.active == 1)
        {
            meshes[19].visible = 0;
        }
        if (car->unk33cc.active == 1)
        {
            meshes[20].visible = 0;
        }
    }
    else if (car->unk328c.active == 1)
    {
        meshes[19].visible = 1;
        meshes[19].matrix[1].x = car->unk328c.unk024.x;
        meshes[19].matrix[1].y = car->unk328c.unk024.y;
        meshes[19].matrix[1].z = car->unk328c.unk024.z;
        if (car->unk33cc.active == 1)
        {
            meshes[20].visible = 1;
            meshes[20].matrix[1].x = car->unk33cc.unk024.x;
            meshes[20].matrix[1].y = car->unk33cc.unk024.y;
            meshes[20].matrix[1].z = car->unk33cc.unk024.z;
        }
    }
}

// GLOBAL: STUNTGP_D3D 0x4d5b30
float g_4d5b30[16];

// FUNCTION: STUNTGP_D3D 0x413b60
void FUN_413b60()
{
    Vec4 *m = g_4d5bb8->unk26b0->lods[0]->matrix;
    Vec4 r0;
    Vec4 r1;
    r0.x = m[2].y * m[3].z - m[2].z * m[3].y;
    r0.y = m[2].z * m[3].x - m[3].z * m[2].x;
    r0.z = m[3].y * m[2].x - m[2].y * m[3].x;
    r1.x = r0.y * m[2].z - r0.z * m[2].y;
    r1.y = r0.z * m[2].x - r0.x * m[2].z;
    r1.z = r0.x * m[2].y - r0.y * m[2].x;
    Vec3_Normalize(&r0.x);
    Vec3_Normalize(&r1.x);
    Matrix_FromRows(&r0.x, &r1.x, &m[2].x, g_4d5b30);
}


// FUNCTION: STUNTGP_D3D 0x413c10
void FUN_413c10()
{
    Vec4 *m = g_4d5bb8->unk26b0->lods[0]->matrix;
    Vec4 r0;
    Vec4 r1;
    float flip[16];
    float rot[16];
    r0.x = m[2].y * m[3].z - m[2].z * m[3].y;
    r0.y = m[2].z * m[3].x - m[3].z * m[2].x;
    r0.z = m[3].y * m[2].x - m[2].y * m[3].x;
    r1.x = r0.z * m[2].y - r0.y * m[2].z;
    r1.y = r0.x * m[2].z - r0.z * m[2].x;
    r1.z = r0.y * m[2].x - r0.x * m[2].y;
    Vec3_Normalize(&r0.x);
    Vec3_Normalize(&r1.x);
    Matrix_FromRows(&r0.x, &r1.x, &m[2].x, rot);
    Matrix_Identity(flip);
    flip[0] *= -1.0f;
    FUN_44efd0(g_4d5b30, flip, rot);
}

// FUNCTION: STUNTGP_D3D 0x413ce0
void FUN_413ce0()
{
    Car *car = g_4d5bb8;
    Scene *scene = car->unk26b0;
    car->unk28a8 = 0;
    car->unk2cf4[0] = 0.0f;
    car->unk2cf4[1] = 0.0f;
    car->unk2cf4[2] = 0.0f;
    car->unk2cf4[3] = 0.0f;
    ObjectDef *meshes = scene->lods[scene->lod];
    meshes[5].visible = 0;
    meshes[6].visible = 0;
    meshes[7].visible = 0;
    meshes[8].visible = 0;
    meshes[9].visible = 0;
    meshes[11].visible = 0;
    meshes[12].visible = 0;
    meshes[13].visible = 0;
    meshes[14].visible = 0;
    meshes[15].visible = 0;
    meshes[16].visible = 0;
    if (scene->objectCount > 19)
    {
        meshes[19].visible = 0;
    }
    if (scene->objectCount > 20)
    {
        meshes[20].visible = 0;
    }
    car->unk7628 = 0;
    car->unk3928 = 0;
    car->unk328c.unk13c = 0;
    car->unk33cc.unk13c = 0;
}

// FUNCTION: STUNTGP_D3D 0x413da0
void FUN_413da0()
{
    g_4d5bb8->unk3134 = 1;
    ObjectDef *meshes = g_4d5bb8->unk26b0->lods[g_4d5bb8->unk26b0->lod];
    meshes[11].visible = 1;
    meshes[12].visible = 1;
    meshes[13].visible = 1;
    meshes[14].visible = 1;
    meshes[15].visible = 1;
    meshes[16].visible = 1;
    g_4d5bb8->unk3928 = g_4d5bb8->unk3924;
    FUN_4166f0();
    g_4d5bb8->unk328c.unk13c = 1;
    g_4d5bb8->unk33cc.unk13c = 1;
}

// FUNCTION: STUNTGP_D3D 0x413e10
void FUN_413e10()
{
    g_4d5bb8->unk26b0->unk64 = FUN_42b580(&g_4d5bb8->unk1bbc);
    DWORD lod = FUN_42b580((Vec4 *)&g_4d5bb8->posX);
    g_4d5bb8->unk26b0->lod = lod;
    if (lod >= 3)
    {
        FUN_413ce0();
    }
    else
    {
        FUN_413da0();
    }
}

// Places the two exhaust-flame meshes at their emitters, oriented like the body.
// FUNCTION: STUNTGP_D3D 0x414130
void FUN_414130()
{
    Car *car = g_4d5bb8;
    if (car->unk328c.active)
    {
        ObjectDef *meshes = car->unk26b0->lods[car->unk26b0->lod];
        Vec4 *m = meshes[19].matrix;
        m[3] = meshes[0].matrix[3];
        m[2] = meshes[0].matrix[2];
        Vec4 v = car->unk328c.unk004;
        float y = v.y + car->unk288c;
        Vec4 r;
        r.x = g_4d5b30[0] * v.x + g_4d5b30[4] * y + g_4d5b30[8] * v.z;
        r.y = g_4d5b30[1] * v.x + g_4d5b30[5] * y + g_4d5b30[9] * v.z;
        r.z = g_4d5b30[2] * v.x + g_4d5b30[6] * y + g_4d5b30[10] * v.z;
        m[0] = r;
        if (car->unk33cc.active)
        {
            m = meshes[20].matrix;
            m[3] = meshes[0].matrix[3];
            m[2] = meshes[0].matrix[2];
            v = car->unk33cc.unk004;
            y = v.y + car->unk288c;
            r.x = g_4d5b30[0] * v.x + g_4d5b30[4] * y + g_4d5b30[8] * v.z;
            r.y = g_4d5b30[1] * v.x + g_4d5b30[5] * y + g_4d5b30[9] * v.z;
            r.z = g_4d5b30[2] * v.x + g_4d5b30[6] * y + g_4d5b30[10] * v.z;
            m[0] = r;
        }
    }
}

// Spins each wheel by the distance it rolled this tick.
// FUNCTION: STUNTGP_D3D 0x414370
void FUN_414370()
{
    Wheel *wheel = g_4d5bb8->wheels;
    for (int i = 0; i < 4; i++)
    {
        wheel->unk90 = wheel->unk94;
        wheel->unk94 += -(wheel->unk04 * 180.0f / (g_4d5bb8->unkcb8[i].x * 3.1415927f));
        Matrix_RotationX(g_4d5bb8->wheelMatrix[i], wheel->unk94);
        wheel++;
    }
}

// FUNCTION: STUNTGP_D3D 0x414460
void FUN_414460()
{
    Vec4 base;
    Vec4 side;
    Vec4 p;
    float s;
    base.x = g_4d5bb8->axisY.x;
    base.y = g_4d5bb8->axisY.y;
    base.z = g_4d5bb8->axisY.z;
    base.x += g_4d5bb8->posX;
    base.y += g_4d5bb8->posY;
    base.z += g_4d5bb8->posZ;

    s = -(g_4d5bb8->unk230 * g_4d5bb8->unk228);
    p.x = s * g_4d5bb8->axisZ.x;
    p.y = s * g_4d5bb8->axisZ.y;
    p.z = s * g_4d5bb8->axisZ.z;
    s = g_4d5bb8->unk238 * 0.5f;
    side.x = s * g_4d5bb8->axisX.x;
    side.y = s * g_4d5bb8->axisX.y;
    side.z = s * g_4d5bb8->axisX.z;
    p.x += side.x;
    p.y += side.y;
    p.z += side.z;
    p.x += base.x;
    p.y += base.y;
    p.z += base.z;
    g_4d5bb8->wheels[0].pos = p;

    s = -(g_4d5bb8->unk230 * g_4d5bb8->unk228);
    p.x = s * g_4d5bb8->axisZ.x;
    p.y = s * g_4d5bb8->axisZ.y;
    p.z = s * g_4d5bb8->axisZ.z;
    s = g_4d5bb8->unk238 * -0.5f;
    side.x = s * g_4d5bb8->axisX.x;
    side.y = s * g_4d5bb8->axisX.y;
    side.z = s * g_4d5bb8->axisX.z;
    p.x += side.x;
    p.y += side.y;
    p.z += side.z;
    p.x += base.x;
    p.y += base.y;
    p.z += base.z;
    g_4d5bb8->wheels[1].pos = p;

    s = g_4d5bb8->unk224;
    s *= g_4d5bb8->unk230;
    p.x = s * g_4d5bb8->axisZ.x;
    p.y = s * g_4d5bb8->axisZ.y;
    p.z = s * g_4d5bb8->axisZ.z;
    s = g_4d5bb8->unk234 * 0.5f;
    side.x = s * g_4d5bb8->axisX.x;
    side.y = s * g_4d5bb8->axisX.y;
    side.z = s * g_4d5bb8->axisX.z;
    p.x += side.x;
    p.y += side.y;
    p.z += side.z;
    p.x += base.x;
    p.y += base.y;
    p.z += base.z;
    g_4d5bb8->wheels[2].pos = p;

    s = g_4d5bb8->unk224;
    s *= g_4d5bb8->unk230;
    p.x = s * g_4d5bb8->axisZ.x;
    p.y = s * g_4d5bb8->axisZ.y;
    p.z = s * g_4d5bb8->axisZ.z;
    s = g_4d5bb8->unk234 * -0.5f;
    side.x = s * g_4d5bb8->axisX.x;
    side.y = s * g_4d5bb8->axisX.y;
    side.z = s * g_4d5bb8->axisX.z;
    p.x += side.x;
    p.y += side.y;
    p.z += side.z;
    p.x += base.x;
    p.y += base.y;
    p.z += base.z;
    g_4d5bb8->wheels[3].pos = p;
}

// STUB: STUNTGP_D3D 0x414710
void FUN_414710()
{
}

// Fades the four tyre smoke meshes, which follow the wheel meshes.
// FUNCTION: STUNTGP_D3D 0x414b30
void FUN_414b30()
{
    Scene *model = g_4d5bb8->unk26b0;
    int i;
    for (i = 0; i < 3; i++)
    {
        model->lods[i][6].visible = 0;
    }
    ObjectDef *meshes = model->lods[model->lod];
    ObjectDef *mesh = &meshes[6];
    ObjectDef *wheel = &meshes[1];
    for (i = 0; i < 4; i++, mesh++, wheel++)
    {
        if (g_4d5bb8->unk2cf4[i] != 0.0f)
        {
            mesh->matrix[2] = wheel->matrix[2];
            mesh->matrix[3] = wheel->matrix[3];
            g_4d5bb8->unk2cf4[i] -= 2.0f;
            if (g_4d5bb8->unk2cf4[i] <= 0.0f)
            {
                g_4d5bb8->unk2cf4[i] = 0.0f;
                mesh->visible = 0;
            }
            else
            {
                mesh->visible = 1;
            }
            for (unsigned int j = 0; j < mesh->vertCount; j++)
            {
                mesh->verts[j * 8 + 2] = (BYTE)g_4d5bb8->unk2cf4[i];
                mesh->verts[j * 8 + 3] = 0x60;
            }
        }
    }
}

// GLOBAL: STUNTGP_D3D 0x474c08
TrailParams g_474c08 = {1, 16, 2, 8};

// GLOBAL: STUNTGP_D3D 0x474d18
TrailParams g_474d18 = {0, 5, 1, 4};

// GLOBAL: STUNTGP_D3D 0x474e28
TrailParams g_474e28 = {0, 9, 2, 4};

int FUN_41e410(Vec4 *p, float *out);

// Pushes a body-mesh point, placed in world space like FUN_416420, into a trail ring.
// FUNCTION: STUNTGP_D3D 0x41e510
void FUN_41e510(Vec4 *ring, DWORD *head, DWORD *count, Vec4 *pos, TrailParams *params)
{
    FUN_413b60();
    Vec4 v = *pos;
    Vec4 w;
    w.x = g_4d5b30[0] * v.x + g_4d5b30[4] * v.y + g_4d5b30[8] * v.z;
    w.y = g_4d5b30[1] * v.x + g_4d5b30[5] * v.y + g_4d5b30[9] * v.z;
    w.z = g_4d5b30[2] * v.x + g_4d5b30[6] * v.y + g_4d5b30[10] * v.z;
    float nx = -w.x;
    Vec4 a;
    a.x = nx * g_4d5bb8->axisX.x;
    a.y = nx * g_4d5bb8->axisX.y;
    a.z = nx * g_4d5bb8->axisX.z;
    float t = 70.0f - w.y - g_4d5bb8->unk288c;
    v.x = t * g_4d5bb8->axisY.x;
    v.y = t * g_4d5bb8->axisY.y;
    v.z = t * g_4d5bb8->axisY.z;
    Vec4 c;
    c.x = w.z * g_4d5bb8->axisZ.x;
    c.y = w.z * g_4d5bb8->axisZ.y;
    c.z = w.z * g_4d5bb8->axisZ.z;
    a.x = a.x + v.x;
    a.y = a.y + v.y;
    a.z = a.z + v.z;
    a.x = c.x + a.x;
    a.y = c.y + a.y;
    a.z = c.z + a.z;
    w.x = g_4d5bb8->posX - a.x;
    w.y = g_4d5bb8->posY - a.y;
    w.z = g_4d5bb8->posZ - a.z;
    DWORD size = params->size;
    if (*count < size)
    {
        (*count)++;
    }
    DWORD h = (*head + 1) % size;
    *head = h;
    ring[size] = w;
    ring[h] = w;
    if (!params->unk10)
    {
        FUN_41e410(&w, &ring[h].x);
    }
}


// FUNCTION: STUNTGP_D3D 0x414c60
void FUN_414c60()
{
    if (g_612948.unk0034 < 20)
    {
        return;
    }
    if (g_4d5bb8->unk1cf0 - 4000.0f / 60.0f < 0.0f)
    {
        FUN_414c50(g_4d5bb8);
        return;
    }
    Vec4 pos;
    pos.x = 0.0f;
    pos.y = g_4d5bb8->unk244;
    pos.z = g_4d5bb8->unk26b0->lods[0][23].matrix->z;
    FUN_41e510(g_4d5bb8->unk351c, &g_4d5bb8->unk391c, &g_4d5bb8->unk3920, &pos, &g_474c08);
}

// FUNCTION: STUNTGP_D3D 0x414f90
void FUN_414f90()
{
    if (g_612948.unk0034 >= 60 && g_4d5bb8->unk28a0)
    {
        Trail *trail = g_4d5bb8->unk2d04;
        Vec4 pos = trail[0].pos;
        FUN_41e510(trail[0].points, &trail[0].head, &trail[0].count, &pos, &g_474d18);
        pos = trail[1].pos;
        FUN_41e510(trail[1].points, &trail[1].head, &trail[1].count, &pos, &g_474d18);
    }
}

// FUNCTION: STUNTGP_D3D 0x4152d0
void FUN_4152d0()
{
    if (g_612948.unk0034 >= 60 && g_4d5bb8->unk28a0)
    {
        TrailSlot *slot = g_4d5bb8->unk28bc;
        Vec4 pos = slot[0].trail.pos;
        pos.y -= 20.0f;
        FUN_41e510(slot[0].trail.points, &slot[0].trail.head, &slot[0].trail.count, &pos, &g_474e28);
        pos = slot[1].trail.pos;
        pos.y -= 20.0f;
        FUN_41e510(slot[1].trail.points, &slot[1].trail.head, &slot[1].trail.count, &pos, &g_474e28);
    }
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
    ObjectDef *mesh = &g_4d5bb8->unk26b0->lods[g_4d5bb8->unk26b0->lod][5];
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
            ObjectDef *meshes = g_4d5bb8->unk26b0->lods[i];
            meshes[10].visible = 1;
            meshes[5].visible = 1;
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
            ObjectDef *meshes = g_4d5bb8->unk26b0->lods[i];
            meshes[10].visible = 0;
            meshes[5].visible = 0;
        }
    }
}

// Switches the car lights from the track's light mask at the car's path position.
// FUNCTION: STUNTGP_D3D 0x415770
void FUN_415770()
{
    if (g_4d5bb8->unk26b0->objectCount > 10)
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

extern float g_48266c;

// FUNCTION: STUNTGP_D3D 0x4157f0
void FUN_4157f0(Unk62a078 *p)
{
    p->unk98 = 0x60;
    p->flags = 7;
    p->texture = 7;
    p->mode = 2;
    p->gravity = g_48266c * -0.3f;
    p->colors[0] = 0x406090;
    p->lifetime = 30;
    p->unk68 = 0.01f;
    p->unk7c = 1;
    p->anim = NULL;
    p->sizeIn = 1.5f;
    p->sizeOut = 6.0f;
    p->size = 1.0f;
    p->alphaIn = 0.0f;
    p->alphaOut = 21.0f;
    p->alpha = 255.0f;
}

// STUB: STUNTGP_D3D 0x415880
void FUN_415880()
{
}

// FUNCTION: STUNTGP_D3D 0x415ac0
void FUN_415ac0(Vec4 *pos, Vec4 *vel, float speed)
{
    if (g_612948.unk0458 <= 0)
    {
        g_612948.unk0458 = g_612948.unk0034 < 80 ? 2 : 1;
        if ((DWORD)g_612948.unk0454 >= 32)
        {
            g_612948.unk0454 = 0;
        }
        Unk612da4 *p = &((Unk612da4 *)g_612948.unk045c)[g_612948.unk0454];
        p->pos = *pos;
        p->unk04 = 4;
        p->life = FUN_42f1f0(30) + 60;
        p->unk28 = 0.9f;
        p->unk438 = 1.0f;
        p->unk43c = p->life;
        p->unk430 = 0;
        p->unk434 = 0;
        p->unk2c = (float)fabs(speed) * 0.25f + 0.5f;
        p->vel = *vel;
        Vec4 r;
        r.x = FUN_42f1c0(8.333333f);
        r.y = FUN_42f1c0(16.666666f) + 8.333333f;
        r.z = FUN_42f1c0(8.333333f);
        p->vel.x = r.x + p->vel.x;
        p->vel.y = r.y + p->vel.y;
        p->vel.z = r.z + p->vel.z;
        g_612948.unk0454++;
        g_612948.unk0450++;
    }
}

// FUNCTION: STUNTGP_D3D 0x415c00
void FUN_415c00(Vec4 *pos, Vec4 *vel, float unused)
{
    if (g_612948.unk0458 <= 0)
    {
        g_612948.unk0458 = g_612948.unk0034 < 80 ? 4 : 2;
        if ((DWORD)g_612948.unk0454 >= 32)
        {
            g_612948.unk0454 = 0;
        }
        Unk612da4 *p = &((Unk612da4 *)g_612948.unk045c)[g_612948.unk0454];
        float r = FUN_42f1c0(66.666664f);
        Vec4 d;
        d.x = r * g_4d5bb8->axisX.x;
        d.y = r * g_4d5bb8->axisX.y;
        d.z = r * g_4d5bb8->axisX.z;
        p->vel.x = d.x + vel->x;
        p->vel.y = d.y + vel->y;
        p->vel.z = d.z + vel->z;
        p->life = 60;
        p->pos = *pos;
        p->unk28 = 0.9f;
        p->unk438 = 0;
        p->unk43c = 0;
        p->unk430 = 0;
        p->unk434 = 0;
        p->unk2c = 1.0f;
        int r2 = FUN_42f1f0(1024);
        if ((r2 & 3) == 0)
        {
            p->unk04 = 7;
        }
        else
        {
            p->unk04 = (r2 & 1) + 5;
        }
        g_612948.unk0454++;
        g_612948.unk0450++;
    }
}

// FUNCTION: STUNTGP_D3D 0x415d20
void FUN_415d20(Vec4 *pos, Vec4 *vel, float unused)

{
    if (g_612948.unk0458 == 2)
    {
        g_612948.unk0458 = g_612948.unk0034 < 80 ? 4 : 2;
        if ((DWORD)g_612948.unk0454 >= 32)
        {
            g_612948.unk0454 = 0;
        }
        Unk612da4 *p = &((Unk612da4 *)g_612948.unk045c)[g_612948.unk0454];
        p->vel = *vel;
        p->life = 60;
        p->pos = *pos;
        p->unk28 = 0.9f;
        p->unk438 = 0;
        p->unk43c = 0;
        p->unk2c = 1.0f;
        p->unk430 = 0;
        p->unk434 = 0;
        p->unk04 = 5;
        g_612948.unk0454++;
        g_612948.unk0450++;
    }
}

// Scrolls the second float of every unk2c entry of one mesh, wrapping at 1.
// FUNCTION: STUNTGP_D3D 0x4167a0
void FUN_4167a0(int index)
{
    ObjectDef *mesh = &g_4d5bb8->unk26b0->lods[0][index];
    BYTE *entry = mesh->unk2c;
    for (DWORD i = 0; i < mesh->unk26; i++)
    {
        ((float *)entry)[1] += 0.02f;
        if (((float *)entry)[1] > 1.0f)
        {
            ((float *)entry)[1] -= 1.0f;
        }
        entry += 16;
    }
}

// STUB: STUNTGP_D3D 0x416800
void FUN_416800()
{
}

// GLOBAL: STUNTGP_D3D 0x4d5bc0
Unk62a078 g_4d5bc0;

// FUNCTION: STUNTGP_D3D 0x4169e0
void FUN_4169e0()
{
    g_4d5bc0.unk68 = 0.01f;
    g_4d5bc0.flags = 7;
    g_4d5bc0.mode = 2;
    g_4d5bc0.unk7c = 1;
    g_4d5bc0.anim = NULL;
    g_4d5bc0.gravity = g_48266c * -0.3f;
    g_4d5bc0.size = 0.5f;
    g_4d5bc0.sizeIn = 3.0f;
    g_4d5bc0.sizeOut = 12.0f;
    g_4d5bc0.alpha = 96.0f;
    g_4d5bc0.alphaIn = 0.0f;
    g_4d5bc0.alphaOut = 18.0f;
    g_4d5bc0.colors[0] = 0x406090;
    g_4d5bc0.texture = 7;
    g_4d5bc0.unk98 = 0x60;
}

// STUB: STUNTGP_D3D 0x416a80
void FUN_416a80()
{
}

// FUNCTION: STUNTGP_D3D 0x416ea0
void FUN_416ea0(Unk62a078 *p)
{
    p->flags = 3;
    p->texture = 0;
    p->anim = NULL;
    p->unk98 = 0x60;
    p->gravity = g_48266c * -0.15f;
    p->mode = 2;
    p->lifetime = 30;
    p->unk68 = 0.01f;
    p->unk7c = 1;
    p->size = 0.5f;
    p->sizeIn = 6.0f;
    p->sizeOut = 12.0f;
    p->alpha = 128.0f;
    p->alphaIn = 0.59999996f;
    p->alphaOut = 12.0f;
    p->colors[0] = 0x182010;
}

// STUB: STUNTGP_D3D 0x416f30
void FUN_416f30()
{
}

// FUNCTION: STUNTGP_D3D 0x417130
void FUN_417130(Unk62a078 *p)
{
    p->flags = 3;
    p->unk98 = 0x60;
    p->mode = 2;
    p->texture = 0;
    p->lifetime = 30;
    p->unk68 = 0.01f;
    p->gravity = 0.25f;
    p->unk7c = 1;
    p->anim = NULL;
    p->size = 0.25f;
    p->sizeIn = 6.0f;
    p->sizeOut = 12.0f;
    p->alpha = 192.0f;
    p->alphaIn = 0.59999996f;
    p->alphaOut = 12.0f;
    p->colors[0] = 0x182010;
}

// FUNCTION: STUNTGP_D3D 0x417350
void FUN_417350(Unk62a078 *p)
{
    p->flags = 3;
    p->texture = 0;
    p->anim = NULL;
    p->unk98 = 0x60;
    p->mode = 2;
    p->lifetime = 41;
    p->unk68 = 0.01f;
    p->gravity = 0.25f;
    p->unk7c = 1;
    p->size = 1.0f;
    p->sizeIn = 0.59999996f;
    p->sizeOut = 24.0f;
    p->alpha = 224.0f;
    p->alphaIn = 0.59999996f;
    p->alphaOut = 18.0f;
    p->colors[0] = 0x182010;
}

void FUN_45e110(Unk62a078 *particle);

// Bursts 32 dust particles from under the car.
// FUNCTION: STUNTGP_D3D 0x4171c0
void FUN_4171c0()
{
    Unk62a078 p;
    *(Camera *)&p.pos = g_4864e8;
    FUN_417130(&p);
    Vec4 v;
    v.x = g_4d5bb8->unk1c8c.x * 0.5f;
    v.y = g_4d5bb8->unk1c8c.y * 0.5f;
    v.z = g_4d5bb8->unk1c8c.z * 0.5f;
    Vec4 down;
    down.x = g_4d5bb8->axisY.x * 60.000004f;
    down.y = g_4d5bb8->axisY.y * 60.000004f;
    down.z = g_4d5bb8->axisY.z * 60.000004f;
    for (int i = 0; i < 32; i++)
    {
        p.pos.x = g_4d5bb8->posX - down.x;
        p.pos.y = g_4d5bb8->posY - down.y;
        p.pos.z = g_4d5bb8->posZ - down.z;
        Vec4 r;
        r.x = FUN_42f1c0(5.0f);
        r.y = (float)fabs(FUN_42f1c0(1.0f));
        r.z = FUN_42f1c0(5.0f);
        p.vel[0] = r.x + v.x;
        p.vel[1] = r.y + v.y;
        p.vel[2] = r.z + v.z;
        p.size = (float)fabs(FUN_42f1c0(0.25f)) + 0.5f;
        r.x = FUN_42f1c0(150.0f);
        r.y = (float)fabs(FUN_42f1c0(10.0f));
        r.z = FUN_42f1c0(150.0f);
        p.pos.x = r.x + p.pos.x;
        p.pos.y = r.y + p.pos.y;
        p.pos.z = r.z + p.pos.z;
        FUN_45e110(&p);
    }
}

// FUNCTION: STUNTGP_D3D 0x4173e0
void FUN_4173e0()
{
    if (g_612948.unk0034 >= 80 && g_4d5bb8->unk71ec == 0 && g_4d5bb8->unk7244 <= 60 &&
        (++g_4d5bb8->unk7244 & 1) == 0)
    {
        Unk62a078 p;
        FUN_417350(&p);
        Vec4 v;
        v.x = g_4d5bb8->unk1c8c.x * 0.5f;
        v.y = g_4d5bb8->unk1c8c.y * 0.5f;
        v.z = g_4d5bb8->unk1c8c.z * 0.5f;
        for (int i = 0; i < 2; i++)
        {
            p.pos = g_4d5bb8->wheels[i].pos;
            p.vel[0] = FUN_42f1c0(5.0f) + v.x;
            p.vel[1] = v.y;
            p.vel[2] = v.z;
            FUN_45e110(&p);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x4174e0
void FUN_4174e0(Unk62a078 *p)
{
    *(Camera *)&p->pos = g_4864e8;
    Car *car = g_4d5bb8;
    p->unk98 = 0x60;
    p->flags = 3;
    p->vel[0] = car->unk1c8c.x * 0.5f;
    p->mode = 2;
    p->colors[0] = 0x402000;
    p->texture = 9;
    p->lifetime = 30;
    p->unk68 = 0.01f;
    p->unk7c = 1;
    p->vel[1] = car->unk1c8c.y * 0.5f;
    p->anim = NULL;
    p->sizeIn = 6.0f;
    p->sizeOut = 6.0f;
    p->vel[2] = car->unk1c8c.z * 0.5f;
    p->gravity = g_48266c * -0.6f;
    if (car->unk1cf0 < 10.0f)
    {
        p->size = car->unk1cf0 * 0.1f;
    }
    else
    {
        p->size = 1.0f;
    }
    p->alphaIn = 6.0f;
    p->alphaOut = 21.0f;
    p->alpha = 255.0f;
}

// FUNCTION: STUNTGP_D3D 0x4175e0
void FUN_4175e0(Unk62a078 *p)
{
    *(Camera *)&p->pos = g_4864e8;
    Car *car = g_4d5bb8;
    p->unk98 = 0x60;
    p->flags = 3;
    p->vel[0] = car->unk1c8c.x * 0.75f;
    p->mode = 2;
    p->colors[0] = 0x101800;
    p->texture = 9;
    p->lifetime = 18;
    p->unk68 = 0.05f;
    p->unk7c = 1;
    p->vel[1] = car->unk1c8c.y * 0.75f;
    p->anim = NULL;
    p->sizeIn = 3.0f;
    p->sizeOut = 9.0f;
    p->vel[2] = car->unk1c8c.z * 0.75f;
    p->gravity = g_48266c * -0.3f;
    if (car->unk1cf0 < 10.0f)
    {
        p->size = car->unk1cf0 * 0.1f;
    }
    else
    {
        p->size = 0.75f;
    }
    p->alphaIn = 3.0f;
    p->alphaOut = 6.0f;
    p->alpha = 255.0f;
}

// FUNCTION: STUNTGP_D3D 0x4176f0
void FUN_4176f0(Unk62a078 *p)
{
    *(Camera *)&p->pos = g_4864e8;
    Car *car = g_4d5bb8;
    p->unk98 = 0x60;
    p->flags = 3;
    p->vel[0] = car->unk1c8c.x * 0.5f;
    p->mode = 2;
    p->colors[0] = 0x401000;
    p->texture = 9;
    p->lifetime = 18;
    p->unk68 = 0.1f;
    p->unk7c = 1;
    p->vel[1] = car->unk1c8c.y * 0.5f;
    p->anim = NULL;
    p->sizeIn = 3.0f;
    p->sizeOut = 12.0f;
    p->vel[2] = car->unk1c8c.z * 0.5f;
    p->gravity = g_48266c * -0.3f;
    if (car->unk1cf0 < 10.0f)
    {
        p->size = car->unk1cf0 * 0.075f;
    }
    else
    {
        p->size = 1.0f;
    }
    p->alphaIn = 3.0f;
    p->alphaOut = 6.0f;
    p->alpha = 255.0f;
}

// STUB: STUNTGP_D3D 0x417800
void FUN_417800()
{
}

// FUNCTION: STUNTGP_D3D 0x417b50
void FUN_417b50(Vec4 *pos, Vec4 *vel, float speed)
{
    if ((DWORD)g_612948.unk0454 >= 32)
    {
        g_612948.unk0454 = 0;
    }
    Unk612da4 *p = &((Unk612da4 *)g_612948.unk045c)[g_612948.unk0454];
    p->pos = *pos;
    p->unk04 = 4;
    p->life = FUN_42f1f0(30) + 60;
    p->unk28 = 0.99f;
    p->unk438 = 1.0f;
    p->unk43c = p->life;
    p->unk430 = 0;
    p->unk434 = 0;
    p->unk2c = (float)fabs(speed) * 0.25f + 0.5f;
    Vec4 r;
    r.x = FUN_42f1c0(0.41666666f);
    r.y = (float)fabs(FUN_42f1c0(0.8333333f) + (g_4d5bb8->unk1cf0 * 0.033333335f) * 2.5f);
    p->vel.x = r.y * g_4d5bb8->matrix[4] + r.x * g_4d5bb8->matrix[0];
    p->vel.y = r.y * g_4d5bb8->matrix[5] + r.x * g_4d5bb8->matrix[1];
    p->vel.z = r.y * g_4d5bb8->matrix[6] + r.x * g_4d5bb8->matrix[2];
    p->vel.x += vel->x;
    p->vel.y = vel->y + p->vel.y;
    p->vel.z = vel->z + p->vel.z;
    g_612948.unk0454++;
    g_612948.unk0450++;
}

// Hard landing on two or more wheels: queues sparks under the car for a few frames.
// FUNCTION: STUNTGP_D3D 0x417ca0
void FUN_417ca0()
{
    Car *car = g_4d5bb8;
    if (car->unk1fd8 == 1 || car->unk1cf0 < 10.0f)
    {
        car->unk761c = 0;
        return;
    }
    float s = g_482670 * car->unk2618 * 3.0f;
    float sum = 0.0f;
    unsigned int hits = 0;
    Wheel *w = car->wheels;
    for (int i = 0; i < 4; i++)
    {
        if (w->unk78 == 1 && w->unk80 > s)
        {
            hits++;
        }
        sum += w->unk80;
        w++;
    }
    if (hits >= 2)
    {
        unsigned int n = sum * 0.001953125f;
        if (n > 8)
        {
            n = 8;
        }
        if (car->unk761c < 15)
        {
            car->unk761c += n;
        }
    }
    if (car->unk761c > 0)
    {
        car->unk761c--;
        s = sum * 0.25f;
        Vec4 off;
        off.x = car->axisY.x * -25.0f;
        off.y = car->axisY.y * -25.0f;
        off.z = car->axisY.z * -25.0f;
        Vec4 p;
        p.x = off.x + car->posX;
        p.y = off.y + car->posY;
        p.z = off.z + car->posZ;
        for (int j = 0; j < 2; j++)
        {
            FUN_417b50(&p, &g_4d5bb8->unk1c8c, s);
        }
        g_4d5bb8->unk2354 = 1;
        g_4d5bb8->unk235c = s;
    }
}


// STUB: STUNTGP_D3D 0x417f10
void FUN_417f10()
{
}

// FUNCTION: STUNTGP_D3D 0x418150
void FUN_418150()
{
    Car *car = g_4d5bb8;
    car->unk26b0->unk04 = car->unk7684 * 512.0f;
}

// STUB: STUNTGP_D3D 0x418320
void FUN_418320()
{
}

extern DWORD g_60f2b0;

// FUNCTION: STUNTGP_D3D 0x418510
void FUN_418510()
{
    if (g_60f2b0 != 3)
    {
        Car *car = g_4d5bb8;
        if (car->unk24c0.z * car->axisZ.z + car->unk24c0.y * car->axisZ.y + car->unk24c0.x * car->axisZ.x < -0.707f)
        {
            if (++car->unk7634 <= 600)
            {
                return;
            }
            car->unk763c = 1;
        }
        car->unk7634 = 0;
    }
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
    sprintf(text, "%s %s\n", g_60f02c[car - g_49a1f8].name, g_6127a0[17]);
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

// FUNCTION: STUNTGP_D3D 0x418710
void FUN_418710(Car *car)
{
    if (g_60f2b4 != 3)
    {
        if (car->unk2640 == 1)
        {
            car->unk2570 -= g_60f2d0[3];
        }
        else
        {
            car->unk2570 -= g_60f2d0[1];
        }
        if (car->unk2568 < 0)
        {
            car->unk2568 = 0;
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
    FUN_401d70(&g_4d5bb8->unk1c8c.x, 1.0f);
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
    if (g_612948.unk0034 < 80)
    {
        return;
    }
    if (g_4d5bb8->unk7268 && g_4d5bb8->unk7268->mode == 1)
    {
        return;
    }
    FUN_41cd30(0);
    FUN_41cd30(1);
}

void FUN_41d4b0();
void FUN_41d5c0();

// Lap percentage of each of the ten splits.
// GLOBAL: STUNTGP_D3D 0x474870
float g_474870[10] = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f, 90.0f, 99.0f};

// Records a split time when the car crosses the next split point, announcing the gap on some.
// FUNCTION: STUNTGP_D3D 0x41d760
void FUN_41d760()
{
    if (g_60f2b0 == 3 || g_4d5bb8->unk23bc < 0)
    {
        return;
    }
    float prev = fmod(g_4d5bb8->unk23b4, 100.0);
    float cur = fmod(g_4d5bb8->unk23b0, 100.0);
    unsigned int split = g_4d5bb8->unk24ec;
    if (g_60f2b0 == 2)
    {
        if (prev <= g_474870[split] && cur >= g_474870[split] && split == 9)
        {
            FUN_41d5c0();
        }
    }
    else if (g_60f2b0 == 4)
    {
        if (prev <= g_474870[split] && cur >= g_474870[split] && (split == 2 || split == 5 || split == 8))
        {
            FUN_41d4b0();
        }
    }
    if (prev <= g_474870[split] && cur >= g_474870[split])
    {
        g_4d5bb8->unk24f0[g_4d5bb8->unk24ec] = g_4d5bb8->unk23a4 * 12000 + g_4d5bb8->unk23c4;
        if (++g_4d5bb8->unk24ec >= 10)
        {
            g_4d5bb8->unk24ec = 0;
        }
    }
}


// FUNCTION: STUNTGP_D3D 0x407000
void FUN_407000()
{
    g_4d5bb8->unk2674 = 0;
}

extern StuntKnot g_499fb8[33];

// FUNCTION: STUNTGP_D3D 0x4077b0
int FUN_4077b0()
{
    StuntKnot *knot = &g_499fb8[g_4d5bb8->unk2674];
    if (knot->pathPosition != 0.0f &&
        knot->pathPosition * g_49a160->unk18 * 0.01f -
                g_4d5bb8->unk2658 * g_49a160->unk18 * 0.01f <
            10000.0f &&
        g_4d5bb8->unk2574 * 0.5f < g_4d5bb8->unk2570 && g_4d5bb8->unk1cf8 > 0.5f &&
        g_4d5bb8->unk045c * 0.75f > g_4d5bb8->unk1cfc)
    {
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x407860
int FUN_407860()
{
    Car *car = g_4d5bb8;
    if (car->unk2574 * 0.3f < car->unk2570 && car->unk1cf8 > 0.75f && car->unk1cf0 > 3.3333333f &&
        ((1.0f - car->unk2660) * g_60f2d0[12] + 1.0f) * (car->unk045c * 0.4f) > car->unk1cfc)
    {
        return 1;
    }
    return 0;
}

// Times the AI boost: runs it while it lasts, then waits out the cooldown before the next one.
// FUNCTION: STUNTGP_D3D 0x4078f0
void FUN_4078f0()
{
    if (g_4d5bb8->unk2698 != 0)
    {
        g_4d5bb8->unk2698--;
        return;
    }
    if (g_4d5bb8->unk2694 != 0)
    {
        g_4d5bb8->unk2250 = 1;
        g_4d5bb8->unk2694--;
        if (g_4d5bb8->unk045c * 0.99f < g_4d5bb8->unk1cfc || g_4d5bb8->unk2678 > 0)
        {
            g_4d5bb8->unk2694 = 0;
        }
        if (g_4d5bb8->unk2694 == 0)
        {
            g_4d5bb8->unk2250 = 0;
            g_4d5bb8->unk2698 = g_4d5bb8->unk269c;
        }
        return;
    }
    if (FUN_407860() == 1)
    {
        float k = g_60f2d0[12] * g_4d5bb8->unk2660 + 1.0f;
        g_4d5bb8->unk2694 = (fabs(FUN_42f1c0(120.0f)) + 180.0) * k;
        g_4d5bb8->unk269c = (fabs(FUN_42f1c0(300.0f)) + 300.0) / k;
    }
    else if (FUN_4077b0() == 1)
    {
        float k = g_60f2d0[12] * g_4d5bb8->unk2660 + 1.0f;
        g_4d5bb8->unk2694 = (fabs(FUN_42f1c0(60.0f)) + 120.0) * k;
        g_4d5bb8->unk269c = (fabs(FUN_42f1c0(300.0f)) + 300.0) / k;
    }
}

// Picks which side to pass the car ahead on.
// FUNCTION: STUNTGP_D3D 0x4073e0
void FUN_4073e0()
{
    Car *car = g_4d5bb8;
    Car *target = car->unk2688;
    Vec4 d;
    d.x = target->posX - car->posX;
    d.y = target->posY - car->posY;
    d.z = target->posZ - car->posZ;
    if (d.x * car->axisZ.x + d.y * car->axisZ.y + d.z * car->axisZ.z >= 500.0f)
    {
        Vec4 p;
        p.x = car->posX - car->unk24b0.x;
        p.y = car->posY - car->unk24b0.y;
        p.z = car->posZ - car->unk24b0.z;
        float side = p.x * car->unk24d0.x + p.y * car->unk24d0.y + p.z * car->unk24d0.z;
        if ((float)fabs(side) < 1000.0f)
        {
            car->unk2690 =
                d.x * car->unk24d0.x + d.y * car->unk24d0.y + d.z * car->unk24d0.z > -200.0f ? 500.0f : -500.0f;
        }
        else
        {
            car->unk2690 = side > 0.0f ? 500.0f : -500.0f;
        }
    }
}

// Nearest active car ahead within the 100-unit lap fraction, else the nearest behind.
// FUNCTION: STUNTGP_D3D 0x407a70
Car *FUN_407a70(Car *self)
{
    float mine = fmod(self->unk23b0, 100.0);
    Car *car = g_49a1f8;
    Car *ahead = NULL;
    float aheadDist = 1000.0f;
    Car *behind = NULL;
    float behindDist = 1000.0f;
    for (int i = 0; i < 6; i++, car++)
    {
        if (car != self && car->active == 1)
        {
            float d = fmod(car->unk23b0, 100.0) - mine;
            if (d < 0.0f)
            {
                if (d < behindDist)
                {
                    behindDist = d;
                    behind = car;
                }
            }
            else if (d < aheadDist)
            {
                aheadDist = d;
                ahead = car;
            }
        }
    }
    if (!ahead)
    {
        ahead = behind;
    }
    return ahead;
}

// Like FUN_407a70 but measured the other way round the lap, with negative positions wrapped.
// FUNCTION: STUNTGP_D3D 0x407b20
Car *FUN_407b20(Car *self)
{
    float mine = fmod(self->unk23b0, 100.0);
    if (mine < 0.0f)
    {
        mine += 100.0f;
    }
    Car *car = g_49a1f8;
    Car *ahead = NULL;
    float aheadDist = 1000.0f;
    Car *behind = NULL;
    float behindDist = 1000.0f;
    for (int i = 0; i < 6; i++, car++)
    {
        if (car != self && car->active == 1)
        {
            float other = car->unk23b0 < 0.0f ? fmod(car->unk23b0 + 100.0f, 100.0) : fmod(car->unk23b0, 100.0);
            float d = mine - other;
            if (d < 0.0f)
            {
                if (d < behindDist)
                {
                    behindDist = d;
                    behind = car;
                }
            }
            else if (d < aheadDist)
            {
                aheadDist = d;
                ahead = car;
            }
        }
    }
    return ahead ? ahead : behind;
}

// Slipstreaming: builds up a draft counter behind a similar-speed car and pulls the finish target towards it.
// FUNCTION: STUNTGP_D3D 0x407c10
void FUN_407c10()
{
    if (g_4d5bb8->unk26a0 > 0)
    {
        g_4d5bb8->unk26a0--;
    }
    if (!g_4d5bb8->unk1fd8 && (float)fabs(g_4d5bb8->unk2668) <= 100.0f && g_4d5bb8->unk1cf0 >= 41.666668f)
    {
        Car *other = FUN_407a70(g_4d5bb8);
        float dv = other->unk1cf0 - g_4d5bb8->unk1cf0;
        if (dv <= 16.666666f && dv >= -33.333332f)
        {
            float len = g_571328->unk18 * 0.01f;
            float gap = len * other->unk23b0 - len * g_4d5bb8->unk23b0;
            if (gap > 1000.0f && gap < 10000.0f && g_4d5bb8->unk26a0 < 240)
            {
                g_4d5bb8->unk26a0 += 2;
            }
            Vec4 p = *(Vec4 *)&other->posX;
            float dx = p.x - g_49a148.x;
            float dy = p.y - g_49a148.y;
            float dz = p.z - g_49a148.z;
            if ((float)fabs(dx * g_4d5bb8->unk24d0.x + dy * g_4d5bb8->unk24d0.y + dz * g_4d5bb8->unk24d0.z) <= 500.0f)
            {
                float k = g_4d5bb8->unk26a0 * 0.0041666669f;
                p.x = dx;
                p.y = dy;
                p.z = dz;
                p.x *= k;
                p.y *= k;
                p.z *= k;
                g_49a148.x = g_49a148.x + p.x;
                g_49a148.y = g_49a148.y + p.y;
                g_49a148.z = g_49a148.z + p.z;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x407dd0
void FUN_407dd0()
{
}
// When closing on a slower car just ahead, mirrors the finish target across it to swing out and pass.
// FUNCTION: STUNTGP_D3D 0x407de0
void FUN_407de0()
{
    if (g_4d5bb8->unk1fd8)
    {
        return;
    }
    Car *other = FUN_407b20(g_4d5bb8);
    if ((float)fabs(g_4d5bb8->unk2668) <= 25.0f && other->unk1cf0 - g_4d5bb8->unk1cf0 >= 1.6666666f &&
        g_4d5bb8->unk25f4[other - g_49a1f8] >= (g_4d5bb8->unk23a4 + 1) * 3)
    {
        Vec4 d;
        d.x = other->posX - g_4d5bb8->posX;
        d.y = other->posY - g_4d5bb8->posY;
        d.z = other->posZ - g_4d5bb8->posZ;
        float gap = (other->unk23b0 - g_4d5bb8->unk23b0) * g_60f010 * 0.01f;
        if (gap >= -1500.0f && gap <= 0.0f)
        {
            float t = d.y * g_4d5bb8->unk24d0.y;
            t += d.z * g_4d5bb8->unk24d0.z;
            t += d.x * g_4d5bb8->unk24d0.x;
            t = t + t;
            d.x = t * g_4d5bb8->unk24d0.x;
            d.y = t * g_4d5bb8->unk24d0.y;
            d.z = t * g_4d5bb8->unk24d0.z;
            g_499fb0 *= 5.0f;
            g_49a148.x = g_49a148.x + d.x;
            g_49a148.y = g_49a148.y + d.y;
            g_49a148.z = g_49a148.z + d.z;
        }
    }
}


// FUNCTION: STUNTGP_D3D 0x41d390
void FUN_41d390()
{
    g_60f010 = FUN_428840(g_624474);
}

// FUNCTION: STUNTGP_D3D 0x41d3b0
void FUN_41d3b0()
{
    for (int i = 0; i < 10; i++)
    {
        g_4d5bb8->unk2518[i] = g_4d5bb8->unk24f0[i];
    }
}

// FUNCTION: STUNTGP_D3D 0x41d3d0
void FUN_41d3d0()
{
    for (int i = 0; i < 10; i++)
    {
        g_4d5bb8->unk2540[i] = g_4d5bb8->unk24f0[i];
    }
}

// Formats a frame count as a lap time, dropping leading zero fields.
// FUNCTION: STUNTGP_D3D 0x41d3f0
void FUN_41d3f0(int time, char *out)
{
    DWORD d[8];
    FUN_4482a0(time, d);
    if (d[5] != 0)
    {
        // STRING: STUNTGP_D3D 0x474898
        sprintf(out, "%d%d.%d%d.%d%d", d[5], d[4], d[3], d[2], d[1], d[0]);
    }
    else if (d[4] != 0)
    {
        // STRING: STUNTGP_D3D 0x4748a8
        sprintf(out, "%d.%d%d.%d%d", d[4], d[3], d[2], d[1], d[0]);
    }
    else if (d[3] != 0)
    {
        // STRING: STUNTGP_D3D 0x4748b8
        sprintf(out, "%d%d.%d%d", d[3], d[2], d[1], d[0]);
    }
    else
    {
        // STRING: STUNTGP_D3D 0x4748c4
        sprintf(out, "%d.%d%d", d[2], d[1], d[0]);
    }
}
// Records the split time and shows the gap to the previous lap's split.
// FUNCTION: STUNTGP_D3D 0x41d4b0
void FUN_41d4b0()
{
    int split = g_4d5bb8->unk24ec;
    g_4d5bb8->unk24f0[split] = g_4d5bb8->unk23a4 * 12000 + g_4d5bb8->unk23c4;
    if (g_4d5bb8->unk23bc > 0)
    {
        int index = g_4d5bb8 - g_49a1f8;
        int diff = g_4d5bb8->unk24f0[split] - g_4d5bb8->unk2518[split];
        int gap = abs(diff);
        if (gap <= 1800)
        {
            char time[16];
            char text[32];
            FUN_41d3f0(gap, time);
            // STRING: STUNTGP_D3D 0x4748cc
            sprintf(text, "%s %s %s %s ", g_60f02c[index].name, g_6127a0[25], time, g_6127a0[26]);
            strcat(text, diff < 0 ? g_6127a0[29] : g_6127a0[30]);
            FUN_442cf0(180, text, g_4d5bb8, 0, 0);
        }
    }
}


// Shows the split gap to the car behind (when leading) or to the car ahead.
// FUNCTION: STUNTGP_D3D 0x41d5c0
void FUN_41d5c0()
{
    char time[16];
    char text[32];
    if (!g_612948.unk03cc[1] || g_4d5bb8->unk23bc < 0 || g_4d5bb8->unk23a4 >= g_60eff8)
    {
        return;
    }
    if (g_4d5bb8->unk24ac == 0)
    {
        Car *second = g_612948.unk03cc[1];
        if (second->unk23a4 < 1)
        {
            return;
        }
        int index = second - g_49a1f8;
        int split = second->unk24ec - 1;
        if (split < 0)
        {
            split = 9;
        }
        int gap = abs((int)(g_4d5bb8->unk24f0[split] - second->unk24f0[split]));
        if (gap > 1800)
        {
            return;
        }
        FUN_41d3f0(gap, time);
        // STRING: STUNTGP_D3D 0x4748dc
        sprintf(text, "%s %s %s %s %s!", g_60f02c[index].name, g_6127a0[25], time, g_6127a0[26], g_6127a0[28]);
        FUN_442cf0(180, text, g_4d5bb8, 2, 0);
    }
    else
    {
        Car *ahead = g_612948.unk03cc[g_4d5bb8->unk24ac - 1];
        int split = g_4d5bb8->unk24ec;
        int gap = abs((int)(g_4d5bb8->unk24f0[split] - ahead->unk24f0[split]));
        if (gap > 1800)
        {
            return;
        }
        FUN_41d3f0(gap, time);
        // STRING: STUNTGP_D3D 0x4748ec
        sprintf(text, "%s %s %s %s %s!", g_60f02c[ahead - g_49a1f8].name, g_6127a0[25], time, g_6127a0[26],
                g_6127a0[27]);
        FUN_442cf0(180, text, g_4d5bb8, 2, 0);
    }
}

// FUNCTION: STUNTGP_D3D 0x41d8a0
void FUN_41d8a0()
{
    if (g_4d5bb8->active == 1 && FUN_402590(g_4d5bb8))
    {
        unsigned int lap = g_4d5bb8->unk23a4;
        if (lap > 1 && lap <= g_60eff8 && lap >= g_60eff8)
        {
            FUN_442cf0(180, g_6127a0[46], g_4d5bb8, 2, 0);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x41d8f0
void FUN_41d8f0()
{
    char text[64];
    char time[16];
    if (g_4d5bb8->unk23a4 < g_60eff8)
    {
        if (g_4d5bb8->unk23a4 == 1)
        {
            // STRING: STUNTGP_D3D 0x4748fc
            sprintf(text, "LAP %d/%d", 1, g_60eff8);
        }
        else
        {
            // STRING: STUNTGP_D3D 0x474908
            sprintf(text, "LAP %d/%d - TIME:", g_4d5bb8->unk23a4, g_60eff8);
            FUN_41d3f0(g_4d5bb8->unk23c8, time);
            // STRING: STUNTGP_D3D 0x47491c
            sprintf(text, "%s %s", text, time);
        }
        FUN_442cf0(180, text, g_4d5bb8, 2, 0);
    }
}

void FUN_41da50(int *count);
void FUN_41d9f0(int *a, int *b);

// The current car crossed the line: records its finish, and once the race is decided
// finishes everyone still running with a time extrapolated from their remaining distance.
// FUNCTION: STUNTGP_D3D 0x41da70
void FUN_41da70()
{
    g_4d5bb8->unk24e0 = 1;
    g_4d5bb8->unk24e4 = g_4d5bb8->unk24ac;
    int t = g_4d5bb8->unk260c;
    g_4d5bb8->unk23d0 = t;
    g_612948.unk040c[g_612948.unk044c] = g_4d5bb8;
    g_612948.unk044c++;
    if (g_4d5bb8->unk23cc < g_60f000[1])
    {
        g_60f000[1] = g_4d5bb8->unk23cc;
    }
    if (t > g_60f000[3])
    {
        g_60f000[3] = t;
    }
    int count;
    FUN_41da50(&count);
    int a;
    int b;
    FUN_41d9f0(&a, &b);
    if (b == 0 && a != 0 && g_612948.unk044c < count)
    {
        float lap = g_60f000[0] * 150 / 100;
        do
        {
            Car *car = g_612948.unk03cc[g_612948.unk044c];
            car->unk24e0 = 1;
            car->unk24e4 = car->unk24ac;
            t = car->unk260c;
            car->unk23d0 = t;
            float left = (100.0f - (float)fmod(car->unk23b0, 100.0)) * 0.01f;
            int laps = g_60eff8 - car->unk23a4;
            if (laps > 0)
            {
                left += laps;
            }
            car->unk23cc += (int)(lap * left);
            if (car->unk23d4 == 216000)
            {
                car->unk23d4 = car->unk23cc;
                car->unk23d8 = t;
            }
            if (car->unk23cc < g_60f000[1])
            {
                g_60f000[1] = car->unk23cc;
            }
            if (t > g_60f000[3])
            {
                g_60f000[3] = t;
            }
            g_612948.unk040c[g_612948.unk044c] = car;
            g_612948.unk044c++;
        } while (g_612948.unk044c < count);
    }
}


// FUNCTION: STUNTGP_D3D 0x41dc30
void FUN_41dc30()
{
    if (g_4d5bb8->unk23c4 < g_4d5bb8->unk23d4)
    {
        g_4d5bb8->unk23d4 = g_4d5bb8->unk23c4;
        FUN_41d3b0();
    }
    if (g_4d5bb8->unk23c4 < g_60f000[0])
    {
        g_60effc = g_60f000[0];
        g_60f000[0] = g_4d5bb8->unk23c4;
        FUN_41d3d0();
        if (g_60f2b0 == 4)
        {
            if (FUN_402590(g_4d5bb8))
            {
                if (FUN_442fb0() == 1)
                {
                    g_4d5bb8->unk23c0 = 1;
                }
                FUN_443de0();
            }
        }
        else if (g_60f2b0 == 2)
        {
            if (g_4d5bb8->unk23a4 < g_60eff8 && FUN_402590(g_4d5bb8))
            {
                FUN_443de0();
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x41dce0
void FUN_41dce0()
{
    unsigned int lap = g_4d5bb8->unk23a4;
    if (!lap)
    {
        g_4d5bb8->unk2440[0] = (int)g_4d5bb8->unk260c;
    }
    else
    {
        g_4d5bb8->unk2440[lap] = (int)g_4d5bb8->unk260c - g_4d5bb8->unk2440[lap - 1];
    }
    if (g_4d5bb8->unk2440[g_4d5bb8->unk23a4] > g_4d5bb8->unk23d8)
    {
        g_4d5bb8->unk23d8 = g_4d5bb8->unk2440[g_4d5bb8->unk23a4];
    }
    if (g_4d5bb8->unk2440[g_4d5bb8->unk23a4] > g_60f000[2])
    {
        g_60f000[2] = g_4d5bb8->unk2440[g_4d5bb8->unk23a4];
    }
}

// FUNCTION: STUNTGP_D3D 0x41dd60
void FUN_41dd60()
{
    if (g_60f2b4 == 3)
    {
        return;
    }
    g_4d5bb8->unk26a8 = 0;
    FUN_41dce0();
    if (g_60f2b0 != 3)
    {
        FUN_41dc30();
    }
    g_4d5bb8->unk23c8 = g_4d5bb8->unk23c4;
    g_4d5bb8->unk23dc[g_4d5bb8->unk23a4] = g_4d5bb8->unk23c4;
    if (g_4d5bb8->unk23a4 > 24)
    {
        g_4d5bb8->unk23dc[g_4d5bb8->unk23a4] = 0;
    }
    else
    {
        g_4d5bb8->unk23a4++;
    }
    g_4d5bb8->unk23bc++;
    g_4d5bb8->unk23c4 = 0;
    FUN_407000();
    if (g_60eff8 != 100 && g_4d5bb8->unk23a4 > g_60eff8 && !g_4d5bb8->unk24e0)
    {
        FUN_41da70();
    }
    if (g_60f2b0 == 2)
    {
        FUN_41d8a0();
        if (g_576be0)
        {
            FUN_41d8f0();
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x41de70
void FUN_41de70()
{
    Car *car = g_4d5bb8;
    if (car->unk24e0 == 1)
    {
        car->unk23c4 = -1;
        return;
    }
    if (g_60eff8 != 100 && car->unk23a4 > g_60eff8)
    {
        car->unk23c4 = 1;
        return;
    }
    if (car->unk23c4 != -1)
    {
        car->unk23c4++;
    }
    if (car->unk23cc != -1)
    {
        car->unk23cc++;
    }
}

void FUN_41d9c0(int value);

// Tracks the car along the race path: lap fraction, path direction and the nearest point on it.
// FUNCTION: STUNTGP_D3D 0x41ded0
void FUN_41ded0(float *pos, CameraPath *path, int *index)
{
    Vec4 *pts = path->points;
    int i = *index;
    int step = 0;
    unsigned int a;
    Vec4 d;
    float len;
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
        FUN_44eda0(&d.x, &len);
        Vec4 q;
        q.x = pos[0] - pts[a].x;
        q.y = pos[1] - pts[a].y;
        q.z = pos[2] - pts[a].z;
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
    FUN_41d9c0(g_4d5bb8->unk24a4 * 100 / g_571328->count);
    g_4d5bb8->unk23b4 = g_4d5bb8->unk23b0;
    float f = t / len;
    g_4d5bb8->unk23b0 = (f + g_4d5bb8->unk24a4) * 100.0f / g_571328->count;
    g_4d5bb8->unk24c0 = d;
    g_4d5bb8->unk24d0.x = g_482690 * d.y - g_48268c * d.z;
    g_4d5bb8->unk24d0.y = g_482688 * d.z - g_482690 * d.x;
    g_4d5bb8->unk24d0.z = g_48268c * d.x - g_482688 * d.y;
    Vec3_Normalize(&g_4d5bb8->unk24d0.x);
    d.x = t * d.x;
    d.y = t * d.y;
    d.z = t * d.z;
    g_4d5bb8->unk24b0.x = d.x + pts[a].x;
    g_4d5bb8->unk24b0.y = d.y + pts[a].y;
    g_4d5bb8->unk24b0.z = d.z + pts[a].z;
}


// STUB: STUNTGP_D3D 0x41e0f0
void FUN_41e0f0()
{
}

// Tracks the car along the race path and fires the lap hook once at the 99 -> 0 wrap.
// FUNCTION: STUNTGP_D3D 0x41e210
void FUN_41e210()
{
    FUN_41de70();
    if (g_571328->points)
    {
        FUN_41ded0(&g_4d5bb8->posX, g_571328, &g_4d5bb8->unk24a4);
        int prev = g_4d5bb8->unk23a8 % 100;
        int cur = g_4d5bb8->unk23ac % 100;
        if (prev < 0)
        {
            prev = (prev + 100) % 100;
        }
        if (cur < 0)
        {
            cur = (cur + 100) % 100;
        }
        if (prev == 99 && cur == 0)
        {
            if (!g_4d5bb8->unk24a8)
            {
                g_4d5bb8->unk24a8 = 1;
                FUN_41dd60();
                FUN_41e0f0();
                FUN_41d760();
                return;
            }
        }
        else
        {
            g_4d5bb8->unk24a8 = 0;
        }
        FUN_41e0f0();
        FUN_41d760();
    }
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

// Rebuilds an orthonormal rotation once all four points are grounded and the body is level.
// FUNCTION: STUNTGP_D3D 0x421e70
void FUN_421e70(Body *body)
{
    for (unsigned int i = 0; i < 4; i++)
    {
        if (body->points[i].unk40 < 4)
        {
            return;
        }
    }
    Vec4 r2 = *(Vec4 *)&body->mat1[8];
    Vec4 ref = {0.0f, 0.0f, 1.0f, 0.0f};
    float dx = r2.x;
    dx += ref.x * r2.z;
    if ((float)fabs(dx) <= 0.05f && (float)fabs(r2.y + ref.y * r2.z) <= 0.05f)
    {
        Vec4 r0 = *(Vec4 *)&body->mat1[0];
        r0.x *= 1.5f;
        Vec4 r1 = *(Vec4 *)&body->mat1[4];
        r1.y *= 1.5f;
        r2 = *(Vec4 *)&body->mat1[8];
        r2.z *= 1.5f;
        Vec3_Normalize(&r0.x);
        Vec3_Normalize(&r1.x);
        Vec3_Normalize(&r2.x);
        Matrix_FromRows(&r0.x, &r1.x, &r2.x, body->mat1);
    }
}

// FUNCTION: STUNTGP_D3D 0x421fa0
void FUN_421fa0(Body *body)
{
    for (unsigned int i = 0; i < 4; i++)
    {
        if (body->points[i].unk40 < 4)
        {
            return;
        }
    }
    Vec4 up = *(Vec4 *)&body->mat1[8];
    Vec4 ref = {0.0f, 0.0f, 1.0f, 0.0f};
    float dx = up.x;
    dx += ref.x * up.z;
    if ((float)fabs(dx) <= 0.002f && (float)fabs(up.y + ref.y * up.z) <= 0.002f)
    {
        Matrix_Identity(body->mat1);
    }
}

extern Vec4 g_498198;
void FUN_44f8e0(float *m);
void FUN_44efd0(float *out, float *a, float *b);

// Spins m about the axis from point i to the body centre, expressed in the body's unk108 frame.
// FUNCTION: STUNTGP_D3D 0x422020
void FUN_422020(Body *body, int i, float turns, float *m)
{
    float a[16];
    float b[16];
    float t[16];
    Vec4 s;
    Vec4 up;
    Vec4 n;
    Matrix_Transpose(t, body->mat0);
    Matrix_Multiply3(t, body->unk108);
    Matrix_Multiply3(t, body->mat0);
    Vec4 d;
    d.x = body->pos.x - body->points[i].world.x;
    d.y = body->pos.y - body->points[i].world.y;
    d.z = body->pos.z - body->points[i].world.z;
    n.x = t[0] * d.x + t[4] * d.y + t[8] * d.z;
    n.y = t[1] * d.x + t[5] * d.y + t[9] * d.z;
    n.z = t[2] * d.x + t[6] * d.y + t[10] * d.z;
    Vec3_Normalize(&n.x);
    up = g_498198;
    s.x = up.y * n.z - up.z * n.y;
    s.y = up.z * n.x - up.x * n.z;
    s.z = up.x * n.y - up.y * n.x;
    Vec3_Normalize(&s.x);
    up.x = s.y * n.z - s.z * n.y;
    up.y = s.z * n.x - s.x * n.z;
    up.z = s.x * n.y - s.y * n.x;
    Vec3_Normalize(&up.x);
    Matrix_FromRows(&s.x, &up.x, &n.x, a);
    Matrix_Identity(b);
    Matrix_RotateX(b, (turns * 360.0f) * 0.15915494f);
    Matrix_Transpose(t, a);
    Matrix_Multiply3(t, b);
    FUN_44efd0(b, t, a);
    FUN_44f8e0(b);
    Matrix_Multiply3(m, b);
    FUN_44f8e0(m);
}

// Moves the body's points so their centroid is at the origin.
// FUNCTION: STUNTGP_D3D 0x422200
void FUN_422200(Body *body)
{
    Vec4 c;
    c.x = 0.0f;
    c.y = 0.0f;
    c.z = 0.0f;
    unsigned int n = body->numPoints;
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        c.x += body->points[i].local.x;
        c.y += body->points[i].local.y;
        c.z += body->points[i].local.z;
    }
    float scale = -1.0f / n;
    c.x *= scale;
    c.y *= scale;
    c.z *= scale;
    for (i = 0; i < body->numPoints; i++)
    {
        body->points[i].local.x += c.x;
        body->points[i].local.y += c.y;
        body->points[i].local.z += c.z;
    }
    body->unk140 = c.y;
}

// Returns the palette index (skipping 0) nearest to the colour, by Manhattan distance.
// FUNCTION: STUNTGP_D3D 0x4222c0
int FUN_4222c0(BYTE *palette, float r, float g, float b)
{
    int best = -1;
    int ir = (int)r;
    int ig = (int)g;
    int ib = (int)b;
    int bestDist = 10000000;
    BYTE *p = palette + 5;
    for (int i = 1; i < 256; i++)
    {
        int pr = *p++;
        int pg = *p++;
        int pb = *p;
        p += 2;
        int d = abs(pr - ir);
        if (d <= bestDist)
        {
            d += abs(pg - ig);
            if (d <= bestDist)
            {
                d += abs(pb - ib);
                if (d <= bestDist)
                {
                    best = i;
                    bestDist = d;
                }
            }
        }
    }
    return best;
}

// Lays out the collision points for the current car's model.
// FUNCTION: STUNTGP_D3D 0x4082d0
void FUN_4082d0()
{
    Body *body = &g_4d5bb8->body;
    body->points[0].radius = 70.0f;
    body->points[1].radius = 70.0f;
    body->points[2].radius = 70.0f;
    body->points[3].radius = 70.0f;
    body->points[1].local.x = 60.000004f;
    body->points[3].local.x = 60.000004f;
    body->points[0].local.x = -60.000004f;
    body->points[0].local.y = 0.0f;
    body->points[0].local.z = -110.0f;
    body->points[0].unk44 = 0.25f;
    body->points[1].local.y = 0.0f;
    body->points[1].local.z = -110.0f;
    body->points[1].unk44 = 0.25f;
    body->points[2].local.x = -60.000004f;
    body->points[2].local.y = 0.0f;
    body->points[2].local.z = 110.0f;
    body->points[2].unk44 = 0.25f;
    body->numPoints = 4;
    body->points[3].local.y = 0.0f;
    body->points[3].local.z = 110.0f;
    body->points[3].unk44 = 0.25f;
    switch (g_60f02c[g_4d5bb8 - g_49a1f8].unk08)
    {
    case 1:
    case 3:
    case 4:
    case 5:
    case 8:
    case 9:
    case 10:
    case 12:
    case 14:
    case 15:
    case 16:
    case 18:
    case 19:
    case 20:
        body->numPoints = 5;
        body->points[4].local.x = 0.0f;
        body->points[4].local.y = 30.000002f;
        body->points[4].local.z = 0.0f;
        body->points[4].unk44 = 0.25f;
        body->points[4].radius = 60.000004f;
        break;
    case 2:
    case 7:
    case 11:
    case 13:
        body->numPoints = 5;
        body->points[4].local.x = 0.0f;
        body->points[4].local.y = 50.0f;
        body->points[4].local.z = 0.0f;
        body->points[4].unk44 = 0.25f;
        body->points[4].radius = 80.0f;
        break;
    case 17:
        body->points[4].local.x = 0.0f;
        body->points[4].local.y = 50.0f;
        body->points[4].local.z = 0.0f;
        body->points[4].unk44 = 0.25f;
        body->points[4].radius = 80.0f;
        body->numPoints = 6;
        body->points[5].local.x = 0.0f;
        body->points[5].local.y = 130.0f;
        body->points[5].local.z = 0.0f;
        body->points[5].unk44 = 0.25f;
        body->points[5].radius = 80.0f;
        break;
    case 6:
        body->points[4].local.x = 0.0f;
        body->points[4].local.y = 60.000004f;
        body->points[4].local.z = 70.0f;
        body->points[4].unk44 = 0.25f;
        body->points[4].radius = 110.0f;
        body->numPoints = 6;
        body->points[5].local.x = 0.0f;
        body->points[5].local.y = 60.000004f;
        body->points[5].local.z = -70.0f;
        body->points[5].unk44 = 0.25f;
        body->points[5].radius = 110.0f;
        break;
    }
    FUN_422200(body);
    unsigned int i;
    for (i = 0; i < body->numPoints; i++)
    {
        body->points[i].world.x = body->points[i].local.x + body->pos.x;
        body->points[i].world.y = body->pos.y + body->points[i].local.y;
        body->points[i].world.z = body->points[i].local.z + body->pos.z;
        body->points[i].prev = body->points[i].world;
    }
    body->radius = 0.0f;
    for (i = 0; i < body->numPoints; i++)
    {
        float r = (float)sqrt(body->points[i].local.x * body->points[i].local.x +
                              body->points[i].local.y * body->points[i].local.y +
                              body->points[i].local.z * body->points[i].local.z) +
                  body->points[i].radius;
        if (r > body->radius)
        {
            body->radius = r;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x4085e0
void FUN_4085e0()
{
    Body *body = &g_4d5bb8->body;
    body->pos.x = 0.0f;
    body->pos.y = 1000.0f;
    body->pos.z = -10000.0f;
    body->unk40 = 1000.0f;
    Matrix_Identity(body->mat0);
    Matrix_Identity(body->mat1);
    Matrix_Identity(body->mat2);
    body->vel[0] = 0.0f;
    body->vel[1] = 0.0f;
    body->vel[2] = 0.0f;
    FUN_4082d0();
}

// FUNCTION: STUNTGP_D3D 0x408640
void FUN_408640(Car *car, float *pos)
{
    Body *body = &car->body;
    car->unk1bbc = *(Vec4 *)pos;
    *(Vec4 *)&car->posX = *(Vec4 *)pos;
    body->prevPos = *(Vec4 *)pos;
    body->pos = *(Vec4 *)pos;
    for (unsigned int i = 0; i < body->numPoints; i++)
    {
        body->points[i].world.x = body->points[i].local.x + body->pos.x;
        body->points[i].world.y = body->pos.y + body->points[i].local.y;
        body->points[i].world.z = body->points[i].local.z + body->pos.z;
        body->points[i].prev = body->points[i].world;
    }
}

// Places the car 2000 units ahead of the slot camera, 500 up.
// FUNCTION: STUNTGP_D3D 0x408710
void FUN_408710()
{
    Body *body = &g_474630->body;
    Vec4 dir = g_4722d0->axisZ;
    Vec4 up;
    up.x = 0.0f;
    up.y = dir.y;
    up.z = 0.0f;
    dir.x -= up.x;
    dir.y -= up.y;
    dir.z -= up.z;
    Vec3_Normalize(&dir.x);
    dir.x *= 2000.0f;
    dir.y *= 2000.0f;
    dir.z *= 2000.0f;
    dir.y += 500.0f;
    body->pos.x = dir.x + g_4722d0->cam.pos.x;
    body->pos.y = dir.y + g_4722d0->cam.pos.y;
    body->pos.z = dir.z + g_4722d0->cam.pos.z;
    for (unsigned int i = 0; i < body->numPoints; i++)
    {
        body->points[i].world.x = body->points[i].local.x + body->pos.x;
        body->points[i].world.y = body->points[i].local.y + body->pos.y;
        body->points[i].world.z = body->points[i].local.z + body->pos.z;
    }
    Matrix_Identity(body->mat0);
    Matrix_Identity(body->mat1);
    Matrix_Identity(body->mat2);
    body->vel[0] = 0.0f;
    body->vel[1] = 0.0f;
    body->vel[2] = 0.0f;
    g_474630->posX = dir.x + g_4722d0->cam.pos.x;
    g_474630->posY = dir.y + g_4722d0->cam.pos.y;
    g_474630->posZ = dir.z + g_4722d0->cam.pos.z;
    Matrix_Identity(g_474630->matrix);
    Matrix_Identity(g_474630->unk1c0c);
    Matrix_Identity(g_474630->unk1c4c);
    g_474630->unk1c8c.x = 0.0f;
    g_474630->unk1c8c.y = 0.0f;
    g_474630->unk1c8c.z = 0.0f;
}

// FUNCTION: STUNTGP_D3D 0x4088b0
void FUN_4088b0(Body *body)
{
    memcpy(body->mat0, g_4d5bb8->matrix, sizeof(body->mat0));
    memcpy(body->mat1, g_4d5bb8->unk1c0c, sizeof(body->mat1));
    body->pos = *(Vec4 *)&g_4d5bb8->posX;
    *(Vec4 *)body->vel = g_4d5bb8->unk1c8c;
}

// FUNCTION: STUNTGP_D3D 0x408920
void FUN_408920(Body *body)
{
    g_4d5bb8->unk1bbc = *(Vec4 *)&g_4d5bb8->posX;
    memcpy(g_4d5bb8->matrix, body->mat0, sizeof(g_4d5bb8->matrix));
    memcpy(g_4d5bb8->unk1c0c, body->mat1, sizeof(g_4d5bb8->unk1c0c));
    *(Vec4 *)&g_4d5bb8->posX = body->pos;
    g_4d5bb8->unk1c8c = *(Vec4 *)body->vel;
}

extern Vec4 g_498198;
void FUN_413290(float *v);

void FUN_40f760(Body *body, int i, float angle, float *m);

// Turns point i's slide along the contact plane into a capped rotation about it, signed by the body's spin.
// FUNCTION: STUNTGP_D3D 0x4089b0
void FUN_4089b0(Body *body, float *m, int i, float limit)
{
    BodyPoint *pt = &body->points[i];
    Vec4 pr;
    Vec4 dv;
    Vec4 w;
    Vec4 p = pt->local;
    float r = (float)sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
    w.x = p.x * body->mat1[0] + p.y * body->mat1[4] + p.z * body->mat1[8];
    w.y = p.x * body->mat1[1] + p.y * body->mat1[5] + p.z * body->mat1[9];
    w.z = p.x * body->mat1[2] + p.y * body->mat1[6] + p.z * body->mat1[10];
    dv.x = w.x - p.x;
    dv.y = w.y - p.y;
    dv.z = w.z - p.z;
    float a = g_498198.x * dv.x + g_498198.y * dv.y + g_498198.z * dv.z;
    pr.x = g_498198.x * a;
    pr.y = g_498198.y * a;
    pr.z = g_498198.z * a;
    p.x = dv.x - pr.x;
    p.y = dv.y - pr.y;
    p.z = dv.z - pr.z;
    FUN_44eda0(&p.x, &a);
    if (limit * 0.2f < a)
    {
        a = limit * 0.1f;
    }
    a = a / r;
    w.x = body->points[i].local.z * body->spin.y - body->spin.z * body->points[i].local.y;
    w.y = body->points[i].local.x * body->spin.z - body->points[i].local.z * body->spin.x;
    w.z = body->points[i].local.y * body->spin.x - body->points[i].local.x * body->spin.y;
    Vec3_Normalize(&w.x);
    if (p.x * w.x + p.y * w.y + p.z * w.z < 0.0f)
    {
        a = -a;
    }
    FUN_40f760(body, i, a, m);
}

// FUNCTION: STUNTGP_D3D 0x408bc0
void FUN_408bc0(Body *body, float *out, int point, float limit)
{
    Vec4 v = *(Vec4 *)body->vel;
    float d = g_498198.x * v.x + g_498198.y * v.y + g_498198.z * v.z;
    Vec4 p;
    p.x = g_498198.x * d;
    p.y = g_498198.y * d;
    p.z = g_498198.z * d;
    Vec4 t;
    t.x = v.x - p.x;
    t.y = v.y - p.y;
    t.z = v.z - p.z;
    FUN_44eda0(&t.x, &d);
    if (d > limit * 0.2f)
    {
        d = limit * 0.1f;
    }
    v.x = t.x * d;
    v.y = t.y * d;
    v.z = t.z * d;
    out[0] -= v.x;
    out[1] -= v.y;
    out[2] -= v.z;
}

// FUNCTION: STUNTGP_D3D 0x408cb0
void FUN_408cb0(float speed)
{
    float f = speed * 0.025f;
    f = f * f;
    if (f > 5.0f)
    {
        f = 5.0f;
    }
    Vec4 v;
    v.x = g_498198.x * f;
    v.y = g_498198.y * f;
    v.z = g_498198.z * f;
    FUN_413290(&v.x);
}

// FUNCTION: STUNTGP_D3D 0x408d10
void FUN_408d10(float amount)
{
    if (g_60f2b4 != 3)
    {
        float a = (float)fabs(amount);
        if (a >= 1.0f)
        {
            a *= 0.16666667f;
            if (a > 10.0f)
            {
                a = 10.0f;
            }
            g_4d5bb8->unk2568 += (int)a;
            if (g_4d5bb8->unk2568 > g_4d5bb8->unk256c)
            {
                g_4d5bb8->unk2568 = g_4d5bb8->unk256c;
            }
        }
    }
}

int size_of_file(char *path);
int bload(char *path, char *buffer, int maxSize);
void *Mem_Alloc(int size, int type);
int Mem_Free(void *ptr);
void FUN_4436e0(Car *car);
extern int g_ControlMethod;

// Loads Car<n>.cfg into the template car and runs every section parser over it.
// FUNCTION: STUNTGP_D3D 0x40bde0
void FUN_40bde0()
{
    char path[128];
    // STRING: STUNTGP_D3D 0x4738e4
    sprintf(path, "%s\\Config\\Vehicles\\Car%d.cfg", g_GameDirectory, g_472c74);
    g_4d5bb8 = g_474630;
    int size = size_of_file(path);
    char *text = (char *)Mem_Alloc(size + 0x20, 0);
    bload(path, text, size);
    FUN_40b490(text);
    FUN_40b5b0(text);
    FUN_40b690(text);
    FUN_40b750(text);
    FUN_40b7a0(text);
    FUN_40b930(text);
    FUN_40b990(text);
    FUN_40ba10(text);
    FUN_40bac0(text);
    FUN_40bb60(text);
    FUN_40bc30(text);
    FUN_40bcb0(text);
    Mem_Free(text);
    FUN_40a1d0();
    FUN_40a120();
    g_4d5bb8->inputMode = g_ControlMethod;
    g_4d5bb8->unk28a8 = 1;
    FUN_4436e0(g_4d5bb8);
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

// FUNCTION: STUNTGP_D3D 0x413290
void FUN_413290(float *v)
{
    if (g_60f2b4 == 2)
    {
        g_4d5bb8->race.unk70 += (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
        v[0] *= 4.0f;
        v[1] *= 4.0f;
        v[2] *= 4.0f;
        g_4d5bb8->unk2328 += v[0];
        g_4d5bb8->unk232c += v[1];
        g_4d5bb8->unk2330 += v[2];
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
    car->unk2d04[0].count = 0;
    car->unk2d04[1].count = 0;
}

// Turns a point in the g_4d5b30 frame into a world position on the current car.
// FUNCTION: STUNTGP_D3D 0x415190
void FUN_415190(Car *car, Vec4 *p, Vec4 *out)
{
    Vec4 t;
    t.x = p->x * g_4d5b30[0] + (p->y * g_4d5b30[4] + p->z * g_4d5b30[8]);
    t.y = p->x * g_4d5b30[1] + (p->y * g_4d5b30[5] + p->z * g_4d5b30[9]);
    t.z = p->x * g_4d5b30[2] + (p->y * g_4d5b30[6] + p->z * g_4d5b30[10]);
    t.x = -t.x;
    Vec4 a;
    a.x = t.x * g_4d5bb8->axisX.x;
    a.y = t.x * g_4d5bb8->axisX.y;
    a.z = t.x * g_4d5bb8->axisX.z;
    t.y = 70.0f - t.y - g_4d5bb8->unk288c;
    Vec4 b;
    b.x = t.y * g_4d5bb8->axisY.x;
    b.y = t.y * g_4d5bb8->axisY.y;
    b.z = t.y * g_4d5bb8->axisY.z;
    Vec4 c;
    c.x = t.z * g_4d5bb8->axisZ.x;
    c.y = t.z * g_4d5bb8->axisZ.y;
    c.z = t.z * g_4d5bb8->axisZ.z;
    a.x = b.x + a.x;
    a.y = b.y + a.y;
    a.z = b.z + a.z;
    a.x = c.x + a.x;
    a.y = c.y + a.y;
    a.z = c.z + a.z;
    out->x = g_4d5bb8->posX - a.x;
    out->y = g_4d5bb8->posY - a.y;
    out->z = g_4d5bb8->posZ - a.z;
}

// FUNCTION: STUNTGP_D3D 0x4152c0
void FUN_4152c0(Car *car)
{
    car->unk28bc[0].trail.count = 0;
    car->unk28bc[1].trail.count = 0;
}

extern float g_60dff0[0x80];

// Advances the car's path knot to the next one flagged in g_60dff0 and caches its position and direction.
// FUNCTION: STUNTGP_D3D 0x4127e0
void FUN_4127e0(CameraPath *path, Car *car)
{
    int i = car->unk24a4;
    {
        int skipped = 0;
        for (;;)
        {
            if (i < 0)
            {
                i = path->count - -i % path->count;
            }
            else
            {
                i = i % path->count;
            }
            if (g_60dff0[i * 127 / path->count] == 1.0f)
            {
                break;
            }
            i++;
            skipped++;
        }
        car->unk24a4 += skipped;
    }
    Vec4 *points = path->points;
    car->unk24b0 = points[i];
    Vec4 d;
    d.x = points[i + 1].x - points[i].x;
    d.y = points[i + 1].y - points[i].y;
    d.z = points[i + 1].z - points[i].z;
    Vec3_Normalize(&d.x);
    car->unk24c0 = d;
    car->unk2644 = car->unk24a4;
    car->unk264c = car->unk24a4;
    car->unk2654 = car->unk24a4;
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

// FUNCTION: STUNTGP_D3D 0x413470
void FUN_413470(Car *car)
{
    for (int i = 0; i < 4; i++)
    {
        car->wheels[i].unk04 = 0;
        car->wheels[i].unk00 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x413490
void FUN_413490(Car *car)
{
    FUN_413470(car);
    car->unk1cec = 0;
    car->unk1cf0 = 0;
    car->unk1cfc = 0;
    car->unk1c9c.x = 0;
    car->unk1c9c.y = 0;
    car->unk1c9c.z = 0;
    car->unk1c8c.x = 0;
    car->unk1c8c.y = 0;
    car->unk1c8c.z = 0;
    car->unk1cac.x = 0;
    car->unk1cac.y = 0;
    car->unk1cac.z = 0;
    Matrix_Identity(car->unk1c0c);
    Matrix_Identity(car->unk1c4c);
}

// FUNCTION: STUNTGP_D3D 0x413500
void FUN_413500()
{
    for (int i = 0; i < 6; i++)
    {
        if (!g_60f02c[i].model)
        {
            g_49a1f8[i].active = 0;
        }
    }
}

void FUN_418d90(Car *car);

// Resets a car's motion, controls and race-assist state.
// FUNCTION: STUNTGP_D3D 0x413530
void FUN_413530(Car *car)
{
    FUN_413470(car);
    car->unk1cec = 0;
    car->unk1cf0 = 0;
    car->unk1c9c.x = 0;
    car->unk1c9c.y = 0;
    car->unk1c9c.z = 0;
    car->unk1c8c.x = 0;
    car->unk1c8c.y = 0;
    car->unk1c8c.z = 0;
    car->unk1cac.x = 0;
    car->unk1cac.y = 0;
    car->unk1cac.z = 0;
    Matrix_Identity(car->unk1c0c);
    Matrix_Identity(car->unk1c4c);
    car->unk1cf8 = 0;
    car->unk1cfc = 0;
    car->unk2250 = 0;
    car->unk2254 = 0;
    car->unk2258 = 0;
    memset(car->controls, 0, sizeof(car->controls));
    memset(car->prevControls, 0, sizeof(car->prevControls));
    car->unk2298 = 0;
    car->unk229c = 0;
    car->unk22b4 = 0;
    car->unk22bc = 0;
    car->unk22c0 = 0;
    car->unk2640 = 0;
    car->unk2644 = 0;
    car->unk2648 = 0;
    car->unk264c = 0;
    car->unk2650 = 0;
    car->catchUp = 1;
    car->unk2634 = 1.0f;
    car->unk2620 = 1;
    car->unk2624 = 0;
    car->unk2628 = 0;
    car->unk262c = 0;
    FUN_414d80(car);
    FUN_414c50(car);
    FUN_414ef0(car);
    FUN_4152c0(car);
    FUN_418d90(car);
}

// FUNCTION: STUNTGP_D3D 0x414f00
void FUN_414f00()
{
    Car *car = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        if (car->active == 1 && car->unk26b0->objectCount >= 23)
        {
            car->unk2d04[0].pos = *car->unk26b0->lods[0][23].matrix;
            car->unk2d04[1].pos = *car->unk26b0->lods[0][24].matrix;
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
        car->unk28bc[1].active = car->unk28bc[0].active = 0;
        if (car->active == 1 && car->unk26b0->objectCount >= 21)
        {
            ObjectDef *mesh = &car->unk26b0->lods[0][21];
            car->unk28bc[0].active = 1;
            car->unk28bc[0].trail.pos = *mesh->matrix;
            if (car->unk26b0->objectCount >= 22)
            {
                mesh = &car->unk26b0->lods[0][22];
                car->unk28bc[1].active = 1;
                car->unk28bc[1].trail.pos = *mesh->matrix;
            }
        }
        car++;
    }
    g_4d5bb8 = g_49a1f8;
}

extern float g_482674;

// GLOBAL: STUNTGP_D3D 0x474634
DWORD g_474634[3] = {0xffff80, 0xff8010, 0xff1000};

// Every other call, puffs a flame particle from pos, sized by the scaled strength.
// FUNCTION: STUNTGP_D3D 0x416100
void FUN_416100(Vec4 *pos, Vec4 *vel, float strength)
{
    g_4d5bb8->unk7624 = (g_4d5bb8->unk7624 - 1) & 1;
    if (g_4d5bb8->unk7624)
    {
        return;
    }
    strength = (float)fabs(g_482674 * strength);
    if (strength < 0.1f)
    {
        strength = 0.1f;
    }
    else if (strength > 1.0f)
    {
        strength = 1.0f;
    }
    Vec4 r;
    Unk62a078 p;
    *(Camera *)&p.pos = g_4864e8;
    p.vel[0] = vel->x * 0.1f;
    p.vel[1] = vel->y * 0.1f;
    p.vel[2] = vel->z * 0.1f;
    p.pos = *pos;
    p.flags = 15;
    r.x = FUN_42f1c0(10.0f);
    r.z = FUN_42f1c0(10.0f);
    float rz = r.z;
    p.vel[0] = r.x + p.vel[0];
    p.gravity = g_48266c;
    p.colors[1] = g_474634[1];
    p.vel[1] = p.vel[1] + 10.0f;
    p.unk98 = 0x60;
    p.mode = 2;
    p.texture = 4;
    p.lifetime = 60;
    p.unk68 = 0.01f;
    p.unk7c = 1;
    p.anim = NULL;
    p.vel[2] = rz + p.vel[2];
    p.sizeIn = 6.0f;
    p.sizeOut = 54.0f;
    p.alphaIn = 9.0f;
    p.alphaOut = 45.0f;
    p.spin = 8.0f;
    p.colors[0] = g_474634[0];
    p.colors[2] = g_474634[2];
    p.colorIn = 12.0f;
    p.colorOut = 24.0f;
    p.size = strength * 0.1f + 0.25f;
    p.alpha = strength * 255.0f;
    FUN_45e110(&p);
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
            if (car->unk26b0->objectCount > 19)
            {
                ObjectDef *meshes = car->unk26b0->lods[car->unk26b0->lod];
                car->unk328c.active = 1;
                car->unk328c.unk004 = meshes[19].matrix[0];
                car->unk328c.unk014 = meshes[19].matrix[1];
                if (meshes[20].visible == 1 && car->unk26b0->objectCount > 20)
                {
                    car->unk33cc.active = 1;
                    car->unk33cc.unk004 = meshes[20].matrix[0];
                    car->unk33cc.unk014 = meshes[20].matrix[1];
                }
            }
        }
        car++;
    }
    g_4d5bb8 = g_49a1f8;
}

// FUNCTION: STUNTGP_D3D 0x4163e0
void FUN_4163e0(Car *car, float value)
{
    int level = value * 255.0f;
    if (level >= car->unk2260)
    {
        car->unk2260 = level;
    }
    car->unk2268 = 30;
    car->unk2264 = value + value;
}
// Rotates a body-mesh point by g_4d5b30 and places it in world space, 70 units below the roof.
// FUNCTION: STUNTGP_D3D 0x416420
void FUN_416420(Car *car, Vec4 *in, float *out)
{
    Vec4 v = *in;
    Vec4 *r = (Vec4 *)out;
    r->x = g_4d5b30[0] * v.x + g_4d5b30[4] * v.y + g_4d5b30[8] * v.z;
    r->y = g_4d5b30[1] * v.x + g_4d5b30[5] * v.y + g_4d5b30[9] * v.z;
    r->z = g_4d5b30[2] * v.x + g_4d5b30[6] * v.y + g_4d5b30[10] * v.z;
    float nx = -r->x;
    Vec4 a;
    a.x = nx * car->axisX.x;
    a.y = nx * car->axisX.y;
    a.z = nx * car->axisX.z;
    Vec4 b;
    b.x = (70.0f - r->y - car->unk288c) * car->axisY.x;
    b.y = (70.0f - out[1] - car->unk288c) * car->axisY.y;
    b.z = (70.0f - out[1] - car->unk288c) * car->axisY.z;
    Vec4 c;
    c.x = out[2] * car->axisZ.x;
    c.y = out[2] * car->axisZ.y;
    c.z = out[2] * car->axisZ.z;
    a.x = a.x + b.x;
    a.y = a.y + b.y;
    a.z = a.z + b.z;
    a.x = c.x + a.x;
    a.y = c.y + a.y;
    a.z = c.z + a.z;
    out[0] = car->posX - a.x;
    out[1] = car->posY - a.y;
    out[2] = car->posZ - a.z;
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
            if (car->unk26b0->objectCount <= 11)
            {
                car->unk3134 = 0;
            }
            else
            {
                ObjectDef *meshes = car->unk26b0->lods[car->unk26b0->lod];
                float top = 0.0f;
                DWORD count = meshes[11].pointCount;
                Vec4 *points = meshes[11].points;
                for (DWORD j = 0; j < count; j++)
                {
                    if (top < points[j].z)
                    {
                        top = points[j].z;
                    }
                }
                car->unk3148 = meshes[11].matrix[2];
                car->unk3148.x = -car->unk3148.x;
                car->unk3138 = meshes[11].matrix[0];
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

// FUNCTION: STUNTGP_D3D 0x41d1f0
void FUN_41d1f0(Stat *stat, float value)
{
    stat->count++;
    stat->last = value;
    stat->sum = value + stat->sum;
    stat->mean = stat->sum / stat->count;
}

// FUNCTION: STUNTGP_D3D 0x41d230
void FUN_41d230()
{
    Car *car = g_4d5bb8;
    float d = car->unk723c - car->unk7238;
    if (d >= 0.0f)
    {
        FUN_41d1f0(&car->unk25b4, d);
    }
}

// FUNCTION: STUNTGP_D3D 0x41d270
void FUN_41d270(Car *a, Car *b)
{
    a->unk25c4[b - g_49a1f8] = 8;
    b->unk25c4[a - g_49a1f8] = 8;
}

// FUNCTION: STUNTGP_D3D 0x41d2c0
void FUN_41d2c0()
{
    for (int i = 0; i < 6; i++)
    {
        if (!g_4d5bb8->unk25dc[i] && g_4d5bb8->unk25c4[i])
        {
            g_4d5bb8->unk25f4[i]++;
        }
        g_4d5bb8->unk25dc[i] = g_4d5bb8->unk25c4[i];
        if (g_4d5bb8->unk25c4[i] > 0)
        {
            g_4d5bb8->unk25c4[i]--;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x41d300
void FUN_41d300()
{
    memset(g_4d5bb8->unk23dc, 0xff, sizeof(g_4d5bb8->unk23dc));
    g_4d5bb8->unk23c4 = -1;
    g_4d5bb8->unk23c8 = -1;
    g_4d5bb8->unk23cc = -1;
    g_4d5bb8->unk23d0 = 0;
    g_4d5bb8->unk23d4 = 0x34bc0;
    g_4d5bb8->unk23d8 = 0;
    g_4d5bb8->unk26a8 = 0;
    g_4d5bb8->unk23a4 = 0;
    g_4d5bb8->unk23bc = -1;
    g_4d5bb8->unk23a8 = -2;
    g_4d5bb8->unk23ac = -1;
    g_4d5bb8->unk23b8 = -1.0f;
    g_4d5bb8->unk24a4 = 0;
    g_4d5bb8->unk24a8 = 0;
    g_4d5bb8->unk7678 = 0;
    g_4d5bb8->unk24e0 = 0;
    g_4d5bb8->unk24e4 = 0;
}

// FUNCTION: STUNTGP_D3D 0x41d980
void FUN_41d980()
{
    g_4d5bb8 = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        FUN_41d300();
        g_4d5bb8++;
    }
    g_4d5bb8 = g_49a1f8;
    FUN_41d390();
}
