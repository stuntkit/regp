#include "vecmath.h"

#include <math.h>

// FUNCTION: STUNTGP_D3D 0x44ee00
void FUN_44ee00()
{
}

// FUNCTION: STUNTGP_D3D 0x44ee10
void Matrix_Identity(float *m)
{
    m[0] = 1.0f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[4] = 0.0f;
    m[5] = 1.0f;
    m[6] = 0.0f;
    m[7] = 0.0f;
    m[8] = 0.0f;
    m[9] = 0.0f;
    m[10] = 1.0f;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
}

// FUNCTION: STUNTGP_D3D 0x44ed40
void Vec3_Normalize(float *v)
{
    float len = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    if (len == 0.0f)
    {
        v[0] = v[1] = v[2] = 0.0f;
        return;
    }
    len = 1.0f / (float)sqrt(len);
    v[0] *= len;
    v[1] *= len;
    v[2] *= len;
}

// GLOBAL: STUNTGP_D3D 0x61c3e8
float g_61c3e8[16];

// GLOBAL: STUNTGP_D3D 0x61c468
float g_61c468[16];

// STUB: STUNTGP_D3D 0x44f4e0
void FUN_44f4e0(float *m)
{
}

// FUNCTION: STUNTGP_D3D 0x44f4c0
void FUN_44f4c0()
{
    Matrix_Identity(g_61c3e8);
    FUN_44f4e0(g_61c3e8);
    Matrix_Identity(g_61c468);
}

// STUB: STUNTGP_D3D 0x450190
void FUN_450190(Camera *cam)
{
}

// STUB: STUNTGP_D3D 0x44eb70
void FUN_44eb70(DWORD yaw, DWORD pitch, DWORD roll, float *x, float *y, float *z)
{
}
