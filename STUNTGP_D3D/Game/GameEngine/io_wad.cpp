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

// Bubble sort, highest unk08 first, then unk04, then unk10.
// FUNCTION: STUNTGP_D3D 0x44be80
void FUN_44be80(MenuSlot20 *slots, int count)
{
    for (int i = count - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            int d = slots[j].unk08 - slots[j + 1].unk08;
            if (d == 0)
            {
                d = slots[j].unk04 - slots[j + 1].unk04;
                if (d == 0)
                {
                    d = slots[j].unk10 - slots[j + 1].unk10;
                }
            }
            if (d < 0)
            {
                MenuSlot20 t = slots[j];
                slots[j] = slots[j + 1];
                slots[j + 1] = t;
            }
        }
    }
}

extern char *g_4863f4[7];
void FUN_436490(int a, ShopEntry *out, ShopCar *car, ShopItem *item, int unused);
void FUN_43af20(RaceSetup5 *src, RaceResults *dst);

// GLOBAL: STUNTGP_D3D 0x61bbe0
RaceSetup5 g_61bbe0;

// GLOBAL: STUNTGP_D3D 0x61bed0
RaceResults g_61bed0;

// Starts the championship round of the current save: the player's car against the five rivals.
// FUNCTION: STUNTGP_D3D 0x44bf10
void FUN_44bf10()
{
    ShopEntry shop;
    memset(&g_61bbe0, 0, sizeof(g_61bbe0));
    memset(&g_61bed0, 0, sizeof(g_61bed0));
    FUN_436490(g_menuState.unk19d7c.sponsor, &shop, &g_menuState.unk19d7c.carSetup,
               &g_menuState.items[g_menuState.unk19d7c.car], 1);
    g_61bbe0.item = shop.item;
    *(Initials *)&g_61bbe0.cars[0].unk04 = g_menuState.unk19d7c.name;
    g_61bbe0.cars[0].unk08 = g_menuState.unk19d7c.car;
    g_61bbe0.cars[0].car = g_menuState.unk19d7c.unk10c;
    g_61bbe0.cars[0].unk10 = g_menuState.sponsors[g_menuState.unk19d7c.sponsor].id;
    g_61bbe0.cars[0].unk00 = 1;
    for (int i = 0; i < 5; i++)
    {
        *(Initials *)&g_61bbe0.cars[i + 1].unk04 = *(Initials *)g_4863f4[g_menuState.unk19d7c.unk110[i][2]];
        g_61bbe0.cars[i + 1].unk00 = 0;
        g_61bbe0.cars[i + 1].unk10 = g_menuState.sponsors[g_menuState.unk19d7c.unk110[i][2]].id;
        g_61bbe0.cars[i + 1].car = g_menuState.unk19d7c.unk110[i][3];
        g_61bbe0.cars[i + 1].unk08 = g_menuState.rounds[g_menuState.unk19d7c.unk008 - 1].cars[i].unk00;
        g_61bbe0.cars[i + 1].unk14 = g_menuState.rounds[g_menuState.unk19d7c.unk008 - 1].cars[i].unk04;
        g_61bbe0.cars[i + 1].unk18 = g_menuState.rounds[g_menuState.unk19d7c.unk008 - 1].cars[i].unk08;
    }
    g_61bbe0.track = g_menuState.rounds[g_menuState.unk19d7c.unk008 - 1].track;
    g_61bbe0.unk1d8 = g_menuState.rounds[g_menuState.unk19d7c.unk008 - 1].unk04;
    g_61bbe0.unk1dc = g_menuState.unk1a1c[g_61bbe0.track][0].time;
    g_61bbe0.unk1e0 = g_menuState.unk1a1c[g_61bbe0.track][1].time;
    g_61bbe0.unk1e4 = g_menuState.unk1a1c[g_61bbe0.track][2].time;
    g_61bbe0.unk1e8 = g_menuState.unk1a1c[g_61bbe0.track][3].time;
    FUN_43af20(&g_61bbe0, &g_61bed0);
}

int FUN_437230(int car, int mode);
int FUN_437790(ScoreEntry *table, int count, Initials *name, int score);
void FUN_437880(int index);
int FUN_437de0(int sponsor, int car, ShopCar *setup);
void FUN_437e20(int *settings);
void FUN_43ae00(RaceSetup4 *src, RaceResults4 *dst);
void FUN_43bf30();
void FUN_43d500(int a);
int FUN_43dc20(int first, int last);
char *FUN_441170(int id);
void FUN_44bd00();
int FUN_44cc90(int value);
void FUN_44ccc0();
int FUN_44ccf0();
void FUN_44cd10(int track, Initials *name, int time0, int time1, int score2, int score3);

// GLOBAL: STUNTGP_D3D 0x61b9c0
RaceResults4 g_61b9c0;

// GLOBAL: STUNTGP_D3D 0x61b9c8
char g_61b9c8[0x100];

