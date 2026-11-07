#include "font.h"
#include "d3drender.h"
#include "Game/GameEngine/io_wad.h"
#include "globals.h"
#include "mem.h"

#include <stdio.h>

extern char g_GraphicsDirectory[128];

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

// GLOBAL: STUNTGP_D3D 0x577ad0
BYTE g_577ad0[160];

// FUNCTION: STUNTGP_D3D 0x428a80
void FUN_428a80()
{
    memset(g_57b318, 0, sizeof(g_57b318));
    for (DWORD i = 0; i < 160; i++)
    {
        g_57b318[g_577ad0[i]] = i;
    }
    g_57b318[' '] = 0x99;
}

// Bounding box of the opaque pixels in one glyph cell; magenta and dark pixels are background.
// FUNCTION: STUNTGP_D3D 0x428ab0
void FUN_428ab0(Font *font, BYTE *cell, DWORD *outWidth, DWORD *outHeight, DWORD *outLeft, DWORD *outTop)
{
    DWORD w = font->cellWidth;
    DWORD h = font->cellHeight;
    DWORD offset = 0;
    DWORD maxWidth = 0;
    DWORD maxHeight = 0;
    DWORD left = w;
    DWORD top = h;
    DWORD minY = h;
    DWORD minX = w;
    DWORD maxY = 0;
    DWORD maxX = 0;
    DWORD x;
    DWORD y;
    int d;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            DWORD r = cell[offset + x * 3];
            DWORD g = cell[offset + x * 3 + 1];
            DWORD b = cell[offset + x * 3 + 2];
            if (r == 0xff ? (g != 0 || b != r) : (r >= 0x60 || g >= 0x60 || b >= 0x60))
            {
                if (x < minX)
                {
                    minX = x;
                }
                if (x > maxX)
                {
                    maxX = x;
                }
                if (y < minY)
                {
                    minY = y;
                }
                if (y > maxY)
                {
                    maxY = y;
                }
            }
        }
        offset += w * 3;
        d = maxX - minX;
        if (d < 0)
        {
            d = 0;
        }
        if (d + 1 > maxWidth)
        {
            maxWidth = d + 1;
        }
        d = maxY - minY;
        if (d < 2)
        {
            d = 2;
        }
        if (d + 1 > maxHeight)
        {
            maxHeight = d + 1;
        }
        if (minX < left)
        {
            left = minX;
        }
        if (minY < top)
        {
            top = minY;
        }
    }
    *outWidth = maxWidth;
    *outHeight = h;
    *outLeft = left;
    *outTop = 0;
}

// Packs the 160 glyph cells of the font image into a 256x256 RGB texture.
// FUNCTION: STUNTGP_D3D 0x428c00
void FUN_428c00(Font *font, BYTE *data, BYTE *texture)
{
    DWORD top;
    DWORD left;
    DWORD w;
    DWORD h;
    DWORD row;
    BYTE *dst;
    DWORD col;
    DWORD i;
    DWORD x;
    DWORD y;
    DWORD src;
    for (i = 0; i < 0x10000; i++)
    {
        texture[i * 3] = 0xff;
        texture[i * 3 + 1] = 0;
        texture[i * 3 + 2] = 0xff;
    }
    FUN_4291b0(font, 3.0f);
    FUN_4291d0(font, 8.0f);
    FUN_429180(font, 8);
    font->unk00 = 0;
    font->unk04 = Mem_Alloc(0x400, 0);
    font->cellWidth = g_489714;
    font->cellHeight = g_489718 / 160;
    x = 0;
    y = 0;
    Glyph *glyph = font->glyphs;
    for (i = 0; i < 160; i++)
    {
        src = font->cellWidth * font->cellHeight * i * 3;
        FUN_428ab0(font, data + src, &w, &h, &left, &top);
        DWORD width = w;
        if (width + x > 256)
        {
            y += h;
            x = 0;
            if (y >= 256)
            {
                break;
            }
        }
        src += left * 3;
        dst = texture + (y * 256 + x) * 3;
        for (row = 0; row < font->cellHeight; row++)
        {
            for (col = 0; col < width; col++)
            {
                dst[col * 3] = data[src + col * 3];
                dst[col * 3 + 1] = data[src + col * 3 + 1];
                dst[col * 3 + 2] = data[src + col * 3 + 2];
            }
            src += font->cellWidth * 3;
            dst += 256 * 3;
        }
        float fx = x;
        float fy = y;
        x += width + 1;
        glyph->u0 = fx * (1.0f / 256.0f);
        glyph->v0 = (fy + 0.05f) * (1.0f / 256.0f);
        glyph->u1 = (width + fx) * (1.0f / 256.0f);
        glyph->v1 = (h + fy + 0.25f) * (1.0f / 256.0f);
        glyph->width = width;
        glyph->height = h;
        glyph->advance = width + 1;
        glyph->unk10 = 0;
        glyph->unk14 = 0;
        glyph++;
    }
    font->glyphs[0x99] = font->glyphs[g_57b318[' ']];
}

