#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../../globals.h"

struct Vec4
{
    float x; // 0x00
    float y; // 0x04
    float z; // 0x08
    float w; // 0x0c
};

struct Camera
{
    Vec4 pos;     // 0x00
    Vec4 scale;   // 0x10
    Vec4 target;  // 0x20
    Vec4 up;      // 0x30
    int unk40;    // 0x40
    Vec4 *unk44;  // 0x44
    Vec4 *matrix; // 0x48
    int unk4c;    // 0x4c
};

// Spline of camera positions, looked up by id.
struct CameraPath
{
    int id;             // 0x00
    Vec4 *points;       // 0x04
    unsigned int count; // 0x08
    int unk0c;          // 0x0c
    int mode;           // 0x10
    int unk14;          // 0x14
    float unk18;        // 0x18
};

// Preset a GameSlot camera is reset to (GameSlot::preset).
struct CameraPreset
{
    Vec4 pos;    // 0x00
    Vec4 target; // 0x10
    Vec4 up;     // 0x20
    float fov;   // 0x30
    int unk34;   // 0x34
    float roll;  // 0x38
    int unk3c;   // 0x3c
};

struct Fader
{
    float x;          // 0x00
    float y;          // 0x04
    float unk08;      // 0x08
    float unk0c;      // 0x0c
    int active;       // 0x10
    float value;      // 0x14
    float target;     // 0x18
    int dx;           // 0x1c, offset at value 100, in 1/100 units
    int dy;           // 0x20
};

struct SlotFx
{
    int unk000;       // 0x000
    int delay;        // 0x004
    Fader faders[18]; // 0x008
};

struct Car;

// On-screen message; count is the frames it has left.
struct SlotEvent
{
    int count;        // 0x00
    int duration;     // 0x04
    DWORD order;      // 0x08
    char text[0x40];  // 0x0c
    Car *car;         // 0x4c
    int mode;         // 0x50
};

struct CarRace
{
    DWORD unk00;      // 0x00
    int unk04;        // 0x04
    BYTE unk08[0x10]; // 0x08
    int unk18;        // 0x18
    int unk1c;        // 0x1c
    int unk20;        // 0x20
    DWORD unk24;      // 0x24
    BYTE unk28[0x4];  // 0x28
    DWORD unk2c;      // 0x2c
    int unk30;        // 0x30
    BYTE unk34[0x10]; // 0x34
    int unk44;        // 0x44
    DWORD unk48;      // 0x48
    DWORD unk4c[9];    // 0x4c ([7] 0x68, [8] 0x6c)
    float unk70;       // 0x70
    DWORD unk74;       // 0x74
    DWORD unk78;       // 0x78
    int unk7c;         // 0x7c
    DWORD unk80[7];    // 0x80 ([5] 0x94, [6] 0x98)
};

struct Vector4
{
    float x;
    float y;
    float z;
    float w;
};

// 4 per car, from Car+0x1fe0
struct Wheel
{
    float unk00;        // 0x0000
    float unk04;        // 0x0004
    BYTE unk0008[0x4];  // 0x0008
    float unk0c;        // 0x000c
    float unk10;        // 0x0010
    BYTE unk0014[0x8];  // 0x0014
    float unk1c;        // 0x001c
    BYTE unk0020[0x10]; // 0x0020
    float unk30;        // 0x0030
    float unk34;        // 0x0034
    float unk38;        // 0x0038
    Vec4 pos;           // 0x003c world position
    BYTE unk004c[0x24]; // 0x004c
    int unk70;          // 0x0070
    int unk74;          // 0x0074
    int unk78;          // 0x0078
    int unk7c;          // 0x007c
    float unk80;        // 0x0080
    float unk84;        // 0x0084
    float unk88;        // 0x0088
    float unk8c;        // 0x008c
    float unk90;        // 0x0090
    float unk94;        // 0x0094
};

// Car models are Scenes too (FUN_42f090 hands loaded scenes to the drivers).
struct Scene;

// Ring buffer of recent world positions, fed by FUN_41e510.
struct Trail
{
    Vec4 pos;         // 0x000
    Vec4 points[32];  // 0x010
    DWORD head;       // 0x210
    DWORD count;      // 0x214
};

struct TrailSlot
{
    int active;  // 0x000
    Trail trail; // 0x004
};

struct CarFx
{
    int active;         // 0x000
    Vec4 unk004;        // 0x004
    Vec4 unk014;        // 0x014
    Vec4 unk024;        // 0x024
    BYTE unk034[0x104]; // 0x034
    DWORD count;        // 0x138
    int unk13c;         // 0x13c
};

