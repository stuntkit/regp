#include "soundsys.h"

#include <string.h>

#include "globals.h"

#include <mmsystem.h>
#include <dsound.h>

// LIBRARY: STUNTGP_D3D 0x4627b0
// _DirectSoundCreate@12

// LIBRARY: STUNTGP_D3D 0x4627b6
// _DirectSoundEnumerateA@8

struct SoundDef
{
    const char *name;
    int id;
    int flags;
};

struct SoundTable
{
    SoundDef defs[72];
};

struct SoundChannel
{
    LPDIRECTSOUNDBUFFER buffer;
    BYTE unk04[0x20 - 4];
};

struct SoundDriver
{
    GUID guid;
    char name[0x80];
};

// GLOBAL: STUNTGP_D3D 0x489798
int g_489798 = 0xff;

// GLOBAL: STUNTGP_D3D 0x48979c
int g_48979c = 0xff;

// GLOBAL: STUNTGP_D3D 0x4897ac
int g_4897ac = 1;

// GLOBAL: STUNTGP_D3D 0x4897b0
int g_4897b0 = 1;

// GLOBAL: STUNTGP_D3D 0x4897b4
int g_4897b4 = 1;

// GLOBAL: STUNTGP_D3D 0x4899e0
SoundTable g_4899e0 = {{{NULL, 0, 1}}};

