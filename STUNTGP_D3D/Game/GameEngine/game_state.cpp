#include "game_state.h"

#include "../../vecmath.h"

// FUNCTION: STUNTGP_D3D 0x402580
void FUN_402580()
{
    g_4722d0 = g_498248;
}

struct CameraPath
{
    int id;           // 0x00
    BYTE unk04[0x18]; // 0x04
};

// GLOBAL: STUNTGP_D3D 0x624474
CameraPath *g_624474;

// GLOBAL: STUNTGP_D3D 0x624498
DWORD g_624498;

// FUNCTION: STUNTGP_D3D 0x428800
CameraPath *FUN_428800(int id)
{
    for (DWORD i = 0; i < g_624498; i++)
    {
        if (g_624474[i].id == id)
        {
            return &g_624474[i];
        }
    }
    return NULL;
}

// STUB: STUNTGP_D3D 0x402ad0
void FUN_402ad0()
{
}

// STUB: STUNTGP_D3D 0x402b90
void FUN_402b90()
{
}

// STUB: STUNTGP_D3D 0x402c80
void FUN_402c80()
{
}

// FUNCTION: STUNTGP_D3D 0x402e90
void FUN_402e90()
{
    FUN_44f4c0();
    switch (g_4722d0->camMode)
    {
    case 1:
        FUN_402ad0();
        break;
    case 2:
        FUN_402ad0();
        break;
    case 3:
        if (!FUN_428800(1))
        {
            FUN_4028d0(1);
        }
        else
        {
            FUN_402b90();
        }
        break;
    }
    FUN_450190(&g_4722d0->cam);
    g_4722d0->axisX = g_4722d0->cam.matrix[0];
    g_4722d0->axisY = g_4722d0->cam.matrix[1];
    g_4722d0->axisZ = g_4722d0->cam.matrix[2];
    FUN_402c80();
}
