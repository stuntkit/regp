#ifndef CAMERA_PATH_H
#define CAMERA_PATH_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct CameraPath
{
    int id;           // 0x00
    BYTE unk04[0x14]; // 0x04
    float unk18;      // 0x18
};

extern CameraPath *g_624474;

#endif /* CAMERA_PATH_H */
