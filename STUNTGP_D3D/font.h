#ifndef FONT_H
#define FONT_H
#define WIN32_LEAN_AND_MEAN
#include <d3dtypes.h>
#include <windows.h>

// Glyph cell in the font texture. The first glyph's two leading words double
// as the font's texture slots (normal and inverted).
struct Glyph
{
    int texture;    // 0x00
    int textureAlt; // 0x04
    DWORD width;    // 0x08
    DWORD height;   // 0x0c
    DWORD unk10;    // 0x10
    DWORD unk14;    // 0x14
    DWORD advance;  // 0x18
    float u0;       // 0x1c
    float v0;       // 0x20
    float u1;       // 0x24
    float v1;       // 0x28
};

struct Font
{
    DWORD unk00;         // 0x00
    void *unk04;         // 0x04
    DWORD cellWidth;     // 0x08
    DWORD cellHeight;    // 0x0c
    DWORD unk10;         // 0x10
    float slant;         // 0x14
    float slantScale;    // 0x18
    float shadowOffset;  // 0x1c
    Glyph glyphs[160];   // 0x20
};

extern Font g_fonts[2];
extern DWORD g_fontCount;
extern Font *g_currentFont;
extern float g_57b418;
extern BYTE g_57b318[256];

extern BYTE g_577ad0[160];

void FUN_428a80();
void FUN_428ab0(Font *font, BYTE *cell, DWORD *outWidth, DWORD *outHeight, DWORD *outLeft, DWORD *outTop);
void FUN_429180(Font *font, DWORD width);
void FUN_4291b0(Font *font, float value);
void FUN_4291d0(Font *font, float value);
void Font_Load(char *name);
void FUN_428c00(Font *font, BYTE *data, BYTE *texture);
void FUN_4291a0(float value);
void Font_Select(DWORD font);
float FUN_4290d0(const char *text, float size);
void FUN_4291f0(const char *text, int align, float x, float y, float z, D3DCOLOR color, float size, DWORD flags);

#endif /* FONT_H */
