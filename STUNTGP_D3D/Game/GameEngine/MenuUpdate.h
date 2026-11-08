#ifndef MENUUPDATE_H
#define MENUUPDATE_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../../objects.h"

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

struct MenuRaceResult
{
    int position; // 0x00
    int unk04;    // 0x04, time
    int unk08;    // 0x08, time
    int unk0c;    // 0x0c, score
    int unk10;    // 0x10, score
};

struct ScoreList
{
    int unk00;           // 0x00
    int unk04;           // 0x04
    int unk08;           // 0x08
    int count;           // 0x0c
    ScoreEntry *entries; // 0x10
};

// High-score initials, copied as one 3-byte block.
struct Initials
{
    char c[3];
};

// Finisher name shown on the results table.
struct MenuName
{
    Initials name;      // 0x00
    BYTE unk03[0x19];   // 0x03
};

// Car%02d row of the front-end csv, read by FUN_435e30.
struct ShopCar
{
    int unk00;        // 0x00, set for a used car
    int unk04;        // 0x04
    int unk08;        // 0x08
    int parts[14][4]; // 0x0c, indexed by part id, 3..13 read from the csv
};

struct MenuSlot160
{
    int unk000;       // 0x000
    Initials name;    // 0x004
    BYTE unk007;      // 0x007
    int unk008;       // 0x008
    int money;        // 0x00c, spent in the shop
    int car;          // 0x010, index into MenuState::cars
    ShopCar carSetup; // 0x014
    int unk100;       // 0x100
    int unk104;       // 0x104
    int sponsor;      // 0x108, index into MenuState::sponsors
    int unk10c;       // 0x10c
    int unk110[5][4]; // 0x110
};

struct MenuSlot20
{
    int unk00;   // 0x00
    int unk04;   // 0x04
    int unk08;   // 0x08
    int unk0c;   // 0x0c
    int unk10;   // 0x10
    char name[8]; // 0x14
    int unk1c;   // 0x1c
};

// One "<name>, a, b, c, d" row of the front-end csv car tables.
struct MenuCarEntry
{
    char name[8]; // 0x00
    int unk08;    // 0x08
    int unk0c;    // 0x0c
    int unk10;    // 0x10
    int unk14;    // 0x14
};

struct MenuNode
{
    int unk00;              // 0x00
    int unk04;              // 0x04
    int unk08;              // 0x08
    MenuCarEntry cars[5];   // 0x0c
};

struct MenuAiCar
{
    MenuCarEntry entries[3][5]; // Easy, Medium, Hard
};

