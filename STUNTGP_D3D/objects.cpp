#include "objects.h"

#include <stdlib.h>

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

// STUB: STUNTGP_D3D 0x43ee40
int FUN_43ee40(PoolObject *object)
{
    return 0;
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
