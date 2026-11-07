#include "input.h"

#include <string.h>

#include "globals.h"

#define DIRECTINPUT_VERSION 0x0500
#include <dinput.h>

// LIBRARY: STUNTGP_D3D 0x462798
// _DirectInputCreateA@16

// GLOBAL: STUNTGP_D3D 0x46fb60
// GUID_Spring

// GLOBAL: STUNTGP_D3D 0x46fb70
// GUID_Damper

// GLOBAL: STUNTGP_D3D 0x46fb80
// GUID_Inertia

// GLOBAL: STUNTGP_D3D 0x46fb90
// GUID_Friction

struct JoyDevice
{
    int unk00;
    BYTE unk04[0x5a4 - 4];
};

// GLOBAL: STUNTGP_D3D 0x572ce8
JoyDevice g_572ce8[10];

// GLOBAL: STUNTGP_D3D 0x576550
JoyDevice *g_576550;

// GLOBAL: STUNTGP_D3D 0x576554
int g_576554;

// GLOBAL: STUNTGP_D3D 0x576558
GUID g_576558[4];

struct Unk576618
{
    int unk00;
    int unk04;
    BYTE unk08[0x94 - 8];
    BYTE unk94[0x550 - 0x94];
};

// GLOBAL: STUNTGP_D3D 0x576618
Unk576618 g_576618;

// GLOBAL: STUNTGP_D3D 0x576b68
LPDIRECTINPUT g_576b68;

// GLOBAL: STUNTGP_D3D 0x576b6c
BYTE *g_576b6c;

// FUNCTION: STUNTGP_D3D 0x4239b0
void FUN_4239b0()
{
    g_576558[0] = GUID_Spring;
    g_576558[1] = GUID_Damper;
    g_576558[2] = GUID_Inertia;
    g_576558[3] = GUID_Friction;
}

// STUB: STUNTGP_D3D 0x423b00
BOOL CALLBACK FUN_423b00(LPCDIDEVICEINSTANCE instance, LPVOID ref)
{
    return DIENUM_CONTINUE;
}

// STUB: STUNTGP_D3D 0x424740
BOOL CALLBACK FUN_424740(LPCDIDEVICEINSTANCE instance, LPVOID ref)
{
    return DIENUM_CONTINUE;
}

// FUNCTION: STUNTGP_D3D 0x4249b0
int FUN_4249b0()
{
    g_576b68 = NULL;
    g_576554 = 0;
    memset(g_572ce8, 0, sizeof(g_572ce8));
    memset(&g_576618, 0, sizeof(g_576618));
    g_576550 = g_572ce8;
    g_576618.unk00 = 1;
    g_576618.unk04 = 1;
    g_576b6c = g_576618.unk94;
    FUN_4239b0();
    for (int i = 0; i < 10; i++)
    {
        g_572ce8[i].unk00 = 0;
    }
    if (DirectInputCreate(g_hInstance, DIRECTINPUT_VERSION, &g_576b68, NULL) != DI_OK)
    {
        return 0;
    }
    g_576b68->EnumDevices(DIDEVTYPE_JOYSTICK, FUN_423b00, g_576b68, DIEDFL_ATTACHEDONLY | DIEDFL_FORCEFEEDBACK);
    if (g_576554 == 0)
    {
        if (g_576b68->EnumDevices(DIDEVTYPE_JOYSTICK, FUN_424740, g_576b68, DIEDFL_ATTACHEDONLY) != DI_OK)
        {
            return 0;
        }
    }
    return 1;
}
