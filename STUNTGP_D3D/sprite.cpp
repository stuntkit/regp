#include "sprite.h"
#include "d3drender.h"
#include "font.h"

#include <direct.h>
#include <io.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "globals.h"
#include "mem.h"
#include "objects.h"
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

// GLOBAL: STUNTGP_D3D 0x480134
SpriteFile g_480134[1];

// GLOBAL: STUNTGP_D3D 0x4798bc
int g_4798bc = -1;

// GLOBAL: STUNTGP_D3D 0x5ff4bc
char g_5ff4bc[0x400];

// GLOBAL: STUNTGP_D3D 0x5ff8bc
int g_5ff8bc;

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

// Frame texture layout used by FUN_439520: shadow inset, corner size, row end.
// GLOBAL: STUNTGP_D3D 0x4793dc
int g_4793dc = 12;

// GLOBAL: STUNTGP_D3D 0x4793e0
int g_4793e0 = 30;

// GLOBAL: STUNTGP_D3D 0x4793e4
int g_4793e4 = 62;

// Scroll bar thickness.
// GLOBAL: STUNTGP_D3D 0x4793e8
float g_4793e8 = 13.0f;

// Scroll bar end cap length.
// GLOBAL: STUNTGP_D3D 0x4793ec
float g_4793ec = 5.0f;

// Per-frame arena the sprite nodes are carved from.
// GLOBAL: STUNTGP_D3D 0x5da374
BYTE g_spriteArena[20000];

// High-water mark of g_5da370.
// GLOBAL: STUNTGP_D3D 0x5df514
int g_5df514;

// GLOBAL: STUNTGP_D3D 0x605cc8
char *g_feText[0x2dc];

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

// FUNCTION: STUNTGP_D3D 0x438910
float FUN_438910(const char *text, float size)
{
    Font_Select(size <= 1.0f ? 0 : 1);
    return FUN_4290d0(text, size);
}

// FUNCTION: STUNTGP_D3D 0x438950
float FUN_438950(float size)
{
    return size * 16.0f;
}

// Clips a sprite against the integer clip rectangle and queues it.
// FUNCTION: STUNTGP_D3D 0x438370
void FUN_438370(SpriteData *src, int layer, int sub)
{
    float t;
    SpriteData s;

    if (src->width + src->x < g_5da360[0])
    {
        return;
    }
    if (src->height + src->y < g_5da360[1])
    {
        return;
    }
    if (src->x > g_5da360[2])
    {
        return;
    }
    if (src->y > g_5da360[3])
    {
        return;
    }
    s = *src;
    if (s.x < g_5da360[0])
    {
        float d = g_5da360[0] - s.x;
        s.x = g_5da360[0];
        t = d / s.width;
        s.width -= d;
        s.u0 += (s.u1 - s.u0) * t;
    }
    if (s.width + s.x > g_5da360[2])
    {
        t = (s.width + s.x - g_5da360[2]) / s.width;
        s.width = g_5da360[2] - s.x;
        s.u1 += (s.u0 - s.u1) * t;
    }
    if (s.y < g_5da360[1])
    {
        float d = g_5da360[1] - s.y;
        s.y = g_5da360[1];
        t = d / s.height;
        s.height -= d;
        s.v0 += (s.v1 - s.v0) * t;
    }
    if (s.height + s.y > g_5da360[3])
    {
        t = (s.height + s.y - g_5da360[3]) / s.height;
        s.height = g_5da360[3] - s.y;
        s.v1 += (s.v0 - s.v1) * t;
    }
    if (s.width > 1.0f && s.height > 1.0f)
    {
        FUN_438500(layer, sub, &s);
    }
}

// FUNCTION: STUNTGP_D3D 0x438500
void FUN_438500(int layer, int sub, SpriteData *sprite)
{
    SpriteNode *node = (SpriteNode *)FUN_438550(sizeof(SpriteData) + 8);
    if (node != NULL)
    {
        node->sprite = *sprite;
        node->type = 1;
        FUN_438590(layer, sub, node);
    }
}

// FUNCTION: STUNTGP_D3D 0x438550
void *FUN_438550(int size)
{
    BYTE *p = &g_spriteArena[g_5da370];
    size = ((size + 3) & ~3) + g_5da370;
    if (size > 20000)
    {
        return NULL;
    }
    g_5da370 = size;
    if (size > g_5df514)
    {
        g_5df514 = size;
    }
    return p;
}