struct MenuRace
{
    int track;            // 0x00
    MenuCarEntry cars[6]; // 0x04
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
    int price;    // 0x000
    int unk004;   // 0x004
    float unk008; // 0x008
    float unk00c; // 0x00c
    float unk010; // 0x010
    float unk014; // 0x014
    float unk018; // 0x018
    float unk01c; // 0x01c
    float unk020; // 0x020
    float unk024; // 0x024
    float unk028; // 0x028
    int unk02c;   // 0x02c
    int unk030;   // 0x030
    int unk034;   // 0x034
    float unk038; // 0x038
    float unk03c; // 0x03c
    float unk040; // 0x040
    float unk044; // 0x044
    float unk048; // 0x048
    float unk04c; // 0x04c
    float unk050; // 0x050
    float unk054; // 0x054
    float unk058; // 0x058
    float unk05c; // 0x05c
    float unk060; // 0x060
    float unk064; // 0x064
    float unk068; // 0x068
    float unk06c; // 0x06c
    float unk070; // 0x070
    float unk074; // 0x074
    float unk078; // 0x078
    float unk07c; // 0x07c
    float unk080; // 0x080
    float unk084; // 0x084
    float unk088; // 0x088
    int unk08c;   // 0x08c
    int unk090;   // 0x090
    float unk094; // 0x094
    float unk098; // 0x098
    float unk09c; // 0x09c
    float unk0a0; // 0x0a0
    float unk0a4; // 0x0a4
    float unk0a8; // 0x0a8
    float unk0ac; // 0x0ac
    float unk0b0; // 0x0b0
    float unk0b4; // 0x0b4
    float unk0b8; // 0x0b8
    float unk0bc; // 0x0bc
    float unk0c0; // 0x0c0
    float unk0c4; // 0x0c4
    float unk0c8; // 0x0c8
    float unk0cc; // 0x0cc
    float unk0d0; // 0x0d0
    float unk0d4; // 0x0d4
    float unk0d8; // 0x0d8
    float unk0dc; // 0x0dc
    float unk0e0; // 0x0e0
    float unk0e4; // 0x0e4
    int unk0e8;   // 0x0e8
    int unk0ec;   // 0x0ec
    int unk0f0;   // 0x0f0
    int unk0f4;   // 0x0f4
    int unk0f8;   // 0x0f8
    int unk0fc;   // 0x0fc
    float unk100; // 0x100
    float unk104; // 0x104
    float unk108; // 0x108
    float unk10c; // 0x10c
    float unk110; // 0x110
    float unk114; // 0x114
    float unk118; // 0x118
    float unk11c; // 0x11c
    float unk120; // 0x120
    int sponsor;  // 0x124
    float unk128; // 0x128
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

// Front-end list of MenuDef items; FUN_43c860 sets it up.
struct MenuList
{
    PoolObject base; // 0x00
    int count;       // 0x14
    MenuDef *def;    // 0x18
    float unk1c;     // 0x1c
    float unk20;     // 0x20
    float unk24[32]; // 0x24
    int selected;    // 0xa4
    int unka8;       // 0xa8
    int unkac;       // 0xac
    int unkb0;       // 0xb0
    int unkb4;       // 0xb4
    float unkb8;     // 0xb8, MenuDef::x
    float unkbc;     // 0xbc, MenuDef::y
    float unkc0;     // 0xc0
    int unkc4;       // 0xc4
};

struct MenuLanguage
{
    char name[0x20];
    int id;
};

// One line of a framed message, drawn by FUN_45be20.
struct MenuLine
{
    DWORD color; // 0x00
    char *text;  // 0x04
};

// Car slot of a race setup; car is the 1-based RaceState entry.
struct RaceSetupCar
{
    int unk00; // 0x00
    int unk04; // 0x04
    int unk08; // 0x08
    int car;   // 0x0c
    int unk10; // 0x10
    int unk14; // 0x14
    int unk18; // 0x18
};

struct RaceSetup1
{
    RaceSetupCar cars[6]; // 0x00
};

struct RaceSetup3
{
    Initials name;   // 0x00
    int car;         // 0x04
    int track;       // 0x08, 1-based
    int unk0c;       // 0x0c
    int unk10;       // 0x10
    int unk14;       // 0x14
    BYTE *unk18;     // 0x18, int at 0x3c
};

struct RaceSetup4
{
    Initials name; // 0x00
    int car;       // 0x04
    int track;     // 0x08, 1-based
    int unk0c;     // 0x0c
    int minutes;   // 0x10
};

struct RaceSetup5
{
    BYTE unk000[0x12c];   // 0x000
    RaceSetupCar cars[6]; // 0x12c
};

struct RaceSetup6
{
    MenuRoundCar cars[4]; // 0x00, unk08 is the RaceState entry
    int count;            // 0x30
};

struct RaceSetup7Car
{
    int unk00;        // 0x00
    int car;          // 0x04
    BYTE unk08[0x18]; // 0x08
};

struct RaceSetup7
{
    RaceSetup7Car cars[6]; // 0x00
    int count;             // 0xc0
};

struct RaceResults
{
    int won;                   // 0x00
    MenuRaceResult results[6]; // 0x04
};

struct RaceResults3
{
    int won;   // 0x00
    int unk04; // 0x04
    int unk08; // 0x08
    int unk0c; // 0x0c
    int unk10; // 0x10
};

struct RaceResults4
{
    int won;   // 0x00
    int unk04; // 0x04
};

struct RaceResults6
{
    int won;                   // 0x00
    MenuRaceResult results[4]; // 0x04
    int count;                 // 0x54
};

struct RaceResults7
{
    int won;                   // 0x00
    MenuRaceResult results[6]; // 0x04
    int count;                 // 0x7c
};

// Race started from the front end; FUN_439e90 copies its results back into dst<mode>.
struct RaceRequest
{
    int mode;           // 0x00
    RaceSetup1 *src1;   // 0x04
    RaceResults *dst1;  // 0x08
    void *src3;         // 0x0c
    RaceResults3 *dst3; // 0x10
    void *src4;         // 0x14
    RaceResults4 *dst4; // 0x18
    RaceSetup5 *src5;   // 0x1c
    RaceResults *dst5;  // 0x20
    RaceSetup6 *src6;   // 0x24
    RaceResults6 *dst6; // 0x28
    RaceSetup7 *src7;   // 0x2c
    RaceResults7 *dst7; // 0x30
};

extern RaceRequest g_5df528;

// Front-end state, cleared as a whole by FUN_43d0b0.
struct MenuState
{
    int saveSize;              // 0x0000, 0x211c in a setup save
    unsigned int saveChecksum; // 0x0004, FUN_43d5d0 over the save with this field 0
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
    int unk4230; // 0x4230
    int unk4234; // 0x4234, challenge state run by FUN_44b5e0
    int unk4238; // 0x4238
    int unk423c; // 0x423c, entries used in unk46ac
    int unk4240; // 0x4240
    int unk4244; // 0x4244
    BYTE unk4248[0x424c - 0x4248];
    int unk424c;                // 0x424c, total score
    BYTE unk4250[0x4254 - 0x4250];
    int unk4254;                // 0x4254
    int language;               // 0x4258, id of the loaded front-end language
    MenuLanguage languages[8];  // 0x425c, from Setup\languagePC.csv
    int languageCount;          // 0x437c
    int unk4380; // 0x4380
    int unk4384; // 0x4384
    int unk4388; // 0x4388
    int unk438c; // 0x438c
    int unk4390; // 0x4390
    int unk4394; // 0x4394, set when the car page is left without a choice
    int unk4398;     // 0x4398, entries used in unk439c
    int unk439c[20]; // 0x439c
    BYTE unk43ec[0x43f4 - 0x43ec];
    int unk43f4[4];  // 0x43f4, random car per entry of unk46ac
    int unk4404;     // 0x4404
    int unk4408;     // 0x4408, entries used in unk440c
    int unk440c[26]; // 0x440c
    int unk4474;     // 0x4474
    int unk4478; // 0x4478
    int unk447c; // 0x447c
    int unk4480; // 0x4480
    BYTE unk4484[0x44d0 - 0x4484];
    int unk44d0; // 0x44d0
    char unk44d4[4][0x40]; // 0x44d4, names entered on PageEnterName
    int unk45d4;   // 0x45d4
    int unk45d8;   // 0x45d8
    int unk45dc;   // 0x45dc
    float unk45e0; // 0x45e0
    float unk45e4; // 0x45e4
    int unk45e8; // 0x45e8
    int unk45ec;           // 0x45ec, FUN_43dd40 id for the message page
    MenuLine unk45f0[20];  // 0x45f0, message page lines
    int unk4690;           // 0x4690, lines used in unk45f0
    ScoreList unk4694; // 0x4694, copied by FUN_459200
    int unk46a8; // 0x46a8
    int unk46ac[4]; // 0x46ac
    int unk46bc; // 0x46bc
    int unk46c0; // 0x46c0
    int unk46c4; // 0x46c4
    int unk46c8; // 0x46c8
    int unk46cc; // 0x46cc
    int unk46d0; // 0x46d0
    int unk46d4; // 0x46d4
    int unk46d8; // 0x46d8
    int unk46dc; // 0x46dc
    int unk46e0; // 0x46e0
    int unk46e4; // 0x46e4
    BYTE unk46e8[0x4704 - 0x46e8];
    int unk4704; // 0x4704
    BYTE unk4708[0x4714 - 0x4708];
    char unk4714[4]; // 0x4714
    BYTE unk4718[0x13148 - 0x4718];
    Unk4d5cc0 *unk13148; // 0x13148
    ShopCar cars[21];    // 0x1314c, [1..20] used
    BYTE unk144a8[0x14594 - 0x144a8];
    // Shop catalogue: [1..20] cars, then the part groups returned by FUN_43db20.
    ShopItem items[75];    // 0x14594
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
    int unk1a604;           // 0x1a604
    char unk1a608[0x40];    // 0x1a608
    int unk1a648;           // 0x1a648
    char unk1a64c[0x40];    // 0x1a64c
    // Read by FUN_435980; names are the csv keys.
    int nodePositions[6]; // 0x1a68c
    int gold;             // 0x1a6a4
    int silver;           // 0x1a6a8
    MenuNode nodes[19];   // 0x1a6ac, [1..18] used
    int unk1b078;          // 0x1b078, row of unk0114
    BYTE unk1b07c[0x1b080 - 0x1b07c];
    MenuName names[6];     // 0x1b080, [0] is the player
    BYTE unk1b128[0x1b140 - 0x1b128];
    MenuRaceResult results[6]; // 0x1b140, [0] is the player
    BYTE unk1b1b8[0x1b320 - 0x1b1b8];
    MenuAiCar aiCars[21]; // 0x1b320, read by FUN_435860
    MenuRace races[8];    // 0x1d0a8, read by FUN_435730
    int numberOfRaces;    // 0x1d548
    int car18UnlockScore; // 0x1d54c
    int screenMusic[50];  // 0x1d550, music track per front-end screen
    BYTE unk1d618[0x1d630 - 0x1d618];
    int unk1d630[25][6];          // 0x1d630, read by FUN_434f60
    MenuCarEntry unk1d888[3][4];  // 0x1d888, Easy, Medium, Hard; read by FUN_434e90
    int unk1d9a8; // 0x1d9a8
    BYTE unk1d9ac[0x1da5c - 0x1d9ac];
    int unk1da5c[6][2];           // 0x1da5c, read by FUN_434e10
    int unk1da8c;                 // 0x1da8c
    int unk1da90[4][2];           // 0x1da90
    MenuSlot unk1dab0[4];         // 0x1dab0, sorted by FUN_44d070
    int unk1dae0;                 // 0x1dae0
    int unk1dae4; // 0x1dae4
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

// Car stat screen run by FUN_453710.
struct Unk453710
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18
    int unk1c;         // 0x1c
    float unk20;       // 0x20
    float unk24;       // 0x24
    float unk28;       // 0x28
    float unk2c[3];    // 0x2c, shown stat bars
    float unk38[3];    // 0x38, stat targets
    int unk44[3];      // 0x44
    int unk50;         // 0x50
    int unk54;         // 0x54
};

// Car part page with named fields; groups is laid out as in Unk451a50.
struct Unk451aa0
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18, selected item
    int unk1c;         // 0x1c, selected group
    float unk20;       // 0x20
    float unk24;       // 0x24
    float unk28;       // 0x28
    float unk2c;       // 0x2c
    float unk30;       // 0x30
    float unk34;       // 0x34
    float unk38[3];    // 0x38, shown stat bars
    float unk44[3];    // 0x44, stat targets
    int groups[48];    // 0x50
    int unk110;        // 0x110, groups in use
    char unk114[0x20]; // 0x114
    int unk134[22];    // 0x134
    BYTE unk18c[1][3]; // 0x18c, stats per item
};

