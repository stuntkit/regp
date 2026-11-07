#define WIN32_LEAN_AND_MEAN

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <ddraw.h>
#include <windows.h>

#include "Game/GameEngine/Engine_LevelScript.h"
#include "Game/GameEngine/Game.h"
#include "windowInit.h"

#include "globals.h"

#include "common.h"
// #include "pure.h"

// FUNCTION: STUNTGP_D3D 0x44e490
void FUN_44e490()
{
    g_612994 = 0;
}

void FUN_44ea10();

// FUNCTION: STUNTGP_D3D 0x44e4b0
void FUN_44e4b0(BOOL windowMessage)
{
    DDSCAPS2 caps;
    if (windowMessage == 1)
    {
        if (g_WindowMessage == 0)
        {
            g_WindowMessage = windowMessage;
            g_surface->GetCaps(&caps);
            if (caps.dwCaps & DDSCAPS_MODEX)
            {
                FUN_422f30(g_dd4, &g_surface, &g_surface2, 640, 480, 8);
            }
            g_dd4->FlipToGDISurface();
            DrawMenuBar(g_Hwnd);
            RedrawWindow(g_Hwnd, NULL, NULL, RDW_FRAME);
            FUN_44e490();
            return;
        }
    }
    else
    {
        g_WindowMessage = 0;
        FUN_44ea10();
        // FUN_4411c0();
        // g_6244f4 = 0;
        // FUN_4320c0(1.0);
    }
}

// FUNCTION: STUNTGP_D3D 0x44e5d0
void FUN_44e5d0()
{
    g_61c37c = GetTickCount();
    g_61c394 = 0;
    g_61c390 = g_61c37c;
    g_61c370 = g_61c37c;
    g_61c388 = g_61c37c;
}

// FUNCTION: STUNTGP_D3D 0x44e610
void FUN_44e610()
{
    g_61c388 = g_61c390;
    g_61c390 = GetTickCount();
    g_61c36c = (float)(g_61c390 - g_61c388) * 0.06f;
    g_61c394++;
    DWORD elapsed = g_61c390 - g_61c370;
    // if over a second?
    if (elapsed > 1000)
    {
        g_61c39c = (g_61c394 * 1000 - g_61c35c * 1000) / elapsed;
        g_61c35c = g_61c394;
        g_61c370 = g_61c390;
    }
}

// thunk
// FUNCTION: STUNTGP_D3D 0x44e6b0
void thunk_FUN_44e6b0()
{
    FUN_44e610();
}

// FUNCTION: STUNTGP_D3D 0x44e6c0
void FUN_44e6c0()
{
    g_61c390 = GetTickCount();
}

