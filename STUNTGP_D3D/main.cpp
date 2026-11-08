#define WIN32_LEAN_AND_MEAN

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ddraw.h>
#include <windows.h>

#include "Game/GameEngine/Engine_LevelScript.h"
#include "Game/GameEngine/Game.h"
#include "Game/GameEngine/MenuUpdate.h"
#include "windowInit.h"

#include "globals.h"
#include "surface.h"

// GLOBAL: STUNTGP_D3D 0x57b420
int g_57b420;

// GLOBAL: STUNTGP_D3D 0x57b424
char g_57b424[0x2ee0];

// GLOBAL: STUNTGP_D3D 0x57e304
char *g_57e304;

// GLOBAL: STUNTGP_D3D 0x57e308
int g_57e308;

// GLOBAL: STUNTGP_D3D 0x57eb08
char *g_57eb08;

// GLOBAL: STUNTGP_D3D 0x580af0
char g_580af0[0x1c20];

// GLOBAL: STUNTGP_D3D 0x589600
int g_589600;
#include "d3drender.h"
#include "font.h"
#include "sprite.h"

#include "common.h"
#include "Game/GameEngine/RenderState.h"
// #include "pure.h"

struct Unk61c208
{
    int unk00;
    int unk04;
    MenuCarEntry car; // 0x08
};

// GLOBAL: STUNTGP_D3D 0x61c208
Unk61c208 g_61c208[6];

// GLOBAL: STUNTGP_D3D 0x61c2c8
int g_61c2c8;

int FUN_437230(int car, int mode);

// FUNCTION: STUNTGP_D3D 0x44d420
void FUN_44d420()
{
    int cars[64];
    int count = 0;
    for (int i = 1; i < 21; i++)
    {
        if (FUN_437230(i, g_menuState.unk4230) || g_menuState.unk0074)
        {
            cars[count++] = i;
        }
    }
    for (int j = 0; j < g_menuState.unk423c; j++)
    {
        g_menuState.unk43f4[j] = cars[(rand() & 0xff) % count];
    }
}

// FUNCTION: STUNTGP_D3D 0x44d4a0
void FUN_44d4a0()
{
    g_menuState.unk4474 = g_menuState.unk440c[(rand() & 0xff) % g_menuState.unk4408];
}

// FUNCTION: STUNTGP_D3D 0x44e2b0
void FUN_44e2b0()
{
    int cars[64];
    int count = 0;
    for (int i = 1; i < 21; i++)
    {
        if (FUN_437230(i, g_menuState.unk4230) || g_menuState.unk0074)
        {
            cars[count++] = i;
        }
    }
    for (int j = 0; j < g_menuState.unk423c; j++)
    {
        g_menuState.unk43f4[j] = cars[(rand() & 0xff) % count];
    }
}

// FUNCTION: STUNTGP_D3D 0x44e330
void FUN_44e330()
{
    g_menuState.unk4474 = g_menuState.unk440c[(rand() & 0xff) % g_menuState.unk4408];
}

int FUN_44e430();

