#include "GameUpdate.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../d3drender.h"
#include "../../font.h"
#include "../../gametext.h"
#include "../../sound.h"
#include "../../soundsys.h"
#include "../../sprite.h"
#include "GameSetup.h"
#include "RenderState.h"

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

extern DWORD g_60eff4;
extern DWORD g_60eff8;
extern char g_LevelScript[32];
void FUN_445f70(int value);
void FUN_4487d0(unsigned int index, float x, float y, float z);
extern int g_60f020;
extern int g_60f2c8;
extern int g_60f01c;
extern int g_60eff0;
extern int g_60df98;
extern int g_61b74c;

// Level script names: tracks, track sets, then cars.
// GLOBAL: STUNTGP_D3D 0x482b88
char *g_482b88[76] = {
    // STRING: STUNTGP_D3D 0x482cb8
    "TRACK1",
    // STRING: STUNTGP_D3D 0x482cc0
    "TRACK2",
    // STRING: STUNTGP_D3D 0x482cc8
    "TRACK3",
    // STRING: STUNTGP_D3D 0x482cd0
    "TRACK4",
    // STRING: STUNTGP_D3D 0x482cd8
    "TRACK5",
    // STRING: STUNTGP_D3D 0x482ce0
    "TRACK6",
    // STRING: STUNTGP_D3D 0x482ce8
    "TRACK7",
    // STRING: STUNTGP_D3D 0x482cf0
    "TRACK8",
    // STRING: STUNTGP_D3D 0x482cf8
    "TRACK9",
    // STRING: STUNTGP_D3D 0x482d00
    "TRACK10",
    // STRING: STUNTGP_D3D 0x482d08
    "TRACK11",
    // STRING: STUNTGP_D3D 0x482d10
    "TRACK12",
    // STRING: STUNTGP_D3D 0x482d18
    "TRACK13",
    // STRING: STUNTGP_D3D 0x482d20
    "TRACK14",
    // STRING: STUNTGP_D3D 0x482d28
    "TRACK15",
    // STRING: STUNTGP_D3D 0x482d30
    "TRACK16",
    // STRING: STUNTGP_D3D 0x482d38
    "TRACK17",
    // STRING: STUNTGP_D3D 0x482d40
    "TRACK18",
    // STRING: STUNTGP_D3D 0x482d48
    "TRACK19",
    // STRING: STUNTGP_D3D 0x482d50
    "TRACK20",
    // STRING: STUNTGP_D3D 0x482d58
    "TRACK21",
    // STRING: STUNTGP_D3D 0x482d60
    "TRACK22",
    // STRING: STUNTGP_D3D 0x482d68
    "TRACK23",
    // STRING: STUNTGP_D3D 0x482d70
    "TRACK24",
    // STRING: STUNTGP_D3D 0x482d78
    "CHALL1",
    // STRING: STUNTGP_D3D 0x482d80
    "TRACKSET00",
    // STRING: STUNTGP_D3D 0x482d8c
    "TRACKSET01",
    // STRING: STUNTGP_D3D 0x482d98
    "TRACKSET02",
    // STRING: STUNTGP_D3D 0x482da4
    "TRACKSET03",
    // STRING: STUNTGP_D3D 0x482db0
    "TRACKSET04",
    // STRING: STUNTGP_D3D 0x482dbc
    "TRACKSET05",
    // STRING: STUNTGP_D3D 0x482dc8
    "TRACKSET06",
    // STRING: STUNTGP_D3D 0x482dd4
    "DUMMY",
    // STRING: STUNTGP_D3D 0x482ddc
    "DUMMY",
    // STRING: STUNTGP_D3D 0x482de4
    "Car1",
    // STRING: STUNTGP_D3D 0x482dec
    "Car1sh",
    // STRING: STUNTGP_D3D 0x482df4
    "Car2",
    // STRING: STUNTGP_D3D 0x482dfc
    "Car2sh",
    // STRING: STUNTGP_D3D 0x482e04
    "Car3",
    // STRING: STUNTGP_D3D 0x482e0c
    "Car3sh",
    // STRING: STUNTGP_D3D 0x482e14
    "Car4",
    // STRING: STUNTGP_D3D 0x482e1c
    "Car4sh",
    // STRING: STUNTGP_D3D 0x482e24
    "Car5",
    // STRING: STUNTGP_D3D 0x482e2c
    "Car5sh",
    // STRING: STUNTGP_D3D 0x482e34
    "Car6",
    // STRING: STUNTGP_D3D 0x482e3c
    "Car6sh",
    // STRING: STUNTGP_D3D 0x482e44
    "Car7",
    // STRING: STUNTGP_D3D 0x482e4c
    "Car7sh",
    // STRING: STUNTGP_D3D 0x482e54
    "Car8",
    // STRING: STUNTGP_D3D 0x482e5c
    "Car8sh",
    // STRING: STUNTGP_D3D 0x482e64
    "Car9",
    // STRING: STUNTGP_D3D 0x482e6c
    "Car9sh",
    // STRING: STUNTGP_D3D 0x482e74
    "Car10",
    // STRING: STUNTGP_D3D 0x482e7c
    "Car10sh",
    // STRING: STUNTGP_D3D 0x482e84
    "Car11",
    // STRING: STUNTGP_D3D 0x482e8c
    "Car11sh",
    // STRING: STUNTGP_D3D 0x482e94
    "Car12",
    // STRING: STUNTGP_D3D 0x482e9c
    "Car12sh",
    // STRING: STUNTGP_D3D 0x482ea4
    "Car13",
    // STRING: STUNTGP_D3D 0x482eac
    "Car13sh",
    // STRING: STUNTGP_D3D 0x482eb4
    "Car14",
    // STRING: STUNTGP_D3D 0x482ebc
    "Car14sh",
    // STRING: STUNTGP_D3D 0x482ec4
    "Car15",
    // STRING: STUNTGP_D3D 0x482ecc
    "Car15sh",
    // STRING: STUNTGP_D3D 0x482ed4
    "Car16",
    // STRING: STUNTGP_D3D 0x482edc
    "Car16sh",
    // STRING: STUNTGP_D3D 0x482ee4
    "Car17",
    // STRING: STUNTGP_D3D 0x482eec
    "Car17sh",
    // STRING: STUNTGP_D3D 0x482ef4
    "Car18",
    // STRING: STUNTGP_D3D 0x482efc
    "Car18sh",
    // STRING: STUNTGP_D3D 0x482f04
    "Car19",
    // STRING: STUNTGP_D3D 0x482f0c
    "Car19sh",
    // STRING: STUNTGP_D3D 0x482f14
    "Car20",
    // STRING: STUNTGP_D3D 0x482f1c
    "Car20sh",
    // STRING: STUNTGP_D3D 0x482f24
    "Car4",
    // STRING: STUNTGP_D3D 0x482f2c
    "Car4sh",
};

