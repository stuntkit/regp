#include "GameUpdate.h"

#include <math.h>

#include "../../vecmath.h"
#include "GameSetup.h"
#include "RenderState.h"

void FUN_402ab0(float fov);
void FUN_403310(float fov);
void FUN_403770(Car *car);
void FUN_428520(CameraPath *path, Vec4 *out, float t);
void FUN_4028f0(CameraPreset *preset, int mode);

extern CameraPreset g_4722d8[32];

extern BYTE g_62d480[256];
extern Vec4 g_482688;
extern float g_60f010;

// GLOBAL: STUNTGP_D3D 0x499f8c
float g_499f8c;

// GLOBAL: STUNTGP_D3D 0x4980c0
CameraSweep g_cameraSweep;

// FUNCTION: STUNTGP_D3D 0x403180
void FUN_403180(float delta)
{
    Car *car = g_4722d0->data;
    car->unk22fc += delta;
    if (car->unk22fc > 10000.0f)
    {
        car->unk22fc = 10000.0f;
    }
    else if (car->unk22fc < 500.0f)
    {
        car->unk22fc = 500.0f;
    }
}

// Polygon list offset of the octree leaf holding g_cameraSweep.unk14, 0 when not found yet.
// GLOBAL: STUNTGP_D3D 0x49823c
int g_49823c;

// GLOBAL: STUNTGP_D3D 0x498240
int g_498240;

// Copies the handling set of each human player's race entry onto the car.
// FUNCTION: STUNTGP_D3D 0x41f5d0
void FUN_41f5d0()
{
    for (int i = 0; i < 6; i++)
    {
        RaceEntry *e = &g_60d730.entries[i];
        if (g_60d730.entries[i].type == 2 && g_60d730.entries[i].unk034 == 1)
        {
            Car *car = &g_49a1f8[i];
            car->unk220 = e->unk038;
            car->unk224 = e->unk040;
            car->unk228 = e->unk044;
            car->unk22c = e->unk048;
            car->unk220 = e->unk03c + car->unk220;
            car->unk248 = e->unk0a8;
            car->unk468 = e->unk04c;
            car->unk460 = e->unk050;
            car->unk464 = e->unk054;
            car->unk045c = e->unk058;
            car->unk46c = e->unk05c;
            car->unk1f0c = e->unk060;
            car->unkf78 = e->unk0e4;
            car->unk1184 = e->unk0ec;
            car->unkf80 = e->unk0e8;
            car->unkc70 = e->unk068;
            car->unkc74 = e->unk06c + 1;
            car->unkca0 = e->unk070;
            car->unkca4 = e->unk074;
            car->unkca8 = e->unk078;
            car->unkc7c[0] = e->unk07c;
            car->unkc7c[1] = -2.06f;
            car->unkc7c[2] = 2.0f;
            for (unsigned int j = 0; j < e->unk06c; j++)
            {
                car->unkc7c[3 + j] = e->unk080[j];
            }
            car->unkd5c = e->unk0a0;
            car->unkd58 = e->unk0a4;
            int k;
            for (k = 0; k < 4; k++)
            {
                car->unkcb8[k].z = e->unk0c8;
                car->unkcb8[k].w = e->unk0cc;
            }
            for (k = 0; k < 4; k++)
            {
                car->suspension[k].maxTravelIn = e->unk0ac;
                car->suspension[k].maxDampingIn = e->unk0b0;
                car->suspension[k].maxStiffnessIn = e->unk0b4;
                car->suspension[k].maxTravelOut = e->unk0b8;
                car->suspension[k].maxDampingOut = e->unk0bc;
                car->suspension[k].maxStiffnessOut = e->unk0c0;
            }
            car->unkcac = e->unk0d0;
            car->unkcb0 = e->unk0d4;
            car->unk24c = e->unk0d8;
            car->unk254 = e->unk0dc;
            car->unk250 = e->unk0e0;
            car->unkd60 = e->unk0f0;
            car->unkd64 = e->unk0f4;
            car->unkd68 = e->unk0f8;
            car->unkd6c = e->unk0fc;
            car->unkf70 = e->unk100;
            car->unkf74 = e->unk104;
            car->unk1b94 = e->unk108;
            car->unk1b98 = e->unk10c;
            car->unk1b9c = e->unk110;
            car->unk1ba0 = e->unk114;
            car->unk1ba4 = e->unk118;
            car->race.unk80[1] = e->unk11c[1];
            car->race.unk80[2] = e->unk11c[2];
            car->race.unk80[3] = e->unk11c[3];
            car->race.unk80[0] = e->unk11c[0];
            car->race.unk80[4] = e->unk11c[4];
            car->race.unk80[5] = e->unk11c[5];
            car->race.unk80[6] = e->unk11c[6];
        }
    }
}

Vec4 *FUN_420b20(Vec4 *out, WORD *idx);

// 1 when every vertex of the polygon lies within 0.1 of its plane.
// FUNCTION: STUNTGP_D3D 0x41f870
int FUN_41f870(TrackPoly *poly)
{
    WORD *idx = g_renderState.unk7f98->indices + poly->firstIndex;
    Vec4 *a = g_renderState.unk7f98->vertices + *idx;
    Vec4 n;
    FUN_420b20(&n, idx);
    int flat = 1;
    unsigned int count = poly->vertexCount;
    for (unsigned int i = 0; i < count; i++)
    {
        Vec4 *b = &g_renderState.unk7f98->vertices[*idx];
        Vec4 d;
        d.x = b->x - a->x;
        d.y = b->y - a->y;
        d.z = b->z - a->z;
        if ((float)fabs(n.x * d.x + n.y * d.y + n.z * d.z) > 0.1f)
        {
            flat = 0;
        }
        idx++;
    }
    return flat;
}

// FUNCTION: STUNTGP_D3D 0x41f920
void FUN_41f920(TrackPoly *poly, float dist)
{
    Vec4 dir = g_cameraSweep.unk58;
    Vec3_Normalize(&dir.x);
    if (poly)
    {
        FUN_41f870(poly);
    }
}

// Same test as FUN_420690.
// FUNCTION: STUNTGP_D3D 0x41f970
int FUN_41f970(TrackPoly *poly, Vec4 *p)
{
    WORD *idx = g_renderState.unk7f98->indices + poly->firstIndex;
    Vec4 *b = g_renderState.unk7f98->vertices + *idx;
    unsigned int n = poly->vertexCount;
    for (unsigned int i = 0; i < n;)
    {
        i++;
        Vec4 *a = b;
        b = &g_renderState.unk7f98->vertices[idx[i % n]];
        Vec4 e;
        e.x = b->x - a->x;
        e.y = b->y - a->y;
        e.z = b->z - a->z;
        Vec4 side;
        side.x = e.y * g_cameraSweep.unka0->z - e.z * g_cameraSweep.unka0->y;
        side.y = e.z * g_cameraSweep.unka0->x - e.x * g_cameraSweep.unka0->z;
        side.z = e.x * g_cameraSweep.unka0->y - e.y * g_cameraSweep.unka0->x;
        float d;
        FUN_44eda0(&side.x, &d);
        Vec4 q;
        q.x = p->x - a->x;
        q.y = p->y - a->y;
        q.z = p->z - a->z;
        d = q.x * side.x + q.y * side.y + q.z * side.z;
        if (d > 0.0f)
        {
            return 0;
        }
    }
    return 1;
}

int FUN_420690(TrackPoly *poly, Vec4 *p);

