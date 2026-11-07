#ifndef OBJECTS_H
#define OBJECTS_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct PoolBlockHeader
{
    DWORD magic;
    DWORD size;
};

struct Pool
{
    BYTE blocks[16][0x208];
    int freeCount;
    int allocCount;
    PoolBlockHeader *freeBlocks[16];
    int usedBytes;
    int peakBytes;
};

struct PoolObject
{
    DWORD unk00[3];
    void (*destroy)(PoolObject *object);
};

void Pool_Init();
void Pool_Free(void *ptr);
int FUN_43ef10(int a, int screen);
PoolObject *FUN_43e000(int a, int screen);
int FUN_43ee40(PoolObject *object);
void FUN_43d180();
void FUN_43d460();
void FUN_43de50();
void FUN_436fb0();
void FUN_437e50();
void FUN_437ea0();
void FUN_4408f0();
void FUN_440c20();
void FUN_441200();
#endif /* OBJECTS_H */
