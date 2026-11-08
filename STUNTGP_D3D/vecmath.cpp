#include "vecmath.h"

#include "Game/GameEngine/GameUpdate.h"
#include "Game/GameEngine/RenderState.h"

#include <math.h>
#include <string.h>

// FUNCTION: STUNTGP_D3D 0x44ee00
void FUN_44ee00()
{
}

// FUNCTION: STUNTGP_D3D 0x44ee10
void Matrix_Identity(float *m)
{
    m[0] = 1.0f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[4] = 0.0f;
    m[5] = 1.0f;
    m[6] = 0.0f;
    m[7] = 0.0f;
    m[8] = 0.0f;
    m[9] = 0.0f;
    m[10] = 1.0f;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
}

// FUNCTION: STUNTGP_D3D 0x44ed40
void Vec3_Normalize(float *v)
{
    float len = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    if (len == 0.0f)
    {
        v[0] = v[1] = v[2] = 0.0f;
        return;
    }
    len = 1.0f / (float)sqrt(len);
    v[0] *= len;
    v[1] *= len;
    v[2] *= len;
}

// GLOBAL: STUNTGP_D3D 0x61c3e8
float g_61c3e8[16];

// GLOBAL: STUNTGP_D3D 0x61c428
float g_61c428[16];

// GLOBAL: STUNTGP_D3D 0x61c468
float g_61c468[16];

// FUNCTION: STUNTGP_D3D 0x44f150
void FUN_44f150(float *m, float x, float y, float z)
{
    m[12] += x;
    m[13] += y;
    m[14] += z;
}

// Multiplies m in place by the matrix given row by row.
// FUNCTION: STUNTGP_D3D 0x44f1a0
void Matrix_Multiply(float *m, float b00, float b01, float b02, float b03, float b10, float b11, float b12, float b13,
                     float b20, float b21, float b22, float b23, float b30, float b31, float b32, float b33)
{
    float t[16];
    for (int i = 0; i < 4; i++)
    {
        t[i * 4 + 0] = m[i * 4 + 0] * b00 + m[i * 4 + 1] * b10 + m[i * 4 + 2] * b20 + m[i * 4 + 3] * b30;
        t[i * 4 + 1] = m[i * 4 + 0] * b01 + m[i * 4 + 1] * b11 + m[i * 4 + 2] * b21 + m[i * 4 + 3] * b31;
        t[i * 4 + 2] = m[i * 4 + 0] * b02 + m[i * 4 + 1] * b12 + m[i * 4 + 2] * b22 + m[i * 4 + 3] * b32;
        t[i * 4 + 3] = m[i * 4 + 0] * b03 + m[i * 4 + 1] * b13 + m[i * 4 + 2] * b23 + m[i * 4 + 3] * b33;
        m[i * 4 + 0] = t[i * 4 + 0];
        m[i * 4 + 1] = t[i * 4 + 1];
        m[i * 4 + 2] = t[i * 4 + 2];
        m[i * 4 + 3] = t[i * 4 + 3];
    }
}

// Rotation angle and axis of the 3x3 part of m.
// Multiplies a in place by b.
// FUNCTION: STUNTGP_D3D 0x44f280
void FUN_44f280(float *a, float *b)
{
    float t[16];
    for (int i = 0; i < 4; i++)
    {
        t[i * 4 + 0] = a[i * 4 + 0] * b[0] + a[i * 4 + 1] * b[4] + a[i * 4 + 2] * b[8] + a[i * 4 + 3] * b[12];
        t[i * 4 + 1] = a[i * 4 + 0] * b[1] + a[i * 4 + 1] * b[5] + a[i * 4 + 2] * b[9] + a[i * 4 + 3] * b[13];
        t[i * 4 + 2] = a[i * 4 + 0] * b[2] + a[i * 4 + 1] * b[6] + a[i * 4 + 2] * b[10] + a[i * 4 + 3] * b[14];
        t[i * 4 + 3] = a[i * 4 + 0] * b[3] + a[i * 4 + 1] * b[7] + a[i * 4 + 2] * b[11] + a[i * 4 + 3] * b[15];
        a[i * 4 + 0] = t[i * 4 + 0];
        a[i * 4 + 1] = t[i * 4 + 1];
        a[i * 4 + 2] = t[i * 4 + 2];
        a[i * 4 + 3] = t[i * 4 + 3];
    }
}

