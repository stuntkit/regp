#include "objects.h"

#include <stdlib.h>

void FUN_45f8f0(int track, int loop);
int FUN_43eee0(int screen);
void FUN_43dc30(int track);

// GLOBAL: STUNTGP_D3D 0x5fd250
int g_5fd250;

// GLOBAL: STUNTGP_D3D 0x5fd258
Pool g_pool;

// Music track per front-end screen.
// GLOBAL: STUNTGP_D3D 0x5fcab0
int g_5fcab0[64];

// GLOBAL: STUNTGP_D3D 0x6087a0
char *g_6087a0;

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

// FUNCTION: STUNTGP_D3D 0x43d5d0
unsigned int FUN_43d5d0(BYTE *data, int len)
{
    unsigned int hash = 0;
    for (int i = 0; i < len; i++)
    {
        hash = ((hash >> 29) | (hash << 3)) + *data++;
    }
    return hash;
}

// FUNCTION: STUNTGP_D3D 0x43ef10
int FUN_43ef10(int a, int screen)
{
    if (screen <= 0 || screen >= 0x29)
    {
        return 0;
    }
    for (int i = 0; i < g_frontEnd.objectCount; i++)
    {
        g_frontEnd.objects[i]->destroy(g_frontEnd.objects[i]);
        Pool_Free(g_frontEnd.objects[i]);
        g_frontEnd.objects[i] = NULL;
    }
    g_frontEnd.objectCount = 0;
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
    if (g_frontEnd.nextScreen && !g_frontEnd.nextScreenStatic)
    {
        g_frontEnd.nextScreen->destroy(g_frontEnd.nextScreen);
        Pool_Free(g_frontEnd.nextScreen);
    }
    g_frontEnd.nextScreen = NULL;
    if (g_frontEnd.state <= 0 || g_frontEnd.state > 3)
    {
        return 0;
    }
    if (object->unk00[2])
    {
        int track = FUN_43eee0(object->unk00[2]);
        if (track != g_frontEnd.musicTrack)
        {
            FUN_43dc30(track);
            g_frontEnd.musicTrack = track;
        }
    }
    g_frontEnd.nextScreen = object;
    g_frontEnd.nextScreenStatic = FALSE;
    if (g_frontEnd.screen)
    {
        g_frontEnd.screen->message(g_frontEnd.screen, 0x14, 0);
    }
    g_frontEnd.state = 2;
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
    if (g_frontEnd.screen && !g_frontEnd.screenStatic)
    {
        g_frontEnd.screen->destroy(g_frontEnd.screen);
        Pool_Free(g_frontEnd.screen);
        g_frontEnd.screen = NULL;
    }
    if (g_frontEnd.nextScreen && !g_frontEnd.nextScreenStatic)
    {
        g_frontEnd.nextScreen->destroy(g_frontEnd.nextScreen);
        Pool_Free(g_frontEnd.nextScreen);
        g_frontEnd.nextScreen = NULL;
    }
    for (int i = 0; i < g_frontEnd.objectCount; i++)
    {
        g_frontEnd.objects[i]->destroy(g_frontEnd.objects[i]);
        Pool_Free(g_frontEnd.objects[i]);
        g_frontEnd.objects[i] = NULL;
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
