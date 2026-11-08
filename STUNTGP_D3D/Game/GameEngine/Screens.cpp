#include "objects.h"
#include "Game/GameEngine/MenuUpdate.h"
#include "sprite.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// PageSelectTeam: a menu and a scroll position.
// PageHighScore
// PageLanguage
int FUN_4371c0(int track, int mode);
int FUN_4375a0(int *tracks, int count);

// PageSlot
// PageSelectTrack
// PageUnlock
// PageCatalog
// Header of a saved ghost, read by FUN_440660.
void FUN_4400a0(int value);
void FUN_43dd40(int a, float b, float c);
void FUN_440890(int id);
void FUN_438710(float x, float y, int layer, int def, float scale, DWORD flags);

int FUN_436fd0(int player, int button);
int FUN_455b90(int player);
void FUN_455be0(int player, int delta);
void FUN_455c20(int player, int delta);

void FUN_4402f0(int value);
int FUN_440180();
int FUN_458e10();
int FUN_458e30();
int FUN_458e50();
int FUN_458eb0();

// PageArcadeScore
int FUN_452d70(int id);
void FUN_440880(int a);

int FUN_4527d0(int index);

void FUN_438a20(float x, float y, int layer, int sub, int style, const char *text, float size, D3DCOLOR color,
                DWORD flags, float unk18);
Initials *FUN_43d690(Initials *name);

struct Unk459790
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18
    int unk1c;         // 0x1c
    int unk20;         // 0x20
    int unk24;         // 0x24
    int unk28;         // 0x28, total score before this race
    int unk2c;         // 0x2c
    int unk30;         // 0x30, points for the position
    int unk34;         // 0x34
    int unk38;         // 0x38
    int unk3c;         // 0x3c
    int unk40;         // 0x40
    int unk44;         // 0x44
    int unk48;         // 0x48
    int unk4c;         // 0x4c
    int unk50;         // 0x50
    int unk54;         // 0x54
    int unk58[6];      // 0x58, results sorted by position
    int unk70;         // 0x70
    int unk74;         // 0x74
    int unk78;         // 0x78
    int unk7c;         // 0x7c
    int unk80[8];      // 0x80
    float unka0[8];    // 0xa0
};

int FUN_437d20(ScoreEntry *entry, Initials *name, int score);
int FUN_437d60(ScoreEntry *entry, Initials *name, int time);
int FUN_459a00(int which);

struct GhostHeader
{
    BYTE unk00[0x1c]; // 0x00
    int frames;       // 0x1c
    BYTE unk20[0xc];  // 0x20
    char name[0x54];  // 0x2c
};

int FUN_440160();
int FUN_4402e0();
int FUN_440660(void *buffer, int size, int ghost);
char *FUN_43d550(int frames);
float FUN_43d8f0(float current, float target, float step);
int FUN_457a20(int value);
int FUN_457bf0(int card, int *freeSpace);
int FUN_457e70(Unk457e70 *object, int id);

struct Unk4522c0
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18
    int unk1c;         // 0x1c
    int unk20;         // 0x20
    int unk24;         // 0x24
    int unk28;         // 0x28
};

int FUN_437710(int *tracks, int count);
int FUN_437a90(int id);
int FUN_437af0(int track);

struct Unk45db80
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18
    int unk1c;         // 0x1c
    int unk20;         // 0x20
};

// One newly unlocked car or track, shown by PageUnlock.
struct Unlock
{
    char text[0x80]; // 0x00
    int id;          // 0x80
};

char *FUN_441170(int id);
void FUN_437870();

struct Unk45c4b0
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18
    int unk1c;         // 0x1c, selected track
    float unk20;       // 0x20
    float unk24;       // 0x24
    int unk28;         // 0x28
    int unk2c;         // 0x2c
    int unk30;         // 0x30
};

struct Unk45a9c0
{
    DWORD unk00[5];    // 0x00
    int unk14;         // 0x14
    int unk18;         // 0x18
    int unk1c;         // 0x1c, selected slot
    int unk20;         // 0x20
    float unk24;       // 0x24
    float unk28;       // 0x28
    float unk2c;       // 0x2c
    float unk30;       // 0x30
    PoolObject *unk34; // 0x34
    PoolObject *unk38; // 0x38
};

int FUN_437de0(int sponsor, int car, ShopCar *setup);
char *FUN_43d5f0(int value, int digits);

struct Unk452c00
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18, selected language
    int unk1c;         // 0x1c
    float unk20;       // 0x20
    float unk24;       // 0x24
    int unk28;         // 0x28
};

int FUN_445ad0();
int FUN_440c40(int id);

struct Unk459200
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18
    int unk1c;         // 0x1c, first entry shown
    int unk20;         // 0x20
    int unk24;         // 0x24
    int unk28;         // 0x28
    float unk2c;       // 0x2c
    float unk30;       // 0x30
    float unk34;       // 0x34
    ScoreList scores;  // 0x38
};

struct Unk45b520
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    float unk18;       // 0x18, bob phase
};

void FUN_43bf30();
void FUN_457770(Unk457770 *object);

struct Unk45b7a0
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    float unk18;       // 0x18
    float unk1c;       // 0x1c
};

// PageSelectTree: two menus.
struct Unk45d2e0
{
    DWORD unk00[5];     // 0x00
    PoolObject *unk14;  // 0x14
    PoolObject *unk18;  // 0x18
    int unk1c;          // 0x1c
    int unk20;          // 0x20
    float unk24;        // 0x24
    float unk28;        // 0x28
    int unk2c;          // 0x2c
    int unk30;          // 0x30
    int unk34[2];       // 0x34, FUN_437920 of unk2c and unk30
};

struct Unk450930;
struct Unk454b20;
struct Unk455fc0;
struct Unk456070;
struct Unk457ea0;
struct Unk45ab70;
struct Unk45c670;

int FUN_45c030(MenuObject *object, int arg);
void FUN_45c070(PoolObject *object);
int FUN_45c080(PoolObject *object, int msg, int arg);
int FUN_4530b0(Unk4516c0 *object, int arg);
void FUN_4531d0(Unk4516c0 *object);
int FUN_453210(Unk4516c0 *object, int msg, int arg);
int FUN_45a770(MenuHolder *object, int arg);
void FUN_45a7f0(MenuHolder *object);
int FUN_45a810(MenuHolder *object, int msg, int arg);
int FUN_450880(Unk450930 *object, int arg);
void FUN_450930(Unk450930 *object);
int FUN_450950(Unk450930 *object, int msg, int arg);
int FUN_45a610(MenuObject *object, int arg);
void FUN_45a620(PoolObject *object);
int FUN_45a630(MenuObject *object, int msg, int arg);
int FUN_454220(MenuHolder *object, int arg);
void FUN_4542a0(MenuHolder *object);
int FUN_4542c0(MenuHolder *object, int msg, int arg);
int FUN_453480(PoolObject *object, int arg);
void FUN_4536f0(MenuHolder *object);
int FUN_453710(PoolObject *object, int msg, int arg);
int FUN_4522c0(Unk4522c0 *object, int arg);
void FUN_452530(MenuHolder *object);
struct Unk452550;
int FUN_452550(Unk452550 *object, int msg, int arg);
int FUN_454410(Unk454b20 *object, int arg);
void FUN_454450(PoolObject *object);
int FUN_454460(PoolObject *object, int msg, int arg);
int FUN_451700(PoolObject *object, int arg);
void FUN_451a80(MenuHolder *object);
int FUN_451aa0(Unk451aa0 *object, int msg, int arg);
int FUN_45c4b0(Unk45c4b0 *object, int arg);
void FUN_45c640(Unk45c670 *object);
struct Unk45c6a0;
int FUN_45c6a0(Unk45c6a0 *object, int msg, int arg);
int FUN_45d1a0(PoolObject *object, int arg);
void FUN_45d2e0(Unk45d2e0 *object);
int FUN_45d320(PoolObject *object, int msg, int arg);
int FUN_45b7a0(Unk45b7a0 *object, int arg);
void FUN_45b850(MenuHolder *object);
struct Unk45b870;
int FUN_45b870(Unk45b870 *object, int msg, int arg);
int FUN_450c10(Unk4516c0 *object, int arg);
void FUN_450e10(Unk4516c0 *object);
int FUN_4512b0(PoolObject *object, int msg, int arg);
int FUN_454ce0(MenuHolder *object, int arg);
void FUN_454d80(MenuHolder *object);
int FUN_454da0(MenuHolder *object, int msg, int arg);
int FUN_454fa0(Unk4516c0 *object, int arg);
void FUN_455090(Unk4516c0 *object);
int FUN_4550d0(Unk4516c0 *object, int msg, int arg);
int FUN_455340(MenuHolder *object, int arg);
void FUN_455410(MenuHolder *object);
int FUN_455430(MenuHolder *object, int msg, int arg);
int FUN_4555e0(MenuHolder *object, int arg);
void FUN_455690(MenuHolder *object);
int FUN_4556b0(MenuHolder *object, int msg, int arg);
int FUN_4557e0(PoolObject *object, int arg);
void FUN_4557f0(PoolObject *object);
int FUN_455800(PoolObject *object, int msg, int arg);
int FUN_455c70(Unk455fc0 *object, int arg);
void FUN_455d70(MenuHolder *object);
int FUN_455d90(Unk455fc0 *object, int msg, int arg);
int FUN_457470(MenuHolder *object, int arg);
void FUN_457500(MenuHolder *object);
int FUN_457520(MenuHolder *object, int msg, int arg);
int FUN_4576e0(Unk457770 *object, int arg);
void FUN_4577c0(MenuHolder *object);
int FUN_4577e0(Unk457770 *object, int msg, int arg);
int FUN_450400(Unk4516c0 *object, int arg);
void FUN_450510(Unk4516c0 *object);
int FUN_450550(Unk4516c0 *object, int msg, int arg);
int FUN_456010(Unk456070 *object, int arg);
void FUN_4560b0(PoolObject *object);
int FUN_4560c0(Unk456070 *object, int msg, int arg);
int FUN_452b30(MenuObject *object, int arg);
void FUN_452b50(PoolObject *object);
int FUN_452b60(MenuObject *object, int msg, int arg);
int FUN_45bba0(MenuObject *object, int arg);
void FUN_45bbb0(PoolObject *object);
int FUN_45bbc0(MenuObject *object, int msg, int arg);
int FUN_457920(Unk457e70 *object, int arg);
void FUN_457ea0(Unk457ea0 *object);
int FUN_457ec0(PoolObject *object, int msg, int arg);
int FUN_45a9c0(Unk45a9c0 *object, int arg);
void FUN_45ab70(Unk45ab70 *object);
int FUN_45abb0(PoolObject *object, int msg, int arg);
int FUN_452c00(Unk452c00 *object, int arg);
void FUN_452d50(MenuHolder *object);
int FUN_452d90(Unk452c00 *object, int msg, int arg);
int FUN_452940(MenuHolder *object, int arg);
void FUN_4529c0(MenuHolder *object);
int FUN_4529e0(MenuHolder *object, int msg, int arg);
int FUN_459790(Unk459790 *object, int arg);
void FUN_459a20(MenuHolder *object);
int FUN_459a40(Unk459790 *object, int msg, int arg);
int FUN_45a360(MenuHolder *object, int arg);
void FUN_45a3f0(MenuHolder *object);
int FUN_45a410(PoolObject *object, int msg, int arg);
int FUN_4567d0(Unk4516c0 *object, int arg);
void FUN_456910(Unk4516c0 *object);
struct Unk456950;
int FUN_456950(Unk456950 *object, int msg, int arg);
int FUN_456fc0(MenuHolder *object, int arg);
void FUN_4570f0(MenuHolder *object);
int FUN_457110(MenuHolder *object, int msg, int arg);
int FUN_457260(MenuHolder *object, int arg);
void FUN_4572e0(MenuHolder *object);
int FUN_457300(MenuHolder *object, int msg, int arg);
int FUN_452fc0(MenuObject *object, int arg);
void FUN_452fd0(PoolObject *object);
int FUN_452fe0(PoolObject *object, int msg, int arg);
int FUN_45b520(Unk45b520 *object, int arg);
void FUN_45b5b0(MenuHolder *object);
int FUN_45b5d0(Unk45b520 *object, int msg, int arg);
int FUN_45bd70(MenuHolder *object, int arg);
void FUN_45be00(MenuHolder *object);
int FUN_45bf40(MenuHolder *object, int msg, int arg);
int FUN_459200(Unk459200 *object, int arg);
void FUN_459300(MenuHolder *object);
struct Unk459320;
int FUN_459320(Unk459320 *object, int msg, int arg);
int FUN_45db80(Unk45db80 *object, int arg);
void FUN_45dde0(MenuHolder *object);
struct Unk45de00;
int FUN_45de00(Unk45de00 *object, int msg, int arg);

// One entry per language, built by FUN_452c00.
// One entry per track, built by FUN_456fc0.
// Per save slot: money text, then the FUN_45a9c0 number.
int FUN_45dc40(Unlock *unlock);
int FUN_457a40(Unk457e70 *object);
int FUN_457be0();
int FUN_457cf0(Unk457e70 *object, int mode);
void FUN_455af0(PoolObject *object);
void FUN_452070(int id, float x, float y);
void FUN_458d50(Unk457e70 *object, int mode, int card);
void FUN_45cba0(float pos, int index);
void FUN_45da70(Unk45d2e0 *object, int index, float pos);
void FUN_45c320(float x, float y);
void FUN_45c3d0(float x, float y);
void FUN_452830(float x, float y);
void FUN_45cf10(int row);
void FUN_45cd60(int table);
void FUN_456c80(Unk4516c0 *object);
// GLOBAL: STUNTGP_D3D 0x6250f8
char g_6250f8[0x40];

// GLOBAL: STUNTGP_D3D 0x627b54
GhostHeader g_627b54;

// GLOBAL: STUNTGP_D3D 0x627ff8
int g_627ff8;

// GLOBAL: STUNTGP_D3D 0x627ffc
Unlock g_627ffc[0x3f];

// GLOBAL: STUNTGP_D3D 0x627cd8
char g_627cd8[2][8][0x20];

// GLOBAL: STUNTGP_D3D 0x625138
MenuItem g_625138[25];

// GLOBAL: STUNTGP_D3D 0x624bb8
MenuItem g_624bb8[9];

// GLOBAL: STUNTGP_D3D 0x627ff4
int g_627ff4;

// GLOBAL: STUNTGP_D3D 0x4866a0
PoolClass g_4866a0 = {(void (*)(PoolObject *))FUN_450510, (int (*)(PoolObject *, int, int))FUN_450550};

// GLOBAL: STUNTGP_D3D 0x486738
PoolClass g_486738 = {(void (*)(PoolObject *))FUN_450930, (int (*)(PoolObject *, int, int))FUN_450950};

// GLOBAL: STUNTGP_D3D 0x4868d0
PoolClass g_4868d0 = {(void (*)(PoolObject *))FUN_450e10, FUN_4512b0};

// GLOBAL: STUNTGP_D3D 0x4869d0
PoolClass g_4869d0 = {(void (*)(PoolObject *))FUN_451a80, (int (*)(PoolObject *, int, int))FUN_451aa0};

// GLOBAL: STUNTGP_D3D 0x487920
PoolClass g_487920 = {(void (*)(PoolObject *))FUN_452530, (int (*)(PoolObject *, int, int))FUN_452550};

// GLOBAL: STUNTGP_D3D 0x4879a8
PoolClass g_4879a8 = {(void (*)(PoolObject *))FUN_4529c0, (int (*)(PoolObject *, int, int))FUN_4529e0};

// GLOBAL: STUNTGP_D3D 0x4879c0
PoolClass g_4879c0 = {FUN_452b50, (int (*)(PoolObject *, int, int))FUN_452b60};

// GLOBAL: STUNTGP_D3D 0x487a38
PoolClass g_487a38 = {(void (*)(PoolObject *))FUN_452d50, (int (*)(PoolObject *, int, int))FUN_452d90};

// GLOBAL: STUNTGP_D3D 0x487a50
PoolClass g_487a50 = {FUN_452fd0, FUN_452fe0};

// GLOBAL: STUNTGP_D3D 0x487c18
PoolClass g_487c18 = {(void (*)(PoolObject *))FUN_4531d0, (int (*)(PoolObject *, int, int))FUN_453210};

// GLOBAL: STUNTGP_D3D 0x487db8
TrackRecord g_487db8[12] = {
    {0x107, 3},  {0x10c, 7},  {0xe9, 4},   {0xf8, 5},   {0xf3, 6}, {0xee, 8},
    {0x102, 9},  {0xfd, 0xa}, {0x116, 0xb}, {0x111, 0xc}, {0x11b, 0xd}, {0, 0},
};

// GLOBAL: STUNTGP_D3D 0x624db8
TrackRecord g_624db8[12];

// GLOBAL: STUNTGP_D3D 0x4880f0
PoolClass g_4880f0 = {(void (*)(PoolObject *))FUN_4536f0, FUN_453710};

// GLOBAL: STUNTGP_D3D 0x488198
PoolClass g_488198 = {(void (*)(PoolObject *))FUN_4542a0, (int (*)(PoolObject *, int, int))FUN_4542c0};

// GLOBAL: STUNTGP_D3D 0x4881c0
PoolClass g_4881c0 = {FUN_454450, FUN_454460};

// GLOBAL: STUNTGP_D3D 0x488388
PoolClass g_488388 = {(void (*)(PoolObject *))FUN_454d80, (int (*)(PoolObject *, int, int))FUN_454da0};

// GLOBAL: STUNTGP_D3D 0x4884c0
PoolClass g_4884c0 = {(void (*)(PoolObject *))FUN_455090, (int (*)(PoolObject *, int, int))FUN_4550d0};

// GLOBAL: STUNTGP_D3D 0x488570
PoolClass g_488570 = {(void (*)(PoolObject *))FUN_455410, (int (*)(PoolObject *, int, int))FUN_455430};

// GLOBAL: STUNTGP_D3D 0x4885f8
PoolClass g_4885f8 = {(void (*)(PoolObject *))FUN_455690, (int (*)(PoolObject *, int, int))FUN_4556b0};

// GLOBAL: STUNTGP_D3D 0x488610
PoolClass g_488610 = {FUN_4557f0, FUN_455800};

// GLOBAL: STUNTGP_D3D 0x488748
PoolClass g_488748 = {(void (*)(PoolObject *))FUN_455d70, (int (*)(PoolObject *, int, int))FUN_455d90};

// GLOBAL: STUNTGP_D3D 0x488760
PoolClass g_488760 = {FUN_4560b0, (int (*)(PoolObject *, int, int))FUN_4560c0};

// GLOBAL: STUNTGP_D3D 0x4888f8
PoolClass g_4888f8 = {(void (*)(PoolObject *))FUN_456910, (int (*)(PoolObject *, int, int))FUN_456950};

// GLOBAL: STUNTGP_D3D 0x488990
PoolClass g_488990 = {(void (*)(PoolObject *))FUN_4570f0, (int (*)(PoolObject *, int, int))FUN_457110};

// GLOBAL: STUNTGP_D3D 0x488a38
PoolClass g_488a38 = {(void (*)(PoolObject *))FUN_4572e0, (int (*)(PoolObject *, int, int))FUN_457300};

// GLOBAL: STUNTGP_D3D 0x488b20
PoolClass g_488b20 = {(void (*)(PoolObject *))FUN_457500, (int (*)(PoolObject *, int, int))FUN_457520};

// GLOBAL: STUNTGP_D3D 0x488be8
PoolClass g_488be8 = {(void (*)(PoolObject *))FUN_4577c0, (int (*)(PoolObject *, int, int))FUN_4577e0};

// GLOBAL: STUNTGP_D3D 0x488c90
PoolClass g_488c90 = {(void (*)(PoolObject *))FUN_457ea0, FUN_457ec0};

// GLOBAL: STUNTGP_D3D 0x488d28
PoolClass g_488d28 = {(void (*)(PoolObject *))FUN_459300, (int (*)(PoolObject *, int, int))FUN_459320};

// GLOBAL: STUNTGP_D3D 0x488dd0
PoolClass g_488dd0 = {(void (*)(PoolObject *))FUN_459a20, (int (*)(PoolObject *, int, int))FUN_459a40};

// GLOBAL: STUNTGP_D3D 0x488e68
PoolClass g_488e68 = {(void (*)(PoolObject *))FUN_45a3f0, FUN_45a410};

// GLOBAL: STUNTGP_D3D 0x488e80
PoolClass g_488e80 = {FUN_45a620, (int (*)(PoolObject *, int, int))FUN_45a630};

// GLOBAL: STUNTGP_D3D 0x488f78
PoolClass g_488f78 = {(void (*)(PoolObject *))FUN_45a7f0, (int (*)(PoolObject *, int, int))FUN_45a810};

// GLOBAL: STUNTGP_D3D 0x4890b0
PoolClass g_4890b0 = {(void (*)(PoolObject *))FUN_45ab70, FUN_45abb0};

// GLOBAL: STUNTGP_D3D 0x489150
PoolClass g_489150 = {(void (*)(PoolObject *))FUN_45b5b0, (int (*)(PoolObject *, int, int))FUN_45b5d0};

// GLOBAL: STUNTGP_D3D 0x4891d8
PoolClass g_4891d8 = {(void (*)(PoolObject *))FUN_45b850, (int (*)(PoolObject *, int, int))FUN_45b870};

// GLOBAL: STUNTGP_D3D 0x4891f0
PoolClass g_4891f0 = {FUN_45bbb0, (int (*)(PoolObject *, int, int))FUN_45bbc0};

// GLOBAL: STUNTGP_D3D 0x489278
PoolClass g_489278 = {(void (*)(PoolObject *))FUN_45be00, (int (*)(PoolObject *, int, int))FUN_45bf40};

// GLOBAL: STUNTGP_D3D 0x489298
PoolClass g_489298 = {FUN_45c070, FUN_45c080};

// GLOBAL: STUNTGP_D3D 0x489510
PoolClass g_489510 = {(void (*)(PoolObject *))FUN_45c640, (int (*)(PoolObject *, int, int))FUN_45c6a0};

// GLOBAL: STUNTGP_D3D 0x489670
PoolClass g_489670 = {(void (*)(PoolObject *))FUN_45d2e0, FUN_45d320};

// GLOBAL: STUNTGP_D3D 0x489700
PoolClass g_489700 = {(void (*)(PoolObject *))FUN_45dde0, (int (*)(PoolObject *, int, int))FUN_45de00};

