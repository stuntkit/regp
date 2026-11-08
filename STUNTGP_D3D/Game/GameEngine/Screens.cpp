#include "objects.h"
#include "Game/GameEngine/MenuUpdate.h"

#include <string.h>

// PageSelectTeam: a menu and a scroll position.
// PageHighScore
// PageLanguage
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
    int unk18;         // 0x18
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
int FUN_453210(PoolObject *object, int msg, int arg);
int FUN_45a770(MenuHolder *object, int arg);
void FUN_45a7f0(MenuHolder *object);
int FUN_45a810(PoolObject *object, int msg, int arg);
int FUN_450880(Unk450930 *object, int arg);
void FUN_450930(Unk450930 *object);
int FUN_450950(PoolObject *object, int msg, int arg);
int FUN_45a610(MenuObject *object, int arg);
void FUN_45a620(PoolObject *object);
int FUN_45a630(PoolObject *object, int msg, int arg);
int FUN_454220(MenuHolder *object, int arg);
void FUN_4542a0(MenuHolder *object);
int FUN_4542c0(PoolObject *object, int msg, int arg);
int FUN_453480(PoolObject *object, int arg);
void FUN_4536f0(MenuHolder *object);
int FUN_453710(PoolObject *object, int msg, int arg);
int FUN_4522c0(PoolObject *object, int arg);
void FUN_452530(MenuHolder *object);
int FUN_452550(PoolObject *object, int msg, int arg);
int FUN_454410(Unk454b20 *object, int arg);
void FUN_454450(PoolObject *object);
int FUN_454460(PoolObject *object, int msg, int arg);
int FUN_451700(PoolObject *object, int arg);
void FUN_451a80(MenuHolder *object);
int FUN_451aa0(PoolObject *object, int msg, int arg);
int FUN_45c4b0(PoolObject *object, int arg);
void FUN_45c640(Unk45c670 *object);
int FUN_45c6a0(PoolObject *object, int msg, int arg);
int FUN_45d1a0(PoolObject *object, int arg);
void FUN_45d2e0(Unk45d2e0 *object);
int FUN_45d320(PoolObject *object, int msg, int arg);
int FUN_45b7a0(Unk45b7a0 *object, int arg);
void FUN_45b850(MenuHolder *object);
int FUN_45b870(PoolObject *object, int msg, int arg);
int FUN_450c10(Unk4516c0 *object, int arg);
void FUN_450e10(Unk4516c0 *object);
int FUN_4512b0(PoolObject *object, int msg, int arg);
int FUN_454ce0(MenuHolder *object, int arg);
void FUN_454d80(MenuHolder *object);
int FUN_454da0(PoolObject *object, int msg, int arg);
int FUN_454fa0(Unk4516c0 *object, int arg);
void FUN_455090(Unk4516c0 *object);
int FUN_4550d0(PoolObject *object, int msg, int arg);
int FUN_455340(MenuHolder *object, int arg);
void FUN_455410(MenuHolder *object);
int FUN_455430(PoolObject *object, int msg, int arg);
int FUN_4555e0(MenuHolder *object, int arg);
void FUN_455690(MenuHolder *object);
int FUN_4556b0(PoolObject *object, int msg, int arg);
int FUN_4557e0(PoolObject *object, int arg);
void FUN_4557f0(PoolObject *object);
int FUN_455800(PoolObject *object, int msg, int arg);
int FUN_455c70(Unk455fc0 *object, int arg);
void FUN_455d70(MenuHolder *object);
int FUN_455d90(PoolObject *object, int msg, int arg);
int FUN_457470(MenuHolder *object, int arg);
void FUN_457500(MenuHolder *object);
int FUN_457520(PoolObject *object, int msg, int arg);
int FUN_4576e0(Unk457770 *object, int arg);
void FUN_4577c0(MenuHolder *object);
int FUN_4577e0(PoolObject *object, int msg, int arg);
int FUN_450400(Unk4516c0 *object, int arg);
void FUN_450510(Unk4516c0 *object);
int FUN_450550(PoolObject *object, int msg, int arg);
int FUN_456010(Unk456070 *object, int arg);
void FUN_4560b0(PoolObject *object);
int FUN_4560c0(PoolObject *object, int msg, int arg);
int FUN_452b30(MenuObject *object, int arg);
void FUN_452b50(PoolObject *object);
int FUN_452b60(PoolObject *object, int msg, int arg);
int FUN_45bba0(MenuObject *object, int arg);
void FUN_45bbb0(PoolObject *object);
int FUN_45bbc0(PoolObject *object, int msg, int arg);
int FUN_457920(PoolObject *object, int arg);
void FUN_457ea0(Unk457ea0 *object);
int FUN_457ec0(PoolObject *object, int msg, int arg);
int FUN_45a9c0(PoolObject *object, int arg);
void FUN_45ab70(Unk45ab70 *object);
int FUN_45abb0(PoolObject *object, int msg, int arg);
int FUN_452c00(Unk452c00 *object, int arg);
void FUN_452d50(MenuHolder *object);
int FUN_452d90(PoolObject *object, int msg, int arg);
int FUN_452940(MenuHolder *object, int arg);
void FUN_4529c0(MenuHolder *object);
int FUN_4529e0(PoolObject *object, int msg, int arg);
int FUN_459790(PoolObject *object, int arg);
void FUN_459a20(MenuHolder *object);
int FUN_459a40(PoolObject *object, int msg, int arg);
int FUN_45a360(MenuHolder *object, int arg);
void FUN_45a3f0(MenuHolder *object);
int FUN_45a410(PoolObject *object, int msg, int arg);
int FUN_4567d0(Unk4516c0 *object, int arg);
void FUN_456910(Unk4516c0 *object);
int FUN_456950(PoolObject *object, int msg, int arg);
int FUN_456fc0(PoolObject *object, int arg);
void FUN_4570f0(MenuHolder *object);
int FUN_457110(PoolObject *object, int msg, int arg);
int FUN_457260(MenuHolder *object, int arg);
void FUN_4572e0(MenuHolder *object);
int FUN_457300(PoolObject *object, int msg, int arg);
int FUN_452fc0(MenuObject *object, int arg);
void FUN_452fd0(PoolObject *object);
int FUN_452fe0(PoolObject *object, int msg, int arg);
int FUN_45b520(Unk45b520 *object, int arg);
void FUN_45b5b0(MenuHolder *object);
int FUN_45b5d0(PoolObject *object, int msg, int arg);
int FUN_45bd70(MenuHolder *object, int arg);
void FUN_45be00(MenuHolder *object);
int FUN_45bf40(PoolObject *object, int msg, int arg);
int FUN_459200(Unk459200 *object, int arg);
void FUN_459300(MenuHolder *object);
int FUN_459320(PoolObject *object, int msg, int arg);
int FUN_45db80(PoolObject *object, int arg);
void FUN_45dde0(MenuHolder *object);
int FUN_45de00(PoolObject *object, int msg, int arg);

