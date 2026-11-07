#include "d3drender.h"
#include "common.h"
#include "sprite.h"
#include "font.h"
#include "globals.h"
#include "windowInit.h"
#include "vecmath.h"
#include "surface.h"
#include "Game/GameEngine/io_wad.h"
#include "Game/GameEngine/GameSetup.h"
#include "Game/GameEngine/GameUpdate.h"

#include <stdlib.h>
#include <string.h>

// GLOBAL: STUNTGP_D3D 0x5da1c4
LPDIRECT3DDEVICE3 g_d3dDevice = NULL;

// GLOBAL: STUNTGP_D3D 0x5da1c8
BOOL g_d3dInScene = FALSE;

// GLOBAL: STUNTGP_D3D 0x576bc4
int g_576bc4 = 0;

// GLOBAL: STUNTGP_D3D 0x576bc8
int g_576bc8 = 0;

// GLOBAL: STUNTGP_D3D 0x576bd8
int g_576bd8 = 0;

// GLOBAL: STUNTGP_D3D 0x576be0
int g_576be0 = 0;

// GLOBAL: STUNTGP_D3D 0x5d91b4
int *g_5d91b4 = NULL;

// GLOBAL: STUNTGP_D3D 0x592054
int g_592054 = 0;

// GLOBAL: STUNTGP_D3D 0x592058
int g_592058 = 0;

// GLOBAL: STUNTGP_D3D 0x59205c
int g_59205c = 0;

// GLOBAL: STUNTGP_D3D 0x592060
int g_592060 = 0;

// GLOBAL: STUNTGP_D3D 0x592064
int g_592064 = 0;

// GLOBAL: STUNTGP_D3D 0x477ccc
float g_477ccc = 128.0f;

// GLOBAL: STUNTGP_D3D 0x61c5f0
OverlayPoly *g_61c5f0 = NULL;

// GLOBAL: STUNTGP_D3D 0x61c604
DWORD g_61c604 = 0;

// GLOBAL: STUNTGP_D3D 0x58332c
int g_58332c = 0;

// Per texture slot: set when the texture has transparent texels.
// GLOBAL: STUNTGP_D3D 0x59207c
BYTE g_59207c[255];

// GLOBAL: STUNTGP_D3D 0x592028
BYTE *g_592028;

// GLOBAL: STUNTGP_D3D 0x592050
int g_592050 = 0;

// GLOBAL: STUNTGP_D3D 0x61c5e4
int g_61c5e4 = 0;

// GLOBAL: STUNTGP_D3D 0x6227d4
TextureSlot g_6227d4[1];

// GLOBAL: STUNTGP_D3D 0x58d818
D3DTLVERTEX2 g_58d818[8];

// Virtual 640x480 to display scale and offset.
// GLOBAL: STUNTGP_D3D 0x624990
float g_624990 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x624994
float g_624994 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576b94
float g_576b94 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576b98
float g_576b98 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x6243b8
TextureSlot *g_6243b8 = NULL;

// GLOBAL: STUNTGP_D3D 0x6243bc
int g_6243bc = 0;

// GLOBAL: STUNTGP_D3D 0x6244a8
short g_6244a8[16];

// GLOBAL: STUNTGP_D3D 0x6244c8
int g_6244c8;

// GLOBAL: STUNTGP_D3D 0x6244cc
int g_6244cc;

// GLOBAL: STUNTGP_D3D 0x6244d0
int g_6244d0;

// GLOBAL: STUNTGP_D3D 0x6244d4
int g_6244d4;

// GLOBAL: STUNTGP_D3D 0x6244d8
int g_6244d8;

// GLOBAL: STUNTGP_D3D 0x6244dc
int g_6244dc;

// GLOBAL: STUNTGP_D3D 0x6244e0
int g_6244e0;

// GLOBAL: STUNTGP_D3D 0x6244e4
int g_6244e4;

// GLOBAL: STUNTGP_D3D 0x61c50c
int g_61c50c = 0;

// GLOBAL: STUNTGP_D3D 0x576b8c
int g_576b8c = 0;

// GLOBAL: STUNTGP_D3D 0x576b90
int g_576b90 = 0;

// GLOBAL: STUNTGP_D3D 0x576b9c
float g_576b9c = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576ba0
float g_576ba0 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576be4
float g_576be4 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576be8
float g_576be8 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x57e310
ResourceFile g_textureFiles[255];

// GLOBAL: STUNTGP_D3D 0x5895c0
ResourceFile g_fontFiles[8];

// GLOBAL: STUNTGP_D3D 0x5895bc
ResourceFile *g_5895bc;

// Pool holding the registered file names.
// GLOBAL: STUNTGP_D3D 0x580aec
char *g_580aec;

// GLOBAL: STUNTGP_D3D 0x58271c
int g_58271c;

// Records a font file so it can be reloaded when surfaces are lost.
// FUNCTION: STUNTGP_D3D 0x42be90
void FUN_42be90(char *path)
{
    g_5895bc->name = g_580aec;
    g_5895bc->slot = g_58271c;
    g_5895bc++;
    g_5895bc->name = NULL;
    strcpy(g_580aec, path);
    g_580aec += strlen(path) + 1;
}

// GLOBAL: STUNTGP_D3D 0x489714
int g_489714 = 320;

// GLOBAL: STUNTGP_D3D 0x489718
int g_489718 = 200;

