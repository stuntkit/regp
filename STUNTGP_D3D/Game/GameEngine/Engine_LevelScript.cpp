#include "Engine_LevelScript.h"

#include "../../sound.h"
#include "GameSetup.h"
#include "GameUpdate.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// GLOBAL: STUNTGP_D3D 0x48491c
char g_GraphicsDirectory[128] = "D:\\Game\\Graphics24\\";

// GLOBAL: STUNTGP_D3D 0x48499c
char g_GraphicsDirectory24Max[128] = "D:\\Game\\Graphics24Max\\";

// GLOBAL: STUNTGP_D3D 0x484a1c
char g_SoundDirectory[128] = "D:\\Game\\Sound";

extern DWORD g_60effc;
extern DWORD g_60f000[4];

// GLOBAL: STUNTGP_D3D 0x589604
char g_LevelScript[32];

// end of the current script section; FindKey ignores matches past it
// GLOBAL: STUNTGP_D3D 0x589624
char *g_ScriptSectionEnd;

// GLOBAL: STUNTGP_D3D 0x60dfa0
int g_DisplayBootGfx;

// GLOBAL: STUNTGP_D3D 0x60f018
int g_ControlMethod;

// GLOBAL: STUNTGP_D3D 0x60f2a0
int g_D3DDeviceIndex;

// GLOBAL: STUNTGP_D3D 0x60f2a4
int g_D3DDriverIndex;

// GLOBAL: STUNTGP_D3D 0x60f2a8
int g_D3DUVFix;

// GLOBAL: STUNTGP_D3D 0x60f2ac
int g_DisableFramerateCorrection;

// GLOBAL: STUNTGP_D3D 0x61b640
char g_GameLocation[256];

