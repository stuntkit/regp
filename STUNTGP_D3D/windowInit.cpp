#include "windowInit.h"
#include "Game/GameEngine/RenderState.h"

// LIBRARY: STUNTGP_D3D 0x4627a4
// _DirectDrawCreate@12

// GLOBAL: STUNTGP_D3D 0x46ecb0
// IID_IDirectDraw4

// LIBRARY: STUNTGP_D3D 0x4627aa
// _DirectDrawEnumerateExA@12

// GLOBAL: STUNTGP_D3D 0x46ed90
// IID_IDirectDrawGammaControl

// TODO: should we set this as a struct???
// GLOBAL: STUNTGP_D3D 0x4754d0
errorMessage errorMessages[] = {
    {"No Error", DD_OK},
    {" This object is already initialised", DDERR_ALREADYINITIALIZED},
    {" This surface can not be attached to the requested surface.", DDERR_CANNOTATTACHSURFACE},
    {" This surface can not be detached from the requested surface.", DDERR_CANNOTDETACHSURFACE},
    {" Support is currently not available.", DDERR_CURRENTLYNOTAVAIL},
    {" An exception was encountered while performing the requested operation", DDERR_EXCEPTION},
    {"Generic failure.", DDERR_GENERIC},
    {" Height of rectangle provided is not a multiple of reqd alignment", DDERR_HEIGHTALIGN},
    {" Unable to match primary surface creation request with existing primary surface.", DDERR_INCOMPATIBLEPRIMARY},
    {" One or more of the caps bits passed to the callback are incorrect.", DDERR_INVALIDCAPS},
    {" DirectDraw does not support provided Cliplist.", DDERR_INVALIDCLIPLIST},
    {" DirectDraw does not support the requested mode", DDERR_INVALIDMODE},
    {" DirectDraw received a pointer that was an invalid DIRECTDRAW object.", DDERR_INVALIDOBJECT},
    {"One or more of the parameters passed to the callback function are incorrect.", DDERR_INVALIDPARAMS},
    {" pixel format was invalid as specified", DDERR_INVALIDPIXELFORMAT},
    {" Rectangle provided was invalid.", DDERR_INVALIDRECT},
    {" Operation could not be carried out because one or more surfaces are locked", DDERR_LOCKEDSURFACES},
    {" There is no 3D present.", DDERR_NO3D},
    {" Operation could not be carried out because there is no alpha accleration hardware present or available.",
     DDERR_NOALPHAHW},
    {" no clip list available", DDERR_NOCLIPLIST},
    {" Operation could not be carried out because there is no color conversion hardware present or available.",
     DDERR_NOCOLORCONVHW},
    {" Create function called without DirectDraw object method SetCooperativeLevel being called.",
     DDERR_NOCOOPERATIVELEVELSET},
    {" Surface doesn't currently have a color key", DDERR_NOCOLORKEY},
    {" Operation could not be carried out because there is no hardware support of the dest color key.",
     DDERR_NOCOLORKEYHW},
    {" No DirectDraw support possible with current display driver", DDERR_NODIRECTDRAWSUPPORT},
    {" Operation requires the application to have exclusive mode but the application does not have exclusive mode.",
     DDERR_NOEXCLUSIVEMODE},
    {" Flipping visible surfaces is not supported.", DDERR_NOFLIPHW},
    {" There is no GDI present.", DDERR_NOGDI},
    {" Operation could not be carried out because there is no hardware present or available.", DDERR_NOMIRRORHW},
    {" Requested item was not found", DDERR_NOTFOUND},
    {" Operation could not be carried out because there is no overlay hardware present or available.",
     DDERR_NOOVERLAYHW},
    {" Operation could not be carried out because there is no appropriate raster op hardware present or available.",
     DDERR_NORASTEROPHW},
    {" Operation could not be carried out because there is no rotation hardware present or available.",
     DDERR_NOROTATIONHW},
    {" Operation could not be carried out because there is no hardware support for stretching", DDERR_NOSTRETCHHW},
    {" DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette.",
     DDERR_NOT4BITCOLOR},
    {" DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index "
     "palette.",
     DDERR_NOT4BITCOLORINDEX},
    {" DirectDraw Surface is not in 8 bit color mode and the requested operation requires 8 bit color.",
     DDERR_NOT8BITCOLOR},
    {" Operation could not be carried out because there is no texture mapping hardware present or available.",
     DDERR_NOTEXTUREHW},
    {" Operation could not be carried out because there is no hardware support for vertical blank synchronized "
     "operations.",
     DDERR_NOVSYNCHW},
    {" Operation could not be carried out because there is no hardware support for zbuffer blting.", DDERR_NOZBUFFERHW},
    {" Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z "
     "layering of overlays.",
     DDERR_NOZOVERLAYHW},
    {" The hardware needed for the requested operation has already been allocated.", DDERR_OUTOFCAPS},
    {"DirectDraw does not have enough memory to perform the operation.", DDERR_OUTOFMEMORY},
    {" DirectDraw does not have enough memory to perform the operation.", DDERR_OUTOFVIDEOMEMORY},
    {" hardware does not support clipped overlays", DDERR_OVERLAYCANTCLIP},
    {" Can only have ony color key active at one time for overlays", DDERR_OVERLAYCOLORKEYONLYONEACTIVE},
    {" Access to this palette is being refused because the palette is already locked by another thread.",
     DDERR_PALETTEBUSY},
    {" No src color key specified for this operation.", DDERR_COLORKEYNOTSET},
    {" This surface is already attached to the surface it is being attached to.", DDERR_SURFACEALREADYATTACHED},
    {" This surface is already a dependency of the surface it is being made a dependency of.",
     DDERR_SURFACEALREADYDEPENDENT},
    {" Access to this surface is being refused because the surface is already locked by another thread.",
     DDERR_SURFACEBUSY},
    {"Access to this surface is being refused because no driver existswhich can supply a pointer to the surface.This "
     "is most likely to happen when attempting to lock the primarysurface when no DCI provider is present.",
     DDERR_CANTLOCKSURFACE},
    {" Access to Surface refused because Surface is obscured.", DDERR_SURFACEISOBSCURED},
    {" Access to this surface is being refused because the surface is gone.The DIRECTDRAWSURFACE object representing "
     "this surface should have Restore called on it.",
     DDERR_SURFACELOST},
    {" The requested surface is not attached.", DDERR_SURFACENOTATTACHED},
    {" Height requested by DirectDraw is too large.", DDERR_TOOBIGHEIGHT},
    {" Size requested by DirectDraw is too large --  The individual height and width are OK.", DDERR_TOOBIGSIZE},
    {" Width requested by DirectDraw is too large.", DDERR_TOOBIGWIDTH},
    {"Action not supported.", DDERR_UNSUPPORTED},
    {" FOURCC format requested is unsupported by DirectDraw", DDERR_UNSUPPORTEDFORMAT},
    {" Bitmask in the pixel format requested is unsupported by DirectDraw", DDERR_UNSUPPORTEDMASK},
    {" vertical blank is in progress", DDERR_VERTICALBLANKINPROGRESS},
    {" Informs DirectDraw that the previous Blt which is transfering information to or from this Surface is "
     "incomplete.",
     DDERR_WASSTILLDRAWING},
    {" Rectangle provided was not horizontally aligned on reqd. boundary", DDERR_XALIGN},
    {" The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.", DDERR_INVALIDDIRECTDRAWGUID},
    {" A DirectDraw object representing this driver has already been created for this process.",
     DDERR_DIRECTDRAWALREADYCREATED},
    {" A hardware only DirectDraw object creation was attempted but the driver did not support any hardware.",
     DDERR_NODIRECTDRAWHW},
    {" this process already has created a primary surface", DDERR_PRIMARYSURFACEALREADYEXISTS},
    {" software emulation not available.", DDERR_NOEMULATION},
    {" region passed to Clipper::GetClipList is too small.", DDERR_REGIONTOOSMALL},
    {" an attempt was made to set a clip list for a clipper objec that is already monitoring an hwnd.",
     DDERR_CLIPPERISUSINGHWND},
    {" No clipper object attached to surface object", DDERR_NOCLIPPERATTACHED},
    {" Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.",
     DDERR_NOHWND},
    {" HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state.",
     DDERR_HWNDSUBCLASSED},
    {" The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes "
     "created.",
     DDERR_HWNDALREADYSET},
    {" No palette object attached to this surface.", DDERR_NOPALETTEATTACHED},
    {" No hardware support for 16 or 256 color palettes.", DDERR_NOPALETTEHW},
    {" If a clipper object is attached to the source surface passed into a BltFast call.", DDERR_BLTFASTCANTCLIP},
    {" No blter.", DDERR_NOBLTHW},
    {" No DirectDraw ROP hardware.", DDERR_NODDROPSHW},
    {" returned when GetOverlayPosition is called on a hidden overlay", DDERR_OVERLAYNOTVISIBLE},
    {" returned when GetOverlayPosition is called on a overlay that UpdateOverlay has never been called on to "
     "establish a destionation.",
     DDERR_NOOVERLAYDEST},
    {" returned when the position of the overlay on the destionation is no Sint32er legal for that destionation.",
     DDERR_INVALIDPOSITION},
    {" returned when an overlay member is called for a non-overlay surface", DDERR_NOTAOVERLAYSURFACE},
    {" An attempt was made to set the cooperative level when it was already set to exclusive.",
     DDERR_EXCLUSIVEMODEALREADYSET},
    {" An attempt has been made to flip a surface that is not flippable.", DDERR_NOTFLIPPABLE},
    {" Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.", DDERR_CANTDUPLICATE},
    {" Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has "
     "been attempted.",
     DDERR_NOTLOCKED},
    {" Windows can not create any more DCs", DDERR_CANTCREATEDC},
    {" No DC was ever created for this surface.", DDERR_NODC},
    {" This surface can not be restored because it was created in a different mode.", DDERR_WRONGMODE},
    {" This surface can not be restored because it is an implicitly created surface.", DDERR_IMPLICITLYCREATED},
    {" The surface being used is not a palette-based surface", DDERR_NOTPALETTIZED},
    {" The display is currently in an unsupported mode", DDERR_UNSUPPORTEDMODE},
    {" Operation could not be carried out because there is no mip-map texture mapping hardware present or available.",
     DDERR_NOMIPMAPHW},
    {" The requested action could not be performed because the surface was of the wrong type.",
     DDERR_INVALIDSURFACETYPE},
    {" A DC has already been returned for this surface. Only one DC can be retrieved per surface.",
     DDERR_DCALREADYCREATED},
    {" The attempt to page lock a surface failed.", DDERR_CANTPAGELOCK},
    {" The attempt to page unlock a surface failed.", DDERR_CANTPAGEUNLOCK},
    {" An attempt was made to page unlock a surface with no outstanding page locks.", DDERR_NOTPAGELOCKED},
    {" An attempt was made to invoke an interface member of a DirectDraw object created by CoCreateInstance(), before "
     "it was initialized.",
     DDERR_NOTINITIALIZED},
    {NULL, NULL}};

