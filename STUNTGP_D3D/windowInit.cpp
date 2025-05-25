#include "windowInit.h"

// FUNCTION: STUNTGP_D3D 0x422700
HWND windowCreateInternal(HINSTANCE hInstance, LPCSTR className, LPCSTR windowName)
{
    HWND wHandle = CreateWindowEx(
        WS_EX_APPWINDOW,
        className,
        windowName,
        WS_POPUP,
        0,
        0,
        GetSystemMetrics(SM_CXFULLSCREEN),
        GetSystemMetrics(SM_CYFULLSCREEN),
        NULL,
        NULL,
        hInstance,
        NULL);
    if (!wHandle)
    {
        return NULL;
    }
    ShowWindow(wHandle, SW_NORMAL);
    UpdateWindow(wHandle);
    return wHandle;
}

// STUB: STUNTGP_D3D 0x422780
void FUN_422780()
{
}

// STUB: STUNTGP_D3D 0x4227b0
void FUN_4227b0()
{
}

// STUB: STUNTGP_D3D 0x4227e0
void FUN_4227e0()
{
}

// STUB: STUNTGP_D3D 0x422820
void FUN_422820()
{
}

// STUB: STUNTGP_D3D 0x422860
void FUN_422860()
{
}

// STUB: STUNTGP_D3D 0x422880
void FUN_422880()
{
}

// STUB: STUNTGP_D3D 0x4228a0
void FUN_4228a0()
{
}

// STUB: STUNTGP_D3D 0x4228c0
void FUN_4228c0()
{
}

// STUB: STUNTGP_D3D 0x4228e0
void FUN_4228e0()
{
}

// STUB: STUNTGP_D3D 0x422910 - unused
void FUN_422910()
{
}

// STUB: STUNTGP_D3D 0x422930
void FUN_422930()
{
}

// STUB: STUNTGP_D3D 0x422950
void FUN_422950()
{
}

// STUB: STUNTGP_D3D 0x4229e0
void FUN_4229e0()
{
}

// STUB: STUNTGP_D3D 0x422a00
void FUN_422a00()
{
}

// STUB: STUNTGP_D3D 0x422a20
void FUN_422a20()
{
}

// STUB: STUNTGP_D3D 0x422a60
void FUN_422a60()
{
}

// STUB: STUNTGP_D3D 0x422a80
void FUN_422a80()
{
}

// STUB: STUNTGP_D3D 0x422ac0
void FUN_422ac0()
{
}

// STUB: STUNTGP_D3D 0x422b50
void FUN_422b50()
{
}

// STUB: STUNTGP_D3D 0x422ba0
void FUN_422ba0()
{
}

// STUB: STUNTGP_D3D 0x422bb0
void FUN_422bb0()
{
}

// STUB: STUNTGP_D3D 0x422bf0
void FUN_422bf0()
{
}

// STUB: STUNTGP_D3D 0x422c60
void FUN_422c60()
{
}

// STUB: STUNTGP_D3D 0x422d50
void FUN_422d50()
{
}

// STUB: STUNTGP_D3D 0x422df0
void FUN_422df0()
{
}

// STUB: STUNTGP_D3D 0x422ea0
void FUN_422ea0()
{
}

// STUB: STUNTGP_D3D 0x422f30
void FUN_422f30()
{
}

// STUB: STUNTGP_D3D 0x423070
void FUN_423070()
{
}

// STUB: STUNTGP_D3D 0x4230b0
void FUN_4230b0()
{
}
