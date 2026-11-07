#include "GameUpdate.h"

#include <cstring>
#include <stdio.h>
#include <float.h>

#include "../../gametext.h"
#include "../../globals.h"
#include "../../random.h"
#include "../../surface.h"
#include "../../timer.h"
#include "../../vecmath.h"

// GLOBAL: STUNTGP_D3D 0x60d618
int g_60d618;

// GLOBAL: STUNTGP_D3D 0x60d620
int g_60d620;

// GLOBAL: STUNTGP_D3D 0x60df9c
int g_60df9c;

// GLOBAL: STUNTGP_D3D 0x60f2c0
int g_60f2c0;

// GLOBAL: STUNTGP_D3D 0x60f2c4
DWORD g_60f2c4;

// GLOBAL: STUNTGP_D3D 0x61294c
int g_61294c;

// GLOBAL: STUNTGP_D3D 0x612954
DWORD g_612954;

struct SoundZone
{
    int id;           // 0x00
    int unk04;        // 0x04
    float bounds[16]; // 0x08
};

// Entry 0 is the fallback zone; the list ends at id -1.
// GLOBAL: STUNTGP_D3D 0x483f98
SoundZone g_483f98[2] = {
    {0, 0, {1000.0f, 1000.0f, 1000.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f}},
    {-1},
};

// GLOBAL: STUNTGP_D3D 0x484898
SoundZone *g_484898 = g_483f98;

// GLOBAL: STUNTGP_D3D 0x61b740
SlotFx *g_61b740;

int FUN_4278a0(float *bounds, float *point);

// GLOBAL: STUNTGP_D3D 0x473a24
int g_473a24 = 720;

// GLOBAL: STUNTGP_D3D 0x473a28
float g_473a28 = -5.0f;

// GLOBAL: STUNTGP_D3D 0x4d5b18
float g_4d5b18;

// GLOBAL: STUNTGP_D3D 0x4d5b1c
int g_4d5b1c;

// GLOBAL: STUNTGP_D3D 0x612990
int g_612990;

// GLOBAL: STUNTGP_D3D 0x61299c
int g_61299c;

void FUN_441e20();

struct AnimObject
{
    int type;         // 0x00
    float rotX;       // 0x04
    float rotY;       // 0x08
    float rotZ;       // 0x0c
    int unk10;        // 0x10
    float spinX;      // 0x14
    float spinY;      // 0x18
    float spinZ;      // 0x1c
    BYTE unk20[0x18]; // 0x20
    int angleA;       // 0x38
    int angleB;       // 0x3c
    BYTE unk40[0x8];  // 0x40
};

struct ObjectDef
{
    BYTE unk00[0x40]; // 0x00
};

struct Scene
{
    BYTE unk00[0x24];   // 0x00
    DWORD objectCount;  // 0x24
    BYTE unk28[0x20];   // 0x28
    ObjectDef *objects; // 0x48
};

// GLOBAL: STUNTGP_D3D 0x576cd0
AnimObject g_576cd0[32];

// GLOBAL: STUNTGP_D3D 0x636448
Scene *g_636448;

// 6 entries at 0x49a1f8, 0x7724 bytes each
// GLOBAL: STUNTGP_D3D 0x49a1f8
Car g_49a1f8[6];

// GLOBAL: STUNTGP_D3D 0x4d5bb8
Car *g_4d5bb8;

// GLOBAL: STUNTGP_D3D 0x60f050
char g_60f050[6][100];

// GLOBAL: STUNTGP_D3D 0x60f2b0
DWORD g_60f2b0;

// GLOBAL: STUNTGP_D3D 0x612d10
unsigned int g_612d10;

// GLOBAL: STUNTGP_D3D 0x612d14
Car *g_612d14[6];

// GLOBAL: STUNTGP_D3D 0x474630
Car *g_474630 = g_49a1f8;

void FUN_41af50();
void FUN_418830();
void FUN_41e2d0();

// --- per-tick game logic ---

// STUB: STUNTGP_D3D 0x401770
void FUN_401770()
{
}