// FUNCTION: STUNTGP_D3D 0x44e6d0
LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // #define WM_NULL                         0x0000
    // #define WM_CREATE                       0x0001
    // #define WM_DESTROY                      0x0002
    // #define WM_MOVE                         0x0003
    // #define WM_SIZE                         0x0005
    // #define WM_ACTIVATE                     0x0006
    BOOL windowMessage;
    if (uMsg < WM_ACTIVATE)
    {
        if (uMsg != WM_SIZE)
        {
            if (uMsg == WM_DESTROY)
            {
                PostQuitMessage(0);
                return DefWindowProc(hWnd, WM_DESTROY, wParam, lParam);
            }
            if (uMsg != WM_MOVE)
            {
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        }
        // TODO: what produces goto?
        if (!IsIconic(hWnd))
        {
            goto exit;
        }
        windowMessage = 1;
    }
    else
    {
        if (uMsg != WM_ACTIVATEAPP)
        {
            if ((uMsg == WM_CHAR) && (g_62ddfc == '\0'))
            {
                g_62ddfc = wParam;
                // TODO: save wparam to static
                return DefWindowProc(hWnd, WM_CHAR, wParam, lParam);
            }
            goto exit;
        }
        // TODO wparam blah
        g_61c374 = wParam;
        if ((wParam == 0) || (!g_WindowMessage))
        {
            goto exit;
        }
        windowMessage = 0;
    }
    FUN_44e4b0(windowMessage);
exit:
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// unused: STUNTGP_D3D 0x44e7a0

// FUNCTION: STUNTGP_D3D 0x44e870
void m_keyboard()
{
    for (int i = 10; i != 0; i--)
    {
        GetKeyboardState(g_62d480);
    }
}

// FUNCTION: STUNTGP_D3D 0x44e890
BOOL windowCreate(HINSTANCE hInstance, HINSTANCE hPrevInstance)
{

    // TODO: global?
    static HINSTANCE g_HINSTANCE = hInstance;

    DWORD totalVideoMem = 0;
    DWORD totalTextureMem = 0;
    DWORD freeMem = 0;

    const char menuName[] = "AppMenu";
    const char className[] = "Stunt GP";
    if (!hPrevInstance)
    {
        WNDCLASS windowInfo;
        windowInfo.style = CS_OWNDC;
        windowInfo.lpfnWndProc = WndProc;
        windowInfo.cbClsExtra = 0;
        windowInfo.cbWndExtra = 0;
        windowInfo.hInstance = hInstance;
        windowInfo.hIcon = LoadIcon(hInstance, IDC_ARROW);
        windowInfo.hCursor = NULL;
        windowInfo.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
        windowInfo.lpszMenuName = menuName;
        windowInfo.lpszClassName = className;
        if (!RegisterClass(&windowInfo))
        {
            return FALSE;
        }
    }
    g_Hwnd = windowCreateInternal(hInstance, "Stunt GP", "Stunt GP");
    if (!g_Hwnd)
    {
        return FALSE;
    }

    //  TODO: DirectX init
    windowDDCreate(&g_dd, NULL, g_Hwnd);
    ddGetDD4(g_dd, &g_dd4, g_Hwnd);
    ddGetMemory(g_dd4, &totalVideoMem, &totalTextureMem, &freeMem);
    // FUN_4229e0();
    FUN_422f30(g_dd4, &g_surface, &g_surface2, 640, 480, 8);
    m_keyboard();
    return !FUN_4230b0(g_61c384, g_571fd4);
}

// FUNCTION: STUNTGP_D3D 0x44e9b0
HRESULT surfaceIsLost(LPDIRECTDRAWSURFACE4 *surface)
{
    if (*surface)
    {
        return (*surface)->IsLost();
    }
    return DD_OK;
}

// FUNCTION: STUNTGP_D3D 0x44e9c0
HRESULT surfaceRestore(LPDIRECTDRAWSURFACE4 *surface)
{
    if (*surface)
    {
        return (*surface)->Restore();
    }
    return DD_OK;
}

// FUNCTION: STUNTGP_D3D 0x4314c0
BOOL surfaceSlotsNoneLost()
{
    for (DWORD i = 0; i < g_surfaceSlotCount; i++)
    {
        if (g_surfaceSlots[i].surface && g_surfaceSlots[i].surface->IsLost())
        {
            return FALSE;
        }
        if (g_surfaceSlots[i].surface2 && g_surfaceSlots[i].surface2->IsLost())
        {
            return FALSE;
        }
    }
    return TRUE;
}

// FUNCTION: STUNTGP_D3D 0x44e9d0
void FUN_44e9d0()
{
    if (surfaceIsLost(&g_surface) == DD_OK && surfaceIsLost(&g_surface2) == DD_OK && surfaceSlotsNoneLost() == TRUE)
    {
        return;
    }
    FUN_44e4b0(1);
}

// FUNCTION: STUNTGP_D3D 0x431510
BOOL surfaceSlotsRestore()
{
    for (DWORD i = 0; i < g_surfaceSlotCount; i++)
    {
        if (g_surfaceSlots[i].surface && g_surfaceSlots[i].surface->Restore())
        {
            return FALSE;
        }
        if (g_surfaceSlots[i].surface2 && g_surfaceSlots[i].surface2->Restore())
        {
            return FALSE;
        }
    }
    return TRUE;
}

// STUB: STUNTGP_D3D 0x42bf00
void FUN_42bf00()
{
}

// FUNCTION: STUNTGP_D3D 0x44ea10
void FUN_44ea10()
{
    if (surfaceRestore(&g_surface) != DD_OK || surfaceRestore(&g_surface2) != DD_OK || surfaceSlotsRestore() != TRUE)
    {
        FUN_44e4b0(1);
        return;
    }
    FUN_42bf00();
}

// FUNCTION: STUNTGP_D3D 0x44ea50
void FUN_44ea50()
{
}

// FUNCTION: STUNTGP_D3D 0x44ea60
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    MSG uMsg;

    g_DISPLAYRESWIDTH = 640;
    g_DISPLAYRESHEIGHT = 480;
    g_DISPLAYRESDEPTH = 8;
#if !defined(SGP_DEBUG)
    ShowCursor(FALSE);
#endif
    Script_ParseGameConfig();
    GetGameBuildVersion();
    if (!windowCreate(hInstance, hPrevInstance))
    {
        return FALSE;
    }

    g_612be8 = 2;
    g_612bec = 2;
    FUN_442120();
    FUN_44e5d0();
    do
    {
        if (PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE))
        {
            if (uMsg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&uMsg);
            DispatchMessage(&uMsg);
        }
        else
        {
            FUN_44e9d0();
            if (g_61c374 && !g_WindowMessage)
            {
                if (g_612be8 == 1)
                {
                    FUN_442810();
                    FUN_4427b0();
                }
                else if (g_612be8 == 2)
                {
                    FUN_441f00();
                    FUN_441d70();
                }
                thunk_FUN_44e6b0();
            }
        }
    } while (g_612948 != 1);

    FUN_44e6c0();
    FUN_442180();
    FUN_44ea50();
    return uMsg.wParam;
}
