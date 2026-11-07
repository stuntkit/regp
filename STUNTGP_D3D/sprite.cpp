#include "sprite.h"
#include "d3drender.h"
#include "font.h"

#include <string.h>

#include "common.h"
#include "globals.h"
#include "mem.h"
#include "surface.h"
#include "windowInit.h"

extern int g_61b634;

// GLOBAL: STUNTGP_D3D 0x576c38
SpriteDesc g_spriteDesc;

// GLOBAL: STUNTGP_D3D 0x5da370
int g_5da370 = 0;

// Sprite lists bucketed by depth, drawn back to front by FUN_437ed0.
// GLOBAL: STUNTGP_D3D 0x5df194
SpriteLists g_spriteLists;

// Integer sprite clip rectangle set by FUN_438190.
// GLOBAL: STUNTGP_D3D 0x5da360
int g_5da360[4];

// GLOBAL: STUNTGP_D3D 0x47f318
SpriteFile g_47f318[1];

// GLOBAL: STUNTGP_D3D 0x608d88
SpriteDef g_spriteDefs[0x183];

// GLOBAL: STUNTGP_D3D 0x5df518
int g_5df518 = 0;

// GLOBAL: STUNTGP_D3D 0x5df51c
int g_5df51c = 0;

// GLOBAL: STUNTGP_D3D 0x5df520
int g_5df520 = 0;

// GLOBAL: STUNTGP_D3D 0x5df524
int g_5df524 = 0;

// GLOBAL: STUNTGP_D3D 0x4793d4
int g_4793d4 = -1;

// FUNCTION: STUNTGP_D3D 0x437e40
void FUN_437e40(char *name)
{
}

// FUNCTION: STUNTGP_D3D 0x437e60
void FUN_437e60()
{
    FUN_437e80();
    FUN_441190();
    FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
}