// FUNCTION: STUNTGP_D3D 0x438590
void FUN_438590(int layer, int sub, SpriteNode *node)
{
    int i = layer * 4 + sub;
    node->next = NULL;
    if (g_spriteLists.tails[i] == NULL)
    {
        g_spriteLists.tails[i] = node;
        g_spriteLists.heads[i] = node;
    }
    else
    {
        g_spriteLists.tails[i]->next = node;
        g_spriteLists.tails[i] = node;
    }
}

// Tiles a 64-pixel texture over a rectangle, scrolled by the fractional part of u/v.
// FUNCTION: STUNTGP_D3D 0x438830
void FUN_438830(float x0, float y0, float x1, float y1, int layer, int def, float u, float v)
{
    if (def != 0)
    {
        SpriteData s;
        FUN_441320(&s, def);
        s.flags = 2;
        s.blendMode = 0x20;
        s.alpha = 0xff;
        u -= (int)u;
        v -= (int)v;
        s.x = x0;
        s.y = y0;
        s.width = x1 - x0;
        s.height = y1 - y0;
        s.u0 = (x0 * 0.015625f - u) * 1024.0f;
        s.v0 = (y0 * 0.015625f - v) * 1024.0f;
        s.u1 = (x1 * 0.015625f - u) * 1024.0f;
        s.v1 = (y1 * 0.015625f - v) * 1024.0f;
        FUN_438370(&s, layer, 0);
    }
}

// FUNCTION: STUNTGP_D3D 0x438960
void FUN_438960(float x, float y, int layer, int sub, int style, const char *text, float size, D3DCOLOR color, DWORD flags)
{
    FUN_438990(x, y, layer, sub, style, text, size, color, flags, 0.0f);
}

// FUNCTION: STUNTGP_D3D 0x438990
void FUN_438990(float x, float y, int layer, int sub, int style, const char *text, float size, D3DCOLOR color, DWORD flags, float unk18)
{
    int len = strlen(text) + 1;
    SpriteNode *node = (SpriteNode *)FUN_438550(len + 0x38);
    if (node != NULL)
    {
        node->text.x = x;
        node->text.y = y;
        node->text.style = style;
        node->type = 0;
        memcpy(node->text.text, text, len);
        node->text.size = size;
        node->text.color = color;
        node->text.flags = flags;
        node->text.unk18 = unk18;
        FUN_438590(layer, sub, node);
    }
}

// FUNCTION: STUNTGP_D3D 0x438be0
void FUN_438be0(float x, float y, int layer, int style, int textId, float size, D3DCOLOR color, DWORD flags)
{
    FUN_438990(x, y, layer, 1, style, FUN_441170(textId), size, color, flags, 0.0f);
}

// FUNCTION: STUNTGP_D3D 0x439380
void FUN_439380(float x0, float y0, float x1, float y1, int layer, int scroll, int flags, float fade)
{
    SpriteData s;
    FUN_441320(&s, 0x76);
    s.flags = 2;
    s.alpha = 0xff;
    if (flags & 0x100)
    {
        s.blendMode = 0x58;
    }
    else if (flags & 0x200)
    {
        s.blendMode = 0x70;
    }
    else if (flags & 0x400)
    {
        s.alpha = (int)(FUN_43d7b0(fade, 0.0f, 1.0f) * 255.0f);
        s.blendMode = 0x60;
    }
    else
    {
        s.blendMode = 0x20;
    }
    float offset = scroll * 32.0f;
    s.x = x0;
    s.y = y0;
    s.width = x1 - x0;
    s.height = y1 - y0;
    s.v0 += offset;
    s.v1 += offset;
    FUN_438370(&s, layer, 0);
}

// Framed panel, with a drop shadow when flags & 0x40.
// FUNCTION: STUNTGP_D3D 0x439450
void FUN_439450(float x0, float y0, float x1, float y1, int layer, int def, int flags)
{
    if (x0 < x1 && y0 < y1)
    {
        if (flags & 0x40)
        {
            FUN_439520(x0 + 8.0f, y0 + 8.0f, x1 + 8.0f, y1 + 8.0f, 15, 0, def, 2, 0x70);
        }
        FUN_439520(x0, y0, x1, y1, layer, 3, def, 1, 0x70);
        FUN_439520(x0, y0, x1, y1, layer, 2, def, 0, 0x58);
    }
}

