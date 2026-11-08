#include "game_state.h"

#include "camera_path.h"

#include <math.h>

#include "../../sintable.h"
#include "../../vecmath.h"

// FUNCTION: STUNTGP_D3D 0x402580
void FUN_402580()
{
    g_4722d0 = g_498248;
}

// GLOBAL: STUNTGP_D3D 0x624474
CameraPath *g_624474;

// GLOBAL: STUNTGP_D3D 0x624498
DWORD g_624498;

// FUNCTION: STUNTGP_D3D 0x428800
CameraPath *FUN_428800(int id)
{
    for (DWORD i = 0; i < g_624498; i++)
    {
        if (g_624474[i].id == id)
        {
            return &g_624474[i];
        }
    }
    return NULL;
}

// Length of the path, summed over its knots.
// FUNCTION: STUNTGP_D3D 0x428840
float FUN_428840(CameraPath *path)
{
    Vec4 *points = path->points;
    float len = 0.0f;
    Vec4 prev = points[0];
    for (DWORD i = 0; i < path->count; i++)
    {
        Vec4 cur = points[i];
        float dx = cur.x - prev.x;
        float dy = cur.y - prev.y;
        float dz = cur.z - prev.z;
        len += (float)sqrt(dx * dx + dy * dy + dz * dz);
        prev = cur;
    }
    return len;
}

// Point on the closed path at the given distance along it, linear between knots.
// FUNCTION: STUNTGP_D3D 0x4288d0
void FUN_4288d0(CameraPath *path, Vec4 *out, float dist)
{
    DWORD count = path->count;
    dist = (float)count * dist / path->unk18;
    int i = (int)dist;
    DWORD a;
    if (i < 0)
    {
        a = count - (DWORD)-i % count;
    }
    else
    {
        a = (DWORD)i % count;
    }
    DWORD b = (a + 1) % count;
    *out = path->points[a];
    Vec4 d;
    d.x = path->points[b].x - out->x;
    d.y = path->points[b].y - out->y;
    d.z = path->points[b].z - out->z;
    double f = fmod(dist, 1.0);
    d.x *= f;
    d.y *= f;
    d.z *= f;
    out->x += d.x;
    out->y += d.y;
    out->z += d.z;
}

// FUN_4288d0 that also reports the knot it started from.
// FUNCTION: STUNTGP_D3D 0x4289a0
void FUN_4289a0(CameraPath *path, Vec4 *out, float dist, DWORD *knot)
{
    DWORD count = path->count;
    dist = (float)count * dist / path->unk18;
    int i = (int)dist;
    DWORD a;
    if (i < 0)
    {
        a = count - (DWORD)-i % count;
    }
    else
    {
        a = (DWORD)i % count;
    }
    DWORD b = (a + 1) % count;
    *out = path->points[a];
    Vec4 d;
    d.x = path->points[b].x - out->x;
    d.y = path->points[b].y - out->y;
    d.z = path->points[b].z - out->z;
    double f = fmod(dist, 1.0);
    d.x *= f;
    *knot = a;
    d.y *= f;
    d.z *= f;
    out->x += d.x;
    out->y += d.y;
    out->z += d.z;
}

// FUNCTION: STUNTGP_D3D 0x402ad0
void FUN_402ad0()
{
    Vec4 dir;
    DWORD roll;

    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = -1.0f;
    FUN_44eb70(g_4722d0->angX >> 12, g_4722d0->angY >> 12, 0, &dir.x, &dir.y, &dir.z);
    g_4722d0->cam.target = g_4722d0->cam.pos;
    g_4722d0->cam.target.x = dir.x + g_4722d0->cam.pos.x;
    g_4722d0->cam.target.y = dir.y + g_4722d0->cam.pos.y;
    g_4722d0->cam.target.z = dir.z + g_4722d0->cam.pos.z;
    roll = (g_4722d0->angZ >> 12) & 0x1fff;
    g_4722d0->cam.up.x = g_sinTable[roll];
    g_4722d0->cam.up.y = g_cosTable[roll];
    g_4722d0->cam.up.z = 0.0f;
}

