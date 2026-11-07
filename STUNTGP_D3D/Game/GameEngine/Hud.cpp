#include "GameUpdate.h"

#include <stdlib.h>

#include "../../d3drender.h"
#include "../../font.h"
#include "../../gametext.h"
#include "../../sound.h"
#include "../../soundsys.h"
#include "../../sprite.h"
#include "GameSetup.h"

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

void FUN_40d200(Car *car);
void FUN_40d280(Car *car);
void FUN_40d300(Car *car);
void FUN_40d380(Car *car);
void FUN_441e20();

extern DWORD g_61297c;
extern int g_60f020;
extern int g_60f2c8;
extern int g_60df98;
extern int g_61b74c;

// GLOBAL: STUNTGP_D3D 0x60d73c
DWORD g_60d73c;

// GLOBAL: STUNTGP_D3D 0x60d788
int g_60d788;

// GLOBAL: STUNTGP_D3D 0x612960
int g_612960;

// GLOBAL: STUNTGP_D3D 0x61b748
unsigned int g_61b748;

// GLOBAL: STUNTGP_D3D 0x61b750
int g_61b750;

// FUNCTION: STUNTGP_D3D 0x445350
void FUN_445350()
{
    g_60d788 = 1;
}

// FUNCTION: STUNTGP_D3D 0x446a70
void FUN_446a70()
{
    g_61297c += 10;
    if (g_61297c > 100)
    {
        g_61297c = 0;
    }
    g_60d73c = g_61297c;
}

// FUNCTION: STUNTGP_D3D 0x446a90
void FUN_446a90()
{
    g_sfxSetting += 10;
    if (g_sfxSetting > 100)
    {
        g_sfxSetting = 0;
    }
    Sound_ApplyVolumes();
}

// FUNCTION: STUNTGP_D3D 0x446ac0
void FUN_446ac0()
{
    g_musicSetting += 10;
    if (g_musicSetting > 100)
    {
        g_musicSetting = 0;
    }
    Sound_ApplyVolumes();
}

// FUNCTION: STUNTGP_D3D 0x446af0
void FUN_446af0()
{
    FUN_45f9d0();
    FUN_40d500();
    g_60f2c8 = 4;
    FUN_442350();
    g_61b748 = 0;
}

// FUNCTION: STUNTGP_D3D 0x446b20
void FUN_446b20()
{
    FUN_445350();
    FUN_441e20();
    g_61b748 = 0;
}

// FUNCTION: STUNTGP_D3D 0x446b40
void FUN_446b40()
{
    FUN_442350();
    g_61b744 = NULL;
    g_61b748 = 0;
}

void FUN_446bb0();

// GLOBAL: STUNTGP_D3D 0x485120
PauseItem g_485120[8] = {
    {1, 8, 12, 51, FUN_446b40, 0},
    {1, 9, 12, 71, FUN_446af0, 0},
    {1, 10, 12, 91, FUN_446b20, 0},
    {1, 12, 12, 131, FUN_446a90, 0},
    {1, 13, 12, 151, FUN_446ac0, 0},
    {1, 14, 12, 171, FUN_446a70, 0},
    {1, 15, 12, 191, FUN_446bb0, 54},
    {0, 0, 0, 0, NULL, 0},
};

// FUNCTION: STUNTGP_D3D 0x446b60
void FUN_446b60()
{
    switch (g_60f020)
    {
    case 1:
        g_485120[6].value = 51;
        return;
    case 2:
        g_485120[6].value = 52;
        return;
    case 3:
        g_485120[6].value = 53;
        return;
    case 4:
        g_485120[6].value = 54;
        return;
    }
}

// FUNCTION: STUNTGP_D3D 0x446bb0
void FUN_446bb0()
{
    if (++g_60f020 > 4)
    {
        g_60f020 = 1;
    }
    Car *car = &g_49a1f8[g_61b744->unk018];
    switch (g_60f020)
    {
    case 1:
        FUN_40d280(car);
        return;
    case 2:
        FUN_40d200(car);
        return;
    case 3:
        FUN_40d300(car);
        return;
    case 4:
        FUN_40d380(car);
        return;
    }
}

