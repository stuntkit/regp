#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "../../globals.h"

int disk_size_of_file(char *path);
int disk_bload(char *path, char *buffer, int size);
void WAD_SplitFileName(char *path, char *dir, char *filename);
void WAD_FlushWadCache();
BOOL WAD_CacheNewWadFile(char *wad);
int bload(char *path, char *buffer, int maxSize);
int WAD_DirDiffers(char *a, char *b);
int size_of_file(char *path);
void FUN_4623c0(char *path, void *buffer, void *arg);
void tolower(char *out, char *in);
int WAD_FindFile(char *wad, char *name, unsigned int *size);
int WAD_NameEquals(char *a, char *b);
int WAD_HashName(char *name);
// int WAD_PrintDir(uchar *param_1);
