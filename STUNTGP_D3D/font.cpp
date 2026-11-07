#include "font.h"
#include "d3drender.h"
#include "Game/GameEngine/io_wad.h"

#include <stdlib.h>
#include <string.h>

// GLOBAL: STUNTGP_D3D 0x577bd0
Font g_fonts[2];

// GLOBAL: STUNTGP_D3D 0x57b310
Font *g_currentFont = NULL;

// GLOBAL: STUNTGP_D3D 0x57b314
DWORD g_fontCount = 0;

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

// STUB: STUNTGP_D3D 0x4291f0
void FUN_4291f0(const char *text, int align, float x, float y, float z, D3DCOLOR color, float size, DWORD flags)
{
}
