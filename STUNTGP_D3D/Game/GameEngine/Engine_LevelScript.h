#ifndef ENGINE_LEVELSCRIPT_H
#define ENGINE_LEVELSCRIPT_H
#define WIN32_LEAN_AND_MEAN

#include <cstdio>
#include <windows.h>

#include "../../globals.h"
#include "../../mem.h"
#include "io_wad.h"

int Script_FindKey(char *script, char **value, char *key);
void Script_ReadString(char *pos, char **next, char *out);
void Script_ReadInt(char *pos, char **next, int *out);
void FUN_42d060(char *script, char *key);
void Script_ParseGameSettings(char *script);
void Script_ParseGameConfig();
void FUN_42d7e0();
void Script_GetFloat(char *section, char *key, float *out);
void Script_GetVector3(char *section, char *key, float *out);
void Script_GetInt(char *section, char *key, int *out);
void Script_GetFloatArray(char *section, char *key, float *out, DWORD count);
char *Script_GetWord(char *section, char *key);
// Ambient light from the level script; FUN_42d7e0 derives the scaled values.
struct Ambience
{
    float intensity; // 0x00
    float red;       // 0x04
    float green;     // 0x08
    float blue;      // 0x0c
    float r;         // 0x10
    float g;         // 0x14
    float b;         // 0x18
    int ir;          // 0x1c
    int ig;          // 0x20
    int ib;          // 0x24
};

#endif /* ENGINE_LEVELSCRIPT_H */
