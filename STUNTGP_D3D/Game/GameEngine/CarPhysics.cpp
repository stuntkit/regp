#include "GameUpdate.h"

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

int FUN_442fb0();
void FUN_443de0();
void FUN_40e360(Car *sub);
void FUN_40e380(Car *sub);

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
void FUN_414d80(Car *car);
void FUN_414c50(Car *car);
void FUN_414ef0(Car *car);
void FUN_4152c0(Car *car);

CameraPath *FUN_428800(int id);

extern int g_60d688[37];
extern DWORD g_61297c;
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

// Adds the scaled gravity vector unless the velocity is already above the cap.
// STUB: STUNTGP_D3D 0x405c80
void FUN_405c80()
{
}

// GLOBAL: STUNTGP_D3D 0x49a158
CameraPath *g_49a158;

// GLOBAL: STUNTGP_D3D 0x49a15c
CameraPath *g_49a15c;

// GLOBAL: STUNTGP_D3D 0x49a16c
float g_49a16c;

// GLOBAL: STUNTGP_D3D 0x49a170
float g_49a170;

// GLOBAL: STUNTGP_D3D 0x472b88
float g_472b88[4] = {0.0f, 0.05f, 0.1f, 0.2f};

// GLOBAL: STUNTGP_D3D 0x472b98
float g_472b98 = 0.5f;

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

// STUB: STUNTGP_D3D 0x405610
void FUN_405610(float amount)
{
}

void FUN_4143e0(float amount);
void FUN_414420(float amount);
void FUN_4288d0(CameraPath *path, Vec4 *out, float dist);

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
        g_4d5bb8->unk7234 = g_612cfc;
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
        g_4d5bb8->unk7234 = g_612cfc;
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

// STUB: STUNTGP_D3D 0x40fc90
void FUN_40fc90()
{
}

// STUB: STUNTGP_D3D 0x410b30
void FUN_410b30()
{
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

// FUNCTION: STUNTGP_D3D 0x412670
void FUN_412670()
{
    if (g_60eff0 == 3)
    {
        return;
    }
    if (g_4d5bb8->race.unk4c[10])
    {
        g_4d5bb8->race.unk4c[10]--;
        g_4d5bb8->unk2634 = (float)g_4d5bb8->race.unk4c[10] * 0.0055555556f + 1.0f;
        g_4d5bb8->unk2250 = 1;
        FUN_40e360(g_4d5bb8);
        FUN_40e380(g_4d5bb8);
        return;
    }
    if (g_4d5bb8->race.unk00 && !g_4d5bb8->unk22b4 && g_4d5bb8->unk22bc == 1 &&
        g_4d5bb8->unk045c * 0.2f < g_4d5bb8->unk1cfc && abs((int)g_4d5bb8->race.unk00 - 60) < 10)
    {
        g_4d5bb8->race.unk4c[10] = 180;
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

// FUNCTION: STUNTGP_D3D 0x4166f0
void FUN_4166f0()
{
    Car *car = g_4d5bb8;
    ModelPart *part = car->unk26b0->parts[car->unk26b0->current];
    if (!car->unk226c)
    {
        if (car->unk328c.active == 1)
        {
            part->meshes[19].visible = 0;
        }
        if (car->unk33cc.active == 1)
        {
            part->meshes[20].visible = 0;
        }
    }
    else if (car->unk328c.active == 1)
    {
        part->meshes[19].visible = 1;
        part->meshes[19].matrix[1].x = car->unk328c.unk024.x;
        part->meshes[19].matrix[1].y = car->unk328c.unk024.y;
        part->meshes[19].matrix[1].z = car->unk328c.unk024.z;
        if (car->unk33cc.active == 1)
        {
            part->meshes[20].visible = 1;
            part->meshes[20].matrix[1].x = car->unk33cc.unk024.x;
            part->meshes[20].matrix[1].y = car->unk33cc.unk024.y;
            part->meshes[20].matrix[1].z = car->unk33cc.unk024.z;
        }
    }
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
    CarModel *model = g_4d5bb8->unk26b0;
    int i;
    for (i = 0; i < 3; i++)
    {
        model->parts[i]->meshes[6].visible = 0;
    }
    ModelPart *part = model->parts[model->current];
    ModelMesh *mesh = &part->meshes[6];
    ModelMesh *wheel = &part->meshes[1];
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

// Static description of a trail's look; the ring length is size.
struct TrailParams
{
    int unk00;        // 0x000
    DWORD size;       // 0x004
    int unk08;        // 0x008
    int unk0c;        // 0x00c
    void *unk10;      // 0x010
    BYTE unk14[0xfc]; // 0x014
};

// GLOBAL: STUNTGP_D3D 0x474c08
TrailParams g_474c08 = {1, 16, 2, 8};

// GLOBAL: STUNTGP_D3D 0x474d18
TrailParams g_474d18 = {0, 5, 1, 4};

// GLOBAL: STUNTGP_D3D 0x474e28
TrailParams g_474e28 = {0, 9, 2, 4};

// STUB: STUNTGP_D3D 0x41e510
void FUN_41e510(Vec4 *ring, DWORD *head, DWORD *count, Vec4 *pos, TrailParams *params)
{
}

// FUNCTION: STUNTGP_D3D 0x414c60
void FUN_414c60()
{
    if (g_61297c < 20)
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
    pos.z = g_4d5bb8->unk26b0->parts[0]->meshes[23].matrix->z;
    FUN_41e510(g_4d5bb8->unk351c, &g_4d5bb8->unk391c, &g_4d5bb8->unk3920, &pos, &g_474c08);
}

// FUNCTION: STUNTGP_D3D 0x414f90
void FUN_414f90()
{
    if (g_61297c >= 60 && g_4d5bb8->unk28a0)
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
    if (g_61297c >= 60 && g_4d5bb8->unk28a0)
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

// STUB: STUNTGP_D3D 0x41d760
void FUN_41d760()
{
}

// FUNCTION: STUNTGP_D3D 0x407000
void FUN_407000()
{
    g_4d5bb8->unk2674 = 0;
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

// STUB: STUNTGP_D3D 0x41d3f0
void FUN_41d3f0(int time, char *out)
{
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

// STUB: STUNTGP_D3D 0x41da70
void FUN_41da70()
{
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

// STUB: STUNTGP_D3D 0x41ded0
void FUN_41ded0(float *pos, CameraPath *path, int *index)
{
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
    car->unk2d04[0].count = 0;
    car->unk2d04[1].count = 0;
}

// FUNCTION: STUNTGP_D3D 0x4152c0
void FUN_4152c0(Car *car)
{
    car->unk28bc[0].trail.count = 0;
    car->unk28bc[1].trail.count = 0;
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
        if (!g_60f02c[i].model)
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
            car->unk2d04[0].pos = *car->unk26b0->parts[0]->meshes[23].matrix;
            car->unk2d04[1].pos = *car->unk26b0->parts[0]->meshes[24].matrix;
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
        if (car->active == 1 && car->unk26b0->meshCount >= 21)
        {
            ModelMesh *mesh = &car->unk26b0->parts[0]->meshes[21];
            car->unk28bc[0].active = 1;
            car->unk28bc[0].trail.pos = *mesh->matrix;
            if (car->unk26b0->meshCount >= 22)
            {
                mesh = &car->unk26b0->parts[0]->meshes[22];
                car->unk28bc[1].active = 1;
                car->unk28bc[1].trail.pos = *mesh->matrix;
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
