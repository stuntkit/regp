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
int FUN_461150(int id, int a, int b, int volume, int c, int d, int e);
extern DWORD g_masterVolume;
extern int g_sfxVolume;
extern int g_sfxVolumeTarget;
extern DWORD g_musicSetting;
extern BOOL g_soundInitialised;
extern DWORD g_sfxSetting;
extern int g_musicVolume;
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

// Streamed music: a looping DirectSound buffer refilled from a wav file by a
// multimedia timer, which gets the whole block as its user data.
struct MusicStream
{
    LPDIRECTSOUNDBUFFER buffer;       // 0x000
    DWORD bufferSize;                 // 0x004, bytes
    DWORD unk008;                     // 0x008
    int periods;                      // 0x00c, buffer length in timer delays
    BYTE blockShift;                  // 0x010, log2 of the format's block align
    UINT timerDelay;                  // 0x014, ms
    UINT timerResolution;             // 0x018, ms
    int blocks;                       // 0x01c, buffer length in blocks, rounded up
    DWORD writePos;                   // 0x020
    DWORD played;                     // 0x024, bytes played since the start
    DWORD dataRead;                   // 0x028, bytes read from the data chunk
    DWORD playPos;                    // 0x02c
    DWORD flags;                      // 0x030
    LPTHREAD_START_ROUTINE onEnd;     // 0x034, run on a new thread at the end
    LPVOID onEndParam;                // 0x038
    TIMECAPS timeCaps;                // 0x03c
    UINT timerPeriod;                 // 0x044
    UINT timer;                       // 0x048
    char path[MAX_PATH];              // 0x04c
    WAVEFORMATEX format;              // 0x150
    HMMIO file;                       // 0x164
    MMCKINFO chunk;                   // 0x168, RIFF, then the data chunk
    DWORD unk17c;                     // 0x17c
    BOOL playing;                     // 0x180
    HRESULT result;                   // 0x184
    int pauseCount;                   // 0x188
    DWORD endMargin;                  // 0x18c, bytes
    DWORD tickTime;                   // 0x190, total ms spent in the timer
    DWORD tickAverage;                // 0x194
    DWORD ticks;                      // 0x198
};

extern MusicStream g_musicStream;
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
extern int g_62f5a8;
extern char *g_4898fc[24];
extern char g_SoundDirectory[128];
HRESULT FUN_45fb50(LPDIRECTSOUND ds, char *file, DWORD flags, int a, int b, LPTHREAD_START_ROUTINE onEnd,
                   LPVOID onEndParam);
void FUN_460d60(int index);
#endif /* SOUND_H */