// GLOBAL: STUNTGP_D3D 0x4881f8
MenuItem g_4881f8[6] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x4e, 0x4f, 1, 0, 0},
    {2, 0xffc8c8ff, 0xffffffff, 0x54, 0x55, 1, 0, 0},
    {3, 0xffc8c8ff, 0xffffffff, 0x4b, 0x4c, 1, 0, 0},
    {4, 0xffc8c8ff, 0xffffffff, 0x5f, 0x60, 1, 0, 0},
    {5, 0xffc8c8ff, 0xffffffff, 0x2da, 0x2db, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x4882b8
MenuItem g_4882b8[5] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x4e, 0x4f, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x51, 0x52, 1, 0, 0},
    {2, 0xffc8c8ff, 0xffffffff, 0x54, 0x55, 1, 0, 0},
    {3, 0xffc8c8ff, 0xffffffff, 0x4b, 0x4c, 1, 0, 0},
    {0},
};

// Items are picked by FUN_454ce0.
// GLOBAL: STUNTGP_D3D 0x488358
MenuDef g_488358 = {0xb, 0.0f, 0, 320.0f, 240.0f, 1.0f, 2, 1.25f, 1, 0xc8, NULL, 0};

// GLOBAL: STUNTGP_D3D 0x488e88
MenuItem g_488e88[6] = {
    {0, 0xffc8c8ff, 0xffffffff, 0xb2, 0xb3, 1, 0x156, 0x163},
    {1, 0xffc8c8ff, 0xffffffff, 0xb4, 0xb5, 1, 0x15e, 0x16b},
    {2, 0xffc8c8ff, 0xffffffff, 0xb6, 0xb7, 1, 0x159, 0x166},
    {3, 0xffc8c8ff, 0xffffffff, 0xb8, 0xb9, 1, 0x162, 0x16f},
    {4, 0xffc8c8ff, 0xffffffff, 0xba, 0xbb, 1, 0x161, 0x16e},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488f48
MenuDef g_488f48 = {0xb, 1.0f, 0, 400.0f, 240.0f, 1.0f, 2, 1.25f, 4, 0xc8, g_488e88, 0};

// GLOBAL: STUNTGP_D3D 0x489168
MenuItem g_489168[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x17, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x4891a8
MenuDef g_4891a8 = {0xb, 1.0f, 0, 520.0f, 360.0f, 1.0f, 2, 1.25f, 4, 0x32, g_489168, 0};

// GLOBAL: STUNTGP_D3D 0x4889a8
MenuItem g_4889a8[3] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x2d1, 0x28b, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x2d0, 0x28a, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488a08
MenuDef g_488a08 = {0xb, 1.0f, 0, 320.0f, 240.0f, 1.0f, 2, 1.25f, 4, 0xc8, g_4889a8, 0};

// GLOBAL: STUNTGP_D3D 0x488a50
MenuItem g_488a50[5] = {
    {0, 0xffc8c8ff, 0xffffffff, 0xb2, 0, 1, 0x156, 0x163},
    {1, 0xffc8c8ff, 0xffffffff, 0xb6, 0, 1, 0x159, 0x166},
    {2, 0xffc8c8ff, 0xffffffff, 0xb8, 0, 1, 0x162, 0x16f},
    {3, 0xffc8c8ff, 0xffffffff, 0xba, 0, 1, 0x161, 0x16e},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488af0
MenuDef g_488af0 = {0xb, 1.0f, 0, 400.0f, 240.0f, 1.0f, 2, 1.25f, 4, 0xc8, g_488a50, 0};

// GLOBAL: STUNTGP_D3D 0x488b38
MenuItem g_488b38[4] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x8f, 0x90, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x91, 0x92, 1, 0, 0},
    {2, 0xffc8c8ff, 0xffffffff, 0x93, 0x94, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488bb8
MenuDef g_488bb8 = {0xb, 0.0f, 0, 320.0f, 240.0f, 1.0f, 2, 1.25f, 4, 0xc8, g_488b38, 0};

// GLOBAL: STUNTGP_D3D 0x488df8
MenuItem g_488df8[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x17, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488e38
MenuDef g_488e38 = {0xb, 0.0f, 0x3f000000, 320.0f, 420.0f, 1.0f, 2, 1.25f, 1, 0x32, g_488df8, 0};

// GLOBAL: STUNTGP_D3D 0x4890e0
MenuItem g_4890e0[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x17, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x489120
MenuDef g_489120 = {0xb, 0.0f, 0x3f000000, 320.0f, 420.0f, 1.0f, 2, 1.25f, 1, 0x32, g_4890e0, 0};

// GLOBAL: STUNTGP_D3D 0x489208
MenuItem g_489208[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x17, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x489248
MenuDef g_489248 = {0xb, 0.0f, 0x3f000000, 320.0f, 420.0f, 1.0f, 2, 1.25f, 1, 0x32, g_489208, 0};

// GLOBAL: STUNTGP_D3D 0x4883a0
MenuItem g_4883a0[4] = {
    {-1, 0xffffffff, 0xffffffff, 0x14, 0, 4, 0, 0},
    {0, 0xffc8c8ff, 0xffffffff, 0x15, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x16, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488420
MenuDef g_488420 = {0xb, -1.0f, 0, 320.0f, 340.0f, 1.0f, 2, 1.25f, 1, 0x78, g_4883a0, 0};

// GLOBAL: STUNTGP_D3D 0x488450
MenuItem g_488450[2] = {
    {3, 0xffc8c8ff, 0xffffffff, 0x5a, 0x5b, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488490
MenuDef g_488490 = {0xb, 0.0f, 0, 320.0f, 200.0f, 1.0f, 2, 1.25f, 1, 0xc8, g_488450, 0};

// GLOBAL: STUNTGP_D3D 0x4884e0
MenuItem g_4884e0[3] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x6d, 0x78, 2, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x61, 0x6c, 2, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488540
MenuDef g_488540 = {0xb, 0.0f, 0, 320.0f, 240.0f, 1.0f, 2, 1.25f, 1, 0xc8, g_4884e0, 0};

// GLOBAL: STUNTGP_D3D 0x488770
MenuItem g_488770[4] = {
    {-1, 0xffffffff, 0xffffffff, 0x14, 0, 4, 0, 0},
    {0, 0xffc8c8ff, 0xffffffff, 0x15, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x16, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x4887f0
MenuDef g_4887f0 = {0xb, 1.0f, 0, 510.0f, 340.0f, 1.0f, 2, 1.25f, 1, 0x64, g_488770, 0};

// GLOBAL: STUNTGP_D3D 0x488820
MenuItem g_488820[3] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x18, 0x291, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x19, 0x291, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488880
MenuItem g_488880[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x17, 0x2d9, 1, 0, 0},
    {0},
};

// The last field doubles as the first of three score thresholds, see FUN_4567d0.
// GLOBAL: STUNTGP_D3D 0x4888c0
MenuDef g_4888c0 = {0xb, 0.0f, 0, 320.0f, 340.0f, 1.0f, 2, 1.25f, 1, 0x64, g_488820, 3};

// GLOBAL: STUNTGP_D3D 0x4888f0
int g_4888f0[2] = {5, 9};

// GLOBAL: STUNTGP_D3D 0x488cb8
MenuItem g_488cb8[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x17, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488cf8
MenuDef g_488cf8 = {0xb, 0.0f, 0x3f000000, 320.0f, 420.0f, 1.0f, 2, 1.25f, 1, 0x32, g_488cb8, 0};

// GLOBAL: STUNTGP_D3D 0x4879c8
MenuItem g_4879c8 = {0, 0xffc8c8ff, 0xffffffff, 0, 0, 1, 0, 0};

// GLOBAL: STUNTGP_D3D 0x4879e8
MenuItem g_4879e8 = {0};

// GLOBAL: STUNTGP_D3D 0x487a08
MenuDef g_487a08 = {0xb, 0.0f, 0, 480.0f, 240.0f, 1.0f, 2, 1.25f, 4, 0x8c, g_624bb8, 0};

// GLOBAL: STUNTGP_D3D 0x488920
MenuItem g_488920 = {0, 0xffc8c8ff, 0xffffffff, 0xb2, 0xb3, 1, 0, 0};

// GLOBAL: STUNTGP_D3D 0x488940
MenuItem g_488940 = {0};

// GLOBAL: STUNTGP_D3D 0x488960
MenuDef g_488960 = {0xb, 1.0f, 0, 320.0f, 240.0f, 1.0f, 2, 1.25f, 1, 0xc8, g_625138, 0};

// GLOBAL: STUNTGP_D3D 0x488f90
MenuItem g_488f90[3] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x2d, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x2e, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488ff0
MenuDef g_488ff0 = {0xb, 0.0f, 0, 520.0f, 382.0f, 1.0f, 2, 1.25f, 3, 0x50, g_488f90, 0};

// GLOBAL: STUNTGP_D3D 0x489020
MenuItem g_489020[3] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x15, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x16, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x489080
MenuDef g_489080 = {0xb, 0.0f, 0, 520.0f, 382.0f, 1.0f, 2, 1.25f, 1, 0x50, g_489020, 0};

// GLOBAL: STUNTGP_D3D 0x4892a0
MenuItem g_4892a0[5] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x18, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x1ff, 0, 2, 0, 0},
    {2, 0xffc8c8ff, 0xffffffff, 0x202, 0, 2, 0, 0},
    {3, 0xffc8c8ff, 0xffffffff, 0x205, 0, 2, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x489340
MenuItem g_489340[4] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x18, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x20, 0, 1, 0, 0},
    {2, 0xffc8c8ff, 0xffffffff, 0x21, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x4893c0
MenuItem g_4893c0[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x18, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x489400
MenuItem g_489400[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x18, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x489440
MenuItem g_489440[3] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x18, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x1ff, 0, 2, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x4894a0
MenuItem g_4894a0[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x18, 0, 1, 0, 0},
    {0},
};

// Items are picked by FUN_45c4b0.
// GLOBAL: STUNTGP_D3D 0x4894e0
MenuDef g_4894e0 = {0xb, 0.0f, 0x3f800000, 220.0f, 400.0f, 0.8f, 2, 1.1f, 1, 0xbe, NULL, 0};

// GLOBAL: STUNTGP_D3D 0x489690
MenuItem g_489690[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x17, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x4896d0
MenuDef g_4896d0 = {0xb, 0.0f, 0x3f000000, 320.0f, 420.0f, 1.0f, 2, 1.25f, 1, 0x50, g_489690, 0};

// GLOBAL: STUNTGP_D3D 0x4869e8
MenuItem g_4869e8[13] = {
    {0, 0xffc8c8ff, 0xffffffff, 0xdd, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0xde, 0, 1, 0, 0},
    {2, 0xffc8c8ff, 0xffffffff, 0xd7, 0, 1, 0, 0},
    {3, 0xffc8c8ff, 0xffffffff, 0xd5, 0, 1, 0, 0},
    {4, 0xffc8c8ff, 0xffffffff, 0xd2, 0, 1, 0, 0},
    {5, 0xffc8c8ff, 0xffffffff, 0xd6, 0, 1, 0, 0},
    {6, 0xffc8c8ff, 0xffffffff, 0xdc, 0, 1, 0, 0},
    {7, 0xffc8c8ff, 0xffffffff, 0xda, 0, 1, 0, 0},
    {8, 0xffc8c8ff, 0xffffffff, 0xd8, 0, 1, 0, 0},
    {9, 0xffc8c8ff, 0xffffffff, 0xdb, 0, 1, 0, 0},
    {10, 0xffc8c8ff, 0xffffffff, 0xd3, 0, 1, 0, 0},
    {11, 0xffc8c8ff, 0xffffffff, 0xd9, 0, 1, 0, 0},
    {0},
};


// GLOBAL: STUNTGP_D3D 0x4878f0
MenuDef g_4878f0 = {0xb, -1.0f, 0, 85.0f, 254.0f, 0.8f, 2, 1.1f, 1, 0x70, g_4869e8, 0};

// GLOBAL: STUNTGP_D3D 0x488c00
MenuItem g_488c00[3] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x15, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x16, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488c60
MenuDef g_488c60 = {0xb, 0.0f, 0, 520.0f, 382.0f, 1.0f, 2, 1.25f, 1, 0x50, g_488c00, 0};

// GLOBAL: STUNTGP_D3D 0x489290
float g_489290 = 201.0f;

// GLOBAL: STUNTGP_D3D 0x489294
float g_489294 = 172.0f;

// GLOBAL: STUNTGP_D3D 0x488d60
MenuItem g_488d60[2] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x17, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x488da0
MenuDef g_488da0 = {0xb, 0.0f, 0x3f000000, 320.0f, 420.0f, 1.0f, 2, 1.25f, 1, 0x32, g_488d60, 0};

void FUN_424a90(int mode);
void FUN_450760(int textId);
void FUN_4507e0(Unk4516c0 *object);

// Display mode test: unk1c is 0 before the switch, 1 while counting down unk20, 2 asking to keep it.
// FUNCTION: STUNTGP_D3D 0x450550
int FUN_450550(Unk4516c0 *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x69, 0.3f, -0.5f);
    case 2:
    case 0x14:
        object->unk14->message(object->unk14, msg, 0);
        object->unk18->message(object->unk18, msg, 0);
        return 0;
    case 0x10:
        switch (object->unk1c)
        {
        case 2:
            child = object->unk18;
            child->message(child, msg, 0);
            switch (child->message(child, 0x1a, 0))
            {
            case 1:
                g_menuState.unk0094 = 1;
                break;
            case 0:
                g_menuState.unk0094 = 2;
                break;
            default:
                return 0;
            }
            FUN_424a90(g_menuState.unk0094);
            FUN_43eef0();
            return 0;
        case 1:
            object->unk14->message(object->unk14, msg, 0);
            object->unk1c = 2;
            return 0;
        case 0:
            object->unk14->message(object->unk14, msg, 0);
            FUN_424a90(2);
            object->unk1c = 1;
            return 0;
        }
        break;
    case 0xb:
    case 0xc:
        switch (object->unk1c)
        {
        case 2:
            object->unk18->message(object->unk18, msg, 0);
            return 0;
        }
        break;
    case 0x11:
        FUN_440880(2);
        FUN_424a90(g_menuState.unk0094);
        FUN_43eef0();
        return 0;
    case 1:
        switch (object->unk1c)
        {
        case 1:
            if (--object->unk20 <= 0)
            {
                FUN_424a90(g_menuState.unk0094);
                object->unk1c = 2;
                return 0;
            }
            break;
        }
        break;
    case 3:
        FUN_4392b0(0x96, 0);
        switch (object->unk1c)
        {
        case 2:
            object->unk18->message(object->unk18, msg, 0);
            FUN_450760(0x99);
            return 0;
        case 1:
            object->unk14->message(object->unk14, msg, 0);
            FUN_450760(0x98);
            FUN_4507e0(object);
            return 0;
        case 0:
            object->unk14->message(object->unk14, msg, 0);
            FUN_450760(0x97);
            break;
        }
        break;
    }
    return 0;
}

void FUN_450ac0(MenuObject *object);
void FUN_450b00(MenuObject *object);

// FUNCTION: STUNTGP_D3D 0x450950
int FUN_450950(Unk450930 *object, int msg, int arg)
{
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x5d, -0.1f, 0.093f);
    case 2:
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        object->child->message(object->child, msg, 0);
        FUN_43eef0();
        return 0;
    case 4:
        object->unk20 -= 0.5f;
        FUN_450ac0((MenuObject *)object);
        return 0;
    case 5:
        object->unk20 += 0.5f;
        FUN_450ac0((MenuObject *)object);
        return 0;
    case 6:
        object->unk1c -= 0.5f;
        FUN_450ac0((MenuObject *)object);
        return 0;
    case 7:
        object->unk1c += 0.5f;
        FUN_450ac0((MenuObject *)object);
        return 0;
    case 0x11:
        g_menuState.offsetX = 0;
        g_menuState.offsetY = 0;
        FUN_440890(msg);
        FUN_43eef0();
        return 0;
    case 1:
        g_menuState.offsetX = (int)object->unk1c;
        g_menuState.offsetY = (int)object->unk20;
        return 0;
    case 3:
        object->child->message(object->child, msg, 0);
        FUN_450b00((MenuObject *)object);
        break;
    }
    return 0;
}

void FUN_450db0(Unk4516c0 *object);
void FUN_450dd0(Unk4516c0 *object);
void FUN_450e50(int a, int b, float x, float y);
void FUN_451680(Unk4516c0 *object);
void FUN_4516c0(Unk4516c0 *object);
void FUN_4516f0(Unk4516c0 *object);

// Championship hub: the round menu (unk14) and its confirm box (unk18) over the results table.
// FUNCTION: STUNTGP_D3D 0x4512b0
int FUN_4512b0(PoolObject *base, int msg, int arg)
{
    Unk4516c0 *object = (Unk4516c0 *)base;
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x5f, 0.3f, -0.5f);
        object->unk14->message(object->unk14, msg, 0);
        return 0;
    case 0x10:
        if (object->unk28)
        {
            child = object->unk18;
            child->message(child, msg, 0);
            if (child->message(child, 0x1a, 0) == 1)
            {
                FUN_4516c0(object);
                return 0;
            }
            g_menuState.unk1a53c = 2;
            if (g_menuState.unk19d7c.unk008 > 1)
            {
                FUN_43eef0();
                return 0;
            }
            FUN_43eef0();
            return 0;
        }
        else
        {
            child = object->unk14;
            switch (child->message(child, 0x1a, 0))
            {
            case 0:
                child->message(child, msg, 0);
                g_menuState.unk1a53c = 4;
                FUN_43eef0();
                return 0;
            case 1:
                child->message(child, msg, 0);
                FUN_43dfa0(0x16, 7);
                object->unk20 = 1;
                return 0;
            case 2:
                if (g_menuState.unk4398 > 0)
                {
                    object->unk1c = 1;
                    child->message(child, msg, 0);
                    FUN_43dfa0(0x14, 10);
                    return 0;
                }
                FUN_440880(9);
                return 0;
            case 3:
                child->message(child, msg, 0);
                g_menuState.unk46bc = 0;
                g_menuState.unk46c0 = 0;
                g_menuState.unk46c8 = 3;
                g_menuState.unk46c4 = 0;
                object->unk24 = 1;
                FUN_43dfa0(0, 0x1b);
                return 0;
            case 4:
                FUN_451680(object);
                object->unk14->message(object->unk14, msg, 0);
                return 0;
            }
        }
        break;
    case 0x11:
        if (object->unk28)
        {
            FUN_4516c0(object);
            FUN_440890(msg);
            return 0;
        }
        FUN_440890(msg);
        FUN_451680(object);
        return 0;
    case 0xb:
    case 0xc:
        if (object->unk28)
        {
            child = object->unk18;
            child->message(child, msg, 0);
            return 0;
        }
        child = object->unk14;
        child->message(child, msg, 0);
        return 0;
    case 2:
        object->unk14->message(object->unk14, msg, 0);
        child = object->unk18;
        child->message(child, msg, 0);
        return 0;
    case 1:
        FUN_450dd0(object);
        if (object->unk24)
        {
            object->unk24 = 0;
            if (g_menuState.unk46e0)
            {
                g_menuState.unk1a540 = 0;
                object->unk14->message(object->unk14, 0x1c, 0);
            }
        }
        if (object->unk1c)
        {
            object->unk1c = 0;
            if (g_menuState.unk4394)
            {
                break;
            }
            int car = g_menuState.unk43f4[g_menuState.unk4238];
            int refund = FUN_437de0(g_menuState.unk19d7c.sponsor, g_menuState.unk19d7c.car,
                                    &g_menuState.unk19d7c.carSetup);
            int price = FUN_437de0(g_menuState.unk19d7c.sponsor, car, &g_menuState.cars[car]);
            g_menuState.unk19d7c.money += refund;
            g_menuState.unk19d7c.car = car;
            object->unk20 = 1;
            g_menuState.unk19d7c.carSetup = g_menuState.cars[car];
            g_menuState.unk19d7c.money -= price;
        }
        FUN_450db0(object);
        return 0;
    case 3:
        FUN_4392b0(0x9b, 0);
        object->unk14->message(object->unk14, msg, 0);
        object->unk18->message(object->unk18, msg, 0);
        FUN_4516f0(object);
        FUN_450e50(g_menuState.unk19d7c.unk008, g_menuState.numberOfRounds, 192.0f, 240.0f);
        break;
    }
    return 0;
}

// STUB: STUNTGP_D3D 0x451700
int FUN_451700(PoolObject *object, int arg)
{
    return 0;
}

struct Unk451a50;
struct Unk452000;
int FUN_451e80(Unk451a50 *object, float x, float y);
void FUN_451ed0(Unk451aa0 *object);
void FUN_452000(Unk452000 *object, float x, float y);
void FUN_452070(int id, float x, float y);
void FUN_452130(Unk451aa0 *object, float x, float y, float phase);
void FUN_4521b0(Unk451aa0 *object, int index);

// Car part page: a grid of part groups, with the stats of the highlighted part.
// FUNCTION: STUNTGP_D3D 0x451aa0
int FUN_451aa0(Unk451aa0 *object, int msg, int arg)
{
    PoolObject *child;
    int count;
    int sel;
    int item;
    switch (msg)
    {
    case 0x13:
    {
        int music = 5;
        if (g_menuState.unk4230 == 5)
        {
            music = 7;
        }
        FUN_4400a0(music);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x60, -0.3f, -0.5f);
    }
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0xd:
        count = object->groups[object->unk1c * 12];
        if (object->unk18 >= count)
        {
            object->unk18 = count - 1;
        }
        if (object->unk18 > 0)
        {
            object->unk18--;
            FUN_440890(msg);
            FUN_440880(0x14);
            return 0;
        }
        break;
    case 0xe:
        if (object->unk18 < object->groups[object->unk1c * 12] - 1)
        {
            object->unk18++;
            FUN_440890(msg);
            FUN_440880(0x14);
            return 0;
        }
        break;
    case 0xb:
    case 0xc:
        child = object->child;
        if (child->message(child, msg, 0))
        {
            FUN_440880(0x14);
        }
        object->unk1c = child->message(child, 0x1a, 0);
        return 0;
    case 0x11:
        g_menuState.unk4394 = 1;
        FUN_440890(msg);
        FUN_43eef0();
        return 0;
    case 0x10:
        count = object->groups[object->unk1c * 12];
        sel = object->unk18;
        if (sel >= count)
        {
            sel = count - 1;
        }
        g_menuState.unk43f4[g_menuState.unk4238] = object->groups[object->unk1c * 12 + sel + 2];
        FUN_440890(msg);
        FUN_43eef0();
        return 0;
    case 1:
        count = object->groups[object->unk1c * 12];
        sel = object->unk18;
        if (sel >= count)
        {
            sel = count - 1;
        }
        item = object->groups[object->unk1c * 12 + sel + 2];
        object->unk44[0] = object->unk18c[item][0] * 0.01f;
        object->unk44[1] = object->unk18c[item][1] * 0.01f;
        object->unk44[2] = object->unk18c[item][2] * 0.01f;
        return 0;
    case 2:
    {
        object->child->message(object->child, msg, 0);
        float phase = object->unk34 + 0.03f;
        object->unk34 = phase - (int)phase;
        int group = object->unk1c;
        sel = object->unk18;
        count = object->groups[group * 12];
        if (sel >= count)
        {
            sel = count - 1;
        }
        float target = sel;
        object->unk2c = target;
        float row = group;
        object->unk30 = row;
        object->unk24 = FUN_43d810(object->unk24, target, 0.001f);
        object->unk28 = FUN_43d810(object->unk28, row, 0.001f);
        FUN_43df60(count, 1.0f, target, object->unk110, 1.0f, row);
        for (int i = 0; i < 3; i++)
        {
            object->unk38[i] = FUN_43d810(object->unk38[i], object->unk44[i], 0.001f);
        }
        return 0;
    }
    case 3:
        item = FUN_451e80((Unk451a50 *)object, object->unk24, object->unk28);
        if (item > 0)
        {
            FUN_452070(item, object->unk24, object->unk28);
        }
        FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
        count = object->groups[object->unk1c * 12];
        sel = object->unk18;
        if (sel >= count)
        {
            sel = count - 1;
        }
        item = object->groups[object->unk1c * 12 + sel + 2];
        FUN_452130(object, 69.0f, 82.0f, object->unk28);
        FUN_4521b0(object, item);
        FUN_4392b0(0x184, 0);
        object->child->message(object->child, msg, 0);
        if (g_menuState.unk423c > 1)
        {
            FUN_452000((Unk452000 *)object, g_486998.x, g_486998.y);
        }
        FUN_451ed0(object);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x4522c0
int FUN_4522c0(Unk4522c0 *object, int arg)
{
    int tracks[64];
    int cars[64];
    int count;
    int i;
    int n;
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x487928
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4878f0))
    {
        Pool_Free(list);
        object->child = NULL;
    }
    else
    {
        object->child = &list->base;
    }
    object->child->message(object->child, 0x18, 0);
    object->unk18 = 0;
    object->unk1c = 0;
    object->unk20 = 0;
    object->unk24 = 0;
    object->unk28 = 0;
    for (n = 0; g_486b88[n].id; n++)
    {
    }
    for (n = 0; g_4869e8[n].text; n++)
    {
    }
    for (i = 0; i < 12; i++)
    {
        for (n = 0; n < 32; n++)
        {
            g_486b88[i].unk08[n] = 0;
            g_486b88[i].unk88[n] = 0;
        }
    }
    count = 0;
    for (i = 1; i < 0x15; i++)
    {
        if (g_menuState.unlocked[i])
        {
            cars[count++] = i;
        }
    }
    FUN_437710(cars, count);
    for (i = 0; i < count; i++)
    {
        int car = cars[i];
        g_486b88[0].unk08[i] = FUN_437af0(g_486b88[0].id) + car - 1;
        g_486b88[0].unk88[i] = g_486b88[0].text + car - 1;
    }
    for (; i < FUN_437a90(g_486b88[0].id); i++)
    {
        g_486b88[0].unk08[i] = 0x77;
        g_486b88[0].unk88[i] = 0;
    }
    count = 0;
    for (i = 1; i < 0x19; i++)
    {
        if (g_menuState.unlocked[0x18 + i])
        {
            tracks[count++] = i;
        }
    }
    FUN_4375a0(tracks, count);
    for (i = 0; i < count; i++)
    {
        int track = tracks[i];
        g_486b88[1].unk08[i] = FUN_437af0(g_486b88[1].id) + track - 1;
        g_486b88[1].unk88[i] = g_486b88[1].text + track - 1;
    }
    for (; i < FUN_437a90(g_486b88[1].id); i++)
    {
        g_486b88[1].unk08[i] = 0x77;
        g_486b88[1].unk88[i] = 0;
    }
    for (i = 2; i < 12; i++)
    {
        int entries = FUN_437a90(g_486b88[i].id);
        int first = FUN_437af0(g_486b88[i].id);
        for (n = 0; n < entries; n++)
        {
            g_486b88[i].unk08[n] = first + n;
            g_486b88[i].unk88[n] = g_486b88[i].text + n;
        }
    }
    return 1;
}

// PageCatalog: unk18 is the column in the highlighted row, unk1c/unk20 the scrolled position.
struct Unk452550
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18
    float unk1c;       // 0x1c
    float unk20;       // 0x20
    float unk24;       // 0x24
    float unk28;       // 0x28
};

void FUN_4527f0(int entry, int category);

// FUNCTION: STUNTGP_D3D 0x452550
int FUN_452550(Unk452550 *object, int msg, int arg)
{
    PoolObject *child;
    int count;
    int sel;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(3);
        FUN_43dd10(0x534527);
        FUN_43dd40(0x69, -0.3f, 0.5f);
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0xb:
    case 0xc:
        if (object->child->message(object->child, msg, 0))
        {
            FUN_440880(0x14);
            return 0;
        }
        break;
    case 0xd:
        count = FUN_4527d0(object->child->message(object->child, 0x1a, 0));
        if (object->unk18 >= count)
        {
            object->unk18 = count - 1;
        }
        if (object->unk18)
        {
            object->unk18--;
            FUN_440880(0x14);
            FUN_440890(msg);
            return 0;
        }
        break;
    case 0xe:
        sel = object->unk18;
        if (sel < FUN_4527d0(object->child->message(object->child, 0x1a, 0)) - 1)
        {
            object->unk18 = sel + 1;
            FUN_440880(0x14);
            FUN_440890(msg);
            return 0;
        }
        break;
    case 0x10:
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 2:
    {
        child = object->child;
        child->message(child, msg, 0);
        int row = child->message(child, 0x1a, 0);
        count = FUN_4527d0(row);
        sel = object->unk18;
        float target = sel >= count ? count - 1 : sel;
        object->unk24 = target;
        float y = row;
        object->unk28 = y;
        object->unk1c = FUN_43d810(object->unk1c, target, 0.001f);
        object->unk20 = FUN_43d810(object->unk20, y, 0.001f);
        FUN_43df60(count, 1.0f, sel >= count ? count - 1 : sel, 12.0f, 1.0f, y);
        return 0;
    }
    case 3:
        FUN_452830(object->unk1c, object->unk20);
        FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
        FUN_4392b0(0xd1, 0);
        child = object->child;
        child->message(child, msg, 0);
        count = child->message(child, 0x1a, 0);
        sel = object->unk18;
        count = FUN_4527d0(count) - 1;
        if (sel > count)
        {
            sel = count;
        }
        FUN_4527f0(sel, child->message(child, 0x1a, 0));
        break;
    }
    return 0;
}
void FUN_452ac0(MenuHolder *object);

// FUNCTION: STUNTGP_D3D 0x4529e0
int FUN_4529e0(MenuHolder *object, int msg, int arg)
{
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x5f, 0.3f, -0.5f);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        object->child->message(object->child, msg, 0);
        FUN_43eef0();
        return 0;
    case 0x11:
        FUN_440890(msg);
        FUN_43eef0();
        return 0;
    case 3:
        FUN_4392b0(0x2b4, 0);
        object->child->message(object->child, msg, 0);
        FUN_452ac0(object);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x452b50
void FUN_452b50(PoolObject *object)
{
}

void FUN_439e10();
void FUN_439e50();
void FUN_439e90();
void FUN_45f8e0(int target, int step);

// Fades the music out, then runs the race and copies its results back.
// FUNCTION: STUNTGP_D3D 0x452b60
int FUN_452b60(MenuObject *object, int msg, int arg)
{
    switch (msg)
    {
    case 1:
        switch (object->unk14)
        {
        case 1:
            if (object->unk18++ >= 0x78)
            {
                FUN_439e50();
                FUN_439e10();
                object->unk14 = 2;
            }
            break;
        case 2:
            FUN_439e90();
            FUN_436eb0();
            FUN_4411c0();
            object->unk14 = 3;
            FUN_43de40();
            FUN_43eef0();
            return 0;
        }
        break;
    case 0x13:
        FUN_4400a0(0);
        FUN_43dd10(0);
        FUN_43dd40(0, 0.0f, 0.0f);
        if (object->unk14 == 0)
        {
            FUN_45f8e0(0, -4);
            object->unk14 = 1;
            return 0;
        }
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x452c00
int FUN_452c00(Unk452c00 *object, int arg)
{
    int i = 0;
    object->unk28 = g_menuState.unk0090;
    object->unk18 = i;
    object->unk20 = i;
    object->unk24 = i;
    for (; i < g_menuState.languageCount; i++)
    {
        g_624bb8[i] = g_4879c8;
        g_624bb8[i].id = i;
        g_624bb8[i].text = i + 0x2dd;
    }
    g_624bb8[i] = g_4879e8;
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x487a40
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_487a08))
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
    object->unk1c = g_menuState.unk4254;
    if (!g_menuState.unk0090)
    {
        g_menuState.unk0090 = FUN_445ad0();
        object->unk1c = 0;
    }
    if (g_menuState.unk0090)
    {
        int index = FUN_440c40(g_menuState.unk0090);
        if (index < 0)
        {
            g_menuState.unk0090 = 0;
            object->unk18 = 0;
        }
        else
        {
            object->unk18 = index;
        }
    }
    if (g_menuState.languageCount < 2)
    {
        object->unk1c = 1;
    }
    int selected = object->unk18;
    child->message(child, 0x1c, selected);
    object->unk20 = object->unk24 = selected;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x452d90
int FUN_452d90(Unk452c00 *object, int msg, int arg)
{
    PoolObject *child;
    int i;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x5d, 0.3f, -0.5f);
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x11:
        if (object->unk28 <= 0)
        {
            FUN_440880(9);
            return 0;
        }
        FUN_452d70(object->unk28);
        FUN_440890(msg);
        FUN_43eef0();
        return 0;
    case 0x10:
        child = object->child;
        child->message(child, msg, 0);
        object->unk18 = child->message(child, 0x1a, 0);
        FUN_452d70(g_menuState.languages[object->unk18].id);
        FUN_43eef0();
        return 0;
    case 2:
    {
        child = object->child;
        child->message(child, msg, 0);
        float target = child->message(child, 0x1a, 0);
        object->unk24 = target;
        object->unk20 = FUN_43d810(object->unk20, target, 0.001f);
        return 0;
    }
    case 1:
        if (object->unk1c)
        {
            FUN_452d70(g_menuState.languages[object->unk18].id);
            FUN_43eef0();
            return 0;
        }
        break;
    case 3:
        object->child->message(object->child, msg, 0);
        for (i = 0; i < g_menuState.languageCount; i++)
        {
            float angle = (i - object->unk20) * 6.2831855f / g_menuState.languageCount;
            int id = g_menuState.languages[i].id - 1;
            float x = (float)cos(angle) * 200.0f + 68.0f;
            float y = (float)sin(angle) * 130.0f + 240.0f;
            FUN_438710(x, y, 0xd, id + 0x15, 1.0f, 0x203);
            FUN_438710(x, y, 0xc, id + 0xd, 1.0f, 0x103);
        }
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x452fd0
void FUN_452fd0(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x452fe0
int FUN_452fe0(PoolObject *object, int msg, int arg)
{
    return 0;
}

struct Unk453460;
void FUN_4531a0(Unk4516c0 *object);
void FUN_453430(Unk453460 *object);
void FUN_453460(Unk453460 *object);

// Main menu; unk1c is set while the quit confirmation is open.
// FUNCTION: STUNTGP_D3D 0x453210
int FUN_453210(Unk4516c0 *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
    case 0x14:
        object->unk14->message(object->unk14, msg, 0);
        return 0;
    case 0x10:
        if (object->unk1c)
        {
            child = object->unk18;
            child->message(child, msg, 0);
            if (child->message(child, 0x1a, 0) == 1)
            {
                FUN_453460((Unk453460 *)object);
                return 0;
            }
            exit(0);
        }
        child = object->unk14;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 0:
            FUN_43dfa0(3, 3);
            return 0;
        case 1:
            FUN_43dfa0(4, 6);
            return 0;
        case 2:
            FUN_43dfa0(5, 8);
            return 0;
        case 3:
            FUN_43dfa0(6, 0x15);
            return 0;
        case 4:
            FUN_43dfa0(7, 0xf);
            return 0;
        case 5:
            FUN_453430((Unk453460 *)object);
            return 0;
        }
        break;
    case 0xb:
    case 0xc:
        if (!object->unk1c)
        {
            object->unk14->message(object->unk14, msg, 0);
            return 0;
        }
        object->unk18->message(object->unk18, msg, 0);
        break;
    case 0x11:
        if (object->unk1c)
        {
            FUN_453460((Unk453460 *)object);
            FUN_440890(msg);
            return 0;
        }
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 1:
        FUN_4531a0(object);
        return 0;
    case 3:
        FUN_4392b0(0x3e, 0);
    case 2:
        object->unk14->message(object->unk14, msg, 0);
        object->unk18->message(object->unk18, msg, 0);
        break;
    }
    return 0;
}

extern MenuItem g_487c38[12];
extern MenuDef g_4880b8;
void FUN_453680(Unk453710 *object);

// Part shop init: lists the part groups the car can still upgrade, then their part ranges.
// FUNCTION: STUNTGP_D3D 0x453480
int FUN_453480(PoolObject *base, int arg)
{
    Unk453710 *object = (Unk453710 *)base;
    object->unk1c = 0;
    object->unk20 = 0;
    object->unk24 = 0;
    object->unk28 = 0;
    object->unk18 = 0;
    object->unk50 = 0;
    object->unk54 = 0xe0;
    int i;
    for (i = 0; i < 3; i++)
    {
        object->unk2c[i] = 0;
        object->unk38[i] = 0;
    }
    for (i = 0; g_487db8[i].track; i++)
    {
        int track = g_487db8[i].track;
        FUN_437a90(track);
        g_487c38[i].id = -1;
        if (g_menuState.unk19d7c.carSetup.parts[track][1] &&
            g_menuState.unk19d7c.carSetup.parts[track][2] < g_menuState.unk19d7c.carSetup.parts[track][3])
        {
            g_487c38[i].id = object->unk18;
            g_624db8[object->unk18] = g_487db8[i];
            object->unk18++;
        }
    }
    for (i = 0; i < object->unk18; i++)
    {
        int track = g_624db8[i].track;
        g_624db8[i].unk34 = g_menuState.unk19d7c.carSetup.parts[track][1];
        g_624db8[i].unk38 = g_menuState.unk19d7c.carSetup.parts[track][2];
        g_624db8[i].unk3c = g_menuState.unk19d7c.carSetup.parts[track][3];
        g_624db8[i].unk30 = g_624db8[i].unk34 - 1;
        for (int j = 0; j < 5; j++)
        {
            g_624db8[i].unk08[j] = 0;
            g_624db8[i].unk1c[j] = 0;
        }
    }
    for (i = 0; i < object->unk18; i++)
    {
        int track = g_624db8[i].track;
        int first = FUN_437af0(track);
        int last = g_menuState.unk19d7c.carSetup.parts[track][3] - 1;
        for (int k = g_menuState.unk19d7c.carSetup.parts[track][2] - 1; k <= last; k++)
        {
            g_624db8[i].unk08[k] = first + k;
            g_624db8[i].unk1c[k] = g_624db8[i].unk00 + k;
        }
    }
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x4880f8
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4880b8))
    {
        Pool_Free(list);
        object->child = NULL;
    }
    else
    {
        object->child = &list->base;
    }
    object->child->message(object->child, 0x18, 0);
    FUN_453680(object);
    return 1;
}

void FUN_453a90(Unk453710 *object);
void FUN_453b50(Unk453710 *object, float x, float y);
void FUN_453dd0(Unk453710 *object);
int FUN_454150(Unk453710 *object);

// Part shop: pick a part group, step through its parts and buy one.
// FUNCTION: STUNTGP_D3D 0x453710
int FUN_453710(PoolObject *base, int msg, int arg)
{
    Unk453710 *object = (Unk453710 *)base;
    PoolObject *child;
    int sel;
    int pos;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(2);
        FUN_43dd10(0x534527);
        FUN_43dd40(0x69, -0.3f, 0.5f);
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0xb:
        child = object->child;
        if (child->message(child, 0x1a, 0) <= 0)
        {
            break;
        }
        goto group;
    case 0xc:
        child = object->child;
        if (child->message(child, 0x1a, 0) < object->unk18 - 1)
        {
        group:
            FUN_440880(0x14);
            child->message(child, msg, 0);
            object->unk1c = 0;
            FUN_453680(object);
            object->unk50 = 0;
            return 0;
        }
        break;
    case 0xd:
        sel = object->child->message(object->child, 0x1a, 0);
        pos = object->unk1c;
        if (g_624db8[sel].unk34 + pos - 1 >= g_624db8[sel].unk38)
        {
            FUN_440880(0x14);
            FUN_440890(msg);
            pos--;
            goto part;
        }
        break;
    case 0xe:
        sel = object->child->message(object->child, 0x1a, 0);
        pos = object->unk1c;
        if (g_624db8[sel].unk34 + pos + 1 <= g_624db8[sel].unk3c)
        {
            FUN_440880(0x14);
            FUN_440890(msg);
            pos++;
        part:
            object->unk1c = pos;
            FUN_453680(object);
            object->unk50 = 0;
            return 0;
        }
        break;
    case 0x10:
        if (object->unk1c == 0)
        {
            FUN_440880(9);
            return 0;
        }
        if (FUN_454150(object))
        {
            object->unk1c = 0;
            FUN_453680(object);
            FUN_440890(msg);
            object->unk50 = 0;
            return 0;
        }
        FUN_440880(9);
        return 0;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 2:
    {
        object->unk50++;
        child = object->child;
        child->message(child, msg, 0);
        sel = child->message(child, 0x1a, 0);
        float shown = sel;
        object->unk28 = shown;
        object->unk24 = FUN_43d810(object->unk24, shown, 0.001f);
        object->unk20 = FUN_43d810(object->unk20, object->unk1c, 0.001f);
        FUN_43df60(g_624db8[sel].unk3c - g_624db8[sel].unk38 + 1, 1.0f,
                   g_624db8[sel].unk34 - g_624db8[sel].unk38 + object->unk1c, object->unk18, 1.0f, shown);
        object->unk38[0] = object->unk44[0] * 0.01f;
        object->unk38[1] = object->unk44[1] * 0.01f;
        object->unk38[2] = object->unk44[2] * 0.01f;
        for (int i = 0; i < 3; i++)
        {
            object->unk2c[i] = FUN_43d810(object->unk2c[i], object->unk38[i], 0.001f);
        }
        for (int j = 0; j < object->unk18; j++)
        {
            float target = g_624db8[j].unk34 - 1;
            g_624db8[j].unk30 = FUN_43d810(g_624db8[j].unk30, target, 0.001f);
        }
        return 0;
    }
    case 3:
        FUN_453b50(object, object->unk20, object->unk24);
        FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
        FUN_4392b0(0xdf, 0);
        FUN_439340(object->unk54);
        FUN_453a90(object);
        FUN_453dd0(object);
        break;
    }
    return 0;
}

int FUN_456000();

// FUNCTION: STUNTGP_D3D 0x4542c0
int FUN_4542c0(MenuHolder *object, int msg, int arg)
{
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        FUN_440890(msg);
        switch (object->child->message(object->child, 0x1a, 0))
        {
        case 1:
            g_menuState.unk4234 = 0;
            g_menuState.unk4230 = 7;
            FUN_43dfa0(0, 0x24);
            return 0;
        case 0:
            g_menuState.unk4234 = 0;
            g_menuState.unk4230 = 6;
            FUN_43dfa0(0, 0x24);
            return 0;
        }
        break;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 1:
        if (FUN_456000() < 2)
        {
            FUN_440880(2);
            FUN_43eef0();
            return 0;
        }
        break;
    case 3:
        FUN_4392b0(0xbc, 0);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x454450
void FUN_454450(PoolObject *object)
{
}

// FUNCTION: STUNTGP_D3D 0x454ce0
int FUN_454ce0(MenuHolder *object, int arg)
{
    g_488358.items = g_4882b8;
    if (g_menuState.languageCount >= 2)
    {
        g_488358.items = g_4881f8;
    }
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488390
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488358))
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
    return 1;
}

void FUN_43d500(int a);

// Options menu: opens the chosen settings page, saving when it is left.
// FUNCTION: STUNTGP_D3D 0x454da0
int FUN_454da0(MenuHolder *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        child = object->child;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 0:
            FUN_43dfa0(0, 0x11);
            return 0;
        case 1:
            FUN_43dfa0(0, 0x12);
            return 0;
        case 2:
            FUN_43dfa0(0, 0x13);
            return 0;
        case 3:
            FUN_43dfa0(0, 0x10);
            return 0;
        case 4:
            g_menuState.unk4254 = 0;
            FUN_43dfa0(0, 0x1d);
            return 0;
        case 5:
            FUN_43dfa0(0, 0x1e);
            return 0;
        case 99:
            FUN_43dfa0(0, 0x1a);
            return 0;
        }
        break;
    case 0x11:
        FUN_440890(msg);
        FUN_43eef0();
        FUN_43d500(0);
        return 0;
    case 3:
        FUN_4392b0(0x49, 0);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x454fa0
int FUN_454fa0(Unk4516c0 *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x4884c8
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488490))
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
    object->unk1c = 0;
    list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x4884d4
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488420))
    {
        Pool_Free(list);
        object->unk18 = NULL;
    }
    else
    {
        object->unk18 = &list->base;
    }
    child = object->unk18;
    child->message(child, 0x18, 0);
    return 1;
}

