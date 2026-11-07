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
#endif /* SOUND_H */
