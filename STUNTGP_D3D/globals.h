#ifndef GLOBALS_H
#define GLOBALS_H
#define WIN32_LEAN_AND_MEAN
#include <ddraw.h>
#include <windows.h>

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

struct Car;

// Game state from 0x612948. FUN_445fa0 never schedules its zero stores past the
// inline memsets of g_612d54/g_612da4/g_61b5a4, so all of it is one object.
struct GameState
{
    int unk0000;             // 0x0000
    int unk0004;             // 0x0004
    int unk0008;             // 0x0008
    DWORD unk000c;           // 0x000c
    int unk0010;             // 0x0010
    int unk0014;             // 0x0014
    int unk0018;             // 0x0018
    int unk001c;             // 0x001c
    int unk0020;             // 0x0020
    int unk0024;             // 0x0024
    int unk0028;             // 0x0028
    int unk002c;             // 0x002c
    int unk0030;             // 0x0030
    DWORD unk0034;           // 0x0034
    int unk0038;             // 0x0038
    int frameCount;          // 0x003c
    int unk0040;             // 0x0040
    int unk0044;             // 0x0044
    DWORD unk0048;           // 0x0048
    BOOL unk004c;            // 0x004c
    int unk0050;             // 0x0050
    int unk0054;             // 0x0054
    int unk0058;             // 0x0058
    BYTE unk005c[0x240];     // 0x005c
    int unk029c;             // 0x029c
    int unk02a0;             // 0x02a0
    int unk02a4;             // 0x02a4
    int unk02a8;             // 0x02a8
    int unk02ac;             // 0x02ac
    char versionString[255]; // 0x02b0
    BYTE unk03af[0x1];       // 0x03af
    int unk03b0;             // 0x03b0
    DWORD unk03b4;           // 0x03b4
    DWORD unk03b8;           // 0x03b8
    DWORD unk03bc;           // 0x03bc
    // Performance counter ticks per 1/60 s.
    DWORD unk03c0;          // 0x03c0
    DWORD unk03c4;           // 0x03c4
    unsigned int unk03c8;    // 0x03c8
    Car *unk03cc[6];         // 0x03cc
    BYTE unk03e4[0x28];      // 0x03e4
    int unk040c[6];          // 0x040c
    BYTE unk0424[0x28];      // 0x0424
    int unk044c;             // 0x044c
    int unk0450;             // 0x0450
    int unk0454;             // 0x0454
    int unk0458;             // 0x0458
    int unk045c[0x2200];     // 0x045c
    int unk8c5c[0x20];       // 0x8c5c
    int unk8cdc;             // 0x8cdc
    int unk8ce0;             // 0x8ce0
    int unk8ce4;             // 0x8ce4
    int unk8ce8;             // 0x8ce8
    int unk8cec;             // 0x8cec
};

extern GameState g_612948;
#endif /* GLOBALS_H */
