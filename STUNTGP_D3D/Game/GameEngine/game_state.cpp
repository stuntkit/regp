#include "game_state.h"

// GLOBAL: STUNTGP_D3D 0x498248
GameState g_498248;

// GLOBAL: STUNTGP_D3D 0x4722d0
GameState *g_gameState = &g_498248;

// FUNCTION: STUNTGP_D3D 0x402580
void FUN_402580()
{
    g_gameState = &g_498248;
}

// STUB: STUNTGP_D3D 0x402e90
void FUN_402e90()
{
}
