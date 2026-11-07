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
extern int g_musicVolume;
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

// EAX 2.0 listener properties (EAXLISTENERPROPERTIES)
struct EaxListener
{
    long room;                  // 0x00
    long roomHF;                // 0x04
    float roomRolloffFactor;    // 0x08
    float decayTime;            // 0x0c
    float decayHFRatio;         // 0x10
    long reflections;           // 0x14
    float reflectionsDelay;     // 0x18
    long reverb;                // 0x1c
    float reverbDelay;          // 0x20
    DWORD environment;          // 0x24
    float environmentSize;      // 0x28
    float environmentDiffusion; // 0x2c
    float airAbsorptionHF;      // 0x30
    DWORD flags;                // 0x34
};

extern EaxListener g_62e0b8;
extern int g_62e0fc;
extern int g_62e104;
extern int g_62e110;
extern int g_62e10c;
extern short g_4897f8[129];
extern int g_62df14;
extern int g_62df1c;
extern int g_62df3c;
extern int g_62df40;
extern char g_62df54[MAX_PATH];
extern int g_62f5a8;
extern char *g_4898fc[24];
extern char g_SoundDirectory[128];
HRESULT FUN_45fb50(LPDIRECTSOUND ds, char *file, DWORD flags, int a, int b, int c, int d);
void FUN_460d60(int index);
#endif /* SOUND_H */