struct SkidMark
{
    int unk00;          // 0x000
    int unk04;          // 0x004
    DWORD unk08;        // 0x008
    BYTE unk0c[0xd04];  // 0x00c
};

// One per car.
struct Driver
{
    Scene *model;  // 0x00
    Scene *unk04;  // 0x04
    int unk08;        // 0x08
    int unk0c;        // 0x0c
    int unk10;        // 0x10
    int unk14;        // 0x14
    int unk18;        // 0x18
    int unk1c;        // 0x1c
    int unk20;        // 0x20
    char name[0x40];  // 0x24
};

// Collision point of a car body, offsets relative to the body position.
struct BodyPoint
{
    Vec4 local;       // 0x00
    Vec4 world;       // 0x10
    Vec4 prev;        // 0x20
    BYTE unk30[0x10]; // 0x30
    float unk40;      // 0x40
    float unk44;      // 0x44
    float radius;     // 0x48
};

// Car+0x7270
struct Body
{
    Vec4 pos;              // 0x000
    Vec4 prevPos;          // 0x010
    BYTE unk020[0x10];     // 0x020
    float vel[3];          // 0x030
    BYTE unk03c[0x4];      // 0x03c
    float unk40;           // 0x040
    float radius;          // 0x044
    float mat0[16];        // 0x048
    float mat1[16];        // 0x088
    float mat2[16];        // 0x0c8
    BYTE unk108[0x34];     // 0x108
    DWORD numPoints;       // 0x13c
    float unk140;          // 0x140
    BodyPoint points[8];   // 0x144
};

// One recorded frame of car state.
struct ReplayFrame
{
    int pos[3];           // 0x00
    BYTE unk0c[0x8];      // 0x0c
    short unk14[4];       // 0x14
    char unk1c[4];        // 0x1c
    unsigned short unk20; // 0x20
    char unk22;           // 0x22
    char unk23;           // 0x23
    BYTE flags;           // 0x24
    BYTE unk25;           // 0x25
    BYTE unk26[0x6];      // 0x26
};

// Ghost/replay buffer: 0x80 byte header followed by frames.
struct Replay
{
    unsigned short mode;    // 0x00 1 = record, 2 = play
    unsigned short count;   // 0x02
    unsigned short unk04;   // 0x04
    unsigned short unk06;   // 0x06
    float unk08;            // 0x08
    float unk0c;            // 0x0c
    ReplayFrame *cur;       // 0x10
    int unk14;              // 0x14
    BYTE unk18[0x8];        // 0x18
    short unk20;            // 0x20
    short unk22;            // 0x22
    short unk24;            // 0x24
    short unk26;            // 0x26
    int checksum;           // 0x28
    char name[0x10];        // 0x2c
    int size;               // 0x3c
    BYTE unk40[0x40];       // 0x40
    ReplayFrame frames[1];  // 0x80
};

// Running count, last value, sum and mean.
struct Stat
{
    DWORD count; // 0x00
    float last;  // 0x04
    float sum;   // 0x08
    float mean;  // 0x0c
};

struct PosSample
{
    Vec4 pos;  // 0x00
    int unk10; // 0x10
};

struct PosHistory
{
    PosSample samples[8]; // 0x00
    int unka0;            // 0xa0
};

// 6 entries at 0x49a1f8
// Per-wheel suspension settings; names are the car config keys.
struct Suspension
{
    float maxTravelIn;     // 0x00
    float maxDampingIn;    // 0x04
    float maxStiffnessIn;  // 0x08
    float maxTravelOut;    // 0x0c
    float maxDampingOut;   // 0x10
    float maxStiffnessOut; // 0x14
};

// Collision polygon of the track octree.
struct TrackPoly
{
    BYTE unk0;        // 0x0
    BYTE vertexCount; // 0x1
    WORD firstIndex;  // 0x2, into TrackOctree::indices
    WORD plane;       // 0x4, into TrackOctree::planes
    WORD surface;     // 0x6, into TrackOctree::surfaces
};

struct OctNode
{
    float x;          // 0x00
    float y;          // 0x04
    float z;          // 0x08
    int unk0c;        // 0x0c
    WORD children[8]; // 0x10, node index, 0 for a leaf
    WORD leaves[8];   // 0x20, polygon list offset per octant
};

struct OctRoot
{
    float key;     // 0x0
    OctNode *root; // 0x4
};