// Sprite clip rectangle in virtual 640x480 space.
// GLOBAL: STUNTGP_D3D 0x576c04
float g_clipLeft = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576c08
float g_clipRight = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576c0c
float g_clipTop = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576c10
float g_clipBottom = 0.0f;

// FUNCTION: STUNTGP_D3D 0x4251a0
int FUN_4251a0(SpriteDesc *desc)
{
    float x;
    float y;
    float t;
    float w;
    float x2;
    float y2;
    float u1;
    float h;
    float u0;
    float v0;
    float v1;
    if (desc->flags & 8)
    {
        desc->x = desc->x - desc->originX * desc->scaleX + desc->originX;
        desc->originX = 0.0f;
        desc->y = desc->y - desc->originY * desc->scaleY + desc->originY;
        desc->originY = 0.0f;
        w = desc->width * desc->scaleX;
        h = desc->scaleY * desc->height;
    }
    else
    {
        w = desc->width;
        h = desc->height;
    }
    x = desc->x;
    y = desc->y;
    x2 = x + w;
    y2 = y + h;

    // Sign tests on the float bit pattern.
    t = x2 - g_clipLeft;
    if (*(int *)&t <= 0)
    {
        return 0;
    }
    t = x - g_clipRight;
    if (*(int *)&t >= 0)
    {
        return 0;
    }
    t = y2 - g_clipTop;
    if (*(int *)&t <= 0)
    {
        return 0;
    }
    t = y - g_clipBottom;
    if (*(int *)&t >= 0)
    {
        return 0;
    }
    if (x >= g_clipLeft && x2 < g_clipRight && y >= g_clipTop && y2 < g_clipBottom)
    {
        return 1;
    }

    u0 = desc->u0;
    v0 = desc->v0;
    v1 = desc->v1;
    u1 = desc->u1;
    if (x < g_clipLeft)
    {
        t = g_clipLeft - x;
        u0 += (u1 - u0) * t / w;
        w -= t;
        x += t;
    }
    if (x2 > g_clipRight)
    {
        float d = x2 - g_clipRight;
        u1 -= (u1 - u0) * d / w;
        w -= d;
    }
    if (y < g_clipTop)
    {
        float d = g_clipTop - y;
        v0 += (v1 - v0) * d / h;
        h -= d;
        y += d;
    }
    if (y2 > g_clipBottom)
    {
        float d = y2 - g_clipBottom;
        v1 -= (v1 - v0) * d / h;
        h -= d;
    }
    desc->width = w;
    desc->height = h;
    desc->u0 = u0;
    desc->u1 = u1;
    desc->v0 = v0;
    desc->y = y;
    desc->v1 = v1;
    desc->scaleY = 1.0f;
    desc->scaleX = 1.0f;
    desc->x = x;
    return 1;
}

// Converts 24-bit RGB to ARGB1555. Near-black is lifted so it stays opaque; magenta becomes
// transparent and flags the texture as needing alpha.
// FUNCTION: STUNTGP_D3D 0x430280
void FUN_430280(BYTE *src, WORD *dst, DWORD width, DWORD height)
{
    DWORD count = width * height;
    for (DWORD i = 0; i < count; i++)
    {
        BYTE r = src[0];
        BYTE g = src[1];
        BYTE b = src[2];
        BYTE a;
        if (r < 8 && g < 8 && b < 8)
        {
            r = g = b = 8;
            a = 0xff;
        }
        else if (r == 0xff && g == 0 && b == r)
        {
            r = 1;
            a = 0;
            b = r;
            *g_592028 = r;
        }
        else
        {
            a = 0xff;
        }
        src += 3;
        *dst = ((((a & 0x80) << 1 | (r >> 3 << 3)) << 5 | (g >> 3 << 3)) << 2) | (b >> 3);
        dst++;
    }
}

// FUNCTION: STUNTGP_D3D 0x430690
void FUN_430690()
{
    memset(g_59207c, 0, sizeof(g_59207c));
    g_592028 = g_59207c;
}

// GLOBAL: STUNTGP_D3D 0x583330
int g_583330;

// Loads an RLE packed image; the header holds the size at offsets 6 and 8.
// FUNCTION: STUNTGP_D3D 0x430330
void FUN_430330(char *path, BYTE *dst)
{
    int size = size_of_file(path);
    BYTE *data = (BYTE *)malloc(size);
    bload(path, (char *)data, size);
    FUN_4234e0(dst, data + 10);
    g_489714 = *(WORD *)(data + 6);
    g_489718 = *(WORD *)(data + 8);
    free(data);
    g_583330 = 0;
}

// GLOBAL: STUNTGP_D3D 0x46f080
// IID_IDirect3DTexture2

// GLOBAL: STUNTGP_D3D 0x5d91c0
DDPIXELFORMAT *g_5d91c0;

// STUB: STUNTGP_D3D 0x4234e0
void FUN_4234e0(BYTE *dst, BYTE *src)
{
}

// STUB: STUNTGP_D3D 0x430100
void FUN_430100(LPDIRECTDRAWSURFACE4 surface, BYTE *image, DWORD width, DWORD height, int bits)
{
}