// Nine-slice frame: four 30-pixel corners and four stretched edges from row `row` of the frame texture.
// FUNCTION: STUNTGP_D3D 0x439520
void FUN_439520(float x0, float y0, float x1, float y1, int layer, int sub, int def, DWORD row, int blend)
{
    SpriteData s;

    x0 -= g_4793dc;
    y0 -= g_4793dc;
    x1 = x1 - g_4793e0 + g_4793dc;
    y1 = y1 - g_4793e0 + g_4793dc;
    FUN_441320(&s, def);
    s.flags = 2;
    s.blendMode = blend;
    s.alpha = 0xff;
    s.width = g_4793e0;
    s.height = g_4793e0;
    float u = s.u0;
    float v = (row << 6) * 4.0f + s.v0;

    s.x = x0;
    s.y = y0;
    s.v0 = v;
    s.u1 = g_4793e0 * 4.0f + u;
    s.v1 = g_4793e0 * 4.0f + v;
    FUN_438370(&s, layer, sub);

    s.x = x1;
    s.y = y0;
    s.u0 = (g_4793e4 - g_4793e0) * 4.0f + u;
    s.v0 = v;
    s.u1 = g_4793e4 * 4.0f + u;
    s.v1 = g_4793e0 * 4.0f + v;
    FUN_438370(&s, layer, sub);

    s.x = x0;
    s.y = y1;
    s.u0 = u;
    s.v0 = (g_4793e4 - g_4793e0) * 4.0f + v;
    s.u1 = g_4793e0 * 4.0f + u;
    s.v1 = g_4793e4 * 4.0f + v;
    FUN_438370(&s, layer, sub);

    s.x = x1;
    s.y = y1;
    s.u0 = (g_4793e4 - g_4793e0) * 4.0f + u;
    s.v0 = (g_4793e4 - g_4793e0) * 4.0f + v;
    s.u1 = g_4793e4 * 4.0f + u;
    s.v1 = g_4793e4 * 4.0f + v;
    FUN_438370(&s, layer, sub);

    s.x = x0 + g_4793e0;
    s.y = y0;
    s.u0 = g_4793e0 * 4.0f + u;
    s.v0 = v;
    s.u1 = (g_4793e4 - g_4793e0) * 4.0f + u;
    s.v1 = g_4793e0 * 4.0f + v;
    s.width = x1 - x0 - g_4793e0;
    FUN_438370(&s, layer, sub);

    s.x = x0 + g_4793e0;
    s.y = y1;
    s.u0 = g_4793e0 * 4.0f + u;
    s.v0 = (g_4793e4 - g_4793e0) * 4.0f + v;
    s.u1 = (g_4793e4 - g_4793e0) * 4.0f + u;
    s.v1 = g_4793e4 * 4.0f + v;
    FUN_438370(&s, layer, sub);

    s.x = x0;
    s.width = g_4793e0;
    s.height = y1 - y0 - g_4793e0;
    s.u0 = u;
    s.y = y0 + g_4793e0;
    s.v0 = g_4793e0 * 4.0f + v;
    s.u1 = g_4793e0 * 4.0f + u;
    s.v1 = (g_4793e4 - g_4793e0) * 4.0f + v;
    FUN_438370(&s, layer, sub);

    s.x = x1;
    s.y = y0 + g_4793e0;
    s.u0 = (g_4793e4 - g_4793e0) * 4.0f + u;
    s.v0 = g_4793e0 * 4.0f + v;
    s.u1 = g_4793e4 * 4.0f + u;
    s.v1 = (g_4793e4 - g_4793e0) * 4.0f + v;
    FUN_438370(&s, layer, sub);
}

