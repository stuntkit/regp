#include "d3drender.h"
#include "common.h"
#include "sprite.h"
#include "font.h"
#include "globals.h"
#include "windowInit.h"
#include "vecmath.h"
#include "surface.h"
#include "mem.h"
#include "Game/GameEngine/io_wad.h"
#include "Game/GameEngine/GameSetup.h"
#include "Game/GameEngine/GameUpdate.h"
#include "Game/GameEngine/RenderState.h"

#include <math.h>
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

// GLOBAL: STUNTGP_D3D 0x592068
int g_592068;

// GLOBAL: STUNTGP_D3D 0x59206c
int g_59206c;

// GLOBAL: STUNTGP_D3D 0x592070
int g_592070;

// GLOBAL: STUNTGP_D3D 0x592074
int g_592074;

// GLOBAL: STUNTGP_D3D 0x592078
int g_592078;

// Four corner records reset by FUN_425ae0.
extern int g_6249a4;

// GLOBAL: STUNTGP_D3D 0x5775d0
float g_5775d0[4][8];

// GLOBAL: STUNTGP_D3D 0x577660
int g_577660[10];

// GLOBAL: STUNTGP_D3D 0x583990
char g_583990[0x4000];

// GLOBAL: STUNTGP_D3D 0x587990
int g_587990;

// GLOBAL: STUNTGP_D3D 0x587994
int g_587994;

// GLOBAL: STUNTGP_D3D 0x5895b0
ImageLoader g_5895b0;

// GLOBAL: STUNTGP_D3D 0x5ba788
DisplayDevices g_5ba788;

// Display modes collected by FUN_42f3c0.
struct DisplayModeList
{
    BYTE unk000[0x360];
    DWORD count;                // 0x360
    DDSURFACEDESC2 modes[64];   // 0x364
};

// Texture formats collected by FUN_42f780.
struct TextureFormatList
{
    BYTE unk000[0x170];
    DWORD count;               // 0x170
    DDPIXELFORMAT formats[16]; // 0x174
};

// Z-buffer formats collected by FUN_42fe40; one per Direct3D driver of a
// DirectDraw device, 0x478 bytes apart from devices[i] + 0x2274.
struct ZBufferFormatList
{
    BYTE unk000[0x64];
    int unk064;                // 0x064
    BYTE unk068[0x374 - 0x68];
    DWORD count;               // 0x374
    DDPIXELFORMAT formats[8];  // 0x378
};

// Name storage for g_textureFiles.
// GLOBAL: STUNTGP_D3D 0x57eb0c
char g_57eb0c[0x1fe0];

// GLOBAL: STUNTGP_D3D 0x582710
ResourceFile *g_582710;

// GLOBAL: STUNTGP_D3D 0x58332c
int g_58332c = 0;

// Per texture slot: set when the texture has transparent texels.
// GLOBAL: STUNTGP_D3D 0x59207c
BYTE g_59207c[255];

// GLOBAL: STUNTGP_D3D 0x592028
BYTE *g_592028;

// GLOBAL: STUNTGP_D3D 0x592050
int g_592050 = 0;

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

// GLOBAL: STUNTGP_D3D 0x576b8c
int g_576b8c = 0;

// GLOBAL: STUNTGP_D3D 0x576b90
int g_576b90 = 0;

// GLOBAL: STUNTGP_D3D 0x576b9c
float g_576b9c = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576ba0
float g_576ba0 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576ba4
float g_576ba4 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576ba8
float g_576ba8 = 0.0f;

// GLOBAL: STUNTGP_D3D 0x576bac
int g_576bac = 0;

// GLOBAL: STUNTGP_D3D 0x576bb0
int g_576bb0 = 0;

// GLOBAL: STUNTGP_D3D 0x576bb4
int g_576bb4 = 0;

// GLOBAL: STUNTGP_D3D 0x576bb8
int g_576bb8 = 0;

// GLOBAL: STUNTGP_D3D 0x576bc0
int g_576bc0 = 0;

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

// GLOBAL: STUNTGP_D3D 0x582718
TextureSlots g_582718;

// Write position in g_582b28.
// GLOBAL: STUNTGP_D3D 0x582f24
char **g_582f24;

// GLOBAL: STUNTGP_D3D 0x582f28
char *g_582f28[255];

// Write position in g_582f28.
// GLOBAL: STUNTGP_D3D 0x583324
char **g_583324;

// GLOBAL: STUNTGP_D3D 0x583328
int g_583328;

// GLOBAL: STUNTGP_D3D 0x583334
TextureEntry g_583334[50];

// Write position in g_583334.
// GLOBAL: STUNTGP_D3D 0x58358c
TextureEntry *g_58358c;