// Track collision octree; FUN_42ed80 turns its file offsets into pointers.
struct TrackOctree
{
    short *polyLists;    // 0x00, -1 terminated polygon lists
    WORD *indices;       // 0x04
    Vec4 *vertices;      // 0x08
    Vec4 *planes;        // 0x0c
    TrackPoly *polys;    // 0x10
    DWORD *surfaces;     // 0x14, low byte holds the surface flags
    OctRoot roots[2];    // 0x18, roots[0].root is also the node array base
};

extern TrackOctree *g_624480;

// One of the 32 effect slots at g_612948.unk045c.
struct Unk612da4
{
    int life;           // 0x000
    int unk04;          // 0x004
    Vec4 pos;           // 0x008
    Vec4 vel;           // 0x018
    float unk28;        // 0x028
    float unk2c;        // 0x02c
    BYTE unk030[0x400]; // 0x030
    int unk430;         // 0x430
    int unk434;         // 0x434
    float unk438;       // 0x438
    int unk43c;         // 0x43c
};

// Stunt marker along the track path (CarAI_StuntKnotList).
struct StuntKnot
{
    float pathPosition; // 0x00
    float width;        // 0x04
    int grade;          // 0x08
};

struct Car
{
    BYTE unk0000[0x20];       // 0x0000
    float tyreFrictionEnv[128]; // 0x0020
    float unk220;             // 0x0220
    float unk224;             // 0x0224
    float unk228;             // 0x0228
    float unk22c;             // 0x022c
    float unk230;             // 0x0230
    float unk234;             // 0x0234
    float unk238;             // 0x0238
    float unk23c;             // 0x023c
    float unk240;             // 0x0240
    float unk244;             // 0x0244
    float unk248;             // 0x0248
    float unk24c;             // 0x024c
    float unk250;             // 0x0250
    float unk254;             // 0x0254
    float unk258[128];        // 0x0258
    BYTE unk0458[0x4];        // 0x0458
    float unk045c;            // 0x045c
    float unk460;             // 0x0460
    float unk464;             // 0x0464
    float unk468;             // 0x0468
    float unk46c;             // 0x046c
    float unk470[4][128];     // 0x0470, torque curves
    int unkc70;               // 0x0c70
    unsigned int unkc74;      // 0x0c74
    int unkc78;               // 0x0c78
    float unkc7c[9];          // 0x0c7c
    float unkca0;             // 0x0ca0
    float unkca4;             // 0x0ca4
    float unkca8;             // 0x0ca8
    float unkcac;             // 0x0cac
    float unkcb0;             // 0x0cb0
    float unkcb4;             // 0x0cb4
    Vector4 unkcb8[4];        // 0x0cb8
    Suspension suspension[4]; // 0x0cf8
    float unkd58;             // 0x0d58
    float unkd5c;             // 0x0d5c
    float unkd60;             // 0x0d60
    float unkd64;             // 0x0d64
    float unkd68;             // 0x0d68
    float unkd6c;             // 0x0d6c
    float unkd70[128];        // 0x0d70
    float unkf70;             // 0x0f70
    float unkf74;             // 0x0f74
    float unkf78;             // 0x0f78
    float unkf7c;             // 0x0f7c
    float unkf80;             // 0x0f80
    float unkf84[128];        // 0x0f84
    float unk1184;            // 0x1184
    float unk1188[5][128];    // 0x1188
    BYTE unk1b88[0x4];        // 0x1b88
    float unk1b8c;            // 0x1b8c
    float unk1b90;            // 0x1b90
    float unk1b94;            // 0x1b94
    float unk1b98;            // 0x1b98
    float unk1b9c;            // 0x1b9c
    float unk1ba0;            // 0x1ba0
    float unk1ba4;            // 0x1ba4
    int active;               // 0x1ba8
    float posX;               // 0x1bac
    float posY;               // 0x1bb0
    float posZ;               // 0x1bb4
    float posW;               // 0x1bb8
    Vec4 unk1bbc;             // 0x1bbc
    float matrix[16];         // 0x1bcc
    float unk1c0c[16];        // 0x1c0c
    float unk1c4c[16];        // 0x1c4c
    Vec4 unk1c8c;             // 0x1c8c
    Vec4 unk1c9c;             // 0x1c9c
    Vec4 unk1cac;             // 0x1cac
    Vec4 axisX;               // 0x1cbc
    Vec4 axisY;               // 0x1ccc
    Vec4 axisZ;               // 0x1cdc
    float unk1cec;            // 0x1cec
    float unk1cf0;            // 0x1cf0
    float unk1cf4;            // 0x1cf4
    float unk1cf8;            // 0x1cf8
    float unk1cfc;            // 0x1cfc
    BYTE unk1d00[0x4];        // 0x1d00
    float unk1d04;            // 0x1d04, peak power
    float unk1d08[128];       // 0x1d08, power curve
    float unk1f08;            // 0x1f08
    int unk1f0c;              // 0x1f0c
    unsigned int unk1f10;     // 0x1f10
    float unk1f14;            // 0x1f14
    BYTE unk1f18[0x4];        // 0x1f18
    int unk1f1c;              // 0x1f1c
    float unk1f20;            // 0x1f20
    float unk1f24;            // 0x1f24
    float unk1f28;            // 0x1f28
    PosHistory unk1f2c;       // 0x1f2c
    float unk1fd0;            // 0x1fd0
    int unk1fd4;              // 0x1fd4
    int unk1fd8;              // 0x1fd8
    unsigned int unk1fdc;     // 0x1fdc
    Wheel wheels[4];          // 0x1fe0
    float unk2240[4];         // 0x2240
    int unk2250;              // 0x2250
    float unk2254;            // 0x2254
    float unk2258;            // 0x2258
    float unk225c;            // 0x225c
    int unk2260;              // 0x2260
    float unk2264;            // 0x2264
    int unk2268;              // 0x2268
    int unk226c;              // 0x226c
    float unk2270;            // 0x2270
    float unk2274;            // 0x2274
    int unk2278;              // 0x2278
    int inputMode;            // 0x227c
    int unk2280;              // 0x2280
    BYTE keyMap[0xd];         // 0x2284
    BYTE unk2291[0x7];        // 0x2291
    int unk2298;              // 0x2298
    int unk229c;              // 0x229c
    BYTE prevControls[0xa];   // 0x22a0
    BYTE controls[0xa];       // 0x22aa
    int unk22b4;              // 0x22b4
    int unk22b8;              // 0x22b8
    int unk22bc;              // 0x22bc
    int unk22c0;              // 0x22c0
    float unk22c4;            // 0x22c4
    int unk22c8;              // 0x22c8
    Vec4 camOffset;           // 0x22cc
    float unk22dc;            // 0x22dc
    float unk22e0;            // 0x22e0
    float unk22e4;            // 0x22e4
    BYTE unk22e8[0x4];        // 0x22e8
    float unk22ec;            // 0x22ec
    float unk22f0;            // 0x22f0
    float unk22f4;            // 0x22f4
    BYTE unk22f8[0x4];        // 0x22f8
    float unk22fc;            // 0x22fc
    float unk2300;            // 0x2300
    int unk2304;              // 0x2304
    float unk2308[4];         // 0x2308
    float unk2318[4];         // 0x2318
    float unk2328;            // 0x2328
    float unk232c;            // 0x232c
    float unk2330;            // 0x2330
    BYTE unk2334[0x8];        // 0x2334
    int unk233c[4];           // 0x233c
    int unk234c;              // 0x234c
    int unk2350;              // 0x2350
    int unk2354;              // 0x2354
    int unk2358;              // 0x2358
    int unk235c;              // 0x235c
    float unk2360;            // 0x2360
    float unk2364;            // 0x2364
    int unk2368;              // 0x2368
    int unk236c;              // 0x236c
    int unk2370;              // 0x2370
    int unk2374;              // 0x2374
    int unk2378;              // 0x2378
    int unk237c;              // 0x237c
    int unk2380;              // 0x2380
    int unk2384;              // 0x2384
    int unk2388;              // 0x2388
    int unk238c;              // 0x238c
    int unk2390;              // 0x2390
    int unk2394;              // 0x2394
    int unk2398;              // 0x2398
    int unk239c;              // 0x239c
    int unk23a0;              // 0x23a0
    unsigned int unk23a4;     // 0x23a4
    int unk23a8;              // 0x23a8
    int unk23ac;              // 0x23ac
    float unk23b0;            // 0x23b0
    BYTE unk23b4[0x4];        // 0x23b4
    float unk23b8;            // 0x23b8
    int unk23bc;              // 0x23bc
    int unk23c0;              // 0x23c0
    int unk23c4;              // 0x23c4
    int unk23c8;              // 0x23c8
    int unk23cc;              // 0x23cc
    int unk23d0;              // 0x23d0
    unsigned int unk23d4;     // 0x23d4
    int unk23d8;              // 0x23d8
    int unk23dc[24];          // 0x23dc
    BYTE unk243c[0x4];        // 0x243c
    DWORD unk2440[25];        // 0x2440 per-lap times
    int unk24a4;              // 0x24a4
    int unk24a8;              // 0x24a8
    int unk24ac;              // 0x24ac
    BYTE unk24b0[0x10];       // 0x24b0
    Vec4 unk24c0;             // 0x24c0
    BYTE unk24d0[0x10];       // 0x24d0
    int unk24e0;              // 0x24e0
    int unk24e4;              // 0x24e4
    int unk24e8;              // 0x24e8
    BYTE unk24ec[0x4];        // 0x24ec
    DWORD unk24f0[10];        // 0x24f0
    DWORD unk2518[10];        // 0x2518
    DWORD unk2540[10];        // 0x2540
    int unk2568;              // 0x2568
    int unk256c;              // 0x256c
    float unk2570;            // 0x2570
    float unk2574;            // 0x2574
    unsigned int unk2578;     // 0x2578
    float unk257c;            // 0x257c
    int unk2580;              // 0x2580
    Stat unk2584;             // 0x2584
    Stat unk2594[2];          // 0x2594
    Stat unk25b4;             // 0x25b4
    DWORD unk25c4[6];         // 0x25c4
    DWORD unk25dc[6];         // 0x25dc
    int unk25f4[6];           // 0x25f4
    float unk260c;            // 0x260c
    float unk2610;            // 0x2610
    float unk2614;            // 0x2614
    float unk2618;            // 0x2618
    float unk261c;            // 0x261c
    BYTE unk2620[0x4];        // 0x2620
    int unk2624;              // 0x2624
    int unk2628;              // 0x2628
    int unk262c;              // 0x262c
    int catchUp;              // 0x2630
    float unk2634;            // 0x2634
    float leaderGap;          // 0x2638
    BYTE unk263c[0x4];        // 0x263c
    int unk2640;              // 0x2640
    int unk2644;              // 0x2644 path knot
    float unk2648;            // 0x2648
    int unk264c;              // 0x264c path knot
    float unk2650;            // 0x2650
    int unk2654;              // 0x2654
    float unk2658;            // 0x2658
    float unk265c;            // 0x265c
    float unk2660;            // 0x2660
    unsigned int unk2664;     // 0x2664
    BYTE unk2668[0xc];        // 0x2668
    int unk2674;              // 0x2674
    int unk2678;              // 0x2678
    BYTE unk267c[0x10];       // 0x267c
    int unk268c;              // 0x268c
    BYTE unk2690[0x4];        // 0x2690
    int unk2694;              // 0x2694
    BYTE unk2698[0x8];        // 0x2698
    int unk26a0;              // 0x26a0
    int unk26a4;              // 0x26a4
    int unk26a8;              // 0x26a8
    int unk26ac;              // 0x26ac
    Scene *unk26b0;        // 0x26b0
    Scene *unk26b4;        // 0x26b4
    BYTE unk26b8[0x54];       // 0x26b8
    float unk270c[16];        // 0x270c
    float wheelMatrix[4][16]; // 0x274c
    Vec4 unk284c;             // 0x284c
    BYTE unk285c[0x30];       // 0x285c
    float unk288c;            // 0x288c
    float unk2890;            // 0x2890
    float unk2894;            // 0x2894
    BYTE unk2898[0x4];        // 0x2898
    float unk289c;            // 0x289c
    int unk28a0;              // 0x28a0
    int unk28a4;              // 0x28a4
    int unk28a8;              // 0x28a8
    BYTE unk28ac[0xc];        // 0x28ac
    int unk28b8;              // 0x28b8
    TrailSlot unk28bc[2];     // 0x28bc
    float unk2cf4[4];         // 0x2cf4
    Trail unk2d04[2];         // 0x2d04
    int unk3134;              // 0x3134
    Vec4 unk3138;             // 0x3138
    Vec4 unk3148;             // 0x3148
    float unk3158;            // 0x3158
    BYTE unk315c[0x130];      // 0x315c
    CarFx unk328c;            // 0x328c
    CarFx unk33cc;            // 0x33cc
    BYTE unk350c[0x10];       // 0x350c
    Vec4 unk351c[64];         // 0x351c
    DWORD unk391c;            // 0x391c
    DWORD unk3920;            // 0x3920
    int unk3924;              // 0x3924
    int unk3928;              // 0x3928
    BYTE unk392c[0x38];       // 0x392c
    SkidMark skids[4];        // 0x3964
    int unk6da4;              // 0x6da4
    int unk6da8;              // 0x6da8
    int unk6dac;              // 0x6dac
    int unk6db0;              // 0x6db0
    int unk6db4[64];          // 0x6db4
    int unk6eb4[64];          // 0x6eb4
    int unk6fb4[64];          // 0x6fb4
    int unk70b4[64];          // 0x70b4
    DWORD unk71b4;            // 0x71b4
    DWORD unk71b8;            // 0x71b8
    DWORD unk71bc;            // 0x71bc
    DWORD unk71c0;            // 0x71c0
    int unk71c4;              // 0x71c4
    DWORD unk71c8;            // 0x71c8
    Vec4 unk71cc;             // 0x71cc
    DWORD unk71dc;            // 0x71dc
    DWORD unk71e0;            // 0x71e0
    DWORD unk71e4;            // 0x71e4
    int unk71e8;              // 0x71e8
    unsigned int unk71ec;     // 0x71ec
    int unk71f0;              // 0x71f0
    int unk71f4;              // 0x71f4
    BYTE unk71f8[0x4];        // 0x71f8
    unsigned int unk71fc;     // 0x71fc
    BYTE unk7200[0x14];       // 0x7200
    float unk7214;            // 0x7214
    float unk7218;            // 0x7218
    float unk721c;            // 0x721c
    BYTE unk7220[0x4];        // 0x7220
    float unk7224;            // 0x7224
    float unk7228;            // 0x7228
    float unk722c;            // 0x722c
    BYTE unk7230[0x4];        // 0x7230
    DWORD unk7234;            // 0x7234
    float unk7238;            // 0x7238
    float unk723c;            // 0x723c
    float unk7240;            // 0x7240
    int unk7244;              // 0x7244
    int unk7248;              // 0x7248
    int unk724c;              // 0x724c
    int unk7250;              // 0x7250
    int unk7254;              // 0x7254
    DWORD unk7258;            // 0x7258
    int unk725c;              // 0x725c
    int unk7260;              // 0x7260
    int unk7264;              // 0x7264
    Replay *unk7268;          // 0x7268
    BYTE unk726c[0x4];        // 0x726c
    Body body;                // 0x7270
    int unk7614;              // 0x7614
    int unk7618;              // 0x7618
    BYTE unk761c[0xc];        // 0x761c
    int unk7628;              // 0x7628
    int unk762c;              // 0x762c
    int unk7630;              // 0x7630
    unsigned int unk7634;     // 0x7634
    int unk7638;              // 0x7638
    int unk763c;              // 0x763c
    int unk7640;              // 0x7640
    int unk7644;              // 0x7644
    int unk7648;              // 0x7648
    BYTE unk764c[0x8];        // 0x764c
    int unk7654;              // 0x7654
    BYTE unk7658[0x1c];       // 0x7658
    int unk7674;              // 0x7674
    int unk7678;              // 0x7678
    int unk767c;              // 0x767c
    DWORD unk7680;            // 0x7680
    float unk7684;            // 0x7684
    CarRace race;             // 0x7688
};

