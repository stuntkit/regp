#include "globals.h"

// TODO: move this where it is needed, global stuff
// 0-1
// GLOBAL: STUNTGP_D3D 0x612994
BOOL g_612994 = 0;

// GLOBAL: STUNTGP_D3D 0x571fd4
void *g_571fd4 = NULL;

// GLOBAL: STUNTGP_D3D 0x576bcc
int g_DISPLAYRESWIDTH = 0;

// GLOBAL: STUNTGP_D3D 0x576bd0
int g_DISPLAYRESHEIGHT = 0;

// GLOBAL: STUNTGP_D3D 0x576bd4
int g_DISPLAYRESDEPTH = 0;

// GLOBAL: STUNTGP_D3D 0x61c364
BOOL g_WindowMessage = 0;

// GLOBAL: STUNTGP_D3D 0x61c398
HWND g_Hwnd = 0;

// GLOBAL: STUNTGP_D3D 0x6244f4
int g_6244f4 = 0;

// Timing stuff

// GLOBAL: STUNTGP_D3D 0x61c37c
DWORD g_61c37c = 0;

// GLOBAL: STUNTGP_D3D 0x61c394
DWORD g_61c394 = 0;

// GLOBAL: STUNTGP_D3D 0x61c390
DWORD g_61c390 = 0;

// GLOBAL: STUNTGP_D3D 0x61c370
DWORD g_61c370 = 0;

// GLOBAL: STUNTGP_D3D 0x61c388
DWORD g_61c388 = 0;

// GLOBAL: STUNTGP_D3D 0x61c35c
DWORD g_61c35c = 0;

// GLOBAL: STUNTGP_D3D 0x61c36c
DWORD g_61c36c = 0;

// GLOBAL: STUNTGP_D3D 0x61c39c
DWORD g_61c39c = 0;

// GLOBAL: STUNTGP_D3D 0x62ddfc
char g_62ddfc = 0;

// GLOBAL: STUNTGP_D3D 0x61c374
WPARAM g_61c374 = 0;

// GLOBAL: STUNTGP_D3D 0x62d480
BYTE g_62d480[256];

// GLOBAL: STUNTGP_D3D 0x61c368
LPDIRECTDRAWSURFACE4 g_surface;

// GLOBAL: STUNTGP_D3D 0x61c3a0
LPDIRECTDRAWSURFACE4 g_surface2;

// GLOBAL: STUNTGP_D3D 0x61c378
LPDIRECTDRAW g_dd = NULL;

// GLOBAL: STUNTGP_D3D 0x61c380
LPDIRECTDRAW4 g_dd4 = NULL;

// GLOBAL: STUNTGP_D3D 0x61c384
LPDIRECTDRAWPALETTE g_61c384 = NULL;

// GLOBAL: STUNTGP_D3D 0x48489c
char g_GameDirectory[128] = "D:\\Game\\";

// GLOBAL: STUNTGP_D3D 0x576b80
int g_DD_DISPLAYRESWIDTH = 0;

// GLOBAL: STUNTGP_D3D 0x576b84
int g_DD_DISPLAYRESHEIGHT = 0;

// GLOBAL: STUNTGP_D3D 0x576bbc
int g_DD_DISPLAYRESDEPTH = 0;

// GLOBAL: STUNTGP_D3D 0x5728d8
int g_005728d8_dd = 0;

// GLOBAL: STUNTGP_D3D 0x5d91cc
DWORD g_surfaceSlotCount = 0;

// size inferred: next referenced address is 0x5da1c0
// GLOBAL: STUNTGP_D3D 0x5d91d0
SurfaceSlot g_surfaceSlots[255];

// --- agent D (io_wad / Engine_LevelScript) ---

// zero-filled, 32-byte aligned allocation tracked in a 0x180-slot table at 0x589e2c
// STUB: STUNTGP_D3D 0x42e8d0
void *Mem_Alloc(int size, int type)
{
    return NULL;
}

// STUB: STUNTGP_D3D 0x42e980
int Mem_Free(void *ptr)
{
    return 0;
}
// --- end agent D ---