// Records a font file so it can be reloaded when surfaces are lost.
// FUNCTION: STUNTGP_D3D 0x42be90
void FUN_42be90(char *path)
{
    g_5895bc->name = g_580aec;
    g_5895bc->slot = g_582718.unk04;
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
// Converts 24-bit pixels to RGB565; near-black is lifted and magenta becomes the colour key.
// FUNCTION: STUNTGP_D3D 0x4301f0
void FUN_4301f0(BYTE *src, WORD *dst, DWORD width, DWORD height)
{
    DWORD count = width * height;
    for (DWORD i = 0; i < count; i++)
    {
        BYTE r = src[0];
        BYTE g = src[1];
        BYTE b = src[2];
        if (r < 8 && g < 8 && b < 8)
        {
            r = g = b = 8;
        }
        else if (r == 0xff && g == 0 && b == r)
        {
            r = 1;
            b = r;
            *g_592028 = r;
        }
        src += 3;
        *dst = (((WORD)r & ~7) << 5 | ((WORD)g & ~3)) << 3 | (WORD)(b >> 3);
        dst++;
    }
}

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

// FUNCTION: STUNTGP_D3D 0x4306b0
int FUN_4306b0(int a, int b, int c, int d, int e)
{
    return 1;
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
    FUN_4234e0((WORD *)dst, (WORD *)(data + 10));
    g_489714 = *(WORD *)(data + 6);
    g_489718 = *(WORD *)(data + 8);
    free(data);
    g_583330 = 0;
}

// GLOBAL: STUNTGP_D3D 0x46f080
// IID_IDirect3DTexture2

// One token of the image packing: a run of literal words (top bit set), then either a back reference of
// 2..9 words (bit 14 set, 11 bit distance) or a run of zero words, a zero count ending the image.
#define UNPACK_STEP()                                                                                                 \
    w = *s;                                                                                                            \
    while (w & 0x8000)                                                                                                 \
    {                                                                                                                  \
        s++;                                                                                                           \
        *d++ = w;                                                                                                      \
        w = *s;                                                                                                        \
    }                                                                                                                  \
    w = *s++;                                                                                                          \
    if (w & 0x4000)                                                                                                    \
    {                                                                                                                  \
        WORD *from = d - ((w & 0x7ff) + 1);                                                                            \
        switch (((w >> 11) & 7) + 1)                                                                                   \
        {                                                                                                              \
        case 8:                                                                                                        \
            *d++ = *from++;                                                                                            \
        case 7:                                                                                                        \
            *d++ = *from++;                                                                                            \
        case 6:                                                                                                        \
            *d++ = *from++;                                                                                            \
        case 5:                                                                                                        \
            *d++ = *from++;                                                                                            \
        case 4:                                                                                                        \
            *d++ = *from++;                                                                                            \
        case 3:                                                                                                        \
            *d++ = *from++;                                                                                            \
        case 2:                                                                                                        \
            *d++ = *from++;                                                                                            \
        case 1:                                                                                                        \
            *d++ = *from++;                                                                                            \
        case 0:                                                                                                        \
            *d++ = *from;                                                                                              \
        }                                                                                                              \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        n = w & 0x3fff;                                                                                                \
        if (!n)                                                                                                        \
        {                                                                                                              \
            break;                                                                                                     \
        }                                                                                                              \
        memset(d, 0, n << 1);                                                                                           \
        d += n;                                                                                                        \
    }

// Unpacks an image into dst and returns its length in words.
// FUNCTION: STUNTGP_D3D 0x4234e0
int FUN_4234e0(WORD *d, WORD *s)
{
    WORD *start = d;
    WORD w;
    unsigned int n;
    *d++ = *s++;
    for (;;)
    {
        UNPACK_STEP()
        UNPACK_STEP()
        UNPACK_STEP()
        UNPACK_STEP()
    }
    return d - start;
}

// Copies a packed image into a locked surface row by row, honouring its pitch.
// FUNCTION: STUNTGP_D3D 0x430100
void FUN_430100(LPDIRECTDRAWSURFACE4 surface, BYTE *image, int width, int height, int bits)
{
    DDSURFACEDESC2 desc;
    desc.dwSize = sizeof(desc);
    int res = surface->Lock(NULL, &desc, DDLOCK_WAIT, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    if (desc.dwFlags & DDSD_PITCH)
    {
        int bpp = bits / 8;
        int pitch = desc.lPitch;
        BYTE *dst = (BYTE *)desc.lpSurface;
        int rowBytes = bpp * width;
        for (int y = 0; y < height; y++)
        {
            int offset = 0;
            for (int x = 0; x < width; x++)
            {
                for (int k = 0; k < bpp; k++)
                {
                    dst[offset] = image[offset];
                    offset++;
                }
            }
            image += rowBytes;
            dst += pitch;
        }
        surface->Unlock(NULL);
    }
}

// Loads a width x height image (RLE packed when g_583330 is set, else a TGA) into a new
// video-memory texture (and a second-stage copy when the device supports it) in the next
// surface slot and texture slot.
// FUNCTION: STUNTGP_D3D 0x4303a0
int FUN_4303a0(int width, int height, int index, int unk, char *path)
{
    DDSURFACEDESC2 desc;
    LPDIRECTDRAWSURFACE4 sysSurface = NULL;
    LPDIRECTDRAWSURFACE4 surface = NULL;
    LPDIRECT3DTEXTURE2 sysTexture = NULL;
    LPDIRECT3DTEXTURE2 texture = NULL;
    int res;
    BYTE *image = (BYTE *)Mem_Alloc(width * height * 3 + 0x100, 0);
    if (g_583330 == 1)
    {
        FUN_430330(path, image);
    }
    else
    {
        FUN_4623c0(path, image, &g_571fd4);
        FUN_430280(image, (WORD *)image, width, height);
    }
    SurfaceSlot *slot = &g_5ba788.surfaceSlots[g_5ba788.surfaceSlotCount++];
    memset(&desc, 0, sizeof(desc));
    desc.dwWidth = width;
    desc.dwSize = sizeof(desc);
    desc.dwHeight = height;
    desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    desc.ddpfPixelFormat = *g_5ba788.textureFormat;
    desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    res = g_dd4->CreateSurface(&desc, &sysSurface, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    FUN_430100(sysSurface, image, width, height, 16);
    Mem_Free(image);
    res = sysSurface->QueryInterface(IID_IDirect3DTexture2, (void **)&sysTexture);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    res = sysSurface->GetSurfaceDesc(&desc);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    desc.dwFlags = (*g_592028 ? DDSD_CKSRCBLT : 0) + 0x101007;
    desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
    desc.ddsCaps.dwCaps2 = 0x80;
    desc.dwTextureStage = 0;
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
    res = texture->Load(sysTexture);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    slot->unk04 = (DWORD)texture;
    slot->surface = surface;
    g_renderState.unk7ed0->texture = texture;
    g_renderState.unk7ed0->unk04[0] = (DWORD)texture;
    *(WORD *)&g_renderState.unk7ed0->unk04[1] = width;
    if (g_5ba788.deviceDesc[29] & 0x4000)
    {
        LPDIRECTDRAWSURFACE4 surface2 = NULL;
        LPDIRECT3DTEXTURE2 texture2 = NULL;
        desc.dwTextureStage = 1;
        res = g_dd4->CreateSurface(&desc, &surface2, NULL);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
        res = surface2->QueryInterface(IID_IDirect3DTexture2, (void **)&texture2);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
        res = texture2->Load(sysTexture);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
        slot->unk0c = (DWORD)texture2;
        slot->surface2 = surface2;
        g_renderState.unk7ed0->unk04[0] = (DWORD)texture2;
    }
    FUN_4300f0(sysTexture);
    ddReleaseSurface(&sysSurface);
    g_renderState.unk7ed0++;
    g_592028++;
    return 1;
}

void FUN_42be20(char *path);

// Loads count textures from path (at least one), through FUN_4303a0 when g_58332c is set;
// returns the number loaded.
// FUNCTION: STUNTGP_D3D 0x4306c0
DWORD FUN_4306c0(int width, int height, DWORD count, int unk, char *path)
{
    FUN_42be20(path);
    DWORD i = 0;
    if (count)
    {
        count--;
    }
    do
    {
        if (g_58332c == 1)
        {
            FUN_4303a0(width, height, i, unk, path);
        }
        else
        {
            FUN_4306b0(width, height, i, unk, (int)path);
        }
    } while (i++ < count);
    return i;
}

// Creates an empty size x size video-memory texture (and a second-stage copy when the device
// supports it) in the next surface slot and texture slot.
// FUNCTION: STUNTGP_D3D 0x430730
int FUN_430730(int size, int unk)
{
    DDSURFACEDESC2 desc;
    LPDIRECTDRAWSURFACE4 sysSurface = NULL;
    LPDIRECTDRAWSURFACE4 surface = NULL;
    LPDIRECT3DTEXTURE2 sysTexture = NULL;
    LPDIRECT3DTEXTURE2 texture = NULL;
    int res;
    SurfaceSlot *slot = &g_5ba788.surfaceSlots[g_5ba788.surfaceSlotCount++];
    memset(&desc, 0, sizeof(desc));
    desc.dwWidth = size;
    desc.dwHeight = size;
    desc.dwSize = sizeof(desc);
    desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    desc.ddpfPixelFormat = *g_5ba788.textureFormat;
    desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    res = g_dd4->CreateSurface(&desc, &sysSurface, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    res = sysSurface->QueryInterface(IID_IDirect3DTexture2, (void **)&sysTexture);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    res = sysSurface->GetSurfaceDesc(&desc);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    desc.dwFlags = (*g_592028 ? DDSD_CKSRCBLT : 0) + 0x101007;
    desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
    desc.ddsCaps.dwCaps2 = 0x80;
    desc.dwTextureStage = 0;
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
    res = texture->Load(sysTexture);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    slot->unk04 = (DWORD)texture;
    slot->surface = surface;
    g_renderState.unk7ed0->texture = texture;
    g_renderState.unk7ed0->unk04[0] = (DWORD)texture;
    *(WORD *)&g_renderState.unk7ed0->unk04[1] = size;
    if (g_5ba788.deviceDesc[29] & 0x4000)
    {
        LPDIRECTDRAWSURFACE4 surface2 = NULL;
        LPDIRECT3DTEXTURE2 texture2 = NULL;
        desc.dwTextureStage = 1;
        res = g_dd4->CreateSurface(&desc, &surface2, NULL);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
        res = surface2->QueryInterface(IID_IDirect3DTexture2, (void **)&texture2);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
        res = texture2->Load(sysTexture);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
        slot->unk0c = (DWORD)texture2;
        slot->surface2 = surface2;
        g_renderState.unk7ed0->unk04[0] = (DWORD)texture2;
    }
    FUN_4300f0(sysTexture);
    ddReleaseSurface(&sysSurface);
    g_renderState.unk7ed0++;
    g_592028++;
    return 1;
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
    desc.ddpfPixelFormat = *g_5ba788.textureFormat;
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
    if (g_renderState.unk62ec[slot].texture)
    {
        res = g_renderState.unk62ec[slot].texture->Load(texture);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
    }
    if (g_renderState.unk62ec[slot].unk04[0])
    {
        res = ((LPDIRECT3DTEXTURE2)g_renderState.unk62ec[slot].unk04[0])->Load(texture);
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
    g_renderState.unk7ff4 = g_renderState.unk7fe4;
    g_renderState.unk7ff0 = g_renderState.unk7fe0;
    g_renderState.unk7ffc = g_renderState.unk7fec;
    g_renderState.unk7ff8 = g_renderState.unk7fe8;
}

// FUNCTION: STUNTGP_D3D 0x427270
void FUN_427270()
{
    g_renderState.unk7fec = g_renderState.unk24 + 0x60000;
    FUN_427240();
    for (int i = 0; i < 16; i++)
    {
        g_renderState.unk7fc0[i] = i;
    }
}

// FUNCTION: STUNTGP_D3D 0x427520
void FUN_427520(int *p)
{
    *p = 0;
}

// FUNCTION: STUNTGP_D3D 0x431a80
void FUN_431a80()
{
    FUN_423430();
}

void FUN_42fa00();

// FUNCTION: STUNTGP_D3D 0x431a90
void FUN_431a90()
{
    FUN_42fa00();
}

// GLOBAL: STUNTGP_D3D 0x592018
Vec4 g_592018;

// GLOBAL: STUNTGP_D3D 0x592030
Vec4 g_592030;

// GLOBAL: STUNTGP_D3D 0x592040
Vec4 g_592040;

// Moves g_592040 the fraction t of the way towards g_592030.
// FUNCTION: STUNTGP_D3D 0x431aa0
void FUN_431aa0(float t)
{
    Vec4 step;
    g_592018.x = g_592030.x - g_592040.x;
    g_592018.y = g_592030.y - g_592040.y;
    g_592018.z = g_592030.z - g_592040.z;
    step.x = g_592018.x * t;
    step.y = g_592018.y * t;
    step.z = g_592018.z * t;
    g_592040.x += step.x;
    g_592040.y += step.y;
    g_592040.z += step.z;
}

// Moves g_592030 the fraction t of the way towards g_592040.
// FUNCTION: STUNTGP_D3D 0x431b40
void FUN_431b40(float t)
{
    Vec4 step;
    g_592018.x = g_592030.x - g_592040.x;
    g_592018.y = g_592030.y - g_592040.y;
    g_592018.z = g_592030.z - g_592040.z;
    step.x = g_592018.x * t;
    step.y = g_592018.y * t;
    step.z = g_592018.z * t;
    g_592030.x -= step.x;
    g_592030.y -= step.y;
    g_592030.z -= step.z;
}

// Clips the screen-space segment (x0, y0, z0)-(x1, y1, z1) to the display inset by a pixel,
// in place; returns 0 when it lies wholly outside.
// FUNCTION: STUNTGP_D3D 0x431be0
int FUN_431be0(float *x0, float *y0, float *z0, float *x1, float *y1, float *z1)
{
    float right = g_576ba4 - 1.0f;
    float bottom = g_576ba8 - 1.0f;
    g_592040.x = *x0;
    g_592040.y = *y0;
    g_592040.z = *z0;
    g_592030.x = *x1;
    g_592030.y = *y1;
    g_592030.z = *z1;
    if (g_592040.x < 1.0f && g_592030.x < 1.0f)
    {
        return 0;
    }
    if (g_592040.x > right && g_592030.x > right)
    {
        return 0;
    }
    if (g_592040.y < 1.0f && g_592030.y < 1.0f)
    {
        return 0;
    }
    if (g_592040.y > bottom && g_592030.y > bottom)
    {
        return 0;
    }
    if (g_592040.x < 1.0f)
    {
        FUN_431aa0((1.0f - g_592040.x) / (float)fabs(g_592030.x - g_592040.x));
    }
    if (g_592030.x < 1.0f)
    {
        FUN_431b40((1.0f - g_592030.x) / (float)fabs(g_592030.x - g_592040.x));
    }
    if (g_592040.x > right)
    {
        FUN_431aa0((g_592040.x - right) / (float)fabs(g_592030.x - g_592040.x));
    }
    if (g_592030.x > right)
    {
        FUN_431b40((g_592030.x - right) / (float)fabs(g_592030.x - g_592040.x));
    }
    if (g_592040.y < 1.0f)
    {
        FUN_431aa0((1.0f - g_592040.y) / (float)fabs(g_592030.y - g_592040.y));
    }
    if (g_592030.y < 1.0f)
    {
        FUN_431b40((1.0f - g_592030.y) / (float)fabs(g_592030.y - g_592040.y));
    }
    if (g_592040.y > bottom)
    {
        FUN_431aa0((g_592040.y - bottom) / (float)fabs(g_592030.y - g_592040.y));
    }
    if (g_592030.y > bottom)
    {
        FUN_431b40((g_592030.y - bottom) / (float)fabs(g_592030.y - g_592040.y));
    }
    *x0 = g_592040.x;
    *y0 = g_592040.y;
    *z0 = g_592040.z;
    *x1 = g_592030.x;
    *y1 = g_592030.y;
    *z1 = g_592030.z;
    return 1;
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
    g_renderState.unkfc = -1;
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

// FUNCTION: STUNTGP_D3D 0x42f3c0
HRESULT WINAPI FUN_42f3c0(LPDDSURFACEDESC2 desc, LPVOID context)
{
    DisplayModeList *list = (DisplayModeList *)context;
    if (list->count >= 64)
    {
        return DDENUMRET_CANCEL;
    }
    list->modes[list->count] = *desc;
    list->count++;
    return DDENUMRET_OK;
}

HRESULT WINAPI FUN_42f420(GUID *guid, LPSTR description, LPSTR name, LPD3DDEVICEDESC hw, LPD3DDEVICEDESC hel, LPVOID context);

// Records one DirectDraw device: its caps, display modes and, when it has Direct3D, its drivers.
// FUNCTION: STUNTGP_D3D 0x42f530
BOOL WINAPI FUN_42f530(GUID *guid, LPSTR description, LPSTR name, LPVOID context, HMONITOR monitor)
{
    DisplayDevices *devices = (DisplayDevices *)context;
    LPDIRECTDRAW dd;
    LPDIRECT3D3 d3d;
    LPDIRECTDRAW4 dd4;
    BYTE *dev = devices->devices[devices->count];
    int res = DirectDrawCreate(guid, &dd, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    res = dd->QueryInterface(IID_IDirectDraw4, (LPVOID *)&dd4);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    if (guid)
    {
        *(GUID *)(dev + 0x300) = *guid;
    }
    strncpy((char *)dev + 0x310, description, 0x40);
    strncpy((char *)dev + 0x350, name, 0x10);
    DDCAPS *driverCaps = (DDCAPS *)(dev + 8);
    memset(driverCaps, 0, sizeof(DDCAPS));
    DDCAPS *helCaps = (DDCAPS *)(dev + 0x184);
    memset(helCaps, 0, sizeof(DDCAPS));
    driverCaps->dwSize = sizeof(DDCAPS);
    helCaps->dwSize = sizeof(DDCAPS);
    dd4->GetCaps(driverCaps, helCaps);
    ((DisplayModeList *)dev)->count = 0;
    dd4->EnumDisplayModes(DDEDM_REFRESHRATES, NULL, dev, FUN_42f3c0);
    *(int *)dev = guid == NULL;
    if (dd4->QueryInterface(IID_IDirect3D3, (LPVOID *)&d3d) == DD_OK)
    {
        *(int *)(dev + 4) = 1;
        *(LPDIRECT3D3 *)(dev + 0x2264) = d3d;
        *(DWORD *)(dev + 0x2270) = 0;
        d3d->EnumDevices(FUN_42f420, dev);
    }
    else
    {
        *(int *)(dev + 4) = 0;
    }
    devices->count++;
    dd4->Release();
    dd->Release();
    return TRUE;
}

HRESULT WINAPI FUN_42fe40(LPDDPIXELFORMAT format, LPVOID context);

// Direct3D device enumeration callback; records up to six drivers of a DirectDraw device.
// FUNCTION: STUNTGP_D3D 0x42f420
HRESULT WINAPI FUN_42f420(GUID *guid, LPSTR description, LPSTR name, LPD3DDEVICEDESC hw, LPD3DDEVICEDESC hel, LPVOID context)
{
    BYTE *dev = (BYTE *)context;
    D3DDriver *drv = (D3DDriver *)(dev + 0x2274) + *(DWORD *)(dev + 0x2270);
    if (*(DWORD *)(dev + 0x2270) >= 6)
    {
        return D3DENUMRET_CANCEL;
    }
    drv->guid = *guid;
    strncpy(drv->description, description, sizeof(drv->description));
    strncpy(drv->name, name, sizeof(drv->name));
    if (hw->dcmColorModel)
    {
        drv->hardware = 1;
        drv->desc = *hw;
    }
    else
    {
        drv->hardware = 0;
        drv->desc = *hel;
    }
    drv->perspective = drv->desc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE;
    if (drv->desc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_WBUFFER)
    {
        drv->zbufferMode = 2;
    }
    else
    {
        drv->zbufferMode = 1;
    }
    drv->zbufferFormatCount = 0;
    (*(LPDIRECT3D3 *)(dev + 0x2264))->EnumZBufferFormats(drv->guid, FUN_42fe40, drv);
    if (!drv->zbufferFormatCount)
    {
        drv->zbufferMode = 0;
    }
    (*(DWORD *)(dev + 0x2270))++;
    return D3DENUMRET_OK;
}

// FUNCTION: STUNTGP_D3D 0x42f6a0
void FUN_42f6a0()
{
    memset(&g_5ba788, 0, sizeof(g_5ba788));
    g_5ba788.count = 0;
    DirectDrawEnumerateEx(FUN_42f530, &g_5ba788, DDENUM_ATTACHEDSECONDARYDEVICES | DDENUM_NONDISPLAYDEVICES);
}

// FUNCTION: STUNTGP_D3D 0x42f6d0
int FUN_42f6d0(DDPIXELFORMAT *format)
{
    if (format->dwRGBBitCount != 16)
    {
        return 0;
    }
    if (!(format->dwFlags & DDPF_ALPHAPIXELS))
    {
        return 0;
    }
    if (!(format->dwFlags & DDPF_RGB))
    {
        return 0;
    }
    if (format->dwRBitMask != 0x7c00)
    {
        return 0;
    }
    if (format->dwGBitMask != 0x3e0)
    {
        return 0;
    }
    if (format->dwBBitMask != 0x1f)
    {
        return 0;
    }
    if (format->dwRGBAlphaBitMask != 0x8000)
    {
        return 0;
    }
    g_5ba788.hasArgb1555 = 1;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x42f780
HRESULT WINAPI FUN_42f780(LPDDPIXELFORMAT format, LPVOID context)
{
    TextureFormatList *list = (TextureFormatList *)context;
    DWORD count = list->count;
    DDPIXELFORMAT *slot = &list->formats[count];
    if (count >= 16)
    {
        return DDENUMRET_CANCEL;
    }
    if (g_58332c == 1)
    {
        if (FUN_42f6d0(format) == 1)
        {
            g_5ba788.textureFormat = slot;
        }
    }
    else if (format->dwFlags & DDPF_PALETTEINDEXED8)
    {
        g_5ba788.textureFormat = slot;
    }
    *slot = *format;
    list->count = count + 1;
    return DDENUMRET_OK;
}

// FUNCTION: STUNTGP_D3D 0x42f7f0
void FUN_42f7f0(D3DVIEWPORT2 *viewport, DWORD width, DWORD height)
{
    memset(viewport, 0, sizeof(D3DVIEWPORT2));
    viewport->dwSize = sizeof(D3DVIEWPORT2);
    viewport->dwWidth = width;
    viewport->dwHeight = height;
    viewport->dvMaxZ = 1.0f;
    viewport->dvClipX = -1.0f;
    viewport->dvClipWidth = 2.0f;
    viewport->dvClipY = 1.0f;
    viewport->dvClipHeight = 2.0f;
}

// Creates the selected device's viewport covering the display and makes it current.
// FUNCTION: STUNTGP_D3D 0x42f840
int FUN_42f840()
{
    BYTE *dev = g_5ba788.device;
    LPDIRECT3DDEVICE3 *device = &((D3DDriver *)g_5ba788.deviceDesc)->device;
    LPDIRECT3DDEVICE3 d3dDevice = *device;
    LPDIRECT3DVIEWPORT3 *viewport = (LPDIRECT3DVIEWPORT3 *)(dev + 0x2268);
    if (*viewport)
    {
        (*viewport)->Release();
    }
    D3DVIEWPORT2 desc;
    FUN_42f7f0(&desc, (float)g_DD_DISPLAYRESWIDTH, (float)g_DD_DISPLAYRESHEIGHT);
    int res = (*(LPDIRECT3D3 *)(dev + 0x2264))->CreateViewport(viewport, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    res = (*device)->AddViewport(*viewport);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    res = (*viewport)->SetViewport2(&desc);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    g_5ba788.unk1ea30 = (int)*viewport;
    res = d3dDevice->SetCurrentViewport((LPDIRECT3DVIEWPORT3)g_5ba788.unk1ea30);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x42f930
void FUN_42f930()
{
    if (g_61c358)
    {
        if (g_5ba788.deviceDesc[57] & ~0x81)
        {
            g_592068 = 1;
            g_59206c = 0;
            return;
        }
        DDCOLORKEY key;
        key.dwColorSpaceLowValue = 0x10001;
        key.dwColorSpaceHighValue = 0x10001;
        (*g_61c358)->SetColorKey(DDCKEY_SRCBLT, &key);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
        g_592068 = 0;
        g_59206c = 1;
    }
}

// FUNCTION: STUNTGP_D3D 0x42f9c0
void FUN_42f9c0()
{
    if (g_5ba788.deviceDesc[60] & ~5)
    {
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR);
        g_d3dDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR);
        g_592078 = 1;
    }
}

// FUNCTION: STUNTGP_D3D 0x42fa00
void FUN_42fa00()
{
}

// FUNCTION: STUNTGP_D3D 0x42fa10
void FUN_42fa10()
{
    int caps = g_5ba788.deviceDesc[58];
    if (!(caps & 0x5000))
    {
        if (caps & 0xa000)
        {
            g_d3dDevice->SetRenderState(D3DRENDERSTATE_STIPPLEDALPHA, TRUE);
        }
        g_592070 = 1;
    }
}

// FUNCTION: STUNTGP_D3D 0x42fa40
void FUN_42fa40()
{
    g_renderState.unk8008 = 0;
    if (((WORD *)g_5ba788.deviceDesc)[0xb0] >= 2 && ((WORD *)g_5ba788.deviceDesc)[0xb1] >= 2)
    {
        g_592074 = g_renderState.unk8008 = 1;
    }
}

// Sets the default light, render and texture-stage states inside a scene.
// FUNCTION: STUNTGP_D3D 0x42fa80
BOOL FUN_42fa80()
{
    LPDIRECT3DDEVICE3 device = ((D3DDriver *)g_5ba788.deviceDesc)->device;
    if (device->BeginScene() != D3D_OK)
    {
        return FALSE;
    }
    device->SetLightState(D3DLIGHTSTATE_MATERIAL, 0);
    device->SetLightState(D3DLIGHTSTATE_AMBIENT, 0);
    device->SetLightState(D3DLIGHTSTATE_COLORMODEL, D3DCOLOR_RGB);
    device->SetLightState(D3DLIGHTSTATE_FOGMODE, D3DFOG_NONE);
    device->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);
    device->SetRenderState(D3DRENDERSTATE_ANTIALIAS, D3DANTIALIAS_NONE);
    device->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);
    device->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
    device->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
    device->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
    device->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
    device->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
    device->SetRenderState(D3DRENDERSTATE_MONOENABLE, FALSE);
    device->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
    device->SetRenderState(D3DRENDERSTATE_LASTPIXEL, FALSE);
    device->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR);
    device->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR);
    device->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
    device->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
    device->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
    device->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0xf0);
    device->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, D3DCMP_GREATEREQUAL);
    device->SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);
    device->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
    device->SetRenderState(D3DRENDERSTATE_FOGENABLE, FALSE);
    device->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
    device->SetRenderState(D3DRENDERSTATE_SUBPIXEL, TRUE);
    device->SetRenderState(D3DRENDERSTATE_SUBPIXELX, FALSE);
    device->SetRenderState(D3DRENDERSTATE_STIPPLEDALPHA, FALSE);
    device->SetRenderState(D3DRENDERSTATE_FOGCOLOR, 0);
    device->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_NONE);
    device->SetRenderState(D3DRENDERSTATE_FOGTABLEDENSITY, 1);
    device->SetRenderState(D3DRENDERSTATE_EDGEANTIALIAS, FALSE);
    device->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    FUN_42f9c0();
    FUN_42f930();
    FUN_42fa10();
    FUN_42fa00();
    FUN_42fa40();
    return device->EndScene() == D3D_OK;
}