// GLOBAL: STUNTGP_D3D 0x60dfec
int g_60dfec;

// GLOBAL: STUNTGP_D3D 0x61b748
unsigned int g_61b748;

// GLOBAL: STUNTGP_D3D 0x61b750
int g_61b750;

// FUNCTION: STUNTGP_D3D 0x445120
void FUN_445120()
{
    g_60eff8 = 100;
    g_60dfec = 2;
    g_60eff4 = g_60d730.unk038;
    if (g_60d730.unk038 < 1200)
    {
        g_60eff4 = 5400;
    }
}

int FUN_42f1f0(int range);
void FUN_443010(int enable);
void FUN_442ef0();
void FUN_442f60(Unk4d5cc0 *ghost);

// Copies the player's race entry to the AI slots, then adds the replay and level ghosts when
// present and clears the rest.
// FUNCTION: STUNTGP_D3D 0x445150
void FUN_445150()
{
    if (g_60d730.entries[0].unk02c == 8)
    {
        g_60d730.entries[0].unk02c = 0;
    }
    if (g_60d730.entries[0].unk02c == 0)
    {
        g_60d730.entries[0].unk02c = abs(FUN_42f1f0(5)) + 2;
    }
    g_60d730.entries[0].unk008 = 1;
    for (int i = 1; i < 3; i++)
    {
        g_60d730.entries[i] = g_60d730.entries[0];
        g_60d730.entries[i].unk004 = 2;
    }
    Unk4d5cc0 *ghost = (Unk4d5cc0 *)g_60d730.unk85c;
    if (ghost)
    {
        FUN_443010((int)ghost);
        g_60d730.unk854 = 0;
        g_60d730.unk85c = 0;
        g_60d730.unk858 = 0;
        g_60d730.entries[3] = g_60d730.entries[0];
        g_60d730.entries[3].unk024 = ghost->unk20;
        g_60d730.entries[3].unk028 = ghost->unk22;
        g_60d730.entries[3].unk030 = ghost->unk26;
        g_60d730.entries[3].unk02c = ghost->unk24;
    }
    else
    {
        g_60d730.entries[3] = g_60d730.entries[0];
    }
    int count = 4;
    FUN_442ef0();
    ghost = g_60d730.unk850;
    if (ghost)
    {
        FUN_442f60(ghost);
        g_60d730.unk848 = 0;
        g_60d730.unk850 = NULL;
        g_60d730.unk84c = 0;
        g_60d730.entries[4] = g_60d730.entries[0];
        g_60d730.entries[4].unk024 = ghost->unk20;
        g_60d730.entries[4].unk028 = ghost->unk22;
        g_60d730.entries[4].unk030 = ghost->unk26;
        g_60d730.entries[4].unk02c = 1;
        count = 5;
    }
    RaceEntry *rest = &g_60d730.entries[count];
    memset(rest, 0, (BYTE *)&g_60d730.entries[6] - (BYTE *)rest);
}

