#ifndef MENUUPDATE_H
#define MENUUPDATE_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct Unk4d5cc0;

struct MenuSlot
{
    int unk00;
    int unk04;
    int unk08;
};

struct ScoreEntry
{
    int time;
    char name[4];
};

struct ScoreTable
{
    int unk00;
    ScoreEntry entries[10];
};

struct MenuSlot160
{
    BYTE unk000[8];
    int unk008; // 0x008
    BYTE unk00c[0x160 - 0xc];
};

struct MenuSlot20
{
    int unk00;
    BYTE unk04[0x1c];
};

struct MenuRecord
{
    int unk00;
    BYTE unk04[0x80];
};

struct MenuSponsor
{
    int unk00; // 0x00
    int id;    // 0x04, matched against ShopItem::sponsor
};

struct MenuRoundCar
{
    int unk00; // 0x00
    int unk04; // 0x04
    int unk08; // 0x08
};

struct MenuRound
{
    int track;            // 0x00
    int unk04;            // 0x04
    MenuRoundCar cars[5]; // 0x08
};

// Shop catalogue entry.
struct ShopItem
{
    int price;           // 0x000
    BYTE unk004[0x120];  // 0x004
    int sponsor;         // 0x124
    int unk128;          // 0x128
};

// Car%02d row of the front-end csv, read by FUN_435e30.
struct ShopCar
{
    int unk00;        // 0x00
    int unk04;        // 0x04
    int unk08;        // 0x08
    BYTE unk0c[0x30]; // 0x0c
    int parts[11][4]; // 0x3c, filled by FUN_435f60
};

struct ShopEntry
{
    ShopCar car;   // 0x000
    ShopItem item; // 0x0ec
};

// Menu entry; entries with a negative id are skipped, a zero text ends the list.
struct MenuItem
{
    int id;      // 0x00
    DWORD unk04; // 0x04, ARGB
    DWORD unk08; // 0x08, ARGB
    int text;    // 0x0c, front-end text id
    int unk10;   // 0x10
    int unk14;   // 0x14
    int unk18;   // 0x18
    int unk1c;   // 0x1c
};

struct MenuDef
{
    int unk00;       // 0x00
    float unk04;     // 0x04
    int unk08;       // 0x08
    float x;         // 0x0c
    float y;         // 0x10
    float scale;     // 0x14
    int unk18;       // 0x18
    float unk1c;     // 0x1c
    int unk20;       // 0x20
    int unk24;       // 0x24
    MenuItem *items; // 0x28
    int unk2c;       // 0x2c
};

struct MenuLanguage
{
    char name[0x20];
    int id;
};

