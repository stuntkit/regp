#include "GameUpdate.h"

#include <mmsystem.h>
#include <dsound.h>

struct SoundSlot
{
    LPDIRECTSOUNDBUFFER buffer;     // 0x00
    LPDIRECTSOUND3DBUFFER buffer3d; // 0x04
    BYTE unk08[0x18];               // 0x08
};

// GLOBAL: STUNTGP_D3D 0x489790
DWORD g_489790 = 0xff;

// GLOBAL: STUNTGP_D3D 0x489798
int g_489798 = 0xff;

// GLOBAL: STUNTGP_D3D 0x48979c
int g_48979c = 0xff;

// GLOBAL: STUNTGP_D3D 0x4897b4
int g_4897b4 = 1;

// GLOBAL: STUNTGP_D3D 0x60d734
int g_60d734;

// GLOBAL: STUNTGP_D3D 0x60d738
int g_60d738;

// GLOBAL: STUNTGP_D3D 0x62e0a8
int g_62e0a8;

// GLOBAL: STUNTGP_D3D 0x62e0ac
int g_62e0ac;

// GLOBAL: STUNTGP_D3D 0x62e0f0
int g_62e0f0;

// GLOBAL: STUNTGP_D3D 0x62e0f8
int g_62e0f8;

// GLOBAL: STUNTGP_D3D 0x62e104
int g_62e104;

// GLOBAL: STUNTGP_D3D 0x62e108
int g_62e108;

// GLOBAL: STUNTGP_D3D 0x62e110
int g_62e110;

// The first 72 slots are fixed sounds, the remaining 32 are one-shot copies.
// GLOBAL: STUNTGP_D3D 0x62e118
SoundSlot g_62e118[104];

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

// FUNCTION: STUNTGP_D3D 0x45f880
void FUN_45f880()
{
    if (g_62e0f8 != 0)
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

// FUNCTION: STUNTGP_D3D 0x460bc0
void FUN_460bc0()
{
    g_60d734 = g_62e0a8;
    g_62e0f8 = g_489790 * g_62e0a8 * 255 / 10000;
    g_60d738 = g_62e0f0;
    g_489798 = g_48979c = g_489790 * g_62e0f0 * 255 / 10000;
}

// FUNCTION: STUNTGP_D3D 0x460ce0
void FUN_460ce0()
{
    if (g_489798 != g_48979c)
    {
        if (g_489798 < g_48979c)
        {
            g_489798 += 4;
            if (g_489798 > g_48979c)
            {
                g_489798 = g_48979c;
            }
        }
        else
        {
            g_489798 -= 4;
            if (g_489798 < g_48979c)
            {
                g_489798 = g_48979c;
            }
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x460df0
void FUN_460df0()
{
    if (g_62f5b0 != 0)
    {
        SoundSlot *slot = &g_62e118[72];
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
    if (g_62e0ac)
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