// FUNCTION: STUNTGP_D3D 0x4023f0
void FUN_4023f0()
{
    GameSlot *slot = g_4722d0;
    slot->unk0d8 = 0;
    slot->unk0dc = 0;
    slot->unk0e0 = 0;
    slot->unk104 = 0;
    slot->unk108 = 0;
    slot->unk10c = 0;
}

// STUB: STUNTGP_D3D 0x402950
void FUN_402950()
{
}

// STUB: STUNTGP_D3D 0x402a80
void FUN_402a80()
{
}

// STUB: STUNTGP_D3D 0x402f60
void FUN_402f60()
{
}

// STUB: STUNTGP_D3D 0x403080
void FUN_403080()
{
}

// STUB: STUNTGP_D3D 0x4039b0
void FUN_4039b0()
{
}

// STUB: STUNTGP_D3D 0x404450
void FUN_404450()
{
}

// FUNCTION: STUNTGP_D3D 0x405210
void FUN_405210()
{
    for (int i = 0; i < 4; i++)
    {
        g_4722d0 = &g_498248[i];
        if (g_498248[i].active == 1)
        {
            FUN_402950();
            FUN_4039b0();
            FUN_402a80();
            FUN_404450();
            FUN_403080();
            FUN_402f60();
        }
    }
    g_4722d0 = g_498248;
}

