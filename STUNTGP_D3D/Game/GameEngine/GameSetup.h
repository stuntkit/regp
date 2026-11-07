#ifndef GAMESETUP_H
#define GAMESETUP_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct Unk4d5cc0
{
    short unk00;
    BYTE unk02[0x1a];
    DWORD unk1c;
    BYTE unk20[0x1c];
    int unk3c;
    BYTE unk40[0x19d00 - 0x40];
};

extern int g_589e08;
extern int g_624984;

void FUN_401de0();
void FUN_40a2f0();
void FUN_40d500();
void FUN_40e050();
void FUN_413670();
void FUN_4199a0();
void FUN_424c30(int param);
void FUN_425ad0();
void FUN_4277d0();
void FUN_429a40();
void FUN_42b040();
void FUN_42dcf0();
void FUN_42e800();
void FUN_42e820();
extern int g_624988;
extern int g_62498c;
extern DWORD g_61c508;
void FUN_429510();
void FUN_42e6e0();
void FUN_43d0b0();
void FUN_43d1b0();
void FUN_43d1d0();
void FUN_43d1f0();
int FUN_43d420();
void FUN_445fa0();
void FUN_4469f0();
void FUN_45ec30();
#endif /* GAMESETUP_H */