void FUN_4552f0(Unk453460 *object);
void FUN_455320(Unk453460 *object);

// Options menu; unk1c is set while the reset confirmation is open.
// FUNCTION: STUNTGP_D3D 0x4550d0
int FUN_4550d0(Unk4516c0 *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
        object->unk14->message(object->unk14, msg, 0);
        return 0;
    case 0x10:
        if (object->unk1c)
        {
            child = object->unk18;
            child->message(child, msg, 0);
            if (child->message(child, 0x1a, 0) == 1)
            {
                FUN_455320((Unk453460 *)object);
                return 0;
            }
            int language = g_menuState.unk0090;
            FUN_43c060();
            FUN_43c370();
            FUN_43c130();
            FUN_43c000();
            g_menuState.unk0090 = language;
            FUN_455320((Unk453460 *)object);
            FUN_43eef0();
            return 0;
        }
        child = object->unk14;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 0:
            g_menuState.unk0078 ^= 1;
            return 0;
        case 1:
            g_menuState.unk46c8 = 2;
            g_menuState.unk46bc = 0;
            g_menuState.unk46c0 = 0;
            break;
        case 2:
            g_menuState.unk46c8 = 3;
            g_menuState.unk46bc = 0;
            g_menuState.unk46c0 = 0;
            break;
        case 3:
            FUN_4552f0((Unk453460 *)object);
            object->unk14->message(object->unk14, msg, 0);
            return 0;
        default:
            return 0;
        }
        g_menuState.unk46c4 = 0;
        FUN_43dfa0(0, 0x1b);
        return 0;
    case 0x14:
        object->unk14->message(object->unk14, msg, 0);
        return 0;
    case 0xb:
    case 0xc:
        if (!object->unk1c)
        {
            object->unk14->message(object->unk14, msg, 0);
            return 0;
        }
        object->unk18->message(object->unk18, msg, 0);
        break;
    case 0x11:
        if (object->unk1c)
        {
            FUN_455320((Unk453460 *)object);
            FUN_440890(msg);
            return 0;
        }
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 3:
        FUN_4392b0(0x4a, 0);
    case 2:
        object->unk14->message(object->unk14, msg, 0);
        object->unk18->message(object->unk18, msg, 0);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x455340