// Fills the remaining opponent slots with random cars from the current difficulty's table.
// FUNCTION: STUNTGP_D3D 0x44e350
void FUN_44e350()
{
    int level = g_menuState.unk00e4 - 1;
    if (level >= 0)
    {
        for (int n = g_61c2c8; n < 6; n = ++g_61c2c8)
        {
            int pick = (rand() >> 8) & 3;
            g_61c208[n].unk00 = 0;
            g_61c208[n].unk04 = FUN_44e430();
            strcpy(g_61c208[n].car.name, g_menuState.unk1d888[level][pick].name);
            g_61c208[n].car.unk08 = g_menuState.unk1d888[level][pick].unk08;
            g_61c208[n].car.unk0c = g_menuState.unk1d888[level][pick].unk0c;
            g_61c208[n].car.unk10 = g_menuState.unk1d888[level][pick].unk10;
            g_61c208[n].car.unk14 = g_menuState.unk1d888[level][pick].unk14;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x44e430
int FUN_44e430()
{
    int used[7];
    memset(used, 0, sizeof(used));
    for (int i = 0; i < g_61c2c8; i++)
    {
        int slot = g_61c208[i].unk04;
        if (slot > 0 && slot < 7)
        {
            used[slot] = 1;
        }
    }
    for (int j = 1; j < 7; j++)
    {
        if (!used[j])
        {
            return j;
        }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x44e490
void FUN_44e490()
{
    g_612948.unk004c = 0;
}

void FUN_44ea10();

// GLOBAL: STUNTGP_D3D 0x6087a8
int g_6087a8[0x25];

// GLOBAL: STUNTGP_D3D 0x60883c
int g_60883c[0x12d];

// GLOBAL: STUNTGP_D3D 0x608cf0
int g_608cf0[0x25];

// FUNCTION: STUNTGP_D3D 0x4411c0
void FUN_4411c0()
{
    int i;
    for (i = 0; i < 0x25; i++)
    {
        g_6087a8[i] = -1;
    }
    for (i = 0; i < 0x12d; i++)
    {
        g_60883c[i] = -1;
    }
    for (i = 0; i < 0x25; i++)
    {
        g_608cf0[i] = 0x10000;
    }
}

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
        FUN_4411c0();
        g_renderState.unk800c = 0;
        FUN_4320c0(1.0f);
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

// FUNCTION: STUNTGP_D3D 0x44e600
void FUN_44e600(float *value)
{
    *value *= g_61c36c;
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
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MOVE:
    case WM_SIZE:
        if (IsIconic(hWnd))
        {
            FUN_44e4b0(1);
        }
        break;
    case WM_ACTIVATEAPP:
        g_61c374 = wParam;
        if (wParam && g_WindowMessage == 1)
        {
            FUN_44e4b0(0);
        }
        break;
    case WM_CHAR:
        if (!g_62ddfc)
        {
            g_62ddfc = wParam;
        }
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// unused: STUNTGP_D3D 0x44e7a0

// Parses "-m<width>x<height>x<depth>" from the command line.
// FUNCTION: STUNTGP_D3D 0x44e7a0
void FUN_44e7a0(char *cmdLine)
{
    char *p = cmdLine;
    g_DISPLAYRESWIDTH = 640;
    g_DISPLAYRESHEIGHT = 480;
    g_DISPLAYRESDEPTH = 8;
    for (DWORD i = 0; i < strlen(cmdLine); i++)
    {
        if (*p++ == '-' && (*p == 'm' || *p == 'M'))
        {
            p++;
            g_DISPLAYRESWIDTH = strtol(p, &p, 10);
            p++;
            g_DISPLAYRESHEIGHT = strtol(p, &p, 10);
            p++;
            g_DISPLAYRESDEPTH = strtol(p, &p, 10);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x44e870
void m_keyboard()
{
    for (int i = 10; i != 0; i--)
    {
        GetKeyboardState(g_62d480);
    }
}

// FUNCTION: STUNTGP_D3D 0x44e890
BOOL windowCreate(HINSTANCE hInstance, HINSTANCE hPrevInstance, int nCmdShow, PSTR lpCmdLine)
{
    DWORD totalVideoMem;
    DWORD totalTextureMem;
    DWORD freeMem;

    g_hInstance = hInstance;
    g_61c384 = NULL;
    if (!hPrevInstance)
    {
        WNDCLASS windowInfo;
        windowInfo.style = CS_OWNDC;
        windowInfo.lpfnWndProc = WndProc;
        windowInfo.cbClsExtra = 0;
        windowInfo.cbWndExtra = 0;
        windowInfo.hInstance = hInstance;
        windowInfo.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
        windowInfo.hCursor = NULL;
        windowInfo.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
        // STRING: STUNTGP_D3D 0x486474
        windowInfo.lpszMenuName = "AppMenu";
        // STRING: STUNTGP_D3D 0x48647c
        windowInfo.lpszClassName = "Stunt GP";
        if (!RegisterClass(&windowInfo))
        {
            return FALSE;
        }
    }
    // STRING: STUNTGP_D3D 0x486494
    // STRING: STUNTGP_D3D 0x486488
    g_Hwnd = windowCreateInternal(hInstance, "Stunt GP", "Stunt GP");
    if (!g_Hwnd)
    {
        return FALSE;
    }

    windowDDCreate(&g_dd, NULL, g_Hwnd);
    ddGetDD4(&g_dd, &g_dd4, g_Hwnd);
    ddGetMemory(&g_dd4, &totalVideoMem, &totalTextureMem, &freeMem);
    FUN_4229e0();
    FUN_422f30(g_dd4, &g_surface, &g_surface2, 640, 480, 8);
    m_keyboard();
    return !FUN_4230b0(&g_61c384, (BYTE *)&g_571fd4);
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
    for (DWORD i = 0; i < g_5ba788.surfaceSlotCount; i++)
    {
        if (g_5ba788.surfaceSlots[i].surface && g_5ba788.surfaceSlots[i].surface->IsLost())
        {
            return FALSE;
        }
        if (g_5ba788.surfaceSlots[i].surface2 && g_5ba788.surfaceSlots[i].surface2->IsLost())
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
    for (DWORD i = 0; i < g_5ba788.surfaceSlotCount; i++)
    {
        if (g_5ba788.surfaceSlots[i].surface && g_5ba788.surfaceSlots[i].surface->Restore())
        {
            return FALSE;
        }
        if (g_5ba788.surfaceSlots[i].surface2 && g_5ba788.surfaceSlots[i].surface2->Restore())
        {
            return FALSE;
        }
    }
    return TRUE;
}

// Reloads every registered texture and font after the surfaces were restored.
// FUNCTION: STUNTGP_D3D 0x42bf00
void FUN_42bf00()
{
    int i;
    for (i = 0; g_textureFiles[i].name; i++)
    {
        FUN_4316f0(g_textureFiles[i].slot, g_textureFiles[i].name);
    }
    for (i = 0; g_fontFiles[i].name; i++)
    {
        Font_Select(i);
        Font_Load(g_fontFiles[i].name);
    }
}

int FUN_430730(int size, int unk);
extern int g_582718;
extern int g_582728[255];
extern int g_582724;
extern int g_58332c;
extern int g_58271c;
extern int g_583328;
extern int g_582b24;
extern char **g_582f24;
extern char **g_583324;
extern SpriteFile *g_58358c;

int FUN_42b9a0(const char *name);
int FUN_42bb70(char *path, char *out);
void FUN_42bcf0(char *suffix, char *path, int highDetail);
DWORD FUN_4306c0(int width, int height, DWORD count, int unk, char *path);
extern int g_583590;

// Registers the texture file path: loads it into the next texture slot when FUN_42b9a0 accepts
// it, and records the name in the lists at g_583324 and g_582f24.
// FUNCTION: STUNTGP_D3D 0x42bf60
void FUN_42bf60(char *path, int highDetail)
{
    char file[128];
    char name[128];
    sprintf(name, path);
    if (FUN_42b9a0(name))
    {
        FUN_42bb70(path, name);
        FUN_42bcf0(name, file, highDetail);
        g_renderState.unk7ed0->unk04[2] = 0;
        if ((DWORD)g_58271c < (DWORD)g_583590)
        {
            g_renderState.unk7ed0->unk04[4] = 0;
        }
        else
        {
            g_renderState.unk7ed0->unk04[4] = g_582718;
        }
        int n = FUN_4306c0(g_489714, g_489714, 0, 0, file);
        if (g_58332c == 1)
        {
            g_583328 += g_489718 * g_489714 * 2;
        }
        else
        {
            g_583328 += g_489718 * g_489714;
        }
        g_582728[g_582718] = g_582724 + g_582718;
        g_582718 += n;
        g_58271c += n;
        *g_583324++ = path;
        *g_583324 = NULL;
    }
    *g_582f24++ = path;
    *g_582f24 = NULL;
    g_582b24++;
}

// Registers a new empty texture of size code sizeCode (4..8 for 16..256 texels) and names it by
// its slot number.
// FUNCTION: STUNTGP_D3D 0x42c0a0
void FUN_42c0a0(int arg, int sizeCode)
{
    int size;
    switch (sizeCode)
    {
    case 4:
        size = 16;
        break;
    case 5:
        size = 32;
        break;
    case 6:
        size = 64;
        break;
    case 7:
        size = 128;
        break;
    case 8:
        size = 256;
        break;
    }
    g_renderState.unk7ed0->unk04[2] = 0;
    g_renderState.unk7ed0->unk04[4] = 0;
    int n = FUN_430730(size, arg);
    if (g_58332c == 1)
    {
        g_583328 += size * size * 2;
    }
    else
    {
        g_583328 += size * size;
    }
    g_582728[g_582718] = g_582724 + g_582718;
    g_582718 += n;
    g_58271c += n;
    // STRING: STUNTGP_D3D 0x4777e8
    sprintf((char *)g_58358c, "%d", g_582718);
    *g_583324++ = (char *)g_58358c;
    *g_583324 = NULL;
    *g_582f24++ = (char *)g_58358c;
    *g_582f24 = NULL;
    g_582b24++;
    g_58358c = (SpriteFile *)((char *)g_58358c + strlen((char *)g_58358c));
}

// FUNCTION: STUNTGP_D3D 0x42c1d0
void FUN_42c1d0()
{
    if (g_589600 != 1)
    {
        memset(g_57b424, 0, sizeof(g_57b424));
        memset(g_580af0, 0, sizeof(g_580af0));
        g_57eb08 = g_580af0;
        g_57e304 = g_57b424;
        g_589600 = 1;
    }
}

struct ImageCacheEntry
{
    int used;
    char *name;
    DWORD data[4];
};

void FUN_430ca0(char *name, int compressed, int type);

// Loads an image once; later loads of the same name reuse the cached table entry.
// FUNCTION: STUNTGP_D3D 0x42c220
int FUN_42c220(char *name, int compressed)
{
    ImageCacheEntry *e;
    for (e = (ImageCacheEntry *)g_580af0; e->used; e++)
    {
        if (!_strcmpi(name, e->name))
        {
            *(ImageCacheEntry *)g_5895b0.entryCursor = *e;
            g_5895b0.entryCursor += 6;
            return 1;
        }
    }
    FUN_430ca0(name, compressed, 1);
    *(ImageCacheEntry *)g_57eb08 = *(ImageCacheEntry *)(g_5895b0.entryCursor - 6);
    // STRING: STUNTGP_D3D 0x4777ec
    sprintf(g_57e304, "%s", name);
    ((ImageCacheEntry *)g_57eb08)->used = 1;
    ((ImageCacheEntry *)g_57eb08)->name = g_57e304;
    g_57eb08 += sizeof(ImageCacheEntry);
    g_57e304 += strlen(name) + 1;
    return 1;
}

SpriteFile *FUN_441180();

// FUNCTION: STUNTGP_D3D 0x42c2e0
int FUN_42c2e0(const char *name)
{
    SpriteFile *f;
    for (f = FUN_441180(); f->name; f++)
    {
        if (!_strcmpi(f->name, name))
        {
            if (!g_57b420)
            {
                g_57e308 = g_5895b0.totalSize;
                g_57b420 = 1;
            }
            return 1;
        }
    }
    return 0;
}

void FUN_431810();
void FUN_42bc00();
extern int g_583594[255];
extern char *g_582b28[255];
extern char **g_582f24;
extern char *g_582f28[255];
extern char **g_583324;
extern SpriteFile g_583334[50];
extern SpriteFile *g_58358c;
extern int g_583328;
extern int g_582b24;
extern int g_58271c;
extern int g_582720;

void FUN_42c0a0(int arg, int sizeCode);
extern int g_587990;

// Loads a NULL-terminated texture list, recording each image's table index in g_583594.
// FUNCTION: STUNTGP_D3D 0x42c340
void FUN_42c340(TextureEntry *list)
{
    int empty = 0;
    for (TextureEntry *e = list; e->name; e++)
    {
        if (e->type == 2 || e->type == 0 || e->type == 3)
        {
            empty++;
        }
    }
    g_583590 = empty;
    g_582724 = g_582b24;
    g_582718 = 0;
    int *slot = g_583594;
    for (; list->name; list++, slot++)
    {
        if (list->type == 1)
        {
            if (g_612948.unk02a0 == 2 && FUN_42c2e0(list->name) != 1)
            {
                FUN_42c220(list->name, list->arg);
            }
            else
            {
                FUN_430ca0(list->name, list->arg, 0);
            }
            *slot = ((int)g_5895b0.entryCursor - (int)&g_587990) / 0x18 - 1;
        }
        else if (list->type == 2 || list->type == 3)
        {
            FUN_42c0a0(list->type, list->arg);
        }
        else if (g_612948.unk02a0 == 2)
        {
            FUN_42bf60(list->name, 0);
        }
        else
        {
            FUN_42bf60(list->name, 1);
        }
    }
}

extern int g_6249a0;

// Registers a NULL-terminated list of texture files.
// FUNCTION: STUNTGP_D3D 0x42c440
void FUN_42c440(char **names)
{
    g_582718 = 0;
    g_582724 = g_582b24;
    for (int i = 0; names[i]; i++)
    {
        FUN_42bf60(names[i], g_6249a0);
    }
}

// Clears the texture, sprite and file registries.
// FUNCTION: STUNTGP_D3D 0x42c480
void FUN_42c480()
{
    FUN_431810();
    FUN_42c1d0();
    memset(g_583594, 0xff, sizeof(g_583594));
    memset(g_582b28, 0, sizeof(g_582b28));
    memset(g_renderState.unk62ec, 0, 255 * sizeof(TextureSlot));
    g_renderState.unk7ed0 = g_renderState.unk62ec;
    g_renderState.unk2e0 = g_renderState.unk120;
    g_582f24 = g_582b28;
    g_583324 = g_582f28;
    g_58358c = g_583334;
    FUN_42bc00();
    g_583328 = 0;
    g_582b24 = 0;
    g_58271c = 0;
    g_582720 = 0;
    g_57b420 = 0;
    g_57e308 = 0;
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
    if (!windowCreate(hInstance, hPrevInstance, nCmdShow, lpCmdLine))
    {
        return FALSE;
    }

    g_612948.unk02a0 = 2;
    g_612948.unk02a4 = 2;
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
                if (g_612948.unk02a0 == 1)
                {
                    FUN_442810();
                    FUN_4427b0();
                }
                else if (g_612948.unk02a0 == 2)
                {
                    FUN_441f00();
                    FUN_441d70();
                }
                thunk_FUN_44e6b0();
            }
        }
    } while (g_612948.unk0000 != 1);

    FUN_44e6c0();
    FUN_442180();
    FUN_44ea50();
    return uMsg.wParam;
}
