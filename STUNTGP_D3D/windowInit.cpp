#include "windowInit.h"

// FUNCTION: STUNTGP_D3D 0x422700
HWND windowCreateInternal(HINSTANCE hInstance, LPCSTR className, LPCSTR windowName)
{
    HWND wHandle =
        CreateWindowEx(WS_EX_APPWINDOW, className, windowName, WS_POPUP, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN),
                       GetSystemMetrics(SM_CYFULLSCREEN), NULL, NULL, hInstance, NULL);
    if (!wHandle)
    {
        return NULL;
    }
    ShowWindow(wHandle, SW_NORMAL);
    UpdateWindow(wHandle);
    return wHandle;
}

// // STUB: STUNTGP_D3D 0x422780
// void FUN_422780()
// {
// }

// // STUB: STUNTGP_D3D 0x4227b0
// void FUN_4227b0()
// {
// }

// TODO: move
int setCoopLevel(LPDIRECTDRAW lplpDD, HWND hWnd)
{
    int res = lplpDD->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE);
    if (res != DD_OK)
    {
        // TODO
    }
    return res;
}

// FUNCTION: STUNTGP_D3D 0x4227e0
int windowDDCreate(LPDIRECTDRAW *lplpDD, GUID *lpGUID, HWND hWnd)
{
    int res = 0;
    res = DirectDrawCreate(lpGUID, lplpDD, NULL);
    if (res != DD_OK)
    {
        // TODO
        // FUN_00422690(puVar1);
        // FUN_0044e4a0();
    }
    setCoopLevel(*lplpDD, hWnd);
    return res;
}

// TODO: move
int FUN_004227b0(LPDIRECTDRAW4 ppvObj, HWND hWnd)
{
    // TODO; move the last parameter to define and use in both SetCooperativeLevel?
    int res = ppvObj->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE);
    if (res != DD_OK)
    {
        // TODO
    }
    return res;
}

// STUB: STUNTGP_D3D 0x422820
int ddGetDD4(LPDIRECTDRAW lplpDD, LPDIRECTDRAW4 *ppvObj, HWND hWnd)
{
    int res = lplpDD->QueryInterface(IID_IDirectDraw4, (LPVOID *)ppvObj);
    if (res != DD_OK)
    {
        // TODO
    }
    FUN_004227b0(*ppvObj, hWnd);
    return res;
}

// // STUB: STUNTGP_D3D 0x422860
// void FUN_422860()
// {
// }

// // STUB: STUNTGP_D3D 0x422880
// void FUN_422880()
// {
// }

// // STUB: STUNTGP_D3D 0x4228a0
// void FUN_4228a0()
// {
// }

// // STUB: STUNTGP_D3D 0x4228c0
// void FUN_4228c0()
// {
// }

// // STUB: STUNTGP_D3D 0x4228e0
// void FUN_4228e0()
// {
// }

// // STUB: STUNTGP_D3D 0x422910 - unused
// void FUN_422910()
// {
// }

// // STUB: STUNTGP_D3D 0x422930
// void FUN_422930()
// {
// }

// FUNCTION: STUNTGP_D3D 0x422950
int ddGetMemory(LPDIRECTDRAW4 lpDD4, LPDWORD totalVideoMem, LPDWORD totalTextureMem, LPDWORD freeMem)
{
    DWORD dwTotal = 0;
    DWORD dwFree = 0;

    DDSCAPS2 ddsCaps2;
    ZeroMemory(&ddsCaps2, sizeof(ddsCaps2));
    ddsCaps2.dwCaps = DDSCAPS_VIDEOMEMORY;
    int res = lpDD4->GetAvailableVidMem(&ddsCaps2, &dwTotal, &dwFree);
    if (res == DD_OK)
    {
        *totalVideoMem = dwTotal;
        *freeMem = dwFree;
#if defined(SGP_DEBUG)
        char buffer[256];
        sprintf(buffer, "Free/Total video mem: %lu/%lu MB", dwFree / 1024 / 1024, dwTotal / 1024 / 1024);
        OutputDebugString(buffer);
#endif
        DDSCAPS2 textureCaps;
        ZeroMemory(&textureCaps, sizeof(textureCaps));
        textureCaps.dwCaps = DDSCAPS_TEXTURE;
        res = lpDD4->GetAvailableVidMem(&textureCaps, &dwTotal, &dwFree);
        if (res == DD_OK)
        {
            *totalTextureMem = dwTotal;
            res = DD_OK;
#if defined(SGP_DEBUG)
            sprintf(buffer, "Free/total texture mem: %lu/%lu MB", dwFree / 1024 / 1024, dwTotal / 1024 / 1024);
            OutputDebugString(buffer);
#endif
        }
    }
    return res;
}

// // STUB: STUNTGP_D3D 0x4229e0
// void FUN_4229e0()
// {
// }

// // STUB: STUNTGP_D3D 0x422a00
// void FUN_422a00()
// {
// }

// // STUB: STUNTGP_D3D 0x422a20
// void FUN_422a20()
// {
// }

// // STUB: STUNTGP_D3D 0x422a60
// void FUN_422a60()
// {
// }

// // STUB: STUNTGP_D3D 0x422a80
// void FUN_422a80()
// {
// }

// // STUB: STUNTGP_D3D 0x422ac0
// void FUN_422ac0()
// {
// }

// // STUB: STUNTGP_D3D 0x422b50
// void FUN_422b50()
// {
// }

// // STUB: STUNTGP_D3D 0x422ba0
// void FUN_422ba0()
// {
// }

// // STUB: STUNTGP_D3D 0x422bb0
// void FUN_422bb0()
// {
// }

// // STUB: STUNTGP_D3D 0x422bf0
// void FUN_422bf0()
// {
// }

// // STUB: STUNTGP_D3D 0x422c60
// void FUN_422c60()
// {
// }

// // STUB: STUNTGP_D3D 0x422d50
// void FUN_422d50()
// {
// }

// // STUB: STUNTGP_D3D 0x422df0
// void FUN_422df0()
// {
// }

// // STUB: STUNTGP_D3D 0x422ea0
// void FUN_422ea0()
// {
// }

// STUB: STUNTGP_D3D 0x422f30
int FUN_422f30(LPDIRECTDRAW4 lpDD4, void *b, void *c, int width, int height, int depth)
{
    // TODO
    if (false)
    {
        int res = lpDD4->SetDisplayMode(width, height, depth, 0, 0);
        if (res != DD_OK)
        {
            if (false)
            {
            }
            if (false)
            {
            }
        }
    }
    return 0;
}

// // STUB: STUNTGP_D3D 0x423070
// void FUN_423070()
// {
// }

// STUB: STUNTGP_D3D 0x4230b0
int FUN_4230b0(LPDIRECTDRAWPALETTE outPalette, void *sth)
{
    // TODO: init static 256 palette
    LPPALETTEENTRY pal;
    int res = 0;
    HDC hDC = GetDC(NULL);
    int rasterCaps = GetDeviceCaps(hDC, RASTERCAPS);
    if (rasterCaps & RC_PALETTE)
    {
        GetSystemPaletteEntries(hDC, 0, 256, pal);
        // TODO
        // int res2 = lpDD->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE, pal, param_1, NULL);
        // if (res2 == DD_OK) {

        // }
    }
    ReleaseDC(NULL, hDC);
    return res;
}