// 4x4 product a * b into out. When out aliases an input the result goes to a scratch matrix and is lost.
// FUNCTION: STUNTGP_D3D 0x44f360
void FUN_44f360(float *out, float *a, float *b)
{
    float t[16];
    if (out == a || out == b)
    {
        out = t;
    }
    for (int i = 0; i < 4; i++)
    {
        out[i * 4 + 0] = a[i * 4 + 0] * b[0] + a[i * 4 + 1] * b[4] + a[i * 4 + 2] * b[8] + a[i * 4 + 3] * b[12];
        out[i * 4 + 1] = a[i * 4 + 0] * b[1] + a[i * 4 + 1] * b[5] + a[i * 4 + 2] * b[9] + a[i * 4 + 3] * b[13];
        out[i * 4 + 2] = a[i * 4 + 0] * b[2] + a[i * 4 + 1] * b[6] + a[i * 4 + 2] * b[10] + a[i * 4 + 3] * b[14];
        out[i * 4 + 3] = a[i * 4 + 0] * b[3] + a[i * 4 + 1] * b[7] + a[i * 4 + 2] * b[11] + a[i * 4 + 3] * b[15];
    }
}

// FUNCTION: STUNTGP_D3D 0x44f420
void FUN_44f420(float *m, float *angle, Vec4 *axis)
{
    Vec4 v;
    *angle = acos((m[10] + m[5] + m[0] - 1.0f) * 0.5f);
    float s = sin(*angle) * 2.0f;
    if (s != 0.0f)
    {
        s = 1.0f / s;
    }
    else
    {
        s = 1.0f;
    }
    v.x = (m[9] - m[6]) * s;
    v.y = (m[2] - m[8]) * s;
    v.z = (m[4] - m[1]) * s;
    Vec3_Normalize(&v.x);
    *axis = v;
}

// Builds the current view's perspective projection.
// FUNCTION: STUNTGP_D3D 0x44f4e0
void FUN_44f4e0(float *m)
{
    float w = g_4722d0->fov;
    float n = g_4722d0->unk0b4;
    float f = g_4722d0->unk0b8 * 4096.0f;
    float l = -g_4722d0->unk0bc;
    float r = g_4722d0->unk0bc;
    float b = -g_4722d0->unk0c0;
    float t = g_4722d0->unk0c0;
    Matrix_Identity(m);
    w += w;
    Matrix_Multiply(m, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, (r + l) / w, (t + b) / w, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f);
    Matrix_Multiply(m, w / (r - l), 0.0f, 0.0f, 0.0f, 0.0f, w / (t - b), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f);
    Matrix_Multiply(m, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, f / (f - n), 1.0f, 0.0f, 0.0f,
                    -(f * n) / (f - n), 0.0f);
    g_renderState.unk4c = 1.0f / m[10];
    g_renderState.unk50 = m[14];
}

// FUNCTION: STUNTGP_D3D 0x44f4c0
void FUN_44f4c0()
{
    Matrix_Identity(g_61c3e8);
    FUN_44f4e0(g_61c3e8);
    Matrix_Identity(g_61c468);
}

// Matrix_Multiply3 with b passed by value.
// FUNCTION: STUNTGP_D3D 0x44eeb0
void FUN_44eeb0(float *a, float b00, float b01, float b02, float b03, float b10, float b11, float b12, float b13,
                float b20, float b21, float b22, float b23, float b30, float b31, float b32, float b33)
{
    float t[16];
    for (int i = 0; i < 3; i++)
    {
        t[i * 4 + 0] = a[i * 4 + 0] * b00 + a[i * 4 + 1] * b10 + a[i * 4 + 2] * b20;
        t[i * 4 + 1] = a[i * 4 + 0] * b01 + a[i * 4 + 1] * b11 + a[i * 4 + 2] * b21;
        t[i * 4 + 2] = a[i * 4 + 0] * b02 + a[i * 4 + 1] * b12 + a[i * 4 + 2] * b22;
        a[i * 4 + 0] = t[i * 4 + 0];
        a[i * 4 + 1] = t[i * 4 + 1];
        a[i * 4 + 2] = t[i * 4 + 2];
    }
}

