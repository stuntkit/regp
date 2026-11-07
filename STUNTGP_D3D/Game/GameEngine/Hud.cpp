#include "GameUpdate.h"

#include "../../d3drender.h"

// STUB: STUNTGP_D3D 0x431f10
void FUN_431f10(DWORD color, float x0, float y0, float z0, float x1, float y1, float z1)
{
}

// Draws a line given in 640x480 screen units.
// FUNCTION: STUNTGP_D3D 0x447840
void FUN_447840(DWORD color, float x0, float y0, float z0, float x1, float y1, float z1)
{
    FUN_431f10(color, (x0 - 320.0f) * g_624990 + g_576b94, (y0 - 240.0f) * g_624994 + g_576b98, z0,
               (x1 - 320.0f) * g_624990 + g_576b94, (y1 - 240.0f) * g_624994 + g_576b98, z1);
}

// White frame with a grey inner frame one pixel inside it.
// FUNCTION: STUNTGP_D3D 0x447280
void FUN_447280(float x, float y, float width, float height)
{
    float right = x + width;
    float bottom = y + height + 1.0f;
    float left = x - 1.0f;
    FUN_447840(0xffffffff, left, y, 0.99f, right + 1.0f, y, 0.99f);
    FUN_447840(0xffffffff, right, y, 0.99f, right, bottom, 0.99f);
    FUN_447840(0xffffffff, right, bottom, 0.99f, x, bottom, 0.99f);
    FUN_447840(0xffffffff, x, bottom, 0.99f, x, y, 0.99f);
    float top = y - 1.0f;
    right = right - 1.0f + 1.0f;
    bottom = bottom - 1.0f + 1.0f;
    float innerRight = right - 1.0f;
    FUN_447840(0xffc0c0c0, left, top, 0.99f, innerRight, top, 0.99f);
    float innerBottom = bottom - 1.0f;
    FUN_447840(0xffc0c0c0, right, top, 0.99f, right, innerBottom, 0.99f);
    FUN_447840(0xffc0c0c0, innerRight, bottom, 0.99f, left, bottom, 0.99f);
    FUN_447840(0xffc0c0c0, left, innerBottom, 0.99f, left, top, 0.99f);
}
