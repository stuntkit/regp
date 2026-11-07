#ifndef VECMATH_H
#define VECMATH_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct Camera;

void FUN_44ee00();
void Matrix_Identity(float *m);
void Vec3_Normalize(float *v);
void FUN_44f4c0();
void FUN_44f4e0(float *m);
void FUN_450190(Camera *cam);
void FUN_44eb70(DWORD yaw, DWORD pitch, DWORD roll, float *x, float *y, float *z);

extern float g_61c3e8[16];
extern float g_61c468[16];
#endif /* VECMATH_H */
