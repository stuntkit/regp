#define WIN32_LEAN_AND_MEAN

#include <cstdio>
#include <windows.h>

#include "../../globals.h"
#include "io_wad.h"

int Script_FindKey(char *script, char **value, char *key);
void Script_ReadString(char *pos, char **next, char *out);
void Script_ReadInt(char *pos, char **next, int *out);
void FUN_42d060(char *script, char *key);
void Script_ParseGameSettings(char *script);
void Script_ParseGameConfig();
