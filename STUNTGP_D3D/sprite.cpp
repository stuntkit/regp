#include "sprite.h"
#include "d3drender.h"

#include <string.h>

// GLOBAL: STUNTGP_D3D 0x576c38
SpriteDesc g_spriteDesc;

// GLOBAL: STUNTGP_D3D 0x5da370
int g_5da370 = 0;

// Sprite lists bucketed by depth, drawn back to front by FUN_437ed0.
// GLOBAL: STUNTGP_D3D 0x5df194
SpriteLists g_spriteLists;

// GLOBAL: STUNTGP_D3D 0x5df518
int g_5df518 = 0;

// GLOBAL: STUNTGP_D3D 0x5df51c
int g_5df51c = 0;

// GLOBAL: STUNTGP_D3D 0x5df520
int g_5df520 = 0;

// GLOBAL: STUNTGP_D3D 0x5df524
int g_5df524 = 0;

// GLOBAL: STUNTGP_D3D 0x4793d4
int g_4793d4 = -1;

// GLOBAL: STUNTGP_D3D 0x608d34
int g_608d34[20];

// FUNCTION: STUNTGP_D3D 0x437e80
void FUN_437e80()
{
    g_5da370 = 0;
    for (int i = 0; i < 80; i++)
    {
        g_spriteLists.tails[i] = NULL;
        g_spriteLists.heads[i] = NULL;
    }
}

// FUNCTION: STUNTGP_D3D 0x437ec0
void FUN_437ec0()
{
    FUN_437ed0();
    FUN_437e80();
    FUN_441220();
}

// FUNCTION: STUNTGP_D3D 0x437ed0
void FUN_437ed0()
{
    g_5df518 = 0;
    memset(&g_spriteDesc, 0, sizeof(g_spriteDesc));
    g_5df51c = 0;
    g_5df520 = 0;
    g_5df524 = 0;
    g_4793d4 = -1;
    for (int i = 79; i >= 0; i--)
    {
        for (SpriteNode *node = g_spriteLists.heads[i]; node != NULL; node = node->next)
        {
            FUN_437f40(node, i);
        }
    }
}

// STUB: STUNTGP_D3D 0x437f40
void FUN_437f40(SpriteNode *node, int depth)
{
}

// FUNCTION: STUNTGP_D3D 0x441220
void FUN_441220()
{
    for (int i = 0; i < 20; i++)
    {
        g_608d34[i]++;
    }
}

// STUB: STUNTGP_D3D 0x43f6b0
void FUN_43f6b0()
{
}

// FUNCTION: STUNTGP_D3D 0x43d250
void FUN_43d250()
{
    FUN_43f6b0();
    FUN_437ec0();
}
