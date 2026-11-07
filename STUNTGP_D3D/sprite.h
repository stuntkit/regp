#ifndef SPRITE_H
#define SPRITE_H
#define WIN32_LEAN_AND_MEAN
#include <d3dtypes.h>
#include <windows.h>

// Corner of a free-form sprite quad; u/v in 1/1024 texels.
struct SpritePoint
{
    float x;
    float y;
    float u;
    float v;
};

// Screen-space quad handed to FUN_432e00.
struct SpriteDesc
{
    DWORD flags;     // 0x00
    float x;         // 0x04
    float y;         // 0x08
    float z;         // 0x0c
    float width;     // 0x10
    float height;    // 0x14
    float u0;        // 0x18
    float v0;        // 0x1c
    float u1;        // 0x20
    float v1;        // 0x24
    int texture;     // 0x28
    DWORD blendMode; // 0x2c
    DWORD alpha;     // 0x30
    float angle;     // 0x34
    float originX;   // 0x38
    float originY;   // 0x3c
    float scaleX;    // 0x40
    float scaleY;    // 0x44
    D3DCOLOR color;  // 0x48
    SpritePoint points[4]; // 0x4c, used when flags & 4
};

// Queued textured quad (SpriteNode type 1).
struct SpriteData
{
    DWORD flags;     // 0x00
    float x;         // 0x04
    float y;         // 0x08
    float width;     // 0x0c
    float height;    // 0x10
    float u0;        // 0x14
    float v0;        // 0x18
    float u1;        // 0x1c
    float v1;        // 0x20
    int texture;     // 0x24, bit 16 set while it is still an unresolved texture id
    DWORD blendMode; // 0x28
    DWORD alpha;     // 0x2c
};

// Queued text string (SpriteNode type 0).
struct TextData
{
    float x;         // 0x00
    float y;         // 0x04
    int style;       // 0x08
    float size;      // 0x0c
    D3DCOLOR color;  // 0x10
    DWORD flags;     // 0x14
    float unk18;     // 0x18
    BYTE unk1c[0x14];
    char text[4];    // 0x30, length unknown
};

struct SpriteNode
{
    SpriteNode *next;
    int type;
    union
    {
        SpriteData sprite;
        TextData text;
    };
};

extern SpriteDesc g_spriteDesc;
struct SpriteLists
{
    SpriteNode *tails[80];
    SpriteNode *heads[80];
};

extern SpriteLists g_spriteLists;

void FUN_437e80();
void FUN_437ec0();
void FUN_437ed0();
void FUN_437f40(SpriteNode *node, int depth);
void FUN_441220();
void FUN_432e00(SpriteDesc *desc);
void FUN_43d250();
void FUN_43f6b0();
int FUN_438130(int style, float size);
float FUN_438950(float size);
int FUN_441240(SpriteData *sprite);
int FUN_441270(int id);
int FUN_4412c0();
void FUN_441310(int slot, int id);
void FUN_430d40(int slot, int id);

// Texture cache: slot -> texture id, texture id -> slot, slot age.
extern int g_6087a8[0x25];
extern int g_60883c[0x12d];
extern int g_608cf0[0x25];

#endif /* SPRITE_H */
