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
InputState *g_576b6c;

// GLOBAL: STUNTGP_D3D 0x576b74
BOOL g_576b74;

// GLOBAL: STUNTGP_D3D 0x462780
// c_dfDIJoystick

// GLOBAL: STUNTGP_D3D 0x46f9e0
// IID_IDirectInputDevice2A

int FUN_4246c0(LPDIRECTINPUTDEVICE device);

// FUNCTION: STUNTGP_D3D 0x423950
void FUN_423950(InputDevice *dev)
{
    for (int i = 0; i < 12; i++)
    {
        g_576550->effects[i].effect = NULL;
        memset(&g_576550->effects[i].condition, 0, sizeof(DICONDITION));
        memset(&g_576550->effects[i].constant, 0, sizeof(DICONSTANTFORCE));
        memset(&g_576550->effects[i].periodic, 0, sizeof(DIPERIODIC));
        memset(&g_576550->effects[i].envelope, 0, sizeof(DIENVELOPE));
        memset(&g_576550->effects[i].desc, 0, sizeof(DIEFFECT));
    }
}

// FUNCTION: STUNTGP_D3D 0x4239b0
void FUN_4239b0()
{
    g_576558[0] = GUID_Spring;
    g_576558[1] = GUID_Damper;
    g_576558[2] = GUID_Inertia;
    g_576558[3] = GUID_Friction;
}

// FUNCTION: STUNTGP_D3D 0x423a70
BOOL CALLBACK FUN_423a70(LPCDIEFFECTINFO info, LPVOID ref)
{
    *(GUID *)ref = info->guid;
    g_576b74 = TRUE;
    return DIENUM_CONTINUE;
}

// FUNCTION: STUNTGP_D3D 0x423aa0
BOOL FUN_423aa0(InputDevice *dev)
{
    GUID guid;
    return dev->device->EnumEffects(FUN_423a70, &guid, DIEFT_ALL) == DI_OK;
}

// FUNCTION: STUNTGP_D3D 0x423ad0
BOOL CALLBACK FUN_423ad0(LPCDIDEVICEINSTANCE instance, LPVOID ref)
{
    *(GUID *)ref = instance->guidInstance;
    return DIENUM_STOP;
}

