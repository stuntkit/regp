#include "surface.h"

#include <math.h>
#include <string.h>

#include "globals.h"
#include "windowInit.h"
#include "common.h"
#include "d3drender.h"
#include "Game/GameEngine/RenderState.h"

// GLOBAL: STUNTGP_D3D 0x5ba780
LPDIRECTDRAWSURFACE4 g_5ba780;

// GLOBAL: STUNTGP_D3D 0x592180
DDGAMMARAMP g_gammaRamp;

// GLOBAL: STUNTGP_D3D 0x5da1dc
LPDIRECTDRAWGAMMACONTROL g_gammaControl;

void FUN_42fe90(int device, int driver);

// Creates the z-buffer surface unless the driver does hidden-surface removal without one.
// FUNCTION: STUNTGP_D3D 0x42ff20
void FUN_42ff20(int device, int driver)
{
    if (((D3DDriver *)&g_5ba788.devices[device][0x2274])[driver].desc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZBUFFERLESSHSR)
    {
        return;
    }
    DDSURFACEDESC2 desc;
    memset(&desc, 0, sizeof(desc));
    desc.dwWidth = g_DD_DISPLAYRESWIDTH;
    desc.dwHeight = g_DD_DISPLAYRESHEIGHT;
    desc.dwSize = sizeof(desc);
    desc.ddsCaps.dwCaps = (((D3DDriver *)&g_5ba788.devices[device][0x2274])[driver].hardware != 1 ? DDSCAPS_SYSTEMMEMORY : 0) + DDSCAPS_ZBUFFER;
    desc.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
    FUN_42fe90(device, driver);
    desc.ddpfPixelFormat = *g_5ba788.zbufferFormat;
    int res = g_dd4->CreateSurface(&desc, &g_5ba780, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    FUN_422a00(&g_5ba780);
}

// FUNCTION: STUNTGP_D3D 0x42fff0
void FUN_42fff0()
{
    int res = (*g_61c358)->AddAttachedSurface(g_5ba780);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
}

HRESULT WINAPI FUN_42f780(LPDDPIXELFORMAT format, LPVOID context);

// GLOBAL: STUNTGP_D3D 0x46efd0
// IID_IDirect3D3

// FUNCTION: STUNTGP_D3D 0x430020
int FUN_430020(int device, int driver)
{
    BYTE *dev = g_5ba788.devices[device];
    LPDIRECT3D3 *d3d = (LPDIRECT3D3 *)(dev + 0x2264);
    D3DDriver *drv = (D3DDriver *)(dev + 0x2274) + driver;
    if (*d3d)
    {
        (*d3d)->Release();
    }
    if (drv->device)
    {
        drv->device->Release();
    }
    int res = g_dd4->QueryInterface(IID_IDirect3D3, (void **)d3d);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    res = (*d3d)->CreateDevice(drv->guid, g_surface2, &drv->device, NULL);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
    g_5ba788.device = dev;
    g_5ba788.deviceDesc = (int *)drv;
    drv->textureFormatCount = 0;
    drv->device->EnumTextureFormats(FUN_42f780, drv);
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x4300f0
void FUN_4300f0(IUnknown *object)
{
    if (object)
    {
        object->Release();
    }
}

// FUNCTION: STUNTGP_D3D 0x431790
void FUN_431790()
{
    int i = g_5ba788.surfaceSlotCount;
    while (i > 0)
    {
        i--;
        if (g_5ba788.surfaceSlots[i].surface2 != g_5ba788.surfaceSlots[i].surface)
        {
            ddReleaseSurface(&g_5ba788.surfaceSlots[i].surface2);
        }
        else
        {
            g_5ba788.surfaceSlots[i].surface2 = NULL;
        }
        ddReleaseSurface(&g_5ba788.surfaceSlots[i].surface);
        FUN_4300f0((IUnknown *)g_5ba788.surfaceSlots[i].unk04);
        FUN_4300f0((IUnknown *)g_5ba788.surfaceSlots[i].unk0c);
    }
    g_5ba788.surfaceSlotCount = 0;
    memset(g_5ba788.surfaceSlots, 0, sizeof(g_5ba788.surfaceSlots));
}

// FUNCTION: STUNTGP_D3D 0x431800
void FUN_431800()
{
    FUN_4320a0();
    FUN_431790();
}

// FUNCTION: STUNTGP_D3D 0x431ff0
void FUN_431ff0(D3DCOLOR color, float x, float y, float z)
{
    g_58d818[0].sx = x;
    g_58d818[0].sy = y;
    g_58d818[0].rhw = g_58d818[0].sz = z;
    g_58d818[0].color = color;
    g_58d818[0].specular = 0xff000000;
    g_d3dDevice->SetTexture(0, NULL);
    g_d3dDevice->DrawPrimitive(D3DPT_POINTLIST, FVF_TLVERTEX2, g_58d818, 1, D3DDP_DONOTCLIP | D3DDP_DONOTLIGHT);
}

// FUNCTION: STUNTGP_D3D 0x432070
void FUN_432070()
{
    int res = g_surface->QueryInterface(IID_IDirectDrawGammaControl, (void **)&g_gammaControl);
    if (res != DD_OK)
    {
        exitError(ddGetErrMessage(res));
    }
}

// FUNCTION: STUNTGP_D3D 0x4320a0
void FUN_4320a0()
{
    if (g_gammaControl)
    {
        g_gammaControl->Release();
        g_gammaControl = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x4320c0
void FUN_4320c0(float gamma)
{
    LPDIRECTDRAWGAMMACONTROL control = g_gammaControl;
    if (control && fabs(gamma - g_renderState.unk800c) >= 0.01)
    {
        float scale = (gamma - 1.0) * 0.2;
        g_renderState.unk800c = gamma;
        if (scale > 0.98)
        {
            scale = 0.98f;
        }
        DWORD start = scale * scale * 65280.0f;
        DWORD step = ((start >> 6) - start + 0xff00) >> 8;
        DWORD level = start;
        for (int i = 0; i < 256; i++)
        {
            WORD value = level;
            if (level > 0xfffe)
            {
                value = 0xfffe;
            }
            g_gammaRamp.red[i] = value;
            g_gammaRamp.green[i] = value;
            g_gammaRamp.blue[i] = value;
            level += step;
        }
        control->SetGammaRamp(0, &g_gammaRamp);
    }
}