// GLOBAL: STUNTGP_D3D 0x5728dc
int DAT_CAPS = 0;

// FUNCTION: STUNTGP_D3D 0x422700
HWND windowCreateInternal(HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName)
{
    HWND wHandle = CreateWindowEx(WS_EX_APPWINDOW, className, windowName, WS_POPUP, 0, 0,
                                  GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), NULL, NULL,
                                  hInstance, NULL);
    if (!wHandle)
    {
        return NULL;
    }
    ShowWindow(wHandle, SW_NORMAL);
    UpdateWindow(wHandle);
    return wHandle;
}

// GLOBAL: STUNTGP_D3D 0x572ae4
char g_ddErrorText[256];

// FUNCTION: STUNTGP_D3D 0x422690
const char *ddGetErrMessage(int res)
{
    for (int i = 0; errorMessages[i].message != NULL; i++)
    {
        if (errorMessages[i].code == res)
        {
            // STRING: STUNTGP_D3D 0x477570
            sprintf(g_ddErrorText, "%s\n", errorMessages[i].message);
            return g_ddErrorText;
        }
    }
    // STRING: STUNTGP_D3D 0x477574
    sprintf(g_ddErrorText, "No Text For Error : %.8x\n", res);
    return g_ddErrorText;
}

// FUNCTION: STUNTGP_D3D 0x422780
int ddSetCoopLevel(LPDIRECTDRAW *lplpDD, HWND hWnd)
{
    int res = (*lplpDD)->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    return res;
}

