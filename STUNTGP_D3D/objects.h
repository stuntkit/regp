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
    const char *name; // 0x00
    DWORD type;       // 0x04
    DWORD unk08;      // 0x08
    void (*destroy)(PoolObject *object);
    int (*message)(PoolObject *object, int msg, int arg);
};

// Handlers copied into a PoolObject when it is created.
struct PoolClass
{
    void (*destroy)(PoolObject *object);
    int (*message)(PoolObject *object, int msg, int arg);
};

// Front-end state, cleared as one block by FUN_43dda0.
struct FrontEnd
{
    int state; // 0x00
    // Screen fade in 16.16 fixed point.
    int fade; // 0x04
    // Current and pending screens; the flags mark screens not owned by the pool.
    PoolObject *screen;      // 0x08
    BOOL screenStatic;       // 0x0c
    PoolObject *nextScreen;  // 0x10
    BOOL nextScreenStatic;   // 0x14
    PoolObject *objects[16]; // 0x18
    int objectCount;         // 0x58
    int unk5c;               // 0x5c
    int unk60;               // 0x60
    float unk64;             // 0x64
    float unk68;             // 0x68
    float unk6c;             // 0x6c
    float unk70;             // 0x70
    int unk74;               // 0x74
    int unk78;               // 0x78
    int unk7c;               // 0x7c
    float unk80;             // 0x80
    int unk84;               // 0x84
    float unk88[6];          // 0x88
    float unka0[6];          // 0xa0
    // Player locked to the menu, or 0 for any.
    int lockedPlayer; // 0xb8
    int unkbc;        // 0xbc
    int unkc0;        // 0xc0
    int musicTrack;   // 0xc4
    int unkc8;        // 0xc8
    int unkcc;        // 0xcc
};

extern FrontEnd g_frontEnd;

void Pool_Init();
void Pool_Free(void *ptr);
void *Pool_Alloc(int size);
int FUN_43ef10(int a, int screen);
int FUN_43eef0();
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