// One of the four per-player blocks at 0x498248 (0x74c bytes each).
struct GameSlot
{
    int active;            // 0x000
    unsigned int camMode;  // 0x004
    Camera cam;            // 0x008
    BYTE unk058[0x10];     // 0x058
    Vec4 prevTarget;       // 0x068
    float roll;            // 0x078
    Vec4 axisX;            // 0x07c
    Vec4 axisY;            // 0x08c
    Vec4 axisZ;            // 0x09c
    Car *data;             // 0x0ac
    float fov;             // 0x0b0
    float unk0b4;          // 0x0b4
    float unk0b8;          // 0x0b8
    float unk0bc;          // 0x0bc
    float unk0c0;          // 0x0c0
    float velX;            // 0x0c4
    float velY;            // 0x0c8
    float velZ;            // 0x0cc
    float velW;            // 0x0d0
    float speed;           // 0x0d4
    float accelX;          // 0x0d8
    float accelY;          // 0x0dc
    float accelZ;          // 0x0e0
    BYTE unk0e4[0x4];      // 0x0e4
    DWORD angX;            // 0x0e8
    DWORD angY;            // 0x0ec
    DWORD angZ;            // 0x0f0
    float angVelX;         // 0x0f4
    float angVelY;         // 0x0f8
    float angVelZ;         // 0x0fc
    BYTE unk100[0x4];      // 0x100
    float angAccelX;       // 0x104
    float angAccelY;       // 0x108
    float angAccelZ;       // 0x10c
    BYTE unk110[0x8];      // 0x110
    Vec4 planeLeft;        // 0x118
    Vec4 planeRight;       // 0x128
    Vec4 planeTop;         // 0x138
    Vec4 planeBottom;      // 0x148
    BYTE unk158[0x44];     // 0x158
    float unk19c;          // 0x19c
    float fov2;            // 0x1a0
    int unk1a4;            // 0x1a4
    CameraPath *path;      // 0x1a8
    Vec4 unk1ac;           // 0x1ac
    unsigned int unk1bc;   // 0x1bc
    float unk1c0;          // 0x1c0
    float unk1c4;          // 0x1c4
    BYTE unk1c8[0x4];      // 0x1c8
    CameraPreset *unk1cc;  // 0x1cc
    int unk1d0;            // 0x1d0
    int unk1d4;            // 0x1d4
    CameraPreset *preset;  // 0x1d8
    int presetMode;        // 0x1dc
    int fovPending;        // 0x1e0
    float fovNext;         // 0x1e4
    int fadeActive;       // 0x1e8
    int fadeTime;         // 0x1ec
    int fadeValue;        // 0x1f0
    int fadeType;         // 0x1f4
    int fadeDuration;     // 0x1f8
    int fadeDelay;        // 0x1fc
    int fadeEnd;          // 0x200
    int fadeFrom;         // 0x204
    int fadeTo;           // 0x208
    float fadeScale;      // 0x20c
    SlotFx fx;            // 0x210
    BYTE unk4a0[0xc];     // 0x4a0
    SlotEvent events[8];  // 0x4ac
};

