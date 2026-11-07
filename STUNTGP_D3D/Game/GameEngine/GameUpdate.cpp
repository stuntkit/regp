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

// GLOBAL: STUNTGP_D3D 0x612958
int g_612958;

// GLOBAL: STUNTGP_D3D 0x612970
int g_612970;

// Previous frame's keyboard state, copied from g_62d480.
// GLOBAL: STUNTGP_D3D 0x62dcf0
BYTE g_62dcf0[256];

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

// STUB: STUNTGP_D3D 0x40d860
void FUN_40d860()
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

// STUB: STUNTGP_D3D 0x42eaa0
void FUN_42eaa0()
{
}

// STUB: STUNTGP_D3D 0x431810
void FUN_431810()
{
}

// --- timer ---

// FUNCTION: STUNTGP_D3D 0x434820
DWORD FUN_434820()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return count.LowPart;
}

// STUB: STUNTGP_D3D 0x43d200
void FUN_43d200()
{
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

// --- input ---

// STUB: STUNTGP_D3D 0x4243f0
void FUN_4243f0()
{
}

// STUB: STUNTGP_D3D 0x4244c0
void FUN_4244c0()
{
}

// FUNCTION: STUNTGP_D3D 0x45ec20
void FUN_45ec20()
{
}

// STUB: STUNTGP_D3D 0x45ee60
void FUN_45ee60()
{
}

// STUB: STUNTGP_D3D 0x45ef00
void FUN_45ef00()
{
}

// STUB: STUNTGP_D3D 0x45f110
void FUN_45f110()
{
}

// FUNCTION: STUNTGP_D3D 0x45f210
void FUN_45f210()
{
    g_612958 = 0;
    memcpy(g_62dcf0, g_62d480, sizeof(g_62dcf0));
    FUN_4243f0();
    FUN_4244c0();
    FUN_45ef00();
    FUN_45f110();
    FUN_45ec20();
    FUN_45ee60();
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

// STUB: STUNTGP_D3D 0x462280
void FUN_462280()
{
}
