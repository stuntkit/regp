#ifndef MENUUPDATE_H
#define MENUUPDATE_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct Unk4d5cc0;

struct MenuSlot
{
    int unk00;
    int unk04;
    int unk08;
};

// Front-end state, cleared as a whole by FUN_43d0b0.
struct MenuState
{
    BYTE unk0000[8];
    BYTE unlocked[0x34];      // 0x0008
    BYTE unlockedSaved[0x34]; // 0x003c
    int unk0070;              // 0x0070
    int unk0074;              // 0x0074
    int unk0078;              // 0x0078
    int music;   // 0x007c
    int sfx;     // 0x0080
    int unk0084; // 0x0084
    int offsetX; // 0x0088
    int offsetY; // 0x008c
    int unk0090; // 0x0090
    int unk0094; // 0x0094
    MenuSlot unk0098[5];
    int unk00d4; // 0x00d4
    int unk00d8; // 0x00d8
    int unk00dc; // 0x00dc
    int unk00e0; // 0x00e0
    int unk00e4; // 0x00e4
    int unk00e8; // 0x00e8
    BYTE unk00ec[0x211c - 0xec];
    BYTE saved[0x2114]; // 0x211c, copy of 0x0008..0x211c
    BYTE unk4230[0x10];
    int unk4240; // 0x4240
    BYTE unk4244[0x4258 - 0x4244];
    int unk4258; // 0x4258
    BYTE unk425c[0x427c - 0x425c];
    int unk427c; // 0x427c
    BYTE unk4280[0x13148 - 0x4280];
    Unk4d5cc0 *unk13148; // 0x13148
    BYTE unk1314c[0x1dae8 - 0x1314c];
};

extern MenuState g_menuState;

struct PoolObject;

void FUN_424bd0(float x, float y);
int FUN_43d790(int value, int min, int max);
float FUN_43d810(float current, float target, float rate);
int FUN_43dd70();
void FUN_43de40();
void FUN_43dee0();
void FUN_43f310(PoolObject *screen);
void FUN_43f610();
void FUN_440770(int a, int b);
void FUN_440880(int a);
void FUN_434b50();
int FUN_437360(int track);
int FUN_437da0(int track);
void FUN_439e30();
void FUN_43c060();
void FUN_43c130();
void FUN_43c370();
void FUN_43c400();
void FUN_43d280();
void FUN_43dd10(DWORD color);
void FUN_43dda0();
void FUN_4408e0();
void FUN_440ae0();
void FUN_436eb0();
void FUN_436ed0();
void FUN_436f00(int player);
BYTE FUN_436f60(BYTE *keys, int button);
int FUN_437090(int player);
void FUN_43c000();
void FUN_43eff0();
int FUN_440c40(int id);

#endif /* MENUUPDATE_H */
