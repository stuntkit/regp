#include "sound.h"
#include "Game/GameEngine/GameSetup.h"

#include <stdlib.h>
#include <string.h>

DWORD WINAPI FUN_45fda0(LPVOID param);
HRESULT FUN_45ffd0();
HRESULT FUN_460240();
LONG FUN_4604e0(HPSTR buffer, DWORD size);
void CALLBACK FUN_460510(UINT id, UINT msg, DWORD user, DWORD dw1, DWORD dw2);
int FUN_462090();

extern int g_576be0;
extern int g_4897ac;
extern int g_4897b4;

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
MusicStream g_musicStream;

// GLOBAL: STUNTGP_D3D 0x62e0a4
DWORD g_62e0a4;

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
HRESULT FUN_45fb50(LPDIRECTSOUND ds, char *file, DWORD flags, int a, int b, LPTHREAD_START_ROUTINE onEnd,
                   LPVOID onEndParam)
{
    char path[MAX_PATH];
    if (g_musicStream.playing)
    {
        Music_Stop();
    }
    _fullpath(path, file, MAX_PATH);
    strncpy(g_musicStream.path, path, MAX_PATH);
    switch (flags & 0x78)
    {
    case 0x08:
        g_musicStream.timerDelay = 2000;
        g_musicStream.periods = 24;
        break;
    case 0x10:
        g_musicStream.timerDelay = 600;
        g_musicStream.periods = 5;
        break;
    case 0x20:
        g_musicStream.timerDelay = 400;
        g_musicStream.periods = 4;
        break;
    case 0x40:
        g_musicStream.timerDelay = 100;
        g_musicStream.periods = 3;
        break;
    default:
        if (!a || !b)
        {
            return E_INVALIDARG;
        }
        g_musicStream.timerDelay = a;
        g_musicStream.periods = b;
        break;
    }
    g_musicStream.flags = flags;
    g_musicStream.onEnd = onEnd;
    g_musicStream.onEndParam = onEndParam;
    if (flags & 2)
    {
        CreateThread(NULL, 0, FUN_45fda0, &g_musicStream, 0, &flags);
        g_musicStream.result = DS_OK;
        return DS_OK;
    }
    return FUN_45fda0(&g_musicStream);
}

// FUNCTION: STUNTGP_D3D 0x45fd40
void FUN_45fd40(LPDIRECTSOUNDBUFFER buffer)
{
    LPVOID data;
    DWORD size;
    if (buffer->Lock(0, g_musicStream.bufferSize, &data, &size, NULL, NULL, 0) == DS_OK)
    {
        memset(data, 0, g_musicStream.bufferSize);
        buffer->Unlock(data, g_musicStream.bufferSize, NULL, 0);
    }
}

// FUNCTION: STUNTGP_D3D 0x45fda0
DWORD WINAPI FUN_45fda0(LPVOID param)
{
    MusicStream *stream = (MusicStream *)param;
    char root[5] = {0};
    DWORD unused;
    DWORD bytesPerSector;
    BYTE shift;
    DSBUFFERDESC desc;
    HRESULT hr;
    if (timeGetDevCaps(&stream->timeCaps, sizeof(TIMECAPS)) != TIMERR_NOERROR)
    {
        __asm int 3
        return E_FAIL;
    }
    stream->timerPeriod = min(max(stream->timeCaps.wPeriodMin, 1), stream->timeCaps.wPeriodMax);
    timeBeginPeriod(stream->timerPeriod);
    strncpy(root, stream->path, 3);
    if (GetDriveTypeA(root) == DRIVE_REMOVABLE)
    {
        return E_FAIL;
    }
    GetDiskFreeSpaceA(root, &unused, &bytesPerSector, &unused, &unused);
    __asm
    {
        push eax
        bsf eax, bytesPerSector
        mov shift, al
        pop eax
    }
    stream->blockShift = shift;
    if (FUN_45ffd0())
    {
        return 0;
    }
    UINT resolution = stream->timerDelay / 4;
    stream->timerResolution = resolution;
    float avg = stream->format.nAvgBytesPerSec;
    float delay = stream->timerDelay;
    stream->bufferSize = (DWORD)(delay * avg * 0.001f) * stream->periods;
    stream->blocks = (stream->bufferSize >> shift) + 1;
    if ((1 << shift) * stream->blocks < (DWORD)(avg / (1000.0f / delay)))
    {
        Music_Stop();
        stream->result = E_FAIL;
        return E_FAIL;
    }
    stream->endMargin = (stream->timerDelay + resolution) * (stream->format.nAvgBytesPerSec / 1000);
    memset(&desc, 0, sizeof(desc));
    desc.dwSize = sizeof(desc);
    desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_LOCSOFTWARE;
    desc.dwBufferBytes = stream->bufferSize;
    desc.lpwfxFormat = &stream->format;
    hr = g_directSound->CreateSoundBuffer(&desc, &stream->buffer, NULL);
    stream->result = hr;
    if (hr != DS_OK)
    {
        Music_Stop();
        return hr;
    }
    FUN_45fd40(stream->buffer);
    stream->played = 0;
    stream->playPos = 0;
    stream->playing = TRUE;
    stream->flags |= 0x4000;
    if (stream->flags & 4)
    {
        hr = FUN_460240();
        stream->result = hr;
        if (hr != DS_OK)
        {
            Music_Stop();
            return hr;
        }
    }
    return stream->result;
}