// FUNCTION: STUNTGP_D3D 0x428e40
void FUN_428e40(char *name)
{
    char path[128];
    Font *font = g_currentFont;
    // STRING: STUNTGP_D3D 0x477758
    sprintf(path, "%s\\Fonts\\%s.TGA", g_GraphicsDirectory, name);
    BYTE *data = (BYTE *)Mem_Alloc(size_of_file(path), 0);
    FUN_4623c0(path, data, font->unk04);
    BYTE *texture = (BYTE *)Mem_Alloc(0x30000, 0);
    FUN_428c00(font, data, texture);
    FUN_4327e0(texture, font, 0);
    FUN_42be90(path);
    Mem_Free(texture);
    Mem_Free(data);
    g_fontCount++;
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

// Loads the charset index and the fonts sized for the display width.
// FUNCTION: STUNTGP_D3D 0x428fa0
void FUN_428fa0()
{
    char path[128];
    FUN_4291a0(0.0f);
    g_currentFont = g_fonts;
    g_fontCount = 0;
    // STRING: STUNTGP_D3D 0x477768
    sprintf(path, "%s\\Fonts\\INDEX.TXT", g_GraphicsDirectory);
    bload(path, (char *)g_577ad0, sizeof(g_577ad0));
    if (g_DD_DISPLAYRESWIDTH >= 1280)
    {
        // STRING: STUNTGP_D3D 0x47777c
        FUN_428e40("I32");
        g_currentFont = &g_fonts[g_fontCount];
        // STRING: STUNTGP_D3D 0x477780
        FUN_428e40("I32_b025");
    }
    else if (g_DD_DISPLAYRESWIDTH >= 1152)
    {
        // STRING: STUNTGP_D3D 0x47778c
        FUN_428e40("I32");
        g_currentFont = &g_fonts[g_fontCount];
        // STRING: STUNTGP_D3D 0x477790
        FUN_428e40("I32_b025");
    }
    else if (g_DD_DISPLAYRESWIDTH >= 1024)
    {
        // STRING: STUNTGP_D3D 0x47779c
        FUN_428e40("I32_b05");
        g_currentFont = &g_fonts[g_fontCount];
        // STRING: STUNTGP_D3D 0x4777a4
        FUN_428e40("I32_b025");
    }
    else if (g_DD_DISPLAYRESWIDTH >= 800)
    {
        // STRING: STUNTGP_D3D 0x4777b0
        FUN_428e40("I32_b05");
    }
    else
    {
        // STRING: STUNTGP_D3D 0x4777b8
        FUN_428e40("I32_b05");
    }
    FUN_428a80();
    Font_Select(0);
}

// FUNCTION: STUNTGP_D3D 0x429180
void FUN_429180(Font *font, DWORD width)
{
    font->glyphs[g_57b318[' ']].width = width;
}

// FUNCTION: STUNTGP_D3D 0x4291a0
void FUN_4291a0(float value)
{
    g_57b418 = value;
}

// FUNCTION: STUNTGP_D3D 0x4291b0
void FUN_4291b0(Font *font, float value)
{
    font->shadowOffset = g_DD_DISPLAYRESWIDTH * value * (1.0f / 640.0f);
}

// FUNCTION: STUNTGP_D3D 0x4291d0
void FUN_4291d0(Font *font, float value)
{
    font->slant = g_DD_DISPLAYRESWIDTH * value * (1.0f / 640.0f);
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
