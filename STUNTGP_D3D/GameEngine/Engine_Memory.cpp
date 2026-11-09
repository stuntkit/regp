#include "Engine_Memory.h"

// GLOBAL: STUNTGP_D3D 0X589e2c
Mem_Entry MEM_DATA[MEM_SIZE];

// GLOBAL: STUNTGP_D3D 0X589e10
int MEM_INITIALIZED;

// GLOBAL: STUNTGP_D3D 0X589e14
int MEM_KIND_NORMAL;

// GLOBAL: STUNTGP_D3D 0X589e18
int MEM_KIND_RESILIENT;

// GLOBAL: STUNTGP_D3D 0X589e1c
int MEM_KIND_TOTAL;

// GLOBAL: STUNTGP_D3D 0x589e20
int MEM_TOTAL_ALLOCATIONS;
// GLOBAL: STUNTGP_D3D 0x589e24
int MEM_ALWAYS_ZERO;

// GLOBAL: STUNTGP_D3D 0x589e28
int MEM_CLEANUP_ONCE;

// FUNCTION: STUNTGP_D3D 0x42e8d0
void *Mem_Alloc(size_t size, MemAllocType type)
{
    // Allocates size +0x24 bytes, to return 0x20 bytes aligned pointer
    // finds first free slot
    Mem_Entry *el = MEM_DATA;
    int i = 0;
    do
    {
        if (el->dataWithPadding == NULL)
        {
            int totalSize = size + 0x24;
            void *dataTotal = malloc(totalSize);
            void *dataActual = (void *)((unsigned int)(&dataTotal + 0x20) & 0xffffffe0);
            el->data = dataActual;
            el->dataWithPadding = dataTotal;
            el->totalSize = totalSize;
            el->size = size;
            el->type = type;
            el->number = MEM_TOTAL_ALLOCATIONS;
            MEM_TOTAL_ALLOCATIONS++;
            if (type == MEM_RESILIENT)
            {
                MEM_KIND_RESILIENT++;
            }
            else
            {
                MEM_KIND_NORMAL++;
            }
            if (MEM_KIND_TOTAL < MEM_KIND_NORMAL + MEM_KIND_RESILIENT)
            {
                MEM_KIND_TOTAL = MEM_KIND_NORMAL + MEM_KIND_RESILIENT;
            }
            // TODO zero the allocation
            memset(dataActual, 0, size);
            return dataActual;
        }
        el++;
        i++;
    } while (i < MEM_SIZE);
    return 0x0;
}

// gets optimizzed to dust?
void Mem_CleanupMemoryManager()
{
    Mem_FreeAllMemory();
}

// FUNCTION: STUNTGP_D3D 0x42eaf0
void Mem_CleanupMemoryManager_Once()
{
    MEM_CLEANUP_ONCE = 1;
    Mem_FreeAllMemory();
}

// FUNCTION: STUNTGP_D3D 0x42e980
size_t Mem_Free(void *mem)
{
    Mem_Entry *el = MEM_DATA;
    int i = 0;
    if (mem != NULL)
    {
        do
        {
            if (mem == el->data)
            {
                if ((el->type == MEM_RESILIENT) && (MEM_CLEANUP_ONCE == 0))
                {
                    return el->totalSize;
                }
                size_t totalSize = el->totalSize;
                if (el->type == MEM_RESILIENT)
                {
                    MEM_KIND_RESILIENT--;
                }
                else
                {
                    MEM_KIND_NORMAL--;
                }
                free(el->dataWithPadding);
                el->data = NULL;
                el->dataWithPadding = NULL;
                el->totalSize = 0;
                el->size = 0;
                el->type = MEM_NORMAL;
                el->number = 0;
                return totalSize;
            }
            el++;
            i++;
        } while (i < MEM_SIZE);
    }
    return 0;
}

// STUB: STUNTGP_D3D 0x42ea00
void Mem_FreeAllMemory()
{
}

// FUNCTION: STUNTGP_D3D 0x42ea80
void Mem_InitMemoryManager()
{
    Mem_FreeAllMemory();
    MEM_INITIALIZED = 1;
    MEM_TOTAL_ALLOCATIONS = 0;
    MEM_ALWAYS_ZERO = 0;
}

// FUNCTION: STUNTGP_D3D 0x42eab0
void Mem_InitMemoryManager_Once()
{
    // TODO: loop sth
    // TODO: this might be inlined array cleanup
    memset(MEM_DATA, 0, sizeof(MEM_DATA));
    MEM_INITIALIZED = 0;
    MEM_KIND_NORMAL = 0;
    MEM_KIND_RESILIENT = 0;
    MEM_KIND_TOTAL = 0;
    MEM_TOTAL_ALLOCATIONS = 0;
    MEM_ALWAYS_ZERO = 0;
    MEM_CLEANUP_ONCE = 0;
    Mem_InitMemoryManager();
}
