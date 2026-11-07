#include "input.h"

#include <string.h>

#include "Game/GameEngine/GameUpdate.h"
#include "globals.h"

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

// GLOBAL: STUNTGP_D3D 0x572ce8
InputDevice g_inputDevices[10];

// GLOBAL: STUNTGP_D3D 0x576550
InputDevice *g_576550;

// GLOBAL: STUNTGP_D3D 0x576554
DWORD g_inputDeviceCount;

// GLOBAL: STUNTGP_D3D 0x576558
GUID g_576558[4];

// GLOBAL: STUNTGP_D3D 0x576b68
LPDIRECTINPUT g_directInput;

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

// FUNCTION: STUNTGP_D3D 0x424930
void Input_Shutdown()
{
    if (g_directInput)
    {
        for (DWORD i = 0; i < g_inputDeviceCount; i++)
        {
            InputDevice *dev = &g_inputDevices[i];
            for (int j = 0; j < 12; j++)
            {
                if (dev->effects[j].effect)
                {
                    dev->effects[j].effect->Release();
                    dev->effects[j].effect = NULL;
                }
            }
            dev->device->Unacquire();
            dev->device->Release();
        }
        g_directInput->Release();
    }
}

// FUNCTION: STUNTGP_D3D 0x4249b0
int FUN_4249b0()
{
    g_directInput = NULL;
    g_inputDeviceCount = 0;
    memset(g_inputDevices, 0, sizeof(g_inputDevices));
    memset(g_576618, 0, sizeof(g_576618));
    g_576550 = g_inputDevices;
    g_576618[0].present = 1;
    g_576618[0].type = 1;
    g_576b6c = (BYTE *)&g_576618[1].state;
    FUN_4239b0();
    for (int i = 0; i < 10; i++)
    {
        g_inputDevices[i].device = NULL;
    }
    if (DirectInputCreate(g_hInstance, DIRECTINPUT_VERSION, &g_directInput, NULL) != DI_OK)
    {
        return 0;
    }
    g_directInput->EnumDevices(DIDEVTYPE_JOYSTICK, FUN_423b00, g_directInput, DIEDFL_ATTACHEDONLY | DIEDFL_FORCEFEEDBACK);
    if (g_inputDeviceCount == 0)
    {
        if (g_directInput->EnumDevices(DIDEVTYPE_JOYSTICK, FUN_424740, g_directInput, DIEDFL_ATTACHEDONLY) != DI_OK)
        {
            return 0;
        }
    }
    return 1;
}
