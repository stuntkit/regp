#include "GameUpdate.h"

#include <math.h>

#include "../../vecmath.h"

void FUN_402ab0(float fov);
void FUN_403310(float fov);
void FUN_403770(Car *car);
void FUN_428520(CameraPath *path, Vec4 *out, float t);
void FUN_4028f0(CameraPreset *preset, int mode);

extern CameraPreset g_4722d8[32];

extern BYTE g_62d480[256];
extern float g_482688;
extern float g_48268c;
extern float g_482690;
extern float g_60f010;
extern unsigned int g_612d10;
extern Car *g_612d14[6];

// GLOBAL: STUNTGP_D3D 0x499f8c
float g_499f8c;

// Swept-sphere collision state used to keep the camera out of the scenery.
// GLOBAL: STUNTGP_D3D 0x4980c0
float g_4980c0;

// GLOBAL: STUNTGP_D3D 0x4980c4
Vec4 g_4980c4;

// GLOBAL: STUNTGP_D3D 0x4980d4
Vec4 g_4980d4;

// GLOBAL: STUNTGP_D3D 0x4980e8
Vec4 g_4980e8;

// GLOBAL: STUNTGP_D3D 0x49814c
float g_49814c;

// GLOBAL: STUNTGP_D3D 0x498150
float g_498150;

// GLOBAL: STUNTGP_D3D 0x498154
float g_498154;

// GLOBAL: STUNTGP_D3D 0x498158
float g_498158;

// GLOBAL: STUNTGP_D3D 0x498198
Vec4 g_498198;

// FUNCTION: STUNTGP_D3D 0x403180
void FUN_403180(float delta)
{
    Car *car = g_4722d0->data;
    car->unk22fc += delta;
    if (car->unk22fc > 10000.0f)
    {
        car->unk22fc = 10000.0f;
    }
    else if (car->unk22fc < 500.0f)
    {
        car->unk22fc = 500.0f;
    }
}

// STUB: STUNTGP_D3D 0x4215b0
int FUN_4215b0()
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x421c30
void FUN_421c30(float bounce)
{
    Vec4 push;
    float d = (g_4980e8.x * g_498198.x + g_4980e8.y * g_498198.y + g_4980e8.z * g_498198.z) * (2.0f - (1.0f - bounce));
    push.x = g_498198.x * d;
    push.y = g_498198.y * d;
    push.z = g_498198.z * d;
    g_4980e8.x -= push.x;
    g_4980e8.y -= push.y;
    g_4980e8.z -= push.z;
}