int FUN_455340(MenuHolder *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488578
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488540))
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
    g_menuState.music = FUN_43d790(g_menuState.music, 0, 100);
    int value = FUN_43d790(g_menuState.sfx, 0, 100);
    g_menuState.sfx = value - value % 10;
    g_menuState.music -= g_menuState.music % 10;
    return 1;
}

// Sound options: music and effects volume in steps of 10, and the speaker mode.
// FUNCTION: STUNTGP_D3D 0x455430
int FUN_455430(MenuHolder *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        child = object->child;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 2:
            if (g_menuState.unk4240 == 2)
            {
                g_menuState.unk4240 = 1;
                return 0;
            }
            if (g_menuState.unk4240 == 1)
            {
                g_menuState.unk4240 = 2;
                return 0;
            }
            break;
        case 1:
            g_menuState.sfx += 10;
            if (g_menuState.sfx > 100)
            {
                g_menuState.sfx = 0;
                return 0;
            }
            break;
        case 0:
            g_menuState.music += 10;
            if (g_menuState.music > 100)
            {
                g_menuState.music = 0;
                return 0;
            }
            break;
        }
        break;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 3:
        FUN_4392b0(0x4d, 0);
        g_488540.items[0].text = g_menuState.music / 10 + 0x6d;
        g_488540.items[1].text = g_menuState.sfx / 10 + 0x61;
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        break;
    }
    return 0;
}

// Graphics options: detail level in steps of 10, and the display and controls pages.
// FUNCTION: STUNTGP_D3D 0x4556b0
int FUN_4556b0(MenuHolder *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        child = object->child;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 2:
            FUN_43dfa0(0, 0x16);
            return 0;
        case 1:
            FUN_43dfa0(0, 4);
            return 0;
        case 0:
            g_menuState.unk0084 += 10;
            if (g_menuState.unk0084 > 100)
            {
                g_menuState.unk0084 = 0;
                return 0;
            }
            break;
        }
        break;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 3:
        FUN_4392b0(0x50, 0);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x4557f0
void FUN_4557f0(PoolObject *object)
{
}

void FUN_4558c0();
void FUN_4558e0(PoolObject *object);

// Car choice page: each player picks a car with the pad.
// FUNCTION: STUNTGP_D3D 0x455800
int FUN_455800(PoolObject *object, int msg, int arg)
{
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
        return 0;
    case 0x10:
    case 0x11:
        FUN_440890(msg);
        FUN_43eef0();
        FUN_4558c0();
        return 0;
    case 1:
        FUN_455af0(object);
        return 0;
    case 3:
        FUN_4392b0(0x53, 0);
        FUN_439340(0x55);
        FUN_4558e0(object);
        break;
    }
    return 0;
}

void FUN_455f60(Unk455fc0 *object);
void FUN_455fc0(Unk455fc0 *object);

// FUNCTION: STUNTGP_D3D 0x455d90
int FUN_455d90(Unk455fc0 *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        child = object->child;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 0:
            FUN_455fc0(object);
            FUN_43eef0();
            return 0;
        case 1:
            object->unk18 = (object->unk18 + 1) % 2;
            return 0;
        case 2:
            object->unk1c = (object->unk1c + 1) % 2;
            return 0;
        case 3:
            object->unk20 = (object->unk20 + 1) % 3;
            return 0;
        case 4:
            object->unk24 = (object->unk24 + 1) % 3;
            return 0;
        case 5:
            object->unk28 = (object->unk28 + 1) % 4;
            return 0;
        case 6:
            object->unk2c = (object->unk2c + 1) % 4;
            return 0;
        }
        break;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
        }
        g_menuState.unk1dae4 = 1;
        FUN_455fc0(object);
        return 0;
    case 3:
        FUN_455f60(object);
        FUN_4392b0(0x292, 0);
        FUN_439340(0x2c7);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x4560b0
void FUN_4560b0(PoolObject *object)
{
}

void FUN_456220(Unk456070 *object);
void FUN_4562b0(Unk456070 *object);
void FUN_4564b0(Unk456070 *object);
int FUN_456670(Unk456070 *object);
void FUN_4566b0(Unk456070 *object);
void FUN_456760(Unk456070 *object);

// Player join page; unk14 delays the input, unk18 is set while too few players have joined.
// FUNCTION: STUNTGP_D3D 0x4560c0
int FUN_4560c0(Unk456070 *object, int msg, int arg)
{
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
        return 0;
    case 1:
        if (object->unk14)
        {
            object->unk14--;
            return 0;
        }
        FUN_4564b0(object);
        FUN_456760(object);
        if (!object->unk1c && FUN_456670(object))
        {
            FUN_440880(3);
            FUN_43eef0();
            return 0;
        }
        break;
    case 0x11:
        FUN_440880(2);
        g_menuState.unk46a8 = 1;
        FUN_43eef0();
        return 0;
    case 3:
        FUN_4392b0(0xc1, 0);
        FUN_439340(0xd0);
        if (FUN_456000() < 2)
        {
            if (!object->unk18)
            {
                FUN_440880(7);
                object->unk18 = 1;
            }
            FUN_456220(object);
        }
        else if (object->unk18)
        {
            FUN_440880(8);
            object->unk18 = 0;
        }
        FUN_4562b0(object);
        if (!object->unk18)
        {
            FUN_4566b0(object);
        }
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x4567d0
int FUN_4567d0(Unk4516c0 *object, int arg)
{
    object->unk24 = 0;
    g_4888c0.items = g_488820;
    if (g_menuState.unk4230 == 7 && g_menuState.unk00e8 >= 0 && g_menuState.unk00e8 <= 2 &&
        g_menuState.unk1dae0 >= (&g_4888c0.unk2c)[g_menuState.unk00e8])
    {
        g_4888c0.items = g_488880;
        object->unk24 = 1;
    }
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488900
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4888c0))
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
    object->unk1c = 0;
    object->unk20 = 0;
    list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x48890c
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4887f0))
    {
        Pool_Free(list);
        object->unk18 = NULL;
    }
    else
    {
        object->unk18 = &list->base;
    }
    child = object->unk18;
    child->message(child, 0x18, 0);
    g_menuState.unk1da8c = 0;
    return 1;
}

// Race result page; unk1c is the arrow animation phase, unk20 set while the second menu is open.
struct Unk456950
{
    DWORD unk00[5];    // 0x00
    PoolObject *unk14; // 0x14
    PoolObject *unk18; // 0x18
    float unk1c;       // 0x1c
    int unk20;         // 0x20
    int unk24;         // 0x24
};

void FUN_456bf0(Unk456950 *object);
void FUN_456c80(Unk4516c0 *object);
void FUN_456f70(Unk453460 *object);
void FUN_456fa0(Unk453460 *object);

// FUNCTION: STUNTGP_D3D 0x456950
int FUN_456950(Unk456950 *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x5f, 0.3f, -0.5f);
    case 0x14:
        object->unk14->message(object->unk14, msg, 0);
        return 0;
    case 0x10:
        if (object->unk20)
        {
            child = object->unk18;
            child->message(child, msg, 0);
            if (child->message(child, 0x1a, 0) == 1)
            {
                FUN_456fa0((Unk453460 *)object);
                return 0;
            }
            g_menuState.unk1da8c = 2;
            FUN_43eef0();
            return 0;
        }
        child = object->unk14;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 1:
            FUN_456f70((Unk453460 *)object);
            return 0;
        case 0:
            if (object->unk24)
            {
                g_menuState.unk1da8c = 2;
                FUN_43eef0();
                return 0;
            }
            g_menuState.unk1da8c = 1;
            FUN_43eef0();
            return 0;
        }
        break;
    case 0xb:
    case 0xc:
        if (object->unk20)
        {
            object->unk18->message(object->unk18, msg, 0);
            return 0;
        }
        object->unk14->message(object->unk14, msg, 0);
        return 0;
    case 0x11:
        if (object->unk24)
        {
            FUN_440880(9);
            return 0;
        }
        FUN_440890(msg);
        if (object->unk20)
        {
            FUN_456fa0((Unk453460 *)object);
        }
        else
        {
            FUN_456f70((Unk453460 *)object);
        }
        return 0;
    case 2:
    {
        object->unk14->message(object->unk14, msg, 0);
        object->unk18->message(object->unk18, msg, 0);
        float phase = object->unk1c + 0.03f;
        object->unk1c = phase - (int)phase;
        return 0;
    }
    case 3:
        FUN_456c80((Unk4516c0 *)object);
        FUN_456bf0(object);
        FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
        object->unk14->message(object->unk14, msg, 0);
        object->unk18->message(object->unk18, msg, 0);
        switch (g_menuState.unk4230)
        {
        case 7:
            switch (g_menuState.unk00e0)
            {
            case 2:
                FUN_4392b0(0x2a7, 0);
                return 0;
            case 1:
                FUN_4392b0(0x2a6, 0);
                return 0;
            case 0:
                FUN_4392b0(0x2a5, 0);
                return 0;
            }
            break;
        case 6:
            FUN_4392b0(0x28c, 0);
            break;
        }
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x456fc0
int FUN_456fc0(MenuHolder *object, int arg)
{
    int tracks[64];
    int count = 0;
    int i;
    for (i = 1; i < 0x19; i++)
    {
        if (FUN_4371c0(i, 3))
        {
            tracks[count++] = i;
        }
    }
    FUN_4375a0(tracks, count);
    for (i = 0; i < count; i++)
    {
        MenuItem *item = &g_625138[i];
        *item = g_488920;
        item->id = tracks[i];
        item->text = tracks[i] + 0x1b7;
        item->unk10 = 0;
    }
    g_625138[i] = g_488940;
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488998
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488960))
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
    return 1;
}

// Track high-score menu: opens the score list of the chosen track.
// FUNCTION: STUNTGP_D3D 0x457110
int FUN_457110(MenuHolder *object, int msg, int arg)
{
    PoolObject *child;
    int track;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        child = object->child;
        child->message(child, msg, 0);
        track = child->message(child, 0x1a, 0);
        if (FUN_4371c0(track, 3))
        {
            g_menuState.unk4694.unk00 = 0x1fc;
            g_menuState.unk4694.unk04 = (int)FUN_441170(track + 0x1b7);
            g_menuState.unk4694.unk08 = 3;
            g_menuState.unk4694.count = 10;
            g_menuState.unk4694.entries = g_menuState.unk0694[track].entries;
            FUN_43dfa0(0x2a, 0x27);
            return 0;
        }
        break;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 3:
        FUN_4392b0(0x2cc, 0);
        object->child->message(object->child, msg, 0);
        FUN_439340(0x2cd);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x457260
int FUN_457260(MenuHolder *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488a40
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488a08))
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
    return 1;
}

// Arcade high-score menu.
// FUNCTION: STUNTGP_D3D 0x457300
int FUN_457300(MenuHolder *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        child = object->child;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 1:
            g_menuState.unk4694.unk00 = 0x28a;
            g_menuState.unk4694.unk04 = 0;
            g_menuState.unk4694.unk08 = 1;
            g_menuState.unk4694.count = 10;
            g_menuState.unk4694.entries = g_menuState.unk1dac;
            FUN_43dfa0(0x31, 0x27);
            return 0;
        case 0:
            g_menuState.unk4694.unk00 = 0x28b;
            g_menuState.unk4694.unk04 = 0;
            g_menuState.unk4694.unk08 = 0;
            g_menuState.unk4694.count = 10;
            g_menuState.unk4694.entries = g_menuState.unk1d5c;
            FUN_43dfa0(0x31, 0x27);
            return 0;
        }
        break;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 3:
        FUN_4392b0(0x2ce, 0);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x457470
int FUN_457470(MenuHolder *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488b28
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488af0))
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
    FUN_43bf30();
    return 1;
}

// High-score category menu.
// FUNCTION: STUNTGP_D3D 0x457520
int FUN_457520(MenuHolder *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        child = object->child;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 0:
            g_menuState.unk4694.unk00 = 0x1fb;
            g_menuState.unk4694.unk04 = 0;
            g_menuState.unk4694.unk08 = 2;
            g_menuState.unk4694.count = 100;
            g_menuState.unk4694.entries = g_menuState.unk0374;
            FUN_43dfa0(0x10, 0x27);
            return 0;
        case 1:
            FUN_43dfa0(0x2a, 0x22);
            return 0;
        case 2:
            g_menuState.unk4694.unk00 = 0x1fd;
            g_menuState.unk4694.unk04 = 0;
            g_menuState.unk4694.unk08 = 2;
            g_menuState.unk4694.count = 100;
            g_menuState.unk4694.entries = g_menuState.unk1dfc;
            FUN_43dfa0(0x25, 0x27);
            return 0;
        case 3:
            FUN_43dfa0(0x31, 0x23);
            return 0;
        }
        break;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 3:
        FUN_4392b0(0x2ca, 0);
        object->child->message(object->child, msg, 0);
        FUN_439340(0x2cb);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x4576e0
int FUN_4576e0(Unk457770 *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488bf0
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488bb8))
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
    object->unk18 = 1;
    FUN_457770(object);
    return 1;
}

void FUN_424a90(int mode);

// Display options: two display modes, or the screen position page.
// FUNCTION: STUNTGP_D3D 0x4577e0
int FUN_4577e0(Unk457770 *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x61, 0.3f, -0.5f);
        object->unk14->message(object->unk14, msg, 0);
        return 0;
    case 0x10:
        child = object->unk14;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 2:
            object->unk18 = 1;
            FUN_43dfa0(0, 0x17);
            return 0;
        case 1:
            g_menuState.unk0094 = 2;
            FUN_424a90(g_menuState.unk0094);
            FUN_43eef0();
            return 0;
        case 0:
            g_menuState.unk0094 = 1;
            FUN_424a90(g_menuState.unk0094);
            FUN_43eef0();
            return 0;
        }
        break;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 1:
        FUN_457770(object);
        return 0;
    case 3:
        FUN_4392b0(0x8e, 0);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->unk14->message(object->unk14, msg, 0);
        break;
    }
    return 0;
}

int FUN_440170();

// FUNCTION: STUNTGP_D3D 0x457910
int FUN_457910()
{
    return FUN_440170();
}

// FUNCTION: STUNTGP_D3D 0x457920
int FUN_457920(Unk457e70 *object, int arg)
{
    object->unk18 = FUN_4402e0();
    g_menuState.unk46e0 = 0;
    object->unk1c = 0;
    object->unk20 = 0;
    object->unk24 = 0;
    object->unk28 = 0;
    object->unk2c = 0;
    object->unk30 = 0;
    object->unk34 = 0;
    object->unk38 = 1.0f;
    object->unk3c = 1.0f;
    for (int i = 0; i < 8; i++)
    {
        object->unk044[i] = 1;
    }
    FUN_457a40(object);
    int index = FUN_457cf0(object, g_menuState.unk46c8);
    object->unk20 = index;
    object->unk2c = object->unk28 = index;
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488c98
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488c60))
    {
        Pool_Free(list);
        object->unk40 = NULL;
    }
    else
    {
        object->unk40 = &list->base;
    }
    PoolObject *child = object->unk40;
    child->message(child, 0x18, 0);
    child->message(child, 0x13, 0);
    if (FUN_457a20(g_menuState.unk46c8))
    {
        g_menuState.unk46bc = 1;
    }
    return 1;
}

// GLOBAL: STUNTGP_D3D 0x627bd4
char g_627bd4[0x80];

int FUN_457a20(int value);
void FUN_4581b0(Unk457e70 *object);
void FUN_458730(Unk457e70 *object);
int FUN_458800(Unk457e70 *object);
int FUN_458820(Unk457e70 *object);
void FUN_458880(Unk457e70 *object, int msg);
char *FUN_43d550(int frames);

// PageSave: card checks, the card list and the prompt, with the page title for the action.
// FUNCTION: STUNTGP_D3D 0x457ec0
int FUN_457ec0(PoolObject *base, int msg, int arg)
{
    Unk457e70 *object = (Unk457e70 *)base;
    switch (msg)
    {
    case 2:
    {
        object->unk40->message(object->unk40, msg, 0);
        object->unk1c++;
        float sel = object->unk20;
        object->unk2c = sel;
        object->unk28 = FUN_43d810(object->unk28, sel, 0.2f);
        object->unk30 = FUN_43d810(object->unk30, object->unk34, 0.001f);
        float fade = FUN_43d8f0(object->unk38, object->unk3c, 0.025f);
        object->unk38 = fade;
        if (FUN_457a20(g_menuState.unk46c8) && g_menuState.unk46bc)
        {
            FUN_43dd40(0, 0.0f, 0.0f);
            return 0;
        }
        if (object->unk24)
        {
            FUN_43dd40(object->unk1ec ? 0x69 : 0x5c, fade * 0.75f, fade * 0.45f);
            return 0;
        }
        break;
    }
    case 1:
        if (FUN_458820(object))
        {
            break;
        }
        object->unk40->message(object->unk40, msg, 0);
        FUN_458880(object, msg);
        if (g_menuState.unk46c8 == 1 && g_menuState.unk46bc && object->unk1ec && (object->unk1f0 || object->unk1e8))
        {
            object->unk14 = 1;
        }
        if (object->unk14)
        {
            FUN_458800(object);
            return 0;
        }
        break;
    case 0xb:
    case 0xc:
    case 0x10:
    case 0x11:
        if (!FUN_458820(object))
        {
            FUN_458880(object, msg);
            return 0;
        }
        break;
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x112a43);
        object->unk24 = 1;
        object->unk34 = 1.0f;
        return 0;
    case 0x14:
        object->unk34 = 0.0f;
        return 0;
    case 3:
        if (FUN_457a20(g_menuState.unk46c8) && g_menuState.unk46bc)
        {
            break;
        }
        if (object->unk1ec && !object->unk1e8 && !object->unk1f0)
        {
            FUN_458730(object);
        }
        FUN_4581b0(object);
        switch (g_menuState.unk46c8)
        {
        case 1:
            FUN_4392b0(0x20c, 0);
            break;
        case 2:
            FUN_4392b0(0x213, 0);
            break;
        case 3:
            FUN_4392b0(0x21a, 0);
            break;
        case 4:
            FUN_4392b0(0x221, (int)FUN_441170(g_menuState.unk46cc + 0x1b7));
            break;
        case 5:
            // STRING: STUNTGP_D3D 0x488cac
            sprintf(g_627bd4, "%s - %s", FUN_441170(g_menuState.unk46cc + 0x1b7),
                    FUN_43d550(((GhostHeader *)g_menuState.unk46d0)->frames));
            FUN_4392b0(0x228, (int)g_627bd4);
            break;
        }
        FUN_458880(object, msg);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x459200
int FUN_459200(Unk459200 *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488d30
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488cf8))
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
    object->unk2c = 0.05f;
    object->scores = g_menuState.unk4694;
    int count = object->scores.count;
    object->unk1c = 0;
    object->unk20 = 0;
    object->unk24 = 0;
    object->unk28 = 0;
    object->unk30 = 200.0f;
    object->unk34 = 1.0f;
    object->unk18 = 0;
    if (count > 10)
    {
        for (int i = 0; i < count; i++)
        {
            if (object->scores.entries[i].name[3])
            {
                object->unk1c = i - 4;
                break;
            }
        }
        int max = count - 10;
        if (object->unk1c < 0)
        {
            object->unk1c = 0;
        }
        if (object->unk1c > max)
        {
            object->unk1c = max;
        }
    }
    return 1;
}

// PageHighScore as its handler sees it: unk20 scrolls towards unk1c, unk28 drives the wave.
struct Unk459320
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18, set once the wave starts to settle
    int unk1c;         // 0x1c, first entry shown
    float unk20;       // 0x20
    float unk24;       // 0x24
    float unk28;       // 0x28
    float unk2c;       // 0x2c
    float unk30;       // 0x30, wave amplitude
    float unk34;       // 0x34
    ScoreList scores;  // 0x38
};

// GLOBAL: STUNTGP_D3D 0x627c54
char g_627c54[0x80];

float FUN_43d880(float current, float target, float rate);