void FUN_428520(CameraPath *path, Vec4 *out, float t);
void FUN_428740(float *t, float *speed);
extern float g_499f8c;
extern float g_499f88;

// FUNCTION: STUNTGP_D3D 0x402b90
void FUN_402b90()
{
    Vec4 p;
    CameraPath *path = g_4722d0->path;
    float lead = path->unk14;
    FUN_428520(path, &p, path->count * g_499f8c);
    g_4722d0->cam.pos = p;
    g_4722d0->cam.pos.y += 500.0f;
    FUN_428520(path, &p, path->count * (lead * 0.001f + g_499f8c));
    g_4722d0->cam.target = p;
    g_4722d0->cam.target.y += 500.0f;
    FUN_428740(&g_499f8c, &g_499f88);
    g_4722d0->camMode = 3;
}

// FUNCTION: STUNTGP_D3D 0x402c80
void FUN_402c80()
{
    Vec4 v;
    Vec4 *m = g_4722d0->cam.matrix;

    v.x = -g_4722d0->fov;
    v.y = 0.0f;
    v.z = -g_4722d0->unk0bc;
    Vec3_Normalize(&v.x);
    g_4722d0->planeLeft.x = v.x * m[0].x + v.y * m[1].x + v.z * m[2].x;
    g_4722d0->planeLeft.y = v.x * m[0].y + v.y * m[1].y + v.z * m[2].y;
    g_4722d0->planeLeft.z = v.x * m[0].z + v.y * m[1].z + v.z * m[2].z;

    v.x = g_4722d0->fov;
    v.y = 0.0f;
    v.z = -g_4722d0->unk0bc;
    Vec3_Normalize(&v.x);
    g_4722d0->planeRight.x = v.x * m[0].x + v.y * m[1].x + v.z * m[2].x;
    g_4722d0->planeRight.y = v.x * m[0].y + v.y * m[1].y + v.z * m[2].y;
    g_4722d0->planeRight.z = v.x * m[0].z + v.y * m[1].z + v.z * m[2].z;

    v.x = 0.0f;
    v.y = g_4722d0->fov;
    v.z = -g_4722d0->unk0c0;
    Vec3_Normalize(&v.x);
    g_4722d0->planeTop.x = v.x * m[0].x + v.y * m[1].x + v.z * m[2].x;
    g_4722d0->planeTop.y = v.x * m[0].y + v.y * m[1].y + v.z * m[2].y;
    g_4722d0->planeTop.z = v.x * m[0].z + v.y * m[1].z + v.z * m[2].z;

    v.x = 0.0f;
    v.y = -g_4722d0->fov;
    v.z = -g_4722d0->unk0c0;
    Vec3_Normalize(&v.x);
    g_4722d0->planeBottom.x = v.x * m[0].x + v.y * m[1].x + v.z * m[2].x;
    g_4722d0->planeBottom.y = v.x * m[0].y + v.y * m[1].y + v.z * m[2].y;
    g_4722d0->planeBottom.z = v.x * m[0].z + v.y * m[1].z + v.z * m[2].z;
}

// FUNCTION: STUNTGP_D3D 0x402e90
void FUN_402e90()
{
    FUN_44f4c0();
    switch (g_4722d0->camMode)
    {
    case 1:
        FUN_402ad0();
        break;
    case 2:
        FUN_402ad0();
        break;
    case 3:
        if (!FUN_428800(1))
        {
            FUN_4028d0(1);
        }
        else
        {
            FUN_402b90();
        }
        break;
    }
    FUN_450190(&g_4722d0->cam);
    g_4722d0->axisX = g_4722d0->cam.matrix[0];
    g_4722d0->axisY = g_4722d0->cam.matrix[1];
    g_4722d0->axisZ = g_4722d0->cam.matrix[2];
    FUN_402c80();
}
