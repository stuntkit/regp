#include "Engine_LevelScript.h"

// STUB: STUNTGP_D3D 0x42d660
void Script_ParseGameConfig()
{
    void *data;
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
    data = Mem_Alloc(size + 0x20, MEM_NORMAL);
    // TODO: mem alloc etc
    Mem_Free(data);
    return;
}
