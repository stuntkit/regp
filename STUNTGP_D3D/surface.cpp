#include "surface.h"

#include <math.h>
#include <string.h>

#include "globals.h"
#include "windowInit.h"

// GLOBAL: STUNTGP_D3D 0x592180
DDGAMMARAMP g_gammaRamp;

// GLOBAL: STUNTGP_D3D 0x5da1dc
LPDIRECTDRAWGAMMACONTROL g_gammaControl;

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
    for (int i = g_surfaceSlotCount; i > 0; i--)
    {
        SurfaceSlot *slot = &g_surfaceSlots[i - 1];
        if (slot->surface2 != slot->surface)
        {
            ddReleaseSurface(&slot->surface2);
        }
        else
        {
            slot->surface2 = NULL;
        }
        ddReleaseSurface(&slot->surface);
        FUN_4300f0((IUnknown *)slot->unk04);
        FUN_4300f0((IUnknown *)slot->unk0c);
    }
    g_surfaceSlotCount = 0;
    memset(g_surfaceSlots, 0, sizeof(g_surfaceSlots));
}

// FUNCTION: STUNTGP_D3D 0x431800
void FUN_431800()
{
    FUN_4320a0();
    FUN_431790();
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
    if (control && fabs(gamma - g_6244f4) >= 0.01)
    {
        float scale = (gamma - 1.0) * 0.2;
        g_6244f4 = gamma;
        if (scale > 0.98)
        {
            scale = 0.98f;
        }
        DWORD level = scale * scale * 65280.0f;
        DWORD step = ((level >> 6) - level + 0xff00) >> 8;
        for (int i = 0; i < 256; i++)
        {
            WORD value = level > 0xfffe ? 0xfffe : level;
            g_gammaRamp.red[i] = value;
            g_gammaRamp.green[i] = value;
            g_gammaRamp.blue[i] = value;
            level += step;
        }
        control->SetGammaRamp(0, &g_gammaRamp);
    }
}
