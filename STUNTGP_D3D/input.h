#ifndef INPUT_H
#define INPUT_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define DIRECTINPUT_VERSION 0x0500
#include <dinput.h>

struct InputEffect
{
    LPDIRECTINPUTEFFECT effect;
    BYTE unk04[0x74];
};

struct InputDevice
{
    LPDIRECTINPUTDEVICE2 device;
    InputEffect effects[12];
};

void FUN_4239b0();
int FUN_4249b0();
void Input_Shutdown();
#endif /* INPUT_H */