// FUNCTION: STUNTGP_D3D 0x45ffd0
HRESULT FUN_45ffd0()
{
    MMIOINFO info;
    MMCKINFO chunk;
    WAVEFORMATEX *format;
    LONG size;
    memset(&info, 0, sizeof(info));
    info.cchBuffer = 0x400;
    g_musicStream.file = mmioOpenA(g_musicStream.path, &info, MMIO_ALLOCBUF);
    if (!g_musicStream.file)
    {
        return g_musicStream.result = E_INVALIDARG;
    }
    if (mmioDescend(g_musicStream.file, &g_musicStream.chunk, NULL, 0))
    {
        mmioClose(g_musicStream.file, 0);
        g_musicStream.file = NULL;
        return g_musicStream.result = DSERR_BADFORMAT;
    }
    if (g_musicStream.chunk.ckid != FOURCC_RIFF || g_musicStream.chunk.fccType != mmioFOURCC('W', 'A', 'V', 'E'))
    {
        mmioClose(g_musicStream.file, 0);
        g_musicStream.file = NULL;
        return g_musicStream.result = DSERR_BADFORMAT;
    }
    chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(g_musicStream.file, &chunk, &g_musicStream.chunk, MMIO_FINDCHUNK))
    {
        mmioClose(g_musicStream.file, 0);
        g_musicStream.file = NULL;
        return g_musicStream.result = DSERR_BADFORMAT;
    }
    size = chunk.cksize;
    format = (WAVEFORMATEX *)new BYTE[(WORD)size];
    if (mmioRead(g_musicStream.file, (HPSTR)format, size) != size)
    {
        delete format;
        mmioClose(g_musicStream.file, 0);
        return g_musicStream.result = DSERR_BADFORMAT;
    }
    g_musicStream.format = *format;
    delete format;
    if (g_musicStream.format.wFormatTag != WAVE_FORMAT_PCM)
    {
        mmioClose(g_musicStream.file, 0);
        g_musicStream.file = NULL;
        return g_musicStream.result = DSERR_BADFORMAT;
    }
    if (mmioAscend(g_musicStream.file, &chunk, 0))
    {
        mmioClose(g_musicStream.file, 0);
        g_musicStream.file = NULL;
        return g_musicStream.result = DSERR_BADFORMAT;
    }
    if (mmioSeek(g_musicStream.file, g_musicStream.chunk.dwDataOffset + 4, SEEK_SET) == -1)
    {
        mmioClose(g_musicStream.file, 0);
        g_musicStream.file = NULL;
        return g_musicStream.result = DSERR_BADFORMAT;
    }
    chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(g_musicStream.file, &chunk, &g_musicStream.chunk, MMIO_FINDCHUNK))
    {
        mmioClose(g_musicStream.file, 0);
        g_musicStream.file = NULL;
        return g_musicStream.result = DSERR_BADFORMAT;
    }
    g_musicStream.chunk = chunk;
    g_musicStream.dataRead = 0;
    return g_musicStream.result = DS_OK;
}