// GLOBAL: STUNTGP_D3D 0x489d40
SoundTable g_489d40 = {{
    {NULL, 1, 1},
    // STRING: STUNTGP_D3D 0x48a16c
    {"petes-revving", 1, 2},
    // STRING: STUNTGP_D3D 0x48a17c
    {"karls-revving", 2, 2},
    // STRING: STUNTGP_D3D 0x48a18c
    {"mgfboot-revving", 3, 2},
    // STRING: STUNTGP_D3D 0x48a19c
    {"stefans-revving", 4, 2},
    // STRING: STUNTGP_D3D 0x48a1ac
    {"engine3-revving", 5, 2},
    // STRING: STUNTGP_D3D 0x48a1bc
    {"petes-idling", 6, 2},
    // STRING: STUNTGP_D3D 0x48a1cc
    {"karls-idling", 7, 2},
    // STRING: STUNTGP_D3D 0x48a1dc
    {"mgfboot-idling", 8, 2},
    // STRING: STUNTGP_D3D 0x48a1ec
    {"stefans-idling", 9, 2},
    // STRING: STUNTGP_D3D 0x48a1fc
    {"engine3-idling", 10, 2},
    // STRING: STUNTGP_D3D 0x48a20c
    {"turbo1", 11, 2},
    // STRING: STUNTGP_D3D 0x48a214
    {"Crashwall1", 12, 2},
    // STRING: STUNTGP_D3D 0x48a220
    {"Crashwall2", 13, 2},
    // STRING: STUNTGP_D3D 0x48a22c
    {"Crashwall3", 14, 2},
    // STRING: STUNTGP_D3D 0x48a238
    {"Crowdpart1", 15, 1},
    // STRING: STUNTGP_D3D 0x48a244
    {"Crowdpart2", 16, 1},
    // STRING: STUNTGP_D3D 0x48a250
    {"Combo01", 17, 1},
    // STRING: STUNTGP_D3D 0x48a258
    {"Combo02", 18, 1},
    // STRING: STUNTGP_D3D 0x48a260
    {"Combo03", 19, 1},
    // STRING: STUNTGP_D3D 0x48a268
    {"Combo04", 20, 1},
    // STRING: STUNTGP_D3D 0x48a270
    {"Combo05", 21, 1},
    // STRING: STUNTGP_D3D 0x48a278
    {"lofuel", 22, 1},
    // STRING: STUNTGP_D3D 0x48a280
    {"powerjump", 23, 1},
    // STRING: STUNTGP_D3D 0x48a28c
    {"roadnoise1", 24, 2},
    // STRING: STUNTGP_D3D 0x48a298
    {"scrape1", 25, 2},
    // STRING: STUNTGP_D3D 0x48a2a0
    {"skidloop", 26, 2},
    // STRING: STUNTGP_D3D 0x48a2ac
    {"skidsand", 27, 2},
    // STRING: STUNTGP_D3D 0x48a2b8
    {"carland", 28, 2},
    // STRING: STUNTGP_D3D 0x48a2c0
    {"travsand", 29, 2},
    // STRING: STUNTGP_D3D 0x48a2cc
    {"DriveShaft", 30, 2},
    // STRING: STUNTGP_D3D 0x48a2d8
    {"carbottoming1", 31, 2},
    // STRING: STUNTGP_D3D 0x48a2e8
    {"servo1", 32, 1},
    // STRING: STUNTGP_D3D 0x48a2f0
    {"gearchange1", 33, 1},
    // STRING: STUNTGP_D3D 0x48a2fc
    {"hornloop01", 34, 2},
    // STRING: STUNTGP_D3D 0x48a308
    {"hornloop02", 35, 2},
    // STRING: STUNTGP_D3D 0x48a314
    {"hornloop03", 36, 2},
    // STRING: STUNTGP_D3D 0x48a320
    {"hornloop04", 37, 2},
    // STRING: STUNTGP_D3D 0x48a32c
    {"hornloop06", 38, 2},
    // STRING: STUNTGP_D3D 0x48a338
    {"elecloop01", 39, 1},
    // STRING: STUNTGP_D3D 0x48a344
    {"elec01", 40, 1},
    // STRING: STUNTGP_D3D 0x48a34c
    {"elec02", 41, 1},
    // STRING: STUNTGP_D3D 0x48a354
    {"elec04", 42, 1},
    // STRING: STUNTGP_D3D 0x48a35c
    {"elec05", 43, 1},
    // STRING: STUNTGP_D3D 0x48a364
    {"start1", 44, 1},
    // STRING: STUNTGP_D3D 0x48a36c
    {"start2", 45, 1},
    // STRING: STUNTGP_D3D 0x48a374
    {"swoosh1", 46, 1},
    // STRING: STUNTGP_D3D 0x48a37c
    {"swoosh2", 47, 1},
    // STRING: STUNTGP_D3D 0x48a384
    {"menublip1", 48, 1},
    // STRING: STUNTGP_D3D 0x48a390
    {"menublip2", 49, 1},
    // STRING: STUNTGP_D3D 0x48a39c
    {"clunk", 50, 1},
    // STRING: STUNTGP_D3D 0x48a3a4
    {"fe-dialogmove", 51, 1},
    // STRING: STUNTGP_D3D 0x48a3b4
    {"fe-dialogcancel", 52, 1},
    // STRING: STUNTGP_D3D 0x48a3c4
    {"fe-dialogconfirm", 53, 1},
    // STRING: STUNTGP_D3D 0x48a3d8
    {"fe-keypressed", 54, 1},
    // STRING: STUNTGP_D3D 0x48a3e8
    {"fe-keydeleted", 55, 1},
    // STRING: STUNTGP_D3D 0x48a3f8
    {"fe-cardschanged", 56, 1},
    // STRING: STUNTGP_D3D 0x48a408
    {"fe-cardserror", 57, 1},
    // STRING: STUNTGP_D3D 0x48a418
    {"fe-cardssuccess", 58, 1},
    // STRING: STUNTGP_D3D 0x48a428
    {"fe-warning", 59, 1},
    // STRING: STUNTGP_D3D 0x48a434
    {"fe-timertick", 60, 1},
    // STRING: STUNTGP_D3D 0x48a444
    {"fe-bonustick", 61, 1},
    // STRING: STUNTGP_D3D 0x48a454
    {"fe-bonuschime", 62, 1},
    // STRING: STUNTGP_D3D 0x48a464
    {"fe-bonuscomplete", 63, 1},
    // STRING: STUNTGP_D3D 0x48a478
    {"fe-vehicleupgrade", 64, 1},
    // STRING: STUNTGP_D3D 0x48a48c
    {"fe-vehicledowngrade", 65, 1},
    // STRING: STUNTGP_D3D 0x48a4a0
    {"fe-gameload", 66, 1},
    // STRING: STUNTGP_D3D 0x48a4ac
    {"fe-iconappear", 67, 1},
    // STRING: STUNTGP_D3D 0x48a4bc
    {"fe-menuappear", 68, 1},
    // STRING: STUNTGP_D3D 0x48a4cc
    {"fe-menudisappear", 69, 1},
    // STRING: STUNTGP_D3D 0x48a4e0
    {"fe-bitmapscroll", 70, 1},
    // STRING: STUNTGP_D3D 0x48a4f0
    {"fe-vmodscroll", 71, 1},
}};

// GLOBAL: STUNTGP_D3D 0x62e0ac
int g_62e0ac;

