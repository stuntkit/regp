#ifndef GAME_STATE_H
#define GAME_STATE_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct Vec4
{
    float x;
    float y;
    float z;
    float w;
};

// Layout is only known for the fields touched so far; the rest is padding.
struct GameState
{
    DWORD unk000;
    int screen;             // 0x004
    BYTE unk008[0x48];      // 0x008, passed to FUN_450190
    Vec4 *camera;           // 0x050
    BYTE unk054[0x24];      // 0x054
    int unk078;             // 0x078
    Vec4 unk07c;            // 0x07c
    Vec4 unk08c;            // 0x08c
    Vec4 unk09c;            // 0x09c
    BYTE unk0ac[0xf8];      // 0x0ac
    int unk1a4;             // 0x1a4
    BYTE unk1a8[0x40];      // 0x1a8
    int unk1e8;             // 0x1e8
    DWORD unk1ec;           // 0x1ec
    int unk1f0;             // 0x1f0
    int unk1f4;             // 0x1f4
    BYTE unk1f8[0x14];      // 0x1f8
    float unk20c;           // 0x20c
};

extern GameState *g_gameState;
extern GameState g_498248;

void FUN_402580();
void FUN_402e90();

#endif /* GAME_STATE_H */