// 1 when p lies within the sphere radius of the plane and inside the polygon.
// FUNCTION: STUNTGP_D3D 0x41fa80
int FUN_41fa80(TrackPoly *poly, Vec4 *p)
{
    Vec4 v;
    v.x = p->x - g_cameraSweep.unk9c->x;
    v.y = p->y - g_cameraSweep.unk9c->y;
    v.z = p->z - g_cameraSweep.unk9c->z;
    float d = v.x * g_cameraSweep.unka0->x + v.y * g_cameraSweep.unka0->y + v.z * g_cameraSweep.unka0->z;
    float ad = (float)fabs(d);
    if (ad < g_cameraSweep.unk94 - 0.01f && FUN_420690(poly, p) == 1)
    {
        if (ad < g_cameraSweep.unk94 - 0.01f)
        {
            FUN_41f920(poly, d);
        }
        return 1;
    }
    return 0;
}

// Pushes the camera away from every polygon edge inside the sphere.
// FUNCTION: STUNTGP_D3D 0x41fb10
int FUN_41fb10(TrackPoly *poly, Vec4 *p)
{
    WORD *idx = g_renderState.unk7f98->indices + poly->firstIndex;
    WORD *cur = idx;
    for (unsigned int i = 0; i < poly->vertexCount; cur++)
    {
        Vec4 *a = &g_renderState.unk7f98->vertices[*cur];
        i++;
        Vec4 *b = &g_renderState.unk7f98->vertices[idx[i % poly->vertexCount]];
        Vec4 e;
        e.x = b->x - a->x;
        e.y = b->y - a->y;
        e.z = b->z - a->z;
        float len;
        FUN_44eda0(&e.x, &len);
        Vec4 q;
        q.x = p->x - a->x;
        q.y = p->y - a->y;
        q.z = p->z - a->z;
        float t = q.x * e.x + q.y * e.y + q.z * e.z;
        if (t >= 0.0f && t <= len)
        {
            Vec4 s;
            s.x = t * e.x;
            s.y = t * e.y;
            s.z = t * e.z;
            q.x = q.x - s.x;
            q.y = q.y - s.y;
            q.z = q.z - s.z;
            t = (float)sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
            if (t < g_cameraSweep.unk94 - 0.01f)
            {
                FUN_41f920(poly, t);
            }
        }
    }
    return 0;
}

// Pushes the camera away from every polygon vertex inside the sphere.
// FUNCTION: STUNTGP_D3D 0x41fc70
int FUN_41fc70(TrackPoly *poly, Vec4 *p)
{
    WORD *idx = g_renderState.unk7f98->indices + poly->firstIndex;
    for (unsigned int i = 0; i < poly->vertexCount; i++, idx++)
    {
        Vec4 *v = &g_renderState.unk7f98->vertices[*idx];
        Vec4 d;
        d.x = v->x - p->x;
        d.y = v->y - p->y;
        d.z = v->z - p->z;
        float dist = (float)sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
        if (dist < g_cameraSweep.unk94 - 0.01f)
        {
            FUN_41f920(poly, dist);
        }
    }
    return 0;
}

// GLOBAL: STUNTGP_D3D 0x571448
Vec4 g_571448;

// FUNCTION: STUNTGP_D3D 0x41fd20
int FUN_41fd20(TrackPoly *poly)
{
    WORD *idx = g_renderState.unk7f98->indices + poly->firstIndex;
    g_cameraSweep.unka0 = g_renderState.unk7f98->planes + poly->plane;
    g_cameraSweep.unk9c = g_renderState.unk7f98->vertices + *idx;
    FUN_420b20(&g_571448, idx);
    g_cameraSweep.unka0 = &g_571448;
    FUN_41fc70(poly, &g_cameraSweep.unk04);
    FUN_41fb10(poly, &g_cameraSweep.unk04);
    FUN_41fa80(poly, &g_cameraSweep.unk04);
    return 0;
}

// Tests the sweep sphere against every polygon of a -1 terminated list.
// FUNCTION: STUNTGP_D3D 0x41fda0
void FUN_41fda0(WORD *list)
{
    int hit = 0;
    while (*list != 0xffff)
    {
        hit |= FUN_41fd20(&g_renderState.unk7f98->polys[*list++]);
    }
}

