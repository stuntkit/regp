#ifndef SOUND_H
#define SOUND_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <mmsystem.h>

#include <dsound.h>

void FUN_45fab0();
void FUN_45fb40();
void Music_Stop();
BOOL Music_IsStreaming();
HRESULT Music_StopStream();
void Sound_ApplyVolumes();
void Sound_SetVolumes(DWORD master, DWORD sfx, DWORD music, DWORD quality);
void Sound_Shutdown();
extern DWORD g_masterVolume;
extern int g_sfxVolume;
extern int g_sfxVolumeTarget;
extern DWORD g_musicSetting;
extern BOOL g_soundInitialised;
extern DWORD g_sfxSetting;
extern DWORD g_musicVolume;
extern DWORD g_60d734;
extern DWORD g_60d738;
extern DWORD g_62f5ac;
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

extern DWORD g_soundQuality;
extern LPDIRECTSOUNDBUFFER g_musicBuffer;
extern DWORD g_musicFlags;
extern DWORD g_62df28;
extern DWORD g_62df2c;
extern DWORD g_62df30;
extern DWORD g_62df34;
extern UINT g_musicTimerPeriod;
extern UINT g_musicTimer;
extern HMMIO g_musicFile;
extern LONG g_musicDataOffset;
extern DWORD g_62e084;
extern BOOL g_musicPlaying;
extern HRESULT g_musicResult;
extern LPDIRECTSOUND g_directSound;
extern SoundChannel g_62e118[0x80];
void FUN_460d60(int index);
#endif /* SOUND_H */
