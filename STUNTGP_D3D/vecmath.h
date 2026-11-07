#ifndef VECMATH_H
#define VECMATH_H
#define WIN32_LEAN_AND_MEAN
#include "sintable.h"
#include <windows.h>

struct Camera;

void FUN_44ee00();
void Matrix_Identity(float *m);
void Vec3_Normalize(float *v);
void FUN_44f4c0();
void FUN_44f4e0(float *m);
void FUN_450190(Camera *cam);
void FUN_44eb70(DWORD yaw, DWORD pitch, DWORD roll, float *x, float *y, float *z);
void FUN_44ec00(float *angles, float *v);
void FUN_44fb00(float *m, DWORD yaw, DWORD pitch, DWORD roll);

extern float g_61c3e8[16];
extern float g_61c468[16];

void Matrix_Set(float *m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
void Matrix_RotationZ(float *m, float degrees);

void Matrix_Transpose(float *out, float *m);
void Matrix_FromRows(float *r0, float *r1, float *r2, float *m);
#endif /* VECMATH_H */
