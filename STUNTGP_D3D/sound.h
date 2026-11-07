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
#endif /* SOUND_H */
