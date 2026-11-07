#include "soundsys.h"

#include <stdio.h>
#include <string.h>

#include "globals.h"
#include "mem.h"
#include "Game/GameEngine/io_wad.h"

#include <mmsystem.h>
#include <dsound.h>

extern char g_SoundDirectory[128];

// LIBRARY: STUNTGP_D3D 0x4627b0
// _DirectSoundCreate@12

// LIBRARY: STUNTGP_D3D 0x4627b6
// _DirectSoundEnumerateA@8

// GLOBAL: STUNTGP_D3D 0x46fe80
// IID_IDirectSound3DListener

// GLOBAL: STUNTGP_D3D 0x46fe90
// IID_IDirectSound3DBuffer

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
    LPDIRECTSOUND3DBUFFER buffer3d;
    int type;
    int unk0c;
    DWORD size;
    DWORD rate;
    DWORD bits;
    DWORD channels;
};

struct SoundDriver
{
    GUID guid;
    char name[0x80];
};

// GLOBAL: STUNTGP_D3D 0x489794
int g_489794 = 22050;

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

// GLOBAL: STUNTGP_D3D 0x62df08
int g_62df08;

// GLOBAL: STUNTGP_D3D 0x62df0c
int g_62df0c;

// GLOBAL: STUNTGP_D3D 0x62df14
int g_62df14;

// GLOBAL: STUNTGP_D3D 0x62df18
char g_62df18;

// GLOBAL: STUNTGP_D3D 0x62df1c
int g_62df1c;

// GLOBAL: STUNTGP_D3D 0x62df20
int g_62df20;

// GLOBAL: STUNTGP_D3D 0x62df24
int g_62df24;

// GLOBAL: STUNTGP_D3D 0x62df28
int g_62df28;

// GLOBAL: STUNTGP_D3D 0x62df2c
int g_62df2c;

// GLOBAL: STUNTGP_D3D 0x62df30
int g_62df30;

// GLOBAL: STUNTGP_D3D 0x62df34
int g_62df34;

// GLOBAL: STUNTGP_D3D 0x62df38
int g_62df38;

// GLOBAL: STUNTGP_D3D 0x62df3c
int g_62df3c;

// GLOBAL: STUNTGP_D3D 0x62df40
int g_62df40;

// GLOBAL: STUNTGP_D3D 0x62df50
int g_62df50;

// GLOBAL: STUNTGP_D3D 0x62df54
char g_62df54;

// GLOBAL: STUNTGP_D3D 0x62e06c
int g_62e06c;

// GLOBAL: STUNTGP_D3D 0x62e084
int g_62e084;

// GLOBAL: STUNTGP_D3D 0x62e088
int g_62e088;

// GLOBAL: STUNTGP_D3D 0x62e08c
int g_62e08c;

// GLOBAL: STUNTGP_D3D 0x62e090
int g_62e090;

// GLOBAL: STUNTGP_D3D 0x62e098
int g_62e098;

// GLOBAL: STUNTGP_D3D 0x62e09c
int g_62e09c;

// GLOBAL: STUNTGP_D3D 0x62e0a0
int g_62e0a0;

// GLOBAL: STUNTGP_D3D 0x62e0ac
int g_62e0ac;

// GLOBAL: STUNTGP_D3D 0x62e0b0
LPDIRECTSOUND g_62e0b0;

// GLOBAL: STUNTGP_D3D 0x62e0f0
int g_62e0f0;

// GLOBAL: STUNTGP_D3D 0x62e0f8
int g_62e0f8;

// GLOBAL: STUNTGP_D3D 0x62e0fc
int g_62e0fc;

// GLOBAL: STUNTGP_D3D 0x62e100
int g_62e100;

// GLOBAL: STUNTGP_D3D 0x62e104
int g_62e104;

// GLOBAL: STUNTGP_D3D 0x62e108
int g_62e108;

// GLOBAL: STUNTGP_D3D 0x62e10c
int g_62e10c;

// GLOBAL: STUNTGP_D3D 0x62e110
int g_62e110;

// GLOBAL: STUNTGP_D3D 0x62e114
LPDIRECTSOUNDBUFFER g_62e114;

// GLOBAL: STUNTGP_D3D 0x62e118
SoundChannel g_62e118[0x80];

// GLOBAL: STUNTGP_D3D 0x62f118
SoundDriver *g_62f118;

// GLOBAL: STUNTGP_D3D 0x62f11c
LPDIRECTSOUND3DLISTENER g_62f11c;

// GLOBAL: STUNTGP_D3D 0x62f120
int g_62f120;

// GLOBAL: STUNTGP_D3D 0x62f128
SoundDriver g_62f128[8];