// Panel with optional horizontal and vertical scroll bars.
// FUNCTION: STUNTGP_D3D 0x4398a0
void FUN_4398a0(float x0, float y0, float x1, float y1, int layer, int def, int flags, float a0, float a1, float a2, float b0, float b1, float b2)
{
    FUN_439450(x0, y0, x1, y1, layer, def, flags);
    if (a0 > 0.0f && a1 > 0.0f && a2 <= a0)
    {
        FUN_4399b0(0x75, x0 + 10.0f, x1 - 10.0f, y1 + 10.0f - g_4793e8, a0, a1, a2, layer);
    }
    if (b0 > 0.0f && b1 > 0.0f && b2 <= b0)
    {
        FUN_439b80(0x75, x1 + 10.0f - g_4793e8, y0 + 10.0f, y1 - 10.0f, b0, b1, b2, layer);
    }
}

// Horizontal scroll bar: track in three pieces, then the thumb.
// FUNCTION: STUNTGP_D3D 0x4399b0
void FUN_4399b0(int def, float x0, float x1, float y, float total, float visible, float pos, int layer)
{
    SpriteData s;
    float u;

    FUN_441320(&s, def);
    u = s.u0;
    s.flags = 2;
    s.alpha = 0xff;
    s.x = x0;
    s.y = y;
    s.width = g_4793ec;
    s.u1 = g_4793ec * 4.0f + s.u0;
    s.blendMode = 0x70;
    FUN_438370(&s, layer, 1);

    s.x = s.width + s.x;
    s.u0 = s.u1;
    s.u1 = (g_4793e8 - g_4793ec) * 4.0f + u;
    x1 -= x0;
    s.width = x1 - g_4793ec * 2.0f;
    FUN_438370(&s, layer, 1);

    s.x = s.width + s.x;
    s.u0 = s.u1;
    s.width = g_4793ec;
    s.u1 = g_4793e8 * 4.0f + u;
    FUN_438370(&s, layer, 1);

    u = (g_4793e8 + 2.0f) * 4.0f + u;
    s.y = y;
    s.u0 = u;
    s.x = x1 * pos / total + x0;
    s.u1 = g_4793ec * 4.0f + u;
    s.width = g_4793ec;
    s.blendMode = 0x58;
    FUN_438370(&s, layer, 0);

    s.x = s.width + s.x;
    s.u0 = s.u1;
    s.u1 = (g_4793e8 - g_4793ec) * 4.0f + u;
    s.width = x1 * visible / total - g_4793ec * 2.0f;
    FUN_438370(&s, layer, 0);

    s.x = s.width + s.x;
    s.u0 = s.u1;
    s.width = g_4793ec;
    s.u1 = g_4793e8 * 4.0f + u;
    FUN_438370(&s, layer, 0);
}

// FUNCTION: STUNTGP_D3D 0x439b80
void FUN_439b80(int def, float x, float y0, float y1, float total, float visible, float pos, int layer)
{
    SpriteData s;
    float u;
    float v;

    FUN_441320(&s, def);
    u = s.u0;
    v = s.v0;
    s.flags = 2;
    s.alpha = 0xff;
    s.x = x;
    s.y = y0;
    s.height = g_4793ec;
    s.v1 = g_4793ec * 4.0f + s.v0;
    s.blendMode = 0x70;
    FUN_438370(&s, layer, 1);

    s.y = s.height + s.y;
    s.v0 = s.v1;
    s.v1 = (g_4793e8 - g_4793ec) * 4.0f + v;
    y1 -= y0;
    s.height = y1 - g_4793ec * 2.0f;
    FUN_438370(&s, layer, 1);

    s.y = s.height + s.y;
    s.v0 = s.v1;
    s.height = g_4793ec;
    s.v1 = g_4793e8 * 4.0f + v;
    FUN_438370(&s, layer, 1);

    s.x = x;
    u = (g_4793e8 + 2.0f) * 8.0f + u;
    s.y = y1 * pos / total + y0;
    s.u0 = u;
    s.u1 = g_4793e8 * 4.0f + u;
    s.v0 = v;
    s.height = g_4793ec;
    s.v1 = g_4793ec * 4.0f + v;
    s.blendMode = 0x58;
    FUN_438370(&s, layer, 0);

    s.y = s.height + s.y;
    s.v0 = s.v1;
    s.v1 = (g_4793e8 - g_4793ec) * 4.0f + v;
    s.height = y1 * visible / total - g_4793ec * 2.0f;
    FUN_438370(&s, layer, 0);

    s.y = s.height + s.y;
    s.v0 = s.v1;
    s.height = g_4793ec;
    s.v1 = g_4793e8 * 4.0f + v;
    FUN_438370(&s, layer, 0);
}