// GLOBAL: STUNTGP_D3D 0x61bac8
RaceSetup4 g_61bac8;

// GLOBAL: STUNTGP_D3D 0x61bdcc
char g_61bdcc[0x100];

// Championship state machine: sponsor and car choice, the shop, the rounds with their bonus
// time trials, then the final tables.
// FUNCTION: STUNTGP_D3D 0x44c0a0
void FUN_44c0a0(PoolObject *object)
{
    int i;
    int pos;
    int team;
    switch (g_menuState.unk4234)
    {
    case 0:
        g_menuState.unk4238 = 0;
        g_menuState.unk423c = 1;
        g_menuState.unk424c = 0;
        g_menuState.unk4248 = 0;
        g_menuState.unk43f4[0] = 0;
        g_menuState.unk1a540 = 0;
        g_menuState.unk4234 = 1;
        return;
    case 1:
        FUN_43dfa0(0x11, 0x1c);
        g_menuState.unk4234 = 2;
        return;
    case 2:
        if (g_menuState.unk4380)
        {
            FUN_43eef0();
            return;
        }
        memset(&g_menuState.unk19d7c, 0, sizeof(g_menuState.unk19d7c));
        g_menuState.unk19d78 = g_menuState.unk4384;
        if (g_menuState.unk4388)
        {
            g_menuState.unk4234 = 3;
            g_menuState.unk19d78 = g_menuState.unk4384;
            return;
        }
        g_menuState.unk19d7c = g_menuState.unk0f1c[g_menuState.unk4384];
        g_menuState.unk1a53c = 1;
        g_menuState.unk4234 = 7;
        return;
    case 3:
        g_menuState.unk4390 = 0;
        g_menuState.unk4234 = 4;
        FUN_43dfa0(0x12, 9);
        return;
    case 4:
        if (!g_menuState.unk44d0)
        {
            FUN_43dfa0(0x13, 13);
            g_menuState.unk4234 = 5;
            return;
        }
        g_menuState.unk4234 = 1;
        return;
    case 5:
        if (g_menuState.unk438c)
        {
            g_menuState.unk4234 = 3;
            return;
        }
        team = 1;
        g_menuState.unk19d7c.car = 0;
        g_menuState.unk19d7c.unk000 = 1;
        g_menuState.unk19d7c.unk008 = 1;
        g_menuState.unk19d7c.money = g_menuState.sponsors[g_menuState.unk4390].unk00;
        g_menuState.unk19d7c.name = *(Initials *)g_menuState.unk44d4[g_menuState.unk4238];
        pos = 1;
        g_menuState.unk19d7c.unk10c = 6;
        g_menuState.unk19d7c.sponsor = g_menuState.unk4390;
        g_menuState.unk19d7c.unk104 = 0;
        g_menuState.unk19d7c.unk100 = 0;
        for (i = 0; i < 5; i++)
        {
            if (g_menuState.unk19d7c.unk10c == pos)
            {
                pos++;
            }
            if (g_menuState.unk19d7c.sponsor == team)
            {
                team++;
            }
            g_menuState.unk19d7c.unk110[i][0] = 0;
            g_menuState.unk19d7c.unk110[i][1] = 0;
            g_menuState.unk19d7c.unk110[i][2] = team;
            g_menuState.unk19d7c.unk110[i][3] = pos;
            pos++;
            team++;
            if (g_menuState.unk19d7c.unk10c == pos)
            {
                pos++;
            }
            if (g_menuState.unk19d7c.sponsor == team)
            {
                team++;
            }
        }
        g_menuState.unk4398 = 0;
        for (i = 1; i < 21; i++)
        {
            int cost = FUN_437de0(g_menuState.unk19d7c.sponsor, i, &g_menuState.cars[i]);
            if (FUN_437230(i, g_menuState.unk4230) && cost <= g_menuState.unk19d7c.money)
            {
                g_menuState.unk439c[g_menuState.unk4398] = i;
                g_menuState.unk4398++;
            }
        }
        g_menuState.unk4234 = 6;
        FUN_43dfa0(0x14, 10);
        return;
    case 6:
    {
        if (g_menuState.unk4394)
        {
            g_menuState.unk4234 = 4;
            return;
        }
        FUN_437e20((int *)&g_menuState.unk19d7c);
        int car = g_menuState.unk43f4[g_menuState.unk4238];
        g_menuState.unk19d7c.money -= FUN_437de0(g_menuState.unk19d7c.sponsor, car, &g_menuState.cars[car]);
        g_menuState.unk19d7c.car = g_menuState.unk43f4[g_menuState.unk4238];
        g_menuState.unk19d7c.carSetup = g_menuState.cars[car];
        FUN_437e20((int *)&g_menuState.unk19d7c);
        g_menuState.unk1a53c = 1;
        g_menuState.unk4234 = 7;
        return;
    }
    case 7:
        FUN_44bd00();
        switch (g_menuState.unk1a53c)
        {
        case 1:
            g_menuState.unk1a53c = 0;
            FUN_43dfa0(0x15, 14);
            return;
        case 2:
            g_menuState.unk1a53c = 0;
            g_menuState.unk4234 = 0x18;
            return;
        case 3:
            g_menuState.unk1a53c = 0;
            g_menuState.unk4234 = 5;
            return;
        case 4:
            g_menuState.unk1a53c = 0;
            g_menuState.unk4234 = 8;
            return;
        }
        return;
    case 8:
        g_menuState.unk4404 = 0;
        g_menuState.unk440c[0] = g_menuState.rounds[g_menuState.unk19d7c.unk008 - 1].track;
        g_menuState.unk4408 = 1;
        FUN_43dfa0(0x17, 11);
        g_menuState.unk4234 = 9;
        return;
    case 9:
        if (g_menuState.unk4404)
        {
            g_menuState.unk1a53c = 1;
            g_menuState.unk4234 = 7;
            return;
        }
        g_menuState.unk19d7c.carSetup.unk00 = 1;
        for (i = 0; i < 14; i++)
        {
            g_menuState.unk19d7c.carSetup.parts[i][0] = 1;
        }
        FUN_44bf10();
        FUN_43dfa0(0, 25);
        g_menuState.unk4234 = 10;
        return;
    case 10:
    {
        if (g_61bed0.won)
        {
            g_menuState.unk4234 = 0x18;
            return;
        }
        int scale = g_menuState.unk19d7c.unk008 > g_menuState.numberOfRounds ? 3 : 1;
        FUN_44cd10(g_61bbe0.track, &g_menuState.unk19d7c.name, g_61bed0.results[0].unk04,
                   g_61bed0.results[0].unk08, g_61bed0.results[0].unk0c, g_61bed0.results[0].unk10);
        int(*tally)[4] = (int(*)[4]) & g_menuState.unk19d7c.unk100;
        for (i = 0; i < 6; i++)
        {
            int position = g_61bed0.results[i].position;
            tally[i][3] = FUN_43dc20(position, 6);
            if (scale < 2 || i == 0)
            {
                tally[i][0] += position == 1;
                tally[i][1] += g_menuState.positions[position - 1][0] * scale;
            }
        }
        int bonus;
        pos = g_61bed0.results[0].position;
        if (g_menuState.unk19d7c.unk008 > g_menuState.numberOfRounds)
        {
            bonus = g_menuState.positions[g_61bed0.results[0].position - 1][3] + g_61bed0.results[0].unk10;
            if (g_61bed0.results[0].position == 1)
            {
                FUN_437880(0x12);
            }
            else
            {
                FUN_437880(0x11);
            }
        }
        else
        {
            bonus = g_menuState.positions[g_61bed0.results[0].position - 1][1] + g_61bed0.results[0].unk10;
        }
        g_menuState.unk19d7c.money += bonus;
        FUN_44bd00();
        g_menuState.unk1d9ac = 0x5f;
        g_menuState.unk1d9b0[0].color = 0xffffffff;
        g_menuState.unk1d9b0[0].text = FUN_441170(pos + 0x27c);
        sprintf(g_61b9c8, FUN_441170(0x283), g_menuState.positions[pos - 1][0] * scale);
        g_menuState.unk1d9b0[1].color = 0xffff8080;
        g_menuState.unk1d9b0[1].text = g_61b9c8;
        sprintf(g_61bdcc, FUN_441170(0x284), bonus);
        g_menuState.unk1d9b0[2].color = 0xffff8080;
        g_menuState.unk1d9b0[2].text = g_61bdcc;
        g_menuState.unk1d9b0[3].color = 0xffc8c8ff;
        g_menuState.unk1d9b0[3].text = FUN_441170(0x26c);
        g_menuState.unk1da58 = g_menuState.numberOfRounds;
        g_menuState.unk1d9a8 = 0;
        g_menuState.unk1da50 = 4;
        g_menuState.unk1da54 = g_menuState.unk19d7c.unk008;
        FUN_43dfa0(0x2c, 0x20);
        g_menuState.unk4234 = 11;
        return;
    }
    case 11:
        FUN_43dfa0(0x30, 0x28);
        g_menuState.unk4234 = 12;
        return;
    case 12:
        g_menuState.unk19d7c.unk008++;
        g_menuState.unk4234 = 13;
        return;
    case 13:
        if (g_menuState.unk19d7c.unk008 > g_menuState.numberOfRounds)
        {
            g_menuState.unk4234 = g_menuState.unk19d7c.unk008 > g_menuState.numberOfRounds + 1 ? 0x11 : 0x13;
            return;
        }
        if (!FUN_44cc90(g_menuState.unk19d7c.unk008))
        {
            g_menuState.unk1a53c = 1;
            g_menuState.unk4234 = 7;
            return;
        }
        g_menuState.unk4234 = 14;
        return;
    case 14:
    {
        int minutes = 0x5a;
        switch (FUN_44ccf0())
        {
        case 1:
            minutes = 0x1e;
            break;
        case 2:
            minutes = 0x28;
            break;
        case 3:
            minutes = 0x32;
            break;
        case 4:
            minutes = 0x3c;
            break;
        case 5:
            minutes = 0x46;
            break;
        case 6:
            minutes = 0x5a;
            break;
        }
        g_61bac8.name = g_menuState.unk19d7c.name;
        g_61bac8.car = 0x15;
        g_61bac8.track = 0x19;
        g_61bac8.unk0c = g_menuState.unk1dfc[0].time;
        g_menuState.unk4234 = 15;
        g_menuState.unk45ec = 0x5f;
        g_menuState.unk45f0[0].color = 0xffffffff;
        g_61bac8.minutes = minutes;
        g_menuState.unk45f0[0].text = FUN_441170(0x263);
        sprintf(g_61b9c8, FUN_441170(0x264), minutes);
        g_menuState.unk45f0[1].color = 0xffff8080;
        g_menuState.unk45f0[1].text = g_61b9c8;
        g_menuState.unk45f0[2].color = 0xffc8c8ff;
        g_menuState.unk45f0[2].text = FUN_441170(0x265);
        g_menuState.unk45f0[3].color = 0xffc8c8ff;
        g_menuState.unk45f0[3].text = FUN_441170(0x266);
        g_menuState.unk45e8 = 0;
        g_menuState.unk4690 = 4;
        FUN_43dfa0(0x2d, 0x26);
        return;
    }
    case 15:
        FUN_43ae00(&g_61bac8, &g_61b9c0);
        g_menuState.unk4234 = 16;
        FUN_43dfa0(0, 25);
        return;
    case 16:
        if (!g_61b9c0.won)
        {
            g_menuState.unk19d7c.money += g_61b9c0.unk04;
            g_menuState.unk45ec = 0x5f;
            sprintf(g_61b9c8, FUN_441170(0x268), g_61b9c0.unk04);
            g_menuState.unk45f0[0].color = 0xffff8080;
            g_menuState.unk45f0[0].text = g_61b9c8;
            g_menuState.unk45f0[1].color = 0xffc8c8ff;
            g_menuState.unk45f0[1].text = FUN_441170(0x267);
            g_menuState.unk45f0[2].color = 0xffc8c8ff;
            g_menuState.unk45f0[2].text = FUN_441170(0x269);
            g_menuState.unk45e8 = 0;
            g_menuState.unk4690 = 3;
            FUN_43dfa0(0x2e, 0x26);
        }
        g_menuState.unk1a53c = 1;
        g_menuState.unk4234 = 7;
        return;
    case 17:
        g_menuState.unk4234 = 0x15;
        return;
    case 18:
        g_menuState.unk4404 = 0;
        g_menuState.unk4234 = 9;
        g_menuState.unk45ec = 0x5f;
        g_menuState.unk45f0[0].color = 0xffffffff;
        g_menuState.unk45f0[0].text = FUN_441170(0x26a);
        g_menuState.unk45f0[1].color = 0xffc8c8ff;
        g_menuState.unk45f0[1].text = FUN_441170(0x26b);
        g_menuState.unk45f0[2].color = 0xffc8c8ff;
        g_menuState.unk45f0[2].text = FUN_441170(0x26c);
        g_menuState.unk45e8 = 0;
        g_menuState.unk4690 = 3;
        FUN_43dfa0(0x2f, 0x26);
        return;
    case 19:
    {
        int rank = FUN_44ccf0();
        if (rank < 4)
        {
            g_menuState.unk45d8 = rank + 0x17f;
            g_menuState.unk45d4 = 0x5f;
            g_menuState.unk45dc = 0;
            g_menuState.unk45e0 = 0.015f;
            g_menuState.unk45e4 = 80.0f;
            FUN_43dfa0(0x2c, 0x25);
        }
        g_menuState.unk4234 = 20;
        return;
    }
    case 20:
        g_menuState.unk4234 = FUN_44ccf0() != 1 ? 0x15 : 0x12;
        return;
    case 21:
        FUN_44bd00();
        FUN_437790(g_menuState.unk1d5c, 10, &g_menuState.unk19d7c.name,
                   g_menuState.unk1a648 + g_menuState.unk1a604);
        g_menuState.unk4694.unk00 = 0x28b;
        g_menuState.unk4694.unk04 = 0;
        g_menuState.unk4694.unk08 = 0;
        g_menuState.unk4694.count = 10;
        g_menuState.unk4694.entries = g_menuState.unk1d5c;
        FUN_43dfa0(0x31, 0x27);
        g_menuState.unk4234 = 22;
        return;
    case 22:
        FUN_437790(g_menuState.unk1dac, 10, &g_menuState.unk19d7c.name, g_menuState.unk19d7c.unk104);
        g_menuState.unk4694.unk00 = 0x28a;
        g_menuState.unk4694.unk04 = 0;
        g_menuState.unk4694.unk08 = 1;
        g_menuState.unk4694.count = 10;
        g_menuState.unk4694.entries = g_menuState.unk1dac;
        FUN_43dfa0(0x31, 0x27);
        g_menuState.unk4234 = 23;
        return;
    case 23:
        g_menuState.unk19d7c.unk000 = 0;
        FUN_43bf30();
        g_menuState.unk4234 = 24;
        return;
    case 24:
        FUN_44ccc0();
        g_menuState.unk4234 = 25;
        FUN_43d500(0);
        return;
    case 25:
        FUN_43eef0();
        return;
    }
}

