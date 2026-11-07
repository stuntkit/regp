#include "GameUpdate.h"

#include <cstring>
#include <float.h>

#include "../../globals.h"
#include "../../sound.h"
#include "io_wad.h"
#include "../../surface.h"
#include "../../timer.h"

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

// Entry 0 is the fallback zone; the list ends at id -1.
// GLOBAL: STUNTGP_D3D 0x483f98
SoundZone g_483f98[32] = {
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

void FUN_41af50();
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

// STUB: STUNTGP_D3D 0x40dad0
void FUN_40dad0()
{
}

// STUB: STUNTGP_D3D 0x40dd30
void FUN_40dd30()
{
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

// STUB: STUNTGP_D3D 0x415df0
void FUN_415df0()
{
}

// STUB: STUNTGP_D3D 0x40e340
void FUN_40e340()
{
}

// STUB: STUNTGP_D3D 0x418830
void FUN_418830()
{
}

// STUB: STUNTGP_D3D 0x418970
void FUN_418970()
{
}

// STUB: STUNTGP_D3D 0x4189e0
void FUN_4189e0()
{
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

// STUB: STUNTGP_D3D 0x41af50
void FUN_41af50()
{
}

// STUB: STUNTGP_D3D 0x41e2d0
void FUN_41e2d0()
{
}

// STUB: STUNTGP_D3D 0x4278a0
int FUN_4278a0(float *bounds, float *point)
{
    return 0;
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

void FUN_443100();
void FUN_443630();
void FUN_443780();
void FUN_443890();
void FUN_443950();
void FUN_443980();
void FUN_443e20();
void FUN_444390();
void FUN_444410();
void FUN_4446d0();
void FUN_444ae0();
void FUN_444c00();
void FUN_444c50();
void FUN_40e360(Car *sub);
void FUN_40e380(Car *sub);

// GLOBAL: STUNTGP_D3D 0x474630
Car *g_474630;

// GLOBAL: STUNTGP_D3D 0x60df98
int g_60df98;

// GLOBAL: STUNTGP_D3D 0x60f010
float g_60f010;

// GLOBAL: STUNTGP_D3D 0x60f2b0
DWORD g_60f2b0;

// GLOBAL: STUNTGP_D3D 0x60f2c8
int g_60f2c8;

// GLOBAL: STUNTGP_D3D 0x60f2cc
int g_60f2cc;

// STUB: STUNTGP_D3D 0x443100
void FUN_443100()
{
}

// STUB: STUNTGP_D3D 0x443630
void FUN_443630()
{
}

// STUB: STUNTGP_D3D 0x443780
void FUN_443780()
{
}

// STUB: STUNTGP_D3D 0x443890
void FUN_443890()
{
}

// STUB: STUNTGP_D3D 0x443950
void FUN_443950()
{
}

// STUB: STUNTGP_D3D 0x443980
void FUN_443980()
{
}

// STUB: STUNTGP_D3D 0x443e20
void FUN_443e20()
{
}

// STUB: STUNTGP_D3D 0x444390
void FUN_444390()
{
}

// STUB: STUNTGP_D3D 0x444410
void FUN_444410()
{
}

// STUB: STUNTGP_D3D 0x4446d0
void FUN_4446d0()
{
}

// STUB: STUNTGP_D3D 0x444ae0
void FUN_444ae0()
{
}

// STUB: STUNTGP_D3D 0x444c00
void FUN_444c00()
{
}

// STUB: STUNTGP_D3D 0x444c50
void FUN_444c50()
{
}

// FUNCTION: STUNTGP_D3D 0x4439f0
void FUN_4439f0()
{
    g_60f2c4 = 0;
    switch (g_60df98)
    {
    case 2:
    case 5:
        FUN_443950();
        break;
    case 4:
        FUN_443100();
        break;
    case 3:
        FUN_443980();
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x443a30
void FUN_443a30()
{
    if (g_60f2cc != 480)
    {
        if (g_60f010 * g_4d5bb8->unk23b0 * 0.01f > g_60f010 - 30000.0f)
        {
            g_60f2cc = 480;
            FUN_444c00();
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x443a80
void FUN_443a80()
{
    if (g_60f2c8)
    {
        if (--g_60f2c8 <= 0)
        {
            FUN_4439f0();
            g_60f2c8 = 0;
        }
    }
    FUN_443780();
    switch (g_60f2b0)
    {
    case 2:
    case 5:
    {
        for (int i = 0; i < 4; i++)
        {
            GameSlot *slot = &g_498248[i];
            if (slot->active == 1)
            {
                g_4722d0 = slot;
                g_4d5bb8 = (Car *)slot->data;
                g_61b740 = &slot->fx;
                FUN_443e20();
                FUN_4446d0();
                FUN_444c50();
                FUN_444ae0();
                FUN_444410();
                FUN_444390();
            }
        }
        g_4722d0 = g_498248;
        break;
    }
    case 3:
        g_4d5bb8 = g_474630 = (Car *)g_4722d0->data;
        FUN_443890();
        FUN_444c50();
        FUN_444ae0();
        FUN_4446d0();
        FUN_40e360((Car *)g_4722d0->data);
        FUN_40e380((Car *)g_4722d0->data);
        break;
    case 4:
        g_4d5bb8 = g_474630 = (Car *)g_4722d0->data;
        FUN_443630();
        FUN_443e20();
        FUN_444c50();
        FUN_443a30();
        FUN_40e360((Car *)g_4722d0->data);
        FUN_40e380((Car *)g_4722d0->data);
        break;
    }
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

extern float g_482678;
extern float g_48267c;
extern float g_482680;

// FUNCTION: STUNTGP_D3D 0x401d70
void FUN_401d70(float *v, float scale)
{
    if (v[0] * v[0] + v[1] * v[1] + v[2] * v[2] <= 27777.777f)
    {
        float g[4];
        g[0] = g_482678 * scale;
        g[1] = g_48267c * scale;
        g[2] = g_482680 * scale;
        v[0] += g[0];
        v[1] += g[1];
        v[2] += g[2];
    }
}

// FUNCTION: STUNTGP_D3D 0x422620
DWORD Color_Lerp(DWORD from, DWORD to, int t)
{
    int fromG = (BYTE)(from >> 8);
    int fromR = (BYTE)(from >> 16);
    int toR = (BYTE)(to >> 16);
    int fromB = (BYTE)from;
    return ((fromR + ((toR - fromR) * t >> 8)) << 16) |
           ((fromG + (((BYTE)(to >> 8) - fromG) * t >> 8)) << 8) | (fromB + (((BYTE)to - fromB) * t >> 8));
}

// FUNCTION: STUNTGP_D3D 0x45e170
void FUN_45e170(Unk62a078 *p)
{
    p->unk00 = 2;
}

// FUNCTION: STUNTGP_D3D 0x45e180
void FUN_45e180(Unk62a078 *p)
{
    DWORD *anim = p->anim;
    if (anim)
    {
        int frame = p->frame;
        p->frame += 0x6aa;
        if ((DWORD)(frame / 4096) >= anim[2] - 1)
        {
            p->frame = 0;
            if (p->mode == 1)
            {
                FUN_45e170(p);
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45e1d0
void FUN_45e1d0()
{
    if (g_62d478)
    {
        g_62d478 = 0;
        Unk62a078 *p = g_62a078;
        for (int i = 0; i < 0x40; i++, p++)
        {
            if (p->unk00 == 1)
            {
                g_62d478 = 1;
                p->pos[0] = p->vel[0] + p->pos[0];
                p->pos[1] = p->vel[1] + p->pos[1];
                p->pos[2] = p->vel[2] + p->pos[2];
                if (p->vel[1] < 166.66667f)
                {
                    FUN_401d70(p->vel, p->gravity);
                }
                if (p->flags & 2)
                {
                    if ((float)p->time < p->alphaIn)
                    {
                        p->alphaNow = (float)p->time * p->alpha / p->alphaIn;
                    }
                    else if ((float)p->time > (float)p->lifetime - p->alphaOut)
                    {
                        p->alphaNow = (float)(p->lifetime - p->time) * p->alpha / p->alphaOut;
                    }
                    else
                    {
                        p->alphaNow = p->alpha;
                    }
                }
                else
                {
                    p->alphaNow = p->alpha;
                }
                if (p->flags & 1)
                {
                    if ((float)p->time < p->sizeIn)
                    {
                        p->sizeNow = (float)p->time * p->size / p->sizeIn;
                    }
                    else if ((float)p->time > (float)p->lifetime - p->sizeOut)
                    {
                        p->sizeNow = (float)(p->lifetime - p->time) * p->size / p->sizeOut;
                    }
                    else
                    {
                        p->sizeNow = p->size;
                    }
                }
                else
                {
                    p->sizeNow = p->size;
                }
                if (p->flags & 4)
                {
                    float angle = p->spin + p->angle;
                    p->angle = angle;
                    if (angle >= 360.0f)
                    {
                        p->angle = angle - 360.0f;
                    }
                    else if (angle < 0.0f)
                    {
                        p->angle = angle + 360.0f;
                    }
                }
                if (p->flags & 8)
                {
                    if ((float)p->time < p->colorIn)
                    {
                        p->color = Color_Lerp(p->colors[0], p->colors[1], (int)((float)p->time * 255.0f / p->colorIn));
                    }
                    else if ((float)p->time > (float)p->lifetime - p->colorOut)
                    {
                        p->color = Color_Lerp(
                            p->colors[1], p->colors[2],
                            (int)(255.0f - (float)(p->lifetime - p->time) * 255.0f / p->colorOut)
                        );
                    }
                    else
                    {
                        p->color = p->colors[1];
                    }
                }
                else
                {
                    p->color = p->colors[0];
                }
                if (p->mode == 2)
                {
                    if (++p->time >= p->lifetime)
                    {
                        FUN_45e170(p);
                    }
                }
                FUN_45e180(p);
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45f8f0
void FUN_45f8f0(int track, int loop)
{
    char path[256];
    if (g_soundInitialised && g_musicVolume)
    {
        int t;
        if (track == 0 && g_62f5a8 != 0)
        {
            t = g_62f5a8;
        }
        else
        {
            t = track;
        }
        g_62e10c = t;
        if (t)
        {
            // STRING: STUNTGP_D3D 0x48a500
            sprintf(path, "%s\\Music\\%s.wav", g_SoundDirectory, g_4898fc[t]);
            if (!size_of_file(path))
            {
                g_62f5ac = 0;
                return;
            }
            DWORD flags = 0x24;
            if (loop == 1)
            {
                flags = 0x25;
            }
            FUN_45fb50(g_directSound, path, flags, 0, 0, 0, 0);
            FUN_45f7d0(0, 0);
            g_62e110 = 0;
            g_62e0fc = 0;
            g_62e104 = 0;
            FUN_45f8e0(255, 255);
            g_62f5ac = 1;
        }
    }
}

// --- sound ---


// STUB: STUNTGP_D3D 0x41bdd0
void FUN_41bdd0()
{
}