// One entry per language, built by FUN_452c00.
// GLOBAL: STUNTGP_D3D 0x624bb8
MenuItem g_624bb8[9];

// GLOBAL: STUNTGP_D3D 0x627ff4
int g_627ff4;

// GLOBAL: STUNTGP_D3D 0x4866a0
PoolClass g_4866a0 = {(void (*)(PoolObject *))FUN_450510, FUN_450550};

// GLOBAL: STUNTGP_D3D 0x486738
PoolClass g_486738 = {(void (*)(PoolObject *))FUN_450930, FUN_450950};

// GLOBAL: STUNTGP_D3D 0x4868d0
PoolClass g_4868d0 = {(void (*)(PoolObject *))FUN_450e10, FUN_4512b0};

// GLOBAL: STUNTGP_D3D 0x4869d0
PoolClass g_4869d0 = {(void (*)(PoolObject *))FUN_451a80, FUN_451aa0};

// GLOBAL: STUNTGP_D3D 0x487920
PoolClass g_487920 = {(void (*)(PoolObject *))FUN_452530, FUN_452550};

// GLOBAL: STUNTGP_D3D 0x4879a8
PoolClass g_4879a8 = {(void (*)(PoolObject *))FUN_4529c0, FUN_4529e0};

// GLOBAL: STUNTGP_D3D 0x4879c0
PoolClass g_4879c0 = {FUN_452b50, FUN_452b60};

// GLOBAL: STUNTGP_D3D 0x487a38
PoolClass g_487a38 = {(void (*)(PoolObject *))FUN_452d50, FUN_452d90};

// GLOBAL: STUNTGP_D3D 0x487a50
PoolClass g_487a50 = {FUN_452fd0, FUN_452fe0};

// GLOBAL: STUNTGP_D3D 0x487c18
PoolClass g_487c18 = {(void (*)(PoolObject *))FUN_4531d0, FUN_453210};

// GLOBAL: STUNTGP_D3D 0x4880f0
PoolClass g_4880f0 = {(void (*)(PoolObject *))FUN_4536f0, FUN_453710};