// Uploads an image into texture slot through a system-memory staging surface.
// FUNCTION: STUNTGP_D3D 0x431560
void FUN_431560(int slot, BYTE *image)
{
    DDSURFACEDESC2 desc;
    LPDIRECT3DTEXTURE2 texture;
    LPDIRECTDRAWSURFACE4 surface;
    int res;
    memset(&desc, 0, sizeof(desc));
    desc.dwWidth = g_489714;
    surface = NULL;
    texture = NULL;
    desc.dwHeight = g_489718;
    desc.dwSize = sizeof(desc);
    desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    desc.ddpfPixelFormat = *g_5d91c0;
    desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    res = g_dd4->CreateSurface(&desc, &surface, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    FUN_430100(surface, image, g_489714, g_489718, 16);
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
    desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
    desc.dwFlags = (g_59207c[slot] ? 0x10000 : 0) + 0x101007;
    desc.ddsCaps.dwCaps2 = 0x80;
    desc.dwTextureStage = 0;
    if (g_6227d4[slot].texture)
    {
        res = g_6227d4[slot].texture->Load(texture);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
    }
    if (g_6227d4[slot].unk04[0])
    {
        res = ((LPDIRECT3DTEXTURE2)g_6227d4[slot].unk04[0])->Load(texture);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
    }
    FUN_4300f0(texture);
    ddReleaseSurface(&surface);
}

// FUNCTION: STUNTGP_D3D 0x4316f0
int FUN_4316f0(int slot, char *path)
{
    int size = size_of_file(path);
    BYTE *image = (BYTE *)malloc(0x20000);
    // STRING: STUNTGP_D3D 0x47889c
    if (strstr(path, ".TGA"))
    {
        BYTE *data = (BYTE *)malloc(size + 16);
        FUN_4623c0(path, data, &g_571fd4);
        FUN_430280(data, (WORD *)image, g_489714, g_489718);
        free(data);
    }
    else
    {
        FUN_430330(path, image);
    }
    FUN_431560(slot, image);
    free(image);
    return 1;
}

// GLOBAL: STUNTGP_D3D 0x576bdc
int g_576bdc;

// Screen-space clip rectangle, and the same grown by 100 pixels.
// GLOBAL: STUNTGP_D3D 0x576c14
float g_576c14;

// GLOBAL: STUNTGP_D3D 0x576c18
float g_576c18;

// GLOBAL: STUNTGP_D3D 0x576c1c
float g_576c1c;

// GLOBAL: STUNTGP_D3D 0x576c20
float g_576c20;

// GLOBAL: STUNTGP_D3D 0x576c24
float g_576c24;

// GLOBAL: STUNTGP_D3D 0x576c28
float g_576c28;

// GLOBAL: STUNTGP_D3D 0x576c2c
float g_576c2c;

// GLOBAL: STUNTGP_D3D 0x576c30
float g_576c30;

// Viewport layout for the split-screen modes (1 = full screen).
// FUNCTION: STUNTGP_D3D 0x424c30
void FUN_424c30(int mode)
{
    float x;
    float y;
    float w;
    float h;
    if (mode >= 17)
    {
        mode = 1;
    }
    switch (mode)
    {
    case 1:
        w = g_576bc4;
        x = 0.0f;
        y = 0.0f;
        g_576bd8 = 0;
        h = g_576bc8;
        break;
    case 2:
        w = g_576bc4;
        h = g_576bc8 * 0.5625f;
        x = (g_576bc4 - w) * 0.5f;
        y = (g_576bc8 - h) * 0.5f;
        g_576bd8 = 1;
        break;
    case 3:
        w = g_576bc4 * 0.75f;
        h = g_576bc8 * 0.75f;
        x = (g_576bc4 - w) * 0.5f;
        y = (g_576bc8 - h) * 0.5f;
        g_576bd8 = 1;
        break;
    case 4:
        w = g_576bc4 * 0.5f;
        h = g_576bc8 * 0.5f;
        x = (g_576bc4 - w) * 0.5f;
        y = (g_576bc8 - h) * 0.5f;
        g_576bd8 = 1;
        break;
    case 5:
        w = g_576bc4 * 0.25f;
        h = g_576bc8 * 0.25f;
        x = (g_576bc4 - w) * 0.5f;
        y = (g_576bc8 - h) * 0.5f;
        g_576bd8 = 1;
        break;
    case 6:
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = (g_576bc4 - w) * 0.5f;
        y = 0.0f;
        g_576bd8 = 1;
        break;
    case 7:
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = (g_576bc4 - w) * 0.5f;
        y = h;
        g_576bd8 = 1;
        break;
    case 8:
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = 0.0f;
        y = (g_576bc8 - h) * 0.5f;
        g_576bd8 = 1;
        break;
    case 9:
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = w;
        y = (g_576bc8 - h) * 0.5f;
        g_576bd8 = 1;
        break;
    case 10:
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = (g_576bc4 - w) * 0.5f;
        y = 0.0f;
        g_576bd8 = 1;
        break;
    case 11:
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = 0.0f;
        y = g_576bc8 - h;
        g_576bd8 = 1;
        break;
    case 12:
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = w;
        y = g_576bc8 - h;
        g_576bd8 = 1;
        break;
    case 13:
        y = 0.0f;
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = 0.0f;
        g_576bd8 = 1;
        break;
    case 14:
        y = 0.0f;
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = w;
        g_576bd8 = 1;
        break;
    case 15:
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = 0.0f;
        y = g_576bc8 - h;
        g_576bd8 = 1;
        break;
    case 16:
        w = g_576bc4 / 2;
        h = g_576bc8 / 2;
        x = w;
        y = g_576bc8 - h;
        g_576bd8 = 1;
        break;
    }
    g_DD_DISPLAYRESWIDTH = (int)w;
    g_DD_DISPLAYRESHEIGHT = (int)h;
    FUN_425070();
    w *= 0.5f;
    h *= 0.5f;
    g_576b9c = w;
    g_576ba0 = h;
    x = g_576be4 + x + w;
    y = g_576be8 + y + h;
    g_576b8c = (int)x;
    g_576b90 = (int)y;
    g_576b94 = x;
    g_576b98 = y;
    g_576bdc = mode;
    g_624988 = mode;
    g_62498c = mode;
    FUN_4250a0(0.0f, 0.0f, 640.0f, 480.0f);
}

// FUNCTION: STUNTGP_D3D 0x4250a0
void FUN_4250a0(float left, float top, float right, float bottom)
{
    g_clipLeft = left;
    g_clipTop = top;
    g_clipRight = right;
    g_clipBottom = bottom;
    g_576c14 = (left - 320.0f) * g_576b9c * (1.0f / 320.0f) + g_576b94;
    g_576c18 = (right - 320.0f) * g_576b9c * (1.0f / 320.0f) + g_576b94;
    g_576c1c = (top - 240.0f) * g_576ba0 * (1.0f / 240.0f) + g_576b98;
    g_576c20 = (bottom - 240.0f) * g_576ba0 * (1.0f / 240.0f) + g_576b98;
    g_576c24 = g_576c14 - 100.0f;
    g_576c28 = g_576c18 + 100.0f;
    g_576c2c = g_576c1c - 100.0f;
    g_576c30 = g_576c20 + 100.0f;
}

// FUNCTION: STUNTGP_D3D 0x425070
void FUN_425070()
{
    g_624990 = g_DD_DISPLAYRESWIDTH * (1.0f / 640.0f);
    g_624994 = g_DD_DISPLAYRESHEIGHT * (1.0f / 480.0f);
}

// FUNCTION: STUNTGP_D3D 0x427240
void FUN_427240()
{
    g_6244dc = g_6244cc;
    g_6244d8 = g_6244c8;
    g_6244e4 = g_6244d4;
    g_6244e0 = g_6244d0;
}

// FUNCTION: STUNTGP_D3D 0x427270
void FUN_427270()
{
    g_6244d4 = g_61c50c + 0x60000;
    FUN_427240();
    for (int i = 0; i < 16; i++)
    {
        g_6244a8[i] = i;
    }
}

// FUNCTION: STUNTGP_D3D 0x431a80
void FUN_431a80()
{
    FUN_423430();
}

// Outlines the display area with four lines; ends are nudged half a pixel so the corners close.
// FUNCTION: STUNTGP_D3D 0x431830
void FUN_431830(D3DCOLOR color)
{
    FUN_42f380();
    color |= 0xff000000;
    float width = (float)g_DD_DISPLAYRESWIDTH;
    float halfWidth = width * 0.5f;
    float height = (float)g_DD_DISPLAYRESHEIGHT;
    float halfHeight = height * 0.5f;
    float left = g_576b94 - halfWidth;
    float top = g_576b98 - halfHeight;
    float topEdge = top + 0.5f;
    float right = left + width - 0.5f;
    float bottom = top + height - 0.5f;
    g_58d818[0].sx = left;
    g_58d818[0].sy = topEdge;
    g_58d818[0].sz = 0.94f;
    g_58d818[0].rhw = 0.94f;
    g_58d818[0].color = color;
    g_58d818[0].specular = 0xff000000;
    g_58d818[1].sx = right + 0.5f;
    g_58d818[1].sy = topEdge;
    g_58d818[1].sz = 0.94f;
    g_58d818[1].rhw = 0.94f;
    g_58d818[1].color = color;
    g_58d818[1].specular = 0xff000000;
    g_58d818[2].sx = right;
    g_58d818[2].sy = topEdge;
    g_58d818[2].sz = 0.94f;
    g_58d818[2].rhw = 0.94f;
    g_58d818[2].color = color;
    g_58d818[2].specular = 0xff000000;
    g_58d818[3].sx = right;
    g_58d818[3].sy = bottom + 0.5f;
    g_58d818[3].sz = 0.94f;
    g_58d818[3].rhw = 0.94f;
    g_58d818[3].color = color;
    g_58d818[3].specular = 0xff000000;
    g_58d818[4].sx = right;
    g_58d818[4].sy = bottom;
    g_58d818[4].sz = 0.94f;
    g_58d818[4].rhw = 0.94f;
    g_58d818[4].color = color;
    g_58d818[4].specular = 0xff000000;
    g_58d818[5].sx = left;
    g_58d818[5].sy = bottom;
    g_58d818[5].sz = 0.94f;
    g_58d818[5].rhw = 0.94f;
    g_58d818[5].color = color;
    g_58d818[5].specular = 0xff000000;
    g_58d818[6].sx = left;
    g_58d818[6].sy = bottom;
    g_58d818[6].sz = 0.94f;
    g_58d818[6].rhw = 0.94f;
    g_58d818[6].color = color;
    g_58d818[6].specular = 0xff000000;
    g_58d818[7].sx = left;
    g_58d818[7].sy = topEdge - 0.5f;
    g_58d818[7].sz = 0.94f;
    g_58d818[7].rhw = 0.94f;
    g_58d818[7].color = color;
    g_58d818[7].specular = 0xff000000;
    FUN_432190(0x28);
    g_d3dDevice->SetTexture(0, NULL);
    g_d3dDevice->DrawPrimitive(D3DPT_LINELIST, FVF_TLVERTEX2, g_58d818, 8, D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT);
    g_61c5e4 = -1;
    if (g_624984 == 1)
    {
        FUN_42f340();
    }
}

// FUNCTION: STUNTGP_D3D 0x42f340
void FUN_42f340()
{
    if (g_589e08 != 1)
    {
        g_592050 = 1;
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 1);
    }
}