// 64 entries at 0x62a078
struct Unk62a078
{
    int unk00;          // 0x00 1 = live, 2 = dead
    DWORD flags;        // 0x04
    Vec4 pos;           // 0x08
    BYTE unk18[0x40];   // 0x18
    float vel[3];       // 0x58
    BYTE unk64[0x4];    // 0x64
    float unk68;        // 0x68
    float gravity;      // 0x6c
    DWORD time;         // 0x70
    DWORD lifetime;     // 0x74
    int mode;           // 0x78
    int unk7c;          // 0x7c
    DWORD *anim;        // 0x80
    int frame;          // 0x84
    int texture;        // 0x88
    DWORD colors[3];    // 0x8c
    DWORD unk98;        // 0x98
    float size;         // 0x9c
    float sizeIn;       // 0xa0
    float sizeOut;      // 0xa4
    float sizeNow;      // 0xa8
    float alpha;        // 0xac
    float alphaIn;      // 0xb0
    float alphaOut;     // 0xb4
    float alphaNow;     // 0xb8
    float angle;        // 0xbc
    float spin;         // 0xc0
    float colorIn;      // 0xc4
    float colorOut;     // 0xc8
    DWORD color;        // 0xcc
};

extern Unk62a078 g_62a078[0x40];
extern int g_62d478;