// Total video memory reported by ddGetMemory.
// GLOBAL: STUNTGP_D3D 0x5da1cc
DWORD g_5da1cc;

// GLOBAL: STUNTGP_D3D 0x5da1d0
DWORD g_5da1d0;

// GLOBAL: STUNTGP_D3D 0x5da1d4
DWORD g_5da1d4;

// Sets the display mode and creates the flipping primary surface and its back buffer;
// cards with more than 8MB get triple buffering.
// FUNCTION: STUNTGP_D3D 0x42fc90
int FUN_42fc90(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *front, LPDIRECTDRAWSURFACE4 *back, DWORD width, DWORD height, DWORD depth)
{
    int res = dd->SetDisplayMode(width, height, depth, 0, 0);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    DDSURFACEDESC2 desc;
    memset(&desc, 0, sizeof(desc));
    desc.dwBackBufferCount = (g_5da1cc > 0x800000) + 1;
    desc.ddsCaps.dwCaps = DAT_CAPS | DDSCAPS_VIDEOMEMORY | DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    desc.dwSize = sizeof(desc);
    desc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    res = dd->CreateSurface(&desc, front, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    FUN_422a00(front);
    DDSCAPS2 caps;
    caps.dwCaps = DDSCAPS_BACKBUFFER;
    res = (*front)->GetAttachedSurface(&caps, back);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    g_61c358 = back;
    return res;
}

void FUN_424aa0();
extern DWORD g_477c30;

// Recreates DirectDraw on the chosen display device (0 = primary) and resets the display mode.
// FUNCTION: STUNTGP_D3D 0x42fd80
int FUN_42fd80(int device)
{
    FUN_422a20();
    ddRelease();
    DAT_CAPS = 0x2000;
    // STRING: STUNTGP_D3D 0x478768
    if (windowDDCreate(&g_dd, device ? (GUID *)&g_5ba788.devices[device][0x300] : NULL, g_Hwnd))
    {
        exitError("DirectDraw Init Failed!\n");
    }
    ddGetDD4(&g_dd, &g_dd4, g_Hwnd);
    ddGetMemory(&g_dd4, &g_5da1cc, &g_5da1d0, &g_5da1d4);
    g_477c30 = g_5da1d0;
    FUN_42fc90(g_dd4, &g_surface, &g_surface2, g_DISPLAYRESWIDTH, g_DISPLAYRESHEIGHT, g_DISPLAYRESDEPTH);
    FUN_424aa0();
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x42fe40
HRESULT WINAPI FUN_42fe40(LPDDPIXELFORMAT format, LPVOID context)
{
    if (!(format->dwFlags & DDPF_ZBUFFER))
    {
        return D3DENUMRET_OK;
    }
    ZBufferFormatList *list = (ZBufferFormatList *)context;
    list->formats[list->count] = *format;
    list->count++;
    return D3DENUMRET_OK;
}

// Picks the deepest z-buffer format of at least 16 bits, preferring less stencil.
// FUNCTION: STUNTGP_D3D 0x42fe90
void FUN_42fe90(int device, int driver)
{
    ZBufferFormatList *list = (ZBufferFormatList *)&g_5ba788.devices[device][0x2274] + driver;
    DDPIXELFORMAT *best = NULL;
    if (!list->unk064)
    {
        return;
    }
    g_5ba788.zbufferFormat = best;
    for (DWORD i = 0; i < list->count; i++)
    {
        DDPIXELFORMAT *format = &list->formats[i];
        DWORD depth = format->dwZBufferBitDepth;
        DWORD stencil = format->dwStencilBitDepth;
        if (depth >= 16 &&
            (!best || depth > best->dwZBufferBitDepth ||
             (depth == best->dwZBufferBitDepth && stencil < best->dwStencilBitDepth)))
        {
            best = format;
            g_5ba788.zbufferFormat = best;
        }
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
        int mode = 0x60;
        if (!(flags & 8))
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
    if (g_renderState.unkfc != texture)
    {
        g_d3dDevice->SetTexture(0, g_renderState.unk62ec[texture].texture);
        g_renderState.unkfc = texture;
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

// MeshUv with its colour as bytes.
struct ClipUv
{
    float u;       // 0x00
    float v;       // 0x04
    WORD point;    // 0x08
    WORD unk0a;    // 0x0a
    BYTE color[4]; // 0x0c
};

// Transformed vertex as written by FUN_429520.
struct XformVertex
{
    float x;     // 0x00
    float y;     // 0x04
    float z;     // 0x08
    DWORD unk0c; // 0x0c
    WORD code;   // 0x10, outcode bits
    WORD unk12;  // 0x12
    DWORD unk14; // 0x14
    DWORD unk18; // 0x18
    float w;     // 0x1c, view-space depth
};

// Polygon vertex for the 3D clipper.
struct ClipVertex3
{
    ClipUv uv;      // 0x00
    XformVertex xv; // 0x10
};

// Point where the edge a-b crosses clip plane 1 (near), 4, 8, 16 or 32.
// FUNCTION: STUNTGP_D3D 0x4272a0
void FUN_4272a0(ClipVertex3 *a, ClipVertex3 *b, ClipVertex3 *out, int plane)
{
    float da;
    float db;
    switch (plane)
    {
    case 1:
        da = a->xv.z - g_4722d0->nearZ;
        db = b->xv.z - g_4722d0->nearZ;
        break;
    case 4:
        da = a->xv.z + a->xv.x + 1.0f;
        db = b->xv.z + b->xv.x + 1.0f;
        break;
    case 8:
        da = a->xv.x - a->xv.z - 1.0f;
        db = b->xv.x - b->xv.z - 1.0f;
        break;
    case 16:
        da = a->xv.z + a->xv.y + 1.0f;
        db = b->xv.z + b->xv.y + 1.0f;
        break;
    case 32:
        da = a->xv.y - a->xv.z - 1.0f;
        db = b->xv.y - b->xv.z - 1.0f;
        break;
    }
    float d = db - da;
    float t;
    if ((float)fabs(d) <= 1.0f)
    {
        t = 1.0f;
    }
    else
    {
        t = -(da / d);
    }
    float x = (b->xv.x - a->xv.x) * t + a->xv.x;
    out->xv.x = x;
    float y = (b->xv.y - a->xv.y) * t + a->xv.y;
    out->xv.y = y;
    float z = (b->xv.z - a->xv.z) * t + a->xv.z;
    out->xv.z = z;
    float w = (b->xv.w - a->xv.w) * t + a->xv.w;
    out->xv.w = w;
    out->uv.u = (b->uv.u - a->uv.u) * t + a->uv.u;
    out->uv.v = (b->uv.v - a->uv.v) * t + a->uv.v;
    int f = (int)(t * 256.0f);
    out->uv.color[3] = (BYTE)(((b->uv.color[3] - a->uv.color[3]) * f >> 8) + a->uv.color[3]);
    out->uv.color[2] = (BYTE)(((b->uv.color[2] - a->uv.color[2]) * f >> 8) + a->uv.color[2]);
    out->uv.color[1] = (BYTE)(((b->uv.color[1] - a->uv.color[1]) * f >> 8) + a->uv.color[1]);
    out->uv.color[0] = (BYTE)(((b->uv.color[0] - a->uv.color[0]) * f >> 8) + a->uv.color[0]);
    float c[5];
    c[0] = g_4722d0->nearZ - z;
    c[1] = -x - w;
    c[2] = x - w;
    c[3] = -y - w;
    c[4] = y - w;
    out->xv.code = 2 | (*(DWORD *)&c[0] >> 31) | ((*(DWORD *)&c[1] >> 29) & 4) | ((*(DWORD *)&c[2] >> 28) & 8) |
                ((*(DWORD *)&c[3] >> 27) & 0x10) | ((*(DWORD *)&c[4] >> 26) & 0x20);
}

// Queued polygon (PolyRef layout); type holds the clip planes it is already inside, 0x3f for all.
struct RenderItem
{
    DWORD *poly;        // 0x00, first byte is the vertex count
    WORD *ref;          // 0x04
    ClipUv *src;        // 0x08
    XformVertex *verts; // 0x0c
    int type;           // 0x10
};

// Clips the polygon against each plane it is not yet inside, appending the result to the
// clipped-polygon buffers; drops it when fewer than three vertices remain.
// FUNCTION: STUNTGP_D3D 0x427530
void FUN_427530(RenderItem *item)
{
    ClipVertex3 bufA[16];
    ClipVertex3 bufB[16];
    ClipVertex3 *dst = bufA;
    WORD *ref = item->ref;
    DWORD *poly = item->poly;
    DWORD n = *poly & 0xff;
    ClipVertex3 *src = bufB;
    DWORD i;
    for (i = 0; i < n; i++)
    {
        src[i].uv = item->src[*ref];
        src[i].xv = item->verts[src[i].uv.point];
        ref++;
    }
    DWORD flags = item->type;
    DWORD bit = 1;
    DWORD pass = 0;
    do
    {
        if (!(flags & bit))
        {
            ClipVertex3 *out = dst;
            ClipVertex3 *prev = &src[n - 1];
            ClipVertex3 *cur = src;
            for (i = 0; i < n; i++)
            {
                int prevIn = prev->xv.code & bit;
                int curIn = cur->xv.code & bit;
                if (prevIn && curIn)
                {
                    *out++ = *prev;
                }
                else if (prevIn)
                {
                    *out++ = *prev;
                    FUN_4272a0(prev, cur, out++, bit);
                }
                else if (curIn)
                {
                    FUN_4272a0(prev, cur, out++, bit);
                }
                prev = cur;
                cur++;
            }
            n = out - dst;
            if (n < 3)
            {
                FUN_427520((int *)item);
                return;
            }
            ClipVertex3 *t = src;
            src = dst;
            dst = t;
        }
        flags |= bit;
        bit <<= 1;
        if (flags == 0x3f)
        {
            break;
        }
    } while (++pass < 6);
    DWORD *np = (DWORD *)g_renderState.unk7ff4;
    item->src = (ClipUv *)g_renderState.unk7ff0;
    item->poly = np;
    item->ref = (WORD *)g_renderState.unk7fc0;
    item->verts = (XformVertex *)g_renderState.unk7ffc;
    g_renderState.unk7ff4 = (int)(np + 2);
    np[0] = poly[0];
    np[1] = poly[1];
    *(BYTE *)np = (BYTE)n;
    ((WORD *)np)[3] = 0;
    DWORD k = 0;
    for (i = 0; i < n; i++)
    {
        src[k].uv.point = (WORD)i;
        *(ClipUv *)g_renderState.unk7ff0 = src[k].uv;
        *(XformVertex *)g_renderState.unk7ffc = src[k].xv;
        g_renderState.unk7ffc += 0x20;
        g_renderState.unk7ff0 += 0x10;
        k++;
        if (k >= n)
        {
            k -= n;
        }
    }
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
    if (g_renderState.unk7ef8[0].count)
    {
        g_4722d0->unk19c = 5000000.0f;
        FUN_4277b0((RenderItem *)g_renderState.unk7ef8[0].data, g_renderState.unk7ef8[0].count);
    }
    g_4722d0->unk19c = 500000.0f;
    if (g_renderState.unk7ef8[2].count)
    {
        FUN_4277b0((RenderItem *)g_renderState.unk7ef8[2].data, g_renderState.unk7ef8[2].count);
    }
    if (g_renderState.unk7ef8[2].unk0c)
    {
        FUN_4277b0((RenderItem *)g_renderState.unk7ef8[2].unk08, g_renderState.unk7ef8[2].unk0c);
    }
    g_4722d0->unk19c = 500000.0f;
    if (g_renderState.unk7ef8[4].count)
    {
        FUN_4277b0((RenderItem *)g_renderState.unk7ef8[4].data, g_renderState.unk7ef8[4].count);
    }
    if (g_renderState.unk7ef8[4].unk0c)
    {
        FUN_4277b0((RenderItem *)g_renderState.unk7ef8[4].unk08, g_renderState.unk7ef8[4].unk0c);
    }
    if (g_renderState.unk7ef8[6].count)
    {
        FUN_4277b0((RenderItem *)g_renderState.unk7ef8[6].data, g_renderState.unk7ef8[6].count);
    }
    if (g_renderState.unk7ef8[6].unk0c)
    {
        FUN_4277b0((RenderItem *)g_renderState.unk7ef8[6].unk08, g_renderState.unk7ef8[6].unk0c);
    }
}

// Directory searched first for track textures.
// GLOBAL: STUNTGP_D3D 0x60dfac
char g_60dfac[0x40];

// Redirects a track texture path into g_60dfac when that directory is set.
// FUNCTION: STUNTGP_D3D 0x42bb70
int FUN_42bb70(char *path, char *out)
{
    char name[64];
    if (g_60dfac[0])
    {
        int i;
        for (i = strlen(path); i > 0; i--)
        {
            if (path[i] == '\\')
            {
                break;
            }
        }
        if (i)
        {
            i++;
        }
        // STRING: STUNTGP_D3D 0x4777c0
        sprintf(name, "%s", path + i);
        // STRING: STUNTGP_D3D 0x4777c4
        if (strstr(path, "Trk_"))
        {
            // STRING: STUNTGP_D3D 0x4777cc
            sprintf(out, "%s\\%s", g_60dfac, name);
            return 1;
        }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x42bc00
void FUN_42bc00()
{
    g_5895b0.nameCursor = g_583990;
    g_5895b0.totalSize = 0;
    g_583990[0] = 0;
    g_587994 = 0;
    g_5895b0.entryCursor = &g_587990;
}

// Reads the size of a .PC image; returns whether it fits the texture size limit.
// FUNCTION: STUNTGP_D3D 0x42bc30
int FUN_42bc30(char *suffix, char *base, char *path)
{
    BYTE header[20];
    // STRING: STUNTGP_D3D 0x4777d4
    sprintf(path, "%s%s.PC", base, suffix);
    if (!size_of_file(path))
    {
        return 0;
    }
    if (!bload(path, (char *)header, 10))
    {
        return 0;
    }
    int width = *(WORD *)&header[6];
    int height = *(WORD *)&header[8];
    g_489718 = height;
    g_489714 = width;
    g_583330 = 1;
    return width <= g_6249a4;
}

void FUN_462440(char *path);

// FUNCTION: STUNTGP_D3D 0x42bcb0
int FUN_42bcb0(char *suffix, char *base, char *path)
{
    // STRING: STUNTGP_D3D 0x4777dc
    sprintf(path, "%s%s.TGA", base, suffix);
    FUN_462440(path);
    return g_489714 <= g_6249a4;
}

extern char g_GraphicsDirectory[128];
extern char g_GraphicsDirectory24Max[128];
extern int g_6249a0;

// Finds an image as .PC or .TGA, trying the high-detail directory first when allowed.
// FUNCTION: STUNTGP_D3D 0x42bcf0
void FUN_42bcf0(char *suffix, char *path, int highDetail)
{
    char dirs[2][128];
    g_489714 = 0;
    g_583330 = 0;
    strcpy(dirs[0], g_GraphicsDirectory);
    strcpy(dirs[1], g_GraphicsDirectory24Max);
    g_58332c = 1;
    int level;
    if (highDetail == 1 && g_6249a0 == 1)
    {
        level = 1;
    }
    else
    {
        level = 0;
    }
    char *dir = dirs[level];
    for (;;)
    {
        if (FUN_42bc30(suffix, dir, path) == 1)
        {
            return;
        }
        if (FUN_42bcb0(suffix, dir, path) == 1)
        {
            return;
        }
        dir -= 128;
        if (--level < 0)
        {
            return;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x42bdd0
void FUN_42bdd0()
{
    memset(g_textureFiles, 0, sizeof(g_textureFiles));
    memset(g_57eb0c, 0, sizeof(g_57eb0c));
    memset(g_fontFiles, 0, sizeof(g_fontFiles));
    g_582710 = g_textureFiles;
    g_580aec = g_57eb0c;
    g_5895bc = g_fontFiles;
}

// Records a texture file so it can be reloaded when surfaces are lost.
// FUNCTION: STUNTGP_D3D 0x42be20
void FUN_42be20(char *path)
{
    g_582710->name = g_580aec;
    g_582710->slot = g_582718.unk04;
    g_582710++;
    g_582710->name = NULL;
    strcpy(g_580aec, path);
    g_580aec += strlen(path) + 1;
}

// Pre-lit transformed vertex for the polygon batches.
struct BatchVertex
{
    float x;            // 0x00
    float y;            // 0x04
    float z;            // 0x08
    float rhw;          // 0x0c
    D3DCOLOR diffuse;   // 0x10
    D3DCOLOR specular;  // 0x14
    float u0;           // 0x18
    float v0;           // 0x1c
    float u1;           // 0x20
    float v1;           // 0x24
};

// Triangle-fan indices into g_592780 for the current batch.
// GLOBAL: STUNTGP_D3D 0x590018
WORD g_590018[0x1000];

// GLOBAL: STUNTGP_D3D 0x592780
BatchVertex g_592780[0x1000];

// First texture slot with a UV scroll record in g_577660.
// GLOBAL: STUNTGP_D3D 0x583590
int g_583590;

// Draws queued polygons with their textures scrolled by g_577660, z-test off, one indexed
// batch per texture run.
// FUNCTION: STUNTGP_D3D 0x433290
void FUN_433290(void *data, int count)
{
    if (!count)
    {
        return;
    }
    int res = g_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    int base = 0;
    DWORD texture = 0xffffffff;
    BatchVertex *v;
    WORD *idx;
    float *scroll;
    PolyRef *ref = (PolyRef *)data;
    for (DWORD i = 0; i < (DWORD)count; i++)
    {
        if (ref->poly)
        {
            BYTE *src = ref->src;
            BYTE *verts = (BYTE *)ref->verts;
            WORD *r = ref->ref;
            DWORD slot = ((BYTE *)ref->poly)[1];
            if (slot != texture)
            {
                if (base)
                {
                    g_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0x2c4, g_592780, v - g_592780, g_590018, idx - g_590018, 0x1c);
                }
                texture = slot;
                base = 0;
                v = g_592780;
                idx = g_590018;
                g_d3dDevice->SetTexture(0, g_renderState.unk62ec[texture].texture);
                scroll = (float *)g_577660 + (texture - g_583590) * 5;
            }
            DWORD n = *(BYTE *)ref->poly;
            for (DWORD k = 0; k < n; k++)
            {
                BYTE *e = src + *r++ * 16;
                float *p = (float *)(verts + *(WORD *)(e + 8) * 32);
                v->x = p[0];
                v->y = p[1];
                v->rhw = v->z = p[7];
                v->u0 = scroll[1] + ((float *)e)[0];
                v->v0 = ((float *)e)[1] + scroll[2];
                v->diffuse = 0xffffffff;
                v->specular = 0;
                v++;
            }
            int first = base;
            base++;
            for (DWORD j = 2; j < n; j++)
            {
                idx[0] = first;
                idx[1] = base;
                base++;
                idx[2] = base;
                idx += 3;
            }
            base++;
        }
        ref++;
    }
    if (base)
    {
        g_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0x2c4, g_592780, v - g_592780, g_590018, idx - g_590018, 0x1c);
    }
    FUN_432a90();
}

struct Unk624488;

// FUN_433290 for opaque vertex-coloured polygons with UVs scrolled by the slot's g_renderState.unk7fa0 record.
// FUNCTION: STUNTGP_D3D 0x4334c0
void FUN_4334c0(void *data, int count)
{
    if (!count)
    {
        return;
    }
    int base = 0;
    DWORD texture = 0xffffffff;
    BatchVertex *v;
    WORD *idx;
    float *scroll;
    PolyRef *ref = (PolyRef *)data;
    for (DWORD i = 0; i < (DWORD)count; i++)
    {
        if (ref->poly)
        {
            BYTE *src = ref->src;
            BYTE *verts = (BYTE *)ref->verts;
            WORD *r = ref->ref;
            DWORD slot = ((BYTE *)ref->poly)[1];
            if (slot != texture)
            {
                if (base)
                {
                    g_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0x2c4, g_592780, v - g_592780, g_590018, idx - g_590018, 0x1c);
                }
                texture = slot;
                base = 0;
                v = g_592780;
                idx = g_590018;
                g_d3dDevice->SetTexture(0, g_renderState.unk62ec[texture].texture);
                scroll = (float *)g_renderState.unk7fa0 + g_renderState.unk62ec[texture].unk04[4] * 5;
            }
            DWORD n = *(BYTE *)ref->poly;
            for (DWORD k = 0; k < n; k++)
            {
                BYTE *e = src + *r++ * 16;
                float *p = (float *)(verts + *(WORD *)(e + 8) * 32);
                v->x = p[0];
                v->y = p[1];
                v->rhw = v->z = p[7];
                v->u0 = ((float *)e)[0] + scroll[1];
                v->v0 = ((float *)e)[1] + scroll[2];
                v->diffuse = *(D3DCOLOR *)(e + 12) | 0xff000000;
                v->specular = 0;
                v++;
            }
            int first = base;
            base++;
            for (DWORD j = 2; j < n; j++)
            {
                idx[0] = first;
                idx[1] = base;
                base++;
                idx[2] = base;
                idx += 3;
            }
            base++;
        }
        ref++;
    }
    if (base)
    {
        g_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0x2c4, g_592780, v - g_592780, g_590018, idx - g_590018, 0x1c);
    }
}

// FUN_433290 for vertex-coloured polygons: diffuse from the vertex colour, its alpha as a grey
// specular term, UVs scrolled by the slot's g_renderState.unk7fa0 record.
// FUNCTION: STUNTGP_D3D 0x4336c0
void FUN_4336c0(void *data, int count)
{
    if (!count)
    {
        return;
    }
    if (g_624984 == 1)
    {
        FUN_42f340();
    }
    int base = 0;
    DWORD texture = 0xffffffff;
    BatchVertex *v;
    WORD *idx;
    float *scroll;
    PolyRef *ref = (PolyRef *)data;
    for (DWORD i = 0; i < (DWORD)count; i++)
    {
        if (ref->poly)
        {
            BYTE *src = ref->src;
            BYTE *verts = (BYTE *)ref->verts;
            WORD *r = ref->ref;
            DWORD slot = ((BYTE *)ref->poly)[1];
            if (slot != texture)
            {
                if (base)
                {
                    g_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0x2c4, g_592780, v - g_592780, g_590018, idx - g_590018, 0x1c);
                }
                texture = slot;
                base = 0;
                v = g_592780;
                idx = g_590018;
                g_d3dDevice->SetTexture(0, g_renderState.unk62ec[texture].texture);
                scroll = (float *)g_renderState.unk7fa0 + g_renderState.unk62ec[texture].unk04[4] * 5;
            }
            DWORD n = *(BYTE *)ref->poly;
            for (DWORD k = 0; k < n; k++)
            {
                BYTE *e = src + *r++ * 16;
                float *p = (float *)(verts + *(WORD *)(e + 8) * 32);
                v->x = p[0];
                v->y = p[1];
                v->rhw = v->z = p[7];
                v->u0 = ((float *)e)[0] + scroll[1];
                v->v0 = ((float *)e)[1] + scroll[2];
                D3DCOLOR color = *(D3DCOLOR *)(e + 12);
                v->diffuse = color;
                DWORD a = color >> 24;
                v->specular = ((a << 8 | a) << 8) | a;
                v++;
            }
            int first = base;
            base++;
            for (DWORD j = 2; j < n; j++)
            {
                idx[0] = first;
                idx[1] = base;
                base++;
                idx[2] = base;
                idx += 3;
            }
            base++;
        }
        ref++;
    }
    if (base)
    {
        g_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0x2c4, g_592780, v - g_592780, g_590018, idx - g_590018, 0x1c);
    }
    if (g_624984 == 1)
    {
        FUN_42f380();
    }
}

// Fan-to-strip vertex order for an n-gon, indexed by n.
// GLOBAL: STUNTGP_D3D 0x477cd0
int g_477cd0[17][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 2, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 2, 5, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 2, 6, 3, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 2, 7, 3, 6, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 2, 8, 3, 7, 4, 6, 5, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 2, 9, 3, 8, 4, 7, 5, 6, 0, 0, 0, 0, 0, 0},
    {1, 0, 2, 10, 3, 9, 4, 8, 5, 7, 6, 0, 0, 0, 0, 0},
    {1, 0, 2, 11, 3, 10, 4, 9, 5, 8, 6, 7, 0, 0, 0, 0},
    {1, 0, 2, 12, 3, 11, 4, 10, 5, 9, 6, 8, 7, 0, 0, 0},
    {1, 0, 2, 13, 3, 12, 4, 11, 5, 10, 6, 9, 7, 8, 0, 0},
    {1, 0, 2, 14, 3, 13, 4, 12, 5, 11, 6, 10, 7, 9, 8, 0},
    {1, 0, 2, 15, 3, 14, 4, 13, 5, 12, 6, 11, 7, 10, 8, 9},
};

// Draws the blended polygons one triangle strip at a time, switching the blend mode on
// poly[3] & 0x78; mode 0x50 keeps the vertex alpha, the others take poly[2].
// FUNCTION: STUNTGP_D3D 0x4338e0
void FUN_4338e0(void *data, int count)
{
    PolyRef *ref = (PolyRef *)data;
    if (!count)
    {
        return;
    }
    DWORD blend = 0xffffffff;
    DWORD texture = 0xffffffff;
    float *scroll;
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
    for (DWORD i = 0; i < (DWORD)count; i++)
    {
        BYTE *poly = (BYTE *)ref->poly;
        if (poly)
        {
            BYTE *src = ref->src;
            BYTE *verts = (BYTE *)ref->verts;
            WORD *r = ref->ref;
            DWORD mode = poly[3] & 0x78;
            if (mode != blend)
            {
                blend = mode;
                switch (mode)
                {
                case 0x48:
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
                    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
                    break;
                case 0x50:
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
                    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
                    break;
                case 0x58:
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
                    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
                    break;
                case 0x60:
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
                    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
                    break;
                case 0x70:
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR);
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
                    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
                    break;
                default:
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
                    g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
                    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
                    break;
                }
            }
            DWORD slot = poly[1];
            if (slot != texture)
            {
                g_d3dDevice->SetTexture(0, g_renderState.unk62ec[slot].texture);
                scroll = (float *)g_renderState.unk7fa0 + g_renderState.unk62ec[slot].unk04[4] * 5;
                texture = slot;
            }
            DWORD n = poly[0];
            BYTE alpha = poly[2];
            int *order = g_477cd0[n];
            D3DTLVERTEX2 *v = g_58d818;
            for (DWORD k = 0; k < n; k++)
            {
                float *e = (float *)(src + r[*order] * 16);
                float *p = (float *)(verts + *(WORD *)(e + 2) * 32);
                v->sx = p[0];
                v->sy = p[1];
                v->rhw = v->sz = p[7];
                v->tu1 = e[0] + scroll[1];
                v->tv1 = e[1] + scroll[2];
                v->specular = 0;
                if (mode == 0x50)
                {
                    v->color = ((DWORD *)e)[3];
                }
                else
                {
                    v->color = ((DWORD *)e)[3] & 0xffffff | alpha << 24;
                }
                order++;
                v++;
            }
            g_d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0x2c4, g_58d818, n, 0x1c);
        }
        ref++;
    }
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    g_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
    FUN_432a90();
}

// Two-texture pass: FUN_4334c0 with the shared detail texture (slot 0) added on stage 1.
// FUNCTION: STUNTGP_D3D 0x433c50
void FUN_433c50(void *data, int count)
{
    if (!count)
    {
        return;
    }
    if (!g_592074 || !g_624984)
    {
        FUN_4334c0(data, count);
        return;
    }
    if (g_624984 == 1)
    {
        FUN_42f340();
    }
    int base = 0;
    DWORD texture = 0xffffffff;
    BatchVertex *v;
    WORD *idx;
    g_d3dDevice->SetTexture(1, (LPDIRECT3DTEXTURE2)g_renderState.unk62ec[0].unk04[0]);
    g_d3dDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
    g_d3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
    PolyRef *ref = (PolyRef *)data;
    for (DWORD i = 0; i < (DWORD)count; i++)
    {
        if (ref->poly)
        {
            BYTE *src = ref->src;
            BYTE *verts = (BYTE *)ref->verts;
            WORD *r = ref->ref;
            DWORD slot = ((BYTE *)ref->poly)[1];
            if (slot != texture)
            {
                if (base)
                {
                    g_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0x2c4, g_592780, v - g_592780, g_590018, idx - g_590018, 0x1c);
                }
                base = 0;
                v = g_592780;
                idx = g_590018;
                g_d3dDevice->SetTexture(0, g_renderState.unk62ec[slot].texture);
                texture = slot;
            }
            DWORD n = *(BYTE *)ref->poly;
            for (DWORD k = 0; k < n; k++)
            {
                BYTE *e = src + *r++ * 16;
                float *p = (float *)(verts + *(WORD *)(e + 8) * 32);
                v->x = p[0];
                v->y = p[1];
                v->rhw = v->z = p[7];
                v->u0 = ((float *)e)[0];
                v->v0 = ((float *)e)[1];
                v->u1 = p[5];
                v->v1 = p[6];
                D3DCOLOR color = *(D3DCOLOR *)(e + 12);
                v->diffuse = color;
                DWORD a = color >> 24;
                v->specular = ((a << 8 | a) << 8) | a;
                v++;
            }
            int first = base;
            base++;
            for (DWORD j = 2; j < n; j++)
            {
                idx[0] = first;
                idx[1] = base;
                base++;
                idx[2] = base;
                idx += 3;
            }
            base++;
        }
        ref++;
    }
    if (base)
    {
        g_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0x2c4, g_592780, v - g_592780, g_590018, idx - g_590018, 0x1c);
    }
    g_d3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    if (g_624984 == 1)
    {
        FUN_42f380();
    }
}

