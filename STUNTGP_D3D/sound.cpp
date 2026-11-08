#include "sound.h"
#include "Game/GameEngine/GameSetup.h"

#include <stdlib.h>
#include <string.h>

DWORD WINAPI FUN_45fda0(LPVOID param);
int FUN_462090();

extern int g_576be0;
extern int g_4897ac;
extern int g_4897b4;
extern int g_62df0c;

// GLOBAL: STUNTGP_D3D 0x489790
DWORD g_masterVolume = 255;

// GLOBAL: STUNTGP_D3D 0x489794
DWORD g_soundQuality = 22050;

// GLOBAL: STUNTGP_D3D 0x489798
int g_sfxVolume = 255;

// GLOBAL: STUNTGP_D3D 0x48979c
int g_sfxVolumeTarget = 255;

// GLOBAL: STUNTGP_D3D 0x4899d8
int g_4899d8 = -1;

// GLOBAL: STUNTGP_D3D 0x62df08
LPDIRECTSOUNDBUFFER g_musicBuffer;

// GLOBAL: STUNTGP_D3D 0x62e0a4
DWORD g_62e0a4;

// GLOBAL: STUNTGP_D3D 0x62df38
DWORD g_musicFlags;

// GLOBAL: STUNTGP_D3D 0x62df28
DWORD g_62df28;

// GLOBAL: STUNTGP_D3D 0x62df2c
DWORD g_62df2c;

// GLOBAL: STUNTGP_D3D 0x62df30
DWORD g_62df30;

// GLOBAL: STUNTGP_D3D 0x62df34
DWORD g_62df34;

// GLOBAL: STUNTGP_D3D 0x62df4c
UINT g_musicTimerPeriod;

// GLOBAL: STUNTGP_D3D 0x62df50
UINT g_musicTimer;

// GLOBAL: STUNTGP_D3D 0x62e06c
HMMIO g_musicFile;

// GLOBAL: STUNTGP_D3D 0x62e074
DWORD g_62e074;

// GLOBAL: STUNTGP_D3D 0x62e07c
LONG g_musicDataOffset;

// GLOBAL: STUNTGP_D3D 0x62e084
DWORD g_62e084;

// GLOBAL: STUNTGP_D3D 0x62e088
BOOL g_musicPlaying;

// GLOBAL: STUNTGP_D3D 0x62e08c
HRESULT g_musicResult;

// GLOBAL: STUNTGP_D3D 0x62e0a8
DWORD g_musicSetting;

// GLOBAL: STUNTGP_D3D 0x62e0ac
BOOL g_soundInitialised;

// GLOBAL: STUNTGP_D3D 0x62e0b0
LPDIRECTSOUND g_directSound;

// GLOBAL: STUNTGP_D3D 0x62e0f0
DWORD g_sfxSetting;

// GLOBAL: STUNTGP_D3D 0x62e0f8
int g_musicVolume;

// GLOBAL: STUNTGP_D3D 0x62f5ac
DWORD g_62f5ac;

// FUNCTION: STUNTGP_D3D 0x45fab0
void FUN_45fab0()
{
    if (g_musicVolume)
    {
        FUN_45fb40();
    }
}

// FUNCTION: STUNTGP_D3D 0x45fb40
void FUN_45fb40()
{
    Music_Stop();
}

// FUNCTION: STUNTGP_D3D 0x45fb50
HRESULT FUN_45fb50(LPDIRECTSOUND ds, char *file, DWORD flags, int a, int b, int c, int d)
{
    char path[MAX_PATH];
    if (g_musicPlaying)
    {
        Music_Stop();
    }
    _fullpath(path, file, MAX_PATH);
    strncpy(g_62df54, path, MAX_PATH);
    switch (flags & 0x78)
    {
    case 0x08:
        g_62df1c = 2000;
        g_62df14 = 24;
        break;
    case 0x10:
        g_62df1c = 600;
        g_62df14 = 5;
        break;
    case 0x20:
        g_62df1c = 400;
        g_62df14 = 4;
        break;
    case 0x40:
        g_62df1c = 100;
        g_62df14 = 3;
        break;
    default:
        if (!a || !b)
        {
            return E_INVALIDARG;
        }
        g_62df1c = a;
        g_62df14 = b;
        break;
    }
    g_musicFlags = flags;
    g_62df3c = c;
    g_62df40 = d;
    if (flags & 2)
    {
        CreateThread(NULL, 0, FUN_45fda0, &g_musicBuffer, 0, &flags);
        g_musicResult = DS_OK;
        return DS_OK;
    }
    return FUN_45fda0(&g_musicBuffer);
}