// Multiplies the 3x3 part of a in place by b.
// FUNCTION: STUNTGP_D3D 0x44ef40
void Matrix_Multiply3(float *a, float *b)
{
    float t[16];
    for (int i = 0; i < 3; i++)
    {
        t[i * 4 + 0] = a[i * 4 + 0] * b[0] + a[i * 4 + 1] * b[4] + a[i * 4 + 2] * b[8];
        t[i * 4 + 1] = a[i * 4 + 0] * b[1] + a[i * 4 + 1] * b[5] + a[i * 4 + 2] * b[9];
        t[i * 4 + 2] = a[i * 4 + 0] * b[2] + a[i * 4 + 1] * b[6] + a[i * 4 + 2] * b[10];
        a[i * 4 + 0] = t[i * 4 + 0];
        a[i * 4 + 1] = t[i * 4 + 1];
        a[i * 4 + 2] = t[i * 4 + 2];
    }
}


// Builds a look-at matrix (rows side, up, back) and its transpose for a scene camera.
// FUNCTION: STUNTGP_D3D 0x44fdb0
void FUN_44fdb0(Camera *cam)
{
    Vec4 dir;
    dir.x = cam->pos.x - cam->target.x;
    dir.y = cam->pos.y - cam->target.y;
    dir.z = cam->pos.z - cam->target.z;
    Vec4 up = cam->up;
    Vec3_Normalize(&dir.x);
    if ((float)fabs(dir.x * up.x + dir.y * up.y + dir.z * up.z) > 0.99999f)
    {
        up.z += 1.0f;
        Vec3_Normalize(&up.x);
    }
    float d = dir.x * up.x + dir.y * up.y + dir.z * up.z;
    Vec4 t;
    t.x = d * dir.x;
    t.y = d * dir.y;
    t.z = d * dir.z;
    up.x -= t.x;
    up.y -= t.y;
    up.z -= t.z;
    Vec3_Normalize(&up.x);
    Vec4 side;
    side.x = dir.y * up.z - dir.z * up.y;
    side.y = dir.z * up.x - dir.x * up.z;
    side.z = dir.x * up.y - dir.y * up.x;
    side.x = -side.x;
    side.y = -side.y;
    side.z = -side.z;

    float *m = (float *)g_renderState.unk62e4;
    m[0] = side.x;
    m[1] = side.y;
    m[2] = side.z;
    m[3] = 0.0f;
    m[4] = up.x;
    m[5] = up.y;
    m[6] = up.z;
    m[7] = 0.0f;
    m[8] = dir.x;
    m[9] = dir.y;
    m[10] = dir.z;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    cam->unk44 = (Vec4 *)m;
    m += 16;
    g_renderState.unk62e8++;
    cam->matrix = (Vec4 *)m;
    m[0] = side.x;
    m[1] = up.x;
    m[2] = dir.x;
    m[3] = 0.0f;
    m[4] = side.y;
    m[5] = up.y;
    m[6] = dir.y;
    m[7] = 0.0f;
    m[8] = side.z;
    m[9] = up.z;
    m[10] = dir.z;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    m += 16;
    g_renderState.unk62e8++;
    g_renderState.unk62e4 = (BYTE *)m;
}