// FUNCTION: STUNTGP_D3D 0x41fde0
int FUN_41fde0(Car *car)
{
    Body *body = &car->body;
    if (body == g_cameraSweep.unk10c)
    {
        return 0;
    }
    for (DWORD i = 0; i < body->numPoints; i++)
    {
        Vec4 d;
        d.x = body->points[i].prev.x - g_cameraSweep.unk04.x;
        d.y = body->points[i].prev.y - g_cameraSweep.unk04.y;
        d.z = body->points[i].prev.z - g_cameraSweep.unk04.z;
        float dist = (float)sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
        if (dist < g_cameraSweep.unk94 + body->points[i].radius - 1.0f)
        {
            FUN_41f920(NULL, dist);
        }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x41fe80
int FUN_41fe80()
{
    for (int i = 0; i < 6; i++)
    {
        Car *car = &g_49a1f8[i];
        if (car->active == 1)
        {
            FUN_41fde0(car);
        }
    }
    return 0;
}

// GLOBAL: STUNTGP_D3D 0x571458
CameraSweep g_571458;

void FUN_420f80();

// Runs the car test for a sphere at p, then restores the sweep state.
// FUNCTION: STUNTGP_D3D 0x41feb0
void FUN_41feb0(Vec4 p)
{
    g_571458 = g_cameraSweep;
    g_cameraSweep.unk04 = p;
    g_cameraSweep.unk14 = p;
    FUN_420f80();
    FUN_41fe80();
    g_cameraSweep = g_571458;
}

// 1 when the point lies inside every edge of the polygon, seen along the g_cameraSweep.unka0 normal.
// FUNCTION: STUNTGP_D3D 0x420690
int FUN_420690(TrackPoly *poly, Vec4 *p)
{
    WORD *idx = g_renderState.unk7f98->indices + poly->firstIndex;
    Vec4 *b = g_renderState.unk7f98->vertices + *idx;
    unsigned int n = poly->vertexCount;
    for (unsigned int i = 0; i < n;)
    {
        i++;
        Vec4 *a = b;
        b = &g_renderState.unk7f98->vertices[idx[i % n]];
        Vec4 e;
        e.x = b->x - a->x;
        e.y = b->y - a->y;
        e.z = b->z - a->z;
        Vec4 side;
        side.x = e.y * g_cameraSweep.unka0->z - e.z * g_cameraSweep.unka0->y;
        side.y = e.z * g_cameraSweep.unka0->x - e.x * g_cameraSweep.unka0->z;
        side.z = e.x * g_cameraSweep.unka0->y - e.y * g_cameraSweep.unka0->x;
        float d;
        FUN_44eda0(&side.x, &d);
        Vec4 q;
        q.x = p->x - a->x;
        q.y = p->y - a->y;
        q.z = p->z - a->z;
        d = q.x * side.x + q.y * side.y + q.z * side.z;
        if (d > 0.0f)
        {
            return 0;
        }
    }
    return 1;
}

// 0 when both sweep points are further than the sphere radius from the plane.
// FUNCTION: STUNTGP_D3D 0x420a70
int FUN_420a70()
{
    Vec4 d;
    d.x = g_cameraSweep.unk14.x - g_cameraSweep.unk9c->x;
    d.y = g_cameraSweep.unk14.y - g_cameraSweep.unk9c->y;
    d.z = g_cameraSweep.unk14.z - g_cameraSweep.unk9c->z;
    g_cameraSweep.unka8 = d.y * g_cameraSweep.unka0->y + (d.x * g_cameraSweep.unka0->x + d.z * g_cameraSweep.unka0->z);
    d.x = g_cameraSweep.unk04.x - g_cameraSweep.unk9c->x;
    d.y = g_cameraSweep.unk04.y - g_cameraSweep.unk9c->y;
    d.z = g_cameraSweep.unk04.z - g_cameraSweep.unk9c->z;
    g_cameraSweep.unkac = d.y * g_cameraSweep.unka0->y + (d.x * g_cameraSweep.unka0->x + d.z * g_cameraSweep.unka0->z);
    float r = g_cameraSweep.unk94 + 0.25f;
    if ((float)fabs(g_cameraSweep.unka8) > r && (float)fabs(g_cameraSweep.unkac) > r)
    {
        return 0;
    }
    return 1;
}

// Unit normal of a track polygon; falls back to the next edge when the first two are parallel.
// FUNCTION: STUNTGP_D3D 0x420b20
Vec4 *FUN_420b20(Vec4 *out, WORD *idx)
{
    TrackOctree *tree = g_renderState.unk7f98;
    Vec4 a;
    a.x = tree->vertices[idx[1]].x - tree->vertices[idx[0]].x;
    a.y = tree->vertices[idx[1]].y - tree->vertices[idx[0]].y;
    a.z = tree->vertices[idx[1]].z - tree->vertices[idx[0]].z;
    Vec4 b;
    b.x = tree->vertices[idx[2]].x - tree->vertices[idx[1]].x;
    b.y = tree->vertices[idx[2]].y - tree->vertices[idx[1]].y;
    b.z = tree->vertices[idx[2]].z - tree->vertices[idx[1]].z;
    Vec4 n;
    n.x = b.z * a.y - b.y * a.z;
    n.y = b.x * a.z - b.z * a.x;
    n.z = b.y * a.x - b.x * a.y;
    if (n.x * n.x + n.y * n.y + n.z * n.z < 0.0001f)
    {
        b.x = tree->vertices[idx[3]].x - tree->vertices[idx[2]].x;
        b.y = tree->vertices[idx[3]].y - tree->vertices[idx[2]].y;
        b.z = tree->vertices[idx[3]].z - tree->vertices[idx[2]].z;
        n.x = b.z * a.y - b.y * a.z;
        n.y = b.x * a.z - b.z * a.x;
        n.z = b.y * a.x - b.x * a.y;
    }
    Vec3_Normalize(&n.x);
    *out = n;
    return out;
}

// FUNCTION: STUNTGP_D3D 0x420f00
void FUN_420f00(OctNode *node)
{
    if (g_49823c == 0)
    {
        TrackOctree *tree = g_renderState.unk7f98;
        for (;;)
        {
            int octant = 0;
            if (g_cameraSweep.unk14.x >= node->x)
            {
                octant = 1;
            }
            if (g_cameraSweep.unk14.y <= node->y)
            {
                octant |= 4;
            }
            if (g_cameraSweep.unk14.z <= node->z)
            {
                octant |= 2;
            }
            if (node->children[octant] == 0)
            {
                g_49823c = node->leaves[octant];
                return;
            }
            node = &tree->roots[0].root[node->children[octant]];
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x420f80
void FUN_420f80()
{
    TrackOctree *tree = g_renderState.unk7f98;
    g_49823c = 0;
    g_498240 = 0;
    while (g_cameraSweep.unk94 > tree->roots[g_498240].key)
    {
        g_498240++;
        if (g_498240 == 1)
        {
            FUN_420f00(tree->roots[g_498240].root);
            return;
        }
    }
    FUN_420f00(tree->roots[g_498240].root);
}

// STUB: STUNTGP_D3D 0x4215b0
int FUN_4215b0()
{
    return 0;
}

// True when two cars are close enough, given their speeds, to possibly touch.
// FUNCTION: STUNTGP_D3D 0x421830
int FUN_421830(Car *a, Car *b)
{
    Vec4 d;
    d.x = a->posX - b->posX;
    d.y = a->posY - b->posY;
    d.z = a->posZ - b->posZ;
    float r = a->body.radius + b->body.radius;
    float bz;
    float by;
    float bx;
    float az;
    float ay;
    float ax;
    az = a->unk1c8c.z;
    ay = a->unk1c8c.y;
    ax = a->unk1c8c.x;
    bz = b->unk1c8c.z;
    by = b->unk1c8c.y;
    bx = b->unk1c8c.x;
    if (d.x * d.x + d.y * d.y + d.z * d.z < r * r + (ax * ax + ay * ay + az * az) + (bx * bx + by * by + bz * bz))
    {
        return 1;
    }
    return 0;
}

// GLOBAL: STUNTGP_D3D 0x49a1f4
Car *g_49a1f4;

// Finds another active car within 300 units of the current car.
// FUNCTION: STUNTGP_D3D 0x421b80
int FUN_421b80()
{
    if (g_60f2b0 != 4)
    {
        Car *self = g_4d5bb8;
        g_49a1f4 = NULL;
        Car *car = g_49a1f8;
        for (unsigned int i = 0; i < 6; car++, i++)
        {
            if (car != self && car->active == 1)
            {
                Vec4 d;
                d.x = self->unk1bbc.x - car->unk1bbc.x;
                d.y = self->unk1bbc.y - car->unk1bbc.y;
                d.z = self->unk1bbc.z - car->unk1bbc.z;
                if (d.x * d.x + d.y * d.y + d.z * d.z < 90000.0f)
                {
                    if (car->unk7640 == 0)
                    {
                        g_49a1f4 = car;
                        return 1;
                    }
                    if (car->unk7640 < 10)
                    {
                        car->unk7640 += 60;
                    }
                }
            }
        }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x421c30
void FUN_421c30(float bounce)
{
    Vec4 push;
    float d = (g_cameraSweep.unk28.x * g_cameraSweep.unkd8.x + g_cameraSweep.unk28.y * g_cameraSweep.unkd8.y +
               g_cameraSweep.unk28.z * g_cameraSweep.unkd8.z) *
              (2.0f - (1.0f - bounce));
    push.x = g_cameraSweep.unkd8.x * d;
    push.y = g_cameraSweep.unkd8.y * d;
    push.z = g_cameraSweep.unkd8.z * d;
    g_cameraSweep.unk28.x -= push.x;
    g_cameraSweep.unk28.y -= push.y;
    g_cameraSweep.unk28.z -= push.z;
}

// Moves a body point to its new world position, keeping the old one.
// FUNCTION: STUNTGP_D3D 0x421cc0
void FUN_421cc0(Body *body, int i)
{
    body->points[i].prev = body->points[i].world;
    Vec4 l = body->points[i].local;
    Vec4 w;
    w.x = l.x * body->mat0[0] + l.y * body->mat0[4] + l.z * body->mat0[8];
    w.y = l.x * body->mat0[1] + l.y * body->mat0[5] + l.z * body->mat0[9];
    w.z = l.x * body->mat0[2] + l.y * body->mat0[6] + l.z * body->mat0[10];
    w.x += body->pos.x;
    w.y += body->pos.y;
    w.z += body->pos.z;
    body->points[i].world = w;
}

// Velocity of a body point: the rotation step applied to its offset, plus the body velocity.
// FUNCTION: STUNTGP_D3D 0x421d90
void FUN_421d90(Body *body, int i)
{
    Vec4 d;
    d.x = body->points[i].world.x - body->pos.x;
    d.y = body->points[i].world.y - body->pos.y;
    d.z = body->points[i].world.z - body->pos.z;
    Vec4 r;
    r.x = d.x * body->mat1[0] + d.y * body->mat1[4] + d.z * body->mat1[8];
    r.y = d.x * body->mat1[1] + d.y * body->mat1[5] + d.z * body->mat1[9];
    r.z = d.x * body->mat1[2] + d.y * body->mat1[6] + d.z * body->mat1[10];
    r.x -= d.x;
    r.y -= d.y;
    r.z -= d.z;
    r.x += body->vel[0];
    r.y += body->vel[1];
    r.z += body->vel[2];
    body->points[i].unk30 = r;
}

// FUNCTION: STUNTGP_D3D 0x4031e0
void FUN_4031e0(float delta)
{
    Car *car = g_4722d0->data;
    car->unk22f0 += delta;
    if (car->unk22f0 < 0.0f)
    {
        car->unk22f0 += 360.0f;
    }
    else if (car->unk22f0 >= 360.0f)
    {
        car->unk22f0 -= 360.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x403240
void FUN_403240(float delta)
{
    Car *car = g_4722d0->data;
    car->unk22ec += delta;
    if (car->unk22ec < 0.0f)
    {
        car->unk22ec += 360.0f;
    }
    else if (car->unk22ec > 360.0f)
    {
        car->unk22ec -= 360.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x4032a0
void FUN_4032a0()
{
    Vec4 offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = g_4722d0->data->unk22fc;
    FUN_44ec00(&g_4722d0->data->unk22ec, &offset.x);
    g_4722d0->data->camOffset = offset;
}

// FUNCTION: STUNTGP_D3D 0x403340
void FUN_403340()
{
    g_4722d0->cam.pos.x -= g_4722d0->data->unk2318[0];
    g_4722d0->cam.pos.y -= g_4722d0->data->unk2318[1];
    g_4722d0->cam.pos.z -= g_4722d0->data->unk2318[2];
    g_4722d0->cam.target.x -= g_4722d0->data->unk2318[0];
    g_4722d0->cam.target.y -= g_4722d0->data->unk2318[1];
    g_4722d0->cam.target.z -= g_4722d0->data->unk2318[2];
    g_4722d0->cam.pos.x = g_4722d0->data->unk2308[0] + g_4722d0->cam.pos.x;
    g_4722d0->cam.pos.y = g_4722d0->data->unk2308[1] + g_4722d0->cam.pos.y;
    g_4722d0->cam.pos.z = g_4722d0->data->unk2308[2] + g_4722d0->cam.pos.z;
    g_4722d0->cam.target.x = g_4722d0->data->unk2308[0] + g_4722d0->cam.target.x;
    g_4722d0->cam.target.y = g_4722d0->data->unk2308[1] + g_4722d0->cam.target.y;
    g_4722d0->cam.target.z = g_4722d0->data->unk2308[2] + g_4722d0->cam.target.z;
}

// FUNCTION: STUNTGP_D3D 0x403420
void FUN_403420()
{
    g_4722d0->roll = (g_4722d0->roll - (g_4722d0->velX * g_4722d0->axisX.x + g_4722d0->velY * g_4722d0->axisX.y +
                                        g_4722d0->velZ * g_4722d0->axisX.z) *
                                           0.25f) *
                     0.5f;
}

// FUNCTION: STUNTGP_D3D 0x403460
void FUN_403460()
{
    if (g_4722d0->camMode != 6)
    {
        Car *car = g_4722d0->data;
        float dx = g_4722d0->cam.pos.x - car->posX;
        float dy = g_4722d0->cam.pos.y - car->posY;
        float dz = g_4722d0->cam.pos.z - car->posZ;
        if (dx * dx + dy * dy + dz * dz > 6250000.0f)
        {
            g_4722d0->unk1a4 = 600;
        }
        if (g_4722d0->unk1a4)
        {
            g_4722d0->cam.pos.x = g_4722d0->velX + g_4722d0->cam.pos.x;
            g_4722d0->cam.pos.y = g_4722d0->velY + g_4722d0->cam.pos.y;
            g_4722d0->cam.pos.z = g_4722d0->velZ + g_4722d0->cam.pos.z;
            g_4722d0->unk1a4--;
            return;
        }
        g_cameraSweep.unk04 = g_4722d0->cam.pos;
        g_cameraSweep.unk00 = 1.0f;
        g_cameraSweep.unk94 = 125.0f;
        g_cameraSweep.unk98 = 15625.0f;
        g_cameraSweep.unk90 = 1.0f;
        g_cameraSweep.unk28 = *(Vec4 *)&g_4722d0->velX;
        g_cameraSweep.unk8c = (float)sqrt(g_cameraSweep.unk28.x * g_cameraSweep.unk28.x +
                                          g_cameraSweep.unk28.y * g_cameraSweep.unk28.y +
                                          g_cameraSweep.unk28.z * g_cameraSweep.unk28.z);
        unsigned int i = 0;
        int hit;
        do
        {
            hit = FUN_4215b0();
            if (hit == 1)
            {
                FUN_421c30(0.01f);
            }
        } while (hit == 1 && i++ < 32);
        g_4722d0->cam.pos = g_cameraSweep.unk14;
    }
}

// Billboard at the camera position.
// FUNCTION: STUNTGP_D3D 0x4035e0
void FUN_4035e0()
{
    Billboard billboard = g_486538;
    billboard.unk00 = 0x58;
    billboard.texture = 0;
    billboard.pos = g_4722d0->cam.pos;
    FUN_434590(&billboard);
}

// FUNCTION: STUNTGP_D3D 0x403650
void FUN_403650(int step)
{
    if ((float)g_4722d0->unk1bc < 30.0f)
    {
        g_4722d0->unk1bc += step;
    }
}

// FUNCTION: STUNTGP_D3D 0x403bc0
void FUN_403bc0()
{
    if (g_4722d0->camMode < 10)
    {
        g_4722d0->unk1c0 = 0.0f;
        float speed = (float)sqrt(g_4722d0->data->unk1c8c.x * g_4722d0->data->unk1c8c.x +
                                  g_4722d0->data->unk1c8c.y * g_4722d0->data->unk1c8c.y +
                                  g_4722d0->data->unk1c8c.z * g_4722d0->data->unk1c8c.z) -
                      83.333336f;
        if (speed < 0.0f)
        {
            speed = 0.0f;
        }
        else
        {
            speed *= 0.023999998f;
            if (speed > 1.0f)
            {
                speed = 1.0f;
            }
            g_4722d0->unk1c0 = speed * 75.0f;
            speed *= 0.5f;
        }
        FUN_403310(2.09f - speed);
    }
}

void FUN_405370(float *pos, CameraPath *path, int *index, float *distance);
void FUN_4288d0(CameraPath *path, Vec4 *out, float dist);

// Camera path tracking for the current slot.
// GLOBAL: STUNTGP_D3D 0x499f78
Vec4 g_499f78;

// GLOBAL: STUNTGP_D3D 0x499f98
int g_499f98;

// GLOBAL: STUNTGP_D3D 0x499f9c
float g_499f9c;

// GLOBAL: STUNTGP_D3D 0x499fa0
float g_499fa0;

// Shake builds up while the camera strays from the camera path and the wheels are slipping.
// FUNCTION: STUNTGP_D3D 0x403c80
void FUN_403c80()
{
    FUN_405370(&g_4722d0->cam.pos.x, g_4722d0->path, &g_499f98, &g_499f9c);
    g_499fa0 = g_499f9c * g_4722d0->path->unk18 * 0.01f;
    FUN_4288d0(g_4722d0->path, &g_499f78, g_499fa0);
    Vec4 ahead;
    FUN_4288d0(g_4722d0->path, &ahead, g_499fa0 + 5000.0f);
    Vec4 d;
    d.x = ahead.x - g_499f78.x;
    d.y = ahead.y - g_499f78.y;
    d.z = ahead.z - g_499f78.z;
    Vec4 n;
    n.x = g_482688.z * d.y - g_482688.y * d.z;
    n.y = g_482688.x * d.z - g_482688.z * d.x;
    n.z = g_482688.y * d.x - g_482688.x * d.y;
    Vec3_Normalize(&n.x);
    Vec4 e;
    e.x = g_499f78.x - g_4722d0->cam.pos.x;
    e.y = g_499f78.y - g_4722d0->cam.pos.y;
    e.z = g_499f78.z - g_4722d0->cam.pos.z;
    float off = e.x * n.x + e.y * n.y + e.z * n.z;
    g_4722d0->unk1c4 *= 0.97f;
    off = (float)fabs(off) - 1300.0f;
    if (off >= 0.0f)
    {
        off *= 0.0025f;
        if (off > 1.0f)
        {
            off = 1.0f;
        }
        off = off * off * 5000.0f;
        float slip = 0.0f;
        for (int i = 0; i < 4; i++)
        {
            slip += g_4722d0->data->wheels[i].unk30;
        }
        slip = slip * 0.25f - 10.0f;
        if (slip < 0.0f)
        {
            slip = 0.0f;
        }
        else
        {
            slip *= 0.02f;
            if (slip > 1.0f)
            {
                slip = 1.0f;
            }
        }
        g_4722d0->unk1c4 = off * slip * 0.05f + g_4722d0->unk1c4;
        if (g_4722d0->unk1c4 > 400.0f)
        {
            g_4722d0->unk1c4 = 400.0f;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x403e80
void FUN_403e80()
{
    float fov;
    FUN_4031e0(0.5f);
    if ((float)fabs(g_4722d0->fov - 1.25f) > 0.02f)
    {
        fov = g_4722d0->fov;
        if (fov > 1.25f)
        {
            fov -= 0.01f;
        }
        else
        {
            fov += 0.01f;
        }
        FUN_402ab0(fov);
    }
    Car *car = g_4722d0->data;
    if (car->unk22ec > 6.0f)
    {
        car->unk22ec -= 0.1f;
    }
    if (car->unk22fc > 500.0f)
    {
        car->unk22fc -= 5.0f;
    }
}

extern int g_60f020;
extern int g_576be0;

void FUN_40d200(Car *car);
void FUN_40d280(Car *car);
void FUN_40d300(Car *car);
void FUN_40d380(Car *car);

// FUNCTION: STUNTGP_D3D 0x404310
void FUN_404310(Car *car)
{
    int mode = g_60f020;
    if (g_576be0)
    {
        mode = 1;
    }
    switch (mode)
    {
    case 1:
        FUN_40d280(car);
        break;
    case 2:
        FUN_40d200(car);
        break;
    case 3:
        FUN_40d300(car);
        break;
    case 4:
        FUN_40d380(car);
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x404360
void FUN_404360()
{
    Car *car = g_4d5bb8;
    if (car->unk2304)
    {
        int index = car->unk24ac + 1;
        Car *next = index < (int)g_612948.unk03c8 ? g_612948.unk03cc[index] : car;
        float gap = (car->unk23b0 - next->unk23b0) * g_60f010 * 0.01f;
        if (gap > 0.0f && gap < 5000.0f && next->unk1cf0 + 8.333333f > car->unk1cf0 && car->unk1cf0 > 0.41666666f)
        {
            car->unk22fc += 10.0f;
        }
        else
        {
            car->unk22fc -= 5.0f;
        }
        if (car->unk22fc < 600.0f)
        {
            car->unk22fc = 600.0f;
        }
        else if (car->unk22fc > 2500.0f)
        {
            car->unk22fc = 2500.0f;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x404450
void FUN_404450()
{
    Vec4 right;
    Vec4 fwd;
    Vec4 side;
    Vec4 off;
    Vec4 tmp;
    Vec4 v;
    float dot;
    float h;
    float k;
    Car *car;

    g_4722d0->prevTarget = g_4722d0->cam.target;
    switch (g_4722d0->camMode)
    {
    case 4:
        FUN_403770(g_4722d0->data);
        FUN_403460();
        FUN_403340();
        return;
    case 5:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        FUN_404360();
        FUN_403420();
        if (g_4722d0->camMode == 16)
        {
            FUN_403e80();
        }
        FUN_403bc0();
        FUN_4032a0();

        tmp.x = g_4722d0->data->unk22dc + g_4722d0->data->posX;
        tmp.y = g_4722d0->data->unk22e0 + g_4722d0->data->posY;
        tmp.z = g_4722d0->data->unk22e4 + g_4722d0->data->posZ;
        v.x = tmp.x - g_4722d0->cam.target.x;
        v.y = tmp.y - g_4722d0->cam.target.y;
        v.z = tmp.z - g_4722d0->cam.target.z;
        v.x *= 0.33333334f;
        v.y *= 0.33333334f;
        v.z *= 0.33333334f;
        g_4722d0->cam.target.x += v.x;
        g_4722d0->cam.target.y += v.y;
        g_4722d0->cam.target.z += v.z;

        v = g_4722d0->data->axisY;
        tmp.x = g_4722d0->unk1ac.x - v.x;
        tmp.y = g_4722d0->unk1ac.y - v.y;
        tmp.z = g_4722d0->unk1ac.z - v.z;
        tmp.x *= 0.1f;
        tmp.y *= 0.1f;
        tmp.z *= 0.1f;
        g_4722d0->unk1ac.x -= tmp.x;
        g_4722d0->unk1ac.y -= tmp.y;
        g_4722d0->unk1ac.z -= tmp.z;
        v = g_4722d0->unk1ac;

        dot = v.x * g_4722d0->data->axisZ.x + v.y * g_4722d0->data->axisZ.y + v.z * g_4722d0->data->axisZ.z;
        tmp.x = dot * v.x;
        tmp.y = dot * v.y;
        tmp.z = dot * v.z;
        fwd.x = g_4722d0->data->axisZ.x - tmp.x;
        fwd.y = g_4722d0->data->axisZ.y - tmp.y;
        fwd.z = g_4722d0->data->axisZ.z - tmp.z;
        Vec3_Normalize(&fwd.x);
        right.x = fwd.y * v.z - fwd.z * v.y;
        right.y = fwd.z * v.x - fwd.x * v.z;
        right.z = fwd.x * v.y - fwd.y * v.x;
        Vec3_Normalize(&right.x);

        tmp.x = right.x * g_4722d0->data->camOffset.x;
        tmp.y = right.y * g_4722d0->data->camOffset.x;
        tmp.z = right.z * g_4722d0->data->camOffset.x;
        off.x = g_4722d0->data->camOffset.y * v.x;
        off.y = g_4722d0->data->camOffset.y * v.y;
        off.z = g_4722d0->data->camOffset.y * v.z;
        side.x = g_4722d0->data->camOffset.z * fwd.x;
        side.y = g_4722d0->data->camOffset.z * fwd.y;
        side.z = g_4722d0->data->camOffset.z * fwd.z;
        dot = g_482688.x * v.x + g_482688.y * v.y + g_482688.z * v.z;
        if (dot >= 0.0f)
        {
            off.x = -off.x;
            off.y = -off.y;
            off.z = -off.z;
        }
        off.x += tmp.x;
        off.y += tmp.y;
        off.z += tmp.z;
        off.x = side.x + off.x;
        off.y = side.y + off.y;
        off.z = side.z + off.z;
        tmp.x = off.x + g_4722d0->data->posX;
        tmp.y = off.y + g_4722d0->data->posY;
        tmp.z = off.z + g_4722d0->data->posZ;
        v = tmp;

        tmp.x -= g_4722d0->data->posX;
        tmp.y -= g_4722d0->data->posY;
        tmp.z -= g_4722d0->data->posZ;
        h = g_482688.x * tmp.x + g_482688.y * tmp.y + g_482688.z * tmp.z;
        if (h < 100.0f)
        {
            h = -(h - 100.0f);
            tmp.x = h * g_482688.x;
            tmp.y = h * g_482688.y;
            tmp.z = h * g_482688.z;
            v.x += tmp.x;
            v.y += tmp.y;
            v.z += tmp.z;
        }
        if (dot >= 0.0f)
        {
            tmp.x = g_482688.x + g_482688.x;
            tmp.y = g_482688.y + g_482688.y;
            tmp.z = g_482688.z + g_482688.z;
            g_4722d0->accelX -= tmp.x;
            g_4722d0->accelY -= tmp.y;
            g_4722d0->accelZ -= tmp.z;
        }
        k = g_4722d0->data->unk244 - 115.0f;
        if (k < 0.0f)
        {
            k = 0.0f;
        }
        side.x = k * g_4722d0->data->axisY.x;
        side.y = k * g_4722d0->data->axisY.y;
        side.z = k * g_4722d0->data->axisY.z;
        v.x -= side.x;
        v.y -= side.y;
        v.z -= side.z;
        v.y = v.y - g_4722d0->unk1c4 + g_4722d0->unk1c0;

        tmp.x = g_4722d0->cam.pos.x - g_4722d0->data->posX;
        tmp.y = g_4722d0->cam.pos.y - g_4722d0->data->posY;
        tmp.z = g_4722d0->cam.pos.z - g_4722d0->data->posZ;
        if (tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z < 9000000.0f)
        {
            car = g_4722d0->data;
            if (car->unk71ec == 0 && (float)fabs(car->posY - car->unk7238) > 50.0f)
            {
                g_4722d0->accelX *= 0.9f;
                g_4722d0->accelY *= 0.9f;
                g_4722d0->accelZ *= 0.9f;
                tmp.x = g_482688.x + g_482688.x;
                tmp.y = g_482688.y + g_482688.y;
                tmp.z = g_482688.z + g_482688.z;
                g_4722d0->accelX -= tmp.x;
                g_4722d0->accelY -= tmp.y;
                g_4722d0->accelZ -= tmp.z;
                FUN_403650(2);
                FUN_403460();
                FUN_403340();
                return;
            }
            if (car->unk1fd8 == 2)
            {
                FUN_403650(1);
                if (g_4722d0->data->unk71ec < 4)
                {
                    g_4722d0->accelX *= 0.9f;
                    g_4722d0->accelY *= 0.9f;
                    g_4722d0->accelZ *= 0.9f;
                    FUN_403460();
                    FUN_403340();
                    return;
                }
            }
            else if (car->unk1fd8 == 1)
            {
                FUN_403650(1);
                if (g_4722d0->data->unk71ec >= 2)
                {
                    g_4722d0->accelX *= 0.9f;
                    g_4722d0->accelY *= 0.9f;
                    g_4722d0->accelZ *= 0.9f;
                    FUN_403460();
                    FUN_403340();
                    return;
                }
            }
        }
        g_4722d0->accelX = 0.0f;
        g_4722d0->accelY = 0.0f;
        g_4722d0->accelZ = 0.0f;
        tmp.x = v.x - g_4722d0->cam.pos.x;
        tmp.y = v.y - g_4722d0->cam.pos.y;
        tmp.z = v.z - g_4722d0->cam.pos.z;
        g_4722d0->accelX = 0.0f;
        g_4722d0->accelY = 0.0f;
        g_4722d0->accelZ = 0.0f;
        tmp.x = v.x - g_4722d0->data->posX;
        tmp.y = v.y - g_4722d0->data->posY;
        tmp.z = v.z - g_4722d0->data->posZ;
        Vec3_Normalize(&tmp.x);
        tmp.x *= -g_4722d0->data->unk22fc;
        tmp.y *= -g_4722d0->data->unk22fc;
        tmp.z *= -g_4722d0->data->unk22fc;
        tmp.x += g_4722d0->data->posX;
        tmp.y += g_4722d0->data->posY;
        tmp.z += g_4722d0->data->posZ;
        tmp.x -= g_4722d0->cam.pos.x;
        tmp.y -= g_4722d0->cam.pos.y;
        tmp.z -= g_4722d0->cam.pos.z;
        dot = (float)sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z) * g_4722d0->data->unk2300;
        k = 256.0f;
        if (g_4722d0->unk1bc)
        {
            k = (30.0f - (float)g_4722d0->unk1bc--) * 8.533334f;
        }
        if (dot > k)
        {
            dot = k;
        }
        Vec3_Normalize(&tmp.x);
        g_4722d0->velX = dot * tmp.x;
        g_4722d0->velY = dot * tmp.y;
        g_4722d0->velZ = dot * tmp.z;
        g_4722d0->accelX = 0.0f;
        g_4722d0->accelY = 0.0f;
        g_4722d0->accelZ = 0.0f;
        FUN_403460();
        FUN_403340();
        return;
    case 6:
        car = g_4722d0->data;
        car->camOffset.x = 0.0f;
        car->camOffset.y = 100.0f;
        car->camOffset.z = 0.0f;
        tmp.x = g_4722d0->data->camOffset.x * g_4722d0->data->axisX.x;
        tmp.y = g_4722d0->data->camOffset.x * g_4722d0->data->axisX.y;
        tmp.z = g_4722d0->data->camOffset.x * g_4722d0->data->axisX.z;
        off.x = g_4722d0->data->camOffset.y * g_4722d0->data->axisY.x;
        off.y = g_4722d0->data->camOffset.y * g_4722d0->data->axisY.y;
        off.z = g_4722d0->data->camOffset.y * g_4722d0->data->axisY.z;
        side.x = g_4722d0->data->camOffset.z * g_4722d0->data->axisZ.x;
        side.y = g_4722d0->data->camOffset.z * g_4722d0->data->axisZ.y;
        side.z = g_4722d0->data->camOffset.z * g_4722d0->data->axisZ.z;
        tmp.x = off.x + tmp.x;
        tmp.y = off.y + tmp.y;
        tmp.z = off.z + tmp.z;
        tmp.x = side.x + tmp.x;
        tmp.y = side.y + tmp.y;
        tmp.z = side.z + tmp.z;
        g_4722d0->cam.pos.x = tmp.x + g_4722d0->data->posX;
        g_4722d0->cam.pos.y = tmp.y + g_4722d0->data->posY;
        g_4722d0->cam.pos.z = tmp.z + g_4722d0->data->posZ;

        tmp = g_4722d0->data->unk26b0->lods[0]->matrix[3];
        tmp.x = -tmp.x;
        g_4722d0->cam.up.x = tmp.x * g_4722d0->data->matrix[0] + tmp.y * g_4722d0->data->matrix[4] +
                             tmp.z * g_4722d0->data->matrix[8];
        g_4722d0->cam.up.y = tmp.x * g_4722d0->data->matrix[1] + tmp.y * g_4722d0->data->matrix[5] +
                             tmp.z * g_4722d0->data->matrix[9];
        g_4722d0->cam.up.z = tmp.x * g_4722d0->data->matrix[2] + tmp.y * g_4722d0->data->matrix[6] +
                             tmp.z * g_4722d0->data->matrix[10];
        tmp = g_4722d0->data->unk26b0->lods[0]->matrix[2];
        tmp.y = -tmp.y;
        off.x = tmp.x * g_4722d0->data->matrix[0] + tmp.y * g_4722d0->data->matrix[4] + tmp.z * g_4722d0->data->matrix[8];
        off.y = tmp.x * g_4722d0->data->matrix[1] + tmp.y * g_4722d0->data->matrix[5] + tmp.z * g_4722d0->data->matrix[9];
        off.z =
            tmp.x * g_4722d0->data->matrix[2] + tmp.y * g_4722d0->data->matrix[6] + tmp.z * g_4722d0->data->matrix[10];
        off.x *= 256.0f;
        off.y *= 256.0f;
        off.z *= 256.0f;
        g_4722d0->cam.target.x = off.x + g_4722d0->cam.pos.x;
        g_4722d0->cam.target.y = off.y + g_4722d0->cam.pos.y;
        g_4722d0->cam.target.z = off.z + g_4722d0->cam.pos.z;
        g_4722d0->roll = 0.0f;
        FUN_403460();
        FUN_403340();
        return;
    case 7:
    {
        FUN_403770(g_4722d0->data);
        GameSlot *slot = g_4722d0;
        car = slot->data;
        float diff = car->unk23b0 - g_499f8c;
        if (car->unk23b0 < g_499f8c)
        {
            diff -= -2.0f;
        }
        else
        {
            diff -= 2.0f;
        }
        if ((float)fabs(diff) > 0.01f)
        {
            diff *= 0.02f;
            if ((float)fabs(diff) > 0.2f)
            {
                diff = diff < 0.0f ? -0.2f : 0.2f;
            }
            g_499f8c += diff;
        }
        float t = g_499f8c * 0.01f;
        float frac;
        if (t < 0.0f)
        {
            frac = 1.0f - (float)fmod(-t, 1.0);
        }
        else
        {
            frac = fmod(t, 1.0);
        }
        FUN_428520(slot->path, &tmp, slot->path->count * frac);
        g_4722d0->cam.pos = tmp;
        tmp = *(Vec4 *)&g_4722d0->data->posX;
        off = g_4722d0->cam.pos;
        tmp.y = 0.0f;
        float dx = off.x - tmp.x;
        float dz = off.z - tmp.z;
        float lift = (float)sqrt(dx * dx + dz * dz) * 0.1f;
        lift *= 0.1f;
        lift *= lift;
        if (lift < 1000.0f)
        {
            lift = 1000.0f;
        }
        else if (lift > 3000.0f)
        {
            lift = 3000.0f;
        }
        off.x = g_482688.x * lift;
        off.y = g_482688.y * lift;
        off.z = lift * g_482688.z;
        g_4722d0->cam.pos.x -= off.x;
        g_4722d0->cam.pos.y -= off.y;
        g_4722d0->cam.pos.z -= off.z;
        break;
    }
    }
    FUN_403460();
    FUN_403340();
}

// FUNCTION: STUNTGP_D3D 0x4051e0
void FUN_4051e0()
{
    g_4722d0->unk1d0 = 10;
    g_4722d0->unk1d4 = 1;
    g_4722d0->camMode = g_4722d0->unk1d0;
    FUN_4028f0(g_4722d8, 10);
}

// FUNCTION: STUNTGP_D3D 0x41ff30
int FUN_41ff30(Vec4 *p)
{
    Vec4 v;
    v.x = p->x - g_cameraSweep.unk04.x;
    v.y = p->y - g_cameraSweep.unk04.y;
    v.z = p->z - g_cameraSweep.unk04.z;
    float d = g_cameraSweep.unk68.z * v.z + g_cameraSweep.unk68.y * v.y + g_cameraSweep.unk68.x * v.x;
    if (d >= -0.01f && d < g_cameraSweep.unk108)
    {
        g_cameraSweep.unk108 = d;
        return 1;
    }
    return 0;
}

// Sweeps the sphere along g_cameraSweep.unk68 against point p; on a hit records the contact, its normal and the
// sphere centre at contact.
// FUNCTION: STUNTGP_D3D 0x41ffa0
int FUN_41ffa0(Vec4 *p)
{
    Vec4 d;
    d.x = p->x - g_cameraSweep.unk04.x;
    d.y = p->y - g_cameraSweep.unk04.y;
    d.z = p->z - g_cameraSweep.unk04.z;
    float dist2 = d.x * d.x + d.y * d.y + d.z * d.z;
    float r = g_cameraSweep.unk88 + g_cameraSweep.unk94;
    if (dist2 > r * r)
    {
        return 0;
    }
    float t = g_cameraSweep.unk68.x * d.x + g_cameraSweep.unk68.y * d.y + g_cameraSweep.unk68.z * d.z;
    float h = dist2 - t * t;
    if (h > g_cameraSweep.unk98)
    {
        return 0;
    }
    t = t - (float)sqrt(g_cameraSweep.unk98 - h);
    Vec4 q;
    q.x = g_cameraSweep.unk68.x * t;
    q.y = g_cameraSweep.unk68.y * t;
    q.z = t * g_cameraSweep.unk68.z;
    q.x = g_cameraSweep.unk04.x + q.x;
    q.y = g_cameraSweep.unk04.y + q.y;
    q.z = g_cameraSweep.unk04.z + q.z;
    if (!FUN_41ff30(&q))
    {
        return 0;
    }
    Vec4 n;
    n.x = q.x - p->x;
    g_cameraSweep.unke8 = q;
    n.y = q.y - p->y;
    n.z = q.z - p->z;
    Vec3_Normalize(&n.x);
    g_cameraSweep.unkf8.x = g_cameraSweep.unk94 * n.x;
    g_cameraSweep.unkf8.y = g_cameraSweep.unk94 * n.y;
    g_cameraSweep.unkd8 = n;
    g_cameraSweep.unkf8.z = g_cameraSweep.unk94 * n.z;
    g_cameraSweep.unkf8.x = g_cameraSweep.unkf8.x + p->x;
    g_cameraSweep.unkf8.y = g_cameraSweep.unkf8.y + p->y;
    g_cameraSweep.unkf8.z = g_cameraSweep.unkf8.z + p->z;
    g_cameraSweep.unkc8 = g_cameraSweep.unkf8;
    return 1;
}

// FUN_41ffa0 against body point i, with the sphere grown by the point's radius.
// FUNCTION: STUNTGP_D3D 0x421960
int FUN_421960(Body *body, int i)
{
    float r = g_cameraSweep.unk94 + body->points[i].radius;
    Vec4 *p = &body->points[i].prev;
    Vec4 d;
    d.x = p->x - g_cameraSweep.unk04.x;
    d.y = p->y - g_cameraSweep.unk04.y;
    d.z = p->z - g_cameraSweep.unk04.z;
    float dist2 = d.x * d.x + d.y * d.y + d.z * d.z;
    float reach = g_cameraSweep.unk88 + r;
    if (dist2 > reach * reach)
    {
        return 0;
    }
    float t = g_cameraSweep.unk68.x * d.x + g_cameraSweep.unk68.y * d.y + g_cameraSweep.unk68.z * d.z;
    float h = dist2 - t * t;
    float r2 = r * r;
    if (h > r2)
    {
        return 0;
    }
    t = t - (float)sqrt(r2 - h);
    Vec4 q;
    q.x = g_cameraSweep.unk68.x * t;
    q.y = g_cameraSweep.unk68.y * t;
    q.z = t * g_cameraSweep.unk68.z;
    q.x = g_cameraSweep.unk04.x + q.x;
    q.y = g_cameraSweep.unk04.y + q.y;
    q.z = g_cameraSweep.unk04.z + q.z;
    if (!FUN_41ff30(&q))
    {
        return 0;
    }
    Vec4 n;
    n.x = q.x - p->x;
    g_cameraSweep.unke8 = q;
    n.y = q.y - p->y;
    n.z = q.z - p->z;
    Vec3_Normalize(&n.x);
    g_cameraSweep.unkf8.x = g_cameraSweep.unk94 * n.x;
    g_cameraSweep.unkf8.y = g_cameraSweep.unk94 * n.y;
    g_cameraSweep.unkd8 = n;
    g_cameraSweep.unkf8.z = g_cameraSweep.unk94 * n.z;
    g_cameraSweep.unkf8.x = g_cameraSweep.unkf8.x + p->x;
    g_cameraSweep.unkf8.y = g_cameraSweep.unkf8.y + p->y;
    g_cameraSweep.unkf8.z = g_cameraSweep.unkf8.z + p->z;
    g_cameraSweep.unkc8 = g_cameraSweep.unkf8;
    return 1;
}

// GLOBAL: STUNTGP_D3D 0x5715cc
int g_5715cc;

// Tests every vertex of the polygon with FUN_41ffa0, remembering the polygon on a hit.
// FUNCTION: STUNTGP_D3D 0x420190
void FUN_420190(TrackPoly *poly, int *hit)
{
    WORD *idx = g_renderState.unk7f98->indices + poly->firstIndex;
    unsigned int n = poly->vertexCount;
    for (unsigned int i = 0; i < n; i++)
    {
        int r = FUN_41ffa0(&g_renderState.unk7f98->vertices[*idx]);
        *hit |= r;
        if (r == 1)
        {
            g_cameraSweep.unka4 = poly;
            g_5715cc = 3;
        }
        idx++;
    }
}

// Classifies a box (centre pos, half extents size / 75) against the view frustum: 1 outside,
// 2 crossing a plane, 0 fully inside. Plane distances are sign-tested through their bits.
// FUNCTION: STUNTGP_D3D 0x4280a0
int FUN_4280a0(Vec4 *pos, Vec4 *size)
{
    float d[5];
    Vec4 s;
    Vec4 v;
    float t;
    v.x = pos->x - g_4722d0->cam.pos.x;
    v.y = pos->y - g_4722d0->cam.pos.y;
    v.z = pos->z - g_4722d0->cam.pos.z;
    t = v.z * g_4722d0->axisZ.z + v.y * g_4722d0->axisZ.y + v.x * g_4722d0->axisZ.x;
    if (*(int *)&t < 0)
    {
        return 1;
    }
    d[0] = t;
    t = t - g_4722d0->unk19c;
    if (*(int *)&t > 0)
    {
        return 1;
    }
    s.x = size->x * 75.0f;
    d[1] = v.z * g_4722d0->planeLeft.z + v.y * g_4722d0->planeLeft.y + v.x * g_4722d0->planeLeft.x;
    t = d[1] - s.x;
    if (*(int *)&t > 0)
    {
        return 1;
    }
    d[2] = v.z * g_4722d0->planeRight.z + v.y * g_4722d0->planeRight.y + v.x * g_4722d0->planeRight.x;
    t = d[2] - s.x;
    if (*(int *)&t > 0)
    {
        return 1;
    }
    s.y = size->y * 75.0f;
    d[3] = v.z * g_4722d0->planeTop.z + v.y * g_4722d0->planeTop.y + v.x * g_4722d0->planeTop.x;
    t = d[3] - s.y;
    if (*(int *)&t > 0)
    {
        return 1;
    }
    d[4] = v.z * g_4722d0->planeBottom.z + v.y * g_4722d0->planeBottom.y + v.x * g_4722d0->planeBottom.x;
    t = d[4] - s.y;
    if (*(int *)&t > 0)
    {
        return 1;
    }
    s.z = size->z * 75.0f;
    d[0] += s.z;
    if (*(int *)&d[0] > 0)
    {
        return 2;
    }
    d[1] += s.x;
    if (*(int *)&d[1] > 0)
    {
        return 2;
    }
    d[2] += s.x;
    if (*(int *)&d[2] > 0)
    {
        return 2;
    }
    d[3] += s.y;
    if (*(int *)&d[3] > 0)
    {
        return 2;
    }
    d[4] += s.y;
    return *(int *)&d[4] > 0 ? 2 : 0;
}

// Uniform cubic B-spline basis weights, written to m[0], m[4], m[8], m[12].
// FUNCTION: STUNTGP_D3D 0x4282a0
void FUN_4282a0(float *m, float t)
{
    float t2 = t * t;
    float t3 = t2 * t;
    m[12] = t3 * 0.16666667f;
    m[8] = (((3.0f - t * 3.0f) * t + 3.0f) * t + 1.0f) * 0.16666667f;
    m[4] = (t3 * 3.0f - t2 * 6.0f + 4.0f) * 0.16666667f;
    m[0] = (t2 * 3.0f - t3 - t * 3.0f + 1.0f) * 0.16666667f;
}

// FUNCTION: STUNTGP_D3D 0x428460
void FUN_428460(CameraPath *path, Vec4 *out, float t)
{
    Vec4 *points = path->points;
    unsigned int i = (int)floor(t);
    if (i >= path->count)
    {
        i = 0;
    }
    unsigned int j = i + 1;
    if (j >= path->count)
    {
        j = 0;
    }
    float f = fmod(t, 1.0);
    Vec4 d;
    d.x = points[j].x - points[i].x;
    d.y = points[j].y - points[i].y;
    d.z = points[j].z - points[i].z;
    d.x *= f;
    d.y *= f;
    d.z *= f;
    d.x += points[i].x;
    d.y += points[i].y;
    d.z += points[i].z;
    *out = d;
}

// FUNCTION: STUNTGP_D3D 0x428520
void FUN_428520(CameraPath *path, Vec4 *out, float t)
{
    if (path->unk0c == 1)
    {
        FUN_428460(path, out, t);
        return;
    }
    t += 3.0f;
    unsigned int idx = (int)floor(t);
    t = fmod(t, 1.0);
    Vec4 *points = path->points;
    Vec4 acc;
    acc.x = 0.0f;
    acc.y = 0.0f;
    acc.z = 0.0f;
    float basis[16];
    FUN_4282a0(basis, t);
    float *w = &basis[12];
    unsigned int count = path->count;
    for (int n = 0; n < 4; n++)
    {
        unsigned int k = idx;
        if (idx >= count)
        {
            if (path->mode == 2)
            {
                k = idx % count;
            }
            else
            {
                k = count - 1;
            }
        }
        acc.x += *w * points[k].x;
        acc.y += points[k].y * *w;
        acc.z += points[k].z * *w;
        if (idx > 0)
        {
            idx--;
        }
        w -= 4;
    }
    out->x = acc.x;
    out->y = acc.y;
    out->z = acc.z;
}

// FUNCTION: STUNTGP_D3D 0x4286e0
void FUN_4286e0(float *value, float step)
{
    float v = *value;
    if (g_62d480[0x4c] & 0x80)
    {
        v += step;
    }
    if ((g_62d480[0x4b] & 0x80) && v > 0.0f)
    {
        v -= step;
    }
    *value = fmod(v, 1.0);
}

// GLOBAL: STUNTGP_D3D 0x499f88
float g_499f88;

// Advances the path position *t by *speed, steered by the L and apostrophe keys.
// FUNCTION: STUNTGP_D3D 0x428740
void FUN_428740(float *t, float *speed)
{
    float s = *speed * 0.95f;
    *speed = s;
    if ((g_62d480[0x26] & 0x80) && s < 0.0015f)
    {
        *speed = s + 2.5e-5f;
    }
    if ((g_62d480[0x28] & 0x80) && *speed > -0.0015f)
    {
        *speed -= 2.5e-5f;
    }
    float v = *t + *speed;
    *t = v;
    if (v < 0.0f)
    {
        *t = v + 1.0;
    }
    else
    {
        *t = fmod(v, 1.0);
    }
    if ((float)fabs(*speed) < 1.5625e-6f)
    {
        *speed = 0.0f;
    }
}
