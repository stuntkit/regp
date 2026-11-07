#include "sound.h"

// GLOBAL: STUNTGP_D3D 0x489790
DWORD g_masterVolume = 255;

// GLOBAL: STUNTGP_D3D 0x489794
DWORD g_soundQuality = 22050;

// GLOBAL: STUNTGP_D3D 0x489798
DWORD g_sfxVolume = 255;

// GLOBAL: STUNTGP_D3D 0x48979c
DWORD g_sfxVolumeTarget = 255;

// GLOBAL: STUNTGP_D3D 0x62df08
LPDIRECTSOUNDBUFFER g_musicBuffer;

// GLOBAL: STUNTGP_D3D 0x62df38
DWORD g_musicFlags;

// GLOBAL: STUNTGP_D3D 0x62df4c
UINT g_musicTimerPeriod;

// GLOBAL: STUNTGP_D3D 0x62e06c
HMMIO g_musicFile;

// GLOBAL: STUNTGP_D3D 0x62e088
BOOL g_musicPlaying;

// GLOBAL: STUNTGP_D3D 0x62e0a8
DWORD g_musicSetting;

// GLOBAL: STUNTGP_D3D 0x62e0ac
BOOL g_soundInitialised;

// GLOBAL: STUNTGP_D3D 0x62e0b0
LPDIRECTSOUND g_directSound;

// GLOBAL: STUNTGP_D3D 0x62e0f0
DWORD g_sfxSetting;

// GLOBAL: STUNTGP_D3D 0x62e0f8
DWORD g_musicVolume;

// GLOBAL: STUNTGP_D3D 0x60d734
DWORD g_60d734;

// GLOBAL: STUNTGP_D3D 0x60d738
DWORD g_60d738;

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

// FUNCTION: STUNTGP_D3D 0x45fce0
void Music_Stop()
{
    if (g_musicPlaying)
    {
        FUN_460330();
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

// STUB: STUNTGP_D3D 0x460330
int FUN_460330()
{
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x460bc0
void Sound_ApplyVolumes()
{
    g_60d734 = g_musicSetting;
    g_60d738 = g_sfxSetting;
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
