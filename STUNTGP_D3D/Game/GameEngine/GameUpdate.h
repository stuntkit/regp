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

// Preset a GameSlot camera is reset to (GameSlot::preset).
struct CameraPreset
{
    Vec4 pos;    // 0x00
    Vec4 target; // 0x10
    Vec4 up;     // 0x20
    float fov;   // 0x30
    int unk34;   // 0x34
    float roll;  // 0x38
};

struct Fader
{
    BYTE unk00[0x10]; // 0x00
    int active;       // 0x10
    float value;      // 0x14
    float target;     // 0x18
    BYTE unk1c[0x8];  // 0x1c
};

struct SlotFx
{
    int unk000;       // 0x000
    int delay;        // 0x004
    Fader faders[9];  // 0x008
};

struct SlotEvent
{
    int count;        // 0x00
    int unk04;        // 0x04
    DWORD order;      // 0x08
    BYTE unk0c[0x48]; // 0x0c
};

// 6 entries at 0x49a1f8
struct Car
{
    BYTE unk0000[0xf78];  // 0x0000
    int unkf78;           // 0x0f78
    BYTE unkf7c[0xc2c];   // 0x0f7c
    int active;           // 0x1ba8
    float posX;           // 0x1bac
    float posY;           // 0x1bb0
    float posZ;           // 0x1bb4
    BYTE unk1bb8[0x6b8];  // 0x1bb8
    int unk2270;          // 0x2270
    BYTE unk2274[0x68];   // 0x2274
    float unk22dc;        // 0x22dc
    float unk22e0;        // 0x22e0
    float unk22e4;        // 0x22e4
    BYTE unk22e8[0xdc];   // 0x22e8
    int unk23c4;          // 0x23c4
    BYTE unk23c8[0x118];  // 0x23c8
    int unk24e0;          // 0x24e0
    int unk24e4;          // 0x24e4
    BYTE unk24e8[0x80];   // 0x24e8
    int unk2568;          // 0x2568
    int unk256c;          // 0x256c
    int unk2570;          // 0x2570
    int unk2574;          // 0x2574
    BYTE unk2578[0x138];  // 0x2578
    int unk26b0;          // 0x26b0
    int unk26b4;          // 0x26b4
    BYTE unk26b8[0x4bb0]; // 0x26b8
    short *unk7268;       // 0x7268
    BYTE unk726c[0x3dc];  // 0x726c
    int unk7648;          // 0x7648
    BYTE unk764c[0x3c];   // 0x764c
    DWORD unk7688;        // 0x7688
    BYTE unk768c[0x14];   // 0x768c
    int unk76a0;          // 0x76a0
    int unk76a4;          // 0x76a4
    BYTE unk76a8[0xc];    // 0x76a8
    DWORD unk76b4;        // 0x76b4
    BYTE unk76b8[0x6c];   // 0x76b8
};

// One of the four per-player blocks at 0x498248 (0x74c bytes each).
struct GameSlot
{
    int active;            // 0x000
    int camMode;           // 0x004
    Camera cam;            // 0x008
    BYTE unk058[0x20];     // 0x058
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
    BYTE unk0d0[0x4];      // 0x0d0
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
    BYTE unk110[0x90];     // 0x110
    float fov2;            // 0x1a0
    int unk1a4;            // 0x1a4
    void *unk1a8;          // 0x1a8
    BYTE unk1ac[0x20];     // 0x1ac
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
    BYTE unk35c[0x150];   // 0x35c
    SlotEvent events[8];  // 0x4ac
};

// Device-specific input snapshot, copied verbatim from InputDevice to Controller.
struct InputState
{
    int unk00;          // 0x00
    int unk04;          // 0x04
    int range;          // 0x08
    int x;              // 0x0c
    int y;              // 0x10
    BYTE unk14[0x28];   // 0x14
    BYTE buttons[0x40]; // 0x3c
};

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
void FUN_4023f0();
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
#endif /* GAMEUPDATE_H */