// Ten rows of the score list, each line swaying on its own phase.
// FUNCTION: STUNTGP_D3D 0x459530
void FUN_459530(Unk459320 *object)
{
    int rows = 10;
    if (object->scores.count < 10)
    {
        rows = object->scores.count;
    }
    int first = (int)object->unk20;
    float y = (235.0f - ((rows - 1) * 28.0f) * 0.5f) - (object->unk20 - first) * 28.0f;
    int i = first;
    if (first < 0)
    {
        i = 0;
    }
    int end = first + rows + 1;
    if (end > object->scores.count)
    {
        end = object->scores.count;
    }
    float phase = object->unk28;
    if (i >= end)
    {
        return;
    }
    int type = object->scores.unk08;
    ScoreEntry *entry = &object->scores.entries[i];
    char *name = entry->name;
    do
    {
        phase += 0.02f;
        int next = i + 1;
        // STRING: STUNTGP_D3D 0x488d3c
        sprintf(g_627c54, "%03d:", next);
        float wave = (float)sin(((i & 1) ? phase + object->unk34 : phase) * 3.1415927f) * object->unk30;
        D3DCOLOR color;
        if (name[3] && (FUN_43dd60() & 0x20))
        {
            color = 0xffff8080;
        }
        else
        {
            color = 0xffffffff;
        }
        float x = wave + 320.0f;
        FUN_438960(x - 150.0f, y, 17, 0, 2, g_627c54, 1.5f, color, 3);
        FUN_438960(x - 70.0f, y, 17, 0, 2, FUN_43d690((Initials *)name)->c, 1.5f, color, 3);
        // STRING: STUNTGP_D3D 0x488d44
        FUN_438960(x, y, 17, 0, 2, "..........", 1.5f, color, 3);
        switch (type)
        {
        case 0:
            strcpy(g_627c54, FUN_43d5f0(entry->time, 7));
            break;
        case 1:
            // STRING: STUNTGP_D3D 0x488d50
            sprintf(g_627c54, "%03d", entry->time);
            break;
        case 2:
            // STRING: STUNTGP_D3D 0x488d58
            sprintf(g_627c54, "%07d", entry->time);
            break;
        case 3:
            strcpy(g_627c54, FUN_43d550(entry->time));
            break;
        }
        FUN_438a20(wave + 480.0f, y, 17, 0, 2, g_627c54, 1.5f, color, 6, 14.0f);
        y += 28.0f;
        entry++;
        name += 8;
        i = next;
    } while (i < end);
}

// FUNCTION: STUNTGP_D3D 0x459320
int FUN_459320(Unk459320 *object, int msg, int arg)
{
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(6);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x61, -0.4f, 0.3f);
        object->child->message(object->child, msg, 0);
        object->unk18 = 1;
        return 0;
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x11:
        FUN_440890(msg);
    case 0x10:
        object->child->message(object->child, msg, 0);
        FUN_43eef0();
        return 0;
    case 0xb:
        if (object->scores.count > 10 && object->unk1c)
        {
            object->unk1c -= 5;
            if (object->unk1c < 0)
            {
                object->unk1c = 0;
            }
            FUN_440890(msg);
            return 0;
        }
        break;
    case 0xc:
        if (object->scores.count > 10)
        {
            int last = object->scores.count - 10;
            if (object->unk1c != last)
            {
                object->unk1c += 5;
                if (object->unk1c > last)
                {
                    object->unk1c = last;
                }
                FUN_440890(msg);
                return 0;
            }
        }
        break;
    case 2:
    {
        object->child->message(object->child, msg, 0);
        float target = object->unk1c;
        object->unk24 = target;
        object->unk20 = FUN_43d810(object->unk20, target, 0.001f);
        object->unk28 += object->unk2c;
        if (object->unk18)
        {
            object->unk30 = FUN_43d880(object->unk30, 0.0f, 0.001f);
        }
        int count = object->scores.count;
        if (count > 10)
        {
            FUN_43df60(0.0f, 0.0f, 0.0f, count, 10.0f, target);
            return 0;
        }
        FUN_43df60(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        return 0;
    }
    case 3:
        FUN_459530(object);
        FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
        object->child->message(object->child, msg, 0);
        FUN_4392b0(object->scores.unk00, object->scores.unk04);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x459790
int FUN_459790(Unk459790 *object, int arg)
{
    int row = g_menuState.unk1b078;
    int i;
    int j;
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488dd8
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488da0))
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
    object->unk1c = 0;
    object->unk18 = 0;
    object->unk30 = g_menuState.nodePositions[g_menuState.results[0].position - 1];
    object->unk48 = 1;
    object->unk4c = 1;
    object->unk50 = 1;
    object->unk54 = 1;
    object->unk70 = 0;
    object->unk74 = 0;
    object->unk20 = 0;
    object->unk34 = g_menuState.results[0].unk10;
    for (i = 1; i < 6; i++)
    {
        if (g_menuState.results[i].unk04 < g_menuState.results[0].unk04)
        {
            object->unk48 = 0;
        }
        if (g_menuState.results[i].unk08 < g_menuState.results[0].unk08)
        {
            object->unk4c = 0;
        }
        if (g_menuState.results[i].unk0c > g_menuState.results[0].unk0c)
        {
            object->unk50 = 0;
        }
        if (g_menuState.results[i].unk10 > g_menuState.results[0].unk10)
        {
            object->unk54 = 0;
        }
    }
    if (FUN_437d60(&g_menuState.unk0114[row][0], &g_menuState.names[0].name, g_menuState.results[0].unk04))
    {
        object->unk48 = 2;
    }
    if (FUN_437d60(&g_menuState.unk0114[row][1], &g_menuState.names[0].name, g_menuState.results[0].unk08))
    {
        object->unk4c = 2;
    }
    if (FUN_437d20(&g_menuState.unk0114[row][2], &g_menuState.names[0].name, g_menuState.results[0].unk0c))
    {
        object->unk50 = 2;
    }
    if (FUN_437d20(&g_menuState.unk0114[row][3], &g_menuState.names[0].name, g_menuState.results[0].unk10))
    {
        object->unk54 = 2;
    }
    object->unk38 = FUN_459a00(object->unk48);
    object->unk3c = FUN_459a00(object->unk4c);
    object->unk40 = FUN_459a00(object->unk50);
    object->unk44 = FUN_459a00(object->unk54);
    object->unk28 = g_menuState.unk424c;
    g_menuState.unk424c +=
        object->unk34 + object->unk44 + object->unk40 + object->unk3c + object->unk38 + object->unk30;
    for (i = 0; i < 6; i++)
    {
        object->unk58[i] = i;
    }
    for (i = 5; i >= 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            int a = object->unk58[j];
            int b = object->unk58[j + 1];
            if (g_menuState.results[a].position > g_menuState.results[b].position)
            {
                object->unk58[j] = b;
                object->unk58[j + 1] = a;
            }
        }
    }
    object->unk78 = 0;
    object->unk7c = 0;
    for (i = 0; i < 8; i++)
    {
        object->unk80[i] = 0;
        object->unka0[i] = 0;
    }
    if (object->unk48)
    {
        object->unk7c++;
    }
    if (object->unk4c)
    {
        object->unk7c++;
    }
    if (object->unk54)
    {
        object->unk7c++;
    }
    return 1;
}

void FUN_459ec0(Unk459790 *object);
void FUN_45a280(Unk459790 *object);
void FUN_45a350();

// Results screen: counts the race score, then each bonus in turn, into the total.
// FUNCTION: STUNTGP_D3D 0x459a40
int FUN_459a40(Unk459790 *object, int msg, int arg)
{
    int v;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x5f, 0.3f, -0.5f);
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        object->child->message(object->child, msg, 0);
        FUN_43bf30();
        FUN_43eef0();
        return 0;
    case 2:
    {
        object->child->message(object->child, msg, 0);
        float *fade = object->unka0;
        for (int i = 8; i; i--)
        {
            *fade = FUN_43d810(*fade, 0.0f, 0.001f);
            fade++;
        }
        return 0;
    }
    case 1:
        v = object->unk24;
        if (v)
        {
            int step = v;
            if (step > 1000)
            {
                step = 1000;
            }
            int frequency = (object->unk2c - v) / 20 + 20000;
            if (frequency > 44000)
            {
                frequency = 44000;
            }
            if (object->unk20 % 3 == 0)
            {
                FUN_440770(11, frequency);
            }
            object->unk24 = v - step;
            object->unk28 += step;
            object->unk20++;
            return 0;
        }
        if (object->unk1c)
        {
            object->unk1c--;
            return 0;
        }
        switch (object->unk18)
        {
        case 0:
            object->unk1c = 60;
            object->unk18 = 1;
            return 0;
        case 1:
            v = object->unk30;
            if (v)
            {
                object->unk74 = 15;
                object->unk70 = v;
                object->unk1c = 60;
                object->unk20 = 0;
                FUN_45a350();
            }
            object->unk24 = v;
            object->unk2c = v;
            object->unk30 = 0;
            if (!v)
            {
                object->unk18 = 2;
                return 0;
            }
            break;
        case 2:
            v = object->unk38;
            if (v)
            {
                if (object->unk48 == 1)
                {
                    object->unka0[object->unk78] = 1.0f;
                    object->unk80[object->unk78] = 0x4d;
                    object->unk78++;
                }
                if (object->unk48 == 2)
                {
                    object->unka0[object->unk78] = 1.0f;
                    object->unk80[object->unk78] = 0x51;
                    object->unk78++;
                }
                v = object->unk38;
                object->unk74 = 16;
                object->unk70 = v;
                object->unk1c = 60;
                object->unk20 = 0;
                FUN_45a350();
            }
            object->unk24 = v;
            object->unk2c = v;
            object->unk38 = 0;
            if (!v)
            {
                object->unk18 = 3;
                return 0;
            }
            break;
        case 3:
            v = object->unk3c;
            if (v)
            {
                if (object->unk4c == 1)
                {
                    object->unka0[object->unk78] = 1.0f;
                    object->unk80[object->unk78] = 0x50;
                    object->unk78++;
                }
                if (object->unk4c == 2)
                {
                    object->unka0[object->unk78] = 1.0f;
                    object->unk80[object->unk78] = 0x54;
                    object->unk78++;
                }
                v = object->unk3c;
                object->unk74 = 17;
                object->unk70 = v;
                object->unk1c = 60;
                object->unk20 = 0;
                FUN_45a350();
            }
            object->unk24 = v;
            object->unk2c = v;
            object->unk3c = 0;
            if (!v)
            {
                object->unk18 = 4;
                return 0;
            }
            break;
        case 4:
            v = object->unk44;
            if (v)
            {
                if (object->unk54 == 1)
                {
                    object->unka0[object->unk78] = 1.0f;
                    object->unk80[object->unk78] = 0x4f;
                    object->unk78++;
                }
                if (object->unk54 == 2)
                {
                    object->unka0[object->unk78] = 1.0f;
                    object->unk80[object->unk78] = 0x53;
                    object->unk78++;
                }
                v = object->unk44;
                object->unk74 = 18;
                object->unk70 = v;
                object->unk1c = 60;
                object->unk20 = 0;
                FUN_45a350();
            }
            object->unk24 = v;
            object->unk2c = v;
            object->unk44 = 0;
            if (!v)
            {
                object->unk18 = 5;
                return 0;
            }
            break;
        case 5:
            v = object->unk34;
            if (v)
            {
                object->unk74 = 19;
                object->unk70 = v;
                object->unk1c = 60;
                object->unk20 = 0;
                FUN_45a350();
            }
            object->unk24 = v;
            object->unk2c = v;
            object->unk34 = 0;
            if (!v)
            {
                object->unk18 = 6;
                FUN_440880(13);
                return 0;
            }
            break;
        case 6:
            object->unk74 = 0;
            object->unk70 = 0;
            return 0;
        }
        break;
    case 3:
        FUN_459ec0(object);
        FUN_45a280(object);
        FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
        object->child->message(object->child, msg, 0);
        FUN_4392b0(0x1fa, 0);
        break;
    }
    return 0;
}


void FUN_438740(int layer, int def, float x, float y, float scale, DWORD flags, float fade);

// Results table: per finisher in order its position, name, two times and score, then the total
// and the medal bonus.
// FUNCTION: STUNTGP_D3D 0x459ec0
void FUN_459ec0(Unk459790 *object)
{
    FUN_439450(120.0f, 90.0f, 520.0f, 380.0f, 10, 0x6e, 0x40);
    FUN_439380(120.0f, 90.0f, 520.0f, 380.0f, 13, 2, 0, 0.0f);
    FUN_438be0(150.0f, 110.0f, 12, 4, 9, 1.25f, 0xffff8080, 3);
    FUN_438be0(200.0f, 110.0f, 12, 4, 10, 1.25f, 0xffff8080, 2);
    FUN_438be0(320.0f, 110.0f, 12, 4, 11, 1.25f, 0xffff8080, 6);
    FUN_438be0(410.0f, 110.0f, 12, 4, 13, 1.25f, 0xffff8080, 6);
    FUN_438be0(500.0f, 110.0f, 12, 4, 12, 1.25f, 0xffff8080, 6);
    float y = 130.0f;
    int *order = object->unk58;
    for (int n = 6; n; n--)
    {
        int r = *order;
        D3DCOLOR color = r ? 0xff808080 : 0xffffffff;
        FUN_438be0(150.0f, y, 12, 4, g_menuState.results[r].position + 2, 1.25f, color, 3);
        FUN_438960(200.0f, y, 12, 0, 4, FUN_43d690(&g_menuState.names[r].name)->c, 1.25f, color, 2);
        FUN_438a20(320.0f, y, 12, 0, 4, FUN_43d550(g_menuState.results[r].unk04), 1.25f, color, 6, 14.0f);
        FUN_438a20(394.0f, y, 12, 0, 4, FUN_43d550(g_menuState.results[r].unk08), 1.25f, color, 6, 14.0f);
        // STRING: STUNTGP_D3D 0x488de4
        sprintf(g_627c54 + 0x40, "%d", g_menuState.results[r].unk10);
        FUN_438a20(484.0f, y, 12, 0, 4, g_627c54 + 0x40, 1.25f, color, 6, 14.0f);
        y += 20.0f;
        order++;
    }
    y += 10.0f;
    // STRING: STUNTGP_D3D 0x488de8
    sprintf(g_627c54 + 0x40, "%07d", object->unk28);
    if (object->unk18 == 6)
    {
        float y2 = y + 20.0f;
        FUN_438be0(280.0f, y2, 12, 4, 14, 1.875f, 0xffff8080, 6);
        FUN_438a20(410.0f, y2, 12, 0, 4, g_627c54 + 0x40, 1.875f, 0xffffffff, 6, 14.0f);
    }
    else
    {
        FUN_438be0(300.0f, y, 12, 4, 14, 1.25f, 0xffff8080, 6);
        FUN_438a20(384.0f, y, 12, 0, 4, g_627c54 + 0x40, 1.25f, 0xffffffff, 6, 14.0f);
    }
    y += 30.0f;
    if (object->unk74 && object->unk70)
    {
        FUN_438be0(300.0f, y, 12, 4, object->unk74, 1.25f, 0xffff8080, 6);
        // STRING: STUNTGP_D3D 0x488df0
        sprintf(g_627c54 + 0x40, "+%d", object->unk70);
        FUN_438a20(384.0f, y, 12, 0, 4, g_627c54 + 0x40, 1.25f, 0xffffffff, 6, 14.0f);
    }
}

// Row of medals won on the results screen.
// FUNCTION: STUNTGP_D3D 0x45a280
void FUN_45a280(Unk459790 *object)
{
    float x = 320.0f - (object->unk7c - 1) * 30.0f;
    for (int i = 0; i < object->unk78; i++)
    {
        FUN_438710(x, 338.0f, 12, 0x55, 0.75f, 0x203);
        FUN_438710(x, 338.0f, 11, object->unk80[i], 0.75f, 0x103);
        float fade = object->unka0[i];
        if (fade > 0.0001)
        {
            FUN_438740(10, 0x56, x, 338.0f, 0.75f, 0x403, fade);
        }
        x += 60.0f;
    }
}

// FUNCTION: STUNTGP_D3D 0x45a360
int FUN_45a360(MenuHolder *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488e70
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488e38))
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
    g_menuState.unk1d9a8 = 0;
    return 1;
}

void FUN_450e50(int a, int b, float x, float y);
void FUN_45a500(MenuLine *lines, int count);

// Results page: its text lines over the results table; any key leaves.
// FUNCTION: STUNTGP_D3D 0x45a410
int FUN_45a410(PoolObject *base, int msg, int arg)
{
    MenuHolder *object = (MenuHolder *)base;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(g_menuState.unk1d9ac, 0.3f, -0.5f);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x11:
        FUN_440890(msg);
        g_menuState.unk1d9a8 = 1;
        FUN_43eef0();
        return 0;
    case 0x10:
        object->child->message(object->child, msg, 0);
        FUN_43eef0();
        return 0;
    case 3:
        FUN_45a500(g_menuState.unk1d9b0, g_menuState.unk1da50);
        FUN_450e50(g_menuState.unk1da54, g_menuState.unk1da58, 320.0f, 180.0f);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45a620
void FUN_45a620(PoolObject *object)
{
}

// First-run sequence: language, then the setup pages, then the main menu.
// FUNCTION: STUNTGP_D3D 0x45a630
int FUN_45a630(MenuObject *object, int msg, int arg)
{
    switch (msg)
    {
    case 1:
        switch (object->unk14)
        {
        case 0:
            g_menuState.unk46c0 = 0;
            g_menuState.unk46c4 = 0;
            g_menuState.unk46bc = 1;
            g_menuState.unk46c8 = 1;
            g_menuState.unk46d8 = -1;
            g_menuState.unk46dc = -1;
            FUN_43dfa0(0, 0x1b);
            object->unk14 = 1;
            return 0;
        case 1:
            object->unk14 = (g_menuState.unk0090 != 0) + 2;
            g_menuState.unk4254 = 1;
            FUN_43dfa0(0, 0x1d);
            return 0;
        case 2:
            g_menuState.unk46bc = 1;
            g_menuState.unk46c0 = 1;
            g_menuState.unk46c8 = 3;
            g_menuState.unk46c4 = 0;
            g_menuState.unk46d8 = 0;
            g_menuState.unk46dc = -1;
            FUN_43dfa0(0, 0x1b);
            object->unk14 = 3;
            return 0;
        case 3:
            object->unk14 = 4;
            return 0;
        case 4:
            FUN_43ef10(1, 1);
            break;
        }
        break;
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x112a43);
        FUN_43dd40(0, 0.0f, 0.0f);
        return 0;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45a770
int FUN_45a770(MenuHolder *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x488f80
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488f48))
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
    return 1;
}

// Game mode menu; the mode goes to unk4230 and resets the challenge state.
// FUNCTION: STUNTGP_D3D 0x45a810
int FUN_45a810(MenuHolder *object, int msg, int arg)
{
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(99, 0.3f, -0.5f);
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        child = object->child;
        child->message(child, msg, 0);
        switch (child->message(child, 0x1a, 0))
        {
        case 0:
            g_menuState.unk4234 = 0;
            g_menuState.unk4230 = 1;
            FUN_43dfa0(0, 0x24);
            return 0;
        case 1:
            g_menuState.unk4234 = 0;
            g_menuState.unk4230 = 2;
            FUN_43dfa0(0, 0x24);
            return 0;
        case 2:
            g_menuState.unk4234 = 0;
            g_menuState.unk4230 = 3;
            FUN_43dfa0(0, 0x24);
            return 0;
        case 3:
            g_menuState.unk4234 = 0;
            g_menuState.unk4230 = 4;
            FUN_43dfa0(0, 0x24);
            return 0;
        case 4:
            g_menuState.unk4234 = 0;
            g_menuState.unk4230 = 5;
            FUN_43dfa0(0, 0x24);
            return 0;
        }
        break;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
            return 0;
        }
        break;
    case 3:
        FUN_4392b0(0xb1, 0);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45a9c0
int FUN_45a9c0(Unk45a9c0 *object, int arg)
{
    if (g_menuState.unk4384 >= 0)
    {
        object->unk1c = g_menuState.unk4384;
    }
    else
    {
        object->unk1c = 0;
    }
    g_menuState.unk4380 = 0;
    g_menuState.unk4388 = 0;
    object->unk18 = 0;
    object->unk2c = object->unk30 = object->unk1c;
    object->unk14 = 1;
    object->unk24 = 1.0f;
    object->unk28 = 1.0f;
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x4890b8
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_488ff0))
    {
        Pool_Free(list);
        object->unk34 = NULL;
    }
    else
    {
        object->unk34 = &list->base;
    }
    list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x4890c4
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_489080))
    {
        Pool_Free(list);
        object->unk38 = NULL;
    }
    else
    {
        object->unk38 = &list->base;
    }
    object->unk34->message(object->unk34, 0x18, 0);
    PoolObject *child = object->unk38;
    child->message(child, 0x18, 0);
    for (int i = 0; i < 8; i++)
    {
        MenuSlot160 *slot = &g_menuState.unk0f1c[i];
        int money = slot->money;
        if (slot->unk000)
        {
            money += FUN_437de0(slot->sponsor, slot->car, &slot->carSetup);
        }
        strcpy(g_627cd8[0][i], FUN_43d5f0(money, 0));
        // STRING: STUNTGP_D3D 0x4890d0
        sprintf(g_627cd8[1][i], "%d", slot->unk104);
    }
    return 1;
}

void FUN_45af60(Unk45a9c0 *object);
void FUN_45b2c0(Unk45a9c0 *object);
void FUN_45b360(Unk45a9c0 *object);
void FUN_45b440(Unk45a9c0 *object);