// Draws the queued world primitives pass by pass.
// FUNCTION: STUNTGP_D3D 0x433f40
void FUN_433f40()
{
    FUN_432a90();
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0xa0);
    FUN_433290(g_renderState.unk7ef8[0].data, g_renderState.unk7ef8[0].count);
    FUN_4334c0(g_renderState.unk7ef8[2].data, g_renderState.unk7ef8[2].count);
    FUN_4334c0(g_renderState.unk7ef8[3].data, g_renderState.unk7ef8[3].count);
    if (g_624984 == 1)
    {
        FUN_4336c0(g_renderState.unk7ef8[4].data, g_renderState.unk7ef8[4].count);
        FUN_4336c0(g_renderState.unk7ef8[5].data, g_renderState.unk7ef8[5].count);
    }
    else
    {
        FUN_4334c0(g_renderState.unk7ef8[4].data, g_renderState.unk7ef8[4].count);
        FUN_4334c0(g_renderState.unk7ef8[5].data, g_renderState.unk7ef8[5].count);
    }
    FUN_433c50(g_renderState.unk7ef8[6].data, g_renderState.unk7ef8[6].count);
    FUN_433c50(g_renderState.unk7ef8[7].data, g_renderState.unk7ef8[7].count);
    g_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 1);
    FUN_4338e0(g_renderState.unk118, g_renderState.unk7ed8[1].count);
    FUN_4338e0(g_renderState.unk110, g_renderState.unk7ed8[3].count);
}

