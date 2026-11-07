#include "GameUpdate.h"
#include "MenuUpdate.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../../globals.h"
#include "../../sound.h"
#include "../../d3drender.h"
#include "../../objects.h"
#include "../../sprite.h"
#include "Game.h"
#include "GameSetup.h"

// Menu button state per player, indexed 1..4.
struct MenuInput
{
    BYTE held[8]; // 0x00, [1..7] used
    BYTE prev[8]; // 0x08
    int unk10;    // 0x10
    int unk14;    // 0x14
};

struct Unk450930
{
    DWORD unk00[5];    // 0x00
    int unk14;         // 0x14
    int unk18;         // 0x18
    float unk1c;       // 0x1c
    float unk20;       // 0x20
    PoolObject *child; // 0x24
};

struct Unk453460
{
    DWORD unk00[6];    // 0x00
    PoolObject *unk18; // 0x18
    int unk1c;         // 0x1c
    int unk20;         // 0x20
};

struct Unk451a50
{
    BYTE unk00[0x50];   // 0x00
    // Each group is a count, an unused word and up to ten items.
    int groups[1];      // 0x50, group count unknown
};

// Name entry: three characters plus the terminator.
struct Unk454b20
{
    BYTE unk00[0x14]; // 0x00
    int unk14;        // 0x14
    int unk18;        // 0x18
    int unk1c;        // 0x1c
    int unk20;        // 0x20
    int unk24;        // 0x24
    int unk28;        // 0x28
    int unk2c;        // 0x2c
    int unk30;        // 0x30
    int unk34;        // 0x34
    int unk38;        // 0x38
    int unk3c;        // 0x3c
    int unk40;        // 0x40
    int unk44;        // 0x44
    char text[4];     // 0x48
    int unk4c;        // 0x4c
};

struct Unk457770
{
    DWORD unk00[5];    // 0x00
    PoolObject *unk14; // 0x14
    int unk18;         // 0x18
};

struct Unk454b40
{
    BYTE unk00[0x1c]; // 0x00
    int unk1c;        // 0x1c
    int unk20;        // 0x20
    float unk24;      // 0x24
    float unk28;      // 0x28
    float unk2c;      // 0x2c
    float unk30;      // 0x30
};

struct Unk455fc0
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;        // 0x18
    int unk1c;        // 0x1c
    int unk20;        // 0x20
    int unk24;        // 0x24
    int unk28;        // 0x28
    int unk2c;        // 0x2c
};

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

void FUN_456070(Unk456070 *object);

struct Unk457ea0
{
    BYTE unk00[0x40];  // 0x00
    PoolObject *child; // 0x40
};

struct Unk457e70Entry
{
    int id;
    int unk04;
    int unk08;
    BYTE unk0c[0x24];
};

struct Unk457e70
{
    BYTE unk000[0x20];         // 0x000
    int unk20;                 // 0x020, selected entry
    BYTE unk024[0x1c];         // 0x024
    PoolObject *unk40;         // 0x040
    BYTE unk044[0x20];         // 0x044
    Unk457e70Entry entries[8]; // 0x064
    int count;                 // 0x1e4
    int unk1e8;                // 0x1e8
    int unk1ec;                // 0x1ec
    int unk1f0;                // 0x1f0
    int unk1f4;                // 0x1f4
    int unk1f8;                // 0x1f8
};

typedef Unk457e70 Unk458860;