// Draws the pause menu lines; the selected one pulses red.
// FUNCTION: STUNTGP_D3D 0x446c20
void FUN_446c20(float x, float y)
{
    g_485120[1].active = g_612960 != 1;
    if (g_60f2b0 == 3 || g_576be0)
    {
        g_485120[6].active = 0;
    }
    else
    {
        g_485120[6].active = 1;
    }
    FUN_446b60();
    if (g_60df98 == 2 || g_60df98 == 5)
    {
        g_485120[2].text = 10;
    }
    else
    {
        g_485120[2].text = 11;
    }
    g_61b750 += 4;
    if (g_61b750 > 127)
    {
        g_61b750 -= 255;
    }
    int i = 0;
    for (PauseItem *item = g_485120; item->text != 0; item++, i++)
    {
        if (item->active == 1)
        {
            D3DCOLOR color;
            if (i == g_61b74c)
            {
                int pulse = abs(g_61b750) * 2;
                if (pulse > 255)
                {
                    pulse = 255;
                }
                color = (pulse | 0xffffff00) << 16;
            }
            else
            {
                color = 0xffffffff;
            }
            float tx = item->x + x;
            float ty = item->y + y;
            FUN_4291f0(g_6127a0[item->text], 0, tx, ty, 0.98f, color, 1.0f, 6);
            if (item->value)
            {
                FUN_4291f0(g_6127a0[item->value], 0, tx + 142.40001f, ty, 0.98f, color, 1.0f, 6);
            }
        }
    }
}

// STRING: STUNTGP_D3D 0x4857b0
// STRING: STUNTGP_D3D 0x4857b4
// GLOBAL: STUNTGP_D3D 0x4851e0
char *g_4851e0[2] = {"-", "+"};

// Percentage slider with - and + labels.
// FUNCTION: STUNTGP_D3D 0x446d90
void FUN_446d90(unsigned int value, float x, float y, float width, float height)
{
    width *= 0.8f;
    height *= 0.8f;
    float left = (100 - value) * width * 0.01f;
    float right = value * width * 0.01f;
    float ty = y - 4.0f;
    FUN_4291f0(g_4851e0[0], 0, x - 16.0f, ty, 0.98f, 0xffffffff, 1.0f, 6);
    float end = x + width;
    FUN_4291f0(g_4851e0[1], 0, end, ty, 0.98f, 0xffffffff, 1.0f, 6);
    if (left > 0.0f)
    {
        g_spriteDesc.flags = 4;
        g_spriteDesc.x = right + x;
        g_spriteDesc.y = y;
        g_spriteDesc.z = 0.97f;
        g_spriteDesc.points[0].x = 0.0f;
        g_spriteDesc.points[0].y = 0.0f;
        g_spriteDesc.points[0].u = 1008.0f;
        g_spriteDesc.points[0].v = 800.0f;
        g_spriteDesc.points[1].x = left;
        g_spriteDesc.points[1].y = 0.0f;
        g_spriteDesc.points[1].u = 1008.0f;
        g_spriteDesc.points[1].v = 864.0f;
        g_spriteDesc.points[2].x = left - 11.0f;
        g_spriteDesc.points[2].y = height;
        g_spriteDesc.points[2].u = 1008.0f;
        g_spriteDesc.points[2].v = 864.0f;
        g_spriteDesc.points[3].x = -11.0f;
        g_spriteDesc.points[3].y = height;
        g_spriteDesc.points[3].u = 1008.0f;
        g_spriteDesc.points[3].v = 800.0f;
        g_spriteDesc.texture = 11;
        g_spriteDesc.blendMode = 0x20;
        FUN_432e00(&g_spriteDesc);
    }
    if (right > 0.0f)
    {
        g_spriteDesc.flags = 4;
        g_spriteDesc.x = x;
        g_spriteDesc.y = y;
        g_spriteDesc.z = 0.97f;
        g_spriteDesc.points[0].x = 0.0f;
        g_spriteDesc.points[0].y = 0.0f;
        g_spriteDesc.points[0].u = 64.0f;
        g_spriteDesc.points[0].v = 684.0f;
        g_spriteDesc.points[1].x = right;
        g_spriteDesc.points[1].y = 0.0f;
        g_spriteDesc.points[1].u = (value * 100 / 100 + 16) * 4.0f;
        g_spriteDesc.points[1].v = 684.0f;
        g_spriteDesc.points[2].x = right - 11.0f;
        g_spriteDesc.points[2].y = height;
        g_spriteDesc.points[2].u = g_spriteDesc.points[1].u;
        g_spriteDesc.points[2].v = 744.0f;
        g_spriteDesc.points[3].x = -11.0f;
        g_spriteDesc.points[3].y = height;
        g_spriteDesc.points[3].u = 64.0f;
        g_spriteDesc.points[3].v = 744.0f;
        g_spriteDesc.texture = 11;
        g_spriteDesc.blendMode = 0x20;
        FUN_432e00(&g_spriteDesc);
    }
    float bottom = y + (height + 1.0f);
    float slant = end - 11.0f;
    FUN_447840(0xffffffff, x, y, 0.98f, end + 1.0f, y, 0.98f);
    FUN_447840(0xffffffff, end, y, 0.98f, slant, bottom, 0.98f);
    float left2 = x - 11.0f;
    FUN_447840(0xffffffff, slant, bottom, 0.98f, left2, bottom, 0.98f);
    FUN_447840(0xffffffff, left2, bottom, 0.98f, x, y, 0.98f);
}