// Picks a random active car, giving up after 16 tries.
// FUNCTION: STUNTGP_D3D 0x40dd30
void FUN_40dd30()
{
    for (unsigned int i = 0; i < 16; i++)
    {
        int index = FUN_42f1f0(1024) % 6;
        if (g_49a1f8[index].active == 1)
        {
            g_474630 = &g_49a1f8[index];
            i = 16;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x40dd80
void FUN_40dd80()
{
    if (g_612994 != 1)
    {
        g_612994 = 1;
        g_473a24 = 720;
        g_4d5b18 = 0.0f;
        g_473a28 = -5.0f;
        g_4d5b1c = 0;
        FUN_40dd30();
    }
}

// FUNCTION: STUNTGP_D3D 0x40ddd0
void FUN_40ddd0()
{
    FUN_40dd80();
    FUN_447b60();
    if (g_473a24 > 0)
    {
        g_473a24--;
        return;
    }
    g_473a28 -= 0.35f;
    g_4d5b18 += g_473a28;
    if (g_4d5b18 < 0.0f)
    {
        g_4d5b18 = 0.0f;
        g_473a28 = 5.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x40de30
void FUN_40de30()
{
    if (g_61299c == 1)
    {
        g_60f2c0 = 1;
        FUN_40ddd0();
        if (--g_612990 == 0 || g_612968 == 1)
        {
            g_612994 = 0;
            g_61299c = 0;
            g_612990 = 0;
            FUN_441e20();
        }
    }
}

// STUB: STUNTGP_D3D 0x410a10
void FUN_410a10(int index)
{
}

// STUB: STUNTGP_D3D 0x415df0
void FUN_415df0()
{
}

// FUNCTION: STUNTGP_D3D 0x40e340
void FUN_40e340()
{
    for (int i = 0; i < 6; i++)
    {
        g_49a1f8[i].unk1fd0 = 1.0f;
    }
}

// STUB: STUNTGP_D3D 0x418970
void FUN_418970()
{
}

// STUB: STUNTGP_D3D 0x409b60
void FUN_409b60(int a)
{
}

// Flags cars that have fallen off or left the world.
// FUNCTION: STUNTGP_D3D 0x4189e0
void FUN_4189e0()
{
    g_4d5bb8 = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        if (g_4d5bb8->active == 1 && !(g_4d5bb8->unk7268 && *g_4d5bb8->unk7268 == 1))
        {
            if (g_4d5bb8->unk1bb0 < -5000.0f || g_4d5bb8->unk1bb0 > 60000.0f ||
                (g_60f2b0 == 3 && g_4d5bb8->unk1bb0 < 160.0f))
            {
                g_4d5bb8->unk763c = 1;
                g_4d5bb8->unk7638 = 0;
            }
            FUN_409b60(0);
        }
        g_4d5bb8++;
    }
}

// FUNCTION: STUNTGP_D3D 0x418a90
void FUN_418a90()
{
    g_4d5bb8 = g_49a1f8;
    FUN_4189e0();
    FUN_40e340();
    g_4d5bb8 = g_49a1f8;
    for (int i = 0; i < 6; i++)
    {
        if (g_4d5bb8->active == 1)
        {
            FUN_41af50();
            if (g_4d5bb8->unk7268 && *g_4d5bb8->unk7268 == 1)
            {
                FUN_418970();
            }
            else
            {
                FUN_418830();
            }
        }
        g_4d5bb8++;
    }
    FUN_41e2d0();
    g_4d5bb8 = g_49a1f8;
}

// STUB: STUNTGP_D3D 0x41ab70
void FUN_41ab70(Car *car)
{
}

// FUNCTION: STUNTGP_D3D 0x41af50
void FUN_41af50()
{
    if (g_4d5bb8->unk7268)
    {
        switch (*g_4d5bb8->unk7268)
        {
        case 1:
            FUN_41ab70(g_4d5bb8);
            break;
        }
    }
}

// STUB: STUNTGP_D3D 0x442cf0
void FUN_442cf0(int a, char *text, Car *car, int b, int c)
{
}

// Sorts the active cars into race order and announces a new leader.
// FUNCTION: STUNTGP_D3D 0x41e2d0
void FUN_41e2d0()
{
    char text[32];
    unsigned int i;
    unsigned int j;
    memset(g_612d14, 0, sizeof(g_612d14));
    unsigned int count = 0;
    for (i = 0; i < 6; i++)
    {
        if (g_49a1f8[i].active == 1)
        {
            g_612d14[count] = &g_49a1f8[i];
            count++;
        }
    }
    g_612d10 = count;
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            if (g_612d14[i]->unk23b0 > g_612d14[j]->unk23b0)
            {
                Car *t = g_612d14[j];
                g_612d14[j] = g_612d14[i];
                g_612d14[i] = t;
            }
        }
    }
    for (i = 0; i < count; i++)
    {
        if (i == 0 && g_612d14[0]->unk24ac)
        {
            int index = g_612d14[0] - g_49a1f8;
            // STRING: STUNTGP_D3D 0x474924
            sprintf(text, "%s %s", g_60f050[index], g_6127a0[24]);
            FUN_442cf0(180, text, &g_49a1f8[index], 1, 100);
        }
        g_612d14[i]->unk24ac = i;
    }
}

// GLOBAL: STUNTGP_D3D 0x477658
float g_477658[6][4] = {
    {-1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, -1.0f, 0.0f},
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, -1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
};

// GLOBAL: STUNTGP_D3D 0x4776d8
float g_4776d8[8][4] = {
    {-0.5f, 0.5f, -0.5f, 0.0f},
    {0.5f, 0.5f, -0.5f, 0.0f},
    {0.5f, -0.5f, -0.5f, 0.0f},
    {-0.5f, -0.5f, -0.5f, 0.0f},
    {-0.5f, 0.5f, 0.5f, 0.0f},
    {0.5f, 0.5f, 0.5f, 0.0f},
    {0.5f, -0.5f, 0.5f, 0.0f},
    {-0.5f, -0.5f, 0.5f, 0.0f},
};

// Point-in-oriented-box test. bounds: centre (0), size (4), two axes (8, 12).
// FUNCTION: STUNTGP_D3D 0x4278a0
int FUN_4278a0(float *bounds, float *point)
{
    float m[16];
    float t[16];
    float v[4];
    float e[4];
    float d;
    v[0] = bounds[9] * bounds[14] - bounds[13] * bounds[10];
    v[1] = bounds[12] * bounds[10] - bounds[8] * bounds[14];
    v[2] = bounds[13] * bounds[8] - bounds[12] * bounds[9];
    Matrix_FromRows(v, &bounds[8], &bounds[12], m);
    Matrix_Transpose(t, m);
    float dx = point[0] - bounds[0];
    float dy = point[1] - bounds[1];
    float dz = point[2] - bounds[2];
    v[0] = t[8] * dz + t[4] * dy + t[0] * dx + t[12];
    v[1] = t[9] * dz + t[5] * dy + t[1] * dx + t[13];
    v[2] = t[10] * dz + t[6] * dy + t[2] * dx + t[14];
    v[0] += bounds[0];
    v[1] += bounds[1];
    v[2] += bounds[2];

    e[0] = g_4776d8[0][0] * bounds[4];
    e[1] = g_4776d8[0][1] * bounds[5];
    e[2] = g_4776d8[0][2] * bounds[6];
    e[0] += bounds[0];
    e[1] += bounds[1];
    e[2] += bounds[2];
    e[0] = v[0] - e[0];
    e[1] = v[1] - e[1];
    e[2] = v[2] - e[2];
    d = g_477658[0][2] * e[2] + g_477658[0][1] * e[1] + g_477658[0][0] * e[0];
    if (*(int *)&d >= 0)
    {
        return 0;
    }
    d = g_477658[1][2] * e[2] + g_477658[1][1] * e[1] + g_477658[1][0] * e[0];
    if (*(int *)&d >= 0)
    {
        return 0;
    }
    d = g_477658[2][2] * e[2] + g_477658[2][1] * e[1] + g_477658[2][0] * e[0];
    if (*(int *)&d >= 0)
    {
        return 0;
    }

    e[0] = g_4776d8[6][0] * bounds[4];
    e[1] = g_4776d8[6][1] * bounds[5];
    e[2] = g_4776d8[6][2] * bounds[6];
    e[0] += bounds[0];
    e[1] += bounds[1];
    e[2] += bounds[2];
    e[0] = v[0] - e[0];
    e[1] = v[1] - e[1];
    e[2] = v[2] - e[2];
    d = g_477658[3][2] * e[2] + g_477658[3][1] * e[1] + g_477658[3][0] * e[0];
    if (*(int *)&d >= 0)
    {
        return 0;
    }
    d = g_477658[4][2] * e[2] + g_477658[4][1] * e[1] + g_477658[4][0] * e[0];
    if (*(int *)&d >= 0)
    {
        return 0;
    }
    d = g_477658[5][2] * e[2] + g_477658[5][1] * e[1] + g_477658[5][0] * e[0];
    return *(int *)&d < 0;
}

// FUNCTION: STUNTGP_D3D 0x427010
void FUN_427010(AnimObject *obj)
{
    obj->angleA = (obj->angleA + 0x80) & 0x1fff;
}

// FUNCTION: STUNTGP_D3D 0x427030
void FUN_427030(AnimObject *obj, int step)
{
    obj->angleA = (obj->angleA - step) & 0x1fff;
}

// FUNCTION: STUNTGP_D3D 0x427040
void FUN_427040(AnimObject *obj, int step)
{
    obj->angleB = (obj->angleB - step) & 0x1fff;
}

// FUNCTION: STUNTGP_D3D 0x427050
void FUN_427050(AnimObject *obj, ObjectDef *def)
{
    // four lanes to match the original frame layout; w is never used
    float delta[4];
    float x;
    float y;
    float z;
    delta[0] = obj->spinX * (1.0f / 60.0f);
    delta[1] = obj->spinY * (1.0f / 60.0f);
    delta[2] = obj->spinZ * (1.0f / 60.0f);
    obj->rotX = x = obj->rotX + delta[0];
    obj->rotY = y = obj->rotY + delta[1];
    obj->rotZ = z = obj->rotZ + delta[2];
    if (x < 0.0f)
    {
        obj->rotX = x + 360.0f;
    }
    else if (x > 360.0f)
    {
        obj->rotX = x - 360.0f;
    }
    if (y < 0.0f)
    {
        obj->rotY = y + 360.0f;
    }
    else if (y > 360.0f)
    {
        obj->rotY = y - 360.0f;
    }
    if (z < 0.0f)
    {
        obj->rotZ = z + 360.0f;
    }
    else if (z > 360.0f)
    {
        obj->rotZ = z - 360.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x427140
void FUN_427140()
{
    if (g_636448 && g_636448->objectCount > 1)
    {
        ObjectDef *def = g_636448->objects;
        AnimObject *obj = g_576cd0;
        DWORD count = g_636448->objectCount;
        for (DWORD i = 1; i < count; i++)
        {
            obj++;
            def++;
            switch (obj->type)
            {
            case 1:
                FUN_427010(obj);
                break;
            case 3:
                FUN_427030(obj, -0x100);
                break;
            case 4:
                FUN_427050(obj, def);
                break;
            case 16:
                FUN_427050(obj, def);
                FUN_427030(obj, 0x80);
                FUN_427040(obj, 0x2a);
                break;
            case 2:
            case 8:
            case 9:
                FUN_427030(obj, 0x100);
                break;
            case 5:
            case 6:
            case 10:
                FUN_427030(obj, 0x40);
                break;
            case 11:
                FUN_427030(obj, 0x80);
                break;
            case 12:
                FUN_427030(obj, 8);
                break;
            case 13:
                FUN_427030(obj, 0x10);
                break;
            case 7:
            case 14:
                FUN_427030(obj, 0x20);
                break;
            }
        }
    }
}

// --- fpu ---

// FUNCTION: STUNTGP_D3D 0x4294f0
void FUN_4294f0()
{
    _control87(_PC_53, _MCW_PC);
    _control87(_RC_NEAR, _MCW_RC);
}

// FUNCTION: STUNTGP_D3D 0x429510
void FUN_429510()
{
    FUN_4294f0();
}

// FUNCTION: STUNTGP_D3D 0x431810
void FUN_431810()
{
    FUN_431790();
}

// --- timer ---

// STUB: STUNTGP_D3D 0x443a80
void FUN_443a80()
{
}

// FUNCTION: STUNTGP_D3D 0x442de0
void FUN_442de0()
{
    GameSlot *slot = g_498248;
    for (int i = 0; i < 4; i++, slot++)
    {
        if (slot->active == 1)
        {
            SlotEvent *oldest = NULL;
            SlotEvent *event = slot->events;
            for (int j = 0; j < 8; j++, event++)
            {
                if (event->count != 0)
                {
                    if (oldest == NULL || oldest->order > event->order)
                    {
                        oldest = event;
                    }
                }
            }
            if (oldest != NULL)
            {
                oldest->count--;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x446110
void FUN_446110()
{
    SoundZone *found = &g_483f98[0];
    int searching = 1;
    for (SoundZone *zone = &g_483f98[1]; zone->id != -1 && searching == 1; zone++)
    {
        if (FUN_4278a0(zone->bounds, &g_4722d0->unk008) == 1)
        {
            found = zone;
            searching = 0;
        }
    }
    if (found != g_484898 && found->id >= 0 && found->id <= 6)
    {
        FUN_460af0(found->id);
        g_484898 = found;
    }
}

// FUNCTION: STUNTGP_D3D 0x447ab0
void FUN_447ab0(Fader *fader)
{
    if (fader->active)
    {
        if (fader->value < fader->target)
        {
            float step = (100.0f - (fader->target - fader->value)) * 0.0625f;
            if (step < 0.1f)
            {
                step = 0.1f;
            }
            fader->value += step;
            if (fader->value > fader->target)
            {
                fader->active = 0;
                fader->value = fader->target;
            }
        }
        else
        {
            float step = (fader->value - fader->target) * 0.0625f;
            if (step < 0.1f)
            {
                step = 0.1f;
            }
            fader->value -= step;
            if (fader->value < fader->target)
            {
                fader->value = fader->target;
                fader->active = 0;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x447b60
void FUN_447b60()
{
    g_61b740->unk000 = 0;
}

// FUNCTION: STUNTGP_D3D 0x447b70
void FUN_447b70(int delay)
{
    g_61b740 = &g_4722d0->fx;
    g_61b740->delay = delay;
    g_61b740->faders[0].active = 1;
    g_61b740->faders[0].value = 100.0f;
    g_61b740->faders[0].target = 0.0f;
}

// FUNCTION: STUNTGP_D3D 0x447ba0
void FUN_447ba0(int delay)
{
    g_61b740 = &g_4722d0->fx;
    g_61b740->delay = delay;
    g_61b740->faders[0].active = 1;
    g_61b740->faders[0].value = 0.0f;
    g_61b740->faders[0].target = 100.0f;
}

// FUNCTION: STUNTGP_D3D 0x447bd0
void FUN_447bd0(int delay)
{
    GameSlot *saved = g_4722d0;
    g_4722d0 = g_498248;
    for (int i = 0; i < 4; i++)
    {
        if (!g_4722d0->data->unk24e0)
        {
            FUN_447b70(delay);
        }
        g_4722d0++;
    }
    g_4722d0 = saved;
}

// FUNCTION: STUNTGP_D3D 0x447c30
void FUN_447c30(int delay)
{
    GameSlot *saved = g_4722d0;
    g_4722d0 = g_498248;
    for (int i = 0; i < 4; i++)
    {
        if (!g_4722d0->data->unk24e0)
        {
            FUN_447ba0(delay);
        }
        g_4722d0++;
    }
    g_4722d0 = saved;
}

// FUNCTION: STUNTGP_D3D 0x447c90
void FUN_447c90()
{
    for (int i = 0; i < 4; i++)
    {
        if (g_498248[i].active == 1)
        {
            g_4722d0 = &g_498248[i];
            g_61b740 = &g_4722d0->fx;
            if (g_4722d0->data->unk23c4 != -1)
            {
                FUN_447ab0(&g_61b740->faders[3]);
                FUN_447ab0(&g_61b740->faders[4]);
                FUN_447ab0(&g_61b740->faders[5]);
            }
            if (g_4722d0->data->unk7648 == 1)
            {
                FUN_447ab0(&g_61b740->faders[6]);
            }
            if (g_61b740->faders[0].active == 1)
            {
                if (g_61b740->delay)
                {
                    g_61b740->delay--;
                }
                else
                {
                    FUN_447ab0(&g_61b740->faders[0]);
                }
            }
            if (g_61b740->faders[8].active == 1)
            {
                FUN_447ab0(&g_61b740->faders[8]);
            }
        }
    }
    g_4722d0 = g_498248;
    FUN_442de0();
}

// STUB: STUNTGP_D3D 0x45e1d0
void FUN_45e1d0()
{
}

// STUB: STUNTGP_D3D 0x45f8f0
void FUN_45f8f0(int a, int b)
{
}

// --- sound ---


// FUNCTION: STUNTGP_D3D 0x41bdd0
void FUN_41bdd0()
{
    FUN_460dd0();
    for (int i = 0; i < 6; i++)
    {
        if (g_49a1f8[i].active == 1)
        {
            for (int j = 0; j < 4; j++)
            {
                g_49a1f8[i].unk233c[j] = 0;
                g_49a1f8[i].wheels[j].unk2c = 0;
            }
            g_49a1f8[i].unk234c = 0;
            g_49a1f8[i].unk2350 = 0;
            g_49a1f8[i].unk2354 = 0;
            g_49a1f8[i].unk2358 = 0;
            g_49a1f8[i].unk235c = 0;
            g_49a1f8[i].unk2360 = 0;
            g_49a1f8[i].unk2364 = 0;
            g_49a1f8[i].unk2368 = 0;
            g_49a1f8[i].unk236c = 0;
            g_49a1f8[i].unk2370 = 0;
            g_49a1f8[i].unk2374 = 0;
            g_49a1f8[i].unk2378 = 0;
            g_49a1f8[i].unk237c = 0;
            g_49a1f8[i].unk2380 = 0;
            g_49a1f8[i].unk2384 = 0;
            g_49a1f8[i].unk2388 = 0;
            g_49a1f8[i].unk238c = 0;
            g_49a1f8[i].unk2390 = 0;
            g_49a1f8[i].unk2394 = 0;
            g_49a1f8[i].unk2398 = 0;
            g_49a1f8[i].unk239c = 0;
            g_49a1f8[i].unk23a0 = 0;
        }
    }
}