// Builds an object's rotation matrix (rows side, up, facing) and its transpose from its frame.
// FUNCTION: STUNTGP_D3D 0x44ff90
void FUN_44ff90(ObjectDef *obj)
{
    Camera *xf = (Camera *)obj->matrix;
    Vec4 dir = xf->target;
    Vec4 up = xf->up;
    if ((float)fabs(dir.x * up.x + dir.y * up.y + dir.z * up.z) > 0.99999f)
    {
        up.z += 1.0f;
        Vec3_Normalize(&up.x);
    }
    float d = dir.x * up.x + dir.y * up.y + dir.z * up.z;
    up.x -= d * dir.x;
    up.y -= d * dir.y;
    up.z -= d * dir.z;
    Vec3_Normalize(&up.x);
    Vec4 side;
    side.x = dir.y * up.z - dir.z * up.y;
    side.y = dir.z * up.x - dir.x * up.z;
    side.z = dir.x * up.y - dir.y * up.x;
    side.x = -side.x;
    side.y = -side.y;
    side.z = -side.z;

    float *m = (float *)g_renderState.unk62e4;
    m[0] = side.x;
    m[1] = side.y;
    m[2] = side.z;
    m[3] = 0.0f;
    m[4] = up.x;
    m[5] = up.y;
    m[6] = up.z;
    m[7] = 0.0f;
    m[8] = dir.x;
    m[9] = dir.y;
    m[10] = dir.z;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    xf->unk40 = (int)m;
    m += 16;
    g_renderState.unk62e8++;
    m[0] = side.x;
    m[1] = up.x;
    m[2] = dir.x;
    m[3] = 0.0f;
    m[4] = side.y;
    m[5] = up.y;
    m[6] = dir.y;
    m[7] = 0.0f;
    m[8] = side.z;
    m[9] = up.z;
    m[10] = dir.z;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    xf->unk44 = (Vec4 *)m;
    m += 16;
    g_renderState.unk62e8++;
    g_renderState.unk62e4 = (BYTE *)m;
}

// Rotation matrices of the current level-of-detail objects; hidden objects get the identity.
// FUNCTION: STUNTGP_D3D 0x450150
void FUN_450150(Scene *scene)
{
    ObjectDef *obj = scene->lods[scene->lod];
    for (DWORD i = 0; i < scene->objectCount; i++, obj++)
    {
        if (!obj->visible)
        {
            Camera *xf = (Camera *)obj->matrix;
            xf->unk40 = (int)g_61c468;
            xf->unk44 = (Vec4 *)g_61c468;
        }
        else
        {
            FUN_44ff90(obj);
        }
    }
}

// Builds the camera's view matrix and its transpose from pos, target, up and the view roll.
// FUNCTION: STUNTGP_D3D 0x450190
void FUN_450190(Camera *cam)
{
    Vec4 up = cam->up;
    up.x = -up.x;
    up.y = -up.y;
    up.z = -up.z;
    Vec4 dir;
    dir.x = cam->target.x - cam->pos.x;
    dir.y = cam->target.y - cam->pos.y;
    dir.z = cam->target.z - cam->pos.z;
    Vec3_Normalize(&dir.x);
    if ((float)fabs(dir.x + up.x) + (float)fabs(dir.y + up.y) + (float)fabs(dir.z + up.z) < 1e-05f)
    {
        up.z += 1.0f;
        Vec3_Normalize(&up.x);
    }
    float d = dir.x * up.x + dir.y * up.y + dir.z * up.z;
    up.x -= d * dir.x;
    up.y -= d * dir.y;
    up.z -= d * dir.z;
    Vec3_Normalize(&up.x);
    Vec4 side;
    side.x = dir.y * up.z - dir.z * up.y;
    side.y = dir.z * up.x - dir.x * up.z;
    side.z = dir.x * up.y - dir.y * up.x;
    Vec3_Normalize(&side.x);
    float rows[16];
    Matrix_FromRows(&side.x, &up.x, &dir.x, rows);
    float rot[16];
    Matrix_RotationZ(rot, g_4722d0->roll);
    Matrix_Multiply3(rot, rows);
    side = *(Vec4 *)&rot[0];
    up = *(Vec4 *)&rot[4];
    dir = *(Vec4 *)&rot[8];

    float *m = (float *)g_renderState.unk62e4;
    cam->matrix = (Vec4 *)m;
    m[0] = side.x;
    m[1] = side.y;
    m[2] = side.z;
    m[3] = 0.0f;
    m[4] = up.x;
    m[5] = up.y;
    m[6] = up.z;
    m[7] = 0.0f;
    m[8] = dir.x;
    m[9] = dir.y;
    m[10] = dir.z;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    m += 16;
    g_renderState.unk62e8++;
    cam->unk44 = (Vec4 *)m;
    m[0] = side.x;
    m[1] = up.x;
    m[2] = dir.x;
    m[3] = 0.0f;
    m[4] = side.y;
    m[5] = up.y;
    m[6] = dir.y;
    m[7] = 0.0f;
    m[8] = side.z;
    m[9] = up.z;
    m[10] = dir.z;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    m += 16;
    g_renderState.unk62e8++;
    g_renderState.unk62e4 = (BYTE *)m;
}

