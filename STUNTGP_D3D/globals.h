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

extern int g_6244f4;

extern DWORD g_61c37c;
extern DWORD g_61c394;
extern DWORD g_61c390;
extern DWORD g_61c370;
extern DWORD g_61c388;

extern DWORD g_61c35c;
extern DWORD g_61c36c;
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

extern DWORD g_surfaceSlotCount;
extern SurfaceSlot g_surfaceSlots[255];

// --- WinMain main loop state ---
extern int g_612be8;
extern int g_612bec;
extern int g_612948;
#endif /* GLOBALS_H */