// GLOBAL: STUNTGP_D3D 0x62f5ac
int g_62f5ac;

// GLOBAL: STUNTGP_D3D 0x62f5b4
int g_62f5b4;

void FUN_45fac0();

// FUNCTION: STUNTGP_D3D 0x45f9d0
void FUN_45f9d0()
{
    if (g_62f5ac && g_62e0f8)
    {
        FUN_460330();
        g_62f5ac = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x45fa60
void FUN_45fa60()
{
    if (g_62f5ac == 0 && g_62e0f8 != 0)
    {
        FUN_45fac0();
        g_62e0f8 = 0x66;
        g_62e10c = 0;
        g_62e0fc = 0;
        g_62e110 = 0;
        g_62e100 = 0;
        g_62e104 = 0;
        g_62e108 = 0;
        g_62f5ac = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x45fac0
void FUN_45fac0()
{
    g_62df0c = 0;
    g_62df18 = 0;
    g_62df1c = 0;
    g_62df20 = 0;
    g_62df14 = 0;
    g_62df24 = 0;
    g_62df28 = 0;
    g_62df2c = 0;
    g_62df30 = 0;
    g_62df34 = 0;
    g_62e084 = 0;
    g_62df38 = 0;
    g_62e090 = 0;
    g_62e098 = 0;
    g_62e09c = 0;
    g_62e0a0 = 0;
    g_62df3c = 0;
    g_62df40 = 0;
    g_62df50 = 0;
    g_62df54 = 0;
    g_62e06c = 0;
    g_62e088 = 0;
    g_62e08c = 0;
    g_62df08 = 0;
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

// FUNCTION: STUNTGP_D3D 0x461a80
int FUN_461a80()
{
    if (g_62e114 == NULL)
    {
        return 0;
    }
    if (g_62e114->QueryInterface(IID_IDirectSound3DListener, (LPVOID *)&g_62f11c) != DS_OK)
    {
        return 0;
    }
    g_62f11c->SetRolloffFactor(1.0f, DS3D_IMMEDIATE);
    g_62f11c->SetDopplerFactor(6.0f, DS3D_IMMEDIATE);
    g_62f11c->SetDistanceFactor(0.01f, DS3D_IMMEDIATE);
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x461cf0
int FUN_461cf0()
{
    DSCAPS caps;
    DSBUFFERDESC desc;
    DWORD written;
    WAVEFORMATEX format;

    desc.dwSize = sizeof(DSBUFFERDESC);
    desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
    desc.dwReserved = 0;
    desc.dwBufferBytes = 0;
    desc.lpwfxFormat = NULL;
    if (g_62e0b0->CreateSoundBuffer(&desc, &g_62e114, NULL) != DS_OK)
    {
        return 0;
    }
    caps.dwSize = sizeof(DSCAPS);
    if (g_62e0b0->GetCaps(&caps) != DS_OK)
    {
        return 0;
    }
    if (caps.dwMaxHw3DAllBuffers < 8)
    {
        g_4897ac = 0;
        g_4897b0 = 0;
    }
    if (g_62e114->GetFormat(&format, sizeof(WAVEFORMATEX), &written) != DS_OK)
    {
        return 0;
    }
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nSamplesPerSec = g_489794;
    WORD bits = (caps.dwFlags & DSCAPS_PRIMARY16BIT) ? 16 : 8;
    format.wBitsPerSample = bits;
    format.nBlockAlign = format.nChannels * bits / 8;
    format.nAvgBytesPerSec = format.nBlockAlign * format.nSamplesPerSec;
    return g_62e114->SetFormat(&format) == DS_OK;
}

// FUNCTION: STUNTGP_D3D 0x461b70
int FUN_461b70(LPDIRECTSOUND sound, SoundChannel *channel, DWORD flags)
{
    PCMWAVEFORMAT format;
    DSBUFFERDESC desc;
    LPDIRECTSOUNDBUFFER buffer;
    LPDIRECTSOUND3DBUFFER buffer3d;

    memset(&format, 0, sizeof(format));
    format.wBitsPerSample = channel->bits;
    format.wf.nSamplesPerSec = channel->rate;
    format.wf.nChannels = channel->channels;
    format.wf.nBlockAlign = channel->channels * channel->bits / 8;
    format.wf.nAvgBytesPerSec = format.wf.nBlockAlign * format.wf.nSamplesPerSec;
    format.wf.wFormatTag = WAVE_FORMAT_PCM;
    memset(&desc, 0, sizeof(desc));
    desc.dwSize = sizeof(DSBUFFERDESC);
    desc.dwBufferBytes = channel->size;
    desc.lpwfxFormat = (LPWAVEFORMATEX)&format;
    desc.dwFlags = flags | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
    if (sound->CreateSoundBuffer(&desc, &buffer, NULL) != DS_OK)
    {
        return 0;
    }
    if (buffer->QueryInterface(IID_IDirectSound3DBuffer, (LPVOID *)&buffer3d) != DS_OK)
    {
        return 0;
    }
    channel->buffer = buffer;
    channel->buffer3d = buffer3d;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x461c40
int FUN_461c40(LPDIRECTSOUND sound, SoundChannel *channel, DWORD flags)
{
    PCMWAVEFORMAT format;
    DSBUFFERDESC desc;
    LPDIRECTSOUNDBUFFER buffer;

    memset(&format, 0, sizeof(format));
    format.wBitsPerSample = channel->bits;
    format.wf.nSamplesPerSec = channel->rate;
    format.wf.nChannels = channel->channels;
    format.wf.nBlockAlign = channel->channels * channel->bits / 8;
    format.wf.nAvgBytesPerSec = format.wf.nBlockAlign * format.wf.nSamplesPerSec;
    format.wf.wFormatTag = WAVE_FORMAT_PCM;
    memset(&desc, 0, sizeof(desc));
    desc.dwSize = sizeof(DSBUFFERDESC);
    desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
    desc.dwBufferBytes = channel->size;
    desc.lpwfxFormat = (LPWAVEFORMATEX)&format;
    if (sound->CreateSoundBuffer(&desc, &buffer, NULL) != DS_OK)
    {
        return 0;
    }
    channel->buffer = buffer;
    return 1;
}

// Loads a RIFF WAV file (canonical 44-byte header) into a new static buffer.
// FUNCTION: STUNTGP_D3D 0x461e00
int FUN_461e00(SoundChannel *channel, char *path, DWORD flags)
{
    LPVOID ptr1;
    DWORD bytes1;
    LPVOID ptr2;
    DWORD bytes2;

    int size = size_of_file(path);
    if (size == 0)
    {
        return 0;
    }
    BYTE *wav = (BYTE *)Mem_Alloc(size + 0x20, 0);
    bload(path, (char *)wav, size);
    if (flags & DSBCAPS_CTRL3D)
    {
        channel->type = 2;
    }
    else
    {
        channel->type = 1;
    }
    channel->rate = *(DWORD *)(wav + 0x18);
    channel->size = *(DWORD *)(wav + 0x28);
    channel->bits = *(short *)(wav + 0x22);
    channel->channels = channel->bits / (*(short *)(wav + 0x20) * 8);
    channel->buffer = NULL;
    channel->unk0c = 1;
    if (g_4897b0 == 1 && (flags & DSBCAPS_CTRL3D))
    {
        if (!FUN_461b70(g_62e0b0, channel, flags))
        {
            return 0;
        }
    }
    else if (!FUN_461c40(g_62e0b0, channel, DSBCAPS_STATIC))
    {
        return 0;
    }
    LPDIRECTSOUNDBUFFER buffer = channel->buffer;
    DWORD length = channel->size;
    if (buffer->Lock(0, length, &ptr1, &bytes1, &ptr2, &bytes2, DSBLOCK_ENTIREBUFFER) != DS_OK)
    {
        return 0;
    }
    memcpy(ptr1, wav + 0x2c, length);
    if (buffer->Unlock(ptr1, length, NULL, 0) != DS_OK)
    {
        return 0;
    }
    Mem_Free(wav);
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x461f50
int FUN_461f50()
{
    char path[128];
    int i;

    memset(g_62e118, 0, sizeof(g_62e118));
    for (i = 1; g_4899e0.defs[i].name; i++)
    {
        if (g_4897b0 == 0)
        {
            g_4899e0.defs[i].flags = 1;
        }
        else if (g_4899e0.defs[i].flags == 2)
        {
            // STRING: STUNTGP_D3D 0x48a568
            sprintf(path, "%s\\Sfx\\%s.wav", g_SoundDirectory, g_4899e0.defs[i].name);
            FUN_461e00(&g_62e118[i], path, DSBCAPS_MUTE3DATMAXDISTANCE | DSBCAPS_CTRL3D | DSBCAPS_STATIC);
        }
    }
    for (i = 1; g_4899e0.defs[i].name; i++)
    {
        if (g_4899e0.defs[i].flags == 1)
        {
            // STRING: STUNTGP_D3D 0x48a578
            sprintf(path, "%s\\Sfx\\%s.wav", g_SoundDirectory, g_4899e0.defs[i].name);
            FUN_461e00(&g_62e118[i], path, DSBCAPS_STATIC);
        }
    }
    return 1;
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
    g_62e114 = NULL;
    g_62f11c = NULL;
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