// FUNCTION: STUNTGP_D3D 0x4452e0
void FUN_4452e0()
{
    if (g_612948.unk02a4 == 1)
    {
        FUN_445f70(g_60d730.unk014);
        sprintf(g_LevelScript, g_482b88[g_60d730.unk018]);
    }
}

// FUNCTION: STUNTGP_D3D 0x445310
void FUN_445310()
{
    g_612948.unk0048 = 3600;
    g_612948.unk0054 = 1;
    g_60f2c8 = 4;
    g_60f01c = 10;
    g_60eff0 = 1;
    g_60df98 = 2;
}

// FUNCTION: STUNTGP_D3D 0x445350
void FUN_445350()
{
    g_60d730.unk058 = 1;
}

void FUN_443060();
extern int g_60f284;
extern int g_60f294;
extern int g_60f298;
extern int g_60f29c;

// GLOBAL: STUNTGP_D3D 0x60f288
int g_60f288;

// GLOBAL: STUNTGP_D3D 0x60f28c
int g_60f28c;

// GLOBAL: STUNTGP_D3D 0x60f290
int g_60f290;

// FUNCTION: STUNTGP_D3D 0x445360
void FUN_445360()
{
    FUN_443060();
    FUN_445150();
    g_60d730.unk024[0] = 0;
    g_576be0 = 0;
    g_60f294 = 0;
    g_60f298 = 0;
    g_60f29c = 0;
    g_60f288 = 0;
    g_60f28c = 0;
    g_60f290 = 0;
    g_60f284 = g_60d730.unk844;
}