// FUNCTION: STUNTGP_D3D 0x43d7b0
float FUN_43d7b0(float value, float lo, float hi)
{
    if (value < lo)
    {
        return lo;
    }
    if (value > hi)
    {
        return hi;
    }
    return value;
}

// FUNCTION: STUNTGP_D3D 0x43d960
void FUN_43d960(ScreenRect *dst, ScreenRect *from, ScreenRect *to, float t)
{
    dst->left = (to->left - from->left) * t + from->left;
    dst->top = (to->top - from->top) * t + from->top;
    dst->right = (to->right - from->right) * t + from->right;
    dst->bottom = (to->bottom - from->bottom) * t + from->bottom;
}

// FUNCTION: STUNTGP_D3D 0x43dd40
void FUN_43dd40(int a, float b, float c)
{
    g_frontEnd.unk60 = a;
    g_frontEnd.unk64 = b;
    g_frontEnd.unk68 = c;
}

// FUNCTION: STUNTGP_D3D 0x43dd60
int FUN_43dd60()
{
    return g_frontEnd.unk74;
}

// Darkens the screen around a rectangle.
// FUNCTION: STUNTGP_D3D 0x43feb0
void FUN_43feb0(float x0, float y0, float x1, float y1, int def, float u, float v)
{
    FUN_438830(0.0f, 0.0f, x0, 480.0f, 0x10, def, u, v);
    FUN_438830(x1, 0.0f, 640.0f, 480.0f, 0x10, def, u, v);
    FUN_438830(0.0f, 0.0f, 640.0f, y0, 0x10, def, u, v);
    FUN_438830(0.0f, y1, 640.0f, 480.0f, 0x10, def, u, v);
}

// Collapses a rectangle to a 48x48 square around its centre.
// FUNCTION: STUNTGP_D3D 0x43ff40
void FUN_43ff40(ScreenRect *rect)
{
    float cx = (rect->left + rect->right) * 0.5f;
    float cy = (rect->top + rect->bottom) * 0.5f;
    rect->left = cx - 24.0f;
    rect->top = cy - 24.0f;
    rect->right = cx + 24.0f;
    rect->bottom = cy + 24.0f;
}

// FUNCTION: STUNTGP_D3D 0x43ff90
void FUN_43ff90(int arg)
{
    char buf[256];
    FUN_438830(0.0f, 0.0f, 640.0f, 480.0f, 0x13, 0x5f, g_frontEnd.unk6c, g_frontEnd.unk70);
    if (arg != 0)
    {
        sprintf(buf, FUN_441170(0x25e), arg);
    }
    else
    {
        strcpy(buf, FUN_441170(0x25d));
    }
    FUN_439450(40.0f, 220.0f, 600.0f, 260.0f, 3, (FUN_43dd60() & 0x20) ? 0x6f : 0x70, 0x40);
    FUN_439380(40.0f, 220.0f, 600.0f, 260.0f, 6, 2, 0, 0.0f);
    FUN_438960(320.0f, 240.0f, 5, 0, 4, buf, 1.5f, 0xffffffff, 0x803);
}

// FUNCTION: STUNTGP_D3D 0x4400a0
void FUN_4400a0(int value)
{
    g_frontEnd.unk84 = value;
}

// FUNCTION: STUNTGP_D3D 0x440160
int FUN_440160()
{
    return 8;
}

// FUNCTION: STUNTGP_D3D 0x440170
int FUN_440170()
{
    int value = g_5ff8bc;
    g_5ff8bc = 0;
    return value;
}

// Makes sure the save directory exists: 7 if it already did, 0 if created, 8 on failure.
// FUNCTION: STUNTGP_D3D 0x440180
int FUN_440180()
{
    char *path = FUN_4401e0(g_4798bc);
    if (FUN_4401c0(path))
    {
        return 7;
    }
    return _mkdir(path) < 0 ? 8 : 0;
}

// FUNCTION: STUNTGP_D3D 0x4401c0
BOOL FUN_4401c0(char *path)
{
    DWORD attributes = GetFileAttributesA(path);
    if (attributes != 0xffffffff && (attributes & FILE_ATTRIBUTE_DIRECTORY))
    {
        return TRUE;
    }
    return FALSE;
}