extern MenuDef g_486998;

// Per-player front-end panel; the arrays are indexed by player, 1 to 4.
struct Unk456070
{
    BYTE unk00[0x14]; // 0x00
    int unk14;        // 0x14
    int unk18;        // 0x18
    int unk1c;        // 0x1c
    int unk20[5];     // 0x20
    int unk34[5];     // 0x34
    int unk48[5];     // 0x48
};

// Screen position page; unk1c/unk20 are the offsets being adjusted.
struct Unk450930
{
    DWORD unk00[5];    // 0x00
    int unk14;         // 0x14
    int unk18;         // 0x18
    float unk1c;       // 0x1c
    float unk20;       // 0x20
    PoolObject *child; // 0x24
};

// Controls page: each field cycles through its options.
struct Unk455fc0
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18
    int unk1c;         // 0x1c
    int unk20;         // 0x20
    int unk24;         // 0x24
    int unk28;         // 0x28
    int unk2c;         // 0x2c
};

struct Unk457770
{
    DWORD unk00[5];    // 0x00
    PoolObject *unk14; // 0x14
    int unk18;         // 0x18
};

extern PoolClass g_menuListClass;

// Shop category: text id, FUN_437a90 id, then the entries FUN_4522c0 fills in.
struct Unk486b88
{
    int text;      // 0x00
    int id;        // 0x04
    int unk08[32]; // 0x08
    int unk88[32]; // 0x88
};

