#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct GameSlotData
{
    BYTE unk0000[0x23c4]; // 0x0000
    int unk23c4;          // 0x23c4
    BYTE unk23c8[0x118];  // 0x23c8
    int unk24e0;          // 0x24e0
    BYTE unk24e4[0x5164]; // 0x24e4
    int unk7648;          // 0x7648
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

// One of the four per-player blocks at 0x498248 (0x74c bytes each).
struct Car
{
    BYTE unk0000[0xf78];  // 0x0000
    int unkf78;           // 0x0f78
    BYTE unkf7c[0xc2c];   // 0x0f7c
    int active;           // 0x1ba8
    BYTE unk1bac[0x6c4];  // 0x1bac
    int unk2270;          // 0x2270
    BYTE unk2274[0x13c];  // 0x2274
    float unk23b0;        // 0x23b0
    BYTE unk23b4[0x8];    // 0x23b4
    int unk23bc;          // 0x23bc
    BYTE unk23c0[0xc];    // 0x23c0
    int unk23cc;          // 0x23cc
    int unk23d0;          // 0x23d0
    int unk23d4;          // 0x23d4
    int unk23d8;          // 0x23d8
    BYTE unk23dc[0x108];  // 0x23dc
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
    BYTE unk726c[0x4b8];  // 0x726c
};

struct GameSlot
{
    int active;           // 0x000
    int unk004;           // 0x004
    float unk008;         // 0x008
    float unk00c;         // 0x00c
    float unk010;         // 0x010
    BYTE unk014[0x78];    // 0x014
    float unk08c;         // 0x08c
    float unk090;         // 0x090
    float unk094;         // 0x094
    int unk098;           // 0x098
    float unk09c;         // 0x09c
    float unk0a0;         // 0x0a0
    float unk0a4;         // 0x0a4
    int unk0a8;           // 0x0a8
    GameSlotData *data;   // 0x0ac
    BYTE unk0b0[0x14];    // 0x0b0
    float unk0c4;         // 0x0c4
    float unk0c8;         // 0x0c8
    float unk0cc;         // 0x0cc
    BYTE unk0d0[0x8];     // 0x0d0
    int unk0d8;           // 0x0d8
    int unk0dc;           // 0x0dc
    int unk0e0;           // 0x0e0
    BYTE unk0e4[0x20];    // 0x0e4
    int unk104;           // 0x104
    int unk108;           // 0x108
    int unk10c;           // 0x10c
    BYTE unk110[0xd8];    // 0x110
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