// FUNCTION: STUNTGP_D3D 0x42f380
void FUN_42f380()
{
    if (g_589e08 != 1)
    {
        g_592050 = 0;
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0xa0);
    }
}

// FUNCTION: STUNTGP_D3D 0x432190
void FUN_432190(int mode)
{
    switch (mode)
    {
    case 0x58:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
        break;
    case 0x70:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
        break;
    case 0x60:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
        break;
    case 0x48:
    case 0x50:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
        break;
    case 0x20:
    case 0x28:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
        break;
    default:
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
        break;
    }
    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

// FUNCTION: STUNTGP_D3D 0x432300
void FUN_432300(Font *font, D3DCOLOR color, DWORD flags)
{
    int texture;
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 1);
    if (!(flags & 0x14))
    {
        int mode;
        if (flags & 8)
        {
            mode = 0x60;
        }
        else
        {
            mode = 0x28;
        }
        FUN_432190(mode);
        texture = font->glyphs[0].texture;
    }
    else
    {
        FUN_432190(0x70);
        texture = font->glyphs[0].textureAlt;
    }
    if (g_61c5e4 != texture)
    {
        g_d3dDevice->SetTexture(0, g_6227d4[texture].texture);
        g_61c5e4 = texture;
    }
    FUN_42f380();
}

