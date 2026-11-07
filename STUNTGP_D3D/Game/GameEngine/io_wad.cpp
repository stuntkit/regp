#include "io_wad.h"
#include "../../mem.h"
#include "MenuUpdate.h"

struct WadEntry
{
    char *dir;
    char *wad;
};

// GLOBAL: STUNTGP_D3D 0x4858b8
WadEntry g_WadTable[] = {
    {"sound\\sfx", "sfx.wad"},
    {"graphics24\\overlays", "overlay.wad"},
    {"graphics24\\misc", "misc.wad"},
    {"graphics24\\trackset00", "tset00.wad"},
    {"graphics24\\trackset01", "tset01.wad"},
    {"graphics24\\trackset02", "tset02.wad"},
    {"graphics24\\trackset03", "tset03.wad"},
    {"graphics24\\trackset04", "tset04.wad"},
    {"graphics24\\trackset05", "tset05.wad"},
    {"graphics24\\trackset06", "tset06.wad"},
    {"graphics24\\cars\\misc", "carmisc.wad"},
    {"graphics24\\cars\\car1", "car01.wad"},
    {"graphics24\\cars\\car2", "car02.wad"},
    {"graphics24\\cars\\car3", "car03.wad"},
    {"graphics24\\cars\\car4", "car04.wad"},
    {"graphics24\\cars\\car5", "car05.wad"},
    {"graphics24\\cars\\car6", "car06.wad"},
    {"graphics24\\cars\\car7", "car07.wad"},
    {"graphics24\\cars\\car8", "car08.wad"},
    {"graphics24\\cars\\car9", "car09.wad"},
    {"graphics24\\cars\\car10", "car10.wad"},
    {"graphics24\\cars\\car11", "car11.wad"},
    {"graphics24\\cars\\car12", "car12.wad"},
    {"graphics24\\cars\\car13", "car13.wad"},
    {"graphics24\\cars\\car14", "car14.wad"},
    {"graphics24\\cars\\car15", "car15.wad"},
    {"graphics24\\cars\\car16", "car16.wad"},
    {"graphics24\\cars\\car17", "car17.wad"},
    {"graphics24\\cars\\car18", "car18.wad"},
    {"graphics24\\cars\\car19", "car19.wad"},
    {"graphics24\\cars\\car20", "car20.wad"},
    {"graphics24\\level1", "level1.wad"},
    {"graphics24\\level2", "level2.wad"},
    {"graphics24\\level3", "level3.wad"},
    {"graphics24\\level4", "level4.wad"},
    {"graphics24\\level5", "level5.wad"},
    {"graphics24\\level6", "level6.wad"},
    {"graphics24\\level7", "level7.wad"},
    {"graphics24\\level8", "level8.wad"},
    {"graphics24\\challenge3", "chall3.wad"},
    {"graphics24\\frontend\\dialog", "dialog.wad"},
    {"graphics24\\frontend\\tiles", "tiles.wad"},
    {"graphics24\\frontend\\logos", "logos.wad"},
    {"graphics24\\frontend\\icons", "icons.wad"},
    {"graphics24\\frontend\\pads\\pc", "pads_pc.wad"},
    {"graphics24\\frontend\\pads\\dc", "pads_dc.wad"},
    {"graphics24\\frontend\\pads\\ps", "pads_ps.wad"},
    {"graphics24\\frontend\\pages\\cars\\a", "p_carsa.wad"},
    {"graphics24\\frontend\\pages\\cars\\b", "p_carsb.wad"},
    {"graphics24\\frontend\\pages\\catalog", "p_catal.wad"},
    {"graphics24\\frontend\\pages\\sponsor", "p_spons.wad"},
    {"graphics24\\frontend\\pages\\title", "p_title.wad"},
    {"graphics24\\frontend\\pages\\tracks\\a", "p_tracka.wad"},
    {"graphics24\\frontend\\pages\\tracks\\b", "p_trackb.wad"},
    {"graphics24\\frontend\\pages\\language", "p_lang.wad"},
    {"graphics24\\frontend\\pages\\single\\arcade", "p_single.wad"},
    {"graphics24\\fonts", "fonts.wad"},
    {"graphics24\\boot", "boot.wad"},
    {"graphics24\\loading", "loading.wad"},
    {"setup", "setup.wad"},
    {"replays", "replays.wad"},
    {"config", "config.wad"},
    {"config\\cams", "config.wad"},
    {"config\\levels", "config.wad"},
    {"config\\vehicles", "config.wad"},
    {NULL, NULL},
};

