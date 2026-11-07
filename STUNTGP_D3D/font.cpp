#include "font.h"

// GLOBAL: STUNTGP_D3D 0x577bd0
Font g_fonts[2];

// GLOBAL: STUNTGP_D3D 0x57b310
Font *g_currentFont = NULL;

// GLOBAL: STUNTGP_D3D 0x57b314
DWORD g_fontCount = 0;

// GLOBAL: STUNTGP_D3D 0x57b418
float g_57b418 = 0.0f;

// FUNCTION: STUNTGP_D3D 0x428f70
void Font_Select(DWORD font)
{
    if (font >= g_fontCount)
    {
        font = g_fontCount - 1;
    }
    g_currentFont = &g_fonts[font];
}

// FUNCTION: STUNTGP_D3D 0x4291a0
void FUN_4291a0(float value)
{
    g_57b418 = value;
}

// STUB: STUNTGP_D3D 0x4291f0
void FUN_4291f0(char *text, int align, float x, float y, float z, D3DCOLOR color, float size, DWORD flags)
{
}