// FUNCTION: STUNTGP_D3D 0x423b00
BOOL CALLBACK FUN_423b00(LPCDIDEVICEINSTANCE instance, LPVOID ref)
{
    LPDIRECTINPUTDEVICE device;
    LPDIRECTINPUTDEVICE2 device2;
    DIPROPRANGE range;
    DIPROPDWORD dword;

    if (g_directInput->CreateDevice(instance->guidInstance, &device, NULL) != DI_OK)
    {
        return DIENUM_CONTINUE;
    }
    if (device->QueryInterface(IID_IDirectInputDevice2, (void **)&g_576550->device) != DI_OK)
    {
        device->Release();
        return DIENUM_STOP;
    }
    device2 = g_576550->device;
    if (device2->SetCooperativeLevel(g_Hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
    {
        device->Release();
        return DIENUM_CONTINUE;
    }
    if (device2->SetDataFormat(&c_dfDIJoystick) != DI_OK)
    {
        device->Release();
        return DIENUM_CONTINUE;
    }

    dword.diph.dwSize = sizeof(DIPROPDWORD);
    dword.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dword.diph.dwObj = 0;
    dword.diph.dwHow = DIPH_DEVICE;
    dword.dwData = DIPROPAUTOCENTER_OFF;
    device2->SetProperty(DIPROP_AUTOCENTER, &dword.diph);
    FUN_423aa0(g_576550);

    range.diph.dwSize = sizeof(DIPROPRANGE);
    range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    range.diph.dwObj = DIJOFS_X;
    range.diph.dwHow = DIPH_BYOFFSET;
    range.lMin = -5000;
    range.lMax = 5000;
    if (device2->SetProperty(DIPROP_RANGE, &range.diph) != DI_OK)
    {
        device->Release();
        return DIENUM_STOP;
    }
    range.diph.dwObj = DIJOFS_Y;
    if (device2->SetProperty(DIPROP_RANGE, &range.diph) != DI_OK)
    {
        device->Release();
        return DIENUM_STOP;
    }

    dword.diph.dwSize = sizeof(DIPROPDWORD);
    dword.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dword.diph.dwObj = DIJOFS_X;
    dword.diph.dwHow = DIPH_BYOFFSET;
    dword.dwData = 1250;
    if (device2->SetProperty(DIPROP_DEADZONE, &dword.diph) != DI_OK)
    {
        device->Release();
        return DIENUM_STOP;
    }
    dword.diph.dwObj = DIJOFS_Y;
    if (device2->SetProperty(DIPROP_DEADZONE, &dword.diph) != DI_OK)
    {
        device->Release();
        return DIENUM_STOP;
    }

    FUN_423950(g_576550);
    DWORD slot = g_inputDeviceCount + 1;
    if (slot < 10)
    {
        g_576618[slot].present = 1;
        g_576618[slot].type = FUN_4246c0(device);
        g_576618[slot].unk08 = 2;
    }
    g_576550++;
    g_inputDeviceCount++;
    g_576b74 = TRUE;
    return DIENUM_CONTINUE;
}

// FUNCTION: STUNTGP_D3D 0x4246c0
int FUN_4246c0(LPDIRECTINPUTDEVICE device)
{
    DIDEVICEINSTANCE info;
    memset(&info, 0, sizeof(info));
    info.dwSize = sizeof(info);
    if (device->GetDeviceInfo(&info) == DI_OK)
    {
        switch (GET_DIDEVICE_SUBTYPE(info.dwDevType))
        {
        case DIDEVTYPEJOYSTICK_UNKNOWN:
            return 5;
        case DIDEVTYPEJOYSTICK_TRADITIONAL:
            return 5;
        case DIDEVTYPEJOYSTICK_FLIGHTSTICK:
            return 5;
        case DIDEVTYPEJOYSTICK_GAMEPAD:
            return 5;
        case DIDEVTYPEJOYSTICK_RUDDER:
            return 5;
        case DIDEVTYPEJOYSTICK_WHEEL:
            return 2;
        }
    }
    return 5;
}

// FUNCTION: STUNTGP_D3D 0x424740
BOOL CALLBACK FUN_424740(LPCDIDEVICEINSTANCE instance, LPVOID ref)
{
    LPDIRECTINPUTDEVICE device;
    DIPROPRANGE range;
    DIPROPDWORD dword;

    if (g_directInput->CreateDevice(instance->guidInstance, &device, NULL) != DI_OK)
    {
        return DIENUM_CONTINUE;
    }
    if (device->SetDataFormat(&c_dfDIJoystick) != DI_OK)
    {
        device->Release();
        return DIENUM_CONTINUE;
    }
    if (device->SetCooperativeLevel(g_Hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
    {
        device->Release();
        return DIENUM_CONTINUE;
    }

    range.diph.dwSize = sizeof(DIPROPRANGE);
    range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    range.diph.dwObj = DIJOFS_X;
    range.diph.dwHow = DIPH_BYOFFSET;
    range.lMin = -5000;
    range.lMax = 5000;
    if (device->SetProperty(DIPROP_RANGE, &range.diph) != DI_OK)
    {
        device->Release();
        return DIENUM_STOP;
    }
    range.diph.dwObj = DIJOFS_Y;
    if (device->SetProperty(DIPROP_RANGE, &range.diph) != DI_OK)
    {
        device->Release();
        return DIENUM_STOP;
    }

    dword.diph.dwSize = sizeof(DIPROPDWORD);
    dword.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dword.diph.dwObj = DIJOFS_X;
    dword.diph.dwHow = DIPH_BYOFFSET;
    dword.dwData = 1250;
    if (device->SetProperty(DIPROP_DEADZONE, &dword.diph) != DI_OK)
    {
        device->Release();
        return DIENUM_STOP;
    }
    dword.diph.dwObj = DIJOFS_Y;
    if (device->SetProperty(DIPROP_DEADZONE, &dword.diph) != DI_OK)
    {
        device->Release();
        return DIENUM_STOP;
    }

    if (device->QueryInterface(IID_IDirectInputDevice2, (void **)&g_576550->device) != DI_OK)
    {
        device->Release();
        return DIENUM_STOP;
    }
    DWORD slot = g_inputDeviceCount + 1;
    if (slot < 10)
    {
        g_576618[slot].present = 1;
        g_576618[slot].type = FUN_4246c0(device);
        g_576618[slot].unk08 = 0;
    }
    g_576550++;
    g_inputDeviceCount++;
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
    g_576b6c = &g_576618[1].state;
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
