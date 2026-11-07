#include "vecmath.h"

#include <math.h>
#include <string.h>

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

// FUNCTION: STUNTGP_D3D 0x44f0e0
void Matrix_Set(float *m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
    m[0] = m00;
    m[1] = m01;
    m[2] = m02;
    m[3] = m03;
    m[4] = m10;
    m[5] = m11;
    m[6] = m12;
    m[7] = m13;
    m[8] = m20;
    m[9] = m21;
    m[10] = m22;
    m[11] = m23;
    m[12] = m30;
    m[13] = m31;
    m[14] = m32;
    m[15] = m33;
}

// FUNCTION: STUNTGP_D3D 0x44f870
void Matrix_RotationZ(float *m, float degrees)
{
    int i = (int)(degrees * (8192.0f / 360.0f)) & 0x1fff;
    float c = g_cosTable[i];
    float s = g_sinTable[i];
    Matrix_Set(m, c, s, 0.0f, 0.0f, -s, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

// FUNCTION: STUNTGP_D3D 0x44ee50
void Matrix_Transpose(float *out, float *m)
{
    out[0] = m[0];
    out[1] = m[4];
    out[2] = m[8];
    out[3] = m[12];
    out[4] = m[1];
    out[5] = m[5];
    out[6] = m[9];
    out[7] = m[13];
    out[8] = m[2];
    out[9] = m[6];
    out[10] = m[10];
    out[11] = m[14];
    out[12] = m[3];
    out[13] = m[7];
    out[14] = m[11];
    out[15] = m[15];
}

// FUNCTION: STUNTGP_D3D 0x44f050
void Matrix_FromRows(float *r0, float *r1, float *r2, float *m)
{
    m[0] = 0.0f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[4] = 0.0f;
    m[5] = 0.0f;
    m[6] = 0.0f;
    m[7] = 0.0f;
    m[8] = 0.0f;
    m[9] = 0.0f;
    m[10] = 0.0f;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    memcpy(m, r0, 16);
    m[4] = r1[0];
    m[5] = r1[1];
    m[6] = r1[2];
    m[7] = r1[3];
    m[8] = r2[0];
    m[9] = r2[1];
    m[10] = r2[2];
    m[11] = r2[3];
}
