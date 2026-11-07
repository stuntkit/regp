#ifndef VECMATH_H
#define VECMATH_H

void FUN_44ee00();
void Matrix_Identity(float *m);
void Matrix_Set(float *m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
void Matrix_RotationZ(float *m, float degrees);

extern float g_sinTable[0x2800];
extern float *g_cosTable;
#endif /* VECMATH_H */
