#define WIN32_LEAN_AND_MEAN

#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <windows.h>

#include "uwu.h"
#include "windowInit.h"

#include "globals.h"

#include "pure.h"

// FUNCTION: STUNTGP_D3D 0x44e490
void FUN_44e490()
{
    g_612994 = 0;
}

// FUNCTION: STUNTGP_D3D 0x44e4a0
void exitError()
{
    exit(1);
}

// fastcall ?
// STUB: STUNTGP_D3D 0x44e4b0
void FUN_44e4b0(BOOL windowMessage)
{
    if (windowMessage)
    {
        if (!g_WindowMessage)
        {
            g_WindowMessage = windowMessage;
            // TODO: class sth
            DrawMenuBar(g_Hwnd);
            RedrawWindow(g_Hwnd, NULL, NULL, RDW_FRAME);
            FUN_44e490();
            return;
        }
    }
    else
    {
        g_WindowMessage = 0;
        // FUN_44ea10();
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
    g_61c394 = g_61c394 + 1;
    g_61c36c = (float)(g_61c390 - g_61c388) * 0.06;
    // if over a second?
    if (1000 < g_61c390 - g_61c370)
    {
        g_61c39c = (g_61c394 * 1000 + g_61c35c * -1000) / (g_61c390 - g_61c370);
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

// TODO: is this even correct? check assembly
// STUB: STUNTGP_D3D 0x44e870
void m_keyboard()
{
    int i = 10;
    for (i = 10; i >= 0; i--)
    {
        GetKeyboardState(g_62d480[i]);
    }
}

// FUNCTION: STUNTGP_D3D 0x44e890
BOOL windowCreate(HINSTANCE hInstance, HINSTANCE hPrevInstance)
{

    // TODO: global?
    static HINSTANCE g_HINSTANCE = hInstance;

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
    // FUN_4227e0(&g_61c378_dd, NULL, g_Hwnd);
    // FUN_422820(&g_61c378_dd, &g_61c380, g_Hwnd);
    // FUN_422950(&g_61c380, &local_10, &local_c, &local_8);
    // FUN_4229e0();
    // FUN_422f30(g_61c380, &g_61c368, &g_61c3a0, 640, 480, 8);
    // m_keyboard();
    // return !FUN_4230b0(&g_61c384, g_571fd4);
    return NULL;
}

// FUNCTION: STUNTGP_D3D 0x44e9b0
int FUN_44e9b0(int *param_1)
{
    if (param_1)
    {
        // TODO: objects
    }
    return NULL;
}
// FUNCTION: STUNTGP_D3D 0x44e9c0
int *FUN_44e9c0(int *param_1)
{
    if (param_1)
    {
        // TODO: objects
    }
    return NULL;
}

// FUNCTION: STUNTGP_D3D 0x44e9d0
void FUN_44e9d0()
{
    if (!FUN_44e9b0(&g_61c368))
    {
        if (!FUN_44e9b0(&g_61c3a0))
        {
            // if (FUN_4314c0() == 1)
            // {
            //     return;
            // }
        }
    }
    FUN_44e4b0(1);

    return;
}

// FUNCTION: STUNTGP_D3D 0x44ea10

// FUNCTION: STUNTGP_D3D 0x44ea50
void FUN_44ea50()
{
}

// FUNCTION: STUNTGP_D3D 0x44ea60
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    MSG uMsg;
    static BOOL SHOULD_STOP = false;

    g_DISPLAYRESWIDTH = 640;
    g_DISPLAYRESHEIGHT = 480;
    g_DISPLAYRESDEPTH = 8;
    BOOL windowCreated = windowCreate(hInstance, hPrevInstance);
    if (!windowCreated)
    {
        return 0;
    }

    ShowCursor(false);

    Script_ParseGameConfig();
    GetGameBuildVersion();

    // srand(time(NULL));

    static HINSTANCE uwu = hInstance;
    static HINSTANCE owo = hPrevInstance;

    static int mode_current = 2;
    do
    {
        BOOL availableMessage = PeekMessageA(&uMsg, NULL, 0, 0, PM_REMOVE);
        if (!availableMessage)
        {
            FUN_44e9d0();
            if ((false) && (false))
            {
                // TODO: replace with switch?
                if (mode_current == 1)
                {
                    OutputDebugString("Game logic");
                    printf("game logic");
                }
                else if (mode_current == 2)
                {
                    OutputDebugString("Frontend logic");
                    printf("Frontend logic");
                }
                // thunk
            }
        }
        else
        {
            if (uMsg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&uMsg);
            DispatchMessage(&uMsg);
        }

    } while (!SHOULD_STOP);

    DestroyWindow(NULL);
    // shutdowny();
    // fuckery();

    FUN_44ea50();
    return uMsg.wParam;
}