// FUNCTION: STUNTGP_D3D 0x432380
void FUN_432380()
{
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0xa0);
    if (g_624984 == 1)
    {
        FUN_42f340();
    }
}

// FUNCTION: STUNTGP_D3D 0x4323f0
float FUN_4323f0(Font *font, char c, float x, float y, float z, D3DCOLOR color, float scale, DWORD flags)
{
    D3DTLVERTEX2 v[4];
    Glyph *glyph = &font->glyphs[g_57b318[(BYTE)c]];
    float w = glyph->width * scale;
    float h = glyph->height * scale;

    v[0].sx = x;
    v[0].sy = y;
    v[0].sz = z;
    v[0].rhw = z;
    v[0].tu1 = glyph->u0;
    v[0].tv1 = glyph->v0;
    v[0].color = color | 0xff000000;
    v[0].specular = 0;

    v[1].sx = x + w;
    v[1].sy = y;
    v[1].sz = z;
    v[1].rhw = z;
    v[1].tu1 = glyph->u1;
    v[1].tv1 = glyph->v0;
    v[1].color = color | 0xff000000;
    v[1].specular = 0;

    v[2].sx = x + w;
    v[2].sy = y + h;
    v[2].sz = z;
    v[2].rhw = z;
    v[2].tu1 = glyph->u1;
    v[2].tv1 = glyph->v1;
    v[2].color = color | 0xff000000;
    v[2].specular = 0;

    v[3].sx = x;
    v[3].sy = y + h;
    v[3].sz = z;
    v[3].rhw = z;
    v[3].tu1 = glyph->u0;
    v[3].tv1 = glyph->v1;
    v[3].color = color | 0xff000000;
    v[3].specular = 0;

    D3DTLVERTEX2 *p = v;
    for (int i = 0; i < 4; i++)
    {
        p->sx = (p->sx - 320.0f) * g_624990 + g_576b94;
        p->sy = (p->sy - 240.0f) * g_624994 + g_576b98;
        p++;
    }
    if (flags & 2)
    {
        v[0].sx = v[0].sx + font->slantScale * font->slant * h;
        v[1].sx = v[1].sx + font->slantScale * font->slant * h;
        v[2].sx = v[2].sx - font->slantScale * font->slant * h;
        v[3].sx = v[3].sx - font->slantScale * font->slant * h;
    }
    g_d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, FVF_TLVERTEX2, v, 4, D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT);
    if (g_57b418 != 0.0f && c >= '0' && c <= '9')
    {
        return g_57b418 * scale + 1.0f;
    }
    return glyph->width * scale + 1.0f;
}

// FUNCTION: STUNTGP_D3D 0x4328c0
void FUN_4328c0(int color)
{
    D3DTLVERTEX2 v[8];
    BOOL inScene = g_d3dInScene;
    FUN_433ee0();

    float width = (float)g_576bc4;
    float height = (float)g_576bc8;
    D3DCOLOR c = RGBA_MAKE(color & 0xff, (color & 0xff00) >> 8, (color >> 16) & 0xff, 0xff);

    v[0].sx = 0.0f;
    v[0].sy = 0.0f;
    v[0].sz = 0.0f;
    v[0].rhw = 0.999f;
    v[0].color = c;
    v[0].specular = 0xff000000;

    v[1].sx = width;
    v[1].sy = 0.0f;
    v[1].sz = 0.0f;
    v[1].rhw = 0.999f;
    v[1].color = c;
    v[1].specular = 0xff000000;

    v[2].sx = width;
    v[2].sy = height;
    v[2].sz = 0.0f;
    v[2].rhw = 0.999f;
    v[2].color = c;
    v[2].specular = 0xff000000;

    v[3].sx = 0.0f;
    v[3].sy = height;
    v[3].sz = 0.0f;
    v[3].rhw = 0.999f;
    v[3].color = c;
    v[3].specular = 0xff000000;

    FUN_432190(0x28);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, FALSE);
    g_d3dDevice->SetTexture(0, NULL);
    g_d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, FVF_TLVERTEX2, v, 4, D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT);
    FUN_432a90();
    if (g_592054 == 1 || g_592058 == 1)
    {
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);
    }
    if (!inScene)
    {
        FUN_433f20();
    }
}