// FUNCTION: STUNTGP_D3D 0x44cc90
int FUN_44cc90(int value)
{
    if (value > 1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (g_menuState.bonusRounds[i] == value)
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

int FUN_437d20(ScoreEntry *entry, Initials *name, int score);
int FUN_437d60(ScoreEntry *entry, Initials *name, int time);

// FUNCTION: STUNTGP_D3D 0x44cd10
void FUN_44cd10(int track, Initials *name, int time0, int time1, int score2, int score3)
{
    FUN_437d60(&g_menuState.unk1a1c[track][0], name, time0);
    FUN_437d60(&g_menuState.unk1a1c[track][1], name, time1);
    FUN_437d20(&g_menuState.unk1a1c[track][2], name, score2);
    FUN_437d20(&g_menuState.unk1a1c[track][3], name, score3);
}

int FUN_437230(int car, int mode);
int FUN_4371c0(int track, int mode);
int FUN_437cc0(int track);
void FUN_43d500(int a);
char *FUN_441170(int id);
void FUN_43a780(RaceSetup2 *src);

// GLOBAL: STUNTGP_D3D 0x61bf50
RaceSetup2 g_61bf50;

// Challenge mode state machine: pick a car, pick a track, then race unk447c AI cars.
// FUNCTION: STUNTGP_D3D 0x44cd70
void FUN_44cd70(PoolObject *object)
{
    char name[0x40];
    int i;
    switch (g_menuState.unk4234)
    {
    case 0:
        g_menuState.unk423c = 1;
        g_menuState.unk4234 = 1;
        g_menuState.unk4238 = 0;
        g_menuState.unk4474 = 0;
        g_menuState.unk447c = 3;
        g_menuState.unk4480 = 0;
        g_menuState.unk43f4[0] = 0;
        return;
    case 1:
        g_menuState.unk4398 = 0;
        for (i = 1; i < 21; i++)
        {
            if (FUN_437230(i, g_menuState.unk4230) || g_menuState.unk0074)
            {
                g_menuState.unk439c[g_menuState.unk4398] = i;
                g_menuState.unk4398++;
            }
        }
        g_menuState.unk4234 = 2;
        FUN_43dfa0(0x21, 10);
        return;
    case 2:
        if (g_menuState.unk4394)
        {
            FUN_43eef0();
            return;
        }
        g_menuState.unk4408 = 0;
        for (i = 1; i < 25; i++)
        {
            if (FUN_4371c0(i, g_menuState.unk4230) || g_menuState.unk0074)
            {
                g_menuState.unk440c[g_menuState.unk4408] = i;
                g_menuState.unk4408++;
            }
        }
        g_menuState.unk4234 = 3;
        FUN_43dfa0(0x22, 11);
        return;
    case 3:
    {
        if (g_menuState.unk4404)
        {
            g_menuState.unk4234 = 1;
            return;
        }
        g_61bf50.count = g_menuState.unk447c + 1;
        g_61bf50.track = g_menuState.unk4474;
        g_61bf50.unkb0 = g_menuState.unk4478;
        sprintf(name, FUN_441170(0x1f), 1);
        int pos = g_61bf50.count;
        int car = g_menuState.unk43f4[g_menuState.unk4238];
        FUN_437cc0(car);
        *(Initials *)&g_61bf50.cars[0].unk04 = *(Initials *)name;
        g_61bf50.cars[0].car = pos--;
        g_61bf50.cars[0].unk00 = 1;
        g_61bf50.cars[0].unk08 = car;
        g_61bf50.cars[0].unk10 = g_menuState.cars[car].unk08;
        for (i = 0; i < g_menuState.unk447c; i++)
        {
            *(Initials *)&g_61bf50.cars[i + 1].unk04 = *(Initials *)g_menuState.aiCars[car - 1].entries[g_menuState.unk4480][i].name;
            g_61bf50.cars[i + 1].unk00 = 0;
            g_61bf50.cars[i + 1].unk10 = g_menuState.aiCars[car - 1].entries[g_menuState.unk4480][i].unk0c;
            g_61bf50.cars[i + 1].car = pos--;
            g_61bf50.cars[i + 1].unk08 = g_menuState.aiCars[car - 1].entries[g_menuState.unk4480][i].unk08;
            g_61bf50.cars[i + 1].unk14 = g_menuState.aiCars[car - 1].entries[g_menuState.unk4480][i].unk10;
            g_61bf50.cars[i + 1].unk18 = g_menuState.aiCars[car - 1].entries[g_menuState.unk4480][i].unk14;
        }
        FUN_43a780(&g_61bf50);
        g_menuState.unk4234 = 4;
        FUN_43dfa0(0, 25);
        return;
    }
    case 4:
        g_menuState.unk4234 = 5;
        FUN_43d500(0);
        return;
    case 5:
        g_menuState.unk4234 = 2;
        return;
    }
}

void FUN_44d070(MenuSlot *slots, int count);

// FUNCTION: STUNTGP_D3D 0x44d030
void FUN_44d030()
{
    for (int i = 0; i < g_menuState.unk423c; i++)
    {
        g_menuState.unk1dab0[i].unk00 = i;
        g_menuState.unk1dab0[i].unk04 = g_menuState.unk1da90[i][0];
        g_menuState.unk1dab0[i].unk08 = g_menuState.unk1da90[i][1];
    }
    FUN_44d070(g_menuState.unk1dab0, g_menuState.unk423c);
}

// Bubble sort, highest unk04 first, then unk08.
// FUNCTION: STUNTGP_D3D 0x44d070
void FUN_44d070(MenuSlot *slots, int count)
{
    for (int i = count - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            int d = slots[j].unk04 - slots[j + 1].unk04;
            if (d == 0)
            {
                d = slots[j].unk08 - slots[j + 1].unk08;
            }
            if (d < 0)
            {
                MenuSlot t = slots[j];
                slots[j] = slots[j + 1];
                slots[j + 1] = t;
            }
        }
    }
}

int FUN_43d0a0(int count, int track);
int FUN_43dc20(int first, int last);
void FUN_43aa50(RaceSetup6 *src, RaceResults6 *dst);
void FUN_44d420();
void FUN_44d4a0();

// GLOBAL: STUNTGP_D3D 0x61c008
RaceSetup6 g_61c008;

// GLOBAL: STUNTGP_D3D 0x61c048
RaceResults6 g_61c048;

// Mode-6 party: the players pick a track, then race rounds until the results page is left.
// FUNCTION: STUNTGP_D3D 0x44d100
void FUN_44d100(PoolObject *object)
{
    int i;
    switch (g_menuState.unk4234)
    {
    case 0:
        for (i = 0; i < 4; i++)
        {
            g_menuState.unk43f4[i] = 0;
        }
        g_menuState.unk4238 = 0;
        g_menuState.unk423c = 0;
        g_menuState.unk1dae0 = 0;
        for (i = 0; i < 4; i++)
        {
            g_menuState.unk1da90[i][0] = 0;
            g_menuState.unk1da90[i][1] = i + 1;
        }
        g_menuState.unk4234 = 1;
        return;
    case 1:
        FUN_43dd90(g_menuState.unk4244);
        FUN_43dfa0(0x18, 0x18);
        g_menuState.unk4234 = 2;
        return;
    case 2:
        if (g_menuState.unk46a8)
        {
            g_menuState.unk4234 = 7;
            return;
        }
        g_menuState.unk4408 = 0;
        for (i = 1; i < 25; i++)
        {
            if ((FUN_4371c0(i, g_menuState.unk4230) || g_menuState.unk0074) &&
                !FUN_43d0a0(g_menuState.unk423c, i))
            {
                g_menuState.unk440c[g_menuState.unk4408] = i;
                g_menuState.unk4408++;
            }
        }
        FUN_44d4a0();
        FUN_43dd90(g_menuState.unk46ac[g_menuState.unk4238]);
        FUN_43dfa0(0x1a, 11);
        g_menuState.unk4234 = 3;
        return;
    case 3:
        FUN_44d420();
        if (g_menuState.unk4404)
        {
            g_menuState.unk4234 = g_menuState.unk1dae0 > 0 ? 5 : 1;
            return;
        }
        g_menuState.unk1dae0++;
        g_61c008.count = g_menuState.unk423c;
        for (i = 0; i < g_menuState.unk423c; i++)
        {
            g_61c008.cars[i].unk00 = g_menuState.unk46ac[i];
            g_61c008.cars[i].unk04 = g_menuState.unk43f4[i];
            g_61c008.cars[i].unk08 = g_menuState.unk1da90[i][1];
        }
        g_61c008.track = g_menuState.unk4474;
        g_61c008.unk38 = g_menuState.unk4478;
        FUN_43aa50(&g_61c008, &g_61c048);
        g_menuState.unk4234 = 4;
        FUN_43dfa0(0, 25);
        return;
    case 4:
        if (g_61c048.won)
        {
            g_menuState.unk4234 = 7;
            return;
        }
        for (i = 0; i < g_61c048.count; i++)
        {
            int position = g_61c048.results[i].position;
            g_menuState.unk1da90[i][1] = FUN_43dc20(position, g_61c048.count);
            g_menuState.unk1da90[i][0] += g_menuState.unk1da5c[position - 1][0];
        }
        FUN_44d030();
        g_menuState.unk4234 = 5;
        return;
    case 5:
        FUN_43dfa0(0x1b, 0x21);
        g_menuState.unk4234 = 6;
        return;
    case 6:
        switch (g_menuState.unk1da8c)
        {
        case 2:
            g_menuState.unk4234 = 7;
            return;
        case 1:
            g_menuState.unk4234 = 2;
            FUN_44d4a0();
            return;
        }
        break;
    case 7:
        FUN_43dd90(g_menuState.unk4244);
        FUN_43d500(0);
        g_menuState.unk4234 = 8;
        return;
    case 8:
        FUN_43eef0();
        break;
    }
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
    g_489714 = g_48971c = *(WORD *)(tga + 0xc);
    g_489718 = g_489720 = *(WORD *)(tga + 0xe);
    g_62f5c8 = tga[0x10];
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

int FUN_437790(ScoreEntry *table, int count, Initials *name, int score);
void FUN_437880(int index);
void FUN_4378a0(int index);
void FUN_4378c0(int id);
int FUN_437920(int index);
void FUN_43a2a0(RaceSetup1 *src, RaceResults *dst);
void FUN_43bf30();
void FUN_43bfd0();

// GLOBAL: STUNTGP_D3D 0x61b880
RaceSetup1 g_61b880;

// GLOBAL: STUNTGP_D3D 0x61b940
RaceResults g_61b940;

// Arcade state machine: pick a car, then race node after node of the arcade map.
// FUNCTION: STUNTGP_D3D 0x44b5e0
void FUN_44b5e0(PoolObject *object)
{
    int i;
    int node;
    switch (g_menuState.unk4234)
    {
    case 0:
        g_menuState.unk423c = 1;
        g_menuState.unk4234 = 1;
        g_menuState.unk4238 = 0;
        g_menuState.unk4488 = 0;
        g_menuState.unk4484 = 0;
        g_menuState.unk424c = 0;
        g_menuState.unk4248 = 0;
        g_menuState.unk4250 = 6;
        g_menuState.unk43f4[0] = 0;
        return;
    case 1:
        g_menuState.unk4234 = 2;
        FUN_43dfa0(8, 9);
        return;
    case 2:
        if (g_menuState.unk44d0)
        {
            FUN_43eef0();
            return;
        }
        g_menuState.unk4398 = 0;
        for (i = 1; i < 21; i++)
        {
            if (FUN_437230(i, g_menuState.unk4230) || g_menuState.unk0074)
            {
                g_menuState.unk439c[g_menuState.unk4398] = i;
                g_menuState.unk4398++;
            }
        }
        g_menuState.unk4234 = 3;
        FUN_43dfa0(9, 10);
        return;
    case 3:
        if (g_menuState.unk4394)
        {
            g_menuState.unk4234 = 1;
            return;
        }
        g_menuState.unk448c = 1;
        switch (FUN_437cc0(g_menuState.unk43f4[g_menuState.unk4238]))
        {
        case 1:
            g_menuState.unk4490[0] = 0x10;
            break;
        case 2:
        case 4:
            g_menuState.unk4490[0] = 0x11;
            break;
        case 3:
            g_menuState.unk4490[0] = 0x12;
            break;
        }
        g_menuState.unk4408 = 0;
        g_menuState.unk440c[g_menuState.unk4408] = FUN_437920(g_menuState.unk4490[0]);
        g_menuState.unk4408++;
        FUN_43dfa0(10, 11);
        g_menuState.unk4234 = 4;
        return;
    case 4:
    {
        if (g_menuState.unk4404)
        {
            g_menuState.unk4234 = 2;
            return;
        }
        if (g_menuState.unk4484)
        {
            g_menuState.unk4234 = 8;
            return;
        }
        g_61b880.cars[0].unk00 = 1;
        node = g_menuState.unk4490[g_menuState.unk448c - 1];
        int score = g_menuState.nodes[node].unk00;
        int car = g_menuState.unk43f4[g_menuState.unk4238];
        g_61b880.cars[0].unk08 = car;
        *(Initials *)&g_61b880.cars[0].unk04 = *(Initials *)g_menuState.unk44d4[g_menuState.unk4238];
        g_61b880.cars[0].car = g_menuState.unk4250;
        g_61b880.cars[0].unk10 = g_menuState.cars[car].unk08;
        int pos = 1;
        RaceSetupCar *dst = g_61b880.cars;
        for (i = 0; i < 5; i++)
        {
            if (pos == g_menuState.unk4250)
            {
                pos++;
            }
            dst++;
            *(Initials *)&dst->unk04 = *(Initials *)g_menuState.nodes[node].cars[i].name;
            dst->unk00 = 0;
            dst->unk10 = g_menuState.nodes[node].cars[i].unk0c;
            dst->car = pos;
            dst->unk08 = g_menuState.nodes[node].cars[i].unk08;
            dst->unk14 = g_menuState.nodes[node].cars[i].unk10;
            dst->unk18 = g_menuState.nodes[node].cars[i].unk14;
            pos++;
            if (pos == g_menuState.unk4250)
            {
                pos++;
            }
        }
        g_61b880.track = FUN_437920(node);
        g_61b880.unkac = score;
        g_61b880.unkb0 = g_menuState.unk0114[node][0].time;
        g_61b880.unkb4 = g_menuState.unk0114[node][1].time;
        g_61b880.unkb8 = g_menuState.unk0114[node][2].time;
        g_61b880.unkbc = g_menuState.unk0114[node][3].time;
        FUN_43a2a0(&g_61b880, &g_61b940);
        g_menuState.unk4234 = 5;
        FUN_43dfa0(0, 25);
        return;
    }
    case 5:
        node = g_menuState.unk4490[g_menuState.unk448c - 1];
        FUN_437920(node);
        if (g_61b940.won)
        {
            g_menuState.unk4234 = 8;
            return;
        }
        if (!g_61b940.results[0].position)
        {
            g_menuState.unk4234 = 8;
            return;
        }
        g_menuState.unk1b078 = node;
        *(RaceSetup1 *)g_menuState.unk1b07c = g_61b880;
        *(RaceResults *)(g_menuState.unk1b128 + 0x14) = g_61b940;
        FUN_43dfa0(11, 0x1f);
        g_menuState.unk4234 = 6;
        return;
    case 6:
    {
        node = g_menuState.unk4490[g_menuState.unk448c - 1];
        int track = FUN_437920(node);
        if (g_61b940.results[0].position == 1)
        {
            FUN_4378a0(track);
            switch (node)
            {
            case 1:
                FUN_437880(2);
                break;
            case 3:
                FUN_437880(3);
                break;
            case 6:
                FUN_437880(5);
                break;
            case 2:
                FUN_437880(6);
                break;
            case 4:
                FUN_437880(14);
                break;
            case 5:
                FUN_437880(16);
                break;
            }
        }
        g_menuState.unk4250 = FUN_43dc20(g_61b940.results[0].position, 6);
        if (g_61b940.results[0].position > g_menuState.nodes[node].unk08)
        {
            g_menuState.unk4234 = 8;
            return;
        }
        if (g_menuState.nodes[node].unk08 != 1)
        {
            g_menuState.unk4234 = 7;
            FUN_43dfa0(12, 0x28);
            return;
        }
        g_menuState.unk4248 = 1;
        g_menuState.unk4234 = 8;
        FUN_4378c0(node);
        return;
    }
    case 7:
        node = g_menuState.unk4490[g_menuState.unk448c - 1];
        if (node <= 0 || node > 6)
        {
            g_menuState.unk4234 = 4;
            FUN_43dfa0(13, 12);
        }
        return;
    case 8:
    {
        int all = 1;
        for (i = 1; i < 19; i++)
        {
            if (!FUN_4371c0(FUN_437920(i), g_menuState.unk4230))
            {
                all = 0;
            }
        }
        for (i = 7; i < 19; i++)
        {
            if (!g_menuState.unk00ec[i * 2] || !g_menuState.unk00ec[i * 2 + 1])
            {
                all = 0;
            }
        }
        if (all)
        {
            FUN_437880(12);
            FUN_437880(13);
            FUN_437880(17);
        }
        FUN_437790(g_menuState.unk0374, 100, (Initials *)g_menuState.unk44d4[g_menuState.unk4238],
                   g_menuState.unk424c);
        FUN_43bfd0();
        g_menuState.unk45d4 = 0x5f;
        if (g_menuState.unk4248)
        {
            g_menuState.unk45d8 = 0x3b;
            g_menuState.unk45dc = 0x3c;
            g_menuState.unk45e0 = 0.015f;
            g_menuState.unk45e4 = 80.0f;
            g_menuState.unk4234 = 9;
            FUN_43dfa0(14, 0x25);
        }
        else
        {
            g_menuState.unk45d8 = 0x39;
            g_menuState.unk45dc = 0x3a;
            g_menuState.unk45e0 = 0.015f;
            g_menuState.unk45e4 = 0.0f;
            g_menuState.unk4234 = 9;
            FUN_43dfa0(15, 0x25);
        }
        return;
    }
    case 9:
        g_menuState.unk4694.unk00 = 0x1fb;
        g_menuState.unk4694.unk04 = 0;
        g_menuState.unk4694.unk08 = 2;
        g_menuState.unk4694.count = 100;
        g_menuState.unk4694.entries = g_menuState.unk0374;
        g_menuState.unk4234 = 10;
        FUN_43dfa0(0x10, 0x27);
        return;
    case 10:
        FUN_43bf30();
        g_menuState.unk4234 = 11;
        FUN_43dfa0(12, 0x28);
        return;
    case 11:
        g_menuState.unk4234 = 12;
        FUN_43d500(0);
        return;
    case 12:
        FUN_43eef0();
        break;
    }
}
