#include "Engine_LevelScript.h"

#include "../../sound.h"
#include "GameUpdate.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GLOBAL: STUNTGP_D3D 0x48491c
char g_GraphicsDirectory[128] = "D:\\Game\\Graphics24\\";

// GLOBAL: STUNTGP_D3D 0x484a1c
char g_SoundDirectory[128] = "D:\\Game\\Sound";

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

// FUNCTION: STUNTGP_D3D 0x42d060
void FUN_42d060(char *script, char *key)
{
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