// FUNCTION: STUNTGP_D3D 0x432a60
void FUN_432a60()
{
    int res = g_surface->Flip(NULL, DDFLIP_WAIT);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
}

// Queued primitives per render pass.
struct RenderBucket
{
    void *data;   // 0x00
    int count;    // 0x04
    void *unk08;  // 0x08
    int unk0c;    // 0x0c
};

// Queued primitive; type 0x3f marks one that needs no depth key.
struct RenderItem
{
    DWORD unk00[4];
    int type; // 0x10
};

// GLOBAL: STUNTGP_D3D 0x6243cc
int g_6243cc;

// GLOBAL: STUNTGP_D3D 0x6243dc
int g_6243dc;

// GLOBAL: STUNTGP_D3D 0x6243e0
RenderBucket g_6243e0[8];

extern void *g_61c5f8;
extern void *g_61c600;

// STUB: STUNTGP_D3D 0x427530
void FUN_427530(RenderItem *item)
{
}

// FUNCTION: STUNTGP_D3D 0x4277b0
void FUN_4277b0(RenderItem *item, DWORD count)
{
    for (DWORD i = 0; i < count; i++)
    {
        if (item->type != 0x3f)
        {
            FUN_427530(item);
        }
        item++;
    }
}

// FUNCTION: STUNTGP_D3D 0x4277d0
void FUN_4277d0()
{
    FUN_427240();
    if (g_6243e0[0].count)
    {
        g_4722d0->unk19c = 5000000.0f;
        FUN_4277b0((RenderItem *)g_6243e0[0].data, g_6243e0[0].count);
    }
    g_4722d0->unk19c = 500000.0f;
    if (g_6243e0[2].count)
    {
        FUN_4277b0((RenderItem *)g_6243e0[2].data, g_6243e0[2].count);
    }
    if (g_6243e0[2].unk0c)
    {
        FUN_4277b0((RenderItem *)g_6243e0[2].unk08, g_6243e0[2].unk0c);
    }
    g_4722d0->unk19c = 500000.0f;
    if (g_6243e0[4].count)
    {
        FUN_4277b0((RenderItem *)g_6243e0[4].data, g_6243e0[4].count);
    }
    if (g_6243e0[4].unk0c)
    {
        FUN_4277b0((RenderItem *)g_6243e0[4].unk08, g_6243e0[4].unk0c);
    }
    if (g_6243e0[6].count)
    {
        FUN_4277b0((RenderItem *)g_6243e0[6].data, g_6243e0[6].count);
    }
    if (g_6243e0[6].unk0c)
    {
        FUN_4277b0((RenderItem *)g_6243e0[6].unk08, g_6243e0[6].unk0c);
    }
}

// STUB: STUNTGP_D3D 0x433290
void FUN_433290(void *data, int count)
{
}

// STUB: STUNTGP_D3D 0x4334c0
void FUN_4334c0(void *data, int count)
{
}

// STUB: STUNTGP_D3D 0x4336c0
void FUN_4336c0(void *data, int count)
{
}

// STUB: STUNTGP_D3D 0x4338e0
void FUN_4338e0(void *data, int count)
{
}

// STUB: STUNTGP_D3D 0x433c50
void FUN_433c50(void *data, int count)
{
}

// Draws the queued world primitives pass by pass.
// FUNCTION: STUNTGP_D3D 0x433f40
void FUN_433f40()
{
    FUN_432a90();
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0xa0);
    FUN_433290(g_6243e0[0].data, g_6243e0[0].count);
    FUN_4334c0(g_6243e0[2].data, g_6243e0[2].count);
    FUN_4334c0(g_6243e0[3].data, g_6243e0[3].count);
    if (g_624984 == 1)
    {
        FUN_4336c0(g_6243e0[4].data, g_6243e0[4].count);
        FUN_4336c0(g_6243e0[5].data, g_6243e0[5].count);
    }
    else
    {
        FUN_4334c0(g_6243e0[4].data, g_6243e0[4].count);
        FUN_4334c0(g_6243e0[5].data, g_6243e0[5].count);
    }
    FUN_433c50(g_6243e0[6].data, g_6243e0[6].count);
    FUN_433c50(g_6243e0[7].data, g_6243e0[7].count);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 1);
    FUN_4338e0(g_61c600, g_6243cc);
    FUN_4338e0(g_61c5f8, g_6243dc);
}