// FUNCTION: STUNTGP_D3D 0x4401e0
char *FUN_4401e0(int card)
{
    // STRING: STUNTGP_D3D 0x479a18
    sprintf(g_5ff4bc, "%s\\save\\card%02d", g_GameDirectory, card);
    return g_5ff4bc;
}

// Free space left in the 256K save area.
// FUNCTION: STUNTGP_D3D 0x440200
int FUN_440200(int *freeSpace)
{
    char *dir = FUN_4401e0(g_4798bc);
    *freeSpace = 0;
    if (!FUN_4401c0(dir))
    {
        return 1;
    }
    int used = FUN_440250(dir);
    if (used < 0)
    {
        return 9;
    }
    *freeSpace = 0x40000 - used;
    return 0;
}

// Total size of the files in a directory, or -1 if it does not exist.
// FUNCTION: STUNTGP_D3D 0x440250
int FUN_440250(char *dir)
{
    char pattern[0x400];
    struct _finddatai64_t data;
    int total = 0;
    if (!FUN_4401c0(dir))
    {
        return -1;
    }
    // STRING: STUNTGP_D3D 0x479a2c
    sprintf(pattern, "%s\\*.*", dir);
    long handle = _findfirsti64(pattern, &data);
    if (handle >= 0)
    {
        do
        {
            if (!(data.attrib & _A_SUBDIR))
            {
                total += (int)data.size;
            }
        } while (_findnexti64(handle, &data) >= 0);
        _findclose(handle);
    }
    return total;
}

// FUNCTION: STUNTGP_D3D 0x4402e0
int FUN_4402e0()
{
    return 0x200;
}

// FUNCTION: STUNTGP_D3D 0x4402f0
void FUN_4402f0(int value)
{
    g_4798bc = value;
}

// FUNCTION: STUNTGP_D3D 0x440300
int FUN_440300(int value)
{
    return value <= 8;
}

// FUNCTION: STUNTGP_D3D 0x440310
int FUN_440310(int value)
{
    return value;
}

// FUNCTION: STUNTGP_D3D 0x440320
int FUN_440320()
{
    char path[0x400];
    char *dir = FUN_4401e0(g_4798bc);
    if (!FUN_4401c0(dir))
    {
        return 1;
    }
    // STRING: STUNTGP_D3D 0x479a34
    sprintf(path, "%s\\setup.bin", dir);
    return FUN_440380(path) ? 4 : 6;
}

// FUNCTION: STUNTGP_D3D 0x440380
BOOL FUN_440380(char *path)
{
    DWORD attributes = GetFileAttributesA(path);
    if (attributes != 0xffffffff && !(attributes & FILE_ATTRIBUTE_DIRECTORY))
    {
        return TRUE;
    }
    return FALSE;
}

// Size of a file, or -1 if it is missing or a directory.
// FUNCTION: STUNTGP_D3D 0x440480
int FUN_440480(char *path)
{
    struct _finddatai64_t data;
    long handle = _findfirsti64(path, &data);
    if (handle < 0)
    {
        return -1;
    }
    _findclose(handle);
    if (data.attrib & _A_SUBDIR)
    {
        return -1;
    }
    return (int)data.size;
}

// FUNCTION: STUNTGP_D3D 0x4405c0
int FUN_4405c0(int ghost)
{
    char path[0x400];
    char *dir = FUN_4401e0(g_4798bc);
    if (!FUN_4401c0(dir))
    {
        return 1;
    }
    // STRING: STUNTGP_D3D 0x479a74
    sprintf(path, "%s\\ghost%02d.bin", dir, ghost);
    return FUN_440380(path) ? 4 : 6;
}

// FUNCTION: STUNTGP_D3D 0x4406e0
int FUN_4406e0(int ghost)
{
    char path[0x400];
    char *dir = FUN_4401e0(g_4798bc);
    if (!FUN_4401c0(dir))
    {
        return 1;
    }
    // STRING: STUNTGP_D3D 0x479aa8
    sprintf(path, "%s\\ghost%02d.bin", dir, ghost);
    if (!FUN_440380(path))
    {
        return 6;
    }
    return _unlink(path) < 0 ? 6 : 0;
}

// FUNCTION: STUNTGP_D3D 0x441170
char *FUN_441170(int id)
{
    return g_feText[id];
}