// FUNCTION: STUNTGP_D3D 0x42c580
int Script_FindKey(char *script, char **value, char *key)
{
    char *found = strstr(script, key);
    if ((g_ScriptSectionEnd != NULL) && ((found > g_ScriptSectionEnd) || (found == NULL)))
    {
        return 0;
    }
    // STRING: STUNTGP_D3D 0x4777f0
    found = strstr(found, "=");
    if (value != NULL)
    {
        while (*found != ' ')
        {
            found++;
        }
        *value = found;
    }
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x42c5e0
void Script_ReadString(char *pos, char **next, char *out)
{
    while ((*pos == ' ') || (*pos == '\r') || (*pos == '\n'))
    {
        pos++;
    }
    int len = 0;
    while ((pos[len] != ' ') && (pos[len] != '\r') && (pos[len] != '\n'))
    {
        out[len] = pos[len];
        len++;
    }
    out[len] = '\0';
    if (next != NULL)
    {
        *next = pos + len + 1;
    }
}

// FUNCTION: STUNTGP_D3D 0x42c650
void FUN_42c650(char *text, char **end, float *value)
{
    while (*text == ' ' || *text == '\r' || *text == '\n')
    {
        text++;
    }
    *value = atof(text);
    if (end)
    {
        int i = 0;
        while (text[i] != ' ')
        {
            i++;
        }
        *end = &text[i + 1];
    }
}

// FUNCTION: STUNTGP_D3D 0x42c6a0
void Script_ReadInt(char *pos, char **next, int *out)
{
    while ((*pos == ' ') || (*pos == '\r') || (*pos == '\n'))
    {
        pos++;
    }
    *out = atol(pos);
    if (next != NULL)
    {
        int len = 0;
        while (pos[len] != ' ')
        {
            len++;
        }
        *next = pos + len + 1;
    }
}

// FUNCTION: STUNTGP_D3D 0x42c6f0
void FUN_42c6f0(char *text, char **end, char *value)
{
    while (*text == ' ' || *text == '\r' || *text == '\n')
    {
        text++;
    }
    *value = atol(text);
    if (end)
    {
        int i = 0;
        while (text[i] != ' ')
        {
            i++;
        }
        *end = &text[i + 1];
    }
}

extern int g_577660[10];
extern int g_624460;
void FUN_425880();

// Queues the sky and track scenes; the animated sky gets its scroll speeds.
// FUNCTION: STUNTGP_D3D 0x42c740
void FUN_42c740(char *script)
{
    // STRING: STUNTGP_D3D 0x4777f4
    if (Script_FindKey(script, &script, "L_SKY") == 1)
    {
        Script_ReadString(script, &script, (char *)g_58c234);
        g_58c540[g_58c808].id = g_58c234;
        g_58c234 += strlen((char *)g_58c234) + 1;
        g_58c540[g_58c808].slot = 2;
        g_58c808++;
        g_58c540[g_58c808].id = 0;
        FUN_425880();
        // STRING: STUNTGP_D3D 0x4777fc
        if (strstr((char *)g_58c540[g_58c808 - 1].id, "AnimSkyGround"))
        {
            ((float *)g_577660)[3] = 0.0f;
            ((float *)g_577660)[4] = 0.0f;
            ((float *)g_577660)[8] = 0.0007f;
            ((float *)g_577660)[9] = 0.0007f;
        }
    }
    // STRING: STUNTGP_D3D 0x47780c
    if (Script_FindKey(script, &script, "L_TRACK") == 1)
    {
        Script_ReadString(script, &script, (char *)g_58c234);
        g_624460 = g_58c234;
        g_58c540[g_58c808].id = g_58c234;
        g_58c234 += strlen((char *)g_58c234) + 1;
        g_58c540[g_58c808].slot = 3;
        g_58c808++;
        g_58c540[g_58c808].id = 0;
    }
}

// Queues each car's model and shadow scene from the L_CARn keys.
// FUNCTION: STUNTGP_D3D 0x42c880
void FUN_42c880(char *script)
{
    char shadowKey[16];
    char key[16];
    int slot = 4;
    for (DWORD car = 1; car <= 6; car++)
    {
        // STRING: STUNTGP_D3D 0x477814
        sprintf(key, "L_CAR%d", car);
        // STRING: STUNTGP_D3D 0x47781c
        sprintf(shadowKey, "L_CAR%dSHADOW", car);
        if (Script_FindKey(script, &script, key) != 1)
        {
            return;
        }
        Script_ReadString(script, &script, (char *)g_58c234);
        g_58c540[g_58c808].id = g_58c234;
        g_58c234 += strlen((char *)g_58c234) + 1;
        g_58c540[g_58c808].slot = slot;
        g_58c808++;
        g_58c540[g_58c808].id = 0;
        Script_FindKey(script, &script, shadowKey);
        Script_ReadString(script, &script, (char *)g_58c234);
        g_58c540[g_58c808].id = g_58c234;
        g_58c540[g_58c808].slot = slot + 1;
        g_58c234 += strlen((char *)g_58c234) + 1;
        g_58c808++;
        g_58c540[g_58c808].id = 0;
        slot += 2;
    }
}

// FUNCTION: STUNTGP_D3D 0x42c9b0
void FUN_42c9b0(char *script)
{
    char key[64];
    char *value;
    int i;
    for (i = 0; i < 6; i++)
    {
        g_60f02c[i].unk0c = 1;
    }
    for (i = 0; i < 6; i++)
    {
        // STRING: STUNTGP_D3D 0x47782c
        sprintf(key, "L_CAR%d_CONFIG", i + 1);
        if (Script_FindKey(script, &value, key) == 1)
        {
            Script_ReadInt(value, NULL, &g_60f02c[i].unk0c);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x42ca20
void FUN_42ca20(char *script)
{
    char key[64];
    char *value;
    int i;
    for (i = 0; i < 6; i++)
    {
        g_60f02c[i].unk10 = 0;
    }
    for (i = 0; i < 6; i++)
    {
        // STRING: STUNTGP_D3D 0x47783c
        sprintf(key, "L_CAR%d_TYRE", i + 1);
        if (Script_FindKey(script, &value, key) == 1)
        {
            Script_ReadInt(value, NULL, &g_60f02c[i].unk10);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x42ca90
void FUN_42ca90(char *script)
{
    char key[64];
    char *value;
    int i;
    for (i = 0; i < 6; i++)
    {
        g_60f02c[i].unk14 = 0;
    }
    for (i = 0; i < 6; i++)
    {
        // STRING: STUNTGP_D3D 0x47784c
        sprintf(key, "L_CAR%d_LIVERY", i + 1);
        if (Script_FindKey(script, &value, key) == 1)
        {
            Script_ReadInt(value, NULL, &g_60f02c[i].unk14);
        }
    }
}

extern char g_60dfac[0x40];
extern int g_60dfec;
extern float g_60dfa8;
extern int g_60df98;
extern DWORD g_60eff4;
extern DWORD g_60eff8;
extern DWORD g_60f014;
extern int g_60f01c;

// GLOBAL: STUNTGP_D3D 0x60dfa4
int g_60dfa4;

// GLOBAL: STUNTGP_D3D 0x60f024
int g_60f024;

// GLOBAL: STUNTGP_D3D 0x60f028
int g_60f028;

// Reads the level's race settings from its LvScript.cfg entry.
// FUNCTION: STUNTGP_D3D 0x42cc20
void FUN_42cc20(char *script)
{
    char text[128];
    int ground;
    DWORD n;
    char *value;
    // STRING: STUNTGP_D3D 0x47788c
    if (Script_FindKey(script, &value, "TRACKTEXSET") == 1)
    {
        Script_ReadString(value, NULL, text);
        sprintf(g_60dfac, text);
        n = strlen(text);
        if (n > 2)
        {
            g_60dfec = atol(text + n - 2);
        }
    }
    else
    {
        g_60dfac[0] = 0;
    }
    // STRING: STUNTGP_D3D 0x477898
    if (Script_FindKey(script, &value, "MUS_TRACK") == 1)
    {
        Script_ReadInt(value, NULL, (int *)&n);
        g_60dfa4 = n;
    }
    // STRING: STUNTGP_D3D 0x4778a4
    if (Script_FindKey(script, &value, "GROUNDLEVEL") == 1)
    {
        Script_ReadInt(value, NULL, &ground);
        g_60dfa8 = ground * 100.0f;
    }
    else
    {
        g_60dfa8 = -2000.0f;
    }
    // STRING: STUNTGP_D3D 0x4778b0
    if (Script_FindKey(script, &value, "GAMETYPE") == 1)
    {
        Script_ReadString(value, NULL, text);
        g_60df98 = 2;
        // STRING: STUNTGP_D3D 0x4778bc
        if (_stricmp(text, "RACE_TYPE_1") == 0)
        {
            g_60df98 = 2;
        }
        // STRING: STUNTGP_D3D 0x4778c8
        else if (_stricmp(text, "CHALLENGE_TYPE_1") == 0)
        {
            g_60df98 = 3;
        }
        // STRING: STUNTGP_D3D 0x4778dc
        else if (_stricmp(text, "TIMETRIAL_TYPE_1") == 0)
        {
            g_60df98 = 4;
        }
    }
    g_60eff4 = 0;
    // STRING: STUNTGP_D3D 0x4778f0
    if (Script_FindKey(script, &value, "TIME") == 1)
    {
        Script_ReadInt(value, NULL, (int *)&n);
        g_60eff4 = n * 60;
    }
    // STRING: STUNTGP_D3D 0x4778f8
    if (Script_FindKey(script, &value, "LAPCOUNT") == 1)
    {
        Script_ReadInt(value, NULL, (int *)&n);
        if (n > 24)
        {
            n = 24;
        }
        g_60eff8 = n;
    }
    // STRING: STUNTGP_D3D 0x477904
    if (Script_FindKey(script, &value, "LAPRECORD") == 1)
    {
        Script_ReadInt(value, &value, (int *)&n);
        DWORD record = n * 3600;
        Script_ReadInt(value, &value, (int *)&n);
        record += n % 100 * 60;
        Script_ReadInt(value, &value, (int *)&n);
        g_60f000[0] = n % 100 * 60 / 100 + record;
    }
    g_60f014 = 60000;
    // STRING: STUNTGP_D3D 0x477910
    if (Script_FindKey(script, &value, "ROLSTARTOFFSET") == 1)
    {
        Script_ReadInt(value, NULL, (int *)&n);
        n = (DWORD)(n * 100.0f);
        g_60f014 = n;
    }
    g_60f024 = 0;
    // STRING: STUNTGP_D3D 0x477920
    if (Script_FindKey(script, &value, "OVERLAYDEMO") == 1)
    {
        Script_ReadInt(value, NULL, (int *)&n);
        g_60f024 = n;
    }
    g_60f01c = 1;
    // STRING: STUNTGP_D3D 0x47792c
    if (Script_FindKey(script, &value, "CAMERAMODE") == 1)
    {
        Script_ReadInt(value, NULL, (int *)&n);
        g_60f01c = n;
    }
    g_60f028 = 3600;
    // STRING: STUNTGP_D3D 0x477938
    if (Script_FindKey(script, &value, "R_DEMOLOOP") == 1)
    {
        Script_ReadInt(value, NULL, (int *)&n);
        if (!n)
        {
            n = -1;
        }
        else
        {
            n *= 60;
        }
        g_60f028 = n;
    }
}

// FUNCTION: STUNTGP_D3D 0x42cb00
void FUN_42cb00(char *script)
{
    char key[64];
    char *value;
    int i;
    for (i = 0; i < 6; i++)
    {
        g_60f02c[i].unk18 = 0;
    }
    for (i = 0; i < 6; i++)
    {
        // STRING: STUNTGP_D3D 0x47785c
        sprintf(key, "L_CAR%d_REPLAY", i + 1);
        if (Script_FindKey(script, &value, key) == 1)
        {
            Script_ReadInt(value, NULL, &g_60f02c[i].unk18);
        }
    }
}

// FUNCTION: STUNTGP_D3D 0x42cb70
void FUN_42cb70(char *script)
{
    char key[64];
    char *value;
    for (int i = 0; i < 6; i++)
    {
        g_60f02c[i].unk1c = 100;
        g_60f02c[i].unk20 = 100;
    }
    for (DWORD car = 0; car < 6; car++)
    {
        // STRING: STUNTGP_D3D 0x47786c
        sprintf(key, "L_CAR%d_AISKILL", car + 1);
        if (Script_FindKey(script, &value, key) == 1)
        {
            Script_ReadInt(value, NULL, &g_60f02c[car].unk1c);
        }
        // STRING: STUNTGP_D3D 0x47787c
        sprintf(key, "L_CAR%d_AIMODE", car + 1);
        if (Script_FindKey(script, &value, key) == 1)
        {
            Script_ReadInt(value, NULL, &g_60f02c[car].unk20);
        }
    }
}

// Reads the rolling demo script names from the -ROLLINGDEMOLIST section.
// FUNCTION: STUNTGP_D3D 0x42cfa0
void FUN_42cfa0(char *script)
{
    char name[64];
    char *value;
    char *dest = g_612948.demoNames;
    // STRING: STUNTGP_D3D 0x477944
    Script_FindKey(script, &value, "-ROLLINGDEMOLIST");
    // STRING: STUNTGP_D3D 0x477958
    g_ScriptSectionEnd = strstr(value, "-END");
    memset(g_612948.demoScripts, 0, sizeof(g_612948.demoScripts));
    DWORD count = 0;
    int n = 0;
    for (char *pos = value; pos < g_ScriptSectionEnd; pos = value + 8)
    {
        if (count >= 16)
        {
            return;
        }
        // STRING: STUNTGP_D3D 0x477960
        if (Script_FindKey(pos, &value, "DEMOSCRIPT") == 1)
        {
            Script_ReadString(value, NULL, name);
            sprintf(dest, name);
            g_612948.demoScripts[n++] = dest;
            dest += strlen(name) + 1;
        }
        count++;
    }
}

// FUNCTION: STUNTGP_D3D 0x42d060
void FUN_42d060(char *script, char *key)
{
}

// Writes the best lap time (frames at 60 per second) over the LAPRECORD value in place.
// FUNCTION: STUNTGP_D3D 0x42d170
void FUN_42d170(char *script)
{
    DWORD time = g_60f000[0];
    if (time != g_60effc)
    {
        // STRING: STUNTGP_D3D 0x477998
        Script_FindKey(script, &script, "LAPRECORD");
        script[1] = time / 3600 + '0';
        DWORD seconds = time / 60 % 60;
        script[3] = seconds / 10 + '0';
        script[4] = seconds % 10 + '0';
        DWORD hundredths = time * 100 / 60;
        script[6] = hundredths / 10 % 10 + '0';
        script[7] = hundredths % 10 + '0';
    }
}

int size_of_file(char *path);
int bload(char *path, char *buffer, int maxSize);
int FUN_44aff0(char *name, void *data, int size);

// Stores the lap record into this level's entry in LvScript.cfg.
// FUNCTION: STUNTGP_D3D 0x42d240
void FUN_42d240()
{
    char path[128];
    char *value;
    // STRING: STUNTGP_D3D 0x4779a4
    sprintf(path, "%s\\Config\\LvScript.cfg", g_GameDirectory);
    int size = size_of_file(path);
    char *buffer = (char *)Mem_Alloc(size + 0x20, 0);
    bload(path, buffer, size);
    // STRING: STUNTGP_D3D 0x4779bc
    FUN_42d060(buffer, "ClogMeister");
    g_ScriptSectionEnd = NULL;
    value = buffer;
    Script_FindKey(buffer, &value, g_LevelScript);
    FUN_42d170(value);
    FUN_44aff0(path, buffer, size);
    Mem_Free(buffer);
}

// FUNCTION: STUNTGP_D3D 0x42d2e0
void Script_ParseGameSettings(char *script)
{
    char *value;
    int width;
    int height;
    int depth;
    int soundQuality;
    int sfxVolume;
    int musicVolume;
    int masterVolume;
    char controlMethod[64];

    // STRING: STUNTGP_D3D 0x4779c8
    Script_FindKey(script, NULL, "-GAMESETTINGS");
    // STRING: STUNTGP_D3D 0x4779d8
    g_ScriptSectionEnd = strstr(script, "-END");

    // STRING: STUNTGP_D3D 0x4779e0
    if (Script_FindKey(script, &value, "GAMELOCATION") == 1)
    {
        Script_ReadString(value, NULL, g_GameLocation);
    }
    // STRING: STUNTGP_D3D 0x4779f0
    sprintf(g_GameDirectory, "%s\\", g_GameLocation);
    // STRING: STUNTGP_D3D 0x4779f4
    sprintf(g_GraphicsDirectory, "%s\\Graphics\\", g_GameLocation);
    // STRING: STUNTGP_D3D 0x477a04
    sprintf(g_SoundDirectory, "%s\\Sound", g_GameLocation);

    // STRING: STUNTGP_D3D 0x477a10
    if (Script_FindKey(script, &value, "CONTROLMETHOD") == 1)
    {
        Script_ReadString(value, NULL, controlMethod);
        g_ControlMethod = 2;
        // STRING: STUNTGP_D3D 0x477a20
        if (_stricmp(controlMethod, "Steering_Analog") == 0)
        {
            g_ControlMethod = 0;
        }
        // STRING: STUNTGP_D3D 0x477a30
        else if (_stricmp(controlMethod, "Joystick_Analog") == 0)
        {
            g_ControlMethod = 1;
        }
        // STRING: STUNTGP_D3D 0x477a40
        else if (_stricmp(controlMethod, "Keyboard") == 0)
        {
            g_ControlMethod = 2;
        }
        // STRING: STUNTGP_D3D 0x477a4c
        else if (_stricmp(controlMethod, "Pad_Digital") == 0)
        {
            g_ControlMethod = 4;
        }
        // STRING: STUNTGP_D3D 0x477a58
        else if (_stricmp(controlMethod, "Pad_Analog") == 0)
        {
            g_ControlMethod = 3;
        }
    }

    // STRING: STUNTGP_D3D 0x477a64
    if (Script_FindKey(script, &value, "DISPLAYRESWIDTH") == 1)
    {
        Script_ReadInt(value, NULL, &width);
    }
    // STRING: STUNTGP_D3D 0x477a74
    if (Script_FindKey(script, &value, "DISPLAYRESHEIGHT") == 1)
    {
        Script_ReadInt(value, NULL, &height);
    }
    // STRING: STUNTGP_D3D 0x477a88
    if (Script_FindKey(script, &value, "DISPLAYRESDEPTH") == 1)
    {
        Script_ReadInt(value, NULL, &depth);
    }
    if ((width >= 320) && (width <= 2048) && (height >= 200) && (height <= 2048))
    {
        g_DISPLAYRESWIDTH = width;
        g_DISPLAYRESHEIGHT = height;
        g_DISPLAYRESDEPTH = depth;
    }

    // STRING: STUNTGP_D3D 0x477a98
    Script_FindKey(script, &value, "SOUNDQUALITY");
    Script_ReadInt(value, NULL, &soundQuality);
    // STRING: STUNTGP_D3D 0x477aa8
    Script_FindKey(script, &value, "MASTERVOLUME");
    Script_ReadInt(value, NULL, &masterVolume);
    // STRING: STUNTGP_D3D 0x477ab8
    Script_FindKey(script, &value, "SFXVOLUME");
    Script_ReadInt(value, NULL, &sfxVolume);
    // STRING: STUNTGP_D3D 0x477ac4
    Script_FindKey(script, &value, "MUSVOLUME");
    Script_ReadInt(value, NULL, &musicVolume);
    Sound_SetVolumes(masterVolume, sfxVolume, musicVolume, soundQuality);

    // STRING: STUNTGP_D3D 0x477ad0
    Script_FindKey(script, &value, "LEVELSCRIPT");
    Script_ReadString(value, NULL, g_LevelScript);

    g_D3DDeviceIndex = 0;
    g_D3DDriverIndex = 1;
    g_D3DUVFix = 0;
    // STRING: STUNTGP_D3D 0x477adc
    if (Script_FindKey(script, &value, "D3D_DEVICEINDEX") == 1)
    {
        Script_ReadInt(value, NULL, &g_D3DDeviceIndex);
    }
    // STRING: STUNTGP_D3D 0x477aec
    if (Script_FindKey(script, &value, "D3D_DRIVERINDEX") == 1)
    {
        Script_ReadInt(value, NULL, &g_D3DDriverIndex);
    }
    // STRING: STUNTGP_D3D 0x477afc
    if (Script_FindKey(script, &value, "D3D_UVFIX") == 1)
    {
        Script_ReadInt(value, NULL, &g_D3DUVFix);
    }

    g_DisableFramerateCorrection = 0;
    // STRING: STUNTGP_D3D 0x477b08
    if (Script_FindKey(script, &value, "DISABLE_FRAMERATE_CORRECTION") == 1)
    {
        Script_ReadInt(value, NULL, &g_DisableFramerateCorrection);
    }

    g_DisplayBootGfx = 0;
    // STRING: STUNTGP_D3D 0x477b28
    if (Script_FindKey(script, &value, "DISPLAY_BOOT_GFX") == 1)
    {
        Script_ReadInt(value, NULL, &g_DisplayBootGfx);
    }
}

// FUNCTION: STUNTGP_D3D 0x42d660
void Script_ParseGameConfig()
{
    char path[128];

    // STRING: STUNTGP_D3D 0x477b3c
    sprintf(path, "Game.cfg");
    if (size_of_file(path) == 0)
    {
        // STRING: STUNTGP_D3D 0x477b48
        sprintf(path, "D:\\Game\\Game.cfg");
        if (size_of_file(path) == 0)
        {
            // STRING: STUNTGP_D3D 0x477b5c
            sprintf(path, "C:\\Game\\Game.cfg");
            size_of_file(path);
        }
    }

    int size = size_of_file(path);
    char *script = (char *)Mem_Alloc(size + 32, 0);
    bload(path, script, size);
    // STRING: STUNTGP_D3D 0x477b70
    FUN_42d060(script, "ClogMeister");
    Script_ParseGameSettings(script);
    Mem_Free(script);
}

// GLOBAL: STUNTGP_D3D 0x624504
Ambience g_624504;

// GLOBAL: STUNTGP_D3D 0x5da264
char g_5da264[0x80];

// FUNCTION: STUNTGP_D3D 0x42d7e0
void FUN_42d7e0()
{
    float r = g_624504.red * g_624504.intensity;
    float g = g_624504.green * g_624504.intensity;
    float b = g_624504.blue * g_624504.intensity;
    g_624504.r = r;
    g_624504.g = g;
    g_624504.b = b;
    int ir = (int)r;
    int ig = (int)g;
    int ib = (int)b;
    g_624504.ir = ir << 8;
    g_624504.ig = ig << 8;
    g_624504.ib = ib << 8;
}

// GLOBAL: STUNTGP_D3D 0x477b80
float g_477b80 = 1.0f;

// GLOBAL: STUNTGP_D3D 0x477b84
float g_477b84 = 1.0f;

// GLOBAL: STUNTGP_D3D 0x589e00
float g_589e00;

extern int g_576be0;
void FUN_4320c0(float gamma);

// Eases the gamma towards its target, adding a slow flash while it is above 3.
// FUNCTION: STUNTGP_D3D 0x42d870
void FUN_42d870()
{
    if (g_4722d0->fadeActive == 1 || g_576be0)
    {
        g_477b84 = 1.0f;
        g_477b80 = 1.0f;
        FUN_4320c0(1.0f);
        return;
    }
    float diff = g_477b80 - g_477b84;
    if ((float)fabs(diff) > 0.2f)
    {
        float step;
        if (diff > 0.0f)
        {
            step = 0.5f;
        }
        else
        {
            step = -0.05f;
        }
        g_477b84 += step;
    }
    if (g_477b84 > 3.0f)
    {
        g_589e00 += 0.0075f;
        if (g_589e00 > 1.0f)
        {
            g_589e00 = 1.0f;
        }
    }
    else
    {
        g_589e00 -= 0.05f;
        if (g_589e00 < 0.0f)
        {
            g_589e00 = 0.0f;
        }
    }
    FUN_4320c0(g_477b84 - g_589e00);
}

// FUNCTION: STUNTGP_D3D 0x434980
void Script_GetFloat(char *section, char *key, float *out)
{
    char *p = strstr(section, key);
    // STRING: STUNTGP_D3D 0x478b5c
    p = strstr(p, "=");
    *out = atof(p + 1);
}

// FUNCTION: STUNTGP_D3D 0x4349b0
void Script_GetVector3(char *section, char *key, float *out)
{
    char *p = strstr(section, key);
    // STRING: STUNTGP_D3D 0x478b60
    p = strstr(p, "=") + 1;
    out[0] = atof(p);
    char *q = p;
    while (*q == ' ')
    {
        q++;
    }
    while (*q != ' ')
    {
        q++;
    }
    p = q + 1;
    out[1] = atof(p);
    q = p;
    while (*q == ' ')
    {
        q++;
    }
    while (*q != ' ')
    {
        q++;
    }
    out[2] = atof(q + 1);
}

// FUNCTION: STUNTGP_D3D 0x434a40
void Script_GetInt(char *section, char *key, int *out)
{
    char *p = strstr(section, key);
    // STRING: STUNTGP_D3D 0x478b64
    p = strstr(p, "=");
    *out = atol(p + 1);
}

// FUNCTION: STUNTGP_D3D 0x434a70
void Script_GetFloatArray(char *section, char *key, float *out, DWORD count)
{
    char *p = strstr(section, key);
    // STRING: STUNTGP_D3D 0x478b68
    p = strstr(p, "=");
    while (*p != ' ')
    {
        p++;
    }
    while (*p == ' ' || *p == '\r' || *p == '\n')
    {
        p++;
    }
    for (DWORD i = 0; i < count; i++)
    {
        *out = atof(p);
        while (*p != ' ')
        {
            p++;
        }
        while (*p == ' ' || *p == '\r' || *p == '\n')
        {
            p++;
        }
        out++;
    }
}

// FUNCTION: STUNTGP_D3D 0x434af0
char *Script_GetWord(char *section, char *key)
{
    char *p = strstr(section, key);
    // STRING: STUNTGP_D3D 0x478b6c
    p = strstr(p, "=") + 2;
    int i = 0;
    while (*p != '\n' && *p != '\r' && *p != ' ')
    {
        g_5da264[i] = *p;
        i++;
        p++;
    }
    g_5da264[i] = 0;
    return g_5da264;
}