// Championship slot select: picks a slot, then asks its two questions through unk34 and unk38.
// FUNCTION: STUNTGP_D3D 0x45abb0
int FUN_45abb0(PoolObject *base, int msg, int arg)
{
    Unk45a9c0 *object = (Unk45a9c0 *)base;
    PoolObject *child;
    int mode;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x5f, 0.3f, -0.5f);
        object->unk38->message(object->unk38, msg, 0);
        object->unk34->message(object->unk34, msg, 0);
        object->unk18 = 1;
        return 0;
    case 0xb:
        switch (object->unk14)
        {
        case 1:
            if (object->unk1c > 0)
            {
                object->unk20 = 0;
                object->unk1c--;
                FUN_440890(msg);
                return 0;
            }
            break;
        case 2:
            object->unk34->message(object->unk34, msg, 0);
            return 0;
        case 3:
            object->unk38->message(object->unk38, msg, 0);
            return 0;
        }
        break;
    case 0xc:
        switch (object->unk14)
        {
        case 1:
            if (object->unk1c < 7)
            {
                object->unk20 = 0;
                object->unk1c++;
                FUN_440890(msg);
                return 0;
            }
            break;
        case 2:
            object->unk34->message(object->unk34, msg, 0);
            return 0;
        case 3:
            object->unk38->message(object->unk38, msg, 0);
            return 0;
        }
        break;
    case 0x10:
        switch (object->unk14)
        {
        case 1:
            FUN_440890(msg);
            if (!g_menuState.unk0f1c[object->unk1c].unk000)
            {
                g_menuState.unk4388 = 1;
                g_menuState.unk4384 = object->unk1c;
                object->unk14 = 4;
                FUN_43eef0();
                return 0;
            }
            object->unk34->message(object->unk34, 0x1c, 0);
            object->unk14 = 2;
            return 0;
        case 2:
            child = object->unk34;
            child->message(child, msg, 0);
            switch (child->message(child, 0x1a, 0))
            {
            case 0:
                g_menuState.unk4384 = object->unk1c;
                object->unk14 = 4;
                FUN_43eef0();
                return 0;
            case 1:
                object->unk14 = 3;
                object->unk38->message(object->unk38, 0x1c, 0);
                return 0;
            }
            break;
        case 3:
            child = object->unk38;
            switch (child->message(child, 0x1a, 0))
            {
            case 0:
                child->message(child, msg, 0);
                g_menuState.unk4388 = 1;
                g_menuState.unk4384 = object->unk1c;
                object->unk14 = 4;
                FUN_43eef0();
                return 0;
            case 1:
                object->unk14 = 1;
                FUN_440880(2);
                return 0;
            }
            break;
        }
        break;
    case 0x11:
        switch (object->unk14)
        {
        case 1:
            g_menuState.unk4380 = 1;
            FUN_440890(msg);
            FUN_43eef0();
            return 0;
        case 2:
            object->unk34->message(object->unk34, msg, 0);
            object->unk14 = 1;
            FUN_440890(msg);
            return 0;
        case 3:
            object->unk38->message(object->unk38, msg, 0);
            object->unk14 = 1;
            FUN_440890(msg);
            return 0;
        }
        break;
    case 2:
    {
        object->unk20++;
        float slot = object->unk1c;
        object->unk30 = slot;
        object->unk2c = FUN_43d810(object->unk2c, slot, 0.2f);
        object->unk24 = FUN_43d810(object->unk24, object->unk28, 0.001f);
    }
    case 1:
    case 0x14:
        object->unk38->message(object->unk38, msg, 0);
        child = object->unk34;
        child->message(child, msg, 0);
        return 0;
    case 3:
        FUN_4392b0(0x2c, 0);
        FUN_45af60(object);
        mode = object->unk14;
        if (mode == 3 && object->unk18)
        {
            FUN_43dd40(0x69, 0.3f, -0.5f);
        }
        else
        {
            FUN_43dd40(0x5f, 0.3f, -0.5f);
        }
        switch (mode)
        {
        case 1:
            FUN_45b2c0(object);
            break;
        case 2:
            FUN_45b360(object);
            return 0;
        case 3:
            FUN_45b440(object);
            return 0;
        }
        break;
    }
    return 0;
}

// GLOBAL: STUNTGP_D3D 0x627ed8
char g_627ed8[0x80];

Initials *FUN_43d690(Initials *name);

// Championship table: per slot its name, sponsor, money and points, with a pulsing bar on the
// selected row.
// FUNCTION: STUNTGP_D3D 0x45af60
void FUN_45af60(Unk45a9c0 *object)
{
    float slide = (object->unk24 - 1.0f) * 640.0f;
    float x0 = slide + 40.0f;
    float x1 = slide + 600.0f;
    FUN_439450(x0, 91.0f, x1, 299.0f, 10, 0x6e, 0x40);
    FUN_439380(x0, 91.0f, x1, 299.0f, 13, 2, 0, 0.0f);
    int selected = object->unk1c;
    float y = 111.0f;
    float x = x0 + 100.0f - 12.0f;
    float xi = x + 4.0f;
    MenuSlot160 *slot = g_menuState.unk0f1c;
    for (int i = 0; i < 8; i++, slot++)
    {
        D3DCOLOR color = i != selected ? 0xffffffff : 0xffff8080;
        FUN_438be0(xi, y, 12, 4, i + 0x2f, 1.5f, color, 6);
        if (!slot->unk000)
        {
            FUN_438be0(x + 16.0f, y, 12, 4, 0x37, 1.5f, color, 2);
        }
        else
        {
            FUN_438960(x + 16.0f, y, 12, 0, 4, FUN_43d690(&slot->name)->c, 1.5f, color, 2);
            // STRING: STUNTGP_D3D 0x4890d4
            sprintf(g_627ed8, "(%s)", FUN_441170(slot->sponsor + 0x1ea));
            FUN_438960(x + 64.0f, y, 12, 0, 4, g_627ed8, 1.5f, color, 2);
            FUN_438be0(x + 192.0f - 24.0f, y, 12, 4, 0x1b, 1.5f, color, 3);
            FUN_438a20(x + 264.0f, y, 12, 0, 4, g_627cd8[0][i], 1.5f, color, 6, 14.0f);
            FUN_438be0(x + 352.0f - 16.0f, y, 12, 4, 0x39, 1.5f, color, 6);
            FUN_438a20(x + 376.0f, y, 12, 0, 4, g_627cd8[1][i], 1.5f, color, 6, 14.0f);
            FUN_438be0(x + 396.0f, y, 12, 4, 0x38, 1.5f, color, 2);
            // STRING: STUNTGP_D3D 0x4890dc
            sprintf(g_627ed8, "%d", slot->unk008);
            FUN_438960(x + 460.0f, y, 12, 0, 4, g_627ed8, 1.5f, color, 6);
        }
        y += 24.0f;
    }
    int pulse = (object->unk20 - 32) & 0x3f;
    float cy = object->unk2c * 24.0f + 111.0f;
    if (pulse >= 32)
    {
        pulse = 64 - pulse;
    }
    FUN_439380(x0, cy - 16.0f, x1, cy + 16.0f, 11, 4, 0x400, (pulse + 32) * 0.015625f);
}

// Prompt box under the slot list; the text depends on whether the slot is in use.
// FUNCTION: STUNTGP_D3D 0x45b2c0
void FUN_45b2c0(Unk45a9c0 *object)
{
    FUN_439450(40.0f, 332.0f, 600.0f, 432.0f, 10, 0x6f, 0x40);
    FUN_439380(40.0f, 332.0f, 600.0f, 432.0f, 13, 2, 0x100, 0.0f);
    FUN_438ba0(320.0f, 382.0f, 12, 4, (g_menuState.unk0f1c[object->unk1c].unk000 != 0) + 0x3c, 1.5f, 0xffffffff,
               0x803);
}

// Yes/no question box beside the slot list, with its menu in unk34.
// FUNCTION: STUNTGP_D3D 0x45b360
void FUN_45b360(Unk45a9c0 *object)
{
    FUN_439450(40.0f, 332.0f, 408.0f, 432.0f, 10, 0x6f, 0x40);
    FUN_439380(40.0f, 332.0f, 408.0f, 432.0f, 13, 2, 0x100, 0.0f);
    FUN_438ba0(224.0f, 382.0f, 12, 4, 0x3a, 1.5f, 0xffffffff, 0x803);
    FUN_439450(440.0f, 332.0f, 600.0f, 432.0f, 10, 0x6e, 0x40);
    FUN_439380(440.0f, 332.0f, 600.0f, 432.0f, 13, 2, 0, 0.0f);
    object->unk34->message(object->unk34, 3, 0);
}

// As FUN_45b360 for the second question, with its menu in unk38.
// FUNCTION: STUNTGP_D3D 0x45b440
void FUN_45b440(Unk45a9c0 *object)
{
    FUN_439450(40.0f, 332.0f, 408.0f, 432.0f, 10, 0x6f, 0x40);
    FUN_439380(40.0f, 332.0f, 408.0f, 432.0f, 13, 2, 0x100, 0.0f);
    FUN_438ba0(224.0f, 382.0f, 12, 4, 0x3b, 1.5f, 0xffffffff, 0x803);
    FUN_439450(440.0f, 332.0f, 600.0f, 432.0f, 10, 0x6e, 0x40);
    FUN_439380(440.0f, 332.0f, 600.0f, 432.0f, 13, 2, 0, 0.0f);
    object->unk38->message(object->unk38, 3, 0);
}

// FUNCTION: STUNTGP_D3D 0x45b520
int FUN_45b520(Unk45b520 *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x489158
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_489120))
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
    object->unk18 = 0;
    return 1;
}

// The original recomputes the sin of object->unk18 after each FUN_438710 call; /Oa would reuse it.
#pragma optimize("a", off)
// FUNCTION: STUNTGP_D3D 0x45b5d0
int FUN_45b5d0(Unk45b520 *object, int msg, int arg)
{
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(g_menuState.unk45d4, 0.3f, -0.5f);
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        object->child->message(object->child, msg, 0);
        FUN_43eef0();
        return 0;
    case 0x11:
        FUN_440880(9);
        return 0;
    case 2:
    {
        object->child->message(object->child, msg, 0);
        float phase = g_menuState.unk45e0 + object->unk18;
        object->unk18 = phase - (int)phase;
        return 0;
    }
    case 3:
        object->child->message(object->child, msg, 0);
        if (g_menuState.unk45d8 && !g_menuState.unk45dc)
        {
            FUN_438710(320.0f, 240.0f - (float)sin(object->unk18 * 3.1415927f) * g_menuState.unk45e4, 0xc,
                       g_menuState.unk45d8, 1.0f, 3);
        }
        if (g_menuState.unk45d8 && g_menuState.unk45dc)
        {
            FUN_438710(193.0f, 240.0f - (float)sin(object->unk18 * 3.1415927f) * g_menuState.unk45e4, 0xc,
                       g_menuState.unk45d8, 1.0f, 3);
            FUN_438710(448.0f, 240.0f - (float)sin(object->unk18 * 3.1415927f) * g_menuState.unk45e4, 0xc,
                       g_menuState.unk45dc, 1.0f, 3);
        }
        break;
    }
    return 0;
}
#pragma optimize("", on)

// FUNCTION: STUNTGP_D3D 0x45b7a0
int FUN_45b7a0(Unk45b7a0 *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x4891e0
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4891a8))
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
    g_menuState.unk438c = 0;
    if (!g_menuState.unk4390)
    {
        g_menuState.unk4390 = 1;
    }
    object->unk18 = object->unk1c = g_menuState.unk4390 - 1.0f;
    return 1;
}

// Sponsor page: six panels scrolled to the chosen sponsor in unk4390.
struct Unk45b870
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    float unk18;       // 0x18, scroll position
    float unk1c;       // 0x1c, target
};

struct Unk45ba30;
void FUN_45ba30(Unk45ba30 *object);

// Sponsor name, frame and fee.
// FUNCTION: STUNTGP_D3D 0x45bab0
void FUN_45bab0(Unk45b870 *object)
{
    FUN_438ba0(224.0f, 336.0f, 12, 4, g_menuState.unk4390 + 0x1f1, 1.5f, 0xffffffff, 0x803);
    FUN_439450(440.0f, 288.0f, 600.0f, 324.0f, 10, 0x6f, 0x40);
    FUN_439380(440.0f, 288.0f, 600.0f, 324.0f, 13, 2, 0, 0.0f);
    FUN_438be0(456.0f, 306.0f, 12, 4, 0x1b, 1.5f, 0xffffffff, 3);
    FUN_438a20(584.0f, 306.0f, 12, 0, 4, FUN_43d5f0(g_menuState.sponsors[g_menuState.unk4390].unk00, 0), 1.5f,
               0xffffffff, 0x806, 14.0f);
}

// FUNCTION: STUNTGP_D3D 0x45b870
int FUN_45b870(Unk45b870 *object, int msg, int arg)
{
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(4);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x6b, 0.3f, -0.5f);
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        object->child->message(object->child, msg, 0);
        FUN_43eef0();
        return 0;
    case 0xd:
        if (g_menuState.unk4390 > 1)
        {
            g_menuState.unk4390--;
            FUN_440890(msg);
            FUN_440880(0x14);
            return 0;
        }
        break;
    case 0xe:
        if (g_menuState.unk4390 < 6)
        {
            g_menuState.unk4390++;
            FUN_440890(msg);
            FUN_440880(0x14);
            return 0;
        }
        break;
    case 0x11:
        if (FUN_43eef0())
        {
            g_menuState.unk438c = 1;
            FUN_440890(msg);
            return 0;
        }
        break;
    case 2:
    {
        object->child->message(object->child, msg, 0);
        float target = g_menuState.unk4390 - 1.0f;
        object->unk1c = target;
        float scroll = FUN_43d810(object->unk18, target, 0.001f);
        object->unk18 = scroll;
        FUN_43df60(6.0f, 1.0f, scroll, 0.0f, 0.0f, 0.0f);
        return 0;
    }
    case 3:
        FUN_45ba30((Unk45ba30 *)object);
        FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
        FUN_4392b0(0x2a, 0);
        object->child->message(object->child, msg, 0);
        FUN_45bab0(object);
        FUN_439340(0x2b);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45bbb0
void FUN_45bbb0(PoolObject *object)
{
}

// FUNCTION: STUNTGP_D3D 0x45bbc0
int FUN_45bbc0(MenuObject *object, int msg, int arg)
{
    char text[0x100];
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x112a43);
        FUN_43dd40(0x60, 0.5f, 0.3f);
        return 0;
    case 0x11:
        if (FUN_43eef0())
        {
            FUN_440890(msg);
        }
        return 0;
    case 0xb:
        if ((object->unk14 -= 10) <= 0)
        {
            object->unk14 = 1;
        }
        FUN_440890(msg);
        return 0;
    case 0xc:
        if ((object->unk14 += 10) >= 0x183)
        {
            object->unk14 = 0x182;
        }
        FUN_440890(msg);
        return 0;
    case 0xd:
        if (--object->unk14 <= 0)
        {
            object->unk14 = 1;
        }
        FUN_440890(msg);
        return 0;
    case 0xe:
        if (++object->unk14 >= 0x183)
        {
            object->unk14 = 0x182;
        }
        FUN_440890(msg);
        return 0;
    case 3:
        int bmp = object->unk14;
        FUN_438710(320.0f, 240.0f, 0xd, bmp, 1.0f, 3);
        // STRING: STUNTGP_D3D 0x4891f8
        sprintf(text, "bmp %d of %d\n", bmp, 0x182);
        FUN_438960(320.0f, 416.0f, 2, 0, 4, text, 1.25f, 0xffffffff, 1);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45bd70
int FUN_45bd70(MenuHolder *object, int arg)
{
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x489280
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_489248))
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
    g_menuState.unk45e8 = 0;
    return 1;
}

void FUN_45be20(MenuLine *lines, int count, float x, float y, float width, float spacing);

// Message page: the lines in g_menuState.unk45f0 under an OK menu.
// FUNCTION: STUNTGP_D3D 0x45bf40
int FUN_45bf40(MenuHolder *object, int msg, int arg)
{
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(g_menuState.unk45ec, 0.3f, -0.5f);
    case 2:
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x11:
        FUN_440890(msg);
        g_menuState.unk45e8 = 1;
        FUN_43eef0();
        return 0;
    case 0x10:
        object->child->message(object->child, msg, 0);
        FUN_43eef0();
        return 0;
    case 3:
        object->child->message(object->child, msg, 0);
        FUN_45be20(g_menuState.unk45f0, g_menuState.unk4690, 320.0f, 240.0f, 400.0f, 10.0f);
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45c070
void FUN_45c070(PoolObject *object)
{
}

// Attract screen; unk18 is the slide position, its fraction the slide in progress.
struct Unk45c080
{
    DWORD unk00[5]; // 0x00
    int unk14;      // 0x14, frames shown
    float unk18;    // 0x18
    float unk1c;    // 0x1c
    float unk20;    // 0x20
};

// GLOBAL: STUNTGP_D3D 0x627fdc
int g_627fdc;

void FUN_43b0e0(MenuRace *race);
void FUN_43dd90(int player);
void FUN_45c050(MenuObject *object);
void FUN_45c320(float x, float y);
void FUN_45c3d0(float x, float y);
void FUN_45c480();
void FUN_438ff0(float x, float y, int layer, int font, int textId, float size, D3DCOLOR color, int style, int row,
                float scale, DWORD flags, int width, float fade);

// Attract screen: slides through the title pictures and starts a demo race after a while.
// FUNCTION: STUNTGP_D3D 0x45c080
int FUN_45c080(PoolObject *base, int msg, int arg)
{
    Unk45c080 *object = (Unk45c080 *)base;
    D3DCOLOR color = 0xffffffff;
    switch (msg)
    {
    case 0xf:
    case 0x10:
        FUN_43dfa0(2, 2);
        FUN_440890(0x10);
        g_menuState.unk4244 = arg;
        FUN_43dd90(arg);
        return 0;
    case 0x13:
        FUN_45c050((MenuObject *)object);
        FUN_4400a0(1);
        FUN_43dd10(0x112a43);
        FUN_43dd40(0x60, 0.5f, 0.3f);
        object->unk20 = 0.0f;
        return 0;
    case 0x14:
        object->unk20 = 1.0f;
        return 0;
    case 2:
        object->unk1c = FUN_43d810(object->unk1c, object->unk20, 0.001f);
        if (object->unk14 >= 600)
        {
            object->unk18 += 0.03f;
        }
        object->unk14++;
        return 0;
    case 1:
        if (object->unk14 >= 0xe10)
        {
            FUN_43b0e0(&g_menuState.races[g_627fdc]);
            object->unk14 = 0;
            g_627fdc = (g_627fdc + 1) % g_menuState.numberOfRaces;
            FUN_43dfa0(0, 0x19);
            return 0;
        }
        break;
    case 3:
    {
        int frame = (int)object->unk18;
        float x = 111.5f;
        float t = object->unk18 - frame;
        if ((frame & 7) == 7)
        {
            x = 111.5f - t * 640.0f;
        }
        float y = 84.0f - ((float)sin(t * 3.1415927f) * 30.0f + object->unk1c * 480.0f);
        FUN_45c320(x, y);
        float x2 = x + 640.0f;
        FUN_45c320(x2, y);
        FUN_45c3d0(x, y);
        FUN_45c3d0(x2, y);
        if ((frame & 7) == 6)
        {
            t *= 480.0f;
            FUN_438190(0.0f, t, 640.0f, t + 16.0f);
            FUN_45c3d0(x, y);
            FUN_45c3d0(x2, y);
            FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
        }
        if ((frame & 1) == 1)
        {
            color = 0xffff6060;
        }
        FUN_438ff0(320.0f, 440.0f, 2, 4, 0x28, 1.25f, color, 4, 0, 1.0f, 0x41, 400, 0.0f);
        FUN_45c480();
        break;
    }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45c4b0
int FUN_45c4b0(Unk45c4b0 *object, int arg)
{
    object->unk1c = 0;
    FUN_4375a0(g_menuState.unk440c, g_menuState.unk4408);
    int track = g_menuState.unk4474;
    if (track)
    {
        for (int i = 0; i < g_menuState.unk4408; i++)
        {
            if (g_menuState.unk440c[i] == track)
            {
                object->unk1c = i;
                break;
            }
        }
    }
    object->unk28 = 0;
    object->unk18 = g_menuState.unk4238;
    object->unk2c = 0;
    object->unk24 = object->unk20 = object->unk1c;
    g_menuState.unk4404 = 0;
    switch (g_menuState.unk4478)
    {
    default:
        g_menuState.unk4478 = 3;
    case 3:
        object->unk30 = 0;
        break;
    case 9:
        object->unk30 = 2;
        break;
    case 5:
        object->unk30 = 1;
        break;
    }
    switch (g_menuState.unk4230)
    {
    case 2:
        g_4894e0.items = g_4892a0;
        break;
    case 3:
        g_4894e0.items = g_489340;
        break;
    case 6:
        g_4894e0.items = g_489440;
        break;
    case 7:
        g_4894e0.items = g_4894a0;
        break;
    case 1:
        g_4894e0.items = g_4893c0;
        break;
    case 5:
        g_4894e0.items = g_489400;
        break;
    }
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x489518
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4894e0))
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
    return 1;
}

// PageSelectTrack as its handler sees it; unk28 is the arrow animation phase.
struct Unk45c6a0
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18
    int unk1c;         // 0x1c, selected track
    float unk20;       // 0x20, scroll position
    float unk24;       // 0x24, scroll target
    float unk28;       // 0x28
    int unk2c;         // 0x2c, set while a record ghost is being chosen
    int unk30;         // 0x30
};

struct Unk45d130;
void FUN_45c670(Unk45c670 *object);
void FUN_45cc40(int track);
void FUN_45cc70(Unk45c4b0 *object);
void FUN_45d130(Unk45d130 *object, float x, float y);