// FUNCTION: STUNTGP_D3D 0x441320
int FUN_441320(SpriteData *dst, int id)
{
    *dst = g_spriteDefs[id];
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x441220
void FUN_441220()
{
    for (int i = 17; i < 0x25; i++)
    {
        g_608cf0[i]++;
    }
}

// FUNCTION: STUNTGP_D3D 0x43f6b0
void FUN_43f6b0()
{
    ScreenRect to;
    ScreenRect from;
    ScreenRect rect;
    float u;
    float v;

    u = g_frontEnd.unk6c;
    v = g_frontEnd.unk70;
    FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
    rect.left = 0.0f;
    rect.top = 0.0f;
    rect.right = 640.0f;
    rect.bottom = 480.0f;
    from = rect;
    to = rect;
    if (g_frontEnd.unkbc != 0)
    {
        FUN_43ff90(g_frontEnd.lockedPlayer);
        g_frontEnd.unk78 = 0;
        return;
    }
    switch (g_frontEnd.unk84)
    {
    case 1:
        FUN_438830(0.0f, 0.0f, 640.0f, 480.0f, 0x10, g_frontEnd.unk60, u, v);
        break;
    case 4:
        from.left = 40.0f;
        from.top = 96.0f;
        from.right = 600.0f;
        from.bottom = 256.0f;
        to = from;
        FUN_43ff40(&from);
        FUN_43d960(&rect, &from, &to, g_frontEnd.unk80);
        FUN_438830(rect.left, rect.top, rect.right, rect.bottom, 0x13, 0x5f, u * 0.5f, v * 0.5f);
        FUN_43feb0(rect.left, rect.top, rect.right, rect.bottom, g_frontEnd.unk60, u, v);
        FUN_4398a0(rect.left, rect.top, rect.right, rect.bottom, 0xe, 0x6e, 0x40, g_frontEnd.unk88[0], g_frontEnd.unk88[1], g_frontEnd.unk88[2], g_frontEnd.unk88[3], g_frontEnd.unk88[4], g_frontEnd.unk88[5]);
        FUN_439450(40.0f, 288.0f, 408.0f, 384.0f, 10, 0x6f, 0x40);
        FUN_439380(40.0f, 288.0f, 408.0f, 384.0f, 0xd, 2, 0, 0.0f);
        break;
    case 3:
        from.left = 180.0f;
        from.top = 86.0f;
        from.right = 588.0f;
        from.bottom = 310.0f;
        to = from;
        FUN_43ff40(&from);
        FUN_43d960(&rect, &from, &to, g_frontEnd.unk80);
        FUN_438830(rect.left, rect.top, rect.right, rect.bottom, 0x13, 0x5f, u * 0.5f, v * 0.5f);
        FUN_43feb0(rect.left, rect.top, rect.right, rect.bottom, g_frontEnd.unk60, u, v);
        FUN_4398a0(rect.left, rect.top, rect.right, rect.bottom, 0xe, 0x6e, 0x40, g_frontEnd.unk88[0], g_frontEnd.unk88[1], g_frontEnd.unk88[2], g_frontEnd.unk88[3], g_frontEnd.unk88[4], g_frontEnd.unk88[5]);
        FUN_439450(180.0f, 342.0f, 588.0f, 422.0f, 10, 0x6e, 0x40);
        FUN_439380(180.0f, 342.0f, 588.0f, 422.0f, 0xd, 2, 0, 0.0f);
        break;
    case 2:
        from.left = 48.0f;
        from.top = 86.0f;
        from.right = 592.0f;
        from.bottom = 272.0f;
        to = from;
        FUN_43ff40(&from);
        FUN_43d960(&rect, &from, &to, g_frontEnd.unk80);
        FUN_438830(rect.left, rect.top, rect.right, rect.bottom, 0x13, 0x5f, u * 0.5f, v * 0.5f);
        FUN_43feb0(rect.left, rect.top, rect.right, rect.bottom, g_frontEnd.unk60, u, v);
        FUN_4398a0(rect.left, rect.top, rect.right, rect.bottom, 0xe, 0x6e, 0x40, g_frontEnd.unk88[0], g_frontEnd.unk88[1], g_frontEnd.unk88[2], g_frontEnd.unk88[3], g_frontEnd.unk88[4], g_frontEnd.unk88[5]);
        break;
    case 5:
        from.left = 49.0f;
        from.top = 82.0f;
        from.right = 391.0f;
        from.bottom = 334.0f;
        to = from;
        FUN_43ff40(&from);
        FUN_43d960(&rect, &from, &to, g_frontEnd.unk80);
        FUN_438830(rect.left, rect.top, rect.right, rect.bottom, 0x13, 0x5f, u * 0.5f, v * 0.5f);
        FUN_43feb0(rect.left, rect.top, rect.right, rect.bottom, g_frontEnd.unk60, u, v);
        FUN_4398a0(rect.left, rect.top, rect.right, rect.bottom, 0xe, 0x6e, 0x40, g_frontEnd.unk88[0], g_frontEnd.unk88[1], g_frontEnd.unk88[2], g_frontEnd.unk88[3], g_frontEnd.unk88[4], g_frontEnd.unk88[5]);
        FUN_439450(423.0f, 82.0f, 591.0f, 334.0f, 10, 0x6e, 0x40);
        FUN_439380(423.0f, 82.0f, 591.0f, 334.0f, 0xd, 2, 0, 0.0f);
        break;
    case 7:
        from.left = 49.0f;
        from.top = 82.0f;
        from.right = 391.0f;
        from.bottom = 334.0f;
        to = from;
        FUN_43ff40(&from);
        FUN_43d960(&rect, &from, &to, g_frontEnd.unk80);
        FUN_438830(rect.left, rect.top, rect.right, rect.bottom, 0x13, 0x5f, u * 0.5f, v * 0.5f);
        FUN_43feb0(rect.left, rect.top, rect.right, rect.bottom, g_frontEnd.unk60, u, v);
        FUN_4398a0(rect.left, rect.top, rect.right, rect.bottom, 0xe, 0x6e, 0x40, g_frontEnd.unk88[0], g_frontEnd.unk88[1], g_frontEnd.unk88[2], g_frontEnd.unk88[3], g_frontEnd.unk88[4], g_frontEnd.unk88[5]);
        FUN_439450(423.0f, 82.0f, 591.0f, 240.0f, 10, 0x6e, 0x40);
        FUN_439380(423.0f, 82.0f, 591.0f, 240.0f, 0xd, 2, 0, 0.0f);
        FUN_439450(423.0f, 272.0f, 591.0f, 334.0f, 10, 0x6f, 0x40);
        FUN_439380(423.0f, 272.0f, 591.0f, 334.0f, 0xd, 2, 0, 0.0f);
        break;
    case 6:
        from.left = 120.0f;
        from.top = 90.0f;
        from.right = 520.0f;
        from.bottom = 380.0f;
        to = from;
        FUN_43ff40(&from);
        FUN_43d960(&rect, &from, &to, g_frontEnd.unk80);
        FUN_438830(rect.left, rect.top, rect.right, rect.bottom, 0x13, 0x5f, u * 0.5f, v * 0.5f);
        FUN_43feb0(rect.left, rect.top, rect.right, rect.bottom, g_frontEnd.unk60, u, v);
        FUN_4398a0(rect.left, rect.top, rect.right, rect.bottom, 0xe, 0x6e, 0x40, g_frontEnd.unk88[0], g_frontEnd.unk88[1], g_frontEnd.unk88[2], g_frontEnd.unk88[3], g_frontEnd.unk88[4], g_frontEnd.unk88[5]);
        break;
    }
    FUN_439450(0.0f, 0.0f, 640.0f, 480.0f, 1, 0x71, 0);
    FUN_438190(rect.left, rect.top, rect.right, rect.bottom);
    if (g_frontEnd.screen != NULL)
    {
        if (g_frontEnd.screen->unk00[1] != 1)
        {
            FUN_438be0(320.0f, 16.0f, 2, 4, 1, 1.25f, 0xffffffff, 0x803);
        }
        if (g_frontEnd.screen != NULL)
        {
            g_frontEnd.screen->message(g_frontEnd.screen, 3, 0);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x43d250
void FUN_43d250()
{
    FUN_43f6b0();
    FUN_437ec0();
}

// FUNCTION: STUNTGP_D3D 0x441180
SpriteFile *FUN_441180()
{
    return g_480134;
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
