#ifndef GLOBALS_H
#define GLOBALS_H
#define WIN32_LEAN_AND_MEAN
#include <ddraw.h>
#include <windows.h>

extern BOOL g_612994;

extern void *g_571fd4;

extern int g_DISPLAYRESWIDTH;

extern int g_DISPLAYRESHEIGHT;

extern int g_DISPLAYRESDEPTH;

extern BOOL g_WindowMessage;

extern HWND g_Hwnd;

extern float g_6244f4;
extern int g_6244ec;

extern DWORD g_61c37c;
extern DWORD g_61c394;
extern DWORD g_61c390;
extern DWORD g_61c370;
extern DWORD g_61c388;

extern DWORD g_61c35c;
extern float g_61c36c;
extern DWORD g_61c39c;

extern char g_62ddfc;
extern WPARAM g_61c374;

extern BYTE g_62d480[256];

extern LPDIRECTDRAWSURFACE4 g_surface;
extern LPDIRECTDRAWSURFACE4 g_surface2;

extern LPDIRECTDRAW g_dd;
extern LPDIRECTDRAW4 g_dd4;

extern LPDIRECTDRAWPALETTE g_61c384;

extern char g_GameDirectory[128];

extern int g_DD_DISPLAYRESWIDTH;
extern int g_DD_DISPLAYRESHEIGHT;
extern int g_DD_DISPLAYRESDEPTH;
extern int g_005728d8_dd;

struct SurfaceSlot
{
    LPDIRECTDRAWSURFACE4 surface;
    DWORD unk04;
    LPDIRECTDRAWSURFACE4 surface2;
    DWORD unk0c;
};

// DirectDraw devices collected by FUN_42f530, the selected device's state and
// the surface slots. FUN_42f6a0 clears all of it with one memset.
struct DisplayDevices
{
    int count;                     // 0x00000
    int unk04;                     // 0x00004
    BYTE devices[8][0x3d44];       // 0x00008
    int unk1ea28;                  // 0x1ea28
    int *deviceDesc;               // 0x1ea2c
    int unk1ea30;                  // 0x1ea30
    int unk1ea34;                  // 0x1ea34
    DDPIXELFORMAT *textureFormat;  // 0x1ea38
    int hasArgb1555;               // 0x1ea3c
    int unk1ea40;                  // 0x1ea40
    DWORD surfaceSlotCount;        // 0x1ea44
    SurfaceSlot surfaceSlots[255]; // 0x1ea48
};

extern DisplayDevices g_5ba788;

// --- WinMain main loop state ---
extern int g_612be8;
extern int g_612bec;
extern int g_612948;
extern HINSTANCE g_hInstance;

// --- windowInit ---
extern LPDIRECTDRAWSURFACE4 *g_61c358;
extern int g_DD_DISPLAYPITCH;
extern int g_DD_RSHIFT;
extern int g_DD_GSHIFT;
extern int g_DD_BSHIFT;
extern int g_DD_RBITS;
extern int g_DD_GBITS;
extern int g_DD_BBITS;
#endif /* GLOBALS_H */