// FUNCTION: STUNTGP_D3D 0x4227b0
int dd4SetCoopLevel(LPDIRECTDRAW4 *lplpDD4, HWND hWnd)
{
    int res = (*lplpDD4)->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    return res;
}

// FUNCTION: STUNTGP_D3D 0x4227e0
int windowDDCreate(LPDIRECTDRAW *lplpDD, GUID *lpGUID, HWND hWnd)
{
    int res = DirectDrawCreate(lpGUID, lplpDD, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    ddSetCoopLevel(lplpDD, hWnd);
    return res;
}

// FUNCTION: STUNTGP_D3D 0x422820
int ddGetDD4(LPDIRECTDRAW *lplpDD, LPDIRECTDRAW4 *lplpDD4, HWND hWnd)
{
    int res = (*lplpDD)->QueryInterface(IID_IDirectDraw4, (LPVOID *)lplpDD4);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    dd4SetCoopLevel(lplpDD4, hWnd);
    return res;
}

// FUNCTION: STUNTGP_D3D 0x422860
void FUN_422860(IUnknown **object)
{
    if (*object)
    {
        (*object)->Release();
        *object = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x422880
void ddReleaseSurface(LPDIRECTDRAWSURFACE4 *surface)
{
    if (*surface)
    {
        (*surface)->Release();
        *surface = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x4228a0
void ddReleaseDD(LPDIRECTDRAW *lplpDD)
{
    if (*lplpDD)
    {
        (*lplpDD)->Release();
        *lplpDD = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x4228c0
void ddReleaseDD4(LPDIRECTDRAW4 *lplpDD4)
{
    if (*lplpDD4)
    {
        (*lplpDD4)->Release();
        *lplpDD4 = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x4228e0
void ddRelease()
{
    ddReleaseDD(&g_dd);
    ddReleaseDD4(&g_dd4);
    g_61c358 = NULL;
    g_surface = NULL;
    g_surface2 = NULL;
}

// FUNCTION: STUNTGP_D3D 0x422910
void FUN_422910(IUnknown **object)
{
    if (*object)
    {
        (*object)->Release();
        *object = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x422930
void windowDestroy(HWND *hWnd)
{
    if (hWnd)
    {
        DestroyWindow(*hWnd);
        *hWnd = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x422950
int ddGetMemory(LPDIRECTDRAW4 *lplpDD4, LPDWORD totalVideoMem, LPDWORD totalTextureMem, LPDWORD freeVideoMem)
{
    DWORD dwTotal;
    DWORD dwFree;
    DDSCAPS2 caps;

    // The original ignores lplpDD4 and reads the global directly.
    ZeroMemory(&caps, sizeof(caps));
    caps.dwCaps = DDSCAPS_VIDEOMEMORY;
    int res = g_dd4->GetAvailableVidMem(&caps, &dwTotal, &dwFree);
    if (res != DD_OK)
    {
        return res;
    }
    *totalVideoMem = dwTotal;
    *freeVideoMem = dwFree;

    ZeroMemory(&caps, sizeof(caps));
    caps.dwCaps = DDSCAPS_TEXTURE;
    res = g_dd4->GetAvailableVidMem(&caps, &dwTotal, &dwFree);
    if (res != DD_OK)
    {
        return res;
    }
    *totalTextureMem = dwTotal;
    return DD_OK;
}

// MSVC lays out this file's uninitialised globals in symbol hash order, not definition order.
// These names keep g_trackedSurfaces directly after g_paletteEntries, which FUN_423070's loop bound relies on.
// GLOBAL: STUNTGP_D3D 0x5723d4
PALETTEENTRY g_paletteEntries[256];

// Every surface created through FUN_422a80, released in bulk by FUN_422a20.
// GLOBAL: STUNTGP_D3D 0x5727d4
LPDIRECTDRAWSURFACE4 g_trackedSurfaces[64];

// GLOBAL: STUNTGP_D3D 0x5728d4
DWORD g_surfaceCount;

// FUNCTION: STUNTGP_D3D 0x4229e0
void FUN_4229e0()
{
    memset(g_trackedSurfaces, 0, sizeof(g_trackedSurfaces));
    g_surfaceCount = 0;
}

// FUNCTION: STUNTGP_D3D 0x422a00
void FUN_422a00(LPDIRECTDRAWSURFACE4 *surface)
{
    g_trackedSurfaces[g_surfaceCount++] = *surface;
}

// FUNCTION: STUNTGP_D3D 0x422a20
void FUN_422a20()
{
    for (DWORD i = 0; i < g_surfaceCount; i++)
    {
        if (g_trackedSurfaces[i])
        {
            g_trackedSurfaces[i]->Release();
            g_trackedSurfaces[i] = NULL;
        }
    }
    FUN_4229e0();
}

// FUNCTION: STUNTGP_D3D 0x422a60
void FUN_422a60()
{
    if (g_dd)
    {
        FUN_422a20();
        ddRelease();
        windowDestroy(&g_Hwnd);
    }
}

// FUNCTION: STUNTGP_D3D 0x422a80
int FUN_422a80(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDDSURFACEDESC2 desc, int fatal)
{
    int res = dd->CreateSurface(desc, surface, NULL);
    if (res == DD_OK)
    {
        FUN_422a00(surface);
    }
    else if (fatal == 1)
    {
        exit(1);
    }
    return res;
}

// FUNCTION: STUNTGP_D3D 0x422ac0
int FUN_422ac0(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, int width, int height, DWORD memCaps)
{
    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwWidth = width;
    ddsd.dwHeight = height;
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DAT_CAPS | memCaps | DDSCAPS_OFFSCREENPLAIN;

    int res;
    if (memCaps != DDSCAPS_VIDEOMEMORY || (res = FUN_422a80(dd, surface, &ddsd, 2)) != DD_OK)
    {
        ddsd.ddsCaps.dwCaps = (ddsd.ddsCaps.dwCaps & ~DDSCAPS_VIDEOMEMORY) | DDSCAPS_SYSTEMMEMORY;
        res = FUN_422a80(dd, surface, &ddsd, 2);
    }
    return res;
}

// FUNCTION: STUNTGP_D3D 0x422b50
void *FUN_422b50(LPDIRECTDRAWSURFACE4 surface)
{
    DDSURFACEDESC2 ddsd;
    ddsd.dwSize = sizeof(ddsd);
    if (surface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) != DD_OK &&
        surface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) != DD_OK)
    {
        return NULL;
    }
    return ddsd.lpSurface;
}

// FUNCTION: STUNTGP_D3D 0x422ba0
void FUN_422ba0(LPDIRECTDRAWSURFACE4 surface)
{
    surface->Unlock(NULL);
}

// FUNCTION: STUNTGP_D3D 0x422bb0
void FUN_422bb0(DWORD mask, int *bits, int *shift)
{
    int count = 0;
    int first = -1;
    for (int i = 0; i < 16; i++)
    {
        int bit = mask & 1;
        if (first < 0 && bit)
        {
            first = i;
        }
        if (bit)
        {
            count++;
        }
        mask >>= 1;
    }
    *bits = count;
    *shift = first;
}

// FUNCTION: STUNTGP_D3D 0x422bf0
void FUN_422bf0()
{
    DDPIXELFORMAT pf;
    pf.dwSize = sizeof(pf);
    g_surface2->GetPixelFormat(&pf);
    if ((pf.dwFlags & DDPF_RGB) && pf.dwRGBBitCount == 16)
    {
        FUN_422bb0(pf.dwRBitMask, &g_DD_RBITS, &g_DD_RSHIFT);
        FUN_422bb0(pf.dwGBitMask, &g_DD_GBITS, &g_DD_GSHIFT);
        FUN_422bb0(pf.dwBBitMask, &g_DD_BBITS, &g_DD_BSHIFT);
    }
}

// Fallback when the requested mode can't be set: 640x480 primary plus an offscreen back buffer.
// FUNCTION: STUNTGP_D3D 0x422c60
int FUN_422c60(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDIRECTDRAWSURFACE4 *surface2, int width, int height,
               int depth)
{
    if (dd->SetDisplayMode(640, 480, depth, 0, 0) != DD_OK)
    {
        return -1;
    }

    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.ddsCaps.dwCaps = DAT_CAPS | DDSCAPS_VIDEOMEMORY | DDSCAPS_PRIMARYSURFACE;
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    if (FUN_422a80(dd, surface, &ddsd, 2) != DD_OK)
    {
        return -1;
    }

    int res = FUN_422ac0(dd, surface2, 640, 480, DDSCAPS_VIDEOMEMORY);
    if (res != DD_OK)
    {
        res = FUN_422ac0(dd, surface2, 640, 480, DDSCAPS_SYSTEMMEMORY);
        if (res != DD_OK)
        {
            exitError(ddGetErrMessage(res));
        }
    }
    g_61c358 = surface2;
    g_005728d8_dd = 4;
    return res;
}

// FUNCTION: STUNTGP_D3D 0x422d50
int FUN_422d50(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDIRECTDRAWSURFACE4 *surface2, int width, int height)
{
    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DAT_CAPS | DDSCAPS_VIDEOMEMORY | DDSCAPS_PRIMARYSURFACE;
    if (FUN_422a80(dd, surface, &ddsd, 1) != DD_OK)
    {
        return -1;
    }

    int res = FUN_422ac0(dd, surface2, width, height, DDSCAPS_SYSTEMMEMORY);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    g_61c358 = surface2;
    g_005728d8_dd = 1;
    return res;
}

// FUNCTION: STUNTGP_D3D 0x422df0
int FUN_422df0(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDIRECTDRAWSURFACE4 *surface2, int width, int height)
{
    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwBackBufferCount = 1;
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DAT_CAPS | DDSCAPS_VIDEOMEMORY | DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    FUN_422a80(dd, surface, &ddsd, 2);

    DDSCAPS2 caps;
    ZeroMemory(&caps, sizeof(caps));
    caps.dwCaps = DDSCAPS_BACKBUFFER;
    int res = (*surface)->GetAttachedSurface(&caps, surface2);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    g_61c358 = surface2;
    g_005728d8_dd = 2;
    return res;
}

// FUNCTION: STUNTGP_D3D 0x422ea0
int FUN_422ea0(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDIRECTDRAWSURFACE4 *surface2, int width, int height)
{
    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.dwBackBufferCount = 1;
    ddsd.ddsCaps.dwCaps = DAT_CAPS | DDSCAPS_SYSTEMMEMORY | DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    FUN_422a80(dd, surface, &ddsd, 2);

    DDSCAPS2 caps;
    caps.dwCaps = DDSCAPS_BACKBUFFER;
    int res = (*surface)->GetAttachedSurface(&caps, surface2);
    g_61c358 = surface2;
    g_005728d8_dd = 3;
    return res;
}

// FUNCTION: STUNTGP_D3D 0x422f30
int FUN_422f30(LPDIRECTDRAW4 dd, LPDIRECTDRAWSURFACE4 *surface, LPDIRECTDRAWSURFACE4 *surface2, int width, int height,
               int depth)
{
    if (g_DD_DISPLAYRESWIDTH == width && g_DD_DISPLAYRESHEIGHT == height && g_DD_DISPLAYRESDEPTH == depth)
    {
        return DD_OK;
    }

    g_005728d8_dd = 0;
    int res = dd->SetDisplayMode(width, height, depth, 0, 0);
    if (res != DD_OK)
    {
        if (g_005728d8_dd == 0)
        {
            res = FUN_422c60(dd, surface, surface2, width, height, depth);
        }
        if (res != DD_OK)
        {
            res = dd->SetDisplayMode(width, height, depth, 0, 0);
            if (res != DD_OK)
            {
                return res;
            }
        }
    }

    if (g_005728d8_dd == 0)
    {
        res = FUN_422df0(dd, surface, surface2, width, height);
    }
    if (g_005728d8_dd == 0)
    {
        res = FUN_422d50(dd, surface, surface2, width, height);
    }
    if (g_005728d8_dd == 0)
    {
        res = FUN_422ea0(dd, surface, surface2, width, height);
    }
    if (res != DD_OK)
    {
        return res;
    }

    if (depth == 16)
    {
        FUN_422bf0();
    }

    DDSURFACEDESC2 ddsd;
    ddsd.dwSize = sizeof(ddsd);
    g_DD_DISPLAYRESWIDTH = width;
    g_DD_DISPLAYRESHEIGHT = height;
    g_DD_DISPLAYRESDEPTH = depth;
    g_DD_DISPLAYPITCH = width;
    g_surface->GetSurfaceDesc(&ddsd);
    if (ddsd.dwFlags & DDSD_PITCH)
    {
        g_DD_DISPLAYPITCH = ddsd.lPitch;
    }
    return DD_OK;
}

// FUNCTION: STUNTGP_D3D 0x423070
void FUN_423070(BYTE *src)
{
    for (int i = 0; i < 256; i++)
    {
        src++;
        g_paletteEntries[i].peRed = *src++;
        g_paletteEntries[i].peGreen = *src++;
        g_paletteEntries[i].peBlue = *src++;
        g_paletteEntries[i].peFlags = PC_RESERVED;
    }
    g_paletteEntries[0].peFlags = D3DPAL_READONLY;
    g_paletteEntries[255].peFlags = D3DPAL_READONLY;
}

// FUNCTION: STUNTGP_D3D 0x4230b0
int FUN_4230b0(LPDIRECTDRAWPALETTE *palette, BYTE *src)
{
    int res = 0;
    HDC hDC = GetDC(NULL);
    if (GetDeviceCaps(hDC, RASTERCAPS) & RC_PALETTE)
    {
        GetSystemPaletteEntries(hDC, 0, 256, g_paletteEntries);
        FUN_423070(src);
        res = g_dd->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE, g_paletteEntries, palette, NULL) == DD_OK;
        if (res)
        {
            LPDIRECTDRAWPALETTE pal = *palette;
            g_surface->SetPalette(pal);
            res = g_surface2->SetPalette(pal);
        }
    }
    ReleaseDC(NULL, hDC);
    return res;
}

// FUNCTION: STUNTGP_D3D 0x423140
int FUN_423140(LPDIRECTDRAWSURFACE4 surface, LPDIRECTDRAWPALETTE *palette, BYTE *src)
{
    FUN_423070(src);
    int res = g_dd->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE | DDPCAPS_ALLOW256, g_paletteEntries, palette, NULL);
    if (res == DD_OK)
    {
        surface->SetPalette(*palette);
        return DD_OK;
    }
    return res;
}

// Copies a block of rows into a locked surface.
// FUNCTION: STUNTGP_D3D 0x423180
void FUN_423180(LPDIRECTDRAWSURFACE surface, BYTE *src, int width, int height, int pitch)
{
    DDSURFACEDESC ddsd;
    if (g_DD_DISPLAYRESDEPTH == 16)
    {
        width *= 2;
        pitch *= 2;
    }
    ddsd.dwSize = sizeof(ddsd);
    if (surface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) == DD_OK)
    {
        BYTE *dst = (BYTE *)ddsd.lpSurface;
        if (ddsd.dwFlags & DDSD_PITCH)
        {
            pitch = ddsd.lPitch;
        }
        for (int y = 0; y < height; y++)
        {
            if (width > 0)
            {
                memcpy(dst, src, width);
            }
            src += width;
            dst += pitch;
        }
        surface->Unlock(NULL);
    }
}

// FUNCTION: STUNTGP_D3D 0x423230
void FUN_423230(LPDIRECTDRAWSURFACE4 surface, char color)
{
    DDBLTFX fx;
    fx.dwSize = sizeof(fx);
    fx.dwFillColor = color;
    if (surface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &fx) != DD_OK &&
        surface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &fx) != DD_OK)
    {
        surface->GetBltStatus(DDGBS_CANBLT);
        // STRING: STUNTGP_D3D 0x477590
        exitError("Requested Blitter Fill operation failed...\n");
    }
}

// FUNCTION: STUNTGP_D3D 0x423290
void FUN_423290(LPDIRECTDRAWSURFACE4 surface, char color, int width, int height)
{
    DDBLTFX fx;
    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = width;
    rect.bottom = height;
    fx.dwSize = sizeof(fx);
    fx.dwFillColor = color;
    if (surface->Blt(&rect, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &fx) != DD_OK &&
        surface->Blt(&rect, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &fx) != DD_OK)
    {
        surface->GetBltStatus(DDGBS_CANBLT);
        // STRING: STUNTGP_D3D 0x4775bc
        exitError("Requested Blitter Fill operation failed...\n");
    }
}

// FUNCTION: STUNTGP_D3D 0x423310
void FUN_423310(LPDIRECTDRAWSURFACE4 src, LPDIRECTDRAWSURFACE4 dst, DWORD x, DWORD y, int width, int height)
{
    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = width;
    rect.bottom = height;
    if (dst->BltFast(x, y, src, &rect, DDBLTFAST_WAIT) != DD_OK &&
        dst->BltFast(x, y, src, &rect, DDBLTFAST_WAIT) != DD_OK)
    {
        // STRING: STUNTGP_D3D 0x4775e8
        exitError("Requested Blitter Blit operation failed...\n");
    }
}

// FUNCTION: STUNTGP_D3D 0x423380
void FUN_423380(LPDIRECTDRAWSURFACE4 src, LPDIRECTDRAWSURFACE4 dst, int x, int y, int width, int height)
{
    DDBLTFX fx;
    RECT srcRect;
    RECT dstRect;
    fx.dwSize = sizeof(fx);
    srcRect.left = 0;
    srcRect.top = 0;
    srcRect.right = width;
    srcRect.bottom = height;
    dstRect.left = 0;
    dstRect.top = 0;
    dstRect.right = width;
    dstRect.bottom = height;
    if (dst->Blt(&dstRect, src, &srcRect, DDBLTFAST_WAIT, &fx) != DD_OK)
    {
        // STRING: STUNTGP_D3D 0x477614
        exitError("Requested Blitter Blit operation failed...\n");
    }
}

// FUNCTION: STUNTGP_D3D 0x423430
void FUN_423430()
{
    if (g_renderState.unk8004 != 1)
    {
        FUN_422ba0(*g_61c358);
        g_renderState.unk8004 = 1;
    }
}

// GLOBAL: STUNTGP_D3D 0x5729e0
DWORD g_perfFrequency;

// GLOBAL: STUNTGP_D3D 0x572be4
DWORD g_572be4;

// FUNCTION: STUNTGP_D3D 0x423450
void FUN_423450()
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    g_perfFrequency = freq.LowPart;
    g_572be4 = freq.LowPart / 60;
}
