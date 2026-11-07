#include "GameUpdate.h"

#include <cstring>
#include <float.h>

#include "../../globals.h"

// GLOBAL: STUNTGP_D3D 0x60d618
int g_60d618;

// GLOBAL: STUNTGP_D3D 0x60d620
int g_60d620;

// GLOBAL: STUNTGP_D3D 0x60df9c
int g_60df9c;

// GLOBAL: STUNTGP_D3D 0x60f2c0
int g_60f2c0;

// GLOBAL: STUNTGP_D3D 0x60f2c4
DWORD g_60f2c4;

// GLOBAL: STUNTGP_D3D 0x61294c
int g_61294c;

// GLOBAL: STUNTGP_D3D 0x612954
DWORD g_612954;

// --- per-tick game logic ---

// STUB: STUNTGP_D3D 0x401770
void FUN_401770()
{
}

// FUNCTION: STUNTGP_D3D 0x4023f0
void FUN_4023f0()
{
    GameSlot *slot = g_4722d0;
    slot->unk0d8 = 0;
    slot->unk0dc = 0;
    slot->unk0e0 = 0;
    slot->unk104 = 0;
    slot->unk108 = 0;
    slot->unk10c = 0;
}

// STUB: STUNTGP_D3D 0x405210
void FUN_405210()
{
}

// STUB: STUNTGP_D3D 0x40dad0
void FUN_40dad0()
{
}

// STUB: STUNTGP_D3D 0x40de30
void FUN_40de30()
{
}

// STUB: STUNTGP_D3D 0x415df0
void FUN_415df0()
{
}

// STUB: STUNTGP_D3D 0x418a90
void FUN_418a90()
{
}

// STUB: STUNTGP_D3D 0x427140
void FUN_427140()
{
}

// --- fpu ---

// FUNCTION: STUNTGP_D3D 0x4294f0
void FUN_4294f0()
{
    _controlfp(_PC_53, _MCW_PC);
    _controlfp(_RC_NEAR, _MCW_RC);
}

// FUNCTION: STUNTGP_D3D 0x429510
void FUN_429510()
{
    FUN_4294f0();
}

// STUB: STUNTGP_D3D 0x431790
void FUN_431790()
{
}

// FUNCTION: STUNTGP_D3D 0x431810
void FUN_431810()
{
    FUN_431790();
}

// --- timer ---

// FUNCTION: STUNTGP_D3D 0x434820
DWORD FUN_434820()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return count.LowPart;
}

// STUB: STUNTGP_D3D 0x443a80
void FUN_443a80()
{
}

// STUB: STUNTGP_D3D 0x446110
void FUN_446110()
{
}

// STUB: STUNTGP_D3D 0x447c90
void FUN_447c90()
{
}

// STUB: STUNTGP_D3D 0x45e1d0
void FUN_45e1d0()
{
}

// STUB: STUNTGP_D3D 0x45f8f0
void FUN_45f8f0(int a, int b)
{
}

// --- sound ---

// STUB: STUNTGP_D3D 0x460af0
void FUN_460af0(int a)
{
}


// STUB: STUNTGP_D3D 0x41bdd0
void FUN_41bdd0()
{
}

// STUB: STUNTGP_D3D 0x447bd0
void FUN_447bd0(int a)
{
}

// STUB: STUNTGP_D3D 0x447c30
void FUN_447c30(int a)
{
}

// STUB: STUNTGP_D3D 0x45fa00
void FUN_45fa00()
{
}

// STUB: STUNTGP_D3D 0x45fa30
void FUN_45fa30()
{
}

// STUB: STUNTGP_D3D 0x460cb0
void FUN_460cb0(int a)
{
}

// STUB: STUNTGP_D3D 0x460dd0
void FUN_460dd0()
{
}