// FUNCTION: STUNTGP_D3D 0x4031e0
void FUN_4031e0(float delta)
{
    Car *car = g_4722d0->data;
    car->unk22f0 += delta;
    if (car->unk22f0 < 0.0f)
    {
        car->unk22f0 += 360.0f;
    }
    else if (car->unk22f0 >= 360.0f)
    {
        car->unk22f0 -= 360.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x403240
void FUN_403240(float delta)
{
    Car *car = g_4722d0->data;
    car->unk22ec += delta;
    if (car->unk22ec < 0.0f)
    {
        car->unk22ec += 360.0f;
    }
    else if (car->unk22ec > 360.0f)
    {
        car->unk22ec -= 360.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x4032a0
void FUN_4032a0()
{
    Vec4 offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = g_4722d0->data->unk22fc;
    FUN_44ec00(&g_4722d0->data->unk22ec, &offset.x);
    g_4722d0->data->camOffset = offset;
}

// FUNCTION: STUNTGP_D3D 0x403340
void FUN_403340()
{
    g_4722d0->cam.pos.x -= g_4722d0->data->unk2318[0];
    g_4722d0->cam.pos.y -= g_4722d0->data->unk2318[1];
    g_4722d0->cam.pos.z -= g_4722d0->data->unk2318[2];
    g_4722d0->cam.target.x -= g_4722d0->data->unk2318[0];
    g_4722d0->cam.target.y -= g_4722d0->data->unk2318[1];
    g_4722d0->cam.target.z -= g_4722d0->data->unk2318[2];
    g_4722d0->cam.pos.x = g_4722d0->data->unk2308[0] + g_4722d0->cam.pos.x;
    g_4722d0->cam.pos.y = g_4722d0->data->unk2308[1] + g_4722d0->cam.pos.y;
    g_4722d0->cam.pos.z = g_4722d0->data->unk2308[2] + g_4722d0->cam.pos.z;
    g_4722d0->cam.target.x = g_4722d0->data->unk2308[0] + g_4722d0->cam.target.x;
    g_4722d0->cam.target.y = g_4722d0->data->unk2308[1] + g_4722d0->cam.target.y;
    g_4722d0->cam.target.z = g_4722d0->data->unk2308[2] + g_4722d0->cam.target.z;
}

// FUNCTION: STUNTGP_D3D 0x403420
void FUN_403420()
{
    g_4722d0->roll = (g_4722d0->roll - (g_4722d0->velX * g_4722d0->axisX.x + g_4722d0->velY * g_4722d0->axisX.y +
                                        g_4722d0->velZ * g_4722d0->axisX.z) *
                                           0.25f) *
                     0.5f;
}

// FUNCTION: STUNTGP_D3D 0x403460
void FUN_403460()
{
    if (g_4722d0->camMode != 6)
    {
        Car *car = g_4722d0->data;
        float dx = g_4722d0->cam.pos.x - car->posX;
        float dy = g_4722d0->cam.pos.y - car->posY;
        float dz = g_4722d0->cam.pos.z - car->posZ;
        if (dx * dx + dy * dy + dz * dz > 6250000.0f)
        {
            g_4722d0->unk1a4 = 600;
        }
        if (g_4722d0->unk1a4)
        {
            g_4722d0->cam.pos.x = g_4722d0->velX + g_4722d0->cam.pos.x;
            g_4722d0->cam.pos.y = g_4722d0->velY + g_4722d0->cam.pos.y;
            g_4722d0->cam.pos.z = g_4722d0->velZ + g_4722d0->cam.pos.z;
            g_4722d0->unk1a4--;
            return;
        }
        g_4980c4 = g_4722d0->cam.pos;
        g_4980c0 = 1.0f;
        g_498154 = 125.0f;
        g_498158 = 15625.0f;
        g_498150 = 1.0f;
        g_4980e8 = *(Vec4 *)&g_4722d0->velX;
        g_49814c = (float)sqrt(g_4980e8.x * g_4980e8.x + g_4980e8.y * g_4980e8.y + g_4980e8.z * g_4980e8.z);
        unsigned int i = 0;
        int hit;
        do
        {
            hit = FUN_4215b0();
            if (hit == 1)
            {
                FUN_421c30(0.01f);
            }
        } while (hit == 1 && i++ < 32);
        g_4722d0->cam.pos = g_4980d4;
    }
}

// FUNCTION: STUNTGP_D3D 0x403650
void FUN_403650(int step)
{
    if ((float)g_4722d0->unk1bc < 30.0f)
    {
        g_4722d0->unk1bc += step;
    }
}

// FUNCTION: STUNTGP_D3D 0x403bc0
void FUN_403bc0()
{
    if (g_4722d0->camMode < 10)
    {
        g_4722d0->unk1c0 = 0.0f;
        float speed = (float)sqrt(g_4722d0->data->unk1c8c.x * g_4722d0->data->unk1c8c.x +
                                  g_4722d0->data->unk1c8c.y * g_4722d0->data->unk1c8c.y +
                                  g_4722d0->data->unk1c8c.z * g_4722d0->data->unk1c8c.z) -
                      83.333336f;
        if (speed < 0.0f)
        {
            speed = 0.0f;
        }
        else
        {
            speed *= 0.023999998f;
            if (speed > 1.0f)
            {
                speed = 1.0f;
            }
            g_4722d0->unk1c0 = speed * 75.0f;
            speed *= 0.5f;
        }
        FUN_403310(2.09f - speed);
    }
}

// FUNCTION: STUNTGP_D3D 0x403e80
void FUN_403e80()
{
    float fov;
    FUN_4031e0(0.5f);
    if ((float)fabs(g_4722d0->fov - 1.25f) > 0.02f)
    {
        fov = g_4722d0->fov;
        if (fov > 1.25f)
        {
            fov -= 0.01f;
        }
        else
        {
            fov += 0.01f;
        }
        FUN_402ab0(fov);
    }
    Car *car = g_4722d0->data;
    if (car->unk22ec > 6.0f)
    {
        car->unk22ec -= 0.1f;
    }
    if (car->unk22fc > 500.0f)
    {
        car->unk22fc -= 5.0f;
    }
}

extern int g_60f020;
extern int g_576be0;

void FUN_40d200(Car *car);
void FUN_40d280(Car *car);
void FUN_40d300(Car *car);
void FUN_40d380(Car *car);

// FUNCTION: STUNTGP_D3D 0x404310
void FUN_404310(Car *car)
{
    int mode = g_60f020;
    if (g_576be0)
    {
        mode = 1;
    }
    switch (mode)
    {
    case 1:
        FUN_40d280(car);
        break;
    case 2:
        FUN_40d200(car);
        break;
    case 3:
        FUN_40d300(car);
        break;
    case 4:
        FUN_40d380(car);
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x404360
void FUN_404360()
{
    Car *car = g_4d5bb8;
    if (car->unk2304)
    {
        int index = car->unk24ac + 1;
        Car *next = index < (int)g_612d10 ? g_612d14[index] : car;
        float gap = (car->unk23b0 - next->unk23b0) * g_60f010 * 0.01f;
        if (gap > 0.0f && gap < 5000.0f && next->unk1cf0 + 8.333333f > car->unk1cf0 && car->unk1cf0 > 0.41666666f)
        {
            car->unk22fc += 10.0f;
        }
        else
        {
            car->unk22fc -= 5.0f;
        }
        if (car->unk22fc < 600.0f)
        {
            car->unk22fc = 600.0f;
        }
        else if (car->unk22fc > 2500.0f)
        {
            car->unk22fc = 2500.0f;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x404450
void FUN_404450()
{
    Vec4 right;
    Vec4 fwd;
    Vec4 side;
    Vec4 off;
    Vec4 tmp;
    Vec4 v;
    float dot;
    float h;
    float k;
    Car *car;

    g_4722d0->prevTarget = g_4722d0->cam.target;
    switch (g_4722d0->camMode)
    {
    case 4:
        FUN_403770(g_4722d0->data);
        FUN_403460();
        FUN_403340();
        return;
    case 5:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        FUN_404360();
        FUN_403420();
        if (g_4722d0->camMode == 16)
        {
            FUN_403e80();
        }
        FUN_403bc0();
        FUN_4032a0();

        tmp.x = g_4722d0->data->unk22dc + g_4722d0->data->posX;
        tmp.y = g_4722d0->data->unk22e0 + g_4722d0->data->posY;
        tmp.z = g_4722d0->data->unk22e4 + g_4722d0->data->posZ;
        v.x = tmp.x - g_4722d0->cam.target.x;
        v.y = tmp.y - g_4722d0->cam.target.y;
        v.z = tmp.z - g_4722d0->cam.target.z;
        v.x *= 0.33333334f;
        v.y *= 0.33333334f;
        v.z *= 0.33333334f;
        g_4722d0->cam.target.x += v.x;
        g_4722d0->cam.target.y += v.y;
        g_4722d0->cam.target.z += v.z;

        v = g_4722d0->data->axisY;
        tmp.x = g_4722d0->unk1ac.x - v.x;
        tmp.y = g_4722d0->unk1ac.y - v.y;
        tmp.z = g_4722d0->unk1ac.z - v.z;
        tmp.x *= 0.1f;
        tmp.y *= 0.1f;
        tmp.z *= 0.1f;
        g_4722d0->unk1ac.x -= tmp.x;
        g_4722d0->unk1ac.y -= tmp.y;
        g_4722d0->unk1ac.z -= tmp.z;
        v = g_4722d0->unk1ac;

        dot = v.x * g_4722d0->data->axisZ.x + v.y * g_4722d0->data->axisZ.y + v.z * g_4722d0->data->axisZ.z;
        tmp.x = dot * v.x;
        tmp.y = dot * v.y;
        tmp.z = dot * v.z;
        fwd.x = g_4722d0->data->axisZ.x - tmp.x;
        fwd.y = g_4722d0->data->axisZ.y - tmp.y;
        fwd.z = g_4722d0->data->axisZ.z - tmp.z;
        Vec3_Normalize(&fwd.x);
        right.x = fwd.y * v.z - fwd.z * v.y;
        right.y = fwd.z * v.x - fwd.x * v.z;
        right.z = fwd.x * v.y - fwd.y * v.x;
        Vec3_Normalize(&right.x);

        tmp.x = right.x * g_4722d0->data->camOffset.x;
        tmp.y = right.y * g_4722d0->data->camOffset.x;
        tmp.z = right.z * g_4722d0->data->camOffset.x;
        off.x = g_4722d0->data->camOffset.y * v.x;
        off.y = g_4722d0->data->camOffset.y * v.y;
        off.z = g_4722d0->data->camOffset.y * v.z;
        side.x = g_4722d0->data->camOffset.z * fwd.x;
        side.y = g_4722d0->data->camOffset.z * fwd.y;
        side.z = g_4722d0->data->camOffset.z * fwd.z;
        dot = g_482688 * v.x + g_48268c * v.y + g_482690 * v.z;
        if (dot >= 0.0f)
        {
            off.x = -off.x;
            off.y = -off.y;
            off.z = -off.z;
        }
        off.x += tmp.x;
        off.y += tmp.y;
        off.z += tmp.z;
        off.x = side.x + off.x;
        off.y = side.y + off.y;
        off.z = side.z + off.z;
        tmp.x = off.x + g_4722d0->data->posX;
        tmp.y = off.y + g_4722d0->data->posY;
        tmp.z = off.z + g_4722d0->data->posZ;
        v = tmp;

        tmp.x -= g_4722d0->data->posX;
        tmp.y -= g_4722d0->data->posY;
        tmp.z -= g_4722d0->data->posZ;
        h = g_482688 * tmp.x + g_48268c * tmp.y + g_482690 * tmp.z;
        if (h < 100.0f)
        {
            h = -(h - 100.0f);
            tmp.x = h * g_482688;
            tmp.y = h * g_48268c;
            tmp.z = h * g_482690;
            v.x += tmp.x;
            v.y += tmp.y;
            v.z += tmp.z;
        }
        if (dot >= 0.0f)
        {
            tmp.x = g_482688 + g_482688;
            tmp.y = g_48268c + g_48268c;
            tmp.z = g_482690 + g_482690;
            g_4722d0->accelX -= tmp.x;
            g_4722d0->accelY -= tmp.y;
            g_4722d0->accelZ -= tmp.z;
        }
        k = g_4722d0->data->unk244 - 115.0f;
        if (k < 0.0f)
        {
            k = 0.0f;
        }
        side.x = k * g_4722d0->data->axisY.x;
        side.y = k * g_4722d0->data->axisY.y;
        side.z = k * g_4722d0->data->axisY.z;
        v.x -= side.x;
        v.y -= side.y;
        v.z -= side.z;
        v.y = v.y - g_4722d0->unk1c4 + g_4722d0->unk1c0;

        tmp.x = g_4722d0->cam.pos.x - g_4722d0->data->posX;
        tmp.y = g_4722d0->cam.pos.y - g_4722d0->data->posY;
        tmp.z = g_4722d0->cam.pos.z - g_4722d0->data->posZ;
        if (tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z < 9000000.0f)
        {
            car = g_4722d0->data;
            if (car->unk71ec == 0 && (float)fabs(car->posY - car->unk7238) > 50.0f)
            {
                g_4722d0->accelX *= 0.9f;
                g_4722d0->accelY *= 0.9f;
                g_4722d0->accelZ *= 0.9f;
                tmp.x = g_482688 + g_482688;
                tmp.y = g_48268c + g_48268c;
                tmp.z = g_482690 + g_482690;
                g_4722d0->accelX -= tmp.x;
                g_4722d0->accelY -= tmp.y;
                g_4722d0->accelZ -= tmp.z;
                FUN_403650(2);
                FUN_403460();
                FUN_403340();
                return;
            }
            if (car->unk1fd8 == 2)
            {
                FUN_403650(1);
                if (g_4722d0->data->unk71ec < 4)
                {
                    g_4722d0->accelX *= 0.9f;
                    g_4722d0->accelY *= 0.9f;
                    g_4722d0->accelZ *= 0.9f;
                    FUN_403460();
                    FUN_403340();
                    return;
                }
            }
            else if (car->unk1fd8 == 1)
            {
                FUN_403650(1);
                if (g_4722d0->data->unk71ec >= 2)
                {
                    g_4722d0->accelX *= 0.9f;
                    g_4722d0->accelY *= 0.9f;
                    g_4722d0->accelZ *= 0.9f;
                    FUN_403460();
                    FUN_403340();
                    return;
                }
            }
        }
        g_4722d0->accelX = 0.0f;
        g_4722d0->accelY = 0.0f;
        g_4722d0->accelZ = 0.0f;
        tmp.x = v.x - g_4722d0->cam.pos.x;
        tmp.y = v.y - g_4722d0->cam.pos.y;
        tmp.z = v.z - g_4722d0->cam.pos.z;
        g_4722d0->accelX = 0.0f;
        g_4722d0->accelY = 0.0f;
        g_4722d0->accelZ = 0.0f;
        tmp.x = v.x - g_4722d0->data->posX;
        tmp.y = v.y - g_4722d0->data->posY;
        tmp.z = v.z - g_4722d0->data->posZ;
        Vec3_Normalize(&tmp.x);
        tmp.x *= -g_4722d0->data->unk22fc;
        tmp.y *= -g_4722d0->data->unk22fc;
        tmp.z *= -g_4722d0->data->unk22fc;
        tmp.x += g_4722d0->data->posX;
        tmp.y += g_4722d0->data->posY;
        tmp.z += g_4722d0->data->posZ;
        tmp.x -= g_4722d0->cam.pos.x;
        tmp.y -= g_4722d0->cam.pos.y;
        tmp.z -= g_4722d0->cam.pos.z;
        dot = (float)sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z) * g_4722d0->data->unk2300;
        k = 256.0f;
        if (g_4722d0->unk1bc)
        {
            k = (30.0f - (float)g_4722d0->unk1bc--) * 8.533334f;
        }
        if (dot > k)
        {
            dot = k;
        }
        Vec3_Normalize(&tmp.x);
        g_4722d0->velX = dot * tmp.x;
        g_4722d0->velY = dot * tmp.y;
        g_4722d0->velZ = dot * tmp.z;
        g_4722d0->accelX = 0.0f;
        g_4722d0->accelY = 0.0f;
        g_4722d0->accelZ = 0.0f;
        FUN_403460();
        FUN_403340();
        return;
    case 6:
        car = g_4722d0->data;
        car->camOffset.x = 0.0f;
        car->camOffset.y = 100.0f;
        car->camOffset.z = 0.0f;
        tmp.x = g_4722d0->data->camOffset.x * g_4722d0->data->axisX.x;
        tmp.y = g_4722d0->data->camOffset.x * g_4722d0->data->axisX.y;
        tmp.z = g_4722d0->data->camOffset.x * g_4722d0->data->axisX.z;
        off.x = g_4722d0->data->camOffset.y * g_4722d0->data->axisY.x;
        off.y = g_4722d0->data->camOffset.y * g_4722d0->data->axisY.y;
        off.z = g_4722d0->data->camOffset.y * g_4722d0->data->axisY.z;
        side.x = g_4722d0->data->camOffset.z * g_4722d0->data->axisZ.x;
        side.y = g_4722d0->data->camOffset.z * g_4722d0->data->axisZ.y;
        side.z = g_4722d0->data->camOffset.z * g_4722d0->data->axisZ.z;
        tmp.x = off.x + tmp.x;
        tmp.y = off.y + tmp.y;
        tmp.z = off.z + tmp.z;
        tmp.x = side.x + tmp.x;
        tmp.y = side.y + tmp.y;
        tmp.z = side.z + tmp.z;
        g_4722d0->cam.pos.x = tmp.x + g_4722d0->data->posX;
        g_4722d0->cam.pos.y = tmp.y + g_4722d0->data->posY;
        g_4722d0->cam.pos.z = tmp.z + g_4722d0->data->posZ;

        tmp = g_4722d0->data->unk26b0->lods[0]->matrix[3];
        tmp.x = -tmp.x;
        g_4722d0->cam.up.x = tmp.x * g_4722d0->data->matrix[0] + tmp.y * g_4722d0->data->matrix[4] +
                             tmp.z * g_4722d0->data->matrix[8];
        g_4722d0->cam.up.y = tmp.x * g_4722d0->data->matrix[1] + tmp.y * g_4722d0->data->matrix[5] +
                             tmp.z * g_4722d0->data->matrix[9];
        g_4722d0->cam.up.z = tmp.x * g_4722d0->data->matrix[2] + tmp.y * g_4722d0->data->matrix[6] +
                             tmp.z * g_4722d0->data->matrix[10];
        tmp = g_4722d0->data->unk26b0->lods[0]->matrix[2];
        tmp.y = -tmp.y;
        off.x = tmp.x * g_4722d0->data->matrix[0] + tmp.y * g_4722d0->data->matrix[4] + tmp.z * g_4722d0->data->matrix[8];
        off.y = tmp.x * g_4722d0->data->matrix[1] + tmp.y * g_4722d0->data->matrix[5] + tmp.z * g_4722d0->data->matrix[9];
        off.z =
            tmp.x * g_4722d0->data->matrix[2] + tmp.y * g_4722d0->data->matrix[6] + tmp.z * g_4722d0->data->matrix[10];
        off.x *= 256.0f;
        off.y *= 256.0f;
        off.z *= 256.0f;
        g_4722d0->cam.target.x = off.x + g_4722d0->cam.pos.x;
        g_4722d0->cam.target.y = off.y + g_4722d0->cam.pos.y;
        g_4722d0->cam.target.z = off.z + g_4722d0->cam.pos.z;
        g_4722d0->roll = 0.0f;
        FUN_403460();
        FUN_403340();
        return;
    case 7:
    {
        FUN_403770(g_4722d0->data);
        GameSlot *slot = g_4722d0;
        car = slot->data;
        float diff = car->unk23b0 - g_499f8c;
        if (car->unk23b0 < g_499f8c)
        {
            diff -= -2.0f;
        }
        else
        {
            diff -= 2.0f;
        }
        if ((float)fabs(diff) > 0.01f)
        {
            diff *= 0.02f;
            if ((float)fabs(diff) > 0.2f)
            {
                diff = diff < 0.0f ? -0.2f : 0.2f;
            }
            g_499f8c += diff;
        }
        float t = g_499f8c * 0.01f;
        float frac;
        if (t < 0.0f)
        {
            frac = 1.0f - (float)fmod(-t, 1.0);
        }
        else
        {
            frac = fmod(t, 1.0);
        }
        FUN_428520(slot->path, &tmp, slot->path->count * frac);
        g_4722d0->cam.pos = tmp;
        tmp = *(Vec4 *)&g_4722d0->data->posX;
        off = g_4722d0->cam.pos;
        tmp.y = 0.0f;
        float dx = off.x - tmp.x;
        float dz = off.z - tmp.z;
        float lift = (float)sqrt(dx * dx + dz * dz) * 0.1f;
        lift *= 0.1f;
        lift *= lift;
        if (lift < 1000.0f)
        {
            lift = 1000.0f;
        }
        else if (lift > 3000.0f)
        {
            lift = 3000.0f;
        }
        off.x = g_482688 * lift;
        off.y = g_48268c * lift;
        off.z = lift * g_482690;
        g_4722d0->cam.pos.x -= off.x;
        g_4722d0->cam.pos.y -= off.y;
        g_4722d0->cam.pos.z -= off.z;
        break;
    }
    }
    FUN_403460();
    FUN_403340();
}

// FUNCTION: STUNTGP_D3D 0x4051e0
void FUN_4051e0()
{
    g_4722d0->unk1d0 = 10;
    g_4722d0->unk1d4 = 1;
    g_4722d0->camMode = g_4722d0->unk1d0;
    FUN_4028f0(g_4722d8, 10);
}

// GLOBAL: STUNTGP_D3D 0x498128
Vec4 g_498128;

// GLOBAL: STUNTGP_D3D 0x4981c8
float g_4981c8;

// FUNCTION: STUNTGP_D3D 0x41ff30
int FUN_41ff30(Vec4 *p)
{
    Vec4 v;
    v.x = p->x - g_4980c4.x;
    v.y = p->y - g_4980c4.y;
    v.z = p->z - g_4980c4.z;
    float d = g_498128.z * v.z + g_498128.y * v.y + g_498128.x * v.x;
    if (d >= -0.01f && d < g_4981c8)
    {
        g_4981c8 = d;
        return 1;
    }
    return 0;
}

// Uniform cubic B-spline basis weights, written to m[0], m[4], m[8], m[12].
// FUNCTION: STUNTGP_D3D 0x4282a0
void FUN_4282a0(float *m, float t)
{
    float t2 = t * t;
    float t3 = t2 * t;
    m[12] = t3 * 0.16666667f;
    m[8] = (((3.0f - t * 3.0f) * t + 3.0f) * t + 1.0f) * 0.16666667f;
    m[4] = (t3 * 3.0f - t2 * 6.0f + 4.0f) * 0.16666667f;
    m[0] = (t2 * 3.0f - t3 - t * 3.0f + 1.0f) * 0.16666667f;
}

// FUNCTION: STUNTGP_D3D 0x428460
void FUN_428460(CameraPath *path, Vec4 *out, float t)
{
    Vec4 *points = path->points;
    unsigned int i = (int)floor(t);
    if (i >= path->count)
    {
        i = 0;
    }
    unsigned int j = i + 1;
    if (j >= path->count)
    {
        j = 0;
    }
    float f = fmod(t, 1.0);
    Vec4 d;
    d.x = points[j].x - points[i].x;
    d.y = points[j].y - points[i].y;
    d.z = points[j].z - points[i].z;
    d.x *= f;
    d.y *= f;
    d.z *= f;
    d.x += points[i].x;
    d.y += points[i].y;
    d.z += points[i].z;
    *out = d;
}

// FUNCTION: STUNTGP_D3D 0x428520
void FUN_428520(CameraPath *path, Vec4 *out, float t)
{
    if (path->unk0c == 1)
    {
        FUN_428460(path, out, t);
        return;
    }
    t += 3.0f;
    unsigned int idx = (int)floor(t);
    t = fmod(t, 1.0);
    Vec4 *points = path->points;
    Vec4 acc;
    acc.x = 0.0f;
    acc.y = 0.0f;
    acc.z = 0.0f;
    float basis[16];
    FUN_4282a0(basis, t);
    float *w = &basis[12];
    unsigned int count = path->count;
    for (int n = 0; n < 4; n++)
    {
        unsigned int k = idx;
        if (idx >= count)
        {
            if (path->mode == 2)
            {
                k = idx % count;
            }
            else
            {
                k = count - 1;
            }
        }
        acc.x += *w * points[k].x;
        acc.y += points[k].y * *w;
        acc.z += points[k].z * *w;
        if (idx > 0)
        {
            idx--;
        }
        w -= 4;
    }
    out->x = acc.x;
    out->y = acc.y;
    out->z = acc.z;
}

// FUNCTION: STUNTGP_D3D 0x4286e0
void FUN_4286e0(float *value, float step)
{
    float v = *value;
    if (g_62d480[0x4c] & 0x80)
    {
        v += step;
    }
    if ((g_62d480[0x4b] & 0x80) && v > 0.0f)
    {
        v -= step;
    }
    *value = fmod(v, 1.0);
}

// GLOBAL: STUNTGP_D3D 0x499f88
float g_499f88;

// Advances the path position *t by *speed, steered by the L and apostrophe keys.
// FUNCTION: STUNTGP_D3D 0x428740
void FUN_428740(float *t, float *speed)
{
    float s = *speed * 0.95f;
    *speed = s;
    if ((g_62d480[0x26] & 0x80) && s < 0.0015f)
    {
        *speed = s + 2.5e-5f;
    }
    if ((g_62d480[0x28] & 0x80) && *speed > -0.0015f)
    {
        *speed -= 2.5e-5f;
    }
    float v = *t + *speed;
    *t = v;
    if (v < 0.0f)
    {
        *t = v + 1.0;
    }
    else
    {
        *t = fmod(v, 1.0);
    }
    if ((float)fabs(*speed) < 1.5625e-6f)
    {
        *speed = 0.0f;
    }
}
