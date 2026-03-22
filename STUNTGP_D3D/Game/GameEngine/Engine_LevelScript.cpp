#include "Engine_LevelScript.h"

// FUNCTION: STUNTGP_D3D 0x42d660
void Script_ParseGameConfig()
{
    int size = {0};
    // char *filename;
    char path[128];
    sprintf(path, "Game.cfg");
    size = size_of_file(path);
    if (size == 0)
    {
        sprintf(path, "D:\\Game\\Game.cfg");
        size = size_of_file(path);
        if (size == 0)
        {
            sprintf(path, "C:\\Game\\Game.cfg");
            size_of_file(path);
        }
    }
    size = size_of_file(path);
    // mem alloc etc
    return;
}
