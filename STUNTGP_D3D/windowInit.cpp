#include "windowInit.h"

// TODO: should we set this as a struct???
// GLOBAL: STUNTGP_D3D 0x4754d0
errorMessage errorMessages[] = {
    {"No Error", DD_OK},
    {" This object is already initialised", DDERR_ALREADYINITIALIZED},
    {" This surface can not be attached to the requested surface.", DDERR_CANNOTATTACHSURFACE},
    {" This surface can not be detached from the requested surface.", DD_OK},
    {" Support is currently not available.", DD_OK},
    {" An exception was encountered while performing the requested operation", DD_OK},
    {"Generic failure.", DD_OK},
    {" Height of rectangle provided is not a multiple of reqd alignment", DD_OK},
    {" Unable to match primary surface creation request with existing primary surface.", DD_OK},
    {" One or more of the caps bits passed to the callback are incorrect.", DD_OK},
    {" DirectDraw does not support provided Cliplist.", DD_OK},
    {" DirectDraw does not support the requested mode", DD_OK},
    {" DirectDraw received a pointer that was an invalid DIRECTDRAW object.", DD_OK},
    {"One or more of the parameters passed to the callback function are incorrect.", DD_OK},
    {" pixel format was invalid as specified", DD_OK},
    {" Rectangle provided was invalid.", DD_OK},
    {" Operation could not be carried out because one or more surfaces are locked", DD_OK},
    {" There is no 3D present.", DD_OK},
    {" Operation could not be carried out because there is no alpha accleration hardware present or available.", DD_OK},
    {" no clip list available", DD_OK},
    {" Operation could not be carried out because there is no color conversion hardware present or available.", DD_OK},
    {" Create function called without DirectDraw object method SetCooperativeLevel being called.", DD_OK},
    {" Surface doesn't currently have a color key", DD_OK},
    {" Operation could not be carried out because there is no hardware support of the dest color key.", DD_OK},
    {" No DirectDraw support possible with current display driver", DD_OK},
    {" Operation requires the application to have exclusive mode but the application does not have exclusive mode.",
     DD_OK},
    {" Flipping visible surfaces is not supported.", DD_OK},
    {" There is no GDI present.", DD_OK},
    {" Operation could not be carried out because there is no hardware present or available.", DD_OK},
    {" Requested item was not found", DD_OK},
    {" Operation could not be carried out because there is no overlay hardware present or available.", DD_OK},
    {" Operation could not be carried out because there is no appropriate raster op hardware present or available.",
     DD_OK},
    {" Operation could not be carried out because there is no rotation hardware present or available.", DD_OK},
    {" Operation could not be carried out because there is no hardware support for stretching", DD_OK},
    {" DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette.",
     DD_OK},
    {" DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index "
     "palette.",
     DD_OK},
    {" DirectDraw Surface is not in 8 bit color mode and the requested operation requires 8 bit color.", DD_OK},
    {" Operation could not be carried out because there is no texture mapping hardware present or available.", DD_OK},
    {" Operation could not be carried out because there is no hardware support for vertical blank synchronized "
     "operations.",
     DD_OK},
    {" Operation could not be carried out because there is no hardware support for zbuffer blting.", DD_OK},
    {" Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z "
     "layering of overlays.",
     DD_OK},
    {" The hardware needed for the requested operation has already been allocated.", DD_OK},
    {"DirectDraw does not have enough memory to perform the operation.", DD_OK},
    {" DirectDraw does not have enough memory to perform the operation.", DD_OK},
    {" hardware does not support clipped overlays", DD_OK},
    {" Can only have ony color key active at one time for overlays", DD_OK},
    {" Access to this palette is being refused because the palette is already locked by another thread.", DD_OK},
    {" No src color key specified for this operation.", DD_OK},
    {" This surface is already attached to the surface it is being attached to.", DD_OK},
    {" This surface is already a dependency of the surface it is being made a dependency of.", DD_OK},
    {" Access to this surface is being refused because the surface is already locked by another thread.", DD_OK},
    {"Access to this surface is being refused because no driver existswhich can supply a pointer to the surface.This "
     "is most likely to happen when attempting to lock the primarysurface when no DCI provider is present.",
     DD_OK},
    {" Access to Surface refused because Surface is obscured.", DD_OK},
    {" Access to this surface is being refused because the surface is gone.The DIRECTDRAWSURFACE object representing "
     "this surface should have Restore called on it.",
     DD_OK},
    {" The requested surface is not attached.", DD_OK},
    {" Height requested by DirectDraw is too large.", DD_OK},
    {" Size requested by DirectDraw is too large --  The individual height and width are OK.", DD_OK},
    {" Width requested by DirectDraw is too large.", DD_OK},
    {"Action not supported.", DD_OK},
    {" FOURCC format requested is unsupported by DirectDraw", DD_OK},
    {" Bitmask in the pixel format requested is unsupported by DirectDraw", DD_OK},
    {" vertical blank is in progress", DD_OK},
    {" Informs DirectDraw that the previous Blt which is transfering information to or from this Surface is "
     "incomplete.",
     DD_OK},
    {" Rectangle provided was not horizontally aligned on reqd. boundary", DD_OK},
    {" The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.", DD_OK},
    {" A DirectDraw object representing this driver has already been created for this process.", DD_OK},
    {" A hardware only DirectDraw object creation was attempted but the driver did not support any hardware.", DD_OK},
    {" this process already has created a primary surface", DD_OK},
    {" software emulation not available.", DD_OK},
    {" region passed to Clipper::GetClipList is too small.", DD_OK},
    {" an attempt was made to set a clip list for a clipper objec that is already monitoring an hwnd.", DD_OK},
    {" No clipper object attached to surface object", DD_OK},
    {" Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.", DD_OK},
    {" HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state.",
     DD_OK},
    {" The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes "
     "created.",
     DD_OK},
    {" No palette object attached to this surface.", DD_OK},
    {" No hardware support for 16 or 256 color palettes.", DD_OK},
    {" If a clipper object is attached to the source surface passed into a BltFast call.", DD_OK},
    {" No blter.", DD_OK},
    {" No DirectDraw ROP hardware.", DD_OK},
    {" returned when GetOverlayPosition is called on a hidden overlay", DD_OK},
    {" returned when GetOverlayPosition is called on a overlay that UpdateOverlay has never been called on to "
     "establish a destionation.",
     DD_OK},
    {" returned when the position of the overlay on the destionation is no Sint32er legal for that destionation.",
     DD_OK},
    {" returned when an overlay member is called for a non-overlay surface", DD_OK},
    {" An attempt was made to set the cooperative level when it was already set to exclusive.", DD_OK},
    {" An attempt has been made to flip a surface that is not flippable.", DD_OK},
    {" Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.", DD_OK},
    {" Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has "
     "been attempted.",
     DD_OK},
    {" Windows can not create any more DCs", DD_OK},
    {" No DC was ever created for this surface.", DD_OK},
    {" This surface can not be restored because it was created in a different mode.", DD_OK},
    {" This surface can not be restored because it is an implicitly created surface.", DD_OK},
    {" The surface being used is not a palette-based surface", DD_OK},
    {" The display is currently in an unsupported mode", DD_OK},
    {" Operation could not be carried out because there is no mip-map texture mapping hardware present or available.",
     DD_OK},
    {" The requested action could not be performed because the surface was of the wrong type.", DD_OK},
    {" A DC has already been returned for this surface. Only one DC can be retrieved per surface.", DD_OK},
    {" The attempt to page lock a surface failed.", DD_OK},
    {" The attempt to page unlock a surface failed.", DD_OK},
    {" An attempt was made to page unlock a surface with no outstanding page locks.", DD_OK},
    {" An attempt was made to invoke an interface member of a DirectDraw object created by CoCreateInstance(), before "
     "it was initialized.",
     DD_OK},
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