// FUNCTION: STUNTGP_D3D 0x45c6a0
int FUN_45c6a0(Unk45c6a0 *object, int msg, int arg)
{
    PoolObject *child;
    int sel;
    int count = g_menuState.unk4408;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(5);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x60, -0.3f, -0.5f);
    case 0xb:
    case 0xc:
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0xd:
        if (object->unk1c >= count)
        {
            object->unk1c = count - 1;
        }
        if (object->unk1c > 0)
        {
            object->unk1c--;
            FUN_440890(msg);
            FUN_440880(0x14);
            return 0;
        }
        break;
    case 0xe:
        if (object->unk1c < count - 1)
        {
            object->unk1c++;
            FUN_440890(msg);
            FUN_440880(0x14);
            return 0;
        }
        break;
    case 0x11:
        g_menuState.unk4404 = 1;
        FUN_440890(msg);
        FUN_43eef0();
        return 0;
    case 0x10:
        child = object->child;
        child->message(child, msg, 0);
        sel = object->unk1c;
        g_menuState.unk4474 = g_menuState.unk440c[sel];
        switch (g_menuState.unk4230)
        {
        case 2:
            switch (child->message(child, 0x1a, 0))
            {
            case 0:
                FUN_45c670((Unk45c670 *)object);
                FUN_43eef0();
                return 0;
            case 1:
                if (++object->unk30 > 2)
                {
                    object->unk30 = 0;
                    return 0;
                }
                break;
            case 2:
                if (++g_menuState.unk4480 > 2)
                {
                    g_menuState.unk4480 = 0;
                    return 0;
                }
                break;
            case 3:
                if (++g_menuState.unk447c > 5)
                {
                    g_menuState.unk447c = 0;
                    return 0;
                }
                break;
            }
            break;
        case 3:
            switch (child->message(child, 0x1a, 0))
            {
            case 0:
                FUN_45c670((Unk45c670 *)object);
                FUN_43eef0();
                return 0;
            case 2:
                g_menuState.unk46bc = 0;
                g_menuState.unk46c0 = 0;
                g_menuState.unk46c8 = 5;
                g_menuState.unk46c4 = 0;
                g_menuState.unk46cc = g_menuState.unk440c[sel];
                g_menuState.unk46d0 = (int)g_menuState.unk46e8;
                g_menuState.unk46d4 = FUN_437da0(g_menuState.unk4474);
                FUN_43dfa0(0, 0x1b);
                return 0;
            case 1:
                g_menuState.unk46bc = 0;
                g_menuState.unk46c0 = 0;
                g_menuState.unk46c8 = 4;
                g_menuState.unk46c4 = 0;
                g_menuState.unk46cc = g_menuState.unk440c[sel];
                g_menuState.unk46d0 = (int)(g_menuState.unk4718 + 0x7500);
                g_menuState.unk46d4 = FUN_437da0(g_menuState.unk4474);
                FUN_43dfa0(0, 0x1b);
                object->unk2c = 1;
                return 0;
            }
            break;
        case 6:
            switch (child->message(child, 0x1a, 0))
            {
            case 0:
                FUN_45c670((Unk45c670 *)object);
                FUN_43eef0();
                return 0;
            case 1:
                if (++object->unk30 > 2)
                {
                    object->unk30 = 0;
                    return 0;
                }
                break;
            }
            break;
        case 1:
        case 5:
        case 7:
            if (!child->message(child, 0x1a, 0))
            {
                FUN_45c670((Unk45c670 *)object);
                FUN_43eef0();
                return 0;
            }
            break;
        }
        break;
    case 2:
    {
        object->child->message(object->child, msg, 0);
        sel = object->unk1c;
        float target = sel >= count ? count - 1 : sel;
        object->unk24 = target;
        object->unk20 = FUN_43d810(object->unk20, target, 0.001f);
        float phase = object->unk28 + 0.03f;
        object->unk28 = phase - (int)phase;
        if (count > 1)
        {
            FUN_43df60(count, 1.0f, sel >= count ? count - 1 : sel, 0.0f, 0.0f, 0.0f);
            return 0;
        }
        FUN_43df60(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        return 0;
    }
    case 1:
        if (object->unk2c)
        {
            object->unk2c = 0;
            if (g_menuState.unk46e0)
            {
                g_menuState.unk46e0 = 0;
                object->child->message(object->child, 0x1c, 0);
                memcpy(g_menuState.unk46e8, g_menuState.unk4718 + 0x7500, 0x7530);
                g_menuState.unk46e4 = g_menuState.unk46cc;
                return 0;
            }
        }
        break;
    case 3:
        sel = object->unk1c;
        FUN_45cba0(object->unk20, sel);
        FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
        if (g_menuState.unk4408 == 1)
        {
            FUN_4392b0(0x1b7, 0);
        }
        else
        {
            FUN_4392b0(0x1b6, 0);
        }
        FUN_45cc40(g_menuState.unk440c[sel]);
        FUN_45cc70((Unk45c4b0 *)object);
        object->child->message(object->child, msg, 0);
        if (g_menuState.unk423c > 1)
        {
            FUN_45d130((Unk45d130 *)object, g_4894e0.x, g_4894e0.y);
        }
        break;
    }
    return 0;
}

// GLOBAL: STUNTGP_D3D 0x489530
MenuItem g_489530[4] = {
    {-1, 0xffffffff, 0xffffffff, 0x14, 0, 4, 0, 0},
    {0, 0xffc8c8ff, 0xffffffff, 0x15, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x16, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x4895b0
MenuDef g_4895b0 = {0xb, 1.0f, 0, 507.0f, 405.0f, 1.0f, 2, 1.25f, 1, 0x78, g_489530, 0};

// GLOBAL: STUNTGP_D3D 0x4895e0
MenuItem g_4895e0[3] = {
    {0, 0xffc8c8ff, 0xffffffff, 0x18, 0, 1, 0, 0},
    {1, 0xffc8c8ff, 0xffffffff, 0x19, 0, 1, 0, 0},
    {0},
};

// GLOBAL: STUNTGP_D3D 0x489640
MenuDef g_489640 = {0xb, 1.0f, 0, 507.0f, 405.0f, 1.0f, 2, 1.25f, 1, 0xa0, g_4895e0, 0};

int FUN_437920(int index);
int FUN_437930(int id, int *from, int *to);

// PageSelectTree init: the branch menu, its confirm box and the two nodes reachable from here.
// FUNCTION: STUNTGP_D3D 0x45d1a0
int FUN_45d1a0(PoolObject *base, int arg)
{
    Unk45d2e0 *object = (Unk45d2e0 *)base;
    g_627ff4++;
    object->unk28 = object->unk24 = g_menuState.unk4488;
    object->unk20 = g_menuState.unk4488;
    g_menuState.unk4484 = 0;
    object->unk1c = 0;
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x489678
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_489640))
    {
        Pool_Free(list);
        object->unk14 = NULL;
    }
    else
    {
        object->unk14 = &list->base;
    }
    object->unk14->message(object->unk14, 0x18, 0);
    list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x489684
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4895b0))
    {
        Pool_Free(list);
        object->unk18 = NULL;
    }
    else
    {
        object->unk18 = &list->base;
    }
    object->unk18->message(object->unk18, 0x18, 0);
    FUN_437930(g_menuState.unk4490[g_menuState.unk448c - 1], &object->unk2c, &object->unk30);
    object->unk34[0] = FUN_437920(object->unk2c);
    object->unk34[1] = FUN_437920(object->unk30);
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x45d2e0
void FUN_45d2e0(Unk45d2e0 *object)
{
    g_627ff4--;
    PoolObject *child = object->unk14;
    child->destroy(child);
    Pool_Free(child);
    object->unk14 = NULL;
    child = object->unk18;
    child->destroy(child);
    Pool_Free(child);
    object->unk18 = NULL;
}

void FUN_45d630(int sel, int dir);
void FUN_45da40(int index);
void FUN_45da70(Unk45d2e0 *object, int index, float pos);
void FUN_45db10(Unk4516c0 *object);
void FUN_45db50(Unk4516c0 *object);

// Node choice: pick the left or right branch out of the current node, then confirm it.
// FUNCTION: STUNTGP_D3D 0x45d320
int FUN_45d320(PoolObject *base, int msg, int arg)
{
    Unk45d2e0 *object = (Unk45d2e0 *)base;
    PoolObject *child;
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(5);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x60, -0.3f, -0.5f);
        child = object->unk14;
        child->message(child, msg, 0);
        return 0;
    case 0xd:
        if (!object->unk1c)
        {
            if (object->unk20 >= 2)
            {
                object->unk20 = 1;
            }
            if (object->unk20 > 0)
            {
                object->unk20--;
                FUN_440890(msg);
                return 0;
            }
        }
        break;
    case 0xe:
        if (!object->unk1c && object->unk20 < 1)
        {
            object->unk20++;
            FUN_440890(msg);
            return 0;
        }
        break;
    case 0xb:
    case 0xc:
        if (object->unk1c)
        {
            object->unk18->message(object->unk18, msg, 0);
            return 0;
        }
    case 0x14:
        object->unk14->message(object->unk14, msg, 0);
        return 0;
    case 0x11:
        if (!object->unk1c)
        {
            FUN_440890(msg);
            FUN_45db10((Unk4516c0 *)object);
            return 0;
        }
        FUN_45db50((Unk4516c0 *)object);
        FUN_440890(msg);
        return 0;
    case 0x10:
        if (object->unk1c)
        {
            FUN_440890(msg);
            if (object->unk18->message(object->unk18, 0x1a, 0) == 1)
            {
                FUN_45db50((Unk4516c0 *)object);
                return 0;
            }
            g_menuState.unk4484 = 1;
            FUN_43eef0();
            return 0;
        }
        if (object->unk14->message(object->unk14, 0x1a, 0))
        {
            FUN_440890(msg);
            FUN_45db10((Unk4516c0 *)object);
            return 0;
        }
    {
        int side = object->unk20;
        int node = (&object->unk2c)[side];
        g_menuState.unk00ec[g_menuState.unk4490[g_menuState.unk448c - 1] * 2 + side] = 1;
        g_menuState.unk4490[g_menuState.unk448c] = node;
        g_menuState.unk448c++;
        g_menuState.unk4488 = side;
    }
        FUN_440890(msg);
        FUN_43eef0();
        return 0;
    case 2:
    {
        object->unk14->message(object->unk14, msg, 0);
        object->unk18->message(object->unk18, msg, 0);
        int side = object->unk20;
        float shown = side >= 2 ? 1 : side;
        object->unk28 = shown;
        object->unk24 = FUN_43d810(object->unk24, shown, 0.001f);
        FUN_43df60(2.0f, 1.0f, side >= 2 ? 1 : side, 0.0f, 0.0f, 0.0f);
        return 0;
    }
    case 3:
    {
        FUN_45da70(object, object->unk20, object->unk24);
        FUN_438190(0.0f, 0.0f, 640.0f, 480.0f);
        FUN_4392b0(0x1f9, 0);
        object->unk14->message(object->unk14, msg, 0);
        object->unk18->message(object->unk18, msg, 0);
        int side = object->unk20;
        int node = (&object->unk2c)[side];
        FUN_45da40(node);
        FUN_45d630(node, side ? 1 : -1);
        break;
    }
    }
    return 0;
}

// GLOBAL: STUNTGP_D3D 0x627fe0
char g_627fe0[0x13];

int FUN_43dd60();
int FUN_4371c0(int track, int mode);

// Node map: a pyramid of rows of 6 down to 3 nodes, with the links between visited nodes and the
// cursor arrows on the current one.
// FUNCTION: STUNTGP_D3D 0x45d630
void FUN_45d630(int sel, int dir)
{
    int blink = FUN_43dd60() & 0x10;
    memset(g_627fe0, 0, sizeof(g_627fe0));
    for (int i = 0; i < g_menuState.unk448c; i++)
    {
        g_627fe0[g_menuState.unk4490[i]] = 1;
    }
    int current = g_menuState.unk4490[g_menuState.unk448c - 1];
    FUN_439450(49.0f, 366.0f, 391.0f, 444.0f, 10, 0x6f, 0x40);
    FUN_439380(49.0f, 366.0f, 391.0f, 444.0f, 13, 0, 0, 0.0f);
    int index = 1;
    float y = 382.0f;
    int textId = 3;
    for (int count = 6; count >= 3; count--)
    {
        for (int column = 0; column < count; column++)
        {
            float x = column - (count - 1) * 0.5f;
            int sprite;
            if (FUN_4371c0(FUN_437920(index), g_menuState.unk4230))
            {
                if (x <= -1.0f)
                {
                    sprite = 0x41;
                }
                else if (x >= 1.0f)
                {
                    sprite = 0x43;
                }
                else
                {
                    sprite = 0x42;
                }
            }
            else
            {
                if (x <= -1.0f)
                {
                    sprite = 0x44;
                }
                else if (x >= 1.0f)
                {
                    sprite = 0x46;
                }
                else
                {
                    sprite = 0x45;
                }
            }
            if (column == count - 1)
            {
                FUN_438be0(x * 56.0f + 232.0f, y, 12, 2, textId, 0.8f, 0xffffffff, 2);
            }
            float px = x * 56.0f + 220.0f;
            FUN_438710(px, y, 12, sprite, 1.0f, 0x103);
            if (index == sel && blink)
            {
                FUN_438710(px, y, 12, 0x47, 1.0f, 0x103);
                if (dir < 0)
                {
                    FUN_438710(x * 56.0f + 234.0f, y + 8.0f, 12, 0x4a, 1.0f, 0x103);
                }
                if (dir > 0)
                {
                    FUN_438710(px - 14.0f, y + 8.0f, 12, 0x4a, 1.0f, 0x113);
                }
            }
            if (g_627fe0[index] && index > 6)
            {
                int from;
                int to;
                FUN_437930(index, &from, &to);
                if (g_627fe0[from])
                {
                    FUN_438710(px - 14.0f, y - 8.0f, 12, 0x4b, 1.0f, 0x103);
                }
                if (g_627fe0[to])
                {
                    FUN_438710(x * 56.0f + 234.0f, y - 8.0f, 12, 0x4b, 1.0f, 0x113);
                }
            }
            if (g_menuState.unk00ec[index * 2] && (index != current || !blink || dir >= 0))
            {
                FUN_438710(px - 14.0f, y - 8.0f, 12, 0x4c, 1.0f, 0x103);
            }
            if (g_menuState.unk00ec[index * 2 + 1] && (index != current || !blink || dir <= 0))
            {
                FUN_438710(x * 56.0f + 234.0f, y - 8.0f, 12, 0x4c, 1.0f, 0x113);
            }
            index++;
        }
        y += 16.0f;
        textId++;
    }
}

// FUNCTION: STUNTGP_D3D 0x45db80
int FUN_45db80(Unk45db80 *object, int arg)
{
    object->unk18 = 0;
    object->unk1c = 0;
    object->unk20 = 0;
    MenuList *list = (MenuList *)Pool_Alloc(sizeof(MenuList));
    memset(list, 0, sizeof(MenuList));
    *(PoolClass *)&list->base.destroy = g_menuListClass;
    list->base.type = 0x29;
    // STRING: STUNTGP_D3D 0x489708
    list->base.name = "MenuText";
    list->base.unk08 = 0;
    if (!FUN_43c860(list, &g_4896d0))
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
    FUN_437870();
    for (g_627ff8 = 0; g_627ff8 < 0x3f; g_627ff8++)
    {
        if (!FUN_45dc40(&g_627ffc[g_627ff8]))
        {
            break;
        }
    }
    return 1;
}

// PageUnlock while it runs: unk18 is the shown unlock, unk1c the scroll towards it.
struct Unk45de00
{
    DWORD unk00[5];    // 0x00
    PoolObject *child; // 0x14
    int unk18;         // 0x18
    float unk1c;       // 0x1c
    float unk20;       // 0x20
};

float FUN_438a60(const char *text, float size);
float FUN_438ab0(float x, float y, int layer, int style, char *text, float size, D3DCOLOR color, DWORD flags);