// Re-orthonormalises the rotation rows, keeping the z row's direction.
// FUNCTION: STUNTGP_D3D 0x44f8e0
void FUN_44f8e0(float *m)
{
    Vec4 *rows = (Vec4 *)m;
    Vec4 *rowZ = &rows[2];
    Vec4 z = *rowZ;
    Vec3_Normalize(&z.x);
    Vec4 *rowY = &rows[1];
    Vec4 y = *rowY;
    Vec3_Normalize(&y.x);
    Vec4 x;
    x.x = z.z * y.y - z.y * y.z;
    x.y = z.x * y.z - y.x * z.z;
    x.z = y.x * z.y - z.x * y.y;
    Vec3_Normalize(&x.x);
    y.x = x.z * z.y - x.y * z.z;
    y.y = x.x * z.z - x.z * z.x;
    y.z = x.y * z.x - x.x * z.y;
    Vec3_Normalize(&y.x);
    rows[0] = x;
    *rowY = y;
    *rowZ = z;
}

// GLOBAL: STUNTGP_D3D 0x61c3a4
float g_61c3a4[16];

// FUNCTION: STUNTGP_D3D 0x44fa00
void FUN_44fa00(float *m)
{
    Vec3_Normalize(m);
    Vec3_Normalize(m + 4);
    Vec3_Normalize(m + 8);
}

// FUNCTION: STUNTGP_D3D 0x44fb00
void FUN_44fb00(float *m, DWORD yaw, DWORD pitch, DWORD roll)
{
    yaw &= 0x1fff;
    pitch &= 0x1fff;
    roll &= 0x1fff;
    float cy = g_cosTable[yaw];
    float cp = g_cosTable[pitch];
    float cr = g_cosTable[roll];
    float sy = g_sinTable[yaw];
    float sp = g_sinTable[pitch];
    float sr = g_sinTable[roll];
    m[0] = cr * cp;
    m[1] = sr * cp;
    m[2] = -sp;
    m[3] = 0.0f;
    m[4] = sp * sy * cr - sr * cy;
    m[5] = cr * cy + sp * sy * sr;
    m[6] = sy * cp;
    m[7] = 0.0f;
    m[8] = sp * cy * cr + sr * sy;
    m[9] = sp * cy * sr - sy * cr;
    m[10] = cp * cy;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
}