// FUNCTION: STUNTGP_D3D 0x432a90
void FUN_432a90()
{
    if (g_5ba788.deviceDesc[25])
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
    SurfaceSlot *slot = &g_5ba788.surfaceSlots[g_5ba788.surfaceSlotCount++];
    memset(&desc, 0, sizeof(desc));
    staging = NULL;
    surface = NULL;
    stagingTexture = NULL;
    texture = NULL;
    desc.dwWidth = width;
    desc.dwHeight = height;
    desc.dwSize = sizeof(desc);
    desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    desc.ddpfPixelFormat = *g_5ba788.textureFormat;
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
    g_renderState.unk7ed0->texture = texture;
    g_renderState.unk7ed0++;
    return g_renderState.unk7ed0 - g_renderState.unk62ec - 1;
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
    if (g_renderState.unkfc != d.texture)
    {
        int tex = d.texture;
        g_d3dDevice->SetTexture(0, g_renderState.unk62ec[tex].texture);
        g_renderState.unkfc = tex;
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
    poly = g_renderState.unk108;
    mode = 0xffffffff;
    for (i = 0; i < g_renderState.unk11c; i++)
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
        if (g_renderState.unkfc != tex)
        {
            g_d3dDevice->SetTexture(0, g_renderState.unk62ec[tex].texture);
            g_renderState.unkfc = tex;
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

// FUNCTION: STUNTGP_D3D 0x44fd60
void FUN_44fd60()
{
    g_renderState.unk62e4 = g_renderState.unk2e4;
    g_renderState.unk62e8 = 0;
}

// Screen-space vertex for the 2D clipper; flags holds the inside bits for the four clip edges.
struct ClipVertex
{
    float x;        // 0x00
    float y;        // 0x04
    float z;        // 0x08
    float rhw;      // 0x0c
    float u;        // 0x10
    float v;        // 0x14
    BYTE color[4];  // 0x18
    DWORD flags;    // 0x1c
};

// Point where the edge a-b crosses clip edge 1 (left), 2 (right), 4 (top) or 8 (bottom).
// FUNCTION: STUNTGP_D3D 0x4253e0
void FUN_4253e0(ClipVertex *a, ClipVertex *b, ClipVertex *out, int edge)
{
    float da;
    float db;
    switch (edge)
    {
    case 1:
        da = a->x - g_576c14;
        db = b->x - g_576c14;
        break;
    case 2:
        da = a->x - g_576c18;
        db = b->x - g_576c18;
        break;
    case 4:
        da = a->y - g_576c1c;
        db = b->y - g_576c1c;
        break;
    case 8:
        da = a->y - g_576c20;
        db = b->y - g_576c20;
        break;
    }
    float d = db - da;
    float t;
    if ((float)fabs(d) <= 1.0f)
    {
        t = 1.0f;
    }
    else
    {
        t = -(da / d);
    }
    float x = (b->x - a->x) * t + a->x;
    out->x = x;
    float y = (b->y - a->y) * t + a->y;
    out->y = y;
    out->z = (b->z - a->z) * t + a->z;
    out->u = (b->u - a->u) * t + a->u;
    out->v = (b->v - a->v) * t + a->v;
    int f = (int)(t * 256.0f);
    out->color[3] = (BYTE)(((b->color[3] - a->color[3]) * f >> 8) + a->color[3]);
    out->color[2] = (BYTE)(((b->color[2] - a->color[2]) * f >> 8) + a->color[2]);
    out->color[1] = (BYTE)(((b->color[1] - a->color[1]) * f >> 8) + a->color[1]);
    out->color[0] = (BYTE)(((b->color[0] - a->color[0]) * f >> 8) + a->color[0]);
    out->flags = 0xf;
    if (x < g_576c14)
    {
        out->flags = 0xe;
    }
    else if (x > g_576c18)
    {
        out->flags = 0xd;
    }
    if (y < g_576c1c)
    {
        out->flags &= ~4;
    }
    else if (y > g_576c20)
    {
        out->flags &= ~8;
    }
}

// Clips a queued polygon to the screen, one edge at a time. 0 when a vertex lies outside the guard band, the
// polygon is entirely off screen or clipping leaves fewer than 3 or more than 6 vertices.
// FUNCTION: STUNTGP_D3D 0x4255e0
int FUN_4255e0(OverlayPoly *poly)
{
    ClipVertex bufA[16];
    ClipVertex bufB[16];
    DWORD n = poly->numVerts;
    DWORD all = 0xf;
    DWORD any = 0;
    ClipVertex *out = bufA;
    ClipVertex *v = (ClipVertex *)poly->verts;
    for (DWORD i = 0; i < n; i++, v++)
    {
        if (v->x < g_576c24 || v->x > g_576c28 || v->y < g_576c2c || v->y > g_576c30)
        {
            return 0;
        }
        DWORD f = 0xf;
        if (v->x < g_576c14)
        {
            f = 0xe;
        }
        else if (v->x >= g_576c18)
        {
            f = 0xd;
        }
        if (v->y < g_576c1c)
        {
            f &= ~4;
        }
        else if (v->y >= g_576c20)
        {
            f &= ~8;
        }
        v->flags = f;
        all &= f;
        any |= f;
    }
    if (all == 0xf)
    {
        return 1;
    }
    if (any != 0xf)
    {
        return 0;
    }
    if (n)
    {
        memcpy(bufB, poly->verts, n * sizeof(ClipVertex));
    }
    DWORD edge = 1;
    DWORD count = n;
    ClipVertex *in = bufB;
    for (DWORD pass = 0; pass < 4; pass++)
    {
        if (!(all & edge))
        {
            ClipVertex *o = out;
            ClipVertex *prev = &in[count - 1];
            ClipVertex *cur = in;
            for (DWORD k = count; k != 0; k--)
            {
                if (prev->flags & edge)
                {
                    *o++ = *prev;
                    if (!(cur->flags & edge))
                    {
                        FUN_4253e0(prev, cur, o, edge);
                        o++;
                    }
                }
                else if (cur->flags & edge)
                {
                    FUN_4253e0(prev, cur, o, edge);
                    o++;
                }
                prev = cur;
                cur++;
            }
            count = o - out;
            if (count < 3 || count > 6)
            {
                return 0;
            }
            ClipVertex *t = in;
            in = out;
            out = t;
        }
        all |= edge;
        edge <<= 1;
        if (all == 0x3f)
        {
            break;
        }
    }
    if (count)
    {
        memcpy(poly->verts, in, count * sizeof(ClipVertex));
    }
    poly->numVerts = count;
    return 1;
}

// Queues a screen-space polygon after clipping it; dropped when the clip rejects it.
// FUNCTION: STUNTGP_D3D 0x425830
void FUN_425830(OverlayPoly *src)
{
    g_renderState.unk108[g_renderState.unk11c] = *src;
    if (FUN_4255e0(&g_renderState.unk108[g_renderState.unk11c]))
    {
        g_renderState.unk11c++;
    }
}

// FUNCTION: STUNTGP_D3D 0x425870
void FUN_425870()
{
    g_renderState.unk11c = 0;
}

// FUNCTION: STUNTGP_D3D 0x425880
void FUN_425880()
{
    memset(g_577660, 0, sizeof(g_577660));
}

// FUNCTION: STUNTGP_D3D 0x425ae0
void FUN_425ae0()
{
    memset(g_5775d0, 0, sizeof(g_5775d0));
    g_5775d0[0][0] = 10000.0f;
    g_5775d0[1][0] = -10000.0f;
    g_5775d0[2][0] = 10000.0f;
    g_5775d0[3][0] = -10000.0f;
    g_5775d0[0][1] = 10000.0f;
    g_5775d0[1][1] = 10000.0f;
    g_5775d0[2][1] = -10000.0f;
    g_5775d0[3][1] = -10000.0f;
}

// Finds the four corner points of an object's mesh: corners take the UVs of points whose
// UV record carries id, the second UV slot otherwise.
// FUNCTION: STUNTGP_D3D 0x425b50
void FUN_425b50(ObjectDef *obj, int id)
{
    Vec4 *pt = obj->points;
    MeshUv *uvs = (MeshUv *)obj->unk2c;
    FUN_425ae0();
    for (unsigned int i = 0; i < obj->pointCount; i++, pt++)
    {
        MeshUv *uv = &uvs[i];
        if (uv->unk0a == (WORD)id)
        {
            if (pt->x <= g_5775d0[0][0] && pt->y <= g_5775d0[0][1])
            {
                *(Vec4 *)g_5775d0[0] = *pt;
                g_5775d0[0][4] = uv->u;
                g_5775d0[0][5] = uv->v;
            }
            else if (pt->x >= g_5775d0[1][0] && pt->y <= g_5775d0[1][1])
            {
                *(Vec4 *)g_5775d0[1] = *pt;
                g_5775d0[1][4] = uv->u;
                g_5775d0[1][5] = uv->v;
            }
            if (pt->x <= g_5775d0[2][0] && pt->y >= g_5775d0[2][1])
            {
                *(Vec4 *)g_5775d0[2] = *pt;
                g_5775d0[2][4] = uv->u;
                g_5775d0[2][5] = uv->v;
            }
            else if (pt->x >= g_5775d0[3][0] && pt->y >= g_5775d0[3][1])
            {
                *(Vec4 *)g_5775d0[3] = *pt;
                g_5775d0[3][4] = uv->u;
                g_5775d0[3][5] = uv->v;
            }
        }
        else
        {
            if (pt->x <= g_5775d0[0][0] && pt->y <= g_5775d0[0][1])
            {
                g_5775d0[0][6] = uv->u;
                g_5775d0[0][7] = uv->v;
            }
            else if (pt->x >= g_5775d0[1][0] && pt->y <= g_5775d0[1][1])
            {
                g_5775d0[1][6] = uv->u;
                g_5775d0[1][7] = uv->v;
            }
            if (pt->x <= g_5775d0[2][0] && pt->y >= g_5775d0[2][1])
            {
                g_5775d0[2][6] = uv->u;
                g_5775d0[2][7] = uv->v;
            }
            else if (pt->x >= g_5775d0[3][0] && pt->y >= g_5775d0[3][1])
            {
                g_5775d0[3][6] = uv->u;
                g_5775d0[3][7] = uv->v;
            }
        }
    }
    g_5775d0[0][2] = 0.0f;
    g_5775d0[1][2] = 0.0f;
    g_5775d0[2][2] = 0.0f;
    g_5775d0[3][2] = 0.0f;
}

// FUNCTION: STUNTGP_D3D 0x42e420
void FUN_42e420()
{
    g_renderState.unkfc = -1;
}

void FUN_42f2e0(char *dst, const char *src);

// Flags ATI Radeon and Intel i740/i810/i815 cards, which get a reduced render path.
// FUNCTION: STUNTGP_D3D 0x42f220
void FUN_42f220()
{
    DDDEVICEIDENTIFIER id;
    char desc[516];
    g_dd4->GetDeviceIdentifier(&id, 0);
    FUN_42f2e0(desc, id.szDescription);
    switch (id.dwVendorId)
    {
    case 0x8086:
        // STRING: STUNTGP_D3D 0x478118
        if (strstr(desc, "intel(r) 82740") ||
            // STRING: STUNTGP_D3D 0x478128
            strstr(desc, "intel(r) 82810") ||
            // STRING: STUNTGP_D3D 0x478138
            strstr(desc, "intel(r) 82815"))
        {
            g_589e08 = 1;
            g_592050 = 0;
        }
        break;
    case 0x1002:
        // STRING: STUNTGP_D3D 0x478110
        if (strstr(desc, "radeon"))
        {
            g_589e08 = 1;
            g_592050 = 0;
        }
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x42f2e0
void FUN_42f2e0(char *dst, const char *src)
{
    char c;
    while ((c = *src) != 0)
    {
        src++;
        if (c >= 'A' && c <= 'Z')
        {
            c += 0x20;
        }
        *dst++ = c;
    }
    *dst = 0;
}

// FUNCTION: STUNTGP_D3D 0x42f300
void FUN_42f300()
{
    g_592050 = g_592054 = g_592058 = g_59205c = g_592060 = g_592064 = g_592068 = g_59206c = g_592070 = g_592074 =
        g_592078 = 0;
}