// GLOBAL: STUNTGP_D3D 0x488198
PoolClass g_488198 = {(void (*)(PoolObject *))FUN_4542a0, FUN_4542c0};

// GLOBAL: STUNTGP_D3D 0x4881c0
PoolClass g_4881c0 = {FUN_454450, FUN_454460};

// GLOBAL: STUNTGP_D3D 0x488388
PoolClass g_488388 = {(void (*)(PoolObject *))FUN_454d80, FUN_454da0};

// GLOBAL: STUNTGP_D3D 0x4884c0
PoolClass g_4884c0 = {(void (*)(PoolObject *))FUN_455090, FUN_4550d0};

// GLOBAL: STUNTGP_D3D 0x488570
PoolClass g_488570 = {(void (*)(PoolObject *))FUN_455410, FUN_455430};

// GLOBAL: STUNTGP_D3D 0x4885f8
PoolClass g_4885f8 = {(void (*)(PoolObject *))FUN_455690, FUN_4556b0};

// GLOBAL: STUNTGP_D3D 0x488610
PoolClass g_488610 = {FUN_4557f0, FUN_455800};

// GLOBAL: STUNTGP_D3D 0x488748
PoolClass g_488748 = {(void (*)(PoolObject *))FUN_455d70, FUN_455d90};

// GLOBAL: STUNTGP_D3D 0x488760
PoolClass g_488760 = {FUN_4560b0, FUN_4560c0};

// GLOBAL: STUNTGP_D3D 0x4888f8
PoolClass g_4888f8 = {(void (*)(PoolObject *))FUN_456910, FUN_456950};

// GLOBAL: STUNTGP_D3D 0x488990
PoolClass g_488990 = {(void (*)(PoolObject *))FUN_4570f0, FUN_457110};

// GLOBAL: STUNTGP_D3D 0x488a38
PoolClass g_488a38 = {(void (*)(PoolObject *))FUN_4572e0, FUN_457300};

// GLOBAL: STUNTGP_D3D 0x488b20
PoolClass g_488b20 = {(void (*)(PoolObject *))FUN_457500, FUN_457520};

// GLOBAL: STUNTGP_D3D 0x488be8
PoolClass g_488be8 = {(void (*)(PoolObject *))FUN_4577c0, FUN_4577e0};

// GLOBAL: STUNTGP_D3D 0x488c90
PoolClass g_488c90 = {(void (*)(PoolObject *))FUN_457ea0, FUN_457ec0};

// GLOBAL: STUNTGP_D3D 0x488d28
PoolClass g_488d28 = {(void (*)(PoolObject *))FUN_459300, FUN_459320};

// GLOBAL: STUNTGP_D3D 0x488dd0
PoolClass g_488dd0 = {(void (*)(PoolObject *))FUN_459a20, FUN_459a40};

// GLOBAL: STUNTGP_D3D 0x488e68
PoolClass g_488e68 = {(void (*)(PoolObject *))FUN_45a3f0, FUN_45a410};

// GLOBAL: STUNTGP_D3D 0x488e80
PoolClass g_488e80 = {FUN_45a620, FUN_45a630};

// GLOBAL: STUNTGP_D3D 0x488f78
PoolClass g_488f78 = {(void (*)(PoolObject *))FUN_45a7f0, FUN_45a810};

// GLOBAL: STUNTGP_D3D 0x4890b0
PoolClass g_4890b0 = {(void (*)(PoolObject *))FUN_45ab70, FUN_45abb0};

// GLOBAL: STUNTGP_D3D 0x489150
PoolClass g_489150 = {(void (*)(PoolObject *))FUN_45b5b0, FUN_45b5d0};

// GLOBAL: STUNTGP_D3D 0x4891d8
PoolClass g_4891d8 = {(void (*)(PoolObject *))FUN_45b850, FUN_45b870};

// GLOBAL: STUNTGP_D3D 0x4891f0
PoolClass g_4891f0 = {FUN_45bbb0, FUN_45bbc0};

// GLOBAL: STUNTGP_D3D 0x489278
PoolClass g_489278 = {(void (*)(PoolObject *))FUN_45be00, FUN_45bf40};

// GLOBAL: STUNTGP_D3D 0x489298
PoolClass g_489298 = {FUN_45c070, FUN_45c080};

// GLOBAL: STUNTGP_D3D 0x489510
PoolClass g_489510 = {(void (*)(PoolObject *))FUN_45c640, FUN_45c6a0};

// GLOBAL: STUNTGP_D3D 0x489670
PoolClass g_489670 = {(void (*)(PoolObject *))FUN_45d2e0, FUN_45d320};