// FUNCTION: STUNTGP_D3D 0x446a70
void FUN_446a70()
{
    g_612948.unk0034 += 10;
    if (g_612948.unk0034 > 100)
    {
        g_612948.unk0034 = 0;
    }
    g_60d730.unk00c = g_612948.unk0034;
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

// Pip animation frames, indexed by frame / 2.
// GLOBAL: STUNTGP_D3D 0x485110
char g_485110[8] = {0, 13, 26, 39, 39, 26, 13, 0};

// GLOBAL: STUNTGP_D3D 0x485118
char g_485118[8] = {0, 11, 22, 33, 33, 22, 11, 0};

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
    g_485120[1].active = g_612948.unk0018 != 1;
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

void FUN_447b70(int delay);

// FUNCTION: STUNTGP_D3D 0x4478c0
void FUN_4478c0()
{
    g_61b740->unk000 = 1;
    g_61b740->faders[0].active = 0;
    g_61b740->faders[0].value = 100.0f;
    g_61b740->faders[0].target = 100.0f;
    g_61b740->faders[1].unk08 = 640.0f - (g_renderState.unk8014 + 166.40001f);
    g_61b740->faders[1].unk0c = 480.0f - (g_renderState.unk8018 + 106.4f);
    g_61b740->faders[1].value = 0.0f;
    g_61b740->faders[1].dx = 256;
    g_61b740->faders[1].dy = 0;
    g_61b740->faders[2].unk08 = 255.2f;
    g_61b740->faders[2].unk0c = g_renderState.unk8018 + 6.0f;
    g_61b740->faders[2].value = 0.0f;
    g_61b740->faders[2].dx = 0;
    g_61b740->faders[2].dy = -96;
    g_61b740->faders[7].unk08 = g_renderState.unk8014 + 35.2f;
    g_61b740->faders[7].unk0c = 448.0f - g_renderState.unk8018;
    g_61b740->faders[7].value = 0.0f;
    g_61b740->faders[7].dx = -96;
    g_61b740->faders[7].dy = 0;
    g_61b740->faders[3].unk08 = 571.2f - g_renderState.unk8014;
    g_61b740->faders[3].unk0c = g_renderState.unk8018 + 3.2f;
    g_61b740->faders[3].value = 0.0f;
    g_61b740->faders[3].dx = 160;
    g_61b740->faders[3].dy = 0;
    g_61b740->faders[4].unk08 = 571.2f - g_renderState.unk8014;
    g_61b740->faders[4].unk0c = g_renderState.unk8018 + 3.2f;
    g_61b740->faders[4].value = 0.0f;
    g_61b740->faders[4].dx = 256;
    g_61b740->faders[4].dy = 0;
    g_61b740->faders[5].unk08 = 571.2f - g_renderState.unk8014;
    g_61b740->faders[5].unk0c = g_renderState.unk8018 + 3.2f;
    g_61b740->faders[5].value = 0.0f;
    g_61b740->faders[5].dx = 352;
    g_61b740->faders[5].dy = 0;
    g_61b740->faders[6].unk08 = g_renderState.unk8014 + 3.2f;
    g_61b740->faders[6].unk0c = g_renderState.unk8018 + 19.2f;
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

// FUNCTION: STUNTGP_D3D 0x448a70
void FUN_448a70()
{
    Car *car = g_4722d0->data;
    unsigned int index;
    if (car->unk24e0 == 1)
    {
        index = car->unk24e4;
    }
    else
    {
        index = car->unk24ac;
    }
    FUN_4487d0(index, g_61b740->faders[6].x, g_61b740->faders[6].y, 0.95f);
}

int FUN_448150(DWORD value, int *digits, DWORD count, int leadingZeros);

// Three-digit readout at fader 1, right-aligned by skipping the blank leading digits.
// FUNCTION: STUNTGP_D3D 0x4492d0
void FUN_4492d0(float value)
{
    int digits[3];
    int blanks = FUN_448150((int)value, digits, 3, 0);
    g_spriteDesc.flags = 2;
    g_spriteDesc.z = 0.95f;
    g_spriteDesc.width = 19.2f;
    g_spriteDesc.height = 24.800001f;
    g_spriteDesc.texture = 11;
    g_spriteDesc.blendMode = 0x20;
    g_spriteDesc.v0 = 896.0f;
    g_spriteDesc.v1 = 1020.0f;
    float x = blanks * 16.0f + g_61b740->faders[1].x + 82.4f;
    g_spriteDesc.y = g_61b740->faders[1].y + 52.8f;
    for (int i = 0; i < 3; i++)
    {
        if (digits[i] != -1)
        {
            g_spriteDesc.x = x;
            g_spriteDesc.u0 = ((digits[i] * 25 + 1) * 1024.0f) * 0.00390625f;
            g_spriteDesc.u1 = g_spriteDesc.u0 + 96.0f;
            FUN_432e00(&g_spriteDesc);
            x += 16.0f;
        }
    }
}

struct HudPip
{
    DWORD x;     // 0x00
    DWORD y;     // 0x04
    DWORD frame; // 0x08
};

// GLOBAL: STUNTGP_D3D 0x485250
HudPip g_485250[10] = {
    {0, 0, 0},
    {13, 0, 0},
    {26, 0, 0},
    {39, 0, 0},
    {52, 0, 0},
    {66, 0, 0},
    {79, 0, 0},
    {92, 0, 0},
    {105, 0, 0},
    {118, 0, 0},
};

// Flashes the pip at fader 2 for a cycle each time unk7254 reaches 1 mod 10.
// FUNCTION: STUNTGP_D3D 0x448360
void FUN_448360()
{
    if (g_61b740[1].delay)
    {
        g_spriteDesc.flags = 10;
        DWORD frame = (g_61b740[1].delay + 1) & 0xf;
        g_spriteDesc.z = 0.98f;
        g_61b740[1].delay = frame;
        g_spriteDesc.scaleX = 1.5f;
        g_spriteDesc.scaleY = 1.5f;
        g_spriteDesc.x = g_61b740->faders[2].x + 115.8f;
        g_spriteDesc.y = g_61b740->faders[2].y + 25.800001f;
        g_spriteDesc.v0 = 512.0f;
        g_spriteDesc.v1 = 572.0f;
        g_spriteDesc.width = 8.8f;
        g_spriteDesc.height = 11.6f;
        g_spriteDesc.texture = 11;
        g_spriteDesc.blendMode = 0x20;
        g_spriteDesc.u0 = ((g_485110[frame >> 1] + 122) * 1024.0f) * 0.00390625f;
        g_spriteDesc.u1 = g_spriteDesc.u0 + 44.0f;
        FUN_432e00(&g_spriteDesc);
    }
    else if (g_4722d0->data->unk7254 % 10 == 1)
    {
        g_61b740[1].delay = 1;
    }
}

// Row of pips at fader 2, one per unk725c; lit pips grow in, the rest fade out.
// FUNCTION: STUNTGP_D3D 0x448480
void FUN_448480()
{
    float x = g_61b740->faders[2].x + 2.0f;
    float y = g_61b740->faders[2].y + 52.2f;
    HudPip *pip = g_485250;
    for (DWORD i = 0; i < g_4722d0->data->unk725c; i++, pip++)
    {
        g_spriteDesc.flags = 10;
        g_spriteDesc.z = 0.98f;
        g_spriteDesc.scaleX = 1.5f;
        g_spriteDesc.scaleY = 1.5f;
        g_spriteDesc.x = pip->x + x;
        g_spriteDesc.y = pip->y + y;
        if (i < g_4722d0->data->unk725c)
        {
            if (pip->frame < 8)
            {
                pip->frame++;
            }
        }
        else if (pip->frame != 0)
        {
            pip->frame = (pip->frame + 1) & 0xf;
        }
        g_spriteDesc.v0 = 580.0f;
        g_spriteDesc.v1 = 624.0f;
        g_spriteDesc.width = 8.8f;
        g_spriteDesc.height = 8.8f;
        g_spriteDesc.texture = 11;
        g_spriteDesc.blendMode = 0x20;
        g_spriteDesc.u0 = ((g_485118[pip->frame >> 1] + 123) * 1024.0f) * 0.00390625f;
        g_spriteDesc.u1 = g_spriteDesc.u0 + 44.0f;
        FUN_432e00(&g_spriteDesc);
    }
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

// u0, v0, u1, v1 of the left cap, the middle and the right cap of a HUD bar.
// GLOBAL: STUNTGP_D3D 0x4851f0
float g_4851f0[4][6] = {
    {440.0f, 572.0f, 0.0f, 72.0f, 364.0f, 436.0f},
    {440.0f, 572.0f, 436.0f, 508.0f, 800.0f, 872.0f},
    {0.0f, 252.0f, 0.0f, 72.0f, 948.0f, 1020.0f},
    {0.0f, 252.0f, 1020.0f, 948.0f, 72.0f, 0.0f},
};

// Bar with 18 pixel caps; flags 2 centres it, 4 right-aligns it, 0x10/0x20/0x40 pick the style.
// FUNCTION: STUNTGP_D3D 0x4476c0
void FUN_4476c0(DWORD flags, float x, float y, float z, float width, float height)
{
    float *uv;
    float left;

    if (flags & 0x40)
    {
        uv = g_4851f0[3];
    }
    else if (flags & 0x20)
    {
        uv = g_4851f0[2];
    }
    else if (flags & 0x10)
    {
        uv = g_4851f0[1];
    }
    else
    {
        uv = g_4851f0[0];
    }
    width += 36.0f;
    if (flags & 2)
    {
        left = width * -0.5f;
    }
    else if (flags & 4)
    {
        left = -(width - 18.0f);
    }
    else
    {
        left = -18.0f;
    }
    g_spriteDesc.z = z;
    g_spriteDesc.height = height;
    g_spriteDesc.v0 = uv[0];
    g_spriteDesc.v1 = uv[1];
    g_spriteDesc.y = y;
    g_spriteDesc.x = left + x;
    g_spriteDesc.flags = 2;
    g_spriteDesc.texture = 15;
    g_spriteDesc.blendMode = 0x20;
    g_spriteDesc.u0 = uv[2];
    g_spriteDesc.u1 = uv[3];
    g_spriteDesc.width = 18.0f;
    FUN_432e00(&g_spriteDesc);
    left += 18.0f;
    g_spriteDesc.y = y;
    g_spriteDesc.u0 = uv[3];
    g_spriteDesc.u1 = uv[4];
    width -= 36.0f;
    g_spriteDesc.x = left + x;
    g_spriteDesc.width = width;
    FUN_432e00(&g_spriteDesc);
    g_spriteDesc.x = x + (width + left);
    g_spriteDesc.y = y;
    g_spriteDesc.u0 = uv[4];
    g_spriteDesc.u1 = uv[5];
    g_spriteDesc.width = 18.0f;
    FUN_432e00(&g_spriteDesc);
}

// Piece of texture 14 in 1/256 units, drawn at 0.8 scale.
struct HudSprite
{
    int u;
    int v;
    int x;
    int y;
    int width;
    int height;
};

// Lap counter digits [0..7] and the "LAP" label [8].
// GLOBAL: STUNTGP_D3D 0x4852c8
HudSprite g_4852c8[9] = {
    {0, 89, 0, 0, 38, 34},
    {0, 124, 0, 0, 38, 33},
    {38, 89, 0, 0, 38, 34},
    {76, 89, 0, 0, 38, 34},
    {114, 89, 0, 0, 38, 34},
    {38, 124, 0, 0, 38, 33},
    {76, 124, 0, 0, 38, 33},
    {114, 124, 0, 0, 38, 33},
    {215, 231, 0, 0, 39, 22},
};

// Draws the current lap number right-aligned on fader 7, with its label.
// FUNCTION: STUNTGP_D3D 0x4485e0
void FUN_4485e0()
{
    g_spriteDesc.flags = 2;
    g_spriteDesc.z = 0.95f;
    g_spriteDesc.texture = 14;
    g_spriteDesc.blendMode = 0x20;
    unsigned int lap = g_4722d0->data->unk1f10;
    float width = g_4852c8[lap].width * 0.8f;
    g_spriteDesc.x = g_61b740->faders[7].x - width;
    g_spriteDesc.y = g_61b740->faders[7].y;
    g_spriteDesc.u0 = (float)(g_4852c8[lap].u * 1024.0f) * 0.00390625f;
    g_spriteDesc.v0 = (float)(g_4852c8[lap].v * 1024.0f) * 0.00390625f;
    g_spriteDesc.u1 = (float)((g_4852c8[lap].u + g_4852c8[lap].width) * 1024.0f) * 0.00390625f;
    g_spriteDesc.v1 = (float)((g_4852c8[lap].height + g_4852c8[lap].v) * 1024.0f) * 0.00390625f;
    g_spriteDesc.width = width;
    g_spriteDesc.height = g_4852c8[lap].height * 0.8f;
    FUN_432e00(&g_spriteDesc);
    g_spriteDesc.z = 0.95f;
    g_spriteDesc.x = g_61b740->faders[7].x - 8.0f;
    g_spriteDesc.y = g_61b740->faders[7].y + 8.8f;
    g_spriteDesc.u0 = (float)(g_4852c8[8].u * 1024.0f) * 0.00390625f;
    g_spriteDesc.v0 = (float)(g_4852c8[8].v * 1024.0f) * 0.00390625f;
    g_spriteDesc.u1 = (float)((g_4852c8[8].width + g_4852c8[8].u) * 1024.0f) * 0.00390625f;
    g_spriteDesc.v1 = (float)((g_4852c8[8].height + g_4852c8[8].v) * 1024.0f) * 0.00390625f;
    g_spriteDesc.width = g_4852c8[8].width * 0.8f;
    g_spriteDesc.height = g_4852c8[8].height * 0.8f;
    FUN_432e00(&g_spriteDesc);
}

// GLOBAL: STUNTGP_D3D 0x4853a0
HudSprite g_4853a0[12] = {
    {0, 0, 0, 0, 71, 88},
    {73, 0, 0, 0, 71, 88},
    {146, 0, 0, 0, 71, 88},
    {0, 185, 8, 11, 44, 70},
    {44, 185, 12, 11, 39, 70},
    {83, 185, 7, 11, 45, 70},
    {128, 185, 12, 11, 38, 70},
    {167, 185, 6, 11, 46, 70},
    {224, 0, 0, 0, 29, 26},
    {155, 88, 56, 8, 44, 41},
    {201, 88, 56, 8, 44, 41},
    {155, 130, 56, 8, 44, 41},
};

// Draws place badge index; the first three get a medal, the rest a plain tag.
// FUNCTION: STUNTGP_D3D 0x4487d0
void FUN_4487d0(unsigned int index, float x, float y, float z)
{
    HudSprite *sprite = &g_4853a0[index];
    g_spriteDesc.flags = 2;
    g_spriteDesc.z = z;
    g_spriteDesc.texture = 14;
    g_spriteDesc.blendMode = 0x20;
    g_spriteDesc.x = sprite->x + x;
    g_spriteDesc.y = sprite->y + y;
    g_spriteDesc.u0 = (float)(sprite->u * 1024.0f) * 0.00390625f;
    g_spriteDesc.v0 = (float)(sprite->v * 1024.0f) * 0.00390625f;
    g_spriteDesc.u1 = (float)(sprite->width * 1024.0f) * 0.00390625f + g_spriteDesc.u0;
    g_spriteDesc.v1 = (float)(sprite->height * 1024.0f) * 0.00390625f + g_spriteDesc.v0;
    g_spriteDesc.width = sprite->width * 0.8f;
    g_spriteDesc.height = sprite->height * 0.8f;
    FUN_432e00(&g_spriteDesc);
    if (index < 3)
    {
        HudSprite *medal = &g_4853a0[index + 9];
        g_spriteDesc.z = z;
        g_spriteDesc.x = (float)medal->x + sprite->x + x;
        g_spriteDesc.y = (float)medal->y + sprite->y + y;
        g_spriteDesc.u0 = (float)(medal->u * 1024.0f) * 0.00390625f;
        g_spriteDesc.v0 = (float)(medal->v * 1024.0f) * 0.00390625f;
        g_spriteDesc.u1 = (float)(medal->width * 1024.0f) * 0.00390625f + g_spriteDesc.u0;
        g_spriteDesc.v1 = (float)(medal->height * 1024.0f) * 0.00390625f + g_spriteDesc.v0;
        g_spriteDesc.width = medal->width * 0.8f;
        g_spriteDesc.height = medal->height * 0.8f;
    }
    else
    {
        g_spriteDesc.texture = 14;
        g_spriteDesc.z = z;
        g_spriteDesc.x = x + 44.0f;
        g_spriteDesc.y = y + 10.0f;
        g_spriteDesc.u0 = (float)(g_4853a0[8].u * 1024.0f) * 0.00390625f;
        g_spriteDesc.v0 = (float)(g_4853a0[8].v * 1024.0f) * 0.00390625f;
        g_spriteDesc.u1 = (float)(g_4853a0[8].width * 1024.0f) * 0.00390625f + g_spriteDesc.u0;
        g_spriteDesc.v1 = (float)(g_4853a0[8].height * 1024.0f) * 0.00390625f + g_spriteDesc.v0;
        g_spriteDesc.width = g_4853a0[8].width * 0.8f;
        g_spriteDesc.height = g_4853a0[8].height * 0.8f;
    }
    g_spriteDesc.blendMode = 0x20;
    FUN_432e00(&g_spriteDesc);
}