// Front-end state, cleared as a whole by FUN_43d0b0.
struct MenuState
{
    BYTE unk0000[8];
    BYTE unlocked[0x34];      // 0x0008
    BYTE unlockedSaved[0x34]; // 0x003c
    int unk0070;              // 0x0070
    int unk0074;              // 0x0074
    int unk0078;              // 0x0078
    int music;   // 0x007c
    int sfx;     // 0x0080
    int unk0084; // 0x0084
    int offsetX; // 0x0088
    int offsetY; // 0x008c
    int unk0090; // 0x0090
    int unk0094; // 0x0094
    MenuSlot unk0098[5];
    int unk00d4; // 0x00d4
    int unk00d8; // 0x00d8
    int unk00dc; // 0x00dc
    int unk00e0; // 0x00e0
    int unk00e4; // 0x00e4
    int unk00e8; // 0x00e8
    BYTE unk00ec[0x114 - 0xec];
    // High-score tables, reset by FUN_43c130.
    ScoreEntry unk0114[19][4];  // 0x0114
    ScoreEntry unk0374[100];    // 0x0374
    ScoreTable unk0694[25];     // 0x0694
    BYTE unk0ec8[0xf1c - 0xec8];
    MenuSlot160 unk0f1c[8];     // 0x0f1c
    ScoreEntry unk1a1c[25][4];  // 0x1a1c
    BYTE unk1d3c[0x1d5c - 0x1d3c];
    ScoreEntry unk1d5c[10];     // 0x1d5c
    ScoreEntry unk1dac[10];     // 0x1dac
    ScoreEntry unk1dfc[100];    // 0x1dfc
    BYTE saved[0x2114]; // 0x211c, copy of 0x0008..0x211c
    BYTE unk4230[0x8];
    int unk4238; // 0x4238
    int unk423c; // 0x423c, entries used in unk46ac
    int unk4240; // 0x4240
    int unk4244; // 0x4244
    BYTE unk4248[0x4258 - 0x4248];
    int language;               // 0x4258, id of the loaded front-end language
    MenuLanguage languages[8];  // 0x425c, from Setup\languagePC.csv
    int languageCount;          // 0x437c
    BYTE unk4380[0x4398 - 0x4380];
    int unk4398;     // 0x4398, entries used in unk439c
    int unk439c[20]; // 0x439c
    BYTE unk43ec[0x4408 - 0x43ec];
    int unk4408;     // 0x4408, entries used in unk440c
    int unk440c[26]; // 0x440c
    int unk4474;     // 0x4474
    int unk4478; // 0x4478
    BYTE unk447c[0x44d0 - 0x447c];
    int unk44d0; // 0x44d0
    BYTE unk44d4[0x46a8 - 0x44d4];
    int unk46a8; // 0x46a8
    int unk46ac[4]; // 0x46ac
    BYTE unk46bc[0x46c4 - 0x46bc];
    int unk46c4; // 0x46c4
    int unk46c8; // 0x46c8
    BYTE unk46cc[0x46d8 - 0x46cc];
    int unk46d8; // 0x46d8
    int unk46dc; // 0x46dc
    BYTE unk46e0[0x13148 - 0x46e0];
    Unk4d5cc0 *unk13148; // 0x13148
    BYTE unk1314c[0x19d78 - 0x1314c];
    int unk19d78;          // 0x19d78, index into unk0f1c
    MenuSlot160 unk19d7c;  // 0x19d7c
    // Championship settings, read by FUN_435b60; names are the csv keys.
    int numberOfRounds;          // 0x19edc
    int bonusRounds[4];          // 0x19ee0
    int saveRounds[6];           // 0x19ef0
    int sponsorDiscountPercent;  // 0x19f08
    int usedItemDiscountPercent; // 0x19f0c
    MenuSponsor sponsors[7];     // 0x19f10, [1..6] used
    int positions[6][4];         // 0x19f48
    MenuRound rounds[21];        // 0x19fa8
    BYTE unk1a53c[0x1a544 - 0x1a53c];
    MenuSlot20 unk1a544[6]; // 0x1a544
    BYTE unk1a604[0x1a6a4 - 0x1a604];
    int unk1a6a4; // 0x1a6a4
    int unk1a6a8; // 0x1a6a8
    BYTE unk1a6ac[0x1a6b0 - 0x1a6ac];
    MenuRecord unk1a6b0[64]; // 0x1a6b0, count unknown
    BYTE unk1c7b0[0x1dae8 - 0x1c7b0];
};

extern MenuState g_menuState;

struct PoolObject;

// Front-end object; the first 0x14 bytes are the pool object header.
struct MenuObject
{
    DWORD unk00[5]; // 0x00
    int unk14;      // 0x14
    int unk18;      // 0x18
    float unk1c;    // 0x1c
    float unk20;    // 0x20
};

struct Unk4516c0
{
    DWORD unk00[5];    // 0x00
    PoolObject *unk14; // 0x14
    PoolObject *unk18; // 0x18
    int unk1c;         // 0x1c
    int unk20;         // 0x20
    int unk24;         // 0x24
    int unk28;         // 0x28
};

// Front-end object owning one child object at 0x14.
struct MenuHolder
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
};

void FUN_424bd0(float x, float y);
int FUN_43d790(int value, int min, int max);
float FUN_43d810(float current, float target, float rate);
int FUN_43dd70();
void FUN_43dd90(int player);
void FUN_43de40();
void FUN_43dee0();
void FUN_43f310(PoolObject *screen);
void FUN_43f610();
void FUN_440770(int a, int b);
void FUN_440880(int a);
void FUN_434b50();
int FUN_437360(int track);
int FUN_437da0(int track);
void FUN_439e30();
void FUN_43c060();
void FUN_43c130();
void FUN_43c370();
void FUN_43c400();
void FUN_43d280();
void FUN_43dd10(DWORD color);
void FUN_43dda0();
void FUN_4408e0();
void FUN_440ae0();
void FUN_436eb0();
void FUN_436ed0();
void FUN_436f00(int player);
BYTE FUN_436f60(BYTE *keys, int button);
int FUN_437090(int player);
void FUN_43c000();
void FUN_43eff0();
int FUN_440c40(int id);

#endif /* MENUUPDATE_H */