// FUNCTION: STUNTGP_D3D 0x432a90
void FUN_432a90()
{
    if (g_5d91b4[25])
    {
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_GREATEREQUAL);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
        g_477ccc = 128.0f;
        g_59205c = 1;
        g_592060 = 1;
        g_592064 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x4327c0
void FUN_4327c0(WORD *pixels, DWORD width, DWORD height)
{
    DWORD count = width * height;
    for (DWORD i = 0; i < count; i++)
    {
        *pixels ^= 0x7fff;
        pixels++;
    }
}

// Creates a video-memory texture from an image and returns its texture slot.
// FUNCTION: STUNTGP_D3D 0x4325e0
int FUN_4325e0(BYTE *image, DWORD width, DWORD height)
{
    DDSURFACEDESC2 desc;
    LPDIRECT3DTEXTURE2 stagingTexture;
    LPDIRECTDRAWSURFACE4 surface;
    LPDIRECT3DTEXTURE2 texture;
    LPDIRECTDRAWSURFACE4 staging;
    int res;
    SurfaceSlot *slot = &g_surfaceSlots[g_surfaceSlotCount++];
    memset(&desc, 0, sizeof(desc));
    staging = NULL;
    surface = NULL;
    stagingTexture = NULL;
    texture = NULL;
    desc.dwWidth = width;
    desc.dwHeight = height;
    desc.dwSize = sizeof(desc);
    desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    desc.ddpfPixelFormat = *g_5d91c0;
    desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    res = g_dd4->CreateSurface(&desc, &staging, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    FUN_430100(staging, image, width, height, 16);
    res = staging->QueryInterface(IID_IDirect3DTexture2, (void **)&stagingTexture);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    res = staging->GetSurfaceDesc(&desc);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_CKSRCBLT;
    desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
    res = g_dd4->CreateSurface(&desc, &surface, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    res = surface->QueryInterface(IID_IDirect3DTexture2, (void **)&texture);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    res = texture->Load(stagingTexture);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    FUN_4300f0(stagingTexture);
    ddReleaseSurface(&staging);
    slot->unk04 = (DWORD)texture;
    slot->surface = surface;
    g_6243b8->texture = texture;
    g_6243b8++;
    return g_6243b8 - g_6227d4 - 1;
}

// FUNCTION: STUNTGP_D3D 0x4327e0
void FUN_4327e0(BYTE *texture, Font *font, int arg)
{
    if (g_58332c == 1)
    {
        FUN_430280(texture, (WORD *)texture, 256, 256);
        font->glyphs[0].texture = FUN_4325e0(texture, 256, 256);
        FUN_4327c0((WORD *)texture, 256, 256);
        font->glyphs[0].textureAlt = FUN_4325e0(texture, 256, 256);
    }
}

// FUNCTION: STUNTGP_D3D 0x432840
void FUN_432840(BYTE *texture, Font *font, int arg)
{
    g_489714 = 256;
    g_489718 = 256;
    if (g_58332c == 1)
    {
        FUN_430280(texture, (WORD *)texture, 256, 256);
        FUN_431560(font->glyphs[0].texture, texture);
        FUN_4327c0((WORD *)texture, 256, 256);
        FUN_431560(font->glyphs[0].textureAlt, texture);
    }
}

// FUNCTION: STUNTGP_D3D 0x432af0
void FUN_432af0(D3DTLVERTEX2 *verts, SpriteDesc *desc)
{
    float m[16];
    float x;
    float y;
    float rx;
    float ry;
    float dx;
    float dy;
    int i;
    DWORD flags = desc->flags;
    DWORD rotate = flags & 1;
    if (rotate)
    {
        Matrix_RotationZ(m, desc->angle);
    }
    D3DCOLOR color;
    if (flags & 0x20)
    {
        color = desc->color;
    }
    else
    {
        color = 0xffffffff;
    }
    DWORD scale = flags & 8;
    for (i = 0; i < 4; i++)
    {
        x = desc->points[i].x;
        verts[i].sx = x;
        y = desc->points[i].y;
        verts[i].sy = y;
        if (rotate)
        {
            dx = x - desc->originX;
            dy = y - desc->originY;
            rx = dx * m[0] + dy * m[4] + m[12];
            ry = dx * m[1] + dy * m[5] + m[13];
            verts[i].sx = rx + desc->originX;
            verts[i].sy = ry + desc->originY;
        }
        if (scale)
        {
            verts[i].sx = (verts[i].sx - desc->originX) * desc->scaleX + desc->originX;
            verts[i].sy = (verts[i].sy - desc->originY) * desc->scaleY + desc->originY;
        }
        verts[i].sx = verts[i].sx + desc->x;
        verts[i].sy = verts[i].sy + desc->y;
        verts[i].sz = desc->z;
        verts[i].rhw = desc->z;
        verts[i].color = color;
        verts[i].specular = 0;
        verts[i].tu1 = desc->points[i].u * (1.0f / 1024.0f);
        verts[i].tv1 = desc->points[i].v * (1.0f / 1024.0f);
    }
}

// FUNCTION: STUNTGP_D3D 0x432c00
void FUN_432c00(D3DTLVERTEX2 *verts, SpriteDesc *desc)
{
    float m[16];
    int i;
    D3DTLVERTEX2 *v;
    float z = desc->z;
    D3DCOLOR color;
    if (desc->flags & 0x20)
    {
        color = desc->color;
    }
    else
    {
        color = 0xffffffff;
    }
    float u0 = (desc->u0 + 1.0f) * (1.0f / 1024.0f);
    float v0 = (desc->v0 + 1.0f) * (1.0f / 1024.0f);
    float u1 = (desc->u1 - 1.0f) * (1.0f / 1024.0f);
    float v1 = (desc->v1 - 1.0f) * (1.0f / 1024.0f);
    verts[0].sx = 0.0f;
    verts[0].sy = 0.0f;
    verts[1].sx = desc->width;
    verts[1].sy = 0.0f;
    verts[2].sx = desc->width;
    verts[2].sy = desc->height;
    verts[3].sx = 0.0f;
    verts[3].sy = desc->height;
    if (desc->flags & 1)
    {
        Matrix_RotationZ(m, desc->angle);
        v = verts;
        for (i = 4; i > 0; i--)
        {
            float dx = v->sx - desc->originX;
            float dy = v->sy - desc->originY;
            float rx = dy * m[4] + dx * m[0] + m[12];
            float ry = dy * m[5] + dx * m[1] + m[13];
            v->sx = rx + desc->originX;
            v->sy = ry + desc->originY;
            v++;
        }
    }
    if (desc->flags & 8)
    {
        v = verts;
        for (i = 4; i > 0; i--)
        {
            v->sx = (v->sx - desc->originX) * desc->scaleX + desc->originX;
            v->sy = (v->sy - desc->originY) * desc->scaleY + desc->originY;
            v++;
        }
    }
    float x = desc->x;
    float y = desc->y;
    v = verts;
    v->sx = x + v->sx;
    v->sy = y + v->sy;
    v->sz = z;
    v->rhw = z;
    v->color = color;
    v->specular = 0;
    v->tu1 = u0;
    v->tv1 = v0;
    v++;
    v->sx = x + v->sx;
    v->sy = y + v->sy;
    v->sz = z;
    v->rhw = z;
    v->color = color;
    v->specular = 0;
    v->tu1 = u1;
    v->tv1 = v0;
    v++;
    v->sx = x + v->sx;
    v->sy = y + v->sy;
    v->sz = z;
    v->rhw = z;
    v->color = color;
    v->specular = 0;
    v->tu1 = u1;
    v->tv1 = v1;
    v++;
    v->sx = x + v->sx;
    v->sy = y + v->sy;
    v->sz = z;
    v->rhw = z;
    v->color = color;
    v->specular = 0;
    v->tu1 = u0;
    v->tv1 = v1;
}

// FUNCTION: STUNTGP_D3D 0x432e00
void FUN_432e00(SpriteDesc *desc)
{
    SpriteDesc d = *desc;
    if (!(d.flags & 0x40) && !FUN_4251a0(&d))
    {
        return;
    }
    if (d.flags & 4)
    {
        FUN_432af0(g_58d818, &d);
    }
    else
    {
        FUN_432c00(g_58d818, &d);
    }
    FUN_432190(d.blendMode);
    if (d.blendMode & 0x40)
    {
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 1);
    }
    else
    {
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0xa0);
    }
    int tex = d.texture;
    if (g_61c5e4 != tex)
    {
        g_d3dDevice->SetTexture(0, g_6227d4[tex].texture);
        g_61c5e4 = tex;
    }
    for (int i = 0; i < 4; i++)
    {
        D3DTLVERTEX2 *v = &g_58d818[i];
        v->sx = (v->sx - 320.0f) * g_624990 + g_576b94;
        v->sy = (v->sy - 240.0f) * g_624994 + g_576b98;
        if (d.blendMode & 0x40)
        {
            v->color = (v->color & 0xffffff) | (d.alpha << 24);
        }
        v->specular |= 0xff000000;
    }
    g_d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, FVF_TLVERTEX2, g_58d818, 4, D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT);
    if (d.blendMode & 0x40)
    {
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
    }
}

