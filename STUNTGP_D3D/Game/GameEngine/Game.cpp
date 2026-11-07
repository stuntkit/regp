#include "Game.h"
#include "../../d3drender.h"
#include "../../sprite.h"
#include "game_state.h"

// GLOBAL: STUNTGP_D3D 0x612984
int g_frameCount = 0;

// GLOBAL: STUNTGP_D3D 0x61294c
int g_61294c = 0;

// GLOBAL: STUNTGP_D3D 0x612954
DWORD g_612954 = 0;

// GLOBAL: STUNTGP_D3D 0x612958
int g_612958 = 0;

// GLOBAL: STUNTGP_D3D 0x61b630
int g_61b630 = 0;

// TODO: update this based on currrent date and a compile-time define?

#if !defined(REGP_FIXES)
// GLOBAL: STUNTGP_D3D 0x4826a4
const char g_VERSION_DATE[] = "Nov 21 2000";

// GLOBAL: STUNTGP_D3D 0x482698
const char g_VERSION_TIME[] = "16:26:50";
#else
const char g_VERSION_DATE[] = __DATE__;

const char g_VERSION_TIME[] = __TIME__;
#endif

// GLOBAL: STUNTGP_D3D 0x4826b0
const char g_VERSION_FORMAT[] = "Version: %s - %s";

// GLOBAL: STUNTGP_D3D 0x612bf8
static char g_VERSION_STRING[255];

// FUNCTION: STUNTGP_D3D 0x442010
void GetGameBuildVersion()
{
    sprintf(g_VERSION_STRING, g_VERSION_FORMAT, g_VERSION_DATE, g_VERSION_TIME);
#if defined(SGP_DEBUG)
    OutputDebugString(g_VERSION_STRING);
#endif
    return;
}

// FUNCTION: STUNTGP_D3D 0x441d70
void FUN_441d70()
{
    if (g_612be8 == 2)
    {
        g_frameCount++;
        FUN_402e90();
        FUN_432a60();
        FUN_433ee0();
        FUN_4328c0(0);
        FUN_43d250();
        FUN_442a00();
        FUN_442a20();
        FUN_431a80();
        FUN_44fd60();
        FUN_433f20();
    }
}

// STUB: STUNTGP_D3D 0x441f00
void FUN_441f00()
{
}

// STUB: STUNTGP_D3D 0x442120
void FUN_442120()
{
}

// STUB: STUNTGP_D3D 0x442180
void FUN_442180()
{
}

// FUNCTION: STUNTGP_D3D 0x442200
void FUN_442200()
{
    if (g_61294c == 1 && g_612954 >= 18000)
    {
        DWORD alpha = (g_612954 - 18000) >> 1;
        if (alpha > 192)
        {
            alpha = 192;
        }
        g_spriteDesc.flags = 2;
        g_spriteDesc.x = 0.0f;
        g_spriteDesc.y = 0.0f;
        g_spriteDesc.z = 1.0f;
        g_spriteDesc.width = 640.0f;
        g_spriteDesc.height = 480.0f;
        g_spriteDesc.blendMode = 0x48;
        g_spriteDesc.alpha = alpha;
        g_spriteDesc.u0 = 128.0f;
        g_spriteDesc.v0 = 128.0f;
        g_spriteDesc.u1 = 128.0f;
        g_spriteDesc.v1 = 128.0f;
        g_spriteDesc.texture = 10;
        FUN_432e00(&g_spriteDesc);
    }
}

// FUNCTION: STUNTGP_D3D 0x4421f0
int FUN_4421f0()
{
    return 0;
}

// STUB: STUNTGP_D3D 0x442640
void FUN_442640()
{
}

// FUNCTION: STUNTGP_D3D 0x4427b0
void FUN_4427b0()
{
    if (g_612be8 == 1)
    {
        g_frameCount++;
        if (FUN_4421f0() != 1)
        {
            FUN_432a60();
            FUN_433ee0();
            if (g_576bd8 == 1 || g_576be0 != 0)
            {
                FUN_4328c0(0);
            }
            FUN_442640();
            FUN_42e420();
            FUN_432f60();
            FUN_431a80();
            FUN_433f20();
        }
    }
}

// STUB: STUNTGP_D3D 0x442810
void FUN_442810()
{
}

// FUNCTION: STUNTGP_D3D 0x4428a0
void FUN_4428a0()
{
    if (g_61294c == 1 && g_612958 == 1)
    {
        return;
    }
    GameState *gs = g_gameState;
    if (gs->unk1e8 == 0 || gs->unk1f0 < 1)
    {
        return;
    }
    DWORD alpha = gs->unk1f0 * 265 / 100;
    if (alpha > 255)
    {
        alpha = 255;
    }
    g_spriteDesc.flags = 2;
    g_spriteDesc.x = 0.0f;
    g_spriteDesc.y = 0.0f;
    g_spriteDesc.z = gs->unk20c;
    g_spriteDesc.width = 640.0f;
    g_spriteDesc.height = 480.0f;
    g_spriteDesc.blendMode = 0x48;
    g_spriteDesc.alpha = alpha;
    switch (gs->unk1f4)
    {
    case 1:
        g_spriteDesc.u0 = 384.0f;
        g_spriteDesc.v0 = 128.0f;
        g_spriteDesc.u1 = 384.0f;
        g_spriteDesc.v1 = 128.0f;
        g_spriteDesc.texture = g_61b630 == 1 ? 0 : 10;
        break;
    case 2:
        g_spriteDesc.u0 = 128.0f;
        g_spriteDesc.v0 = 128.0f;
        g_spriteDesc.u1 = 128.0f;
        g_spriteDesc.v1 = 128.0f;
        g_spriteDesc.texture = g_61b630 == 1 ? 0 : 10;
        break;
    }
    FUN_432e00(&g_spriteDesc);
}

// FUNCTION: STUNTGP_D3D 0x442a00
void FUN_442a00()
{
    if (g_gameState->unk1e8 == 1 && g_gameState->unk20c != 1.0f)
    {
        FUN_4428a0();
    }
}

// FUNCTION: STUNTGP_D3D 0x442a20
void FUN_442a20()
{
    if (g_gameState->unk1e8 == 1 && g_gameState->unk20c == 1.0f)
    {
        FUN_4428a0();
    }
}
