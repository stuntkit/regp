#include "GameUpdate.h"
#include "../../sound.h"

#include <mmsystem.h>
#include <dsound.h>

// GLOBAL: STUNTGP_D3D 0x4897b0
int g_4897b0 = 1;

// GLOBAL: STUNTGP_D3D 0x4897b4
int g_4897b4 = 1;

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

// GLOBAL: STUNTGP_D3D 0x62f5b0
DWORD g_62f5b0;

// GLOBAL: STUNTGP_D3D 0x62f5b4
int g_62f5b4;

// GLOBAL: STUNTGP_D3D 0x62f5b8
int g_62f5b8;

// GLOBAL: STUNTGP_D3D 0x62f5bc
int g_62f5bc;

void FUN_461ae0(LPDIRECTSOUND3DLISTENER listener, GameSlot *slot);

// STUB: STUNTGP_D3D 0x45f7d0
void FUN_45f7d0(int a, int b)
{
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

// STUB: STUNTGP_D3D 0x460760
void FUN_460760()
{
}

// STUB: STUNTGP_D3D 0x460800
void FUN_460800()
{
}

// STUB: STUNTGP_D3D 0x4608a0
void FUN_4608a0()
{
}

// STUB: STUNTGP_D3D 0x460940
void FUN_460940()
{
}

// STUB: STUNTGP_D3D 0x4609e0
void FUN_4609e0()
{
}

// STUB: STUNTGP_D3D 0x460a80
int FUN_460a80()
{
    return 0;
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

// FUNCTION: STUNTGP_D3D 0x461ae0
void FUN_461ae0(LPDIRECTSOUND3DLISTENER listener, GameSlot *slot)
{
    if (listener && slot->active)
    {
        listener->SetPosition(slot->unk008, slot->unk00c, slot->unk010, DS3D_IMMEDIATE);
        listener->SetVelocity(slot->unk0c4, slot->unk0c8, slot->unk0cc, DS3D_IMMEDIATE);
        listener->SetOrientation(
            slot->unk09c, slot->unk0a0, slot->unk0a4, -slot->unk08c, -slot->unk090, -slot->unk094, DS3D_IMMEDIATE
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
