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
extern float g_624504;
extern float g_624508;
extern float g_62450c;
extern float g_624510;
