#include "mem.h"

#include <stdlib.h>
#include <string.h>

struct MemSlot
{
    char *data;
    void *raw;
    DWORD total;
    DWORD size;
    int type;
    DWORD id;
};

struct MemManager
{
    DWORD type0Bytes;
    DWORD type1Bytes;
    DWORD peakBytes;
    DWORD allocCount;
    DWORD unk10;
    BOOL freeType1;
    MemSlot slots[0x180];
};

// GLOBAL: STUNTGP_D3D 0x589e14
MemManager g_Mem;

// FUNCTION: STUNTGP_D3D 0x42e8d0
void *Mem_Alloc(int size, int type)
{
    MemSlot *slot = g_Mem.slots;
    for (DWORD i = 0; i < 0x180; slot++, i++)
    {
        if (slot->raw == NULL)
        {
            DWORD total = size + 0x24;
            void *raw = malloc(total);
            char *data = (char *)(((DWORD)raw + 0x20) & ~0x1f);
            slot->data = data;
            slot->raw = raw;
            slot->total = total;
            slot->size = size;
            slot->type = type;
            slot->id = g_Mem.allocCount;
            g_Mem.allocCount++;
            if (type == 1)
            {
                g_Mem.type1Bytes += total;
            }
            else
            {
                g_Mem.type0Bytes += total;
            }
            if (g_Mem.type0Bytes + g_Mem.type1Bytes > g_Mem.peakBytes)
            {
                g_Mem.peakBytes = g_Mem.type0Bytes + g_Mem.type1Bytes;
            }
            memset(data, 0, size);
            return data;
        }
    }
    return NULL;
}

// FUNCTION: STUNTGP_D3D 0x42e980
int Mem_Free(void *ptr)
{
    if (ptr != NULL)
    {
        MemSlot *slot = g_Mem.slots;
        for (DWORD i = 0; i < 0x180; slot++, i++)
        {
            if (ptr == slot->data)
            {
                if ((slot->type == 1) && (g_Mem.freeType1 == FALSE))
                {
                    return slot->total;
                }
                DWORD total = slot->total;
                if (slot->type == 1)
                {
                    g_Mem.type1Bytes -= total;
                }
                else
                {
                    g_Mem.type0Bytes -= total;
                }
                free(slot->raw);
                slot->data = NULL;
                slot->raw = NULL;
                slot->total = 0;
                slot->size = 0;
                slot->type = 0;
                slot->id = 0;
                return total;
            }
        }
    }
    return 0;
}
