#include "Engine_LevelScript.h"

// The original keeps EBP frames everywhere (/Oy-). Drop this once the global flags do.
#pragma optimize("y", off)

// FUNCTION: STUNTGP_D3D 0x42d060
void FUN_42d060(char *script, char *key)
{
}

// STUB: STUNTGP_D3D 0x42d2e0
void Script_ParseGameConfigBuffer(char *script)
{
}

// FUNCTION: STUNTGP_D3D 0x42d660
void Script_ParseGameConfig()
{
    char path[128];

    // STRING: STUNTGP_D3D 0x477b3c
    sprintf(path, "Game.cfg");
    if (size_of_file(path) == 0)
    {
        // STRING: STUNTGP_D3D 0x477b48
        sprintf(path, "D:\\Game\\Game.cfg");
        if (size_of_file(path) == 0)
        {
            // STRING: STUNTGP_D3D 0x477b5c
            sprintf(path, "C:\\Game\\Game.cfg");
            size_of_file(path);
        }
    }

    int size = size_of_file(path);
    char *script = (char *)Mem_Alloc(size + 32, 0);
    bload(path, script, size);
    // STRING: STUNTGP_D3D 0x477b70
    FUN_42d060(script, "ClogMeister");
    Script_ParseGameConfigBuffer(script);
    Mem_Free(script);
}
