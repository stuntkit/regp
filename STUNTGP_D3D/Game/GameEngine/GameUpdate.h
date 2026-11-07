#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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
    BYTE unk14[0x4];    // 0x14
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
    BYTE unk0c[0x4];  // 0x0c
    int active;       // 0x10
    float value;      // 0x14
    float target;     // 0x18
    BYTE unk1c[0x8];  // 0x1c
};

struct SlotFx
{
    int unk000;       // 0x000
    int delay;        // 0x004
    Fader faders[18]; // 0x008
};

struct SlotEvent
{
    int count;        // 0x00
    int unk04;        // 0x04
    DWORD order;      // 0x08
    BYTE unk0c[0x48]; // 0x0c
};

struct CarRace
{
    DWORD unk00;      // 0x00
    BYTE unk04[0x14]; // 0x04
    int unk18;        // 0x18
    int unk1c;        // 0x1c
    BYTE unk20[0x4];  // 0x20
    DWORD unk24;      // 0x24
    BYTE unk28[0x4];  // 0x28
    DWORD unk2c;      // 0x2c
    BYTE unk30[0x14]; // 0x30
    int unk44;        // 0x44
    int unk48;        // 0x48
    BYTE unk4c[0x50]; // 0x4c
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
    int unk00;          // 0x0000
    float unk04;        // 0x0004
    BYTE unk0008[0x4];  // 0x0008
    float unk0c;        // 0x000c
    float unk10;        // 0x0010
    BYTE unk0014[0x1c]; // 0x0014
    int unk30;          // 0x0030
    float unk34;        // 0x0034
    float unk38;        // 0x0038
    BYTE unk003c[0x3c]; // 0x003c
    int unk78;          // 0x0078
    BYTE unk007c[0x1c]; // 0x007c
};

// 6 entries at 0x60f050, one per car
struct Driver
{
    char name[0x40];  // 0x00
    int unk40;        // 0x40
    int unk44;        // 0x44
    BYTE unk48[0x1c]; // 0x48
};

