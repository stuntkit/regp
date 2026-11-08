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

// SpriteNode types 2 and 3.
struct CommandData
{
    float x; // 0x00
    float y; // 0x04
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
        CommandData command;
    };
};

extern SpriteDesc g_spriteDesc;
struct SpriteLists
{
    SpriteNode *tails[80];
    SpriteNode *heads[80];
};

extern SpriteLists g_spriteLists;

// Entry of the front-end sprite file table at 0x47f318.
struct SpriteFile
{
    char *name;
    int unk04;
    int unk08;
};

// Sprite template, copied into a SpriteData before it is queued.
typedef SpriteData SpriteDef;

struct ScreenRect
{
    float left;
    float top;
    float right;
    float bottom;
};

extern int g_5da360[4];
extern SpriteFile g_47f318[1];
extern SpriteDef g_spriteDefs[0x183];

void FUN_437e40(char *name);
void FUN_437e60();
void FUN_437e80();
void FUN_438190(float left, float top, float right, float bottom);
void FUN_441190();
BOOL FUN_4401c0(char *path);
BOOL FUN_440380(char *path);
int FUN_440250(char *dir);
char *FUN_4401e0(int card);
void FUN_441340();
int FUN_441380(SpriteDef *def, int id);
void FUN_4411c0();
void FUN_437ec0();
void FUN_437ed0();
void FUN_437f40(SpriteNode *node, int depth);
void FUN_441220();
void FUN_432e00(SpriteDesc *desc);
void FUN_43d250();
void FUN_43f6b0();
int FUN_438130(int style, float size);
float FUN_438910(const char *text, float size);
float FUN_438950(float size);
int FUN_441240(SpriteData *sprite);
int FUN_441270(int id);
int FUN_4412c0();
void FUN_441310(int slot, int id);
void FUN_430d40(int slot, int id);
char *FUN_441170(int id);
int FUN_441320(SpriteData *dst, int id);
void FUN_438370(SpriteData *src, int layer, int sub);
void FUN_438500(int layer, int sub, SpriteData *sprite);
void *FUN_438550(int size);
void FUN_438590(int layer, int sub, SpriteNode *node);
void FUN_438830(float x0, float y0, float x1, float y1, int layer, int def, float u, float v);
void FUN_438960(float x, float y, int layer, int sub, int style, const char *text, float size, D3DCOLOR color, DWORD flags);
void FUN_438990(float x, float y, int layer, int sub, int style, const char *text, float size, D3DCOLOR color, DWORD flags, float unk18);
void FUN_438be0(float x, float y, int layer, int style, int textId, float size, D3DCOLOR color, DWORD flags);
void FUN_439380(float x0, float y0, float x1, float y1, int layer, int scroll, int flags, float fade);
void FUN_439450(float x0, float y0, float x1, float y1, int layer, int def, int flags);
float FUN_438ba0(float x, float y, int layer, int style, int textId, float size, D3DCOLOR color, DWORD flags);
void FUN_4392b0(int textId, int value);
void FUN_439340(int textId);
void FUN_439520(float x0, float y0, float x1, float y1, int layer, int sub, int def, DWORD row, int blend);
void FUN_4398a0(float x0, float y0, float x1, float y1, int layer, int def, int flags, float a0, float a1, float a2, float b0, float b1, float b2);
void FUN_4399b0(int def, float x0, float x1, float y, float a0, float a1, float a2, int layer);
void FUN_439b80(int def, float x, float y0, float y1, float b0, float b1, float b2, int layer);
float FUN_43d7b0(float value, float lo, float hi);
void FUN_43d960(ScreenRect *dst, ScreenRect *from, ScreenRect *to, float t);
int FUN_43dd60();
void FUN_43feb0(float x0, float y0, float x1, float y1, int def, float u, float v);
void FUN_43ff40(ScreenRect *rect);
void FUN_43ff90(int arg);

// Front-end text strings by id.
extern char *g_feText[0x2dc];

// Texture cache: slot -> texture id, texture id -> slot, slot age.
extern int g_6087a8[0x25];
extern int g_60883c[0x12d];
extern int g_608cf0[0x25];

#endif /* SPRITE_H */