// The unlock pictures side by side with their captions, scrolled by unk1c.
// FUNCTION: STUNTGP_D3D 0x45dfa0
void FUN_45dfa0(Unk45de00 *object)
{
    for (int i = 0; i < g_627ff8; i++)
    {
        Unlock *unlock = &g_627ffc[i];
        float x = (i - object->unk1c) * 640.0f + 320.0f;
        FUN_438710(x, 190.0f, 12, unlock->id, 1.0f, 3);
        if (unlock->text[0])
        {
            float height = FUN_438a60(unlock->text, 1.25f) + 20.0f;
            float left = x - 290.0f;
            float right = x + 290.0f;
            float top = 348.0f - height * 0.5f;
            float bottom = height * 0.5f + 352.0f;
            FUN_439450(left, top, right, bottom, 10, 0x6f, 0x40);
            FUN_439380(left, top, right, bottom, 13, 2, 0, 0.0f);
            FUN_438ab0(x, 348.0f, 12, 4, unlock->text, 1.25f, 0xffffffff, 3);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45de00
int FUN_45de00(Unk45de00 *object, int msg, int arg)
{
    switch (msg)
    {
    case 0x13:
        FUN_4400a0(1);
        FUN_43dd10(0x114311);
        FUN_43dd40(0x5c, -0.4f, 0.3f);
    case 0x14:
        object->child->message(object->child, msg, 0);
        return 0;
    case 0x10:
        if (object->unk18 < g_627ff8 - 1)
        {
            object->unk18++;
            FUN_440890(msg);
            FUN_440880(0x14);
            return 0;
        }
        memcpy(g_menuState.unlockedSaved, g_menuState.unlocked, sizeof(g_menuState.unlocked));
        object->child->message(object->child, msg, 0);
        FUN_43eef0();
        return 0;
    case 1:
        if (!g_627ff8)
        {
            FUN_43eef0();
            return 0;
        }
        break;
    case 2:
    {
        object->child->message(object->child, msg, 0);
        float target = object->unk18;
        object->unk20 = target;
        object->unk1c = FUN_43d810(object->unk1c, target, 0.001f);
        return 0;
    }
    case 3:
        g_4896d0.items[0].text = object->unk18 < g_627ff8 - 1 ? 0x1a : 0x17;
        object->child->message(object->child, msg, 0);
        FUN_4392b0(0x1fe, 0);
        if (g_627ff8)
        {
            FUN_45dfa0(object);
        }
        break;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45dc40
int FUN_45dc40(Unlock *unlock)
{
    int i;
    unlock->text[0] = 0;
    unlock->id = 0;
    for (i = 1; i < 0x19; i++)
    {
        if (g_menuState.unlocked[0x18 + i] == 2)
        {
            g_menuState.unlocked[0x18 + i] = 1;
            unlock->id = i + 0xc1;
            switch (FUN_437360(i))
            {
            case 1:
            case 3:
                sprintf(unlock->text, FUN_441170(0x27a), FUN_441170(i + 0x1b7));
                return 1;
            case 2:
            case 4:
                sprintf(unlock->text, FUN_441170(0x27b), FUN_441170(i + 0x1b7));
                return 1;
            default:
                strcpy(unlock->text, FUN_441170(i + 0x1b7));
                return 1;
            }
        }
    }
    for (i = 1; i < 0x16; i++)
    {
        if (g_menuState.unlocked[i] == 2)
        {
            g_menuState.unlocked[i] = 1;
            unlock->id = i + 0xac;
            switch (i)
            {
            case 1:
            case 2:
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
            case 13:
            case 14:
            case 15:
            case 17:
            case 18:
            case 21:
                sprintf(unlock->text, FUN_441170(0x278), FUN_441170(i + 0x18a));
                break;
            case 16:
            case 19:
                sprintf(unlock->text, FUN_441170(0x277), FUN_441170(i + 0x18a));
                break;
            case 20:
                sprintf(unlock->text, FUN_441170(0x279), FUN_441170(i + 0x18a));
                break;
            }
            return 1;
        }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x457a40
int FUN_457a40(Unk457e70 *object)
{
    int changed = 0;
    int cards = FUN_457be0();
    object->unk1fc = 0;
    memset(object->entries, 0, sizeof(object->entries));
    for (int i = 0; i < 8; i++)
    {
        object->entries[i].unk08 = 0;
    }
    object->count = 0;
    for (int card = 0; card < cards; card++)
    {
        int freeSpace;
        int state = FUN_457bf0(card, &freeSpace);
        if (state != object->unk044[card])
        {
            changed = 1;
        }
        if (state)
        {
            object->unk044[card] = state;
            object->entries[object->count].id = card;
            object->entries[object->count].unk08 = state;
            object->entries[object->count].unk04 = freeSpace;
            object->entries[object->count].name = FUN_441170(card + 0x255);
            if (object->entries[object->count].unk08 == 5)
            {
                switch (g_menuState.unk46c8)
                {
                case 1:
                case 2:
                case 3:
                    object->unk1fc++;
                    break;
                case 4:
                case 5:
                    if (FUN_440660(&g_627b54, sizeof(g_627b54), g_menuState.unk46cc))
                    {
                        object->entries[object->count].unk08 = 1;
                    }
                    else
                    {
                        // STRING: STUNTGP_D3D 0x488ca4
                        sprintf(object->entries[object->count].text, "%s-%s", g_627b54.name, FUN_43d550(g_627b54.frames));
                    }
                    break;
                }
            }
            object->count++;
        }
    }
    if (object->unk20 >= object->count)
    {
        object->unk20 = object->count - 1;
    }
    if (object->unk20 < 0)
    {
        object->unk20 = 0;
    }
    return changed;
}

// FUNCTION: STUNTGP_D3D 0x457be0
int FUN_457be0()
{
    return FUN_440160();
}

// FUNCTION: STUNTGP_D3D 0x457cf0
int FUN_457cf0(Unk457e70 *object, int mode)
{
    int index = -1;
    int count = object->count;
    int i;
    switch (g_menuState.unk46c8)
    {
    case 1:
    case 2:
    case 3:
        index = FUN_457e70(object, g_menuState.unk46d8);
        if (index >= 0)
        {
            return index;
        }
        break;
    case 4:
    case 5:
        index = FUN_457e70(object, g_menuState.unk46dc);
        if (index >= 0)
        {
            return index;
        }
        break;
    }
    switch (g_menuState.unk46c8)
    {
    case 3:
    case 5:
        if (g_menuState.unk46bc)
        {
            g_menuState.unk46bc = 0;
        }
        break;
    }
    switch (mode)
    {
    case 1:
        for (i = 0; i < count && index < 0; i++)
        {
            if (object->entries[i].unk08 == 5)
            {
                index = i;
            }
        }
        for (i = 0; i < count && index < 0; i++)
        {
            if (object->entries[i].unk08 == 4)
            {
                index = i;
            }
        }
        for (i = 0; i < count && index < 0; i++)
        {
            if (object->entries[i].unk08 == 2)
            {
                index = i;
            }
        }
        break;
    case 2:
        for (i = 0; i < count && index < 0; i++)
        {
            if (object->entries[i].unk08 == 5)
            {
                index = i;
            }
        }
        break;
    case 3:
        for (i = 0; i < count && index < 0; i++)
        {
            if (object->entries[i].unk08 == 4)
            {
                index = i;
            }
        }
        for (i = 0; i < count && index < 0; i++)
        {
            if (object->entries[i].unk08 == 2)
            {
                index = i;
            }
        }
        for (i = 0; i < count && index < 0; i++)
        {
            if (object->entries[i].unk08 == 5)
            {
                index = i;
            }
        }
        break;
    }
    if (index < 0)
    {
        index = 0;
    }
    return index;
}

// FUNCTION: STUNTGP_D3D 0x455af0
void FUN_455af0(PoolObject *object)
{
    for (int player = 1; player < 5; player++)
    {
        if (FUN_455b90(player) && !FUN_43dd70())
        {
            if (FUN_436fd0(player, 3))
            {
                FUN_455be0(player, -1);
            }
            if (FUN_436fd0(player, 4))
            {
                FUN_455be0(player, 1);
            }
            if (FUN_436fd0(player, 1))
            {
                FUN_455c20(player, -1);
            }
            if (FUN_436fd0(player, 2))
            {
                FUN_455c20(player, 1);
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x452070
void FUN_452070(int id, float x, float y)
{
    x -= (int)x;
    if (x >= 0.5f)
    {
        x -= 1.0f;
    }
    y -= (int)y;
    if (y >= 0.5f)
    {
        y -= 1.0f;
    }
    x = x * -1280.0f - 35.0f;
    y = y * -600.0f + 80.0f;
    FUN_438710(x, y, 0x11, id + 0x109, 1.0f, 0);
    FUN_438710(x + 255.0f, y, 0x11, id + 0x11e, 1.0f, 0);
}

// FUNCTION: STUNTGP_D3D 0x458d50
void FUN_458d50(Unk457e70 *object, int mode, int card)
{
    switch (mode)
    {
    case 1:
        FUN_4402f0(card);
        object->unk1f0 = FUN_440180();
        break;
    case 2:
        FUN_4402f0(card);
        object->unk1f0 = FUN_458e50();
        break;
    case 3:
        FUN_4402f0(card);
        object->unk1f0 = FUN_458eb0();
        break;
    case 4:
        FUN_4402f0(card);
        object->unk1f0 = FUN_458e10();
        break;
    case 5:
        FUN_4402f0(card);
        object->unk1f0 = FUN_458e30();
        break;
    case 6:
        object->unk1f0 = 0;
        break;
    }
    if (object->unk1ec != 6)
    {
        Sleep(500);
    }
}

// FUNCTION: STUNTGP_D3D 0x45cba0
void FUN_45cba0(float pos, int index)
{
    pos -= (int)pos;
    if (pos >= 0.5f)
    {
        pos -= 1.0f;
    }
    pos = pos * -1280.0f - 35.0f;
    FUN_438710(pos, 82.0f, 0x11, g_menuState.unk440c[index] + 0xd9, 1.0f, 0);
    FUN_438710(pos + 255.0f, 82.0f, 0x11, g_menuState.unk440c[index] + 0xf1, 1.0f, 0);
}

// FUNCTION: STUNTGP_D3D 0x45da70
void FUN_45da70(Unk45d2e0 *object, int index, float pos)
{
    pos -= (int)pos;
    if (pos >= 0.5f)
    {
        pos -= 1.0f;
    }
    pos = pos * -1280.0f - 35.0f;
    int node = object->unk34[index];
    FUN_438710(pos, 82.0f, 0x11, node + 0xd9, 1.0f, 0);
    FUN_438710(pos + 255.0f, 82.0f, 0x11, node + 0xf1, 1.0f, 0);
}

// FUNCTION: STUNTGP_D3D 0x45c320
void FUN_45c320(float x, float y)
{
    FUN_438710(x, y, 0xd, 0x21, 1.0f, 0x200);
    FUN_438710(g_489290 + x, y, 0xd, 0x22, 1.0f, 0x200);
    FUN_438710(x, g_489294 + y, 0xd, 0x23, 1.0f, 0x200);
    FUN_438710(g_489290 + x, g_489294 + y, 0xd, 0x24, 1.0f, 0x200);
}

// FUNCTION: STUNTGP_D3D 0x45c3d0
void FUN_45c3d0(float x, float y)
{
    FUN_438710(x, y, 0xc, 0x1d, 1.0f, 0x100);
    FUN_438710(g_489290 + x, y, 0xc, 0x1e, 1.0f, 0x100);
    FUN_438710(x, g_489294 + y, 0xc, 0x1f, 1.0f, 0x100);
    FUN_438710(g_489290 + x, g_489294 + y, 0xc, 0x20, 1.0f, 0x100);
}

// FUNCTION: STUNTGP_D3D 0x452830
void FUN_452830(float x, float y)
{
    int left = (int)x;
    int first = left - 1;
    int top = (int)y;
    int last = left + 3;
    int bottom = top + 2;
    if (first < 0)
    {
        first = 0;
    }
    if (top < 0)
    {
        top = 0;
    }
    if (last > 32)
    {
        last = 32;
    }
    if (bottom > 12)
    {
        bottom = 12;
    }
    for (int row = top; row < bottom; row++)
    {
        int *entry = &g_486b88[row].unk08[first];
        int count = FUN_4527d0(row);
        if (count > last)
        {
            count = last;
        }
        for (int col = first; col < count; col++)
        {
            FUN_438710(384.0f - (x - col) * 230.4f, 198.0f - (y - row) * 230.4f, 0x11, *entry, 1.0f, 3);
            entry++;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45c480
void FUN_45c480()
{
    FUN_438ba0(320.0f, 44.0f, 12, 4, 2, 1.0f, 0xffffffff, 3);
}

int FUN_437920(int index);

// FUNCTION: STUNTGP_D3D 0x45da40
void FUN_45da40(int index)
{
    FUN_438ba0(507.0f, 208.0f, 12, 4, FUN_437920(index) + 0x1d0, 1.25f, 0xffffffff, 3);
}

// FUNCTION: STUNTGP_D3D 0x45cc40
void FUN_45cc40(int track)
{
    FUN_438ba0(507.0f, 208.0f, 12, 4, track + 0x1d0, 1.25f, 0xffffffff, 3);
}

// The original reloads g_4894e0.items after every store through it, which /Oa folds away.
#pragma optimize("a", off)
// Updates the track page's menu texts for the game mode, and the record tables beside it.
// FUNCTION: STUNTGP_D3D 0x45cc70
void FUN_45cc70(Unk45c4b0 *object)
{
    switch (g_menuState.unk4230)
    {
    case 2:
        g_4894e0.items[1].text = object->unk30 + 0x1ff;
        g_4894e0.items[2].text = g_menuState.unk4480 + 0x202;
        g_4894e0.items[3].text = g_menuState.unk447c + 0x205;
        return;
    case 3:
    {
        int index = object->unk1c;
        FUN_45cd60(g_menuState.unk440c[index]);
        if (g_menuState.unk46e4 != g_menuState.unk440c[index])
        {
            PoolObject *child = object->child;
            if (child->message(child, 0x1a, 0) == 2)
            {
                child->message(child, 0x1c, 1);
            }
            g_489340[2].id = -2;
        }
        else
        {
            g_489340[2].id = 2;
        }
        return;
    }
    case 5:
        FUN_45cf10(g_menuState.unk440c[object->unk1c]);
        return;
    case 6:
        g_4894e0.items[1].text = object->unk30 + 0x1ff;
        return;
    }
}
#pragma optimize("", on)

// FUNCTION: STUNTGP_D3D 0x45cf10
void FUN_45cf10(int row)
{
    char text[0x20];
    FUN_439450(423.0f, 366.0f, 591.0f, 442.0f, 0xa, 0x6f, 0x40);
    FUN_439380(423.0f, 366.0f, 591.0f, 442.0f, 0xd, 2, 0, 0.0f);
    FUN_438be0(507.0f, 370.0f, 0xc, 4, 0x24, 1.25f, 0xffff8080, 1);
    FUN_438be0(433.0f, 396.0f, 0xc, 4, 0x25, 1.25f, 0xffffffff, 2);
    FUN_438960(497.0f, 396.0f, 0xc, 0, 4, (char *)FUN_43d690((Initials *)g_menuState.unk1a1c[row][0].name), 1.25f,
               0xffffffff, 3);
    FUN_438a20(581.0f, 396.0f, 0xc, 0, 4, FUN_43d550(g_menuState.unk1a1c[row][0].time), 1.25f, 0xffffffff, 6, 14.0f);
    FUN_438be0(433.0f, 412.0f, 0xc, 4, 0x26, 1.25f, 0xffffffff, 2);
    FUN_438960(497.0f, 412.0f, 0xc, 0, 4, (char *)FUN_43d690((Initials *)g_menuState.unk1a1c[row][1].name), 1.25f,
               0xffffffff, 3);
    FUN_438a20(581.0f, 412.0f, 0xc, 0, 4, FUN_43d550(g_menuState.unk1a1c[row][1].time), 1.25f, 0xffffffff, 6, 14.0f);
    FUN_438be0(433.0f, 428.0f, 0xc, 4, 0x27, 1.25f, 0xffffffff, 2);
    FUN_438960(497.0f, 428.0f, 0xc, 0, 4, (char *)FUN_43d690((Initials *)g_menuState.unk1a1c[row][3].name), 1.25f,
               0xffffffff, 3);
    // STRING: STUNTGP_D3D 0x489524
    sprintf(text, "%06d", g_menuState.unk1a1c[row][3].time);
    FUN_438a20(581.0f, 428.0f, 0xc, 0, 4, text, 1.25f, 0xffffffff, 6, 14.0f);
}

// FUNCTION: STUNTGP_D3D 0x45cd60
void FUN_45cd60(int table)
{
    FUN_439450(423.0f, 366.0f, 591.0f, 442.0f, 0xa, 0x6f, 0x40);
    FUN_439380(423.0f, 366.0f, 591.0f, 442.0f, 0xd, 2, 0, 0.0f);
    FUN_438be0(507.0f, 370.0f, 0xc, 4, 0x24, 1.25f, 0xffff8080, 1);
    FUN_438be0(433.0f, 404.0f, 0xc, 4, 0x22, 1.25f, 0xffffffff, 2);
    FUN_438960(497.0f, 404.0f, 0xc, 0, 4, (char *)FUN_43d690((Initials *)g_menuState.unk0694[table].entries[0].name),
               1.25f, g_menuState.unk0694[table].unk00 ? 0xffffe400 : 0xffffffff, 3);
    FUN_438a20(581.0f, 404.0f, 0xc, 0, 4, FUN_43d550(g_menuState.unk0694[table].entries[0].time), 1.25f,
               g_menuState.unk0694[table].unk00 ? 0xffffe400 : 0xffffffff, 6, 14.0f);
    if (g_menuState.unk46e4 == table)
    {
        FUN_438be0(433.0f, 422.0f, 0xc, 4, 0x23, 1.25f, 0xffffffff, 2);
        FUN_438960(497.0f, 422.0f, 0xc, 0, 4, g_menuState.unk4714, 1.25f, 0xffffffff, 3);
        FUN_438a20(581.0f, 422.0f, 0xc, 0, 4, FUN_43d550(g_menuState.unk4704), 1.25f, 0xffffffff, 6, 14.0f);
    }
}

// Bobbing arrows either side of the highlighted entry.
// FUNCTION: STUNTGP_D3D 0x456bf0
void FUN_456bf0(Unk456950 *object)
{
    if (g_menuState.unk423c > 1)
    {
        float x = g_4888c0.x;
        float y = g_4888c0.y;
        x -= (float)sin(object->unk1c * 3.1415927f) * 20.0f + 110.0f;
        FUN_438710(x, y, 13, g_menuState.unk4238 + 0x35, 1.0f, 0x203);
        FUN_438710(x, y, 12, g_menuState.unk4238 + 0x31, 1.0f, 0x103);
    }
}

// FUNCTION: STUNTGP_D3D 0x456c80
void FUN_456c80(Unk4516c0 *object)
{
    FUN_439450(160.0f, 120.0f, 480.0f, 280.0f, 0xa, 0x6e, 0x40);
    FUN_439380(160.0f, 120.0f, 480.0f, 280.0f, 0xd, 2, 0, 0.0f);
    switch (g_menuState.unk4230)
    {
    default:
        g_6250f8[0] = 0;
        break;
    case 7:
    {
        int index = g_menuState.unk00e8;
        if (index < 0)
        {
            break;
        }
        if (index > 2)
        {
            if (index == 3)
            {
                sprintf(g_6250f8, FUN_441170(0x2a9), g_menuState.unk1dae0);
            }
        }
        else
        {
            int target = (&g_4888c0.unk2c)[index];
            if (g_menuState.unk1dae0 >= target)
            {
                sprintf(g_6250f8, FUN_441170(0x2af), g_menuState.unk1dae0);
            }
            else
            {
                sprintf(g_6250f8, FUN_441170(0x2a8), g_menuState.unk1dae0, target);
            }
        }
        break;
    }
    case 6:
        sprintf(g_6250f8, FUN_441170(0x2a9), g_menuState.unk1dae0);
        break;
    }
    FUN_438960(320.0f, 140.0f, 0xc, 0, 4, g_6250f8, 1.25f, 0xffffffff, 3);
    FUN_438be0(259.0f, 160.0f, 0xc, 4, 0x2aa, 1.25f, 0xffff8080, 6);
    int id = 0x2ab;
    if (g_menuState.unk4230 == 7)
    {
        switch (g_menuState.unk00e0)
        {
        case 2:
            id = 0x2ad;
            break;
        case 1:
            id = 0x2ac;
            break;
        case 0:
            id = 0x2ab;
            break;
        }
    }
    FUN_438be0(350.0f, 160.0f, 0xc, 4, id, 1.25f, 0xffff8080, 6);
    FUN_438be0(405.0f, 160.0f, 0xc, 4, 0xae, 1.25f, 0xffff8080, 3);
    float y = 180.0f;
    for (int i = 0; i < g_menuState.unk423c; i++)
    {
        sprintf(g_6250f8, FUN_441170(0x1f), g_menuState.unk1dab0[i].unk00 + 1);
        FUN_438960(243.0f, y, 0xc, 0, 4, g_6250f8, 1.25f, 0xffc8c8ff, 6);
        // STRING: STUNTGP_D3D 0x488918
        sprintf(g_6250f8, "%d", g_menuState.unk1dab0[i].unk04);
        FUN_438a20(350.0f, y, 0xc, 0, 4, g_6250f8, 1.25f, 0xffc8c8ff, 6, 14.0f);
        // STRING: STUNTGP_D3D 0x48891c
        sprintf(g_6250f8, "%d", g_menuState.unk1dab0[i].unk08);
        FUN_438a20(405.0f, y, 0xc, 0, 4, g_6250f8, 1.25f, 0xffc8c8ff, 6, 14.0f);
        y += 20.0f;
    }
    if (object->unk24)
    {
        FUN_438be0(320.0f, y, 0xc, 4, g_menuState.unk1dab0[0].unk00 + 0x2b0, 1.25f, 0xffffffff, 3);
    }
}

typedef int (*ScreenInit)(PoolObject *object, int arg);

// Allocates one front-end screen and runs its init; NULL if the init fails.
__forceinline PoolObject *NewScreen(int size, int type, const char *name, PoolClass *cls, ScreenInit init)
{
    PoolObject *object = (PoolObject *)Pool_Alloc(size);
    memset(object, 0, size);
    object->type = type;
    object->name = name;
    object->unk08 = 0;
    *(PoolClass *)&object->destroy = *cls;
    if (!init(object, 0))
    {
        Pool_Free(object);
        return NULL;
    }
    return object;
}

// FUNCTION: STUNTGP_D3D 0x43e000
PoolObject *FUN_43e000(int a, int screen)
{
    PoolObject *object;
    switch (screen)
    {
    case 1:
        // STRING: STUNTGP_D3D 0x479670
        object = NewScreen(0x24, 1, "PageTitle", &g_489298, (ScreenInit)FUN_45c030);
        break;
    case 4:
        // STRING: STUNTGP_D3D 0x47967c
        object = NewScreen(0x28, 22, "PageAlign", &g_486738, (ScreenInit)FUN_450880);
        break;
    case 5:
        // STRING: STUNTGP_D3D 0x479688
        object = NewScreen(0x18, 23, "PageSetup", &g_488e80, (ScreenInit)FUN_45a610);
        break;
    case 2:
        // STRING: STUNTGP_D3D 0x479694
        object = NewScreen(0x20, 2, "PageMain", &g_487c18, (ScreenInit)FUN_4530b0);
        break;
    case 3:
        // STRING: STUNTGP_D3D 0x4796a0
        object = NewScreen(0x18, 3, "PageSingle", &g_488f78, (ScreenInit)FUN_45a770);
        break;
    case 6:
        // STRING: STUNTGP_D3D 0x4796ac
        object = NewScreen(0x18, 4, "PageMulti", &g_488198, (ScreenInit)FUN_454220);
        break;
    case 7:
        // STRING: STUNTGP_D3D 0x4796b8
        object = NewScreen(0x58, 5, "PageModify", &g_4880f0, FUN_453480);
        break;
    case 8:
        // STRING: STUNTGP_D3D 0x4796c4
        object = NewScreen(0x2c, 6, "PageCatalog", &g_487920, (ScreenInit)FUN_4522c0);
        break;
    case 21:
        // STRING: STUNTGP_D3D 0x4796d0
        object = NewScreen(0x18, 19, "PageRecords", &g_488b20, (ScreenInit)FUN_457470);
        break;
    case 34:
        // STRING: STUNTGP_D3D 0x4796dc
        object = NewScreen(0x18, 39, "PageTTRecords", &g_488990, (ScreenInit)FUN_456fc0);
        break;
    case 35:
        // STRING: STUNTGP_D3D 0x4796ec
        object = NewScreen(0x18, 40, "PageCampaignRecords", &g_488a38, (ScreenInit)FUN_457260);
        break;
    case 22:
        // STRING: STUNTGP_D3D 0x479700
        object = NewScreen(0x1c, 20, "PageRefresh", &g_488be8, (ScreenInit)FUN_4576e0);
        break;
    case 23:
        // STRING: STUNTGP_D3D 0x47970c
        object = NewScreen(0x24, 21, "PageRefreshTest", &g_4866a0, (ScreenInit)FUN_450400);
        break;
    case 9:
        // STRING: STUNTGP_D3D 0x47971c
        object = NewScreen(0x50, 7, "PageEnterName", &g_4881c0, (ScreenInit)FUN_454410);
        break;
    case 10:
        // STRING: STUNTGP_D3D 0x47972c
        object = NewScreen(0x1d0, 8, "PageSelectCar", &g_4869d0, FUN_451700);
        break;
    case 11:
        // STRING: STUNTGP_D3D 0x47973c
        object = NewScreen(0x34, 9, "PageSelectTrack", &g_489510, (ScreenInit)FUN_45c4b0);
        break;
    case 12:
        // STRING: STUNTGP_D3D 0x47974c
        object = NewScreen(0x3c, 10, "PageSelectTree", &g_489670, FUN_45d1a0);
        break;
    case 13:
        // STRING: STUNTGP_D3D 0x47975c
        object = NewScreen(0x20, 11, "PageSelectTeam", &g_4891d8, (ScreenInit)FUN_45b7a0);
        break;
    case 14:
        // STRING: STUNTGP_D3D 0x47976c
        object = NewScreen(0x2c, 12, "PageCampaignMenu", &g_4868d0, (ScreenInit)FUN_450c10);
        break;
    case 15:
        // STRING: STUNTGP_D3D 0x479780
        object = NewScreen(0x18, 13, "PageOptions", &g_488388, (ScreenInit)FUN_454ce0);
        break;
    case 16:
        // STRING: STUNTGP_D3D 0x47978c
        object = NewScreen(0x20, 14, "PageOptionsCFG", &g_4884c0, (ScreenInit)FUN_454fa0);
        break;
    case 17:
        // STRING: STUNTGP_D3D 0x47979c
        object = NewScreen(0x18, 15, "PageOptionsSND", &g_488570, (ScreenInit)FUN_455340);
        break;
    case 18:
        // STRING: STUNTGP_D3D 0x4797ac
        object = NewScreen(0x18, 16, "PageOptionsVID", &g_4885f8, (ScreenInit)FUN_4555e0);
        break;
    case 19:
        // STRING: STUNTGP_D3D 0x4797bc
        object = NewScreen(0x18, 17, "PageOptionsCTL", &g_488610, FUN_4557e0);
        break;
    case 20:
        // STRING: STUNTGP_D3D 0x4797cc
        object = NewScreen(0x30, 18, "PageOptionsTOURNAMENT", &g_488748, (ScreenInit)FUN_455c70);
        break;
    case 25:
        // STRING: STUNTGP_D3D 0x4797e4
        object = NewScreen(0x1c, 24, "PageGame", &g_4879c0, (ScreenInit)FUN_452b30);
        break;
    case 26:
        // STRING: STUNTGP_D3D 0x4797f0
        object = NewScreen(0x18, 25, "PageTest", &g_4891f0, (ScreenInit)FUN_45bba0);
        break;
    case 27:
        // STRING: STUNTGP_D3D 0x4797fc
        object = NewScreen(0x200, 26, "PageSave", &g_488c90, (ScreenInit)FUN_457920);
        break;
    case 29:
        // STRING: STUNTGP_D3D 0x479808
        object = NewScreen(0x2c, 29, "PageLanguage", &g_487a38, (ScreenInit)FUN_452c00);
        break;
    case 30:
        // STRING: STUNTGP_D3D 0x479818
        object = NewScreen(0x18, 30, "PageCredits", &g_4879a8, (ScreenInit)FUN_452940);
        break;
    case 36:
        // STRING: STUNTGP_D3D 0x479824
        object = NewScreen(0x18, 31, "PageGameLoop", &g_487a50, (ScreenInit)FUN_452fc0);
        break;
    case 37:
        // STRING: STUNTGP_D3D 0x479834
        object = NewScreen(0x1c, 32, "PageBmpSplash", &g_489150, (ScreenInit)FUN_45b520);
        break;
    case 38:
        // STRING: STUNTGP_D3D 0x479844
        object = NewScreen(0x18, 33, "PageTextSplash", &g_489278, (ScreenInit)FUN_45bd70);
        break;
    case 39:
        // STRING: STUNTGP_D3D 0x479854
        object = NewScreen(0x4c, 34, "PageHighScore", &g_488d28, (ScreenInit)FUN_459200);
        break;
    case 40:
        // STRING: STUNTGP_D3D 0x479864
        object = NewScreen(0x24, 35, "PageUnlock", &g_489700, (ScreenInit)FUN_45db80);
        break;
    case 24:
        // STRING: STUNTGP_D3D 0x479870
        object = NewScreen(0x5c, 28, "PagePads", &g_488760, (ScreenInit)FUN_456010);
        break;
    case 28:
        // STRING: STUNTGP_D3D 0x47987c
        object = NewScreen(0x3c, 27, "PageSlot", &g_4890b0, (ScreenInit)FUN_45a9c0);
        break;
    case 31:
        // STRING: STUNTGP_D3D 0x479888
        object = NewScreen(0xc0, 36, "PageArcadeScore", &g_488dd0, (ScreenInit)FUN_459790);
        break;
    case 32:
        // STRING: STUNTGP_D3D 0x479898
        object = NewScreen(0x18, 37, "PageCampaignScore", &g_488e68, (ScreenInit)FUN_45a360);
        break;
    case 33:
        // STRING: STUNTGP_D3D 0x4798ac
        object = NewScreen(0x28, 38, "PageQuickScore", &g_4888f8, (ScreenInit)FUN_4567d0);
        break;
    default:
        return NULL;
    }
    if (object)
    {
        object->unk08 = a;
    }
    return object;
}
