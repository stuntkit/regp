#define WIN32_LEAN_AND_MEAN

#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <windows.h>

#include "uwu.h"

// TODO: move this where it is needed, global stuff
// 0-1
// GLOBAL: STUNTGP_D3D 0x612994
BOOL g_sth = 0;

// FUNCTION: STUNTGP_D3D 0x44e490
void FUN_44e490()
{
    g_sth = 0;
}

// FUNCTION: STUNTGP_D3D 0x44e4a0
void exitError()
{
    exit(1);
}

// fastcall
// STUB: STUNTGP_D3D 0x44e4b0
void FUN_0044e4b0(int windowMessage)
{
    if (windowMessage)
    {
        if (false)
        {
        }
    }
    else
    {
    }
}

// STUB: STUNTGP_D3D 0x44e5d0
void FUN_0044e5d0()
{
    GetTickCount();
}

// STUB: STUNTGP_D3D 0x44e610
void FUN_44e610()
{
    GetTickCount();
}

// thunk
// STUB: STUNTGP_D3D 0x44e6b0
void thunk_FUN_44e6b0()
{
    FUN_44e610();
}

// STUB: STUNTGP_D3D 0x44e6c0
void FUN_44e6c0()
{
    GetTickCount();
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
    int windowMessage;
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
            // TODO: not true, DAT_0062ddfc == '\0'
            if ((uMsg == WM_CHAR) && (true))
            {
                // TODO: save wparam to static
                return DefWindowProc(hWnd, WM_CHAR, wParam, lParam);
            }
        }
        // TODO wparam blah
        if ((wParam == 0) || (true))
        {
            goto exit;
        }
        windowMessage = 0;
    }
    FUN_0044e4b0(windowMessage);
exit:
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// STUB: STUNTGP_D3D 0x44e7a0

// STUB: STUNTGP_D3D 0x44e870

// FUNCTION: STUNTGP_D3D 0x44e890
BOOL windowCreate(HINSTANCE hInstance, HINSTANCE hPrevInstance)
{
    WNDCLASS windowInfo;

    // TOIDO: global?
    static HINSTANCE g_HINSTANCE = hInstance;

    const char menuName[] = "AppMenu";
    const char className[] = "Stunt GP";
    if (!hPrevInstance)
    {
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
        ATOM registered = RegisterClass(&windowInfo);
        if (!registered)
        {
            return FALSE;
        }
    }
    HWND wHandle = windowCreateInternal(hInstance, "Stunt GP", "Stunt GP");
    if (!wHandle)
    {
        return FALSE;
    }

    //  ???
    return FALSE;
}

// FUNCTION: STUNTGP_D3D 0x44e9b0
// FUNCTION: STUNTGP_D3D 0x44e9c0

// STUB: STUNTGP_D3D 0x44e9d0
void loopy()
{
    return;
}

// FUNCTION: STUNTGP_D3D 0x44ea10

// FUNCTION: STUNTGP_D3D 0x44ea50
void FUN_0044ea50()
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
            loopy();
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

    FUN_0044ea50();
    return uMsg.wParam;
}
