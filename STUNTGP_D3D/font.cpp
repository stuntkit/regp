#include "font.h"
#include "d3drender.h"
#include "Game/GameEngine/io_wad.h"
#include "globals.h"

#include <stdlib.h>
#include <string.h>

// GLOBAL: STUNTGP_D3D 0x577bd0
Font g_fonts[2];

// GLOBAL: STUNTGP_D3D 0x57b310
Font *g_currentFont = NULL;

// GLOBAL: STUNTGP_D3D 0x57b314
DWORD g_fontCount = 0;

// GLOBAL: STUNTGP_D3D 0x57b318
BYTE g_57b318[256];

// GLOBAL: STUNTGP_D3D 0x57b418
float g_57b418 = 0.0f;

// STUB: STUNTGP_D3D 0x428c00
void FUN_428c00(Font *font, BYTE *data, BYTE *texture)
{
}

// FUNCTION: STUNTGP_D3D 0x428ee0
void Font_Load(char *name)
{
    char path[128];
    Font *font = g_currentFont;
    strcpy(path, name);
    BYTE *data = (BYTE *)malloc(size_of_file(path));
    FUN_4623c0(path, data, font->unk04);
    BYTE *texture = (BYTE *)malloc(0x30000);
    FUN_428c00(font, data, texture);
    FUN_432840(texture, font, 0);
    free(texture);
    free(data);
}

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

// FUNCTION: STUNTGP_D3D 0x4290d0
float FUN_4290d0(const char *text, float size)
{
    float width = 0.0f;
    DWORD i;
    for (i = 0; text[i] != '\0' && text[i] != '\n'; i++)
    {
        BYTE c = text[i];
        BYTE glyph = g_57b318[c];
        if (g_57b418 != 0.0f && c >= '0' && c <= '9')
        {
            width += g_57b418;
        }
        else
        {
            width += g_currentFont->glyphs[glyph].width;
        }
    }
    return size * 10240.0f / (g_currentFont->cellWidth * 640) * width + i;
}

// FUNCTION: STUNTGP_D3D 0x4291f0
void FUN_4291f0(const char *text, int align, float x, float y, float z, D3DCOLOR color, float size, DWORD flags)
{
    if (y < g_clipTop || y > g_clipBottom)
    {
        return;
    }
    float left = x;
    float baseY = y;
    float minX = g_clipLeft - g_currentFont->cellWidth * size;
    float right = g_clipRight;
    switch (align)
    {
    case 1:
        left = x - FUN_4290d0(text, size) * 0.5f;
        break;
    case 2:
        left = x - FUN_4290d0(text, size);
        break;
    }
    size = size * 10240.0f / (g_currentFont->cellWidth * 640);
    float space = g_currentFont->glyphs[g_57b318[' ']].width * size + 1.0f;
    g_currentFont->slantScale = g_DD_DISPLAYRESHEIGHT * 5.2083335e-05f;
    const char *p;
    if (flags & 4)
    {
        float shadowZ = z - 0.001f;
        FUN_432300(g_currentFont, color, flags);
        x = left + size * g_currentFont->shadowOffset;
        y = y + size * g_currentFont->shadowOffset;
        for (p = text; *p != '\0' && *p != '\n' && x <= right; p++)
        {
            if (x < minX)
            {
                x = x + g_currentFont->glyphs[g_57b318[*p]].width * size + 1.0f;
            }
            else if (*p == ' ')
            {
                x += space;
            }
            else
            {
                x += FUN_4323f0(g_currentFont, *p, x, y, shadowZ, 0xffffffff, size, flags);
            }
        }
    }
    FUN_432300(g_currentFont, color, flags & ~4);
    x = left;
    for (p = text; *p != '\0' && *p != '\n' && x <= right; p++)
    {
        if (x < minX)
        {
            x = x + g_currentFont->glyphs[g_57b318[*p]].width * size + 1.0f;
        }
        else if (*p == ' ')
        {
            x += space;
        }
        else
        {
            x += FUN_4323f0(g_currentFont, *p, x, baseY, z, color, size, flags);
        }
    }
    FUN_432380();
}
