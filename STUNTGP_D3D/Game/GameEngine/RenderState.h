#ifndef RENDERSTATE_H
#define RENDERSTATE_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../../d3drender.h"
#include "Engine_LevelScript.h"
#include "GameUpdate.h"

struct AnimDef;
struct Light;
struct LightRec;
struct RenderMaterial;
struct Unk624488;

// Lights active for the current object (unk8044 of them) and the next free record in unk8048.
struct LightList
{
    Light *lights[16]; // 0x00
    LightRec *next;    // 0x40
};

// One block in the original: stores to its scalars are never moved across memsets of its arrays
// (FUN_42e510), which only happens when they share an aggregate.
struct RenderState
{
    Vec4 unk00; // 0x00
    Vec4 unk10; // 0x10
    DWORD unk20; // 0x20
    int unk24; // 0x24
    int unk28; // 0x28
    int unk2c; // 0x2c
    VisIndexList *unk30; // 0x30
    VisIndexList *unk34; // 0x34
    int unk38; // 0x38
    VisIndexList *unk3c; // 0x3c
    VisIndexList *unk40; // 0x40
    Scene *unk44; // 0x44
    ObjectDef *unk48; // 0x48
    float unk4c; // 0x4c
    float unk50; // 0x50
    BYTE unk54[0x14]; // 0x54
    // Polygons queued for the track so far.
    DWORD unk68; // 0x68
    BYTE unk6c[0x40]; // 0x6c
    float unkac[16]; // 0xac
    BYTE unkec[0x10]; // 0xec
    int unkfc; // 0xfc
    int unk100; // 0x100
    int unk104; // 0x104
    OverlayPoly *unk108; // 0x108
    void *unk10c; // 0x10c
    void *unk110; // 0x110
    void *unk114; // 0x114
    void *unk118; // 0x118
    DWORD unk11c; // 0x11c
    BYTE unk120[0x1c0]; // 0x120
    // Write position in unk120.
    BYTE *unk2e0; // 0x2e0
    BYTE unk2e4[0x6000]; // 0x2e4
    BYTE *unk62e4; // 0x62e4
    int unk62e8; // 0x62e8
    TextureSlot unk62ec[255]; // 0x62ec
    TextureSlot *unk7ed0; // 0x7ed0
    int unk7ed4; // 0x7ed4
    void *unk7ed8; // 0x7ed8
    int unk7edc; // 0x7edc
    void *unk7ee0; // 0x7ee0
    int unk7ee4; // 0x7ee4
    void *unk7ee8; // 0x7ee8
    int unk7eec; // 0x7eec
    void *unk7ef0; // 0x7ef0
    int unk7ef4; // 0x7ef4
    RenderBucket unk7ef8[8]; // 0x7ef8
    // Name of the track scene from L_TRACK.
    int unk7f78; // 0x7f78
    BYTE *unk7f7c; // 0x7f7c
    BYTE *unk7f80; // 0x7f80
    BYTE *unk7f84; // 0x7f84
    BYTE *unk7f88; // 0x7f88
    CameraPath *unk7f8c; // 0x7f8c
    BYTE *unk7f90; // 0x7f90
    RenderMaterial *unk7f94; // 0x7f94
    TrackOctree *unk7f98; // 0x7f98
    AnimDef *unk7f9c; // 0x7f9c
    Unk624488 *unk7fa0; // 0x7fa0
    SceneEntry *unk7fa4; // 0x7fa4
    SceneEntry *unk7fa8; // 0x7fa8
    Ambience *unk7fac; // 0x7fac
    DWORD unk7fb0; // 0x7fb0
    DWORD unk7fb4; // 0x7fb4
    int unk7fb8; // 0x7fb8
    int unk7fbc; // 0x7fbc
    short unk7fc0[16]; // 0x7fc0
    int unk7fe0; // 0x7fe0
    int unk7fe4; // 0x7fe4
    int unk7fe8; // 0x7fe8
    int unk7fec; // 0x7fec
    int unk7ff0; // 0x7ff0
    int unk7ff4; // 0x7ff4
    int unk7ff8; // 0x7ff8
    int unk7ffc; // 0x7ffc
    BYTE unk8000[0x4]; // 0x8000
    // Set once the back buffer has been unlocked for the frame.
    int unk8004; // 0x8004
    int unk8008; // 0x8008
    float unk800c; // 0x800c
    int unk8010; // 0x8010
    int unk8014; // 0x8014
    int unk8018; // 0x8018
    Ambience unk801c; // 0x801c
    int unk8044; // 0x8044
    void *unk8048; // 0x8048
    LightList unk804c; // 0x804c
};

extern RenderState g_renderState;

#endif /* RENDERSTATE_H */
