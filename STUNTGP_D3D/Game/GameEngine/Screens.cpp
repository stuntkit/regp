#include "objects.h"
#include "Game/GameEngine/MenuUpdate.h"

#include <string.h>

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
int FUN_45a770(PoolObject *object, int arg);
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
void FUN_45d2e0(PoolObject *object);
int FUN_45d320(PoolObject *object, int msg, int arg);
int FUN_45b7a0(PoolObject *object, int arg);
void FUN_45b850(MenuHolder *object);
int FUN_45b870(PoolObject *object, int msg, int arg);
int FUN_450c10(Unk4516c0 *object, int arg);
void FUN_450e10(Unk4516c0 *object);
int FUN_4512b0(PoolObject *object, int msg, int arg);
int FUN_454ce0(PoolObject *object, int arg);
void FUN_454d80(MenuHolder *object);
int FUN_454da0(PoolObject *object, int msg, int arg);
int FUN_454fa0(PoolObject *object, int arg);
void FUN_455090(Unk4516c0 *object);
int FUN_4550d0(PoolObject *object, int msg, int arg);
int FUN_455340(PoolObject *object, int arg);
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
int FUN_457470(PoolObject *object, int arg);
void FUN_457500(MenuHolder *object);
int FUN_457520(PoolObject *object, int msg, int arg);
int FUN_4576e0(PoolObject *object, int arg);
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
int FUN_452c00(PoolObject *object, int arg);
void FUN_452d50(MenuHolder *object);
int FUN_452d90(PoolObject *object, int msg, int arg);
int FUN_452940(MenuHolder *object, int arg);
void FUN_4529c0(MenuHolder *object);
int FUN_4529e0(PoolObject *object, int msg, int arg);
int FUN_459790(PoolObject *object, int arg);
void FUN_459a20(MenuHolder *object);
int FUN_459a40(PoolObject *object, int msg, int arg);
int FUN_45a360(PoolObject *object, int arg);
void FUN_45a3f0(MenuHolder *object);
int FUN_45a410(PoolObject *object, int msg, int arg);
int FUN_4567d0(PoolObject *object, int arg);
void FUN_456910(Unk4516c0 *object);
int FUN_456950(PoolObject *object, int msg, int arg);
int FUN_456fc0(PoolObject *object, int arg);
void FUN_4570f0(MenuHolder *object);
int FUN_457110(PoolObject *object, int msg, int arg);
int FUN_457260(PoolObject *object, int arg);
void FUN_4572e0(MenuHolder *object);
int FUN_457300(PoolObject *object, int msg, int arg);
int FUN_452fc0(MenuObject *object, int arg);
void FUN_452fd0(PoolObject *object);
int FUN_452fe0(PoolObject *object, int msg, int arg);
int FUN_45b520(PoolObject *object, int arg);
void FUN_45b5b0(MenuHolder *object);
int FUN_45b5d0(PoolObject *object, int msg, int arg);
int FUN_45bd70(PoolObject *object, int arg);
void FUN_45be00(MenuHolder *object);
int FUN_45bf40(PoolObject *object, int msg, int arg);
int FUN_459200(PoolObject *object, int arg);
void FUN_459300(MenuHolder *object);
int FUN_459320(PoolObject *object, int msg, int arg);
int FUN_45db80(PoolObject *object, int arg);
void FUN_45dde0(MenuHolder *object);
int FUN_45de00(PoolObject *object, int msg, int arg);

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
PoolClass g_489670 = {FUN_45d2e0, FUN_45d320};

// GLOBAL: STUNTGP_D3D 0x489700
PoolClass g_489700 = {(void (*)(PoolObject *))FUN_45dde0, FUN_45de00};

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