// 6 entries at 0x49a1f8
struct Car
{
    BYTE unk0000[0x220];     // 0x0000
    float unk220;            // 0x0220
    float unk224;            // 0x0224
    float unk228;            // 0x0228
    float unk22c;            // 0x022c
    float unk230;            // 0x0230
    float unk234;            // 0x0234
    float unk238;            // 0x0238
    BYTE unk023c[0x8];       // 0x023c
    float unk244;            // 0x0244
    BYTE unk0248[0xc];       // 0x0248
    float unk254;            // 0x0254
    BYTE unk0258[0xa60];     // 0x0258
    Vector4 unkcb8[4];       // 0x0cb8
    BYTE unk0cf8[0x280];     // 0x0cf8
    float unkf78;            // 0x0f78
    float unkf7c;            // 0x0f7c
    BYTE unk0f80[0xc28];     // 0x0f80
    int active;              // 0x1ba8
    float posX;              // 0x1bac
    float posY;              // 0x1bb0
    float posZ;              // 0x1bb4
    float posW;              // 0x1bb8
    BYTE unk1bbc[0x10];      // 0x1bbc
    float matrix[16];        // 0x1bcc
    BYTE unk1c0c[0x80];      // 0x1c0c
    float unk1c8c[3];        // 0x1c8c
    BYTE unk1c98[0x24];      // 0x1c98
    Vec4 axisX;              // 0x1cbc
    Vec4 axisY;              // 0x1ccc
    Vec4 axisZ;              // 0x1cdc
    BYTE unk1cec[0x4];       // 0x1cec
    float unk1cf0;           // 0x1cf0
    BYTE unk1cf4[0x4];       // 0x1cf4
    int unk1cf8;             // 0x1cf8
    BYTE unk1cfc[0x20c];     // 0x1cfc
    float unk1f08;           // 0x1f08
    BYTE unk1f0c[0x4];       // 0x1f0c
    int unk1f10;             // 0x1f10
    BYTE unk1f14[0xbc];      // 0x1f14
    float unk1fd0;           // 0x1fd0
    BYTE unk1fd4[0x4];       // 0x1fd4
    int unk1fd8;             // 0x1fd8
    BYTE unk1fdc[0x4];       // 0x1fdc
    Wheel wheels[4];         // 0x1fe0
    BYTE unk2240[0x30];      // 0x2240
    float unk2270;           // 0x2270
    BYTE unk2274[0x4];       // 0x2274
    int unk2278;             // 0x2278
    int inputMode;           // 0x227c
    int unk2280;             // 0x2280
    BYTE keyMap[0xd];        // 0x2284
    BYTE unk2291[0xf];       // 0x2291
    BYTE prevControls[0xa];  // 0x22a0
    BYTE controls[0xa];      // 0x22aa
    BYTE unk22b4[0x14];      // 0x22b4
    int unk22c8;             // 0x22c8
    Vec4 camOffset;          // 0x22cc
    float unk22dc;           // 0x22dc
    float unk22e0;           // 0x22e0
    float unk22e4;           // 0x22e4
    BYTE unk22e8[0x4];       // 0x22e8
    float unk22ec;           // 0x22ec
    float unk22f0;           // 0x22f0
    float unk22f4;           // 0x22f4
    BYTE unk22f8[0x4];       // 0x22f8
    float unk22fc;           // 0x22fc
    float unk2300;           // 0x2300
    int unk2304;             // 0x2304
    float unk2308[4];        // 0x2308
    float unk2318[4];        // 0x2318
    float unk2328;           // 0x2328
    float unk232c;           // 0x232c
    float unk2330;           // 0x2330
    BYTE unk2334[0x8];       // 0x2334
    int unk233c[4];          // 0x233c
    int unk234c;             // 0x234c
    int unk2350;             // 0x2350
    int unk2354;             // 0x2354
    int unk2358;             // 0x2358
    int unk235c;             // 0x235c
    int unk2360;             // 0x2360
    int unk2364;             // 0x2364
    int unk2368;             // 0x2368
    int unk236c;             // 0x236c
    int unk2370;             // 0x2370
    int unk2374;             // 0x2374
    int unk2378;             // 0x2378
    int unk237c;             // 0x237c
    int unk2380;             // 0x2380
    int unk2384;             // 0x2384
    int unk2388;             // 0x2388
    int unk238c;             // 0x238c
    int unk2390;             // 0x2390
    int unk2394;             // 0x2394
    int unk2398;             // 0x2398
    int unk239c;             // 0x239c
    int unk23a0;             // 0x23a0
    BYTE unk23a4[0xc];       // 0x23a4
    float unk23b0;           // 0x23b0
    BYTE unk23b4[0x8];       // 0x23b4
    int unk23bc;             // 0x23bc
    BYTE unk23c0[0x4];       // 0x23c0
    int unk23c4;             // 0x23c4
    BYTE unk23c8[0x4];       // 0x23c8
    int unk23cc;             // 0x23cc
    int unk23d0;             // 0x23d0
    int unk23d4;             // 0x23d4
    int unk23d8;             // 0x23d8
    BYTE unk23dc[0xd0];      // 0x23dc
    int unk24ac;             // 0x24ac
    BYTE unk24b0[0x30];      // 0x24b0
    int unk24e0;             // 0x24e0
    int unk24e4;             // 0x24e4
    int unk24e8;             // 0x24e8
    BYTE unk24ec[0x7c];      // 0x24ec
    int unk2568;             // 0x2568
    int unk256c;             // 0x256c
    float unk2570;           // 0x2570
    float unk2574;           // 0x2574
    BYTE unk2578[0x4];       // 0x2578
    float unk257c;           // 0x257c
    int unk2580;             // 0x2580
    BYTE unk2584[0x94];      // 0x2584
    float unk2618;           // 0x2618
    float unk261c;           // 0x261c
    BYTE unk2620[0x14];      // 0x2620
    float unk2634;           // 0x2634
    BYTE unk2638[0x8];       // 0x2638
    int unk2640;             // 0x2640
    BYTE unk2644[0x6c];      // 0x2644
    int unk26b0;             // 0x26b0
    int unk26b4;             // 0x26b4
    BYTE unk26b8[0x4b34];    // 0x26b8
    unsigned int unk71ec;    // 0x71ec
    BYTE unk71f0[0x48];      // 0x71f0
    float unk7238;           // 0x7238
    BYTE unk723c[0x2c];      // 0x723c
    unsigned short *unk7268; // 0x7268
    BYTE unk726c[0x3c0];     // 0x726c
    int unk762c;             // 0x762c
    BYTE unk7630[0x8];       // 0x7630
    int unk7638;             // 0x7638
    int unk763c;             // 0x763c
    BYTE unk7640[0x8];       // 0x7640
    int unk7648;             // 0x7648
    BYTE unk764c[0x34];      // 0x764c
    DWORD unk7680;           // 0x7680
    BYTE unk7684[0x4];       // 0x7684
    CarRace race;            // 0x7688
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
    BYTE unk1d0[0x4];      // 0x1d0
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
    float pos[3];       // 0x08
    BYTE unk14[0x44];   // 0x14
    float vel[3];       // 0x58
    BYTE unk64[0x8];    // 0x64
    float gravity;      // 0x6c
    DWORD time;         // 0x70
    DWORD lifetime;     // 0x74
    int mode;           // 0x78
    BYTE unk7c[0x4];    // 0x7c
    DWORD *anim;        // 0x80
    int frame;          // 0x84
    BYTE unk88[0x4];    // 0x88
    DWORD colors[3];    // 0x8c
    BYTE unk98[0x4];    // 0x98
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

struct ObjectDef
{
    BYTE unk00[0x8];  // 0x00
    Vec4 *matrix;     // 0x08
    BYTE unk0c[0x34]; // 0x0c
};

struct SceneView
{
    BYTE unk00[0x2c]; // 0x00
    int unk2c;        // 0x2c
    int unk30;        // 0x30
    int unk34;        // 0x34
};

struct Scene
{
    BYTE unk00[0xc];    // 0x00
    Camera *camera;     // 0x0c
    BYTE unk10[0x14];   // 0x10
    DWORD objectCount;  // 0x24
    BYTE unk28[0x1c];   // 0x28
    SceneView *view;    // 0x44
    ObjectDef *objects; // 0x48
};

extern Scene *g_636448;

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

extern GameSlot *g_4722d0;
extern SlotFx *g_61b740;
extern GameSlot g_498248[4];

// --- frame timing ---
extern DWORD g_612cfc;
extern DWORD g_612d00;
extern DWORD g_612d04;
extern DWORD g_612d08;

extern BYTE g_62dcf0[256];

extern int g_60d618;
extern int g_60d620;
extern int g_60df9c;
extern int g_DisableFramerateCorrection;
extern int g_60f2c0;
extern DWORD g_60f2c4;
extern int g_61294c;
extern DWORD g_612990;
extern int g_473a24;
extern float g_4d5b18;
extern int g_4d5b1c;
extern int g_61299c;
extern int g_61b634;
extern DWORD g_612954;
extern int g_612958;
extern int g_612970;
extern int g_612bf4;
extern int g_612950;
extern int g_61295c;
extern int g_612964;
extern int g_612968;
extern int g_61296c;

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
extern Driver g_60f050[6];
extern DWORD g_60f2b0;
#endif /* GAMEUPDATE_H */
