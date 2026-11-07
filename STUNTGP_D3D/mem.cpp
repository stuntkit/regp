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

// GLOBAL: STUNTGP_D3D 0x589e10
BOOL g_MemActive;

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

// Frees every slot, newest id first, then marks the manager inactive.
// FUNCTION: STUNTGP_D3D 0x42ea00
void Mem_FreeAll()
{
    if (g_MemActive == TRUE)
    {
        int count = 0;
        DWORD kept = 0;
        DWORD freed = 0;
        int id = 0x180;
        while (id > 0)
        {
            id--;
            for (int i = 0; i < 0x180; i++)
            {
                if (g_Mem.slots[i].data != NULL && g_Mem.slots[i].id == g_Mem.unk10 + id)
                {
                    if (g_Mem.slots[i].type == 1 && g_Mem.freeType1 == FALSE)
                    {
                        kept += g_Mem.slots[i].total;
                        count++;
                    }
                    else
                    {
                        freed += Mem_Free(g_Mem.slots[i].data);
                        count++;
                    }
                }
            }
        }
        g_MemActive = FALSE;
    }
}

// FUNCTION: STUNTGP_D3D 0x42ea80
void Mem_Reset()
{
    Mem_FreeAll();
    g_MemActive = TRUE;
    g_Mem.allocCount = 0;
    g_Mem.unk10 = 0;
}

// FUNCTION: STUNTGP_D3D 0x42eaa0
void FUN_42eaa0()
{
    Mem_FreeAll();
}

// FUNCTION: STUNTGP_D3D 0x42eab0
void Mem_Init()
{
    memset(g_Mem.slots, 0, sizeof(g_Mem.slots));
    g_MemActive = FALSE;
    g_Mem.type0Bytes = 0;
    g_Mem.type1Bytes = 0;
    g_Mem.peakBytes = 0;
    g_Mem.allocCount = 0;
    g_Mem.unk10 = 0;
    g_Mem.freeType1 = FALSE;
    Mem_Reset();
}

// FUNCTION: STUNTGP_D3D 0x42eaf0
void Mem_Shutdown()
{
    g_Mem.freeType1 = TRUE;
    Mem_FreeAll();
}
