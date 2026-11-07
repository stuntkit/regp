#ifndef SPRITE_H
#define SPRITE_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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
    BYTE unk34[0x58];
};

struct SpriteNode
{
    SpriteNode *next;
    int type;
    BYTE data[0x30];
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
void FUN_43d250();
void FUN_43f6b0();

#endif /* SPRITE_H */