// FUNCTION: STUNTGP_D3D 0x45fce0
void Music_Stop()
{
    if (g_musicStream.playing)
    {
        Music_StopStream();
        g_musicStream.buffer->Release();
        timeEndPeriod(g_musicStream.timerPeriod);
        if (g_musicStream.file)
        {
            mmioClose(g_musicStream.file, 0);
            g_musicStream.file = NULL;
        }
        g_musicStream.playing = FALSE;
        g_musicStream.flags &= ~0x4000;
    }
}

// FUNCTION: STUNTGP_D3D 0x460200
BOOL Music_IsStreaming()
{
    if (g_musicStream.playing && (g_musicStream.flags & 0x4000))
    {
        return TRUE;
    }
    return FALSE;
}

// FUNCTION: STUNTGP_D3D 0x460220
int FUN_460220()
{
    g_musicStream.buffer->GetStatus(&g_62e0a4);
    return g_62e0a4 & DSBSTATUS_PLAYING;
}

// FUNCTION: STUNTGP_D3D 0x460240
HRESULT FUN_460240()
{
    LPVOID data;
    DWORD size;
    if (!Music_IsStreaming())
    {
        return g_musicStream.result = DSERR_UNINITIALIZED;
    }
    if (!FUN_460220())
    {
        g_musicStream.buffer->Lock(0, g_musicStream.bufferSize, &data, &size, NULL, NULL, 0);
        FUN_4604e0((HPSTR)data, size);
        g_musicStream.buffer->Unlock(data, g_musicStream.bufferSize, NULL, 0);
        g_musicStream.buffer->SetVolume(g_4897f8[0]);
        g_musicStream.result = g_musicStream.buffer->Play(0, 0, DSBPLAY_LOOPING);
        g_musicStream.timer = timeSetEvent(g_musicStream.timerDelay, g_musicStream.timerResolution, FUN_460510,
                                           (DWORD)&g_musicStream, TIME_PERIODIC);
        InterlockedExchange((LONG *)&g_musicStream.flags, g_musicStream.flags & ~0x8000);
        return g_musicStream.result;
    }
    g_musicStream.result = DS_OK;
    return DS_OK;
}

// FUNCTION: STUNTGP_D3D 0x460330
HRESULT Music_StopStream()
{
    if (!Music_IsStreaming())
    {
        return g_musicStream.result = DSERR_UNINITIALIZED;
    }
    InterlockedExchange((LONG *)&g_musicStream.flags, g_musicStream.flags | 0x8000);
    if (g_musicStream.timer)
    {
        timeKillEvent(g_musicStream.timer);
        g_musicStream.timer = 0;
    }
    g_musicStream.buffer->Stop();
    g_musicStream.buffer->SetCurrentPosition(0);
    g_musicStream.writePos = 0;
    g_musicStream.played = 0;
    g_musicStream.dataRead = 0;
    g_musicStream.playPos = 0;
    g_musicStream.unk17c = 0;
    if (g_musicStream.file)
    {
        mmioSeek(g_musicStream.file, g_musicStream.chunk.dwDataOffset + 4, SEEK_SET);
    }
    g_62f5ac = 0;
    g_musicStream.result = DS_OK;
    return DS_OK;
}

// FUNCTION: STUNTGP_D3D 0x4603e0
HRESULT FUN_4603e0()
{
    if (!Music_IsStreaming())
    {
        return g_musicStream.result = DSERR_UNINITIALIZED;
    }
    if (!g_musicStream.pauseCount && FUN_460220())
    {
        g_musicStream.pauseCount++;
        InterlockedExchange((LONG *)&g_musicStream.flags, g_musicStream.flags | 0x8000);
        g_musicStream.buffer->Stop();
        timeKillEvent(g_musicStream.timer);
    }
    g_musicStream.result = DS_OK;
    return DS_OK;
}

