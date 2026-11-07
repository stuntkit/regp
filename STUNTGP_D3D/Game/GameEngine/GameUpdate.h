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
    BYTE unk023c[0x18];      // 0x023c
    float unk254;            // 0x0254
    BYTE unk0258[0xa60];     // 0x0258
    Vector4 unkcb8[4];       // 0x0cb8
    BYTE unk0cf8[0x280];     // 0x0cf8
    float unkf78;            // 0x0f78
    float unkf7c;            // 0x0f7c
    BYTE unk0f80[0xc28];     // 0x0f80
    int active;              // 0x1ba8
    float unk1bac;           // 0x1bac
    float unk1bb0;           // 0x1bb0
    float unk1bb4;           // 0x1bb4
    BYTE unk1bb8[0xd4];      // 0x1bb8
    float unk1c8c[3];        // 0x1c8c
    BYTE unk1c98[0x58];      // 0x1c98
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
    BYTE keyMap[13];         // 0x2284
    BYTE unk2291[0xf];       // 0x2291
    BYTE prevControls[10];   // 0x22a0
    BYTE controls[10];       // 0x22aa
    BYTE unk22b4[0x54];      // 0x22b4
    float unk2308[4];        // 0x2308
    BYTE unk2318[0x10];      // 0x2318
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
    BYTE unk23b4[0xf8];      // 0x23b4
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
    BYTE unk26b8[0x4bb0];    // 0x26b8
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
    BYTE unk7684[0xa0];      // 0x7684
};

// 6 entries at 0x60f050, one per car
struct Driver
{
    char name[0x40];  // 0x00
    int unk40;        // 0x40
    int unk44;        // 0x44
    BYTE unk48[0x1c]; // 0x48
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

// Device-specific input snapshot, copied verbatim from InputDevice to Controller.
struct InputState
{
    int unk00;          // 0x00
    int unk04;          // 0x04
    int range;          // 0x08
    int x;              // 0x0c
    int y;              // 0x10
    BYTE unk14[0x28];   // 0x14
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
    int unk018;         // 0x018 index into g_49a1f8, 0xffff if none
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
void FUN_410a10(int index);

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
extern Car *g_4d5bb8;
extern Car *g_474630;
extern Driver g_60f050[6];
extern DWORD g_60f2b0;
#endif /* GAMEUPDATE_H */