// GLOBAL: STUNTGP_D3D 0x62e0b0
LPDIRECTSOUND g_62e0b0;

// GLOBAL: STUNTGP_D3D 0x62e0f0
int g_62e0f0;

// GLOBAL: STUNTGP_D3D 0x62e0f8
int g_62e0f8;

// GLOBAL: STUNTGP_D3D 0x62e114
int g_62e114;

// GLOBAL: STUNTGP_D3D 0x62e118
SoundChannel g_62e118[0x80];

// GLOBAL: STUNTGP_D3D 0x62f118
SoundDriver *g_62f118;

// GLOBAL: STUNTGP_D3D 0x62f11c
int g_62f11c;

// GLOBAL: STUNTGP_D3D 0x62f120
int g_62f120;

// GLOBAL: STUNTGP_D3D 0x62f128
SoundDriver g_62f128[8];

// GLOBAL: STUNTGP_D3D 0x62f5ac
int g_62f5ac;

// GLOBAL: STUNTGP_D3D 0x62f5b4
int g_62f5b4;

// FUNCTION: STUNTGP_D3D 0x45f9d0
void FUN_45f9d0()
{
    if (g_62f5ac && g_62e0f8)
    {
        FUN_460330();
        g_62f5ac = 0;
    }
}

// STUB: STUNTGP_D3D 0x45fa60
void FUN_45fa60()
{
}

// STUB: STUNTGP_D3D 0x460330
void FUN_460330()
{
}

// STUB: STUNTGP_D3D 0x460bc0
void FUN_460bc0()
{
}

// FUNCTION: STUNTGP_D3D 0x460c90
void FUN_460c90()
{
    g_489798 = 0xff;
    g_48979c = 0xff;
}

// FUNCTION: STUNTGP_D3D 0x460d60
void FUN_460d60(unsigned int channel)
{
    if (g_62e0ac)
    {
        LPDIRECTSOUNDBUFFER buffer = g_62e118[channel].buffer;
        if (buffer)
        {
            buffer->Stop();
        }
        g_62f5b4--;
    }
}

// FUNCTION: STUNTGP_D3D 0x460dd0
void FUN_460dd0()
{
    for (unsigned int i = 0; i < 0x80; i++)
    {
        FUN_460d60(i);
    }
}

// STUB: STUNTGP_D3D 0x461a80
int FUN_461a80()
{
    return 0;
}

// STUB: STUNTGP_D3D 0x461cf0
int FUN_461cf0()
{
    return 0;
}

// STUB: STUNTGP_D3D 0x461f50
int FUN_461f50()
{
    return 0;
}

// The context is the address of the cursor itself, so the GUID overwrites the cursor.
// FUNCTION: STUNTGP_D3D 0x462030
BOOL CALLBACK FUN_462030(LPGUID guid, LPCSTR description, LPCSTR module, LPVOID context)
{
    SoundDriver *driver = (SoundDriver *)context;
    if (guid)
    {
        driver->guid = *guid;
    }
    strcpy(driver->name, description);
    return TRUE;
}

// FUNCTION: STUNTGP_D3D 0x462090
int FUN_462090()
{
    g_4899e0 = g_489d40;
    memset(g_62f128, 0, sizeof(g_62f128));
    g_62f118 = g_62f128;
    g_62f120 = 0;
    g_4897b0 = 1;
    g_4897ac = 1;
    g_62e0ac = 0;
    g_62e0b0 = NULL;
    g_62e114 = 0;
    g_62f11c = 0;
    g_489798 = 0x100;
    if (g_62e0f0 == 0)
    {
        return 0;
    }
    if (DirectSoundEnumerate(FUN_462030, &g_62f118) != DS_OK)
    {
        return 0;
    }
    g_62f120 = g_62f118 - g_62f128;
    if (DirectSoundCreate(NULL, &g_62e0b0, NULL) != DS_OK)
    {
        return 0;
    }
    g_62e0b0->SetCooperativeLevel(g_Hwnd, DSSCL_EXCLUSIVE);
    if (!FUN_461cf0())
    {
        return 0;
    }
    if (g_4897b4 == 0)
    {
        g_4897b0 = 0;
    }
    else if (g_4897b0 == 1 && !FUN_461a80())
    {
        return 0;
    }
    if (!FUN_461f50())
    {
        return 0;
    }
    g_62e0ac = 1;
    FUN_45fa60();
    FUN_460bc0();
    g_4897b4 = g_4897b0;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x4624b0
void FUN_4624b0()
{
}