// Level box: an axis frame (position, scale, V, N) with a sound/EAX zone id.
struct SoundZone
{
    int id;           // 0x00
    int unk04;        // 0x04
    float bounds[16]; // 0x08
};

extern SoundZone g_483f98[32];

// Device-specific input snapshot, copied verbatim from InputDevice to Controller.
struct InputState
{
    int unk00;          // 0x00
    int unk04;          // 0x04
    int range;          // 0x08
    int x;                  // 0x0c
    int y;                  // 0x10
    int z;                  // 0x14
    int rx;                 // 0x18
    int ry;                 // 0x1c
    int rz;                 // 0x20
    int sliders[2];         // 0x24
    DWORD pov[2];           // 0x2c
    BYTE unk34[0x8];        // 0x34
    BYTE buttons[0x20];     // 0x3c
    BYTE prevButtons[0x20]; // 0x5c
};

// One mesh of a Scene; each Scene::lods entry points at objectCount of these.
struct ObjectDef
{
    short visible;     // 0x00, 0 hides the mesh
    WORD flags;        // 0x02
    WORD unk04;        // 0x04
    BYTE unk06[0x2];   // 0x06
    Vec4 *matrix;      // 0x08
    BYTE unk0c[0x18];  // 0x0c
    WORD vertCount;    // 0x24, entries in verts
    WORD unk26;        // 0x26, entries in unk2c
    WORD pointCount;   // 0x28, entries in points
    BYTE unk2a[0x2];   // 0x2a
    BYTE *unk2c;       // 0x2c, 16 bytes per entry, colour at +0xc
    Vec4 *points;      // 0x30
    BYTE *verts;       // 0x34, 8 bytes per vertex
    BYTE unk38[0x8];   // 0x38
};