// FUNCTION: STUNTGP_D3D 0x437e80
void FUN_437e80()
{
    g_5da370 = 0;
    for (int i = 0; i < 80; i++)
    {
        g_spriteLists.tails[i] = NULL;
        g_spriteLists.heads[i] = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x437ec0
void FUN_437ec0()
{
    FUN_437ed0();
    FUN_437e80();
    FUN_441220();
}

// FUNCTION: STUNTGP_D3D 0x437ed0
void FUN_437ed0()
{
    g_5df518 = 0;
    memset(&g_spriteDesc, 0, sizeof(g_spriteDesc));
    g_5df51c = 0;
    g_5df520 = 0;
    g_5df524 = 0;
    g_4793d4 = -1;
    for (int i = 79; i >= 0; i--)
    {
        for (SpriteNode *node = g_spriteLists.heads[i]; node != NULL; node = node->next)
        {
            FUN_437f40(node, i);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x437f40
void FUN_437f40(SpriteNode *node, int depth)
{
    float z = 1.0f - depth * 0.01f;
    switch (node->type)
    {
    case 0:
    {
        FUN_4291a0(node->text.unk18);
        float size = node->text.size;
        int align = 0;
        DWORD flags = FUN_438130(node->text.style, size);
        if (node->text.flags & 1)
        {
            align = 1;
        }
        else if (node->text.flags & 4)
        {
            align = 2;
        }
        if (node->text.flags & 2)
        {
            node->text.y -= FUN_438950(size) * 0.5f;
        }
        else if (node->text.flags & 8)
        {
            node->text.y -= FUN_438950(size);
        }
        if (node->text.flags & 0x800)
        {
            FUN_4291f0(node->text.text, align, node->text.x, node->text.y, z, 0xffffffff, size, flags | 0x10);
            FUN_4291f0(node->text.text, align, node->text.x, node->text.y, z, node->text.color, node->text.size,
                       (flags & ~4) | 8);
        }
        else
        {
            if (node->text.flags & 0x100)
            {
                flags |= 8;
            }
            else if (node->text.flags & 0x200)
            {
                flags |= 0x10;
            }
            FUN_4291f0(node->text.text, align, node->text.x, node->text.y, z, node->text.color, size, flags);
        }
        if (g_4793d4 != 999)
        {
            g_5df518++;
        }
        g_4793d4 = 999;
        g_5df520++;
        break;
    }
    case 1:
    {
        SpriteData *s = &node->sprite;
        if (FUN_441240(s) < 0)
        {
            break;
        }
        int texture = s->texture;
        g_spriteDesc.flags = s->flags;
        g_spriteDesc.x = s->x;
        g_spriteDesc.y = s->y;
        g_spriteDesc.z = z;
        g_spriteDesc.width = s->width;
        g_spriteDesc.height = s->height;
        g_spriteDesc.u0 = s->u0;
        g_spriteDesc.v0 = s->v0;
        g_spriteDesc.u1 = s->u1;
        g_spriteDesc.v1 = s->v1;
        g_spriteDesc.texture = texture;
        g_spriteDesc.blendMode = s->blendMode;
        g_spriteDesc.alpha = s->alpha;
        FUN_432e00(&g_spriteDesc);
        if (g_4793d4 != texture)
        {
            g_5df518++;
        }
        g_4793d4 = texture;
        g_5df524++;
        break;
    }
    }
}

// FUNCTION: STUNTGP_D3D 0x438130
int FUN_438130(int style, float size)
{
    int flags = 0;
    switch (style)
    {
    case 2:
        flags = 2;
        break;
    case 3:
        flags = 4;
        break;
    case 4:
        flags = 6;
        break;
    }
    if (size <= 1.0f)
    {
        Font_Select(0);
        return flags;
    }
    Font_Select(1);
    return flags;
}

// FUNCTION: STUNTGP_D3D 0x438190
void FUN_438190(float left, float top, float right, float bottom)
{
    if (left < 0.0f)
    {
        left = 0.0f;
    }
    if (top < 0.0f)
    {
        top = 0.0f;
    }
    if (right > 640.0f)
    {
        right = 640.0f;
    }
    if (bottom > 480.0f)
    {
        bottom = 480.0f;
    }
    g_5da360[0] = (int)left;
    g_5da360[1] = (int)top;
    g_5da360[2] = (int)right;
    g_5da360[3] = (int)bottom;
}

// FUNCTION: STUNTGP_D3D 0x438950
float FUN_438950(float size)
{
    return size * 16.0f;
}

// FUNCTION: STUNTGP_D3D 0x441220
void FUN_441220()
{
    for (int i = 17; i < 0x25; i++)
    {
        g_608cf0[i]++;
    }
}

// STUB: STUNTGP_D3D 0x43f6b0
void FUN_43f6b0()
{
}

// FUNCTION: STUNTGP_D3D 0x43d250
void FUN_43d250()
{
    FUN_43f6b0();
    FUN_437ec0();
}

// FUNCTION: STUNTGP_D3D 0x441190
void FUN_441190()
{
    for (int i = 0; g_47f318[i].name; i++)
    {
    }
    FUN_441340();
    FUN_4411c0();
}

// FUNCTION: STUNTGP_D3D 0x441340
void FUN_441340()
{
    memset(g_spriteDefs, 0, sizeof(g_spriteDefs));
    for (int i = 1; i < 0x183; i++)
    {
        FUN_441380(&g_spriteDefs[i], i);
    }
}

// STUB: STUNTGP_D3D 0x441380
void FUN_441380(SpriteDef *def, int id)
{
}

// FUNCTION: STUNTGP_D3D 0x441240
int FUN_441240(SpriteData *sprite)
{
    if (sprite->texture & 0x10000)
    {
        sprite->texture = FUN_441270(sprite->texture & 0xffff);
    }
    return sprite->texture;
}

// FUNCTION: STUNTGP_D3D 0x441270
int FUN_441270(int id)
{
    int slot;
    if (g_60883c[id] >= 0)
    {
        slot = g_60883c[id];
        g_608cf0[slot] = -2;
    }
    else
    {
        slot = FUN_4412c0();
        if (slot >= 0)
        {
            FUN_441310(slot, id);
            g_60883c[id] = slot;
            g_6087a8[slot] = id;
            g_608cf0[slot] = -2;
        }
    }
    return slot;
}

// Evicts the oldest of the dynamic texture slots 17..36.
// FUNCTION: STUNTGP_D3D 0x4412c0
int FUN_4412c0()
{
    int best = -1;
    int bestAge = 0;
    for (int i = 17; i < 0x25; i++)
    {
        if (g_608cf0[i] > bestAge)
        {
            bestAge = g_608cf0[i];
            best = i;
        }
    }
    if (best >= 0 && g_6087a8[best] >= 0)
    {
        g_60883c[g_6087a8[best]] = -1;
    }
    return best;
}

// FUNCTION: STUNTGP_D3D 0x441310
void FUN_441310(int slot, int id)
{
    FUN_430d40(slot, id);
    g_5df51c++;
}

// Image table entry; data is RLE packed when compressed is 1.
struct ImageEntry
{
    BYTE *data;     // 0x00
    DWORD width;    // 0x04
    DWORD height;   // 0x08
    int compressed; // 0x0c
    DWORD unk10;    // 0x10
    DWORD unk14;    // 0x14
};

// GLOBAL: STUNTGP_D3D 0x583594
int g_583594[256];

// GLOBAL: STUNTGP_D3D 0x587998
ImageEntry g_587998[256];

// Replaces the contents of a texture slot with another image of the same width.
// FUNCTION: STUNTGP_D3D 0x430d40
void FUN_430d40(int slot, int id)
{
    DDSURFACEDESC2 desc;
    SurfaceSlot *surfaceSlot;
    WORD *size;
    LPDIRECT3DTEXTURE2 texture;
    LPDIRECTDRAWSURFACE4 surface;
    int res;
    int image = g_583594[id];
    surface = NULL;
    texture = NULL;
    size = (WORD *)&g_6227d4[slot].unk04[1];
    if (*size == g_587998[image].width)
    {
        if (slot == 15)
        {
            g_61b634 = id;
        }
        surfaceSlot = &g_surfaceSlots[slot];
        memset(&desc, 0, sizeof(desc));
        desc.dwHeight = g_587998[image].height;
        desc.dwWidth = g_587998[image].width;
        desc.dwSize = sizeof(desc);
        desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
        desc.ddpfPixelFormat = *g_5d91c0;
        desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
        res = g_dd4->CreateSurface(&desc, &surface, NULL);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
        if (g_587998[image].compressed == 1)
        {
            BYTE *buffer = (BYTE *)Mem_Alloc(*size * *size * 2 + 0x20, 0);
            FUN_4234e0(buffer, g_587998[image].data + 10);
            FUN_430100(surface, buffer, g_587998[image].width, g_587998[image].height, 16);
            Mem_Free(buffer);
        }
        else
        {
            FUN_430100(surface, g_587998[image].data, g_587998[image].width, g_587998[image].height, 16);
        }
        res = surface->QueryInterface(IID_IDirect3DTexture2, (void **)&texture);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
        res = surface->GetSurfaceDesc(&desc);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
        LPDIRECT3DTEXTURE2 target = (LPDIRECT3DTEXTURE2)surfaceSlot->unk04;
        desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
        desc.ddsCaps.dwCaps2 = 0x80;
        desc.dwFlags = (*g_592028 ? DDSD_CKSRCBLT : 0) + 0x101007;
        desc.dwTextureStage = 0;
        res = target->Load(texture);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
        g_6243b8->texture = target;
        g_6243b8->unk04[0] = (DWORD)target;
        FUN_4300f0(texture);
        ddReleaseSurface(&surface);
    }
}
