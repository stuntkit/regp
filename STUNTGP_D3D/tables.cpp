#include "tables.h"

#include <math.h>

// GLOBAL: STUNTGP_D3D 0x4754c4
float g_4754c4 = 1.0f;

// GLOBAL: STUNTGP_D3D 0x4754c8
float g_4754c8 = 1.0f;

// GLOBAL: STUNTGP_D3D 0x62457c
int g_62457c[256];

// GLOBAL: STUNTGP_D3D 0x5715d4
float g_5715d4[128];

// GLOBAL: STUNTGP_D3D 0x5717d4
float g_5717d4[128];

// FUNCTION: STUNTGP_D3D 0x422380
void FUN_422380()
{
    double x = 1.0;
    float scale = 1.0 / pow(256.0, 2.0);
    for (int i = 0; i < 256; i++)
    {
        float value = pow(x, 2.0) * scale;
        value *= 65280.0f;
        if (value < 2048.0f)
        {
            value = 2048.0f;
        }
        else if (value > 65280.0f)
        {
            value = 65280.0f;
        }
        g_62457c[i] = value;
        x += 1.0;
    }
}

// FUNCTION: STUNTGP_D3D 0x422420
void FUN_422420()
{
    int i;
    double x = 1.0;
    FUN_422380();
    float scale = 1.0 / pow(128.0, g_4754c4);
    for (i = 0; i < 128; i++)
    {
        g_5717d4[i] = pow(x, g_4754c4) * scale;
        x += 1.0;
    }
    x = 1.0;
    scale = 1.0 / pow(128.0, g_4754c8);
    for (i = 0; i < 128; i++)
    {
        g_5715d4[i] = pow(x, g_4754c8) * scale;
        x += 1.0;
    }
}

// Applies the per-channel gamma table and then the overall brightness curve to a colour.
// FUNCTION: STUNTGP_D3D 0x4224e0
void FUN_4224e0(float *r, float *g, float *b)
{
    float vr = *r;
    float vg = *g;
    float vb = *b;
    unsigned int i = vr * 0.5f;
    if (i > 127)
    {
        i = 127;
    }
    vr = (g_5715d4[i] + g_5715d4[i] + 0.25f) * vr;
    i = vg * 0.5f;
    if (i > 127)
    {
        i = 127;
    }
    vg = (g_5715d4[i] + g_5715d4[i] + 0.25f) * vg;
    i = vb * 0.5f;
    if (i > 127)
    {
        i = 127;
    }
    vb = (g_5715d4[i] + g_5715d4[i] + 0.25f) * vb;
    if (vr > 255.0f)
    {
        vr = 255.0f;
    }
    if (vg > 255.0f)
    {
        vg = 255.0f;
    }
    if (vb > 255.0f)
    {
        vb = 255.0f;
    }
    int j = ((vg * 5.0f + vr * 3.0f + vb) * 0.11111111f) * 0.5f;
    *r = vr * g_5717d4[j];
    *g = vg * g_5717d4[j];
    *b = vb * g_5717d4[j];
}