struct SceneView
{
    BYTE unk00[0x2c]; // 0x00
    int unk2c;        // 0x2c
    int unk30;        // 0x30
    int unk34;        // 0x34
};

struct SceneEntry
{
    DWORD unk00[4];
};

struct Scene
{
    BYTE unk00[0x2];     // 0x00
    WORD flags;          // 0x02
    short unk04;         // 0x04
    BYTE unk06[0x6];     // 0x06
    Camera *camera;      // 0x0c
    BYTE unk10[0x14];    // 0x10
    DWORD objectCount;   // 0x24
    SceneEntry *unk28;   // 0x28
    BYTE unk2c[0x14];    // 0x2c
    DWORD *unk40;        // 0x40
    SceneView *view;     // 0x44
    ObjectDef *lods[5];  // 0x48, object list per level of detail
    int lod;             // 0x5c, current level of detail
    char **textures;     // 0x60, NULL-terminated
    int unk64;           // 0x64
};

// Scene render list entry; a list runs until a NULL scene.
struct SceneSlot
{
    Scene *scene; // 0x00
    int unk04;    // 0x04
    void *data;   // 0x08
    int size;     // 0x0c
};

// Two NULL-terminated lists share this array: the menu list from [0], the race list from [2].
extern SceneSlot g_636418[16];

