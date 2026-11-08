#include "GameUpdate.h"
#include "../../sound.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <mmsystem.h>
#include <dsound.h>

extern int g_576be0;

// GLOBAL: STUNTGP_D3D 0x470500
const GUID DSPROPSETID_EAX20_ListenerProperties = {
    0x0306a6a8, 0xb224, 0x11d2, {0x99, 0xe5, 0x00, 0x00, 0xe8, 0xd8, 0xc7, 0x22}
};

// GLOBAL: STUNTGP_D3D 0x46fed0
// IID_IKsPropertySet

// DirectSound volumes (hundredths of a dB) indexed by 0..255 / 2.
// GLOBAL: STUNTGP_D3D 0x4897f8
short g_4897f8[129] = {
    -10000, -8000, -6000, -5500, -5000, -4707, -4415, -4207, -4000, -3839, -3678, -3546,
    -3415, -3303, -3192, -3096, -3000, -2915, -2830, -2754, -2678, -2609, -2540, -2477,
    -2415, -2357, -2299, -2245, -2192, -2142, -2093, -2046, -2000, -1956, -1912, -1871,
    -1830, -1791, -1752, -1715, -1678, -1642, -1607, -1573, -1540, -1508, -1476, -1445,
    -1415, -1385, -1356, -1327, -1299, -1272, -1245, -1218, -1192, -1167, -1142, -1117,
    -1093, -1069, -1045, -1022, -1000, -977, -955, -933, -912, -891, -870, -850,
    -830, -810, -790, -771, -752, -733, -714, -696, -678, -660, -642, -624,
    -607, -590, -573, -556, -540, -524, -508, -492, -476, -460, -445, -430,
    -415, -400, -385, -370, -356, -341, -327, -313, -299, -285, -272, -258,
    -245, -231, -218, -205, -192, -179, -167, -154, -142, -129, -117, -105,
    -93, -81, -69, -57, -45, -33, -22, -11, 0,
};

// GLOBAL: STUNTGP_D3D 0x4898fc
char *g_4898fc[24] = {
    "Empty",
    "Empty",
    "Track2",
    "Track3",
    "Track4",
    "Track5",
    "Track6",
    "Track7",
    "Track8",
    "Track9",
    "Track10",
    "Track11",
    "Track12",
    "Track13",
    "Track14",
    "Track15",
    "Track16",
    "Track17",
    "Track18",
    "Track19",
    "Track20",
    "Track21",
    "Track22",
    "Track23",
};

// GLOBAL: STUNTGP_D3D 0x4897a0
unsigned int g_4897a0 = 7500;

// GLOBAL: STUNTGP_D3D 0x4897a4
unsigned int g_4897a4 = 7500 * 7500;

// GLOBAL: STUNTGP_D3D 0x4897a8
float g_4897a8 = 0.000133333335f;

// GLOBAL: STUNTGP_D3D 0x62def8
int g_62def8;

// GLOBAL: STUNTGP_D3D 0x62defc
int g_62defc;

// GLOBAL: STUNTGP_D3D 0x62df00
int g_62df00;

// GLOBAL: STUNTGP_D3D 0x4897b0
int g_4897b0 = 1;

// GLOBAL: STUNTGP_D3D 0x4897b4
int g_4897b4 = 1;

// GLOBAL: STUNTGP_D3D 0x62e0b8
EaxListener g_62e0b8;

// GLOBAL: STUNTGP_D3D 0x62e100
int g_62e100;

// GLOBAL: STUNTGP_D3D 0x62e104
int g_62e104;

// GLOBAL: STUNTGP_D3D 0x62e108
int g_62e108;

// GLOBAL: STUNTGP_D3D 0x62e110
int g_62e110;

// The first 72 slots are fixed sounds, the remaining 32 are one-shot copies.
// GLOBAL: STUNTGP_D3D 0x62f11c
LPDIRECTSOUND3DLISTENER g_62f11c;

// GLOBAL: STUNTGP_D3D 0x62f5a8
int g_62f5a8;

// GLOBAL: STUNTGP_D3D 0x62f5b0
DWORD g_62f5b0;

// GLOBAL: STUNTGP_D3D 0x62f5b4
int g_62f5b4;

// GLOBAL: STUNTGP_D3D 0x62f5b8
int g_62f5b8;

// GLOBAL: STUNTGP_D3D 0x62f5bc
int g_62f5bc;

// GLOBAL: STUNTGP_D3D 0x62f5c0
DWORD g_62f5c0;