// Object-to-view matrix: the object's own scale, pivot rotation and offset (multi-object scenes),
// then the scene's, then the view camera's.
// FUNCTION: STUNTGP_D3D 0x44fbd0
void FUN_44fbd0(Scene *scene, ObjectDef *obj, float *m)
{
    Camera *cam = scene->camera;
    Matrix_Identity(m);
    if (scene->objectCount > 1 && obj)
    {
        Camera *xf = (Camera *)obj->matrix;
        FUN_44eeb0(m, xf->scale.x, 0.0f, 0.0f, 0.0f, 0.0f, xf->scale.y, 0.0f, 0.0f, 0.0f, 0.0f, xf->scale.z, 0.0f,
                   0.0f, 0.0f, 0.0f, 1.0f);
        Vec4 *pivot = (Vec4 *)((BYTE *)obj + 0x10);
        float pz = pivot->z;
        float py = pivot->y;
        float px = pivot->x;
        FUN_44f150(m, -px, -py, -pz);
        FUN_44f280(m, (float *)xf->unk40);
        FUN_44f150(m, px, py, pz);
        FUN_44f150(m, xf->pos.x, xf->pos.y, xf->pos.z);
    }
    FUN_44eeb0(m, cam->scale.x, 0.0f, 0.0f, 0.0f, 0.0f, cam->scale.y, 0.0f, 0.0f, 0.0f, 0.0f, cam->scale.z, 0.0f,
               0.0f, 0.0f, 0.0f, 1.0f);
    Vec4 *pivot = (Vec4 *)scene->unk10;
    FUN_44f150(m, pivot->x, pivot->y, pivot->z);
    FUN_44f280(m, (float *)cam->unk44);
    FUN_44f150(m, -pivot->x, -pivot->y, -pivot->z);
    FUN_44f150(m, cam->pos.x - g_4722d0->cam.pos.x, cam->pos.y - g_4722d0->cam.pos.y,
               cam->pos.z - g_4722d0->cam.pos.z);
    FUN_44f280(m, (float *)g_4722d0->cam.unk44);
}

// FUNCTION: STUNTGP_D3D 0x44eb70
void FUN_44eb70(DWORD yaw, DWORD pitch, DWORD roll, float *x, float *y, float *z)
{
    FUN_44fb00(g_61c3a4, yaw, pitch, roll);
    float vx = *x;
    float vy = *y;
    float vz = *z;
    *x = g_61c3a4[0] * vx + g_61c3a4[4] * vy + g_61c3a4[8] * vz;
    *y = g_61c3a4[1] * vx + g_61c3a4[5] * vy + g_61c3a4[9] * vz;
    *z = g_61c3a4[2] * vx + g_61c3a4[6] * vy + g_61c3a4[10] * vz;
}

// Rotates v by the yaw/pitch/roll angles given in degrees.
// FUNCTION: STUNTGP_D3D 0x44ec00
void FUN_44ec00(float *angles, float *v)
{
    FUN_44fb00(g_61c3a4, (DWORD)(angles[0] * (8192.0f / 360.0f)), (DWORD)(angles[1] * (8192.0f / 360.0f)),
               (DWORD)(angles[2] * (8192.0f / 360.0f)));
    float vx = v[0];
    float vy = v[1];
    float vz = v[2];
    v[0] = g_61c3a4[0] * vx + g_61c3a4[4] * vy + g_61c3a4[8] * vz;
    v[1] = g_61c3a4[1] * vx + g_61c3a4[5] * vy + g_61c3a4[9] * vz;
    v[2] = g_61c3a4[2] * vx + g_61c3a4[6] * vy + g_61c3a4[10] * vz;
}

// FUNCTION: STUNTGP_D3D 0x44f0e0
void Matrix_Set(float *m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
    m[0] = m00;
    m[1] = m01;
    m[2] = m02;
    m[3] = m03;
    m[4] = m10;
    m[5] = m11;
    m[6] = m12;
    m[7] = m13;
    m[8] = m20;
    m[9] = m21;
    m[10] = m22;
    m[11] = m23;
    m[12] = m30;
    m[13] = m31;
    m[14] = m32;
    m[15] = m33;
}

// Normalizes v in place and writes its original length.
// FUNCTION: STUNTGP_D3D 0x44eda0
void FUN_44eda0(float *v, float *len)
{
    float l = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    if (l == 0.0f)
    {
        *len = 0.0f;
        v[0] = v[1] = v[2] = 0.0f;
        return;
    }
    l = (float)sqrt(l);
    *len = l;
    l = 1.0f / l;
    v[0] *= l;
    v[1] *= l;
    v[2] *= l;
}

