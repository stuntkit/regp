#include "objects.h"

#include <stdlib.h>

extern int g_5ff3e8;
extern int g_5ff4ac;
void FUN_45f8f0(int track, int loop);
int FUN_43eee0(int screen);
void FUN_43dc30(int track);

// GLOBAL: STUNTGP_D3D 0x5fd250
int g_5fd250;

// GLOBAL: STUNTGP_D3D 0x5fd258
Pool g_pool;

// GLOBAL: STUNTGP_D3D 0x5ff3f0
PoolObject *g_5ff3f0;

// GLOBAL: STUNTGP_D3D 0x5ff3f4
BOOL g_5ff3f4;

// GLOBAL: STUNTGP_D3D 0x5ff3f8
PoolObject *g_5ff3f8;

// GLOBAL: STUNTGP_D3D 0x5ff3fc
BOOL g_5ff3fc;

// GLOBAL: STUNTGP_D3D 0x5ff400
PoolObject *g_5ff400[16];

// GLOBAL: STUNTGP_D3D 0x5ff440
int g_5ff440;

// Music track per front-end screen.
// GLOBAL: STUNTGP_D3D 0x5fcab0
int g_5fcab0[64];

// GLOBAL: STUNTGP_D3D 0x6087a0
void *g_6087a0;

// FUNCTION: STUNTGP_D3D 0x43d180
void FUN_43d180()
{
    g_5fd250 = 0;
    FUN_4408f0();
    FUN_43de50();
    FUN_436fb0();
    FUN_437ea0();
    FUN_440c20();
    FUN_43d460();
    FUN_437e50();
}

// FUNCTION: STUNTGP_D3D 0x43d430
void Pool_Init()
{
    for (int i = 0; i < 16; i++)
    {
        g_pool.freeBlocks[i] = (PoolBlockHeader *)g_pool.blocks[i];
    }
    g_pool.freeCount = 16;
    g_pool.allocCount = 0;
}

// FUNCTION: STUNTGP_D3D 0x43d460
void FUN_43d460()
{
}

// FUNCTION: STUNTGP_D3D 0x43d4c0
void Pool_Free(void *ptr)
{
    PoolBlockHeader *block = (PoolBlockHeader *)ptr - 1;
    g_pool.usedBytes -= block->size;
    g_pool.freeBlocks[g_pool.freeCount] = block;
    g_pool.freeCount++;
    g_pool.allocCount--;
}

// FUNCTION: STUNTGP_D3D 0x43ef10
int FUN_43ef10(int a, int screen)
{
    if (screen <= 0 || screen >= 0x29)
    {
        return 0;
    }
    for (int i = 0; i < g_5ff440; i++)
    {
        g_5ff400[i]->destroy(g_5ff400[i]);
        Pool_Free(g_5ff400[i]);
        g_5ff400[i] = NULL;
    }
    g_5ff440 = 0;
    return FUN_43ee40(FUN_43e000(a, screen));
}

// STUB: STUNTGP_D3D 0x43e000
PoolObject *FUN_43e000(int a, int screen)
{
    return NULL;
}

// Queues a screen to replace the current one once the fade-out finishes.
// FUNCTION: STUNTGP_D3D 0x43ee40
int FUN_43ee40(PoolObject *object)
{
    if (g_5ff3f8 && !g_5ff3fc)
    {
        g_5ff3f8->destroy(g_5ff3f8);
        Pool_Free(g_5ff3f8);
    }
    g_5ff3f8 = NULL;
    if (g_5ff3e8 <= 0 || g_5ff3e8 > 3)
    {
        return 0;
    }
    if (object->unk00[2])
    {
        int track = FUN_43eee0(object->unk00[2]);
        if (track != g_5ff4ac)
        {
            FUN_43dc30(track);
            g_5ff4ac = track;
        }
    }
    g_5ff3f8 = object;
    g_5ff3fc = FALSE;
    if (g_5ff3f0)
    {
        g_5ff3f0->message(g_5ff3f0, 0x14, 0);
    }
    g_5ff3e8 = 2;
    return 1;
}

// FUNCTION: STUNTGP_D3D 0x43eee0
int FUN_43eee0(int screen)
{
    return g_5fcab0[screen];
}

// FUNCTION: STUNTGP_D3D 0x43dc30
void FUN_43dc30(int track)
{
    FUN_45f8f0(track, 1);
}

// FUNCTION: STUNTGP_D3D 0x43de50
void FUN_43de50()
{
    if (g_5ff3f0 && !g_5ff3f4)
    {
        g_5ff3f0->destroy(g_5ff3f0);
        Pool_Free(g_5ff3f0);
        g_5ff3f0 = NULL;
    }
    if (g_5ff3f8 && !g_5ff3fc)
    {
        g_5ff3f8->destroy(g_5ff3f8);
        Pool_Free(g_5ff3f8);
        g_5ff3f8 = NULL;
    }
    for (int i = 0; i < g_5ff440; i++)
    {
        g_5ff400[i]->destroy(g_5ff400[i]);
        Pool_Free(g_5ff400[i]);
        g_5ff400[i] = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x436fb0
void FUN_436fb0()
{
}

// FUNCTION: STUNTGP_D3D 0x437e50
void FUN_437e50()
{
}

// FUNCTION: STUNTGP_D3D 0x437ea0
void FUN_437ea0()
{
    FUN_441200();
}

// FUNCTION: STUNTGP_D3D 0x4408f0
void FUN_4408f0()
{
}

// FUNCTION: STUNTGP_D3D 0x440c20
void FUN_440c20()
{
    if (g_6087a0)
    {
        free(g_6087a0);
        g_6087a0 = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x441200
void FUN_441200()
{
}