// STUB: STUNTGP_D3D 0x452b50
void FUN_452b50(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x452b60
int FUN_452b60(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x452c00
int FUN_452c00(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x452d90
int FUN_452d90(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x452fd0
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

// STUB: STUNTGP_D3D 0x454450
void FUN_454450(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x454460
int FUN_454460(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x454ce0
int FUN_454ce0(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x454da0
int FUN_454da0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x454fa0
int FUN_454fa0(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x4550d0
int FUN_4550d0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x455340
int FUN_455340(PoolObject *object, int arg)
{
    return 0;
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

// STUB: STUNTGP_D3D 0x4557f0
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

// STUB: STUNTGP_D3D 0x4560b0
void FUN_4560b0(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x4560c0
int FUN_4560c0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x4567d0
int FUN_4567d0(PoolObject *object, int arg)
{
    return 0;
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

// STUB: STUNTGP_D3D 0x457260
int FUN_457260(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x457300
int FUN_457300(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x457470
int FUN_457470(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x457520
int FUN_457520(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x4576e0
int FUN_4576e0(PoolObject *object, int arg)
{
    return 0;
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

// STUB: STUNTGP_D3D 0x459200
int FUN_459200(PoolObject *object, int arg)
{
    return 0;
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

// STUB: STUNTGP_D3D 0x45a360
int FUN_45a360(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45a410
int FUN_45a410(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45a620
void FUN_45a620(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x45a630
int FUN_45a630(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45a770
int FUN_45a770(PoolObject *object, int arg)
{
    return 0;
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

// STUB: STUNTGP_D3D 0x45b520
int FUN_45b520(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45b5d0
int FUN_45b5d0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45b7a0
int FUN_45b7a0(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45b870
int FUN_45b870(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45bbb0
void FUN_45bbb0(PoolObject *object)
{
}

// STUB: STUNTGP_D3D 0x45bbc0
int FUN_45bbc0(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45bd70
int FUN_45bd70(PoolObject *object, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45bf40
int FUN_45bf40(PoolObject *object, int msg, int arg)
{
    return 0;
}

// STUB: STUNTGP_D3D 0x45c070
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

// STUB: STUNTGP_D3D 0x45d2e0
void FUN_45d2e0(PoolObject *object)
{
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
        object = NewScreen(0x18, 3, "PageSingle", &g_488f78, FUN_45a770);
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
        object = NewScreen(0x18, 19, "PageRecords", &g_488b20, FUN_457470);
        break;
    case 34:
        // STRING: STUNTGP_D3D 0x4796dc
        object = NewScreen(0x18, 39, "PageTTRecords", &g_488990, FUN_456fc0);
        break;
    case 35:
        // STRING: STUNTGP_D3D 0x4796ec
        object = NewScreen(0x18, 40, "PageCampaignRecords", &g_488a38, FUN_457260);
        break;
    case 22:
        // STRING: STUNTGP_D3D 0x479700
        object = NewScreen(0x1c, 20, "PageRefresh", &g_488be8, FUN_4576e0);
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
        object = NewScreen(0x20, 11, "PageSelectTeam", &g_4891d8, FUN_45b7a0);
        break;
    case 14:
        // STRING: STUNTGP_D3D 0x47976c
        object = NewScreen(0x2c, 12, "PageCampaignMenu", &g_4868d0, (ScreenInit)FUN_450c10);
        break;
    case 15:
        // STRING: STUNTGP_D3D 0x479780
        object = NewScreen(0x18, 13, "PageOptions", &g_488388, FUN_454ce0);
        break;
    case 16:
        // STRING: STUNTGP_D3D 0x47978c
        object = NewScreen(0x20, 14, "PageOptionsCFG", &g_4884c0, FUN_454fa0);
        break;
    case 17:
        // STRING: STUNTGP_D3D 0x47979c
        object = NewScreen(0x18, 15, "PageOptionsSND", &g_488570, FUN_455340);
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
        object = NewScreen(0x2c, 29, "PageLanguage", &g_487a38, FUN_452c00);
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
        object = NewScreen(0x1c, 32, "PageBmpSplash", &g_489150, FUN_45b520);
        break;
    case 38:
        // STRING: STUNTGP_D3D 0x479844
        object = NewScreen(0x18, 33, "PageTextSplash", &g_489278, FUN_45bd70);
        break;
    case 39:
        // STRING: STUNTGP_D3D 0x479854
        object = NewScreen(0x4c, 34, "PageHighScore", &g_488d28, FUN_459200);
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
        object = NewScreen(0x18, 37, "PageCampaignScore", &g_488e68, FUN_45a360);
        break;
    case 33:
        // STRING: STUNTGP_D3D 0x4798ac
        object = NewScreen(0x28, 38, "PageQuickScore", &g_4888f8, FUN_4567d0);
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
