#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// One of the four per-player blocks at 0x498248 (0x74c bytes each).
struct GameSlot
{
    int active;           // 0x000
    BYTE unk004[0xa8];    // 0x004
    BYTE *unk0ac;         // 0x0ac
    BYTE unk0b0[0x28];    // 0x0b0
    int unk0d8;           // 0x0d8
    int unk0dc;           // 0x0dc
    int unk0e0;           // 0x0e0
    BYTE unk0e4[0x20];    // 0x0e4
    int unk104;           // 0x104
    int unk108;           // 0x108
    int unk10c;           // 0x10c
    BYTE unk110[0xd8];    // 0x110
    int fadeActive;       // 0x1e8
    int fadeTime;         // 0x1ec
    int fadeValue;        // 0x1f0
    int fadeType;         // 0x1f4
    int fadeDuration;     // 0x1f8
    int fadeDelay;        // 0x1fc
    int fadeEnd;          // 0x200
    int fadeFrom;         // 0x204
    int fadeTo;           // 0x208
    float fadeScale;      // 0x20c
    BYTE unk210[0x53c];   // 0x210
};

extern GameSlot *g_4722d0;
extern GameSlot g_498248[4];

// --- frame timing ---
extern DWORD g_612cfc;
extern DWORD g_612d00;
extern DWORD g_612d04;
extern DWORD g_612d08;

extern BYTE g_62dcf0[256];

extern int g_60d618;
extern int g_60d620;
extern int g_60df9c;
extern int g_60f2ac;
extern int g_60f2c0;
extern DWORD g_60f2c4;
extern int g_61294c;
extern DWORD g_612954;
extern int g_612958;
extern int g_612970;
extern int g_612bf4;

// fpu
void FUN_4294f0();
void FUN_429510();

// timer
DWORD FUN_434820();

// input
void FUN_45f210();
void FUN_40d860();
void FUN_40dad0();
void FUN_45f8f0(int a, int b);

// per-tick game logic
void FUN_4023f0();
void FUN_43d200();
void FUN_405210();
void FUN_427140();
void FUN_45e1d0();
void FUN_415df0();
void FUN_443a80();
void FUN_418a90();
void FUN_401770();
void FUN_447c90();
void FUN_40de30();
void FUN_446110();

// sound
void FUN_462280();
void FUN_460af0(int a);

// mode switch
void FUN_431810();
void FUN_42eaa0();
void FUN_442030();

#endif /* GAMEUPDATE_H */
