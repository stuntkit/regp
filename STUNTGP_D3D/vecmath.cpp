#include "vecmath.h"

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
