#include "input.h"

// GLOBAL: STUNTGP_D3D 0x572ce8
InputDevice g_inputDevices[10];

// GLOBAL: STUNTGP_D3D 0x576554
DWORD g_inputDeviceCount;

// GLOBAL: STUNTGP_D3D 0x576b68
LPDIRECTINPUT g_directInput;

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
