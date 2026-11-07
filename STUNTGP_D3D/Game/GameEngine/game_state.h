#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "GameUpdate.h"

struct CameraPath
{
    int id;           // 0x00
    Vec4 *points;     // 0x04
    DWORD count;      // 0x08
    BYTE unk0c[0x10]; // 0x0c
};

extern CameraPath *g_624474;

void FUN_402580();
void FUN_402e90();

#endif /* GAME_STATE_H */
