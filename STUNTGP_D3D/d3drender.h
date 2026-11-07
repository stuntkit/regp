#ifndef D3DRENDER_H
#define D3DRENDER_H
#define WIN32_LEAN_AND_MEAN
#include <d3d.h>
#include <ddraw.h>
#include <windows.h>

// Pre-transformed vertex with two texture coordinate sets (D3DFVF_TLVERTEX | D3DFVF_TEX2).
struct D3DTLVERTEX2
{
    float sx;
    float sy;
    float sz;
    float rhw;
    D3DCOLOR color;
    D3DCOLOR specular;
    float tu1;
    float tv1;
    float tu2;
    float tv2;
};

#define FVF_TLVERTEX2 (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX2)

struct OverlayVertex
{
    float x;
    float y;
    float z;
    float unk0c;
    float u;
    float v;
    D3DCOLOR color;
    DWORD unk1c;
};

// Queued screen-space polygon, flushed by FUN_432f60.
struct OverlayPoly
{
    int texture;
    DWORD flags;
    DWORD alpha;
    DWORD numVerts;
    OverlayVertex verts[8];
};

struct TextureSlot
{
    LPDIRECT3DTEXTURE2 texture;
    DWORD unk04[6];
};

extern LPDIRECT3DDEVICE3 g_d3dDevice;
extern BOOL g_d3dInScene;

extern int g_576bc4;
extern int g_576bc8;
extern int g_576bd8;
extern int g_576be0;

extern int *g_5d91b4;

// Queued primitives per render pass.
struct RenderBucket
{
    void *data;   // 0x00
    int count;    // 0x04
    void *unk08;  // 0x08
    int unk0c;    // 0x0c
};

extern RenderBucket g_6243e0[8];
extern int g_592054;
extern int g_592058;
extern int g_59205c;
extern int g_592060;
extern int g_592064;
extern float g_477ccc;

extern OverlayPoly *g_61c5f0;
extern DWORD g_61c604;
extern int g_61c5e4;
extern TextureSlot g_6227d4[];

struct SpriteDesc;

extern D3DTLVERTEX2 g_58d818[8];
extern float g_624990;
extern float g_624994;
extern float g_576b94;
extern float g_576b98;
extern TextureSlot *g_6243b8;
extern int g_6243bc;
extern int g_576b8c;
extern int g_576b90;
extern float g_576b9c;
extern float g_576ba0;
extern float g_576be4;
extern float g_576be8;

struct Font;

// Registered texture or font file, re-read when surfaces are lost.
struct ResourceFile
{
    char *name;
    int slot;
};

extern ResourceFile g_textureFiles[255];
extern ResourceFile g_fontFiles[8];
extern int g_489714;
extern int g_489718;
extern float g_clipLeft;
extern float g_clipRight;
extern float g_clipTop;
extern float g_clipBottom;
extern int g_592050;
extern int g_58332c;

int FUN_4251a0(SpriteDesc *desc);
void FUN_430280(BYTE *src, WORD *dst, DWORD width, DWORD height);
void FUN_430690();
extern BYTE *g_592028;
extern BYTE g_59207c[255];
void FUN_430330(char *path, BYTE *dst);
void FUN_431560(int slot, BYTE *image);
int FUN_4316f0(int slot, char *path);
void FUN_4327c0(WORD *pixels, DWORD width, DWORD height);
void FUN_432840(BYTE *texture, Font *font, int arg);
void FUN_4327e0(BYTE *texture, Font *font, int arg);
int FUN_4325e0(BYTE *image, DWORD width, DWORD height);
void FUN_42be90(char *path);
void FUN_4234e0(BYTE *dst, BYTE *src);
void FUN_430100(LPDIRECTDRAWSURFACE4 surface, BYTE *image, DWORD width, DWORD height, int bits);
extern DDPIXELFORMAT *g_5d91c0;
void FUN_42f340();
void FUN_42f380();
void FUN_432300(Font *font, D3DCOLOR color, DWORD flags);
void FUN_432380();
float FUN_4323f0(Font *font, char c, float x, float y, float z, D3DCOLOR color, float scale, DWORD flags);
void FUN_432af0(D3DTLVERTEX2 *verts, SpriteDesc *desc);
void FUN_432c00(D3DTLVERTEX2 *verts, SpriteDesc *desc);
void FUN_431a80();
void FUN_432190(int mode);
void FUN_4328c0(int color);
void FUN_432a60();
void FUN_432a90();
void FUN_432f60();
void FUN_433ee0();
void FUN_433f20();
void FUN_44fd60();
void FUN_425870();
void FUN_425070();
void FUN_424c30(int mode);
void FUN_433f40();
void FUN_4250a0(float left, float top, float right, float bottom);
void FUN_427240();
void FUN_427270();
void FUN_42e420();

#endif /* D3DRENDER_H */