// FUNCTION: STUNTGP_D3D 0x460450
HRESULT FUN_460450()
{
    if (!Music_IsStreaming())
    {
        return g_musicStream.result = DSERR_UNINITIALIZED;
    }
    if (g_musicStream.pauseCount && --g_musicStream.pauseCount == 0 && (g_musicStream.flags & 0x8000))
    {
        // The original passes no user data here, unlike FUN_460240.
        g_musicStream.timer =
            timeSetEvent(g_musicStream.timerDelay, g_musicStream.timerResolution, FUN_460510, 0, TIME_PERIODIC);
        g_musicStream.buffer->Play(0, 0, DSBPLAY_LOOPING);
        InterlockedExchange((LONG *)&g_musicStream.flags, g_musicStream.flags & ~0x8000);
    }
    g_musicStream.result = DS_OK;
    return DS_OK;
}

// FUNCTION: STUNTGP_D3D 0x4604e0
LONG FUN_4604e0(HPSTR buffer, DWORD size)
{
    DWORD left = g_musicStream.chunk.cksize - g_musicStream.dataRead - 0x100;
    if (size > left)
    {
        size = left;
    }
    LONG read = mmioRead(g_musicStream.file, buffer, size);
    g_musicStream.dataRead += read;
    return read;
}

// FUNCTION: STUNTGP_D3D 0x460510
void CALLBACK FUN_460510(UINT id, UINT msg, DWORD user, DWORD dw1, DWORD dw2)
{
    MusicStream *stream;
    LPDIRECTSOUNDBUFFER buffer;
    DWORD play;
    DWORD write;
    int blocks;
    int delta;
    DWORD start;
    int bytes;
    LPVOID data1;
    LPVOID data2;
    DWORD size1;
    DWORD size2;
    LONG read2;
    LONG read1;
    if (((MusicStream *)user)->flags & 0x8000)
    {
        return;
    }
    if (!(((MusicStream *)user)->flags & 0x4000))
    {
        return;
    }
    stream = (MusicStream *)user;
    buffer = stream->buffer;
    buffer->GetCurrentPosition(&play, &write);
    blocks = play - stream->writePos;
    if (blocks < 0)
    {
        blocks += stream->bufferSize;
    }
    delta = play - stream->playPos;
    if (delta < 0)
    {
        delta += stream->bufferSize;
    }
    stream->played += delta;
    stream->playPos = play;
    stream->unk17c = stream->played;
    if (!(stream->flags & 1) && stream->played >= stream->chunk.cksize - stream->endMargin)
    {
        Music_StopStream();
        if (stream->onEnd)
        {
            CreateThread(NULL, 0, stream->onEnd, stream->onEndParam, 0, &write);
        }
        return;
    }
    if (stream->chunk.cksize - stream->dataRead - 0x100 == 0)
    {
        return;
    }
    start = timeGetTime();
    stream->ticks++;
    blocks >>= stream->blockShift;
    if (blocks > stream->blocks)
    {
        blocks = stream->blocks;
    }
    bytes = blocks << stream->blockShift;
    if (blocks > 0)
    {
        read1 = read2 = 0;
        DWORD pos = stream->writePos;
        buffer->Lock(pos, bytes, &data1, &size1, &data2, &size2, 0);
        if (data1)
        {
            read1 = FUN_4604e0((HPSTR)data1, size1);
        }
        if (data2)
        {
            read2 = FUN_4604e0((HPSTR)data2, size2);
        }
        buffer->Unlock(data1, size1, data2, size2);
        stream->writePos = pos + read2 + read1;
        if (stream->writePos >= stream->bufferSize)
        {
            stream->writePos -= stream->bufferSize;
        }
        if (read2 + read1 < bytes && (stream->flags & 1))
        {
            stream->played = 0;
            stream->dataRead = 0;
            mmioSeek(stream->file, stream->chunk.dwDataOffset + 4, SEEK_SET);
            if (stream->onEnd)
            {
                CreateThread(NULL, 0, stream->onEnd, stream->onEndParam, 0, &write);
            }
        }
    }
    stream->tickTime += timeGetTime() - start;
    stream->tickAverage = stream->tickTime / stream->ticks;
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
