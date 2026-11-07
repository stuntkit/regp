#include "GameUpdate.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../../gametext.h"
#include "../../vecmath.h"
#include "camera_path.h"

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

// STUB: STUNTGP_D3D 0x413430
void FUN_413430(int wheel)
{
}

// STUB: STUNTGP_D3D 0x414ac0
void FUN_414ac0(unsigned int wheel)
{
}

// STUB: STUNTGP_D3D 0x415630
void FUN_415630()
{
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

// STUB: STUNTGP_D3D 0x414940
void FUN_414940()
{
}

// STUB: STUNTGP_D3D 0x4149e0
void FUN_4149e0()
{
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

// STUB: STUNTGP_D3D 0x4143e0
void FUN_4143e0(float amount)
{
}

// STUB: STUNTGP_D3D 0x414420
void FUN_414420(float amount)
{
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
            sprintf(text, "%s %s\n", g_60f050[g_4d5bb8 - g_49a1f8].name, g_6127a0[22]);
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

extern int g_60f02c[0x96];

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
    switch (g_60f02c[(g_4d5bb8 - g_49a1f8) * 25 + 2])
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
    Matrix_Identity(g_474630->unk1bcc);
    Matrix_Identity(g_474630->unk1c0c);
    Matrix_Identity(g_474630->unk1c4c);
    g_474630->unk1c8c[0] = 0.0f;
    g_474630->unk1c8c[1] = 0.0f;
    g_474630->unk1c8c[2] = 0.0f;
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