// 10 entries at 0x576618
struct InputSlot
{
    int present;      // 0x00
    int type;         // 0x04
    int unk08;        // 0x08
    InputState state; // 0x0c
};

// 4 entries at 0x62d580
struct Controller
{
    int active;         // 0x000
    int prevActive;     // 0x004
    int unk008;         // 0x008
    int type;           // 0x00c
    int mode;           // 0x010
    int keyMap;         // 0x014
    int unk018;         // 0x018
    int unk01c;         // 0x01c
    int unk020;         // 0x020
    int unk024;         // 0x024
    int unk028;         // 0x028
    InputState state;   // 0x02c
    BYTE unk0a8[0x100]; // 0x0a8
    BYTE keys[7];       // 0x1a8
    BYTE prevKeys[7];   // 0x1af
    BYTE unk1b6[0x26];  // 0x1b6
};

extern InputSlot g_576618[10];
extern Controller g_62d580[4];
extern Controller *g_61b744;

// Line of the in-race pause menu; the list ends at text 0.
struct PauseItem
{
    int active;       // 0x00
    int text;         // 0x04
    int x;            // 0x08
    int y;            // 0x0c
    void (*action)(); // 0x10
    int value;        // 0x14, text drawn to the right, 0 for none
};

extern PauseItem g_485120[8];

extern GameSlot *g_4722d0;
extern SlotFx *g_61b740;
extern GameSlot g_498248[4];

extern BYTE g_62dcf0[256];

extern int g_60d618;
extern int g_60d620;
extern int g_60df9c;
extern int g_DisableFramerateCorrection;
extern int g_60f2c0;
extern DWORD g_60f2c4;
extern int g_473a24;
extern float g_4d5b18;
extern int g_4d5b1c;

// fpu
void FUN_4294f0();
void FUN_429510();

// timer

// input
void FUN_4243f0();
void FUN_4244c0();
int FUN_424520(int index);
void FUN_45ec00();
void FUN_45ec20();
void FUN_45ee60();
void FUN_45ef00();
void FUN_45ef30(Controller *c, BYTE *map);
void FUN_45f020(Controller *c, BYTE *map);
void FUN_45f110();
void FUN_45f210();
void FUN_40d860();
void FUN_40dad0();
void FUN_45f8f0(int a, int b);

// per-tick game logic
void FUN_4023d0();
void FUN_4023f0();
void FUN_4028d0(int mode);
void FUN_43d200();
void FUN_405210();
void FUN_427140();
void FUN_45e1d0();
void FUN_415df0();
void FUN_443a80();
void FUN_418a90();
void FUN_401770();
void FUN_447c90();
void FUN_40de30();
void FUN_446110();

// sound
void FUN_45f8e0(int target, int step);
void FUN_460ca0();
void FUN_45f7d0(int a, int b);
void FUN_45f880();
void FUN_460af0(int a);
void FUN_460ce0();
void FUN_460df0();
void FUN_462200();
void FUN_462280();

void FUN_447b60();

// controller connect/disconnect
void FUN_4422c0();
void FUN_442350();
void FUN_447c30(int a);
void FUN_41bdd0();
void FUN_460dd0();
void FUN_45fa00();
void FUN_447bd0(int a);
void FUN_460cb0(int a);
void FUN_45fa30();

// mode switch
void FUN_431810();
void FUN_42eaa0();
void FUN_442030();

extern Car g_49a1f8[6];
extern Car *g_4d5bb8;
extern Camera g_4864e8;
void FUN_410a10(int index);
extern Car *g_474630;
extern Driver g_60f02c[6];
extern DWORD g_60f2b0;
void FUN_401220(int type, int mode, unsigned int points);
#endif /* GAMEUPDATE_H */
