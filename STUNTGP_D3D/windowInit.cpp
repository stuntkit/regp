#include "windowInit.h"

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

// FUNCTION: STUNTGP_D3D 0x422700
HWND windowCreateInternal(HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName)
{
    int height = GetSystemMetrics(SM_CYFULLSCREEN);
    int width = GetSystemMetrics(SM_CXFULLSCREEN);
    HWND wHandle = CreateWindowEx(WS_EX_APPWINDOW, className, windowName, WS_POPUP, 0, 0, width, height, NULL, NULL,
                                  hInstance, NULL);
    if (!wHandle)
    {
        return NULL;
    }
    ShowWindow(wHandle, SW_NORMAL);
    UpdateWindow(wHandle);
    return wHandle;
}

// FUNCTION: STUNTGP_D3D 0x422690
char *ddGetResMessage(int res)
{
    int elements = {0};
    // DATA: STUNTGP_D3D 0x572ae4
    static char message[256];

    if (errorMessages[0].message)
    {
        errorMessage *errorMessagePtr = errorMessages;
        for (; errorMessagePtr != NULL; errorMessagePtr++)
        {
            if (errorMessagePtr->code == res)
            {
                // STRING: STUNTGP_D3D 0x477570
                sprintf(message, "%s\n", errorMessagePtr->message);
                return message;
            }
        }
        elements++;
    }
    // STRING: STUNTGP_D3D 0x477574
    sprintf(message, "No Text For Error : %.8x\n", res);
    return message;
    // TODO
}

// // STUB: STUNTGP_D3D 0x422780
// void FUN_422780()
// {
// }

// // STUB: STUNTGP_D3D 0x4227b0
// void FUN_4227b0()
// {
// }

// TODO: move to another file, this shouldn't inline at all
// FUNCTION: STUNTGP_D3D 0x422780
int ddSetCoopLevel(LPDIRECTDRAW lplpDD, HWND hWnd)
{
    int res = lplpDD->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE);
    if (res != DD_OK)
    {
        ddGetResMessage(res);
        exitError();
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
        ddGetResMessage(res);
        exitError();
    }
    ddSetCoopLevel(*lplpDD, hWnd);
    return res;
}

// FUNCTION: STUNTGP_D3D 0x4227b0
int dd4SetCoopLevel(LPDIRECTDRAW4 ppvObj, HWND hWnd)
{
    // TODO; move the last parameter to define and use in both SetCooperativeLevel?
    int res = ppvObj->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE);
    if (res != DD_OK)
    {
        ddGetResMessage(res);
        exitError();
    }
    return res;
}

// STUB: STUNTGP_D3D 0x422820
int ddGetDD4(LPDIRECTDRAW lplpDD, LPDIRECTDRAW4 *ppvObj, HWND hWnd)
{
    int res = lplpDD->QueryInterface(IID_IDirectDraw4, (LPVOID *)ppvObj);
    if (res != DD_OK)
    {
        ddGetResMessage(res);
        exitError();
    }
    dd4SetCoopLevel(*ppvObj, hWnd);
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
