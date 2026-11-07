#ifndef FONT_H
#define FONT_H
#define WIN32_LEAN_AND_MEAN
#include <d3dtypes.h>
#include <windows.h>

struct Font
{
    DWORD unk00;
    void *unk04;
    BYTE unk08[0x1ba0 - 8];
};

extern Font g_fonts[2];
extern DWORD g_fontCount;
extern Font *g_currentFont;
extern float g_57b418;

void Font_Load(char *name);
void FUN_428c00(Font *font, BYTE *data, BYTE *texture);
void FUN_4291a0(float value);
void Font_Select(DWORD font);
void FUN_4291f0(const char *text, int align, float x, float y, float z, D3DCOLOR color, float size, DWORD flags);

#endif /* FONT_H */
