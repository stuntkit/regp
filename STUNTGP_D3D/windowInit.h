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
void ddReleaseSurface(LPDIRECTDRAWSURFACE4 *surface);
void ddReleaseDD(LPDIRECTDRAW *lplpDD);
void ddReleaseDD4(LPDIRECTDRAW4 *lplpDD4);
void ddRelease();
void windowDestroy(HWND *hWnd);
int ddGetMemory(LPDIRECTDRAW4 *lplpDD4, LPDWORD totalVideoMem, LPDWORD totalTextureMem, LPDWORD freeVideoMem);
void FUN_4229e0();
void FUN_422a00(LPDIRECTDRAWSURFACE4 *surface);
void FUN_422a20();
void FUN_422a60();
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