// Pause menu input: up/down move the selection, fire runs the line's action, escape closes the menu.
// FUNCTION: STUNTGP_D3D 0x447100
void FUN_447100()
{
    void (*action)() = g_485120[g_61b74c].action;
    if (!g_61b744)
    {
        return;
    }
    if (g_61b744->keys[2] && !g_61b744->prevKeys[2])
    {
        FUN_461150(0x30, 0, 0, 0xff, 0, 1, 0);
        do
        {
            if (--g_61b74c < 0)
            {
                g_61b74c = 6;
            }
        } while (!g_485120[g_61b74c].active);
    }
    else if (g_61b744->keys[3] && !g_61b744->prevKeys[3])
    {
        FUN_461150(0x30, 0, 0, 0xff, 0, 1, 0);
        do
        {
            g_61b74c = (g_61b74c + 1) % 7;
        } while (!g_485120[g_61b74c].active);
    }
    if (g_61b748 > 1)
    {
        if (g_61b744->keys[6] && !g_61b744->prevKeys[6])
        {
            FUN_461150(0x31, 0, 0, 0xff, 0, 1, 0);
            FUN_446b40();
            return;
        }
        if (g_61b744->keys[4] && !g_61b744->prevKeys[4] && g_485120[g_61b74c].action)
        {
            FUN_461150(0x31, 0, 0, 0xff, 0, 1, 0);
            action();
            return;
        }
    }
    if (!g_61b744->keys[6] && !g_61b744->prevKeys[6])
    {
        if (g_61b748 <= 1)
        {
            g_61b748++;
        }
    }
    else
    {
        g_61b748 = 0;
    }
}

extern int g_6244fc;
extern int g_624500;
void FUN_447b70(int delay);

// FUNCTION: STUNTGP_D3D 0x4478c0
void FUN_4478c0()
{
    g_61b740->unk000 = 1;
    g_61b740->faders[0].active = 0;
    g_61b740->faders[0].value = 100.0f;
    g_61b740->faders[0].target = 100.0f;
    g_61b740->faders[1].unk08 = 640.0f - (g_6244fc + 166.40001f);
    g_61b740->faders[1].unk0c = 480.0f - (g_624500 + 106.4f);
    g_61b740->faders[1].value = 0.0f;
    g_61b740->faders[1].dx = 256;
    g_61b740->faders[1].dy = 0;
    g_61b740->faders[2].unk08 = 255.2f;
    g_61b740->faders[2].unk0c = g_624500 + 6.0f;
    g_61b740->faders[2].value = 0.0f;
    g_61b740->faders[2].dx = 0;
    g_61b740->faders[2].dy = -96;
    g_61b740->faders[7].unk08 = g_6244fc + 35.2f;
    g_61b740->faders[7].unk0c = 448.0f - g_624500;
    g_61b740->faders[7].value = 0.0f;
    g_61b740->faders[7].dx = -96;
    g_61b740->faders[7].dy = 0;
    g_61b740->faders[3].unk08 = 571.2f - g_6244fc;
    g_61b740->faders[3].unk0c = g_624500 + 3.2f;
    g_61b740->faders[3].value = 0.0f;
    g_61b740->faders[3].dx = 160;
    g_61b740->faders[3].dy = 0;
    g_61b740->faders[4].unk08 = 571.2f - g_6244fc;
    g_61b740->faders[4].unk0c = g_624500 + 3.2f;
    g_61b740->faders[4].value = 0.0f;
    g_61b740->faders[4].dx = 256;
    g_61b740->faders[4].dy = 0;
    g_61b740->faders[5].unk08 = 571.2f - g_6244fc;
    g_61b740->faders[5].unk0c = g_624500 + 3.2f;
    g_61b740->faders[5].value = 0.0f;
    g_61b740->faders[5].dx = 352;
    g_61b740->faders[5].dy = 0;
    g_61b740->faders[6].unk08 = g_6244fc + 3.2f;
    g_61b740->faders[6].unk0c = g_624500 + 19.2f;
    g_61b740->faders[6].value = 0.0f;
    g_61b740->faders[6].dx = -192;
    g_61b740->faders[6].dy = 0;
    FUN_447b70(60);
    g_61b740->faders[4].active = 1;
    g_61b740->faders[4].value = 100.0f;
    g_61b740->faders[3].active = 1;
    g_61b740->faders[3].value = 100.0f;
    g_61b740->faders[5].active = 1;
    g_61b740->faders[5].value = 100.0f;
}