extern Unk486b88 g_486b88[13];

// One memory card slot listed by PageSave.
struct Unk457e70Entry
{
    int id;         // 0x00, card
    int unk04;      // 0x04, free space
    int unk08;      // 0x08, FUN_457bf0 state
    char text[0x20]; // 0x0c
    char *name;     // 0x2c
};

// PageSave
struct Unk457e70
{
    BYTE unk000[0x14];         // 0x000
    int unk14;                 // 0x014
    int unk18;                 // 0x018
    int unk1c;                 // 0x01c
    int unk20;                 // 0x020, selected entry
    int unk24;                 // 0x024
    float unk28;               // 0x028
    float unk2c;               // 0x02c
    int unk30;                 // 0x030
    int unk34;                 // 0x034
    float unk38;               // 0x038
    float unk3c;               // 0x03c
    PoolObject *unk40;         // 0x040
    int unk044[8];             // 0x044, last state per card
    Unk457e70Entry entries[8]; // 0x064
    int count;                 // 0x1e4
    int unk1e8;                // 0x1e8
    int unk1ec;                // 0x1ec
    int unk1f0;                // 0x1f0
    int unk1f4;                // 0x1f4
    int unk1f8;                // 0x1f8
    int unk1fc;                // 0x1fc
};

int FUN_43c860(MenuList *list, MenuDef *def);
void FUN_424bd0(float x, float y);
int FUN_43d790(int value, int min, int max);
float FUN_43d810(float current, float target, float rate);
void FUN_43df60(float a, float b, float c, float d, float e, float f);
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