// GLOBAL: STUNTGP_D3D 0x4866c8
MenuItem g_4866c8[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x17, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x486708
MenuDef g_486708 = {0xb, 0.0f, 0, 320.0f, 240.0f, 1.0f, 2, 1.25f, 1, 0x50, g_4866c8, 0};

// GLOBAL: STUNTGP_D3D 0x486750
MenuItem g_486750[4] = {
    {-1, 0xffffffff, 0xffffffff, 0x14, 0, 4, 0, 0},
    {0, 0xffc8c8ff, 0xffffffff, 0x15, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x16, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x4867d0
MenuDef g_4867d0 = {0xb, 1.0f, 0, 510.0f, 380.0f, 1.0f, 2, 1.25f, 1, 0x78, g_486750, 0};

// GLOBAL: STUNTGP_D3D 0x486800
MenuItem g_486800[5] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x9c, 0x9e, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x9f, 0xa0, 1, 0, 0},
    {2, 0xffc8c8ff, 0xffffffff, 0xa1, 0xa2, 1, 0, 0},
    {4, 0xffc8c8ff, 0xffffffff, 0xa5, 0xa6, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x4868a0
MenuDef g_4868a0 = {0xb, 1.0f, 0, 510.0f, 240.0f, 1.0f, 2, 1.25f, 4, 0xaa, g_486800, 0};

// GLOBAL: STUNTGP_D3D 0x488588
MenuItem g_488588[2] = {
    {1, 0xffc8c8ff, 0xffffffff, 0x88, 0x89, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x4885c8
MenuDef g_4885c8 = {0xb, 0.0f, 0, 320.0f, 240.0f, 1.0f, 2, 1.25f, 1, 0xc8, g_488588, 0};

// GLOBAL: STUNTGP_D3D 0x488618
MenuItem g_488618[8] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x18, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x293, 0, 2, 0, 0},
    {2, 0xffc8c8ff, 0xffffffff, 0x295, 0, 2, 0, 0},
    {3, 0xffc8c8ff, 0xffffffff, 0x297, 0, 2, 0, 0},
    {4, 0xffc8c8ff, 0xffffffff, 0x29a, 0, 2, 0, 0},
    {5, 0xffc8c8ff, 0xffffffff, 0x29d, 0, 2, 0, 0},
    {6, 0xffc8c8ff, 0xffffffff, 0x2a1, 0, 2, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488718
MenuDef g_488718 = {0xb, 0.0f, 0, 320.0f, 240.0f, 1.0f, 2, 1.25f, 1, 0xfa, g_488618, 0};

// Character grid for name entry, eight per row.
// GLOBAL: STUNTGP_D3D 0x4881b0
char *g_4881b0[4] = {
    // STRING: STUNTGP_D3D 0x4881c8
    "ABCDEFGH",
    // STRING: STUNTGP_D3D 0x4881d4
    "IJKLMNOP",
    // STRING: STUNTGP_D3D 0x4881e0
    "QRSTUVWX",
    // STRING: STUNTGP_D3D 0x4881ec
    "YZ=:()de",
};

// GLOBAL: STUNTGP_D3D 0x5da2e8
MenuInput g_menuInput[5];

// GLOBAL: STUNTGP_D3D 0x5df528
int g_5df528[13];

// GLOBAL: STUNTGP_D3D 0x5df560
MenuState g_menuState;

// GLOBAL: STUNTGP_D3D 0x5ff4b8
DWORD g_5ff4b8;

// GLOBAL: STUNTGP_D3D 0x5ff8c0
int g_5ff8c0;

// GLOBAL: STUNTGP_D3D 0x5ff3e8
FrontEnd g_frontEnd;

// GLOBAL: STUNTGP_D3D 0x61297c
DWORD g_61297c;

// GLOBAL: STUNTGP_D3D 0x47966c
Initials g_47966c = {'!', '!', '!'};

// GLOBAL: STUNTGP_D3D 0x479668
Initials *g_479668 = &g_47966c;

// Byte-oriented decompressor input; bits holds the current flag byte with a sentinel bit.
struct BitReader
{
    int size;    // 0x00
    BYTE *start; // 0x04
    BYTE *cur;   // 0x08
    BYTE bits;   // 0x0c
    BYTE carry;  // 0x0d
};

// Byte-oriented compressor output; flag bits for the following bytes are packed into buffer[flagPos].
struct BitWriter
{
    int count;    // 0x00
    int flagPos;  // 0x04
    int bit;      // 0x08
    BYTE *buffer; // 0x0c
    int size;     // 0x10
    BYTE *start;  // 0x14
};

void FUN_437eb0();
void FUN_441e20();
int FUN_43d730(int id);
int FeCsv_ReadInt(int *value, char *text, int *pos);
int FeCsv_SkipLine(char *text, int *pos);
int FUN_43c600(const char *expected, char *text, int *pos);
int FUN_43d760(int id);
void FUN_442ad0(int type, int duration, int delay, int end, int from, int to, float scale);
int FUN_43efc0();
void FUN_441210();
int FUN_452d70(int id);
void FUN_462270(int a);
int FUN_462260();
int FUN_424a80();
void FUN_424a90(int mode);
extern Unk4d5cc0 *g_60df90;
float FUN_43d9e0(float value);
int FUN_436fc0(int player, int button);
int FUN_436fd0(int player, int button);
void FUN_43f3e0(PoolObject *screen, int player);
int FUN_43f5e0(int player);
int FUN_4407a0(int id);

// FUNCTION: STUNTGP_D3D 0x424a80
int FUN_424a80()
{
    return 2;
}

// FUNCTION: STUNTGP_D3D 0x424a90
void FUN_424a90(int mode)
{
}

// FUNCTION: STUNTGP_D3D 0x424bd0
void FUN_424bd0(float x, float y)
{
    g_576be4 = x;
    g_576be8 = y;
    x = g_576b9c + x;
    y = g_576ba0 + y;
    g_576b8c = (int)x;
    g_576b90 = (int)y;
    g_576b94 = x;
    g_576b98 = y;
}

// STUB: STUNTGP_D3D 0x434b50
void FUN_434b50()
{
}

// Reads the championship settings rows of the front-end csv.
// FUNCTION: STUNTGP_D3D 0x435b60
int FUN_435b60(char *text, int *pos)
{
    char key[64];
    int i;
    int j;

    // STRING: STUNTGP_D3D 0x4791b4
    FUN_43c600("NumberOfRounds", text, pos);
    FeCsv_ReadInt(&g_menuState.numberOfRounds, text, pos);
    FeCsv_SkipLine(text, pos);
    for (i = 0; i < 4; i++)
    {
        // STRING: STUNTGP_D3D 0x4791c4
        sprintf(key, "BonusRound%d", i + 1);
        FUN_43c600(key, text, pos);
        FeCsv_ReadInt(&g_menuState.bonusRounds[i], text, pos);
        FeCsv_SkipLine(text, pos);
    }
    for (i = 0; i < 6; i++)
    {
        // STRING: STUNTGP_D3D 0x4791d4
        sprintf(key, "SaveRound%d", i + 1);
        FUN_43c600(key, text, pos);
        FeCsv_ReadInt(&g_menuState.saveRounds[i], text, pos);
        FeCsv_SkipLine(text, pos);
    }
    // STRING: STUNTGP_D3D 0x4791e0
    FUN_43c600("SponsorDiscountPercent", text, pos);
    FeCsv_ReadInt(&g_menuState.sponsorDiscountPercent, text, pos);
    FeCsv_SkipLine(text, pos);
    // STRING: STUNTGP_D3D 0x4791f8
    FUN_43c600("UsedItemDiscountPercent", text, pos);
    FeCsv_ReadInt(&g_menuState.usedItemDiscountPercent, text, pos);
    FeCsv_SkipLine(text, pos);
    FeCsv_SkipLine(text, pos);
    for (i = 1; i < 7; i++)
    {
        // STRING: STUNTGP_D3D 0x479210
        sprintf(key, "Sponsor%d", i);
        FUN_43c600(key, text, pos);
        FeCsv_ReadInt(&g_menuState.sponsors[i].unk00, text, pos);
        FeCsv_ReadInt(&g_menuState.sponsors[i].id, text, pos);
        FeCsv_SkipLine(text, pos);
    }
    FeCsv_SkipLine(text, pos);
    for (i = 0; i < 6; i++)
    {
        // STRING: STUNTGP_D3D 0x47921c
        sprintf(key, "Position%d", i + 1);
        FUN_43c600(key, text, pos);
        FeCsv_ReadInt(&g_menuState.positions[i][0], text, pos);
        FeCsv_ReadInt(&g_menuState.positions[i][1], text, pos);
        FeCsv_ReadInt(&g_menuState.positions[i][2], text, pos);
        FeCsv_ReadInt(&g_menuState.positions[i][3], text, pos);
        FeCsv_SkipLine(text, pos);
    }
    FeCsv_SkipLine(text, pos);
    for (i = 0; i < 21; i++)
    {
        // STRING: STUNTGP_D3D 0x479228
        sprintf(key, "Round%dTrack", i + 1);
        FUN_43c600(key, text, pos);
        FeCsv_ReadInt(&g_menuState.rounds[i].track, text, pos);
        FeCsv_ReadInt(&g_menuState.rounds[i].unk04, text, pos);
        FeCsv_SkipLine(text, pos);
    }
    FeCsv_SkipLine(text, pos);
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 5; j++)
        {
            // STRING: STUNTGP_D3D 0x479238
            sprintf(key, "Round%dCar%d", i + 1, j + 1);
            FUN_43c600(key, text, pos);
            FeCsv_ReadInt(&g_menuState.rounds[i].cars[j].unk00, text, pos);
            FeCsv_ReadInt(&g_menuState.rounds[i].cars[j].unk04, text, pos);
            FeCsv_ReadInt(&g_menuState.rounds[i].cars[j].unk08, text, pos);
            FeCsv_SkipLine(text, pos);
        }
    }
    return 1;
}

void FUN_435f60(void *unused, int *out, char *text, int *pos);
int FUN_437cc0(int track);
int FeCsv_SkipBlankLines(char *text, int *pos);

// FUNCTION: STUNTGP_D3D 0x435e30
int FUN_435e30(int id, ShopCar *car, char *text, int *pos)
{
    char key[64];
    memset(car, 0, sizeof(ShopCar));
    // STRING: STUNTGP_D3D 0x479248
    sprintf(key, "Car%02d", id);
    FUN_43c600(key, text, pos);
    FeCsv_ReadInt(&car->unk04, text, pos);
    FeCsv_ReadInt(&car->unk08, text, pos);
    // STRING: STUNTGP_D3D 0x479250
    FUN_435f60("Engine ", car->parts[5], text, pos);
    // STRING: STUNTGP_D3D 0x479258
    FUN_435f60("Battery", car->parts[4], text, pos);
    // STRING: STUNTGP_D3D 0x479260
    FUN_435f60("Tyres  ", car->parts[12], text, pos);
    // STRING: STUNTGP_D3D 0x479268
    FUN_435f60("Brakes ", car->parts[8], text, pos);
    // STRING: STUNTGP_D3D 0x479270
    FUN_435f60("Shocks ", car->parts[3], text, pos);
    // STRING: STUNTGP_D3D 0x479278
    FUN_435f60("Chassis", car->parts[6], text, pos);
    // STRING: STUNTGP_D3D 0x479280
    FUN_435f60("Drive  ", car->parts[13], text, pos);
    // STRING: STUNTGP_D3D 0x479288
    FUN_435f60("Horn   ", car->parts[9], text, pos);
    // STRING: STUNTGP_D3D 0x479290
    FUN_435f60("Boost  ", car->parts[11], text, pos);
    // STRING: STUNTGP_D3D 0x479298
    FUN_435f60("BMS    ", car->parts[7], text, pos);
    // STRING: STUNTGP_D3D 0x4792a0
    FUN_435f60("Gears  ", car->parts[10], text, pos);
    FUN_437cc0(id);
    FeCsv_SkipBlankLines(text, pos);
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x435f60
void FUN_435f60(void *unused, int *out, char *text, int *pos)
{
    out[0] = 0;
    FeCsv_ReadInt(&out[1], text, pos);
    FeCsv_ReadInt(&out[2], text, pos);
    FeCsv_ReadInt(&out[3], text, pos);
}

// FUNCTION: STUNTGP_D3D 0x436400
void FUN_436400(const char *name, int *value)
{
}

// FUNCTION: STUNTGP_D3D 0x436410
void FUN_436410()
{
}

void FUN_4365d0(int sponsor, const char *name, ShopItem *item, ShopCar *car, int part, int b);
int FUN_436420(int sponsor, ShopItem *item, int *used, int unused);

// FUNCTION: STUNTGP_D3D 0x436490
void FUN_436490(int a, ShopEntry *out, ShopCar *car, ShopItem *item, int unused)
{
    memset(out, 0, sizeof(ShopEntry));
    out->car = *car;
    out->item = *item;
    if (out->car.unk00)
    {
        out->item.price -= out->item.price * g_menuState.usedItemDiscountPercent / 100;
    }
    // STRING: STUNTGP_D3D 0x4792d4
    FUN_4365d0(a, "UpgradeEngine    ", &out->item, car, 5, 0);
    // STRING: STUNTGP_D3D 0x4792e8
    FUN_4365d0(a, "UpgradeBattery   ", &out->item, car, 4, 0);
    // STRING: STUNTGP_D3D 0x4792fc
    FUN_4365d0(a, "UpgradeTyres     ", &out->item, car, 12, 0);
    // STRING: STUNTGP_D3D 0x479310
    FUN_4365d0(a, "UpgradeBrakes    ", &out->item, car, 8, 0);
    // STRING: STUNTGP_D3D 0x479324
    FUN_4365d0(a, "UpgradeSuspension", &out->item, car, 3, 0);
    // STRING: STUNTGP_D3D 0x479338
    FUN_4365d0(a, "UpgradeChassis   ", &out->item, car, 6, 0);
    // STRING: STUNTGP_D3D 0x47934c
    FUN_4365d0(a, "UpgradeDrive     ", &out->item, car, 13, 0);
    // STRING: STUNTGP_D3D 0x479360
    FUN_4365d0(a, "UpgradeHorns     ", &out->item, car, 9, 0);
    // STRING: STUNTGP_D3D 0x479374
    FUN_4365d0(a, "UpgradeBoost     ", &out->item, car, 11, 0);
    // STRING: STUNTGP_D3D 0x479388
    FUN_4365d0(a, "UpgradeBms       ", &out->item, car, 7, 0);
    // STRING: STUNTGP_D3D 0x47939c
    FUN_4365d0(a, "UpgradeGears     ", &out->item, car, 10, 0);
}

// STUB: STUNTGP_D3D 0x43db20
ShopItem *FUN_43db20(int part, int index)
{
    return NULL;
}

int FUN_437a90(int id);

// Adds the part fitted in car slot `part` to the running totals in item.
// FUNCTION: STUNTGP_D3D 0x4365d0
void FUN_4365d0(int sponsor, const char *name, ShopItem *item, ShopCar *car, int part, int b)
{
    int *slot = car->parts[part];
    ShopItem *parts = FUN_43db20(part, 1);
    if (!slot[1])
    {
        ShopItem *base = FUN_43db20(part, FUN_437a90(part));
        item->unk008 += base->unk008;
        item->price += base->price;
    }
    else
    {
        ShopItem *src = &parts[slot[1] - 1];
        item->price += FUN_436420(sponsor, src, slot, 0);
        item->unk008 += src->unk008;
        if (src->unk104 >= 0.0f)
        {
            item->unk104 = src->unk104;
        }
        if (src->unk108 >= 0.0f)
        {
            item->unk108 = src->unk108;
        }
        if (src->unk10c >= 0.0f)
        {
            item->unk10c = src->unk10c;
        }
        if (src->unk110 >= 0.0f)
        {
            item->unk110 = src->unk110;
        }
        if (src->unk114 >= 0.0f)
        {
            item->unk114 = src->unk114;
        }
        if (src->unk118 >= 0.0f)
        {
            item->unk118 = src->unk118;
        }
        if (src->unk00c >= 0.0f)
        {
            item->unk00c = src->unk00c;
        }
        if (src->unk010 >= 0.0f)
        {
            item->unk010 = src->unk010;
        }
        if (src->unk014 >= 0.0f)
        {
            item->unk014 = src->unk014;
        }
        if (src->unk070 >= 0.0f)
        {
            item->unk070 = src->unk070;
        }
        if (src->unk018 >= 0.0f)
        {
            item->unk018 = src->unk018;
        }
        if (src->unk01c >= 0.0f)
        {
            item->unk01c = src->unk01c;
        }
        if (src->unk020 >= 0.0f)
        {
            item->unk020 = src->unk020;
        }
        if (src->unk024 >= 0.0f)
        {
            item->unk024 = src->unk024;
        }
        if (src->unk028 >= 0.0f)
        {
            item->unk028 = src->unk028;
        }
        if (src->unk02c >= 0)
        {
            item->unk02c = src->unk02c;
        }
        if (src->unk030 >= 0)
        {
            item->unk030 = src->unk030;
        }
        if (src->unk040 >= 0.0f)
        {
            item->unk040 = src->unk040;
        }
        if (src->unk094 >= 0.0f)
        {
            item->unk094 = src->unk094;
        }
        if (src->unk098 >= 0.0f)
        {
            item->unk098 = src->unk098;
        }
        if (src->unk034 >= 0)
        {
            item->unk034 = src->unk034;
        }
        if (src->unk038 >= 0.0f)
        {
            item->unk038 = src->unk038;
        }
        if (src->unk03c >= 0.0f)
        {
            item->unk03c = src->unk03c;
        }
        if (src->unk044 >= 0.0f)
        {
            item->unk044 = src->unk044;
        }
        if (src->unk048 >= 0.0f)
        {
            item->unk048 = src->unk048;
        }
        if (src->unk04c >= 0.0f)
        {
            item->unk04c = src->unk04c;
        }
        if (src->unk050 >= 0.0f)
        {
            item->unk050 = src->unk050;
        }
        if (src->unk054 >= 0.0f)
        {
            item->unk054 = src->unk054;
        }
        if (src->unk058 >= 0.0f)
        {
            item->unk058 = src->unk058;
        }
        if (src->unk05c >= 0.0f)
        {
            item->unk05c = src->unk05c;
        }
        if (src->unk060 >= 0.0f)
        {
            item->unk060 = src->unk060;
        }
        if (src->unk064 >= 0.0f)
        {
            item->unk064 = src->unk064;
        }
        if (src->unk068 >= 0.0f)
        {
            item->unk068 = src->unk068;
        }
        if (src->unk06c >= 0.0f)
        {
            item->unk06c = src->unk06c;
        }
        if (src->unk11c >= 0.0f)
        {
            item->unk11c = src->unk11c;
        }
        if (src->unk120 >= 0.0f)
        {
            item->unk120 = src->unk120;
        }
        if (src->unk074 >= 0.0f)
        {
            item->unk074 = src->unk074;
        }
        if (src->unk078 >= 0.0f)
        {
            item->unk078 = src->unk078;
        }
        if (src->unk07c >= 0.0f)
        {
            item->unk07c = src->unk07c;
        }
        if (src->unk080 >= 0.0f)
        {
            item->unk080 = src->unk080;
        }
        if (src->unk084 >= 0.0f)
        {
            item->unk084 = src->unk084;
        }
        if (src->unk088 >= 0.0f)
        {
            item->unk088 = src->unk088;
        }
        if (src->unk08c >= 0)
        {
            item->unk08c = src->unk08c;
        }
        if (src->unk090 >= 0)
        {
            item->unk090 = src->unk090;
        }
        if (src->unk09c >= 0.0f)
        {
            item->unk09c = src->unk09c;
        }
        if (src->unk0a0 >= 0.0f)
        {
            item->unk0a0 = src->unk0a0;
        }
        if (src->unk0a4 >= 0.0f)
        {
            item->unk0a4 = src->unk0a4;
        }
        if (src->unk0a8 >= 0.0f)
        {
            item->unk0a8 = src->unk0a8;
        }
        if (src->unk0ac >= 0.0f)
        {
            item->unk0ac = src->unk0ac;
        }
        if (src->unk0b0 >= 0.0f)
        {
            item->unk0b0 = src->unk0b0;
        }
        if (src->unk0b4 >= 0.0f)
        {
            item->unk0b4 = src->unk0b4;
        }
        if (src->unk0b8 >= 0.0f)
        {
            item->unk0b8 = src->unk0b8;
        }
        if (src->unk100 >= 0.0f)
        {
            item->unk100 = src->unk100;
        }
        if (src->unk0bc >= 0.0f)
        {
            item->unk0bc = src->unk0bc;
        }
        if (src->unk0c0 >= 0.0f)
        {
            item->unk0c0 = src->unk0c0;
        }
        if (src->unk0c4 >= 0.0f)
        {
            item->unk0c4 = src->unk0c4;
        }
        if (src->unk0c8 >= 0.0f)
        {
            item->unk0c8 = src->unk0c8;
        }
        if (src->unk0cc >= 0.0f)
        {
            item->unk0cc = src->unk0cc;
        }
        if (src->unk0d0 >= 0.0f)
        {
            item->unk0d0 = src->unk0d0;
        }
        if (src->unk0e8 >= 0)
        {
            item->unk0e8 = src->unk0e8;
        }
        if (src->unk0ec >= 0)
        {
            item->unk0ec = src->unk0ec;
        }
        if (src->unk0f0 >= 0)
        {
            item->unk0f0 = src->unk0f0;
        }
        if (src->unk0f4 >= 0)
        {
            item->unk0f4 = src->unk0f4;
        }
        if (src->unk0d4 >= 0.0f)
        {
            item->unk0d4 = src->unk0d4;
        }
        if (src->unk0d8 >= 0.0f)
        {
            item->unk0d8 = src->unk0d8;
        }
        if (src->unk0dc >= 0.0f)
        {
            item->unk0dc = src->unk0dc;
        }
        if (src->unk0e0 >= 0.0f)
        {
            item->unk0e0 = src->unk0e0;
        }
        if (src->unk0e4 >= 0.0f)
        {
            item->unk0e4 = src->unk0e4;
        }
        if (src->unk0f8 >= 0)
        {
            item->unk0f8 = src->unk0f8;
        }
        if (src->unk0fc >= 0)
        {
            item->unk0fc = src->unk0fc;
        }
        if (src->sponsor >= 0)
        {
            item->sponsor = src->sponsor;
        }
        if (src->unk128 >= 0.0f)
        {
            item->unk128 = src->unk128;
        }
    }
}

// Price after the used-item and sponsor discounts.
// FUNCTION: STUNTGP_D3D 0x436420
int FUN_436420(int sponsor, ShopItem *item, int *used, int unused)
{
    int price = item->price;
    if (*used)
    {
        price += g_menuState.usedItemDiscountPercent * price / -100;
    }
    if (sponsor && item->sponsor == g_menuState.sponsors[sponsor].id)
    {
        price += g_menuState.sponsorDiscountPercent * price / -100;
    }
    return price;
}

// FUNCTION: STUNTGP_D3D 0x436e90
void FUN_436e90(int *p)
{
    if (*p == 0)
    {
        *p = 5;
    }
}

// FUNCTION: STUNTGP_D3D 0x436ea0
void FUN_436ea0(int *p)
{
    if (*p == 0)
    {
        *p = 3;
    }
}

// FUNCTION: STUNTGP_D3D 0x436eb0
void FUN_436eb0()
{
    memset(g_menuInput, 0, sizeof(g_menuInput));
}

// FUNCTION: STUNTGP_D3D 0x436ed0
void FUN_436ed0()
{
    for (int i = 1; i < 5; i++)
    {
        memcpy(g_menuInput[i].prev, g_menuInput[i].held, 8);
    }
    for (int j = 1; j < 5; j++)
    {
        FUN_436f00(j);
    }
}

// FUNCTION: STUNTGP_D3D 0x436f00
void FUN_436f00(int player)
{
    MenuInput *in = &g_menuInput[player];
    if (FUN_437090(player))
    {
        for (int i = 1; i < 8; i++)
        {
            in->held[i] = FUN_436f60(g_62d580[player - 1].keys, i);
        }
    }
    else
    {
        memset(&in->held[1], 0, 7);
    }
}

// FUNCTION: STUNTGP_D3D 0x436fc0
int FUN_436fc0(int player, int button)
{
    return (char)g_menuInput[player].held[button];
}

// FUNCTION: STUNTGP_D3D 0x436fd0
int FUN_436fd0(int player, int button)
{
    if (g_menuInput[player].held[button] && !g_menuInput[player].prev[button])
    {
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437040
int FUN_437040()
{
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x437050
int FUN_437050(int player)
{
    FUN_437090(player);
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x436f60
BYTE FUN_436f60(BYTE *keys, int button)
{
    switch (button)
    {
    case 1:
        return keys[2];
    case 2:
        return keys[3];
    case 3:
        return keys[0];
    case 4:
        return keys[1];
    case 5:
        return keys[6];
    case 6:
        return keys[4];
    case 7:
        return keys[5];
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437090
int FUN_437090(int player)
{
    if (g_62d580[player - 1].active)
    {
        switch (g_62d580[player - 1].mode)
        {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            return 5;
        }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437100
int FUN_437100()
{
    int count = 0;
    for (int i = 1; i < 5; i++)
    {
        if (FUN_437090(i))
        {
            count++;
        }
    }
    return count;
}

// FUNCTION: STUNTGP_D3D 0x437360
int FUN_437360(int track)
{
    switch (track)
    {
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 4;
    case 4:
        return 1;
    case 5:
        return 1;
    case 6:
        return 1;
    case 7:
        return 1;
    case 8:
        return 2;
    case 9:
        return 4;
    case 10:
        return 1;
    case 11:
        return 1;
    case 12:
        return 3;
    case 13:
        return 4;
    case 14:
        return 1;
    case 15:
        return 1;
    case 16:
        return 2;
    case 17:
        return 1;
    case 18:
        return 3;
    case 19:
        return 2;
    case 20:
        return 3;
    case 21:
        return 1;
    case 22:
        return 1;
    case 23:
        return 3;
    case 24:
        return 3;
    case 25:
        return 5;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437400
int FUN_437400(int track)
{
    switch (track)
    {
    case 1:
    case 7:
        return 2;
    case 2:
    case 3:
    case 5:
    case 6:
    case 12:
    case 13:
    case 14:
    case 20:
        return 6;
    case 4:
    case 9:
    case 10:
    case 11:
    case 15:
        return 1;
    case 17:
    case 18:
        return 4;
    case 8:
    case 16:
    case 19:
        return 3;
    case 21:
        return 5;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437790
int FUN_437790(ScoreEntry *table, int count, Initials *name, int score)
{
    for (int i = 0; i < count; i++)
    {
        if (score > table[i].time)
        {
            for (int j = count - 1; j > i; j--)
            {
                table[j] = table[j - 1];
            }
            table[i].name[3] = 1;
            table[i].time = score;
            *(Initials *)table[i].name = *name;
            return i;
        }
    }
    return -1;
}

// FUNCTION: STUNTGP_D3D 0x437800
int FUN_437800(ScoreEntry *table, int count, Initials *name, int time)
{
    for (int i = 0; i < count; i++)
    {
        if (time < table[i].time)
        {
            for (int j = count - 1; j > i; j--)
            {
                table[j] = table[j - 1];
            }
            table[i].name[3] = 1;
            table[i].time = time;
            *(Initials *)table[i].name = *name;
            return i;
        }
    }
    return -1;
}

// FUNCTION: STUNTGP_D3D 0x437870
void FUN_437870()
{
}

// FUNCTION: STUNTGP_D3D 0x437880
void FUN_437880(int index)
{
    if (!g_menuState.unlocked[index])
    {
        g_menuState.unlocked[index] = 2;
    }
}

// FUNCTION: STUNTGP_D3D 0x4378a0
void FUN_4378a0(int index)
{
    if (!g_menuState.unlocked[index + 0x18])
    {
        g_menuState.unlocked[index + 0x18] = 2;
    }
}

// FUNCTION: STUNTGP_D3D 0x4378c0
void FUN_4378c0(int id)
{
    int index = 0;
    switch (id)
    {
    case 1:
        index = 2;
        break;
    case 2:
        index = 6;
        break;
    case 3:
        index = 3;
        break;
    case 4:
        index = 14;
        break;
    case 5:
        index = 16;
        break;
    case 6:
        index = 5;
        break;
    }
    FUN_437880(index);
}

// FUNCTION: STUNTGP_D3D 0x437920
int FUN_437920(int index)
{
    return g_menuState.unk1a6b0[index].unk00;
}

// FUNCTION: STUNTGP_D3D 0x437a90
int FUN_437a90(int id)
{
    switch (id)
    {
    case 1:
        return 0x14;
    case 2:
        return 0x18;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        return 5;
    case 13:
        return 3;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437af0
int FUN_437af0(int track)
{
    switch (track)
    {
    case 1:
        return 0xad;
    case 2:
        return 0xc2;
    case 3:
        return 0x96;
    case 4:
        return 0x78;
    case 5:
        return 0x87;
    case 6:
        return 0x82;
    case 7:
        return 0x9b;
    case 8:
        return 0x7d;
    case 9:
        return 0x91;
    case 10:
        return 0x8c;
    case 11:
        return 0xa5;
    case 12:
        return 0xa0;
    case 13:
        return 0xaa;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437cc0
int FUN_437cc0(int track)
{
    switch (track)
    {
    case 2:
    case 6:
    case 7:
    case 10:
    case 11:
    case 13:
        return 1;
    case 1:
    case 5:
    case 8:
    case 9:
    case 16:
        return 3;
    case 3:
    case 4:
    case 12:
    case 14:
    case 15:
        return 2;
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
        return 4;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437d20
int FUN_437d20(ScoreEntry *entry, Initials *name, int score)
{
    if (score > entry->time)
    {
        entry->name[3] = 1;
        entry->time = score;
        *(Initials *)entry->name = *name;
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437d60
int FUN_437d60(ScoreEntry *entry, Initials *name, int time)
{
    if (time < entry->time)
    {
        entry->name[3] = 1;
        entry->time = time;
        *(Initials *)entry->name = *name;
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437da0
int FUN_437da0(int track)
{
    switch (track)
    {
    case 1:
    case 2:
    case 3:
    case 8:
    case 9:
    case 13:
    case 16:
    case 19:
        return 30000;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x437eb0
void FUN_437eb0()
{
    FUN_441210();
}

// FUNCTION: STUNTGP_D3D 0x439e10
void FUN_439e10()
{
    FUN_43d420();
    FUN_441e20();
    Timer_Reset();
    FUN_43d420();
}

// FUNCTION: STUNTGP_D3D 0x439e30
void FUN_439e30()
{
    memset(g_5df528, 0, sizeof(g_5df528));
}

// FUNCTION: STUNTGP_D3D 0x43b210
short FUN_43b210(short a, short b)
{
    return a - b;
}

// FUNCTION: STUNTGP_D3D 0x43b270
void FUN_43b270(BitWriter *writer, BYTE *buffer, int size)
{
    writer->start = buffer;
    writer->size = size;
    writer->buffer = buffer;
    writer->flagPos = 0;
    writer->count = 1;
    *buffer = 0;
    writer->bit = 0;
}

// FUNCTION: STUNTGP_D3D 0x43b2a0
void FUN_43b2a0(BitWriter *writer, BYTE value)
{
    writer->buffer[writer->count++] = value;
}

// FUNCTION: STUNTGP_D3D 0x43b2b0
void FUN_43b2b0(BitWriter *writer, int bit)
{
    if (bit)
    {
        writer->buffer[writer->flagPos] |= 0x80 >> writer->bit;
    }
    if (++writer->bit == 8)
    {
        writer->bit = 0;
        writer->flagPos = writer->count++;
        writer->buffer[writer->flagPos] = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x43b300
void FUN_43b300(BitWriter *writer, int value, int count)
{
    while (count >= 8)
    {
        FUN_43b2a0(writer, value >> (count - 8));
        count -= 8;
    }
    while (count--)
    {
        FUN_43b2b0(writer, (value >> count) & 1);
    }
}

// FUNCTION: STUNTGP_D3D 0x43b370
BYTE FUN_43b370(BitReader *reader)
{
    return *reader->cur++;
}

// FUNCTION: STUNTGP_D3D 0x43b380
void FUN_43b380(BitReader *reader, BYTE *data, int size)
{
    reader->start = data;
    reader->size = size;
    reader->cur = data;
    BYTE b = FUN_43b370(reader);
    reader->carry = b >> 7;
    reader->bits = (b << 1) | 1;
}

// FUNCTION: STUNTGP_D3D 0x43b3b0
int FUN_43b3b0(BitReader *reader)
{
    int bit = reader->carry;
    reader->carry = reader->bits >> 7;
    reader->bits <<= 1;
    if (!reader->bits)
    {
        BYTE b = FUN_43b370(reader);
        reader->carry = b >> 7;
        reader->bits = (b << 1) | 1;
    }
    return bit;
}

// FUNCTION: STUNTGP_D3D 0x43b3f0
int FUN_43b3f0(BitReader *reader, int count)
{
    int value = 0;
    while (count >= 8)
    {
        value = (value << 8) | FUN_43b370(reader);
        count -= 8;
    }
    while (count--)
    {
        value = value * 2 + FUN_43b3b0(reader);
    }
    return value;
}

// FUNCTION: STUNTGP_D3D 0x43b5f0
int FUN_43b5f0(int value, BitWriter *writer)
{
    if (value == 0)
    {
        FUN_43b300(writer, 0, 1);
        return 0;
    }
    if (value < 0)
    {
        FUN_43b300(writer, 1, 1);
        FUN_43b300(writer, 0, 1);
        return -1;
    }
    FUN_43b300(writer, 1, 1);
    FUN_43b300(writer, 1, 1);
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x43bb90
int FUN_43bb90(BitReader *reader)
{
    if (!FUN_43b3b0(reader))
    {
        return 0;
    }
    return FUN_43b3b0(reader) ? 1 : -1;
}

// FUNCTION: STUNTGP_D3D 0x43bfd0
void FUN_43bfd0()
{
}

// FUNCTION: STUNTGP_D3D 0x43bfe0
void FUN_43bfe0()
{
}

// FUNCTION: STUNTGP_D3D 0x43c000
void FUN_43c000()
{
    FUN_424bd0((float)g_menuState.offsetX, (float)g_menuState.offsetY);
    g_sfxSetting = g_menuState.sfx;
    g_musicSetting = g_menuState.music;
    if (!g_menuState.music)
    {
        g_musicSetting = 1;
    }
    g_61297c = g_menuState.unk0084;
    FUN_462270(g_menuState.unk4240);
    Sound_ApplyVolumes();
}

// FUNCTION: STUNTGP_D3D 0x43c060
void FUN_43c060()
{
    memset(&g_menuState, 0, offsetof(MenuState, saved));
    g_menuState.unk00d4 = 0;
    g_menuState.sfx = 100;
    g_menuState.unk0084 = 100;
    g_menuState.unk00d8 = 0;
    g_menuState.unk00dc = 0;
    g_menuState.unk00e0 = 0;
    g_menuState.unk00e4 = 0;
    g_menuState.unk00e8 = 0;
    g_menuState.unk0070 = 0;
    g_menuState.unk0074 = 0;
    g_menuState.unk0078 = 1;
    g_menuState.music = 80;
    g_menuState.offsetX = 0;
    g_menuState.offsetY = 0;
    g_menuState.unk0090 = 0;
    for (int i = 0; i < 5; i++)
    {
        g_menuState.unk0098[i].unk00 = 0;
        g_menuState.unk0098[i].unk04 = 0;
        g_menuState.unk0098[i].unk08 = 0;
    }
    g_menuState.unk13148 = g_60df90;
    g_menuState.unk4240 = FUN_462260();
    if (!g_menuState.unk4240)
    {
        g_menuState.unk4240 = 1;
    }
    FUN_462270(g_menuState.unk4240);
    g_menuState.unk0094 = FUN_424a80();
    FUN_424a90(g_menuState.unk0094);
}

// Blank initials; each reset site has its own copy.
// GLOBAL: STUNTGP_D3D 0x479420
char g_479420[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479424
char g_479424[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479428
char g_479428[4] = "...";

// GLOBAL: STUNTGP_D3D 0x47942c
char g_47942c[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479430
char g_479430[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479434
char g_479434[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479438
char g_479438[4] = "...";

// GLOBAL: STUNTGP_D3D 0x47943c
char g_47943c[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479440
char g_479440[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479444
char g_479444[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479448
char g_479448[4] = "...";

// GLOBAL: STUNTGP_D3D 0x47944c
char g_47944c[4] = "...";

// GLOBAL: STUNTGP_D3D 0x479450
char g_479450[4] = "...";

// FUNCTION: STUNTGP_D3D 0x43c130
void FUN_43c130()
{
    int i;
    int j;

    for (i = 0; i < 19; i++)
    {
        g_menuState.unk0114[i][0].time = 7200;
        memcpy(g_menuState.unk0114[i][0].name, g_479420, 3);
        g_menuState.unk0114[i][1].time = 36000;
        memcpy(g_menuState.unk0114[i][1].name, g_479424, 3);
        g_menuState.unk0114[i][2].time = 0;
        memcpy(g_menuState.unk0114[i][2].name, g_479428, 3);
        g_menuState.unk0114[i][3].time = 0;
        memcpy(g_menuState.unk0114[i][3].name, g_47942c, 3);
    }
    for (i = 0; i < 100; i++)
    {
        g_menuState.unk0374[i].time = 0;
        memcpy(g_menuState.unk0374[i].name, g_479430, 3);
    }
    for (i = 0; i < 100; i++)
    {
        g_menuState.unk1dfc[i].time = 0;
        memcpy(g_menuState.unk1dfc[i].name, g_479434, 3);
    }
    for (i = 0; i < 25; i++)
    {
        g_menuState.unk0694[i].unk00 = 0;
        for (j = 0; j < 10; j++)
        {
            g_menuState.unk0694[i].entries[j].time = 7200;
            memcpy(g_menuState.unk0694[i].entries[j].name, g_479438, 3);
        }
    }
    for (i = 0; i < 25; i++)
    {
        memcpy(g_menuState.unk1a1c[i][0].name, g_47943c, 3);
        g_menuState.unk1a1c[i][0].time = 7200;
        memcpy(g_menuState.unk1a1c[i][1].name, g_479440, 3);
        g_menuState.unk1a1c[i][1].time = 36000;
        memcpy(g_menuState.unk1a1c[i][2].name, g_479444, 3);
        g_menuState.unk1a1c[i][2].time = 0;
        memcpy(g_menuState.unk1a1c[i][3].name, g_479448, 3);
        g_menuState.unk1a1c[i][3].time = 0;
    }
    for (i = 0; i < 10; i++)
    {
        memcpy(g_menuState.unk1d5c[i].name, g_47944c, 3);
        g_menuState.unk1d5c[i].time = 0;
    }
    for (i = 0; i < 10; i++)
    {
        memcpy(g_menuState.unk1dac[i].name, g_479450, 3);
        g_menuState.unk1dac[i].time = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x43c310
void FUN_43c310(char value)
{
    memset(&g_menuState.unlocked[1], value, 21);
    memset(&g_menuState.unlocked[25], value, 24);
    g_menuState.unk0074 = 1;
}

// FUNCTION: STUNTGP_D3D 0x43c370
void FUN_43c370()
{
    memset(g_menuState.unlocked, 0, sizeof(g_menuState.unlocked));
    g_menuState.unlocked[1] = 1;
    g_menuState.unlocked[4] = 1;
    g_menuState.unlocked[7] = 1;
    g_menuState.unlocked[8] = 1;
    g_menuState.unlocked[9] = 1;
    g_menuState.unlocked[10] = 1;
    g_menuState.unlocked[11] = 1;
    g_menuState.unlocked[15] = 1;
    g_menuState.unlocked[21] = 1;
    for (int i = 1; i < 25; i++)
    {
        int type = FUN_437360(i);
        if (type > 0 && type <= 2)
        {
            g_menuState.unlocked[24 + i] = 0;
        }
        else
        {
            g_menuState.unlocked[24 + i] = 1;
        }
    }
    g_menuState.unlocked[30] = 1;
    g_menuState.unlocked[35] = 1;
    g_menuState.unlocked[47] = 1;
    FUN_43c400();
}

// FUNCTION: STUNTGP_D3D 0x43c400
void FUN_43c400()
{
    memcpy(g_menuState.unlockedSaved, g_menuState.unlocked, sizeof(g_menuState.unlockedSaved));
    memcpy(g_menuState.saved, g_menuState.unlocked, sizeof(g_menuState.saved));
}

// FUNCTION: STUNTGP_D3D 0x43d200
void FUN_43d200()
{
    FUN_436ed0();
    FUN_43eff0();
    FUN_437eb0();
    FUN_43c000();
    if (g_menuState.unk0090 && g_menuState.unk0090 != g_menuState.language && FUN_43efc0() && !FUN_452d70(g_menuState.unk0090))
    {
        g_menuState.unk0090 = g_menuState.language;
    }
}

// FUNCTION: STUNTGP_D3D 0x43d790
int FUN_43d790(int value, int min, int max)
{
    if (value < min)
    {
        return min;
    }
    if (value > max)
    {
        return max;
    }
    return value;
}

// FUNCTION: STUNTGP_D3D 0x43d810
float FUN_43d810(float current, float target, float rate)
{
    float dist = FUN_43d9e0(target - current);
    if (dist != 0.0f)
    {
        float step = dist * 0.1f + rate;
        if (dist > step)
        {
            if (target < current)
            {
                step = -step;
            }
            return step + current;
        }
        return target;
    }
    return current;
}

// FUNCTION: STUNTGP_D3D 0x43d880
float FUN_43d880(float current, float target, float rate)
{
    float dist = FUN_43d9e0(target - current);
    if (dist != 0.0f)
    {
        float step = dist * 0.05f + rate;
        if (dist > step)
        {
            if (target < current)
            {
                step = -step;
            }
            return step + current;
        }
        return target;
    }
    return current;
}

// FUNCTION: STUNTGP_D3D 0x43d8f0
float FUN_43d8f0(float current, float target, float step)
{
    if (current != target)
    {
        return fabs(target - current) > step ? (target < current ? -step : step) + current : target;
    }
    return current;
}

// FUNCTION: STUNTGP_D3D 0x43d9b0
int FUN_43d9b0(int value)
{
    if (value < 0)
    {
        value = -value;
    }
    return value;
}

// FUNCTION: STUNTGP_D3D 0x43d9c0
int FUN_43d9c0(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

// FUNCTION: STUNTGP_D3D 0x43d9e0
float FUN_43d9e0(float value)
{
    return value < 0.0f ? -value : value;
}

// FUNCTION: STUNTGP_D3D 0x43da00
float FUN_43da00(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

// FUNCTION: STUNTGP_D3D 0x43da20
float FUN_43da20(float a, float b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

// Reads the detail level and language overrides next to the executable.
// FUNCTION: STUNTGP_D3D 0x43d280
void FUN_43d280()
{
    char path[256];
    FILE *file;
    // STRING: STUNTGP_D3D 0x4795f4
    sprintf(path, "%s\\detail.cfg", g_GameDirectory);
    // STRING: STUNTGP_D3D 0x479604
    file = fopen(path, "r");
    if (file)
    {
        // STRING: STUNTGP_D3D 0x479608
        fscanf(file, "%d", &g_menuState.unk0084);
        int detail = FUN_43d790(g_menuState.unk0084, 0, 100);
        g_menuState.unk0084 = detail - detail % 10;
        fclose(file);
    }
    // STRING: STUNTGP_D3D 0x47960c
    sprintf(path, "%s\\language.cfg", g_GameDirectory);
    // STRING: STUNTGP_D3D 0x47961c
    file = fopen(path, "r");
    if (file)
    {
        // STRING: STUNTGP_D3D 0x479620
        fscanf(file, "%d", &g_menuState.unk0090);
        if (g_menuState.unk0090 <= 0 || g_menuState.unk0090 >= 9)
        {
            g_menuState.unk0090 = 0;
        }
        fclose(file);
    }
}

// FUNCTION: STUNTGP_D3D 0x43d690
Initials *FUN_43d690(Initials *name)
{
    *g_479668 = *name;
    return g_479668;
}

// FUNCTION: STUNTGP_D3D 0x43d6d0
void FUN_43d6d0(BYTE *bits, int index, BYTE value)
{
    int i = index >> 3;
    BYTE mask = 1 << (index & 7);
    bits[i] &= ~mask;
    if (value)
    {
        bits[i] |= mask;
    }
}

// FUNCTION: STUNTGP_D3D 0x43d710
int FUN_43d710(int id)
{
    if (FUN_43d730(id) || FUN_43d760(id))
    {
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x43d730
int FUN_43d730(int id)
{
    switch (id)
    {
    case 4:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x43d760
int FUN_43d760(int id)
{
    switch (id)
    {
    case 11:
    case 12:
    case 13:
    case 14:
    case 16:
    case 17:
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x43dcc0
int FUN_43dcc0(int index, int base)
{
    switch (index)
    {
    case 1:
        return base + 0x171;
    case 2:
        return base + 0x174;
    case 3:
        return base + 0x177;
    case 4:
        return base + 0x17a;
    case 5:
        return base + 0x17d;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x43dd10
void FUN_43dd10(DWORD color)
{
    DWORD r = color & 0xff;
    DWORD g = color & 0xff00;
    BYTE b = ((BYTE *)&color)[2];
    g_5ff4b8 = b | (r << 16) | g;
}

// FUNCTION: STUNTGP_D3D 0x43dd70
int FUN_43dd70()
{
    g_frontEnd.unk78 = 0;
    return g_frontEnd.unk7c != 0;
}

// FUNCTION: STUNTGP_D3D 0x43dd90
void FUN_43dd90(int player)
{
    g_frontEnd.lockedPlayer = player;
}

// FUNCTION: STUNTGP_D3D 0x43dda0
void FUN_43dda0()
{
    memset(&g_frontEnd, 0, sizeof(g_frontEnd));
    g_frontEnd.fade = 0x10000;
    g_frontEnd.state = 1;
    g_frontEnd.screen = NULL;
    g_frontEnd.screenStatic = FALSE;
    g_frontEnd.nextScreen = NULL;
    g_frontEnd.nextScreenStatic = FALSE;
    g_frontEnd.objectCount = 0;
    g_frontEnd.unk5c = 1;
    g_frontEnd.unk60 = 0;
    g_frontEnd.unk64 = 0.0f;
    g_frontEnd.unk68 = 0.0f;
    g_frontEnd.unk6c = 0.0f;
    g_frontEnd.unk70 = 0.0f;
    g_frontEnd.unk74 = 0;
    g_frontEnd.unk78 = 0;
    g_frontEnd.unk7c = 0;
    g_frontEnd.unk80 = 0.0f;
    g_frontEnd.unk84 = 0;
    g_frontEnd.lockedPlayer = 0;
    g_frontEnd.unkbc = 0;
    g_frontEnd.unkc0 = 0;
    g_frontEnd.musicTrack = 0;
    g_frontEnd.unkcc = 0;
    FUN_43dee0();
}

// FUNCTION: STUNTGP_D3D 0x43de40
void FUN_43de40()
{
    g_frontEnd.musicTrack = 0;
}

// FUNCTION: STUNTGP_D3D 0x43dee0
void FUN_43dee0()
{
    g_frontEnd.unk88[0] = 0.0f;
    g_frontEnd.unk88[1] = 0.0f;
    g_frontEnd.unk88[2] = 0.0f;
    g_frontEnd.unk88[3] = 0.0f;
    g_frontEnd.unk88[4] = 0.0f;
    g_frontEnd.unk88[5] = 0.0f;
    g_frontEnd.unka0[0] = 0.0f;
    g_frontEnd.unka0[1] = 0.0f;
    g_frontEnd.unka0[2] = 0.0f;
    g_frontEnd.unka0[3] = 0.0f;
    g_frontEnd.unka0[4] = 0.0f;
    g_frontEnd.unka0[5] = 0.0f;
}

// FUNCTION: STUNTGP_D3D 0x43df60
void FUN_43df60(float a, float b, float c, float d, float e, float f)
{
    g_frontEnd.unka0[0] = a;
    g_frontEnd.unka0[1] = b;
    g_frontEnd.unka0[2] = c;
    g_frontEnd.unka0[3] = d;
    g_frontEnd.unka0[4] = e;
    g_frontEnd.unka0[5] = f;
}

// FUNCTION: STUNTGP_D3D 0x43efc0
int FUN_43efc0()
{
    return g_frontEnd.fade * 100 / 0x10000 > 95;
}

// FUNCTION: STUNTGP_D3D 0x43eff0
void FUN_43eff0()
{
    int fade = g_frontEnd.fade * 100 / 0x10000;
    if (g_frontEnd.unkcc)
    {
        FUN_43dd70();
        FUN_440880(2);
        FUN_4411c0();
        FUN_43de40();
        FUN_43ef10(1, 1);
        g_frontEnd.unkcc = 0;
        return;
    }
    g_frontEnd.unkbc = 0;
    g_frontEnd.unk5c = 1;
    g_frontEnd.unk6c += g_frontEnd.unk64 * (1.0f / 60.0f);
    g_frontEnd.unk70 += g_frontEnd.unk68 * (1.0f / 60.0f);
    FUN_43f610();
    g_frontEnd.unk5c = 0;
    if (fade < g_frontEnd.unk7c)
    {
        fade = g_frontEnd.unk7c;
    }
    FUN_442ad0(2, 1, 0, 0, fade, fade, 1.0f);
    g_frontEnd.unk5c = 1;
    if (g_frontEnd.nextScreen)
    {
        FUN_43f310(g_frontEnd.nextScreen);
    }
    else if (g_frontEnd.screen)
    {
        FUN_43f310(g_frontEnd.screen);
    }
    g_frontEnd.unk5c = 0;
    switch (g_frontEnd.state)
    {
    case 3:
        if (g_frontEnd.fade > 0)
        {
            g_frontEnd.fade = FUN_43d790(g_frontEnd.fade - 0x2492, 0, 0x10000);
        }
        else
        {
            g_frontEnd.state = 1;
        }
        break;
    case 2:
        if (g_frontEnd.fade < 0x10000)
        {
            g_frontEnd.fade = FUN_43d790(g_frontEnd.fade + 0x2492, 0, 0x10000);
        }
        else
        {
            if (g_frontEnd.screen && !g_frontEnd.screenStatic)
            {
                g_frontEnd.screen->destroy(g_frontEnd.screen);
                Pool_Free(g_frontEnd.screen);
            }
            g_frontEnd.screen = g_frontEnd.nextScreen;
            g_frontEnd.screenStatic = g_frontEnd.nextScreenStatic;
            g_frontEnd.nextScreen = NULL;
            g_frontEnd.nextScreenStatic = FALSE;
            FUN_43dee0();
            g_frontEnd.screen->message(g_frontEnd.screen, 0x13, 0);
            g_frontEnd.state = 3;
            g_frontEnd.unk80 = 0.0f;
        }
        break;
    }
    g_frontEnd.unk80 = FUN_43d810(g_frontEnd.unk80, 1.0f, 0.005f);
    if (!g_frontEnd.unkbc)
    {
        if (g_frontEnd.screen)
        {
            g_frontEnd.screen->message(g_frontEnd.screen, 2, 0);
        }
        if (g_frontEnd.nextScreen)
        {
            g_frontEnd.nextScreen->message(g_frontEnd.nextScreen, 2, 0);
        }
        g_frontEnd.unk5c = 1;
        if (g_frontEnd.screen)
        {
            if (g_frontEnd.nextScreen)
            {
                g_frontEnd.nextScreen->message(g_frontEnd.nextScreen, 1, 0);
            }
            else
            {
                g_frontEnd.screen->message(g_frontEnd.screen, 1, 0);
            }
        }
        g_frontEnd.unk5c = 0;
    }
    g_frontEnd.unk88[0] = FUN_43d810(g_frontEnd.unk88[0], g_frontEnd.unka0[0], 0.001f);
    g_frontEnd.unk88[1] = FUN_43d810(g_frontEnd.unk88[1], g_frontEnd.unka0[1], 0.001f);
    g_frontEnd.unk88[2] = FUN_43d810(g_frontEnd.unk88[2], g_frontEnd.unka0[2], 0.001f);
    g_frontEnd.unk88[3] = FUN_43d810(g_frontEnd.unk88[3], g_frontEnd.unka0[3], 0.001f);
    g_frontEnd.unk88[4] = FUN_43d810(g_frontEnd.unk88[4], g_frontEnd.unka0[4], 0.001f);
    g_frontEnd.unk88[5] = FUN_43d810(g_frontEnd.unk88[5], g_frontEnd.unka0[5], 0.001f);
    g_frontEnd.unk74++;
    g_frontEnd.unk78++;
}

// Routes menu input to the screen: from the locked player, or from every active one.
// FUNCTION: STUNTGP_D3D 0x43f310
void FUN_43f310(PoolObject *screen)
{
    int i;
    int count = 0;
    if (g_frontEnd.unkc8)
    {
        if (g_frontEnd.lockedPlayer)
        {
            if (FUN_43f5e0(g_frontEnd.lockedPlayer))
            {
                return;
            }
        }
        else
        {
            for (i = 1; i < 5; i++)
            {
                if (FUN_43f5e0(i))
                {
                    return;
                }
            }
        }
        g_frontEnd.unkc8 = 0;
    }
    if (g_frontEnd.lockedPlayer)
    {
        if (FUN_437090(g_frontEnd.lockedPlayer))
        {
            FUN_43f3e0(screen, g_frontEnd.lockedPlayer);
        }
        else
        {
            g_frontEnd.unkbc = 1;
        }
    }
    else
    {
        for (i = 1; i < 5; i++)
        {
            if (FUN_437090(i))
            {
                FUN_43f3e0(screen, i);
                count++;
            }
        }
        if (!count)
        {
            g_frontEnd.unkbc = 1;
        }
    }
    if (g_frontEnd.unkbc != g_frontEnd.unkc0)
    {
        if (g_frontEnd.unkbc)
        {
            FUN_440880(7);
        }
        else
        {
            FUN_440880(8);
        }
    }
    g_frontEnd.unkc0 = g_frontEnd.unkbc;
}

// FUNCTION: STUNTGP_D3D 0x43f3e0
void FUN_43f3e0(PoolObject *screen, int player)
{
    char key = g_62ddfc;
    int action = 0;
    int pressed = 0;
    g_62ddfc = 0;
    if (FUN_436fd0(player, 7))
    {
        pressed = 0x11;
    }
    else if (FUN_436fd0(player, 6))
    {
        pressed = 0x10;
    }
    else if (FUN_436fd0(player, 5))
    {
        pressed = 0xf;
    }
    else if (FUN_436fd0(player, 1))
    {
        pressed = 0xb;
    }
    else if (FUN_436fd0(player, 2))
    {
        pressed = 0xc;
    }
    else if (FUN_436fd0(player, 3))
    {
        pressed = 0xd;
    }
    else if (FUN_436fd0(player, 4))
    {
        pressed = 0xe;
    }
    if (key)
    {
        g_frontEnd.unk78 = 0;
        if (g_frontEnd.unk7c)
        {
            return;
        }
        screen->message(screen, 0x12, key);
    }
    if (FUN_436fc0(player, 7))
    {
        action = 10;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 6))
    {
        action = 9;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 1))
    {
        action = 4;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 2))
    {
        action = 5;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 3))
    {
        action = 6;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 4))
    {
        action = 7;
        screen->message(screen, action, player);
    }
    if (FUN_436fc0(player, 5))
    {
        action = 8;
        screen->message(screen, action, player);
    }
    if (action || pressed)
    {
        g_frontEnd.unk78 = 0;
    }
    if (!g_frontEnd.unk7c && pressed)
    {
        screen->message(screen, pressed, player);
    }
}

// FUNCTION: STUNTGP_D3D 0x43f5e0
int FUN_43f5e0(int player)
{
    for (int i = 1; i < 8; i++)
    {
        if (FUN_436fc0(player, i))
        {
            return 1;
        }
    }
    return 0;
}

// Idle timeouts: drop back to the title screen, and fade in the attract overlay.
// FUNCTION: STUNTGP_D3D 0x43f610
void FUN_43f610()
{
    if (g_frontEnd.screen)
    {
        switch (g_frontEnd.screen->type)
        {
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
        case 11:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 27:
        case 29:
            if (g_frontEnd.unk78 > 3600)
            {
                FUN_440880(2);
                FUN_43ef10(1, 1);
                FUN_43dd70();
            }
        }
    }
    if (g_frontEnd.unk78 > 18000)
    {
        g_frontEnd.unk7c++;
    }
    else
    {
        g_frontEnd.unk7c = 0;
    }
    g_frontEnd.unk7c = FUN_43d790(g_frontEnd.unk7c, 0, 70);
}

// FUNCTION: STUNTGP_D3D 0x440890
void FUN_440890(int id)
{
    switch (id)
    {
    case 11:
    case 12:
    case 13:
    case 14:
        FUN_440880(1);
        break;
    case 15:
    case 16:
        FUN_440880(3);
        break;
    case 17:
        FUN_440880(2);
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x4408e0
void FUN_4408e0()
{
    g_5ff8c0 = 1;
}

// FUNCTION: STUNTGP_D3D 0x4405b0
int FUN_4405b0(int value)
{
    return value;
}

// FUNCTION: STUNTGP_D3D 0x440770
void FUN_440770(int a, int b)
{
    if (g_5ff8c0 > 0)
    {
        int sound = FUN_4407a0(a);
        if (sound)
        {
            FUN_461150(sound, 0, b, 0xff, 0, 0, 0);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x4407a0
int FUN_4407a0(int id)
{
    switch (id)
    {
    case 1:
        return 0x33;
    case 2:
        return 0x34;
    case 3:
        return 0x35;
    case 4:
        return 0x36;
    case 5:
        return 0x37;
    case 6:
        return 0x38;
    case 7:
        return 0x39;
    case 8:
        return 0x3a;
    case 9:
        return 0x3b;
    case 10:
        return 0x3c;
    case 11:
        return 0x3d;
    case 12:
        return 0x3e;
    case 13:
        return 0x3f;
    case 16:
        return 0x42;
    case 17:
        return 0x43;
    case 18:
        return 0x44;
    case 19:
        return 0x45;
    case 20:
        return 0x46;
    case 21:
        return 0x47;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x440880
void FUN_440880(int a)
{
    FUN_440770(a, 0);
}

// FUNCTION: STUNTGP_D3D 0x441210
void FUN_441210()
{
}

// FUNCTION: STUNTGP_D3D 0x450510
void FUN_450510(Unk4516c0 *object)
{
    PoolObject *child = object->unk14;
    child->destroy(child);
    Pool_Free(child);
    object->unk14 = NULL;
    child = object->unk18;
    child->destroy(child);
    Pool_Free(child);
    object->unk18 = NULL;
}

// FUNCTION: STUNTGP_D3D 0x450880
int FUN_450880(Unk450930 *object)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    // The two handlers are copied as one block.
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x486740
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_486708))
    {
        Pool_Free(list);
        object->child = NULL;
    }
    else
    {
        object->child = &list->base;
    }
    PoolObject *child = object->child;
    child->message(child, 0x18, 0);
    child->message(child, 0x16, 0);
    object->unk14 = g_menuState.offsetX;
    object->unk18 = g_menuState.offsetY;
    object->unk1c = (float)g_menuState.offsetX;
    object->unk20 = (float)g_menuState.offsetY;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x450930
void FUN_450930(Unk450930 *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x450ac0
void FUN_450ac0(MenuObject *object)
{
    object->unk1c = FUN_43d7b0(object->unk1c, -31.0f, 31.0f);
    object->unk20 = FUN_43d7b0(object->unk20, -31.0f, 31.0f);
}

// STUB: STUNTGP_D3D 0x437de0
int FUN_437de0(int sponsor, int car, ShopCar *setup)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x437230
int FUN_437230(int car, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x44bd00
void FUN_44bd00()
{
}

void FUN_450db0(Unk4516c0 *object);
void FUN_450dd0(Unk4516c0 *object);

// FUNCTION: STUNTGP_D3D 0x450c10
int FUN_450c10(Unk4516c0 *object)
{
    object->unk28 = 0;
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    // The two handlers are copied as one block.
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x4868d8
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4867d0))
    {
        Pool_Free(list);
        object->unk18 = NULL;
    }
    else
    {
        object->unk18 = &list->base;
    }
    object->unk18->message(object->unk18, 0x18, 0);
    list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x4868e4
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4868a0))
    {
        Pool_Free(list);
        object->unk14 = NULL;
    }
    else
    {
        object->unk14 = &list->base;
    }
    PoolObject *child = object->unk14;
    child->message(child, 0x18, 0);
    child->message(child, 0x16, 0);
    object->unk24 = 0;
    object->unk1c = 0;
    object->unk20 = 1;
    FUN_450db0(object);
    MenuSlot160 *slot = &g_menuState.unk19d7c;
    int price = FUN_437de0(slot->sponsor, slot->car, &slot->carSetup);
    g_menuState.unk4398 = 0;
    for (int i = 1; i < 21; i++)
    {
        int cost = FUN_437de0(slot->sponsor, i, &g_menuState.cars[i]);
        if ((FUN_437230(i, g_menuState.unk4230) || g_menuState.unk0074) && slot->money + price >= cost &&
            i != slot->car)
        {
            g_menuState.unk439c[g_menuState.unk4398] = i;
            g_menuState.unk4398++;
        }
    }
    FUN_450dd0(object);
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x450db0
void FUN_450db0(Unk4516c0 *object)
{
    if (object->unk20)
    {
        FUN_44bd00();
        object->unk20 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x450dd0
void FUN_450dd0(Unk4516c0 *object)
{
    g_486800[0].text = (g_menuState.unk19d7c.unk008 >= 2) + 0x9c;
    g_486800[2].id = g_menuState.unk4398 <= 0 ? -2 : 2;
}

// FUNCTION: STUNTGP_D3D 0x450e10
void FUN_450e10(Unk4516c0 *object)
{
    PoolObject *child = object->unk14;
    child->destroy(child);
    Pool_Free(child);
    object->unk14 = NULL;
    child = object->unk18;
    child->destroy(child);
    Pool_Free(child);
    object->unk18 = NULL;
}

// FUNCTION: STUNTGP_D3D 0x451680
void FUN_451680(Unk4516c0 *object)
{
    object->unk14->message(object->unk14, 0x19, 0);
    PoolObject *child = object->unk18;
    child->message(child, 0x13, 0);
    child->message(child, 0x1c, 2);
    object->unk28 = 1;
}

// FUNCTION: STUNTGP_D3D 0x4516c0
void FUN_4516c0(Unk4516c0 *object)
{
    object->unk14->message(object->unk14, 0x18, 0);
    object->unk18->message(object->unk18, 0x14, 0);
    object->unk28 = 0;
}

// FUNCTION: STUNTGP_D3D 0x451a50
void FUN_451a50(Unk451a50 *object, int value, int group)
{
    object->groups[(group - 1) * 12 + object->groups[(group - 1) * 12] + 2] = value;
    object->groups[(group - 1) * 12]++;
}

// FUNCTION: STUNTGP_D3D 0x451a80
void FUN_451a80(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x451e80
int FUN_451e80(Unk451a50 *object, float x, float y)
{
    int row = (int)(y + 0.5f);
    int column = (int)(x + 0.5f);
    if (column >= object->groups[row * 12])
    {
        return 0;
    }
    return object->groups[row * 12 + column + 2];
}

// FUNCTION: STUNTGP_D3D 0x452530
void FUN_452530(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x4529c0
void FUN_4529c0(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x452ac0
void FUN_452ac0()
{
    float height = FUN_438950(1.25f);
    float y = (480.0f - height * 16.0f) * 0.5f;
    for (int id = 0x2b6; id < 0x2c6; id++)
    {
        FUN_438be0(320.0f, y, 12, 4, id, 1.25f, 0xffffffff, 3);
        y += height;
    }
}

// FUNCTION: STUNTGP_D3D 0x452b30
int FUN_452b30(MenuObject *object)
{
    object->unk14 = 0;
    object->unk18 = 0;
    FUN_440880(16);
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x452d50
void FUN_452d50(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x452d70
int FUN_452d70(int id)
{
    if (FUN_440c40(id) >= 0)
    {
        g_menuState.unk0090 = id;
    }
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x452fc0
int FUN_452fc0(MenuObject *object)
{
    object->unk14 = 0;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x4531d0
void FUN_4531d0(Unk4516c0 *object)
{
    PoolObject *child = object->unk14;
    child->destroy(child);
    Pool_Free(child);
    object->unk14 = NULL;
    child = object->unk18;
    child->destroy(child);
    Pool_Free(child);
    object->unk18 = NULL;
}

// FUNCTION: STUNTGP_D3D 0x453430
void FUN_453430(Unk453460 *object)
{
    PoolObject *child = object->unk18;
    child->message(child, 0x13, 0);
    child->message(child, 0x1c, 2);
    object->unk1c = 1;
}

// FUNCTION: STUNTGP_D3D 0x453460
void FUN_453460(Unk453460 *object)
{
    object->unk18->message(object->unk18, 0x14, 0);
    object->unk1c = 0;
}

// FUNCTION: STUNTGP_D3D 0x4536f0
void FUN_4536f0(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x4542a0
void FUN_4542a0(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x454410
int FUN_454410(Unk454b20 *object)
{
    object->unk1c = 0;
    object->unk20 = 0;
    object->unk24 = 0;
    object->unk28 = 0;
    object->unk2c = 0;
    object->unk30 = 0;
    object->unk3c = 0;
    object->unk40 = 0;
    object->unk44 = 0;
    object->unk34 = 0;
    object->unk38 = 0;
    object->unk14 = 0;
    object->unk4c = 0;
    object->text[0] = g_menuState.unk44d0 = 0;
    object->unk18 = g_menuState.unk4238;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x4547e0
int FUN_4547e0(char c, int *column, int *row)
{
    for (int r = 0; r < 4; r++)
    {
        for (int i = 0; i < 8; i++)
        {
            if (g_4881b0[r][i] == c)
            {
                *column = i;
                *row = r;
                return i + r * 8;
            }
        }
    }
    return -1;
}

// FUNCTION: STUNTGP_D3D 0x454af0
void FUN_454af0(Unk454b20 *object, char c)
{
    int len = strlen(object->text);
    if (len < 3)
    {
        object->text[len] = c;
        object->text[len + 1] = '\0';
        object->unk14 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x454b20
void FUN_454b20(Unk454b20 *object)
{
    int len = strlen(object->text);
    if (len > 0)
    {
        object->text[len - 1] = '\0';
    }
}

// FUNCTION: STUNTGP_D3D 0x454b40
void FUN_454b40(Unk454b40 *object, int x, int y)
{
    float fx = x;
    object->unk1c = x;
    object->unk20 = y;
    object->unk24 = fx;
    float fy = y;
    object->unk28 = fy;
    object->unk2c = fx;
    object->unk30 = fy;
}

// FUNCTION: STUNTGP_D3D 0x454c80
int FUN_454c80(Unk454b20 *object, int column, int row)
{
    if (column < 0 || row < 0 || column >= 8 || row >= 4)
    {
        return 0;
    }
    int len = strlen(object->text);
    if (len < 3)
    {
        return column != 7 || row != 3;
    }
    return column >= 6 && row == 3;
}

// FUNCTION: STUNTGP_D3D 0x454d80
void FUN_454d80(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x455090
void FUN_455090(Unk4516c0 *object)
{
    PoolObject *child = object->unk18;
    child->destroy(child);
    Pool_Free(child);
    object->unk18 = NULL;
    child = object->unk14;
    child->destroy(child);
    Pool_Free(child);
    object->unk14 = NULL;
}

// FUNCTION: STUNTGP_D3D 0x4552f0
void FUN_4552f0(Unk453460 *object)
{
    PoolObject *child = object->unk18;
    child->message(child, 0x13, 0);
    child->message(child, 0x1c, 2);
    object->unk1c = 1;
}

// FUNCTION: STUNTGP_D3D 0x455320
void FUN_455320(Unk453460 *object)
{
    object->unk18->message(object->unk18, 0x14, 0);
    object->unk1c = 0;
}

// FUNCTION: STUNTGP_D3D 0x455410
void FUN_455410(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x4555e0
int FUN_4555e0(MenuHolder *object)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    // The two handlers are copied as one block.
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488600
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4885c8))
    {
        Pool_Free(list);
        object->child = NULL;
    }
    else
    {
        object->child = &list->base;
    }
    PoolObject *child = object->child;
    child->message(child, 0x18, 0);
    child->message(child, 0x16, 0);
    int value = FUN_43d790(g_menuState.unk0084, 0, 100);
    g_menuState.unk0084 = value - value % 10;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x455690
void FUN_455690(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x455b90
int FUN_455b90(int player)
{
    if (FUN_436fd0(player, 3) || FUN_436fd0(player, 4) || FUN_436fd0(player, 1) || FUN_436fd0(player, 2))
    {
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x455d70
void FUN_455d70(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x455c70
int FUN_455c70(Unk455fc0 *object)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    // The two handlers are copied as one block.
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488750
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488718))
    {
        Pool_Free(list);
        object->child = NULL;
    }
    else
    {
        object->child = &list->base;
    }
    PoolObject *child = object->child;
    child->message(child, 0x18, 0);
    child->message(child, 0x16, 0);
    object->unk18 = g_menuState.unk00d4 % 2;
    object->unk1c = g_menuState.unk00d8 % 2;
    object->unk20 = g_menuState.unk00dc % 3;
    object->unk24 = g_menuState.unk00e0 % 3;
    object->unk28 = g_menuState.unk00e4 % 4;
    object->unk2c = g_menuState.unk00e8 % 4;
    g_menuState.unk1dae4 = 0;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x455f60
void FUN_455f60(Unk455fc0 *object)
{
    MenuItem *items = g_488718.items;
    items[1].text = object->unk18 + 0x293;
    items[2].text = object->unk1c + 0x295;
    items[3].text = object->unk20 + 0x297;
    items[4].text = object->unk24 + 0x29a;
    items[5].text = object->unk28 + 0x29d;
    items[6].text = object->unk2c + 0x2a1;
}

// FUNCTION: STUNTGP_D3D 0x455fc0
void FUN_455fc0(Unk455fc0 *object)
{
    g_menuState.unk00d4 = object->unk18;
    g_menuState.unk00d8 = object->unk1c;
    g_menuState.unk00dc = object->unk20;
    g_menuState.unk00e0 = object->unk24;
    g_menuState.unk00e4 = object->unk28;
    g_menuState.unk00e8 = object->unk2c;
}

// FUNCTION: STUNTGP_D3D 0x456010
int FUN_456010(Unk456070 *object)
{
    object->unk1c = 0x293;
    object->unk14 = 15;
    object->unk18 = 0;
    for (int i = 0; i < 5; i++)
    {
        object->unk34[i] = 0;
        object->unk48[i] = 0;
    }
    g_menuState.unk423c = 0;
    g_menuState.unk46ac[0] = 0;
    g_menuState.unk46a8 = 0;
    g_menuState.unk46ac[1] = 0;
    g_menuState.unk46ac[2] = 0;
    g_menuState.unk46ac[3] = 0;
    FUN_456070(object);
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x456070
void FUN_456070(Unk456070 *object)
{
    for (int i = 1; i < 5; i++)
    {
        int a;
        int b;
        a = b = 1;
        if (!FUN_437090(i))
        {
            a = b = 0;
        }
        object->unk20[i] = a;
        object->unk34[i] = b;
    }
}

// FUNCTION: STUNTGP_D3D 0x4565a0
void FUN_4565a0(Unk456070 *object, int player)
{
    FUN_440880(3);
    object->unk48[player] = 1;
    FUN_456070(object);
}

// FUNCTION: STUNTGP_D3D 0x4565d0
void FUN_4565d0(Unk456070 *object, int player)
{
    FUN_440880(2);
    object->unk48[player] = 0;
    FUN_456070(object);
}

// FUNCTION: STUNTGP_D3D 0x456600
int FUN_456600(int player)
{
    if (FUN_436fd0(player, 3) || FUN_436fd0(player, 4) || FUN_436fd0(player, 1) || FUN_436fd0(player, 2))
    {
        return 1;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x456650
int FUN_456650(Unk456070 *object)
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (object->unk48[i + 1])
        {
            count++;
        }
    }
    return count;
}

// FUNCTION: STUNTGP_D3D 0x456670
int FUN_456670(Unk456070 *object)
{
    int count = 0;
    int *out = g_menuState.unk46ac;
    for (int i = 1; i < 5; i++)
    {
        if (object->unk48[i])
        {
            *out++ = i;
            count++;
        }
    }
    g_menuState.unk423c = count;
    return count >= 2;
}

// FUNCTION: STUNTGP_D3D 0x456760
void FUN_456760(Unk456070 *object)
{
    int seconds = object->unk1c / 60;
    if (FUN_456650(object) < 2)
    {
        object->unk1c = 0x293;
        return;
    }
    if (object->unk1c)
    {
        object->unk1c--;
    }
    if (seconds != object->unk1c / 60)
    {
        FUN_440880(10);
    }
}

// FUNCTION: STUNTGP_D3D 0x456910
void FUN_456910(Unk4516c0 *object)
{
    PoolObject *child = object->unk14;
    child->destroy(child);
    Pool_Free(child);
    object->unk14 = NULL;
    child = object->unk18;
    child->destroy(child);
    Pool_Free(child);
    object->unk18 = NULL;
}

// FUNCTION: STUNTGP_D3D 0x456f70
void FUN_456f70(Unk453460 *object)
{
    PoolObject *child = object->unk18;
    child->message(child, 0x13, 0);
    child->message(child, 0x1c, 2);
    object->unk20 = 1;
}

// FUNCTION: STUNTGP_D3D 0x456fa0
void FUN_456fa0(Unk453460 *object)
{
    object->unk18->message(object->unk18, 0x14, 0);
    object->unk20 = 0;
}

// FUNCTION: STUNTGP_D3D 0x4570f0
void FUN_4570f0(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x4572e0
void FUN_4572e0(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x457500
void FUN_457500(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x457770
void FUN_457770(Unk457770 *object)
{
    if (object->unk18)
    {
        switch (g_menuState.unk0094)
        {
        case 2:
            object->unk14->message(object->unk14, 0x1c, 1);
            break;
        case 1:
            object->unk14->message(object->unk14, 0x1c, 0);
            break;
        }
        object->unk18 = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x4577c0
void FUN_4577c0(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// FUNCTION: STUNTGP_D3D 0x457a20
int FUN_457a20(int value)
{
    return value > 0 && value <= 3;
}

// FUNCTION: STUNTGP_D3D 0x457e70
int FUN_457e70(Unk457e70 *object, int id)
{
    for (int i = 0; i < object->count; i++)
    {
        if (object->entries[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

// FUNCTION: STUNTGP_D3D 0x457ea0
void FUN_457ea0(Unk457ea0 *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}

// Integer division rounding up.
// FUNCTION: STUNTGP_D3D 0x4586e0
int FUN_4586e0(int value, int divisor)
{
    return (value + divisor - 1) / divisor;
}

// FUNCTION: STUNTGP_D3D 0x4586f0
int FUN_4586f0(Unk457e70 *object)
{
    for (int i = 0; i < object->count; i++)
    {
        int type = object->entries[i].unk08;
        if (type == 1 || (type > 3 && type <= 5))
        {
            return 1;
        }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x458800
int FUN_458800()
{
    int screen = g_menuState.unk46c4;
    if (screen)
    {
        return FUN_43ef10(0, screen);
    }
    return FUN_43eef0();
}

// FUNCTION: STUNTGP_D3D 0x458860
void FUN_458860(Unk458860 *object)
{
    object->unk1ec = 0;
    object->unk1e8 = 0;
    object->unk1f0 = 0;
}

// FUNCTION: STUNTGP_D3D 0x458a60
void FUN_458a60(Unk458860 *object, int a, int b, int c)
{
    object->unk1f4 = a;
    object->unk1e8 = c;
    object->unk1ec = b;
    object->unk1f0 = 0;
    object->unk1f8 = 10;
    FUN_440880(3);
    if (b == 1)
    {
        object->unk40->message(object->unk40, 0x1c, 1);
    }
    else
    {
        object->unk40->message(object->unk40, 0x1c, 0);
    }
}

// FUNCTION: STUNTGP_D3D 0x458ad0
void FUN_458ad0(Unk457e70 *object, int a)
{
    switch (object->entries[object->unk20].unk08)
    {
    case 1:
    case 3:
        FUN_440880(9);
        break;
    case 2:
        FUN_458a60(object, a, 1, 1);
        break;
    case 4:
        FUN_458a60(object, a, 2, 0);
        break;
    case 5:
        FUN_458a60(object, a, 3, 0);
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x458b30
void FUN_458b30(Unk457e70 *object, int a)
{
    int type = object->entries[object->unk20].unk08;
    if (type <= 0)
    {
        return;
    }
    if (type > 4)
    {
        if (type == 5)
        {
            FUN_458a60(object, a, 3, 0);
        }
    }
    else
    {
        FUN_440880(9);
    }
}

// FUNCTION: STUNTGP_D3D 0x458b60
void FUN_458b60(Unk457e70 *object, int a)
{
    switch (object->entries[object->unk20].unk08)
    {
    case 1:
    case 3:
        FUN_440880(9);
        break;
    case 2:
        FUN_458a60(object, a, 1, 1);
        break;
    case 5:
        FUN_458a60(object, a, 2, 1);
        break;
    case 4:
        FUN_458a60(object, a, 2, 0);
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x458bc0
void FUN_458bc0(Unk457e70 *object, int a)
{
    int type = object->entries[object->unk20].unk08;
    if (type <= 0)
    {
        return;
    }
    if (type > 4)
    {
        if (type == 5)
        {
            FUN_458a60(object, a, type, 0);
        }
    }
    else
    {
        FUN_440880(9);
    }
}

// FUNCTION: STUNTGP_D3D 0x458bf0
void FUN_458bf0(Unk457e70 *object, int a)
{
    switch (object->entries[object->unk20].unk08)
    {
    case 1:
    case 3:
        FUN_440880(9);
        break;
    case 2:
        FUN_458a60(object, a, 1, 1);
        break;
    case 5:
        FUN_458a60(object, a, 4, 1);
        break;
    case 4:
        FUN_458a60(object, a, 4, 0);
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x458d00
void FUN_458d00(Unk457e70 *object)
{
    switch (g_menuState.unk46c8)
    {
    case 1:
    case 2:
    case 3:
        g_menuState.unk46d8 = object->entries[object->unk20].id;
        break;
    case 4:
    case 5:
        g_menuState.unk46dc = object->entries[object->unk20].id;
        break;
    }
}

// FUNCTION: STUNTGP_D3D 0x459300
void FUN_459300(MenuHolder *object)
{
    PoolObject *child = object->child;
    child->destroy(child);
    Pool_Free(child);
    object->child = NULL;
}