void FUN_461ae0(LPDIRECTSOUND3DLISTENER listener, GameSlot *slot);

// FUNCTION: STUNTGP_D3D 0x45f5b0
void FUN_45f5b0()
{
    time_t now;
    time(&now);
    struct tm *date = localtime(&now);
    g_62def8 = date->tm_mday;
    g_62defc = date->tm_mon + 1;
    g_62df00 = date->tm_year + 1900;
}

// FUNCTION: STUNTGP_D3D 0x45f7c0
void FUN_45f7c0(int value)
{
    g_62f5a8 = value;
}

// FUNCTION: STUNTGP_D3D 0x45f7d0
void FUN_45f7d0(int pan, int volume)
{
    if (g_musicVolume)
    {
        g_62e110 = pan;
        g_62e0fc = volume;
        if (g_musicStream.buffer)
        {
            int value = g_4897f8[128 - ((abs(pan) + 1) >> 1)];
            if (pan < 0)
            {
                value = -value;
            }
            if (value != g_62f5bc)
            {
                g_62f5bc = value;
                if (g_musicStream.buffer->SetPan(value) != DS_OK)
                {
                    return;
                }
            }
            value = g_62e104 * g_62e0fc * g_musicVolume / 65025;
            if (value != g_62f5b8)
            {
                g_62f5b8 = value;
                g_musicStream.buffer->SetVolume(g_4897f8[value >> 1]);
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x45f8e0
void FUN_45f8e0(int target, int step)
{
    g_62e100 = target;
    g_62e108 = step;
}

// FUNCTION: STUNTGP_D3D 0x45fa00
void FUN_45fa00()
{
    if (g_62f5ac == 1 && g_musicVolume)
    {
        FUN_45f8e0(0, -10);
        g_62f5ac = 2;
    }
}

// FUNCTION: STUNTGP_D3D 0x45fa30
void FUN_45fa30()
{
    if (g_62f5ac == 2 && g_musicVolume)
    {
        FUN_45f8e0(255, 10);
        g_62f5ac = 1;
    }
}

// FUNCTION: STUNTGP_D3D 0x45f880
void FUN_45f880()
{
    if (g_musicVolume != 0)
    {
        g_62e104 += g_62e108;
        if (g_62e104 < 0)
        {
            g_62e104 = 0;
            g_62e108 = 0;
            g_62f5b8 = -1;
            g_62f5bc = -1;
        }
        else if (g_62e104 > 255)
        {
            g_62e104 = 255;
            g_62e108 = 0;
            g_62f5b8 = -1;
            g_62f5bc = -1;
        }
        FUN_45f7d0(g_62e110, g_62e104);
    }
}

// FUNCTION: STUNTGP_D3D 0x460700
int FUN_460700(LPKSPROPERTYSET propertySet, DWORD id)
{
    ULONG support = 0;
    if (propertySet->QuerySupport(DSPROPSETID_EAX20_ListenerProperties, id, &support) != DS_OK)
    {
        return 0;
    }
    if ((support & (KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET)) !=
        (KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET))
    {
        return 0;
    }
    g_62f5c0 |= 1 << id;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x460760
void FUN_460760()
{
    memset(&g_62e0b8, 0, sizeof(g_62e0b8));
    g_62e0b8.room = -1000;
    g_62e0b8.roomHF = -800;
    g_62e0b8.roomRolloffFactor = 0.0f;
    g_62e0b8.decayTime = 1.49f;
    g_62e0b8.decayHFRatio = 0.67f;
    g_62e0b8.reflections = -2273;
    g_62e0b8.reflectionsDelay = 0.007f;
    g_62e0b8.reverb = -1691;
    g_62e0b8.reverbDelay = 0.011f;
    g_62e0b8.environment = 16;
    g_62e0b8.environmentSize = 7.5f;
    g_62e0b8.environmentDiffusion = 0.5f;
    g_62e0b8.airAbsorptionHF = -5.0f;
    g_62e0b8.flags = 0x2f;
}

// FUNCTION: STUNTGP_D3D 0x460800
void FUN_460800()
{
    memset(&g_62e0b8, 0, sizeof(g_62e0b8));
    g_62e0b8.room = -800;
    g_62e0b8.roomHF = -300;
    g_62e0b8.roomRolloffFactor = 0.0f;
    g_62e0b8.decayTime = 5.0f;
    g_62e0b8.decayHFRatio = 0.64f;
    g_62e0b8.reflections = -711;
    g_62e0b8.reflectionsDelay = 0.012f;
    g_62e0b8.reverb = 83;
    g_62e0b8.reverbDelay = 0.017f;
    g_62e0b8.environment = 5;
    g_62e0b8.environmentSize = 11.6f;
    g_62e0b8.environmentDiffusion = 1.0f;
    g_62e0b8.airAbsorptionHF = -5.0f;
    g_62e0b8.flags = 0x2f;
}

// FUNCTION: STUNTGP_D3D 0x4608a0
void FUN_4608a0()
{
    memset(&g_62e0b8, 0, sizeof(g_62e0b8));
    g_62e0b8.room = -200;
    g_62e0b8.roomHF = -1000;
    g_62e0b8.roomRolloffFactor = 0.0f;
    g_62e0b8.decayTime = 2.81f;
    g_62e0b8.decayHFRatio = 0.14f;
    g_62e0b8.reflections = 429;
    g_62e0b8.reflectionsDelay = 0.014f;
    g_62e0b8.reverb = 1023;
    g_62e0b8.reverbDelay = 0.021f;
    g_62e0b8.environment = 21;
    g_62e0b8.environmentSize = 1.7f;
    g_62e0b8.environmentDiffusion = 0.8f;
    g_62e0b8.airAbsorptionHF = -5.0f;
    g_62e0b8.flags = 0x2f;
}

// FUNCTION: STUNTGP_D3D 0x460940
void FUN_460940()
{
    memset(&g_62e0b8, 0, sizeof(g_62e0b8));
    g_62e0b8.room = -1100;
    g_62e0b8.roomHF = -1000;
    g_62e0b8.roomRolloffFactor = 0.0f;
    g_62e0b8.decayTime = 2.81f;
    g_62e0b8.decayHFRatio = 0.14f;
    g_62e0b8.reflections = 429;
    g_62e0b8.reflectionsDelay = 0.014f;
    g_62e0b8.reverb = 1023;
    g_62e0b8.reverbDelay = 0.021f;
    g_62e0b8.environment = 21;
    g_62e0b8.environmentSize = 1.7f;
    g_62e0b8.environmentDiffusion = 0.8f;
    g_62e0b8.airAbsorptionHF = -5.0f;
    g_62e0b8.flags = 0x2f;
}

// FUNCTION: STUNTGP_D3D 0x4609e0
void FUN_4609e0()
{
    memset(&g_62e0b8, 0, sizeof(g_62e0b8));
    g_62e0b8.room = -500;
    g_62e0b8.roomHF = -1000;
    g_62e0b8.roomRolloffFactor = 0.0f;
    g_62e0b8.decayTime = 2.81f;
    g_62e0b8.decayHFRatio = 0.14f;
    g_62e0b8.reflections = 429;
    g_62e0b8.reflectionsDelay = 0.014f;
    g_62e0b8.reverb = 1023;
    g_62e0b8.reverbDelay = 0.021f;
    g_62e0b8.environment = 21;
    g_62e0b8.environmentSize = 1.7f;
    g_62e0b8.environmentDiffusion = 0.8f;
    g_62e0b8.airAbsorptionHF = -5.0f;
    g_62e0b8.flags = 0x2f;
}

// FUNCTION: STUNTGP_D3D 0x460a80
int FUN_460a80()
{
    LPKSPROPERTYSET propertySet = NULL;
    if (g_62e118[1].buffer3d->QueryInterface(IID_IKsPropertySet, (void **)&propertySet) != DS_OK)
    {
        return 0;
    }
    if (!FUN_460700(propertySet, 1))
    {
        return 0;
    }
    propertySet->Set(DSPROPSETID_EAX20_ListenerProperties, 1, NULL, 0, &g_62e0b8, sizeof(g_62e0b8));
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x460af0
void FUN_460af0(int zone)
{
    if (g_soundInitialised == 1 && g_4897b0 == 1)
    {
        switch (zone)
        {
        case 0:
            FUN_460760();
            FUN_460a80();
            break;
        case 1:
            FUN_460800();
            FUN_460a80();
            break;
        case 2:
            FUN_460800();
            FUN_460a80();
            break;
        case 3:
            FUN_460800();
            FUN_460a80();
            break;
        case 4:
            FUN_4608a0();
            FUN_460a80();
            break;
        case 5:
            FUN_460940();
            FUN_460a80();
            break;
        case 6:
            FUN_4609e0();
            FUN_460a80();
            break;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x460ca0
void FUN_460ca0()
{
    g_sfxVolumeTarget = 0;
}

// FUNCTION: STUNTGP_D3D 0x460cb0
void FUN_460cb0(int volume)
{
    if (volume != -1)
    {
        g_sfxVolume = volume;
    }
    g_sfxVolumeTarget = g_masterVolume * g_sfxSetting * 255 / 10000;
}

// FUNCTION: STUNTGP_D3D 0x460ce0
void FUN_460ce0()
{
    if (g_sfxVolume != g_sfxVolumeTarget)
    {
        if (g_sfxVolume < g_sfxVolumeTarget)
        {
            g_sfxVolume += 4;
            if (g_sfxVolume > g_sfxVolumeTarget)
            {
                g_sfxVolume = g_sfxVolumeTarget;
            }
        }
        else
        {
            g_sfxVolume -= 4;
            if (g_sfxVolume < g_sfxVolumeTarget)
            {
                g_sfxVolume = g_sfxVolumeTarget;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x460d20
void FUN_460d20(unsigned int n)
{
    g_4897a0 = n;
    g_4897a4 = n * n;
    g_4897a8 = 1.0f / n;
}

// FUNCTION: STUNTGP_D3D 0x460d60
void FUN_460d60(int index)
{
    if (g_soundInitialised)
    {
        if (g_62e118[index].buffer)
        {
            g_62e118[index].buffer->Stop();
        }
        g_62f5b4--;
    }
}

// FUNCTION: STUNTGP_D3D 0x460d90
void FUN_460d90(int *channel)
{
    if (g_soundInitialised && *channel)
    {
        LPDIRECTSOUNDBUFFER buffer = g_62e118[*channel].buffer;
        if (buffer)
        {
            buffer->Stop();
        }
        *channel = 0;
        g_62f5b4--;
    }
}

// FUNCTION: STUNTGP_D3D 0x460dd0
void FUN_460dd0()
{
    for (unsigned int i = 0; i < 128; i++)
    {
        FUN_460d60(i);
    }
}

// FUNCTION: STUNTGP_D3D 0x460df0
void FUN_460df0()
{
    if (g_62f5b0 != 0)
    {
        SoundChannel *slot = &g_62e118[72];
        for (int i = 0; i < 32; i++, slot++)
        {
            LPDIRECTSOUNDBUFFER buffer = slot->buffer;
            if (buffer)
            {
                DWORD status;
                LPDIRECTSOUND3DBUFFER buffer3d = slot->buffer3d;
                if (buffer->GetStatus(&status) == DS_OK && status == 0)
                {
                    if (buffer3d)
                    {
                        buffer3d->Release();
                    }
                    buffer->Release();
                    slot->buffer = NULL;
                    slot->buffer3d = NULL;
                    g_62f5b0--;
                }
            }
        }
    }
}

// If the 3D sound is already playing, swaps it for a duplicate in a free one-shot slot.
// FUNCTION: STUNTGP_D3D 0x460e70
int FUN_460e70(LPDIRECTSOUNDBUFFER *buffer, LPDIRECTSOUND3DBUFFER *buffer3d, int channel, int *slotIndex)
{
    LPDIRECTSOUNDBUFFER copy;
    DWORD status;
    LPDIRECTSOUND3DBUFFER copy3d;
    LPDIRECTSOUNDBUFFER source = *buffer;
    if (source->GetStatus(&status) != DS_OK)
    {
        return 0;
    }
    if (status & DSBSTATUS_PLAYING)
    {
        if ((int)g_62f5b0 >= 32)
        {
            return 0;
        }
        SoundChannel *slot = &g_62e118[72];
        while (slot->buffer)
        {
            slot++;
        }
        if (g_directSound->DuplicateSoundBuffer(source, &copy) != DS_OK)
        {
            return 0;
        }
        if (copy->QueryInterface(IID_IDirectSound3DBuffer, (void **)&copy3d) != DS_OK)
        {
            copy->Release();
            return 0;
        }
        *buffer = copy;
        slot->buffer = copy;
        *buffer3d = copy3d;
        slot->buffer3d = copy3d;
        g_62f5b0++;
        slot->type = g_62e118[channel].type;
        if (slotIndex)
        {
            *slotIndex = slot - g_62e118;
        }
    }
    return 1;
}

// If the sound is already playing, swaps it for a duplicate in a free one-shot slot.
// FUNCTION: STUNTGP_D3D 0x460f70
int FUN_460f70(LPDIRECTSOUNDBUFFER *buffer, int channel, int *slotIndex)
{
    LPDIRECTSOUNDBUFFER source = *buffer;
    DWORD status;
    if (source->GetStatus(&status) != DS_OK)
    {
        return 0;
    }
    if (status & DSBSTATUS_PLAYING)
    {
        if ((int)g_62f5b0 >= 32)
        {
            return 0;
        }
        SoundChannel *slot = &g_62e118[72];
        while (slot->buffer)
        {
            slot++;
        }
        if (g_directSound->DuplicateSoundBuffer(source, &slot->buffer) != DS_OK)
        {
            return 0;
        }
        *buffer = slot->buffer;
        g_62f5b0++;
        slot->type = g_62e118[channel].type;
        if (slotIndex)
        {
            *slotIndex = slot - g_62e118;
        }
    }
    return 1;
}

// Plays a sample on a 2D channel; the 3D processing is switched off.
// FUNCTION: STUNTGP_D3D 0x461030
void FUN_461030(int channel, int loop, DWORD frequency, DWORD volume, int pan, int keep, int *slotIndex)
{
    if (!g_soundInitialised)
    {
        return;
    }
    if ((DWORD)g_62f5b4 > 0x18)
    {
        return;
    }
    LPDIRECTSOUNDBUFFER buffer = g_62e118[channel].buffer;
    if (!buffer)
    {
        return;
    }
    LPDIRECTSOUND3DBUFFER buffer3d = g_62e118[channel].buffer3d;
    if (!buffer3d)
    {
        return;
    }
    if (!keep)
    {
        if (FUN_460e70(&buffer, &buffer3d, channel, slotIndex) != 1)
        {
            return;
        }
    }
    buffer3d->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);
    if (!frequency)
    {
        frequency = g_62e118[channel].rate;
    }
    buffer->SetFrequency(frequency);
    buffer->SetVolume(g_4897f8[g_sfxVolume * volume >> 9]);
    int value = g_4897f8[128 - ((abs(pan) + 1) >> 1)];
    if (pan < 0)
    {
        value = -value;
    }
    buffer->SetPan(value);
    if (loop == 1)
    {
        buffer->Play(0, 0, DSBPLAY_LOOPING);
        g_62f5b4++;
    }
    else
    {
        buffer->Play(0, 0, 0);
        g_62f5b4++;
    }
}

// Nearest active player camera to a point, or the first one in single view.
// FUNCTION: STUNTGP_D3D 0x461270
GameSlot *FUN_461270(Vec4 *pos)
{
    if (!g_576be0)
    {
        return g_498248;
    }
    GameSlot *best = g_498248;
    float bestDist = 2.5e11f;
    GameSlot *slot = g_498248;
    for (int i = 0; i < 4; i++, slot++)
    {
        if (slot->active == 1)
        {
            float dx = slot->cam.pos.x - pos->x;
            float dy = slot->cam.pos.y - pos->y;
            float dz = slot->cam.pos.z - pos->z;
            float dist = dz * dz + dy * dy + dx * dx;
            if (dist <= bestDist)
            {
                bestDist = dist;
                best = slot;
            }
        }
    }
    return best;
}

// GLOBAL: STUNTGP_D3D 0x4897b8
DS3DBUFFER g_4897b8 = {sizeof(DS3DBUFFER), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 360, 360, {0.0f, 0.0f, 1.0f},
                       0, 1300.0f, 7500.0f, DS3DMODE_NORMAL};

// Plays a sample at a world position; nothing is played out of range of the nearest camera.
// FUNCTION: STUNTGP_D3D 0x461300
void FUN_461300(int channel, int loop, DWORD frequency, DWORD volume, Vec4 *pos, Vec4 *velocity, int keep,
                int *slotIndex)
{
    if (!g_soundInitialised)
    {
        return;
    }
    if ((DWORD)g_62f5b4 > 0x18)
    {
        return;
    }
    SoundChannel *ch = &g_62e118[channel];
    if (!ch->buffer)
    {
        return;
    }
    LPDIRECTSOUNDBUFFER buffer = ch->buffer;
    LPDIRECTSOUND3DBUFFER buffer3d = ch->buffer3d;
    if (!buffer3d)
    {
        return;
    }
    GameSlot *slot = FUN_461270(pos);
    float dx = slot->cam.pos.x - pos->x;
    float dy = slot->cam.pos.y - pos->y;
    float dz = slot->cam.pos.z - pos->z;
    if (dz * dz + dy * dy + dx * dx > g_4897a4)
    {
        return;
    }
    if (!frequency)
    {
        frequency = ch->rate;
    }
    if (slotIndex)
    {
        *slotIndex = channel;
    }
    if (!keep)
    {
        if (FUN_460e70(&buffer, &buffer3d, channel, slotIndex) != 1)
        {
            return;
        }
    }
    DS3DBUFFER params = g_4897b8;
    params.flMaxDistance = g_4897a0;
    params.vPosition.x = pos->x;
    params.vPosition.y = pos->y;
    params.vPosition.z = pos->z;
    if (velocity)
    {
        params.vVelocity.x = velocity->x;
        params.vVelocity.y = velocity->y;
        params.vVelocity.z = velocity->z;
    }
    buffer3d->SetAllParameters(&params, DS3D_IMMEDIATE);
    buffer->SetFrequency(frequency);
    buffer->SetVolume(g_4897f8[g_sfxVolume * volume >> 9]);
    if (loop == 1)
    {
        buffer->Play(0, 0, DSBPLAY_LOOPING);
        g_62f5b4++;
    }
    else
    {
        buffer->Play(0, 0, 0);
        g_62f5b4++;
    }
}

// Moves a playing 3D sound; it is stopped once it is out of range of the nearest camera.
// FUNCTION: STUNTGP_D3D 0x461730
void FUN_461730(int *channel, DWORD frequency, int volume, Vec4 *pos, Vec4 *velocity)
{
    if (!g_soundInitialised)
    {
        return;
    }
    SoundChannel *ch = &g_62e118[*channel];
    LPDIRECTSOUNDBUFFER buffer = ch->buffer;
    if (!buffer)
    {
        return;
    }
    LPDIRECTSOUND3DBUFFER buffer3d = ch->buffer3d;
    if (!buffer3d)
    {
        return;
    }
    GameSlot *slot = FUN_461270(pos);
    float x = pos->x;
    float y = pos->y;
    float z = pos->z;
    float dx = slot->cam.pos.x - x;
    float dy = slot->cam.pos.y - y;
    float dz = slot->cam.pos.z - z;
    if (dz * dz + dy * dy + dx * dx > g_4897a4)
    {
        FUN_460d90(channel);
        return;
    }
    buffer3d->SetPosition(x, y, z, DS3D_IMMEDIATE);
    if (velocity)
    {
        buffer3d->SetVelocity(velocity->x, velocity->y, velocity->z, DS3D_IMMEDIATE);
    }
    if (!frequency)
    {
        frequency = ch->rate;
    }
    buffer->SetFrequency(frequency);
    buffer->SetVolume(g_4897f8[(DWORD)(g_sfxVolume * volume) >> 9]);
}

// FUNCTION: STUNTGP_D3D 0x461ae0
void FUN_461ae0(LPDIRECTSOUND3DLISTENER listener, GameSlot *slot)
{
    if (listener && slot->active)
    {
        listener->SetPosition(slot->cam.pos.x, slot->cam.pos.y, slot->cam.pos.z, DS3D_IMMEDIATE);
        listener->SetVelocity(slot->velX, slot->velY, slot->velZ, DS3D_IMMEDIATE);
        listener->SetOrientation(
            slot->axisZ.x, slot->axisZ.y, slot->axisZ.z, -slot->axisY.x, -slot->axisY.y, -slot->axisY.z, DS3D_IMMEDIATE
        );
    }
}

// FUNCTION: STUNTGP_D3D 0x462200
void FUN_462200()
{
    DWORD status;
    g_62f5b4 = 0;
    for (DWORD i = 0; i < g_62f5b0 + 72; i++)
    {
        if (g_62e118[i].buffer && g_62e118[i].buffer->GetStatus(&status) == DS_OK && (status & DSBSTATUS_PLAYING))
        {
            g_62f5b4++;
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x462260
int FUN_462260()
{
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x462270
void FUN_462270(int a)
{
}

// FUNCTION: STUNTGP_D3D 0x462280
void FUN_462280()
{
    if (g_soundInitialised)
    {
        FUN_460df0();
        if (g_4897b4 == 1)
        {
            FUN_461ae0(g_62f11c, g_498248);
            FUN_462200();
        }
        FUN_45f880();
        FUN_460ce0();
    }
}
