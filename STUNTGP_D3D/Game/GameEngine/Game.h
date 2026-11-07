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


struct GhostRecord
{
    int unk00;
    int unk04;
    Unk4d5cc0 *ghost;
    unsigned int time;
};

extern GhostRecord g_60d628[4];