// FUNCTION: STUNTGP_D3D 0x432f60
void FUN_432f60()
{
    D3DTLVERTEX2 v[8];
    DWORD mode;
    DWORD i;
    OverlayPoly *poly;

    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 1);
    poly = g_61c5f0;
    mode = 0xffffffff;
    for (i = 0; i < g_61c604; i++)
    {
        DWORD alpha = poly->alpha << 24;
        OverlayVertex *src = poly->verts;
        D3DTLVERTEX2 *dst = v;
        for (DWORD j = poly->numVerts; j > 0; j--)
        {
            dst->sx = src->x;
            dst->sy = src->y;
            dst->sz = src->z;
            dst->rhw = src->z;
            dst->tu1 = src->u;
            dst->tv1 = src->v;
            dst->color = src->color | alpha;
            dst->specular = 0xff000000;
            src++;
            dst++;
        }
        DWORD newMode = poly->flags & 0x78;
        if (mode != newMode)
        {
            mode = newMode;
            FUN_432190(newMode);
        }
        int tex = poly->texture;
        if (g_61c5e4 != tex)
        {
            g_d3dDevice->SetTexture(0, g_6227d4[tex].texture);
            g_61c5e4 = tex;
        }
        g_d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, FVF_TLVERTEX2, v, poly->numVerts,
                                   D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT);
        poly++;
    }
    if (poly->flags & 0x40)
    {
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
    }
    FUN_425870();
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0xa0);
}

// FUNCTION: STUNTGP_D3D 0x433ee0
void FUN_433ee0()
{
    if (g_d3dInScene != TRUE)
    {
        g_d3dInScene = TRUE;
        int res = g_d3dDevice->BeginScene();
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x433f20
void FUN_433f20()
{
    if (g_d3dInScene)
    {
        g_d3dInScene = FALSE;
        g_d3dDevice->EndScene();
    }
}

// GLOBAL: STUNTGP_D3D 0x61c7cc
BYTE g_61c7cc[0x6000];

// GLOBAL: STUNTGP_D3D 0x6227cc
BYTE *g_6227cc = NULL;

// GLOBAL: STUNTGP_D3D 0x6227d0
int g_6227d0 = 0;

// FUNCTION: STUNTGP_D3D 0x44fd60
void FUN_44fd60()
{
    g_6227cc = g_61c7cc;
    g_6227d0 = 0;
}

// FUNCTION: STUNTGP_D3D 0x425870
void FUN_425870()
{
    g_61c604 = 0;
}

// FUNCTION: STUNTGP_D3D 0x42e420
void FUN_42e420()
{
    g_61c5e4 = -1;
}
