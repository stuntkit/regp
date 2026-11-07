#define WIN32_LEAN_AND_MEAN

#include <cstdio>
#include <windows.h>

#include "../../gametext.h"
#include "../../globals.h"
#include "../../input.h"
#include "../../mem.h"
#include "../../random.h"
#include "../../soundsys.h"
#include "../../tables.h"
#include "../../timer.h"
#include "Engine_LevelScript.h"
#include "GameSetup.h"

void GetGameBuildVersion();
void FUN_441d70();
void FUN_441f00();
void FUN_442030();
void Timer_Reset();
void FUN_442120();
void FUN_442180();
void FUN_4427b0();
void FUN_442810();
void FUN_442200();
int FUN_4421f0();
void FUN_442640();
void FUN_4428a0();
void FUN_442a00();
void FUN_442a20();

extern int g_frameCount;

struct RaceResult
{
    int unk00; // 0x00
    int unk04; // 0x04
    int unk08; // 0x08
    int unk0c; // 0x0c
    int unk10; // 0x10
    int unk14; // 0x14
};

// Per-player race slot, one per car.
struct RaceEntry
{
    int type;              // 0x000
    int unk004;            // 0x004
    int unk008;            // 0x008
    int unk00c;            // 0x00c
    char unk010[0x24];     // 0x010
    BYTE unk034[0x104];    // 0x034
    RaceResult result;     // 0x138
};

extern RaceEntry g_60d78c[6];
