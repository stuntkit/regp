#define WIN32_LEAN_AND_MEAN

#include <cstdio>
#include <d3dtypes.h>
#include <ddraw.h>
#include <windows.h>

#include "common.h"
#include "globals.h"

struct errorMessage
{
    char *message;
    int code;
};

HWND windowCreateInternal(HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName);

const char *ddGetErrMessage(int res);
int ddSetCoopLevel(LPDIRECTDRAW *lplpDD, HWND hWnd);
int windowDDCreate(LPDIRECTDRAW *lplpDD, GUID *lpGUID, HWND hWnd);
int dd4SetCoopLevel(LPDIRECTDRAW4 *lplpDD4, HWND hWnd);
int ddGetDD4(LPDIRECTDRAW *lplpDD, LPDIRECTDRAW4 *lplpDD4, HWND hWnd);
void FUN_422860();
void FUN_422880();
void FUN_4228a0();
void FUN_4228c0();
void FUN_4228e0();
void FUN_422910();
void FUN_422930();
int ddGetMemory(LPDIRECTDRAW4 *lplpDD4, LPDWORD totalVideoMem, LPDWORD totalTextureMem, LPDWORD freeVideoMem);
void FUN_4229e0();
void FUN_422a00(LPDIRECTDRAWSURFACE4 *surface);
int FUN_422a80(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDDSURFACEDESC2 desc, int fatal);
int FUN_422ac0(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, int width, int height, DWORD memCaps);
void FUN_422bb0(DWORD mask, int *bits, int *shift);
void FUN_422bf0();
int FUN_422c60(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDIRECTDRAWSURFACE4 *surface2, int width, int height,
               int depth);
int FUN_422d50(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDIRECTDRAWSURFACE4 *surface2, int width, int height);
int FUN_422df0(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDIRECTDRAWSURFACE4 *surface2, int width, int height);
int FUN_422ea0(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDIRECTDRAWSURFACE4 *surface2, int width, int height);
int FUN_422f30(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDIRECTDRAWSURFACE4 *surface2, int width, int height,
               int depth);
void FUN_423070(BYTE *src);
int FUN_4230b0(LPDIRECTDRAWPALETTE *palette, BYTE *src);

extern int DAT_CAPS;

// TODO(merge): transitional overloads for callers that still pass the interfaces by value.
// The original callers pass the address of the global (e.g. &g_dd); remove these once they do.
// Taking a reference keeps the forwarded pointer identical to the original call.
inline int ddGetDD4(LPDIRECTDRAW &lpDD, LPDIRECTDRAW4 *lplpDD4, HWND hWnd)
{
    return ddGetDD4(&lpDD, lplpDD4, hWnd);
}

inline int ddGetMemory(LPDIRECTDRAW4 &lpDD4, LPDWORD totalVideoMem, LPDWORD totalTextureMem, LPDWORD freeVideoMem)
{
    return ddGetMemory(&lpDD4, totalVideoMem, totalTextureMem, freeVideoMem);
}

inline int FUN_4230b0(LPDIRECTDRAWPALETTE &palette, void *&src)
{
    return FUN_4230b0(&palette, (BYTE *)&src);
}
