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

// TODO: Mem_Alloc/Mem_Free belong in their own source file (needs a CMakeLists entry)
#include <stdlib.h>
#include <string.h>

// The original keeps EBP frames everywhere (/Oy-). Drop this once the global flags do.
#pragma optimize("y", off)

struct MemSlot
{
    char *data;
    void *raw;
    DWORD total;
    DWORD size;
    int type;
    DWORD id;
};

struct MemManager
{
    DWORD type0Bytes;
    DWORD type1Bytes;
    DWORD peakBytes;
    DWORD allocCount;
    DWORD unk10;
    BOOL freeType1;
    MemSlot slots[0x180];
};

// GLOBAL: STUNTGP_D3D 0x589e14
MemManager g_Mem;

// FUNCTION: STUNTGP_D3D 0x42e8d0
void *Mem_Alloc(int size, int type)
{
    MemSlot *slot = g_Mem.slots;
    for (DWORD i = 0; i < 0x180; slot++, i++)
    {
        if (slot->raw == NULL)
        {
            DWORD total = size + 0x24;
            void *raw = malloc(total);
            char *data = (char *)(((DWORD)raw + 0x20) & ~0x1f);
            slot->data = data;
            slot->raw = raw;
            slot->total = total;
            slot->size = size;
            slot->type = type;
            slot->id = g_Mem.allocCount;
            g_Mem.allocCount++;
            if (type == 1)
            {
                g_Mem.type1Bytes += total;
            }
            else
            {
                g_Mem.type0Bytes += total;
            }
            if (g_Mem.type0Bytes + g_Mem.type1Bytes > g_Mem.peakBytes)
            {
                g_Mem.peakBytes = g_Mem.type0Bytes + g_Mem.type1Bytes;
            }
            memset(data, 0, size);
            return data;
        }
    }
    return NULL;
}

// FUNCTION: STUNTGP_D3D 0x42e980
int Mem_Free(void *ptr)
{
    if (ptr != NULL)
    {
        MemSlot *slot = g_Mem.slots;
        for (DWORD i = 0; i < 0x180; slot++, i++)
        {
            if (ptr == slot->data)
            {
                if ((slot->type == 1) && (g_Mem.freeType1 == FALSE))
                {
                    return slot->total;
                }
                DWORD total = slot->total;
                if (slot->type == 1)
                {
                    g_Mem.type1Bytes -= total;
                }
                else
                {
                    g_Mem.type0Bytes -= total;
                }
                free(slot->raw);
                slot->data = NULL;
                slot->raw = NULL;
                slot->total = 0;
                slot->size = 0;
                slot->type = 0;
                slot->id = 0;
                return total;
            }
        }
    }
    return 0;
}
// --- end agent D ---