// FUNCTION: STUNTGP_D3D 0x45fd40
void FUN_45fd40(LPDIRECTSOUNDBUFFER buffer)
{
    LPVOID data;
    DWORD size;
    if (buffer->Lock(0, g_62df0c, &data, &size, NULL, NULL, 0) == DS_OK)
    {
        memset(data, 0, g_62df0c);
        buffer->Unlock(data, g_62df0c, NULL, 0);
    }
}

// STUB: STUNTGP_D3D 0x45fda0
DWORD WINAPI FUN_45fda0(LPVOID param)
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x45fce0
void Music_Stop()
{
    if (g_musicPlaying)
    {
        Music_StopStream();
        g_musicBuffer->Release();
        timeEndPeriod(g_musicTimerPeriod);
        if (g_musicFile)
        {
            mmioClose(g_musicFile, 0);
            g_musicFile = NULL;
        }
        g_musicPlaying = FALSE;
        g_musicFlags &= ~0x4000;
    }
}

// FUNCTION: STUNTGP_D3D 0x460200
BOOL Music_IsStreaming()
{
    if (g_musicPlaying && (g_musicFlags & 0x4000))
    {
        return TRUE;
    }
    return FALSE;
}

// FUNCTION: STUNTGP_D3D 0x460220
int FUN_460220()
{
    g_musicBuffer->GetStatus(&g_62e0a4);
    return g_62e0a4 & DSBSTATUS_PLAYING;
}

// FUNCTION: STUNTGP_D3D 0x460330
HRESULT Music_StopStream()
{
    if (!Music_IsStreaming())
    {
        return g_musicResult = DSERR_UNINITIALIZED;
    }
    InterlockedExchange((LONG *)&g_musicFlags, g_musicFlags | 0x8000);
    if (g_musicTimer)
    {
        timeKillEvent(g_musicTimer);
        g_musicTimer = 0;
    }
    g_musicBuffer->Stop();
    g_musicBuffer->SetCurrentPosition(0);
    g_62df28 = 0;
    g_62df2c = 0;
    g_62df30 = 0;
    g_62df34 = 0;
    g_62e084 = 0;
    if (g_musicFile)
    {
        mmioSeek(g_musicFile, g_musicDataOffset + 4, SEEK_SET);
    }
    g_62f5ac = 0;
    g_musicResult = DS_OK;
    return DS_OK;
}

// FUNCTION: STUNTGP_D3D 0x4604e0
void FUN_4604e0(HPSTR buffer, DWORD size)
{
    DWORD left = g_62e074 - g_62df30 - 0x100;
    if (size > left)
    {
        size = left;
    }
    g_62df30 += mmioRead(g_musicFile, buffer, size);
}

// FUNCTION: STUNTGP_D3D 0x460b80
void FUN_460b80()
{
    g_4899d8 = g_4897b4;
    g_4897b4 = g_576be0 ? 0 : g_4897ac;
    if (g_4899d8 != g_4897b4)
    {
        Sound_Shutdown();
        FUN_462090();
    }
}

// FUNCTION: STUNTGP_D3D 0x460bc0
void Sound_ApplyVolumes()
{
    g_60d730.music = g_musicSetting;
    g_60d730.sfx = g_sfxSetting;
    g_musicVolume = g_masterVolume * g_musicSetting * 255 / 10000;
    g_sfxVolumeTarget = g_sfxVolume = g_masterVolume * g_sfxSetting * 255 / 10000;
}

// FUNCTION: STUNTGP_D3D 0x460c20
void Sound_SetVolumes(DWORD master, DWORD sfx, DWORD music, DWORD quality)
{
    if (quality > 44100)
    {
        quality = 44100;
    }
    else if (quality < 5512)
    {
        quality = 5512;
    }
    g_soundQuality = quality;
    if (master <= 100)
    {
        g_masterVolume = master;
    }
    if (sfx <= 100)
    {
        g_sfxVolume = sfx;
    }
    if (music <= 100)
    {
        g_musicVolume = music;
    }
    g_sfxSetting = g_sfxVolume;
    g_musicSetting = g_musicVolume;
    Sound_ApplyVolumes();
}

// FUNCTION: STUNTGP_D3D 0x4621d0
void Sound_Shutdown()
{
    if (g_soundInitialised)
    {
        FUN_45fab0();
        if (g_directSound)
        {
            g_directSound->Release();
            g_directSound = NULL;
        }
    }
}

// STUB: STUNTGP_D3D 0x461150
int FUN_461150(int id, int a, int b, int volume, int c, int d, int e)
{
    return 0;
}