// GLOBAL: STUNTGP_D3D 0x61b758
char g_WadLookupName[256];

// GLOBAL: STUNTGP_D3D 0x61b858
char g_WadName[32];

// GLOBAL: STUNTGP_D3D 0x61b878
char *g_WadData;

// GLOBAL: STUNTGP_D3D 0x61b87c
int g_WadSize;

// FUNCTION: STUNTGP_D3D 0x44af60
int disk_size_of_file(char *path)
{
    // STRING: STUNTGP_D3D 0x485890
    FILE *file = fopen(path, "rb");
    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fclose(file);
        return size;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x44afa0
int disk_bload(char *path, char *buffer, int size)
{
    // STRING: STUNTGP_D3D 0x485894
    FILE *file = fopen(path, "rb");
    if (file != NULL)
    {
        if (size <= 0)
        {
            size = 0x200000;
        }
        int read = fread(buffer, 1, size, file);
        fclose(file);
        return read;
    }
    return 0;
}

// TODO: should it be here?
// FUNCTION: STUNTGP_D3D 0x44b170
int FUN_44b170(char *in)
{
    // start in from the end of GameDirectory and return position of first non '\\' char
    int len = strlen(g_GameDirectory);
    char tmp = in[len];
    int a = len;
    while (tmp == '\\')
    {
        a = len + 1;
        tmp = in[a];
        len++;
    }
    return len;
}

// TODO: should it be here?
// FUNCTION: STUNTGP_D3D 0x44b140
void FUN_44b140(char *out, char *in)
{
    // get buffer and return filename without doubled '\\\\'
    char tmp = *in;
    while (tmp != '\0')
    {
        if ((tmp == '\\') && (in[1] == '\\'))
        {
            in++;
        }
        tmp = *in;
        in++;
        *out = tmp;
        out++;
        tmp = *in;
    }
    *out = '\0';
    return;
}

// FUNCTION: STUNTGP_D3D 0x44aff0
int FUN_44aff0(char *name, void *data, int size)
{
    // STRING: STUNTGP_D3D 0x4858b4
    FILE *file = fopen(name, "wb");
    if (file && size > 0 && size < 0xa00000)
    {
        int written = fwrite(data, 1, size, file);
        fclose(file);
        return written;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x44b050
void WAD_SplitFileName(char *path, char *dir, char *filename)
{
    char buffer[128];
    strcpy(buffer, path);

    char last = strlen(buffer) - 1;
    while ((buffer[last] != '\\') && (last > 0))
    {
        last--;
    }

    char i = last;
    while (buffer[i] == '\\')
    {
        i++;
    }

    i = FUN_44b170(buffer);
    FUN_44b140(filename, buffer + i);

    if (last < 0)
    {
        *dir = '\0';
    }
    else
    {
        buffer[last] = '\0';
        FUN_44b140(dir, buffer + i);
    }

    tolower(filename, filename);
    tolower(dir, dir);
}

// FUNCTION: STUNTGP_D3D 0x44b1a0
void WAD_FlushWadCache()
{
    if (g_WadData != NULL)
    {
        free(g_WadData);
        g_WadData = NULL;
        g_WadName[0] = '\0';
        g_WadSize = 0;
    }
}

// FUNCTION: STUNTGP_D3D 0x44b1d0
BOOL WAD_CacheNewWadFile(char *wad)
{
    char path[64];
    WAD_FlushWadCache();
    // STRING: STUNTGP_D3D 0x4863e8
    sprintf(path, "%s\\wads\\%s", g_GameDirectory, wad);
    int size = disk_size_of_file(path);
    if (size == 0)
    {
        return FALSE;
    }
    strcpy(g_WadName, wad);
    g_WadData = (char *)malloc(size);
    g_WadSize = size;
    disk_bload(path, g_WadData, size);
    return TRUE;
}

// FUNCTION: STUNTGP_D3D 0x44b260
int bload(char *path, char *buffer, int maxSize)
{
    unsigned int size;
    char dir[64];
    char filename[64];

    WAD_SplitFileName(path, dir, filename);
    unsigned int dirLen = strlen(dir);
    WadEntry *best = NULL;
    for (WadEntry *entry = g_WadTable; entry->dir != NULL; entry++)
    {
        if (WAD_DirDiffers(dir, entry->dir) == 0)
        {
            if (strlen(entry->dir) == dirLen)
            {
                best = entry;
                break;
            }
            if ((best == NULL) || (strlen(entry->dir) > strlen(best->dir)))
            {
                best = entry;
            }
        }
    }

    if (best != NULL)
    {
        if (_stricmp(g_WadName, best->wad) != 0)
        {
            WAD_CacheNewWadFile(best->wad);
        }
        if (g_WadData != NULL)
        {
            int offset = WAD_FindFile(g_WadData, filename, &size);
            if (offset != 0)
            {
                memcpy(buffer, g_WadData + offset, (size < (unsigned int)maxSize) ? size : maxSize);
                return size;
            }
        }
    }

    return disk_bload(path, buffer, maxSize);
}

// FUNCTION: STUNTGP_D3D 0x44b380
int WAD_DirDiffers(char *a, char *b)
{
    while ((*a != '\0') && (*b != '\0'))
    {
        if (*a != *b)
        {
            return 1;
        }
        a++;
        b++;
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x44b3b0
int size_of_file(char *path)
{
    unsigned int size;
    char dir[64];
    char filename[64];
    char buffer[128];

    WAD_SplitFileName(path, dir, filename);
    for (WadEntry *entry = g_WadTable; entry->dir != NULL; entry++)
    {
        if (_stricmp(dir, entry->dir) == 0)
        {
            if (_stricmp(g_WadName, entry->wad) != 0)
            {
                WAD_CacheNewWadFile(entry->wad);
            }
            if (g_WadData != NULL)
            {
                WAD_FindFile(g_WadData, filename, &size);
                return size;
            }
            break;
        }
    }

    strcpy(buffer, path);
    return disk_size_of_file(buffer);
}

extern int g_489714;
extern int g_489718;

// GLOBAL: STUNTGP_D3D 0x62f5c8
int g_62f5c8;

// GLOBAL: STUNTGP_D3D 0x62f5cc
BYTE *g_62f5cc;

// GLOBAL: STUNTGP_D3D 0x62f5d0
BYTE *g_62f5d0;

// GLOBAL: STUNTGP_D3D 0x48971c
int g_48971c = 0;

// GLOBAL: STUNTGP_D3D 0x489720
int g_489720 = 0;

void FUN_442180();

// Fatal error: shuts the game down and exits; the message is not shown.
// FUNCTION: STUNTGP_D3D 0x4234d0
void FUN_4234d0(char *msg)
{
    FUN_442180();
    exit(1);
}

// FUNCTION: STUNTGP_D3D 0x44cc90
int FUN_44cc90(int value)
{
    if (value > 1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (g_menuState.unk19ee0[i] == value)
            {
                return 1;
            }
        }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x44ccc0
void FUN_44ccc0()
{
    g_menuState.unk0f1c[g_menuState.unk19d78] = g_menuState.unk19d7c;
}

// FUNCTION: STUNTGP_D3D 0x44ccf0
int FUN_44ccf0()
{
    for (int i = 0; i < 6; i++)
    {
        if (g_menuState.unk1a544[i].unk00)
        {
            return i + 1;
        }
    }
    return 0;
}

// Decodes an uncompressed 24-bit TGA into top-down RGB.
// FUNCTION: STUNTGP_D3D 0x4622c0
void FUN_4622c0(BYTE *tga, BYTE *dst, void *palette, int size)
{
    int step;
    BYTE type = tga[2];
    if (type != 2 || tga[0x10] != 24)
    {
        // STRING: STUNTGP_D3D 0x48a588
        FUN_4234d0("Unsupported TGA format...\n");
    }
    g_62f5c8 = tga[0x10];
    g_489714 = g_48971c = *(WORD *)(tga + 0xc);
    g_489718 = g_489720 = *(WORD *)(tga + 0xe);
    g_62f5d0 = tga + tga[0] + 0x12;
    if (!(type & 0x20))
    {
        step = -1;
        dst += (g_489720 - 1) * g_48971c * 3;
    }
    else
    {
        step = 1;
    }
    for (int y = 0; y < g_489720; y++)
    {
        for (int i = 0; i < g_48971c * 3; i += 3)
        {
            dst[i] = g_62f5d0[i + 2];
            dst[i + 1] = g_62f5d0[i + 1];
            dst[i + 2] = g_62f5d0[i];
        }
        g_62f5d0 += g_48971c * 3;
        dst += g_48971c * step * 3;
    }
}

// FUNCTION: STUNTGP_D3D 0x4623c0
void FUN_4623c0(char *path, void *buffer, void *arg)
{
    int size = size_of_file(path);
    if (!size)
    {
        char msg[128];
        // STRING: STUNTGP_D3D 0x48a5a4
        sprintf(msg, "File: %s not found...", path);
        FUN_4234d0(msg);
    }
    g_62f5cc = (BYTE *)Mem_Alloc(size, 0);
    bload(path, (char *)g_62f5cc, size);
    FUN_4622c0(g_62f5cc, (BYTE *)buffer, arg, size);
    Mem_Free(g_62f5cc);
}

// FUNCTION: STUNTGP_D3D 0x44b470
void tolower(char *out, char *in)
{
    char tmp;

    tmp = *in;
    while (tmp != '\0')
    {
        in++;
        if ((tmp >= 'A') && (tmp <= 'Z'))
        {
            tmp += ' ';
        }
        *out = tmp;
        out++;
        tmp = *in;
    }
    *out = '\0';

    return;
}

// FUNCTION: STUNTGP_D3D 0x44b4e0
int WAD_FindFile(char *wad, char *name, unsigned int *size)
{
    *size = 0;
    if ((wad != NULL) && (wad[0] == 'D') && (wad[1] == 'I') && (wad[2] == 'R') && (wad[3] == 0x1a))
    {
        int dirOffset = *(int *)(wad + 8);
        tolower(g_WadLookupName, name);
        int entry = *(int *)(wad + dirOffset + WAD_HashName(g_WadLookupName) * 4 + 4);
        if (entry != 0)
        {
            char *dir = wad + dirOffset;
            while (entry != 0)
            {
                if (WAD_NameEquals(dir + entry + 12, g_WadLookupName))
                {
                    *size = *(unsigned int *)(dir + entry + 8);
                    return *(int *)(dir + entry + 4);
                }
                entry = *(int *)(dir + entry);
            }
        }
    }
    return 0;
}

// FUNCTION: STUNTGP_D3D 0x44b570
int WAD_NameEquals(char *a, char *b)
{
    while ((*a != '\0') && (*b != '\0') && (*a == *b))
    {
        a++;
        b++;
    }
    return *a == *b;
}

// TODO: 59%, MSVC folds the 0x1ff mask into the final 0x3ff; the original keeps both
// FUNCTION: STUNTGP_D3D 0x44b5a0
int WAD_HashName(char *name)
{
    unsigned int hash = 0;
    while (*name != '\0')
    {
        // rotate left within 10 bits, then add the character
        hash = ((((hash & 0x1ff) << 1) | ((hash >> 9) & 1)) + (unsigned char)*name) & 0x3ff;
        name++;
    }
    return hash;
}