// FUNCTION: STUNTGP_D3D 0x447a60
void FUN_447a60()
{
    for (int i = 0; i < 4; i++)
    {
        g_61b740 = &g_498248[i].fx;
        FUN_4478c0();
    }
    g_61b740 = &g_498248[0].fx;
}

// FUNCTION: STUNTGP_D3D 0x447a90
void FUN_447a90(Fader *fader)
{
    fader->active = 1;
    fader->target = 100.0f;
}

// FUNCTION: STUNTGP_D3D 0x447aa0
void FUN_447aa0(Fader *fader)
{
    fader->active = 1;
    fader->target = 0.0f;
}

// Places the result-table faders between their base and their offset.
// FUNCTION: STUNTGP_D3D 0x447fa0
void FUN_447fa0()
{
    SlotFx *fx = g_61b740;
    Fader *fader = &fx->faders[12];
    float v;
    for (int i = 0; i < 6; i++, fader++)
    {
        v = fader->value + fx->faders[8].value;
        if (v > 100.0f)
        {
            v = 100.0f;
        }
        fader->x = fader->dx * v * 0.01f + fader->unk08;
        fader->y = fader->dy * v * 0.01f + fader->unk0c;
    }
    v = g_61b740->faders[11].value;
    v += g_61b740->faders[8].value;
    if (v > 100.0f)
    {
        v = 100.0f;
    }
    g_61b740->faders[9].x = g_61b740->faders[9].dx * v * 0.01f + g_61b740->faders[9].unk08;
    g_61b740->faders[9].y = g_61b740->faders[9].dy * v * 0.01f + g_61b740->faders[9].unk0c;
    v = g_61b740->faders[11].value;
    v += g_61b740->faders[8].value;
    if (v > 100.0f)
    {
        v = 100.0f;
    }
    g_61b740->faders[11].x = g_61b740->faders[11].dx * v * 0.01f + g_61b740->faders[11].unk08;
    g_61b740->faders[11].y = g_61b740->faders[11].dy * v * 0.01f + g_61b740->faders[11].unk0c;
    v = g_61b740->faders[10].value + g_61b740->faders[8].value;
    if (v > 100.0f)
    {
        v = 100.0f;
    }
    g_61b740->faders[10].x = g_61b740->faders[10].dx * v * 0.01f + g_61b740->faders[10].unk08;
    g_61b740->faders[10].y = g_61b740->faders[10].dy * v * 0.01f + g_61b740->faders[10].unk0c;
}

// FUNCTION: STUNTGP_D3D 0x449e80
void FUN_449e80()
{
    SlotFx *fx = g_61b740;
    fx->faders[8].active = 0;
    fx->faders[8].value = 0.0f;
    Fader *fader = &fx->faders[12];
    for (unsigned int i = 0; i < 6; i++, fader++)
    {
        fader->unk08 = 102.4f;
        fader->unk0c = 102.4f;
        fader->active = 0;
        fader->target = 0.0f;
        fader->value = 100.0f;
        fader->dx = i * 80 * 0.8f + 640.0f;
        fader->dy = 0;
    }
    fx->faders[9].unk08 = 12.8f;
    fx->faders[9].unk0c = 25.6f;
    fx->faders[9].active = 1;
    fx->faders[9].target = 0.0f;
    fx->faders[9].value = 100.0f;
    fx->faders[9].dx = -288;
    fx->faders[9].dy = 0;
    fx->faders[10].unk08 = 624.0f;
    fx->faders[10].unk0c = 32.0f;
    fx->faders[10].active = 1;
    fx->faders[10].target = 0.0f;
    fx->faders[10].value = 100.0f;
    fx->faders[10].dx = 230;
    fx->faders[10].dy = 0;
    fx->faders[11].unk08 = 320.0f;
    fx->faders[11].unk0c = 440.0f;
    fx->faders[11].active = 1;
    fx->faders[11].target = 0.0f;
    fx->faders[11].value = 100.0f;
    fx->faders[11].dx = 0;
    fx->faders[11].dy = 128;
}