// FUNCTION: STUNTGP_D3D 0x44f640
void Matrix_RotateX(float *m, float degrees)
{
    int i = (int)(degrees * (8192.0f / 360.0f)) & 0x1fff;
    float c = g_cosTable[i];
    float s = g_sinTable[i];
    FUN_44eeb0(m, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, c, s, 0.0f, 0.0f, -s, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

// FUNCTION: STUNTGP_D3D 0x44f6b0
void Matrix_RotateY(float *m, float degrees)
{
    int i = (int)(degrees * (8192.0f / 360.0f)) & 0x1fff;
    float c = g_cosTable[i];
    float s = g_sinTable[i];
    FUN_44eeb0(m, c, 0.0f, -s, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, s, 0.0f, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

// FUNCTION: STUNTGP_D3D 0x44f720
void Matrix_RotateZ(float *m, float degrees)
{
    int i = (int)(degrees * (8192.0f / 360.0f)) & 0x1fff;
    float c = g_cosTable[i];
    float s = g_sinTable[i];
    FUN_44eeb0(m, c, s, 0.0f, 0.0f, -s, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

// FUNCTION: STUNTGP_D3D 0x44f790
void Matrix_RotationX(float *m, float degrees)
{
    int i = (int)(degrees * (8192.0f / 360.0f)) & 0x1fff;
    float c = g_cosTable[i];
    float s = g_sinTable[i];
    Matrix_Set(m, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, c, s, 0.0f, 0.0f, -s, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

// FUNCTION: STUNTGP_D3D 0x44f800
void Matrix_RotationY(float *m, float degrees)
{
    int i = (int)(degrees * (8192.0f / 360.0f)) & 0x1fff;
    float c = g_cosTable[i];
    float s = g_sinTable[i];
    Matrix_Set(m, c, 0.0f, -s, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, s, 0.0f, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

// FUNCTION: STUNTGP_D3D 0x44f870
void Matrix_RotationZ(float *m, float degrees)
{
    int i = (int)(degrees * (8192.0f / 360.0f)) & 0x1fff;
    float c = g_cosTable[i];
    float s = g_sinTable[i];
    Matrix_Set(m, c, s, 0.0f, 0.0f, -s, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

// FUNCTION: STUNTGP_D3D 0x44ee50
void Matrix_Transpose(float *out, float *m)
{
    out[0] = m[0];
    out[1] = m[4];
    out[2] = m[8];
    out[3] = m[12];
    out[4] = m[1];
    out[5] = m[5];
    out[6] = m[9];
    out[7] = m[13];
    out[8] = m[2];
    out[9] = m[6];
    out[10] = m[10];
    out[11] = m[14];
    out[12] = m[3];
    out[13] = m[7];
    out[14] = m[11];
    out[15] = m[15];
}

// 3x3 product a * b into out. When out aliases an input the result goes to a scratch matrix and is lost.
// FUNCTION: STUNTGP_D3D 0x44efd0
void FUN_44efd0(float *out, float *a, float *b)
{
    float t[16];
    if (out == a || out == b)
    {
        out = t;
    }
    for (int i = 0; i < 3; i++)
    {
        out[i * 4 + 0] = a[i * 4 + 0] * b[0] + a[i * 4 + 1] * b[4] + a[i * 4 + 2] * b[8];
        out[i * 4 + 1] = a[i * 4 + 0] * b[1] + a[i * 4 + 1] * b[5] + a[i * 4 + 2] * b[9];
        out[i * 4 + 2] = a[i * 4 + 0] * b[2] + a[i * 4 + 1] * b[6] + a[i * 4 + 2] * b[10];
    }
}

// FUNCTION: STUNTGP_D3D 0x44f050
void Matrix_FromRows(float *r0, float *r1, float *r2, float *m)
{
    m[0] = 0.0f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[4] = 0.0f;
    m[5] = 0.0f;
    m[6] = 0.0f;
    m[7] = 0.0f;
    m[8] = 0.0f;
    m[9] = 0.0f;
    m[10] = 0.0f;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    memcpy(m, r0, 16);
    m[4] = r1[0];
    m[5] = r1[1];
    m[6] = r1[2];
    m[7] = r1[3];
    m[8] = r2[0];
    m[9] = r2[1];
    m[10] = r2[2];
    m[11] = r2[3];
}

// FUNCTION: STUNTGP_D3D 0x4516f0
void FUN_4516f0()
{
}