// GLOBAL: STUNTGP_D3D 0x489700
PoolClass g_489700 = {(void (*)(PoolObject *))FUN_45dde0, FUN_45de00};

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

// STUB: STUNTGP_D3D 0x450550
int FUN_450550(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x450950
int FUN_450950(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x4512b0
int FUN_4512b0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x451700
int FUN_451700(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x451aa0
int FUN_451aa0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x4522c0
int FUN_4522c0(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x452550
int FUN_452550(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x4529e0
int FUN_4529e0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x452b50
void FUN_452b50(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x452b60
int FUN_452b60(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x452d90
int FUN_452d90(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x453210
int FUN_453210(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x453480
int FUN_453480(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x453710
int FUN_453710(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x4542c0
int FUN_4542c0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x454450
void FUN_454450(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x454460
int FUN_454460(PoolObject *object, int msg, int arg)
{
    return 0;
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

// STUB: STUNTGP_D3D 0x454da0
int FUN_454da0(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x4550d0
int FUN_4550d0(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x455430
int FUN_455430(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x4556b0
int FUN_4556b0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x4557f0
void FUN_4557f0(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x455800
int FUN_455800(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x455d90
int FUN_455d90(PoolObject *object, int msg, int arg)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x4560b0
void FUN_4560b0(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x4560c0
int FUN_4560c0(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x456950
int FUN_456950(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x456fc0
int FUN_456fc0(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x457110
int FUN_457110(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x457300
int FUN_457300(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x457520
int FUN_457520(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x4577e0
int FUN_4577e0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x457920
int FUN_457920(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x457ec0
int FUN_457ec0(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x459320
int FUN_459320(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x459790
int FUN_459790(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x459a40
int FUN_459a40(PoolObject *object, int msg, int arg)
{
    return 0;
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

// STUB: STUNTGP_D3D 0x45a410
int FUN_45a410(PoolObject *object, int msg, int arg)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45a620
void FUN_45a620(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x45a630
int FUN_45a630(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x45a810
int FUN_45a810(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45a9c0
int FUN_45a9c0(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45abb0
int FUN_45abb0(PoolObject *object, int msg, int arg)
{
    return 0;
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

// STUB: STUNTGP_D3D 0x45b5d0
int FUN_45b5d0(PoolObject *object, int msg, int arg)
{
    return 0;
}

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

// STUB: STUNTGP_D3D 0x45b870
int FUN_45b870(PoolObject *object, int msg, int arg)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45bbb0
void FUN_45bbb0(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x45bbc0
int FUN_45bbc0(PoolObject *object, int msg, int arg)
{
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

// STUB: STUNTGP_D3D 0x45bf40
int FUN_45bf40(PoolObject *object, int msg, int arg)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45c070
void FUN_45c070(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x45c080
int FUN_45c080(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45c4b0
int FUN_45c4b0(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45c6a0
int FUN_45c6a0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45d1a0
int FUN_45d1a0(PoolObject *object, int arg)
{
    return 0;
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

// STUB: STUNTGP_D3D 0x45d320
int FUN_45d320(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45db80
int FUN_45db80(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45de00
int FUN_45de00(PoolObject *object, int msg, int arg)
{
    return 0;
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
        object = NewScreen(0x2c, 6, "PageCatalog", &g_487920, FUN_4522c0);
        break;
    case 21:
        // STRING: STUNTGP_D3D 0x4796d0
        object = NewScreen(0x18, 19, "PageRecords", &g_488b20, (ScreenInit)FUN_457470);
        break;
    case 34:
        // STRING: STUNTGP_D3D 0x4796dc
        object = NewScreen(0x18, 39, "PageTTRecords", &g_488990, FUN_456fc0);
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
        object = NewScreen(0x34, 9, "PageSelectTrack", &g_489510, FUN_45c4b0);
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
        object = NewScreen(0x200, 26, "PageSave", &g_488c90, FUN_457920);
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
        object = NewScreen(0x24, 35, "PageUnlock", &g_489700, FUN_45db80);
        break;
    case 24:
        // STRING: STUNTGP_D3D 0x479870
        object = NewScreen(0x5c, 28, "PagePads", &g_488760, (ScreenInit)FUN_456010);
        break;
    case 28:
        // STRING: STUNTGP_D3D 0x47987c
        object = NewScreen(0x3c, 27, "PageSlot", &g_4890b0, FUN_45a9c0);
        break;
    case 31:
        // STRING: STUNTGP_D3D 0x479888
        object = NewScreen(0xc0, 36, "PageArcadeScore", &g_488dd0, FUN_459790);
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
