#ifndef INPUT_H
#define INPUT_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define DIRECTINPUT_VERSION 0x0500
#include <dinput.h>

struct InputEffect
{
    LPDIRECTINPUTEFFECT effect; // 0x00
    DICONDITION condition;      // 0x04
    DICONSTANTFORCE constant;   // 0x1c
    DIPERIODIC periodic;        // 0x20
    DIENVELOPE envelope;        // 0x30
    DIEFFECT desc;              // 0x44
};

struct InputDevice
{
    LPDIRECTINPUTDEVICE2 device;
    InputEffect effects[12];
};

extern InputDevice g_inputDevices[10];
extern DWORD g_inputDeviceCount;

void FUN_4239b0();
int FUN_4249b0();
void Input_Shutdown();
#endif /* INPUT_H */
